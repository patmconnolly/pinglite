// Object to store configuration pulled from file.

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

class configuration {
public:
	//Constructor
	configuration();

	//Add more config files
	int update();

	//Ensure final configuration is valid
	int validate();

	//Destructor
	~configuration();
};

#endif // CONFIGURATION_H