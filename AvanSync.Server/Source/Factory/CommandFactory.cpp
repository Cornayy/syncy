#include "../../Header/Factory/CommandFactory.h"
#include "../../Header/Command/QuitCommand.h"
#include "../../Header/Command/MkDirCommand.h"
#include "../../Header/Command/DelCommand.h"
#include "../../Header/Command/GetCommand.h"
#include "../../Header/Command/DirCommand.h"
#include "../../Header/Command/RenCommand.h"
#include "../../Header/Command/InfoCommand.h"
#include "../../Header/Command/PutCommand.h"

CommandFactory::CommandFactory()
{
	_commands.push_back(std::make_unique<QuitCommand>());
	_commands.push_back(std::make_unique<MkDirCommand>());
	_commands.push_back(std::make_unique<DelCommand>());
	_commands.push_back(std::make_unique<GetCommand>());
	_commands.push_back(std::make_unique<DirCommand>());
	_commands.push_back(std::make_unique<RenCommand>());
	_commands.push_back(std::make_unique<InfoCommand>());
	_commands.push_back(std::make_unique<PutCommand>());
}

std::unique_ptr<BaseCommand>& CommandFactory::create(const std::string& input)
{
	// Lowercase comparison.
	auto comparison{input};
	std::transform(comparison.begin(), comparison.end(), comparison.begin(), ::tolower);
	
	for (auto& command : _commands) {
		if (command->isMatch(comparison)) {
			return command;
		}
	}

	const auto message = input + " did not match any registered command.";
	throw std::exception(message.c_str());
}