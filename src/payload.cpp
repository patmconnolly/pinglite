// Object to store payload returned from web call.
// RETCODE - INT
// RESOLVED - BOOL
// SSL Valid - BOOL (possible string for what it should be per cert)
// SSL Expiry - INT (days left before expires)

#include "payload.hpp"
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <chrono>
#include <sstream>
#include <iomanip>

payload::payload(std::string TargetURL) {
    this->URL = TargetURL;
    this->VALID = webcall();
}
payload::~payload() {}

int payload::webcall() {
    auto handle = curl_easy_init();

    int failcode = 0;

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
        std::cerr << "Error initializing curl!" << std::endl;
        failcode++;
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
            std::cout << "HTTP Return Code is: " << RETCODE << "." << std::endl;

            //Collect Cert Correct
            res = curl_easy_getinfo(handle, CURLINFO_SSL_VERIFYRESULT, &certinvalid);
            if (certinvalid) {
                this->SSLVALID = false;
                std::cerr << "SSL Cert is Invalid!" << std::endl;
                failcode++;
            }
            else if (not insecure) {
                this->SSLVALID = true;
                std::cout << "SSL Cert is Valid!" << std::endl;
            }
            else {
                this->SSLVALID = false;
                std::cout << "Insecure Protocol!" << std::endl;
            }
        }
        else {
            std::cerr << "There was a problem with the call!" << std::endl;
            std::cerr << ErrorText << std::endl;
            failcode++;
        }

        //Collect Cert Expiry
        if (not insecure and failcode == 0) {
            //Do the thing.
            std::string DateTimeString = payload::getDate(stderr_buffer);
            this->SSLEXPIRY = payload::calculateDaysDifferenceInt(DateTimeString);
            std::cout << "SSL Cert Expires on: " << DateTimeString << std::endl;
            if (this->SSLEXPIRY < 0) {
                failcode++;
            }
            else {
                std::cout << "SSL Cert Expires in " << this->SSLEXPIRY << " days." << std::endl;
            }
        }
    }
    curl_easy_cleanup(handle);
	return failcode;
}

int payload::calculateDaysDifferenceInt(const std::string& dateTimeString) {

    const int hoursInDay = 24;

    // Parse the input string
    std::tm tm = {};
    std::istringstream ss(dateTimeString);


    ss >> std::get_time(&tm, "%b %e %d %H:%M:%S %Y");

    if (ss.fail()) {
        ss.clear(); //Clear the failstate.
        ss.str(dateTimeString); //Reset the stringstream.
        ss >> std::get_time(&tm, "%b %d %H:%M:%S %Y");
    }
    if (ss.fail()) {
        std::cerr << "Error parsing date/time string." << std::endl;
        return -1; // Return -1 days on error
    }

    // Convert tm to time_point
    std::time_t timeT = std::mktime(&tm);
    if (timeT == -1) {
        std::cerr << "Error converting tm to time_t" << std::endl;
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

bool payload::isvalid() {
    if (this->VALID > 0) {
        return false;
    }
    else {
        return true;
    }
}