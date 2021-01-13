#pragma once
#include <string>
#include <ctime>

class ClientFile
{
public:
	ClientFile(std::string type, std::string name, std::string timestamp, std::time_t timestampTime, unsigned long long size);
	std::string info() const;
	std::string type() const;
	std::string name() const;
	std::string timestamp() const;
	std::time_t timestampTime() const;
	unsigned long long size() const;
private:
	std::string _type;
	std::string _name;
	std::string _timestamp;
	std::time_t _timestampTime;
	unsigned long long _size;
};
