#include <iostream>
#include "../../Header/Server/ServerStreamWrapper.h"
#include "../../Header/Server/Server.h"

ServerStreamWrapper::ServerStreamWrapper(int port) :
_active{ true },
_server{ _context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port) }
{
	_server.accept(_client.socket());
}

void ServerStreamWrapper::connect()
{
	std::cerr << "client connected from " << _client.socket().local_endpoint() << Server::LF;
	_client << "Welcome to AvanSync server 1.0" << Server::CRLF;
}

void ServerStreamWrapper::disconnect()
{
	std::cerr << "will disconnect from client " << _client.socket().local_endpoint() << Server::LF;
	_client << "Bye." << Server::CRLF;
	_active = false;
}

void ServerStreamWrapper::send(const std::string& output)
{
	_client << output << Server::CRLF;
}

void ServerStreamWrapper::send(const std::istream& stream)
{
	_client << stream.rdbuf();
}

asio::ip::tcp::iostream& ServerStreamWrapper::client()
{
	return _client;
}

bool ServerStreamWrapper::isActive() const
{
	return _active;
}

std::string ServerStreamWrapper::next()
{
	std::string request;
	getline(_client, request);

	if (_client.fail()) 
	{
		_active = false;
		throw std::exception{ "the stream failed" };
	}
	
	request.erase(request.end() - 1);
	return request;
}