// Object to store configuration pulled from file.

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>

class configuration {
public:
	//Constructor
	configuration();

	//Add more config files
	int update(std::string confFile);

	//Ensure final configuration is valid
	int validate();

	//Return variable data.
	std::string getHOST();
	int getRETURNCODE();
	int getSSLVALID();
	int getSSLEXPIRYREMINDER();
	std::string getREPORTINGMETHOD();
	int getSSLEXPIRYSNOOZE();
	int getALERTSNOOZE();
	std::string getAPIURL();
	std::string getAPIPAYLOAD();

	//Destructor
	~configuration();

private:
	//Private variables
	std::string HOST;
	int RETURNCODE;
	int SSLVALID;
	int SSLEXPIRYREMINDER;
	std::string REPORTINGMETHOD = "NONE";
	int SSLEXPIRYSNOOZE; //How many days after previous alert to remind you SSL cert is expiring soon.
	int ALERTSNOOZE; //How many minutes after previous alert to wait before alerting again.
	std::string APIURL = "";
	std::string APIPAYLOAD = "";
};

#endif // CONFIGURATION_H