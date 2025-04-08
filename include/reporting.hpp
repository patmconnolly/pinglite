// Object to handle reporting.
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

#ifndef REPORTING_H
#define REPORTING_H

#include <string>
#include "configuration.hpp"
#include "payload.hpp"

//Methods for reporting, more to be added as needed.
#include "api.hpp"

class reporting {
public:
	//Constructor
	reporting(configuration* conf, payload* results);

	//Destructor
	~reporting();

	//Returns 0 if no need for alerts. 1 if need to alert.
	int getRetcode();

	void trigger(std::string ALERTTEXT); //Triggers the alerts to be configured later.
	bool RETCODE_Compare(); // Compare return code to expected retcode, Return false if different.
	bool SSLVALID(); //Return false if SSL is invalid or nonexistant (http).
	bool SSLEXPIRYWARNING(); //Return false if SSL is expiring within the configured range.
	int getAlertSnooze(); //Return int in minutes of snooze for alerts.
	int getWarnSnooze();  //Return in in days of warning snooze for alerts.

	int getHTTPCODE(); //Get HTTP Return Code.
	int getEXPIRY(); //Get time till expire.

private:
	//Private variables of objects.
	configuration* conf;
	payload* results;

};

#endif // REPORTING_H