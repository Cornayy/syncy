#include "../../Header/Command/GetCommand.h"

void GetCommand::execute(Connection& connection, const ServerFileService& service)
{
	const auto path = connection.next();

	if(service.isValidPath(path) && service.isFile(path))
	{
		try
		{
			const auto file = service.retrieveFile(path);
			const auto size = service.size(path);

			// Enable exceptions for the stream.
			file->exceptions(std::ifstream::badbit);
			connection.send(std::to_string(size));
			connection.send(*file);
		}
		catch(...)
		{
			connection.send(ServerFileService::NO_PERMISSION);
		}
	}
	else
	{
		connection.send(ServerFileService::NO_SUCH_FILE);
	}
}

bool GetCommand::isMatch(const std::string& input) const
{
	return input == "get";
}