#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include "../Client/ClientStreamWrapper.h"
#include "../File/ClientFileService.h"
#include "../File/SyncService.h"

class CommandController
{
public:
	CommandController(ClientStreamWrapper& clientStream);
	void handle(const std::string& input) const;
private:
	ClientStreamWrapper& _clientStream;
	std::unordered_map<std::string, std::function<void()>> _commands;
	std::unique_ptr<ClientFileService> _fileService;
	void registerCommand(const std::string& name, const std::function<void()>& command);
	void info() const;
	void dir() const;
	void quit() const;
	void get() const;
	void put() const;
	void ren() const;
	void del() const;
	void mkdir() const;
	void sync() const;
};
