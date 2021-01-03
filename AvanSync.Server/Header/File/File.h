#pragma once
#include <string>

class File
{
public:
	File(const std::string& type, const std::string& name, const std::string& timestamp, size_t size);
	const std::string& info() const;
private:
	const std::string& _type;
	const std::string& _name;
	const std::string& _timestamp;
	size_t _size;
};
