#pragma once
#include "AbstractCommand.h"

class ListDirectoryCommand : public AbstractCommand
{
public:
	ListDirectoryCommand() = default;
	void execute() override;
	bool isMatch(const std::string& input) const override;
};