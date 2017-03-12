#include "TFile.h"

//#include <stdio.h>
#include <string>
#include <glog/logging.h>

namespace T3D {

	TFile::TFile() : m_size(0), m_isOpen(false), m_data(0)
	{

	}

	TFile::~TFile()
	{
		Close();
	}

	TFile::TFile(const TFile &rhs)
	{
		m_size = rhs.m_size;
		m_isOpen = rhs.m_isOpen;

		if (rhs.m_data)
		{
			m_data = new uint8[m_size];
			memcpy(m_data, rhs.m_data, m_size);
		}
	}

	TFile & TFile::operator=(const TFile &rhs)
	{
		Close();

		m_size = rhs.m_size;
		m_isOpen = rhs.m_isOpen;

		if (rhs.m_data)
		{
			m_data = new uint8[m_size];
			memcpy(m_data, rhs.m_data, m_size);
		}

		return *this;
	}

	void TFile::Open(const char *filepath)
	{
		FILE *pFile = NULL;
		fopen_s(&pFile, filepath, "rb");
		if (pFile)
		{
			//得到文件大小
			fseek(pFile, 0, SEEK_END);
			m_size = ftell(pFile);
			fseek(pFile, 0, SEEK_SET);

			if (m_size == -1)
			{
				fclose(pFile);
				LOG(ERROR) << filepath << " size = -1";
				return;
			}

			if (m_size > 1024 * 1024 * 1024)
			{
				fclose(pFile);
				LOG(ERROR) << filepath << " too big, size=" << m_size;
				return;
			}

			void *pTmp = new (std::nothrow) char[m_size];
			if (!pTmp)
			{
				fclose(pFile);
				m_size = 0;
				LOG(ERROR) << "new memory failed, size=" << m_size;
				return;
			}

			size_t bRead = fread(pTmp, 1, m_size, pFile);
			if (bRead != m_size)
			{
				delete[] pTmp;
				m_size = 0;
			}
			else
			{
				m_data = (uint8*)pTmp;
				m_isOpen = true;
			}
			fclose(pFile);
		}
		else
		{
			LOG(ERROR) << "load " << filepath << " error";
		}
	}

	void TFile::Close()
	{
		if (m_data)
		{
			delete[] m_data;
			m_data = NULL;
			m_isOpen = false;
			m_size = 0;
		}
	}

	const uint8 * TFile::GetData() const
	{
		return m_data;
	}

	uint32 TFile::Size() const
	{
		return m_size;
	}

	bool TFile::IsOpen() const
	{
		return m_isOpen;
	}

}