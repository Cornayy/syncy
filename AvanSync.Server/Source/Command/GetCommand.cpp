#include "../../Header/Command/GetCommand.h"

void GetCommand::execute(ServerStreamWrapper& serverStream, const ServerFileService& service)
{
	const auto path = serverStream.next();

	if(service.isFile(path))
	{
		try
		{
			const auto file = service.retrieveFile(path);
			const auto size = service.size(path);
			serverStream.send(std::to_string(size));

			if(size > 0)
			{
				serverStream.send(*file);
			}
		}
		catch(...)
		{
			serverStream.send(ServerFileService::NO_PERMISSION);
		}
	}
	else
	{
		serverStream.send(ServerFileService::NO_SUCH_FILE);
	}
}

bool GetCommand::isMatch(const std::string& input) const
{
	return input == "get";
}
