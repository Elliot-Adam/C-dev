#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

// Target Windows 7 SP1
#define _WIN32_WINNT 0x0601
#include <WinSDKVer.h>

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
#include <array>
#include <list>
#include <thread>         // std::thread
#include <mutex>
#include <chrono>


#include "Client.h"

class Server
{
	SOCKET listenSock = INVALID_SOCKET;
	std::list<Client> clients;
	bool terminate = false;
	std::thread thread;
	std::string root;

	bool StartWinSock();
	void StopWinSock();

	bool CreateListenSocket(const std::string& bindAddress);
	void CloseListenSocket();
	static void CloseSocket(SOCKET sock);

	bool AcceptClient(std::string& from);
	void RemoveClient(const Client& client);

	bool RunClient(Client& client);

	void WorkerThread();


public:
	bool StartServer(const std::string& bindAddress, const std::string& root);
	void StopServer();

	bool ParseTarget(const std::string& bindAddress, uint32_t& ipAddr, uint16_t& port);       // "xxx.xxx.xxx.xxx:pppp"


};

