//
//
//

#if !defined __NYANLIB_MYFILE__
#define __NYANLIB_MYFILE__

class CAllPackFile;
class CMyFile
{
public:
	CMyFile(BOOL packFlag = FALSE);
	~CMyFile();
	void End(void);

	static FILE* Open(LPSTR filename,LPSTR mode,INT64* pFileSize = NULL);
	static FILE* OpenFullPath(LPCSTR fullFilename,LPCSTR mode,INT64* pFileSize = NULL);

	static BOOL CheckExistPackDir(LPCSTR dir);
	static BOOL CheckExistFile(LPCSTR dir,LPCSTR filename,BOOL errorPrintFlag = TRUE);


	static HANDLE OpenRead(LPSTR filename);
	static HANDLE OpenWrite(LPSTR filename);

	static CAllPackFile* m_packFile;
	static BOOL m_iosPackFlag;
	static char m_iosPackFileName[4096];

private:
};

#endif
/*_*/

