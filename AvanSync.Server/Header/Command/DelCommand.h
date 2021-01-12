#pragma once
#include "AbstractCommand.h"

class DelCommand : public AbstractCommand
{
public:
	DelCommand() = default;
	void execute(Connection& connection, const ServerFileService& service) override;
	bool isMatch(const std::string& input) const override;
};