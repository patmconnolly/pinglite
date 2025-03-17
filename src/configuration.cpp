// Object to store configuration pulled from file.
#include <iostream>
#include <string>
#include <stdexcept>
#include "../third-party/inih/cpp/INIReader.h"
#include "configuration.hpp"

configuration::configuration() {
	this-> HOST = "httpx://EMPTY";
	int RETURNCODE = -1;
	int SSLVALID = -1;
	int SSLEXPIRYREMINDER = -1;
}

int configuration::update(std::string confFile) {
	INIReader reader(confFile);

	if (reader.ParseError() < 0) {
		std::cerr << "Cannot load config file: " << confFile << "." << std::endl;
		return 1;
	}

	//Attempt to grab known variables, continue if cannot collect

	//---HOST
	try {
		this->HOST = reader.Get("CHECK", "HOST");
		std::cout << "Collected HOST Variable." << std::endl;
	}
	catch (const std::runtime_error& e) {
		std::cerr << "No HOST Variable Defined." << std::endl;
	}

	//---RETURNCODE
	try {
		this->RETURNCODE = reader.Get("REPORTING", "RETURNCODE");
		std::cout << "Collected RETURNCODE Variable." << std::endl;
	}
	catch (const std::runtime_error& e) {
		std::cerr << "No RETURNCODE Variable Defined." << std::endl;
	}

	//---SSLVALID
	try {
		this->SSLVALID = reader.Get("REPORTING", "SSLVALID");
		std::cout << "Collected SSLVALID Variable." << std::endl;
	}
	catch (const std::runtime_error& e) {
		std::cerr << "No SSLVALID Variable Defined." << std::endl;
	}

	//---SSLEXPIRYREMINDER
	try {
		this->SSLEXPIRYREMINDER = reader.Get("REPORTING", "SSLEXPIRYREMINDER");
		std::cout << "Collected SSLEXPIRYREMINDER Variable." << std::endl;
	}
	catch (const std::runtime_error& e) {
		std::cerr << "No SSLEXPIRYREMINDER Variable Defined." << std::endl;
	}

	return 0;
}

int configuration::validate() {
	bool VALID = true;
	//this->HOST = "httpx://EMPTY";
	//int RETURNCODE = -1;
	//int SSLVALID = -1;
	//int SSLEXPIRYREMINDER = -1;

	if (this->HOST == "httpx://EMPTY") { VALID = false; std::cerr << "HOST IS INVALID!" << std::endl; }
	if (this->RETURNCODE == -1) { VALID = false; std::cerr << "RETURNCODE IS INVALID!" << std::endl; }
	if (this->SSLVALID == -1) { VALID = false;  std::cerr << "SSLVALID IS INVALID!" << std::endl; }
	if (this->SSLEXPIRYREMINDER == -1) { VALID = false;  std::cerr << "SSLEXPIRYREMINDER IS INVALID!" << std::endl; }

	if (not VALID) {
		return 1;
	}
	else {
		return 0;
	}
}

configuration::~configuration() {}
