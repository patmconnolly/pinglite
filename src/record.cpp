// Object to handle recordkeeping.

#include <iostream>
#include <string>
#include "record.hpp"
#include "../third-party/inih/cpp/INIReader.h"

//Constructor
//Takes in a filename, parses the file, and saves data to the object.
record::record(std::string filename) {
	this->FILENAME = filename;
	
	//Read file, if it exists. If not exist, place default data.

}

// Takes in the new data in the form of bool.
// Returns true if data is the same as previous.
// Returns false if any information is changed from previous.
void record::update(bool codeexpected, bool sslvalid, bool sslwarning) {
	this->NEWCODEEXPECTED = codeexpected;
	this->NEWSSLVALID = sslvalid;
	this->NEWSSLWARNING = sslwarning;

	if (this->NEWCODEEXPECTED == this->CODEEXPECTED) { this->CODECHANGE = false; }
	else { this->CODECHANGE = true; }

	if (this->NEWSSLVALID == this->SSLVALID) { this->SSLVALIDCHANGE = false; }
	else { this->SSLVALIDCHANGE = true; }

	if (this->NEWSSLWARNING == this->SSLWARNING) { this->SSLWARNCHANGE = false; }
	else { this->SSLWARNCHANGE = true; }
}

void record::write() {
	this->CODEEXPECTED = this->NEWCODEEXPECTED;
	this->SSLVALID = this->NEWSSLVALID;
	this->SSLWARNING = this->NEWSSLWARNING;

	if (this->CODEEXPECTED) { this->DOWNSINCE = 0; this->LASTALERT = 0; }
	if (not this->SSLWARNING) { this->LASTSSLWARNING = 0; }

	//Write all the data to the file.
}




//Get statements for private variables.
bool record::getCODECHANGE() { return this->CODECHANGE; }
bool record::getSSLVALIDCHANGE() { return this->SSLVALIDCHANGE; }
bool record::getSSLWARNCHANGE() { return this->SSLWARNCHANGE; }
int record::getDOWNSINCE() { return this->DOWNSINCE; }
int record::getLASTALERT() { return this->LASTALERT; }
int record::getLASTSSLWARNING() { return this->LASTSSLWARNING; }

//Destructor
record::~record() {}
