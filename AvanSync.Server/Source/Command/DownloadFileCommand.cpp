#include "../../Header/Command/DownloadFileCommand.h"

void DownloadFileCommand::execute(Connection& connection, FileService& service)
{
}

bool DownloadFileCommand::isMatch(const std::string& input) const
{
	return input == "get";
}
