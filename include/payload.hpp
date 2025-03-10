// Object to store payload returned from web call.
// RETCODE - INT
// RESOLVED - BOOL
// SSL Valid - BOOL (possible string for what it should be per cert)
// SSL Expiry - INT (days left before expires)

#ifndef PAYLOAD_H
#define PAYLOAD_H

#include <string>

class payload {
public:
	//Constructor
	payload(std::string TargetURL);

	//Destructor
	~payload();

	bool isvalid();

private:
	int webcall();

	// Collect the verbose curl output as string instead of file.
	size_t write_string(void* ptr, size_t size, size_t nmemb, std::string* data);

	//Private variables.
	std::string URL;
	int RETCODE;
	bool SSLVALID;
	int SSLEXPIRY;
	int VALID;
};

#endif // PAYLOAD_H