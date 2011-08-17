#pragma once
#include "nBase.hpp"
#include "nDynamicTable.hpp"

namespace NLib
{
	class NBitmap
	{
		struct BitmapMagic	// Probably aligned to 4 bytes
		{
			NUint8 magic[2];				// "BM"
		};

		struct BitmapHeader
		{
			NUint32 uFileSize;			// Bitmap file size
			NUint16 uCreator[2];			// dunno
			NUint32 uPixelArrayOffset;
		};

		struct BitmapInfoHeader
		{
			NUint32 uHeaderSize;			// This header size
			NInt32 uWidth;
			NInt32 uHeight;
			NUint16 uNPlanes;				// must be 1
			NUint16 uBitsPerPixel;		// in this class
			NUint32 uCompressType;		// Typical bitmap 0 - RGB
			NUint32 uBitmapSize;			// Bitmap data size
			NInt32 uHRes;
			NInt32 uVRes;					// DPI ?
			NUint32 uNColors;				// 0
			NUint32 uNImpColors;			// 0
		};

	public:
		NBitmap();
		~NBitmap();

		void create(NUint32 uWidth, NUint32 uHeight, NUint32 uBitsPerPixel);
		void release();

		bool loadFromFile(const char* szFile);
		bool saveToFile(const char* szFile) const;

		NUint32 getWidth() const		{ return m_uWidth; }
		NUint32 getHeight() const		{ return m_uHeight; }
		NUint32 getBitsPerPixel() const { return m_uBitsPerPixel; }

		NUint8* getBuffer() { return m_aBitmap.GetBuffer(); }

		void setPixel(NUint32 x, NUint32 y, NUint32 color);
		NUint32 getPixel(NUint32 x, NUint32 y) const;

	private:
		NDynamicTable<NUint8> m_aBitmap; // uBitsPerPixel * m_uWidth * m_uHeight
		NUint32 m_uWidth;
		NUint32 m_uHeight;
		NUint32 m_uBitsPerPixel;
	};
}

#define NBITMAP_RGB(r, g, b) ((b | (g << 8) | (r << 16)) & 0x00FFFFFF)
#define NBITMAP_R(color) ((color >> 16) & 0xFF)
#define NBITMAP_G(color) ((color >> 8) & 0xFF)
#define NBITMAP_B(color) ((color) & 0xFF)