#include "../../Header/Command/UploadFileCommand.h"

void UploadFileCommand::execute()
{
}

bool UploadFileCommand::isMatch(const std::string& input) const
{
	return input == "upload-file";
}
