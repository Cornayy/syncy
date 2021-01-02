#pragma once
#include <string>
#include "../Server/Connection.h"

class AbstractCommand
{
public:
	virtual void execute(Connection& connection) = 0;
	virtual bool isMatch(const std::string& input) const = 0;
	virtual ~AbstractCommand() = default;
};
