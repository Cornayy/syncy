#include "../../Header/Command/CloseConnectionCommand.h"

void CloseConnectionCommand::execute()
{
	
}

bool CloseConnectionCommand::isMatch(const std::string& input) const
{
	return input == "quit";
}