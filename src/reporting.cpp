// Object to handle reporting.

#include <string>
#include <iostream>
#include "reporting.hpp"
#include "configuration.hpp"
#include "payload.hpp"

//Private variables of objects.
// configuration conf;
// payload results;

//Constructor
reporting::reporting(const configuration* conf, const payload* results) {
	this->conf = conf;
	this->results = results;
}

//Destructor
reporting::~reporting() {}

//Returns 0 if no need for alerts. 1 if need to alert.
int reporting::getRetcode() {
	if (RETCODE_Compare() and SSLVALID() and SSLEXPIRYWARNING()) {
		return 0;
	}
	else {
		return 1;
	}
}

//Triggers the alerts to be configured later.
void reporting::trigger() {
	std::cout << "This is a triggered alert, to be implemented later." << std::endl;
}





 // Compare return code to expected retcode, Return false if different.
bool reporting::RETCODE_Compare() {
	if (this->conf->getRETURNCODE() == this->results->getRETCODE()) {
		return true;
	}
	else {
		return false;
	}
}

//Return false if SSL is invalid or nonexistant (http).
bool reporting::SSLVALID() {
	return this->results->getSSLVALID();
}

//Return false if SSL is expiring within the configured range.
bool reporting::SSLEXPIRYWARNING() {
	if (this->payload->getSSLEXPIRY <= this->conf->getSSLEXPIRYREMINDER) {
		return false;
	}
	else {
		return true;
	}
}
