


#include <windows.h>

#include "..\..\systemNNN\nyanlib\include\commonMacro.h"
#include "..\..\systemNNN\nyanlib\include\areaControl.h"
#include "..\..\systemNNN\nyanlib\include\picture.h"
#include "..\..\systemNNN\nyanlib\include\myGraphics.h"
#include "..\..\systemNNN\nyanlib\include\allGeo.h"

#include "..\..\systemNNN\nnnLib\commonGeneral.h"
#include "..\..\systemNNN\nnnLib\gameCallBack.h"

#include "..\..\systemNNN\nnnUtilLib\myMouseStatus.h"
#include "..\..\systemNNN\nnnUtilLib\nnnButtonStatus.h"
#include "..\..\systemNNN\nnnUtilLib\mymessage.h"

#include "..\..\systemNNN\nnnUtilLib\commonButton.h"
#include "..\..\systemNNN\nnnUtilLib\commonButtonGroup.h"
#include "..\..\systemNNN\nnnUtilLib\commonMultiStateButton.h"
#include "..\..\systemNNN\nnnUtilLib\commonRadioButton.h"

#include "..\..\systemNNN\nnnUtilLib\superButtonPicture.h"
#include "..\..\systemNNN\nnnUtilLib\commonRadioButtonGroup.h"

#include "..\..\systemNNN\nnnUtilLib\commonAnimeParts.h"

#include "..\..\systemNNN\nnnUtilLib\mySaveFolder.h"

#include "..\..\systemNNN\nyanEffectLib\effectstruct.h"


#include "..\..\systemNNN\nnnUtilLib\suuji.h"

#include "..\..\systemNNN\nnnlib\commonMode.h"

#include "..\..\systemNNN\nnnlib\commonDataFile.h"

//#include "mode.h"

#include "gameCallback.h"

#include "..\..\systemNNN\nnnUtilLib\chartList.h"
#include "commonchartMenu.h"

//#define CHARTMENU_MODE 98
//dummy



#define SLOTBUTTON_NORMAL 0
#define SLOTBUTTON_ON 1
#define SLOTBUTTON_CANNOT 2
#define SLOTBUTTON_NOW 3

#define MAPBUTTON_NORMAL 0
#define MAPBUTTON_ON 1
#define MAPBUTTON_CANNOT 2
#define MAPBUTTON_NOW 3



//用語定義
//next slot->slot roadとして処理
//route:内部分岐
//


char CCommonChartMenu::m_defaultChartOpenVarName[]="チャートオープン情報";


int CCommonChartMenu::m_defaultLineColor[]=
{
	128,180,255, 36,99,192, 62,85,101, 191,217,255, 72,148,255
};

char CCommonChartMenu::m_defaultCompName[]="ta_compmark";
char CCommonChartMenu::m_defaultMesWinName[]="ta_chart_meswin1";
char CCommonChartMenu::m_defaultOnCursorName[]="ta_chart_buttoncur";
char CCommonChartMenu::m_defaultNowChartName[]="ta_chartmap_cur01";
char CCommonChartMenu::m_defaultTasseidoName[]="ta_chart_comp";
char CCommonChartMenu::m_defaultChartFontName[]="ta_chart_font01";
char CCommonChartMenu::m_defaultNotLookName[]="ta_chart_button0";
char CCommonChartMenu::m_defaultMiniMapName[]="ta_chart_minimap01";
char CCommonChartMenu::m_defaultMiniMapBaseName[]="ta_chart_minimap02";
char CCommonChartMenu::m_defaultMiniMapWindowName[]="ta_chart_minimap03";
char CCommonChartMenu::m_defaultCaptureName[]="ta_capture";



char CCommonChartMenu::m_defaultSetRouteFunctionName[] ="setroute";
char CCommonChartMenu::m_defaultGetChartPercentFunctionName[] ="getchartpercent";
char CCommonChartMenu::m_defaultCheckCompSlotFunctionName[] ="checkcompslot";
char CCommonChartMenu::m_defaultOpenChartFunctionName[] ="openchart";
char CCommonChartMenu::m_defaultSlotOnFunctionName[] ="sloton";
char CCommonChartMenu::m_defaultSlotOpenFunctionName[] ="slotopen";


char CCommonChartMenu::m_defaultDialogFileName[] = "ta_dialog_4";
char CCommonChartMenu::m_buttonName[][16]=
{
	"dialogOk","dialogCancel"
};


char CCommonChartMenu::m_defaultSlotTag[] = "ta_chart_button";
char CCommonChartMenu::m_defaultBackTag[] = "chart_back";
char CCommonChartMenu::m_defaultCenterTag[] = "ta_chart_center";



char CCommonChartMenu::m_defaultSlotVarName[]="チャートスロット番号";
char CCommonChartMenu::m_defaultFromVarName[]="ワークスロット番号";	//内部使用

char CCommonChartMenu::m_defaultPrintVarName[]="ワークスロット番号２";	//内部使用


char CCommonChartMenu::m_defaultChartPercentVarName[] = "answer";
char CCommonChartMenu::m_defaultCheckCompVarName[] = "answer";
char CCommonChartMenu::m_defaultNewChartFlagVarName[] = "newchartflag";


//	m_mitaYoyakuVarNumber = m_game->GetVarNumber("見た予約");
//	m_genzaichiVarNumber = m_game->GetVarNumber("現在地");
//	m_lastSelectVarNumber = m_game->GetVarNumber("最終選択地");
//	m_slotNumberVarNumber = m_game->GetVarNumber("スロット番号");
//	m_printChartVarNumber = m_game->GetVarNumber("今表示しているマップ");

//map-button
//basic
//

//sav/chart[n]
//


//CChartList::GetRouteKosuu()は、内部分岐の個数




//mita:system情報
//route:play情報
//



//開始時 slot=0,from=0
//->
//slot=1,mita(slot),from=1

//exitgame
//if all mita(slot)
//route from->slot if exist route

//command
//route from->slot if exist route
//from=slot
//if all mita(slot)

