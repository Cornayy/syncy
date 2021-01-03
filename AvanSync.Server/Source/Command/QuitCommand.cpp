#include "../../Header/Command/QuitCommand.h"

void QuitCommand::execute(Connection& connection, FileService& service)
{
	connection.disconnect();
}

bool QuitCommand::isMatch(const std::string& input) const
{
	return input == "quit";
}