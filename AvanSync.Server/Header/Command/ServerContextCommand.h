#pragma once
#include "AbstractCommand.h"

class ServerContextCommand : public AbstractCommand
{
public:
	ServerContextCommand() = default;
	void execute() override;
	bool isMatch(const std::string& input) const override;
};
