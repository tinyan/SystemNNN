#if !defined __NNNUTILLIB_COMMONRESULTDATA__
#define __NNNUTILLIB_COMMONRESULTDATA__


class CCommonResultData
{
public:
	CCommonResultData(LPSTR filename,int kosuu = 1024,BOOL angouFlag = FALSE,int paraKosuu = 1,LPSTR subFoldername = NULL);
	~CCommonResultData();
	void End(void);

	void SetData(int resultNumber,int d,int para = 0);
	void AddData(int resultNumber,int d,int para = 0);
	int GetData(int resultNumber,int para = 0);

	BOOL Load(void);
	BOOL Save(void);


	void ClearData(void);
private:
	int* m_data;
	int m_dataMax;
	int m_paraMax;
	BOOL m_editFlag;
	BOOL m_angouFlag;

	LPSTR m_filenameOnly;
	LPSTR m_subFolderName;

	LPSTR GetFileName(BOOL orgFlag = FALSE);
	char m_filename[1024];
};

#endif
/*_*/

