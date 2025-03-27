// Main class for PingLite

#include <iostream>
#include <string>
#include <ctime>

#include "include/function.hpp"
#include "include/payload.hpp"
#include "include/configuration.hpp"
#include "include/reporting.hpp"
#include "include/record.hpp"

int main(int argc, char* argv[]) {
	std::time_t startTime = std::time(0); // Get start time.
	char* dt = std::ctime(&startTime); // Convert to string format.
	function::debug("Run at: ", dt);
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
		if (function::CONFIG and not function::KILL) {
			function::info("Executing Webcall...");
			targetPayload = new payload(conf->getHOST());
			reporting* report = new reporting(conf, targetPayload);
			if (conf->getREPORTINGMETHOD() == "RETCODE") { function::EXITCODE = report->getRetcode(); }
			else if (conf->getREPORTINGMETHOD() != "NONE") {
				record* Data = nullptr;
				bool reportRequired;

				//Collect history, if it exists, and store in a historical object.
				if (function::RESULTS) {
					Data = new record(function::RESULTS_FILE);
					Data->update(report->RETCODE_Compare(), report->SSLVALID(), report->SSLEXPIRYWARNING());
					reportRequired = Data->alertRequired(report->getWarnSnooze(), report->getAlertSnooze());
					if (reportRequired) {
						report->trigger(Data->alertText());
					}
					Data->write();
					delete Data;
				}
			}
			delete report;
		}
		delete conf;
		delete targetPayload;
	}
	delete i;
	function::debug("======================================================================="); // Makes more readable in the output file.
	return function::EXITCODE;
}