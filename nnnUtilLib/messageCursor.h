//
// messageCursor.h
//

#if !defined __NNNUTILLIB_MESSAGECURSOR__
#define __NNNUTILLIB_MESSAGECURSOR__

class CFloatingLayer;
//#include "floatingLayer.h"
class CMessageCursor : public CFloatingLayer
{
public:
	CMessageCursor(CTaihi* lpTaihi, int n);
	virtual ~CMessageCursor();
	virtual void End(void);

	virtual void Calcu(int count = 1);
	virtual void Print(int type = 0, BOOL taihiFlag = TRUE);

	virtual void SetFullZahyo(int x, int y);

	void SetCursorNumberByConfig(int n){m_cursorNumberConfig = n;}
	void SetCursorNumberByScript(int n){m_cursorNumberScript = n;};

	int GetCursorShuruiConfig(void){return m_cursorShuruiConfig;}
	int GetCursorShuruiScript(void){return m_cursorShuruiScript;}

protected:
	static char m_defaultCursorFileName[];

	int m_printX[4];
	int m_printY[4];

	int m_sizeX[4];
	int m_sizeY[4];

//	int m_percent;

	int m_percentStart[4];
	int m_percentEnd[4];
	int m_percentReverseFlag[4];
	int m_percentLoop[4];

	int m_percentCount[4];


	CPicture* m_cursorPic[4];

//	BOOL m_cursorPicFlag[4];

	int m_animePattern[4];
	int m_animePatternKosuu[4];
	int m_animeReverse[4];
	int m_animeSpeed[4];
	int m_animeCount[4];

	int m_fullFixX;
	int m_fullFixY;

	int m_fullPrintX;
	int m_fullPrintY;

	LPSTR* m_ppCursorFileName;

	int m_cursorNumberConfig;
	int m_cursorNumberScript;

	int m_loadedCursorNumberConfig[4];
	int m_loadedCursorNumberScript[4];

	BOOL CheckCursorLoaded(int type);

	void LoadMyCursor(int type);

	int m_cursorShuruiConfig;
	int m_cursorShuruiScript;

private:
};


#endif
/*_*/

