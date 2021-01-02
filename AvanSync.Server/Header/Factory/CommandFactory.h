#pragma once
#include "../Command/AbstractCommand.h"
#include <memory>
#include <vector>

class CommandFactory
{
public:
	CommandFactory();
	std::unique_ptr<AbstractCommand> create(const std::string& input);
private:
	std::vector<std::unique_ptr<AbstractCommand>> _commands;
};
