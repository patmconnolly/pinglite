// Library of functions to use as to not clutter up main.

#ifndef FUNCITON_H
#define FUNCTION_H

#include "configuration.hpp"

// Add function declarations here.
namespace function {
	void help_message();
	int addConfig(configuration* conf, int argc, char* argv[], int* i);
}

#endif // FUNCTION_H