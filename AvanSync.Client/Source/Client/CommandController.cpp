#include "../../Header/Client/CommandController.h"
#include "../../Header/Client/Client.h"
#include <iostream>

// Can't pass as const reference and save it, since we have to call a non-const method on the object.
CommandController::CommandController(ClientStreamWrapper& clientStream) :
_clientStream{ clientStream },
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
	registerCommand("sync", [&] { sync(); });
}

void CommandController::dir() const
{
	const auto path = _clientStream.prompt();

	if (_fileService->isDirectory(path))
	{
		_clientStream.send("dir");
		_clientStream.send(path);

		const auto response = _clientStream.next();
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
			const auto result = _clientStream.next();
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
	_clientStream.send("quit");
	_clientStream.disconnect();
}

void CommandController::get() const
{
	const auto path = _clientStream.prompt();

	if (_fileService->isFile(path))
	{
		_clientStream.send("get");
		_clientStream.send(path);

		const auto response = _clientStream.next();
		unsigned long size;
		try {
			size = std::stoul(response);
		}
		catch (...) {
			std::cout << response << Client::LF;
			return;
		}

		_fileService->sendFile(path, _clientStream.server(), size);
		std::cout << ClientFileService::OK_DOWNLOAD << Client::LF;
	}
	else
	{
		std::cout << ClientFileService::NO_SUCH_ENTRY << Client::LF;
	}
}

void CommandController::put() const
{
	const auto path = _clientStream.prompt();

	if (_fileService->isFile(path))
	{
		const auto size = _fileService->size(path);
		const auto file = _fileService->retrieveFile(path);

		_clientStream.send("put");
		_clientStream.send(path);
		_clientStream.send(std::to_string(size));

		const auto response = _clientStream.next();

		if (response != ClientFileService::OK_CODE)
		{
			std::cout << response << Client::LF;
			return;
		}

		if (size > 0)
		{
			_clientStream.send(*file);
		}

		std::cout << ClientFileService::OK_UPLOAD << Client::LF;
	}
	else
	{
		std::cout << ClientFileService::NO_SUCH_ENTRY << Client::LF;
	}
}

void CommandController::ren() const
{
	const auto path = _clientStream.prompt();
	if (path.empty()) return;

	if (_fileService->isValidPath(path))
	{
		const auto name = _clientStream.prompt();

		_clientStream.send("ren");
		_clientStream.send(path);
		_clientStream.send(name);

		const auto response = _clientStream.next();

		if (response != ClientFileService::OK_CODE)
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
	const auto path = _clientStream.prompt();
	if (path.empty()) return;

	if (_fileService->isValidPath(path))
	{
		_clientStream.send("del");
		_clientStream.send(path);
		const auto response = _clientStream.next();

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
	_clientStream.send("info");
	const auto response = _clientStream.next();
	std::cout << response << Client::LF;
}

void CommandController::mkdir() const
{
	const auto parent = _clientStream.prompt();

	if (_fileService->isDirectory(parent))
	{
		const auto name = _clientStream.prompt();

		_clientStream.send("mkdir");
		_clientStream.send(parent);
		_clientStream.send(name);

		const auto response = _clientStream.next();

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

void CommandController::sync() const
{
	const auto service = std::make_unique<SyncService>(*_fileService, _clientStream);
	const auto path = _clientStream.prompt();
	service->walk(path);

	std::cout << ClientFileService::OK_SYNC << Client::LF;
}

void CommandController::handle(const std::string& input) const
{
	// Lowercase comparison.
	auto comparison{ input };
	auto found = false;
	std::transform(comparison.begin(), comparison.end(), comparison.begin(), ::tolower);

	for (const auto& command : _commands)
	{
		if (command.first == comparison)
		{
			found = true;
			command.second();
		}
	}

	if (!found)
	{
		_clientStream.send(input);
		const auto response = _clientStream.next();
		std::cout << response << Client::LF;
	}
}

void CommandController::registerCommand(const std::string& name, const std::function<void()>& command)
{
	_commands[name] = command;
}