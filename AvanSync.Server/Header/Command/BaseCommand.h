#pragma once
#include <string>
#include "../Server/ServerStreamWrapper.h"
#include "../File/ServerFileService.h"

class BaseCommand
{
public:
	// Rule of five.
	BaseCommand() = default;
	BaseCommand(const BaseCommand& copy) = delete;
	BaseCommand& operator=(const BaseCommand & copy) = delete;
	BaseCommand(BaseCommand&&) = delete;
	BaseCommand& operator=(BaseCommand&&) = delete;
	virtual void execute(ServerStreamWrapper& serverStream, const ServerFileService& service) = 0;
	virtual bool isMatch(const std::string& input) const = 0;
	virtual ~BaseCommand() = default;
};
