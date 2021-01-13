#include "../../Header/File/SyncService.h"
#include <iostream>
#include "../../Header/Client/Client.h"

SyncService::SyncService(const ClientFileService& fileService, ClientStreamWrapper& clientStream) :
_fileService { fileService },
_clientStream { clientStream }
{
}

void SyncService::walk(const std::string& path) const
{
	if (_fileService.isDirectory(path))
	{
		// Create the directory if it does not exist on server.
		if (!_fileService.isDirectory(path, "D:\\server-dir"))
		{
			const auto parent = std::filesystem::path{ path }.remove_filename().string();
			const auto name = std::filesystem::path{ path }.filename().string();

			_clientStream.send("mkdir");
			_clientStream.send(parent);
			_clientStream.send(name);

			const auto response = _clientStream.next();

			if (response != ClientFileService::OK_CODE)
			{
				std::cout << response << Client::LF;
				return;
			}

			_fileService.createDirectory(parent, name);
		}

		const auto clientFiles = _fileService.retrieveListing(path, "D:\\client-dir");
		const auto serverFiles = _fileService.retrieveListing(path, "D:\\server-dir");

		syncClientFiles(path, *clientFiles, *serverFiles);
		syncServerFiles(path, *clientFiles, *serverFiles);
	}
	else
	{
		std::cout << ClientFileService::NO_SUCH_ENTRY << Client::LF;
	}
}

void SyncService::syncClientFiles(const std::string& path, const std::vector<ClientFile>& clientFiles, const std::vector<ClientFile>& serverFiles) const
{
	for (const auto& file : clientFiles)
	{
		if (file.type() == "F")
		{
			const auto serverFile = std::find_if(serverFiles.begin(), serverFiles.end(), [&](const auto& serverFile) { return serverFile.name() == file.name(); });
			if (serverFile != serverFiles.end() && serverFile->timestampTime() >= file.timestampTime()) continue;

			// Upload the client file to the server.
			const auto clientPath = _fileService.merge(path, file.name());
			const auto size = _fileService.size(clientPath);
			const auto file = _fileService.retrieveFile(clientPath);

			_clientStream.send("put");
			_clientStream.send(clientPath);
			_clientStream.send(std::to_string(size));

			const auto response = _clientStream.next();

			if (response != ClientFileService::OK_CODE)
			{
				std::cout << response << Client::LF;
				return;
			}

			if (size > 0)
			{
				_clientStream.send(*file);
			}
		}
		// Recursively walk through all directories.
		else if (file.type() == "D")
		{
			walk(_fileService.merge(path, file.name()));
		}
	}
}

void SyncService::syncServerFiles(const std::string& path, const std::vector<ClientFile>& clientFiles, const std::vector<ClientFile>& serverFiles) const
{
	// Remove files that do not exist on the client.
	for (const auto& file : serverFiles)
	{
		const auto clientFile = std::find_if(clientFiles.begin(), clientFiles.end(), [&](const auto& clientFile) { return clientFile.name() == file.name(); });

		if (clientFile == clientFiles.end())
		{
			const auto serverPath = _fileService.merge(path, file.name());
			_clientStream.send("del");
			_clientStream.send(serverPath);
			const auto response = _clientStream.next();

			if (response != ClientFileService::OK_CODE)
			{
				std::cout << response << Client::LF;
				return;
			}

			_fileService.remove(serverPath);
		}
	}
}