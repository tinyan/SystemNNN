

#if !defined __MUSHIEX_CHARTMENU__
#define __MUSHIEX_CHARTMENU__


class CCommonGeneral;
//class CGame;
class CChartList;
class CPicture;

class CSuuji;

class CMyMessage;
class CCommonRadioButtonGroup;
class CCommonButtonGroup;

class CCommonAnimeParts;

class CCommonChartMenu : public CCommonGeneral
{
public:
	CCommonChartMenu(CGameCallBack* lpGame);
	~CCommonChartMenu();
	void End(void);

	int Init(void);
	int Calcu(void);
	int Print(void);

	void SetChartNumber(int n){m_chartNumber = n;}
	int GetChartNumber(void){return m_chartNumber;}

	void SetNowSlotNumber(int slot);
	int GetNowSlotNumber(void){return m_nowSlotNumber;}

	int CheckEvent(int slot);
	int CheckComplete(int slot);
	void SetMita(int slot,int k = 0);

	void InitSelectOk(void);
	void InitMoveRoad(void);

//	BOOL GetExtDataForSave(LPVOID ptr);
//	BOOL SetExtDataByLoad(LPVOID ptr);

	void GetExtDataForSave(LPVOID ptr,int extNumber);
	void SetExtDataByLoad(LPVOID ptr,int extNumber);

	static char m_defaultCompName[];
	BOOL CheckSelectOk(int slot);
	BOOL CheckSelectOk2(int slot);
	void SetSelectOk(int slot,BOOL flg = TRUE);
	BOOL GetSelectOk(int slot);

	static int m_defaultLineColor[];

	void FinalExitRoutine(void);
	static char m_defaultDialogFileName[];
	static char m_buttonName[][16];

	void AfterPrint(void);

//	void CheckAllMitaFunction(void);


	void StartUserCommand(int paraKosuu,int* paraPtr);

//	void FunctionGetChartPercent(int chart);
//	void FunctionOpenChart(int chart,int flg = 1);


	void Function(int type,int paraKosuu,int* lpParam);
	void ExitGame(void);

	void AfterInitNewGame(void);


	void InitByLoad(void);

protected:

//	CGame* m_game2;
	int m_chartListKosuu;
	int m_blockSize;

	static char m_defaultSlotVarName[];
	static char m_defaultFromVarName[];
	static char m_defaultPrintVarName[];

	static char m_defaultChartOpenVarName[];
	static char m_defaultSlotTag[];
	static char m_defaultMesWinName[];
	static char m_defaultOnCursorName[];
	static char m_defaultNowChartName[];
	static char m_defaultTasseidoName[];
	static char m_defaultChartFontName[];
	static char m_defaultNotLookName[];
	static char m_defaultMiniMapName[];
	static char m_defaultMiniMapBaseName[];
	static char m_defaultMiniMapWindowName[];
	static char m_defaultChartPercentVarName[];
	static char m_defaultCheckCompVarName[];
	static char m_defaultCaptureName[];

	static char m_defaultNewChartFlagVarName[];


	static char m_defaultBackTag[];
	static char m_defaultCenterTag[];


	static char m_defaultSetRouteFunctionName[];
	static char m_defaultGetChartPercentFunctionName[];
	static char m_defaultCheckCompSlotFunctionName[];
	static char m_defaultOpenChartFunctionName[];
	static char m_defaultSlotOnFunctionName[];
	static char m_defaultSlotOpenFunctionName[];


	int m_chartPercentVarNumber;
	int m_checkCompVarNumber;

	int m_newMarkVarNumber;
	int m_newMarkPrintFlag;

	int m_newMarkFlag;

	int m_chartOpenVar;

	char* m_moveRoad;
	int* m_canSelect;

	BOOL CheckChartOpen(int block);
	BOOL CheckExistClickOk(int block);
//	void SetChartOpen(int block,BOOL flg = TRUE);




