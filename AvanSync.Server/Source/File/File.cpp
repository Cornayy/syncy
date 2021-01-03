#include "../../Header/File/File.h"
#include "../../Header/File/FileService.h"

File::File(const std::string& type, const std::string& name, const std::string& timestamp, size_t size) :
_type { type },
_name{ name },
_timestamp{ timestamp },
_size{ size }
{
}

std::string File::info() const
{
	const auto split = FileService::SPLIT;
	return _type + split + _name + split + _timestamp + split + std::to_string(_size);
}