#ifndef __TFILE_H__
#define __TFILE_H__

typedef unsigned int uint32;
typedef unsigned char uint8;

namespace T3D{

	class TFile
	{
	public:
		TFile();
		~TFile();

		TFile(const TFile &other);
		TFile & operator=(const TFile &rhs);

		void Open(const char *filepath);

		void Close();

		const uint8 * GetData() const;

		uint32 Size() const;

		bool IsOpen() const;


	private:
		uint32 m_size;
		bool m_isOpen;

		uint8 *m_data;
	};

}

#endif
