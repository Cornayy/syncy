#include "../../Header/Client/ClientStreamWrapper.h"
#include "../../Header/Client/Client.h"
#include <iostream>

ClientStreamWrapper::ClientStreamWrapper(const std::string& address, const std::string& port) :
_active { true },
_server{ std::make_unique<asio::ip::tcp::iostream>(address, port) }
{
	if (!_server)
	{
		throw std::runtime_error("could not connect to server");
	}
}

asio::ip::tcp::iostream& ClientStreamWrapper::server() const
{
	return *_server;
}

std::string ClientStreamWrapper::prompt() const
{
	std::cout << Client::PROMPT;
	std::string req;
	getline(std::cin, req);
	return req;
}

std::string ClientStreamWrapper::next()
{
	std::string request;
	getline(*_server, request);

	if (_server->fail())
	{
		throw std::exception{ "the stream failed" };
		_active = false;
	}
	
	request.erase(request.end() - 1);
	return request;
}

void ClientStreamWrapper::send(const std::string& output) const
{
	*_server << output << Client::CRLF;
}

void ClientStreamWrapper::send(const std::istream& stream) const
{
	*_server << stream.rdbuf();
}

void ClientStreamWrapper::disconnect()
{
	_active = false;
}

bool ClientStreamWrapper::isActive() const
{
	return _active;
}