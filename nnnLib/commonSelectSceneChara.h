//
// SelectSceneChara.h
//

#if !defined __NNNLIB_COMMONSELECTSCENECHARA__
#define __NNNLIB_COMMONSELECTSCENECHARA__

class CCommonGeneral;
class CGameCallBack;
class CNameList;

class CSceneDataControl;

class CBackButton;
class CSuuji;

class CCommonSelectSceneChara : public CCommonGeneral
{
public:
	CCommonSelectSceneChara(CGameCallBack* lpGame);
	virtual ~CCommonSelectSceneChara();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	void CreateStartScreen(void);

protected:

	virtual void BeforeInit(void) {}
	virtual void AfterInit(void) {}
	virtual void BeforeCalcu(void){}
	virtual void AfterCalcu(void){}
	virtual void BeforePrint(void){}
	virtual void AfterPrint(void){}

private:
//	LPSTR m_filenameBG;
	LPSTR m_filenameButton;
	LPSTR m_filenameCursor;

	static char m_defaultBGFileName[];
	static char m_defaultButtonFileName[];
	static char m_defaultCursorFileName[];

	static char m_defaultFontFileName[];
	static char m_defaultHeartFileName[];

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
	int m_sceneCustomnPrintFlag;

	int m_basePrintX;
	int m_basePrintY;
	int m_baseNextX;
	int m_baseNextY;

	CPicture* m_cursorPic;

	POINT* m_zahyo;
	POINT GetZahyo(int n) {return m_zahyo[n];}


	void PrintCharaPercent(int n);
	int m_charaVoiceFlag;
	int m_sceneCharaKosuu;

	int m_sceneCustomPrintFlag;

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

//	CMyButtonGroup* m_menu;

	char** m_charaVoiceFileName;

//..	CSuuji* m_suuji;
//	CBackButton* m_back;

	CSuuji* m_totalPercentSuuji;
	CSuuji* m_percentSuuji;

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




	CPicture* m_heartPic;

	int m_kumiawaseFlag;

	int m_heartPrintFlag;

	int m_heartPrintX;
	int m_heartPrintY;
	int m_heartSizeX;
	int m_heartSizeY;

	POINT GetPicSrcZahyo(int n,BOOL eraseFlag = FALSE);

	int m_checkOnByPicFlag;

	void PrintCharaHeart(int n);

	int* m_sceneHMode;
	int m_totalPercent;

	CSceneDataControl* m_sceneDataControl;

};

#endif
/*_*/

