#pragma once
#include <string>
#include <filesystem>

class FileService
{
public:
	static const std::string OK_CODE;
	static const std::string SPLIT;
private:
	const std::string& type(const std::string& path) const;
};
