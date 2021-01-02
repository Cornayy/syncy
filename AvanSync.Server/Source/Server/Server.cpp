#include "../../Header/Server/Server.h"
#include <iostream>

const int Server::PORT = 5000;
const char* Server::LF = "\n";
const char* Server::CRLF = "\r\n";

Server::Server(int port) :
_port{ port },
_factory{ std::make_unique<CommandFactory>() }
{
}

void Server::listen() const
{
	std::cerr << "waiting for client to connect" << LF;
	Connection connection{ _port };
	connection.connect();

	while(connection.isActive())
	{
		try
		{
			const auto& input = connection.next();
			const auto command = _factory->create(input);
			command->execute(connection);
		}
		catch(const std::exception & ex)
		{
			connection.send(ex.what());
		}
	}
}
