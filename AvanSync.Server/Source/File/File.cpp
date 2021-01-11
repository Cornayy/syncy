#include "../../Header/File/File.h"
#include "../../Header/File/FileService.h"
#include <sstream>

File::File(std::string type, std::string name, std::string timestamp, unsigned long long size) :
_type { type },
_name{ name },
_timestamp{ timestamp },
_size{ size }
{
    _timestamp.erase(std::remove(_timestamp.begin(), _timestamp.end(), '\0'), _timestamp.end());
}

std::string File::info() const
{
    auto stream = std::stringstream{};
    stream << _type << FileService::SPLIT << _name << FileService::SPLIT << _timestamp << FileService::SPLIT << _size;
    return stream.str();
}