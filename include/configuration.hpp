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
	const std::string getHOST();
	const int getRETURNCODE();
	const int getSSLVALID();
	const int getSSLEXPIRYREMINDER();
	const std::string getREPORTINGMETHOD();

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