// SimpleTcpServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <this_thread>

/* The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 

#include <iostream>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")


void error(const char* msg)
{
    perror(msg);
    exit(0);
}

bool StartWinSock()
{
    WSADATA wsaData = { 0 };

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

bool ParseTarget(const std::string target, uint32_t& ipAddr, uint16_t& port)       // "xxx.xxx.xxx.xxx:pppp"
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
    return (port != 0);
}



bool RunServer(const std::string bindAddress)   // "xxx.xxx.xxx.xxx:pppp"
{
    std::cout << __FUNCTION__ << " Started RunServer" << ", bindAddress=" << bindAddress << std::endl;

    uint32_t ipAddr = 0;
    uint16_t port = 0;

    if (!ParseTarget(bindAddress, ipAddr, port))
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

    struct sockaddr_in serv_addr = { 0 };
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.S_un.S_addr = ipAddr;
    serv_addr.sin_port = port;

    // bind(int fd, struct sockaddr *local_addr, socklen_t addr_length)
    // bind() passes file descriptor, the address structure, 
    // and the length of the address structure
    // This bind() call will bind  the socket to the current IP address on port, portno
    if (bind(sock, reinterpret_cast<struct sockaddr*>(&serv_addr),  sizeof(serv_addr)) < 0)
    {
        std::cout << __FUNCTION__ << " Cannot bind to=" << bindAddress << std::endl;
        closesocket(sock);
        StopWinSock();
        return false;
    }

    // This listen() call tells the socket to listen to the incoming connections.
    // The listen() function places all incoming connection into a backlog queue
    // until accept() call accepts the connection.
    // Here, we set the maximum size for the backlog queue to 5.
    listen(sock, 5);

    // The accept() call actually accepts an incoming connection
    struct sockaddr_in cli_addr = { 0 };
    socklen_t clilen = sizeof(cli_addr);

    // This accept() function will write the connecting client's address info 
    // into the the address structure and the size of that structure is clilen.
    // The accept() returns a new socket file descriptor for the accepted connection.
    // So, the original socket file descriptor can continue to be used 
    // for accepting new connections while the new socker file descriptor is used for
    // communicating with the connected client.
    SOCKET newsock = accept(sock, reinterpret_cast<struct sockaddr*>(&cli_addr), &clilen);
    if (newsock == INVALID_SOCKET)
    {
        std::cout << __FUNCTION__ << " Accept failure" << std::endl;
        closesocket(sock);
        StopWinSock();
        return false;
    }
    std::cout << __FUNCTION__ << " server: got connection from " << inet_ntoa(cli_addr.sin_addr) << ":" << ntohs(cli_addr.sin_port) << std::endl;

    // This send() function sends the 13 bytes of the string to the new socket
    std::string response = "Hi Ovidiu";
    send(newsock, response.c_str(), static_cast<int>(response.length()), 0);

    closesocket(sock);
    StopWinSock();
    return true;
}

int main()
{
    const std::string bindAddress = "0.0.0.0:9001"; // any ip address, port 9001

    if (!RunServer(bindAddress ))
    {
        std::cout << __FUNCTION__ << " RunServer failed" << std::endl;
        return 0;
    }

    std::this_thread::sleep_for(std::chrono::seconds(10));
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



