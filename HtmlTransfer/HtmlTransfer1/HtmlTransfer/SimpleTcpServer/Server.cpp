#include "Server.h"


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
#include <sstream>
#include <string>
#include <thread>         // std::thread
#include <mutex>
#include <chrono>


std::vector<char> StringToVector(const std::string& bytes)
{
    std::vector<char> dst;
    for (auto b : bytes)
    {
        dst.push_back(b);
    }
    return dst;
}

bool Server::StartWinSock()
{
    WSADATA wsaData = { 0 };

    const int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return false;
    }
    return true;
}

void Server::StopWinSock()
{
    WSACleanup();
}

bool Server::CreateListenSocket(const std::string& bindAddress)
{
    std::cout << __FUNCTION__ << " bindAddress=" << bindAddress << std::endl;

    uint32_t ipAddr = 0;
    uint16_t port = 0;

    if (!ParseTarget(bindAddress, ipAddr, port))
    {
        std::cout << __FUNCTION__ << " ParseTarget failure" << std::endl;
        return false;
    }

    SOCKET listenSock = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSock == INVALID_SOCKET)
    {
        std::cout << __FUNCTION__ << " Cannot create socket" << std::endl;
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
    if (bind(listenSock, reinterpret_cast<struct sockaddr*>(&serv_addr), sizeof(serv_addr)) < 0)
    {
        std::cout << __FUNCTION__ << " Cannot bind to=" << bindAddress << std::endl;
        CloseSocket(listenSock);
        return false;
    }

    // This listen() call tells the socket to listen to the incoming connections.
    // The listen() function places all incoming connection into a backlog queue
    // until accept() call accepts the connection.
    // Here, we set the maximum size for the backlog queue to 5.
    if (listen(listenSock, 5) != 0)
    {
        std::cout << __FUNCTION__ << " listen error" << std::endl;
        CloseSocket(listenSock);
        return false;
    }

    this->listenSock = listenSock;
    return true;
}

void Server::CloseListenSocket()
{
    if (listenSock != INVALID_SOCKET)
    {
        CloseSocket(listenSock);
        listenSock = INVALID_SOCKET;
    }
}

void Server::CloseSocket(SOCKET sock)
{
    if (sock != INVALID_SOCKET)
    {
        closesocket(sock);
    }
}

bool Server::AcceptClient(std::string& from)
{
    // The accept() call actually accepts an incoming connection
    struct sockaddr_in cli_addr = { 0 };
    socklen_t clilen = sizeof(cli_addr);

    SOCKET client = accept(listenSock, reinterpret_cast<struct sockaddr*>(&cli_addr), &clilen);
    if (client == INVALID_SOCKET)
    {
        std::cout << __FUNCTION__ << " Accept failure" << std::endl;
        return false;
    }
    std::stringstream ss;
    ss << inet_ntoa(cli_addr.sin_addr);
    ss << ':';
    ss << ntohs(cli_addr.sin_port);
    from = ss.str();
    std::cout << __FUNCTION__ << " server: got connection from " << from << std::endl;
    //clients.push_back(Client(client, from));
    clients.emplace_back(client, from, this->root);
    return true;
}

void Server::RemoveClient(const Client& client)
{
    std::list<Client>::iterator it = std::find_if(clients.begin(), clients.end(), 
        [&client](const Client& crt) { return crt.GetSocket() == client.GetSocket(); }
    );
    if (it != clients.end())
    {
        clients.erase(it);
    }
}

bool Server::ParseTarget(const std::string& target, uint32_t& ipAddr, uint16_t& port)       // "xxx.xxx.xxx.xxx:pppp"
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

bool Server::RunClient(Client& client)
{
    std::array<char, 4096>  inbox;
    int receivedBytes = recv(client.GetSocket(), inbox.data(), static_cast<int>(inbox.size()), 0);
    if (receivedBytes < 0)
    {
        int err = WSAGetLastError();
        std::cout << __FUNCTION__ << " recv error " << err << std::endl;
        return false;
    }
    if (receivedBytes == 0)
    {
        std::cout << __FUNCTION__ << " Peer closed connection" << std::endl;
        return false;
    }
    client.SetNewData(inbox.data(), receivedBytes);

    if (!client.Run())
    {
        std::cout << __FUNCTION__ << __LINE__ << '\n';
        return false;
    }
    std::cout << __FUNCTION__ << __LINE__ << '\n';
    std::vector<char> outbox = client.GetOutbox();
    std::cout << "outbox size=" << outbox.size() << '\n';
    if (outbox.size() == 0) {
        outbox = StringToVector("No Data");
    }
    int sentBytes = send(client.GetSocket(), outbox.data(), static_cast<int>(outbox.size()), 0);
    if (sentBytes < 0)
    {
        std::cout << __FUNCTION__ << " send error" << std::endl;
        return false;
    }
    if (sentBytes == 0)
    {
        std::cout << __FUNCTION__ << " Peer closed connection" << std::endl;
        return false;
    }
    client.TrimOutbox(sentBytes);
    return true; 
}


void Server::WorkerThread()
{
    std::stringstream ss;
    ss << std::this_thread::get_id();
    const size_t id = std::stoull(ss.str());

    std::cout << __FUNCTION__ << " Starting id=" << id << std::endl;


    while (!terminate)
    {
        fd_set readSet;
        FD_ZERO(&readSet);
        FD_SET(listenSock, &readSet);
        for (const auto& client : clients)
        {
            FD_SET(client.GetSocket(), &readSet);
        }
        const struct timeval timeout = {0, 100000};  // 100ms
        int rc = select(FD_SETSIZE, &readSet, nullptr, nullptr, &timeout);
        if (rc < 0)
        {
            // Major error. This should never happen!
            int err = WSAGetLastError();
            std::cout << __FUNCTION__ << " select error " << err << std::endl;
            return;
        }
        if (rc == 0)
        {
            // timeout
            continue;
        }

        // we have work to do
        if (FD_ISSET(listenSock, &readSet))
        {
            std::string from;
            AcceptClient(from);
        }

        std::vector<Client*> clientsToBeRemoved;

        for (auto& client : clients)
        {
            if (FD_ISSET(client.GetSocket(), &readSet))
            {
                if (!RunClient(client))
                {
                    clientsToBeRemoved.push_back(&client);
                }
            }
        }

        for (auto client : clientsToBeRemoved)
        {
            RemoveClient(*client);
        }
    }

    std::cout << __FUNCTION__ << " Ending id=" << id << std::endl;
}


bool Server::StartServer(const std::string& bindAddress, const std::string& root)
{
    this->root = root;
    terminate = false;
    if (!StartWinSock())
    {
        std::cout << __FUNCTION__ << " StartWinSock failure" << std::endl;
        return false;
    }
    if (!CreateListenSocket(bindAddress))
    {
        std::cout << __FUNCTION__ << " CreateListenSocket failure. bindAddress=" << bindAddress << std::endl;
        StopWinSock();
        return false;
    }

    this->thread = std::thread(&Server::WorkerThread, this /*, 10*/ );

    return true;
}

void Server::StopServer()
{
    this->terminate = true;
    thread.join();
    CloseListenSocket();
    StopWinSock();
}




