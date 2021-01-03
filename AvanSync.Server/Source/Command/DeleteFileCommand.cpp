#include "../../Header/Command/DeleteFileCommand.h"

void DeleteFileCommand::execute(Connection& connection, FileService& service)
{
}

bool DeleteFileCommand::isMatch(const std::string& input) const
{
	return input == "del";
}
