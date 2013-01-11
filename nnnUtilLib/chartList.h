

#if !defined __NNNUTILLIB_CHARTLIST__
#define __NNNUTILLIB_CHARTLIST__


class CNameList;
class CChartList
{
public:
	CChartList(int n,BOOL angouFlag = FALSE,int blockSize = 1000,int* exAngou = NULL);
	~CChartList();
	void End(void);
	
	int GetSlotKosuu(void){return m_slotKosuu;}
	int GetSlot(int n);
	POINT GetZahyo(int slot);
	void SetZahyo(int slot,POINT pt);
	POINT GetNextZahyo(int slot,int k);
	int GetNextKosuu(int slot);
	int GetNext(int slot,int k);
	int GetDescKosuu(int slot,int md = 0);
	LPSTR GetDesc(int slot,int k,int md = 0);
	int GetRouteKosuu(int slot);
	LPSTR GetVarName(int slot);
	void SetVarNumber(int slot,int varNumber);
	int GetVarNumber(int slot);

	int GetTotalRouteKosuu(void);
	int GetN(int slot);
	int GetMaxSlot(void){return m_maxSlot;}

	void Save(void);
	void MakeBak(void);

	int GetMaxSize(void){return m_maxSize;}

	BOOL CheckTop(int slot);
	void SetNotTop(int slot,BOOL flg = FALSE);

	static void SetDescMax(int mx){m_descMax = mx;}
	static int m_descMax;

private:

	int m_blockSize;

	int m_chartNumber;
	CNameList* m_nameList;
	int m_slotKosuu;
	int m_maxNext;
	int* m_slotToNTable;
	POINT* m_zahyo;
	int* m_nextTable;
	int* m_next;
	int* m_descKosuu;
	LPSTR* m_desc;
	int* m_routeKosuu;
	int* m_slot;
	int m_maxSlot;
	int m_maxSize;

	int* m_exAngou;
	int m_exAngouKosuu;
	int* m_exAngouData;

	int* m_varNumber;
	int* m_varName;
	int* m_top;

};

#endif
/*_*/

