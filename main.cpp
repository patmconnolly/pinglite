// Main class for PingLite

#include <iostream>
#include <string>

#include "include/function.hpp"
#include "include/payload.hpp"
#include "include/configuration.hpp"

int main(int argc, char* argv[]) {
	//Collect and parse input.
	if (argc == 1) {
		//Checks if no arguments were passed, other than the program name.
		//Fails the program if so.
		std::cout << "Invalid flags passed! You need to pass at least one argument." << std::endl;
		function::help_message();
		return 1;
	}

	bool test = false;
	bool config = false;
	configuration conf = configuration::configuration();
	int result = 0;

	bool record = false;
	std::string recordfile = "";
	
	bool manual = false;
	std::string manualURL = "";

	int i = 1;
	while (i < argc) {
		i++;
		std::string arg = argv[i];
		if (arg == "-h" || arg == "--help") {
			//Display help message from functions.
			function::help_message();
			
			return 0;
		}
		else if (arg == "-t" || arg == "--test") {
			//Test the config file(s) to ensure they will work. Exit after test with pass/fail.
			//Stop checking for flags and just assume everything is a file.
			test = true;
			do {
				i++;
				result = conf.update(); //Add the new data to the config object.
			} while (i < argc and result);
			std::cout << "You passed the test flag." << std::endl;
			if (not result) {
				std::cout << "Your config is broken! See output above!" << std::endl;
				return 1;
			}
			break;
		}
		else if (arg == "-c" || arg == "--configuration") {
			//Everything after this is configuration from global priority to specific priority with later files taking precidence.
			//This flag must be used last if used.
			//Stop checking for flags and just assume everything is a file.
			config = true;
			do {
				i++;
				result = conf.update(); //Add the new data to the config object.
			} while (i < argc and result);
			std::cout << "You passed the configuration flag." << std::endl;
			if (not result) {
				std::cout << "Your config is broken! See output above!" << std::endl;
				std::cout << "Use the test flag to test your config ahead of time." << std::endl;
				return 1;
			}
			break;
		}
		else if (arg == "-r" || arg == "--record") {
			//File for where to store the data for multiple runs.
			//If passed but file does not exist, this is the first run, create the file.
			//If flag unused, do not save results, just show on the screen.
			record = true;
			i++;
			recordfile = arg;
			std::cout << "You passed the record flag." << std::endl;
			continue;
		}
		else if (arg == "-m" || arg == "--manual") {
			//Indicates a manual run, no config file. Must have URL passed in with this flag.
			//Will not report other than stdout, will not save results.
			manual = true;
			i++;
			manualURL = arg;
			std::cout << "You passed the manual flag." << std::endl;
			break;
		}
		else {
			//Indicates invalid flags passed. Display help message from functions.
			std::cout << "Invalid flags passed! Please check your command and try again." << std::endl;
			function::help_message();
			return 1;
		}

	}

	//Collect configuration and store in configuration object.

	//Collect history, if it exists, and store in a historical object.

	//Send call, store response in payload object.

	//Compare payload to history, prepare alert if needed.

	//Send alert, if needed.


	return 0;
}