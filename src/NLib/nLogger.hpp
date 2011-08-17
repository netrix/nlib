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

		static NRESULT InitLogger(const char* szFilepath, bool bPrint = false);

		static void LogMessage(const char* szFormat, ...);
		static void LogMessage(const wchar_t* szFormat, ...);
		static void LogError(const char* szErrorMessage);
		static void LogFunctionError(const char* szFunctionName, NRESULT errorCode);

		static void Release();
	};
}

#ifdef NLogger_ON
	#define NLogInit NLib::NLogger::InitLogger
	#define NLogHead() NLib::NLogger::LogMessage("[%s | %s | LINE: %d] >> ", __FILE__, __FUNCTION__, __LINE__)
	#define NLogMessage NLib::NLogger::LogMessage
	#define NLogErrorFormat NLogHead(); NLogMessage
	#define NLogError(szErrorMessage) NLib::NLogger::LogMessage("[%s | %s | LINE: %d] >> %s\n", __FILE__, __FUNCTION__, __LINE__, szErrorMessage)
	#define NLogFunctionError(szFunctionName, errorCode) NLib::NLogger::LogMessage("[%s | %s | LINE: %d] >> Function \"%s\" returned an error. Error Code: %d.\n", __FILE__, __FUNCTION__, __LINE__, szFunctionName, errorCode)
	#define NLogRelease NLib::NLogger::Release
#else
	inline void NInlineEmpty(...) { }
	#define NLogInit(a) true
	#define NLogHead()
	#define NLogMessage NInlineEmpty
	#define NLogError NInlineEmpty
	#define NLogFunctionError NInlineEmpty
	#define NLogRelease NInlineEmpty
#endif