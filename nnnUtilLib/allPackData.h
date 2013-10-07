//
//
//

#if !defined __NNNUTILLIB_ALLPACKDATA__
#define __NNNUTILLIB_ALLPACKDATA__

typedef struct _tagMYALLPACKDATA
{
	INT64 size;
	char headerName[16];
	INT64 totalSize;//MYALLPACKDATA +  MYFILENAMESTRUCT + MYFILENAMESTRUCT + MYFILESTARTSTRUCT
	INT64 fileNumber;
	INT64 folderNameStructOffset;
	INT64 filenameStructOffset;
	INT64 hashStructOffset;
	INT64 fileStartStructOffset;
	INT64 pad[3];
}MYALLPACKDATA;

typedef struct _tagMYFOLDERNAMESTRUCT
{
	INT64 size;
	char headerName[16];
	INT64 folderLevelNumber;
	INT64 fullFolderLength;
	INT64 pad[3];
	char fullFolder[64];
	char folder[1][16];//folderLevelNumberå¬êî
}MYFOLDERNAMESTRUCT;

typedef struct _tagMYFILENAMESTRUCT
{
	INT64 size;
	char headerName[16];
	INT64 filenameOffset;
	INT64 pad[4];
	INT64 filenameTableOffset[1];//fileNumberå¬êî
	//data
}MYFILENAMESTRUCT;

typedef struct _tagMYHASHSTRUCT
{
	INT64 size;
	char headerName[16];
	INT64 hashCount;
	INT64 pad[4];
	int hashData[1];//4*hashCount allbit,number,next dummy=0
}MYHASHSTRUCT;

typedef struct _tagMYFILESTARTSTRUCT
{
	INT64 size;	//header size
	char headerName[16];
	INT64 dataOffset;
	INT64 dataSize;
	INT64 pad[3];
	INT64 dataStart[1];//fileNumber+1å¬êî
	//data
}MYFILESTARTSTRUCT;


class CAllPackData
{
public:
	CAllPackData(FILE* file);
	~CAllPackData();
	void End(void);

	BOOL CheckDir(LPCSTR dir);
	INT64 SearchFile(LPCSTR filename,INT64* lpFileSize);

private:
	INT64 m_fileNumber;

	MYALLPACKDATA* m_allPackData;
	MYFOLDERNAMESTRUCT* m_folderNameStruct;
	MYFILENAMESTRUCT* m_fileNameStruct;
	MYHASHSTRUCT* m_hashStruct;
	MYFILESTARTSTRUCT* m_fileStartStruct;

};

#endif
/*_*/

