#pragma once
#include <string>
#include <memory>
#include "../Client/ClientStreamWrapper.h"
#include "CommandController.h"

class Client
{
public:
	static const char* LF;
	static const char* CRLF;
	static const char* PROMPT;
	Client(const std::string& address, const std::string& port);
	void listen() const;
private:
	std::unique_ptr<ClientStreamWrapper> _clientStream;
	std::unique_ptr<CommandController> _controller;
};
