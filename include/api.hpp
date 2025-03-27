// Object to handle API calls.

#ifndef API_H
#define API_H

#include <string>
#include "api.hpp"

class api {
public:
	//Constructor
	api(std::string URL, std::string PAYLOADFILE);

	//Destructor
	~api();

	void updatePlaceholders(std::string HOST, int HTTPCODE, bool SSLVALID, int SSLEXPIRYDAYS, std::string ALERTSTRING);
	void trigger();

private:
	//Private Variables
	std::string URL;
	std::string PAYLOADFILE;
	std::string PAYLOAD;

	// CONSTANT Variables in JSON Payload
	const std::string placeholder_HOST = "{{ HOST }}";
	const std::string placeholder_HTTPCODE = "{{ HTTP_CODE }}";
	const std::string placeholder_SSLVALID = "{{ SSL_VALID }}";
	const std::string placeholder_SSLEXPIRYDAYS = "{{ SSL_EXPIRY_DAYS }}";
	const std::string placeholder_ALERTSTRING = "{{ ALERT_STRING }}";

	//Private Functions
	std::string replace_string(const std::string& original, const std::string& placeholder, const std::string& replacement);
};

#endif // API_H