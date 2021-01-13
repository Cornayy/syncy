#include "../../Header/Command/DelCommand.h"

void DelCommand::execute(ServerStreamWrapper& serverStream, const ServerFileService& service)
{
	const auto path = serverStream.next();

	if (service.isValidPath(path))
	{
		try
		{
			service.remove(path);
			serverStream.send(ServerFileService::OK_CODE);
		}
		catch(...)
		{
			serverStream.send(ServerFileService::NO_PERMISSION);
		}
	}
	else
	{
		serverStream.send(ServerFileService::NO_SUCH_ENTRY);
	}
}

bool DelCommand::isMatch(const std::string& input) const
{
	return input == "del";
}
