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
    URL = TargetURL;
    webcall(URL);
}
payload::~payload() {}

int payload::webcall(std::string URL) {
    auto handle = curl_easy_init();

    long retcode;
    long certvalid;

    if (!handle) {
        std::cout << "Error initializing curl!" << std::endl;
    }
    else {
        //Declaring variable for response.
        CURLcode res;

        curl_easy_setopt(handle, CURLOPT_URL, URL);
        curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L); //Follow redirects
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 1L); //Enable SSL verification
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 2L); //Verify Hostname


        //--------Actual Call
        res = curl_easy_perform(handle);
        //--------End Actual Call


        //Collect retcode.
        curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &retcode);
        this->RETCODE = retcode;
        std::cout << "HTTP Return Code is: " << RETCODE << "." << std::endl;

        //Collect Cert Correct
        res = curl_easy_getinfo(handle, CURLINFO_SSL_VERIFYRESULT, &certvalid);
        if (!res) {
            this->SSLVALID = false;
            std::cout << "SSL Cert is Invalid!" << std::endl;
        }
        else {
            this->SSLVALID = true;
            std::cout << "SSL Cert is Valid!" << std::endl;
        }

        //Collect Cert Expiry


    }
    curl_easy_cleanup(handle);
	return 0;
}