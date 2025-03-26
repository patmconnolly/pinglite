// Main class for PingLite

#include <iostream>
#include <string>

#include "include/function.hpp"
#include "include/payload.hpp"
#include "include/configuration.hpp"
#include "include/reporting.hpp"
#include "include/record.hpp"

int main(int argc, char* argv[]) {
	//Collect and parse input.

	if (argc == 1) {
		//Checks if no arguments were passed, other than the program name.
		//Fails the program if so.
		std::cout << "Invalid flags passed! You need to pass at least one argument." << std::endl;
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl << std::endl;
		function::help_message();
		return 1;
	}
	
	int* i = new int(0);

	std::string arg = "";

	function::parseOptions(argc, argv, i); //Parse menu options.
	if (not function::KILL) { function::validateOptions(); } //Ensure combination of menu options is good.
	function::flushbuffer();
	if (function::CHECKVERSION) { function::version_message(); }
	if (function::HELP) { function::help_message(); }

	if (not function::KILL) {
		configuration* conf = new configuration();
		payload* targetPayload = nullptr;

		// Executes the manual test.
		if (function::MANUAL) {
			targetPayload = new payload(function::MAN_URL);
			if (not targetPayload->validWebcall()) {
				function::KILL = true;
				function::EXITCODE = 1;
			}
		} // Prepares config and tests.
		else if (function::CONFIG or function::TEST) {
			function::EXITCODE = function::addConfig(conf, argc, argv, i);
			if (function::EXITCODE == 0) {
				function::info("Configuration imported successfully.");
			}
			else {
				function::error("Error importing configuration!");
				function::KILL = true;
			}
		}

		// Executes configured test.
		if (function::CONFIG) {
			function::info("Executing Webcall...");
			targetPayload = new payload(conf->getHOST());
			reporting* report = new reporting(conf, targetPayload);
			if (conf->getREPORTINGMETHOD() == "RETCODE") { function::EXITCODE = report->getRetcode(); }
			else if (conf->getREPORTINGMETHOD() != "NONE") {
				record* Data = nullptr;
				bool reportRequired;
				std::string reportText = "";

				//Collect history, if it exists, and store in a historical object.
				if (function::RESULTS) {
					Data = new record(function::RESULTS_FILE);
					Data->update(report->RETCODE_Compare(), report->SSLVALID(), report->SSLEXPIRYWARNING());
					reportRequired = Data->alertRequired(report->getWarnSnooze(), report->getAlertSnooze());
					if (reportRequired) {
						reportText += "Host ----------------: " + conf->getHOST() + "\n";
						reportText += Data->alertText();
						reportText += "Return Code ---------: " + std::to_string(report->getHTTPCODE()) + "\n";
						reportText += "Certificate Valid ---: " + function::stringifyBoolean(report->SSLVALID()) + "\n";
						reportText += "Certificate Expires in " + std::to_string(report->getEXPIRY()) + " days.\n";
					}
					Data->write();
					delete Data;
					if (reportRequired) {
						report->trigger(reportText);
					}
				}
			}
			delete report;
		}
		delete conf;
		delete targetPayload;
	}
	delete i;
	
	return function::EXITCODE;
}