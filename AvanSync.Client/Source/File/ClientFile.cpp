#include "../../Header/File/ClientFile.h"
#include "../../Header/File/ClientFileService.h"
#include <sstream>
#include <utility>

ClientFile::ClientFile(std::string type, std::string name, std::string timestamp, std::time_t timestampTime, unsigned long long size) :
_type { std::move(type) },
_name{ std::move(name) },
_timestamp{ std::move(timestamp) },
_timestampTime { timestampTime },
_size{ size }
{
    _timestamp.erase(std::remove(_timestamp.begin(), _timestamp.end(), '\0'), _timestamp.end());
}

std::string ClientFile::info() const
{
    auto stream = std::stringstream{};
    stream << _type << ClientFileService::SPLIT << _name << ClientFileService::SPLIT << _timestamp << ClientFileService::SPLIT << _size;
    return stream.str();
}

std::string ClientFile::name() const
{
    return _name;
}

std::string ClientFile::type() const
{
    return _type;
}

std::string ClientFile::timestamp() const
{
    return _timestamp;
}

std::time_t ClientFile::timestampTime() const
{
    return _timestampTime;
}

unsigned long long ClientFile::size() const
{
    return _size;
}