CCommonChartMenu::CCommonChartMenu(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	int i;
	//m_game2 = lpGame;
	SetClassNumber(SELECTCHART_MODE);
//	m_classNumber = SELECTCHART_MODE;

	LoadSetupFile("selectchart");

	m_reloadDataFlag = FALSE;
	m_commonBuffer = m_game->GetCommonBuffer();

	GetBackExecSetup();

	int bit = 1;
	for (i=0;i<31;i++)
	{
		m_bitPattern[i] = bit;
		bit <<= 1;
	}
	m_bitPattern[31] = 0x80000000;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	m_picLoadByBackScript = 0;
	if (m_backScriptFlag)
	{
		GetInitGameParam(&m_picLoadByBackScript,"picLoadBackScript");
	}


	m_chartAngouFlag = 0;
	GetInitGameParam(&m_chartAngouFlag,"chartAngouFlag");

	m_chartListKosuu = 1;
	GetInitGameParam(&m_chartListKosuu,"chartListNumber");

	int chartDescMax = 3;
	GetInitGameParam(&chartDescMax,"chartDescMax");
	CChartList::SetDescMax(chartDescMax);


	m_basicChartKosuu = m_chartListKosuu;
	GetInitGameParam(&m_basicChartKosuu,"basicChartNumber");

	m_dontRightMove = 0;
	GetInitGameParam(&m_dontRightMove,"dontRightMove");

	m_mainCaptureOk = 1;
	GetInitGameParam(&m_mainCaptureOk,"mainCaptureOk");

	m_autoNextOn = 0;
	GetInitGameParam(&m_autoNextOn,"autoNextOn");

	m_autoJumpMiniWindow = 1;
	GetInitGameParam(&m_autoJumpMiniWindow,"autoJumpMiniWindow");

	m_eraseButtonFlag = 1;
	GetInitGameParam(&m_eraseButtonFlag,"eraseButtonBack");

//for debug only
m_debugDontPrintButton = 0;
GetInitGameParam(&m_debugDontPrintButton,"debugDontPrintButton");

	m_mainCapturePic = NULL;
	if (m_mainCaptureOk)
	{
		LPSTR capname = m_defaultCaptureName;
		GetInitGameString(&capname,"filenameCapturePic");
		if (capname != NULL)
		{
			if ((*capname) != 0)
			{
				char filename[256];
				wsprintf(filename,"sys\\%s",capname);
				m_mainCapturePic = new CPicture(filename);

				int deltaX = 0;
				int deltaY = 0;
				GetInitGameParam(&deltaX,"capturePrintX");
				GetInitGameParam(&deltaY,"capturePrintY");

				m_mainCapturePicDelta.x = deltaX;
				m_mainCapturePicDelta.y = deltaY;
			}
		}

		m_mainCaptureReverse = 1;
		int rev = 0;
		GetInitGameParam(&rev,"captureReverse");
		if (rev)
		{
			m_mainCaptureReverse = -1;
		}
	}


	m_blockSize = 1000;
	GetInitGameParam(&m_blockSize,"chartBlockSize");

	m_ok = new int[m_blockSize ];

	m_chartSlotTag = m_defaultSlotTag;
	GetInitGameString(&m_chartSlotTag,"tagNameChartSlot");

	m_backTag = m_defaultBackTag;
	GetInitGameString(&m_backTag,"tagNameBack");
	m_centerTag = m_defaultCenterTag;
	GetInitGameString(&m_centerTag,"tagNameCenter");


	m_chartOpenVar = -1;
	if (m_chartListKosuu > m_basicChartKosuu)
	{
		LPSTR chartOpenVarName = m_defaultChartOpenVarName;
		GetInitGameString(&chartOpenVarName,"chartOpenVar");
		m_chartOpenVar = m_game->GetVarNumber(chartOpenVarName);
	}

	m_centerMulti = 200;
	GetInitGameParam(&m_centerMulti,"centerMulti");

	LPSTR chartPercentVarName = m_defaultChartPercentVarName;
	GetInitGameString(&chartPercentVarName,"chartPercentVarName");
	m_chartPercentVarNumber = -1;
//	m_chartPercentVarNumber = m_game->GetVarNumber(chartPercentVarName);

	LPSTR checkCompVarName = m_defaultCheckCompVarName;
	GetInitGameString(&checkCompVarName,"checkCompVarName");
	m_checkCompVarNumber = -1;

	m_newMarkPrintFlag = 0;
	GetInitGameParam(&m_newMarkPrintFlag,"newMarkPrintFlag");
	m_newMarkAnimeParts = NULL;
	if (m_newMarkPrintFlag)
	{
		LPSTR newMarkVarName = m_defaultNewChartFlagVarName;
		GetInitGameString(&newMarkVarName,"newMarkVarName");
		m_newMarkVarNumber = m_game->GetVarNumber(newMarkVarName);

		m_newMarkPrintX = 0;
		m_newMarkPrintY = 0;
		GetInitGameParam(&m_newMarkPrintX,"newMarkPrintX");
		GetInitGameParam(&m_newMarkPrintY,"newMarkPrintY");

		//anime parts
		m_newMarkAnimeParts = new CCommonAnimeParts("newmark",m_setup);
	}


	//ボタンエリア位置X
	//ボタンエリアサイズX
	m_slotAreaStartX = 200;
	GetInitGameParam(&m_slotAreaStartX,"slotAreaStartX");
	m_slotAreaSizeX = screenSizeX - m_slotAreaStartX;
	GetInitGameParam(&m_slotAreaSizeX,"slotAreaSizeX");

	m_slotAreaStartY = 0;
	GetInitGameParam(&m_slotAreaStartY,"slotAreaStartY");
	m_slotAreaSizeY = screenSizeY - m_slotAreaStartY;
	GetInitGameParam(&m_slotAreaSizeY,"slotAreaSizeY");

	m_selectSlotTransPercent = 80;
	m_selectOkSlotTransPercent = 80;
	GetInitGameParam(&m_selectSlotTransPercent,"selectSlotTransPercent");
	GetInitGameParam(&m_selectOkSlotTransPercent,"selectOkSlotTransPercent");


	m_bottomSpace = 60;
	GetInitGameParam(&m_bottomSpace,"bottomSpace");

	int sz = m_blockSize*m_chartListKosuu;
	int szz = (sz + 15) & (~15);//16byte padding
	m_moveRoadSize = szz;
	m_moveRoad = new char[m_moveRoadSize];
	for (i=0;i<m_moveRoadSize;i++)
	{
		m_moveRoad[i] = 0;
	}

	sz = (m_blockSize * m_chartListKosuu + 31) / 32;
	szz = (sz + 3) & (~3);
	m_canSelectSize = szz;
	m_canSelect = new int[m_canSelectSize];//16byte padding
	for (i=0;i<szz;i++)
	{
		m_canSelect[i] = 0xffffffff;
	}

	LPSTR fullFolder = CMySaveFolder::GetFullFolder();
	for (i=0;i<m_chartListKosuu;i++)
	{
		char dirname[256];
		wsprintf(dirname,"%s\\chart%d",fullFolder,i+1);
		CreateDirectory(dirname,NULL);
	}

	m_editMode = 0;
	GetInitGameParam(&m_editMode,"editMode");	//


	m_chart = new CChartList*[m_chartListKosuu];

	for (i=0;i<m_chartListKosuu;i++)
	{
		m_chart[i] = new CChartList(i,m_chartAngouFlag);
		int kosuu = m_chart[i]->GetSlotKosuu();
		for (int k=0;k<kosuu;k++)
		{
			int slot = m_chart[i]->GetSlot(k);
			LPSTR varName = m_chart[i]->GetVarName(slot);
			if (varName != NULL)
			{
				int varNumber = m_game->GetVarNumber(varName);
				if (varNumber != -1)
				{
					m_chart[i]->SetVarNumber(slot,varNumber);
				}
			}
		}
	}

	for (int i=0;i<m_chartListKosuu;i++)
	{
		int kosuu = m_chart[i]->GetSlotKosuu();
		for (int k=0;k<kosuu;k++)
		{
			int slot = m_chart[i]->GetSlot(k);
			int nextKosuu = m_chart[i]->GetNextKosuu(slot);
			for (int p=0;p<nextKosuu;p++)
			{
				int nextSlot = m_chart[i]->GetNext(slot,p);
				int chart2 = SlotToChart(nextSlot);
				m_chart[chart2]->SetNotTop(nextSlot);
			}
		}
	}

	int backPicKosuu = 2;
	GetInitGameParam(&backPicKosuu,"backPicNumberCommon");
	int backPicSizeY = screenSizeY * backPicKosuu;
	GetInitGameParam(&backPicSizeY,"backPicSizeY");

	m_backPicKosuu = new int[m_chartListKosuu];
	m_backPicSizeY = new int[m_chartListKosuu];
	

	m_picKosuuMax = 1;

	for (int i=0;i<m_chartListKosuu;i++)
	{
		char name[256];
		wsprintf(name,"backPicNumber%d",i+1);
		int picKosuu2 = backPicKosuu;
		int backPicSizeY2 = backPicSizeY;

		if (GetInitGameParam(&picKosuu2,name))
		{
			if (picKosuu2 < 1) picKosuu2 = 1;
//			if (picKosuu2 > 4) picKosuu2 = 4;

			backPicSizeY2 = picKosuu2 * screenSizeY;
		}
		else
		{
			wsprintf(name,"backPicSizeY%d",i+1);

			if (GetInitGameParam(&backPicSizeY2,name))
			{
				picKosuu2 = (backPicSizeY2+screenSizeY-1) / screenSizeY;

				if (picKosuu2 < 1) picKosuu2 = 1;
//				if (picKosuu2 > 4) picKosuu2 = 4;
			}
		}
		
		if (picKosuu2 < 1) picKosuu2 = 1;
//		if (picKosuu2 > 4) picKosuu2 = 4;

		if (picKosuu2 > m_picKosuuMax) m_picKosuuMax = picKosuu2;

		m_backPicKosuu[i] = picKosuu2;
		m_backPicSizeY[i] = backPicSizeY2;
	}


	m_centerPicLayer = 5;
	m_centerPic = NULL;
	GetInitGameParam(&m_centerPicLayer,"centerPicLayer");
	

	m_buttonSizeX = 200;
	m_buttonSizeY = 50;
	GetInitGameParam(&m_buttonSizeX,"slotSizeX");
	GetInitGameParam(&m_buttonSizeY,"slotSizeY");



	//1-1をよみこんでサイズ確定
	int seatPicSizeX = screenSizeX;
	int seatPicSizeY = screenSizeY;


	if (LoadStartPic())
	{
		SIZE sz = m_commonParts->GetPicSize();
		seatPicSizeX = sz.cx;
		seatPicSizeY = sz.cy;
	}

	m_buttonPicKosuuX = seatPicSizeX / m_buttonSizeX;
	m_buttonPicKosuuY = seatPicSizeY / m_buttonSizeY;
	m_buttonPicKosuu = m_buttonPicKosuuX * m_buttonPicKosuuY;














	m_chartPicKosuu = new int[m_chartListKosuu];
	for (int i=0;i<m_chartListKosuu;i++)
	{
		int slotMax = m_chart[i]->GetMaxSlot();
		slotMax -= i*m_blockSize;
		slotMax += 1;

		m_chartPicKosuu[i] = (slotMax+m_buttonPicKosuu-1) / m_buttonPicKosuu;
	}



	int cmax = m_chartPicKosuu[0];
	for (i=0;i<m_chartListKosuu;i++)
	{
		if (m_chartPicKosuu[i] > cmax) cmax = m_chartPicKosuu[i];
	}

	m_chartPicMax = cmax;
	m_chartPic = new CPicture*[m_chartPicMax];

	for (i=0;i<cmax;i++)
	{
		m_chartPic[i] = new CPicture();
	}




	LPSTR name = m_defaultCompName;
	GetInitGameString(&name,"fileNameComp");
	char filename[256];
	wsprintf(filename,"sys\\%s",name);
	m_compPic = new CPicture(filename);
	
	if (1)
	{
		SIZE sz = m_compPic->GetPicSize();

		int deltaX = 60;
		int deltaY = 5;
		int sizeX = sz.cx;
		int sizeY = sz.cy;

		GetInitGameParam(&deltaX,"compPrintX");
		GetInitGameParam(&deltaY,"compPrintY");
		GetInitGameParam(&sizeX,"compSizeX");
		GetInitGameParam(&sizeY,"compSizeY");
		
		int nextX = sizeX;
		int nextY = 0;
		GetInitGameParam(&nextX,"compNextX");
		GetInitGameParam(&nextY,"compNextY");

		m_compDelta.x = deltaX;
		m_compDelta.y = deltaY;
		m_compSize.cx = sizeX;
		m_compSize.cy = sizeY;
		m_compNext.x = nextX;
		m_compNext.y = nextY;

		m_compPercent = 20;
		GetInitGameParam(&m_compPercent,"compPercent");
	}


	m_growButton = new CCommonRadioButtonGroup(m_setup,"grow",NULL,m_chartListKosuu,NULL);
	for (i=0;i<m_chartListKosuu;i++)
	{
		CPicture* lpPic = CSuperButtonPicture::GetPicture(i+2);
		m_growButton->SetPicture(lpPic,i,-1);
	}

	m_allClickFlag = 1;
	GetInitGameParam(&m_allClickFlag,"allClickOk");




	m_mitaKosuu = new int[m_chartListKosuu];
	m_mitaPercent = new int[m_chartListKosuu];
	for (int i=0;i<m_chartListKosuu;i++)
	{
		m_mitaPercent[i] = 0;
	}




//	m_totalMitaPercentVarNumber = m_game->GetVarNumber("コンプ・ＭＡＰＴＯＴＡＬ");
//	m_mitaPercentVarNumber[1] = m_game->GetVarNumber("コンプ・ＭＡＰ１");
//	m_mitaPercentVarNumber[2] = m_game->GetVarNumber("コンプ・ＭＡＰ２");
//	m_mitaPercentVarNumber[3] = m_game->GetVarNumber("コンプ・ＭＡＰ３");
//	m_mitaPercentVarNumber[4] = m_game->GetVarNumber("コンプ・ＭＡＰ４");
//	m_mitaPercentVarNumber[5] = m_game->GetVarNumber("コンプ・ＭＡＰ５");
//	m_mitaPercentVarNumber[6] = m_game->GetVarNumber("コンプ・ＭＡＰ６");
//	m_mitaPercentVarNumber[7] = m_game->GetVarNumber("コンプ・ＭＡＰ７");
//	m_mitaPercentVarNumber[8] = m_game->GetVarNumber("コンプ・ＭＡＰ８");
//	m_mitaPercentVarNumber[9] = m_game->GetVarNumber("コンプ・ＭＡＰ９");

//	m_openButtonVarNumber[1] = m_game->GetVarNumber("ＯＮ・チャートマップ１");
//	m_openButtonVarNumber[2] = m_game->GetVarNumber("ＯＮ・チャートマップ２");
//	m_openButtonVarNumber[3] = m_game->GetVarNumber("ＯＮ・チャートマップ３");
//	m_openButtonVarNumber[4] = m_game->GetVarNumber("ＯＮ・チャートマップ４");
//	m_openButtonVarNumber[5] = m_game->GetVarNumber("ＯＮ・チャートマップ５");
//	m_openButtonVarNumber[6] = m_game->GetVarNumber("ＯＮ・チャートマップ６");
//	m_openButtonVarNumber[7] = m_game->GetVarNumber("ＯＮ・チャートマップ７");
//	m_openButtonVarNumber[8] = m_game->GetVarNumber("ＯＮ・チャートマップ８");
//	m_openButtonVarNumber[9] = m_game->GetVarNumber("ＯＰＥＮ・チャートマップ９");



//	m_mitaYoyakuVarNumber = m_game->GetVarNumber("見た予約");
//	m_genzaichiVarNumber = m_game->GetVarNumber("現在地");
//	m_lastSelectVarNumber = m_game->GetVarNumber("最終選択地");





//	int m_compTableBufferSize;
//	int m_mitaBufferSize;
//	int m_tsukaBufferSize;


	m_mitaBufferSize = (m_blockSize * m_chartListKosuu + sizeof(int) - 1) / sizeof(int);
	m_mita = new int[m_mitaBufferSize];
	ZeroMemory(m_mita,sizeof(int)*m_mitaBufferSize);
	LoadMita();

	m_tsukaBufferSize = m_blockSize * m_chartListKosuu;
	m_tsuka = new char[m_tsukaBufferSize];
	ZeroMemory(m_tsuka,sizeof(char)*m_tsukaBufferSize);
	LoadTsuka();

	m_compTableBufferSize = (m_blockSize * m_chartListKosuu+32-1) / 32;
//	m_compTableSize = (m_blockSize * m_chartListKosuu+32-1) / 32;
	m_compTable = new int[m_compTableBufferSize];
	m_eventKosuu = new int[m_chartListKosuu];

	for (i=0;i<m_chartListKosuu;i++)
	{
		m_eventKosuu[i] = m_chart[i]->GetTotalRouteKosuu();
	}

	m_totalEventKosuu = 0;
	for (i=0;i<m_chartListKosuu;i++)
	{
		m_totalEventKosuu += m_eventKosuu[i];
	}

	CalcuMitaPercent();

//	for (i=0;i<m_chartListKosuu;i++)
//	{
//		CountMita(i);
//	}
//	CountTotalMita();
//
//	for (i=0;i<m_chartListKosuu;i++)
//	{
//		SetMitaToVar(i);
//	}
//	SetTotalMitaToVar();


	int wk = m_picKosuuMax;
	if (wk<4) wk = 4;
	m_backChara = new CPicture*[wk];
	for (i=0;i<4;i++)
	{
		m_backChara[i] = m_game->GetEffectPicture(i);
	}
	if (m_picKosuuMax > 4)
	{
		for (int i=4;i<m_picKosuuMax;i++)
		{
			m_backChara[i] = new CPicture();
		}
	}

	m_centerPic = m_game->GetEffectPicture(m_centerPicLayer);



//	m_chartMapButtonPic = m_game->GetSystemPicture("ta_chartmap_button");

	LPSTR varName = m_defaultSlotVarName;
	GetInitGameString(&varName,"slotVarName");
	m_slotNumberVarNumber = m_game->GetVarNumber(varName);

	varName = m_defaultFromVarName;
	GetInitGameString(&varName,"workVarName");
	m_fromNumberVarNumber = m_game->GetVarNumber(varName);

	m_printNumberVarNumber = -1;
	m_savePrintChartFlag = 0;
	GetInitGameParam(&m_savePrintChartFlag,"savePrintChartFlag");
	if (m_savePrintChartFlag)
	{
		varName = m_defaultPrintVarName;
		GetInitGameString(&varName,"workVarName2");
		m_printNumberVarNumber = m_game->GetVarNumber(varName);
	}


	//m_slotNumberVarNumber = m_game->GetVarNumber("スロット番号");
	//m_printChartVarNumber = m_game->GetVarNumber("今表示しているマップ");

	m_message = m_game->GetMyMessage();

	if (m_editMode == 2)
	{
		CreateDirectory("chart\\bak",NULL);
		for (i=0;i<m_chartListKosuu;i++)
		{
			m_chart[i]->MakeBak();
		}
	}



	LPSTR filenameMesWin = m_defaultMesWinName;
	GetInitGameString(&filenameMesWin,"filenameDescWindow");
	if (1)
	{
		char name[256];
		wsprintf(name,"sys\\%s",filenameMesWin);
	
		m_messageWindowPic = new CPicture(name);
		SIZE sz = m_messageWindowPic->GetPicSize();

		m_messageWindowSize.cx = sz.cx;
		m_messageWindowSize.cy = sz.cy;

		int upX = (screenSizeX - sz.cx) / 2;
		int upY = (screenSizeY / 2 - sz.cy) / 2;
		GetInitGameParam(&upX,"upperDescWindowPrintX");
		GetInitGameParam(&upY,"upperDescWindowPrintY");

		int downX = (screenSizeX - sz.cx) / 2;
		int downY = screenSizeY - (screenSizeY / 2 - sz.cy) / 2 - sz.cy;
		GetInitGameParam(&downX,"lowerDescWindowPrintX");
		GetInitGameParam(&downY,"lowerDescWindowPrintY");

		int mesX = 32;
		int mesY = 16;
		GetInitGameParam(&mesX,"descPrintX");
		GetInitGameParam(&mesY,"descPrintY");

		m_messageWindowZahyo[0].x = downX;
		m_messageWindowZahyo[0].y = downY;
		m_messageWindowZahyo[1].x = upX;
		m_messageWindowZahyo[1].y = upY;

		m_messageZahyo[0].x = mesX;
		m_messageZahyo[0].y = mesY;
		m_messageZahyo[1].x = mesX;
		m_messageZahyo[1].y = mesY;

		m_messageUpDown = 0;

		m_descFontSize = 20;
		GetInitGameParam(&m_descFontSize,"descFontSize");

		m_descNextY = m_descFontSize + 8;
		GetInitGameParam(&m_descNextY,"descNextY");

		m_descColorR = 255;
		m_descColorG = 255;
		m_descColorB = 255;
		GetInitGameParam(&m_descColorR,"descColorR");
		GetInitGameParam(&m_descColorG,"descColorG");
		GetInitGameParam(&m_descColorB,"descColorB");

	}


	if (1)
	{
		LPSTR cname = m_defaultOnCursorName;
		GetInitGameString(&cname,"filenameButtonCursor");
		char filename[1024];
		wsprintf(filename,"sys\\%s",cname);
		m_onCursorPic = new CPicture(filename);

		LPSTR nname = m_defaultNowChartName;
		GetInitGameString(&nname,"filenameNowChart");
		wsprintf(filename,"sys\\%s",nname);
		m_chartMapNowPic = new CPicture(filename);

		LPSTR bname = m_defaultTasseidoName;
		GetInitGameString(&bname,"filenameTasseido");
		wsprintf(filename,"sys\\%s",bname);
		m_tasseidoBasePic = new CPicture(filename);

		m_tasseidoBasePrintX = 0;
		m_tasseidoBasePrintY = 0;
		GetInitGameParam(&m_tasseidoBasePrintX,"tasseidoBaseX");
		GetInitGameParam(&m_tasseidoBasePrintY,"tasseidoBaseY");
	}

	if (1)
	{
		LPSTR sname = m_defaultChartFontName;
		GetInitGameString(&sname,"filenameChartFont");
		CPicture* suujiPic = m_game->GetSystemPicture(sname);

		int sizeX = 11;
		int sizeY = 18;
		GetInitGameParam(&sizeX,"chartFontSizeX");
		GetInitGameParam(&sizeY,"chartFontSizeY");
		int nextX = sizeX;
		GetInitGameParam(&nextX,"chartFontNextX");

		int upZero = 0;
		int leftFlag = 0;
		GetInitGameParam(&upZero,"chartFontUpZeroFlag");
		GetInitGameParam(&leftFlag,"chartFontLeftFlag");

		int keta = 3;

		m_suuji = new CSuuji(suujiPic,sizeX,sizeY,keta,nextX,upZero,TRUE,leftFlag);
	}

	m_tasseidoPrintX = 80;
	m_tasseidoPrintY = 34;
	m_totalTasseidoPrintX = 80;
	m_totalTasseidoPrintY = 20;
	GetInitGameParam(&m_tasseidoPrintX,"tasseidoX");
	GetInitGameParam(&m_tasseidoPrintY,"tasseidoY");
	GetInitGameParam(&m_totalTasseidoPrintX,"totalTasseidoX");
	GetInitGameParam(&m_totalTasseidoPrintY,"totalTasseidoY");






	for (i=0;i<5;i++)
	{
		int colR = m_defaultLineColor[i*3+0];
		int colG = m_defaultLineColor[i*3+1];
		int colB = m_defaultLineColor[i*3+2];

		char name[256];
		wsprintf(name,"lineColorR%d",i+1);
		GetInitGameParam(&colR,name);
		wsprintf(name,"lineColorG%d",i+1);
		GetInitGameParam(&colG,name);
		wsprintf(name,"lineColorB%d",i+1);
		GetInitGameParam(&colB,name);
		m_lineColor[i*3+0] = colR;
		m_lineColor[i*3+1] = colG;
		m_lineColor[i*3+2] = colB;
	}

	if (1)
	{
		LPSTR cname = m_defaultNotLookName;
		GetInitGameString(&cname,"filenameNotLook");
		char filename[1024];
		wsprintf(filename,"sys\\%s",cname);
		m_notLookPic = new CPicture(filename);
	}

	if (1)
	{
		LPSTR mname = m_defaultMiniMapName;
		GetInitGameString(&mname,"filenameMiniMapButton");
		char filename[1024];
		wsprintf(filename,"sys\\%s",mname);
		m_miniMapButtonPic = new CPicture(filename);

		m_miniMapButtonSizeX = 12;
		m_miniMapButtonSizeY = 3;
		GetInitGameParam(&m_miniMapButtonSizeX,"miniMapButtonSizeX");
		GetInitGameParam(&m_miniMapButtonSizeY,"miniMapButtonSizeY");
	}


	m_miniMapTenmetsuColor = 0;
	m_miniMapTenmetsuCount = 0;
	m_miniMapTenmetsuTime = 10;
	GetInitGameParam(&m_miniMapTenmetsuTime,"miniButtonTime");



	//base 位置
	//minimap位置
	//minimapSize
	
	m_miniMapBaseName = new LPSTR[m_chartListKosuu];
	m_miniMapBaseZahyo = new POINT[m_chartListKosuu];
	m_miniMapSize = new SIZE[m_chartListKosuu];
	m_miniMapZahyo = new POINT[m_chartListKosuu];

	//チャートリストごとにきりかえる?
	if (1)
	{
		LPSTR mname = m_defaultMiniMapBaseName;
		GetInitGameString(&mname,"filenameMiniMapBase");

		int minimapbasex = 10;
		int minimapbasey = 300;
		GetInitGameParam(&minimapbasex,"miniMapBasePrintX");
		GetInitGameParam(&minimapbasey,"miniMapBasePrintY");

		int minimapsizex = 120;
		int minimapsizey = 180;
		GetInitGameParam(&minimapsizex,"miniMapSizeX");
		GetInitGameParam(&minimapsizey,"miniMapSizeY");

		int minimapprintx = 0;
		int minimapprinty = 30;
		GetInitGameParam(&minimapprintx,"miniMapPrintX");
		GetInitGameParam(&minimapprinty,"miniMapPrintY");


		for (int i=0;i<m_chartListKosuu;i++)
		{
			char name[256];
			wsprintf(name,"filenameMiniMapBase%d",i+1);
			LPSTR mname2 = mname;
			GetInitGameString(&mname2,name);
			m_miniMapBaseName[i] = mname2;

			//zahyo
			int x = minimapbasex;
			int y = minimapbasey;
			wsprintf(name,"miniMapBasePrintX%d",i+1);
			GetInitGameParam(&x,name);
			m_miniMapBaseZahyo[i].x = x;

			wsprintf(name,"miniMapBasePrintY%d",i+1);
			GetInitGameParam(&y,name);
			m_miniMapBaseZahyo[i].y = y;

			int sizeX = minimapsizex;
			int sizeY = minimapsizey;
			wsprintf(name,"miniMapSizeX%d",i+1);
			GetInitGameParam(&sizeX,name);
			m_miniMapSize[i].cx = sizeX;
			wsprintf(name,"miniMapSizeY%d",i+1);
			GetInitGameParam(&sizeY,name);
			m_miniMapSize[i].cy = sizeY;

			x = minimapprintx;
			y = minimapprinty;
			wsprintf(name,"miniMapPrintX%d",i+1);
			GetInitGameParam(&x,name);
			m_miniMapZahyo[i].x = x;
			wsprintf(name,"miniMapPrintY%d",i+1);
			GetInitGameParam(&y,name);
			m_miniMapZahyo[i].y = y;

		}

		m_miniMapBasePic = new CPicture(filename);
	}


	if (1)
	{
		LPSTR mname = m_defaultMiniMapWindowName;
		GetInitGameString(&mname,"filenameMiniMapWindow");
		char filename[1024];
		wsprintf(filename,"sys\\%s",mname);
		m_miniMapWindowPic = new CPicture(filename);

		m_miniMapWindowUpSize = 15;
		m_miniMapWindowDownSize = 15;
		GetInitGameParam(&m_miniMapWindowUpSize,"miniMapWindowUpSize");
		GetInitGameParam(&m_miniMapWindowDownSize,"miniMapWindowDownSize");

		SIZE sz = m_miniMapWindowPic->GetPicSize();
		m_miniMapWindowPrintX = (m_miniMapSize[0].cx - sz.cx) / 2;
		m_miniMapWindowPrintY = -m_miniMapWindowUpSize;
		
		m_miniMapWindowSizeX = sz.cx;
		GetInitGameParam(&m_miniMapWindowSizeX,"miniMapWindowSizeX");


		GetInitGameParam(&m_miniMapWindowPrintX,"miniMapWindowPrintX");
		GetInitGameParam(&m_miniMapWindowPrintY,"miniMapWindowPrintY");
		m_miniMapWindowCenterSize = sz.cy - m_miniMapWindowUpSize - m_miniMapWindowDownSize;
	}



	m_scrollSpeedX = new int[m_chartListKosuu];
	for (i=0;i<m_chartListKosuu;i++)
	{
		int sp = -1;
		wsprintf(name,"scrollSpeedX%d",i+1);
		GetInitGameParam(&sp,name);
		m_scrollSpeedX[i] = sp;
	}


	m_miniWindowTenmetsuCount = 0;
	m_miniWindowTenmetsuTime = 30;
	m_miniWindowPercent1 = 30;
	m_miniWindowPercent2 = 90;
	GetInitGameParam(&m_miniWindowTenmetsuTime,"miniWindowTime");
	GetInitGameParam(&m_miniWindowPercent1,"miniWindowPercent1");
	GetInitGameParam(&m_miniWindowPercent2,"miniWindowPercent2");

	GetBGMSetup();
	GetFadeInOutSetup();
	GetDisableQuickButtonSetup();

	m_scrollX = 0;
	m_scrollY = 0;
	m_scrollSize = 600*3;
//	m_scrollSize = 600*6;
	m_scrollSpeedY = 20;
	GetInitGameParam(&m_scrollSpeedY,"scrollSpeed");
	m_printChartNumber = 0;
	//m_printChartNumberTmp = 0;

	CalcuMiniWindowSize();
	CalcuMiniWindowZahyo();

	//m_miniWindowAreaZahyo.x = 18;
	//m_miniWindowAreaZahyo.y = 369;

	m_buttonZahyo = new POINT[m_chartListKosuu * 2];
	for (i=0;i<m_chartListKosuu;i++)
	{
		int x = 0;
		int y = 0;

		for (int k=0;k<2;k++)
		{
			char name[256];

			wsprintf(name,"grow%dButton%dPrintX",i+1,k+1);
			GetInitGameParam(&x,name);
			wsprintf(name,"grow%dButton%dPrintY",i+1,k+1);
			GetInitGameParam(&y,name);

			m_buttonZahyo[i*2+k].x = x;
			m_buttonZahyo[i*2+k].y = y;
		}
	}

	m_selectSound = -1;
	m_overSound = -1;
	GetInitGameParam(&m_selectSound,"selectSound");
	GetInitGameParam(&m_overSound,"overSound");

	m_buttonMultiMax = 140;
	GetInitGameParam(&m_buttonMultiMax,"buttonMulti");
	m_buttonMulti = m_buttonMultiMax;
	m_buttonCountMax = 40;
	GetInitGameParam(&m_buttonCountMax,"buttonMultiCount");
	m_buttonCount = 0;

	m_selectButtonMulti = 140;
	GetInitGameParam(&m_selectButtonMulti,"selectButtonMulti");
	m_selectButtonMulti2 = 120;
	GetInitGameParam(&m_selectButtonMulti2,"selectButtonMulti2");

	m_lineColorCountMax = 20;
	GetInitGameParam(&m_lineColorCountMax,"lineColorCount");
	m_lineColorCount = 0;



	m_warningPrintFlag = 1;
	GetInitGameParam(&m_warningPrintFlag,"warningPrintFlag");

	m_dialogButton = NULL;

	if (1)
	{
		m_dialogFileName = m_defaultDialogFileName;
		GetInitGameString(&m_dialogFileName,"fileNameDialog");

		//make button
		m_dialogSizeX = 340;
		m_dialogSizeY = 145;
		m_dialogX = 236;
		m_dialogY = 160;

		GetInitGameParam(&m_dialogX,"dialogX");
		GetInitGameParam(&m_dialogY,"dialogY");
		GetInitGameParam(&m_dialogSizeX,"dialogSizeX");
		GetInitGameParam(&m_dialogSizeY,"dialogSizeY");


		char* names[2];
		names[0] = m_buttonName[0];
		names[1] = m_buttonName[1];

		m_dialogButton = new CCommonButtonGroup(m_setup,2,NULL,NULL,names);
		//change zahyo
		for (int i=0;i<2;i++)
		{
			POINT pt = m_dialogButton->GetZahyo(i);
			pt.x += m_dialogX;
			pt.y += m_dialogY;
			m_dialogButton->SetZahyo(i,pt);

			m_dialogButton->SetPicture(i,CSuperButtonPicture::GetPicture(i));
		}
		m_dialogButton->SetCancelButton(1);
	}

//	m_saveSound = 1;
	m_warningSound = -1;
//	GetInitGameParam(&m_saveSound,"saveSound");
	GetInitGameParam(&m_warningSound,"warningSound");

	//set size
	m_game->ChangeAutoExtDataSize(SELECTCHART_MODE,m_moveRoadSize * sizeof(char) + m_canSelectSize * sizeof(int));


	m_chartNumber = 1;	//dummy
	m_printChartNumber = 0;
	//m_printChartNumberTmp = 0;
	m_nowSlotNumber = 0;	//???


	int useSetRouteFunction = 1;
	GetInitGameParam(&useSetRouteFunction,"useSetRouteFunction");
	if (useSetRouteFunction)
	{
		LPSTR fcname = m_defaultSetRouteFunctionName;
		GetInitGameString(&fcname,"setRouteFunctionName");
		m_game->RegistUserFunction(m_classNumber,fcname);
	}

	int useGetChartPercentFunction = 1;
	GetInitGameParam(&useGetChartPercentFunction,"useGetChartPercentFunction");
	if (useGetChartPercentFunction)
	{
		LPSTR fcname = m_defaultGetChartPercentFunctionName;
		GetInitGameString(&fcname,"getChartPercentFunctionName");
		m_game->RegistUserFunction(m_classNumber,fcname,1);

		m_chartPercentVarNumber = m_game->GetVarNumber(chartPercentVarName);
	}

	int useCheckCompSlotFunction = 1;
	GetInitGameParam(&useCheckCompSlotFunction,"useCheckCompSlotFunction");
	if (useCheckCompSlotFunction)
	{
		LPSTR fcname = m_defaultCheckCompSlotFunctionName;
		GetInitGameString(&fcname,"checkCompSlotFunctionName");
		m_game->RegistUserFunction(m_classNumber,fcname,2);

		m_checkCompVarNumber = m_game->GetVarNumber(checkCompVarName);
	}

	int useOpenChartFunction = 1;
	GetInitGameParam(&useOpenChartFunction,"useOpenChartFunction");
	if (useOpenChartFunction)
	{
		LPSTR fcname = m_defaultOpenChartFunctionName;
		GetInitGameString(&fcname,"openChartFunctionName");
		m_game->RegistUserFunction(m_classNumber,fcname,3);
	}

	int useSlotOnFunction = 0;
	GetInitGameParam(&useSlotOnFunction,"useSlotOnFunction");
	if (useSlotOnFunction)
	{
		LPSTR fcname = m_defaultSlotOnFunctionName;
		GetInitGameString(&fcname,"slotOnFunctionName");
		m_game->RegistUserFunction(m_classNumber,fcname,4);
	}

	int useSlotOpenFunction = 0;
	GetInitGameParam(&useSlotOpenFunction,"useSlotOpenFunction");
	if (useSlotOpenFunction)
	{
		LPSTR fcname = m_defaultSlotOpenFunctionName;
		GetInitGameString(&fcname,"slotOpenFunctionName");
		m_game->RegistUserFunction(m_classNumber,fcname,5);
	}
}



