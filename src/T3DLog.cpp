#include "T3DLog.h"

#include <stdarg.h>

namespace T3D {

	FILE* Log::m_file;

	int Log::OpenErrorFile(char *filename)
	{
		m_file = fopen(filename, "r+");
		if (m_file == NULL)
		{
			m_file = fopen(filename, "w+");
		}
		
		if (m_file == NULL) return 1;

		return 0;
	}

	int Log::CloseErrorFile()
	{
		if (m_file != NULL)
		{
			fclose(m_file);
		}

		return 0;
	}

	int Log::WriteError(char *string, ...)
	{
		char buffer[80];

		va_list arglist;
		if (!string || !m_file)
		{
			return 1;
		}

		va_start(arglist, string);
		vsprintf(buffer, string, arglist);
		va_end(arglist);

		// write string to file
		fprintf(m_file, buffer);

		// flush buffer incase the system bails
		fflush(m_file);

		return 0;
	}

}