	int* m_backPicKosuu;
	int* m_backPicSizeY;
	int* m_chartPicKosuu;

	int m_centerPicLayer;
	int m_chartPicMax;
	CPicture** m_chartPic;
	CPicture** m_backChara;
	CChartList** m_chart;

	int m_picKosuuMax;

	CPicture* m_centerPic;


	BOOL LoadChartPic(int chart,int n);
	BOOL LoadStartPic(void);
	void LoadMiniMapBasePic(int n);


	LPSTR m_chartSlotTag;


	int m_chartNumber;
	int m_printChartNumber;

	void LoadBackChara(int n);
	void LoadCenterPic(int n);
	void LoadChartPic(int n);



	int m_tasseidoBasePrintX;
	int m_tasseidoBasePrintY;

	int m_tasseidoPrintX;
	int m_tasseidoPrintY;
	int m_totalTasseidoPrintX;
	int m_totalTasseidoPrintY;





	int m_scrollX;
	int m_scrollY;

	int m_scrollSize;

	void PrintBackChara(void);
	void PrintCenter(void);

//	CPicture* m_chartMapButtonPic;

//	POINT GetChartMapButtonZahyo(int n);
//	void PrintChartMapButton(int n,int md = 0);
//	void PutChartMapButton(int putX,int putY, int n, int md = 0);

	int m_buttonSizeX;
	int m_buttonSizeY;

//	int m_chartMapButtonSizeX;
//	int m_chartMapButtonSizeY;

//	int m_chartMapButtonPrintX;
//	int m_chartMapButtonPrintY;

//	int m_chartMapButtonNextX;
//	int m_chartMapButtonNextY;

	void PrintAllChartLine(void);
	void PrintAllChartMapButton(void);
	void PrintAllButton(void);
	void EraseAllButton(void);
	
	//	int m_onChartMapNumber;
	int m_onButtonNumber;

	int m_buttonPicKosuuX;
	int m_buttonPicKosuuY;
	int m_buttonPicKosuu;

	int m_nowSlotNumber;

	POINT ToScreenZahyo(POINT pt);
	BOOL CheckInScreen(POINT pt);
	BOOL CheckInScreenLine(POINT pt);
	void PrintButton(POINT pt,int slot,int md = 0,BOOL ok = TRUE);
	void EraseButton(POINT pt,int md = 0,BOOL ok = TRUE);

	void CheckOnChartMapButton(POINT pt);
	void CheckOnButton(POINT pt);
	void CheckOnButton2(POINT pt);

	int GetOnDescOkButton(POINT pt);

	void PrintLine(POINT pt,POINT pt2,int md=0);
	void PrintDesc(int md = 0);
	int m_descPrintNumber;

	CMyMessage* m_message;
	int m_slotNumberVarNumber;
	int m_fromNumberVarNumber;
	int m_printNumberVarNumber;

//	int m_printChartVarNumber;
	int* m_mita;
	char* m_tsuka;
	
//	int m_mitaKosuu[10];
	int* m_mitaKosuu;



	void CountMita(int chart);
	void CountTotalMita(void);
//	void SetMitaToVar(int chart);
//	void SetTotalMitaToVar(void);

//	int m_totalMitaPercentVarNumber;
//	int m_mitaPercentVarNumber[10];
//	int m_openButtonVarNumber[10];

	int* m_mitaPercent;
	int m_totalMitaPercent;
	void CalcuMitaPercent(void);




	int m_bitPattern[32];

	void LoadMita(void);
	void SaveMita(void);
	void LoadTsuka(void);
	void SaveTsuka(void);

	int m_totalMitaKosuu;
	int* m_eventKosuu;
	int m_totalEventKosuu;

//	int* m_cannotSelect;
//	int m_mitaYoyakuVarNumber;


	CPicture* m_compPic;
	POINT m_compDelta;
	SIZE m_compSize;

