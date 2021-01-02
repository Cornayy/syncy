#include "../../Header/Command/CloseConnectionCommand.h"

void CloseConnectionCommand::execute(Connection& connection)
{
	
}

bool CloseConnectionCommand::isMatch(const std::string& input) const
{
	return input == "quit";
}