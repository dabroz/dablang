#include "qdt3.h"

#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif

void updateOutput(const qString & s);
void AddDablangStatus2(const qString & ss);

int qdtprintf(const char * format, ...)
{
	char data[1024 * 16];
	va_list args;
	va_start (args, format);
	int q = vsprintf(data, format, args);
	va_end (args);

#ifdef _WIN32
	OutputDebugString(data);
#endif

	return q;
}

int qdtprintf2(const char * format, ...)
{
	char data[1024 * 16];
	va_list args;
	va_start (args, format);
	int q = vsprintf(data, format, args);
	va_end (args);

#ifdef _WIN32
	OutputDebugString(data);
#endif

	AddDablangStatus2(data);

	updateOutput(data);

	return q;
}

void qdterror(const char * format, ...)
{
	char data[1024 * 16];
	va_list args;
	va_start (args, format);
	int q = vsprintf(data, format, args);
	va_end (args);

#ifdef _WIN32
	OutputDebugString(data);
#endif

	AddDablangStatus2(data);

	DebugBreak();
}

void replace_all(std::string &str, const std::string &find_what, const std::string &replace_with)
{
	std::string::size_type pos=0;
	while((pos=str.find(find_what, pos))!=std::string::npos)
	{
		str.erase(pos, find_what.length());
		str.insert(pos, replace_with);
		pos+=replace_with.length();
	}
}
