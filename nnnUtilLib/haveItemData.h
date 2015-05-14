#if !defined ___NNNUTILLIB_HAVEITEMDATA__
#define ___NNNUTILLIB_HAVEITEMDATA__



class CNameList;

class CHaveItemData
{
public:
	CHaveItemData();
	~CHaveItemData();
	void End(void);

	typedef struct _tagHAVEITEMDATA
	{
		int serial;
		int type;
		LPSTR name[16];
		LPSTR varName;
		LPSTR filename;
		int descNumber[16];

		int varNumber;

	}HAVEITEMDATA;

	static char m_errorName[];
	static char m_errorVarName[];
	static char m_errorFilename[];

	int GetListKosuu(void);

	int GetDescNumber(int n,int md=1);
	LPSTR GetDesc(int n,int k,int md=1);
	int GetSerial(int n);
	int GetType(int n);
	LPSTR GetName(int n,int md=1);
	LPSTR GetVarName(int n);
	LPSTR GetFilename(int n);
	int GetVarNumber(int n);
	void SetVarNumber(int n,int d);

	int GetTypeHaveNumber(int type);

private:
	CNameList* m_list;
	int m_listKosuu;
	LPSTR* m_descList;
	int m_descMax;

	HAVEITEMDATA* m_table;

	int m_typeMax;
	int* m_typeKosuu;

	BOOL CheckN(int n);
};




#endif
/*_*/


