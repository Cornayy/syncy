#include "../../Header/File/ClientFileService.h"

const std::string ClientFileService::OK_CODE = "OK";
const std::string ClientFileService::OK_RENAMED = "Success: the requested entry was renamed";
const std::string ClientFileService::OK_DELETED = "Success: the requested entry was deleted";
const std::string ClientFileService::OK_NEW_DIRECTORY = "Success: the requested directory was created";
const std::string ClientFileService::NO_SUCH_ENTRY = "Error: no such entry";

ClientFileService::ClientFileService(const std::string& path) :
_servicePath{ std::string("client") + "-" + path }
{
	// Create the synced directory if it does not exist yet.
	if (!std::filesystem::exists(_servicePath)) 
	{
		std::filesystem::create_directory(_servicePath);
	}
}

std::unique_ptr<std::istream> ClientFileService::retrieveFile(const std::string& path) const
{
	return std::make_unique<std::ifstream>(std::filesystem::path(_servicePath) / path, std::ifstream::in | std::ifstream::binary);
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
		// Copy the contents from the stream.
		std::copy_n(std::istreambuf_iterator<char>(stream), size, std::ostreambuf_iterator<char>(writer));
		stream.ignore(1);
	}

	writer.close();
}

bool ClientFileService::isValidPath(const std::string& path) const
{
	return exists(std::filesystem::path(_servicePath) / path);
}

bool ClientFileService::isDirectory(const std::string& path) const
{
	return is_directory(std::filesystem::path(_servicePath) / path);
}

bool ClientFileService::isFile(const std::string& path) const
{
	return is_regular_file(std::filesystem::path(_servicePath) / path);
}

unsigned long ClientFileService::size(const std::string& path) const
{
	return file_size(std::filesystem::path(_servicePath) / path);
}
