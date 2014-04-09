//
//
//

#if !defined __NNNUTILLIB_ALLPACKFILE__
#define __NNNUTILLIB_ALLPACKFILE__

typedef struct _tagMYALLPACKHEADER
{
	INT64 size;
	char headerName[16];
	INT64 blockCount;
	INT64 filesize;//use??
	INT64 dataBlockOffset;//==size
	INT64 pad[2];
	INT64 dataBlockPointer[1];//blockCountå¬êî
} MYALLPACKHEADER;

class CAllPackData;
class CAllPackFile
{
public:
	CAllPackFile(LPCSTR filename);
	~CAllPackFile();
	void End(void);

	INT64 GetFileOffset(LPCSTR filename,INT64* lpSize = NULL);
	BOOL CheckExistPackDir(LPCSTR dir);
	BOOL CheckExistFile(LPCSTR dir,LPCSTR filename,BOOL errorPrintFlag = TRUE);


private:
	INT64 m_allPackDataKosuu;
	MYALLPACKHEADER* m_header;
	CAllPackData** m_allPackData;


};

#endif
/*_*/

