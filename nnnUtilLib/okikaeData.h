#if !defined ___NNNUTILLIB_OKIKAEDAATA__
#define ___NNNUTILLIB_OKIKAEDAATA__



class CAutoSaveSubData;
class CNameList;

class COkikaeData : public CAutoSaveSubData
{
public:
	COkikaeData(int okikae = 100,int sysMax = 100,BOOL useDefault = FALSE);
	~COkikaeData();
	void End(void);


	void GetExtDataForSave(LPVOID ptr,int extNumber = 0);
	void SetExtDataByLoad(LPVOID ptr,int extNumber = 0);

	int GetOkikaeMax(void){return m_okikaeMax;}
	int GetSystemOkikaeMax(void){return m_systemOkikaeMax;}
	char* GetOkikaeMessage(int n);
	void SetOkikaeMessage(int n,char* mes);
	char* GetSystemOkikaeMessage(int n);
	void SetSystemOkikaeMessage(int n,char* mes);
private:
	int m_okikaeMax;
	char* m_okikaeMessage;
	int m_systemOkikaeMax;
	char* m_systemOkikaeMessage;

	CNameList* m_defaultText;

//	BOOL GetInitGameParam(int* lpVar, LPSTR name,int initData);
//	BOOL GetInitGameParam(int* lpVar, LPSTR name);
//	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name,LPSTR initString);
//	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name);



};




#endif
/*_*/


