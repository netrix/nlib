#pragma once

namespace NLib {
namespace Containers
{
	template<typename Type>
	class NContainerGuard
	{
	public:
		NContainerGuard(Type& container)		: m_pContainer(&container)				{  }
		NContainerGuard(NContainerGuard& guard)	: m_pContainer(guard.m_pContainer)	{ guard.clear(); }
		~NContainerGuard()						{ if(m_pContainer) { m_pContainer->release(); } }

		void clear()							{ m_pContainer = 0; }

	private:
		Type* m_pContainer;
	};
}
}

#ifdef NGUARD_FLAG
	#define NC_GUARD(type, container)		NContainerGuard<type> (n_guard_##container)(container);
	#define NC_GUARD_CLEAR(container)		(n_guard_##container).clear();
#else
	#define NC_GUARD(type, container)
	#define NC_GUARD_CLEAR(container)
#endif

#ifdef NCHECK_MEMORY_FLAG
	#define NCC_RESERVE_V(container, memory)	if((container).full()) { (container).reserve(); NCM_V(memory); }
	#define NCC_RESERVE_RV(container, memory)	if((container).full()) { (container).reserve(); NCM_RV(memory); }
	#define NCC_RESERVE_V_GLOBAL(container)		NCC_RESERVE_V(container, NLib::Memory::NMemoryGlobal);
	#define NCC_RESERVE_RV_GLOBAL(container)	NCC_RESERVE_RV(container, NLib::Memory::NMemoryGlobal);
#else
	#define NCC_RESERVE_V(container, memory)
	#define NCC_RESERVE_RV(container, memory)
	#define NCC_RESERVE_V_GLOBAL(container)
	#define NCC_RESERVE_RV_GLOBAL(container)
#endif