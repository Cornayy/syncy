#pragma once
#include "AbstractCommand.h"

class SynchronizeDirectoryCommand : public AbstractCommand
{
public:
	SynchronizeDirectoryCommand() = default;
	void execute() override;
	bool isMatch(const std::string& input) const override;
};