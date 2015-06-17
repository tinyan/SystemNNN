#if !defined ___NNNUTILLIB_COMMONPARTYSTATUSDATA__
#define ___NNNUTILLIB_COMMONPARTYSTATUSDATA__



class CNameList;
class CSuuji;
class CMyMessage;

class CCommonPartyStatusData
{
public:
	CCommonPartyStatusData(CNameList* setup,CMyMessage* message);
	~CCommonPartyStatusData();
	void End(void);
	
	int GetType(int n,int k);

	LPSTR GetVarName(int n,int k);
	int GetVarNumber(int n,int k);
	void SetVarNumber(int n,int k,int d);
	void SetData(int n,int k,int d);

	LPSTR GetEtcVarName(int n);
	int GetEtcVarNumber(int n);
	void SetEtcVarNumber(int n,int d);
	void SetEtcData(int n,int d);

	LPSTR GetPrintVarName(int n);
	int GetPrintVarNumber(int n);
	void SetPrintVarNumber(int n,int d);
	void SetPrintData(int n,int d);

	int GetPartyNumber(void){return m_partyNumber;}
	int GetPrintNumberMax(void){return m_printNumberMax;}
	int GetStatusNumber(void){return m_statusNumber;}
	int GetEtcNumber(void){return m_etcNumber;}

	void Print(int ps = 100);

	static char m_suujiName[];
	static char m_errorName[];
	static char m_errorVarName[];
	static char m_errorFilename[];

protected:
	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name);

	int m_partyNumber;
	int m_statusNumber;
	int m_etcNumber;

	int m_printNumberMax;
	int* m_printNumberTable;
	int* m_printNumberVarData;



	int m_partyAreaSizeX;
	int m_partyAreaSizeY;

	POINT* m_partyZahyo;

	typedef struct _tagSTATUSPARAM
	{
		int type;
		//1:suuji 2:text 3:systemtext

		POINT zahyo;

		CSuuji* suuji;

		int fontSize;
		int colorR,colorG,colorB;
	} STATUSPARAM;

	STATUSPARAM* m_statusParam;

	typedef struct _tagPARTYPARAM
	{
		CPicture* pic;

		int* statusVar;//var or textnumber
		int* data;
	} PARTYPARAM;

	PARTYPARAM* m_partyParam;


	typedef struct _tagETCPARAM
	{
		POINT zahyo;
		CSuuji* suuji;
		int varNumber;
		int data;
	}ETCPARAM;

	ETCPARAM* m_etcParam;


	int m_printByVar;


	BOOL CheckNK(int n,int k);
	BOOL CheckEtcN(int n);
	BOOL CheckEtcNP(int n);


	CPicture* m_platePic;


	int m_percent;
private:
	CNameList* m_setupList;
	CMyMessage* m_message;

};




#endif
/*_*/


