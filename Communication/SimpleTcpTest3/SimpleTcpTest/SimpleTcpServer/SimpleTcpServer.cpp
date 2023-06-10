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


// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")


bool MakePair(const std::string& src, char separator, std::string& lhs, std::string& rhs)
{
	size_t index = src.find(separator);
	if (index != std::string::npos)
	{
		lhs.assign(src.c_str(), index);
		rhs.assign(src.begin()+index+1, src.end());
		return true;
	}
	return false;
}

// 
int main(int count, const char* args[])
{
	std::string bindAddress;	//  = "0.0.0.0:9001"; // any ip address, port 9001

	//std::cout << __FUNCTION__ << " count=" << count << std::endl;
	for (int i = 0; i < count; ++i)
	{
		std::string key;
		std::string value;
		if (MakePair(args[i], '=', key, value) && key == "bind")
		{
			bindAddress = value;
			break;
		}
	}
	if (bindAddress.empty())
	{
		std::cout << __FUNCTION__ << ". Usage: >SimpleTcpServer bind=xxx.xxx.xxx.xxx:pppp" << std::endl;
		//return 0;

		bindAddress = "0.0.0.0:9001";
		std::cout << __FUNCTION__ << ". Defaulting to bindAddress=" << bindAddress << std::endl;
	}

	std::cout << __FUNCTION__ << ". SimpleTcpServer started. bind=" << bindAddress << std::endl;
	std::cout << __FUNCTION__ << ". Press 'x<cr>'  to terminate"<< std::endl;

	Server server;
	if (!server.StartServer(bindAddress))
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

