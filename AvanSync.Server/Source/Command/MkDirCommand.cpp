#include "../../Header/Command/MkDirCommand.h"

void MkDirCommand::execute(Connection& connection, const ServerFileService& service)
{
	const auto parent = connection.next();
	const auto name = connection.next();

	if (service.isValidPath(parent) && service.isDirectory(parent))
	{
		try
		{
			service.createDirectory(parent, name);
			connection.send(ServerFileService::OK_CODE);
		}
		catch(...)
		{
			connection.send(ServerFileService::NO_PERMISSION);
		}
	}
	else
	{
		connection.send(ServerFileService::NO_SUCH_DIRECTORY);
	}
}

bool MkDirCommand::isMatch(const std::string& input) const
{
	return input == "mkdir";
}