CCommonChartMenu::~CCommonChartMenu()
{
	End();
}

void CCommonChartMenu::End(void)
{
	int i;
	ENDDELETECLASS(m_dialogButton);

	DELETEARRAY(m_buttonZahyo);
	DELETEARRAY(m_scrollSpeedX);

	ENDDELETECLASS(m_miniMapWindowPic);
	ENDDELETECLASS(m_miniMapBasePic);

	DELETEARRAY(m_miniMapZahyo);
	DELETEARRAY(m_miniMapSize);
	DELETEARRAY(m_miniMapBaseZahyo);
	DELETEARRAY(m_miniMapBaseName);
	ENDDELETECLASS(m_miniMapButtonPic);
	ENDDELETECLASS(m_notLookPic);

	ENDDELETECLASS(m_suuji);



	ENDDELETECLASS(m_tasseidoBasePic);
	ENDDELETECLASS(m_chartMapNowPic);
	ENDDELETECLASS(m_onCursorPic);
	ENDDELETECLASS(m_messageWindowPic);

	if (m_backChara != NULL)
	{
		for (int i=4;i<m_picKosuuMax;i++)
		{
			ENDDELETECLASS(m_backChara[i]);
		}
		DELETEARRAY(m_backChara);
	}


	DELETEARRAY(m_eventKosuu);
	DELETEARRAY(m_compTable);

	if (m_tsuka != NULL)
	{
		SaveTsuka();
	}
	DELETEARRAY(m_tsuka);

	if (m_mita != NULL)
	{
		SaveMita();
	}
	DELETEARRAY(m_mita);

	DELETEARRAY(m_mitaPercent);
	DELETEARRAY(m_mitaKosuu);

	ENDDELETECLASS(m_growButton);
	ENDDELETECLASS(m_compPic);

	if (m_chartPic != NULL)
	{
		for (int i=0;i<m_chartPicMax;i++)
		{
			ENDDELETECLASS(m_chartPic[i]);
		}
		DELETEARRAY(m_chartPic);
	}


	DELETEARRAY(m_chartPicKosuu);
	DELETEARRAY(m_backPicSizeY);
	DELETEARRAY(m_backPicKosuu);

	if (m_chart != NULL)
	{
		for (i=0;i<m_chartListKosuu;i++)
		{
			ENDDELETECLASS(m_chart[i]);
		}
		DELETEARRAY(m_chart);
	}

	DELETEARRAY(m_canSelect);
	DELETEARRAY(m_moveRoad);

	ENDDELETECLASS(m_newMarkAnimeParts);

	DELETEARRAY(m_ok);
	ENDDELETECLASS(m_mainCapturePic);
}

int CCommonChartMenu::Init(void)
{
	int i = 0;
	m_catchFlag = FALSE;
	m_reloadDataFlag = FALSE;
	m_warningFlag = FALSE;

	if (m_warningPrintFlag)
	{
		LoadWarningPic();
	}

	m_warningFlag = FALSE;
	m_exitModeFlag = FALSE;
	m_captureFlag = 0;



	m_nowSlotNumber = GetSlotNumber();
//	if (m_genzaichiVarNumber != -1)
//	{
//		m_nowSlotNumber = m_game->GetVarData(m_genzaichiVarNumber);
//	}

	m_printChartNumber = m_nowSlotNumber / m_blockSize;
	if (m_savePrintChartFlag)
	{
		if (m_printNumberVarNumber != -1)
		{
			m_printChartNumber = m_game->GetVarData(m_printNumberVarNumber);
		}
	}
	//m_printChartNumber = m_printChartNumberTmp;

	//CheckAndGetPrintChartNumber();

//	if (m_printChartVarNumber != -1)
//	{
//		m_printChartNumber = m_game->GetVarData(m_printChartVarNumber);
//	}
 

	m_fromSlotNumber = m_nowSlotNumber;
//	m_playMapNumber = m_nowSlotNumber / m_blockSize;
	m_chartNumber = m_nowSlotNumber / m_blockSize;
//	m_chartNumber = m_playMapNumber;

	m_game->InitOptionButton();






/*
	if (m_mitaYoyakuVarNumber != -1)
	{
		int yoyaku = m_game->GetVarData(m_mitaYoyakuVarNumber);
		if (yoyaku != 0)
		{
			SetMita(yoyaku,1);
			m_game->SetVarData(m_mitaYoyakuVarNumber,0);
		}
	}
*/


	m_newMarkFlag = 0;
	int oldNewMark = -1;
	if (m_newMarkPrintFlag)
	{
		if (m_newMarkVarNumber != -1)
		{
			oldNewMark = m_game->GetVarData(m_newMarkVarNumber);
		}
		m_newMarkAnimeParts->Init();
	}

	for (i=0;i<m_chartListKosuu;i++)
	{
		BOOL existFlag = FALSE;
		BOOL enableFlag = FALSE;

		if (i<m_basicChartKosuu)
		{
			existFlag = TRUE;
		}

		if (CheckChartOpen(i))
		{
			existFlag = TRUE;

			if (CheckExistClickOk(i))
			{
				enableFlag = TRUE;
			}
		}

		if (existFlag)
		{
			m_growButton->SetExist(i);
			m_growButton->SetEnable(i,enableFlag);
		}
		else
		{
			m_growButton->SetExist(i,FALSE);
		}

		if (m_newMarkPrintFlag)
		{
			if (enableFlag)
			{
				int bt = m_bitPattern[i];
				if ((bt & oldNewMark) == 0)
				{
					m_newMarkFlag |= bt;
				}
			}
		}
	}

	InitChangePage();


	if (m_printChartNumber == m_chartNumber)
	{
		POINT pt00 = m_chart[m_printChartNumber]->GetZahyo(m_nowSlotNumber);
		int screenSizeY = CMyGraphics::GetScreenSizeY();
		m_scrollY = pt00.y - screenSizeY / 2;
		AdjustInScroll();

		CalcuMiniWindowSize();
		CalcuMiniWindowZahyo();
	}

	m_onButtonNumber = -1;
	m_descPrintNumber = -1;

	return -1;
}




int CCommonChartMenu::Calcu(void)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	m_scrollX -= m_scrollSpeedX[m_printChartNumber];
	m_scrollX += screenSizeX;
	m_scrollX %= screenSizeX;

	if (m_warningFlag)
	{
		return CalcuWarning();
	}

	CalcuButtonMulti();
	CalcuLineColor();

	if (m_editMode == 2)
	{
		return CalcuEdit2();
	}

	if (m_catchFlag)
	{
		return CalcuCatch();
	}

	POINT pt = m_mouseStatus->GetZahyo();

	if (m_mouseStatus->GetTrig(1))
	{
		m_onButtonNumber = -1;
		CheckOnButton2(pt);

		if (m_dontRightMove == 0)
		{
			if (m_onButtonNumber != -1)
			{
				m_catchNumber = m_onButtonNumber;
				m_catchStartPoint = m_chart[m_printChartNumber]->GetZahyo(m_catchNumber);
				m_catchStart = pt;
				m_catchFlag = TRUE;
				return -1;
			}
		}
	}

	int rt = m_game->CalcuOptionButton();
	if (rt != NNNBUTTON_NOTHING)
	{
		m_growButton->Calcu(NULL);
		int nm = ProcessCommonButton(rt);

		if (nm == 0)
		{
			return m_game->ChangeToSystemMode(SYSTEMMENU_MODE,SELECTCHART_MODE);
		}

		int st = CCommonButton::GetButtonStatus(rt);
		if (st == NNNBUTTON_STARTCLICK) return -1;
		if (st == NNNBUTTON_CLICKING) return -1;
	}


	rt = m_growButton->Calcu(m_inputStatus);
	if (rt != NNNBUTTON_NOTHING)
	{
		int nm = ProcessCommonButton(rt);
		if (nm >= 0)
		{
			m_printChartNumber = nm;
			CheckAndSetPrintChartNumber();

//			m_game->SetVarData(m_printChartVarNumber,m_printChartNumber);

			InitChangePage();


			if (m_printChartNumber == m_chartNumber)
			{
				POINT pt00 = m_chart[m_printChartNumber]->GetZahyo(m_nowSlotNumber);
				int screenSizeY = CMyGraphics::GetScreenSizeY();
				m_scrollY = pt00.y - screenSizeY / 2;
				AdjustInScroll();

				CalcuMiniWindowSize();
				CalcuMiniWindowZahyo();
			}


			return -1;
		}

		int st = CCommonButton::GetButtonStatus(rt);
		if (st == NNNBUTTON_STARTCLICK) return -1;
		if (st == NNNBUTTON_CLICKING) return -1;
	}



	int nextMode = m_game->ProcessGameKey(SELECTCHART_MODE);
	if (nextMode != -1)
	{
		if (nextMode == SYSTEMMENU_MODE)
		{
			return m_game->ChangeToSystemMode(SYSTEMMENU_MODE,SELECTCHART_MODE);
		}

		return ReturnFadeOut(nextMode);
	}

