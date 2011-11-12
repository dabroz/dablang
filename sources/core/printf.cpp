#include "stdafx.h"
#include "dab_header.h"

#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif

void updateOutput(const qString & s)
{
	// PLACEHOLDER
}

void AddDablangStatus2(const qString & ss)
{
	// PLACEHOLDER
}

DABCORE_API int qdtprintf(const char * format, ...)
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

DABCORE_API int qdtprintf2(const char * format, ...)
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

DABCORE_API void qdterrorv(const char * format, va_list args)
{
	char data[1024 * 16];
	int q = vsprintf(data, format, args);

#ifdef _WIN32
	OutputDebugString(data);
#endif

	AddDablangStatus2(data);

	DebugBreak();
}

DABCORE_API void qdterror(const char * format, ...)
{
	va_list args;
	va_start (args, format);
	qdterrorv(format, args);
	va_end (args);
}

DABCORE_API void replace_all(std::string &str, const std::string &find_what, const std::string &replace_with)
{
	std::string::size_type pos=0;
	while((pos=str.find(find_what, pos))!=std::string::npos)
	{
		str.erase(pos, find_what.length());
		str.insert(pos, replace_with);
		pos+=replace_with.length();
	}
}
