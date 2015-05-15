#if !defined ___NNNUTILLIB_SHOPITEMDATA__
#define ___NNNUTILLIB_SHOpITEMDATA__



class CNameList;

class CShopItemData
{
public:
	CShopItemData(BOOL angouFlag = FALSE);
	~CShopItemData();
	void End(void);

	typedef struct _tagSHOPITEMDATA
	{
		int serial;
		int type;
		int price;
		int limit;

		LPSTR name;
		LPSTR filename;
		LPSTR appearVarName;
		LPSTR targetVarName;

		int descNumber;

		int appearVarNumber;
		int targetVarNumber;


	}SHOPITEMDATA;





	static char m_errorName[];
	static char m_errorVarName[];
	static char m_errorFilename[];

	int GetListKosuu(void);

	int GetDescNumber(int n,int md=1);
	LPSTR GetDesc(int n,int k,int md=1);
	int GetSerial(int n);
	int GetType(int n);
	int GetPrice(int n);
	int GetLimit(int n);

	LPSTR GetName(int n,int md=1);
	LPSTR GetAppearVarName(int n);
	LPSTR GetTargetVarName(int n);
	int GetAppearVarNumber(int n);
	int GetTargetVarNumber(int n);
	void SetAppearVarNumber(int n,int d);
	void SetTargetVarNumber(int n,int d);

	LPSTR GetFilename(int n);
//	int GetVarNumber(int n);
//	void SetVarNumber(int n,int d);

	int GetTypeShopNumber(int type);

private:
	CNameList* m_list;
	int m_listKosuu;
	LPSTR* m_descList;
	int m_descMax;

	SHOPITEMDATA* m_table;

	int m_typeMax;
	int* m_typeKosuu;

	BOOL CheckN(int n);
};




#endif
/*_*/


