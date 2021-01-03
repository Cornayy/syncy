#pragma once
#include <string>
#include <filesystem>
#include "File.h"

class FileService
{
public:
	FileService(const std::string& serverPath);
	static const std::string OK_CODE;
	static const std::string SPLIT;
	std::vector<std::unique_ptr<File>> retrieveListing(const std::string& path) const;
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
	std::string _serverPath;
};
