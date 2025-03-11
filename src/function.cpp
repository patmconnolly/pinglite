// Library of functions to use as to not clutter up main.

#include <iostream>

#include "function.hpp"
#include "configuration.hpp"

// Add function defenitions here.
namespace function {
	void help_message() {
		std::cout << "PingLite Usage" << std::endl;
		std::cout << "===============================================================================================================================" << std::endl;
		std::cout << "Flags" << std::endl;
		std::cout << "-------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << " -h, --help             Displays this help screen and exits." << std::endl;
		std::cout << " -v, --version          Displays the version number and exits." << std::endl;
		std::cout << " -m, --manual           Indicates a manual run with a URL. No results will be recorded, no alerts to be sent." << std::endl;
		std::cout << " -t, --test             Tests the configuration files and exits." << std::endl;
		std::cout << " -r, --results          Specifies the file to record the results, if the file does not exist it will be created." << std::endl;
		std::cout << " -c, --configuration    Indicates all subsequent arguments are the configuration files ordered from lowest priority to highest." << std::endl;
		std::cout << "" << std::endl;
		std::cout << "Example Usage" << std::endl;
		std::cout << "-------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "pinglite --help" << std::endl;
		std::cout << "pinglite --version" << std::endl;
		std::cout << "pinglite --manual https://download.pinglite.xyz" << std::endl;
		std::cout << "pinglite --test globalconfig.conf localconfig.conf siteconfig.conf" << std::endl;
		std::cout << "pinglite --record results.txt --configuration globalconfig.conf localconfig.conf siteconfig.conf" << std::endl;
		std::cout << "" << std::endl;
		std::cout << "Notes" << std::endl;
		std::cout << "-------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "The results and configuration flags can be used together. The results flag is optional." << std::endl;
		std::cout << "Help, Manual, and Test must be used with no other flags." << std::endl;
		std::cout << "" << std::endl;
		return;
	}

	int addConfig(configuration* conf, int argc, char* argv[], int* i) {
		int result = 0;
		if (*i < argc - 1) {
			do {
				(*i)++;
				std::cout << "Beginning parse of configuration file: " << argv[*i] << "." << std::endl;
				result = conf->update();
			} while (*i < argc - 1 and result == 0);
		}
		else {
			std::cerr << "At least 1 config file must be passed in!" << std::endl;
			return 1;
		}
		if (result == 1) {
			std::cerr << "Your config is broken in file: " << argv[*i] << ". See output above!" << std::endl;
			return 1;
		}
		std::cout << "Parsing of configuration files complete. Beginning configuration validation." << std::endl;
		return conf->validate();
	}
}