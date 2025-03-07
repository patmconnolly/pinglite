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
    webcall();
}
payload::~payload() {}

int payload::webcall() {
    auto handle = curl_easy_init();

    long retcode;
    long certinvalid;
    std::string scheme = this->URL.substr(0, this->URL.find("://"));
    bool insecure;

    if (scheme == "https") {
        insecure = false;
    }
    else {
        insecure = true;
    }

    if (!handle) {
        std::cout << "Error initializing curl!" << std::endl;
    }
    else {
        //Declaring variable for response.
        CURLcode res;
        
        curl_easy_setopt(handle, CURLOPT_URL, this->URL.c_str());
        curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L); //Follow redirects
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L); //Enable SSL verification
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0L); //Verify Hostname


        //--------Actual Call
        res = curl_easy_perform(handle);
        //--------End Actual Call


        //Collect retcode.
        res = curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &retcode);
        this->RETCODE = retcode;
        std::cout << "HTTP Return Code is: " << RETCODE << "." << std::endl;

        //Collect Cert Correct
        res = curl_easy_getinfo(handle, CURLINFO_SSL_VERIFYRESULT, &certinvalid);
        if (certinvalid) {
            this->SSLVALID = false;
            std::cout << "SSL Cert is Invalid!" << std::endl;
        }
        else if (not insecure) {
            this->SSLVALID = true;
            std::cout << "SSL Cert is Valid!" << std::endl;
        }
        else {
            this->SSLVALID = false;
            std::cout << "Insecure Protocol!" << std::endl;
        }

        //Collect Cert Expiry


    }
    curl_easy_cleanup(handle);
	return 0;
}