//
//
//


#include <windows.h>
#include <stdio.h>

#include "include\myFile.h"

CMyFile::CMyFile()
{
}

CMyFile::~CMyFile()
{
	End();
}

void CMyFile::End(void)
{
}

FILE* CMyFile::Open(LPSTR filename,LPSTR mode)
{
#if _MSC_VER >= 1400
	FILE* file = NULL;
	if (fopen_s(&file,filename,mode) == 0)
	{
		return file;
	}
	//error
	//read only?
	if ((*mode) == 'w')
	{
		//check read only

		DWORD at = GetFileAttributes(filename);
		if (at & FILE_ATTRIBUTE_READONLY)
		{
			at &= (~FILE_ATTRIBUTE_READONLY);
			if (SetFileAttributes(filename,at))
			{
				if (fopen_s(&file,filename,mode) == 0)
				{
					return file;
				}
			}
		}
	}

#else
	return fopen(filename,mode);
#endif
	return NULL;
}

HANDLE CMyFile::OpenRead(LPSTR filename)
{
	if (filename == NULL) return NULL;

	return NULL;
}

HANDLE CMyFile::OpenWrite(LPSTR filename)
{
	if (filename == NULL) return NULL;
	return NULL;
}


