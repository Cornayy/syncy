#include "../../Header/Command/QuitCommand.h"

void QuitCommand::execute(Connection& connection, const ServerFileService& service)
{
	connection.disconnect();
}

bool QuitCommand::isMatch(const std::string& input) const
{
	return input == "quit";
}