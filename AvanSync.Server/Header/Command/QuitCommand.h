#pragma once
#include "AbstractCommand.h"

class QuitCommand : public AbstractCommand
{
public:
	QuitCommand() = default;
	void execute(Connection& connection, const ServerFileService& service) override;
	bool isMatch(const std::string& input) const override;
};
