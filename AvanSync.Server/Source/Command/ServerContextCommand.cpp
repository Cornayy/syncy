#include "../../Header/Command/ServerContextCommand.h"

void ServerContextCommand::execute(Connection& connection)
{
	connection.send("AvanSync server 1.0, copyright (c) 2020 Corne Eggebeen.");
}

bool ServerContextCommand::isMatch(const std::string& input) const
{
	return input == "server-context";
}
