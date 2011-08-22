#pragma once

namespace NLib {
namespace Memory
{
	class NMemory;

	template<NMemory& memory>
	class NMemoryGuard
	{
	public:
		NMemoryGuard(void* pMemory)			: m_pMemory(pMemory)			{  }
		NMemoryGuard(NMemoryGuard& guard)	: m_pMemory(guard.m_pMemory)	{ guard.clear(); }
		~NMemoryGuard()						{ if(m_pMemory) { memory.release(m_pMemory); } }

		void clear()						{ m_pMemory = 0; }

	private:
		void* m_pMemory;
	};
}
}

#ifdef NGUARD_FLAG
	#define NM_GUARD_GLOBAL(ptr)		NMemoryGuard<NMemoryGlobal> (n_guard_##ptr)((ptr));
	#define NM_GUARD(ptr, memory)		NMemoryGuard<(memory)> (n_guard_##ptr)(ptr);
	#define NM_GUARD_CLEAR(ptr)			(n_guard_##ptr).clear();
#else
	#define NM_GUARD_GLOBAL(ptr)
	#define NM_GUARD(ptr, memory)
	#define NM_GUARD_CLEAR(ptr)
#endif

// Check memory
#ifdef NCHECK_MEMORY_FLAG
	#define NCM_RV_GLOBAL				if(NLib::Memory::NMemoryGlobal.OutOfMemory())	return NLib::NRV_OUT_OF_MEMORY;
	#define NCM_RV(memory)				if((memory).outOfMemory())						return NLib::NRV_OUT_OF_MEMORY;
	#define NCM_V_GLOBAL				if(NLib::Memory::NMemoryGlobal.OutOfMemory())	return;
	#define NCM_V(memory)				if((memory).outOfMemory())						return;
#else
	#define NCM_RV_GLOBAL
	#define NCM_RV(memory)
	#define NCM_V_GLOBAL
	#define NCM_V(memory)
#endif