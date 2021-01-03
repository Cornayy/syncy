#include "../../Header/Command/DeleteFileCommand.h"

void DeleteFileCommand::execute(Connection& connection)
{
}

bool DeleteFileCommand::isMatch(const std::string& input) const
{
	return input == "del";
}
