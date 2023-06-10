
#include <iostream>

#include "Client.h"


const Client::VALID_REQUESTS Client::viable_requests =
{
	{"Hi Elliot", "Hi Ovidiu"},
	{"Servus Elliot", "Servus Ovidiu"}
};

Client::Client(const SOCKET sock, const std::string& address)
	: sock(sock), address(address)
{
	setRequests();
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
	std::cout << "inbox=" << inbox << '\n';

	VALID_REQUESTS::const_iterator it = this->viable_requests.find(inbox);
	std::string response;
	if (it == this->viable_requests.end())
	{
		// cannot find inbox
		std::cout << "cannot find inbox command " << inbox << std::endl;
		response = " ";
	}
	else 
	{
		response = it->second;
	}
	
	response += std::string(". Message count = ");
	response += std::to_string(messageCount);
	outbox.insert(outbox.end(), response.c_str(), response.c_str() + response.length());	// append 
	
	this->inbox.clear();
	return true;
}

void Client::setRequests() {
	
}
