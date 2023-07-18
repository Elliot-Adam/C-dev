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

bool Client::FileExists(const std::filesystem::path& fileName)
{
	return std::filesystem::exists(fileName);
}

bool Client::FileExists(const std::string& fileName)
{
	std::filesystem::path path = root;
	path /= fileName;
	return std::filesystem::exists(path);
}

Client::VALID_REQUESTS Client::viable_requests =
{
	{"GET", Client::GetFile},
	//{"POST", Client::PutFile}
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

std::string Client::FindDefaultFileName() {
	if (this->FileExists(std::string("index.html"))) {
		return "index.html";
	}
	return "index.htm";
}


bool Client::Run()
{
	std::cout << __FUNCTION__ << '\n';
	static size_t  actionCount = 0;
	++actionCount;
	std::string data = VectorToString(this->data);
	std::cout << "data=" << data << '\n';
	std::vector<std::string> headers_and_content = Utility::Split(data, "\r\n\r\n");
	std::vector<std::string> params = Utility::Split(headers_and_content[0], "\r\n");
	const std::string& content = headers_and_content[1];
	for (const auto& param : params) {
		std::cout << param << '\n';
	}
	std::vector<std::string> cmd = Utility::Split(params[0], " ");
	std::string& method = cmd[0];
	std::string& file_name = cmd[1];
	std::string& version = cmd[2];
	if (file_name[0] == '/')
	{
		file_name.erase(0, 1);
	}
	if (file_name.empty()) {
		file_name = FindDefaultFileName();
	}
	
	VALID_REQUESTS::iterator it = viable_requests.find(method);
	if (it == this->viable_requests.end())
	{
		// cannot find function
		std::cout << "cannot find command " << method << std::endl;
	}
	else
	{
		it->second(method,file_name,version,params,content, this);
		std::cout << __FUNCTION__ << __LINE__ << '\n';
	}
	
	std::cout << "Action count = " << std::to_string(actionCount) << '\n';
	
	this->data.clear(); //Clear data
	return true;
}

bool Client::GetFile(const std::string& method, const std::string& file_name, const std::string& version , const std::vector<std::string>& params, const std::string& content) {
	//Get contents of file from file name
	std::cout << __FUNCTION__ << '\n';
	std::string responseContent;
	std::filesystem::path filePath = std::filesystem::path(root) /= file_name;
	try {
		responseContent = readFileContent(filePath);
		std::cout << __FUNCTION__ << __LINE__ << '\n';
	}
	catch (const std::exception& e){
		std::cout << __FUNCTION__ << __LINE__ << '\n';
		std::string msg = e.what();
		std::cout << "Cannot read file: filePath=" << filePath << " msg=" << msg << '\n';
		responseContent = msg;
	}
	std::cout << "contents=" << responseContent << '\n';
	outbox = StringToVector(responseContent); 

	return true;
}

bool Client::PutFile(const std::string& method, const std::string& file_name, const std::string& version, const std::vector<std::string>& params, const std::string& content) {
	std::cout << __FUNCTION__ << '\n';
	//from file name add new txt file and delete old one if necessary
	//std::string file_name;
	//std::string contents;
	/*
	if (!Utility::MakePair(file_name_and_contents, ' ', file_name, contents)) {
		std::cout << __FUNCTION__ << "MakePair failed file_name_and_contents=" << file_name_and_contents;
	}

	std::filesystem::path dir = std::filesystem::path(root);
	dir /= file_name;
	//Create file_name.txt and write contents to it
	
	writeFileContent(dir.string(), contents);
	outbox = StringToVector("Sent " + contents);
	*/
	return true;
}


