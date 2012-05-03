/*********************************************************************

Name:		NLib
Author:		Kamil Szatkowski "Netrix" (C)
Website:	http://www.netrix.org.pl/
License:	GNU GPL

*********************************************************************/
#pragma once
#include <NLib/Containers/nVector.hpp>

namespace NLib {
namespace CmdLineParser
{
	class NArguments
	{
	public:
		void		create(int argc, const char* argv[]);	// Out of memory
		void		release()								{ if(m_vArguments) { m_vArguments.release(); } }

		const char* getLaunchPath() const					{ return m_pLaunchPath;	}
		const char* getActualArgument() const				{ return m_uActualProcessed < m_vArguments.size() ? m_vArguments[m_uActualProcessed] : null; }

		bool		nextArgument()							{ return ++m_uActualProcessed < m_vArguments.size(); }
		void		reset()									{ m_uActualProcessed = 0; }

		bool		isValid()								{ return m_uActualProcessed < m_vArguments.size(); }

	private:
		Containers::NVector<const char*>	m_vArguments;
		const char*							m_pLaunchPath;
		NSize_t								m_uActualProcessed;
	};
}
}