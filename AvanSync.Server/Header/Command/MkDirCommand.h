#pragma once
#include "AbstractCommand.h"

class MkDirCommand : public AbstractCommand
{
public:
	MkDirCommand() = default;
	void execute(Connection& connection, const ServerFileService& service) override;
	bool isMatch(const std::string& input) const override;
};