#pragma once
#include <string>

class File
{
public:
	File(const std::string type, const std::string name, const std::string timestamp, unsigned long long size);
	std::string info() const;
private:
	std::string _type;
	std::string _name;
	std::string _timestamp;
	unsigned long long _size;
};
