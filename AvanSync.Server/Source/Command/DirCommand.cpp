#include "../../Header/Command/DirCommand.h"

void DirCommand::execute(ServerStreamWrapper& serverStream, const ServerFileService& service)
{
	const auto path = serverStream.next();

	if(service.isDirectory(path))
	{
		const auto files = service.retrieveListing(path);
		serverStream.send(std::to_string(files->size()));

		for (const auto& file : *files)
		{
			serverStream.send(file.info());
		}
	}
	else
	{
		serverStream.send(ServerFileService::NO_SUCH_DIRECTORY);
	}
}

bool DirCommand::isMatch(const std::string& input) const
{
	return input == "dir";
}
