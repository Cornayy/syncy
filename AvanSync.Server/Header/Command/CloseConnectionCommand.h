#pragma once
#include "AbstractCommand.h"

class CloseConnectionCommand : public AbstractCommand
{
public:
	CloseConnectionCommand() = default;
	void execute(Connection& connection) override;
	bool isMatch(const std::string& input) const override;
};
