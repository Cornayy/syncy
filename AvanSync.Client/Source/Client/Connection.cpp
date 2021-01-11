#include "../../Header/Client/Connection.h"
#include "../../Header/Client/Client.h"
#include <iostream>

Connection::Connection(const std::string& address, const std::string& port) :
_active { true },
_server{ std::make_unique<asio::ip::tcp::iostream>(address, port) }
{
	if (!_server) {
		throw std::runtime_error("could not connect to server");
	}
}

asio::ip::tcp::iostream& Connection::server() const
{
	return *_server;
}

std::string Connection::prompt() const
{
	std::cout << Client::PROMPT;
	std::string req;
	if (getline(std::cin, req)) {
		send(req);
	}
	return req;
}

std::string Connection::next() const
{
	std::string request;
	getline(*_server, request);

	if (_server->fail()) {
		throw std::runtime_error("the stream was interrupted");
	}
	
	request.erase(request.end() - 1);
	return request;
}

void Connection::send(const std::string& output) const
{
	*_server << output << Client::CRLF;
}

void Connection::disconnect()
{
	_active = false;
}

bool Connection::isActive() const
{
	return _active;
}