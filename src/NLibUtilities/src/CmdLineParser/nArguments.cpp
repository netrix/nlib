/*********************************************************************

Name:		NLib
Author:		Kamil Szatkowski "Netrix" (C)
Website:	http://www.netrix.org.pl/
License:	GNU GPL

*********************************************************************/
#include <NLib/CmdLineParser/nArguments.hpp>

namespace NLib {
namespace CmdLineParser
{
	void NArguments::create(int argc, const char* argv[])
	{
		if(argc > 1)	{	m_vArguments.create(argc - 1); }

		m_pLaunchPath = argv[0];
		m_uActualProcessed = 0;

		for(int i = 1; i < argc; ++i)
		{
			m_vArguments.push_back(argv[i]);
		}
	}
}
}
