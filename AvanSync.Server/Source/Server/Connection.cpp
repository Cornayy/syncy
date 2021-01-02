#include <iostream>
#include "../../Header/Server/Connection.h"
#include "../../Header/Server/Server.h"

Connection::Connection(int port) :
_active{ true },
_server{ _context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port) }
{
	_server.accept(_client.socket());
}

void Connection::connect()
{
	std::cerr << "client connected from " << _client.socket().local_endpoint() << Server::LF;
	_client << "Welcome to AvanSync server 1.0" << Server::CRLF;
}

void Connection::send(const std::string& output)
{
	_client << output << Server::CRLF;
}

bool Connection::isActive() const
{
	return _active;
}

std::string Connection::next()
{
	std::string request;
	getline(_client, request);
	request.erase(request.end() - 1);
	return request;
}