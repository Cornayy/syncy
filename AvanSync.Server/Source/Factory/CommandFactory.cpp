#include "../../Header/Factory/CommandFactory.h"
#include "../../Header/Command/CloseConnectionCommand.h"
#include "../../Header/Command/CreateDirectoryCommand.h"
#include "../../Header/Command/DeleteFileCommand.h"
#include "../../Header/Command/DownloadFileCommand.h"
#include "../../Header/Command/ListDirectoryCommand.h"
#include "../../Header/Command/RenameFileCommand.h"
#include "../../Header/Command/ServerContextCommand.h"
#include "../../Header/Command/SynchronizeDirectoryCommand.h"
#include "../../Header/Command/UploadFileCommand.h"

CommandFactory::CommandFactory()
{
	_commands.push_back(std::make_unique<CloseConnectionCommand>());
	_commands.push_back(std::make_unique<CreateDirectoryCommand>());
	_commands.push_back(std::make_unique<DeleteFileCommand>());
	_commands.push_back(std::make_unique<DownloadFileCommand>());
	_commands.push_back(std::make_unique<ListDirectoryCommand>());
	_commands.push_back(std::make_unique<RenameFileCommand>());
	_commands.push_back(std::make_unique<ServerContextCommand>());
	_commands.push_back(std::make_unique<SynchronizeDirectoryCommand>());
	_commands.push_back(std::make_unique<UploadFileCommand>());
}

std::unique_ptr<AbstractCommand> CommandFactory::create(const std::string& input)
{
	for (auto& command : _commands) {
		if (command->isMatch(input)) {
			return std::move(command);
		}
	}

	const auto message = input + " did not match any registered command.";
	throw std::exception(message.c_str());
}