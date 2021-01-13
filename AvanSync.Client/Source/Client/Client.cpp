#include "../../Header/Client/Client.h"
#include <iostream>

const char* Client::LF = "\n";
const char* Client::CRLF = "\r\n";
const char* Client::PROMPT = "avansync> ";

Client::Client(const std::string& address, const std::string& port) :
_clientStream{ std::make_unique<ClientStreamWrapper>(address, port)},
_controller{ std::make_unique<CommandController>(*_clientStream) }
{
}

void Client::listen() const
{
    while (_clientStream->server() && _clientStream->isActive()) {
        const auto resp = _clientStream->next();
        std::cout << resp << LF;
    	
    	while(_clientStream->isActive())
    	{
            auto req = _clientStream->prompt();
            _controller->handle(req);
    	}
    }
}
