#include "../../Header/Command/QuitCommand.h"

void QuitCommand::execute(ServerStreamWrapper& serverStream, const ServerFileService& service)
{
	serverStream.disconnect();
}

bool QuitCommand::isMatch(const std::string& input) const
{
	return input == "quit";
}