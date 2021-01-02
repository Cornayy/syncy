#pragma once
#include "AbstractCommand.h"

class CreateDirectoryCommand : public AbstractCommand
{
public:
	CreateDirectoryCommand() = default;
	void execute() override;
	bool isMatch(const std::string& input) const override;
};