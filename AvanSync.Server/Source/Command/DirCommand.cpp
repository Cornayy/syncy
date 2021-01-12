#include "../../Header/Command/DirCommand.h"

void DirCommand::execute(Connection& connection, const ServerFileService& service)
{
	const auto path = connection.next();

	if(service.isValidPath(path))
	{
		const auto files = service.retrieveListing(path);
		connection.send(std::to_string(files->size()));

		for (const auto& file : *files)
		{
			connection.send(file.info());
		}
	}
	else
	{
		connection.send(ServerFileService::NO_SUCH_DIRECTORY);
	}
}

bool DirCommand::isMatch(const std::string& input) const
{
	return input == "dir";
}
