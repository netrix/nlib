/*********************************************************************

Name:		Raytracer
Author:		Kamil Szatkowski "Netrix" (C)
Website:	http://www.netrix.org.pl/

*********************************************************************/
#pragma once
#include "nArguments.hpp"

namespace NLib {
namespace CmdLineParser
{
	typedef bool (*NCommandCallback)(NArguments& pArguments);

	class NCommandWalker
	{
		struct Command
		{
			const char* szCommand;
			const char* szHelp;
			NCommandCallback pCallback;
		};

	public:
		void	create(int argc, const char* argv[]);
		void	release();

		void	addCommand(const char* szCommand, const char* szHelp, NCommandCallback pCallback);
		void	setDefault(NCommandCallback pCallback);

		void	printCommands();
		bool	parseCommands();

	private:
		NArguments						m_arguments;
		Containers::NVector<Command>	m_vCommands;

		NCommandCallback				m_pDefaultAction;
	};
}
}