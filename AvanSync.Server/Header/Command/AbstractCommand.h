#pragma once
#include <string>
#include "../Server/Connection.h"
#include "../File/FileService.h"

class AbstractCommand
{
public:
	virtual void execute(Connection& connection, FileService& service) = 0;
	virtual bool isMatch(const std::string& input) const = 0;
	virtual ~AbstractCommand() = default;
};
