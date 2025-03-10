// Object to store payload returned from web call.
// RETCODE - INT
// RESOLVED - BOOL
// SSL Valid - BOOL (possible string for what it should be per cert)
// SSL Expiry - INT (days left before expires)

#include "payload.hpp"
#include <iostream>
#include <string>
#include <curl/curl.h>

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

    if (scheme == "https") {
        insecure = false;
    }
    else {
        insecure = true;
    }

    if (!handle) {
        std::cerr << "Error initializing curl!" << std::endl;
        failcode = 1;
    }
    else {
        //Declaring variable for response.
        CURLcode res;
        
        curl_easy_setopt(handle, CURLOPT_URL, this->URL.c_str()); //Set URL
        curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L); //Follow redirects
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L); //Enable SSL verification
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0L); //Verify Hostname
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, payload::discard_data); //We actually don't care about the HTML.
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, NULL); //So we discard it with these two lines.


        //--------Actual Call
        res = curl_easy_perform(handle);
        ErrorText = curl_easy_strerror(res); //Tracer turned error message.
        //--------End Actual Call

        if (ErrorText.contains("No error")) {
            //Collect retcode.
            res = curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &retcode);
            this->RETCODE = retcode;
            std::cout << "HTTP Return Code is: " << RETCODE << "." << std::endl;

            //Collect Cert Correct
            res = curl_easy_getinfo(handle, CURLINFO_SSL_VERIFYRESULT, &certinvalid);
            if (certinvalid) {
                this->SSLVALID = false;
                std::cerr << "SSL Cert is Invalid!" << std::endl;
                failcode = 1;
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
            failcode = 1;
        }

        //Collect Cert Expiry


    }
    curl_easy_cleanup(handle);
	return failcode;
}

// Dummy write function to discard data
size_t payload::discard_data(void* buffer, size_t size, size_t nmemb, void* userp) {
    return size * nmemb; // Indicate that all data was written (discarded)
}

int payload::isvalid() {
    return this->VALID;
}