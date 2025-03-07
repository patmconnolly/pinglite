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

private:
	int webcall();

	//Private variables.
	std::string URL;
	int RETCODE;
	bool SSLVALID;
	int SSLEXPIRY;
};

#endif // PAYLOAD_H