#pragma once
#include "AbstractCommand.h"

class GetCommand : public AbstractCommand
{
public:
	GetCommand() = default;
	void execute(Connection& connection, const ServerFileService& service) override;
	bool isMatch(const std::string& input) const override;
};