#include "../../Header/Command/CreateDirectoryCommand.h"

void CreateDirectoryCommand::execute(Connection& connection)
{
}

bool CreateDirectoryCommand::isMatch(const std::string& input) const
{
	return input == "mkdir";
}
