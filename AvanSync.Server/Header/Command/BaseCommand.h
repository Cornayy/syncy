#pragma once
#include <string>
#include "../Server/Connection.h"
#include "../File/ServerFileService.h"

class BaseCommand
{
public:
	virtual void execute(Connection& connection, const ServerFileService& service) = 0;
	virtual bool isMatch(const std::string& input) const = 0;
	virtual ~BaseCommand() = default;
};
