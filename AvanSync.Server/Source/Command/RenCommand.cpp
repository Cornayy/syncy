#include "../../Header/Command/RenCommand.h"

void RenCommand::execute(ServerStreamWrapper& serverStream, const ServerFileService& service)
{
	const auto path = serverStream.next();
	const auto name = serverStream.next();

	if (service.isValidPath(path))
	{
		try
		{
			service.rename(path, name);
			serverStream.send(ServerFileService::OK_CODE);
		}
		catch (...)
		{
			serverStream.send(ServerFileService::NO_PERMISSION);
		}
	}
	else
	{
		serverStream.send(ServerFileService::NO_SUCH_ENTRY);
	}
}

bool RenCommand::isMatch(const std::string& input) const
{
	return input == "ren";
}
