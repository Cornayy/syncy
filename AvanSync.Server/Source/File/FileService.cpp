#include "../../Header/File/FileService.h"

const std::string FileService::OK_CODE = "OK";
const std::string FileService::SPLIT = "|";
const std::string FileService::NO_SUCH_DIRECTORY = "Error: no such directory";
const std::string FileService::NO_SUCH_FILE = "Error: no such file";
const std::string FileService::NO_PERMISSION = "Error: no permission";

FileService::FileService(const std::string& path) :
_clientPath{ std::string("client") + "-" + path },
_serverPath { std::string("server") + "-" + path }
{
	// Create the synced directories if they do not exist yet.
	if (!std::filesystem::exists(_clientPath)) {
		std::filesystem::create_directory(_clientPath);
	}
	
	if (!std::filesystem::exists(_serverPath)) {
		std::filesystem::create_directory(_serverPath);
	}
}

std::unique_ptr<std::vector<File>> FileService::retrieveListing(const std::string& path) const
{
	auto files = std::make_unique<std::vector<File>>();

	for (const auto& file : std::filesystem::directory_iterator(std::filesystem::path(_serverPath) / path))
	{
		const auto& filePath = file.path();
		const auto fileType = getType(filePath);
		const auto size = fileType == "F" ? file.file_size() : 0;
		
		// Format timestamp.
		const auto timestamp = getTime<decltype(file.last_write_time())>(file.last_write_time());
		std::vector<char> buffer(20);
		std::strftime(buffer.data(), 20, "%Y-%m-%d %H:%M:%S", std::localtime(&timestamp));
		files->emplace_back( fileType, filePath.filename().string(), std::string(buffer.data(), 20), size);
	}

	return files;
}

bool FileService::isValidDirectory(const std::string& path) const
{
	return exists(std::filesystem::path(_serverPath) / path);
}

std::string FileService::getType(const std::filesystem::path& path) const
{
	const auto status = std::filesystem::status(path);
	
	if (is_regular_file(status)) return "F";
	if (is_directory(status)) return "D";

	return "*";
}
