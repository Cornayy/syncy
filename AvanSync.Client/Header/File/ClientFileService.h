#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <memory>

class ClientFileService
{
public:
	static const std::string OK_CODE;
	static const std::string OK_RENAMED;
	static const std::string OK_DELETED;
	static const std::string OK_NEW_DIRECTORY;
	static const std::string NO_SUCH_ENTRY;
	ClientFileService(const std::string& path);
	std::unique_ptr<std::istream> retrieveFile(const std::string& path) const;
	void remove(const std::string& path) const;
	void createDirectory(const std::string& parent, const std::string& name) const;
	void rename(const std::string& path, const std::string& name) const;
	void sendFile(const std::string& path, std::istream& stream, unsigned long size) const;
	bool isValidPath(const std::string& path) const;
	bool isDirectory(const std::string& path) const;
	bool isFile(const std::string& path) const;
	unsigned long size(const std::string& path) const;
private:
	std::string _servicePath;
};
