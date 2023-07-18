// SimpleTcpServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Server.h"

/* The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 

#include <iostream>
#include <string>
#include <array>

#include "Utility.h"


// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

// 
int main(int count, const char* args[])
{
	std::string bindAddress;	//  = "0.0.0.0:9001"; // any ip address, port 9001
	std::string root;

	std::cout << __FUNCTION__ << " count=" << count << std::endl;
	for (int i = 0; i < count; ++i)
	{
		std::cout << __FUNCTION__ << " arg=" << args[i] << std::endl;
		std::string key;
		std::string value;
		if (Utility::MakePair(args[i], '=', key, value) && key == "bind")
		{
			bindAddress = value;
		}
		if (Utility::MakePair(args[i], '=', key, value) && key == "root")
		{
			root = value;
			std::cout << __FUNCTION__ << __LINE__ << "root=" << root << std::endl;
		}
	}
	if (bindAddress.empty())
	{
		std::cout << __FUNCTION__ << ". Usage: >SimpleTcpServer bind=xxx.xxx.xxx.xxx:pppp root=folder_name" << std::endl;
		//return 0;

		bindAddress = "0.0.0.0:9001";
		std::cout << __FUNCTION__ << ". Defaulting to bindAddress=" << bindAddress << std::endl;
	}
	if (root.empty()) {
		std::cout << __FUNCTION__ << ". Usage: >SimpleTcpServer bind=xxx.xxx.xxx.xxx:pppp root=folder_name" << std::endl;
		std::cout << "Terminating because of empty root" << std::endl;
		return 0;
	}

	std::cout << __FUNCTION__ << ". SimpleTcpServer started. bind=" << bindAddress << " root=" << root << std::endl;
	std::cout << __FUNCTION__ << ". Press 'x<cr>'  to terminate"<< std::endl;

	Server server;
	if (!server.StartServer(bindAddress,root))
	{
		std::cout << __FUNCTION__ << ". Cannot start server" << std::endl;
		return 0;
	}

	char ch;
	while (std::cin.get(ch)) 
	{
		if (ch == 'x')
		{
			break;
		}
	}

	server.StopServer();


    return 0;
}

