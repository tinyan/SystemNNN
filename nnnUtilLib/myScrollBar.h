#if !defined __NNNUTILLIB_SCROLLBAR__
#define __NNNUTILLIB_SCROLLBAR__


class CNameList;
class CInputStatus;
class CPicture;

class CMyScrollBar
{
public:
	CMyScrollBar(LPSTR barname,CNameList* lpSetup,CPicture* lpBG = NULL);
	~CMyScrollBar();
	void End(void);



	void Init(int pos = 0);
	int Calcu(CInputStatus* lpInput);
	void Print(BOOL flg = TRUE);

	int GetPos(void){return m_pos;}

	void SetExist(BOOL flg = TRUE);
	void SetEnable(BOOL flg = TRUE);
	void SetZahyo(POINT pt);
	void SetSize(SIZE sz);
	void SetMin(int mn){m_min = mn;}
	void SetMax(int mx){m_max = mx;}
	void SetScrollPage(int pg){m_scrollPage = pg;}

	static char m_defaultBasePicFileName[];
	static char m_defaultBoxPicFileName[];


	BOOL CheckOnBox(POINT pt);
	int CheckOnBar(POINT pt);
	POINT GetBoxZahyo(void);

	void AdjustInScroll(void);
private:
	CNameList* m_setup;
	CPicture* m_bg;
	BOOL m_existFlag;
	BOOL m_enableFlag;
	POINT m_zahyo;
	SIZE m_size;

	POINT m_printZahyo;
	SIZE m_printSize;

	SIZE m_boxSize;

	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name);

	CPicture* m_basePic;
	CPicture* m_boxPic;

	int m_min;
	int m_max;
	int m_pos;
	POINT m_printPos;
	int m_tate;
	int m_scrollPage;
	int m_wheelPage;

	int m_captureOk;
	BOOL m_captureFlag;
	POINT m_captureDelta;

	void PosToPrintPos(void);
	void PrintPosToPos(void);
};

#endif
/*_*/
