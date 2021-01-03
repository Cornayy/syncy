#include "../../Header/Command/ListDirectoryCommand.h"

void ListDirectoryCommand::execute(Connection& connection, FileService& service)
{
	const auto path = connection.next();
	const auto files = service.retrieveListing(path);

	for(const auto& file : files)
	{
		connection.send(file->info());
	}
}

bool ListDirectoryCommand::isMatch(const std::string& input) const
{
	return input == "dir";
}
