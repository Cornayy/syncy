#include "../../Header/Command/MkDirCommand.h"

void MkDirCommand::execute(ServerStreamWrapper& serverStream, const ServerFileService& service)
{
	const auto parent = serverStream.next();
	const auto name = serverStream.next();

	if (service.isDirectory(parent))
	{
		try
		{
			service.createDirectory(parent, name);
			serverStream.send(ServerFileService::OK_CODE);
		}
		catch(...)
		{
			serverStream.send(ServerFileService::NO_PERMISSION);
		}
	}
	else
	{
		serverStream.send(ServerFileService::NO_SUCH_DIRECTORY);
	}
}

bool MkDirCommand::isMatch(const std::string& input) const
{
	return input == "mkdir";
}
