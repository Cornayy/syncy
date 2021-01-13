#include "../../Header/File/ClientFileService.h"

const std::string ClientFileService::SPLIT = "|";
const std::string ClientFileService::OK_CODE = "OK";
const std::string ClientFileService::OK_SYNC = "Success: the requested path was synced";
const std::string ClientFileService::OK_RENAMED = "Success: the requested entry was renamed";
const std::string ClientFileService::OK_DELETED = "Success: the requested entry was deleted";
const std::string ClientFileService::OK_NEW_DIRECTORY = "Success: the requested directory was created";
const std::string ClientFileService::NO_SUCH_ENTRY = "Error: no such entry";

ClientFileService::ClientFileService(const std::string& path) :
_servicePath{ std::string("D:\\client") + "-" + path }
{
	// Create the synced directory if it does not exist yet.
	if (!std::filesystem::exists(_servicePath)) 
	{
		std::filesystem::create_directory(_servicePath);
	}
}

std::string ClientFileService::merge(const std::string& path, const std::string& concat) const
{
	return (std::filesystem::path(path) / concat).string();
}

std::unique_ptr<std::vector<ClientFile>> ClientFileService::retrieveListing(const std::string& path, const std::string& base) const
{
	auto files = std::make_unique<std::vector<ClientFile>>();

	for (const auto& file : std::filesystem::directory_iterator(std::filesystem::path(base) / path))
	{
		const auto& filePath = file.path();
		const auto fileType = getType(filePath);
		const auto size = fileType == "F" ? file.file_size() : 0;

		// Format timestamp.
		const auto timestamp = getTime<decltype(file.last_write_time())>(file.last_write_time());
		std::vector<char> buffer(20);
		std::strftime(buffer.data(), 20, "%Y-%m-%d %H:%M:%S", std::localtime(&timestamp));
		files->emplace_back(fileType, filePath.filename().string(), std::string(buffer.data(), 20), timestamp, size);
	}

	return files;
}

std::unique_ptr<std::istream> ClientFileService::retrieveFile(const std::string& path) const
{
	// Enable exceptions for the stream.
	auto file = std::make_unique<std::ifstream>(std::filesystem::path(_servicePath) / path, std::ifstream::in | std::ifstream::binary);
	file->exceptions(std::ifstream::badbit);
	return file;
}

void ClientFileService::remove(const std::string& path) const
{
	remove_all(std::filesystem::path(_servicePath) / path);
}

void ClientFileService::createDirectory(const std::string& parent, const std::string& name) const
{
	create_directory(std::filesystem::path(_servicePath) / parent / name);
}

void ClientFileService::rename(const std::string& path, const std::string& name) const
{
	std::filesystem::rename(std::filesystem::path(_servicePath) / path, std::filesystem::path(std::filesystem::path(_servicePath) / path).replace_filename(name));
}

void ClientFileService::sendFile(const std::string& path, std::istream& stream, unsigned long size) const
{
	// Enable exceptions for the stream.
	auto writer = std::ofstream{ std::filesystem::path(_servicePath) / path, std::ofstream::out | std::ofstream::binary };
	writer.exceptions(std::ofstream::badbit);

	if(size > 0)
	{
		auto buffer = std::vector<char>(size);
		stream.read(buffer.data(), buffer.size());
		writer.write(buffer.data(), buffer.size());
	}

	writer.close();
}

bool ClientFileService::isValidPath(const std::string& path) const
{
	return exists(std::filesystem::path(_servicePath) / path);
}

bool ClientFileService::isDirectory(const std::string& path, const std::string& base) const
{
	return is_directory(std::filesystem::path(base) / path);
}

bool ClientFileService::isFile(const std::string& path) const
{
	return is_regular_file(std::filesystem::path(_servicePath) / path);
}

unsigned long ClientFileService::size(const std::string& path) const
{
	return file_size(std::filesystem::path(_servicePath) / path);
}

std::string ClientFileService::getType(const std::filesystem::path& path) const
{
	const auto status = std::filesystem::status(path);

	if (is_regular_file(status)) return "F";
	if (is_directory(status)) return "D";

	return "*";
}
