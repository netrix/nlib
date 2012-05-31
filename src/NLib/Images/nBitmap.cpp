#include "nBitmap.hpp"
#include <NLib/Base/nAssert.hpp>
#include <NLib/Base/nLogger.hpp>
#include <stdio.h>
#include <string.h>

#pragma warning(disable: 4996)	// fopen deprecated on windows

namespace
{
	struct NRaiiFile
	{
		NRaiiFile(const char* szFile, const char* szFlags)
		{
			pFile = fopen(szFile, szFlags);
		}

		~NRaiiFile()
		{
			if(pFile != null) { fclose(pFile); }
		}

		FILE* pFile;
	};

	NLib::NUint32 g_masks[] = { 0x000000FF, 0x0000FFFF, 0x00FFFFFF };
}

namespace NLib {
namespace Images
{
	NBitmap::NBitmap()
		: m_uWidth(0)
		, m_uHeight(0)
		, m_uBitsPerPixel(0)
	{
	}
	/********************************************************/
	NBitmap::~NBitmap()
	{
		release();
	}
	/********************************************************/
	void NBitmap::create(NUint32 uWidth, NUint32 uHeight, NUint32 uBitsPerPixel)
	{
		NAssert(m_aBitmap == false, "release bitmap first");

		m_aBitmap.create(uWidth * uHeight * uBitsPerPixel);	NCM_V_GLOBAL;
		m_uHeight = uHeight;
		m_uWidth = uWidth;
		m_uBitsPerPixel = uBitsPerPixel;
	}
	/********************************************************/
	void NBitmap::release()
	{
		m_aBitmap.release();
		m_uHeight = 0;
		m_uWidth = 0;
		m_uBitsPerPixel = 0;
	}
	/********************************************************/
	bool NBitmap::loadFromFile(const char* szFile)
	{
		NAssert(m_aBitmap == false, "release bitmap first");

		NRaiiFile file(szFile, "rb");
		FILE* pFile = file.pFile;
		if(pFile == null)
		{
			NLogHead();
			NLogMessage("Failed to open file: %s", szFile);
			return true;
		}

		BitmapMagic bmpMagic;
		BitmapHeader bmpHeader;
		BitmapInfoHeader bmpInfoHeader;

		if(!fread(&bmpMagic, sizeof(bmpMagic), 1, pFile))
		{
			NLogError("Failed to read from file");
			return true;
		}
		if(!fread(&bmpHeader, sizeof(bmpHeader), 1, pFile))
		{
			NLogError("Failed to read from file");
			return true;
		}
		if(!fread(&bmpInfoHeader, sizeof(bmpInfoHeader), 1, pFile))
		{
			NLogError("Failed to read from file");
			return true;
		}

		// Validation of simple bitmap
		if(bmpInfoHeader.uHeaderSize != sizeof(bmpInfoHeader)
		|| bmpInfoHeader.uNPlanes != 1
		|| bmpInfoHeader.uBitsPerPixel >= 8)
		{
			NLogError("Invalid bitmap");
			return true;
		}

		// Loading data
		NUint32 uRowDataSize = bmpInfoHeader.uWidth * m_uBitsPerPixel / 8;
		NUint32 uComplets = (uRowDataSize & 0x3) != 0 ? (((uRowDataSize >> 2) + 1) << 2) - uRowDataSize : 0;	// Completion to get support 4 bytes ending lines
		m_aBitmap.create(uRowDataSize * bmpInfoHeader.uHeight);
		fseek(pFile, bmpHeader.uPixelArrayOffset, SEEK_SET);

		NUint8* pTemp = m_aBitmap.data() + (bmpInfoHeader.uHeight - 1) * uRowDataSize;
		for(NInt32 iRow = 0; iRow < bmpInfoHeader.uHeight; ++iRow)
		{
			if(!fread(pTemp, uRowDataSize, 1, pFile))
			{
				m_aBitmap.release();
				NLogError("Failed to read from file");
				return true;
			}

			fseek(pFile, uComplets, SEEK_CUR);
			pTemp -= uRowDataSize;
		}

		m_uWidth = bmpInfoHeader.uWidth;
		m_uHeight = bmpInfoHeader.uHeight;
		m_uBitsPerPixel = bmpInfoHeader.uBitsPerPixel;

		return false;
	}
	/********************************************************/
	bool NBitmap::saveToFile(const char* szFile) const
	{
		NAssert(m_aBitmap == true, "create bitmap first");

		NRaiiFile file(szFile, "wb");
		FILE* pFile = file.pFile;
		if(pFile == null)
		{
			NLogHead();
			NLogMessage("Failed to open file: %s", szFile);
			return true;
		}

		NSize_t uColorDataOffset = sizeof(BitmapMagic) + sizeof(BitmapHeader) + sizeof(BitmapInfoHeader);
		NUint32 uRowDataSize = m_uWidth * m_uBitsPerPixel / 8;
		NUint32 uComplets = (uRowDataSize & 0x3) != 0 ? (((uRowDataSize >> 2) + 1) << 2) - uRowDataSize : 0;
		NSize_t uColorDataSize = (uComplets + uRowDataSize) * m_uHeight;
		BitmapMagic bmpMagic = { 'B', 'M' };
		BitmapHeader bmpHeader =
		{
			(NUint32)(uColorDataOffset + uColorDataSize),
			{ 0, 0 },
			uColorDataOffset
		};
		BitmapInfoHeader bmpInfoHeader =
		{
			sizeof(BitmapInfoHeader),
			m_uWidth,
			m_uHeight,
			1,
			(NUint16)m_uBitsPerPixel,
			0,
			uColorDataSize,
			0,
			0,
			0,
			0
		};

		if(!fwrite(&bmpMagic, sizeof(bmpMagic), 1, pFile))
		{
			NLogError("Failed to write to file");
			return true;
		}
		if(!fwrite(&bmpHeader, sizeof(bmpHeader), 1, pFile))
		{
			NLogError("Failed to write to file");
			return true;
		}
		if(!fwrite(&bmpInfoHeader, sizeof(bmpInfoHeader), 1, pFile))
		{
			NLogError("Failed to write to file");
			return true;
		}

		// Loading data
		const NUint8* pTemp = m_aBitmap.data() + (m_uHeight - 1) * uRowDataSize;
		for(NUint32 iRow = 0; iRow < m_uHeight; ++iRow)
		{
			if(!fwrite(pTemp, uRowDataSize, 1, pFile))
			{
				NLogError("Failed to write to file");
				return true;
			}
			if(uComplets != 0 && !fwrite(&iRow, uComplets, 1, pFile))
			{
				NLogError("Failed to write to file");
				return true;
			}
			pTemp -= uRowDataSize;
		}

		return false;
	}
	/********************************************************/
	void NBitmap::setPixel(NUint32 x, NUint32 y, NUint32 color)
	{
		NAssert(x < m_uWidth, "");
		NAssert(y < m_uHeight, "");

		NSize_t uOffset = (y * m_uWidth + x) * 3;
		memcpy(m_aBitmap.data() + uOffset, &color, m_uBitsPerPixel / 8);
	}
	/********************************************************/
	NUint32 NBitmap::getPixel(NUint32 x, NUint32 y) const
	{
		NSize_t uOffset = (y * m_uWidth + x) * 3;
		return *((NUint32*)(m_aBitmap.data() + uOffset)) & g_masks[m_uBitsPerPixel / 8 - 1];
	}
}
}