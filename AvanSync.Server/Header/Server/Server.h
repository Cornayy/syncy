#pragma once
#include <memory>
#include "../Factory/CommandFactory.h"
#include "Connection.h"

class Server
{
public:
	static const int PORT;
	static const char* LF;
	static const char* CRLF;
	Server(int port);
	void listen() const;
private:
	int _port;
	std::unique_ptr<CommandFactory> _factory;
};
