// Library of functions to use as to not clutter up main.
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

#include <iostream>
#include <string>
#include <fstream>

#include "function.hpp"
#include "configuration.hpp"
#include "version.hpp"

// Add function defenitions here.
namespace function {
	void info(std::string str, std::string str2, std::string str3)
	{
		std::string output = function::HEADER_INFO + str + str2 + str3;
		if (function::BUFFERLOGS) {
			function::LOGBUFFER += output + "\n";
		}
		else {
			if (not function::SILENT) {
				std::cout << output << std::endl;
				function::writeFile(output, function::LOGFILE);
			}
		}
	}

	void debug(std::string str, std::string str2, std::string str3)
	{
		std::string output = function::HEADER_DEBU + str + str2 + str3;
		if (function::BUFFERLOGS) {
			function::LOGBUFFER += output + "\n";
		}
		else {
			if (not function::SILENT) {
				if (function::DEBUG) { std::cerr << output << std::endl; }
				function::writeFile(output, function::LOGFILE);
			}
		}
	}

	void error(std::string str, std::string str2, std::string str3)
	{
		std::string output = function::HEADER_ERRR + str + str2 + str3;
		if (function::BUFFERLOGS) {
			function::LOGBUFFER += output + "\n";
		}
		else {
			if (not function::SILENT) {
				std::cerr << output << std::endl;
				function::writeFile(output, function::LOGFILE);
			}
		}
	}

	void warning(std::string str, std::string str2, std::string str3)
	{
		std::string output = function::HEADER_WARN + str + str2 + str3;
		if (function::BUFFERLOGS) {
			function::LOGBUFFER += output + "\n";
		}
		else {
			if (not function::SILENT) {
				if (function::DEBUG) { std::cerr << output << std::endl; }
				function::writeFile(output, function::LOGFILE);
			}
		}
	}

	void flushbuffer()
	{
		function::debug("Flushing buffer to log file.");
		function::BUFFERLOGS = false;
		if (not function::SILENT) { function::writeFile(function::LOGBUFFER, function::LOGFILE); }
		if (function::NOLOGFILE) { std::cout << function::LOGBUFFER << std::endl; }
		function::LOGBUFFER = "";
	}

	void writeFile(std::string text, std::string file)
	{
		if (not function::ERRORLOGGING and not function::NOLOGFILE) {
			std::ofstream outputFile;
			outputFile.open(file, std::ios::app);
			if (not outputFile.is_open()) {
				function::ERRORLOGGING = true;
				function::error("LOG FILE CANNOT BE OPENED FOR WRITING!");
			}
			else {
				outputFile << text << std::endl;
			}
			outputFile.close();
		}
	}

	void version_message() {
		function::KILL = true;
		function::debug("Displaying Version Information");
		std::cout << "Compiled and packaged on " << COMPILE_DATE << " at " << COMPILE_TIME << " UTC from the " << COMPILE_BRANCH << " branch." << std::endl;
		std::cout << "Pinglite version: " << COMPILE_BRANCH << "-" << COMPILE_DATE << std::endl;
		return;
	}

	void help_message() {
		function::KILL = true;
		function::debug("Displaying Help Message");
		std::cout << "PingLite Copyright (C) 2025 Patrick Connolly" << std::endl;
		std::cout << "This program comes with ABSOLUTELY NO WARRANTY." << std::endl;
		std::cout << "This is free software, and you are welcome to redistribute it under certain conditions." << std::endl;
		std::cout << "You should have received a copy of the GNU General Public License v3 along with this program." << std::endl;
		std::cout << "If not, see <https://www.gnu.org/licenses/>." << std::endl;
		std::cout << "" << std::endl;
		std::cout << "PingLite Usage" << std::endl;
		std::cout << "===============================================================================================================================" << std::endl;
		std::cout << "Flags" << std::endl;
		std::cout << "-------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << " -h, --help             Displays this help screen and exits." << std::endl;
		std::cout << " -v, --version          Displays the version number and exits." << std::endl;
		std::cout << " -d, --debug            Displays logs as they occur to stdout, still logs to log file." << std::endl;
		std::cout << " -s, --silent           Supress all messages, log nothing. Output only what is needed at an absoloute minimum." << std::endl;
		std::cout << " -m, --manual           Indicates a manual run with a URL. No results will be recorded, no alerts to be sent." << std::endl;
		std::cout << " -t, --test             Tests the configuration files and exits." << std::endl;
		std::cout << " -c, --config           Indicates all subsequent arguments are the configuration files ordered from lowest priority to highest." << std::endl;
		std::cout << "" << std::endl;
		std::cout << "Example Usage" << std::endl;
		std::cout << "-------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "pinglite --help" << std::endl;
		std::cout << "pinglite --version" << std::endl;
		std::cout << "pinglite --manual https://download.pinglite.xyz" << std::endl;
		std::cout << "pinglite --test globalconfig.ini localconfig.ini siteconfig.ini" << std::endl;
		std::cout << "pinglite --debug --config configuration.ini" << std::endl;
		std::cout << "pinglite --config globalconfig.ini localconfig.ini siteconfig.ini" << std::endl;
		std::cout << "" << std::endl;
		std::cout << "Notes" << std::endl;
		std::cout << "-------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "Help, Manual, and Test must be used with no other flags." << std::endl;
		std::cout << "" << std::endl;
		return;
	}

