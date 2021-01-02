#pragma once
#include "AbstractCommand.h"

class DownloadFileCommand : public AbstractCommand
{
public:
	DownloadFileCommand() = default;
	void execute(Connection& connection) override;
	bool isMatch(const std::string& input) const override;
};