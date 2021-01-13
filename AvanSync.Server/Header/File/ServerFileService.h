#pragma once
#include <string>
#include <filesystem>
#include "ServerFile.h"
#include <fstream>

class ServerFileService
{
public:
	ServerFileService(const std::string& path);
	static const std::string OK_CODE;
	static const std::string SPLIT;
	static const std::string NO_SUCH_ENTRY;
	static const std::string INVALID_PATH;
	static const std::string NO_SUCH_DIRECTORY;
	static const std::string NO_SUCH_FILE;
	static const std::string NO_PERMISSION;
	static const std::string NOT_ENOUGH_DISK_SPACE;
	std::unique_ptr<std::vector<ServerFile>> retrieveListing(const std::string& path) const;
	std::unique_ptr<std::istream> retrieveFile(const std::string& path) const;
	static std::string directory(const std::filesystem::path& path);
	void remove(const std::string& path) const;
	void rename(const std::string& path, const std::string& name) const;
	void createDirectory(const std::string& parent, const std::string& name) const;
	void sendFile(const std::string& path, std::istream& stream, unsigned long size) const;
	bool isValidPath(const std::string& path) const;
	bool isDirectory(const std::string& path) const;
	bool isFile(const std::string& path) const;
	bool canWrite(const std::string& path) const;
	unsigned long size(const std::string& path) const;
private:
	template <typename Time>
	std::time_t getTime(Time time) const
	{
		// Converts the last write time to a usable format.
		using namespace std::chrono;
		const auto stamp = time_point_cast<system_clock::duration>(time - Time::clock::now() + system_clock::now());
		return system_clock::to_time_t(stamp);
	}
	std::string getType(const std::filesystem::path& path) const;
	std::string _servicePath;
};