	int addConfig(configuration* conf, int argc, char* argv[], int* i) {
		int result = 0;
		if (*i < argc - 1) {
			do {
				(*i)++;
				function::info("Beginning parse of configuration file: ", argv[*i], ".");
				result = conf->update(argv[*i]);
			} while (*i < argc - 1 and result == 0);
		}
		else {
			function::error("At least 1 config file must be passed in!");
			return 1;
		}
		if (result == 1) {
			function::error("Your config is broken in file: ", argv[*i], ". See output above!");
			return 1;
		}
		function::info("Parsing of configuration files complete, validating.");
		return conf->validate();
	}

	std::string stringifyBoolean(bool value) {
		if (value) { return "true"; }
		else { return "false"; }
	}

	void validateOptions() {
		//These options are not going to happen here.
		// - HELP
		// - VERSION
		
		if (function::SILENT and function::DEBUG) {
			function::error("SILENT and DEBUG cannot be used together!");
			function::HELP = true;
			function::KILL = true;
			function::EXITCODE = 1;
		}
		if (function::MANUAL and function::CONFIG) {
			function::error("MANUAL and CONFIG cannot be used together!");
			function::HELP = true;
			function::KILL = true;
			function::EXITCODE = 1;
		}
		if (function::MANUAL and function::TEST) {
			function::error("MANUAL and TEST cannot be used together!");
			function::HELP = true;
			function::KILL = true;
			function::EXITCODE = 1;
		}
		if (function::TEST and function::CONFIG) {
			function::error("TEST and CONFIG cannot be used together!");
			function::HELP = true;
			function::KILL = true;
			function::EXITCODE = 1;
		}
	}

	std::string stripQuotesIfExist(const std::string& str)
	{
		if (str.empty()) { return str; }
		std::string result = str; //Create duplicate of string.

		//Check for matching quotes if string is greater than 0.
		if (result.length() >= 2 and result.front() == '"' and result.back() == '"') {
			result.erase(0, 1); //Remove leading quote.
			result.pop_back();  //Remove trailing quote.
		}
		return result;
	}

	void parseOptions(int argc, char* argv[], int* i)
	{
		std::string arg = "";

		while (*i < argc - 1 and not function::KILL) {
			(*i)++;
			arg = argv[*i];
			if (arg == "-h" || arg == "--help") {
				function::HELP = true;
			}
			else if (arg == "-v" || arg == "--version") {
				function::CHECKVERSION = true;
			}
			else if (arg == "-d" || arg == "--debug") {
				function::DEBUG = true;
				function::info("DEBUG FLAG SET, VERBOSE OUTPUT SENT TO STDOUT.");
			}
			else if (arg == "-s" || arg == "--silent") {
				function::SILENT = true;
				function::info("SILENT FLAG SET, NO MORE OUTPUT WILL OCCUR.");

			}
			else if (arg == "-m" || arg == "--manual") {
				function::MANUAL = true;
				std::string manuallog = "";
				if (*i < argc - 1) {
					(*i)++;
					function::MAN_URL = argv[*i];
					manuallog += "Target URL: " + function::MAN_URL + ".";
					function::info(manuallog);
				}
				else {
					manuallog += "URL must be passed in with manual flag.";
					function::error(manuallog);
					function::HELP = true;
					function::KILL = true;
					function::EXITCODE = 1;
				}
			}
			else if (arg == "-t" || arg == "--test") {
				function::TEST = true;
				break; // Exiting the loop as all subsequent args are assumed to be filenames.
			}
			else if (arg == "-c" || arg == "--config") {
				function::CONFIG = true;
				break; // Exiting the loop as all subsequent args are assumed to be filenames.
			}
			else {
				function::error("Invalid flags passed! Please check your command and try again.");
				function::error("+============================================================+");
				function::HELP = true;
				function::KILL = true;
				function::EXITCODE = 1;
			}
		}
	}

	//Discard HTML data as that is not needed.
	size_t discard_data(void* buffer, size_t size, size_t nmemb, void* userp) {
		return size * nmemb;
	}

	// Global Variables for Determining Execution
	bool HELP = false;                    // If helpmessage is going to be displayed.
	bool CHECKVERSION = false;            // If version information is going to be displayed.

	bool DEBUG = false;                   // Global variable for debugging.
	bool SILENT = false;                  // Global variable for silence, supress all messages, log nothing.

	bool MANUAL = false;                  // If manual URL is to be checked.
	std::string MAN_URL = "";             // --The manual URL string.

	bool TEST = false;                    // If testing of config files is to be done and that is it.
	bool CONFIG = false;                  //If config files are passed in to be used. Similar to TEST.

	bool RESULTS = false;                 // If results are to be stored.
	std::string RESULTS_FILE = "";        // --The results file string.

	bool BUFFERLOGS = true;               // Determines if buffer is to be used for logs.
	                                      // --Initially buffer until flags are parsed and determine what to do with logs.
	std::string LOGFILE = "pinglite.log"; // --Configured logfile string.
	std::string LOGBUFFER = "";           // Temp log storage until if silence is determined as well as when the logfile is defined.
	bool NOLOGFILE = false;               // False by default, true when no logfile will be defined.

	bool KILL = false;                    // False by default, True if program needs to end as immidietly as possible.
	int EXITCODE = 0;                     // 0 by default, 1 if needed program to fail execution.

	bool ERRORLOGGING;                    // False by default, True if log file cannot be opened.
}