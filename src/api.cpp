// Object to handle API calls.
// Copyright(C) 2025 Patrick Connolly
//
// This program is free software : you can redistribute it and /or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation version 3 of the License.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.If not, see < https://www.gnu.org/licenses/>.

#include <string>
#include <fstream>
#include <curl/curl.h>
#include "api.hpp"
#include "function.hpp"

// Constructor
api::api(std::string URL, std::string HEADERS, std::string PAYLOADFILE) {
	this->URL = URL;
    this->HEADERS = function::stripQuotesIfExist(HEADERS);
	this->PAYLOADFILE = PAYLOADFILE;
    std::ifstream json_file(this->PAYLOADFILE, std::ios::in | std::ios::binary);
    if (!json_file.is_open()) { function::error("CANNOT OPEN JSON FILE: ", this->PAYLOADFILE); return; }
    this->PAYLOAD.assign((std::istreambuf_iterator<char>(json_file)), (std::istreambuf_iterator<char>()));
    json_file.close();
}

// Destructor
api::~api() {}

void api::trigger() {
    // Set CURL to Trigger Payload Here
    auto handle = curl_easy_init();
    struct curl_slist* headers = nullptr;
    std::string ErrorText = "";

    if (!handle) {
        function::error("Error initializing curl!");
    }
    else {
        CURLcode res; //Variable for response.
        curl_easy_setopt(handle, CURLOPT_URL, this->URL.c_str()); //Set URL
        
        headers = curl_slist_append(headers, this->HEADERS.c_str());

        curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(handle, CURLOPT_POST, 1L);

        curl_easy_setopt(handle, CURLOPT_POSTFIELDS, this->PAYLOAD.c_str());

        curl_easy_setopt(handle, CURLOPT_POSTFIELDSIZE, (long)this->PAYLOAD.length());

        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, function::discard_data);

        // Actual CURL Call
        res = curl_easy_perform(handle);
        ErrorText = curl_easy_strerror(res);

        if (ErrorText.find("No error") != std::string::npos) {
            function::debug("CURL command succeeded.");
        }
        else {
            function::error("CURL command failed to hit reporting target!");
            function::error(ErrorText);
        }

        curl_slist_free_all(headers);
    }
    curl_easy_cleanup(handle);
}

void api::updatePlaceholders(std::string HOST, int HTTPCODE, bool SSLVALID, int SSLEXPIRYDAYS, std::string ALERTSTRING)
{
    // Update Host
    this->PAYLOAD = this->replace_string(this->PAYLOAD, this->placeholder_HOST, HOST);

    // Update HTTPCODE
    this->PAYLOAD = this->replace_string(this->PAYLOAD, this->placeholder_HTTPCODE, std::to_string(HTTPCODE));

    // Update SSL Valid
    this->PAYLOAD = this->replace_string(this->PAYLOAD, this->placeholder_SSLVALID, function::stringifyBoolean(SSLVALID));

    // Update SSL Expiry Days
    this->PAYLOAD = this->replace_string(this->PAYLOAD, this->placeholder_SSLEXPIRYDAYS, std::to_string(SSLEXPIRYDAYS));

    // Update Alert String
    this->PAYLOAD = this->replace_string(this->PAYLOAD, this->placeholder_ALERTSTRING, ALERTSTRING);
}

std::string api::replace_string(const std::string& original, const std::string& placeholder, const std::string& replacement) {
    std::string result = original;
    size_t pos = result.find(placeholder);
    while (pos != std::string::npos) {
        result.replace(pos, placeholder.length(), replacement);
        pos = result.find(placeholder, pos + replacement.length());
    }
    return result;
}
