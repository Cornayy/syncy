#include "../../Header/Command/ListDirectoryCommand.h"

void ListDirectoryCommand::execute(Connection& connection)
{
}

bool ListDirectoryCommand::isMatch(const std::string& input) const
{
	return input == "dir";
}
