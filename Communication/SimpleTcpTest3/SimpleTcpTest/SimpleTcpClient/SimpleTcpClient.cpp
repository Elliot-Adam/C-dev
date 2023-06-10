// SimpleTcpClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
#include <array>

#include "Client.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

bool MakePair(const std::string& src, char separator, std::string& lhs, std::string& rhs)
{
    size_t index = src.find(separator);
    if (index != std::string::npos)
    {
        lhs.assign(src.c_str(), index);
        rhs.assign(src.begin() + index + 1, src.end());
        return true;
    }
    return false;
}

int main(int count, const char* args[])
{
    std::string target;	//  = "0.0.0.0:9001"; // any ip address, port 9001

    std::cout << __FUNCTION__ << " count=" << count << std::endl;
    for (int i = 0; i < count; ++i)
    {
        std::string key;
        std::string value;
        std::cout << args[i] << std::endl;
        if (MakePair(args[i], '=', key, value) && key == "target")
        {
            target = value;
            break;
        }
    }
    if (target.empty())
    {
        std::cout << __FUNCTION__ << ". Usage: >SimpleTcpClient target=xxx.xxx.xxx.xxx:pppp" << std::endl;
        return 0;
    }
    
    Client client;

    if (!client.Connect(target)) {
        std::cout << __FUNCTION__ << ". Cannot connect to target " << target << std::endl;
        return 0;
    }

    std::string request;
    std::string response;
    int client_counter = 0;
    for (;;) {
        std::cout << __FUNCTION__ << " Send again or press x key to exit ..." << std::endl;
        char ch;
        //std::cin.get(ch);
        std::cin >> ch;
        client_counter++;
        std::cout << "ch=" << ch << " , client_counter=" << client_counter;
        if (ch == 'x') {
            std::cout << "\nTerminating client\n";
            break;
        }
        else if (ch == 'r') {
            std::cout << "\nSending again\n";
            request = "Servus Elliot";
        }
        else if (ch == 'e') {
            std::cout << "\nSending again\n";
            request = "Hi Elliot";
        }
        else {
            request = "";
            std::cout << "\n Unknown command=" << ch << std::endl;
            std::cout << "Known commands are: r, e, and x to exit\n";
            continue;
        }
        if (client.Run(request, response))
        {
            std::cout << __FUNCTION__ << " request=" << request << std::endl;
            std::cout << __FUNCTION__ << " response=" << response << std::endl;
        }
        else
        {
            std::cout << __FUNCTION__ << " RunClient failed" << std::endl;
//            std::cout << __FUNCTION__ << " Press Enter key to exit ..." << std::endl;
//            char ch;
//            std::cin.get(ch);
//            return 0;
        }
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
