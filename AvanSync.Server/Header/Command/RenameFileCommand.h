#pragma once
#include "AbstractCommand.h"

class RenameFileCommand : public AbstractCommand
{
public:
	RenameFileCommand() = default;
	void execute(Connection& connection, FileService& service) override;
	bool isMatch(const std::string& input) const override;
};