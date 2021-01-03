#include "../../Header/Command/RenameFileCommand.h"

void RenameFileCommand::execute(Connection& connection, FileService& service)
{
}

bool RenameFileCommand::isMatch(const std::string& input) const
{
	return input == "ren";
}
