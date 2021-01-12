#include "../../Header/Client/CommandController.h"
#include "../../Header/Client/Client.h"
#include <iostream>

// Can't pass as const reference and save it, since we have to call a non-const method on the object.
CommandController::CommandController(Connection& connection) :
_connection{ connection },
_fileService{ std::make_unique<ClientFileService>("dir") }
{
	registerCommand("info", [&] { info(); });
	registerCommand("dir", [&] { dir(); });
	registerCommand("quit", [&] { quit(); });
	registerCommand("get", [&] { get(); });
	registerCommand("put", [&] { put(); });
	registerCommand("ren", [&] { ren(); });
	registerCommand("del", [&] { del(); });
	registerCommand("mkdir", [&] { mkdir(); });
}

void CommandController::dir() const
{
	const auto path = _connection.prompt();

	if (_fileService->isDirectory(path))
	{
		_connection.send("dir");
		_connection.send(path);

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
	else
	{
		std::cout << ClientFileService::NO_SUCH_ENTRY << Client::LF;
	}
}

void CommandController::quit() const
{
	_connection.send("quit");
	_connection.disconnect();
}

void CommandController::get() const
{
	const auto path = _connection.prompt();

	if ( _fileService->isFile(path))
	{
		_connection.send("get");
		_connection.send(path);

		const auto response = _connection.next();
		unsigned long size;
		try {
			size = std::stoul(response);
		}
		catch (...) {
			std::cout << response << Client::LF;
			return;
		}

		_fileService->sendFile(path, _connection.server(), size);
	}
	else
	{
		std::cout << ClientFileService::NO_SUCH_ENTRY << Client::LF;
	}
}

void CommandController::put() const
{
	const auto path = _connection.prompt();

	if (_fileService->isFile(path))
	{
		const auto size = _fileService->size(path);
		const auto file = _fileService->retrieveFile(path);

		_connection.send("put");
		_connection.send(path);
		_connection.send(std::to_string(size));

		const auto response = _connection.next();

		if (response != ClientFileService::OK_CODE)
		{
			std::cout << response << Client::LF;
			return;
		}

		_connection.send(*file);
	}
	else
	{
		std::cout << ClientFileService::NO_SUCH_ENTRY << Client::LF;
	}
}

void CommandController::ren() const
{
	const auto path = _connection.prompt();
	if (path.empty()) return;

	if(_fileService->isValidPath(path))
	{
		const auto name = _connection.prompt();

		_connection.send("ren");
		_connection.send(path);
		_connection.send(name);

		const auto response = _connection.next();

		if(response != ClientFileService::OK_CODE)
		{
			std::cout << response << Client::LF;
			return;
		}

		_fileService->rename(path, name);
		std::cout << ClientFileService::OK_RENAMED << Client::LF;
	}
	else
	{
		std::cout << ClientFileService::NO_SUCH_ENTRY << Client::LF;
	}
}

void CommandController::del() const
{
	const auto path = _connection.prompt();
	if (path.empty()) return;

	if (_fileService->isValidPath(path))
	{
		_connection.send("del");
		_connection.send(path);
		const auto response = _connection.next();

		if (response != ClientFileService::OK_CODE)
		{
			std::cout << response << Client::LF;
			return;
		}

		_fileService->remove(path);
		std::cout << ClientFileService::OK_DELETED << Client::LF;
	}
	else
	{
		std::cout << ClientFileService::NO_SUCH_ENTRY << Client::LF;
	}
}

void CommandController::info() const
{
	_connection.send("info");
	const auto response = _connection.next();
	std::cout << response << Client::LF;
}

void CommandController::mkdir() const
{
	const auto parent = _connection.prompt();

	if (_fileService->isDirectory(parent))
	{
		const auto name = _connection.prompt();

		_connection.send("mkdir");
		_connection.send(parent);
		_connection.send(name);

		const auto response = _connection.next();

		if (response != ClientFileService::OK_CODE)
		{
			std::cout << response << Client::LF;
			return;
		}

		_fileService->createDirectory(parent, name);
		std::cout << ClientFileService::OK_NEW_DIRECTORY << Client::LF;
	}
	else
	{
		std::cout << ClientFileService::NO_SUCH_ENTRY << Client::LF;
	}
}

void CommandController::handle(const std::string& input) const
{
	// Lowercase comparison.
	auto comparison{ input };
	auto found = false;
	std::transform(comparison.begin(), comparison.end(), comparison.begin(), ::tolower);
	
	for (auto& command : _commands)
	{
		if (command.first == comparison)
		{
			found = true;
			command.second();
		}
	}

	if(!found)
	{
		_connection.send(input);
		const auto response = _connection.next();
		std::cout << response << Client::LF;
	}
}

void CommandController::registerCommand(const std::string& name, const std::function<void()>& command)
{
	_commands[name] = command;
}


