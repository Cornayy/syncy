#pragma once
#include "AbstractCommand.h"

class DirCommand : public AbstractCommand
{
public:
	DirCommand() = default;
	void execute(Connection& connection, FileService& service) override;
	bool isMatch(const std::string& input) const override;
};