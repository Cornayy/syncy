#include "../../Header/Command/UploadFileCommand.h"

void UploadFileCommand::execute(Connection& connection)
{
}

bool UploadFileCommand::isMatch(const std::string& input) const
{
	return input == "put";
}
