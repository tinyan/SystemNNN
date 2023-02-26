//
// commonSelectCGChara.h
//

#if !defined __NNNLIB_COMMONSELECTCGCHARA__
#define __NNNLIB_COMMONSELECTCGCHARA__


class CGameCallBack;
class CSuuji;
class CBackButton;

class CCGDataControl;

//class CMyButtonGroup;

class CCommonSelectCGChara : public CCommonGeneral
{
public:
	CCommonSelectCGChara(CGameCallBack* lpGame);
	virtual ~CCommonSelectCGChara();
	virtual void End(void);

	virtual int Calcu(void);
	virtual int Print(void);
	virtual int Init(void);

	virtual void CreateStartScreen(void);

protected:
//	LPSTR m_filenameBG;
	LPSTR m_filenameChara;
	LPSTR m_filenameCursor;

	static char m_defaultBGFileName[];
	static char m_defaultCharaFileName[];
	static char m_defaultCursorFileName[];

	static char m_defaultPercentFileName[];

	int m_cursorMode;
	int m_pictureMode;

	int m_sizeX;
	int m_sizeY;

	int m_numberX;
	int m_numberY;

	int m_cursorColorR;
	int m_cursorColorG;
	int m_cursorColorB;
	int m_cursorPercent;
	int m_cursorPrintType;

	int m_picNumberX;
	int m_cgCustomnPrintFlag;

	int m_basePrintX;
	int m_basePrintY;
	int m_baseNextX;
	int m_baseNextY;

	CPicture* m_cursorPic;

	POINT* m_zahyo;
	POINT GetZahyo(int n) {return m_zahyo[n];}


	void PrintCharaPercent(int n);
	int m_charaVoiceFlag;
	int m_cgCharaKosuu;

	int m_cgCustomPrintFlag;

	int m_charaVoiceWaitTime;

	int m_totalPercentPrintFlag;
	int m_totalPercentPercentFlag;

	int m_charaPercentPrintFlag;
	int m_charaPercentPercentFlag;

	int m_totalPercentPrintX;
	int m_totalPercentPrintY;
	int m_totalPercentFontSizeX;
	int m_totalPercentFontSizeY;
	int m_totalPercentFontNextX;

	int m_percentPrintX;
	int m_percentPrintY;
	int m_percentFontSizeX;
	int m_percentFontSizeY;
	int m_percentFontNextX;

	int* specialPercentPrintX;
	int* specialPercentPrintY;
	//	CMyButtonGroup* m_menu;

	int m_changePercentPicFlag;
	int* m_percentPrintDelta;
	int m_useCharaPercentPrintDeltaFlag;


	char** m_charaVoiceFileName;

//..	CSuuji* m_suuji;
//	CBackButton* m_back;

	CSuuji* m_totalPercentSuuji;
	CSuuji* m_percentSuuji;
	CSuuji* m_percentSuuji0;
	CSuuji* m_percentSuuji100;

//	POINT GetButtonZahyo(int n);
	BOOL CheckOnButton(int n, int mouseX, int mouseY);
	int GetOnButton(int mouseX,int mouseY);

//	int m_buttonSizeX;
//	int m_buttonSizeY;

	int m_selectedNumber;
	int m_count;

	int m_maeSelectNumber;
	int m_nowSelectNumber;

	int m_length;
	int m_startupWait;

	void EraseChara(int n);
	void PrintChara(int n);

	POINT GetPicSrcZahyo(int n,BOOL eraseFlag = FALSE);

	int m_checkOnByPicFlag;


	virtual void BeforeInit(void) {}
	virtual void AfterInit(void) {}
	virtual void BeforeCalcu(void){}
	virtual void AfterCalcu(void){}
	virtual void BeforePrint(void){}
	virtual void AfterPrint(void){}

	int m_totalPercent;

	int* m_charaExistFlag;
	int* m_charaExistCheckPercent;
	int* m_charaExistCheckVar;

	int m_selectCommonCGCharaSound;

	CCGDataControl* m_cgDataControl;


private:
};



#endif
/*_*/

