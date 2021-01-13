#pragma once
#include "BaseCommand.h"

class DelCommand : public BaseCommand
{
public:
	void execute(ServerStreamWrapper& serverStream, const ServerFileService& service) override;
	bool isMatch(const std::string& input) const override;
};