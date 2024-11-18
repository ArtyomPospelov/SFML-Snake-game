#include "Log.h"
#include <fstream>
#include <ctime>

Log::Log(const char* path)
	: file(path, std::ios::app)
{
}

void Log::WriteError(const std::string& message)
{
	file << "ERRR [" << _getTimestamp() << "]:" << message << std::endl;
}

void Log::WriteInfo(const std::string& message)
{
	file << "INFO [" << _getTimestamp() << "]:" << message << std::endl;
}

std::string Log::_getTimestamp() const
{
	auto time = std::time(0);
	char str[50];
	std::tm tm;
	localtime_s(&tm, &time);
	asctime_s(str, 50, &tm);
	for (size_t i = 0; i < 50; ++i)
		if (str[i] == '\n')
			str[i] = '\0';
	return str;
}