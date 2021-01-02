#pragma once
#include "AbstractCommand.h"

class DeleteFileCommand : public AbstractCommand
{
public:
	DeleteFileCommand() = default;
	void execute(Connection& connection) override;
	bool isMatch(const std::string& input) const override;
};