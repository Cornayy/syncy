#include "../../Header/Command/DeleteFileCommand.h"

void DeleteFileCommand::execute()
{
}

bool DeleteFileCommand::isMatch(const std::string& input) const
{
	return input == "delete-file";
}
