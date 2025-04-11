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

#ifndef FUNCITON_H
#define FUNCTION_H

#include <string>
#include "configuration.hpp"

// Add function declarations here.
namespace function {
	// Global Variables for Determining Execution
	extern bool HELP;                // If helpmessage is going to be displayed.
	extern bool CHECKVERSION;        // If version information is going to be displayed.

	extern bool DEBUG;               // Global variable for debugging.
	extern bool SILENT;              // Global variable for silence, supress all messages, log nothing.

	extern std::string LOGFILE;      // --Configured logfile string.

	extern bool MANUAL;              // If manual URL is to be checked.
	extern std::string MAN_URL;      // --The manual URL string.

	extern bool TEST;                // If testing of config files is to be done and that is it.
	extern bool CONFIG;              //If config files are passed in to be used. Similar to TEST.

	extern bool RESULTS;             // If results are to be stored.
	extern std::string RESULTS_FILE; // --The results file string.

	extern bool BUFFERLOGS;          // Determines if buffer is to be used for logs.
	                                 // --Initially buffer until flags are parsed and determine what to do with logs.
	extern std::string LOGFILE;      // Configured logfile.
	extern std::string LOGBUFFER;    // Temp log storage until if silence is determined as well as when the logfile is defined.
	extern bool NOLOGFILE;           // False by default, true when no logfile will be defined.

	extern bool KILL;                // False by default, True if program needs to end as immidietly as possible.
	extern int EXITCODE;             // 0 by default, 1 if needed program to fail execution.

	extern bool ERRORLOGGING;        // False by default, True if log file cannot be opened.

	// String headers for LOG, WARN, and ERROR.
	const std::string HEADER_INFO = "   [INFO] - ";
	const std::string HEADER_DEBU = "  [DEBUG] - ";
	const std::string HEADER_WARN = "[WARNING] - ";
	const std::string HEADER_ERRR = "  [ERROR] - ";



	void flushbuffer(); //Triggers a flush of the log buffer.
	void writeFile(std::string text, std::string file); //Actual function that writes to a file.
	void info(std::string str, std::string str2 = "", std::string str3 = ""); //Logs a string to the log, if debug prints as well.
	void debug(std::string str, std::string str2 = "", std::string str3 = ""); //Logs a string to the log, if debug prints as well.
	void error(std::string str, std::string str2 = "", std::string str3 = ""); //Logs a string to the log, if debug prints to stderr as well.
	void warning(std::string str, std::string str2 = "", std::string str3 = ""); //Logs a string to the log, if debug prints to stderr as well.
	void help_message();
	void version_message();
	int addConfig(configuration* conf, int argc, char* argv[], int* i);
	std::string stringifyBoolean(bool value); //Enter a boolean, returns a string (true/false).
	void parseOptions(int argc, char* argv[], int* i);
	void validateOptions(); //Parse through selected options and verify the combination of options selected are good.
	std::string stripQuotesIfExist(const std::string& str); //Strip leading and tailing quotes if they exist.

	//Discard HTML data as that is not needed. For CURL Calls.
	size_t discard_data(void* buffer, size_t size, size_t nmemb, void* userp);
}

#endif // FUNCTION_H