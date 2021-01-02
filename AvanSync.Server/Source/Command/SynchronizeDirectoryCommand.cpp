#include "../../Header/Command/SynchronizeDirectoryCommand.h"

void SynchronizeDirectoryCommand::execute(Connection& connection)
{
}

bool SynchronizeDirectoryCommand::isMatch(const std::string& input) const
{
	return input == "synchronize-directory";
}
