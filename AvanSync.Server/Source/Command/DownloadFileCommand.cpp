#include "../../Header/Command/DownloadFileCommand.h"

void DownloadFileCommand::execute()
{
}

bool DownloadFileCommand::isMatch(const std::string& input) const
{
	return input == "download-file";
}
