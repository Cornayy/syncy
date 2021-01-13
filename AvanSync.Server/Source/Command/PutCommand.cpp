#include "../../Header/Command/PutCommand.h"

void PutCommand::execute(ServerStreamWrapper& serverStream, const ServerFileService& service)
{
	const auto path = serverStream.next();
	const auto size = std::stoul(serverStream.next());
	const auto directory = ServerFileService::directory(path);

	if(!service.isDirectory(directory))
	{
		serverStream.send(ServerFileService::INVALID_PATH);
		return;
	}

	if(!service.canWrite(directory))
	{
		serverStream.send(ServerFileService::NOT_ENOUGH_DISK_SPACE);
		return;
	}

	try
	{
		serverStream.send(ServerFileService::OK_CODE);
		service.sendFile(path, serverStream.client(), size);
	}
	catch(...)
	{
		serverStream.send(ServerFileService::NO_PERMISSION);
	}
}

bool PutCommand::isMatch(const std::string& input) const
{
	return input == "put";
}
