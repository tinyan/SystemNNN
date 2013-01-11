//
// waveData.h
//


#if !defined __NNNUTILLIB_WAVEDATA__
#define __NNNUTILLIB_WAVEDATA__

class COggDecoder;
//class CHuffMan;

#define PACKWAVE_TABLE_KOSUU_MAX 1024

class CWaveData
{
public:
	CWaveData(int initBufferSize = 0);
	~CWaveData();
	void End(void);


	int GetDataSize(void);
	int GetRealDataSize(void);
	void* GetData(void);
	void* GetRealDataPtr(void);

	BOOL LoadSystemWave(LPSTR dirName,LPSTR filename);
	BOOL LoadWave(LPSTR filenameOnly);
	BOOL LoadPackedWave(LPSTR filenameOnly);//,LPSTR packFile, LPSTR tableFile);

	BOOL LoadTable(LPSTR tableName);
	LPSTR GetFileName(void);

	static BOOL m_cdFlag;
	static char m_dirName[];
	static char m_cdDirName[];

	int GetLength(void);

	BOOL AdjustWaveLevel(int percent);

	int GetAdjustPercent(void);
	BOOL CheckAdjusted(void);

	int GetChannel(void);
	int GetBitRate(void);
	int GetSampleRate(void);

private:
	static int m_refCount;
	static COggDecoder* m_oggDecoder;
//	static CHuffMan* m_huffMan;

	static char m_tableName[3*PACKWAVE_TABLE_KOSUU_MAX];
	static int m_tableKosuu;
	static char* m_tableData[PACKWAVE_TABLE_KOSUU_MAX];
	static int m_tableSize[PACKWAVE_TABLE_KOSUU_MAX];

	static int m_commonBufferSize;
	static BOOL m_commonBufferCreateFlag;
	static char* m_commonBuffer;


	int GetCDVAWSeekPointer(int pacNumber,LPSTR filename, int* lpSize);


	int m_dataType;

	int m_headerSize;
	int m_dataSize;
	int m_bufferSize;

	WAVEFORMATEX m_waveformatex;

	char vawHeader[64];
	char m_header[64];
	char* m_data;
	char* m_realDataPtr;

	int m_realDataSize;
	BOOL CreateBuffer(int newSize);

	BOOL LoadWaveRoutine(FILE* file,int loadSize = -1);

	char m_fileName[256];

	BOOL m_adjustWaveLevelFlag;
	int m_adjustPercent;

	BOOL ReCreateCommonBuffer(int size);

};




#endif
/*_*/

