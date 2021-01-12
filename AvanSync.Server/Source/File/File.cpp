#include "../../Header/File/File.h"
#include "../../Header/File/ServerFileService.h"
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
    stream << _type << ServerFileService::SPLIT << _name << ServerFileService::SPLIT << _timestamp << ServerFileService::SPLIT << _size;
    return stream.str();
}