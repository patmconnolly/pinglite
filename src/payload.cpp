// Object to store payload returned from web call.
// RETCODE - INT
// RESOLVED - BOOL
// SSL Valid - BOOL (possible string for what it should be per cert)
// SSL Expiry - INT (days left before expires)

#include "payload.hpp"
#include <iostream>
#include <string>

payload::payload(std::string TargetURL) {
    URL = TargetURL;
    webcall(URL);
}
payload::~payload() {}

int payload::webcall(std::string URL) {
	return 0;
}