// Object to store configuration pulled from file.
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

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>

class configuration {
public:
	//Constructor
	configuration();

	//Add more config files
	int update(std::string confFile);

	//Ensure final configuration is valid
	int validate();

	//Return variable data.
	std::string getHOST();
	int getRETURNCODE();
	int getSSLVALID();
	int getSSLEXPIRYREMINDER();
	std::string getREPORTINGMETHOD();
	int getSSLEXPIRYSNOOZE();
	int getALERTSNOOZE();
	std::string getAPIURL();
	std::string getAPIPAYLOAD();

	//Destructor
	~configuration();

private:
	//Private variables
	std::string HOST;
	int RETURNCODE;
	int SSLVALID;
	int SSLEXPIRYREMINDER;
	std::string REPORTINGMETHOD = "NONE";
	int SSLEXPIRYSNOOZE; //How many days after previous alert to remind you SSL cert is expiring soon.
	int ALERTSNOOZE; //How many minutes after previous alert to wait before alerting again.
	std::string APIURL = "";
	std::string APIPAYLOAD = "";
};

#endif // CONFIGURATION_H