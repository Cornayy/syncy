#pragma once
#include "BaseCommand.h"

class DelCommand : public BaseCommand
{
public:
	void execute(Connection& connection, const ServerFileService& service) override;
	bool isMatch(const std::string& input) const override;
};