//	POINT pt = m_mouseStatus->GetZahyo();
	int trig1 = m_mouseStatus->GetTrig(0);

	CheckWindowUpDown(pt);

	if (m_captureFlag == 1)
	{
		int dy = pt.y - m_captureStartY;
		m_miniWindowZahyoY = m_miniWindowZahyoStartY + dy;
		AdjustMiniWindowZahyo();
		CalcuScrollZahyo();
		AdjustInScroll();

		if (trig1 == 0)
		{
			m_captureFlag = 0;
		}

		return -1;
	}

	if (m_captureFlag == 2)
	{
		int dy = pt.y - m_captureStartY;
		if (m_mainCaptureOk == 1)
		{
			m_scrollY = m_mainWindowCaptureStartY - dy * m_mainCaptureReverse;
		}
		else if (m_mainCaptureOk == 3)
		{
			int ddy = (dy * (m_scrollSize - screenSizeY)) / screenSizeY;
			m_scrollY = m_mainWindowCaptureStartY - ddy * m_mainCaptureReverse;
		}

		AdjustInScroll();
		CalcuMiniWindowZahyo();


		if (trig1 == 0)
		{
			m_captureFlag = 0;
		}

		return -1;
	}


	/*
		int dy = pt.y - m_captureStartY;
		m_miniWindowZahyoY = m_miniWindowZahyoStartY + dy;
		AdjustMiniWindowZahyo();
		CalcuScrollZahyo();
		AdjustInScroll();

		if (trig1 == 0)
		{
			m_captureFlag = 0;
		}
	
	*/

//	if (trig1)
	if (m_mouseStatus->CheckClick(0))
	{
		m_captureStartY = GetOnMiniWindow(pt);
		m_miniWindowZahyoStartY = m_miniWindowZahyoY;

		if (m_captureStartY != -1)
		{
			JumpToMiniWindow();
			m_captureFlag = 1;
			return -1;
		}


		m_mainWindowCaptureStartX = pt.x;
		m_mainWindowCaptureStartY = pt.y;


	}

	int wheel = m_mouseStatus->GetWheel();
	if (wheel != 0)
	{
		if (wheel>0)
		{
			m_scrollY -= m_scrollSpeedY;
		}
		else
		{
			m_scrollY += m_scrollSpeedY;
		}

		AdjustInScroll();
		CalcuMiniWindowZahyo();
		return -1;
	}

//	m_onChartMapNumber = -1;
//	if (1)
//	{
//		CheckOnChartMapButton(pt);
//	}

	m_maeOnSlot = m_onButtonNumber;
	m_onButtonNumber = -1;
	if (1)
	{
		CheckOnButton(pt);
	}

	if (m_mainCaptureOk)
	{
		if (trig1)
		{
			if (m_onButtonNumber == -1)
			{
				//check in main
				if (CheckInSlotArea(pt))
				{
					m_captureStartY = pt.y;
	//				m_mainWindowCaptureStartX = pt.x;
					m_mainWindowCaptureStartY = m_scrollY;

					m_captureFlag = 2;
					m_descPrintNumber = -1;
					return -1;
				}
			}
		}
	}


	m_descPrintNumber = GetOnDescOkButton(pt);



	int sound = -1;


	if (m_onButtonNumber != -1)
	{
		if (m_onButtonNumber != m_maeOnSlot)
		{
			if (m_overSound > 0)
			{
				if (GetSelectOk(m_onButtonNumber))
				{
					m_game->PlaySystemSound(m_overSound-1);
				}
			}
		}
	}

	if (m_mouseStatus->CheckClick())
	{
//		if (m_onChartMapNumber != -1)
//		{
//			m_printChartNumber = m_onChartMapNumber;
//			Init();
//			return -1;
//		}

		if (m_onButtonNumber != -1)
		{
			BOOL f = CheckSelectOk(m_onButtonNumber);

			BOOL chk = FALSE;

			if (f == FALSE)
			{
				if (m_allClickFlag)
				{
					f = CheckSelectOk2(m_onButtonNumber);
					chk = TRUE;
				}
			}


			if (f)
			{
				if (m_selectSound > 0)
				{
					m_game->PlaySystemSound(m_selectSound-1);
				}

				m_selectNumber = m_onButtonNumber;

	//			SetMita(m_nowSlotNumber,0);
	//			Init();

				if ((chk == FALSE) || (m_warningPrintFlag == FALSE))
				{
					m_exitModeFlag = TRUE;
					return ReturnFadeOut(-1);
				}
				else
				{
					m_warningFlag = TRUE;
					m_dialogButton->Init();

					return -1;
				}
//				m_game->SetYoyaku();
			}

			return -1;

		}
		
	}



	return -1;
}



int CCommonChartMenu::Print(void)
{
	CalcuMiniMapButtonAnime();

	CAreaControl::SetNextAllPrint();
	PrintBackChara();

	if (m_backScriptFlag)
	{
		m_game->PrintBackScriptLayers(0,m_centerPicLayer - 1);
	}
	PrintCenter();
	if (m_backScriptFlag)
	{
		m_game->PrintBackScriptLayers(m_centerPicLayer + 1,13);
	}
	PrintAllChartLine();
	
	m_growButton->Print(TRUE);

	if (m_newMarkPrintFlag)
	{
		for (int i=0;i<m_chartListKosuu;i++)
		{
			int bt = m_bitPattern[i];
			if (bt & m_newMarkFlag)
			{
				PrintNewMark(i);
			}
		}
		AnimeNewMark();
	}


	PrintPlayMap();

	PrintMiniMapBase();
	PrintAllMiniButton();
	PrintMiniMapWindow();

	EraseAllButton();

	if (m_debugDontPrintButton == 0)
	{
		PrintAllButton();
	}
	
	PrintTasseido();

	PrintDesc();

	PrintCapturePic();

	if (m_backScriptFlag)
	{
		m_game->PrintBackScriptLayers(14,15);
	}

	if (m_warningFlag)
	{
		m_commonParts->Put(m_dialogX,m_dialogY,TRUE);
		if (m_dialogButton != NULL) m_dialogButton->Print(TRUE);
	}


	if (m_editMode == 2)
	{
		PrintEditStatus2();
	}

	m_game->PrintOptionButton();

#if defined _DEBUG
	char mes[256];
	wsprintf(mes,"ＦＲＯＭ:%d",m_fromSlotNumber);
	m_message->PrintMessage(250,10,mes);
	wsprintf(mes,"スロット:%d",m_nowSlotNumber);
	m_message->PrintMessage(600,10,mes);
#endif

	return -1;
}


void CCommonChartMenu::PrintNewMark(int n)
{
	CCommonRadioButton* radio = m_growButton->GetRadioButton(n);
	int st = 0;
	if (n == m_printChartNumber) st = 1;
	CCommonButton* button = radio->GetButton(st);
	POINT pt = button->GetZahyo();
	
	pt.x += m_newMarkPrintX;
	pt.y += m_newMarkPrintY;

	m_newMarkAnimeParts->Print(pt);
}


void CCommonChartMenu::AnimeNewMark(void)
{
	m_newMarkAnimeParts->Calcu();
}



void CCommonChartMenu::LoadBackChara(int n)
{
	if (m_picLoadByBackScript) return;

	char filename[256];
	int kosuu = m_backPicKosuu[n];
	for (int i=0;i<kosuu;i++)
	{
//		wsprintf(filename,"sys\\chart_back%d_%d",n+1,i+1);
		wsprintf(filename,"sys\\%s%d_%d",m_backTag,n+1,i+1);
		m_backChara[i]->LoadDWQ(filename);
	}
}

void CCommonChartMenu::LoadCenterPic(int n)
{
	if (m_picLoadByBackScript) return;

	char filename[256];
//	wsprintf(filename,"sys\\ta_chart_center%d",n+1);
	wsprintf(filename,"sys\\%s%d",m_centerTag,n+1);
	m_centerPic->LoadDWQ(filename);
}

BOOL CCommonChartMenu::LoadStartPic(void)
{
	char filename[256];
	wsprintf(filename,"sys\\%s1_1",m_chartSlotTag);
	m_commonParts->LoadDWQ(filename);
	return TRUE;
}


BOOL CCommonChartMenu::LoadChartPic(int chart,int n)
{
	char filename[256];
	wsprintf(filename,"sys\\%s%d_%d",m_chartSlotTag,chart+1,n+1);
	m_chartPic[n]->LoadDWQ(filename);
	return TRUE;
}

void CCommonChartMenu::LoadChartPic(int n)
{
	char filename[256];
	for (int i=0;i<m_chartPicKosuu[n];i++)
	{
		wsprintf(filename,"sys\\%s%d_%d",m_chartSlotTag,n+1,i+1);
		m_chartPic[i]->LoadDWQ(filename);
	}
}

void CCommonChartMenu::LoadMiniMapBasePic(int n)
{
	char filename[256];
	wsprintf(filename,"sys\\%s",m_miniMapBaseName[n]);
	m_miniMapBasePic->LoadDWQ(filename);
}

int CCommonChartMenu::GetBackSize(void)
{
	return m_backPicSizeY[m_printChartNumber];
}

void CCommonChartMenu::PrintBackChara(void)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int dy = 0;
	int dv = m_scrollSize - screenSizeY;
	if (dv>0)
	{
		int ml = GetBackSize();
		ml -= screenSizeY;
		if (ml > 0)
		{
			dy = (ml * m_scrollY) / dv;
			dy *= -1;
		}
	}

//	int dy = -((m_scrollY+300)*600 / m_scrollSize);
//	int kosuu = 4;//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	int kosuu = m_backPicKosuu[m_printChartNumber];

	for (int i=0;i<kosuu;i++)
	{
		m_backChara[i]->Blt(0,i*screenSizeY+dy,0,0,screenSizeX,screenSizeY,FALSE);
	}
}


void CCommonChartMenu::PrintCenter(void)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int dy = 0;
	int dv = m_scrollSize - screenSizeY;
	if (dv>0)
	{
		int ml = GetBackSize();
		ml -= screenSizeY;
		if (ml > 0)
		{
			dy = (ml * m_centerMulti * m_scrollY) / (dv * 100);
			dy *= -1;
		}
	}

//	int dy = -((m_scrollY+300)*1200) / m_scrollSize;
	if (dy<0)
	{
		dy *= -1;
		dy %= screenSizeY;
		dy *= -1;
	}

	if (dy>0)
	{
		dy %= screenSizeY;
	}

	int putX = 0;

	for (int i=0;i<2;i++)
	{
		int putX = i * screenSizeX - m_scrollX;
		for (int j=0;j<3;j++)
		{
			int putY = (j-1)*screenSizeY+dy;
			if ((putY > -screenSizeY) && (putY<screenSizeY))
			{
				m_centerPic->Blt(putX,putY,0,0,screenSizeX,screenSizeY,TRUE);
			}
		}
	}
}


void CCommonChartMenu::PrintAllChartLine(void)
{
	int chart = m_printChartNumber;
	int slotKosuu = m_chart[chart]->GetSlotKosuu();

	int sizeX = m_buttonSizeX;
	int sizeY = m_buttonSizeY;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	for (int i=0;i<slotKosuu;i++)
	{
		//char mes[256];
		//wsprintf(mes,"line %d %d",slotKosuu,i);
//MessageBox(NULL,mes,"line",MB_OK);

		int slot = m_chart[chart]->GetSlot(i);
		POINT pt = m_chart[chart]->GetZahyo(slot);
//@@		pt.x += sizeX/2;
//@@		pt.y += sizeY/2;
		POINT pt2 = ToScreenZahyo(pt);
		BOOL b1 = CheckInScreenLine(pt2);

		int nextKosuu = m_chart[chart]->GetNextKosuu(slot);
		for (int k=0;k<nextKosuu;k++)
//		for (int k=nextKosuu-1;k>=0;k--)
		{
			int nextSlot = m_chart[chart]->GetNext(slot,k);
			POINT pt3 = pt2;
			BOOL b2 = TRUE;

			if ((nextSlot / m_blockSize) == (slot/m_blockSize))
			{
				pt3 = m_chart[chart]->GetNextZahyo(slot,k);
				pt3 = ToScreenZahyo(pt3);
//@@				pt3.x += sizeX/2;
//@@				pt3.y += sizeY/2;
				b2 = CheckInScreenLine(pt3);
			}
			else
			{
				continue;
			}

			if ((pt2.y < 0) && (pt3.y >=screenSizeY)) b2 = TRUE;
			if ((pt3.y < 0) && (pt2.y >=screenSizeY)) b2 = TRUE;

			if (b1 || b2)
			{
				int md = 2;


				if (CheckTsuka(slot,k))
				{
					md = 1;
				}


				if (GetMoveRoad(slot) == (k+1))
				{
					md = 0;
				}

				if (m_fromSlotNumber == slot)
				{
					if (CheckSelectOk(nextSlot))
					{
						if (m_onButtonNumber == nextSlot)
						{
							md = 4;
						}
						else
						{
							md = 3;
						}
					}
				}

				PrintLine(pt2,pt3,md);
			}
		}
	}

}


void CCommonChartMenu::EraseAllButton(void)
{
	if (m_eraseButtonFlag == 0) return;

	int chart = m_printChartNumber;
	int slotKosuu = m_chart[chart]->GetSlotKosuu();

	for (int i=0;i<slotKosuu;i++)
	{
		int slot = m_chart[chart]->GetSlot(i);
		POINT pt = m_chart[chart]->GetZahyo(slot);
		POINT pt2 = ToScreenZahyo(pt);

		if (CheckInScreen(pt2))
		{
			BOOL ok = TRUE;
			int md = 0;
			if (CheckSelectOk(slot))
			{
				md = 2;
				if (slot == m_onButtonNumber)
				{
					md = 1;

					if (0)
					{
						ok = FALSE;
					}
				}
			}
			else
			{
				if (CheckSelectOk2(slot))
				{
					if (CheckMita(slot))
					{
						if (slot == m_onButtonNumber)
						{
							md = 1;
							ok = FALSE;
						}
					}
				}
			}

			if (slot == m_nowSlotNumber)
			{
				ok = FALSE;
				md = 3;
				if (slot == m_onButtonNumber)
				{
					md = 4;
				}
			}

			EraseButton(pt2,md,ok);
		}
			
	}

}

void CCommonChartMenu::PrintAllButton(void)
{
	int chart = m_printChartNumber;
	int slotKosuu = m_chart[chart]->GetSlotKosuu();

	for (int i=0;i<slotKosuu;i++)
	{
		int slot = m_chart[chart]->GetSlot(i);
		POINT pt = m_chart[chart]->GetZahyo(slot);
		POINT pt2 = ToScreenZahyo(pt);
		if (CheckInScreen(pt2))
		{
			int md = 0;
			BOOL ok = TRUE;
			
			if (CheckSelectOk(slot))
			{
				md = 2;
				if (slot == m_onButtonNumber)
				{
					md = 1;
					if (0)
					{
						ok = FALSE;
					}
				}
			}
			else
			{
				if (CheckMita(slot) == FALSE)
				{
					md = -1;
				}
				else
				{
					if (CheckSelectOk2(slot))
					{
						if (slot == m_onButtonNumber)
						{
							md = 1;
							ok = FALSE;
						}
					}
					else
					{
						md = 5;
						ok = FALSE;
					}

				}
			}


			if (slot == m_nowSlotNumber)
			{
				md = 3;
				ok = FALSE;
				if (slot == m_onButtonNumber)
				{
					md = 4;
				}
			}

			PrintButton(pt2,slot,md,ok);
			

			int routeKosuu = m_chart[chart]->GetRouteKosuu(slot);
			if (routeKosuu <= 1)
			{
				if (CheckComp(slot))
				{
					PutCompPic(pt2,md,100,0,ok);
				}
			}
			else
			{
				BOOL aru = FALSE;
				int k;
				for (k=0;k<routeKosuu;k++)
				{
					if (CheckRouteMita(slot,k+1))
					{
						aru = TRUE;
						break;
					}
				}
				if (aru)
				{
					for (k=0;k<routeKosuu;k++)
					{
						POINT pt3 = pt2;
						pt3.x += m_compNext.x * k;
						pt3.y += m_compNext.y * k;
						int ps = 100;
						if (CheckRouteMita(slot,k+1) == FALSE)
						{
							ps = m_compPercent;
						}
						PutCompPic(pt3,md,ps,k,ok);
					}
				}
			}
		}
	}
}

POINT CCommonChartMenu::GetMiniMapBaseZahyo(void)
{
	POINT pt;
	pt.x = m_miniMapBaseZahyo[m_printChartNumber].x;
	pt.y = m_miniMapBaseZahyo[m_printChartNumber].y;
	return pt;
}

POINT CCommonChartMenu::GetMiniMapAreaZahyo(void)
{
	POINT pt = GetMiniMapBaseZahyo();
	pt.x += m_miniMapZahyo[m_printChartNumber].x;
	pt.y += m_miniMapZahyo[m_printChartNumber].y;
	return pt;
}

POINT CCommonChartMenu::GetNowMiniMapZahyo(void)
{
	POINT pt = GetMiniMapAreaZahyo();
//@@@@@@	pt.y += 
	return pt;
}

POINT CCommonChartMenu::GetMiniMapWindowZahyo(void)
{
	POINT pt = GetNowMiniMapZahyo();
	pt.x += m_miniMapWindowPrintX;
	pt.y += m_miniMapWindowPrintY;
	return pt;
}


void CCommonChartMenu::PrintMiniMapBase(void)
{
	POINT pt = GetMiniMapBaseZahyo();
	m_miniMapBasePic->Put(pt.x,pt.y,TRUE);
}

void CCommonChartMenu::PrintMiniMapWindow(void)
{
	POINT pt = GetMiniMapWindowZahyo();
	pt.y += m_miniWindowZahyoY;
	PutMiniMapWindow(pt,m_miniWindowSize);
}

