#pragma once
#include "AbstractCommand.h"

class UploadFileCommand : public AbstractCommand
{
public:
	UploadFileCommand() = default;
	void execute(Connection& connection) override;
	bool isMatch(const std::string& input) const override;
};