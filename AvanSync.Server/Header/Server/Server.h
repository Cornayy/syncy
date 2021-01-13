#pragma once
#include <memory>
#include "../Factory/CommandFactory.h"
#include "../File/ServerFileService.h"

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
	std::unique_ptr<ServerFileService> _fileService;
	std::unique_ptr<CommandFactory> _factory;
};
