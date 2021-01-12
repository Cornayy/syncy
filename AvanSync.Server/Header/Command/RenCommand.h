#pragma once
#include "AbstractCommand.h"

class RenCommand : public AbstractCommand
{
public:
	RenCommand() = default;
	void execute(Connection& connection, const ServerFileService& service) override;
	bool isMatch(const std::string& input) const override;
};