#include "../../Header/Command/QuitCommand.h"

void QuitCommand::execute(Connection& connection)
{
	connection.disconnect();
}

bool QuitCommand::isMatch(const std::string& input) const
{
	return input == "quit";
}