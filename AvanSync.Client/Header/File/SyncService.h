#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "ClientFile.h"
#include "ClientFileService.h"
#include "../Client/ClientStreamWrapper.h"

class SyncService
{
public:
	SyncService(const ClientFileService& fileService, ClientStreamWrapper& clientStream);
	void walk(const std::string& path) const;
	void syncClientFiles(const std::string& path, const std::vector<ClientFile>& clientFiles, const std::vector<ClientFile>& serverFiles) const;
	void syncServerFiles(const std::string& path, const std::vector<ClientFile>& clientFiles, const std::vector<ClientFile>& serverFiles) const;
private:
	const ClientFileService& _fileService;
	ClientStreamWrapper& _clientStream;
};