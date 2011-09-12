#pragma once
#include "nBase.hpp"
#include "nErrors.hpp"

#define NLogger_ON // do globalnych to

namespace NLib
{
	class NLogger
	{
	public:
		NLogger();
		~NLogger();

		static NRESULT initLogger(const char* szFilepath, bool bPrint = false);

		static void logMessage(const char* szFormat, ...);
		static void logMessage(const wchar_t* szFormat, ...);
		static void logError(const char* szErrorMessage);
		static void logFunctionError(const char* szFunctionName, NRESULT errorCode);

		static void release();
	};
}

#ifdef NLogger_ON
	#define NLogInit NLib::NLogger::initLogger
	#define NLogHead() NLib::NLogger::logMessage("[%s | %s | LINE: %d] >> ", __FILE__, __FUNCTION__, __LINE__)
	#define NLogMessage NLib::NLogger::logMessage
	#define NLogErrorFormat NLogHead(); NLogMessage
	#define NLogError(szErrorMessage) NLib::NLogger::logMessage("[%s | %s | LINE: %d] >> %s\n", __FILE__, __FUNCTION__, __LINE__, szErrorMessage)
	#define NLogFunctionError(szFunctionName, errorCode) NLib::NLogger::logMessage("[%s | %s | LINE: %d] >> Function \"%s\" returned an error. Error Code: %d.\n", __FILE__, __FUNCTION__, __LINE__, szFunctionName, errorCode)
	#define NLogRelease NLib::NLogger::release
#else
	inline void NInlineEmpty(...) { }
	#define NLogInit(a) true
	#define NLogHead()
	#define NLogMessage NInlineEmpty
	#define NLogError NInlineEmpty
	#define NLogFunctionError NInlineEmpty
	#define NLogRelease NInlineEmpty
#endif