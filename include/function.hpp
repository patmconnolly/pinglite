// Library of functions to use as to not clutter up main.

#ifndef FUNCITON_H
#define FUNCTION_H

#include <string>
#include "configuration.hpp"

// Add function declarations here.
namespace function {
	extern bool DEBUG; // Global variable for debugging.
	extern bool SILENT; // Global variable for silence, supress all messages, log nothing.
	extern bool BUFFERLOGS; //Determines if buffer is to be used for logs.
	extern std::string LOGFILE; // Configured logfile.
	extern std::string LOGBUFFER; // Temp log storage until if silence is determined as well as when the logfile is defined.
	void flushbuffer(); //Triggers a flush of the log buffer.
	void log(std::string str); //Logs a string to the log, if debug prints as well.
	void errlog(std::string str); //Logs a string to the log, if debug prints to stderr as well.
	void help_message();
	int addConfig(configuration* conf, int argc, char* argv[], int* i);
	std::string stringifyBoolean(bool value); //Enter a boolean, returns a string (true/false).
}

#endif // FUNCTION_H