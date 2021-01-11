#pragma once
#include <asio/ip/tcp.hpp>
#include <string>

class Connection
{
public:
	Connection(const std::string& address, const std::string& port);
	asio::ip::tcp::iostream& server() const;
	std::string prompt() const;
	std::string next() const;
	bool isActive() const;
	void disconnect();
	void send(const std::string& output) const;
private:
	bool _active;
	std::unique_ptr<asio::ip::tcp::iostream> _server;
};
