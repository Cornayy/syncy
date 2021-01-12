#pragma once
#include "AbstractCommand.h"

class PutCommand : public AbstractCommand
{
public:
	PutCommand() = default;
	void execute(Connection& connection, const ServerFileService& service) override;
	bool isMatch(const std::string& input) const override;
};