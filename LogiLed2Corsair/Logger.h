#pragma once
#ifndef _LOGGER_H
#define _LOGGER_H

#include <stdio.h>

enum class LogLevel
{
	Debug,
	All,
	Critical,
	Warning,
	Information,
	User,
	Internal,
	None,

	// Just to force the compiler to treat the enum options as an int
	FORCE_32BIT = 0x7fffffff
};

class CLogger
{
public:
	static LogLevel					GetLogLevel(void)						{ return m_eLogLevel; }
	static void						SetLogLevel(const LogLevel e)
	{
#ifndef _DEBUG
		if ( e == LogLevel::Debug ) return;
#endif
		m_eLogLevel = e;
	}

	static void						InitLogging(const char* szFile);
	// Always remember to end logging when you are finished otherwise you will have file handles floating around
	static void						EndLogging(void);

	// Output the text to a log file.
	static void						OutputLog_s(const char* sz, const LogLevel eLevel);
	static void						OutputLog(const char* sz, const LogLevel eLevel, ...);

	static FILE*					GetFile() { return m_pFile; }

private:
	static LogLevel					m_eLogLevel;
	static FILE*					m_pFile;
};

#endif
