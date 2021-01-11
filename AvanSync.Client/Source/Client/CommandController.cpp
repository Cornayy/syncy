#include "../../Header/Client/CommandController.h"
#include "../../Header/Client/Client.h"
#include <iostream>

CommandController::CommandController(Connection& connection) :
	_connection{ connection }
{
	registerCommand("dir", [&] { dir(); });
	registerCommand("quit", [&] { quit(); });
}

void CommandController::dir() const
{
	const auto path = _connection.prompt();
	const auto response = _connection.next();
	auto listing = 0;

	try
	{
		listing = std::stoi(response);
	}
	catch (...)
	{
		std::cout << response << Client::LF;
	}

	for (auto i = 0; i < listing; ++i)
	{
		const auto result = _connection.next();
		std::cout << result << Client::LF;
	}
}

void CommandController::quit() const
{
	_connection.disconnect();
}

void CommandController::handle(std::string& input)
{
	for (auto& command : _commands)
	{
		if (command.first == input)
		{
			command.second();
		}
	}
}

void CommandController::registerCommand(const std::string& name, const std::function<void()>& command)
{
	_commands[name] = command;
}


