#include "../nMemory.hpp"
#include "../nLogger.hpp"
#include "../nAssert.hpp"

namespace
{
	inline NIne::NSize_t ComplementTo8(NIne::NSize_t uValue)
	{
		return (uValue & 0xFFFFFFF8u) == uValue ? uValue : (uValue & 0xFFFFFFF8u) + 8;
	}
}

namespace NIne
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

		return pFreeChunks;
	}
	/***********************************************************************/
	void NMemory::appendChunks(MemoryChunk* pChunks, NSize_t uNumChunks)
	{
		if(m_pFreeChunks == null)
		{
			m_pFreeChunks = pChunks;
		}
		else if(pChunks < m_pFreeChunks)
		{
			(pChunks + uNumChunks - 1)->pNext = m_pFreeChunks;
			m_pFreeChunks = pChunks;
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

			pSizePointer = (NSize_t*)m_pFreeChunks;
			m_pFreeChunks = m_pFreeChunks->pNext;
			*pSizePointer = 1;
			m_uNumUsedChunks++;
		}
		else
		{
			// Determining chunks count
			NSize_t uNumChunks = ComplementTo8(uRealSize) / sizeof(MemoryChunk);

			// Looking for continuous memory
			NSize_t uContChunks = 1;
			MemoryChunk* pFirst = m_pFreeChunks;
			MemoryChunk* pChunk = pFirst->pNext;

			while(pChunk != null && uContChunks != uNumChunks)
			{
				if((NSize_t)(pChunk - pFirst) == uContChunks)	{ uContChunks++; }
				else
				{
					pFirst = pChunk;
					uContChunks = 1;
				}

				pChunk = pChunk->pNext;
			}

			// Found or not
			if(uContChunks != uNumChunks)
			{
				NSize_t uReservationSize = ComplementTo8(max(uRealSize, m_uNumChunks * sizeof(MemoryChunk)));

				MemoryChunk* pNewChunks = allocateChunks(uReservationSize);

				// Reserving first chunks
				pSizePointer = (NSize_t*)pNewChunks;
				*pSizePointer = uNumChunks;
				m_uNumUsedChunks += uNumChunks;
				pNewChunks = pNewChunks + uNumChunks;

				appendChunks(pNewChunks, uReservationSize / sizeof(MemoryChunk) - uNumChunks);
			}
			else
			{
				pSizePointer = (NSize_t*)pFirst;
				*pSizePointer = uNumChunks;
				m_uNumUsedChunks += uNumChunks;
				m_pFreeChunks = pChunk;
			}
		}

		return pSizePointer != null ? pSizePointer + 1 : null;
	}
	/***********************************************************************/
	void* NMemory::allocate(NSize_t uAllocationSize, NSize_t uAlignment)
	{
		NAssert(uAllocationSize > 0, "Invalid parameter");
		NAssert((uAlignment & (uAlignment - 1)) == 0, "uAlignment must be power of 2");

		NSize_t uRealSize = uAllocationSize + sizeof(NSize_t) + uAlignment;	// This approach uses additional memory even if it is no necessary
		NSize_t* pSizePointer = null;

		if(uRealSize <= sizeof(MemoryChunk))
		{
			if(m_pFreeChunks == null)
			{
				m_pFreeChunks = allocateChunks(m_uNumChunks * sizeof(MemoryChunk));
			}

			pSizePointer = (NSize_t*)m_pFreeChunks;
			m_pFreeChunks = m_pFreeChunks->pNext;
			*pSizePointer = 1;
			m_uNumUsedChunks++;
		}
		else
		{
			// Determining chunks count
			NSize_t uNumChunks = ComplementTo8(uRealSize) / sizeof(MemoryChunk);

			// Looking for continuous memory
			NSize_t uContChunks = 1;
			MemoryChunk* pFirst = m_pFreeChunks;
			MemoryChunk* pChunk = pFirst->pNext;

			while(pChunk != null && uContChunks != uNumChunks)
			{
				if((NSize_t)(pChunk - pFirst) == uContChunks)	{ uContChunks++; }
				else
				{
					pFirst = pChunk;
					uContChunks = 1;
				}

				pChunk = pChunk->pNext;
			}

			// Found or not
			if(uContChunks != uNumChunks)
			{
				NSize_t uReservationSize = ComplementTo8(max(uRealSize, m_uNumChunks * sizeof(MemoryChunk)));

				MemoryChunk* pNewChunks = allocateChunks(uReservationSize);

				// Reserving first chunks
				pSizePointer = (NSize_t*)pNewChunks;
				*pSizePointer = uNumChunks;
				m_uNumUsedChunks += uNumChunks;
				pNewChunks = pNewChunks + uNumChunks;

				appendChunks(pNewChunks, uReservationSize / sizeof(MemoryChunk) - uNumChunks);
			}
			else
			{
				pSizePointer = (NSize_t*)pFirst;
				*pSizePointer = uNumChunks;
				m_uNumUsedChunks += uNumChunks;
				m_pFreeChunks = pChunk;
			}
		}

		return pSizePointer != null ? pSizePointer + 1 : null;
	}
	/***********************************************************************/
	void NMemory::release(void* pMemory)
	{
		// Fixing chunks
		MemoryChunk* pFirst = (MemoryChunk*)((NSize_t*)pMemory - 1);
		MemoryChunk* pChunk = pFirst;

		NSize_t uSize = *(NSize_t*)pFirst;
		for(NSize_t u = 0; u < uSize; ++u)
		{
			pChunk->pNext = pChunk + 1;
			pChunk++;
		}

		// Searching for accurate place
		if(m_pFreeChunks == null)
		{
			m_pFreeChunks = pFirst;
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
		}

		m_uNumUsedChunks -= uSize;
	}
}