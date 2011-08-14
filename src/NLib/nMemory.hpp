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

	template<NSize_t uChunkSize>
	struct ChunkTemplate
	{
		ChunkTemplate<uChunkSize>* pNext;
		NUint8	uPool[uChunkSize - sizeof(ChunkTemplate<uChunkSize>*)];
	};

	typedef ChunkTemplate<8> MemoryChunk;

	class NMemory
	{
	public:
		NRESULT initMemory(NSize_t uReservationSize = 0);

		void* allocate(NSize_t uAllocationSize);
		//void* allocate(NSize_t uAllocationSize, NSize_t uAlignment);
		void release(void* pMemory);

		NSize_t getChunksCount() const				{ return m_uNumChunks; }
		NSize_t getAllocatedChunksCount() const		{ return m_uNumUsedChunks; }

		bool outOfMemory()	{ return m_bOutOfMemory; }

	private:
		NMemory();
		~NMemory();

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