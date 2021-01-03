#pragma once
#include "AbstractCommand.h"

class InfoCommand : public AbstractCommand
{
public:
	InfoCommand() = default;
	void execute(Connection& connection) override;
	bool isMatch(const std::string& input) const override;
};