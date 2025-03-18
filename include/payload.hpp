// Object to store payload returned from web call.
// RETCODE - INT
// RESOLVED - BOOL
// SSL Valid - BOOL (possible string for what it should be per cert)
// SSL Expiry - INT (days left before expires)

#ifndef PAYLOAD_H
#define PAYLOAD_H

#include <string>
#include <curl/curl.h>

class payload {
public:
	//Constructor
	payload(std::string TargetURL);

	//Destructor
	~payload();

	bool isvalid();
	int getRETCODE();
	int getSSLEXPIRY();

	bool validWebcall();
	bool getSSLVALID();
	bool isINSECURE();


private:
	bool webcall();

	// Collect the verbose curl output as string instead of file.
	static int debug_function(CURL* handle, curl_infotype type, char* data, size_t size, void* userp);
	//Discard HTML data as that is not needed.
	static size_t discard_data(void* buffer, size_t size, size_t nmemb, void* userp);

	//Strip expiry date from verbose data.
	static std::string getDate(const std::string& inputString);

	static int calculateDaysDifferenceInt(const std::string& dateTimeString);

	static std::string removeDoubleSpaces(std::string str);

	static std::string padSingleDigitDay(std::string input);

	//Private variables.
	std::string URL;
	int RETCODE;
	bool SSLVALID;
	int SSLEXPIRY;
	bool VALIDWEBCALL;
	bool INSECURE;
};

#endif // PAYLOAD_H