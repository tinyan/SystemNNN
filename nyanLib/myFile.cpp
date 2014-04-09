//
//
//


#include <windows.h>
#include <stdio.h>

#include "include\myFile.h"
#include "include\commonmacro.h"
#include "..\nnnUtillib\allPackFile.h"

CAllPackFile* CMyFile::m_packFile = NULL;
BOOL CMyFile::m_iosPackFlag = FALSE;
char CMyFile::m_iosPackFileName[4096] = "iospack.nya";

CMyFile::CMyFile(BOOL packFlag)
{
	if (packFlag)
	{
		//check exist?
		FILE* file = NULL;
		fopen_s(&file,m_iosPackFileName,"rb");
		if (file != NULL)
		{
			fclose(file);
			m_packFile = new CAllPackFile(m_iosPackFileName);
			m_iosPackFlag = TRUE;
//			MessageBox(NULL,"1","1",MB_OK);
		}
	}
}

CMyFile::~CMyFile()
{
	End();
}

void CMyFile::End(void)
{
	ENDDELETECLASS(m_packFile);
}

FILE* CMyFile::Open(LPSTR filename,LPSTR mode,INT64* pFileSize)
{


	if (m_iosPackFlag)
	{
		char filename2[4096];
		int ln = (int)strlen(filename);
		int n = 0;
		while (n<ln)
		{
			char c = *(filename + n);
			int d = (int)c;
			d &= 0xff;
			if (d == 0x5c)
			{
	//			c = '/';
			}
		
			if ((c>='A') && (c<='Z'))
			{
				c += 0x20;
			}
		
		
			*(filename2+n) = c;
			n++;
			//shiftjiskanji
			if (((d >= 0x80) && (d<0xa0)) || ((d >= 0xe0) && (d<=0xff)))
			{
				*(filename2+n) = *(filename);
				n++;
			}
		}
		filename2[ln] = 0;
		filename2[ln+1] = 0;

		fpos_t seek;
		INT64 ret;
		ret = m_packFile->GetFileOffset(filename2,pFileSize);
		FILE* file = NULL;
		if (ret != -1)
		{
//			printf("[openfile:: iospacktype:retok %d] ",(int)ret);
			seek = (fpos_t)ret;
			fopen_s(&file,m_iosPackFileName,mode);
			if (file != NULL)
			{
				fsetpos(file,&seek);
			}
		}
		else
		{
			char mes[] = " [openfile:: iospacktype open:ret err : ] ";
			mes[0] = 0xa;
			printf(mes,filename2);
		}
		
		return file;


	}

#if _MSC_VER >= 1400
	FILE* file = NULL;
	if (fopen_s(&file,filename,mode) == 0)
	{

		if (pFileSize != NULL)
		{
			fseek(file,0,SEEK_END);
			long int sz = ftell(file);
			fseek(file,0,SEEK_SET);
			*pFileSize = sz;
		}

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
					if (pFileSize != NULL)
					{
						fseek(file,0,SEEK_END);
						long int sz = ftell(file);
						fseek(file,0,SEEK_SET);
						*pFileSize = sz;
					}
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


BOOL CMyFile::CheckExistPackDir(LPCSTR dir)
{
	return m_packFile->CheckExistPackDir(dir);
}

BOOL CMyFile::CheckExistFile(LPCSTR dir,LPCSTR filename,BOOL errorPrintFlag)
{
	char filename2[4096];
	char filename3[4096];
	int ln = (int)strlen(filename);
	int n = 0;
	while (n<ln)
	{
		char c = *(filename + n);
		int d = (int)c;
		d &= 0xff;
		if (d == 0x5c)
		{
			//			c = '/';
		}
		
		if ((c>='A') && (c<='Z'))
		{
			c += 0x20;
		}
		
		
		*(filename2+n) = c;
		*(filename3+n) = c;
		if (d == 0x5c)
		{
			*(filename3+n) = '/';//			c = '/';
		}
		
		n++;
		//shiftjiskanji
		if (((d >= 0x80) && (d<0xa0)) || ((d >= 0xe0) && (d<=0xff)))
		{
			*(filename2+n) = *(filename);
			*(filename3+n) = *(filename);
			n++;
		}
	}
	filename2[ln] = 0;
	filename2[ln+1] = 0;
	filename3[ln] = 0;
	filename3[ln+1] = 0;
	
	//	printf("filename2 = %s",filename2);
	
	
	
	if (m_iosPackFlag)
	{
		return m_packFile->CheckExistFile(dir,filename2,errorPrintFlag);
	}
	else
	{
		return FALSE;
		//char fullFilename[4096];
//		sprintf(fullFilename,"%s/%s",m_bandlePath,filename3);
		//return OpenFullPath(fullFilename,mode,pFileSize);
	}
}

//for load save folder
FILE* CMyFile::OpenFullPath(LPCSTR fullFilename,LPCSTR mode,INT64* pFileSize)
{
	FILE* file = NULL;

	fopen_s(&file,fullFilename,mode);
	if (file != NULL)
	{
		if (pFileSize != NULL)
		{
//			if (m_iosPackFlag)
//			{
//			}
//			else
//			{
				fseek(file,0,SEEK_END);
				long int sz = ftell(file);
				fseek(file,0,SEEK_SET);
				*pFileSize = sz;
//			}
		}
		return file;
	}
	fprintf(stderr,"open error:%s",fullFilename);
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


