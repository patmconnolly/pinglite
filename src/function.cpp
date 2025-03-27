// Library of functions to use as to not clutter up main.

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
		function::BUFFERLOGS = false;
		if (function::HELP or function::CHECKVERSION) { std::cout << function::LOGBUFFER << std::endl; }
		if (not function::SILENT) { function::writeFile(function::LOGBUFFER, function::LOGFILE); }
		function::LOGBUFFER = "";
	}

	void writeFile(std::string text, std::string file)
	{
		std::ofstream outputFile;
		outputFile.open(file, std::ios::app);
		outputFile << text << std::endl;
		outputFile.close();
	}

	void version_message() {
		std::cout << "Compiled and packaged on " << COMPILE_DATE << " at " << COMPILE_TIME << " UTC from the " << COMPILE_BRANCH << " branch." << std::endl;
		std::cout << "Pinglite version: " << COMPILE_BRANCH << "-" << COMPILE_DATE << std::endl;
		return;
	}

	void help_message() {
		std::cout << "PingLite Usage" << std::endl;
		std::cout << "===============================================================================================================================" << std::endl;
		std::cout << "Flags" << std::endl;
		std::cout << "-------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << " -h, --help             Displays this help screen and exits." << std::endl;
		std::cout << " -v, --version          Displays the version number and exits." << std::endl;
		std::cout << " -d, --debug            Displays logs as they occur to stdout, still logs to log file." << std::endl;
		std::cout << " -s, --silent           Supress all messages, log nothing. Output only what is needed at an absoloute minimum." << std::endl;
		std::cout << " -l, --logfile          Manually specify the log file, defaults to pinglite.log in current directory." << std::endl;
		std::cout << " -m, --manual           Indicates a manual run with a URL. No results will be recorded, no alerts to be sent." << std::endl;
		std::cout << " -t, --test             Tests the configuration files and exits." << std::endl;
		std::cout << " -r, --results          Specifies the file to record the results, if the file does not exist it will be created." << std::endl;
		std::cout << " -c, --config           Indicates all subsequent arguments are the configuration files ordered from lowest priority to highest." << std::endl;
		std::cout << "" << std::endl;
		std::cout << "Example Usage" << std::endl;
		std::cout << "-------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "pinglite --help" << std::endl;
		std::cout << "pinglite --version" << std::endl;
		std::cout << "pinglite --manual https://download.pinglite.xyz" << std::endl;
		std::cout << "pinglite --test globalconfig.ini localconfig.ini siteconfig.ini" << std::endl;
		std::cout << "pinglite --debug --logfile output.txt --results results.ini --config configuration.ini" << std::endl;
		std::cout << "pinglite --results results.txt --config globalconfig.ini localconfig.ini siteconfig.ini" << std::endl;
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
		if (function::SILENT and function::LOG_FILE) {
			function::error("SILENT and LOGFILE cannot be used together!");
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
		if (function::MANUAL and function::RESULTS) {
			function::error("MANUAL and RESULTS cannot be used together!");
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
		if (function::RESULTS and not function::CONFIG) {
			function::error("RESULTS and CONFIG MUST be used together!");
			function::HELP = true;
			function::KILL = true;
			function::EXITCODE = 1;
		}
	}

	void parseOptions(int argc, char* argv[], int* i)
	{
		std::string arg = "";

		while (*i < argc - 1 and not function::KILL) {
			(*i)++;
			arg = argv[*i];
			if (arg == "-h" || arg == "--help") {
				function::HELP = true;
				function::KILL = true;
			}
			else if (arg == "-v" || arg == "--version") {
				function::CHECKVERSION = true;
				function::KILL = true;
			}
			else if (arg == "-d" || arg == "--debug") {
				function::DEBUG = true;
				function::info("DEBUG FLAG SET, VERBOSE OUTPUT SENT TO STDOUT.");
			}
			else if (arg == "-s" || arg == "--silent") {
				function::SILENT = true;
				function::info("SILENT FLAG SET, NO MORE OUTPUT WILL OCCUR.");

			}
			else if (arg == "-r" || arg == "--results") {
				function::RESULTS = true;
				std::string resultslog = "";
				if (*i < argc - 1) {
					(*i)++;
					function::RESULTS_FILE = argv[*i];
					resultslog += "Recordfile stored as: " + function::RESULTS_FILE + ".";
					function::info(resultslog);
				}
				else {
					resultslog += "File must be passed in with record flag.";
					function::error(resultslog);
					function::HELP = true;
					function::KILL = true;
					function::EXITCODE = 1;
				}
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
			else if (arg == "-l" || arg == "--logfile") {
				function::LOG_FILE = true;
				std::string logfilelog = "";
				if (*i < argc - 1) {
					(*i)++;
					function::LOGFILE = argv[*i];
					logfilelog += "Logfile: " + function::LOGFILE + ".";
					function::info(logfilelog);
				}
				else {
					logfilelog += "Filename must be passed with logfile flag.";
					function::error(logfilelog);
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

	// Global Variables for Determining Execution
	bool HELP = false;                    // If helpmessage is going to be displayed.
	bool CHECKVERSION = false;            // If version information is going to be displayed.

	bool DEBUG = false;                   // Global variable for debugging.
	bool SILENT = false;                  // Global variable for silence, supress all messages, log nothing.

	bool LOG_FILE = false;                // If a manual logfile is configured.

	bool MANUAL = false;                  // If manual URL is to be checked.
	std::string MAN_URL = "";             // --The manual URL string.

	bool TEST = false;                    // If testing of config files is to be done and that is it.
	bool CONFIG = false;                  //If config files are passed in to be used. Similar to TEST.

	bool RESULTS = false;                 // If results are to be stored.
	std::string RESULTS_FILE = "";        // --The results file string.

	bool BUFFERLOGS = true;               // Determines if buffer is to be used for logs.
	                                      // --Initially buffer until flags are parsed and determine what to do with logs.
	std::string LOGFILE = "pinglite.txt"; // --Configured logfile string.
	std::string LOGBUFFER = "";           // Temp log storage until if silence is determined as well as when the logfile is defined.

	bool KILL = false;                    // False by default, True if program needs to end as immidietly as possible.
	int EXITCODE = 0;                     // 0 by default, 1 if needed program to fail execution.
}