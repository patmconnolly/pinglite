// Object to store payload returned from web call.
// RETCODE - INT
// RESOLVED - BOOL
// SSL Valid - BOOL (possible string for what it should be per cert)
// SSL Expiry - INT (days left before expires)

#include "payload.hpp"
#include "function.hpp"
#include <string>
#include <curl/curl.h>
#include <chrono>
#include <sstream>
#include <iomanip>

payload::payload(std::string TargetURL) {
    this->URL = TargetURL;
    this->VALIDWEBCALL = webcall();
}
payload::~payload() {}

//Get functions for data.
int payload::getRETCODE() { return this->RETCODE; }
int payload::getSSLEXPIRY() { return this->SSLEXPIRY; }
bool payload::getSSLVALID() { return this->SSLVALID; }
bool payload::validWebcall() { return this->VALIDWEBCALL; }
bool payload::isINSECURE() { return this->INSECURE; }

//Private functions for backend work.
bool payload::webcall() {
    auto handle = curl_easy_init();

    bool SUCCESS = true;

    long retcode;
    long certinvalid;
    std::string scheme = this->URL.substr(0, this->URL.find("://"));
    bool insecure;
    std::string ErrorText = "";
    std::string stderr_buffer; //String to store stderr data for later parsing.

    if (scheme == "https") {
        insecure = false;
    }
    else {
        insecure = true;
    }

    if (!handle) {
        function::error("Error initializing curl!");
        SUCCESS = false;
    }
    else {
        //Declaring variable for response.
        CURLcode res;
        
        curl_easy_setopt(handle, CURLOPT_URL, this->URL.c_str()); //Set URL
        curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L); //Follow redirects
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L); //Enable SSL verification
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0L); //Verify Hostname
        curl_easy_setopt(handle, CURLOPT_VERBOSE, 1L); //Enable verbose to collect SSL expiry date exactly.
        curl_easy_setopt(handle, CURLOPT_DEBUGFUNCTION, payload::debug_function); //
        curl_easy_setopt(handle, CURLOPT_DEBUGDATA, &stderr_buffer); //
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, payload::discard_data);
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, nullptr);


        //--------Actual Call
        res = curl_easy_perform(handle);
        ErrorText = curl_easy_strerror(res); //Tracer turned error message.
        //--------End Actual Call

        if (ErrorText.find("No error") != std::string::npos) {
            //Collect retcode.
            res = curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &retcode);
            this->RETCODE = retcode;
            function::info("HTTP Return Code is: ", std::to_string(RETCODE), ".");

            //Collect Cert Information
            if (insecure) {
                this->SSLVALID = false;
                this->SSLEXPIRY = 0;
                this->INSECURE = true;
                function::warning("Insecure protocol!");
            }
            else {
                this->INSECURE = false;
                res = curl_easy_getinfo(handle, CURLINFO_SSL_VERIFYRESULT, &certinvalid);

                //Validate Certificate If Applicable
                if (certinvalid) {
                    this->SSLVALID = false;
                    function::error("SSL Cert is Invalid!");
                }
                else {
                    this->SSLVALID = true;
                    function::info("SSL Cert is Valid.");
                }

                //Check certificate expiry date.
                std::string DateTimeString = payload::getDate(stderr_buffer);
                this->SSLEXPIRY = payload::calculateDaysDifferenceInt(DateTimeString);
                function::info("SSL Cert Expires on: ", DateTimeString);
                if (this->SSLEXPIRY < 0) {
                    function::error("SSL Cert is Expired!");
                }
                else {
                    function::info("SSL Cert Expires in ", std::to_string(this->SSLEXPIRY), " days.");
                }
            }

        }
        else {
            function::error("There was a problem with the call!");
            function::error(ErrorText);
            SUCCESS = false;
        }
    }
    curl_easy_cleanup(handle);
	return SUCCESS;
}

int payload::calculateDaysDifferenceInt(const std::string& dateTimeString) {

    const int hoursInDay = 24;
    std::string slimDateTimeString = payload::padSingleDigitDay(payload::removeDoubleSpaces(dateTimeString));

    // Parse the input string
    std::tm tm = {};
    std::istringstream ss(slimDateTimeString);


    ss >> std::get_time(&tm, "%b %d %H:%M:%S %Y");

    if (ss.fail()) {
        function::error("Error parsing date/time string.");
        return -1; // Return -1 days on error
    }

    // Convert tm to time_point
    std::time_t timeT = std::mktime(&tm);
    if (timeT == -1) {
        function::error("Error converting tm to time_t");
        return -1;
    }
    auto parsedTimePoint = std::chrono::system_clock::from_time_t(timeT);

    // Get current time
    auto now = std::chrono::system_clock::now();

    // Calculate duration
    auto duration = parsedTimePoint - now;

    // Convert duration to days and return as int
    auto hoursDifference = std::chrono::duration_cast<std::chrono::hours>(duration);
    int daysDifference = static_cast<int>(hoursDifference.count() / hoursInDay);
    return daysDifference;
}

std::string payload::removeDoubleSpaces(std::string str) {
    size_t pos = 0;
    while ((pos = str.find("  ", pos)) != std::string::npos) {
        str.replace(pos, 2, " ");
    }
    return str;
}

std::string payload::padSingleDigitDay(std::string input) {
    std::stringstream ss(input);
    std::string month, day, time, year;

    ss >> month >> day >> time >> year;

    if (day.length() == 1) {
        day = "0" + day;
    }

    return month + " " + day + " " + time + " " + year;
}

// Collect the verbose curl output as string instead of file.
int payload::debug_function(CURL* handle, curl_infotype type, char* data, size_t size, void* userp) {
    std::string* buffer = static_cast<std::string*>(userp);
    if (type == CURLINFO_TEXT) {
        buffer->append(data, size);
    }
    return 0;
}

//Discard HTML data as that is not needed.
size_t payload::discard_data(void* buffer, size_t size, size_t nmemb, void* userp) {
    return size * nmemb;
}

//Strip expiry date from verbose data.
std::string payload::getDate(const std::string& inputString) {
    std::string ExpireDateText = "expire date: ";
    size_t startPos = inputString.find(ExpireDateText) + ExpireDateText.length();
    size_t endPos = inputString.find('\n', startPos);
    return inputString.substr(startPos, endPos - startPos);
}

