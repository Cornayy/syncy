#pragma once
#include <memory>
#include "../Factory/CommandFactory.h"
#include "Connection.h"
#include "../File/FileService.h"

class Server
{
public:
	static const int PORT;
	static const char* LF;
	static const char* CRLF;
	Server(int port, const std::string& path);
	void listen() const;
private:
	int _port;
	std::unique_ptr<FileService> _fileService;
	std::unique_ptr<CommandFactory> _factory;
};
