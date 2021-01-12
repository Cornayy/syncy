#include "../../Header/Command/PutCommand.h"

void PutCommand::execute(Connection& connection, const ServerFileService& service)
{
	const auto path = connection.next();
	const auto size = std::stoul(connection.next());
	const auto directory = ServerFileService::directory(path);

	if(!service.isDirectory(directory))
	{
		connection.send(ServerFileService::INVALID_PATH);
		return;
	}

	if(!service.canWrite(directory))
	{
		connection.send(ServerFileService::NOT_ENOUGH_DISK_SPACE);
		return;
	}

	try
	{
		connection.send(ServerFileService::OK_CODE);
		auto& stream = connection.client();
		service.sendFile(path, stream, size);
	}
	catch(...)
	{
		connection.send(ServerFileService::NO_PERMISSION);
	}
}

bool PutCommand::isMatch(const std::string& input) const
{
	return input == "put";
}
