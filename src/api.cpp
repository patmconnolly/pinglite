// Object to handle API calls.

#include <string>
#include <fstream>
#include <curl/curl.h>
#include "api.hpp"
#include "function.hpp"

// Constructor
api::api(std::string URL, std::string PAYLOADFILE) {
	this->URL = URL;
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

    function::debug("     API URL: ", this->URL);
    function::debug("PAYLOAD FILE: ", this->PAYLOADFILE);
    function::debug("JSON PAYLOAD: \n", this->PAYLOAD);
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
