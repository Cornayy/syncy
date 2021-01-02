#pragma once
#include <string>

class AbstractCommand
{
public:
	virtual void execute() = 0;
	virtual bool isMatch(const std::string& input) const = 0;
	virtual ~AbstractCommand() = default;
};
