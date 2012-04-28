#include "../NLib/nAssert.hpp"

#ifdef _DEBUG
	#include <stdio.h>

	namespace NLib
	{
		bool NAssertFunction(bool bResult, const char* szExpression, const char* szDescription, const char* szLine, const char* szFilename, const char* szFunction, bool* pbIgnoreAlways)
		{
			if(bResult)
			{
				return false;
			}
			else
			{
				char message[2048];

				sprintf_s<sizeof(message)>(message, "%s %s %s %s %s %s %s %s %s %s %s %s", "This szExpressionbResultsion: \n\n\"", szExpression,
								"\"\n\nhas returned false.\n\nDescription:\n\n\"", szDescription, "\"\n\nFilename: ",
								szFilename, "\nLine: ", szLine, "\nFunction: ", szFunction,
								"\n\nChoose Abort to stop application, Retry to ignore that message, Ignore to ",
								" ignore all messages of this assert.");

				switch(MessageBoxA(0, message, "Assert", MB_ABORTRETRYIGNORE | MB_ICONHAND))
				{
				case IDABORT:
					{
						sprintf_s<sizeof(message)>(message, "%s %s %s %s %s %s %s %s %s %s", szFilename, "(", szLine, ") : assert: \"", szExpression,
									"\" has returned FALSE in szFunction: \"", szFunction, "\". Description: \"", szDescription, "\".\n");
						OutputDebugStringA(message);
					}
					return true;
				case IDRETRY:
					return false;
				case IDIGNORE:
					{
						*pbIgnoreAlways = true;
					}
					return false;
				default:
					return true;
				}
			}
		}
	}
#endif