void CCommonChartMenu::PutMiniMapWindow(POINT pt,int windowSizeY)
{

	m_miniWindowTenmetsuCount++;
	if (m_miniWindowTenmetsuCount >= m_miniWindowTenmetsuTime) m_miniWindowTenmetsuCount = 0;
	
	int c = m_miniWindowTenmetsuCount;
	int dv = m_miniWindowTenmetsuTime / 2;
	if (dv<1) dv = 1;
	if (c>dv) c = m_miniWindowTenmetsuTime - c;
	m_miniWindowPercent = m_miniWindowPercent1 + ((m_miniWindowPercent2 - m_miniWindowPercent1)*c) / dv;



	POINT pt2 = pt;
	pt2.y -= m_miniMapWindowUpSize;

	POINT src;
	src.x = 0;
	src.y = 0;
	SIZE size;
	size.cx = m_miniMapWindowSizeX;
	size.cy = m_miniMapWindowUpSize;
	PutMiniMapWindowSub(pt2,src,size);

	//@@center print stretchblt??
	pt2.y += size.cy;
	src.y += size.cy;
//	size.cy = m_windowSizeY;
//	PutMiniMapWindowSub(pt2,src,size);

	int ps = m_miniWindowPercent;
	m_miniMapWindowPic->StretchBlt1(pt2.x,pt2.y,size.cx,windowSizeY,src.x,src.y,size.cx,m_miniMapWindowCenterSize,ps);

	pt2.y += windowSizeY;
	src.y += m_miniMapWindowCenterSize;
	size.cy = m_miniMapWindowDownSize;
	PutMiniMapWindowSub(pt2,src,size);
}

void CCommonChartMenu::PutMiniMapWindowSub(POINT pt,POINT src,SIZE size)
{
	int ps = m_miniWindowPercent;
	m_miniMapWindowPic->TransLucentBlt3(pt.x,pt.y,src.x,src.y,size.cx,size.cy,ps);
}


void CCommonChartMenu::PrintAllMiniButton(void)
{
	int chart = m_printChartNumber;
	int slotKosuu = m_chart[chart]->GetSlotKosuu();

	for (int i=0;i<slotKosuu;i++)
	{
		int slot = m_chart[chart]->GetSlot(i);
		POINT pt = m_chart[chart]->GetZahyo(slot);

		int md = 0;
		if (CheckComp(slot))
		{
			md = 1;
		}
		if (slot == m_nowSlotNumber)
		{
			md = 2;
		}
		
		if (CheckSelectOk(slot))
		{
			md = 3;
		}

		POINT pt2 = ToMiniMapZahyo(pt);
		PutMiniMapButton(pt2,md);
	}
}


POINT CCommonChartMenu::ToScreenZahyo(POINT pt)
{
	pt.x += m_slotAreaStartX;
	pt.y += m_slotAreaStartY;

//	pt.x -= m_scrollX;
	pt.y -= m_scrollY;
	return pt;
}

BOOL CCommonChartMenu::CheckInScreen(POINT pt)
{
	int x = pt.x;
	int y = pt.y;

	int sizeX = m_buttonSizeX;
	int sizeY = m_buttonSizeY;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if ((x<-sizeX) || (y<-sizeY*2)) return FALSE;
	if ((x>=screenSizeX) || (y>=screenSizeY+sizeY)) return FALSE;

	return TRUE;

}

BOOL CCommonChartMenu::CheckInScreenLine(POINT pt)
{
	int x = pt.x;
	int y = pt.y;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int size = 2;
	if ((x<-size) || (y<-size)) return FALSE;
	if ((x>=screenSizeX+size) || (y>=screenSizeY+size)) return FALSE;

	return TRUE;

}

void CCommonChartMenu::EraseButton(POINT pt,int md,BOOL ok)
{
	int sizeX0 = m_buttonSizeX;
	int sizeY0 = m_buttonSizeY;

	int sizeX = sizeX0;
	int sizeY = sizeY0;

	int putX = pt.x;
	int putY = pt.y;

	if ((md == 1) || (md == 4))
	{
		if (ok)
		{
			sizeX *= m_selectButtonMulti;
			sizeY *= m_selectButtonMulti;
		}
		else
		{
			sizeX *= m_selectButtonMulti2;
			sizeY *= m_selectButtonMulti2;
		}

		sizeX /= 100;
		sizeY /= 100;
//		int deltaX = (sizeX - sizeX0) / 2;
//		int deltaY = (sizeY - sizeY0) / 2;
		int deltaX = sizeX  / 2;
		int deltaY = sizeY  / 2;
		putX -= deltaX;
		putY -= deltaY;
	}
	else if (md == 2)
	{
		sizeX *= m_buttonMulti;
		sizeX /= 100;
		sizeY *= m_buttonMulti;
		sizeY /= 100;
//		int deltaX = (sizeX - sizeX0) / 2;
//		int deltaY = (sizeY - sizeY0) / 2;
		int deltaX = sizeX  / 2;
		int deltaY = sizeY  / 2;
		putX -= deltaX;
		putY -= deltaY;
	}
	else
	{
		putX -= sizeX / 2;
		putY -= sizeY / 2;
	}


	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	//erase back
	int srcY2 = putY;
	int dv = m_scrollSize - screenSizeY;
	if (dv>0)
	{
		int ml = GetBackSize();
		ml -= screenSizeY;
		if (ml>0)
		{
			srcY2 += (ml * m_scrollY) / dv;
		}
	}






	int srcX2 = putX;
	int kosuu = m_backPicKosuu[m_printChartNumber];
	for (int i=0;i<kosuu;i++)
	{
		m_backChara[i]->Blt(putX,putY,srcX2,srcY2,sizeX,sizeY,FALSE);
		srcY2 -= screenSizeY;
	}

//	int srcX3 = srcX2;
//	int srcY3 = srcY2 - screenSizeY;
//	m_backChara[0]->Blt(putX,putY,srcX2,srcY2,sizeX,sizeY,FALSE);
//	m_backChara[1]->Blt(putX,putY,srcX3,srcY3,sizeX,sizeY,FALSE);

}

//0:normal
//1:on
//2:can
//3:(now)
//4:now-sel
//5cannot but look
void CCommonChartMenu::PrintButton(POINT pt,int slot,int md,BOOL ok)
{
	int n = slot - m_printChartNumber*m_blockSize;
	if ((n<0) || (n>=m_blockSize)) return;
	int seat = n / m_buttonPicKosuu;
	
//	if (seat>=3) return;	//dummy

	int sizeX = m_buttonSizeX;
	int sizeY = m_buttonSizeY;

	int srcX = n % m_buttonPicKosuuX;
	srcX *= sizeX;
	int srcY = n / m_buttonPicKosuuX;
	srcY %= m_buttonPicKosuuY;

	srcY *= sizeY;

	int putX = pt.x;
	int putY = pt.y;

	//erase back
//	int srcX2 = putX;
//	int srcY2 = putY+m_scrollY/2;
//	int srcX3 = srcX2;
//	int srcY3 = srcY2 - 600;
//	m_backChara[0]->Blt(putX,putY,srcX2,srcY2,sizeX,sizeY,FALSE);
//	m_backChara[1]->Blt(putX,putY,srcX3,srcY3,sizeX,sizeY,FALSE);








	if (md == -1)
	{
		m_notLookPic->Blt(putX-sizeX/2,putY-sizeY/2,0,0,sizeX,sizeY,TRUE);
		return;
	}


	if (md == 0)
	{
		m_chartPic[seat]->Blt(putX-sizeX/2,putY-sizeY/2,srcX,srcY,sizeX,sizeY,TRUE);
	}
	else if (md == 1)
	{
		int sizeX2,sizeY2;
		if (ok)
		{
			sizeX2 = sizeX * m_selectButtonMulti;
			sizeY2 = sizeY * m_selectButtonMulti;
		}
		else
		{
			sizeX2 = sizeX * m_selectButtonMulti2;
			sizeY2 = sizeY * m_selectButtonMulti2;
		}
		sizeX2 /= 100;
		sizeY2 /= 100;
//		int deltaX = (sizeX2 - sizeX) / 2;
//		int deltaY = (sizeY2 - sizeY) / 2;
		int deltaX = sizeX2 / 2;
		int deltaY = sizeY2 / 2;
		putX -= deltaX;
		putY -= deltaY;

		m_chartPic[seat]->StretchBlt1(putX,putY,sizeX2,sizeY2,srcX,srcY,sizeX,sizeY,m_selectSlotTransPercent,TRUE);
	}
	else if (md == 2)
	{
		int sizeX2 = sizeX * m_buttonMulti;
		sizeX2 /= 100;
		int sizeY2 = sizeY * m_buttonMulti;
		sizeY2 /= 100;
//		int deltaX = (sizeX2 - sizeX) / 2;
//		int deltaY = (sizeY2 - sizeY) / 2;
		int deltaX = sizeX2 / 2;
		int deltaY = sizeY2 / 2;
		putX -= deltaX;
		putY -= deltaY;

		m_chartPic[seat]->StretchBlt1(putX,putY,sizeX2,sizeY2,srcX,srcY,sizeX,sizeY,m_selectOkSlotTransPercent,TRUE);
	}
	else if (md == 3)
	{
		m_chartPic[seat]->Blt(putX-sizeX/2,putY-sizeY/2,srcX,srcY,sizeX,sizeY,TRUE);
		m_onCursorPic->Put(putX-sizeX/2,putY-sizeY/2,TRUE);
	}
	else if (md == 4)
	{
		int	sizeX2 = sizeX * m_selectButtonMulti2;
		int	sizeY2 = sizeY * m_selectButtonMulti2;
		sizeX2 /= 100;
		sizeY2 /= 100;
//		int deltaX = (sizeX2 - sizeX) / 2;
//		int deltaY = (sizeY2 - sizeY) / 2;
		int deltaX = sizeX2  / 2;
		int deltaY = sizeY2  / 2;
		putX -= deltaX;
		putY -= deltaY;

		m_chartPic[seat]->StretchBlt1(putX,putY,sizeX2,sizeY2,srcX,srcY,sizeX,sizeY,100,TRUE);
		m_onCursorPic->StretchBlt1(putX,putY,sizeX2,sizeY2,0,0,sizeX,sizeY,100,TRUE);

//		m_chartPic[seat]->TransLucentBlt_2(putX,putY,srcX,srcY,sizeX,sizeY,50);
	}
	else if (md == 5)
	{
		m_chartPic[seat]->GreyBlt(putX-sizeX/2,putY-sizeY/2,srcX,srcY,sizeX,sizeY,TRUE);
	}

}



/*
void CCommonChartMenu::CheckOnChartMapButton(POINT pt)
{
	int sizeX = m_chartMapButtonSizeX;
	int sizeY = m_chartMapButtonSizeY;

	for (int i=1;i<10;i++)
	{
		if (1)
		{
			POINT pt2 = GetChartMapButtonZahyo(i);
			int x = pt.x - pt2.x;
			int y = pt.y - pt2.y;
			if ((x>=0) && (y>=0) && (x<sizeX) && (y<sizeY))
			{
				m_onChartMapNumber = i;
				return;
			}
		}
	}
}
*/

void CCommonChartMenu::CheckOnButton(POINT pt)
{
//	if (m_printChartNumber != m_chartNumber) return;

	int sizeX = m_buttonSizeX;
	int sizeY = m_buttonSizeY;

	int chart = m_printChartNumber;
	int slotKosuu = m_chart[chart]->GetSlotKosuu();

	int i;
	for (i=0;i<m_blockSize;i++)
	{
		m_ok[i] = 0;
	}


	if (1)
	{
		int fromSlot = m_nowSlotNumber;
		int fromChart = SlotToChart(m_nowSlotNumber);
		int nextKosuu = m_chart[fromChart]->GetNextKosuu(fromSlot);

		for (int k=0;k<nextKosuu;k++)
		{
			int nextSlot = m_chart[fromChart]->GetNext(fromSlot,k);
			int nextChart = SlotToChart(nextSlot);
			if (nextChart == m_printChartNumber)
			{
				int n2 = nextSlot - m_printChartNumber*m_blockSize;
				if ((n2>=0) && (n2<m_blockSize))
				{
					m_ok[n2] = 1;
				}
			}
		}
	}


	for (i=slotKosuu-1;i>=0;i--)
	{
		int slot = m_chart[chart]->GetSlot(i);

		int n = slot - m_printChartNumber*m_blockSize;
		int f = 0;
		if ((n>=0) && (n<m_blockSize))
		{
			f = m_ok[n];
		}

		if (f == 0)
		{
			if (m_allClickFlag)
			{
				if (CheckSelectOk2(slot)) f = 1;
			}
		}

		if (f)
		{
			POINT pt2 = m_chart[chart]->GetZahyo(slot);
			POINT pt3 = ToScreenZahyo(pt2);
			if (CheckInScreen(pt3))
			{
				int x = pt.x - pt3.x;
				int y = pt.y - pt3.y;
				x += sizeX / 2;
				y += sizeY / 2;
				if ((x>=0) && (y>=0) && (x<sizeX) && (y<sizeY))
				{
					m_onButtonNumber = slot;
					return;
				}
			}
		}
	}
}

int CCommonChartMenu::GetOnDescOkButton(POINT pt)
{
	int sizeX = m_buttonSizeX;
	int sizeY = m_buttonSizeY;

	int chart = m_printChartNumber;

	int slotKosuu = m_chart[chart]->GetSlotKosuu();

	int i;
///	for (i=0;i<slotKosuu;i++)
	for (i=slotKosuu-1;i>=0;i--)
	{
		int slot = m_chart[chart]->GetSlot(i);
		if (CheckMita(slot))
		{
			POINT pt2 = m_chart[chart]->GetZahyo(slot);
			POINT pt3 = ToScreenZahyo(pt2);
			if (CheckInScreen(pt3))
			{
				int x = pt.x - pt3.x;
				int y = pt.y - pt3.y;

				x += sizeX / 2;
				y += sizeY / 2;

				if ((x>=0) && (y>=0) && (x<sizeX) && (y<sizeY))
				{
					return slot;
				}
			}
		}
	}



	int fromChart = SlotToChart(m_nowSlotNumber);
	if (m_printChartNumber != fromChart) return -1;

	int nextKosuu = m_chart[fromChart]->GetNextKosuu(m_nowSlotNumber);
	for (i=0;i<nextKosuu;i++)
	{
		int nextSlot = m_chart[fromChart]->GetNext(m_nowSlotNumber,i);
		if (CheckSelectOk(nextSlot))
		{
			int nextChart = SlotToChart(nextSlot);
			POINT pt2 = m_chart[nextChart]->GetZahyo(nextSlot);
			POINT pt3 = ToScreenZahyo(pt2);
			if (CheckInScreen(pt3))
			{
				int x = pt.x - pt3.x;
				int y = pt.y - pt3.y;

				x += sizeX / 2;
				y += sizeY / 2;

				if ((x>=0) && (y>=0) && (x<sizeX) && (y<sizeY))
				{
					return nextSlot;
				}
			}
		}
	}

	return -1;
}

void CCommonChartMenu::CheckOnButton2(POINT pt)
{
//	if (m_printChartNumber != m_chartNumber) return;

	int sizeX = m_buttonSizeX;
	int sizeY = m_buttonSizeY;

	int chart = m_printChartNumber;

	int slotKosuu = m_chart[chart]->GetSlotKosuu();


//	for (int i=0;i<slotKosuu;i++)
	for (int i=slotKosuu-1;i>=0;i--)
	{
		int slot = m_chart[chart]->GetSlot(i);

		POINT pt2 = m_chart[chart]->GetZahyo(slot);
		POINT pt3 = ToScreenZahyo(pt2);
		if (CheckInScreen(pt3))
		{
			int x = pt.x - pt3.x;
			int y = pt.y - pt3.y;

			x += sizeX / 2;
			y += sizeY / 2;

			if ((x>=0) && (y>=0) && (x<sizeX) && (y<sizeY))
			{
				m_onButtonNumber = slot;
				return;
			}
		}
	}
}

void CCommonChartMenu::PrintLine(POINT pt,POINT pt2,int md)
{

	if (md < 4)
	{
		int colR = m_lineColor[md*3];
		int colG = m_lineColor[md*3+1];
		int colB = m_lineColor[md*3+2];
		CAllGeo::Line(pt.x,pt.y,pt2.x,pt2.y,colR,colG,colB);
		CAllGeo::Line(pt.x+1,pt.y,pt2.x+1,pt2.y,colR,colG,colB);
		CAllGeo::Line(pt.x,pt.y+1,pt2.x,pt2.y+1,colR,colG,colB);
		if (md == 0)
		{
			CAllGeo::Line(pt.x-1,pt.y,pt2.x-1,pt2.y,colR,colG,colB);
			CAllGeo::Line(pt.x,pt.y-1,pt2.x,pt2.y-1,colR,colG,colB);
		}
	}
	else
	{
		int r1 = m_lineColor[3*3];
		int g1 = m_lineColor[3*3+1];
		int b1 = m_lineColor[3*3+2];
		int r2 = m_lineColor[4*3];
		int g2 = m_lineColor[4*3+1];
		int b2 = m_lineColor[4*3+2];


		int c = m_lineColorCount;
		int dv = m_lineColorCountMax/2;
		if (dv<1) dv = 1;
		if (c>=dv)
		{
			c = m_lineColorCountMax - c;
		}

		int colR = r1 + ((r2-r1)*c) / dv;
		int colG = g1 + ((g2-g1)*c) / dv;
		int colB = b1 + ((b2-b1)*c) / dv;

		CAllGeo::Line(pt.x-1,pt.y,pt2.x-1,pt2.y,colR,colG,colB);
		CAllGeo::Line(pt.x,pt.y,pt2.x,pt2.y,colR,colG,colB);
		CAllGeo::Line(pt.x+1,pt.y,pt2.x+1,pt2.y,colR,colG,colB);
		CAllGeo::Line(pt.x,pt.y-1,pt2.x,pt2.y-1,colR,colG,colB);
		CAllGeo::Line(pt.x,pt.y+1,pt2.x,pt2.y+1,colR,colG,colB);

	}
}

