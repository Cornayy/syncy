#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <memory>
#include "ClientFile.h"

class ClientFileService
{
public:
	static const std::string SPLIT;
	static const std::string OK_CODE;
	static const std::string OK_SYNC;
	static const std::string OK_RENAMED;
	static const std::string OK_DELETED;
	static const std::string OK_NEW_DIRECTORY;
	static const std::string NO_SUCH_ENTRY;
	ClientFileService(const std::string& path);
	std::unique_ptr<std::vector<ClientFile>> retrieveListing(const std::string& path, const std::string& base) const;
	std::unique_ptr<std::istream> retrieveFile(const std::string& path) const;
	std::string merge(const std::string& path, const std::string& concat) const;
	void remove(const std::string& path) const;
	void createDirectory(const std::string& parent, const std::string& name) const;
	void rename(const std::string& path, const std::string& name) const;
	void sendFile(const std::string& path, std::istream& stream, unsigned long size) const;
	bool isValidPath(const std::string& path) const;
	bool isDirectory(const std::string& path, const std::string& base = "D:\\client-dir") const;
	bool isFile(const std::string& path) const;
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
