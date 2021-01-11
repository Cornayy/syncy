#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include "../Client/Connection.h"

class CommandController
{
public:
	CommandController(Connection& connection);
	void handle(std::string& input);
private:
	Connection& _connection;
	void registerCommand(const std::string& name, const std::function<void()>& command);
	std::unordered_map<std::string, std::function<void()>> _commands;
	void dir() const;
	void quit() const;
};
