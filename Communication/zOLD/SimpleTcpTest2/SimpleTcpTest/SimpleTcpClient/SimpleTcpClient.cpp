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

void error(const char* msg)
{
    perror(msg);
    exit(0);
}

bool StartWinSock()
{
    WSADATA wsaData = {0};

    const int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return false;
    }
    return true;
}

void StopWinSock()
{
    WSACleanup();
}

bool ParseTarget(const std::string& target, uint32_t& ipAddr, uint16_t& port)       // "xxx.xxx.xxx.xxx:pppp"
{
    size_t colon = target.find(':');
    if (colon == std::string::npos)
    {
        std::cout << __FUNCTION__ << " target=" << target << std::endl;
        return false;
    }
    port = htons(static_cast<uint16_t>(std::atoi(&target[colon + 1])));
    const std::string strIpAddr(target.c_str(), colon);
    ipAddr = inet_addr(strIpAddr.c_str());
    return (port != 0) && (ipAddr != 0);
}



bool RunClient( const std::string& target, std::string& request, std::string& response )   // "xxx.xxx.xxx.xxx:pppp"
{
    std::cout << __FUNCTION__ << " Started RunClient" << ", target=" << target << std::endl;


    uint32_t ipAddr = 0;
    uint16_t port = 0;

    if (!ParseTarget(target, ipAddr, port))
    {
        std::cout << __FUNCTION__ << " ParseTarget failure" << std::endl;
        return false;
    }

    if (!StartWinSock())
    {
        std::cout << __FUNCTION__ << " StartWinSock failure" << std::endl;
        return false;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        std::cout << __FUNCTION__ << " Cannot create socket" << std::endl;
        StopWinSock();
        return false;
    }

    struct sockaddr_in serv_addr = {0};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.S_un.S_addr = ipAddr;
    serv_addr.sin_port = port;
    if (connect(sock, reinterpret_cast<struct sockaddr*>(&serv_addr), sizeof(serv_addr)) < 0)
    {
        std::cout << __FUNCTION__ << " Cannot connect to target=" << target << std::endl;
        closesocket(sock);
        StopWinSock();
        return false;
    }

    int sentBytes = send(sock, request.c_str(), static_cast<int>(request.length()), 0);
    if (sentBytes != request.length())
    {
        std::cout << __FUNCTION__ << " Cannot send request=" << request << std::endl;
        closesocket(sock);
        StopWinSock();
        return false;
    }

    std::array<char, 4096>  responseBuffer;

    int receivedBytes = recv(sock, responseBuffer.data(), static_cast<int>(responseBuffer.size()), 0);
    if (receivedBytes < 0)
    {
        std::cout << __FUNCTION__ << " Cannot receive response to request=" << request << std::endl;
        closesocket(sock);
        StopWinSock();
        return false;
    }
    if (receivedBytes == 0)
    {
        std::cout << __FUNCTION__ << " Peer closed connection" << std::endl;
        closesocket(sock);
        StopWinSock();
        return false;
    }
    response.assign(responseBuffer.data(), receivedBytes);

    closesocket(sock);
    StopWinSock();
    return true;
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
    std::string request = "Hi Elliot";
    std::string response;
    for (;;) {

        if (!RunClient(target, request, response))
        {
            std::cout << __FUNCTION__ << " RunClient failed" << std::endl;
            std::cout << __FUNCTION__ << " Press Enter key to exit ..." << std::endl;
            char ch;
            std::cin.get(ch);
            return 0;
        }
        std::cout << __FUNCTION__ << " request=" << request << std::endl;
        std::cout << __FUNCTION__ << " response=" << response << std::endl;

        std::cout << __FUNCTION__ << " Send again or press x key to exit ..." << std::endl;
        char ch;
        std::cin.get(ch);
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
            request = ' ';
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
