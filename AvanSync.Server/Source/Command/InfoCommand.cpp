#include "../../Header/Command/InfoCommand.h"

void InfoCommand::execute(ServerStreamWrapper& serverStream, const ServerFileService& service)
{
	serverStream.send("AvanSync server 1.0, copyright (c) 2021 Corne Eggebeen.");
}

bool InfoCommand::isMatch(const std::string& input) const
{
	return input == "info";
}
