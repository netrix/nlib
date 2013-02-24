#pragma once
#include <NLib/Base/nBase.hpp>
#include <NLib/Base/nErrors.hpp>

namespace NLib {
namespace Memory
{
	struct ChunkHead
	{
		ChunkHead*	pNext;
		NSize_t		uNumChunks;
	};

	struct MemoryChunk
	{
		MemoryChunk*	pNext;
		NSize_t			uContinuousCount;
	};

	class NMemory
	{
	public:
		NMemory();
		~NMemory();

		NRESULT initMemory(NSize_t uReservationSize = 16);
		void	releaseMemory();

		void*	allocate(NSize_t uAllocationSize);
		void*	allocate(NSize_t uAllocationSize, NSize_t uAlignment);
		void	release(void* pMemory);

		NSize_t getChunksCount() const				{ return m_uNumChunks; }
		NSize_t getAllocatedChunksCount() const		{ return m_uNumUsedChunks; }

		bool	outOfMemory()	   { return m_bOutOfMemory; }
      bool  isInitializated() { return m_pHeads == null; }

	private:
		MemoryChunk*	allocateChunks(NSize_t uChunksCount);						// Must be complemented to chunks
		MemoryChunk* 	appendChunks(MemoryChunk* pChunks, NSize_t uNumChunks);		// Returns pointer to object of appended Chunk
		void			releaseChunks();
		void			releaseUnusedChunks();

	private:
		NSize_t m_uNumChunks;
		NSize_t m_uNumUsedChunks;

		ChunkHead*		m_pHeads;
		MemoryChunk*	m_pFreeChunks;

		bool	m_bOutOfMemory;

   public:
		static NMemory m_instance;

	public:
      static NMemory& GetGlobalInstance();
		static NRESULT	InitMemory(NSize_t uReservationSize = 16)				   { return m_instance.initMemory(uReservationSize); }
		static void		ReleaseMemory()											      { GetGlobalInstance().releaseMemory(); }
		static void*	Allocate(NSize_t uAllocationSize)						   { return GetGlobalInstance().allocate(uAllocationSize); }
		static void*	Allocate(NSize_t uAllocationSize, NSize_t uAlignment)	{ return GetGlobalInstance().allocate(uAllocationSize, uAlignment); }
		static void		Release(void* pMemory)									      { GetGlobalInstance().release(pMemory); }
		static NSize_t	GetChunksCount()										         { return GetGlobalInstance().getChunksCount(); }
		static NSize_t	GetAllocatedChunksCount()								      { return GetGlobalInstance().getAllocatedChunksCount(); }
		static bool		OutOfMemory()											         { return GetGlobalInstance().outOfMemory(); }
	};
}
}

//inline void* operator new(size_t uSize)
//{
//	return NLib::Memory::NMemory::Allocate(uSize);
//}
//
//inline void* operator new(size_t uSize, NLib::NSize_t uAlignment)
//{
//	return NLib::Memory::NMemory::Allocate(uSize, uAlignment);
//}
//
//inline void operator delete(void* pMemory)
//{
//	NLib::Memory::NMemory::Release(pMemory);
//}

inline void* operator new(size_t uSize, NLib::Memory::NMemory& memory)
{
	return memory.allocate(uSize);
}

inline void* operator new(size_t uSize, NLib::Memory::NMemory& memory, NLib::NSize_t uAlignment)
{
	return memory.allocate(uSize, uAlignment);
}

inline void* operator new[](size_t uSize, NLib::Memory::NMemory& memory)
{
	return memory.allocate(uSize);
}

inline void* operator new[](size_t uSize, NLib::Memory::NMemory& memory, NLib::NSize_t uAlignment)
{
	return memory.allocate(uSize, uAlignment);
}

template<typename Type>
void ndelete(NLib::Memory::NMemory& memory, Type* pObject)
{
	pObject->~Type();
	memory.release(pObject);
}

#define NMemoryInit				NMemory::InitMemory
#define NMemoryAllocate			NMemory::Allocate
#define NMemoryRelease			NMemory::Release
#define NMemoryGlobal			NMemory::m_instance

#include "nMemoryGuard.hpp"
