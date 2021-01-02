#include "../../Header/Command/ListDirectoryCommand.h"

void ListDirectoryCommand::execute()
{
}

bool ListDirectoryCommand::isMatch(const std::string& input) const
{
	return input == "list-directory";
}
