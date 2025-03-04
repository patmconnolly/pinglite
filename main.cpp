// Main class for PingLite

#include <iostream>
#include <string>

#include "function.hpp"
#include "payload.hpp"
#include "configuration.hpp"

int main(int argc, char* argv[]) {
	//Collect and parse input.
	if (argc == 1) {
		//Checks if no arguments were passed, other than the program name.
		//Fails the program if so.
		std::cout << "Invalid flags passed! You need to pass at least one argument." << std::endl;
	}

	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
		if (arg == "-h" || arg == "--help") {
			//Display help message from functions.
			std::cout << "You passed the help flag." << std::endl;
		}
		else if (arg == "-t" || arg == "--test") {
			//Test the config file(s) to ensure they will work. Exit after test with pass/fail.
			//Stop checking for flags and just assume everything is a file.
			std::cout << "You passed the test flag." << std::endl;
		}
		else if (arg == "-c" || arg == "--configuration") {
			//Everything after this is configuration from global priority to specific priority with later files taking precidence.
			//This flag must be used last if used.
			//Stop checking for flags and just assume everything is a file.
			std::cout << "You passed the configuration flag." << std::endl;
		}
		else if (arg == "-r" || arg == "--record") {
			//File for where to store the data for multiple runs.
			//If passed but file does not exist, this is the first run, create the file.
			//If flag unused, do not save results, just show on the screen.
			std::cout << "You passed the record flag." << std::endl;
		}
		else if (arg == "-m" || arg == "--manual") {
			//Indicates a manual run, no config file. Must have URL passed in with this flag.
			//Will not report other than stdout, will not save results.
			std::cout << "You passed the manual flag." << std::endl;
		}
		else {
			//Indicates invalid flags passed. Display help message from functions.
			std::cout << "Invalid flags passed! Please check your command and try again." << std::endl;
		}

	}

	//Collect configuration and store in configuration object.

	//Collect history, if it exists, and store in a historical object.

	//Send call, store response in payload object.

	//Compare payload to history, prepare alert if needed.

	//Send alert, if needed.


	return 0;
}