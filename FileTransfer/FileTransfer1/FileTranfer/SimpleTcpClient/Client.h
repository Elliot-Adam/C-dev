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

#include <iostream>

class Client
{
	SOCKET sock = INVALID_SOCKET;

public:
	Client();
	~Client();
	Client(const Client& other) = delete;
	Client& operator=(const Client& other) = delete;


	bool Connect(const std::string& target);
	bool Run(std::string& request, std::string& response);

private:
	bool StartWinSock();
	void StopWinSock();
	bool ParseTarget(const std::string& target, uint32_t& ipAddr, uint16_t& port);      // "xxx.xxx.xxx.xxx:pppp"

};

