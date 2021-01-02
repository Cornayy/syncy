#include "../../Header/Command/CreateDirectoryCommand.h"

void CreateDirectoryCommand::execute()
{
}

bool CreateDirectoryCommand::isMatch(const std::string& input) const
{
	return input == "create-directory";
}
