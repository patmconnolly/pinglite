// Object to handle reporting.

#include <string>
#include "reporting.hpp"
#include "configuration.hpp"
#include "payload.hpp"
#include "function.hpp"
#include "api.hpp"

//Private variables of objects.
// configuration conf;
// payload results;

//Constructor
reporting::reporting(configuration* conf, payload* results) {
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
void reporting::trigger(std::string ALERTTEXT) {
	if (this->conf->getREPORTINGMETHOD() == "TEST") {
		function::debug("Host ----------------: ", this->conf->getHOST());
		function::debug(ALERTTEXT);
		function::debug("Return Code ---------: ", std::to_string(this->getHTTPCODE()));
		function::debug("Certificate Valid ---: ", function::stringifyBoolean(this->SSLVALID()));
		function::debug("Certificate Expires in ", std::to_string(this->getEXPIRY()), " days.");
	}
	else if (this->conf->getREPORTINGMETHOD() == "API") {
		api* handler = new api(conf->getAPIURL(), conf->getAPIPAYLOAD());
		handler->updatePlaceholders(this->conf->getHOST(), this->getHTTPCODE(), this->SSLVALID(), this->getEXPIRY(), ALERTTEXT);
		handler->trigger();
		delete handler;
	}
}

 // Compare return code to expected retcode, Return false if different.
bool reporting::RETCODE_Compare() {
	if (this->conf->getRETURNCODE() == this->results->getRETCODE()) {
		function::info("HTTP Return Code Is As Expected.");
		return true;
	}
	else {
		function::error("HTTP Return Code Is NOT As Expected!");
		return false;
	}
}

//Return false if SSL is invalid or nonexistant (http).
bool reporting::SSLVALID() {
	return this->results->getSSLVALID();
}

//Return false if SSL is expiring within the configured range.
bool reporting::SSLEXPIRYWARNING() {
	if (this->results->getSSLEXPIRY() <= this->conf->getSSLEXPIRYREMINDER()) {
		return false;
	}
	else {
		return true;
	}
}

int reporting::getAlertSnooze()
{
	return this->conf->getALERTSNOOZE();
}

int reporting::getWarnSnooze()
{
	return this->conf->getSSLEXPIRYSNOOZE();
}

int reporting::getHTTPCODE()
{
	return this->results->getRETCODE();
}

int reporting::getEXPIRY()
{
	return this->results->getSSLEXPIRY();
}