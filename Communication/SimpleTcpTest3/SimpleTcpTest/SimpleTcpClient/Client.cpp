#include "Client.h"

#include <array>

Client::Client(){}

Client::~Client(){
    std::cout << __FUNCTION__ << ". Closing client" << std::endl;
    closesocket(this->sock);
    StopWinSock();
}

bool Client::ParseTarget(const std::string& target, uint32_t& ipAddr, uint16_t& port)       // "xxx.xxx.xxx.xxx:pppp"
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

bool Client::Connect(const std::string& target){
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

    this->sock = socket(AF_INET, SOCK_STREAM, 0);
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
    if (connect(sock, reinterpret_cast<struct sockaddr*>(&serv_addr), sizeof(serv_addr)) < 0)
    {
        std::cout << __FUNCTION__ << " Cannot connect to target=" << target << std::endl;
        closesocket(sock);
        StopWinSock();
        return false;
    }
    return true;
}

bool Client::Run(std::string& request, std::string& response){   // "xxx.xxx.xxx.xxx:pppp"
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
    return true;
}

bool Client::StartWinSock()
{
    WSADATA wsaData = { 0 };

    const int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return false;
    }
    return true;
}

void Client::StopWinSock()
{
    WSACleanup();
}