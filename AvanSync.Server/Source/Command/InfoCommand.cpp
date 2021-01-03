#include "../../Header/Command/InfoCommand.h"

void InfoCommand::execute(Connection& connection)
{
	connection.send("AvanSync server 1.0, copyright (c) 2020 Corne Eggebeen.");
}

bool InfoCommand::isMatch(const std::string& input) const
{
	return input == "info";
}