	void PutCompPic(POINT pt,int md=0,int ps = 100,int k = 0,BOOL ok = TRUE);
	void MakeAllTable(void);

	int* m_compTable;

	BOOL CheckComp(int slot);
	BOOL CheckRouteMita(int slot,int k);
	BOOL CheckMita(int slot);

	int m_editMode;

	int CalcuEdit2(void);
	int m_editCatchNumber;
	int m_editSaveNumber;
	int m_editSaveCount;

	void PrintEditStatus2(void);
	POINT m_editStartPoint;
	POINT m_editCatchStart;

	POINT m_compNext;
	int m_compPercent;
	CPicture* m_messageWindowPic;
	int m_messageUpDown;
	SIZE m_messageWindowSize;
	POINT m_messageWindowZahyo[2];
	POINT m_messageZahyo[2];
	void CheckWindowUpDown(POINT pt);

	CPicture* m_onCursorPic;
	CPicture* m_notLookPic;
	CPicture* m_miniMapButtonPic;
	CPicture* m_miniMapBasePic;
	CPicture* m_miniMapWindowPic;

	int m_lineColor[5*3];

	int m_miniMapTenmetsuColor;
	int m_miniMapTenmetsuCount;
	int m_miniMapTenmetsuTime;

	void PutMiniMapButton(POINT pt,int n);
	void CalcuMiniMapButtonAnime(void);

	POINT ToMiniMapZahyo(POINT pt);
	void PrintAllMiniButton(void);
	void PrintMiniMapBase(void);
	void PrintMiniMapWindow(void);
	void PutMiniMapWindow(POINT pt,int windowSizeY = 60);
	void PutMiniMapWindowSub(POINT pt,POINT src,SIZE size);

	int m_miniWindowTenmetsuCount;
	int m_miniWindowTenmetsuTime;
	int m_miniWindowPercent;
	int m_miniWindowPercent1;
	int m_miniWindowPercent2;

	int GetMoveRoad(int slot);
	void SetMoveRoad(int slot,int n);

	BOOL CheckTsuka(int slot,int n);
	void SetTsuka(int slot,int n);
	BOOL m_exitModeFlag;

	void CalcuMiniWindowSize(void);

	void CalcuScrollZahyo(void);
	void CalcuMiniWindowZahyo(void);
	int m_miniWindowZahyoY;

	int m_captureFlag;
	int m_captureStartX;
	int m_captureStartY;

	int GetOnMiniWindow(POINT pt);
	void AdjustInScroll(void);
	int m_scrollSpeedY;

	int m_miniWindowSize;
//	POINT m_miniWindowAreaZahyo;
	int m_miniWindowZahyoStartY;
	CCommonRadioButtonGroup* m_growButton;

	void InitChangePage(void);
	void ReLoadGrowPic(void);

	CPicture* m_chartMapNowPic;
	void PrintPlayMap(void);
//	int m_playMapNumber;

//	int m_genzaichiVarNumber;
//	int m_lastSelectVarNumber;

	CPicture* m_tasseidoBasePic;
	CSuuji* m_suuji;
	void PrintTasseido(void);


	int m_selectNumber;

	int m_selectSound;
	int m_overSound;
	int m_maeOnSlot;

	int m_fromSlotNumber;
	
	POINT* m_buttonZahyo;

//	POINT m_buttonZahyo[9][2];

	int m_buttonMulti;
	int m_buttonMultiMax;
	int m_buttonCount;
	int m_buttonCountMax;

	int m_selectButtonMulti;
	int m_selectButtonMulti2;

	int m_lineColorCount;
	int m_lineColorCountMax;

	void CalcuButtonMulti(void);
	void CalcuLineColor(void);

	void SaveChartData(BOOL changeModeFlag = TRUE);
	void LoadChartData(int slot);
	void MakeHeader(int* work, int sz, int cd, LPSTR mes);

	int m_basicChartKosuu;
	int m_allClickFlag;

