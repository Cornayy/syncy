#include "../../Header/File/FileService.h"

const std::string FileService::OK_CODE = "OK";
const std::string FileService::SPLIT = "|";

FileService::FileService(const std::string& serverPath) :
_serverPath { serverPath }
{
}

std::vector<std::unique_ptr<File>> FileService::retrieveListing(const std::string& path) const
{
	std::vector<std::unique_ptr<File>> files;

	for (auto& file : std::filesystem::directory_iterator(std::filesystem::path(_serverPath).concat(path)))
	{
		const auto filePath = file.path();
		const auto fileType = getType(filePath);
		const auto size = fileType == "F" ? file.file_size() : 0;
		const auto timestamp = getTime<decltype(file.last_write_time())>(file.last_write_time());
		files.push_back(std::make_unique<File>(fileType, filePath.filename().string(), std::to_string(timestamp), static_cast<size_t>(size)));
	}

	return files;
}

std::string FileService::getType(const std::filesystem::path& path) const
{
	const auto status = std::filesystem::status(path);
	
	if (is_regular_file(status)) return "F";
	if (is_directory(status)) return "D";

	return "*";
}
