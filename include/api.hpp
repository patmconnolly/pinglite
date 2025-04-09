// Object to handle API calls.
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

#ifndef API_H
#define API_H

#include <string>
#include "api.hpp"

class api {
public:
	//Constructor
	api(std::string URL, std::string HEADERS, std::string PAYLOADFILE);

	//Destructor
	~api();

	void updatePlaceholders(std::string HOST, int HTTPCODE, bool SSLVALID, int SSLEXPIRYDAYS, std::string ALERTSTRING);
	void trigger();

private:
	//Private Variables
	std::string URL;
	std::string HEADERS;
	std::string PAYLOADFILE;
	std::string PAYLOAD;

	// CONSTANT Variables in JSON Payload
	const std::string placeholder_HOST = "{{ HOST }}";
	const std::string placeholder_HTTPCODE = "{{ HTTP_CODE }}";
	const std::string placeholder_SSLVALID = "{{ SSL_VALID }}";
	const std::string placeholder_SSLEXPIRYDAYS = "{{ SSL_EXPIRY_DAYS }}";
	const std::string placeholder_ALERTSTRING = "{{ ALERT_STRING }}";

	//Private Functions
	std::string replace_string(const std::string& original, const std::string& placeholder, const std::string& replacement);
};

#endif // API_H