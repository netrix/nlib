#pragma once
#include "nBase.hpp"
#include "nErrors.hpp"

/*	 32-bit implementation
 *	 128-bytes chunks aligned memory
 *
 */
namespace NIne
{
	struct ChunkHead
	{
		ChunkHead* pNext;
		NIne::NSize_t uNumChunks;
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

		NRESULT initMemory(NSize_t uReservationSize = 0);
		void	releaseMemory();

		void*	allocate(NSize_t uAllocationSize);
		void*	allocate(NSize_t uAllocationSize, NSize_t uAlignment);
		void	release(void* pMemory);

		NSize_t getChunksCount() const				{ return m_uNumChunks; }
		NSize_t getAllocatedChunksCount() const		{ return m_uNumUsedChunks; }

		bool	outOfMemory()	{ return m_bOutOfMemory; }

	private:
		MemoryChunk*	allocateChunks(NSize_t uAllocSize);		// Must be complemented to chunks
		void			appendChunks(MemoryChunk* pChunks, NSize_t uNumChunks);
		void			releaseChunks();

	private:
		NSize_t m_uNumChunks;
		NSize_t m_uNumUsedChunks;

		ChunkHead*		m_pHeads;
		MemoryChunk*	m_pFreeChunks;

		bool m_bOutOfMemory;

	public:
		static NMemory m_instance;
	};
}

#define NMemoryInit				NMemory::m_instance.initMemory
#define NMemoryReleaseAll		NMemory::m_instance.releaseMemory
#define NMemoryAllocate			NMemory::m_instance.allocate
#define NMemoryRelease			NMemory::m_instance.release

#define NMemoryGetChunksCount			NMemory::m_instance.getChunksCount
#define NMemoryGetAllocatedChunksCount	NMemory::m_instance.getAllocatedChunksCount

#define NMemoryOutOfMemory	NMemory::m_instance.outOfMemory