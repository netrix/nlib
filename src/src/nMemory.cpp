#include "../NLib/Memory/nMemory.hpp"
#include "../NLib/nLogger.hpp"
#include "../NLib/nAssert.hpp"

namespace
{
	inline NLib::NSize_t ComplementTo8(NLib::NSize_t uValue)
	{
		return (uValue & 0xFFFFFFF8u) == uValue ? uValue : (uValue & 0xFFFFFFF8u) + 8;
	}

	// http://msinilo.pl/blog/?p=702
	template<size_t V>
	struct Log2
	{
		enum
		{
			Value = Log2<V / 2>::Value + 1
		};
		typedef char V_MustBePowerOfTwo[((V & (V - 1)) == 0 ? 1 : -1)];
	};
	template<> struct Log2<1> { enum { Value = 0 }; };
}

namespace NLib {
namespace Memory
{
	NMemory NMemory::m_instance;

	/***********************************************************************/
	NMemory::NMemory()	: m_pHeads(null)
	{
	}
	/***********************************************************************/
	NMemory::~NMemory()
	{
		releaseChunks();
	}
	/***********************************************************************/
	NRESULT NMemory::initMemory(NSize_t uReservationSize)
	{
		NAssert(uReservationSize > 0, "Invalid parameter");

		m_bOutOfMemory = false;
		m_uNumUsedChunks = 0;
		m_uNumChunks = 0;

		uReservationSize = ComplementTo8(uReservationSize);

		NLogMessage("Initializing memory");

		m_pFreeChunks = allocateChunks(uReservationSize);
		if(m_pFreeChunks == null)	{ return NRV_OUT_OF_MEMORY;	}

		return NRV_SUCCESS;
	}
	/***********************************************************************/
	void NMemory::releaseMemory()
	{
		releaseChunks();
		m_pHeads = null;
	}
	/***********************************************************************/
	MemoryChunk* NMemory::allocateChunks(NSize_t uAllocSize)
	{
		// Allocating additional space for Head chunk
		uAllocSize += sizeof(MemoryChunk);

		NLogMessage("Allocating memory, size: %u bytes... ", uAllocSize);

		// Allocating memory
		void* pMemory = malloc(uAllocSize);
		if(pMemory == null)
		{
			m_bOutOfMemory = true;
			NLogMessage("Failed\n");
			return null;
		}

		NLogMessage("OK\n");

		NSize_t uAllocedChunks = uAllocSize / sizeof(MemoryChunk);

		// Setting free pointers
		MemoryChunk* pFreeChunks = (MemoryChunk*)pMemory;

		// Collecting chunks into list
		MemoryChunk* pChunks = pFreeChunks;
		for(NSize_t i = 0; i < uAllocedChunks; ++i)
		{
			pChunks->pNext = pChunks + 1;
			++pChunks;
		}

		(pChunks - 1)->pNext = null;

		// Setting up head
		ChunkHead* pHead = (ChunkHead*)pFreeChunks;
		pFreeChunks = pFreeChunks->pNext;
		pHead->pNext = null;
		pHead->uNumChunks = m_uNumChunks;
		++m_uNumUsedChunks;

		// Adding Head to memory list
		if(m_pHeads == null)	{ m_pHeads = pHead; }// First use case
		else
		{
			pHead->pNext = m_pHeads;
			m_pHeads = pHead;
		}

		m_uNumChunks += uAllocedChunks;

		// Setting continuity information
		pFreeChunks->uContinuousCount = uAllocedChunks - 2;

		return pFreeChunks;
	}
	/***********************************************************************/
	MemoryChunk* NMemory::appendChunks(MemoryChunk* pChunks, NSize_t uNumChunks)
	{
		if(m_pFreeChunks == null)
		{
			m_pFreeChunks = pChunks;
			return null;
		}
		else if(pChunks < m_pFreeChunks)
		{
			(pChunks + uNumChunks - 1)->pNext = m_pFreeChunks;
			m_pFreeChunks = pChunks;
			return null;
		}
		else
		{
			MemoryChunk* pFreeChunks = m_pFreeChunks;
			while(pFreeChunks->pNext != null && pFreeChunks->pNext < pChunks)
			{
				pFreeChunks = pFreeChunks->pNext;
			}

			(pChunks + uNumChunks - 1)->pNext = pFreeChunks->pNext;
			pFreeChunks->pNext = pChunks;
			pFreeChunks->uContinuousCount = 0;
			return pFreeChunks;
		}
	}
	/***********************************************************************/
	void NMemory::releaseChunks()
	{
		NLogMessage("Releasing memory");

		while(m_pHeads != null)
		{
			ChunkHead* pHead = m_pHeads;
			m_pHeads = m_pHeads->pNext;
			free(pHead);
		}
	}
	/***********************************************************************/
	void* NMemory::allocate(NSize_t uAllocationSize)
	{
		NAssert(uAllocationSize > 0, "Invalid parameter");

		NSize_t  uRealSize = uAllocationSize + sizeof(NSize_t);
		NSize_t* pSizePointer = null;

		if(uRealSize <= sizeof(MemoryChunk))
		{
			if(m_pFreeChunks == null)
			{
				m_pFreeChunks = allocateChunks(m_uNumChunks * sizeof(MemoryChunk));
			}

			// Updating continuous counter
			if(m_pFreeChunks->uContinuousCount > 0)	{ m_pFreeChunks->pNext->uContinuousCount = m_pFreeChunks->uContinuousCount - 1; }

			pSizePointer = (NSize_t*)m_pFreeChunks;
			m_pFreeChunks = m_pFreeChunks->pNext;
			*pSizePointer = 1;
			m_uNumUsedChunks++;
		}
		else
		{
			// Determining chunks count
			NSize_t uNumChunks = ComplementTo8(uRealSize) / sizeof(MemoryChunk);

			// Looking for enough continuous memory
			MemoryChunk* pFirst = m_pFreeChunks;
			MemoryChunk* pPrevious = null;

			while(pFirst != null && pFirst->uContinuousCount < uNumChunks)
			{
				pPrevious = pFirst;
				pFirst = (pFirst + pFirst->uContinuousCount)->pNext;
			}

			// Found or not
			if(pFirst == null)
			{
				NSize_t uReservationSize = ComplementTo8(max(uRealSize, m_uNumChunks * sizeof(MemoryChunk)));
				pFirst = allocateChunks(uReservationSize);

				if(pFirst == null)	{ return null; }

				pPrevious = appendChunks(pFirst, uReservationSize / sizeof(MemoryChunk) - uNumChunks);
			}

			// Updating continuous counter
			if(pFirst->uContinuousCount > uNumChunks - 1)	{ (pFirst + uNumChunks)->uContinuousCount = pFirst->uContinuousCount - uNumChunks; }

			pSizePointer = (NSize_t*)pFirst;

			// Updating continuity of list
			if(pPrevious == null)	{ m_pFreeChunks = pFirst + uNumChunks; }
			else					{ (pPrevious + pPrevious->uContinuousCount)->pNext = pFirst + uNumChunks; }

			*pSizePointer = uNumChunks;
			m_uNumUsedChunks += uNumChunks;
		}

		return pSizePointer != null ? pSizePointer + 1 : null;
	}
	/***********************************************************************/
	void* NMemory::allocate(NSize_t uAllocationSize, NSize_t uAlignment)
	{
		NAssert(uAllocationSize > 0, "Invalid parameter");
		NAssert((uAlignment & (uAlignment - 1)) == 0, "uAlignment must be power of 2");

		NSize_t uRealSize = uAllocationSize + sizeof(NSize_t);
		NSize_t uAlignmentSize = uRealSize + uAlignment;
		NSize_t* pSizePointer = null;

		// Determining chunks count
		NSize_t uNumChunks = ComplementTo8(uAlignmentSize) / sizeof(MemoryChunk);

		// Looking for enough continuous memory
		MemoryChunk* pFirst = m_pFreeChunks;
		MemoryChunk* pPrevious = null;

		while(pFirst != null && pFirst->uContinuousCount < uNumChunks)
		{
			pPrevious = pFirst;
			pFirst = (pFirst + pFirst->uContinuousCount)->pNext;
		}

		// Not found, adding additional space
		if(pFirst == null)
		{
			NSize_t uReservationSize = ComplementTo8(max(uAlignmentSize, m_uNumChunks * sizeof(MemoryChunk)));
			pFirst = allocateChunks(uReservationSize);

			if(pFirst == null)	{ return null; }

			pPrevious = appendChunks(pFirst, uReservationSize / sizeof(MemoryChunk));
		}

		// Updating continuous counter
		if(pFirst->uContinuousCount > uNumChunks - 1)	{ (pFirst + uNumChunks)->uContinuousCount = pFirst->uContinuousCount - uNumChunks; }

		// Calculating offset
		NSize_t uOffset	= (NSize_t)pFirst + sizeof(NSize_t);
		NSize_t uAlignedOffset = (uOffset / uAlignment) * uAlignment;
		uAlignedOffset = uAlignedOffset < uOffset ? uAlignedOffset + uAlignment : uAlignedOffset;

		// If offset takes more block, there's no need to waste it
		NSize_t uOffsetBlocks = (uAlignedOffset - uOffset) / sizeof(MemoryChunk);
		if(uOffsetBlocks > 0)
		{
			// Updating continuous counter
			pFirst->uContinuousCount = uOffsetBlocks - 1;
			pPrevious = pFirst + uOffsetBlocks - 1;
			pPrevious->uContinuousCount = 0;
			pFirst = pFirst + uOffsetBlocks;
			uNumChunks -= uOffsetBlocks;
		}

		// Updating continuity of list
		if(pPrevious == null)	{ m_pFreeChunks = pFirst + uNumChunks; }
		else					{ (pPrevious + pPrevious->uContinuousCount)->pNext = pFirst + uNumChunks; }

		pSizePointer = (NSize_t*)uAlignedOffset - 1;
		*pSizePointer = uNumChunks - uOffsetBlocks;
		m_uNumUsedChunks += *pSizePointer;

		// Saving information about offset at the beginning of *pSizePointer
		*pSizePointer |= ((NSize_t)pSizePointer - (NSize_t)pFirst) << (sizeof(NSize_t) * 8 - Log2<sizeof(MemoryChunk)>::Value);

		return pSizePointer != null ? pSizePointer + 1 : null;
	}
	/***********************************************************************/
	void NMemory::release(void* pMemory)
	{
		// Getting size value
		NSize_t* pOffset = (NSize_t*)pMemory - 1;
		NSize_t uSize = *pOffset;

		pOffset = (NSize_t*)((NSize_t)pOffset - (uSize >> (sizeof(NSize_t) * 8 - Log2<sizeof(MemoryChunk)>::Value)));
		uSize &= (1 << (sizeof(NSize_t) * 8 - sizeof(MemoryChunk))) - 1;

		// Fixing chunks
		MemoryChunk* pFirst = (MemoryChunk*)pOffset;
		MemoryChunk* pChunk = pFirst;

		for(NSize_t u = 0; u < uSize; ++u)
		{
			pChunk->pNext = pChunk + 1;		// Can eliminate this due to the continuity of memory
			pChunk++;
		}

		// Searching for accurate place
		if(m_pFreeChunks == null)
		{
			m_pFreeChunks = pFirst;
			pFirst->uContinuousCount = uSize - 1;
			(pChunk - 1)->pNext = null;
		}
		else
		{
			MemoryChunk* pFreeChunks = m_pFreeChunks;

			while(pFreeChunks->pNext != null && pFreeChunks->pNext < pFirst)
			{
				pFreeChunks = pFreeChunks->pNext;
			}

			(pChunk - 1)->pNext = pFreeChunks->pNext;
			pFreeChunks->pNext = pFirst;

			if(pChunk == pFreeChunks->pNext)	{ pFirst->uContinuousCount = uSize + pChunk->uContinuousCount; } // pChunk == pFreeChunks
			else								{ pFirst->uContinuousCount = uSize - 1; }
		}

		m_uNumUsedChunks -= uSize;
	}
}
}