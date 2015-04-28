//
// SelectPlace.h
//

#if !defined __NNNLIB_COMMONPRINTTERM____
#define __NNNLIB_COMMONPRINTTERM__

class CCommonGeneral;
class CGameCallBack;
class CNameList;
class CMyMessage;

//class CPrintGameDate;
class CCommonAnimeParts;


class CCommonPrintTerm : public CCommonGeneral
{
public:
	CCommonPrintTerm(CGameCallBack* lpGame,int extMode = 0);
	virtual ~CCommonPrintTerm();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	virtual void CreateStartScreen(void);

	typedef struct _tagTERMDATA
	{
		int n;
		int type;
		int param;
		LPSTR title;
	}TERMDATA;

protected:
	virtual void FinalExitRoutine(void);
	virtual int EndMode(void);

	CMyMessage* m_message;
	int m_termTypeKosuu;
	CCommonRadioButtonGroup* m_radio;
	CNameList* m_termList;
	int m_allTermNumber;

	TERMDATA* m_termData;
	static int MyCompare(const void* a,const void* b);
	static int m_sortByType;
	static int m_sortByParam;
	static int m_sortByTitle;

	int m_typeNumber;

	int m_page;
	int m_pageMax;
	int m_termPerPage;
	int m_termNumber;
	int m_selectedTermNumber;

	void ListAndSortTerm(void);
	int** m_typeTable;
	int* m_typeTableNumber;

	void ReloadButtonPic(void);
	int m_onNumber;
	int GetOnNumber(POINT pt);
	POINT GetListPoint(int n);

	int m_listPrintX;
	int m_listPrintY;
	int m_listNextX;
	int m_listNextY;
	int m_listSizeX;
	int m_listSizeY;

	int m_termTextNumber;
	void ReloadTermText(void);
	CNameList* m_termText;

	CCommonAnimeParts* m_newMark;
	int m_newMarkPrintX;
	int m_newMarkPrintY;

private:

};

#endif
/*_*/

