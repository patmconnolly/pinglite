// Library of functions to use as to not clutter up main.

#ifndef FUNCITON_H
#define FUNCTION_H

// Add function declarations here.
namespace function {
	void help_message();
	int addConfig(configuration* conf, const int argc, const char* argv[], int* i);
}

#endif // FUNCTION_H