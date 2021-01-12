#include "../../Header/Command/DelCommand.h"

void DelCommand::execute(Connection& connection, const ServerFileService& service)
{
	const auto path = connection.next();

	if (service.isValidPath(path))
	{
		try
		{
			service.remove(path);
			connection.send(ServerFileService::OK_CODE);
		}
		catch(...)
		{
			connection.send(ServerFileService::NO_PERMISSION);
		}
	}
	else
	{
		connection.send(ServerFileService::NO_SUCH_ENTRY);
	}
}

bool DelCommand::isMatch(const std::string& input) const
{
	return input == "del";
}
