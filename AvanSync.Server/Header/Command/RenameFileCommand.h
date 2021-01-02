#pragma once
#include "AbstractCommand.h"

class RenameFileCommand : public AbstractCommand
{
public:
	RenameFileCommand() = default;
	void execute() override;
	bool isMatch(const std::string& input) const override;
};