void CCommonChartMenu::PrintDesc(int md)
{
	if (m_descPrintNumber == -1) return;

	int putX = m_messageWindowZahyo[m_messageUpDown].x;
	int putY = m_messageWindowZahyo[m_messageUpDown].y;
	int sizeX = m_messageWindowSize.cx;
	int sizeY = m_messageWindowSize.cy;
	int srcX = 0;
	int srcY = 0;
	m_messageWindowPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);

	md = 0;
	if (CheckMita(m_descPrintNumber) == FALSE)
	{
		md = 1;
	}



	if (md == 1)
	{
		int descKosuu2 = m_chart[m_printChartNumber]->GetDescKosuu(m_descPrintNumber,md);
		if (descKosuu2 <= 0) md = 0;
	}


	if ((m_descPrintNumber / m_blockSize) == m_printChartNumber)
	{
		int descKosuu = m_chart[m_printChartNumber]->GetDescKosuu(m_descPrintNumber,md);

		putX += m_messageZahyo[m_messageUpDown].x;
		putY += m_messageZahyo[m_messageUpDown].y;

		for (int i=0;i<descKosuu;i++)
		{
			LPSTR mes = m_chart[m_printChartNumber]->GetDesc(m_descPrintNumber,i,md);
			if (mes != NULL)
			{
				m_message->PrintMessage(putX,putY+m_descNextY*i,mes,m_descFontSize,m_descColorR,m_descColorG,m_descColorB);
			}
		}
	}
}


void CCommonChartMenu::SetNowSlotNumber(int slot)
{
	/*
	m_game->StopMusic();

	m_nowSlotNumber = slot;
	m_chartNumber = m_nowSlotNumber / m_blockSize;
	m_printChartNumber = m_chartNumber;
	m_game->SetVarData(m_slotNumberVarNumber,slot);
//	m_game->SetVarData(m_printChartVarNumber,m_printChartNumber);

	SetMita(slot,1);

	//最終選択のとび先になっていれば、ルートオン
	int last = m_game->GetVarData(m_lastSelectVarNumber);
//	if ((last > 0) && (last < 10000))
	if ((last > 0) && (last < m_blockSize * m_chartListKosuu))
	{
		int chart = last / m_blockSize;
		int found = -1;
		int routeKosuu = m_chart[chart]->GetNextKosuu(last);
		
		for (int i=0;i<routeKosuu;i++)
		{
			if (m_chart[chart]->GetNext(last,i) == slot)
			{
				found = i;
				break;
			}
		}

		if (found != -1)
		{
			SetTsuka(last,found);
			SetMoveRoute(last,found+1);
		}
	}

	//save chart?
	SaveChartData();

*/

}







int CCommonChartMenu::CheckEvent(int slot)
{
	int chart = slot / m_blockSize;
	int routeKosuu = m_chart[chart]->GetRouteKosuu(slot);
	
	int flg = 0;
	for (int i=0;i<routeKosuu;i++)
	{
		int bitPattern = m_bitPattern[(slot & 3) * 8 + i];
		if (m_mita[slot/4] & bitPattern) flg = 1;
	}
	
	return flg;
}

int CCommonChartMenu::CheckComplete(int slot)
{
	int chart = slot / m_blockSize;
	int routeKosuu = m_chart[chart]->GetRouteKosuu(slot);
	
	int flg = 1;
	for (int i=0;i<routeKosuu;i++)
	{
		int bitPattern = m_bitPattern[(slot & 3) * 8 + i];
		if ((m_mita[slot/4] & bitPattern) == 0) flg = 0;
	}
	
	return flg;
}

void CCommonChartMenu::SetMita(int slot,int k)
{
	int chart = slot / m_blockSize;
	int route = m_chart[chart]->GetRouteKosuu(slot);
	
	if (route <= 1)
	{
		int bitPattern = m_bitPattern[(slot & 3) * 8];
		m_mita[slot/4] |= bitPattern;
	}
	else
	{
		if ((k>=1) && (k<=8))
		{
			int bitPattern = m_bitPattern[(slot & 3) * 8 + k - 1];
			m_mita[slot/4] |= bitPattern;
		}
	}
	CalcuMitaPercent();
}


void CCommonChartMenu::CountMita(int chart)
{
	int total = 0;
	int slotKosuu = m_chart[chart]->GetSlotKosuu();
	for (int i=0;i<slotKosuu;i++)
	{
		int slot = m_chart[chart]->GetSlot(i);
		int routeKosuu = m_chart[chart]->GetRouteKosuu(slot);

		for (int b=0;b<routeKosuu;b++)
		{
			int bitPattern = m_bitPattern[(slot & 3) * 8 + b];
			if (m_mita[slot / 4] & bitPattern) total++;
		}
	}

	m_mitaKosuu[chart] = total;
}

void CCommonChartMenu::CountTotalMita(void)
{
	int total = 0;

	for (int i=0;i<m_chartListKosuu;i++)
	{
		total += m_mitaKosuu[i];
	}

	m_totalMitaKosuu = total;
}


//サイズが変更@@@@@
void CCommonChartMenu::LoadMita(void)
{
//	int sz = (m_chartListKosuu * m_blockSize + sizeof(int) - 1) / sizeof(int);

	FILE* file = NULL;
	LPSTR saveFolder = CMySaveFolder::GetFullFolder();
	char filename[1024];
	wsprintf(filename,"%s\\mita.dat",saveFolder);

	fopen_s(&file,filename,"rb");
	if (file != NULL)
	{
//		fread(m_mita,sizeof(int),(10000/4+1),file);
		fread(m_mita,sizeof(int),m_mitaBufferSize,file);
		fclose(file);
	}
}

void CCommonChartMenu::SaveMita(void)
{
	//int sz = (m_chartListKosuu * m_blockSize + sizeof(int) - 1) / sizeof(int);

	FILE* file = NULL;
	LPSTR saveFolder = CMySaveFolder::GetFullFolder();
	char filename[1024];
	wsprintf(filename,"%s\\mita.dat",saveFolder);

	fopen_s(&file,filename,"wb");
	if (file != NULL)
	{
		fwrite(m_mita,sizeof(int),m_mitaBufferSize,file);
		fclose(file);
	}
}

void CCommonChartMenu::LoadTsuka(void)
{
//	int sz = m_chartListKosuu * m_blockSize;

	FILE* file = NULL;

	LPSTR saveFolder = CMySaveFolder::GetFullFolder();
	char filename[1024];
	wsprintf(filename,"%s\\tsuka.dat",saveFolder);

	fopen_s(&file,filename,"rb");
	if (file != NULL)
	{
		fread(m_tsuka,sizeof(char),m_tsukaBufferSize,file);
		fclose(file);
	}
}

void CCommonChartMenu::SaveTsuka(void)
{
//	int sz = m_chartListKosuu * m_blockSize;

	FILE* file = NULL;
	LPSTR saveFolder = CMySaveFolder::GetFullFolder();
	char filename[1024];
	wsprintf(filename,"%s\\tsuka.dat",saveFolder);

	fopen_s(&file,filename,"wb");
	if (file != NULL)
	{
		fwrite(m_tsuka,sizeof(char),m_tsukaBufferSize,file);
		fclose(file);
	}
}






void CCommonChartMenu::InitMoveRoad(void)
{
	for (int i=0;i<m_moveRoadSize;i++)
	{
		m_moveRoad[i] = 0;
	}
}

int CCommonChartMenu::GetMoveRoad(int slot)
{
	int d = m_moveRoad[slot];
	d &= 0xff;
	return d;
}

void CCommonChartMenu::SetMoveRoad(int slot,int n)
{
	m_moveRoad[slot] = (char)(n+1);
}

BOOL CCommonChartMenu::CheckTsuka(int slot,int n)
{
	int bitPattern = m_bitPattern[n];
	int d = (int)(m_tsuka[slot]);
	d &= 0xff;
	if (d & bitPattern) return TRUE;
	return FALSE;
}

void CCommonChartMenu::SetTsuka(int slot,int n)
{
	int bitPattern = m_bitPattern[n];
	int d = (int)(m_tsuka[slot]);
	d |= bitPattern;
	m_tsuka[slot] = (char)d;
}








void CCommonChartMenu::PutCompPic(POINT pt,int md,int ps,int k,BOOL ok)
{
	int putX = pt.x;
	int putY = pt.y;
	int sizeX = m_compSize.cx;
	int sizeY = m_compSize.cy;
	int srcX = 0;//sizeX * md?;
	int srcY = 0;
	putX += m_compDelta.x;
	putY += m_compDelta.y;


	if ((md == 1) || (md == 4))
	{
		int sizeX2,sizeY2;

		if (ok)
		{
			sizeX2 = m_buttonSizeX * m_selectButtonMulti;
			sizeY2 = m_buttonSizeY * m_selectButtonMulti;
		}
		else
		{
			sizeX2 = m_buttonSizeX * m_selectButtonMulti2;
			sizeY2 = m_buttonSizeY * m_selectButtonMulti2;
		}

		sizeX2 /= 100;
		sizeY2 /= 100;
//		int deltaX = (sizeX2 - m_buttonSizeX) / 2;
//		int deltaY = (sizeY2 - m_buttonSizeY) / 2;
		int deltaX = sizeX2 / 2;
		int deltaY = sizeY2 / 2;
		putX -= deltaX;
		putY -= deltaY;

		if (k>0)
		{
			int deltaX2 = ((k * m_compNext.x) * m_buttonMultiMax) / 100;
			deltaX2 -= k * m_compNext.x;
			putX += deltaX2;
		}

	}
	else if (md == 2)
	{
		int sizeX2 = m_buttonSizeX * m_buttonMulti;
		sizeX2 /= 100;
		int sizeY2 = m_buttonSizeY * m_buttonMulti;
		sizeY2 /= 100;
//		int deltaX = (sizeX2 - m_buttonSizeX) / 2;
//		int deltaY = (sizeY2 - m_buttonSizeY) / 2;
		int deltaX = sizeX2 / 2;
		int deltaY = sizeY2 / 2;
		putX -= deltaX;
		putY -= deltaY;

		if (k>0)
		{
			int deltaX2 = ((k * m_compNext.x) * m_buttonMulti) / 100;
			deltaX2 -= k * m_compNext.x;
			putX += deltaX2;
		}

	}
	else
	{
		putX -= m_buttonSizeX / 2;
		putY -= m_buttonSizeY / 2;
	}



	if (ps == 100)
	{
		m_compPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
	}
	else
	{
		m_compPic->TransLucentBlt3(putX,putY,srcX,srcY,sizeX,sizeY,ps);
	}
}

void CCommonChartMenu::MakeAllTable(void)
{
	int i;
//	for (i=0;i<1280/4;i++)
	for (i=0;i<m_compTableBufferSize;i++)
	{
		m_compTable[i] = 0;
	}

	int chart = m_printChartNumber;
	int slotKosuu = m_chart[chart]->GetSlotKosuu();

	for (i=0;i<slotKosuu;i++)
	{
		int slot = m_chart[chart]->GetSlot(i);
		int routeKosuu = m_chart[chart]->GetRouteKosuu(slot);

		BOOL flg = TRUE;
		for (int k=0;k<routeKosuu;k++)
		{
			if (CheckRouteMita(slot,k+1) == FALSE)
			{
				flg = FALSE;
				break;
			}
		}

		int bitPattern = m_bitPattern[slot & 0x1f];
		int k2 = slot / 32;

		if (flg)
		{
			m_compTable[k2] |= bitPattern;
		}
	}





	
}


//for high speed
BOOL CCommonChartMenu::CheckComp(int slot)
{
	int bitPattern = m_bitPattern[slot & 0x1f];
	int k = slot / 32;
	if (m_compTable[k] & bitPattern) return TRUE;
	return FALSE;
}


BOOL CCommonChartMenu::CheckRouteMita(int slot,int k)
{
	int bitPattern = m_bitPattern[(slot & 3) * 8 + k - 1];
	if (m_mita[slot/4] & bitPattern) return TRUE;

	return FALSE;
}



int CCommonChartMenu::CalcuEdit2(void)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (m_editSaveCount > 0)
	{
		m_editSaveCount--;
	}

	if (m_mouseStatus->CheckClick(2))
	{
		m_chart[m_printChartNumber]->Save();
		m_editSaveNumber = m_printChartNumber;
		m_editSaveCount = 70;
	}


	POINT pt = m_mouseStatus->GetZahyo();

	int rt = m_growButton->Calcu(m_inputStatus);
	if (rt != NNNBUTTON_NOTHING)
	{
		int nm = ProcessCommonButton(rt);
		if (nm >= 0)
		{
			m_printChartNumber = nm;
			CheckAndSetPrintChartNumber();
			InitChangePage();

//			m_growButton->Init(nm);
//			ReLoadGrowPic();

//			int chartNumber = m_printChartNumber;
//			LoadBackChara(chartNumber);
//			LoadCenterPic(chartNumber);
//			LoadChartPic(chartNumber);
//			MakeAllTable();

			return -1;
		}

		int st = CCommonButton::GetButtonStatus(rt);
		if (st == NNNBUTTON_STARTCLICK) return -1;
		if (st == NNNBUTTON_CLICKING) return -1;
	}
















	int trig1 = m_mouseStatus->GetTrig(0);

	if (m_captureFlag == 1)
	{
		int dy = pt.y - m_captureStartY;
		m_miniWindowZahyoY = m_miniWindowZahyoStartY + dy;
		AdjustMiniWindowZahyo();
		CalcuScrollZahyo();
		AdjustInScroll();

		if (trig1 == 0)
		{
			m_captureFlag = 0;
		}

		return -1;
	}




	if (m_captureFlag == 2)
	{
		int dy = pt.y - m_captureStartY;
		if (m_mainCaptureOk == 1)
		{
			m_scrollY = m_mainWindowCaptureStartY - dy * m_mainCaptureReverse;
		}
		else if (m_mainCaptureOk == 3)
		{
			int ddy = (dy * (m_scrollSize - screenSizeY)) / screenSizeY;
			m_scrollY = m_mainWindowCaptureStartY - ddy * m_mainCaptureReverse;
		}

		AdjustInScroll();
		CalcuMiniWindowZahyo();


		if (trig1 == 0)
		{
			m_captureFlag = 0;
		}

		return -1;
	}






	if (m_mouseStatus->CheckClick(0))
	{
		m_captureStartY = GetOnMiniWindow(pt);
		m_miniWindowZahyoStartY = m_miniWindowZahyoY;

		if (m_captureStartY != -1)
		{
			JumpToMiniWindow();
			m_captureFlag = 1;
			return -1;
		}


		m_mainWindowCaptureStartX = pt.x;
		m_mainWindowCaptureStartY = pt.y;


	}



	int wheel = m_mouseStatus->GetWheel();
	if (wheel != 0)
	{
		if (wheel>0)
		{
			m_scrollY -= m_scrollSpeedY;
		}
		else
		{
			m_scrollY += m_scrollSpeedY;
		}

		AdjustInScroll();
		CalcuMiniWindowZahyo();
		return -1;
	}





	if (m_editCatchNumber != -1)
	{
		int deltaX = pt.x - m_editCatchStart.x;
		int deltaY = pt.y - m_editCatchStart.y;

		POINT pt2;
		pt2.x = m_editStartPoint.x + deltaX;
		pt2.y = m_editStartPoint.y + deltaY;
		m_chart[m_printChartNumber]->SetZahyo(m_editCatchNumber,pt2);

		if (m_mouseStatus->GetTrig(0) == 0)
		{
			m_editCatchNumber = -1;
			return -1;
		}

		return -1;
	}



	m_scrollX += 1;
	m_scrollX %= screenSizeX;

	if (m_mouseStatus->GetTrig(0))
	{
		m_onButtonNumber = -1;
		CheckOnButton2(pt);

		if (m_onButtonNumber != -1)
		{
			m_editCatchNumber = m_onButtonNumber;
			m_editStartPoint = m_chart[m_printChartNumber]->GetZahyo(m_editCatchNumber);
			m_editCatchStart = pt;
			return -1;
		}


		if (m_onButtonNumber == -1)
		{
			//check in main
			if (CheckInSlotArea(pt))
			{
				m_captureStartY = pt.y;
//				m_mainWindowCaptureStartX = pt.x;
				m_mainWindowCaptureStartY = m_scrollY;

				m_captureFlag = 2;
				m_descPrintNumber = -1;
				return -1;
			}
		}

	}

	return -1;
}

