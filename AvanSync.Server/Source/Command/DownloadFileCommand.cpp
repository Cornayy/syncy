#include "../../Header/Command/DownloadFileCommand.h"

void DownloadFileCommand::execute(Connection& connection)
{
}

bool DownloadFileCommand::isMatch(const std::string& input) const
{
	return input == "get";
}
