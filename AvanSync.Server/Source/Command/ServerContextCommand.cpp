#include "../../Header/Command/ServerContextCommand.h"

void ServerContextCommand::execute()
{
}

bool ServerContextCommand::isMatch(const std::string& input) const
{
	return input == "server-context";
}