int CCommonChartMenu::CalcuCatch(void)
{
	if (m_mouseStatus->GetTrig(1) == 0)
	{
		m_catchFlag = FALSE;
		return -1;
	}

	POINT pt = m_mouseStatus->GetZahyo();
	m_growButton->Calcu(NULL);

	int deltaX = pt.x - m_catchStart.x;
	int deltaY = pt.y - m_catchStart.y;

	POINT pt2;
	pt2.x = m_catchStartPoint.x + deltaX;
	pt2.y = m_catchStartPoint.y + deltaY;

	//adjust in area

//	int x = pt2.x - m_slotAreaStartX;
//	int y = pt2.y - m_slotAreaStartY;
	int x = pt2.x;
	int y = pt2.y;

	int x1 = m_buttonSizeX / 2;
	int x2 = m_slotAreaSizeX - m_buttonSizeX / 2;

	int y1 = m_buttonSizeY / 2;
	int y2 = m_scrollSize - m_buttonSizeY / 2;


	if (x < x1) x = x1;
	if (x > x2) x = x2;
	if (y < y1) y = y1;
	if (y > y2) y = y2;

	pt2.x = x;
	pt2.y = y;



//	if (pt2.x < 150) pt2.x = 150;
//	if (pt2.y < 0) pt2.y = 0;
//	if (pt2.x > 700) pt2.x = 700;
//	if (pt2.y > m_scrollSize+290) pt2.y = m_scrollSize+290;

	m_chart[m_printChartNumber]->SetZahyo(m_catchNumber,pt2);

	return -1;
}


void CCommonChartMenu::PrintEditStatus2(void)
{
	char mes[256];
	if (m_editSaveCount > 0)
	{
		wsprintf(mes,"ＳＡＶＥ：%d",m_editSaveNumber);
		m_message->PrintMessage(350,300,mes);
	}

	if (m_editCatchNumber != -1)
	{
		POINT pt = m_chart[m_printChartNumber]->GetZahyo(m_editCatchNumber);
		wsprintf(mes,"スロット%d（%d，%d）",m_editCatchNumber,pt.x,pt.y);
		m_message->PrintMessage(200,0,mes);
	}
}


void CCommonChartMenu::CheckWindowUpDown(POINT pt)
{
	if (m_messageUpDown == 0)
	{
		if (pt.y >= m_messageWindowZahyo[m_messageUpDown].y - 64)
		{
			m_messageUpDown = 1;
		}
	}
	else
	{
		if (pt.y < m_messageWindowZahyo[m_messageUpDown].y + m_messageWindowSize.cy + 64)
		{
			m_messageUpDown = 0;
		}
	}
}


void CCommonChartMenu::PutMiniMapButton(POINT pt,int n)
{
	int putX = pt.x;
	int putY = pt.y;

	if (n == 3)
	{
		if (m_miniMapTenmetsuColor == 0) return;
	}
	int md = n;

	int sizeX = m_miniMapButtonSizeX;
	int sizeY = m_miniMapButtonSizeY;
	int srcX = md * sizeX;
	int srcY = 0;

	m_miniMapButtonPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
}

void CCommonChartMenu::CalcuMiniMapButtonAnime(void)
{
	m_miniMapTenmetsuCount++;
	if (m_miniMapTenmetsuCount >= m_miniMapTenmetsuTime)
	{
		m_miniMapTenmetsuCount = 0;
		m_miniMapTenmetsuColor++;
		m_miniMapTenmetsuColor %= 2;
	}
}

POINT CCommonChartMenu::ToMiniMapZahyo(POINT pt)
{
	int x = pt.x;// - m_slotAreaStartX;
	int y = pt.y;// - m_slotAreaStartY;

	x *= m_miniMapSize[m_printChartNumber].cx;
	y *= m_miniMapSize[m_printChartNumber].cy;

	x /= m_slotAreaSizeX;
	if (m_scrollSize > 0)
	{
		y /= m_scrollSize;
	}

//	int x = pt.x / 10;
//	int y = (pt.y * 180) / m_scrollSize;

	x -= m_miniMapButtonSizeX / 2;
	y -= m_miniMapButtonSizeY / 2;

	POINT pt2 = GetMiniMapAreaZahyo();

	pt2.x += x;
	pt2.y += y;

	return pt2;
}

void CCommonChartMenu::FinalExitRoutine(void)
{
	if (m_exitModeFlag)
	{
		int fromSlot = m_nowSlotNumber;
		
		if (m_fromNumberVarNumber != -1)
		{
			m_game->SetVarData(m_fromNumberVarNumber,fromSlot);
		}

		if (m_slotNumberVarNumber != -1)
		{
			m_game->SetVarData(m_slotNumberVarNumber,m_selectNumber);
		}

		int roadNumber = SearchRoad(fromSlot,m_selectNumber);
		if (roadNumber == -1)
		{

			LoadChartData(m_selectNumber);
		}

		if (m_newMarkPrintFlag)
		{
			if (m_newMarkFlag != 0)
			{
				if (m_newMarkVarNumber != -1)
				{
					int v = m_game->GetVarData(m_newMarkVarNumber);
					int nm = m_newMarkFlag;


					int cp = SlotToChart(m_selectNumber);
					nm &= m_bitPattern[cp];



					v |= nm;



					m_game->SetVarData(m_newMarkVarNumber,v);
				}
			}
		}

		m_game->SetYoyaku();
	}
}


void CCommonChartMenu::CalcuMiniWindowSize(void)
{
	int ml = m_miniMapSize[m_printChartNumber].cy;
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	m_miniWindowSize = (ml * screenSizeY) / m_scrollSize;
}


void CCommonChartMenu::CalcuScrollZahyo(void)
{
	int dv = m_miniMapSize[m_printChartNumber].cy;
	m_scrollY = (m_miniWindowZahyoY * m_scrollSize) / dv;
}


void CCommonChartMenu::CalcuMiniWindowZahyo(void)
{
	int ml = m_miniMapSize[m_printChartNumber].cy;
	m_miniWindowZahyoY = (m_scrollY * ml) / m_scrollSize;
}


int CCommonChartMenu::GetOnMiniWindow(POINT pt)
{
	POINT pt2 = GetNowMiniMapZahyo();

	int dx = pt.x - pt2.x;

	if ((dx<0) || (dx>=m_miniMapSize[m_printChartNumber].cx)) return -1;

	int dy = pt.y - pt2.y;
	if ((dy<0) || (dy>=m_miniMapSize[m_printChartNumber].cy)) return -1;

	return pt.y;
}

void CCommonChartMenu::AdjustInScroll(void)
{
	int screenSizeY = CMyGraphics::GetScreenSizeY();
	if (m_scrollY > (m_scrollSize - screenSizeY)) m_scrollY = m_scrollSize - screenSizeY;
	if (m_scrollY < 0) m_scrollY = 0;
}


void CCommonChartMenu::ReLoadGrowPic(void)
{
	for (int i=0;i<m_chartListKosuu;i++)
	{
		int st = 0;
		if (i == m_printChartNumber) st = 1;

//		if (i == m_page) st = 1;

		CPicture* lpPic = m_growButton->GetPicture(i,st);
		LPSTR name = m_growButton->GetFileName(i,st);
		char filename[256];
		wsprintf(filename,"sys\\%s",name);
		lpPic->LoadDWQ(filename);
	}
}




void CCommonChartMenu::InitChangePage(void)
{
	LoadBackChara(m_printChartNumber);
	LoadCenterPic(m_printChartNumber);
	LoadChartPic(m_printChartNumber);
	LoadMiniMapBasePic(m_printChartNumber);

	m_growButton->Init(m_printChartNumber);
	ReLoadGrowPic();

	m_scrollSize = m_chart[m_printChartNumber]->GetMaxSize();
	m_scrollSize += m_bottomSpace;

	AdjustInScroll();
	CalcuMiniWindowSize();
	CalcuMiniWindowZahyo();

	m_maeOnSlot = -1;

	m_editCatchNumber = -1;
	m_editSaveNumber = 0;
	m_editSaveCount = 0;


	MakeAllTable();
}


void CCommonChartMenu::PrintPlayMap(void)
{
	int n = m_chartNumber;
	int st = 0;
	if (m_chartNumber == m_printChartNumber) st = 1;
	POINT pt = m_buttonZahyo[n*2+st];

	int putX = pt.x;
	int putY = pt.y;

//	int sizeX = 99;
//	int sizeY = 27;
//	m_chartMapNowPic->Blt(putX,putY,0,0,sizeX,sizeY,TRUE);
	m_chartMapNowPic->Put(putX,putY,TRUE);
}


void CCommonChartMenu::PrintTasseido(void)
{
	m_tasseidoBasePic->Put(m_tasseidoBasePrintX,m_tasseidoBasePrintY,TRUE);

	m_suuji->Print(m_totalTasseidoPrintX,m_totalTasseidoPrintY,m_totalMitaPercent);
	m_suuji->Print(m_tasseidoPrintX,m_tasseidoPrintY,m_mitaPercent[m_printChartNumber]);
}


BOOL CCommonChartMenu::CheckMita(int slot)
{
	char* ptr = (char*)m_mita;
	if (ptr[slot]) return TRUE;
	return FALSE;
}




void CCommonChartMenu::SaveChartData(BOOL changeModeFlag)
{
	if (changeModeFlag)
	{
		m_game->SetSaveMode(SELECTCHART_MODE);
	}
	else
	{
		m_game->SetSaveMode(TITLE_MODE);
//		m_game->SetSaveMode(m_game->GetGameMode());
	}

	m_game->TaihiAllEffect();

	int slot = GetSlotNumber();
	int chart = slot / m_blockSize;


	char filename[1024];

	LPSTR saveFolder = CMySaveFolder::GetFullFolder();
	wsprintf(filename,"%s\\chart%d\\slot%d.dat",saveFolder,chart+1,slot);
//	wsprintf(filename,"sav\\mushiex\\chart%d\\slot%d.dat",chart,m_nowSlotNumber);
	FILE* file = NULL;
	fopen_s(&file,filename,"wb");
	if (file != NULL)
	{
		CCommonDataFile::GAMESTATUS* gameStatus = (CCommonDataFile::GAMESTATUS*)m_commonBuffer;
		int sz = sizeof(CCommonDataFile::GAMESTATUS);
		ZeroMemory(gameStatus,sz);

		m_game->GetGameStatusForSave(gameStatus);

		SYSTEMTIME st;
		GetLocalTime(&st);

		gameStatus->year = st.wYear;
		gameStatus->month = st.wMonth;
		gameStatus->day = st.wDay;
		gameStatus->week = st.wDayOfWeek;
		gameStatus->hour = st.wHour;
		gameStatus->minute = st.wMinute;
		gameStatus->second = st.wSecond;
		gameStatus->milli = st.wMilliseconds;

		gameStatus->saveCount++;


		MakeHeader((int*)gameStatus,sz,GAMEDATATYPE_STATUS,"GAMESTATUS");

		fwrite(gameStatus,sizeof(CCommonDataFile::GAMESTATUS),1,file);


		//圧縮変数
		int* varPtr = (int*)m_commonBuffer;
		int* varPtr0 = varPtr;
		varPtr++;
		int ln = 0;
		sz = 0;
		for (int i=0;i<1000;i++)
		{
			int var = m_game->GetVarData(i);
			if (var == 0)
			{
				ln++;
			}
			else
			{
				if (ln > 0)
				{
					*varPtr = 0;
					varPtr++;
					*varPtr = ln;
					varPtr++;
					sz += 2;
					ln = 0;
				}
				*varPtr = var;
				varPtr++;
				sz += 1;
			}
		}
		if (ln>0)
		{
			*varPtr = 0;
			varPtr++;
			*varPtr = ln;
			varPtr++;
			sz += 2;
			ln = 0;
		}
		*varPtr0 = sz*4;
		fwrite(varPtr0,sizeof(int),sz+1,file);


		//圧縮ルート
		char* movePtr = (char*)m_commonBuffer;
		int* movePtr0 = (int*)movePtr;
		movePtr += 4;


		ln = 0;
		sz = 0;
//		int lp = m_chartListKosuu * m_blockSize;
		int lp = m_moveRoadSize;

		for (int i=0;i<lp;i++)
		{
			char c = m_moveRoad[i];
			if (c == 0)
			{
				if (ln<254)
				{
					ln++;
				}
				else
				{
					ln++;
					*movePtr = 0;
					movePtr++;
					*movePtr = (char)ln;
					movePtr++;
					sz += 2;
					ln = 0;
				}
			}
			else
			{
				if (ln > 0)
				{
					*movePtr = 0;
					movePtr++;
					*movePtr = (char)ln;
					movePtr++;
					sz += 2;
					ln = 0;
				}
				*movePtr = c;
				movePtr++;
				sz += 1;
			}
		}

		if (ln > 0)
		{
			*movePtr = 0;
			movePtr++;
			*movePtr = (char)ln;
			movePtr++;
			sz += 2;
			ln = 0;
		}
		*movePtr0 = sz;
		fwrite(movePtr0,sizeof(char),sz+4,file);

		//圧縮選択OK
		ln = 0;
		sz = 0;
		int* selPtr = (int*)m_commonBuffer;
		int* selPtr0 = selPtr;
		selPtr++;

		//lp = (m_chartListKosuu * m_blockSize + 31) / 32;
		lp = m_canSelectSize;
		for (int i=0;i<lp;i++)
		{
			int ok = m_canSelect[i];
			if (ok == 0xffffffff)
			{
				ln++;
			}
			else
			{
				if (ln > 0)
				{
					*selPtr = 0xffffffff;
					selPtr++;
					*selPtr = ln;
					selPtr++;
					sz += 2;
					ln = 0;
				}
				*selPtr = ok;
				selPtr++;
				sz += 1;
			}
		}
		if (ln > 0)
		{
			*selPtr = 0xffffffff;
			selPtr++;
			*selPtr = ln;
			selPtr++;
			sz += 2;
			ln = 0;
		}
		*selPtr0 = sz * 4;
		fwrite(selPtr0,sizeof(int),sz+1,file);


		fclose(file);
	}
}

void CCommonChartMenu::LoadChartData(int slot)
{
	int chart = slot / m_blockSize;

	char filename[1024];
	LPSTR saveFolder = CMySaveFolder::GetFullFolder();
	wsprintf(filename,"%s\\chart%d\\slot%d.dat",saveFolder,chart+1,slot);
//	wsprintf(filename,"sav\\mushiex\\chart%d\\slot%d.dat",chart,slot);
	FILE* file = NULL;
	fopen_s(&file,filename,"rb");
	if (file != NULL)
	{
		CCommonDataFile::GAMESTATUS* gameStatus = (CCommonDataFile::GAMESTATUS*)m_commonBuffer;
		fread(gameStatus,sizeof(CCommonDataFile::GAMESTATUS),1,file);
		m_game->SetGameStatusByLoad(gameStatus);

		//圧縮変数
		int* varPtr = (int*)m_commonBuffer;
		int sz = 0;
		fread(&sz,sizeof(int),1,file);
		fread(varPtr,sizeof(char),sz,file);
		sz /= 4;
		int k = 0;
		int ln = 0;

		int n = 0;
		while (k<sz)
		{
			ln = 1;
			int d = *(varPtr+k);
//			d++;
			k++;
			if (d == 0)
			{
				ln = *(varPtr+k);
				k++;
			}
			
			for (int i=0;i<ln;i++)
			{
				if ((n<200) || (n>=300))
				{
					m_game->SetVarData(n,d);
				}
				n++;
			}
		}


		//圧縮ルート
		char* movePtr = (char*)m_commonBuffer;
		fread(&sz,sizeof(int),1,file);
		fread(movePtr,sizeof(char),sz,file);
		k=0;
		n=0;
		while (k<sz)
		{
			ln = 1;
			char c = *(movePtr+k);
			k++;
			if (c == 0)
			{
				ln = (int)(*(movePtr+k));
				ln &= 0xff;
				k++;
			}
			for (int i=0;i<ln;i++)
			{
				m_moveRoad[n] = c;
				n++;
			}
		}


		//圧縮選択OK
		ln = 0;
		sz = 0;
		int* selPtr = (int*)m_commonBuffer;
		fread(&sz,sizeof(int),1,file);
		fread(selPtr,sizeof(char),sz,file);

		sz /= 4;
		k=0;
		n=0;
		while (k<sz)
		{
			ln = 1;
			int d = *(selPtr+k);
			k++;
			if (d == 0xffffffff)
			{
				ln = *(selPtr+k);
				k++;
			}
			for (int i=0;i<ln;i++)
			{
				m_canSelect[n] = d;
				n++;
			}
		}

		fclose(file);
	}
}

void CCommonChartMenu::MakeHeader(int* work, int sz, int cd, LPSTR mes)
{
	CCommonDataFile::GAMEHEADER* header = (CCommonDataFile::GAMEHEADER*)work;

	header->general.size = sz;
	header->general.code = cd;
	header->general.dummy1 = 0;
	header->general.dummy2 = 0;

	ZeroMemory(header->general.message,16);

	int ln = strlen(mes);
	if (ln>15) ln = 15;
	memcpy(header->general.message,mes,ln);
}





