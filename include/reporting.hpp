// Object to handle reporting.

#ifndef REPORTING_H
#define REPORTING_H

#include <string>
#include "configuration.hpp"
#include "payload.hpp"

class reporting {
public:
	//Constructor
	reporting(configuration conf, payload results);

	//Destructor
	~reporting();

	//Returns 0 if no need for alerts. 1 if need to alert.
	int getRetcode();

	void trigger(); //Triggers the alerts to be configured later.

private:
	//Private variables of objects.
	configuration conf;
	payload results;

	bool RETCODE_Compare(); // Compare return code to expected retcode, Return false if different.
	bool SSLVALID(); //Return false if SSL is invalid or nonexistant (http).
	bool SSLEXPIRYWARNING(); //Return false if SSL is expiring within the configured range.
};

#endif // REPORTING_H