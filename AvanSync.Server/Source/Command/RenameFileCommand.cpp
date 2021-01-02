#include "../../Header/Command/RenameFileCommand.h"

void RenameFileCommand::execute()
{
}

bool RenameFileCommand::isMatch(const std::string& input) const
{
	return input == "rename-file";
}
