// Object to handle recordkeeping.
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

#ifndef RECORD_H
#define RECORD_H

#include <string>

class record {
public:
	//Constructor
	record(std::string filename);

	//Destructor
	~record();

	void update(bool codeexpected, bool sslvalid, bool sslwarning);

	int write();

	bool alertRequired(int SSLEXPIRYSNOOZE, int ALERTSNOOZE); //Returns True if alert is needed, false if alert is not needed.
	std::string alertText(); //Returns alert text.

	bool getCODECHANGE();
	bool getSSLVALIDCHANGE();
	bool getSSLWARNCHANGE();
	int getDOWNSINCE();
	int getLASTALERT();
	int getLASTSSLWARNING();

private:
	//Private variables of objects.
	std::string FILENAME;      //Record file.
	bool CODEEXPECTED = true;  //Is the previous code as expected.
	bool SSLVALID = true;      //Is the SSL cert valid.
	bool SSLWARNING = false;   //Is the SSL cert warning for expiry.
	long long int DOWNSINCE = 0;         //Timestamp of first down. ------------ 0 for still up.
	long long int LASTALERT = 0;         //Timestamp of last alert. ------------ 0 for still up.
	long long int LASTSSLWARNING = 0;    //Timestamp of last SSL expiry alert. - 0 for no alert needed.

	bool NEWCODEEXPECTED;      //Current return code.
	bool NEWSSLVALID;          //Current SSL is valid.
	bool NEWSSLWARNING;        //Current SSL Warning.

	bool CODECHANGE;           //Notes a change in the Return code as expected since last run.
	bool SSLVALIDCHANGE;       //Notes a change in SSL Validity.
	bool SSLWARNCHANGE;        //Notes a change in warning status of SSL.

	const std::string HEADER = "RECORD"; // Header variable for the INI record file.

	long long int NOW;         //Time of updated information being added. To be used as the time since down if need be.

	std::string ALERTSTRING = "";  //String to be returned for the alert.

	long long stringToLongLong(const std::string& str);

	bool isAlertSnoozeExpired(int SNOOZE); //Int snooze in minutes.
	bool isWarnSnoozeExpired(int SNOOZE);  //Int snooze in days.
	bool isSnoozeExpired(int SNOOZE, long long LAST);      //Int snooze in seconds, long long last is time to compare to of last alert.
};

#endif // RECORD_H