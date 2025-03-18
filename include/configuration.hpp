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

	//Destructor
	~configuration();

private:
	//Private variables
	std::string HOST;
	int RETURNCODE;
	int SSLVALID;
	int SSLEXPIRYREMINDER;
	std::string REPORTINGMETHOD = "NONE";
};

#endif // CONFIGURATION_H