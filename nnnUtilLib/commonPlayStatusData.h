#if !defined ___NNNUTILLIB_COMMONPLAYSTATUSDATA__
#define ___NNNUTILLIB_COMMONPLAYSTATUSDATA__



class CNameList;
class CPolygonShape;

class CCommonPlayStatusData
{
public:
	CCommonPlayStatusData(CNameList* setup,LPSTR statusName);
	~CCommonPlayStatusData();
	void End(void);

	int GetGraphNumber(void);
	LPSTR GetVarName(int n);
//	LPSTR GetFilename(int n);
	int GetVarNumber(int n);
	void SetVarNumber(int n,int d);
	void SetData(int n,int d);
	void Print(int ps = 100);
	void Print(POINT pt, int ps = 100);

	static char m_errorName[];
	static char m_errorVarName[];
	static char m_errorFilename[];

protected:
	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name);

	void PrintRoutine(int ps);

	int m_graphNumber;
	int m_graphType;

	SIZE* m_size;
	POINT* m_zahyo;
	LPSTR* m_varName;
	int* m_varNumber;
	int* m_max;
	int* m_data;
	int m_circleSet;

	CPicture** m_pic;
	int* m_color;
	int m_picFlag;
	int m_perFlag;

	CPolygonShape** m_polygonShape;

	POINT m_basePoint;

	void PrintYokoGraph(void);
	void PrintTateGraph(void);
	void PrintRadarGraph(void);
	void PrintOresenGraph(void);
	void PrintCircleGraph(void);

	int m_lineSize;

	int m_percent;
private:
	CNameList* m_setupList;

	BOOL CheckN(int n);
};




#endif
/*_*/


