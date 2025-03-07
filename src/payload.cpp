// Object to store payload returned from web call.
// RETCODE - INT
// RESOLVED - BOOL
// SSL Valid - BOOL (possible string for what it should be per cert)
// SSL Expiry - INT (days left before expires)

#include "payload.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <curl/curl.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <chrono>
#include <ctime>

payload::payload(std::string TargetURL) {
    URL = TargetURL;
    webcall(URL);
}
payload::~payload() {}

int payload::webcall(std::string URL) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Error initializing curl" << std::endl;
        return 1;
    }

    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L); // Enable SSL verification
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L); // Verify hostname

    CURLcode res = curl_easy_perform(curl);
    long httpCode = 0;

    if (res == CURLE_OK) {
        RESOLVED = true;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        RETCODE = static_cast<int>(httpCode);
        std::cout << "URL resolved. HTTP code: " << RETCODE << std::endl;

        // Get SSL certificate information
        struct curl_slist* certinfo = nullptr;
        res = curl_easy_getinfo(curl, CURLINFO_CERTINFO, &certinfo);

        if (res == CURLE_OK && certinfo && certinfo->data) {
            X509* cert = nullptr;
            BIO* certbio = BIO_new_mem_buf(certinfo->data, -1);
            if (certbio) {
                cert = PEM_read_bio_X509(certbio, nullptr, nullptr, nullptr);
                BIO_free(certbio);
            }

            if (cert) {
                SSLVALID = true;
                char* subject = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
                std::cout << "SSL certificate subject: " << subject << std::endl;
                OPENSSL_free(subject);

                const ASN1_TIME* notAfter = X509_get_notAfter(cert);
                if (notAfter) {
                    BIO* bio = BIO_new(BIO_s_mem());
                    ASN1_TIME_print(bio, notAfter);
                    char* timeStr = nullptr;
                    long len = BIO_get_mem_data(bio, &timeStr);
                    std::string timeString(timeStr, len);
                    BIO_free_all(bio);

                    std::tm tm = {};
                    std::stringstream ss(timeString);
                    ss >> std::get_time(&tm, "%b %d %H:%M:%S %Y %Z");
                    if (ss.fail()) {
                        std::cerr << "Error parsing certificate expiration time." << std::endl;
                    }
                    else {
                        auto expirationTime = std::chrono::system_clock::from_time_t(std::mktime(&tm));
                        auto now = std::chrono::system_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::days>(expirationTime - now);
                        SSLEXPIRY = static_cast<int>(duration.count());
                        std::cout << "SSL certificate expires in " << SSLEXPIRY << " days." << std::endl;
                    }
                }

                X509_free(cert);
            }
            else {
                std::cerr << "Error parsing SSL certificate." << std::endl;
            }

            curl_slist_free_all(certinfo);
        }
        else {
            std::cout << "Could not retrieve certificate information." << std::endl;
        }

    }
    else {
        std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
    }

    curl_easy_cleanup(curl);
	return 0;
}
