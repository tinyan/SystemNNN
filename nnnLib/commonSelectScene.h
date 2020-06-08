//
// SelectScene.h
//

#if !defined __NNNLIB_COMMONSELECTSCENE__
#define __NNNLIB_COMMONSELECTSCENE__

class CCommonGeneral;
class CGameCallBack;

//class CBackButton;
//class CUpDownButtonGroup;
class CSuuji;
class CPagePrint;

class CMyMessage;

class CSceneVoice;
class CSceneList;
class CSceneDataControl;

class CCommonSelectScene : public CCommonGeneral
{
public:
	CCommonSelectScene(CGameCallBack* lpGame);
	virtual ~CCommonSelectScene();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	static char m_defaultBGFileName[];
	static char m_defaultAddFileName[];
	static char m_defaultFont1FileName[];
	static char m_defaultFont3FileName[];
	static char m_defaultCursorFileName[];

	static char m_defaultUpFileName[];
	static char m_defaultDownFileName[];
	static char m_defaultFutaFileName[];

	void CreateStartScreen(void);
	void FinalExitRoutine(void);

protected:
//	LPSTR m_filenameBG;
	LPSTR m_filenameAdd;
	int m_addPicFlag;
	int m_addPicPrintPercent;
	int m_addPicPrintX;
	int m_addPicPrintY;
	int m_addPicSizeX;
	int m_addPicSizeY;
	int m_addPicSrcKosuuX;
	int m_addPicSrcKosuuY;

	int m_blockKosuuX;
	int m_blockKosuuY;

	int m_sceneCharaKosuu;

	CSuuji* m_suuji;
//	CSuuji* m_suuji3;

//	CBackButton* m_back;
//	CUpDownButtonGroup* m_updown;
	CPicture* m_futaPic;
	int m_sceneCharaNumber;
	int m_sceneKosuu;

	CPicture* m_cursorPic;

	CPicture* m_addPic;
	CPicture** m_miniPic;
	int* m_miniPicState;

	int m_pageMax;
	int m_page;

	int m_kosuuPerPage;

	int m_count;

	int m_startupWait;
	int m_sceneVoiceNumber;
	int	m_yoyakuVoiceNumber;

	int m_nowSelectNumber;
	int m_maeSelectNumber;
	int m_selectedNumber;

	int m_printX;
	int m_printY;
	int m_nextX;
	int m_nextY;
	int m_sizeX;
	int m_sizeY;

	int m_picPrintX;
	int m_picPrintY;
	int m_picSizeX;
	int m_picSizeY;

	int m_cursorPrintX;
	int m_cursorPrintY;
	int m_cursorSizeX;
	int m_cursorSizeY;

	int m_fontSizeX1;
	int m_fontSizeY1;
	int m_fontNextX1;
//	int m_fontNextY1;

	int m_fontSizeX2;
	int m_fontSizeY2;
	int m_fontNextX2;
//	int m_fontNextY2;

	int m_fontSizeX3;
	int m_fontSizeY3;
	int m_fontNextX3;
//	int m_fontNextY3;

	int m_totalPercentPrintFlag;

	int m_totalPercentPrintX;
	int m_totalPercentPrintY;

//	int m_pagePrintFlag;
//	int m_pagePrintX;
//	int m_pagePrintY;


	int m_sceneFlag[200];
	int m_hSceneFlag[200];
	int m_voiceStartWait;

	int m_percent;

	void LoadBackCG(void);
	int GetOnScene(int mouseX,int mouseY);

	int m_length;

	int m_selectColorR;
	int m_selectColorG;
	int m_selectColorB;
	int m_selectPercent;
	int m_selectPrintMode;
	int m_cursorPrintType;

	int m_picMustPrintPercent;

	virtual void BeforeInit(void) {}
	virtual void AfterInit(void) {}
	virtual void BeforeCalcu(void){}
	virtual void AfterCalcu(void){}
	virtual void BeforePrint(void){}
	virtual void AfterPrint(void){}

	int m_superMode;
	int m_scenePianoSoundFlag;

	void PutAddPic(void);
	void PrintTotalPercent(void);
//	void PrintPage(void);

	void PrintAllMiniPic(void);
	CMyMessage* m_message;

	CPicture* m_suujiPic3;

	int m_futaPrintFlag;

	int m_smTransFlag;

	int m_selectSound;
	CSceneVoice* m_sceneVoice;
	CSceneList* m_sceneList;

	BOOL m_sceneCommandFlag;

//	int m_pageMaxPrintFlag;
//	int m_pageMaxPrintX;
//	int m_pageMaxPrintY;

//	int m_slashPrintFlag;
//	int m_slashPrintX;
//	int m_slashPrintY;

	void CheckSceneList(void);
	CSceneDataControl* m_sceneDataControl;

	CPagePrint* m_pagePrint;
	int m_exitStopVoiceFlag;
	int m_exitStopVoiceFadeOutTime;
	int m_backlogClearFlag;

	int m_overWriteLayerOff;
	int m_overwriteLayerOffVar;


	int m_menuStartCount;
	int m_menuStartWaitTime;
	int m_menuStartEffectTime;
	int m_menuStartEffectType;

	int m_appearCount;
	int m_appearCountMax;

	int GetStartWaitMode(void);
	void EndStartWaitMode(void);

};


#endif
/*_*/

