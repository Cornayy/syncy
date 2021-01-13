#include "../../Header/File/ServerFile.h"
#include "../../Header/File/ServerFileService.h"
#include <sstream>
#include <utility>

ServerFile::ServerFile(std::string type, std::string name, std::string timestamp, unsigned long long size) :
_type { std::move(type) },
_name{ std::move(name) },
_timestamp{ std::move(timestamp) },
_size{ size }
{
    _timestamp.erase(std::remove(_timestamp.begin(), _timestamp.end(), '\0'), _timestamp.end());
}

std::string ServerFile::info() const
{
    auto stream = std::stringstream{};
    stream << _type << ServerFileService::SPLIT << _name << ServerFileService::SPLIT << _timestamp << ServerFileService::SPLIT << _size;
    return stream.str();
}