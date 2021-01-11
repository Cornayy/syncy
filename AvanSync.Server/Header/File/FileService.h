#pragma once
#include <string>
#include <filesystem>
#include "File.h"

class FileService
{
public:
	FileService(const std::string& path);
	static const std::string OK_CODE;
	static const std::string SPLIT;
	static const std::string NO_SUCH_DIRECTORY;
	static const std::string NO_SUCH_FILE;
	static const std::string NO_PERMISSION;
	std::unique_ptr<std::vector<File>> retrieveListing(const std::string& path) const;
	bool isValidDirectory(const std::string& path) const;
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
	std::string _clientPath;
	std::string _serverPath;
};
