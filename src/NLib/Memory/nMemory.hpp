#pragma once
#include "nMemoryGuard.hpp"
#include "../nBase.hpp"
#include "../nErrors.hpp"

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

		NRESULT initMemory(NSize_t uReservationSize = 8);
		void	releaseMemory();

		void*	allocate(NSize_t uAllocationSize);
		void*	allocate(NSize_t uAllocationSize, NSize_t uAlignment);
		void	release(void* pMemory);

		NSize_t getChunksCount() const				{ return m_uNumChunks; }
		NSize_t getAllocatedChunksCount() const		{ return m_uNumUsedChunks; }

		bool	outOfMemory()	{ return m_bOutOfMemory; }

	private:
		MemoryChunk*	allocateChunks(NSize_t uAllocSize);							// Must be complemented to chunks
		MemoryChunk* 	appendChunks(MemoryChunk* pChunks, NSize_t uNumChunks);		// Returns pointer to object of appended Chunk
		void			releaseChunks();

	private:
		NSize_t m_uNumChunks;
		NSize_t m_uNumUsedChunks;

		ChunkHead*		m_pHeads;
		MemoryChunk*	m_pFreeChunks;

		bool	m_bOutOfMemory;

	public:
		static NMemory m_instance;

	public:
		static NRESULT	InitMemory(NSize_t uReservationSize = 8)				{ return m_instance.initMemory(uReservationSize); }
		static void		ReleaseMemory()											{ m_instance.releaseMemory(); }
		static void*	Allocate(NSize_t uAllocationSize)						{ return m_instance.allocate(uAllocationSize); }
		static void*	Allocate(NSize_t uAllocationSize, NSize_t uAlignment)	{ return m_instance.allocate(uAllocationSize, uAlignment); }
		static void		Release(void* pMemory)									{ m_instance.release(pMemory); }
		static NSize_t	GetChunksCount()										{ return m_instance.getChunksCount(); }
		static NSize_t	GetAllocatedChunksCount()								{ return m_instance.getAllocatedChunksCount(); }
		static bool		OutOfMemory()											{ return m_instance.outOfMemory(); }
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