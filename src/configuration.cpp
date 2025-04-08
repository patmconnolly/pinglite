// Object to store configuration pulled from file.
// Copyright(C) 2025 Patrick Connolly
//
// This program is free software : you can redistribute it and /or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation version 3 of the License.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.If not, see < https://www.gnu.org/licenses/>.

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
	std::string tempREPORTINGLOGFILE;
	std::string tempREPORTINGRESULTS;
	std::string tempREPORTINGMETHOD;
	int tempSSLEXPIRYSNOOZE;
	int tempALERTSNOOZE;
	std::string tempAPIURL;
	std::string tempAPIPAYLOAD;

	//Attempt to grab known variables, continue if cannot collect

	//---HOST
	tempHOST = reader.Get("CHECK", "HOST", "");
	if (tempHOST != "") {
		this->HOST = tempHOST;
		function::debug("Collected HOST Variable.");
	}
	else {
		function::warning("No HOST Variable Defined.");
	}

	//---RETURNCODE
	tempRETCODE = reader.GetInteger("VALIDATION", "RETURNCODE", -1);
	if (tempRETCODE != -1) {
		this->RETURNCODE = tempRETCODE;
		function::debug("Collected RETURNCODE Variable.");
	}
	else {
		function::warning("No RETURNCODE Variable Defined.");
	}

	//---SSLVALID
	tempSSLVALID = reader.GetInteger("VALIDATION", "SSLVALID", -1);
	if (tempSSLVALID != -1) {
		this->SSLVALID = tempSSLVALID;
		function::debug("Collected SSLVALID Variable.");
	}
	else {
		function::warning("No SSLVALID Variable Defined.");
	}

	//---SSLEXPIRYREMINDER
	tempSSLEXPIRYREMINDER = reader.GetInteger("VALIDATION", "SSLEXPIRYREMINDER", -1);
	if (tempSSLEXPIRYREMINDER != -1) {
		this->SSLEXPIRYREMINDER = tempSSLEXPIRYREMINDER;
		function::debug("Collected SSLEXPIRYREMINDER Variable.");
	}
	else {
		function::warning("No SSLEXPIRYREMINDER Variable Defined.");
	}

	//---REPORTING LOGFILE
	tempREPORTINGLOGFILE = reader.Get("REPORTING", "LOGFILE", "");
	if (tempREPORTINGLOGFILE != "") {
		function::LOGFILE = tempREPORTINGLOGFILE;
		function::debug("Collected REPORTINGLOGFILE Variable.");
	}
	else {
		function::warning("No REPORTINGLOGFILE Variable Defined.");
	}

	//---REPORTING RESULTS
	tempREPORTINGRESULTS = reader.Get("REPORTING", "RESULTS", "");
	if (tempREPORTINGRESULTS != "") {
		function::RESULTS_FILE = tempREPORTINGRESULTS;
		function::RESULTS = true;
		function::debug("Collected REPORTINGRESULTS Variable.");
	}
	else {
		function::warning("No REPORTINGRESULTS Variable Defined.");
	}

	//---REPORTING METHOD
	tempREPORTINGMETHOD = reader.Get("REPORTING", "METHOD", "");
	if (tempREPORTINGMETHOD != "") {
		this->REPORTINGMETHOD = tempREPORTINGMETHOD;
		function::debug("Collected REPORTINGMETHOD Variable.");
	}
	else {
		function::warning("No REPORTINGMETHOD Variable Defined.");
	}

	//---SSL Expiry Snooze
	tempSSLEXPIRYSNOOZE = reader.GetInteger("REPORTING", "SSLEXPIRYSNOOZE", -1);
	if (tempSSLEXPIRYSNOOZE != -1) {
		this->SSLEXPIRYSNOOZE = tempSSLEXPIRYSNOOZE;
		function::debug("Collected SSLEXPIRYSNOOZE Variable.");
	}
	else {
		function::warning("No SSLEXPIRYSNOOZE Variable Defined.");
	}

	//---Alert Snooze
	tempALERTSNOOZE = reader.GetInteger("REPORTING", "ALERTSNOOZE", -1);
	if (tempALERTSNOOZE != -1) {
		this->ALERTSNOOZE = tempALERTSNOOZE;
		function::debug("Collected ALERTSNOOZE Variable.");
	}
	else {
		function::warning("No ALERTSNOOZE Variable Defined.");
	}

	//---API URL
	tempAPIURL = reader.Get("API", "URL", "");
	if (tempAPIURL != "") {
		this->APIURL = tempAPIURL;
		function::debug("Collected API URL Variable.");
	}
	else {
		function::warning("No API URL Variable Defined.");
	}

	//---API Payload
	tempAPIPAYLOAD = reader.Get("API", "PAYLOAD", "");
	if (tempAPIPAYLOAD != "") {
		this->APIPAYLOAD = tempAPIPAYLOAD;
		function::debug("Collected API PAYLOAD Variable.");
	}
	else {
		function::warning("No API PAYLOAD Variable Defined.");
	}

	return 0;
}

int configuration::validate() {
	bool VALID = true;

	if (this->HOST == "httpx://EMPTY") { VALID = false; function::error("HOST IS INVALID!"); }
	if (this->RETURNCODE == -1) { VALID = false; function::error("RETURNCODE IS INVALID!"); }
	if (this->SSLVALID == -1) { VALID = false;  function::error("SSLVALID IS INVALID!"); }
	if (this->SSLEXPIRYREMINDER == -1) { VALID = false;  function::error("SSLEXPIRYREMINDER IS INVALID!"); }
	if (this->REPORTINGMETHOD != "NONE" and this->REPORTINGMETHOD != "RETCODE" and not function::RESULTS) { VALID = false; function::error("REPORTINGRESULTS IS INVALID!"); }

	if (this->REPORTINGMETHOD != "NONE" and this->REPORTINGMETHOD != "RETCODE" and this->REPORTINGMETHOD != "TEST" and this->REPORTINGMETHOD != "API") { VALID = false; function::error("REPORTINGMETHOD IS INVALID!"); }

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
std::string configuration::getAPIURL() { return this->APIURL; }
std::string configuration::getAPIPAYLOAD() { return this->APIPAYLOAD; }

configuration::~configuration() {}
