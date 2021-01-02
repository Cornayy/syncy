#pragma once
#include "AbstractCommand.h"

class ListDirectoryCommand : public AbstractCommand
{
public:
	ListDirectoryCommand() = default;
	void execute(Connection& connection) override;
	bool isMatch(const std::string& input) const override;
};