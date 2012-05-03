/*********************************************************************

Name:		Raytracer
Author:		Kamil Szatkowski "Netrix" (C)
Website:	http://www.netrix.org.pl/

*********************************************************************/
#include "nCommandWalker.hpp"
#include <NLib/Utilities/nString.hpp>
#include <stdio.h>
using namespace NLib::Utilities;

namespace
{
	const NLib::NUint32 VECTOR_REALLOC = 4;
}

namespace NLib {
namespace CmdLineParser
{
	void NCommandWalker::create(int argc, const char* argv[])
	{
		m_vCommands.create(VECTOR_REALLOC, VECTOR_REALLOC);
		m_arguments.create(argc, argv);
		m_pDefaultAction = null;
	}

	void NCommandWalker::release()
	{
		m_arguments.release();
		m_vCommands.release();
	}

	void NCommandWalker::addCommand(const char* szCommand, const char* szHelp, NCommandCallback pCallback)
	{
		Command c =
		{
			szCommand,
			szHelp,
			pCallback
		};

		m_vCommands.push_back(c);
	}

	void NCommandWalker::setDefault(NCommandCallback pCallback)
	{
		m_pDefaultAction = pCallback;
	}

	bool NCommandWalker::parseCommands()
	{
		bool bValid = false;	// First time use indicates whether any command was parsed

		while(!bValid && m_arguments.isValid())
		{
			const char* szArg = m_arguments.getActualArgument();

			bool bFound = false;
			for(size_t i = 0; !bFound && !bValid && i < m_vCommands.size(); ++i)
			{
				// Checking if string contains another string at the begin
				if(NStringAtBegin(szArg, m_vCommands[i].szCommand))
				{
					bValid = m_vCommands[i].pCallback(m_arguments);
					i = m_vCommands.size();
					bFound = true;
				}
			}

			// Default action
			if(!bFound && !bValid && m_pDefaultAction != null)
			{
				bValid = m_pDefaultAction(m_arguments);
			}

			m_arguments.nextArgument();
		}

		return bValid;
	}

	void NCommandWalker::printCommands()
	{
		printf("Command list:\n");
		for(size_t i = 0; i < m_vCommands.size(); ++i)
		{
			printf("'%s'\t%s\n", m_vCommands[i].szCommand, m_vCommands[i].szHelp);
		}
		printf("\n");
	}
}
}
