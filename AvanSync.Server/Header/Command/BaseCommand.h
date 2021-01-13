#pragma once
#include <string>
#include "../Server/Connection.h"
#include "../File/ServerFileService.h"

class BaseCommand
{
public:
	// Rule of five.
	BaseCommand() = default;
	BaseCommand(const BaseCommand & copyFrom) = delete;
	BaseCommand& operator=(const BaseCommand & copyFrom) = delete;
	BaseCommand(BaseCommand&&) = delete;
	BaseCommand& operator=(BaseCommand&&) = delete;
	virtual void execute(Connection& connection, const ServerFileService& service) = 0;
	virtual bool isMatch(const std::string& input) const = 0;
	virtual ~BaseCommand() = default;
};
