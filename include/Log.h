#pragma once
#include <string>
#include <fstream>

class Log final
{
public:
	Log(const char* path);

	void WriteError(const std::string& message);
	void WriteInfo(const std::string& message);

private:
	std::string _getTimestamp() const;

private:
	std::ofstream file;
};