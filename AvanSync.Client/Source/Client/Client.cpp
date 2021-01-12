#include "../../Header/Client/Client.h"
#include <iostream>

const int Client::PORT = 5000;
const char* Client::LF = "\n";
const char* Client::CRLF = "\r\n";
const char* Client::PROMPT = "avansync> ";

Client::Client(const std::string& address, const std::string& port) :
_connection{ std::make_unique<Connection>(address, port)},
_controller{ std::make_unique<CommandController>(*_connection) }
{
}

void Client::listen() const
{
    while (_connection->server() && _connection->isActive()) {
        const auto resp = _connection->next();
        std::cout << resp << LF;
    	
    	while(_connection->isActive())
    	{
            auto req = _connection->prompt();
            _controller->handle(req);
    	}
    }
}
