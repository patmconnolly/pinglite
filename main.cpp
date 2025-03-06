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
	configuration* conf = new configuration();

	bool record = false;
	std::string recordfile = "";
	
	bool manual = false;
	std::string manualURL = "";

	int* i = new int(0);

	std::string arg = "";

	std::cout << "i: " << i << std::endl; //tracer
	std::cout << "*i: " << *i << std::endl; //tracer
	std::cout << "argc: " << argc << std::endl; //tracer

	while (*i < argc) {
		(*i)++;
		std::cout << "i: " << i << std::endl; //tracer
		std::cout << "*i: " << *i << std::endl; //tracer
		arg = argv[*i];
		std::cout << "arg: " << arg << std::endl; //tracer
		if (arg == "-h" || arg == "--help") {
			//Display help message from functions.
			function::help_message();
			delete conf;
			delete i;
			return 0;
		}
		else if (arg == "-t" || arg == "--test") {
			//Test the config file(s) to ensure they will work. Exit after test with pass/fail.
			//Stop checking for flags and just assume everything is a file.
			test = true;
			std::cout << "Testing configuration files." << std::endl;
			if (function::addConfig(conf, argc, argv, i) == 0) {
				delete conf;
				delete i;
				return 0;
			}
			else {
				delete conf;
				delete i;
				return 1;
			}
		}
		else if (arg == "-c" || arg == "--configuration") {
			//Everything after this is configuration from global priority to specific priority with later files taking precidence.
			//This flag must be used last if used.
			//Stop checking for flags and just assume everything is a file.
			config = true;
			function::addConfig(conf, argc, argv, i);
			break;
		}
		else if (arg == "-r" || arg == "--record") {
			//File for where to store the data for multiple runs.
			//If passed but file does not exist, this is the first run, create the file.
			//If flag unused, do not save results, just show on the screen.
			record = true;
			if (*i < argc) {
				(*i)++;
				recordfile = argv[*i];
				std::cout << "Recordfile stored as: " << recordfile << "." << std::endl;
			}
			else {
				std::cout << "File must be passed in with record flag." << std::endl;
				delete conf;
				delete i;
				return 1;
			}
			continue;
		}
		else if (arg == "-m" || arg == "--manual") {
			//Indicates a manual run, no config file. Must have URL passed in with this flag.
			//Will not report other than stdout, will not save results.
			manual = true;
			if (*i < argc) {
				(*i)++;
				manualURL = argv[*i];
				std::cout << "Target URL: " << recordfile << "." << std::endl;
			}
			else {
				std::cout << "URL must be passed in with manual flag." << std::endl;
				delete conf;
				delete i;
				return 1;
			}
			break;
		}
		else {
			//Indicates invalid flags passed. Display help message from functions.
			std::cout << "Invalid flags passed! Please check your command and try again." << std::endl;
			function::help_message();
			delete conf;
			delete i;
			return 1;
		}

	}
	delete i;



	//Collect configuration and store in configuration object.

	//Collect history, if it exists, and store in a historical object.

	//Send call, store response in payload object.

	//Compare payload to history, prepare alert if needed.

	//Send alert, if needed.

	delete conf;
	return 0;
}