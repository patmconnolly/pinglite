// Object to handle recordkeeping.

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

	void write();

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
	int DOWNSINCE = 0;         //Timestamp of first down. ------------ 0 for still up.
	int LASTALERT = 0;         //Timestamp of last alert. ------------ 0 for still up.
	int LASTSSLWARNING = 0;    //Timestamp of last SSL expiry alert. - 0 for no alert needed.

	bool NEWCODEEXPECTED;      //Current return code.
	bool NEWSSLVALID;          //Current SSL is valid.
	bool NEWSSLWARNING;        //Current SSL Warning.

	bool CODECHANGE;           //Notes a change in the Return code as expected since last run.
	bool SSLVALIDCHANGE;       //Notes a change in SSL Validity.
	bool SSLWARNCHANGE;        //Notes a change in warning status of SSL.
};

#endif // RECORD_H