#ifndef __BITMAP_H__
#define __BITMAP_H__

typedef unsigned int uint32;

namespace T3D {

	enum BitmapType
	{
		BitmapType_Unknown = 0,
		BitmapType_Alpha8,
		BitmapType_RGB24,
		BitmapType_RGBA32,
		BitmapType_AlphaFloat,
	};

	class Bitmap
	{
	public:
		Bitmap(uint32 width, uint32 height, BitmapType type);
		virtual ~Bitmap();

		static Bitmap * LoadFromFile(const char *filepath);
		bool SaveToFile(const char *filepath);

	private:
		uint32 m_width;
		uint32 m_hegiht;
	};

}

#endif