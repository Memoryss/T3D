#ifndef __T3DLOG_H__
#define __T3DLOG_H__

#include <string>

namespace T3D {

	class Log
	{
	public:
		static int OpenErrorFile(char *filename);
		static int CloseErrorFile();
		static int WriteError(char *string, ...);

	private:
		static FILE* m_file;
	};

}

#endif
