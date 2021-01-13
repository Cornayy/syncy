#include "../../Header/File/ServerFileService.h"

const std::string ServerFileService::OK_CODE = "OK";
const std::string ServerFileService::SPLIT = "|";
const std::string ServerFileService::NO_SUCH_DIRECTORY = "Error: no such directory";
const std::string ServerFileService::NO_SUCH_FILE = "Error: no such file";
const std::string ServerFileService::INVALID_PATH = "Error: invalid path";
const std::string ServerFileService::NO_PERMISSION = "Error: no permission";
const std::string ServerFileService::NOT_ENOUGH_DISK_SPACE = "Error: not enough disk space";
const std::string ServerFileService::NO_SUCH_ENTRY = "Error: no such entry";

ServerFileService::ServerFileService(const std::string& path) :
_servicePath { std::string("D:\\server") + "-" + path }
{
	// Create the synced directory if it does not exist yet.
	if (!std::filesystem::exists(_servicePath))
	{
		std::filesystem::create_directory(_servicePath);
	}
}

std::unique_ptr<std::vector<ServerFile>> ServerFileService::retrieveListing(const std::string& path) const
{
	auto files = std::make_unique<std::vector<ServerFile>>();

	for (const auto& file : std::filesystem::directory_iterator(std::filesystem::path(_servicePath) / path))
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

std::unique_ptr<std::istream> ServerFileService::retrieveFile(const std::string& path) const
{
	// Enable exceptions for the stream.
	auto file = std::make_unique<std::ifstream>(std::filesystem::path(_servicePath) / path, std::ifstream::in | std::ifstream::binary);
	file->exceptions(std::ifstream::badbit);
	return file;
}

std::string ServerFileService::directory(const std::filesystem::path& path)
{
	return std::filesystem::path(path).remove_filename().string();
}

void ServerFileService::remove(const std::string& path) const
{
	remove_all(std::filesystem::path(_servicePath) / path);
}

void ServerFileService::rename(const std::string& path, const std::string& name) const
{
	std::filesystem::rename(std::filesystem::path(_servicePath) / path, std::filesystem::path(std::filesystem::path(_servicePath) / path).replace_filename(name));
}

void ServerFileService::sendFile(const std::string& path, std::istream& stream, unsigned long size) const
{
	// Enable exceptions for the stream.
	auto writer = std::ofstream{ std::filesystem::path(_servicePath) / path, std::ofstream::out | std::ofstream::binary };
	writer.exceptions(std::ofstream::badbit);

	if (size > 0)
	{
		auto buffer = std::vector<char>(size);
		stream.read(buffer.data(), buffer.size());
		writer.write(buffer.data(), buffer.size());
	}
	
	writer.close();
}

void ServerFileService::createDirectory(const std::string& parent, const std::string& name) const
{
	create_directory(std::filesystem::path(_servicePath) / parent / name);
}

bool ServerFileService::isValidPath(const std::string& path) const
{
	return exists(std::filesystem::path(_servicePath) / path);
}

bool ServerFileService::canWrite(const std::string& path) const
{
	return space(std::filesystem::path(_servicePath) / path).available;
}

bool ServerFileService::isDirectory(const std::string& path) const
{
	return is_directory(std::filesystem::path(_servicePath) / path);
}

bool ServerFileService::isFile(const std::string& path) const
{
	return is_regular_file(std::filesystem::path(_servicePath) / path);
}

unsigned long ServerFileService::size(const std::string& path) const
{
	return file_size(std::filesystem::path(_servicePath) / path);
}

std::string ServerFileService::getType(const std::filesystem::path& path) const
{
	const auto status = std::filesystem::status(path);
	
	if (is_regular_file(status)) return "F";
	if (is_directory(status)) return "D";

	return "*";
}
