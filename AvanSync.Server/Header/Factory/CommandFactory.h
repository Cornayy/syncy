#pragma once
#include "../Command/BaseCommand.h"
#include <memory>
#include <vector>

class CommandFactory
{
public:
	CommandFactory();
	std::unique_ptr<BaseCommand>& create(const std::string& input);
private:
	std::vector<std::unique_ptr<BaseCommand>> _commands;
};