	int m_chartAngouFlag;

	CCommonButtonGroup* m_dialogButton;

	int m_warningPrintFlag;
	int m_warningFlag;
	int m_dialogX;
	int m_dialogY;

	int m_dialogSizeX;
	int m_dialogSizeY;
	LPSTR m_dialogFileName;

	int CalcuWarning(void);
	int m_warningSound;
	//int m_scrollSpeedX[10];
	int* m_scrollSpeedX;

	int m_catchFlag;

	int CalcuCatch(void);
	int m_catchNumber;
	POINT m_catchStartPoint;
	POINT m_catchStart;

	BOOL m_reloadDataFlag;

	int m_moveRoadSize;
	int m_canSelectSize;

	int* m_ok;

	int m_picLoadByBackScript;

	int m_compTableBufferSize;
	int m_mitaBufferSize;
	int m_tsukaBufferSize;

	int m_bottomSpace;

	void LoadWarningPic(void);
	int m_miniMapButtonSizeX;
	int m_miniMapButtonSizeY;

	int m_slotAreaStartX;
	int m_slotAreaStartY;
	int m_slotAreaSizeX;
	int m_slotAreaSizeY;

	LPSTR* m_miniMapBaseName;
	POINT* m_miniMapBaseZahyo;
	POINT* m_miniMapZahyo;
	SIZE* m_miniMapSize;


	int m_miniMapWindowPrintX;
	int m_miniMapWindowPrintY;
	int m_miniMapWindowUpSize;
	int m_miniMapWindowCenterSize;
	int m_miniMapWindowDownSize;

	POINT GetMiniMapBaseZahyo(void);
	POINT GetMiniMapAreaZahyo(void);
	POINT GetMiniMapWindowZahyo(void);
	POINT GetNowMiniMapZahyo(void);


	int GetBackSize(void);

	int m_centerMulti;
	int m_descFontSize;
	int m_descNextY;
	int m_descColorR;
	int m_descColorG;
	int m_descColorB;

	int m_miniMapWindowSizeX;


	void SetSlotNumber(int slot);
	void SetFromSlot(int slot);
	int GetSlotNumber(void);
	int GetFromNumber(void);
	int SlotToChart(int slot);
	int SearchRoad(int fromSlot,int toSlot);
	int GetRoadKosuu(int fromSlot);
	int GetRouteKosuu(int slot);


	void FunctionSetMita(int route);
	void FunctionGetChartPercent(int chart);
	void FunctionCheckCompSlot(void);
	void FunctionOpenChart(int chart);
	void FunctionSlotOn(int slot,int flg = 1);
	void FunctionSlotOpen(int slot);


	void OpenChart(int n);

	int m_mainCaptureOk;
	void AdjustMiniWindowZahyo(void);
	CPicture* m_mainCapturePic;
	POINT m_mainCapturePicDelta;

	int m_mainWindowCaptureStartX;
	int m_mainWindowCaptureStartY;
	BOOL CheckInSlotArea(POINT pt);

	void PrintCapturePic(void);
	int m_mainCaptureReverse;
	int m_dontRightMove;

	int m_autoNextOn;

	void JumpToMiniWindow(void);
	int m_autoJumpMiniWindow;

	int m_eraseButtonFlag;

	int m_debugDontPrintButton;

	int m_selectSlotTransPercent;
	int m_selectOkSlotTransPercent;

	LPSTR m_backTag;
	LPSTR m_centerTag;

	void PrintNewMark(int n);
	void AnimeNewMark(void);

	int m_newMarkPrintX;
	int m_newMarkPrintY;

	CCommonAnimeParts* m_newMarkAnimeParts;

	int m_savePrintChartFlag;
	void CheckAndSetPrintChartNumber(void);
	void CheckAndGetPrintChartNumber(void);

//	int m_printChartNumberTmp;


};






#endif
/*_*/

