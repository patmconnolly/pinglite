// Object to store configuration pulled from file.
#include <iostream>
#include <string>
#include "../third-party/inih/cpp/INIReader.h"
#include "configuration.hpp"

configuration::configuration() {
	this->HOST = "httpx://EMPTY";
	this->RETURNCODE = -1;
	this->SSLVALID = -1;
	this->SSLEXPIRYREMINDER = -1;
}

int configuration::update(std::string confFile) {
	INIReader reader(confFile);

	if (reader.ParseError() < 0) {
		std::cerr << "Cannot load config file: " << confFile << "." << std::endl;
		return 1;
	}

	std::string tempHOST;
	int tempRETCODE;
	int tempSSLVALID;
	int tempSSLEXPIRYREMINDER;
	std::string tempREPORTINGMETHOD;

	//Attempt to grab known variables, continue if cannot collect

	//---HOST
	tempHOST = reader.Get("CHECK", "HOST", "");
	if (tempHOST != "") {
		this->HOST = tempHOST;
		std::cout << "Collected HOST Variable." << std::endl;
	}
	else {
		std::cerr << "No HOST Variable Defined." << std::endl;
	}

	//---RETURNCODE
	tempRETCODE = reader.GetInteger("VALIDATION", "RETURNCODE", -1);
	if (tempRETCODE != -1) {
		this->RETURNCODE = tempRETCODE;
		std::cout << "Collected RETURNCODE Variable." << std::endl;
	}
	else {
		std::cerr << "No RETURNCODE Variable Defined." << std::endl;
	}

	//---SSLVALID
	tempSSLVALID = reader.GetInteger("VALIDATION", "SSLVALID", -1);
	if (tempSSLVALID != -1) {
		this->SSLVALID = tempSSLVALID;
		std::cout << "Collected SSLVALID Variable." << std::endl;
	}
	else {
		std::cerr << "No SSLVALID Variable Defined." << std::endl;
	}

	//---SSLEXPIRYREMINDER
	tempSSLEXPIRYREMINDER = reader.GetInteger("VALIDATION", "SSLEXPIRYREMINDER", -1);
	if (tempSSLEXPIRYREMINDER != -1) {
		this->SSLEXPIRYREMINDER = tempSSLEXPIRYREMINDER;
		std::cout << "Collected SSLEXPIRYREMINDER Variable." << std::endl;
	}
	else {
		std::cerr << "No SSLEXPIRYREMINDER Variable Defined." << std::endl;
	}

	//---REPORTING METHOD
	tempREPORTINGMETHOD = reader.Get("REPORTING", "METHOD", "");
	if (tempREPORTINGMETHOD != "") {
		this->REPORTINGMETHOD = tempREPORTINGMETHOD;
		std::cout << "Collected REPORTINGMETHOD Variable." << std::endl;
	}
	else {
		std::cerr << "No REPORTINGMETHOD Variable Defined." << std::endl;
	}

	return 0;
}

int configuration::validate() {
	bool VALID = true;

	if (this->HOST == "httpx://EMPTY") { VALID = false; std::cerr << "HOST IS INVALID!" << std::endl; }
	if (this->RETURNCODE == -1) { VALID = false; std::cerr << "RETURNCODE IS INVALID!" << std::endl; }
	if (this->SSLVALID == -1) { VALID = false;  std::cerr << "SSLVALID IS INVALID!" << std::endl; }
	if (this->SSLEXPIRYREMINDER == -1) { VALID = false;  std::cerr << "SSLEXPIRYREMINDER IS INVALID!" << std::endl; }

	if (this->REPORTINGMETHOD != "NONE" and this->REPORTINGMETHOD != "RETCODE") { VALID = false; std::cerr << "REPORTINGMETHOD IS INVALID!" << std::endl; }

	if (not VALID) {
		return 1;
	}
	else {
		return 0;
	}
}

//Return variable data.
std::string configuration::getHOST() { return this->HOST; }
int configuration::getRETURNCODE() { return this->RETURNCODE; }
int configuration::getSSLVALID() { return this->SSLVALID; }
int configuration::getSSLEXPIRYREMINDER() { return this->SSLEXPIRYREMINDER; }
std::string configuration::getREPORTINGMETHOD() { returrn this->REPORTING_METHOD; }

configuration::~configuration() {}
