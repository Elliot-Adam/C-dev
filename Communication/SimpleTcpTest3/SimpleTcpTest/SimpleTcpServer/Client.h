#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

/* The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 

#include <string>
#include <vector>
#include <map>


class Client
{
	using VALID_REQUESTS = std::map<std::string, std::string>;		// define the VALID_REQUESTS type same as std::map<std::string, std::string>.
	//typedef std::map<std::string, std::string> VALID_REQUESTS;	// also works but obsolete: use the "using" sintax

	static const VALID_REQUESTS viable_requests;		//returns response from input. Because "static", it must be initialized in a cpp file.
	const SOCKET			sock = INVALID_SOCKET;
	const std::string		address;

	std::vector<char>	inbox;
	std::vector<char>	outbox;

	std::string VectorToString(const std::vector<char>& bytes);
	std::vector<char> StringToVector(const std::string& bytes);

public:
	Client() = delete;
	Client(const SOCKET sock, const std::string& address);
	Client(const Client& other) = delete;
	Client& operator=(const Client& other) = delete;
	~Client();

	void SetNewData(const char* data, size_t length);
	const std::vector<char>& GetOutbox() const;
	void TrimOutbox(size_t length);
	void setRequests();			// Ovidiu: What is this for? 

	SOCKET GetSocket() const
	{
		return sock;
	}
	bool Run();
};

