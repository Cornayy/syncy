#pragma once
#include <string>

class ServerFile
{
public:
	ServerFile(std::string type, std::string name, std::string timestamp, unsigned long long size);
	std::string info() const;
private:
	std::string _type;
	std::string _name;
	std::string _timestamp;
	unsigned long long _size;
};
