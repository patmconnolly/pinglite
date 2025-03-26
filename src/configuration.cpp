// Object to store configuration pulled from file.
#include <string>
#include "../third-party/inih/cpp/INIReader.h"
#include "configuration.hpp"
#include "function.hpp"

configuration::configuration() {
	this->HOST = "httpx://EMPTY";
	this->RETURNCODE = -1;
	this->SSLVALID = -1;
	this->SSLEXPIRYREMINDER = -1;
	this->SSLEXPIRYSNOOZE = -1;
	this->ALERTSNOOZE = -1;
}

int configuration::update(std::string confFile) {
	INIReader reader(confFile);

	if (reader.ParseError() < 0) {
		function::error("Cannot load config file: ", confFile, ".");
		return 1;
	}

	std::string tempHOST;
	int tempRETCODE;
	int tempSSLVALID;
	int tempSSLEXPIRYREMINDER;
	std::string tempREPORTINGMETHOD;
	int tempSSLEXPIRYSNOOZE;
	int tempALERTSNOOZE;

	//Attempt to grab known variables, continue if cannot collect

	//---HOST
	tempHOST = reader.Get("CHECK", "HOST", "");
	if (tempHOST != "") {
		this->HOST = tempHOST;
		function::info("Collected HOST Variable.");
	}
	else {
		function::warning("No HOST Variable Defined.");
	}

	//---RETURNCODE
	tempRETCODE = reader.GetInteger("VALIDATION", "RETURNCODE", -1);
	if (tempRETCODE != -1) {
		this->RETURNCODE = tempRETCODE;
		function::info("Collected RETURNCODE Variable.");
	}
	else {
		function::warning("No RETURNCODE Variable Defined.");
	}

	//---SSLVALID
	tempSSLVALID = reader.GetInteger("VALIDATION", "SSLVALID", -1);
	if (tempSSLVALID != -1) {
		this->SSLVALID = tempSSLVALID;
		function::info("Collected SSLVALID Variable.");
	}
	else {
		function::warning("No SSLVALID Variable Defined.");
	}

	//---SSLEXPIRYREMINDER
	tempSSLEXPIRYREMINDER = reader.GetInteger("VALIDATION", "SSLEXPIRYREMINDER", -1);
	if (tempSSLEXPIRYREMINDER != -1) {
		this->SSLEXPIRYREMINDER = tempSSLEXPIRYREMINDER;
		function::info("Collected SSLEXPIRYREMINDER Variable.");
	}
	else {
		function::warning("No SSLEXPIRYREMINDER Variable Defined.");
	}

	//---REPORTING METHOD
	tempREPORTINGMETHOD = reader.Get("REPORTING", "METHOD", "");
	if (tempREPORTINGMETHOD != "") {
		this->REPORTINGMETHOD = tempREPORTINGMETHOD;
		function::info("Collected REPORTINGMETHOD Variable.");
	}
	else {
		function::warning("No REPORTINGMETHOD Variable Defined.");
	}

	//---SSL Expiry Snooze
	tempSSLEXPIRYSNOOZE = reader.GetInteger("REPORTING", "SSLEXPIRYSNOOZE", -1);
	if (tempSSLEXPIRYSNOOZE != -1) {
		this->SSLEXPIRYSNOOZE = tempSSLEXPIRYSNOOZE;
		function::info("Collected SSLEXPIRYSNOOZE Variable.");
	}
	else {
		function::warning("No SSLEXPIRYSNOOZE Variable Defined.");
	}

	//---Alert Snooze
	tempALERTSNOOZE = reader.GetInteger("REPORTING", "ALERTSNOOZE", -1);
	if (tempALERTSNOOZE != -1) {
		this->ALERTSNOOZE = tempALERTSNOOZE;
		function::info("Collected ALERTSNOOZE Variable.");
	}
	else {
		function::warning("No ALERTSNOOZE Variable Defined.");
	}

	return 0;
}

int configuration::validate() {
	bool VALID = true;

	if (this->HOST == "httpx://EMPTY") { VALID = false; function::error("HOST IS INVALID!"); }
	if (this->RETURNCODE == -1) { VALID = false; function::error("RETURNCODE IS INVALID!"); }
	if (this->SSLVALID == -1) { VALID = false;  function::error("SSLVALID IS INVALID!"); }
	if (this->SSLEXPIRYREMINDER == -1) { VALID = false;  function::error("SSLEXPIRYREMINDER IS INVALID!"); }

	if (this->REPORTINGMETHOD != "NONE" and this->REPORTINGMETHOD != "RETCODE" and this->REPORTINGMETHOD != "TEST") { VALID = false; function::error("REPORTINGMETHOD IS INVALID!"); }

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
std::string configuration::getREPORTINGMETHOD() { return this->REPORTINGMETHOD; }
int configuration::getSSLEXPIRYSNOOZE() { return this->SSLEXPIRYSNOOZE; }
int configuration::getALERTSNOOZE() { return this->ALERTSNOOZE; }

configuration::~configuration() {}
