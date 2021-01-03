#pragma once
#include "AbstractCommand.h"

class CreateDirectoryCommand : public AbstractCommand
{
public:
	CreateDirectoryCommand() = default;
	void execute(Connection& connection, FileService& service) override;
	bool isMatch(const std::string& input) const override;
};