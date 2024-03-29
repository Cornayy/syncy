#include "../../Header/Server/Server.h"
#include <iostream>

const int Server::PORT = 3000;
const char* Server::LF = "\n";
const char* Server::CRLF = "\r\n";

Server::Server(int port, const std::string& path) :
_port{ port },
_fileService { std::make_unique<ServerFileService>(path) },
_factory{ std::make_unique<CommandFactory>() }
{
}

void Server::listen() const
{
	std::cerr << "waiting for client to connect" << LF;
	ServerStreamWrapper serverStream{ _port };
	serverStream.connect();

	while(serverStream.isActive())
	{
		try
		{
			const auto& input = serverStream.next();
			const auto& command = _factory->create(input);
			command->execute(serverStream, *_fileService);
		}
		catch(const std::exception & ex)
		{
			serverStream.send(ex.what());
		}
	}
}
