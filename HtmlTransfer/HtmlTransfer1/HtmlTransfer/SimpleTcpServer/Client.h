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
#include <filesystem>
#include <fstream>

#include "Utility.h"

class Client
{
	using Command_Handler = bool(*)(const std::string&, const std::string&, const std::string&, const std::vector<std::string>&, const std::string&, Client*);
	using VALID_REQUESTS = std::map<std::string, Command_Handler>;		// define the VALID_REQUESTS type same as std::map<std::string, std::string>.
	//typedef std::map<std::string, std::string> VALID_REQUESTS;	// also works but obsolete: use the "using" sintax

	static VALID_REQUESTS viable_requests;		//returns response from input. Because "static", it must be initialized in a cpp file.
	const SOCKET			    sock = INVALID_SOCKET;
	const std::string		    address;
	const std::string			root;

	std::vector<char>    data;
	std::vector<char>    outbox;

	std::string VectorToString(const std::vector<char>& bytes);
	std::vector<char> StringToVector(const std::string& bytes);

	bool GetFile(const std::string& method, const std::string& file_name, const std::string& version, const std::vector<std::string>& params, const std::string& contents);
	bool PutFile(const std::string& method, const std::string& file_name, const std::string& version, const std::vector<std::string>& params, const std::string& contents);

	static bool FileExists(const std::filesystem::path& fileName);
	bool FileExists(const std::string& fileName);

	std::string FindDefaultFileName();

public:
	Client() = delete;
	Client(const SOCKET sock, const std::string& address,std::string root);
	Client(const Client& other) = delete;
	Client& operator=(const Client& other) = delete;
	~Client();

	void SetNewData(const char* data, size_t length);
	
	const std::vector<char>& GetOutbox() const;
	void TrimOutbox(size_t length);
	
	SOCKET GetSocket() const
	{
		return sock;
	}
	bool Run();
	
	static bool GetFile(const std::string& method, const std::string& file_name, const std::string& version, const std::vector<std::string>& params, const std::string& content, Client* client) {
		return client->GetFile(method, file_name, version, params,content);
	}
	static bool PutFile(const std::string& method, const std::string& file_name, const std::string& version, const std::vector<std::string>& params, const std::string& content, Client* client) {
		return client->PutFile(method, file_name, version, params,content);
	}
};