int CCommonChartMenu::CalcuWarning(void)
{
	int rt = m_dialogButton->Calcu(m_inputStatus);
	if (rt == NNNBUTTON_NOTHING) return -1;

	int nm = ProcessButtonGroup(rt);
	
	if (nm == 0)
	{
//		SaveNowData();

//		m_warningFlag = FALSE;
		m_exitModeFlag = TRUE;
		return ReturnFadeOut(-1);

//		m_clickingFlag = FALSE;
//		m_updownBack->Init();
//		InitAnime();
//		CAreaControl::SetNextAllPrint();
	}
	else if (nm == 1)
	{
		m_warningFlag = FALSE;
//		m_updownBack->Init();
//		InitAnime();
//		CAreaControl::SetNextAllPrint();
	}

	return -1;
}

void CCommonChartMenu::AfterPrint(void)
{
	if (m_reloadDataFlag)
	{
		m_reloadDataFlag = FALSE;
		LoadChartData(m_nowSlotNumber);
	}

}


void CCommonChartMenu::InitSelectOk(void)
{
//	int sz = (m_blockSize * m_chartListKosuu + 31) / 32;
	int sz = m_canSelectSize;

	for (int i=0;i<sz;i++)
	{
		m_canSelect[i] = 0xffffffff;
	}
}


BOOL CCommonChartMenu::CheckSelectOk(int slot)
{
	if (GetSelectOk(slot) == FALSE) return FALSE;

//	int chart = m_playMapNumber;
	int chart = m_chartNumber;
	int nextKosuu = m_chart[chart]->GetNextKosuu(m_nowSlotNumber);
	for (int i=0;i<nextKosuu;i++)
	{
		if (m_chart[chart]->GetNext(m_nowSlotNumber,i) == slot) return TRUE;
	}

	return FALSE;
}

BOOL CCommonChartMenu::CheckSelectOk2(int slot)
{
	if (GetSelectOk(slot) == FALSE) return FALSE;

	if (CheckMita(slot)) return TRUE;

//	int chart = SlotToChart(slot);
//	if (m_chart[chart]->CheckTop(slot))
//	{
//		return TRUE;
//	}

	return FALSE;
}

void CCommonChartMenu::SetSelectOk(int slot,BOOL flg)
{
	int bitPattern = m_bitPattern[slot & 0x1f];
	int k = slot / 32;

	m_canSelect[k] &= ~bitPattern;
	if (flg)
	{
		m_canSelect[k] |= bitPattern;
	}
}

BOOL CCommonChartMenu::GetSelectOk(int slot)
{
	int bitPattern = m_bitPattern[slot & 0x1f];
	int k = slot / 32;
	if ((m_canSelect[k] & bitPattern) == 0) return FALSE;

	//check var
	int chart = SlotToChart(slot);
	int varNumber = m_chart[chart]->GetVarNumber(slot);
	if (varNumber != -1)
	{
		if (m_game->GetVarData(varNumber) == 0) return FALSE;
	}
	return TRUE;
}


void CCommonChartMenu::GetExtDataForSave(LPVOID ptr,int extNumber)
{
//	int sz = (m_blockSize * m_chartListKosuu + 31) / 32;
//	int szz = (sz + 3) & (~3);

	memcpy(ptr,m_canSelect,m_canSelectSize*sizeof(int));
	char* ptr2 = (char*)ptr;
	ptr2 += m_canSelectSize * sizeof(int);

//	sz = m_blockSize*m_chartListKosuu;
//	szz = (sz + 15) & (~15);//16byte padding

	memcpy(ptr2,m_moveRoad,m_moveRoadSize);
}



void CCommonChartMenu::SetExtDataByLoad(LPVOID ptr,int extNumber)
{
//	int sz = (m_blockSize * m_chartListKosuu + 31) / 32;
//	int szz = (sz + 3) & (~3);

	memcpy(m_canSelect,ptr,m_canSelectSize*sizeof(int));
	char* ptr2 = (char*)ptr;
	ptr2 += m_canSelectSize * sizeof(int);

//	sz = m_blockSize*m_chartListKosuu;
//	szz = (sz + 15) & (~15);//16byte padding
	memcpy(m_moveRoad,ptr2,m_moveRoadSize);

	m_reloadDataFlag = FALSE;
	m_warningFlag = FALSE;

}


void CCommonChartMenu::CalcuLineColor(void)
{
	m_lineColorCount++;
	m_lineColorCount %= m_lineColorCountMax;
}


void CCommonChartMenu::CalcuButtonMulti(void)
{
	m_buttonCount++;
	m_buttonCount %= m_buttonCountMax;

	int dv = m_buttonCountMax / 2;
	int c = m_buttonCount;
	if (c>=dv)
	{
		c = m_buttonCountMax - c;
	}

	m_buttonMulti = 100 + ((m_buttonMultiMax - 100)*c) / dv;
}


BOOL CCommonChartMenu::CheckChartOpen(int block)
{
	if (m_chartOpenVar == -1) return TRUE;
	if (block < m_basicChartKosuu) return TRUE;
	int n = block - m_basicChartKosuu;

	int bitPattern = m_bitPattern[n & 0x1f];
	int d = m_game->GetVarData(m_chartOpenVar);
	if (d & bitPattern) return TRUE;
	return FALSE;
}

BOOL CCommonChartMenu::CheckExistClickOk(int block)
{
	int kosuu = m_chart[block]->GetSlotKosuu();

	for (int k=0;k<kosuu;k++)
	{
		int slot = m_chart[block]->GetSlot(k);
		if (CheckSelectOk(slot))
		{
			return TRUE;
		}

		if (CheckSelectOk2(slot))
		{
			return TRUE;
		}
	}

	return FALSE;
}


void CCommonChartMenu::CalcuMitaPercent(void)
{
	for (int i=0;i<m_chartListKosuu;i++)
	{
		CountMita(i);
	}
	CountTotalMita();

	for (int i=0;i<m_chartListKosuu;i++)
	{
		int ps = (m_mitaKosuu[i] * 100) / m_eventKosuu[i];
		if (ps == 0)
		{
			if (m_mitaKosuu[i] > 0) ps = 1;
		}

		if (ps >= 100)
		{
			if (m_mitaKosuu[i] < m_eventKosuu[i]) ps = 99;
		}
	
		m_mitaPercent[i] = ps;
	}

	int ps = (m_totalMitaKosuu * 100) / m_totalEventKosuu;
	if (ps == 0)
	{
		if (m_totalMitaKosuu>0) ps = 1;
	}

	if (ps >= 100)
	{
		if (m_totalMitaKosuu < m_totalEventKosuu) ps = 99;
	}

	m_totalMitaPercent = ps;


	//m_calcuMitaFlag = TRUE;
}



void CCommonChartMenu::LoadWarningPic(void)
{
	char filename[256];
	wsprintf(filename,"sys\\%s",m_dialogFileName);
	m_commonParts->LoadDWQ(filename);

	for (int i=0;i<2;i++)
	{
		CPicture* lpPic = m_dialogButton->GetPicture(i);
		LPSTR name = m_dialogButton->GetFileName(i);
		char filename[256];
		wsprintf(filename,"sys\\%s",name);
		lpPic->LoadDWQ(filename);
	}
}



int CCommonChartMenu::GetFromNumber(void)
{
	if (m_fromNumberVarNumber != -1)
	{
		return m_game->GetVarData(m_fromNumberVarNumber);
	}

	return 0;
}

int CCommonChartMenu::GetSlotNumber(void)
{
	if (m_slotNumberVarNumber != -1)
	{
		return m_game->GetVarData(m_slotNumberVarNumber);
	}

	return 0;
}

void CCommonChartMenu::SetSlotNumber(int slot)
{
	if (m_slotNumberVarNumber != -1)
	{
		m_game->SetVarData(m_slotNumberVarNumber,slot);
	}
}

void CCommonChartMenu::SetFromSlot(int slot)
{
	if (m_fromNumberVarNumber != -1)
	{
		m_game->SetVarData(m_fromNumberVarNumber,slot);
	}
}

int CCommonChartMenu::SlotToChart(int slot)
{
	return slot / m_blockSize;
}

int CCommonChartMenu::GetRoadKosuu(int fromSlot)
{
	int chart = SlotToChart(fromSlot);
	return m_chart[chart]->GetNextKosuu(fromSlot);
}

int CCommonChartMenu::GetRouteKosuu(int slot)
{
	int chart = SlotToChart(slot);
	return m_chart[chart]->GetRouteKosuu(slot);
}

int CCommonChartMenu::SearchRoad(int fromSlot,int toSlot)
{
	int chart = SlotToChart(fromSlot);
	int kosuu = m_chart[chart]->GetNextKosuu(fromSlot);
	for (int i=0;i<kosuu;i++)
	{
		if (m_chart[chart]->GetNext(fromSlot,i) == toSlot)
		{
			return i;
		}
	}

	return -1;
}


BOOL CCommonChartMenu::CheckInSlotArea(POINT pt)
{
	int dx = pt.x - m_slotAreaStartX;
	int dy = pt.y - m_slotAreaStartY;
	int sizeX = m_slotAreaSizeX;
	int sizeY = m_slotAreaSizeY;

	if ((dx>=0) && (dy>=0) && (dx<sizeX) && (dy<sizeY)) return TRUE;
	return FALSE;
}


void CCommonChartMenu::AdjustMiniWindowZahyo(void)
{
	int limit = m_miniMapSize[m_printChartNumber].cy - m_miniWindowSize;
	if (m_miniWindowZahyoY>limit) m_miniWindowZahyoY = limit;


	if (m_miniWindowZahyoY<0) m_miniWindowZahyoY = 0;
}

void CCommonChartMenu::PrintCapturePic(void)
{
	if (m_captureFlag == 2)
	{
		if (m_mainCapturePic != NULL)
		{
			POINT pt = m_mouseStatus->GetZahyo();
			int putX = pt.x + m_mainCapturePicDelta.x;
			int putY = pt.y + m_mainCapturePicDelta.y;

			m_mainCapturePic->Put(putX,putY,TRUE);
		}
	}
}

void CCommonChartMenu::JumpToMiniWindow(void)
{
	if (m_autoJumpMiniWindow == 0) return;

	POINT pt2 = GetMiniMapWindowZahyo();
	int dy = m_captureStartY - pt2.y;

	if ((dy < m_miniWindowZahyoY) || (dy >= m_miniWindowZahyoY + m_miniWindowSize + m_miniMapWindowUpSize + m_miniMapWindowDownSize))
	{
		m_miniWindowZahyoY = dy - (m_miniWindowSize + m_miniMapWindowUpSize + m_miniMapWindowDownSize)/ 2;
		AdjustMiniWindowZahyo();
		CalcuScrollZahyo();
		AdjustInScroll();
		m_miniWindowZahyoStartY = m_miniWindowZahyoY;
	}
}


//開始時 slot=0,from=0
//->
//slot=1,mita(slot),from=1

//command
//route from->slot if exist route
//from=slot
//if all mita(slot)



void CCommonChartMenu::StartUserCommand(int paraKosuu,int* paraPtr)
{
	int slot = GetSlotNumber();
	
	if (slot == 0)
	{
		//first chart menu
		SetSlotNumber(1);
		SetMita(1);
	}
	else
	{
		int fromSlot = GetFromNumber();
		int road = SearchRoad(fromSlot,slot);
		if (road != -1)
		{
			SetMoveRoad(fromSlot,road);
		}

		int routeKosuu = GetRouteKosuu(slot);
		if (routeKosuu <= 1)
		{
			SetMita(slot);
		}
	}

	SetFromSlot(slot);
	SaveChartData();

	//auto next?
	BOOL nextOnFlag = FALSE;

	if (m_autoNextOn)
	{
		int block = slot / m_blockSize;
		int nextKosuu = m_chart[block]->GetNextKosuu(slot);
		if (nextKosuu == 1)
		{
			int nextSlot = m_chart[block]->GetNext(slot,0);
			int nextBlock = nextSlot / m_blockSize;
			if (nextBlock != block)
			{
				SetSlotNumber(nextSlot);
				int fromSlot = GetFromNumber();
				int road = SearchRoad(fromSlot,nextSlot);
				if (road != -1)
				{
					SetMoveRoad(fromSlot,road);
				}
				SetMita(nextSlot);

				SetFromSlot(nextSlot);
				m_printChartNumber = nextSlot / m_blockSize;
				CheckAndSetPrintChartNumber();
				SaveChartData();
				nextOnFlag = TRUE;
			}
		}
	}

	if (nextOnFlag == FALSE)
	{
//		m_printChartNumber = m_nowSlotNumber / m_blockSize;
//		CheckAndSetPrintChartNumber();
	}
}



	//0:setroute
	//1:getchartpercent
	//2:checkcompslot
	//3:openchart
	//4:sloton

void CCommonChartMenu::Function(int type,int paraKosuu,int* lpParam)
{
	OutputDebugString("\n\nFunction動作しました\n\n");

	int para0 = 0;
	int para1 = 0;
	if (paraKosuu >= 1) para0 = *lpParam;
	if (type == 4)
	{
		para1 = 1;
	}
	if (paraKosuu >= 2) para1 = *(lpParam+1);


	switch (type)
	{
	case 0:
		FunctionSetMita(para0);
		break;
	case 1:
		FunctionGetChartPercent(para0);
		break;
	case 2:
		FunctionCheckCompSlot();
		break;
	case 3:
		FunctionOpenChart(para0);
		break;
	case 4:
		FunctionSlotOn(para0,para1);
		break;
	case 5:
		FunctionSlotOpen(para0);
		break;
	}
}

void CCommonChartMenu::FunctionSetMita(int route)
{
	int slot = GetSlotNumber();
	SetMita(slot,route);
}


void CCommonChartMenu::FunctionGetChartPercent(int chart)
{
	int ps = 0;

	if (chart == -1)//total
	{
		ps = m_totalMitaPercent;
	}
	else if (chart == 0)//基本チャートのみ
	{
		int mita = 0;
		int dv = 0;
		for (int i=0;i<m_basicChartKosuu;i++)
		{
			mita += m_mitaKosuu[i];
			dv += m_eventKosuu[i];
		}

		if (dv<1) dv = 1;
		ps = (mita * 100) / dv;
		if (ps == 0)
		{
			if (mita>0) ps = 1;
		}
		if (ps >= 100)
		{
			if (mita < dv)
			{
				ps = 99;
			}
		}
	}
	else
	{
		ps = m_mitaPercent[chart-1];
	}

	if (m_chartPercentVarNumber != -1)
	{
		m_game->SetVarData(m_chartPercentVarNumber,ps);
	}
}


void CCommonChartMenu::FunctionCheckCompSlot(void)
{
	int slot = GetSlotNumber();
	int flg = 0;

	if (CheckComplete(slot))
	{
		flg = 1;
	}
	
	if (m_checkCompVarNumber != -1)
	{
		m_game->SetVarData(m_checkCompVarNumber,flg);
	}
}

void CCommonChartMenu::FunctionOpenChart(int chart)
{
	int n = chart - m_basicChartKosuu - 1;

	OpenChart(n);
}


void CCommonChartMenu::FunctionSlotOn(int slot,int flg)
{
	SetSelectOk(slot,flg);
}


void CCommonChartMenu::FunctionSlotOpen(int slot)
{
	int oldSlot = GetFromNumber();
	SetFromSlot(slot);
	SetMita(slot);
	SaveChartData();
	SetFromSlot(oldSlot);
}

void CCommonChartMenu::OpenChart(int n)
{
	if ((n>=0) && (n<31))
	{
		if (m_chartOpenVar != -1)
		{
			int d = m_game->GetVarData(m_chartOpenVar);
			int bitPattern = m_bitPattern[n];
			d |= bitPattern;
			m_game->SetVarData(m_chartOpenVar,d);

			m_game->SaveSystemFile();
		}
	}
}

void CCommonChartMenu::AfterInitNewGame(void)
{
	m_printChartNumber = 0;

//	m_printChartNumberTmp = 0;

	InitMoveRoad();
}

void CCommonChartMenu::InitByLoad(void)
{
	m_nowSlotNumber = GetSlotNumber();

	m_printChartNumber = m_nowSlotNumber / m_blockSize;
//	m_printChartNumberTmp = m_printChartNumber;
	if (m_savePrintChartFlag)
	{
		if (m_printNumberVarNumber != -1)
		{
			m_printChartNumber = m_game->GetVarData(m_printNumberVarNumber);
		}
	}
}



//exitgame
//if all mita(slot)
//route from->slot if exist route

void CCommonChartMenu::ExitGame(void)
{
	OutputDebugString("\n\nExitGame動作しました\n");

	int slot = GetSlotNumber();
	if (slot == 0)//dont start	
	{
		return;
	}

	int fromSlot = GetFromNumber();
	int road = SearchRoad(fromSlot,slot);
	if (road != -1)
	{
		SetMoveRoad(fromSlot,road);
	}

	int routeKosuu = GetRouteKosuu(slot);
	if (routeKosuu <= 1)
	{
		SetMita(slot);
	}

	SetFromSlot(slot);
	SaveChartData(FALSE);
}


void CCommonChartMenu::CheckAndSetPrintChartNumber(void)
{
	if (m_savePrintChartFlag)
	{
		if (m_printNumberVarNumber != -1)
		{
			m_game->SetVarData(m_printNumberVarNumber,m_printChartNumber);
		}
	}
//	m_printChartNumberTmp = m_printChartNumber;
}

/*_*/


