#pragma once
#include "AbstractCommand.h"

class CloseConnectionCommand : public AbstractCommand
{
public:
	CloseConnectionCommand() = default;
	void execute() override;
	bool isMatch(const std::string& input) const override;
};
