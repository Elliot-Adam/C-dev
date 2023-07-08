#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "Client.h"


std::string readFileContent(const std::filesystem::path& inFileName)
{
	std::cout << __FUNCTION__ << ' ' << __LINE__ << " inFileName=" << inFileName << std::endl;
	std::ifstream ifs(inFileName);
	std::cout << "error=" << strerror(errno) << std::endl;
	return std::string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
}

void writeFileContent(const std::filesystem::path& outFileName, const std::string& content)
{
	std::cout << __FUNCTION__ << __LINE__ << " outfileName=" << outFileName << " content=" << content << '\n';
	std::ofstream ofs(outFileName);
	ofs << content;
	ofs.close();
}

Client::VALID_REQUESTS Client::viable_requests =
{
	{"g", Client::GetFile},
	{"p", Client::PutFile}
};


Client::Client(const SOCKET sock, const std::string& address,const std::string root)
	: sock(sock), address(address), root(root)
{
	std::cout << __FUNCTION__ << " server: got connection from " << address << std::endl;
}


Client::~Client()
{
	std::cout << __FUNCTION__ << " closing connection from " << address << std::endl;
	closesocket(this->sock);
}

void Client::SetNewData(const char* info, size_t length)
{
	data.insert(data.end(), info, info + length);	// append 
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
	std::cout << __FUNCTION__ << '\n';
	static size_t  actionCount = 0;
	++actionCount;
	std::string data = VectorToString(this->data);
	std::string func;
	std::string file_name;
	const std::filesystem::path exeDir(std::filesystem::path(root).remove_filename());
	if (!Utility::MakePair(data, ' ', func, file_name) || file_name.empty() || func.empty()) {
		return false;
	}
	VALID_REQUESTS::iterator it = viable_requests.find(func);
	if (it == this->viable_requests.end())
	{
		// cannot find function
		std::cout << "cannot find command " << func << std::endl;
	}
	else
	{
		it->second(file_name, this);
		std::cout << __FUNCTION__ << __LINE__ << '\n';
	}
	
	/*
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
	*/
	
	std::cout << "Action count = " << std::to_string(actionCount) << '\n';
	
	this->data.clear(); //Clear data
	return true;
}

bool Client::GetFile(const std::string& file_name) {
	//Get contents of file from file name
	std::cout << __FUNCTION__ << '\n';
	std::string contents;
	std::filesystem::path filePath = std::filesystem::path(root) /= file_name;
	try {
		contents = readFileContent(filePath);
		std::cout << __FUNCTION__ << __LINE__ << '\n';
	}
	catch (const std::exception& e){
		std::cout << __FUNCTION__ << __LINE__ << '\n';
		std::string msg = e.what();
		std::cout << "Cannot read file: filePath=" << filePath << " msg=" << msg << '\n';
		contents = msg;
	}
	std::cout << "contents=" << contents << '\n';
	outbox = StringToVector(contents); 

	return true;
}

bool Client::PutFile(const std::string& file_name_and_contents) {
	std::cout << __FUNCTION__ << '\n';
	//from file name add new txt file and delete old one if necessary
	std::string file_name;
	std::string contents;

	if (!Utility::MakePair(file_name_and_contents, ' ', file_name, contents)) {
		std::cout << __FUNCTION__ << "MakePair failed file_name_and_contents=" << file_name_and_contents;
	}

	std::filesystem::path dir = std::filesystem::path(root);
	dir /= file_name;
	//Create file_name.txt and write contents to it
	
	writeFileContent(dir.string(), contents);
	outbox = StringToVector("Sent " + contents);
	return true;
}


