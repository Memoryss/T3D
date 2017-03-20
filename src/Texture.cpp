#include "Texture.h"

#include <Windows.h>
#include <assert.h>

#include <glog/logging.h>
#include <TMath.h>
#include "TFile.h"

namespace T3D {

	Texture::Texture() : m_data(NULL), m_width(0), m_height(0), m_rawData(NULL), m_byteCount(0), m_pitch(0)
	{ 

	}

	Texture::Texture(const char *filepath, aiTextureType type) : m_filename(filepath), m_data(NULL), m_width(0), m_height(0), m_rawData(NULL), m_byteCount(0), m_pitch(0), m_type(type)
	{
		
	}

	void Texture::SetPathAndType(const char *path, aiTextureType type)
	{
		m_filename = path;
		m_type = type;
	}

	void Texture::ReadFile()
	{
		TFile texFile;
		texFile.Open(m_filename.c_str());
		if (texFile.IsOpen())
		{
			const uint8 *start = texFile.GetData();
			tagBITMAPFILEHEADER *header = (tagBITMAPFILEHEADER*)start;
			tagBITMAPINFO *info = (tagBITMAPINFO*)(start + sizeof(tagBITMAPFILEHEADER));
			LOG(INFO) << "BMP file open," << " width=" << info->bmiHeader.biWidth
				<< " height=" << info->bmiHeader.biHeight
				<< " bitcount=" << info->bmiHeader.biBitCount
				<< " offset=" << header->bfOffBits
				<< " size=" << header->bfSize / 1024 << " kb";

			m_width = info->bmiHeader.biWidth;
			m_height = info->bmiHeader.biHeight;
			m_byteCount = info->bmiHeader.biBitCount;
			m_pitch = -m_width * m_height * m_byteCount / info->bmiHeader.biHeight; //TODO 为什么负号，？屏幕坐标不一样
			m_rawData = new (std::nothrow) uint8[m_width * m_height * m_byteCount];
			if (!m_rawData)
			{
				LOG(ERROR) << "new memory failed, size=" << m_width * m_height * m_byteCount;
				return;
			}

			const uint8 *colorStart = start + header->bfOffBits;
			memcpy(m_rawData, colorStart, m_width * m_height * m_byteCount);
			if (m_pitch < 0)
			{
				m_data = m_rawData + m_width * m_height * m_byteCount;
			}
		}
		else
		{
			LOG(ERROR) << "Bitmap load failed, path=" << m_filename;
			m_rawData = 0;
		}
	}

	uint32 Texture::sampleImp(uint32 x, uint32 y) const
	{
		uint32 texel = 0;
		uint8 *data = m_data;
		
		assert(x >= 0 && x < m_width);
		assert(y >= 0 && y < m_height);

		if (m_byteCount == 3)
		{
			texel = Math::uint8BGR_to_uint32BGRA(m_data + x * m_byteCount + y * m_pitch);
		}
		else
		{
			texel = *(uint32*)(m_data + x * m_byteCount + y * m_pitch);
		}

		return texel;
	}

	uint32 Texture::Sample(float x, float y, SamplerFilter filter)
	{
		float u = x - floor(x);
		float v = y - floor(y);

		uint32 final = 0x00000000;
		if (filter == SF_Linear)
		{
			final = sampleLinear(u, v);
		}
		else
		{
			final = sampleNearest(u, v);
		}

		return final;
	}

	uint32 Texture::sampleLinear(float u, float v)
	{
		int x = u * m_width;
		int y = v * m_height;

		x %= m_width;
		y %= m_height;

		return sampleImp(x, y);
	}

	uint32 Texture::sampleNearest(float u, float v)
	{
		u *= (m_width - 1); //  -1  是为了取点的左边
		v *= (m_height - 1); //

		int x = (int)u;
		int y = (int)y;

		//子像素偏移
		float du = u - x;
		float dv = v - y;

		//找到四个点的坐标
		int left = x % m_width;
		int right = (x + 1) % m_width;
		int up = y % m_height;
		int down = (y + 1) % m_height;

		uint32 lu = sampleImp(left, up);
		uint32 ru = sampleImp(right, up);
		uint32 ld = sampleImp(left, down);
		uint32 rd = sampleImp(right, down);

		 return Math::ColorScaleFloat(lu, (1 - du) * (1 - dv)) + Math::ColorScaleFloat(ru, du * (1 - dv)) + Math::ColorScaleFloat(ld, (1 - du) * dv) + Math::ColorScaleFloat(ru, du * dv);
	}

}