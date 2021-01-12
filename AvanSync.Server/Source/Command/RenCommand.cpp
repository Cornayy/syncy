#include "../../Header/Command/RenCommand.h"

void RenCommand::execute(Connection& connection, const ServerFileService& service)
{
	const auto path = connection.next();
	const auto name = connection.next();

	if (service.isValidPath(path))
	{
		try
		{
			service.rename(path, name);
			connection.send(ServerFileService::OK_CODE);
		}
		catch (...)
		{
			connection.send(ServerFileService::NO_PERMISSION);
		}
	}
	else
	{
		connection.send(ServerFileService::NO_SUCH_ENTRY);
	}
}

bool RenCommand::isMatch(const std::string& input) const
{
	return input == "ren";
}
