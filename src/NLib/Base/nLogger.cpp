#include "nLogger.hpp"
#include "nAssert.hpp"
#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include <cwchar>	// for linux

#pragma warning(disable: 4996)

namespace
{
	FILE* g_pFile;
	bool g_bPrint;
}

namespace NLib
{
	/***********************************************************************/
	NLogger::NLogger()
	{
		g_pFile = null;
	}
	/***********************************************************************/
	NLogger::~NLogger()
	{
		release();
	}
	/***********************************************************************/
	NRESULT NLogger::initLogger(const char* szFilepath, bool bPrint)
	{
		if(g_pFile != null)		// Logger already created
		{
			return NRV_SUCCESS;
		}

		g_bPrint = bPrint;
		g_pFile = fopen(szFilepath, "w");
		if(g_pFile == null)
		{
			return NRV_FAILED_TO_OPEN_FILE;
		}

		logMessage("%s\n", szFilepath);

		return NRV_SUCCESS;
	}
	/***********************************************************************/
	void NLogger::release()
	{
		if(g_pFile != null)
		{
			fclose(g_pFile);
			g_pFile = null;
		}
	}
	/***********************************************************************/
	void NLogger::logMessage(const char* szFormat, ...)
	{
		if(g_pFile != null)
		{
			time_t rawTime;		// Time-stamp
			time(&rawTime);

			tm* pTs = localtime(&rawTime);

			char szBuffer[32];
			strftime(szBuffer, sizeof(szBuffer), "[ %H:%M:%S %d-%m-%Y ] ", pTs);

			// Writing timestamp
			fprintf(g_pFile, "%s", szBuffer);
			if(g_bPrint) { printf("%s", szBuffer); }

			va_list argptr;
			va_start(argptr, szFormat);

			// Writing message
			vfprintf(g_pFile, szFormat, argptr);
			if(g_bPrint) { vprintf(szFormat, argptr); }

			va_end(argptr);

			fprintf(g_pFile, "\n");
			if(g_bPrint) { printf("\n"); }
			fflush(g_pFile);
		}
	}
	/***********************************************************************/
	void NLogger::logMessage(const wchar_t* szFormat, ...)
	{
		if(g_pFile != null)
		{
			time_t rawTime;		// Time-stamp
			time(&rawTime);

			tm* pTs = localtime(&rawTime);

			wchar_t szBuffer[32];
			wcsftime(szBuffer, sizeof(szBuffer), L"[ %H:%M:%S %d-%m-%Y ] ", pTs);

			fwprintf(g_pFile, L"%s", szBuffer);	// Writing timestamp

			va_list argptr;
			va_start(argptr, szFormat);

			vfwprintf(g_pFile, szFormat, argptr);	// Writing message

			va_end(argptr);

			fwprintf(g_pFile, L"\n");
			fflush(g_pFile);
		}
	}
}
