#pragma once
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>

class Connection
{
public:
    Connection(int port);
    void connect();
    void disconnect();
    void send(const std::string& output);
    bool isActive() const;
    std::string next();
private:
    bool _active;
    asio::io_context _context;
    asio::ip::tcp::acceptor _server;
    asio::ip::tcp::iostream _client;
};
