#pragma once
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>

class ServerStreamWrapper
{
public:
    ServerStreamWrapper(int port);
    void connect();
    void disconnect();
    void send(const std::string& output);
    void send(const std::istream& stream);
    bool isActive() const;
    asio::ip::tcp::iostream& client();
    std::string next();
private:
    bool _active;
    asio::io_context _context;
    asio::ip::tcp::acceptor _server;
    asio::ip::tcp::iostream _client;
};
