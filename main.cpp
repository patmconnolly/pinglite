// Main class for PingLite

#include <iostream>
#include <string>

#include "include/version.hpp"
#include "include/function.hpp"
#include "include/payload.hpp"
#include "include/configuration.hpp"

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

	bool HARDSTOP = false; //If a hard stop is triggered, stop doing everything and go straight to end of program.
	int EXITCODE = 0;      //The exit code to be returned. Allows for nonzero to be assigned.
	
	bool config = false;
	configuration* conf = new configuration();

	bool record = false;
	std::string recordfile = "";
	
	bool manual = false;
	std::string manualURL = "";

	int* i = new int(0);

	std::string arg = "";

	while (*i < argc - 1 and not HARDSTOP) {
		(*i)++;
		arg = argv[*i];
		if (arg == "-h" || arg == "--help") {
			//Display help message from functions.
			function::help_message();
			HARDSTOP = true;
			EXITCODE = 0;
		}
		else if (arg == "-v" || arg == "--version") {
			//Display versioning information.
			std::cout << "Compiled and packaged on " << COMPILE_DATE << " at " << COMPILE_TIME << " UTC from the " << COMPILE_BRANCH << " branch." << std::endl;
			std::cout << "Pinglite version: " << COMPILE_BRANCH << "-" << COMPILE_DATE << std::endl;
			HARDSTOP = true;
			EXITCODE = 0;
		}
		else if (arg == "-t" || arg == "--test") {
			//Test the config file(s) to ensure they will work. Exit after test with pass/fail.
			//Stop checking for flags and just assume everything is a file.
			std::cout << "Testing configuration files." << std::endl;
			if (function::addConfig(conf, argc, argv, i) == 0) {
				std::cout << "Validation succeeded." << std::endl;
				HARDSTOP = true;
				EXITCODE = 0;
			}
			else {
				std::cerr << "VALIDATION FAILED! SEE OUTPUT ABOVE." << std::endl;
				HARDSTOP = true;
				EXITCODE = 1;
			}
		}
		else if (arg == "-c" || arg == "--configuration") {
			//Everything after this is configuration from global priority to specific priority with later files taking precidence.
			//This flag must be used last if used.
			//Stop checking for flags and just assume everything is a file.
			config = true;
			if (function::addConfig(conf, argc, argv, i) == 0) {
				std::cout << "Configuration imported successfully." << std::endl;
			}
			else {
				HARDSTOP = true;
				EXITCODE = 1;
			}
		}
		else if (arg == "-r" || arg == "--record") {
			//File for where to store the data for multiple runs.
			//If passed but file does not exist, this is the first run, create the file.
			//If flag unused, do not save results, just show on the screen.
			record = true;
			if (*i < argc - 1) {
				(*i)++;
				recordfile = argv[*i];
				std::cout << "Recordfile stored as: " << recordfile << "." << std::endl;
			}
			else {
				std::cerr << "File must be passed in with record flag." << std::endl;
				HARDSTOP = true;
				EXITCODE = 1;
			}
		}
		else if (arg == "-m" || arg == "--manual") {
			//Indicates a manual run, no config file. Must have URL passed in with this flag.
			//Will not report other than stdout, will not save results.
			manual = true;
			if (*i < argc - 1) {
				(*i)++;
				manualURL = argv[*i];
				std::cout << "Target URL: " << manualURL << "." << std::endl;
			}
			else {
				std::cerr << "URL must be passed in with manual flag." << std::endl;
				HARDSTOP = true;
				EXITCODE = 1;
			}
			break;
		}
		else {
			//Indicates invalid flags passed. Display help message from functions.
			std::cerr << "Invalid flags passed! Please check your command and try again." << std::endl;
			std::cerr << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl << std::endl;
			function::help_message();
			HARDSTOP = true;
			EXITCODE = 1;
		}

	}
	delete i;

	if (record and not config) {
		std::cerr << "Record flag requires Config flag used as well!" << std::endl;
		std::cerr << "++++++++++++++++++++++++++++++++++++++++++++++" << std::endl << std::endl;
		function::help_message();
		HARDSTOP = true;
		EXITCODE = 1;
	}

	if (not HARDSTOP) {
		payload* targetPayload = nullptr;

		//Executes the manual test.
		if (manual) {
			targetPayload = new payload(manualURL);
			if (not targetPayload->validWebcall()) {
				HARDSTOP = true;
				EXITCODE = 1;
			}
		}

		if (config) {
			std::cout << "Executing Webcall..." << std::endl;
			targetPayload = new payload(conf->getHOST());
			//Create alert handler
			//Assign alert functions as needed.



		}

		//Collect history, if it exists, and store in a historical object.

		//Send call, store response in payload object.

		//Compare payload to history, prepare alert if needed.

		//Send alert, if needed.

		delete targetPayload;
	}
	delete conf;
	return EXITCODE;
}