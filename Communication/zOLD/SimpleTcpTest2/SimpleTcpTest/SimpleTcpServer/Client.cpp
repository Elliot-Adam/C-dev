
#include <iostream>

#include "Client.h"



Client::Client(const SOCKET sock, const std::string& address)
	: sock(sock), address(address)
{
	std::cout << __FUNCTION__ << " server: got connection from " << address << std::endl;
}


Client::~Client()
{
	std::cout << __FUNCTION__ << " closing connection from " << address << std::endl;
	closesocket(this->sock);
}

void Client::SetNewData(const char* data, size_t length)
{
	inbox.insert(inbox.end(), data, data + length);	// append 
}

const std::vector<char>& Client::GetOutbox() const
{
	return outbox;
}

void Client::TrimOutbox(size_t length)
{
	if (length < outbox.size())
	{
		outbox.erase(outbox.begin(), outbox.begin() + length);
	}
	else
	{
		outbox.clear();
	}
}

std::string Client::VectorToString(const std::vector<char>& bytes)
{
	std::string dst;
	for (auto b : bytes)
	{
		dst.push_back(b);
	}
	return dst;
}

std::vector<char> Client::StringToVector(const std::string& bytes)
{
	std::vector<char> dst;
	for (auto b : bytes)
	{
		dst.push_back(b);
	}
	return dst;
}




bool Client::Run()
{
	static size_t  messageCount = 0;
	++messageCount;

	std::string inbox = VectorToString(this->inbox);
	if (inbox == "Hi Elliot")
	{
		std::string response("Hi Ovidiu. Message count = ");
		response += std::to_string(messageCount);
		outbox.insert(outbox.end(), response.c_str(), response.c_str() + response.length());	// append 
	}
	else if (inbox == "Servus Elliot") {
		std::string response("Servus Ovidiu. Message count = ");
		response += std::to_string(messageCount);
		outbox.insert(outbox.end(), response.c_str(), response.c_str() + response.length());	// append 
	}
	else
	{
		std::string response("No comprende: ");
		response += inbox;
		response += ". Message count = ";
		response += std::to_string(messageCount);
		outbox.insert(outbox.end(), response.c_str(), response.c_str() + response.length());	// append 
	}
	return true;
}

