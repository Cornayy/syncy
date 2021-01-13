#pragma once
#include "BaseCommand.h"

class MkDirCommand : public BaseCommand
{
public:
	void execute(Connection& connection, const ServerFileService& service) override;
	bool isMatch(const std::string& input) const override;
};