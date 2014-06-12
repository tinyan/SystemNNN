//
// gameCallBack.cpp
//

#include <windows.h>
#include <process.h>
//#include <stddef.h>
#include <stdlib.h>
//#include <conio.h>


#if defined _TINYAN3DLIB_
#include <d3dx9.h>
#endif





//#include <windows.h>
#include <stdio.h>

#include <WINNLS32.H>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\myFile.h"

#include "..\nyanPictureLib\jpegDecoder.h"

#if !defined _TINYAN3DLIB_
#include "..\nyanDirectXLib\myDirectSoundBuffer.h"
#include "..\nyanDirectXLib\myDirectShow.h"
#else
#include "..\nyanDirectXLib\myDirectSoundBuffer.h"
#include "..\nyanDirectXLib\myDirectShow.h"
//#include "..\..\systemNNN3D\nyanDirectX3DLib\myDirectSoundBuffer.h"
//#include "..\..\systemNNN3D\nyanDirectX3DLib\myDirectShow.h"
#endif


//#include <qedit.h>

#if !defined _TINYAN3DLIB_
#include "..\nyanDirectXLib\nyanDirectXLibCompileDesc.h"
#else
#include "..\nyanDirectXLib\nyanDirectXLibCompileDesc.h"
//#include "..\..\systemNNN3D\nyanDirectX3DLib\nyanDirectXLibCompileDesc.h"
#endif

#include "..\nyanLib\nyanLibCompileDesc.h"
#include "..\nnnUtilLib\nnnUtilLibCompileDesc.h"
#include "nnnLibCompileDesc.h"

//#include "..\nyanEffectLib\effectStruct.h"
//#include "..\nyanEffectLib\effectStruct.h"


#include "..\nyanLib\include\picture.h"


#include "..\nyanEffectLIB\commoneffect.h"
#include "..\nyanEffectAnimeLIB\effectAnimation.h"


#include "..\nyanLib\include\allGraphics.h"

#include "..\nyanLib\include\allGeo.h"


#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"

#include "..\nnnUtilLib\nnnButtonStatus.h"
#include "..\nnnUtilLib\inputStatus.h"

#include "..\nnnUtilLib\commonButton.h"

#include "..\nnnUtilLib\menuButtonGroup.h"
#include "..\nnnUtilLib\menuButtonSetup.h"

//#include "..\nnnUtilLib\nnnButtonStatus.h"

//#include "..\nnnUtilLib\waveMusic.h"

#include "..\nnnUtilLib\scriptSoundControl.h"
#include "..\nnnUtilLib\scriptVoiceControl.h"

#include "..\nnnUtilLib\fukaPrint.h"
#include "..\nnnUtilLib\fpsPrint.h"

#include "..\nnnUtilLib\musicControl.h"

#include "..\nnnUtilLib\sceneVoice.h"

#include "..\nnnUtilLib\commonGameVersion.h"

#include "..\nnnUtilLib\myTextInputBox.h"

#include "..\nnnUtilLib\nnnlog.h"

#include "..\nnnUtilLib\autoSelectControl.h"


#include "commonMode.h"
#include "commonSystemSoundName.h"
#include "commonSystemParamName.h"

#include "..\nnnUtilLib\waveData.h"

#include "..\nnnUtilLib\autoSaveDataList.h"

#include "..\nnnUtilLib\autoSaveSubData.h"
#include "..\nnnUtilLib\faceControl.h"



#if !defined _TINYAN3DLIB_
#include "..\nyanDirectXLib\mydirectDraw.h"
#else
#include "..\nyanDirectXLib\mydirectDraw.h"
#include "..\..\systemNNN3D\nyanDirectX3DLib\mydirect3D.h"
#include "..\..\systemNNN3D\nyanDirectX3DLib\myTexture.h"
#include "..\..\systemNNN3D\nyanDirectX3DLib\textureCacheControl.h"
#endif

#include "..\nyanDirectXLib\mmx.h"


#include "..\nyanEffectLib\effectStruct.h"
#include "..\nyanLib\include\effect.h"


//#include "..\nyanEffectLib\effectStruct.h"

#include "..\nyanEffectLib\allEffect.h"
#include "..\nnnUtilLib\wheelMouse.h"




#include "..\nnnUtilLib\scriptDefine.h"
#include "..\nnnUtilLib\commonGameVersion.h"

#include "..\nyanDirectXLib\mydirectsound.h"



#include "..\nnnUtilLib\waveData.h"
//#include "..\nnnUtilLib\commonWave.h"

//#include "..\nnnUtilLib\movingLayer.h"

#include "..\nnnUtilLib\varNumber.h"

#include "..\nnnUtilLib\myFont.h"
#include "..\nnnUtilLib\myMessage.h"

#include "..\nnnUtilLib\taihi.h"
#include "..\nnnUtilLib\saijitsuList.h"

#include "commonKeyList.h"

//#include "..\nnnUtilLib\cdControl.h"

//#include "commonMode.h"
//#include "myMouseStatus.h"


#include "..\nnnUtilLib\commonSystemFile.h"
#include "..\nnnUtilLib\\CViewControl.h"


#include "commonGeneral.h"
#include "scriptCallBack.h"

//dummy
//#include "..\nnnUtilLib\myButtonGroup.h"

#include "commonNothing.h"
#include "commonLogo.h"
#include "commonOpening.h"
#include "commonTitle.h"
#include "commonLoadSave.h"
#include "commonLoad.h"
#include "commonSave.h"
#include "commonBackLog.h"
#include "commonListenBGM.h"
#include "commonSelectMessage.h"
#include "commonPrintMessage.h"
#include "commonConfig.h"
#include "commonSystemMenu.h"
//#include "commonOverrap.h"
#include "commonOmake.h"
#include "commonSelectCGChara.h"
#include "commonSelectCG.h"
#include "commonSelectScene.h"
#include "commonSelectSceneChara.h"
#include "commonSelectPlace.h"
#include "commonPrintCG.h"
#include "commonSelectZukan.h"
#include "commonSelectMovieChara.h"
#include "commonSelectMovie.h"
#include "commonPrintMovie.h"
#include "commonNameInput.h"
//#include "commonPrintCalendar.h"
#include "commonSelectHeroin.h"
#include "commonCodecError.h"
//#include "miniGameBase.h"
#include "commonMiniGame.h"

#include "commonPrintResult.h"
#include "commonChartMenu.h"
#include "commonCardSystem.h"


#include "gameCallBack.h"

//#include "commonPrintMessage.h"
//#include "commonSelectMessage.h"
//#include "commonOverrap.h"

#include "..\nnnUtilLib\nameList.h"

#include "..\nnnUtilLib\sceneList.h"
#include "..\nnnUtilLib\sceneDataControl.h"
#include "..\nnnUtilLib\cgDataControl.h"
#include "..\nnnUtilLib\omakeClassSupport.h"

#include "execscript.h"

//#include "midiPlayer.h"


#include "..\nnnUtilLib\gameUtil.h"

#include "..\nnnUtilLib\basicSetup.h"
#include "..\nnnUtilLib\commonMessageWindow.h"
#include "..\nnnUtilLib\systempicture.h"

#include "commonBackLog.h"
#include "..\nnnUtilLib\mixercontrol.h"

#include "..\nnnUtilLib\setupList.h"

//#include "commonFileControl.h"
#include "commonDataFile.h"

#include "commonConfig.h"

#include "..\nnnUtilLib\floatingLayer.h"
#include "..\nnnUtilLib\sceneOptionButton.h"

#include "..\nnnUtilLib\notice.h"
#include "..\nnnUtilLib\commonResultData.h"

#include "..\nnnUtilLib\messageCursor.h"
#include "..\nnnUtilLib\gameMouse.h"


#include "printDebugParam.h"

#include "backExecClass.h"

#include "..\nnnUtilLib\dataFileSetup.h"

#include "mainControl.h"

#include "..\nnnUtilLib\superButtonSetup.h"

#include "..\nnnUtilLib\superButtonPicture.h"

#include "commonSystemModeList.h"
#include "commonUserCommandList.h"


#include "wm_user.h"

#include "..\nnnUtilLib\shakin.h"


char CGameCallBack::m_defaultSaveHeader[] = "SAVEDATA";
char CGameCallBack::m_defaultSpecialNumberForSaveName[] = "残り日数";
char CGameCallBack::m_defaultOoptionOffVarName[] = "オプションオフ";
char CGameCallBack::m_defaultStartMessage[] = "Initializing..";




char CGameCallBack::m_errorName[] = "エラー名";

//この2つはそろえること
//int CGameCallBack::m_userCommandClass[100]=
//{
	//SELECTPLACE_MODE,SELECTHEROIN_MODE,PRINTMOVIE_MODE,PRINTCALENDAR_MODE,MYPRINTRESULT_MODE,SELECTCHART_MODE,NAMEINPUT_MODE,SELECTPLACE2_MODE,SELECTZUKAN_MODE,-1
//};
//char CGameCallBack::m_userCommandName[100][64]=
//{
//	"selectplace","selectheroin","printmovie","printcalendar","printresult","selectchart","nameinput","selectplace2","selectzukan",""
//};


static int debugdebug = 0;
static int debugMusicNumberPrintFlag = 0;

void CGameCallBack::LogMessage(int msg,WPARAM wParam,LPARAM lParam)
{
	if (m_debugOkFlag == FALSE) return;

	char mes[1024];
	if (msg == WM_MOVE)
	{
		wsprintf(mes,"\x00d\x00aMOVE:%d %d",lParam & 0xffff,(lParam  >> 16) & 0xffff);
	}
	else if (msg == WM_SIZE)
	{
		wsprintf(mes,"\x00d\x00aSIZE %d %d",lParam & 0xffff,(lParam  >> 16) & 0xffff);
	}
	else
	{
		wsprintf(mes,"\x00d\x00a");
	}
	int ln = strlen(mes);

	FILE* file = CMyFile::OpenFullPath("wmlog.txt","ab");
	if (file != NULL)
	{
		fwrite(mes,sizeof(char),ln,file);
		fclose(file);
	}

}

void CGameCallBack::LogMessage(LPSTR mes)
{
	if (m_debugOkFlag == FALSE) return;

	int ln = strlen(mes);

	FILE* file = CMyFile::OpenFullPath("wmlog.txt","ab");
	if (file != NULL)
	{
		fwrite("\x00d\x00a",sizeof(char),2,file);
		fwrite(mes,sizeof(char),ln,file);
		fclose(file);
	}

}

CGameCallBack::CGameCallBack(HWND hwnd, HINSTANCE hinstance, CCommonSystemFile* lpSystemFile, int windowSizeX, int windowSizeY, int bpp) : CScriptCallBack()
{
	m_gameCreateFlagGeneral = FALSE;
	m_hWnd = hwnd;
	m_hInstance = hinstance;
	m_windowSizeX = windowSizeX;
	m_windowSizeY = windowSizeY;
	m_bpp = bpp;
	m_systemFile = lpSystemFile;
	m_quitFlag = FALSE;
	m_screenModeChangedFlag = FALSE;

	m_expSystemMenuMode = NULL;
	m_expSystemMenuCommand = NULL;
	m_expSystemMenuShortCut = NULL;
	m_expSystemMenuSound = NULL;

	m_mouseStatus = NULL;
	m_expSystemMenuKosuu = 0;
	m_expSystemMenuStart = 9;

	m_skipMovieFlag = FALSE;

	m_layerOffVar = NULL;

	m_notUseDirectDraw = 0;

	m_renameLayer = 0;

	m_displaySettingChanged = FALSE;


	//旧バージョンとの互換性のため初期値16
	m_layerKosuuMax = 16;
	m_pictureKosuuMax = 16;



	m_specialVoiceName = NULL;


	for (int i=0;i<LAYER_KOSUU_MAX;i++)
	{
		m_varControlLayer[i] = 0;
		m_taihiVarControlLayer[i] = 0;
	}

	m_miniGameCheckKosuu = 0;
	m_miniGameAreaButtonMode = 0;

	CPicture::m_bpp = m_bpp;

	m_cutinFlag = 0;
	m_3dMode = FALSE;
	m_configMask = 0;
	m_miniGameNumber = 0;
	m_onMiniGameArea = FALSE;

	m_autoFunctionKosuu = 0;
	m_adjustFullScreenLost = 1;
	m_adjustFullWait = 0;

	m_gameMouseDontPrintFlag = FALSE;
//	m_movieEnableFlag = FALSE;
	m_movieEnableFlag = TRUE;

	m_modalLevel = 0;
	m_mainControl = NULL;
	m_floatingLayerFlashFlag = 0;
//	m_omakeClassExistFlag = 0;

	m_openingModeFlag = FALSE;
	m_backScriptModeFlag = FALSE;

	m_lastSaveOkMode = PRINTMESSAGE_MODE;

//	m_threadAddr = NULL;

	HDC hdc = GetDC(m_hWnd);
	m_startWidth = GetDeviceCaps(hdc, HORZRES);
	m_startHeight = GetDeviceCaps(hdc, VERTRES); 
	m_startFrequency = GetDeviceCaps(hdc, VREFRESH); 
	ReleaseDC(m_hWnd,hdc);

	m_shakinControl = NULL;

	m_f9KeyExitOffFlag = 0;
	m_escKeyExitOffFlag = 1;

	m_movieCursor = NULL;
	m_launchFlag = FALSE;
	m_debugMessageKosuu = 0;
	m_layerOff = 0;
	m_myDirect3D = NULL;
	m_yoyaku = 0;

	m_directDraw = NULL;
	m_mmx = NULL;
	m_directShow = NULL;
	m_directSound = NULL;

	m_setup = NULL;
	m_setup3 = NULL;

	m_myGraphics = NULL;

	m_superButtonPicture = NULL;
	m_dataFileSetup = NULL;

	m_noVoiceIsDefaultWait = 0;

	m_nextFadeSe = 0;
	m_nextFadeVoice = 0;
}


void CGameCallBack::GeneralCreate(void)
{

	int i;

	for (i=0;i<4;i++)
	{
		m_threadControlHandle[i] = NULL;
#if defined _MT
		m_threadControlHandle[i] = CreateEvent(NULL,TRUE,FALSE,NULL);
#endif
	}

	m_viewControl = m_mainControl->GetViewControl();


	m_setup = new CNameList();
//	m_setup2 = new CNameList();
//	m_setup3 = new CNameList();
	LoadSetupFile("game",256);
//	LoadSetupFile2("dataFile",256);
//	LoadSetupFile("miniGame",512);

//	m_logFileName[0] = '_';
//	m_logFileName[1] = 0;

	int errorLogFlag = 0;
	GetInitGameParam(&errorLogFlag,"errorLogFlag");
	if (errorLogFlag) CNNNLog::StartLog();

	int startupLoadErrorPrintFlag = 0;
	GetInitGameParam(&startupLoadErrorPrintFlag,"startupLoadErrorPrintFlag");
	if (startupLoadErrorPrintFlag)
	{
		CPicture::m_errorPrintFlag = TRUE;
	}

	GetInitGameParam(&m_layerKosuuMax,"layerExpand");
	m_pictureKosuuMax = m_layerKosuuMax;//同じである必要がある

	CEffect::m_layerKosuuMaxSetup = m_layerKosuuMax;
	CEffect::m_pictureKosuuMaxSetup = m_pictureKosuuMax;

	int animeEffectEnable = 0;
	if (GetInitGameParam(&animeEffectEnable,"animeEffectEnable"))
	{
		CEffectAnimation::SetAnimeEffectEnable(animeEffectEnable);
	}
	int animeBufferMax = 60;
	if (GetInitGameParam(&animeBufferMax,"animeBufferMax"))
	{
		CEffectAnimation::SetAnimeBufferMax(animeBufferMax);
	}
	int animeBufferDepth = 32;
	if (GetInitGameParam(&animeBufferDepth,"animeBufferDepth"))
	{
		CEffectAnimation::SetBufferDepth(animeBufferDepth);
	}


	for (i=0;i<m_pictureKosuuMax;i++)
	{
		SetDontLoadDWQ(i,0);
	}

	GetInitGameParam(&debugMusicNumberPrintFlag,"debugMusicNumberPrintFlag");

	int dontCreateGUID = 0;
	GetInitGameParam(&dontCreateGUID,"dontCreateGUID");
	if (dontCreateGUID == 0)
	{
		m_systemFile->CreateGUID();
	}

//	m_activeErrorFlag = FALSE;

//	CPicture::InitStaticData();

	int dwqPackLevel = 0;
	GetInitGameParam(&dwqPackLevel,"dwqPackLevel");
	CPicture::SetDataPackLevel(dwqPackLevel);


	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);


//	m_realWindowSizeX = m_viewControl->GetRealWindowSizeX();
//	m_realWindowSizeY = m_viewControl->GetRealWindowSizeY();
//	m_viewOffsetX = m_viewControl->GetViewOffsetX();
//	m_viewOffsetY = m_viewControl->GetViewOffsetY();




	int notUseDirectDraw = m_systemFile->m_systemdata.notUseDirectDraw;
	if (notUseDirectDraw == 0)
	{
		GetInitGameParam(&notUseDirectDraw,"notUseDirectDraw");
	}
	CMyDirectDraw::m_notUseDirectDraw = notUseDirectDraw;
	m_notUseDirectDraw = notUseDirectDraw;


//OutputDebugString("\nGeneralCreate -1");
#if defined _TINYAN3DLIB_
	if (m_systemFile->m_systemdata.fullScreenFlag)
	{
		SetFocus(m_hWnd);
//		m_myDirect3D = new CMyDirect3D(m_hWnd,TRUE);
		m_myDirect3D = new CMyDirect3D(m_hWnd,FALSE);
	}
	else
	{
		m_myDirect3D = new CMyDirect3D(m_hWnd);
	}
	m_textureCacheControl = new CTextureCacheControl();

#endif

	int jpegMMX = 1;
	GetInitGameParam(&jpegMMX,"jpegMMX");
	if (jpegMMX == 0)
	{
		CJpegDecoder::SetCalcuFloat();
	}
//	int realWindowSizeX = 1024;
//	int realWindowSizeY = 768;

	m_myGraphics = new CMyGraphics(m_windowSizeX,m_windowSizeY,notUseDirectDraw);


//	CMyGraphics::SetScreenBufferSize(m_windowSizeX,m_windowSizeY);
//	CPicture::SetBpp(bpp);
//	CPicture::m_screenSizeX = m_windowSizeX;
//	CPicture::m_screenSizeY = m_windowSizeY;

//	m_screenBuffer = new int[640*480+640*2];
//	CMyGraphics::InitStaticData();

#if !defined _TINYAN3DLIB_
	CAllGraphics::FillScreen();
#endif


	m_autoSelectControl = NULL;
	m_autoDebugMode = 0;
	GetInitGameParam(&m_autoDebugMode,"autoDebugMode");
	if (m_autoDebugMode)
	{
		m_autoSelectControl = new CAutoSelectControl();
	}
	m_autoDebugWait = 50;
	GetInitGameParam(&m_autoDebugWait,"autoDebugWait");


//	CPicture::FillScreen();

	m_layerOffVar = new int[1000];
	for (int i=0;i<1000;i++)
	{
		m_layerOffVar[i] = -1;
	}

	int vistaCheck = 1;
	GetInitGameParam(&vistaCheck,"vistaCheck");
	if (vistaCheck)
	{
		OSVERSIONINFO osVersion;
		osVersion.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&osVersion);
		if (osVersion.dwPlatformId == VER_PLATFORM_WIN32_NT)
		{
			if (osVersion.dwMajorVersion == 6)
			{
				CAreaControl::SetVista();
			}
		}
	}
	//全バージョンallprintMode
	CAreaControl::SetVista();


	int notSrcCopyFlagEnable = 0;
	GetInitGameParam(&notSrcCopyFlagEnable,"notSrcCopyFlagEnable");
	if (notSrcCopyFlagEnable) CSuperButtonSetup::SetNotCopyFlagEnable();


	m_superButtonPicture = new CSuperButtonPicture();

	m_systemModeList = new CCommonSystemModeList();
	m_commonUserCommandList = new CCommonUserCommandList();


	m_dataFileSetup = NULL;

	int datafileSetupDontCreateFlag = 0;
	int saveDisable = 0;
	GetInitGameParam(&saveDisable,"saveClassDisable");
	int loadDisable = 0;
	GetInitGameParam(&loadDisable,"loadClassDisable");
	if (saveDisable && loadDisable)
	{
		datafileSetupDontCreateFlag = 1;
	}
	GetInitGameParam(&datafileSetupDontCreateFlag,"dataFileDontCreate");

	if (datafileSetupDontCreateFlag == 0)
	{
		m_dataFileSetup = new CDataFileSetup();
	}

//MessageBox(NULL,"gamecallback:const-0-1-0.5","game",MB_OK);
//CAllGeo::BoxFill(10,10,300,300,55,66,77);

	GetInitGameString(&m_companyName,"companyName");
	GetInitGameString(&m_productName,"gameName");

	//特殊文字をスペースに変更


	m_facePrintFlag = 0;
	GetInitGameParam(&m_facePrintFlag,"facePrintMode");


	m_autoSaveDataList = new CAutoSaveDataList();


	m_autoExtDataLoadKosuu = 0;
	m_autoExtDataLoadMode = new int[256];
	m_autoExtSubDataLoadKosuu = 0;
	m_autoExtDataLoadSub = new int[256];
	m_autoSaveSubDataClass = new CAutoSaveSubData*[256];




	for (int i=0;i<256;i++)
	{
		m_autoExtDataLoadMode[i] = 0;
	}

	for (int i=0;i<256;i++)
	{
		m_autoExtDataLoadSub[i] = 0;
		m_autoSaveSubDataClass[i] = NULL;
	}

	for (int i=0;i<256;i++)
	{
		int md = 0;
		char name[256];
		wsprintf(name,"autoExtDataMode%d",i+1);

		LPSTR modeName = NULL;

		if (GetInitGameString(&modeName,name))
//		if (GetInitGameParam(&md,name))
		{
			int md = m_systemModeList->GetModeNumberByName(modeName);
			if (md > 0)
			{
				m_autoExtDataLoadMode[i] = md;
				m_autoExtDataLoadKosuu++;
			}
		}
		else
		{
			break;
		}
	}



	for (int i=0;i<256;i++)
	{
		int sb = 0;
		char name[256];
		wsprintf(name,"autoExtDataSub%d",i+1);

		LPSTR subName = NULL;

		if (GetInitGameString(&subName,name))
		{
//			int s = m_systemModeList->GetModeNumberByName(modeName);
			int s = m_autoSaveDataList->SearchName(subName);

			if (s > 0)
			{
				m_autoExtDataLoadSub[i] = s;
				m_autoExtSubDataLoadKosuu++;
			}
		}
		else
		{
			break;
		}
	}

	//complete auto
	if (m_facePrintFlag)
	{
		int s = m_autoSaveDataList->SearchName("face");

		if (s > 0)
		{
			m_autoExtDataLoadSub[m_autoExtSubDataLoadKosuu] = s;
			m_autoExtSubDataLoadKosuu++;
		}
	}

	m_clearAutoAfterLoad = 0;
	GetInitGameParam(&m_clearAutoAfterLoad,"clearAutoAfterLoad");


	//当面どちらも有効
	m_saveHeaderName = m_defaultSaveHeader;
	GetInitGameString(&m_saveHeaderName,"saveHeaderName");
//	m_dataFileSetup->GetInitGameString(&m_saveHeaderName,"saveHeaderName");

	m_extSaveDataKosuu = 0;
	GetInitGameParam(&m_extSaveDataKosuu,"extSaveDataNumber");



	m_koukaonOnseiDontStopFlag = 0;
	GetInitGameParam(&m_koukaonOnseiDontStopFlag,"seVoiceDontStopFlag");

	m_skipToScriptVoiceStopFlag = 0;
	GetInitGameParam(&m_skipToScriptVoiceStopFlag,"skipToScriptVoiceStopFlag");


//	m_dataFileSetup->GetInitGameParam(&m_extSaveDataKosuu,"extSaveDataNumber");
	m_extSaveDataSizeTable = NULL;
	if ((m_extSaveDataKosuu+m_autoExtDataLoadKosuu+m_autoExtSubDataLoadKosuu) > 0)
	{
		m_extSaveDataSizeTable = new int[m_extSaveDataKosuu+m_autoExtDataLoadKosuu+m_autoExtSubDataLoadKosuu];
		for (int i=0;i<m_autoExtDataLoadKosuu;i++)
		{
			m_extSaveDataSizeTable[i] = 0;//dummy auto size=0
		}

		for (int i=0;i<m_autoExtSubDataLoadKosuu;i++)
		{
			m_extSaveDataSizeTable[m_autoExtDataLoadKosuu+i] = 0;
		}

		for (int i=0;i<m_extSaveDataKosuu;i++)
		{
			char name[256];
			wsprintf(name,"extSaveDataSize%d",i+1);
			m_extSaveDataSizeTable[i+m_autoExtDataLoadKosuu+m_autoExtSubDataLoadKosuu] = 0;
			GetInitGameParam(&m_extSaveDataSizeTable[i+m_autoExtDataLoadKosuu+m_autoExtSubDataLoadKosuu],name);
//			m_dataFileSetup->GetInitGameParam(&m_extSaveDataSizeTable[i],name);
		}
	}

	m_varControlLoadDWQErrorPrint = 0;
	GetInitGameParam(&m_varControlLoadDWQErrorPrint,"varControlLoadDWQErrorPrint");


	m_shiftSkipMessageOnly = 0;
	GetInitGameParam(&m_shiftSkipMessageOnly,"shiftSkipMessageOnly");

	m_autoMessageCheckKillShift = 0;
	m_cannotSkipCheckKillShift = 0;
	GetInitGameParam(&m_autoMessageCheckKillShift,"autoMessageCheckKillShift");
	GetInitGameParam(&m_cannotSkipCheckKillShift,"cannotSkipCheckKillShift");


	m_quickSaveEnable = 0;
	GetInitGameParam(&m_quickSaveEnable,"quickSaveEnable");
	m_quickLoadEnable = m_quickSaveEnable;
	GetInitGameParam(&m_quickLoadEnable,"quickLoadEnable");
	m_quickSavePrint = m_quickSaveEnable;
	GetInitGameParam(&m_quickSavePrint,"quickSavePrint");
	m_quickLoadPrint = m_quickLoadEnable;
	GetInitGameParam(&m_quickLoadPrint,"quickLoadPrint");

	m_quickLoadDelay = 0;
	GetInitGameParam(&m_quickLoadDelay,"quickLoadDelay");
	m_quickLoadYoyaku = 0;

	m_quickLoadGetScreen = 0;//つかわない。すでに1と同等の処理がはいっていた
	GetInitGameParam(&m_quickLoadGetScreen,"quickLoadGetScreen");


	m_quickSaveKey = 0;
	m_quickLoadKey = 0;
	m_quickSaveCommentFlag = 0;

	if (m_quickSaveEnable)
	{
		LPSTR keyName = NULL;
		if (GetInitGameString(&keyName,"quickSaveKey"))
		{
			int accelKey = atoi(keyName);
			if (accelKey == 0)
			{
				if ((*keyName) != '0')
				{
					accelKey = (int)(*keyName);
					accelKey &= 0xff;
				}
			}

			m_quickSaveKey = accelKey;
		}

		GetInitGameParam(&m_quickSaveCommentFlag,"quickSaveCommentFlag");
	}

	if (m_quickLoadEnable)
	{
		LPSTR keyName = NULL;
		if (GetInitGameString(&keyName,"quickLoadKey"))
		{
			int accelKey = atoi(keyName);
			if (accelKey == 0)
			{
				if ((*keyName) != '0')
				{
					accelKey = (int)(*keyName);
					accelKey &= 0xff;
				}
			}

			m_quickLoadKey = accelKey;
		}
	}


	m_quickSaveSound = -1;
	GetInitGameParam(&m_quickSaveSound,"quickSaveSound");
	m_quickLoadSound = m_quickSaveSound;
	GetInitGameParam(&m_quickLoadSound,"quickLoadSound");
	m_quickLoadErrorSound = m_quickLoadSound;
	GetInitGameParam(&m_quickLoadErrorSound,"quickLoadErrorSound");
	
	//total volume?

	m_totalVolumeUseFlag = 0;
	GetInitGameParam(&m_totalVolumeUseFlag,"totalVolumeUseFlag");


	//reset mute?


	m_useCutinFlag = 0;
	GetInitGameParam(&m_useCutinFlag,"useCutinFlag");


	m_directXInitVolumeFlag = 0;
	GetInitGameParam(&m_directXInitVolumeFlag,"directXVolumeFlag");

	m_directXInitVolume = 60;
	GetInitGameParam(&m_directXInitVolume,"directXVolume");

	m_frameTime = 50;
	GetInitGameParam(&m_frameTime,"frameTime");
	m_defaultFrameTime = m_frameTime;



	m_scriptRunMode = 0;

//	m_enableMidiButtonFlag = 1;
//	m_enableCDButtonFlag = 1;

	m_saveCommentKosuuMax = 4;
	m_saveCommentLength = 256;
	m_saveComment = new char*[m_saveCommentKosuuMax];
	for (i=0;i<m_saveCommentKosuuMax;i++)
	{
		m_saveComment[i] = new char[m_saveCommentLength];
		m_saveComment[i][0] = 0;
	}





//	GetInitGameParam(&m_enableMidiButtonFlag,"configMidiButtonFlag");
//	GetInitGameParam(&m_enableCDButtonFlag,"configCDDAButtonFlag");


	m_printStartMessageFlag = 1;
	GetInitGameParam(&m_printStartMessageFlag,"startMessageFlag");
	if (m_printStartMessageFlag)
	{
		m_startMessage = m_defaultStartMessage;
		GetInitGameString(&m_startMessage,"startMessage");
	}

	m_loadVoiceErrorPrintFlag = 0;
	GetInitGameParam(&m_loadVoiceErrorPrintFlag,"loadVoiceErrorPrintFlag");
	m_loadSeErrorPrintFlag = 0;
	GetInitGameParam(&m_loadSeErrorPrintFlag,"loadSeErrorPrintFlag");


	m_backScriptSetCGOkFlag = 0;
	GetInitGameParam(&m_backScriptSetCGOkFlag,"backScriptSetCGOkFlag");

	m_modalCannotCloseFlag = 1;
	GetInitGameParam(&m_modalCannotCloseFlag,"modalCannotCloseFlag");


	m_useHsavemask = 0;
	m_hSaveList = NULL;
	m_hSaveMaskPic = NULL;
	GetInitGameParam(&m_useHsavemask,"useHsaveMask");
	if (m_useHsavemask)
	{
		m_hSaveList = new CNameList();
		m_hSaveMaskPic = new CPicture();
		m_hSaveList->LoadFile("nya\\savemasklist.xtx");
	}


	m_miniCGReduce = 6;
	m_miniCGSizeX = 132;
	m_miniCGSizeY = 100;
	GetInitGameParam(&m_miniCGReduce,"miniCGReduce");
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();
	if (m_miniCGReduce > 0)
	{
		m_miniCGSizeX = screenSizeX / m_miniCGReduce;
		m_miniCGSizeX &= (~3);
		m_miniCGSizeY = screenSizeY / m_miniCGReduce;

		if (m_miniCGReduce == 6)
		{
			if ((screenSizeX == 800) && (screenSizeY == 600))
			{
				m_miniCGSizeX = 132;
			}
		}
	}

	GetInitGameParam(&m_miniCGSizeX,"miniCGSizeX");
	GetInitGameParam(&m_miniCGSizeY,"miniCGSizeY");
	
	m_cgDataControl = new CCGDataControl(m_systemFile);

//	m_cgCharaKosuu = 0;
//	m_cgKosuu = NULL;
//	m_cgList = NULL;
//	m_cgListControl = NULL;

//	int cgCharaKosuu = CCommonSystemFile::GetCGCharaNinzu();
//	GetInitGameParam(&cgCharaKosuu,"cgCharaNumber");
//	if (cgCharaKosuu > 0) CreateCGList(cgCharaKosuu);



	GetInitGameParam(&m_f9KeyExitOffFlag,"f9KeyExitOffFlag");
	GetInitGameParam(&m_escKeyExitOffFlag,"escKeyExitOffFlag");

	m_f4Ok = 1;
	m_f5Ok = 1;
	GetInitGameParam(&m_f4Ok,"F4OK");
	GetInitGameParam(&m_f5Ok,"F5Ok");

	m_optionStartMouseButton = 2;
	GetInitGameParam(&m_optionStartMouseButton,"optionStartMouseButton");


	m_movieVolumeNotUse = 0;
	GetInitGameParam(&m_movieVolumeNotUse,"movieVolumeNotUse");

	m_soundVoiceVolumeNotUse = 1;
	GetInitGameParam(&m_soundVoiceVolumeNotUse,"soundVoiceVolumeNotUse");

	m_noWaitVSync = 0;
	GetInitGameParam(&m_noWaitVSync,"noWaitVSync");


	GetInitGameParam(&m_adjustFullScreenLost,"adjustFullScreenLost");
//OutputDebugString("\nGeneralCreate -2");



	m_backLogDisableCount = 0;
	m_backLogDisableTime = 100;
//	m_backLogDisableTime = 1000;
	m_backLogDisableCheckTime = 3;
	m_backLogDisableCheckFlag = 1;
	GetInitGameParam(&m_backLogDisableTime,"backLogDisableTime");
	GetInitGameParam(&m_backLogDisableCheckTime,"backLogDisableCheckTime");
	GetInitGameParam(&m_backLogDisableCheckFlag,"backLogDisableCheckFlag");
	m_backLogDisableOldTime = 0;



	m_charaVoiceVolumeDelta = 2;
	GetInitGameParam(&m_charaVoiceVolumeDelta,"charaVoiceVolumeDelta");

	m_maxSkipFrame = 2;
	GetInitGameParam(&m_maxSkipFrame,"maxSkipFrame");
	if (m_maxSkipFrame < 1) m_maxSkipFrame = 1;

	m_skipAdjustFrame = 10;
	GetInitGameParam(&m_skipAdjustFrame,"skipAdjustFrame");

	m_mustSetVoiceFlag = 1;
	m_mustSetMusicFlag = 1;
	m_mustSetCGFlag = 1;
	m_mustSetFilmFlag = 1;//dummy

	m_mustMessageReadSkip = 1;

	GetInitGameParam(&m_mustSetVoiceFlag,"mustSetVoiceFlag");
	GetInitGameParam(&m_mustSetMusicFlag,"mustSetMusicFlag");
	GetInitGameParam(&m_mustSetCGFlag,"mustSetCGFlag");
	GetInitGameParam(&m_mustSetFilmFlag,"mustSetFilmFlag");

	GetInitGameParam(&m_mustMessageReadSkip,"mustSetMessageFlag");

	for (i=0;i<100;i++)
	{
		m_createModeDisableFlag[i] = FALSE;
	}


	int commonUserCommandKosuu = m_commonUserCommandList->GetKosuu();

	for (i=0;i<commonUserCommandKosuu ;i++)
	{
		int userClass = m_commonUserCommandList->GetModeNumber(i);
		LPSTR userCommandName = m_commonUserCommandList->GetModeName(i);
		m_createModeDisableFlag[userClass] = TRUE;

		int flg = 0;
		char name[256];
		wsprintf(name,"%sIsDefault",userCommandName);
		GetInitGameParam(&flg,name);
		if (flg)
		{
			m_createModeDisableFlag[userClass] = FALSE;
		}
	}


	m_lastLoadLayer = 0;
	m_offLayerDontSetCG = 0;
	GetInitGameParam(&m_offLayerDontSetCG,"offLayerDontSetCG");


	m_enableButtonVoiceCharaVolume = 0;
	GetInitGameParam(&m_enableButtonVoiceCharaVolume,"enableButtonVoiceCharaVolume");


	CheckCreateBadFlag();
//	CheckDefaultUserCommandFlag();

	if (m_createModeDisableFlag[MINIGAME_MODE] == FALSE)
	{
		m_setup3 = new CNameList();
		LoadSetupFile3("miniGame",512);

		GetInitGameParam3(&m_miniGameAreaButtonMode,"areaButtonMode");
		GetInitGameParam3(&m_miniGameCheckKosuu,"miniGameCheckNumber");
	}

	int omakeClassExistFlag = 0;
	GetInitGameParam(&omakeClassExistFlag,"useExtClass");
//	GetInitGameParam(&m_omakeClassExistFlag,"useExtClass");


	for (i=0;i<MODE_MAX;i++) m_general[i] = NULL;
	m_backLogOkTable = new int[256];
	for (int i=0;i<256;i++) m_backLogOkTable[i] = 0;

	m_defaultUserCommandKosuu = 0;



	m_omakeClassSupport = new COmakeClassSupport(omakeClassExistFlag);
//	AllClearOmakeClass();

	m_superDownButtonSetup = NULL;
	m_superUpButtonSetup = NULL;


	SetupAndCreateCommonBackButton();






//	m_backSizeX = 55;
//	m_backSizeY = 38;
//	GetInitGameParam(&m_backSizeX,"backSizeX");
//	GetInitGameParam(&m_backSizeY,"backSizeY");
//	m_filenameBackButton = m_defaultBackButtonFileName;
//	GetInitGameString(&m_filenameBackButton,"fileNameBackButton");




//AddErrorLog("1");



	m_lastFilmName[0] = 0;
	m_lastStoryName[0] = 0;

	m_musicNumber = -1;
	m_lastMusicNumber = -1;



	m_debugOkFlag = FALSE;
	m_memPrintFlag = FALSE;

	m_motionGetFlag = FALSE;
	m_motionGetCount = 0;

	m_bossMode = FALSE;

	m_fuqueAllEffectYoyaku = FALSE;

	m_disableLoadSaveShortCutKeyFlag = FALSE;
	if (CCommonGameVersion::CheckNetVersion()) m_disableLoadSaveShortCutKeyFlag = TRUE;
	if (CCommonGameVersion::CheckTaikenVersion()) m_disableLoadSaveShortCutKeyFlag = TRUE;

	m_totalTime = 0;
//	m_extDataBlockKosuu = 0;



	m_codecError = -1;

	m_codecErrorRunMode = 0;
//	GetInitGameParam(&m_codecErrorRunMode,"codecErrorRunMode");






//@@@	m_updown = NULL;
	m_wheelMoveFlag = TRUE;


	m_demoFlag = FALSE;

	m_gameMode[0] = NOTHING_MODE;
//	m_nextMode = m_gameMode;




	int highVersion = 0;
	int middleVersion = 0;
	int lowVersion = 0;
	GetInitGameParam(&highVersion,"highVersion");
	GetInitGameParam(&middleVersion,"middleVersion");
	GetInitGameParam(&lowVersion,"lowVersion");
	SetGameVersion(highVersion,middleVersion,lowVersion);


	m_messageVoiceLength = 7000;	//dummy用心

	m_nextShakinFumitaoshi = 0;

	m_debugVarKosuuMax = 1000;

	m_voiceSpeakFlag = FALSE;
	m_voiceSpeakCount = 0;

	m_wheelMove = 0;

	m_fpsPrintFlag = FALSE;

	m_skipNextCommandFlag = FALSE;
	m_skipEffectCommandFlag = FALSE;
	m_skipToFilmEndFlag = FALSE;


	m_demoFlagVar = -1;


	m_lastSelectHeroinNumber = 0;


	m_lastSoundVoiceVolume = -1;
	m_wheelWaitCount = 0;


	m_cursorFlag = FALSE;
//	m_calendarFlag = FALSE;
	m_optionFlag = FALSE;
	m_sceneButtonFlag = FALSE;

	m_nokori = 30;

	m_sceneMode = FALSE;

	m_pastTime = 0;
	m_pastTime2 = 0;

	m_shakin = 0;
	m_shakin1 = 0;
	m_shakin2 = 0;
	m_shakin3 = 0;

	m_totalCount = 0;
	m_skipCount = 0;


	m_debugVarFlag = FALSE;



//	m_bgmNumber = -1;
//	m_bgmKaisuu = 0;

	m_lastSoundVoiceVolume = 101;


	for (i=0;i<1000;i++)
	{
		m_var[i] = 0;
	}

	for (i=0;i<100;i++)
	{
		m_var[200+i] = m_systemFile->m_systemVar.var[i];
	}


	m_windowX = 32;
	m_windowY = 32;

	m_windowX = m_systemFile->m_systemdata.windowX;
	m_windowY = m_systemFile->m_systemdata.windowY;

	int windowAdjustFlag = 1;
	GetInitGameParam(&windowAdjustFlag,"windowAdjustFlag");
	if (windowAdjustFlag)
	{
		int	desktopWindowSizeX = GetSystemMetrics(SM_CXVIRTUALSCREEN);
		int desktopWindowSizeY = GetSystemMetrics(SM_CYVIRTUALSCREEN);
		int desktopWindowStartX = GetSystemMetrics(SM_XVIRTUALSCREEN);
		int desktopWindowStartY = GetSystemMetrics(SM_YVIRTUALSCREEN);
		int desktopWindowEndX = desktopWindowStartX + desktopWindowSizeX;
		int desktopWindowEndY = desktopWindowStartY + desktopWindowSizeY;

		int fixedFrameX = GetSystemMetrics(SM_CXFIXEDFRAME);
		int fixedFrameY = GetSystemMetrics(SM_CYFIXEDFRAME);
		int captionSizeY = GetSystemMetrics(SM_CYCAPTION);

		int checkStartX = m_windowX;// - fixedFrameX;
		int checkStartY = m_windowY;// - fixedFrameY - captionSizeY;

		if ((checkStartX + m_windowSizeX + fixedFrameX*2) >= desktopWindowEndX)
		{
			checkStartX = desktopWindowEndX - (m_windowSizeX + fixedFrameX*2);
		}
		if (checkStartX < desktopWindowStartX)
		{
			checkStartX = desktopWindowStartX;
		}
		m_windowX = checkStartX;
		m_systemFile->m_systemdata.windowX = m_windowX;



		if ((checkStartY + m_windowSizeY + fixedFrameX*2 + captionSizeY) >= desktopWindowEndY)
		{
			checkStartY = desktopWindowEndY - (m_windowSizeY + fixedFrameY*2 + captionSizeY);
		}
		if (checkStartY < desktopWindowStartY)
		{
			checkStartY = desktopWindowStartY;
		}
		m_windowY = checkStartY;
		m_systemFile->m_systemdata.windowY = m_windowY;
	}



//OutputDebugString("\nGeneralCreate -3");


//	if (m_systemFile->m_systemdata.fullScreenFlag)
	if (0)
	{
		DEVMODE devMode;

		ZeroMemory(&devMode,sizeof(devMode));
		devMode.dmSize = sizeof(devMode);

		devMode.dmPelsWidth = m_windowSizeX;
		devMode.dmPelsHeight = m_windowSizeY;
		devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT; 

		int hr = ChangeDisplaySettings(&devMode, CDS_FULLSCREEN); 
/*
		if (hr != DISP_CHANGE_SUCCESSFUL)
		{
			if (hr == DISP_CHANGE_RESTART) MessageBox(NULL,"DISP_CHANGE_RESTART","er",MB_OK);
			if (hr == DISP_CHANGE_BADFLAGS) MessageBox(NULL,"DISP_CHANGE_BADFLAGS","er",MB_OK);
			if (hr == DISP_CHANGE_BADPARAM) MessageBox(NULL,"DISP_CHANGE_BADPARAM","er",MB_OK);
			if (hr == DISP_CHANGE_FAILED) MessageBox(NULL,"DISP_CHANGE_FAILED","er",MB_OK);
			if (hr == DISP_CHANGE_BADMODE) MessageBox(NULL,"DISP_CHANGE_BADMODE","er",MB_OK);
			if (hr == DISP_CHANGE_NOTUPDATED) MessageBox(NULL,"DISP_CHANGE_NOTUPDATED","er",MB_OK);
		}
*/


		SetWindowLong(m_hWnd,GWL_STYLE,WS_POPUP | WS_VISIBLE);
//		SetWindowLong(m_hWnd,GWL_EXSTYLE,GetWindowLong(m_hWnd,GWL_EXSTYLE) | WS_EX_TOPMOST);

//	MoveWindow(m_hWnd,0,0, m_windowSizeX,m_windowSizeY,TRUE);
//	Sleep(100);

//		TaihiWindow();
		MoveWindow(m_hWnd,0,0, m_windowSizeX,m_windowSizeY,TRUE);
//		FuqueWindow();

//	MoveWindow(m_hWnd,0,0, m_windowSizeX,m_windowSizeY,TRUE);
	}

















//OutputDebugString("\nGeneralCreate -3-B");

int realWindowSizeX = m_viewControl->GetRealWindowSizeX();
int realWindowSizeY = m_viewControl->GetRealWindowSizeY();

#if defined _TINYAN3DLIB_
//	if (0)
	if (m_systemFile->m_systemdata.fullScreenFlag)
	{
		CTextureCacheControl::ReleaseAllTexture();
		((CMyDirect3D*)m_myDirect3D)->ReleaseAllResource();
//		((CMyDirect3D*)m_myDirect3D)->ChangeWindowMode(TRUE);



		DEVMODE devMode0;
		ZeroMemory(&devMode0,sizeof(devMode0));
		devMode0.dmSize = sizeof(devMode0);
	//	devMode.dmPelsWidth = m_windowSizeX;
	//	devMode.dmPelsHeight = m_windowSizeY;
		devMode0.dmFields = DM_BITSPERPEL;
		EnumDisplaySettings(NULL,ENUM_CURRENT_SETTINGS,&devMode0);


		DEVMODE devMode;
		ZeroMemory(&devMode,sizeof(devMode));
		devMode.dmSize = sizeof(devMode);
		devMode.dmPelsWidth = m_windowSizeX;
		devMode.dmPelsHeight = m_windowSizeY;
		devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT; 
		int hr = ChangeDisplaySettings(&devMode, CDS_FULLSCREEN); 
		Sleep(100);

		if (hr != DISP_CHANGE_SUCCESSFUL)
		{
			char mes[1024];
			int nn = 0;
			if (hr == DISP_CHANGE_SUCCESSFUL) nn = 1;
			if (hr == DISP_CHANGE_RESTART) nn = 2;
			if (hr == DISP_CHANGE_BADFLAGS) nn = 3;
			if (hr == DISP_CHANGE_BADPARAM) nn = 4;
			if (hr == DISP_CHANGE_FAILED) nn = 5;
			if (hr == DISP_CHANGE_BADMODE) nn = 6;
			if (hr == DISP_CHANGE_NOTUPDATED) nn = 7;
			wsprintf(mes,"%d:%d",hr,nn);
	//		MessageBox(NULL,mes,"fullerrorret",MB_OK);

			int devNum = 0;
			DEVMODE devMode2;
			ZeroMemory(&devMode2,sizeof(devMode2));
			devMode2.dmSize = sizeof(devMode2);
	//		devMode2.dmPelsWidth = m_windowSizeX;
	//		devMode2.dmPelsHeight = m_windowSizeY;
			devMode2.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_BITSPERPEL;  
			BOOL cannot = TRUE;



			while (EnumDisplaySettings(NULL,devNum,&devMode2))
			{
				if ((devMode2.dmPelsWidth == m_windowSizeX) && (devMode2.dmPelsHeight == m_windowSizeY))
				{
					if (devMode2.dmDisplayFrequency > 0)
					{
						if (devMode2.dmBitsPerPel == devMode0.dmBitsPerPel)
						{
							devMode2.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_BITSPERPEL;  
							int hr2 = ChangeDisplaySettings(&devMode2, CDS_FULLSCREEN); 
							Sleep(10);

							int nn2 = 0;
							if (hr2 == DISP_CHANGE_SUCCESSFUL) nn2 = 1;
							if (hr2 == DISP_CHANGE_RESTART) nn2 = 2;
							if (hr2 == DISP_CHANGE_BADFLAGS) nn2 = 3;
							if (hr2 == DISP_CHANGE_BADPARAM) nn2 = 4;
							if (hr2 == DISP_CHANGE_FAILED) nn2 = 5;
							if (hr2 == DISP_CHANGE_BADMODE) nn2 = 6;
							if (hr2 == DISP_CHANGE_NOTUPDATED) nn2 = 7;
							wsprintf(mes,"%d:%d f=%d",hr,nn,devMode2.dmDisplayFrequency);
						//	MessageBox(NULL,mes,"fullerrorret",MB_OK);

							if (hr2 == DISP_CHANGE_SUCCESSFUL)
							{
								Sleep(100);
								cannot = FALSE;
								break;
							}
						}
					}
				}

				devNum++;
			}

			if (cannot)
			{
				MessageBox(m_hWnd,"フルスクリーン処理に失敗しました","Error",MB_ICONEXCLAMATION | MB_OK);
			}
		}

		SetForegroundWindow(m_hWnd);
		SetFocus(m_hWnd);

		((CMyDirect3D*)m_myDirect3D)->ChangeWindowMode(TRUE);

		m_directDraw = new CMyDirectDraw(m_hWnd,m_hInstance,m_windowSizeX,m_windowSizeY,m_bpp,m_systemFile->m_systemdata.fullScreenFlag*0);



		((CMyDirect3D*)m_myDirect3D)->CreateAllResource();
		m_myGraphics->ReCreateAllShader();
	//	m_effect->ReCreateAllShader();

	}
	else
	{
		m_directDraw = new CMyDirectDraw(m_hWnd,m_hInstance,m_windowSizeX,m_windowSizeY,m_bpp,m_systemFile->m_systemdata.fullScreenFlag*0);
	}

#else

//AddErrorLog("createDirectDraw");

m_directDraw = new CMyDirectDraw(m_hWnd,m_hInstance,realWindowSizeX,realWindowSizeY,m_bpp,m_systemFile->m_systemdata.fullScreenFlag*0);

#endif


//	m_directDraw = new CMyDirectDraw(m_hWnd,m_hInstance,m_windowSizeX,m_windowSizeY,m_bpp,m_systemFile->m_systemdata.fullScreenFlag*0);

	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);

	m_startupWindowMode = m_systemFile->m_systemdata.fullScreenFlag;
//OutputDebugString("\nGeneralCreate -3-C");

	if (m_systemFile->m_systemdata.fullScreenFlag)
//	if (0)
	{
		CAreaControl::SetNextAllPrint();

#if !defined _TINYAN3DLIB_
		CAreaControl::ToFullScreen();
#endif

		if (m_directDraw != NULL)
		{
			m_directDraw->SetGDIFullScreen();
		}
	}
//OutputDebugString("\nGeneralCreate -3-D");

	//ImmAssociateContext(m_hWnd,NULL);
//	WINNLSEnableIME(m_hWnd,FALSE);


	///@@@@@@@@@@@@@@@@m_gameUtil = new CGameUtil();

//OutputDebugString("\nGeneralCreate -3-E");


	m_mmx = new CMMX();
	int offsetX = m_viewControl->GetBackBufferOffsetX();
	int offsetY = m_viewControl->GetBackBufferOffsetY();
//	int realWindowSizeX = m_viewControl->GetRealWindowSizeX();
//	int realWindowSizeY = m_viewControl->GetRealWindowSizeY();
	m_mmx->SetViewParam(realWindowSizeX,realWindowSizeY,offsetX,offsetY);
	

	if (m_directDraw != NULL)
	{
		m_mmx->Set565Mode(m_directDraw->Check565Mode());
		m_mmx->SetRGB24Mode(m_directDraw->CheckRGB24Mode());
		m_mmx->SetRGB32Mode(m_directDraw->CheckRGB32Mode());
	}

//OutputDebugString("\nGeneralCreate -3-F");

	if (m_systemFile->m_systemdata.fullScreenFlag)
//	if (0)
	{
		if (m_directDraw != NULL)
		{
			int realWindowSizeX = m_viewControl->GetRealWindowSizeX();
			int realWindowSizeY = m_viewControl->GetRealWindowSizeY();

			m_directDraw->SetWindowSize(realWindowSizeX,realWindowSizeY);
		}
	}
//OutputDebugString("\nGeneralCreate -3-G");

	SetSystemParam(NNNPARAM_SCREENMODE,m_systemFile->m_systemdata.fullScreenFlag*1);


#if defined _TINYAN3DLIB_
//
#endif


	int commonBufferSize = m_windowSizeX*m_windowSizeY;
	if (commonBufferSize < 800*600) commonBufferSize = 800*600;//minimum buffer size

	m_commonBuffer = new int[commonBufferSize];

//OutputDebugString("\nGeneralCreate -3-H");

#if !defined _TINYAN3DLIB_
	m_commonBG = new CPicture(m_windowSizeX,m_windowSizeY);
	m_commonParts = new CPicture(m_windowSizeX,m_windowSizeY);

	m_overrapPic1 = new CPicture(m_windowSizeX,m_windowSizeY);
	m_overrapPic2 = new CPicture(m_windowSizeX,m_windowSizeY);
#else
	m_commonBG = new CPicture(m_windowSizeX,m_windowSizeY,TRUE);
	m_commonParts = new CPicture(m_windowSizeX,m_windowSizeY);
//OutputDebugString("\n[create overrap1]\n");
	m_overrapPic2 = new CPicture(m_windowSizeX,m_windowSizeY,TRUE);
//OutputDebugString("\n[create overrap2]\n");
	m_overrapPic1 = new CPicture(m_windowSizeX,m_windowSizeY,TRUE);

#endif
//OutputDebugString("\nGeneralCreate -3-I");

//	m_cgCharaKosuu = 1;	//dummy 設定わすれでとばないように
//	m_sceneCharaKosuu = 1;

//	m_cgCharaNumber = 0;
//	m_sceneCharaNumber = 0;


//OutputDebugString("\nGeneralCreate -4");

	m_messageWindow = NULL;
//	m_optionPic = NULL;
//	m_sceneButtonPic = NULL;
	m_miniCG = NULL;

	//ここを可変サイズに
	m_miniCG = new int[m_miniCGSizeX*m_miniCGSizeY];


//AddErrorLog("3");

	m_sceneList = NULL;
	m_sceneDataControl = NULL;
//	m_sceneCharaKosuu = 0;

	int noSceneListFlag = 0;
	GetInitGameParam(&noSceneListFlag,"noSceneListFlag");
	if (noSceneListFlag == 0)
	{
		m_sceneList = new CSceneList();
//		m_sceneCharaKosuu = m_sceneList->GetSceneCharaKosuu();
		m_sceneDataControl = new CSceneDataControl(m_systemFile,m_sceneList);
	}


	m_effect = new CEffect();
	m_effect->ClearAllEffect();

//	m_allEffect = m_effect->GetAllEffect();

	
	m_controlScript = NULL;
	m_execScript = NULL;
	m_execSubScript = NULL;
	m_execSubSubScript = NULL;

	m_noScriptFlag = 0;
	GetInitGameParam(&m_noScriptFlag,"noScriptFlag");


	int controlScriptSize = 64;
	int execScriptSize = 2048;
	int subScriptSize = 2048;
	int subSubScriptSize = 2048;

	GetInitGameParam(&controlScriptSize,"controlScriptSize");
	GetInitGameParam(&execScriptSize,"execScriptSize");
	GetInitGameParam(&subScriptSize,"subScriptSize");
	GetInitGameParam(&subSubScriptSize,"subSubScriptSize");

	if (m_noScriptFlag == 0)
	{
		m_controlScript = new CExecScript(this,controlScriptSize * 1024 / 4);
		m_execScript = new CExecScript(this,execScriptSize * 1024  / 4);//2M
		m_execSubScript = new CExecScript(this,subScriptSize * 1024/ 4);
		m_execSubSubScript = new CExecScript(this,subSubScriptSize * 1024 / 4);

//		m_controlScript = new CExecScript(this,16384);
//		m_execScript = new CExecScript(this,1024*512);//2M
//		m_execSubScript = new CExecScript(this,1024*512);
//		m_execSubSubScript = new CExecScript(this,1024*512);
		m_controlScript->LoadScript("spt\\sys.spt");

		TaihiAllEffect();

	}

	m_varInitFlag = 0;
	GetInitGameParam(&m_varInitFlag,"varInitFlag");
	m_varInitData = NULL;
	if (m_varInitFlag)
	{
		m_varInitData = new CNameList();
		m_varInitData->LoadFile("spt\\varinitdata.xtx");
	}


	m_windowOffMouseButton = 1;
	GetInitGameParam(&m_windowOffMouseButton,"windowOffMouseButton");

	m_varList = new CNameList();
	if (m_noScriptFlag == 0)
	{
		m_varList->LoadFile("spt\\var.fxf",TRUE);	//angou
	}




	m_useSaijitsu = 0;
	GetInitGameParam(&m_useSaijitsu,"useSaijistu");
	m_saijitsuList = NULL;
	if (m_useSaijitsu)
	{
		m_saijitsuList = new CSaijitsuList();
	}

	m_rndVar = -1;
	m_dayMonthVar = -1;
	m_yearVar = -1;
	m_holidayVar = -1;
	m_weekVar = -1;

	m_varNumber = new CVarNumber(m_varList);
	if (m_noScriptFlag == 0)
	{
		SetSystemVarNumber();
	}



	m_renameLayerVarNumber = -1;
	LPSTR renameVarName = NULL;
	m_renameTag = NULL;
	m_renameTagKosuu = 0;
	if (GetInitGameString(&renameVarName,"renameLayerVar"))
	{
		m_renameLayerVarNumber = GetVarNumber(renameVarName);
		if (m_renameLayerVarNumber != -1)
		{
			//cg登録のため可変タグは使えないので、この機能は使用できない


			GetInitGameParam(&m_renameTagKosuu,"renameTagNumber");
			if (m_renameTagKosuu > 0)
			{
				m_renameTag = new char[64*m_renameTagKosuu];
				for (int i=0;i<m_renameTagKosuu;i++)
				{
					m_renameTag[i*64] = 0;
					LPSTR tagName = NULL;
					char name[256];
					wsprintf(name,"renameTag%d",i+1);
					if (GetInitGameString(&tagName,name))
					{
						int ln = strlen(tagName);
						if (ln > 62) ln = 62;
						memcpy(m_renameTag + 64 * i,tagName,ln);

						m_renameTag[64*i+ln] = 0;
						m_renameTag[64*i+ln+1] = 0;
					}
				}
			}
		}
	}



	for (int i=0;i<m_layerKosuuMax;i++)
	{
		char name[256];
		wsprintf(name,"layerOffVar%d",i);
		LPSTR layerOffVarName = NULL;
		if (GetInitGameString(&layerOffVarName,name))
		{
			int varNumber = GetVarNumber(layerOffVarName);
			if (varNumber != -1)
			{
				m_layerOffVar[varNumber] = i;
			}
		}
	}




	m_sptList = new CNameList();
	if (m_noScriptFlag == 0)
	{
		m_sptList->LoadFile("spt\\project.xtx");
	}

	m_backExecClass = new CBackExecClass(this);

	int noBGMFlag = 0;
	GetInitGameParam(&noBGMFlag,"noBGMFlag");
	m_bgmList = NULL;
	if (noBGMFlag == 0)
	{
		m_bgmList = new CNameList();
		m_bgmList->LoadFile("spt\\bgmlist.xtx");
		m_bgmKosuu = m_bgmList->GetNameKosuu() / 2;
	}
	else
	{
		m_bgmKosuu = 0;
	}

	int noSystemSeFlag = 0;
	GetInitGameParam(&noSystemSeFlag,"noSystemSeFlag");
	
	m_systemSeList = NULL;
	m_seList = new CNameList();
	m_charaNameList = new CNameList();
	m_faceList = new CNameList();
	m_functionList = new CNameList();

	if (noSystemSeFlag == 0)
	{
		m_systemSeList = new CNameList();
		m_systemSeList->LoadFile("nya\\systemse.xtx");
	}

//	m_facePrintFlag = 0;
//	GetInitGameParam(&m_facePrintFlag,"facePrintMode");
	m_faceControl = NULL;

	if (m_noScriptFlag == 0)
	{

		m_seList->LoadFile("spt\\selist.xtx");
		m_charaNameList->LoadFile("spt\\charaname.xtx");
		m_functionList->LoadFile("spt\\function.xtx");
		m_faceList->LoadFile("spt\\facelist.xtx");
		if (m_facePrintFlag)
		{
			m_faceControl = new CFaceControl(m_faceList);
			SetAutoSaveSubClass(m_autoSaveDataList->SearchName("face"),m_faceControl);
		}
	}



	m_adjustDateFunction = m_functionList->SearchBlock("adjustdate");
//	m_calendarFunction = m_functionList->SearchBlock("calendar");
	m_setsceneFunction = m_functionList->SearchBlock("setscene");
	m_saveSystemFileFunction = m_functionList->SearchBlock("savesystemfile");
	m_layerOnOffFunction = m_functionList->SearchBlock("layer");

	m_stopF5Function = m_functionList->SearchBlock("stopf5");

	m_commandList = new CNameList();
	if (m_noScriptFlag == 0)
	{
		m_commandList->LoadFile("spt\\command.xtx");
	}

	m_movieList = NULL;
	FILE* file = CMyFile::Open("spt\\movielist.xtx","rb");
	if (file != NULL)
	{
		fclose(file);
		m_movieList = new CNameList();
		m_movieList->LoadFile("spt\\movielist.xtx");
	}


	for (i=0;i<commonUserCommandKosuu;i++)
	{
//		int userClass = m_userCommandClass[i];
		int userClass = m_commonUserCommandList->GetModeNumber(i);
//		if (userClass == -1) break;
		if (m_createModeDisableFlag[userClass] == 0)
		{
//			LPSTR userCommandName = m_userCommandName[i];
			LPSTR userCommandName = m_commonUserCommandList->GetModeName(i);

			int flg = 0;
			char name[256];
			wsprintf(name,"%sIsDefault",userCommandName);
			GetInitGameParam(&flg,name);
			if (flg)
			{
				RegistUserCommand(userClass,userCommandName);
			}
		}
	}


	m_sceneVoice = NULL;
	if (m_noScriptFlag == 0)
	{
		m_sceneVoice = new CSceneVoice();
	}

	m_shakinControl = new CShakin();

	m_shakinControl->SetMax(m_maxSkipFrame);
	m_shakinControl->SetKikan(m_skipAdjustFrame);

	m_maxSkipFrameBackScript = m_maxSkipFrame;
	GetInitGameParam(&m_maxSkipFrameBackScript,"maxSkipFrameBackScript");


	if (CheckNoSkipFrame())
	{
		m_shakinControl->SetMax(1);
	}



	m_specialNumberForSaveSetFlag = 0;
	m_specialNumberForSaveVarNumber = -1;
	GetInitGameParam(&m_specialNumberForSaveSetFlag,"specialNumberForSaveSetFlag");
	if (m_specialNumberForSaveSetFlag)
	{
		LPSTR name = m_defaultSpecialNumberForSaveName;
		GetInitGameString(&name,"specialNumberForSaveVarName");
		m_specialNumberForSaveVarNumber = m_varList->GetNameNumber(name);
	}





	m_optionOffVar = -1;
	int optionOffVarFlag = 0;
	GetInitGameParam(&optionOffVarFlag,"optionOffVarFlag");
	if (optionOffVarFlag)
	{
		LPSTR optionOffVarName = m_defaultOoptionOffVarName;
		GetInitGameString(&optionOffVarName,"optionOffVarName");
		m_optionOffVar = GetVarNumber(optionOffVarName);
	}

	GetInitGameParam(&m_floatingLayerFlashFlag,"floatingLayerFlashFlag");


	m_systemYearVar = -1;
	m_systemMonthVar = -1;
	m_systemDayVar = -1;
	m_systemHourVar = -1;
	m_systemMinuteVar = -1;
	m_systemSecondVar = -1;
	m_systemWeekVar = -1;
	m_systemMilliSecondVar = -1;
	m_modeVar = -1;

	m_mouseXVar = -1;
	m_mouseYVar = 1;
	m_trig1Var = -1;
	m_trig2Var = -1;
	m_trig3Var = -1;
	m_click1Var = -1;
	m_click2Var = -1;
	m_click3Var = -1;
	m_wheelVar = -1;
	m_listenbgmmodeVar = -1;
	m_listenbgmnumberVar = -1;
	

	m_direct3DVar = -1;
	m_pixelShaderVar = -1;
	m_vertexShaderVar = -1;

	m_cgPercentVar = -1;
	m_scenePercentVar = -1;

	m_expButtonKosuu = 16;
	for (i=0;i<m_expButtonKosuu;i++)
	{
		m_expButtonVarNumber[i] = -1;
	}

	m_expModeButtonIsMouse = 0;
	m_expModeButtonIsMessageCursor = 0;
	GetInitGameParam(&m_expModeButtonIsMouse,"expModeButtonIsMouse");
	GetInitGameParam(&m_expModeButtonIsMessageCursor,"expModeButtonIsMessageCursor");


	m_expCheckButtonKosuu = 16;
	for (i=0;i<m_expCheckButtonKosuu;i++)
	{
		m_expCheckButtonVarNumber[i] = -1;
	}

	if (m_noScriptFlag == 0)
	{
		m_systemYearVar = GetVarNumber("systemyear");
		m_systemMonthVar = GetVarNumber("systemmonth");
		m_systemDayVar = GetVarNumber("systemday");
		m_systemHourVar = GetVarNumber("systemhour");
		m_systemMinuteVar = GetVarNumber("systemminute");
		m_systemSecondVar = GetVarNumber("systemsecond");
		m_systemWeekVar = GetVarNumber("systemweek");
		m_systemMilliSecondVar = GetVarNumber("systemmillisecond");
		m_modeVar = GetVarNumber("mode");

		m_direct3DVar = GetVarNumber("direct3d");
		m_pixelShaderVar = GetVarNumber("pixelshader");
		m_vertexShaderVar = GetVarNumber("vertexshader");

		m_mouseXVar = GetVarNumber("mousex");
		m_mouseYVar = GetVarNumber("mousey");
		m_trig1Var = GetVarNumber("trig1");
		m_trig2Var = GetVarNumber("trig2");
		m_trig3Var = GetVarNumber("trig3");
		m_click1Var = GetVarNumber("click1");
		m_click2Var = GetVarNumber("click2");
		m_click3Var = GetVarNumber("click3");
		m_wheelVar = GetVarNumber("wheel");

		m_listenbgmmodeVar = GetVarNumber("listenbgmmode");
		m_listenbgmnumberVar = GetVarNumber("listenbgmnumber");

		m_cgPercentVar = GetVarNumber("cgpercent");
		m_scenePercentVar = GetVarNumber("scenepercent");

		for (i=0;i<5;i++)
		{
			char name[256];
			wsprintf(name,"expmode%d",i+1);
			m_expButtonVarNumber[i] = GetVarNumber(name);
		}

		for (i=0;i<5;i++)
		{
			char name[256];
			wsprintf(name,"expcheck%d",i+1);
			m_expCheckButtonVarNumber[i] = GetVarNumber(name);
		}

	}

	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);
	int masterVolumeFlag = 0;
	GetInitGameParam(&masterVolumeFlag,"masterVolumeFlag");

	m_directSound = new CMyDirectSound(m_hWnd);
	m_mixer = new CMixerControl(masterVolumeFlag);
	int vmr = m_systemFile->m_systemdata.useVMR9;
	m_directShow = new CMyDirectShow(m_hWnd,WM_APP+1,vmr);
	SIZE dsSize;
	dsSize.cx = m_viewControl->GetRealWindowSizeX();
	dsSize.cy = m_viewControl->GetRealWindowSizeY();
	int aspectFitFlag = 1;
	GetInitGameParam(&aspectFitFlag,"movieAspectFit");
	if (m_directShow != NULL) m_directShow->SetAspectFitFlag(aspectFitFlag);
	if (m_directShow != NULL) m_directShow->SetWindowSize(dsSize);
	if (m_directShow != NULL) m_directShow->SetFullMonitorSize(dsSize);
	if (m_directShow != NULL) m_directShow->SetAspectFitSize(m_viewControl->GetAspectFitSize());
	if (m_directShow != NULL) m_directShow->OnDisplayChanged();


	m_messageWindowPrintFlag = TRUE;
	m_messageFontSizeType = 0;

	SetVarData(m_dayMonthVar,101);	//dmy ようじんのため一月一日をいれておく
	SetVarData(m_yearVar,2000);	//dmy ようじんのため2000年をいれておく


	m_defaultFadeInTime = 0;
	m_defaultFadeOutTime = 5;
	GetInitGameParam(&m_defaultFadeInTime,"defaultMusicFadeInTime");
	GetInitGameParam(&m_defaultFadeOutTime,"defaultMusicFadeOutTime");

	m_soundChannel = 2;
	GetInitGameParam(&m_soundChannel,"soundChannel");
	
	m_samplingRate = 44100;
	GetInitGameParam(&m_samplingRate,"samplingRate");

	m_samplingBit = 16;
	GetInitGameParam(&m_samplingBit,"samplingBit");

	int primaryForamtSetFlag = 0;
	GetInitGameParam(&primaryForamtSetFlag,"primaryFormatSetFlag");
	if (primaryForamtSetFlag)
	{
//MessageBox(NULL,"constr-5","gamecallback",MB_OK);
		m_directSound->SetPrimaryFormat(m_soundChannel,m_samplingRate,m_samplingBit);
	}
//OutputDebugString("\nGeneralCreate -6");

	m_3dSoundFlag = 0;
	GetInitGameParam(&m_3dSoundFlag,"sound3DFlag");
	if (m_systemFile->m_systemdata.notUse3DSound)
	{
		m_3dSoundFlag = 0;
	}

//MessageBox(NULL,"constr-6","gamecallback",MB_OK);
	m_directSound->Set3DSoundFlag(m_3dSoundFlag);




	//if (GetMusicMode() == 1)
	if (1)
	{
		m_directSound->Start();
	}


	m_musicControl = new CMusicControl(m_directSound);

	m_musicControl->SetDefaultFadeInOutTime(m_defaultFadeInTime,m_defaultFadeOutTime);


	m_systemSound[0] = new CMyDirectSoundBuffer(m_directSound->GetDirectSound(),FALSE);
	m_systemSound[1] = new CMyDirectSoundBuffer(m_directSound->GetDirectSound(),FALSE);

	m_useSystemSoundNumber = 0;



	int scriptVoiceExpand[4];
	int scriptSoundExpand[8];
	for (int i=0;i<4;i++)
	{
		int sve = 0;
		char name[1024];
		wsprintf(name,"scriptVoiceExpand%d",i+1);
		GetInitGameParam(&sve,name);
		scriptVoiceExpand[i] = sve;
	}

	for (int i=0;i<8;i++)
	{
		int sse = 0;
		char name[1024];
		wsprintf(name,"scriptSoundExpand%d",i+1);
		GetInitGameParam(&sse,name);
		scriptSoundExpand[i] = sse;
	}




//	m_scriptVoice[0] = new CMyDirectSoundBuffer(m_directSound->GetDirectSound(),FALSE);
//	m_scriptVoice[1] = new CMyDirectSoundBuffer(m_directSound->GetDirectSound(),TRUE);
//	m_scriptVoice[2] = new CMyDirectSoundBuffer(m_directSound->GetDirectSound(),FALSE);
//	m_scriptVoice[3] = new CMyDirectSoundBuffer(m_directSound->GetDirectSound(),TRUE);



	for (i=0;i<4;i++)
	{
//		m_scriptSound[i] = new CMyDirectSoundBuffer(m_directSound->GetDirectSound(),FALSE);
	}

	for (i=0;i<4;i++)
	{
//		m_scriptSound[i+4] = new CMyDirectSoundBuffer(m_directSound->GetDirectSound(),TRUE);
	}

	for (i=0;i<8;i++)
	{
//		m_loopSoundWork[i*16] = FALSE;
	}

	m_scriptVoiceControl = new CScriptVoiceControl(m_directSound,scriptVoiceExpand);
	m_scriptSoundControl = new CScriptSoundControl(m_directSound,scriptSoundExpand);

//	m_scriptVoiceControl->AllStop();


	for (i=0;i<8;i++)
	{
//		m_loopVoiceWork[i*16] = FALSE;
	}

//	m_noMidiFlag = 0;
//	GetInitGameParam(&m_noMidiFlag,"noMidiFlag");
//	m_midi = new CMIDIPlayer(m_hWnd,m_directSound,m_mixer,GetMusicMode(),m_noMidiFlag);	//last param == midi_mode

//	m_wave = new CCommonWave(this);
	m_waveData = new CWaveData();


	m_systemWaveLoadKosuu = 4;
	GetInitGameParam(&m_systemWaveLoadKosuu,"systemSoundLoadNumber");

	if (m_systemSeList == NULL)
	{
		m_systemWaveLoadKosuu = 0;
	}

	m_systemWaveArray = NULL;
	if (m_systemWaveLoadKosuu > 0)
	{
		m_systemWaveArray = new CWaveData* [m_systemWaveLoadKosuu];
		for (int i=0;i<m_systemWaveLoadKosuu;i++)
		{
			m_systemWaveArray[i] = new CWaveData();

			char syswavename[256];
			wsprintf(syswavename,"%s",m_systemSeList->GetName(i*2));

			m_systemWaveArray[i]->LoadSystemWave("sys",syswavename);
		}
	}

//OutputDebugString("\nGeneralCreate -7");


	//systempiano
//	for (i=0;i<20;i++)
//	{
//		m_systemPiano[i] = NULL;

//		m_systemPiano[i] = new CWave(this);
//		char filename[256];
//		sprintf(filename,"sys\\%s",m_pianoFileName[i]);
//		m_systemPiano[i]->LoadWave(filename,FALSE);
//	}


	//systemwave
//	for (i=0;i<10;i++)
//	{
//		m_systemWave[i] = new CWave(this);
//		char filename[256];
//		LPSTR name = m_systemSeList->GetName(i*2);
//		sprintf(filename,"sys\\%s",name);
//		m_systemWave[i]->LoadWave(filename,FALSE);
//	}


	m_systemPicture = new CSystemPicture();
	CSystemPicture::m_this = m_systemPicture;


	//initからひろうぶん
	LPSTR defaultFont = NULL;
	GetInitGameString(&defaultFont,"defaultFont");
	if (defaultFont != NULL)
	{
		char fname[256];
		wsprintf(fname,"%s",defaultFont);
		//change to space
		int ln = (int)strlen(fname);
		int n = 0;
		while (n<ln)
		{
			char c = fname[n];
			if (c == '?')
			{
				fname[n] = ' ';
			}

			if (c & 0x80)
			{
				n++;
			}
			n++;
		}

		CMyFont::m_userFont = 1;
		memcpy(CMyFont::m_userFontName,fname,256);
	}

	CMyFont::m_fontType = m_systemFile->m_systemdata.fontType;

	if ((defaultFont == NULL) || (m_systemFile->m_systemdata.userFontFlag))
	{
		CMyFont::m_userFont = m_systemFile->m_systemdata.userFontFlag;
		memcpy(CMyFont::m_userFontName,m_systemFile->m_systemdata.fontName,256);
	}

	//rubi
	int rubiFlag = 0;
	GetInitGameParam(&rubiFlag,"rubiFlag");
	if (rubiFlag)
	{
		CMyFont::m_rubiUseFlag = 1;
		int rubiPercent = CMyFont::m_rubiPercent;
		int rubiDeltaY = CMyFont::m_rubiDeltaY;
		int rubiSukima = CMyFont::m_rubiSukima;
		GetInitGameParam(&rubiPercent,"rubiPercent");
		GetInitGameParam(&rubiDeltaY,"rubiDeltaY");
		GetInitGameParam(&rubiSukima,"rubiSukima");
		CMyFont::m_rubiPercent = rubiPercent;
		CMyFont::m_rubiDeltaY = rubiDeltaY;
		CMyFont::m_rubiSukima = rubiSukima;
		int rubiColorR = CMyFont::m_rubiColorR;
		int rubiColorG = CMyFont::m_rubiColorG;
		int rubiColorB = CMyFont::m_rubiColorB;
		GetInitGameParam(&rubiColorR,"rubiColorR");
		GetInitGameParam(&rubiColorG,"rubiColorG");
		GetInitGameParam(&rubiColorB,"rubiColorB");
		CMyFont::m_rubiColorR = rubiColorR;
		CMyFont::m_rubiColorG = rubiColorG;
		CMyFont::m_rubiColorB = rubiColorB;
		int rubiColorFixFlag = CMyFont::m_rubiColorFixFlag;
		GetInitGameParam(&rubiColorFixFlag,"rubiColorFix");
		CMyFont::m_rubiColorFixFlag = rubiColorFixFlag;
	}

	int codeByte = 2;
	GetInitGameParam(&codeByte,"codeByte");
	if (codeByte == 1)
	{
		CMyFont::m_codeByte = 1;
	}

	int fontWeight = 700;
	if (GetInitGameParam(&fontWeight,"fontWeight"))
	{
		if ((fontWeight >= 0) && (fontWeight <= 1000))
		{
			CMyFont::m_fontWeight = fontWeight;
		}
	}

	int fontItalic = 0;
	if (GetInitGameParam(&fontItalic,"fontItalic"))
	{
		CMyFont::m_fontItalic = fontItalic;
	}

	int fukuro = 0;
	GetInitGameParam(&fukuro,"fukuroMoji");
	CMyFont::SetFukuroType(fukuro);


	int fukuroCustom = 0;
	GetInitGameParam(&fukuroCustom,"fukuroCustom");
	if (fukuroCustom)
	{
		for (int j=0;j<=2;j++)
		{
			for (i=0;i<=2;i++)
			{
				char name[256];
				sprintf_s(name,sizeof(name),"fukuro%d_%d",j+1,i+1);
				int fkr = 0;
				GetInitGameParam(&fkr,name);
				CMyFont::m_fukuroTable[j][i] = fkr;
			}
		}
	}




	m_font = new CMyFont(m_hWnd);
	m_message = new CMyMessage(m_font);

	//load user font
	m_userFontKosuu = 0;
	GetInitGameParam(&m_userFontKosuu,"userFontNumber");
	for (i=0;i<m_userFontKosuu;i++)
	{
		char name[256];
		wsprintf(name,"userFont%dFileName",i+1);
		LPSTR userFontName = NULL;
		GetInitGameString(&userFontName,name);
		if (userFontName != NULL)
		{
			if ((*userFontName) != 0)
			{
				m_font->LoadUserFont(userFontName);
			}
		}
	}


//AddErrorLog("7");


	m_taihi = new CTaihi();

	for (int tt=0;tt<PICTURE_KOSUU_MAX;tt++)
	{
		m_taihiFileName[tt][0] = 0;
	}

	m_gameMouse = NULL;
	m_messageCursor = NULL;
	m_optionButton = NULL;
	m_sceneButton = NULL;
	m_skipFilmButton = NULL;
	m_quickSaveButton = NULL;
	m_quickLoadButton = NULL;
	m_quickConfigButton = NULL;
	m_quickBackLogButton = NULL;

	m_freeSaveButton = NULL;
	m_freeLoadButton = NULL;
	m_freeAutoButton = NULL;
	m_freeSkipButton = NULL;
	m_freeWindowOffButton = NULL;

	m_notice = NULL;

	m_gameMouseCreateFlag = 1;
	m_messageCursorCreateFlag = 1;
	m_optionButtonCreateFlag = 1;
	m_sceneButtonCreateFlag = 1;
	m_skipFilmButtonCreateFlag = 0;
	int quickSaveButtonCreateFlag = 0;
	int quickLoadButtonCreateFlag = 0;
	int quickConfigButtonCreateFlag = 0;
	int quickBackLogButtonCreateFlag = 0;
	m_noticeFlag = 0;


//OutputDebugString("\nGeneralCreate -8");

	GetInitGameParam(&m_gameMouseCreateFlag,"gameMouseCreateFlag");
	GetInitGameParam(&m_messageCursorCreateFlag,"messageCursorCreateFlag");
	GetInitGameParam(&m_optionButtonCreateFlag,"optionButtonCreateFlag");
	GetInitGameParam(&m_sceneButtonCreateFlag,"sceneButtonCreateFlag");
	GetInitGameParam(&m_skipFilmButtonCreateFlag,"skipFilmButtonCreateFlag");

	if (m_quickSaveEnable)
	{
		GetInitGameParam(&quickSaveButtonCreateFlag,"quickSaveButtonCreateFlag");
	}
	if (m_quickLoadEnable)
	{
		GetInitGameParam(&quickLoadButtonCreateFlag,"quickLoadButtonCreateFlag");
	}
	GetInitGameParam(&quickConfigButtonCreateFlag,"quickConfigButtonCreateFlag");
	GetInitGameParam(&quickBackLogButtonCreateFlag,"quickBacklogButtonCreateFlag");
	
	int freeSaveButtonCreateFlag = 0;
	int freeLoadButtonCreateFlag = 0;
	int freeAutoButtonCreateFlag = 0;
	int freeSkipButtonCreateFlag = 0;
	int freeWindowOffButtonCreateFlag = 0;

	GetInitGameParam(&freeSaveButtonCreateFlag,"freeSaveButtonCreateFlag");
	GetInitGameParam(&freeLoadButtonCreateFlag,"freeLoadButtonCreateFlag");
	GetInitGameParam(&freeAutoButtonCreateFlag,"freeAutoButtonCreateFlag");
	GetInitGameParam(&freeSkipButtonCreateFlag,"freeSkipButtonCreateFlag");
	GetInitGameParam(&freeWindowOffButtonCreateFlag,"freeWindowOffButtonCreateFlag");



	GetInitGameParam(&m_noticeFlag,"noticeFlag");

	m_loadNoticeNumber = 1;
	m_saveNoticeNumber = 2;
	if (m_noticeFlag)
	{
		GetInitGameParam(&m_loadNoticeNumber,"loadNoticeNumber");
		GetInitGameParam(&m_loadNoticeNumber,"saveNoticeNumber");
	}

	//0:なし 1:シーン 2:オプションタイプ 3:(1+2)
	m_sceneButtonMode = 2;
	GetInitGameParam(&m_sceneButtonMode,"sceneButtonMode");

	if (m_gameMouseCreateFlag) m_gameMouse = new CGameMouse(m_taihi,0);
	if (m_messageCursorCreateFlag) m_messageCursor = new CMessageCursor(m_taihi,2);
	if (m_optionButtonCreateFlag) m_optionButton = new CSceneOptionButton("optionButton",m_taihi,4);
	if (m_sceneButtonCreateFlag && (m_sceneButtonMode & 1)) m_sceneButton = new CSceneOptionButton("sceneButton",m_taihi,8);
	if (m_skipFilmButtonCreateFlag) m_skipFilmButton = new CSceneOptionButton("skipFilmButton",m_taihi,12);
	if (quickSaveButtonCreateFlag) m_quickSaveButton = new CSceneOptionButton("quickSaveButton",m_taihi,14);
	if (quickLoadButtonCreateFlag)
	{
		m_quickLoadButton = new CSceneOptionButton("quickLoadButton",m_taihi,15);
		m_quickLoadButton->SetReturnCannotClick();
	}
	if (quickConfigButtonCreateFlag) m_quickConfigButton = new CSceneOptionButton("quickConfigButton",m_taihi,16);
	if (quickBackLogButtonCreateFlag) m_quickBackLogButton = new CSceneOptionButton("quickBacklogButton",m_taihi,18);

	if (freeSaveButtonCreateFlag) m_freeSaveButton = new CSceneOptionButton("freeSaveButton",m_taihi,20);
	if (freeLoadButtonCreateFlag) m_freeLoadButton = new CSceneOptionButton("freeLoadButton",m_taihi,22);
	if (freeAutoButtonCreateFlag) m_freeAutoButton = new CSceneOptionButton("freeAutoButton",m_taihi,24);
	if (freeSkipButtonCreateFlag) m_freeSkipButton = new CSceneOptionButton("freeSkipButton",m_taihi,26);
	if (freeWindowOffButtonCreateFlag) m_freeWindowOffButton = new CSceneOptionButton("freeWindowOffButton",m_taihi,28);

	//30,31



	if (m_noticeFlag) m_notice = new CNotice(m_taihi,32);

	m_noticeFunction = -1;
	if (m_noticeFlag)
	{
		m_noticeFunction = m_functionList->SearchBlock("notice");
	}

	m_setresultFunction = -1;
	m_getresultFunction = -1;

	m_resultFlag = 0;
	GetInitGameParam(&m_resultFlag,"resultFlag");
	m_commonResultData = NULL;
	m_getResultVarNumber = -1;
	m_autoResultNotice = 0;
	if (m_resultFlag)
	{
		m_commonResultData = new CCommonResultData("result",1024,FALSE,1,NULL);

		m_setresultFunction = m_functionList->SearchBlock("setresult");

		LPSTR getResultVarName = NULL;
		if (GetInitGameString(&getResultVarName,"getResultVarName"))
		{
			m_getresultFunction = m_functionList->SearchBlock("getresult");
			m_getResultVarNumber = GetVarNumber(getResultVarName);
		}

		GetInitGameParam(&m_autoResultNotice,"autoResultNotice");
	}


	m_gameUtil = new CGameUtil();
	m_gameUtil->SetScreenSize(screenSizeX,screenSizeY);
	m_gameUtil->SetMiniCGSize(m_miniCGSizeX,m_miniCGSizeY);
	m_gameUtil->SetMiniCGReduce(m_miniCGReduce);


	m_messageWindowDontPrintFlag = 0;
	GetInitGameParam(&m_messageWindowDontPrintFlag,"noMessageWindowFlag");
	if (m_messageWindowDontPrintFlag == 0)
	{
		m_messageWindow = new CCommonMessageWindow();
		SetMessageWindowPercent();
	}
	else
	{
		m_messageWindow = NULL;
	}


	ClearWindowMouseCursorNumberByScript();

	SetWindowNumberByConfig(m_systemFile->m_systemdata.windowNumber);
	SetMouseNumberByConfig(m_systemFile->m_systemdata.mouseNumber);
	SetCursorNumberByConfig(m_systemFile->m_systemdata.cursorNumber);


	SetupBossComing();

	m_allMusicSetFlag = 1;
	GetInitGameParam(&m_allMusicSetFlag,"allMusicSetFlag");

//	m_messageWindowPic = GetSystemPicture("ta_meswin");

//	CreateMovingLayer(0,32,32);	//mouse;
//	CreateMovingLayer(1,24,24);	//message cursor

//	m_mousePic = GetSystemPicture("mouse");

//	m_cursorPic[0] = GetSystemPicture("mes_cur");
//	m_cursorPic[1] = GetSystemPicture("mes_cur2");
//	m_cursorPic[2] = GetSystemPicture("mes_cur");
//	m_cursorPic[3] = GetSystemPicture("mes_cur");


//	m_optionPic = GetSystemPicture("menubutn");
//	m_sceneButtonPic = GetSystemPicture("scene_bk");


//OutputDebugString("\nGeneralCreate -9");

	//設定ファイルからひろってくる

	char keyname[256];
	wsprintf(keyname,"Software\\%s\\%s",m_companyName,m_productName);

	int n= 0;
	int ln = (int)strlen(keyname);
	while (n<ln)
	{
		char c = keyname[n];
		if (c == '?')
		{
			keyname[n] = ' ';
		}
		if (c & 0x80)
		{
			n++;
		}
		n++;
	}

/*
	HKEY hkey;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,keyname,0,KEY_READ,&hkey) == ERROR_SUCCESS)
	{
		DWORD nType;
		DWORD dt;
		DWORD pcbData = 4;
		if (RegQueryValueEx(hkey,"installmode",NULL,&nType,(unsigned char*)&dt,&pcbData) == ERROR_SUCCESS)
		{
			if (dt == 0)
			{
				char cdwavedir[256];
				DWORD pcbData2 = 256;
				if (RegQueryValueEx(hkey,"wavedirectory",NULL,&nType,(unsigned char*)cdwavedir,&pcbData2) == ERROR_SUCCESS)
				{
					memcpy(CWaveData::m_cdDirName,cdwavedir,pcbData2);
				}
			}
		}
		RegCloseKey(hkey);
	}
*/


//	m_commonBG = new CPicture(m_windowSizeX,m_windowSizeY);
//	m_commonParts = new CPicture(m_windowSizeX,m_windowSizeY);
//
//	m_overrapPic1 = new CPicture(m_windowSizeX,m_windowSizeY);
//	m_overrapPic2 = new CPicture(m_windowSizeX,m_windowSizeY);

//	m_effect = new CEffect();

	m_mouseStatus = new CMyMouseStatus();
	m_inputStatus = new CInputStatus();
	m_keyStatus = new CMyKeyStatus();
	m_inputStatus->SetMouseStatus(m_mouseStatus);
	m_inputStatus->SetKeyStatus(m_keyStatus);

	m_textInputBox = new CMyTextInputBox(m_hWnd,m_message,m_viewControl);

	m_imeAutoOpenFlag = 1;
	GetInitGameParam(&m_imeAutoOpenFlag,"imeAutoOpenFlag");
	m_imeAutoCloseFlag = m_imeAutoOpenFlag;
	GetInitGameParam(&m_imeAutoCloseFlag,"imeAutoCloseFlag");
	m_textInputBox->SetAuto(m_imeAutoOpenFlag,m_imeAutoCloseFlag);


	//default option,mouse,cursor,scenebutton



//AddErrorLog("8");

//OutputDebugString("\nGeneralCreate -10");


	m_printDebugParam = new CPrintDebugParam(this);
	int vistaPatch = 0;
//	if (GetVersion() >= 6)
	if (1)
	{
//		vistaPatch = 1;
		GetInitGameParam(&vistaPatch,"vistaDebug");
		m_printDebugParam->SetVistaPatch(vistaPatch);
	}

	m_printDebugParam->AddDebugVarNumber(300);

	//backbutton

//	m_fileControl = new CCommonFileControl(this);


	//messagewindow


//AddErrorLog("8.1");


	//バッファー初期サイズ設定
	int pictureBufferInitSizeFlag = 0;
	int pictureBufferInitLoadFlag = 0;
	GetInitGameParam(&pictureBufferInitSizeFlag,"pictureBufferInitSizeFlag");
	GetInitGameParam(&pictureBufferInitLoadFlag,"pictureBufferInitLoadFlag");
//AddErrorLog("8.11");

	for (i=0;i<m_pictureKosuuMax;i++)
	{
//AddErrorLog("8.12LOOP");
		CPicture* effpic = m_effect->GetPicture(i);
		if (effpic != NULL)
		{
			if (pictureBufferInitSizeFlag)
			{
				int sx = 0;
				int sy = 0;
				char name[256];

				wsprintf(name,"pictureBufferSizeX%d",i+1);
				GetInitGameParam(&sx,name);

				wsprintf(name,"pictureBufferSizeY%d",i+1);
				GetInitGameParam(&sy,name);

				if ((sx > 0) && (sy>0))
				{
					effpic->ReSize(sx,sy);
				}
			}

			if (pictureBufferInitLoadFlag)
			{
				LPSTR loadfilename = NULL;
				char name[256];
				wsprintf(name,"pictureBufferFileName%d",i+1);

				if (GetInitGameString(&loadfilename,name))
				{
					if (loadfilename != NULL)
					{
						effpic->LoadDWQ(loadfilename);
					}
				}
			}
		}
	}
//AddErrorLog("8.13");

	m_fukaPrint = NULL;
	SetupFukaPrint();
	m_fpsPrint = NULL;
	SetupFpsPrint();

//	SetCalendarFlag(FALSE);
	SetOption(FALSE);

	m_downed1 = FALSE;
	m_downed2 = FALSE;
	m_downed3 = FALSE;

	m_shiftKey = FALSE;
	m_ctrlKey = FALSE;
//AddErrorLog("8.14");

//OutputDebugString("\nGeneralCreate -11");

	m_mouseStatus->Init(TRUE);

	m_yoyakuExecFlag = FALSE;
//AddErrorLog("8.15");

	if (m_controlScript != NULL) m_controlScript->SetPC(0);
	if (m_controlScript != NULL) m_controlScript->m_stackPointer = 0;
	SetMessageSkipFlag(FALSE);
//	m_noMessageWindowFlag = FALSE;

//AddErrorLog("8.16");

	ClearAllKey();
//AddErrorLog("8.17");

	//set volume
	//soundはそのまま

//AddErrorLog("8.2");

	m_skipToFilmEndEnable = FALSE;


	//WAVE 修正 DirectX
	if (m_directXInitVolumeFlag)
	{
//			m_mixer->SetWAVEVolume(60);
		m_mixer->SetWAVEVolume(m_directXInitVolume);
	}

	if (m_totalVolumeUseFlag)
	{
		int totalInitFlag = 1;
		GetInitGameParam(&totalInitFlag,"totalVolumeInitFlag");
		if (totalInitFlag)
		{
			m_mixer->SetTotalVolume(GetSystemParam(NNNPARAM_TOTALVOLUME));
		}

	}


	SetDontPlay(0);

//AddErrorLog("8.3");


	m_resetNameByStartTitle = 0;
	GetInitGameParam(&m_resetNameByStartTitle,"resetNameByStartTitle");

	LPSTR sei = m_systemFile->m_systemdata.sei;
	int ln1 = (int)strlen(sei);
	if (ln1 == 0)
	{
		LPSTR seiInitData = NULL;
		if (GetInitGameString(&seiInitData,"seiInitData"))
		{
			int len1a = (int)strlen(seiInitData);
			memcpy(m_systemFile->m_systemdata.sei,seiInitData,len1a+1);

			int seiClearFlag = 0;
			GetInitGameParam(&seiClearFlag,"seiClearFlag");
			if (seiClearFlag)
			{
				m_systemFile->m_systemdata.sei[0] = 0;
			}

			sei = m_systemFile->m_systemdata.sei;
		}
	}

//	memcpy(CNameInput::m_defaultSei,sei,ln1+1);

	LPSTR mei = m_systemFile->m_systemdata.mei;
	int ln2 = (int)strlen(mei);
	if (ln2 == 0)
	{
		LPSTR meiInitData = NULL;
		if (GetInitGameString(&meiInitData,"meiInitData"))
		{
			int len2a = (int)strlen(meiInitData);
			memcpy(m_systemFile->m_systemdata.mei,meiInitData,len2a+1);

			int meiClearFlag = 0;
			GetInitGameParam(&meiClearFlag,"meiClearFlag");
			if (meiClearFlag)
			{
				m_systemFile->m_systemdata.mei[0] = 0;
			}

			mei = m_systemFile->m_systemdata.mei;
		}
	}

//	memcpy(CNameInput::m_defaultMei,mei,ln2+1);


	memcpy(CMyMessage::m_sei,sei,strlen(sei)+1);
	memcpy(CMyMessage::m_mei,mei,strlen(mei)+1);






	int santenUseFlag = 1;
	int dashUseFlag = 1;
	GetInitGameParam(&santenUseFlag,"santenUseFlag");
	GetInitGameParam(&dashUseFlag,"dashUseFlag");
	CMyMessage::m_santenCheckFlag = santenUseFlag;
	CMyMessage::m_dashCheckFlag = dashUseFlag;



//OutputDebugString("\nGeneralCreate -12");

//AddErrorLog("8.4");


	m_expModeCheckVarNumber = new int[256];
	for (int i=0;i<256;i++)
	{
		m_expModeCheckVarNumber[i] = 0;
	}
	int expModeCheckKosuu = 0;
	GetInitGameParam(&expModeCheckKosuu,"expModeCheckByVarNumber");
	for (int i=0;i<expModeCheckKosuu;i++)
	{
		char name[256];
		wsprintf(name,"expModeCheckByVarMode%d",i+1);
		int md = 0;
		GetInitGameParam(&md,name);
		if ((md>0) && (md<256))
		{
			wsprintf(name,"expModeCheckByVarName%d",i+1);
			LPSTR varName = NULL;
			if (GetInitGameString(&varName,name))
			{
				m_expModeCheckVarNumber[md] = GetVarNumber(varName);
			}
		}
	}


	m_shortCutSystemMenuSound = 1;
	GetInitGameParam(&m_shortCutSystemMenuSound,"shortCutSystemMenuSound");
	m_shortCutSaveSound = m_shortCutSystemMenuSound;
	m_shortCutLoadSound = m_shortCutSystemMenuSound;
	m_shortCutConfigSound = m_shortCutSystemMenuSound;
	GetInitGameParam(&m_shortCutSaveSound,"shortCutSaveSound");
	GetInitGameParam(&m_shortCutLoadSound,"shortCutLoadSound");
	GetInitGameParam(&m_shortCutConfigSound,"shortCutConfigSound");

//AddErrorLog("8.5");

	m_nameIsSpecialVoiceFlag = -1;
	m_specialVoiceNameKosuu = 0;
	GetInitGameParam(&m_specialVoiceNameKosuu,"specialVoiceNameNumber");
	m_specialVoiceName = new char[m_specialVoiceNameKosuu * 64 + 1];
	for (int i=0;i<m_specialVoiceNameKosuu;i++)
	{
		LPSTR name = GetGameDefaultSeiMei(1);
		char key[256];
		sprintf_s(key,"specialVoiceName%d",i+1);
		GetInitGameString(&name,key);
		int ln = strlen(name);
		if (ln>62) ln = 62;
		memcpy(m_specialVoiceName + i*64,name,ln);
		m_specialVoiceName[i*64+ln] = 0;
		m_specialVoiceName[i*64+ln+1] = 0;
	}


	m_effect->ClearAllEffect();

	ClearWork();
//OutputDebugString("\nGeneralCreate -13");

//AddErrorLog("8.6");

	CAreaControl::SetNextAllPrint();

	m_gameCreateFlagGeneral = TRUE;
#if defined _TINYAN3DLIB_
	if (m_myDirect3D != NULL)
	{
		if (0)
		{



			CTextureCacheControl::ReleaseAllTexture();
			((CMyDirect3D*)m_myDirect3D)->ReleaseAllResource();

			((CMyDirect3D*)m_myDirect3D)->ResetAndWait(m_systemFile->m_systemdata.fullScreenFlag);
			//

			((CMyDirect3D*)m_myDirect3D)->CreateAllResource();
			m_myGraphics->ReCreateAllShader();
			m_effect->ReCreateAllShader();

			LPDIRECT3DDEVICE9 d3ddev9 = CMyDirect3D::GetD3DDevice();
			if (d3ddev9 != NULL)
			{
				d3ddev9->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR(0xffff),1.0f,0);
			}
		}

	}
#endif


//AddErrorLog("endof GameCallBack");
//MessageBox(NULL,"GeneralCreateOk","CGameCallBack",MB_OK);
}


//継承されたCGameのCreate終了後に呼ばれる
void CGameCallBack::AfterCreate(void)
{

	CCommonSystemMenu* obj = (CCommonSystemMenu*)(m_general[SYSTEMMENU_MODE]);
	if (obj != NULL)
	{
		int kosuu = obj->GetOptionKosuu();
		if (kosuu > m_expSystemMenuStart)
		{
			m_expSystemMenuKosuu = kosuu - m_expSystemMenuStart;
			m_expSystemMenuMode = new int[kosuu];
			m_expSystemMenuCommand = new int[kosuu];
			m_expSystemMenuShortCut = new int[kosuu];
			m_expSystemMenuSound = new int[kosuu];

			for (int i=0;i<kosuu;i++)
			{
				m_expSystemMenuMode[i] = 0;
				m_expSystemMenuCommand[i] = 0;
				m_expSystemMenuShortCut[i] = -1;
				m_expSystemMenuSound[i] = -1;
			}

			for (int i=0;i<m_expSystemMenuKosuu;i++)
			{
				int k = m_expSystemMenuStart+i;
				m_expSystemMenuMode[k] = obj->GetExpOptionMode(k);
				m_expSystemMenuCommand[k] = obj->GetExpCommandMode(k);
				m_expSystemMenuShortCut[k] = obj->GetExpShortCutKey(k);
				m_expSystemMenuSound[k] = obj->GetExpSound(k);
			}
		}
	}


	//face?
	for (int i=0;i<m_autoExtSubDataLoadKosuu;i++)
	{
		if (m_autoExtDataLoadSub[i] > 0)
		{
			CAutoSaveSubData* subClass = m_autoSaveSubDataClass[i];
			if (subClass != NULL)
			{
				int dataSize = subClass->GetDataSize();
				ChangeAutoExtSubDataSize(i,dataSize);
			}
		}
	}
}






CGameCallBack::~CGameCallBack()
{
	End();
}

void CGameCallBack::End(void)
{
	if (m_gameCreateFlagGeneral == FALSE) return;

	DELETEARRAY(m_specialVoiceName);


	DELETEARRAY(m_expSystemMenuSound);
	DELETEARRAY(m_expSystemMenuCommand);
	DELETEARRAY(m_expSystemMenuMode);
	DELETEARRAY(m_expSystemMenuShortCut);

	DELETEARRAY(m_expModeCheckVarNumber);

	int i= 0;
//ugString("CGameCallBack::End();\n");

//	if (m_scriptSound[0] != NULL)
	if (m_scriptSoundControl != NULL)
	{
		StopMusic();
		Sleep(300);
	}


	for (i=0;i<8;i++)
	{
//		ENDDELETECLASS(m_scriptSound[i]);
	}
	ENDDELETECLASS(m_scriptVoiceControl);
	ENDDELETECLASS(m_scriptSoundControl);

//	ENDDELETECLASS(m_scriptVoice[0]);
//	ENDDELETECLASS(m_scriptVoice[1]);
//	ENDDELETECLASS(m_scriptVoice[2]);
//	ENDDELETECLASS(m_scriptVoice[3]);

	ENDDELETECLASS(m_systemSound[0]);
	ENDDELETECLASS(m_systemSound[1]);


	ENDDELETECLASS(m_musicControl);
//	if (m_waveMusic[0] != NULL)
//	{
//		StopMusic();
//		Sleep(300);
//		ENDDELETECLASS(m_waveMusic[1]);
//		ENDDELETECLASS(m_waveMusic[0]);
//	}

ENDDELETECLASS(m_waveData);	//dummy

//	if (m_wave != NULL)
//	{
//OutputDebugString("StopWave();\n");
//		m_wave->StopWave();
//		Sleep(100);
//	}



//	if (m_midi != NULL)
//	{
//OutputDebugString("StopBgm();\n");
//		StopBGM();
//		m_midi->Stop();
		Sleep(300);
//	}

//OutputDebugString("delete class block 1;\n");

	ENDDELETECLASS(m_fpsPrint);
	ENDDELETECLASS(m_fukaPrint);

	ENDDELETECLASS(m_bossComingPic);

	ENDDELETECLASS(m_messageWindow);

	ENDDELETECLASS(m_printDebugParam);

	ENDDELETECLASS(m_execSubSubScript);
	ENDDELETECLASS(m_execSubScript);
	ENDDELETECLASS(m_execScript);
	ENDDELETECLASS(m_controlScript);

	ENDDELETECLASS(m_overrapPic2);
	ENDDELETECLASS(m_overrapPic1);

	ENDDELETECLASS(m_commonBG);
	ENDDELETECLASS(m_commonParts);


//OutputDebugString("delete all CCommonGeneral;\n");

	for (i=0;i<MODE_MAX;i++)
	{
		DELETECLASS(m_general[i]);
	}

	DELETEARRAY(m_backLogOkTable);
	ENDDELETECLASS(m_omakeClassSupport);

//OutputDebugString("delete class block 2;\n");

	ENDDELETECLASS(m_sceneDataControl);
	ENDDELETECLASS(m_sceneList);
//	ENDDELETECLASS(m_fileControl);
//@@@	ENDDELETECLASS(m_backButton);

	ENDDELETECLASS(m_textInputBox);

	ENDDELETECLASS(m_inputStatus);
	ENDDELETECLASS(m_mouseStatus);
	ENDDELETECLASS(m_keyStatus);
	ENDDELETECLASS(m_gameUtil);

	ENDDELETECLASS(m_commonResultData);
	ENDDELETECLASS(m_notice);
	ENDDELETECLASS(m_quickBackLogButton);
	ENDDELETECLASS(m_quickConfigButton);
	ENDDELETECLASS(m_quickLoadButton);
	ENDDELETECLASS(m_quickSaveButton);

	ENDDELETECLASS(m_freeSaveButton);
	ENDDELETECLASS(m_freeLoadButton);
	ENDDELETECLASS(m_freeAutoButton);
	ENDDELETECLASS(m_freeSkipButton);
	ENDDELETECLASS(m_freeWindowOffButton);

	ENDDELETECLASS(m_skipFilmButton);
	ENDDELETECLASS(m_sceneButton);
	ENDDELETECLASS(m_optionButton);
	ENDDELETECLASS(m_messageCursor);
	ENDDELETECLASS(m_gameMouse);

	ENDDELETECLASS(m_taihi);

	ENDDELETECLASS(m_message);
	ENDDELETECLASS(m_font);
	ENDDELETECLASS(m_systemPicture);

	ENDDELETECLASS(m_superDownButtonSetup);
	ENDDELETECLASS(m_superUpButtonSetup);
	ENDDELETECLASS(m_superBackButtonSetup);

//OutputDebugString("delete sound class block;\n");

	if (m_systemWaveArray != NULL)
	{
		for (int i=0;i<m_systemWaveLoadKosuu;i++)
		{
			ENDDELETECLASS(m_systemWaveArray[i]);
		}
		DELETEARRAY(m_systemWaveArray);
	}

//OutputDebugString("delete m_wave;\n");
//@@@	ENDDELETECLASS(m_wave);
//OutputDebugString("delete m_midi;\n");
//	ENDDELETECLASS(m_midi);
//OutputDebugString("delete m_mixer;\n");

//	ENDDELETECLASS(m_cdControl);
	ENDDELETECLASS(m_mixer);
//OutputDebugString("delete m_directSound;\n");

	ENDDELETECLASS(m_directShow);
	ENDDELETECLASS(m_directSound);

//@@@	ENDDELETECLASS(m_gameUtil);

//OutputDebugString("delete mmx;\n");

	ENDDELETECLASS(m_mmx);
//OutputDebugString("delete directX\n");







	DELETEARRAY(m_renameTag);
	ENDDELETECLASS(m_varNumber);


	ENDDELETECLASS(m_cgDataControl);

	ENDDELETECLASS(m_hSaveList);
	ENDDELETECLASS(m_hSaveMaskPic);

	ENDDELETECLASS(m_autoSelectControl);

//OutputDebugString("delete ***ListX\n");
//	if (m_cgList != NULL)
//	{
//		for (i=0;i<m_cgCharaKosuu;i++)
//		{
//			ENDDELETECLASS(m_cgList[i]);
//		}
//	}
//	DELETEARRAY(m_cgList);

	ENDDELETECLASS(m_functionList);
	ENDDELETECLASS(m_movieList);
	ENDDELETECLASS(m_commandList);
//	ENDDELETECLASS(m_sceneVoiceList);
	ENDDELETECLASS(m_shakinControl);
	ENDDELETECLASS(m_sceneVoice);
	ENDDELETECLASS(m_faceList);
	ENDDELETECLASS(m_charaNameList);
	ENDDELETECLASS(m_sptList);
	ENDDELETECLASS(m_faceControl);
	ENDDELETECLASS(m_seList);
	ENDDELETECLASS(m_systemSeList);
	ENDDELETECLASS(m_varInitData);
	ENDDELETECLASS(m_saijitsuList);
	ENDDELETECLASS(m_varList);
	ENDDELETECLASS(m_bgmList);

//OutputDebugString("delete CEffectX\n");

	ENDDELETECLASS(m_backExecClass);
	ENDDELETECLASS(m_effect);




//	DELETEARRAY(m_cgKosuu);
	DELETEARRAY(m_miniCG);
	DELETEARRAY(m_commonBuffer);

//OutputDebugString("ReleaseStaticData() 1;\n");


	ENDDELETECLASS(m_myGraphics);

//OutputDebugString("ReleaseStaticData() 2;\n");
	CPicture::ReleaseStaticData();



#if defined _TINYAN3DLIB_
	ENDDELETECLASS(m_textureCacheControl);
	if (m_myDirect3D != NULL)
	{
		((CMyDirect3D*)m_myDirect3D)->End();
		m_myDirect3D = NULL;

		LPDIRECT3D9 lastD3DDevice = CMyDirect3D::GetD3D();
		if (lastD3DDevice != NULL)
		{
			lastD3DDevice->Release();
		}
		LPDIRECT3DDEVICE9 lastD3D = CMyDirect3D::GetD3DDevice();
		if (lastD3D != NULL)
		{
			lastD3D->Release();
		}
	}

#endif

	ENDDELETECLASS(m_directDraw);

	if (m_startFrequency >= 0)
	{
		DEVMODE devMode;

		ZeroMemory(&devMode,sizeof(devMode));
		devMode.dmSize = sizeof(devMode);

		devMode.dmPelsWidth = m_startWidth;
		devMode.dmPelsHeight = m_startHeight;
//		devMode.dmDisplayFrequency = m_startFrequency;

//		devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;
		devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

//		ChangeDisplaySettings(&devMode, 0);
		if (	m_displaySettingChanged)
		{
			ChangeDisplaySettings(NULL, 0);
		}
		m_startFrequency = -1;
	}


//	CMyGraphics::ReleaseStaticData();


	DELETEARRAY(m_autoSaveSubDataClass);
	DELETEARRAY(m_autoExtDataLoadSub);
	DELETEARRAY(m_autoExtDataLoadMode);
	DELETEARRAY(m_extSaveDataSizeTable);
	ENDDELETECLASS(m_autoSaveDataList);

//	ENDDELETECLASS(m_setup2);
	ENDDELETECLASS(m_commonUserCommandList);
	ENDDELETECLASS(m_systemModeList);
	ENDDELETECLASS(m_superButtonPicture);
	DELETEARRAY(m_layerOffVar);
	ENDDELETECLASS(m_dataFileSetup);

	ENDDELETECLASS(m_setup3);
	ENDDELETECLASS(m_setup);

	if (m_saveComment != NULL)
	{
		for (int i=0;i<m_saveCommentKosuuMax;i++)
		{
			DELETEARRAY(m_saveComment[i]);
		}
		DELETEARRAY(m_saveComment);
	}


	for (i=0;i<4;i++)
	{
		if (m_threadControlHandle[i] != NULL)
		{
			CloseHandle(m_threadControlHandle[i]);
			m_threadControlHandle[i] = NULL;
		}
	}
//OutputDebugString("End of CGameCallBack::End();\n");
}

















void CGameCallBack::ReceiveUserCommand0(int cmd, int paraKosuu, int* paraPtr)
{
	BOOL proceed = FALSE;

	m_skipF4Mode = FALSE;
	m_skipF5Mode = FALSE;
	m_skipNextCommandFlag = FALSE;
	m_skipEffectCommandFlag = FALSE;
	m_skipToFilmEndFlag = FALSE;

	//default selectplace,selectheroin,printmovie,printcalendar...

	for (int i=0;i<m_defaultUserCommandKosuu;i++)
	{
		if (cmd == m_defaultUserCommandNumber[i])
		{
			CCommonGeneral* general = m_general[m_defaultUserCommandClass[i]];
			if (general != NULL)
			{
				CreateNowExitScreen();
				general->StartUserCommand(paraKosuu,paraPtr);
				proceed = TRUE;
				SetReturnCode(m_defaultUserCommandClass[i]);
				break;
			}
		}
	}



	if (proceed == FALSE)
	{
		ReceiveUserCommand(cmd,paraKosuu,paraPtr);
	}
}

void CGameCallBack::ReceiveUserFunction0(int cmd, int paraKosuu, int* paraPtr)
{
	BOOL proceed = FALSE;

	if (cmd == m_stopF5Function)
	{
		m_skipF4Mode = FALSE;
		m_skipF5Mode = FALSE;
		m_skipNextCommandFlag = FALSE;
		m_skipEffectCommandFlag = FALSE;
		m_skipToFilmEndFlag = FALSE;

		proceed = TRUE;
	}

	if (cmd == m_saveSystemFileFunction)
	{
		SaveSystemFile();
		proceed = TRUE;
	}

	if (cmd == m_layerOnOffFunction)
	{
		proceed = TRUE;
		if (paraKosuu>0)
		{
			int layer = *paraPtr;
			int onoff = 1;
			if (paraKosuu>1)
			{
				onoff = *(paraPtr+1);
			}

			m_effect->SetEye(layer,onoff);
			
			int bt = 1 << layer;
			if (onoff == 0)
			{
				m_layerOff |= bt;
			}
			else
			{
				m_layerOff &= ~bt;
			}
		}
	}

	if (cmd == m_noticeFunction)
	{
		proceed = TRUE;
		if (paraKosuu>0)
		{
			int notice = *paraPtr;
			if (m_noticeFlag)
			{
				if (m_notice != NULL)
				{
					m_notice->Start(notice - 1);
				}
			}
		}
	}

	if (cmd == m_setresultFunction)
	{
		proceed = TRUE;
		if (paraKosuu > 0)
		{
			int result = *paraPtr;
			if (m_resultFlag)
			{
				if (m_commonResultData != NULL)
				{
					int st = 1;
					if (paraKosuu>1)
					{
						st = *(paraPtr+1);
					}

					if (m_commonResultData->GetData(result) == 0)
					{
						m_commonResultData->SetData(result,st);
						if (m_autoResultNotice > 0)
						{
							if (m_noticeFlag)
							{
								if (m_notice != NULL)
								{
									m_notice->Start(result - 1 + m_autoResultNotice - 1);
								}
							}
						}
					}
				}
			}
		}
	}


	if (cmd == m_getresultFunction)
	{
		proceed = TRUE;
		if (paraKosuu > 0)
		{
			int result = *paraPtr;
			if (m_resultFlag)
			{
				if (m_commonResultData != NULL)
				{
					int limit = 1;
					if (paraKosuu > 1)
					{
						limit = *(paraPtr+1);
					}

					int dt = m_commonResultData->GetData(result);
					int d = 0;

					if (dt >= limit)
					{
						d = 1;
					}

					if (m_getResultVarNumber != -1)
					{
						SetVarData(m_getResultVarNumber,d);
					}
				}
			}
		}
	}


	//autofunction
	if (proceed == FALSE)
	{
		for (int i=0;i<m_autoFunctionKosuu;i++)
		{
			if (cmd == m_autoFunctionNumber[i])
			{
				int classNumber = m_autoFunctionClass[i];
				if (classNumber > 0)
				{
					CCommonGeneral* general = m_general[classNumber];
					if (general != NULL)
					{
						general->Function(m_autoFunctionParam[i],paraKosuu,paraPtr);
						proceed = TRUE;
					}
				}
			}
		}
	}



	if (proceed == FALSE)
	{
		ReceiveUserFunction(cmd,paraKosuu,paraPtr);
	}
}



/*
int CGameCallBack::GetGameSystemData(LPSTR name)
{
	return -1;
}

LPSTR CGameCallBack::GetGameSystemString(LPSTR name)
{
	return NULL;
}
*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
BOOL CGameCallBack::CheckCD(void)	//簡易チェックCD 外部呼出し用
{
	return m_cdControl->CheckCD();
}
*/



/*
void CGameCallBack::EndCD(void)
{
	int n = m_bgmNumber;
	int k = m_bgmKaisuu;

	StopBGM();
	if (n != -1) PlayBGM2(n,k);
}
*/


void CGameCallBack::SetCommonBackMode(int mode ,int backMode)
{
	CCommonGeneral* general = m_general[mode];
	if (general == NULL) return;

	general->SetBackMode(backMode);

	//特殊処理?
	switch (mode)
	{
	case CONFIG_MODE:
	case LOAD_MODE:
		break;
	}
}
/*
void CGameCallBack::PlayCommonBgm(int commonBgmNumber, BOOL mustRestartFlag)
{
	if (mustRestartFlag)
	{
		//PlayBGM(-1);
	}



	//table change
	int bgm = commonBgmNumber;

	//PlayBGM(bgm);
}
*/


void CGameCallBack::SetupNameDefault(void)
{
	m_nameIsSpecialVoiceFlag = -1;

	if (m_resetNameByStartTitle)
	{
		LPSTR sei = GetGameDefaultSei();
		LPSTR mei = GetGameDefaultMei();

		if (sei != NULL)
		{
			memcpy(CMyMessage::m_sei,sei,strlen(sei)+1);
		}

		if (mei != NULL)
		{
			memcpy(CMyMessage::m_mei,mei,strlen(mei)+1);
		}
	}
}


BOOL CGameCallBack::CheckClickKey(int keyNumber)
{
	if (keyNumber == MYLEFT_KEY)		{if (m_keyStatus->CheckKey(VK_LEFT,TRUE)) return TRUE;}
	if (keyNumber == MYRIGHT_KEY)		{if (m_keyStatus->CheckKey(VK_RIGHT,TRUE)) return TRUE;}
	if (keyNumber == MYUP_KEY)			{if (m_keyStatus->CheckKey(VK_UP,TRUE)) return TRUE;}
	if (keyNumber == MYDOWN_KEY)		{if (m_keyStatus->CheckKey(VK_DOWN,TRUE)) return TRUE;}
	if (keyNumber == MYNEXT_KEY)		{if (m_keyStatus->CheckKey(VK_NEXT,TRUE)) return TRUE;}
	if (keyNumber == MYBACK_KEY)		{if (m_keyStatus->CheckKey(VK_PRIOR,TRUE)) return TRUE;}
	if (keyNumber == WINDOWOFF_KEY)		{if (m_keyStatus->CheckKey(VK_SPACE,TRUE)) return TRUE;}
	if (keyNumber == MESSAGEOKURI_KEY)	{if (m_keyStatus->CheckKey(VK_RETURN,TRUE)) return TRUE;}

	return m_keyStatus->CheckKey(keyNumber,TRUE);
}



void CGameCallBack::SetSceneMode(BOOL md)
{
	CCommonPrintMessage* pObj = (CCommonPrintMessage*)m_general[PRINTMESSAGE_MODE];
	pObj->SetSceneMode(md);

	m_sceneMode = md;
}

/*
void CGameCallBack::SetChangeScreenEvent(HANDLE* lpHandle)
{
	for (int i=0;i<4;i++)
	{
		m_changeScreenEvent[i] = lpHandle[i];
	}
}
*/


void CGameCallBack::BeforeByConfig(void)
{
#if defined _TINYAN3DLIB_
	if (m_myDirect3D != NULL)
	{
		CMyDirect3D* d3d = (CMyDirect3D*)m_myDirect3D;
		d3d->EndScene();
	}
#else
	BeforeChangeScreenByConfig();
#endif
}

void CGameCallBack::AfterByConfig(void)
{
#if defined _TINYAN3DLIB_
	if (m_myDirect3D != NULL)
	{
		CMyDirect3D* d3d = (CMyDirect3D*)m_myDirect3D;
		d3d->BeginScene();
	}
#else
	AfterChangeScreenByConfig();
#endif
}



void CGameCallBack::ToWindowScreen(BOOL directFlag)
{
	if (GetSystemParam(NNNPARAM_SCREENMODE) == 0) return;
	SetSystemParam(NNNPARAM_SCREENMODE,0);



	if (directFlag == FALSE) BeforeByConfig();

	BeforeChangeScreen();


	int md = GetGameMode();
	if (md == PRINTMOVIE_MODE)
	{
		if (m_directShow != NULL)
		{
			m_directShow->Pause();
		}
	}


	ToWindowScreenRoutine();


	if (m_directShow != NULL)
	{
//		m_directShow->OnDisplayChanged();
	}

	if (md == PRINTMOVIE_MODE)
	{
		if (m_directShow != NULL)
		{
			m_directShow->Resume();
		}
	}

	if (md == CONFIG_MODE)
	{
		CCommonConfig* config = (CCommonConfig*)(m_general[CONFIG_MODE]);
		if (config != NULL) config->ReloadScreenButton();
	}

#if defined _TINYAN3DLIB_
	m_font->ClearCache();
	m_font->ReCreateDIB();
#endif

	AfterChangeScreen();


//	SetWindowLong(m_hWnd,GWL_EXSTYLE,GetWindowLong(m_hWnd,GWL_EXSTYLE) & ~WS_EX_TOPMOST);
//if (GetWindowLong(m_hWnd,GWL_EXSTYLE) & WS_EX_TOPMOST)
//{
//	PlaySystemSound(1);
//	Sleep(1);
//	PlaySystemSound(1);
//
//}



	if (directFlag == FALSE) AfterByConfig();


	CAreaControl::ToWindowScreen();
	CAreaControl::SetNextAllPrint();

	m_wheelWaitCount = 2;
}


void CGameCallBack::ToWindowScreenRoutine(void)
{
	m_displaySettingChanged = TRUE;

LogMessage("ToWindowScreen Start");

	ENDDELETECLASS(m_directDraw);
	Sleep(100);

#if defined _TINYAN3DLIB_
	CTextureCacheControl::ReleaseAllTexture();
	((CMyDirect3D*)m_myDirect3D)->ReleaseAllResource();
#endif

//	SetWindowLong(m_hWnd,GWL_EXSTYLE,GetWindowLong(m_hWnd,GWL_EXSTYLE) & ~WS_EX_TOPMOST);

	DEVMODE devMode0;
	ZeroMemory(&devMode0,sizeof(devMode0));
	devMode0.dmSize = sizeof(devMode0);
//	devMode.dmPelsWidth = m_windowSizeX;
//	devMode.dmPelsHeight = m_windowSizeY;
	devMode0.dmFields = DM_BITSPERPEL;
	EnumDisplaySettings(NULL,ENUM_CURRENT_SETTINGS,&devMode0);


	int lp = 5;
	int hr = 0;
	while (lp>0)
	{
		DEVMODE devMode;
		ZeroMemory(&devMode,sizeof(devMode));
		devMode.dmSize = sizeof(devMode);
		devMode.dmPelsWidth = m_deskTopWindowSizeX;
		devMode.dmPelsHeight = m_deskTopWindowSizeY;
		devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
		if (lp==5)
		{
			hr = ChangeDisplaySettings(NULL, 0);
		}
		else
		{
			hr = ChangeDisplaySettings(&devMode, 0);
		}
	//	int hr = ChangeDisplaySettings(&devMode, 0);
		Sleep(50);
		if (hr == DISP_CHANGE_SUCCESSFUL)
		{
			break;
		}
		lp--;
	}


	if (hr != DISP_CHANGE_SUCCESSFUL)
	{
		char mes[1024];
		int nn = 0;
		if (hr == DISP_CHANGE_SUCCESSFUL) nn = 1;
		if (hr == DISP_CHANGE_RESTART) nn = 2;
		if (hr == DISP_CHANGE_BADFLAGS) nn = 3;
		if (hr == DISP_CHANGE_BADPARAM) nn = 4;
		if (hr == DISP_CHANGE_FAILED) nn = 5;
		if (hr == DISP_CHANGE_BADMODE) nn = 6;
		if (hr == DISP_CHANGE_NOTUPDATED) nn = 7;
		wsprintf(mes,"%d:%d",hr,nn);
//		MessageBox(NULL,mes,"fullerrorret",MB_OK);

		int devNum = 0;
		DEVMODE devMode2;
		ZeroMemory(&devMode2,sizeof(devMode2));
		devMode2.dmSize = sizeof(devMode2);
//		devMode2.dmPelsWidth = m_windowSizeX;
//		devMode2.dmPelsHeight = m_windowSizeY;
		devMode2.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_BITSPERPEL;  
		BOOL cannot = TRUE;



		while (EnumDisplaySettings(NULL,devNum,&devMode2))
		{
			if ((devMode2.dmPelsWidth == m_deskTopWindowSizeX) && (devMode2.dmPelsHeight == m_deskTopWindowSizeY))
			{
				if (devMode2.dmDisplayFrequency > 0)
				{
					if (devMode2.dmBitsPerPel == devMode0.dmBitsPerPel)
					{
						devMode2.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_BITSPERPEL;  
						int hr2 = ChangeDisplaySettings(&devMode2, 0); 
						Sleep(10);

						int nn2 = 0;
						if (hr2 == DISP_CHANGE_SUCCESSFUL) nn2 = 1;
						if (hr2 == DISP_CHANGE_RESTART) nn2 = 2;
						if (hr2 == DISP_CHANGE_BADFLAGS) nn2 = 3;
						if (hr2 == DISP_CHANGE_BADPARAM) nn2 = 4;
						if (hr2 == DISP_CHANGE_FAILED) nn2 = 5;
						if (hr2 == DISP_CHANGE_BADMODE) nn2 = 6;
						if (hr2 == DISP_CHANGE_NOTUPDATED) nn2 = 7;
						wsprintf(mes,"%d:%d f=%d",hr,nn,devMode2.dmDisplayFrequency);
					//	MessageBox(NULL,mes,"fullerrorret",MB_OK);

						if (hr2 == DISP_CHANGE_SUCCESSFUL)
						{
							Sleep(100);
							cannot = FALSE;
							break;
						}
					}
				}
			}

			devNum++;
		}

		if (cannot)
		{
			MessageBox(m_hWnd,"ウィン化処理に失敗しました","Error",MB_ICONEXCLAMATION | MB_OK);
		}
	}



#if defined _TINYAN3DLIB_
	((CMyDirect3D*)m_myDirect3D)->ChangeWindowMode();
	((CMyDirect3D*)m_myDirect3D)->CreateAllResource();
	m_myGraphics->ReCreateAllShader();
	m_effect->ReCreateAllShader();
#endif

//	SetWindowLong(m_hWnd,GWL_STYLE,WS_POPUP | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX);
//	SetWindowLong(m_hWnd,GWL_EXSTYLE,GetWindowLong(m_hWnd,GWL_EXSTYLE) & ~WS_EX_TOPMOST);

	int realWindowSizeX = m_viewControl->GetRealWindowSizeX();
	int realWindowSizeY = m_viewControl->GetRealWindowSizeY();

	m_directDraw = new CMyDirectDraw(m_hWnd,m_hInstance,realWindowSizeX,realWindowSizeY,m_bpp,GetSystemParam(NNNPARAM_SCREENMODE)*0);
//	m_directDraw = new CMyDirectDraw(m_hWnd,m_hInstance,m_windowSizeX,m_windowSizeY,m_bpp,GetSystemParam(NNNPARAM_SCREENMODE)*0);

	m_directDraw->SetGDIFullScreen(FALSE);
LogMessage("ToWindowScreen Mid 1");

	m_mmx->Set565Mode(m_directDraw->Check565Mode());
	m_mmx->SetRGB24Mode(m_directDraw->CheckRGB24Mode());
	m_mmx->SetRGB32Mode(m_directDraw->CheckRGB32Mode());



	
	SIZE sz2 = m_mainControl->GetDesktopWindowSize();
	SetDesktopWindowSize(sz2.cx,sz2.cy);
	POINT pt2 = m_mainControl->GetDesktopWindowStart();
	SetDesktopWindowStart(pt2);
	POINT pt3 = m_mainControl->GetDesktopWindowEnd();
	SetDesktopWindowEnd(pt3);



	SetWindowLong(m_hWnd,GWL_STYLE,WS_POPUP | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX);
	Sleep(20);
LogMessage("ToWindowScreen Mid 2");

	SetWindowLong(m_hWnd,GWL_EXSTYLE,GetWindowLong(m_hWnd,GWL_EXSTYLE) & ~WS_EX_TOPMOST);
	Sleep(20);
LogMessage("ToWindowScreen Mid 3");

//	MoveWindow(m_hWnd,m_windowX, m_windowY, m_windowSizeX + 2*GetSystemMetrics(SM_CXFIXEDFRAME),m_windowSizeY + 2*GetSystemMetrics(SM_CYFIXEDFRAME ) + GetSystemMetrics(SM_CYCAPTION),TRUE);
	
//	int wx = m_windowX - GetSystemMetrics(SM_CXFIXEDFRAME);
//	int wy = 
	if (MoveWindow(m_hWnd,m_windowX, m_windowY, realWindowSizeX + 2*GetSystemMetrics(SM_CXFIXEDFRAME),realWindowSizeY + 2*GetSystemMetrics(SM_CYFIXEDFRAME ) + GetSystemMetrics(SM_CYCAPTION),TRUE) == 0)
//	if (MoveWindow(m_hWnd,m_windowX, m_windowY, m_windowSizeX + 2*GetSystemMetrics(SM_CXFIXEDFRAME),m_windowSizeY + 2*GetSystemMetrics(SM_CYFIXEDFRAME ) + GetSystemMetrics(SM_CYCAPTION),TRUE) == 0)
	{
		/*
		DWORD er = GetLastError();
		char emes[1024];
		FormatMessage(

//    FORMAT_MESSAGE_ALLOCATE_BUFFER |

		FORMAT_MESSAGE_FROM_SYSTEM |

		FORMAT_MESSAGE_IGNORE_INSERTS,

		NULL,

		er,

		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // 既定の言語

		(LPTSTR) emes,

		1024,

		NULL
		);


		MessageBox(m_hWnd,emes,"MoveWindowError",MB_OK);
		*/

	}
	Sleep(20);
LogMessage("ToWindowScreen Mid 4");


//	MoveWindow(m_hWnd,m_windowX, m_windowY, m_windowSizeX + 2*GetSystemMetrics(SM_CXFIXEDFRAME),m_windowSizeY + 2*GetSystemMetrics(SM_CYFIXEDFRAME ) + GetSystemMetrics(SM_CYCAPTION),TRUE);

	SetWindowLong(m_hWnd,GWL_EXSTYLE,GetWindowLong(m_hWnd,GWL_EXSTYLE) & ~WS_EX_TOPMOST);
	Sleep(20);
LogMessage("ToWindowScreen Mid 5");

	int windowSizeX = CMyGraphics::GetScreenSizeX();
	int windowSizeY = CMyGraphics::GetScreenSizeY();


//	if (MoveWindow(m_hWnd,m_windowX, m_windowY, m_windowSizeX + 2*GetSystemMetrics(SM_CXFIXEDFRAME),m_windowSizeY + 2*GetSystemMetrics(SM_CYFIXEDFRAME ) + GetSystemMetrics(SM_CYCAPTION),TRUE) == 0)

	SetWindowPos(m_hWnd,HWND_NOTOPMOST,m_windowX,m_windowY,realWindowSizeX + 2*GetSystemMetrics(SM_CXFIXEDFRAME),realWindowSizeY + 2*GetSystemMetrics(SM_CYFIXEDFRAME ) + GetSystemMetrics(SM_CYCAPTION),0);
//	SetWindowPos(m_hWnd,HWND_NOTOPMOST,0,0,windowSizeX,windowSizeY,SWP_NOMOVE | SWP_NOSIZE);

	Sleep(20);
	LogMessage("ToWindowScreen Mid 6");


	m_directDraw->SetWindowSize(m_deskTopWindowSizeX,m_deskTopWindowSizeY);
	m_directDraw->WindowIsMoved(m_windowX, m_windowY);
	LogMessage("ToWindowScreen End");

	m_screenModeChangedFlag = TRUE;
}



void CGameCallBack::ToFullScreen(BOOL directFlag)
{
//directFlag = TRUE;
	if (GetSystemParam(NNNPARAM_SCREENMODE) != 0) return;
	SetSystemParam(NNNPARAM_SCREENMODE,1);
	if (directFlag == FALSE) BeforeByConfig();

	BeforeChangeScreen();

	int md = GetGameMode();
	if (md == PRINTMOVIE_MODE)
	{
		if (m_directShow != NULL)
		{
			m_directShow->Pause();
			Sleep(50);
		}
	}

	ToFullScreenRoutine();

	if (md == PRINTMOVIE_MODE)
	{
		if (m_directShow != NULL)
		{
			m_directShow->Resume();
		}
	}

	if (md == CONFIG_MODE)
	{
		CCommonConfig* config = (CCommonConfig*)(m_general[CONFIG_MODE]);
		if (config != NULL) config->ReloadScreenButton();
	}

#if defined _TINYAN3DLIB_
	m_font->ClearCache();
	m_font->ReCreateDIB();
#endif

	AfterChangeScreen();

	if (directFlag == FALSE) AfterByConfig();

	CAreaControl::SetNextAllPrint();
	CAreaControl::ToFullScreen();

	m_wheelWaitCount = 2;
}


void CGameCallBack::ToFullScreenRoutine(void)
{
	m_displaySettingChanged = TRUE;

	int realWindowSizeX = m_viewControl->GetRealWindowSizeX();
	int realWindowSizeY = m_viewControl->GetRealWindowSizeY();

	ENDDELETECLASS(m_directDraw);
	Sleep(100);

#if defined _TINYAN3DLIB_
	CTextureCacheControl::ReleaseAllTexture();
	((CMyDirect3D*)m_myDirect3D)->ReleaseAllResource();
#endif

	DEVMODE devMode0;
	ZeroMemory(&devMode0,sizeof(devMode0));
	devMode0.dmSize = sizeof(devMode0);
//	devMode.dmPelsWidth = m_windowSizeX;
//	devMode.dmPelsHeight = m_windowSizeY;
	devMode0.dmFields = DM_BITSPERPEL;
	EnumDisplaySettings(NULL,ENUM_CURRENT_SETTINGS,&devMode0);


	DEVMODE devMode;
	ZeroMemory(&devMode,sizeof(devMode));
	devMode.dmSize = sizeof(devMode);
//	devMode.dmPelsWidth = m_windowSizeX;
//	devMode.dmPelsHeight = m_windowSizeY;
	devMode.dmPelsWidth = realWindowSizeX;
	devMode.dmPelsHeight = realWindowSizeY;
	devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT; 

	//test 20130822
//	devMode.dmBitsPerPel = devMode0.dmBitsPerPel;
//	devMode.dmFields |= DM_BITSPERPEL;

	int hr = ChangeDisplaySettings(&devMode, CDS_FULLSCREEN); 
	Sleep(100);
//	int hr = DISP_CHANGE_BADMODE;

	if (hr != DISP_CHANGE_SUCCESSFUL)
	{
		char mes[1024];
		mes[0] = 0;
		int nn = 0;
		if (hr == DISP_CHANGE_SUCCESSFUL) nn = 1;
		if (hr == DISP_CHANGE_RESTART) nn = 2;
		if (hr == DISP_CHANGE_BADFLAGS) nn = 3;
		if (hr == DISP_CHANGE_BADPARAM) nn = 4;
		if (hr == DISP_CHANGE_FAILED) nn = 5;
		if (hr == DISP_CHANGE_BADMODE) nn = 6;
		if (hr == DISP_CHANGE_NOTUPDATED) nn = 7;
		wsprintf(mes,"%d:%d",hr,nn);
		//fordebug@@@@@@@@@@@@@@@@@
		//MessageBox(NULL,mes,"fullerrorret",MB_OK);

		int devNum = 0;
		DEVMODE devMode2;
		ZeroMemory(&devMode2,sizeof(devMode2));
		devMode2.dmSize = sizeof(devMode2);
//		devMode2.dmPelsWidth = m_windowSizeX;
//		devMode2.dmPelsHeight = m_windowSizeY;
		devMode2.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_BITSPERPEL;  
		BOOL cannot = TRUE;


		BOOL modeFound = FALSE;

		while (EnumDisplaySettings(NULL,devNum,&devMode2))
		{
			if ((devMode2.dmPelsWidth == realWindowSizeX) && (devMode2.dmPelsHeight == realWindowSizeY))
//			if ((devMode2.dmPelsWidth == m_windowSizeX) && (devMode2.dmPelsHeight == m_windowSizeY))
			{
				if (devMode2.dmDisplayFrequency > 0)
				{
					if (devMode2.dmBitsPerPel == devMode0.dmBitsPerPel)
					{
						modeFound = TRUE;

						devMode2.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_BITSPERPEL;  
						int hr2 = ChangeDisplaySettings(&devMode2, CDS_FULLSCREEN); 
						Sleep(10);

						int nn2 = 0;
						if (hr2 == DISP_CHANGE_SUCCESSFUL) nn2 = 1;
						if (hr2 == DISP_CHANGE_RESTART) nn2 = 2;
						if (hr2 == DISP_CHANGE_BADFLAGS) nn2 = 3;
						if (hr2 == DISP_CHANGE_BADPARAM) nn2 = 4;
						if (hr2 == DISP_CHANGE_FAILED) nn2 = 5;
						if (hr2 == DISP_CHANGE_BADMODE) nn2 = 6;
						if (hr2 == DISP_CHANGE_NOTUPDATED) nn2 = 7;
						wsprintf(mes,"HR=%d エラー=%d 周波数=%dHz",hr,nn,devMode2.dmDisplayFrequency);
						//for debug@@@@@@@@
//						MessageBox(NULL,mes,"fullerrorret2",MB_OK);

						if (hr2 == DISP_CHANGE_SUCCESSFUL)
						{
							Sleep(100);
							cannot = FALSE;
							break;
						}
//						MessageBox(NULL,mes,"fullerrorret2",MB_OK);
					}
				}
			}

			devNum++;
		}

		if (cannot)
		{
			if (modeFound)
			{
				MessageBox(m_hWnd,"フルスクリーン処理に失敗しました","Error",MB_ICONEXCLAMATION | MB_OK);
			}
			else
			{
				MessageBox(m_hWnd,"このマシンではこの解像度はサポートされていません","Error",MB_ICONEXCLAMATION | MB_OK);
			}
		}
	}



#if defined _TINYAN3DLIB_
	((CMyDirect3D*)m_myDirect3D)->ChangeWindowMode(TRUE);
	((CMyDirect3D*)m_myDirect3D)->CreateAllResource();
	if (m_myGraphics != NULL) m_myGraphics->ReCreateAllShader();
	if (m_effect != NULL) m_effect->ReCreateAllShader();
#endif


	m_directDraw = new CMyDirectDraw(m_hWnd,m_hInstance,realWindowSizeX,realWindowSizeY,m_bpp,GetSystemParam(NNNPARAM_SCREENMODE) * 0);
//	m_directDraw = new CMyDirectDraw(m_hWnd,m_hInstance,m_windowSizeX,m_windowSizeY,m_bpp,GetSystemParam(NNNPARAM_SCREENMODE) * 0);


	m_directDraw->SetGDIFullScreen(TRUE);


	SIZE sz2 = m_mainControl->GetDesktopWindowSize();
	SetDesktopWindowSize(sz2.cx,sz2.cy);
	POINT pt2 = m_mainControl->GetDesktopWindowStart();
	SetDesktopWindowStart(pt2);
	POINT pt3 = m_mainControl->GetDesktopWindowEnd();
	SetDesktopWindowEnd(pt3);

	m_mmx->Set565Mode(m_directDraw->Check565Mode());
	m_mmx->SetRGB24Mode(m_directDraw->CheckRGB24Mode());
	m_mmx->SetRGB32Mode(m_directDraw->CheckRGB32Mode());


	SetWindowLong(m_hWnd,GWL_STYLE,WS_POPUP | WS_VISIBLE);
//	SetWindowLong(m_hWnd,GWL_EXSTYLE,GetWindowLong(m_hWnd,GWL_EXSTYLE) | WS_EX_TOPMOST);
	MoveWindow(m_hWnd,0,0, realWindowSizeX,realWindowSizeY,TRUE);
//	MoveWindow(m_hWnd,0,0, m_windowSizeX,m_windowSizeY,TRUE);

	m_directDraw->SetWindowSize(realWindowSizeX,realWindowSizeY);
//	m_directDraw->SetWindowSize(m_windowSizeX,m_windowSizeY);
	m_directDraw->WindowIsMoved(0,0);





	m_screenModeChangedFlag = TRUE;
}



BOOL CGameCallBack::CheckMessageSkipMode(void)
{
	if (m_systemFile->m_systemdata.skipMode != 0) return TRUE;
	return FALSE;
}

void CGameCallBack::CalcuEffectOnly(void)
{
	m_effect->CalcuOnly();
}

void CGameCallBack::CountUpOnly(int n)
{
	m_effect->CountUp(n);
}

void CGameCallBack::SkipToEffectEnd(void)
{
	m_effect->SkipAllEffectCount();
	m_effect->EndEffect();
}


void CGameCallBack::StopVoice(void)
{
//	if (m_wave->CheckDataExist())
//	{
//		m_wave->StopWave();
//	}
}


void CGameCallBack::PrintEffect(BOOL bScreenFlag)
{
	BOOL eyeFlag = FALSE;

	if (CheckBackScriptMode() == FALSE)
	{
		eyeFlag = TRUE;
	}

	if (bScreenFlag == FALSE)
	{
		m_effect->CheckNeedAllPrint();
	}
	if (CAreaControl::CheckAllPrintMode()) m_effect->Print(bScreenFlag,eyeFlag);
	if (bScreenFlag == TRUE)
	{
		m_effect->EndEffect();
	}
}

void CGameCallBack::PrintEffectLayer(int startLayer,int endLayer)
{
	m_effect->PrintLayers(startLayer,endLayer);

	if (endLayer == 15)
	{
		m_effect->EndEffect();
	}
}



void CGameCallBack::ChangePreColor(int n, int colR, int colG, int colB)
{
	CCommonBackLog* obj = (CCommonBackLog*)m_general[BACKLOG_MODE];
	if (obj == NULL) return;

	obj->ChangePreColor(n,colR,colG,colB);
}


CPicture* CGameCallBack::GetOverrapPic(int n)
{
	if (n == 0) return m_overrapPic1;

	return m_overrapPic2;
}

BOOL CGameCallBack::CheckVoiceFlag(int n)
{
	int bitPattern = 1;
	if (n>=32)
	{
		bitPattern <<= (n/32);
	}

	int k= n & 0x1f;

	if ((m_systemFile->m_systemdata.voiceOff[k] & bitPattern) == 0) return TRUE;

//	if (m_systemFile->m_systemdata.voiceOff[n % 32] == 0) return TRUE;
	return FALSE;
}

BOOL CGameCallBack::CheckVoiceUsedFlag(int voiceCharaNumber)
{
	return m_systemFile->CheckVoice(voiceCharaNumber);
}

void CGameCallBack::SetVoiceFlag(int n, BOOL flg)
{
	int d = 0;
	if (flg == FALSE) d = 1;

	int bitPattern = 1;
	if (n>=32)
	{
		bitPattern <<= (n/32);
	}

	int k= n & 0x1f;

	if (d)
	{
		m_systemFile->m_systemdata.voiceOff[k] |= bitPattern;
	}
	else
	{
		m_systemFile->m_systemdata.voiceOff[k] &= ~bitPattern;
	}


//	m_systemFile->m_systemdata.voiceOff[n] = d;
}


void CGameCallBack::PrintOverrap(int count)
{
	m_effect->PrintSimpleWipe(m_overrapType,m_overrapPic1,m_overrapPic2,count,m_overrapLength);
}

void CGameCallBack::PrintSimpleWipe(int count, int countMax, int type)
{
	m_effect->PrintSimpleWipe(type,m_overrapPic1,m_overrapPic2,count,countMax);
}

void CGameCallBack::PrintSimpleWipe(CPicture* lpFromPic,CPicture* lpToPic,int count, int countMax, int type)
{
	m_effect->PrintSimpleWipe(type,lpFromPic,lpToPic,count,countMax);
}

BOOL CGameCallBack::CheckDemoMode(void)
{
	//当面つねにFALSEになる予定
	return CCommonGameVersion::m_demoVersion;
}



void CGameCallBack::AddBackLogMessage(LPSTR mes,int colR, int colG, int colB)
{
	CCommonBackLog* obj = (CCommonBackLog*)m_general[BACKLOG_MODE];
	if (obj == NULL) return;

	obj->AddMessage(mes,colR,colG,colB);
}

void CGameCallBack::AddBacklogSeparator(void)
{
	CCommonBackLog* obj = (CCommonBackLog*)m_general[BACKLOG_MODE];
	if (obj == NULL) return;

	obj->AddSeparator();
}

BOOL CGameCallBack::CheckMessageRead(int mesNum, int sptNum)
{
	if (sptNum == -1) sptNum = m_sptFileNumber[m_scriptRunMode];
	return m_systemFile->CheckMessageRead(sptNum,mesNum);
}

void CGameCallBack::SetMessageRead(int mesNum, int sptNum)
{
	if (sptNum == -1) sptNum = m_sptFileNumber[m_scriptRunMode];
	m_systemFile->SetMessageRead(sptNum,mesNum);
}



BOOL CGameCallBack::CheckNoSkipFrame(void)
{
	if (m_systemFile->m_systemdata.noSkipFrame != 0) return TRUE;

	return FALSE;
}

void CGameCallBack::PrintMessageWindow(BOOL bFlag,BOOL nameWindowPrintFlag,POINT* lpDeltaPoint)
{
	if (CheckDemoMode()) return;

	if (m_messageWindowDontPrintFlag) return;

	if (m_messageWindowPrintFlag)
	{
		m_messageWindow->Print(bFlag,nameWindowPrintFlag,lpDeltaPoint);
	}
}


void CGameCallBack::PrintMessageWindowDirect(BOOL bFlag,BOOL nameWindowPrintFlag,POINT* lpPoint)
{
	m_messageWindow->PrintDirect(bFlag,nameWindowPrintFlag,lpPoint);
}


void CGameCallBack::PrintMessageWindowByCheck(BOOL bFlag,BOOL nameWindowPrintFlag,POINT* lpDeltaPoint)
{
	if (m_messageWindowPrintFlag)
	{
		m_messageWindow->Print(bFlag,nameWindowPrintFlag,lpDeltaPoint);
	}
}

CPicture* CGameCallBack::GetSystemPicture(LPSTR filename,BOOL b256Flag)
{
	if (m_systemPicture == NULL) return NULL;
	return m_systemPicture->GetSystemPicture(filename,b256Flag);
}



void CGameCallBack::SetSystemParam(int para, int dat)
{
	switch (para)
	{
	case NNNPARAM_MUSICVOLUME:
		m_systemFile->m_systemdata.musicVolume = dat;
		m_musicControl->ChangeVolume(dat);
		break;
	case NNNPARAM_SOUNDVOLUME:
		m_systemFile->m_systemdata.soundVolume = dat;
		break;
	case NNNPARAM_VOICEVOLUME:
		m_systemFile->m_systemdata.voiceVolume = dat;
		break;
	case NNNPARAM_MOVIEVOLUME:
		if (m_movieVolumeNotUse == 0)
		{
			m_systemFile->m_systemdata.movieVolume = dat;
		}
		break;
	case NNNPARAM_SOUNDVOICEVOLUME:
		if (m_soundVoiceVolumeNotUse == 0)
		{
			m_systemFile->m_systemdata.soundVoiceVolume = dat;
		}
		break;
	case NNNPARAM_TOTALVOLUME:
		if (m_totalVolumeUseFlag)
		{
			m_systemFile->m_systemdata.totalVolume = dat;
			m_mixer->SetTotalVolume(dat);
		}
		break;
	case NNNPARAM_MUSICSWITCH:
		m_systemFile->m_systemdata.musicSwitch = dat;
		if (dat == 0)
		{
			//stop only
			int m = m_lastMusicNumber;
			StopMusic();
			m_lastMusicNumber = m;
		}
		else
		{
			if (m_lastMusicNumber != -1)
			{
				PlayMusic(m_lastMusicNumber,m_musicKaisuu);
			}
		}
		break;
	case NNNPARAM_SOUNDSWITCH:
		m_systemFile->m_systemdata.soundSwitch = dat;
		break;
	case NNNPARAM_VOICESWITCH:
		m_systemFile->m_systemdata.voiceSwitch = dat;
		break;
	case NNNPARAM_MOVIESWITCH:
		if (m_movieVolumeNotUse == 0)
		{
			m_systemFile->m_systemdata.movieSwitch = dat;
		}
		break;
	case NNNPARAM_SOUNDVOICESWITCH:
		if (m_soundVoiceVolumeNotUse == 0)
		{
			m_systemFile->m_systemdata.soundVoiceSwitch = dat;
		}
		break;
	case NNNPARAM_TOTALSWITCH:
		if (m_totalVolumeUseFlag)
		{
			m_systemFile->m_systemdata.totalVolumeSwitch = dat;
			if (dat == 0)
			{
				//stop only
				int m = m_lastMusicNumber;
				StopMusic();
				m_lastMusicNumber = m;
			}
			else
			{
				if (m_lastMusicNumber != -1)
				{
					PlayMusic(m_lastMusicNumber,m_musicKaisuu);
				}
			}
		}
		break;
	case NNNPARAM_SKIPMODE:
		m_systemFile->m_systemdata.skipMode = dat;
		break;
	case NNNPARAM_MESSAGESPEED:
		m_systemFile->m_systemdata.messageSpeed = dat;
		break;
	case NNNPARAM_WINDOWPERCENT:
		m_systemFile->m_systemdata.windowPercent = dat;
		SetMessageWindowPercent();
		break;
	case NNNPARAM_SCREENMODE:
		m_systemFile->m_systemdata.fullScreenFlag = dat;
		break;
	case NNNPARAM_AUTOMODE:
		m_systemFile->m_systemdata.autoMode = dat;
		break;
	case NNNPARAM_AUTOSPEEDSLIDER:
		m_systemFile->m_systemdata.autoSpeedSlider = dat;
		break;
	case NNNPARAM_AUTOCONTINUESWITCH:
		m_systemFile->m_systemdata.coninueAuto = dat;
		break;
	}

	if ((para >= NNNPARAM_EXPMODE) && (para < NNNPARAM_EXPMODE+m_expButtonKosuu))
	{
		m_systemFile->m_systemdata.expMode[para-NNNPARAM_EXPMODE] = dat;
		
		if (AfterChangeSystemParamExpRadio(para-NNNPARAM_EXPMODE,dat) == FALSE)
		{
			CheckAndSetMouseAndCursor(para,dat);
		}
	}
	if ((para >= NNNPARAM_EXPCHECK) && (para < NNNPARAM_EXPCHECK+m_expCheckButtonKosuu))
	{
		m_systemFile->m_systemdata.expCheck[para-NNNPARAM_EXPCHECK] = dat;
		AfterChangeSystemParamExpCheck(para-NNNPARAM_EXPCHECK,dat);
	}

	if ((para >= NNNPARAM_CHARAVOICEVOLUME) && (para < NNNPARAM_CHARAVOICEVOLUME+12*6))
	{
		m_systemFile->SetCharaVoiceVolumeSlider(para-NNNPARAM_CHARAVOICEVOLUME,dat);
	}
}


int CGameCallBack::GetSystemParam(int para)
{
	switch (para)
	{
	case NNNPARAM_MUSICVOLUME:
		return m_systemFile->m_systemdata.musicVolume;
		break;
	case NNNPARAM_SOUNDVOLUME:
		return m_systemFile->m_systemdata.soundVolume;
		break;
	case NNNPARAM_VOICEVOLUME:
		return m_systemFile->m_systemdata.voiceVolume;
		break;
	case NNNPARAM_MOVIEVOLUME:
		if (m_movieVolumeNotUse == 1)
		{
			return m_systemFile->m_systemdata.musicVolume;
		}
		else if (m_movieVolumeNotUse == 2)
		{
			return m_systemFile->m_systemdata.soundVolume;
		}
		else if (m_movieVolumeNotUse == 3)
		{
			return m_systemFile->m_systemdata.voiceVolume;
		}
		else
		{
			return m_systemFile->m_systemdata.movieVolume;
		}
		break;
	case NNNPARAM_SOUNDVOICEVOLUME:
		if (m_soundVoiceVolumeNotUse == 0)
		{
			return m_systemFile->m_systemdata.soundVoiceVolume;
		}
		else if (m_soundVoiceVolumeNotUse == 1)
		{
			return m_systemFile->m_systemdata.voiceVolume;
		}
		else//2
		{
			return m_systemFile->m_systemdata.soundVolume;
		}

		break;
	case NNNPARAM_TOTALVOLUME:
		return m_systemFile->m_systemdata.totalVolume;
		break;
	case NNNPARAM_MUSICSWITCH:
		return m_systemFile->m_systemdata.musicSwitch;
		break;
	case NNNPARAM_SOUNDSWITCH:
		return m_systemFile->m_systemdata.soundSwitch;
		break;
	case NNNPARAM_VOICESWITCH:
		return m_systemFile->m_systemdata.voiceSwitch;
		break;
	case NNNPARAM_MOVIESWITCH:
		if (m_movieVolumeNotUse == 1)
		{
			return m_systemFile->m_systemdata.musicSwitch;
		}
		else if (m_movieVolumeNotUse == 2)
		{
			return m_systemFile->m_systemdata.soundSwitch;
		}
		else if (m_movieVolumeNotUse == 3)
		{
			return m_systemFile->m_systemdata.voiceSwitch;
		}
		else
		{
			return m_systemFile->m_systemdata.movieSwitch;
		}
		break;
	case NNNPARAM_SOUNDVOICESWITCH:
		if (m_soundVoiceVolumeNotUse == 0)
		{
			return m_systemFile->m_systemdata.soundVoiceSwitch;
		}
		else
		{
			return m_systemFile->m_systemdata.voiceSwitch;
		}
		break;
	case NNNPARAM_TOTALSWITCH:
		return m_systemFile->m_systemdata.totalVolumeSwitch;
		break;
	case NNNPARAM_SKIPMODE:
		return m_systemFile->m_systemdata.skipMode;
		break;
	case NNNPARAM_MESSAGESPEED:
		return m_systemFile->m_systemdata.messageSpeed;
		break;
	case NNNPARAM_WINDOWPERCENT:
		return m_systemFile->m_systemdata.windowPercent;
		break;
	case NNNPARAM_SCREENMODE:
		return m_systemFile->m_systemdata.fullScreenFlag;
		break;
	case NNNPARAM_AUTOMODE:
		return m_systemFile->m_systemdata.autoMode;
		break;
	case NNNPARAM_AUTOSPEEDSLIDER:
		return m_systemFile->m_systemdata.autoSpeedSlider;
		break;
	case NNNPARAM_AUTOCONTINUESWITCH:
		return m_systemFile->m_systemdata.coninueAuto;
		break;
	}

	if ((para >= NNNPARAM_EXPMODE) && (para < NNNPARAM_EXPMODE+m_expButtonKosuu))
	{
		return m_systemFile->m_systemdata.expMode[para-NNNPARAM_EXPMODE];
	}

	if ((para >= NNNPARAM_EXPCHECK) && (para < NNNPARAM_EXPCHECK+m_expCheckButtonKosuu))
	{
		return m_systemFile->m_systemdata.expCheck[para-NNNPARAM_EXPCHECK];
	}
	if ((para >= NNNPARAM_CHARAVOICEVOLUME) && (para < NNNPARAM_CHARAVOICEVOLUME+12*6))
	{
		return m_systemFile->GetCharaVoiceVolumeSlider(para-NNNPARAM_CHARAVOICEVOLUME);
	}

	return 0;
}



void CGameCallBack::PostCloseMessage(void)
{
	PostMessage(m_hWnd,WM_CLOSE,0,0);
}



void CGameCallBack::StopReplayVoice(int fadeTime)
{
	if (CheckTotalVolumeOff()) return;

	if (GetSystemParam(NNNPARAM_VOICESWITCH) == 0) return;

	m_scriptVoiceControl->Stop(0,FALSE,fadeTime);
}

void CGameCallBack::ReplayVoice(LPSTR filename)
{
	if (CheckTotalVolumeOff()) return;
	if (GetSystemParam(NNNPARAM_VOICESWITCH) == 0) return;
	
	//check voice off
	if (CheckVoiceOffByName(filename)) return;

//OutputDebugString("\nReplayVoice:");
//OutputDebugString(filename);

//	m_scriptVoice[0]->Stop();
	m_scriptVoiceControl->Stop(0);

	BOOL flg = m_waveData->LoadPackedWave(filename);
	if (flg == FALSE)
	{
		flg = m_waveData->LoadWave(filename);
	}

	if (flg)
	{
		int stereo = m_waveData->GetChannel();
		int sampleRate = m_waveData->GetSampleRate();
		int bitRate = m_waveData->GetBitRate();

		char* realPtr = (char*)(m_waveData->GetRealDataPtr());
		int realSize = m_waveData->GetRealDataSize();

//		m_scriptVoice[0]->SetData(realPtr,realSize,stereo,sampleRate,bitRate);
		m_scriptVoiceControl->SetData(0,realPtr,realSize,stereo,sampleRate,bitRate);

		int vol = GetSystemParam(NNNPARAM_VOICEVOLUME);
		vol += GetVoiceVolumeByName(filename);

		if (vol<0) vol = 0;
		if (vol>100) vol = 100;

		m_scriptVoiceControl->SetVolume(0,vol,0);
		m_scriptVoiceControl->Play(0);
//		m_scriptVoice[0]->SetVolume(vol);
//		m_scriptVoice[0]->Play();
	}
}


int CGameCallBack::GetMusicMode(void)
{
	return m_systemFile->m_systemdata.midiMode;	//???
}

void CGameCallBack::SetByLoad(int cd, LPVOID ptr)
{
	switch (cd)
	{
	case GAMEDATATYPE_HEADER:	//nothing to do
		break;
	case GAMEDATATYPE_INFO:	//nothing to do
		SetGameInfoByLoad(ptr);
		break;
	case GAMEDATATYPE_STATUS:
		SetGameStatusByLoad(ptr);
		break;
	case GAMEDATATYPE_MINICG:	//nothing to do
		break;
	case GAMEDATATYPE_VAR:
		SetVarByLoad(ptr);
		break;
//	case GAMEDATATYPE_VAR2:
//		SetVar2ByLoad(ptr);
//		break;
	case GAMEDATATYPE_EFFECT:
		SetEffectByLoad(ptr);
		break;
	case GAMEDATATYPE_EFFECTFILENAME:
		SetEffectFileNameByLoad(ptr);
		break;
	case GAMEDATATYPE_MESSAGE:
		SetMessageByLoad(ptr);
		break;
	case GAMEDATATYPE_CUTIN:
		SetCutinByLoad(ptr);
		break;
	}
}


void CGameCallBack::GetForSave(int cd, LPVOID ptr)
{
	switch (cd)
	{
	case GAMEDATATYPE_HEADER:	//nothing to do
		break;
	case GAMEDATATYPE_INFO:	//nothing to do
//		GetGameInfoForSave(ptr);
		break;
	case GAMEDATATYPE_STATUS:
		GetGameStatusForSave(ptr);
		break;
	case GAMEDATATYPE_MINICG:
		GetMiniCGForSave(ptr);
		break;
	case GAMEDATATYPE_VAR:
		GetVarForSave(ptr);
		break;
//	case GAMEDATATYPE_VAR2:
//		GetVar2ForSave(ptr);
//		break;
	case GAMEDATATYPE_EFFECT:
		GetEffectForSave(ptr);
		break;
	case GAMEDATATYPE_EFFECTFILENAME:
		GetEffectFileNameForSave(ptr);
		break;
	case GAMEDATATYPE_MESSAGE:
		GetMessageForSave(ptr);
		break;
	case GAMEDATATYPE_CUTIN:
		GetCutinForSave(ptr);
		break;
	}
}



void CGameCallBack::SetGameInfoByLoad(LPVOID ptr)
{
	CCommonDataFile::GAMEINFO* lp = (CCommonDataFile::GAMEINFO*)ptr;
	m_dataFileVersion = lp->version;
}

void CGameCallBack::SetGameStatusByLoad(LPVOID ptr)
{
	int i = 0;

	CCommonDataFile::GAMESTATUS* lp = (CCommonDataFile::GAMESTATUS*)ptr;

	//load script
	int sptFileNumber = lp->scriptNumber;
	int sptSubFileNumber = lp->scriptSubNumber;
	int sptSubSubFileNumber = lp->scriptSubSubNumber;

	m_scriptRunMode = lp->scriptRunMode;

	SetLastSelectHeroinNumber(lp->lastselectheroinnumber);

	char filename[256];
	if (m_scriptRunMode >= 1)
	{
		wsprintf(filename,"spt\\%s.spt",m_sptList->GetName(sptFileNumber));
		m_execScript->LoadScript(filename);
		m_sptFileNumber[1] = sptFileNumber;
	}
	

	if (m_scriptRunMode >= 2)
	{
		wsprintf(filename,"spt\\%s.spt",m_sptList->GetName(sptSubFileNumber));
		m_execSubScript->LoadScript(filename);
		m_sptFileNumber[2] = sptSubFileNumber;
	}

	if (m_scriptRunMode >= 3)
	{
		wsprintf(filename,"spt\\%s.spt",m_sptList->GetName(sptSubSubFileNumber));
		m_execSubSubScript->LoadScript(filename);
		m_sptFileNumber[3] = sptSubSubFileNumber;
	}

	m_layerOff = lp->layerOff;
	int bt = 1;
	for (i=0;i<m_layerKosuuMax;i++)
	{
		if (m_layerOff & bt)
		{
			m_effect->SetEye(i,FALSE);
		}
		else
		{
			m_effect->SetEye(i,TRUE);
		}

		bt <<= 1;
	}

	int j = 0;
	for (j=0;j<8;j++)
	{
		for (i=0;i<16;i++)
		{
//			m_loopSoundWork[j*16+i] = lp->loopSound[j*16+i];
			m_scriptSoundControl->SetLoopWork(j,i,lp->loopSound[j*16+i]);
		}
	}

	for (j=0;j<8;j++)
	{
		for (i=0;i<16;i++)
		{
//			m_loopVoiceWork[j*16+i] = lp->loopVoice[j*16+i];
			m_scriptVoiceControl->SetLoopWork(j,i,lp->loopVoice[j*16+i]);
		}
	}

//	for (j=0;j<8;j++)
//	{
		memcpy(m_loopVoiceFileName,lp->loopVoiceFileName,8*64);
//	}

	m_configMask = lp->configMask;
	
//	m_messageWindowPrintFlag = lp->messageWindowPrintFlag;
	m_messageWindowPrintFlag = lp->messageWindowPrintFlag;

	m_messageFontSizeType = lp->messageFontSizeType;


	SetWindowNumberByScript(lp->scriptWindowNumber);
	SetMouseNumberByScript(lp->scriptMouseNumber);
	SetCursorNumberByScript(lp->scriptCursorNumber);

	m_autoMessage = lp->autoMessage;
	m_cannotClick = lp->cannotClick;
	m_cannotSkip = lp->cannotSkip;

	m_renameLayer = lp->renameLayer;

	for (int i=0;i<m_layerKosuuMax;i++)
	{
		m_varControlLayer[i] = lp->varcontrollayer[i];
	}

	m_controlScript->SetPC(lp->m_PC);
	m_controlScript->m_stackPointer = lp->stackPointer;
	for (i=0;i<255;i++)
	{
		m_controlScript->m_stack[i] = lp->callStack[i];
	}

	m_execScript->SetPC(lp->m_PC2);
	m_execScript->m_stackPointer = lp->stackPointer2;
	for (i=0;i<255;i++)
	{
		m_execScript->m_stack[i] = lp->callStack2[i];
	}

	m_execSubScript->SetPC(lp->m_PC3);
	m_execSubScript->m_stackPointer = lp->stackPointer3;
	for (i=0;i<255;i++)
	{
		m_execSubScript->m_stack[i] = lp->callStack3[i];
	}

	m_execSubSubScript->SetPC(lp->m_PC4);
	m_execSubSubScript->m_stackPointer = lp->stackPointer4;
	for (i=0;i<255;i++)
	{
		m_execSubSubScript->m_stack[i] = lp->callStack4[i];
	}

	if (lp->scriptAdjustVersion >= 1)
	{
		m_controlScript->ChangeIDToAddr();

		//checkすべきでは?
		if (m_scriptRunMode >= 1)
		{
			m_execScript->ChangeIDToAddr();
		}

		if (m_scriptRunMode >= 2)
		{
			m_execSubScript->ChangeIDToAddr();
		}

		if (m_scriptRunMode >= 3)
		{
			m_execSubSubScript->ChangeIDToAddr();
		}

		if (m_scriptRunMode >= 1)
		{
			m_controlScript->AdjustScriptCall();
		}

		if (m_scriptRunMode >= 2)
		{
			m_execScript->AdjustScriptCall();
		}

		if (m_scriptRunMode >= 3)
		{
			m_execSubScript->AdjustScriptCall();
		}
	}


	m_messageKosuu = lp->messageKosuu;
	m_selectMessageKosuu = lp->selectMessageKosuu;
	m_selectMessageAddKosuu = lp->selectMessageAddKosuu;

	m_nokori = lp->nokori;

	//clear auto skip
	if (m_clearAutoAfterLoad)
	{
		SetSystemParam(NNNPARAM_AUTOMODE,0);
		SetMessageSkipFlag(FALSE);
	}

	//bgm
//	m_bgmNumber = lp->bgmNumber;
//	m_bgmKaisuu = lp->bgmKaisuu;
	m_musicNumber = lp->bgmNumber;
	m_musicKaisuu = lp->bgmKaisuu;

	int vol = lp->bgmVolume;
	vol -= GetSystemParam(NNNPARAM_MUSICVOLUME);

	if (m_musicNumber == -1)
	{
		StopMusic();
	}
	else
	{
		PlayMusic(m_musicNumber,m_musicKaisuu,vol);
	}


	m_skipToFilmEndEnable = lp->skipFilm;
	if (m_skipToFilmEndEnable)
	{
		InitSkipFilmButton();
	}

	m_lastMessageID = lp->lastMessageID;
	m_lastSelectID = lp->lastSelectID;	
	
	m_gameMode[0] = lp->gameMode;
	SetLastSaveOkGameMode(lp->gameMode);

	CExecScript* lpScript = GetScript();

	if (m_gameMode[0] == PRINTMESSAGE_MODE)
	{
		CCommonPrintMessage* pObj = (CCommonPrintMessage*)m_general[PRINTMESSAGE_MODE];
		int subMode = lp->messageSubMode;
///		pObj->SetMessageSubMode(subMode);
		pObj->SetPrintModeByLoad(subMode);
		pObj->SetMessageKosuu(m_messageKosuu);
		//change pc
//		if (m_dataFileVersion >= 1)	//version up data
		if ((m_gameVersion - m_dataFileVersion) >= 1)	//version up data
		{
			if (m_lastMessageID >= 0)		//for patch asaki
			{
				lpScript->SearchMessageID(m_lastMessageID);
			}
		}
	}
	else if (m_gameMode[0] == SELECTMESSAGE_MODE)
	{
		CCommonSelectMessage* pObj = (CCommonSelectMessage*)m_general[SELECTMESSAGE_MODE];
		pObj->SetMessageKosuu(m_selectMessageKosuu-m_selectMessageAddKosuu,m_selectMessageAddKosuu);


		pObj->SetTimeLimit(lp->selectTimeLimit,lp->autoSelect);
		pObj->SetTimeLimitCount(lp->selectTimeCount);	//↑でcount初期化されてしまうので再設定
		pObj->SetSpecialFlag(lp->specialFlag);

		//change pc
//		if (m_dataFileVersion >= 1)	//version up data
		if ((m_gameVersion - m_dataFileVersion) >= 1)	//version up data
		{
			if (m_lastMessageID >= 0)		//for patch asaki
			{
				lpScript->SearchSelectID(m_lastSelectID);
			}
		}
	}
	else if (m_gameMode[0] != TITLE_MODE)
	{
		//command.txtでの画面でのセーブ
		if (lp->scriptAdjustVersion >= 1)
		{
			lpScript->AdjustCommandCall();
		}
	}

	//names
	LPSTR sei = lp->playerSei;
	int ln1 = (int)strlen(sei);
	memcpy(CMyMessage::m_sei,sei,ln1+1);
	memcpy(m_systemFile->m_systemdata.sei,sei,ln1+1);

	LPSTR mei = lp->playerMei;
	int ln2 = (int)strlen(mei);
	memcpy(CMyMessage::m_mei,mei,ln2+1);
	memcpy(m_systemFile->m_systemdata.mei,mei,ln2+1);


	int frame = lp->frame;
	if (frame > 0)
	{
		SetFrameRate(frame);
	}


}



void CGameCallBack::SetVarByLoad(LPVOID ptr)
{
	CCommonDataFile::GAMEVAR* lp = (CCommonDataFile::GAMEVAR*)ptr;
	int i = 0;
	for (i=0;i<100;i++)
	{
		m_var[i] = lp->var[i];
	}

	for (i=100;i<200;i++)
	{
		m_var[i] = lp->var[i];
	}

	for (i=300;i<1000;i++)
	{
		m_var[i] = lp->var[i];
	}
}

/*
void CGame::SetVar2ByLoad(LPVOID ptr)
{
	CDataFile::GAMEVAR* lp = (CDataFile::GAMEVAR*)ptr;
	for (int i=0;i<256;i++)
	{
		m_var2[i] = lp->var[i];
	}
}
*/

void CGameCallBack::SetEffectByLoad(LPVOID ptr)
{
	CCommonDataFile::GAMEEFFECT* lp = (CCommonDataFile::GAMEEFFECT*)ptr;

	for (int layer = 0;layer<m_layerKosuuMax;layer++)
	{
		EFFECT* lpEffect = (EFFECT*)(m_effect->GetEffectDataPointer(layer));
		*lpEffect = lp->effect[layer];
	}
}

void CGameCallBack::SetEffectFileNameByLoad(LPVOID ptr)
{
	CCommonDataFile::GAMEEFFECTFILENAME* lp = (CCommonDataFile::GAMEEFFECTFILENAME*)ptr;

	for (int layer=0;layer<m_layerKosuuMax;layer++)
	{
		EFFECT* lpEffect = (EFFECT*)(m_effect->GetEffectDataPointer(layer));
		if (lpEffect->flag)
		{
			LPSTR filename = &(lp->filename[layer][0]);
			if ((*filename) != 0)
			{
				CPicture* pic = m_effect->GetPicture(layer);

				if (pic->LoadDWQ(filename) == FALSE)
				{
					MessageBox(NULL,filename,"LOADDWQ ERROR",MB_OK);
				}

//				m_effect->SetLayerScript(layer,layer);
			}
		}
	}
}



void CGameCallBack::SetMessageByLoad(LPVOID ptr)
{
	CCommonDataFile::GAMEMESSAGE* lp = (CCommonDataFile::GAMEMESSAGE*)ptr;

	CCommonSelectMessage* pDoc = (CCommonSelectMessage*)m_general[SELECTMESSAGE_MODE];
	CCommonPrintMessage* pDoc2 = (CCommonPrintMessage*)m_general[PRINTMESSAGE_MODE];

	int i = 0;
	for (i=0;i<64;i++)
	{
		LPSTR src = &(lp->messageData[i][0]);
		LPSTR dst = pDoc->GetMessagePointer(i);
		memcpy(dst,src,256);
	}

	for (i=0;i<64;i++)
	{
		LPSTR src = &(lp->messageData[i][0]);
		LPSTR dst2 = pDoc2->GetMessagePointer(i);
		memcpy(dst2,src,256);
	}
}


void CGameCallBack::SetOmakeClassDataByLoad(LPVOID ptr)
{
	if (m_omakeClassSupport != NULL)
	{
		m_omakeClassSupport->SetOmakeClassDataByLoad(ptr);
	}
}

void CGameCallBack::GetOmakeClassDataForSave(LPVOID ptr)
{
	if (m_omakeClassSupport != NULL)
	{
		m_omakeClassSupport->GetOmakeClassDataForSave(ptr);
	}
}

void CGameCallBack::SetCutinByLoad(LPVOID ptr)
{
	CCommonDataFile::GAMECUTIN* lp = (CCommonDataFile::GAMECUTIN*)ptr;

	CCommonPrintMessage* pDoc = (CCommonPrintMessage*)m_general[PRINTMESSAGE_MODE];
	pDoc->SetCutinByLoad(lp->cutinData);

	m_cutinFlag = lp->cutinData[64*4-1]; 
}

void CGameCallBack::GetCutinForSave(LPVOID ptr)
{
	CCommonDataFile::GAMECUTIN* lp = (CCommonDataFile::GAMECUTIN*)ptr;

	CCommonPrintMessage* pDoc = (CCommonPrintMessage*)m_general[PRINTMESSAGE_MODE];
	pDoc->GetCutinForSave(lp->cutinData);
	lp->cutinData[64*4-1] = m_cutinFlag;
}




void CGameCallBack::GetGameStatusForSave(LPVOID ptr)
{
	int i = 0;
	CCommonDataFile::GAMESTATUS* lp = (CCommonDataFile::GAMESTATUS*)ptr;
	
	lp->layerOff = m_layerOff;
	//lp->m_PC = m_controlScript->GetPC();
	//lp->m_PC2 = m_execScript->GetPC();
	//lp->m_PC3 = m_execSubScript->GetPC();
	lp->m_PC = m_taihiPC;
	lp->m_PC2 = m_taihiPC2;
	lp->m_PC3 = m_taihiPC3;
	lp->m_PC4 = m_taihiPC4;

	lp->configMask = m_configMask;

	lp->scriptRunMode = m_taihiScriptRunMode;

	lp->gameMode = m_saveMode;

	if (m_saveMode == SELECTMESSAGE_MODE)
	{
		CCommonSelectMessage* selObj = (CCommonSelectMessage*)(m_general[SELECTMESSAGE_MODE]);
		lp->autoSelect = selObj->GetAutoSelect();
		lp->selectTimeLimit = selObj->GetTimeLimit();
		lp->selectTimeCount = selObj->GetTimeLimitCount();
		lp->specialFlag = selObj->GetSpecialFlag();
	}

	lp->scriptNumber = m_taihiSptFileNumber[1];
	lp->scriptSubNumber = m_taihiSptFileNumber[2];
	lp->scriptSubSubNumber = m_taihiSptFileNumber[3];

	CCommonSelectMessage* pDoc = (CCommonSelectMessage*)m_general[SELECTMESSAGE_MODE];
	lp->selectMessageKosuu = pDoc->GetMessageKosuu();
	lp->selectMessageAddKosuu = pDoc->GetAddMessageKosuu();

	CCommonPrintMessage* pDoc2 = (CCommonPrintMessage*)m_general[PRINTMESSAGE_MODE];
	lp->messageKosuu = pDoc2->GetMessageKosuu();
	lp->messageSubMode = pDoc2->GetPrintModeForSave();

	lp->messageWindowPrintFlag = m_taihiMessageWindowPrintFlag;
	lp->messageFontSizeType = m_messageFontSizeType;

	lp->scriptWindowNumber = m_scriptWindowNumber;
	lp->scriptCursorNumber = m_scriptCursorNumber;
	lp->scriptMouseNumber = m_scriptMouseNumber;

	lp->autoMessage = m_autoMessage;
	lp->cannotClick = m_cannotClick;
	lp->cannotSkip = m_cannotSkip;
	lp->renameLayer = m_renameLayer;

	for (int i=0;i<m_layerKosuuMax;i++)
	{
		lp->varcontrollayer[i] = m_taihiVarControlLayer[i];
	}


	lp->frame = GetFrameTime();

	lp->lastselectheroinnumber = GetLastSelectHeroinNumber();


	 lp->skipFilm = m_skipToFilmEndEnable;

	//comment
	LPSTR comment = GetSaveComment();
	if (comment != NULL)
	{
		int ln0 = (int)strlen(comment);
		if (ln0>30) ln0 = 30;
		memcpy(lp->minicomment,comment,ln0);
		lp->minicomment[ln0] = 0;
		lp->minicomment[ln0+1] = 0;
	}
	else
	{
		lp->minicomment[0] = 0;
	}

	//large comment
	LPSTR largeComment[4];
	largeComment[0] = lp->largeComment1;
	largeComment[1] = lp->largeComment2;
	largeComment[2] = lp->largeComment3;
	largeComment[3] = lp->largeComment4;

	for (i=0;i<m_saveCommentKosuuMax;i++)
	{
		LPSTR cmt = m_saveComment[i];
		int ln = (int)strlen(cmt);
		if (ln>m_saveCommentLength-2)
		{
			ln = m_saveCommentLength-2;
		}
		memcpy(largeComment[i],cmt,ln+2);
	}



	//names
	LPSTR sei = CMyMessage::m_sei;
	int ln1 = (int)strlen(sei);
	memcpy(lp->playerSei,sei,ln1+1);

	LPSTR mei = CMyMessage::m_mei;
	int ln2 = (int)strlen(mei);
	memcpy(lp->playerMei,mei,ln2+1);




	if (m_specialNumberForSaveSetFlag)
	{
		if (m_specialNumberForSaveVarNumber != -1)
		{
			m_nokori = GetVarData(m_specialNumberForSaveVarNumber);
		}
	}


	lp->lastMessageID = m_lastMessageID;
	lp->lastSelectID = m_lastSelectID;
	lp->nokori = m_nokori;
//	lp->bgmNumber = m_musicNumber;
	lp->bgmNumber = m_lastMusicNumber;
	lp->bgmKaisuu = m_musicKaisuu;
	lp->bgmVolume = m_musicControl->GetVolumeData();


	int j = 0;
	for (j=0;j<8;j++)
	{
		for (int i=0;i<16;i++)
		{
//			lp->loopSound[j*16+i] = m_loopSoundWork[j*16+i];
			lp->loopSound[j*16+i] = m_scriptSoundControl->GetLoopWork(j,i);//m_loopSoundWork[j*16+i];
		}
	}

	for (j=0;j<8;j++)
	{
		for (int i=0;i<16;i++)
		{
//			lp->loopVoice[j*16+i] = m_loopVoiceWork[j*16+i];
			lp->loopVoice[j*16+i] = m_scriptVoiceControl->GetLoopWork(j,i);
		}
	}

	memcpy(lp->loopVoiceFileName,m_loopVoiceFileName,8*64);

	int dayMonth = GetVarData(m_dayMonthVar);

//	lp->gameYear = 2000;
	lp->gameMonth = GetVarData(m_dayMonthVar) / 100;
	lp->gameDay = GetVarData(m_dayMonthVar) % 100;
	lp->gameWeek = GetWeek(dayMonth);

//	lp->calendarFlag = GetVarData(m_calendarVar);

	lp->scriptAdjustVersion = 1;

	if (m_controlScript->GetData(0) < 32)
	{
		lp->scriptAdjustVersion = 0;
	}

	if (lp->scriptAdjustVersion == 0)
	{
		lp->stackPointer = m_taihiStackPointer;
		for (i=0;i<255;i++)
		{
			lp->callStack[i] = m_taihiStack[i];
		}

		lp->stackPointer2 = m_execScript->m_stackPointer;
		for (i=0;i<255;i++)
		{
			lp->callStack2[i] = m_taihiStack2[i];
		}

		lp->stackPointer3 = m_execSubScript->m_stackPointer;
		for (i=0;i<255;i++)
		{
			lp->callStack3[i] = m_taihiStack3[i];
		}

		lp->stackPointer4 = m_execSubScript->m_stackPointer;
		for (i=0;i<255;i++)
		{
			lp->callStack4[i] = m_taihiStack4[i];
		}
	}
	else
	{

	//	lp->stackPointer = m_controlScript->m_stackPointer;
		lp->stackPointer = m_taihiStackPointer;
		for (i=0;i<250;i++)
		{
	//		lp->callStack[i] = m_controlScript->m_stack[i];
	//		lp->callStack[i] = m_taihiStack[i];
			lp->callStack[i] = m_taihiID[i];
		}
		for (i=250;i<255;i++)
		{
			lp->callStack[i] = m_taihiStack[i];
		}

		lp->stackPointer2 = m_execScript->m_stackPointer;
		for (i=0;i<250;i++)
		{
	//		lp->callStack2[i] = m_execScript->m_stack[i];
	//		lp->callStack2[i] = m_taihiStack2[i];
			lp->callStack2[i] = m_taihiID2[i];
		}
		for (i=250;i<255;i++)
		{
			lp->callStack2[i] = m_taihiStack2[i];
		}

		lp->stackPointer3 = m_execSubScript->m_stackPointer;
		for (i=0;i<250;i++)
		{
	//		lp->callStack3[i] = m_execSubScript->m_stack[i];
	//		lp->callStack3[i] = m_taihiStack3[i];
			lp->callStack3[i] = m_taihiID3[i];
		}
		for (i=250;i<255;i++)
		{
			lp->callStack3[i] = m_taihiStack3[i];
		}

		lp->stackPointer4 = m_execSubSubScript->m_stackPointer;
		for (i=0;i<250;i++)
		{
	//		lp->callStack3[i] = m_execSubScript->m_stack[i];
	//		lp->callStack3[i] = m_taihiStack3[i];
			lp->callStack4[i] = m_taihiID4[i];
		}
		for (i=250;i<255;i++)
		{
			lp->callStack4[i] = m_taihiStack4[i];
		}
	}

}


//type 0:80x60 1:132x100 -1:(custom) -2:cgSize
void CGameCallBack::GetMiniCGForSave(LPVOID ptr, int type, int customSizeX, int customSizeY)
{
	if (m_miniCG == NULL) return;

	CCommonDataFile::GAMEMINICG* lp = (CCommonDataFile::GAMEMINICG*)ptr;
	int* dst = lp->cg;

	GetMiniCGData(dst,type,customSizeX,customSizeY);
}


void CGameCallBack::GetVarForSave(LPVOID ptr)
{
	
	CCommonDataFile::GAMEVAR* lp = (CCommonDataFile::GAMEVAR*)ptr;
	for (int i=0;i<1000;i++)
	{
		lp->var[i] = m_var[i];
	}
	
}
/*
void CGame::GetVar2ForSave(LPVOID ptr)
{
	
	CDataFile::GAMEVAR* lp = (CDataFile::GAMEVAR*)ptr;
	for (int i=0;i<256;i++)
	{
		lp->var[i] = m_var2[i];
	}
}
*/

void CGameCallBack::GetEffectForSave(LPVOID ptr)
{
	CCommonDataFile::GAMEEFFECT* lp = (CCommonDataFile::GAMEEFFECT*)ptr;
	for (int layer = 0;layer<m_layerKosuuMax;layer++)
	{
		EFFECT* lpEffect = (EFFECT*)(m_effect->GetTaihiEffectDataPointer(layer));
		lp->effect[layer] = *lpEffect;
	}
}

void CGameCallBack::GetEffectFileNameForSave(LPVOID ptr)
{
	CCommonDataFile::GAMEEFFECTFILENAME* lp = (CCommonDataFile::GAMEEFFECTFILENAME*)ptr;

	for (int layer=0;layer<m_layerKosuuMax;layer++)
	{
		LPSTR dst = &(lp->filename[layer][0]);


//		CPicture* pic = m_effect->GetTaihiPicture(layer);
//		LPSTR src = pic->GetFileName();

	//	LPSTR src = m_effect->GetTaihiEffectFileName(layer);
		LPSTR src = m_taihiFileName[layer];

		int ln = (int)strlen(src);
		if (ln>254) ln = 254;
		memcpy(dst,src,ln);
		*(dst+ln) = 0;
		*(dst+ln+1) = 0;
	}
}

void CGameCallBack::GetMessageForSave(LPVOID ptr)
{
	CCommonDataFile::GAMEMESSAGE* lp = (CCommonDataFile::GAMEMESSAGE*)ptr;

	if (m_saveMode == SELECTMESSAGE_MODE)
	{
		CCommonSelectMessage* pDoc = (CCommonSelectMessage*)m_general[SELECTMESSAGE_MODE];

		int kosuu = pDoc->GetMessageKosuu();
		if (kosuu>64) kosuu = 64;

		for (int i=0;i<kosuu;i++)
		{
			LPSTR src = pDoc->GetMessagePointer(i);
			int ln = (int)strlen(src);
			if (ln>254) ln = 254;
			memcpy(&(lp->messageData[i][0]),src,ln);
			lp->messageData[i][ln] = 0;
			lp->messageData[i][ln+1] = 0;
		}
	}
	else
	{
		CCommonPrintMessage* pDoc = (CCommonPrintMessage*)m_general[PRINTMESSAGE_MODE];
		int kosuu = pDoc->GetMessageKosuu();
		if (kosuu>64) kosuu = 64;
		for (int i=0;i<kosuu;i++)
		{
			LPSTR src = pDoc->GetMessagePointer(i);
			int ln = (int)strlen(src);
			if (ln>254) ln = 254;
			memcpy(&(lp->messageData[i][0]),src,ln);
			lp->messageData[i][ln] = 0;
			lp->messageData[i][ln+1] = 0;
		}
	}

}



int CGameCallBack::GetWeek(int dayMonth)
{
	//calcu week

	int month = dayMonth / 100;
	int day = dayMonth % 100;

/*
  [(y+[y/4]-[y/100]+[y/400]+[2.6m+1.6]+d)/7]                            (4)

この値が0なら日曜、1なら月曜、、、といった具合いになる。ただしこの場合も 1、2月は前年の13、14月となる。 
  if(month == 1 || month == 2 ){
    year--;
    month += 12;
  }
  (y+y/4-y/100+y/400+(13*m+8)/5+d)%7

ここでは丸め誤差を防ぐため小数ではなく分数形式で計算している
*/

	int year = 2000;
	if (m_yearVar != -1)
	{
		year = GetVarData(m_yearVar);
	}

	int month2 = month;
	int year2 = year;

	if (month2 <= 2)
	{
		year2 -= 1;
		month2 += 12;
	}

	int week = (year2 + year2/4 - year2/100 + year2/400 + (13*month2+8)/5 + day);
	week %= 7;

	return week;
}


void CGameCallBack::PlaySystemPiano(int n)
{
	int oc = n / 7;
	int d = n % 7;
	d += 2;
	d %= 7;
	char filename[64];
	wsprintf(filename,"o%d_",oc+4);
	filename[2] = 'a' + d;
	PlaySystemWaveFilename(filename);
}


void CGameCallBack::PlayCommonSystemSound(int commonSoundNumber)
{
	if (commonSoundNumber == COMMON_SYSTEMSOUND_PAGE) commonSoundNumber = COMMON_SYSTEMSOUND_PON;
	PlaySystemSound(commonSoundNumber);
}



void CGameCallBack::MakeMiniCG(void)
{
	Erase();
	//make
#if defined _TINYAN3DLIB_
	//screen to buffer

	CMyDirect3D::GetScreenToMemory((int*)(CMyGraphics::GetScreenBuffer()));



#endif

	m_gameUtil->MakeMiniCG((int*)(CMyGraphics::GetScreenBuffer()),m_miniCG);


	if (m_useHsavemask)
	{
		//check
		int found = -1;
		int kosuu = m_hSaveList->GetNameKosuu();
		for (int n=1;n<kosuu/2;n++)
		{
			LPSTR name = m_hSaveList->GetName(n*2);
			char checkName[1024];
			memcpy(&checkName[3],name,strlen(name)+1);
			checkName[0] = *name;
			checkName[1] = *(name+1);
			checkName[2] = '\\';

			for (int layer = 0;layer<16;layer++)
			{
				//if exist pic
				LPSTR effectFilename = m_effect->GetExistEffectFileName(layer);
				if (effectFilename != NULL)
				{
					if (_stricmp(effectFilename,checkName) == 0)
					{
						found = n;
						break;
					}
				}
			}
			if (found != -1) break;
		}


		if (found != -1)
		{
			char filename[1024];
			wsprintf(filename,"sys\\%s",m_hSaveList->GetName(found*2+1));
			m_hSaveMaskPic->LoadDWQ(filename);
			m_gameUtil->AddMaskToMiniPic(m_miniCG,m_hSaveMaskPic);
		}
	}



//	m_gameUtil->MakeMiniCG132x100((int*)(CMyGraphics::GetScreenBuffer()),m_miniCG);


}

void CGameCallBack::SearchCase(int caseNumber)
{
	CExecScript* lpScript = GetScript();

	int pc = lpScript->GetCase(-1,caseNumber);
	if (pc != -1)
	{
		lpScript->SetPC(pc);
	}
}

CExecScript* CGameCallBack::GetScript(void)
{
	CExecScript* lpScript = m_execScript;
	if (m_scriptRunMode == 0) lpScript = m_controlScript;
	if (m_scriptRunMode == 2) lpScript = m_execSubScript;
	if (m_scriptRunMode == 3) lpScript = m_execSubSubScript;

	return lpScript;
}

void CGameCallBack::InitOpeningMode(int para1, int para2)
{
	int i = 0;
	for (i=300;i<1000;i++)
	{
		m_var[i] = 0;
	}

	for (i=100;i<200;i++)
	{
		m_var[i] = 0;
	}

	SetOpeningMode();
	if (para1 != -1)
	{
		SetVarData(para1,para2);
	}

	m_messageWindowPrintFlag = FALSE;

//	SetUraMode(uraMode);
//	SetDemoMode(demoFlag);

	//SetCalendarFlag(FALSE);
	SetOption(FALSE);
	SetSceneButton(FALSE);

	m_effect->ClearAllEffect();

	m_skipNextCommandFlag = FALSE;
	m_skipEffectCommandFlag = FALSE;
	m_skipToFilmEndFlag = FALSE;

	m_sceneMode = FALSE;

	AfterInitNewGame();
	for (int i=1;i<100;i++)
	{
		CCommonGeneral* gn = (CCommonGeneral*)(m_general[i]);
		if (gn != NULL)
		{
			gn->AfterInitNewGame();
		}
	}


	if (m_controlScript != NULL)
	{
		m_controlScript->SetPC(0);
		m_controlScript->m_stackPointer = 0;
		if (m_execScript != NULL)
		{
			m_execScript->SetPC(0);
		}
		m_scriptRunMode = 0;
		m_controlScript->Exec();
	}

//	if (demoFlag)
//	{
//		StopBGM();
//		m_midi->Stop();

//		m_wave->StopWave();

//		if (m_wave->LoadPackWave("dm000001",TRUE))
//		{
//			m_wave->PlayWave();
//		}
//	}

//	ResetAllShakin();
	ShakinHensai(-1);
}


int CGameCallBack::InitNewGame(int uraMode, BOOL demoFlag,int setVar,int setData)
{
	int i = 300;
	for (i=300;i<1000;i++)
	{
		m_var[i] = 0;
	}

	for (i=100;i<200;i++)
	{
		m_var[i] = 0;
	}


	if (m_varInitFlag)
	{
		for (i=100;i<200;i++)
		{
			m_var[i] = atoi(m_varInitData->GetName(i));
		}

		for (i=300;i<1000;i++)
		{
			m_var[i] = atoi(m_varInitData->GetName(i));
		}
	}


	if (setVar != -1)
	{
		SetVarData(setVar,setData);
	}

	m_messageWindowPrintFlag = FALSE;
	m_messageFontSizeType = 0;
	m_nameIsSpecialVoiceFlag = -1;

	SetBackScriptMode(FALSE);
	SetDontPlay(0);

	ClearFontCache();

	for (i=0;i<m_layerKosuuMax;i++)
	{
		m_effect->SetEye(i,TRUE);
	}
	m_layerOff = 0;

//	if (uraMode>0) SetUraMode(uraMode);
//	SetUraMode(uraMode);

	m_cutinFlag = 0;
	CCommonPrintMessage* obj = (CCommonPrintMessage*)(m_general[PRINTMESSAGE_MODE]);
	if (obj != NULL)
	{
		obj->SetCutinMode(m_cutinFlag);
	}

	if (m_autoDebugMode)
	{
		if (m_autoSelectControl != NULL)
		{
			m_autoSelectControl->ClearPlayLevel();
		}
	}
	SetDemoMode(demoFlag);

//	m_var[m_sceneModeVar] = 0;

	//SetCalendarFlag(FALSE);
	SetOption(FALSE);
	SetSceneButton(FALSE);

	m_effect->ClearAllEffect();


	m_skipNextCommandFlag = FALSE;
	m_skipEffectCommandFlag = FALSE;
	m_skipToFilmEndFlag = FALSE;
	m_skipToFilmEndEnable = FALSE;

	m_sceneMode = FALSE;

	m_renameLayer = 0;

	for (int i=0;i<m_layerKosuuMax;i++)
	{
		m_varControlLayer[i] = 0;
	}


	AfterInitNewGame();
	for (int i=1;i<100;i++)
	{
		CCommonGeneral* gn = (CCommonGeneral*)(m_general[i]);
		if (gn != NULL)
		{
			gn->AfterInitNewGame();
		}
	}

	int rt = -1;

	if (m_controlScript != NULL)
	{
		m_controlScript->SetPC(0);
		m_controlScript->m_stackPointer = 0;
//		if (m_execScript != NULL)
//		{
//			m_execScript->SetPC(0);
//		}
//		m_scriptRunMode = 0;
//		rt = m_controlScript->Exec();
	}

	m_scriptRunMode = 0;

	if (demoFlag)
	{
		StopMusic();
//		StopBGM();
//		m_midi->Stop();

//@@		m_wave->StopWave();

//		if (m_wave->LoadPackWave("dm000001",TRUE))
//		{
//			m_wave->PlayWave();
//		}
	}

	//ResetAllShakin();
	ShakinHensai(-1);

	int returnCode = -1;

//	if (rt == -1)
//	{
		SetYoyaku();
///	}
//	else
//	{
//		if (rt == CODE_USERCOMMAND)
//		{
//			UserCommandCallBack();
//		}

//		returnCode = GetReturnCode();
//		SetReturnCode(rt);
//	}


	return returnCode;
}


void CGameCallBack::SetDemoMode(BOOL b)
{
	m_demoFlag = b;

	if (m_demoFlag)
	{
		if (m_demoFlagVar != -1)
		{
			SetVarData(m_demoFlagVar,1);
		}
	}
	else
	{
		if (m_demoFlagVar != -1)
		{
			SetVarData(m_demoFlagVar,0);
		}
	}
}


void CGameCallBack::ResetAllShakin(void)
{
	m_pastTime = 0;
	m_pastTime2 = 0;
	m_totalCount = 0;
	m_skipCount = 0;
	m_shakin = 0;
	m_shakin1 = 0;
	m_shakin2 = 0;
	m_shakin3 = 0;

	m_totalTime = 0;

	CCommonPrintMessage* obj1 = (CCommonPrintMessage*)m_general[PRINTMESSAGE_MODE];
	if (obj1 != NULL) obj1->ResetShakin();

//	CCommonOverrap* obj2 = (CCommonOverrap*)m_general[PRINTOVERRAP_MODE];
//	if (obj2 != NULL) obj2->ResetShakin();

//@@@	if (m_backExecClass != NULL) m_backExecClass->ResetShakin();

	m_nextShakinFumitaoshi = 2;

//	OutputDebugString("[reset shakin]");
}





void CGameCallBack::FrameControl(int cnt)
{
	m_totalTime += cnt;
//	PollStream();
	
	if (cnt<0) cnt = 0;

	m_nowFrameCount = cnt;

	CalcuVoiceSpeak(cnt);
	m_effect->SetSpeakingFlag(CheckVoiceSpeak());


	if (cnt<m_frameTime)
	{
		m_pastTime -= (m_frameTime-cnt);
		if (m_pastTime<0) m_pastTime = 0;
	}


	if (cnt > m_frameTime)
	{
		m_pastTime += (cnt - m_frameTime);
	}

	if (m_nextShakinFumitaoshi>0)
	{
		m_nextShakinFumitaoshi--;
		if (m_pastTime>=m_frameTime) m_pastTime = m_frameTime-1;
	}

	if (m_systemFile->m_systemdata.noSkipFrame == 0)
	{
		m_pastTime2 = m_pastTime;
		if (m_pastTime2>(m_frameTime*m_maxSkipFrame)) m_pastTime2 = m_frameTime*m_maxSkipFrame;	//max 2frame skip
	}
}


void CGameCallBack::AdjustMouseZahyo(void)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(m_hWnd,&pt);
	if (m_viewControl != NULL)
	{
		pt = m_viewControl->WindowToGame(pt.x,pt.y);
	}
	m_mouseStatus->SetZahyo(pt.x,pt.y);
//	if (m_viewControl != NULL)
//	{
//		m_mouseStatus->AdjustOffset(m_viewControl->GetViewOffsetX(),m_viewControl->GetViewOffsetY());
//	}



	if (m_downed1) m_mouseStatus->SetTrig(0,TRUE);
	if (m_downed2) m_mouseStatus->SetTrig(1,TRUE);
	if (m_downed3) m_mouseStatus->SetTrig(2,TRUE);

	m_downed1 = FALSE;
	m_downed2 = FALSE;
	m_downed3 = FALSE;

	m_wheelDelta = 0;
	if (m_wheelMoveFlag)
	{
//OutputDebugString("move");

		if (m_wheelMove < 0)
		{
			m_wheelDelta = -1;
		}
		else
		{
			m_wheelDelta = 1;
		}
	}

	m_mouseStatus->SetWheel(m_wheelDelta);
}

void CGameCallBack::YoyakuShori(void)
{
	if (m_yoyaku > 0)
	{
		for (int i=0;i<m_yoyaku;i++)
		{
			CAreaControl::AddArea(m_eraseYoyakuX[i],m_eraseYoyakuY[i],m_eraseYoyakuSizeX[i],m_eraseYoyakuSizeY[i]);
		}
		m_yoyaku = 0;
	}
}

LRESULT CGameCallBack::GameProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int xPos,yPos;

	switch (message)
	{
	case WM_SETCURSOR:
		if (GetGameMode() == PRINTMOVIE_MODE)
		{
			if (m_systemFile->m_systemdata.useVMR9)
			{
				SetCursor(m_movieCursor);
			}
		}
		else
		{
			SetCursor(NULL);
		}
		break;

	case WM_MOUSEWHEEL:
		if (m_wheelWaitCount<=0)
		{
			if (m_backLogDisableCount == 0)
			{
//			m_mouseStatus->SetWheel( (int)(short) HIWORD(wParam) );   
				m_wheelMove = (int)(short)HIWORD(wParam);
//			m_wheelX = (int)(short) LOWORD(lParam);
//			m_wheelY = (int)(short) HIWORD(lParam);    
				m_wheelMoveFlag = TRUE;
//char mm[256];
//wsprintf(mm,"w[%d]",m_wheelMove);
//OutputDebugString(mm);
			}
		}
		break;




	case MM_MCINOTIFY:
		return TRUE;
		//return RepeatBGM(wParam,lParam);
/*
		if (GetSystemParam(SYSTEMPARAM_BGMMODE) == 0)
		{
			if (m_midi != NULL)
			{
				if (((MCIDEVICEID)lParam) == m_midi->GetMCIDeviceID())
				{
					if (wParam == MCI_NOTIFY_SUCCESSFUL)
					{
						m_midi->EndMIDI();
						return FALSE;
					}
				}
			}
		}
		else
		{
			if (((MCIDEVICEID)lParam) == GetCDDeviceID())
			{
				if (wParam == MCI_NOTIFY_SUCCESSFUL)
				{
					EndCD();
//					m_midi->EndMIDI();
					return FALSE;
				}
			}
		}
		return TRUE;
*/
	case WM_SYSKEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
//#if !defined _TINYAN3DLIB_
//			ChangeScreenModeYoyaku();
			ChangeScreenMode(TRUE);
//#endif
			break;
		}
		break;


	case WM_KEYDOWN:
		if (m_keyStatus != NULL)
		{
			m_keyStatus->SetKey((int)wParam);
		}

		if ((wParam >= '@') && (wParam <='Z'))
		{
//			m_alphabetKey[wParam - '@'] = TRUE;
		}
		else
		{
			switch (wParam)
			{
			case VK_ADD:
				if (m_printDebugParam != NULL) m_printDebugParam->ChangeDebugBackPrintMode();


	//@@@			if (m_debugOkFlag) m_debugVarFlag = !m_debugVarFlag;
				break;

				if (m_motionGetFlag == FALSE)
				{
					m_motionGetFlag = TRUE;
				}
				else
				{
					m_motionGetFlag = FALSE;
				}
				break;
			case VK_SUBTRACT:
				if (m_debugOkFlag) m_memPrintFlag = !m_memPrintFlag;
				SetBossMode(!CheckBossMode());
				if (CheckBossMode()) BossModeSoundOff();
				break;

				m_motionGetFlag = FALSE;
				m_motionGetCount = 0;
				break;

			case VK_MULTIPLY:
				AddDebugLibDesc();
				break;

				m_fpsPrintFlag = !m_fpsPrintFlag;
				break;

			case VK_DIVIDE:
				break;

				m_memPrintFlag = !m_memPrintFlag;
				break;

			case VK_ESCAPE:
				if (m_gameMode[0] != NAMEINPUT_MODE)
				{
					if (m_escKeyExitOffFlag == 0)
					{
						PostMessage(hWnd,WM_CLOSE,0,0);
					}
				}
				break;

			case VK_F9:
				if (m_gameMode[0] != NAMEINPUT_MODE)
				{
					if (m_f9KeyExitOffFlag == 0)
					{
						PostMessage(hWnd,WM_CLOSE,0,0);
					}
				}
				break;

			case VK_SHIFT:
				m_shiftKey = TRUE;
				ClickShiftKey();

				//SetMessageSkipFlag(!CheckMessageSkipFlag());
				break;
			case VK_CONTROL:
				m_ctrlKey = TRUE;
				SetMessageSkipFlag();
				break;
			case VK_RETURN:
				m_returnKey = TRUE;
				break;
			case VK_SPACE:
				m_spaceKey = TRUE;
				break;

			case VK_UP:
			case VK_NUMPAD8:
				OOnamiCommand(0);
				if (m_debugVarFlag)
				{
					if (m_printDebugParam != NULL) m_printDebugParam->AddDebugVarNumber(-1,TRUE);
//					m_debugVarDelta--;
//					if (m_debugVarDelta <0) m_debugVarDelta = 19;
					CAreaControl::SetNextAllPrint();
				}
	//			if (m_gameMode != CG_MODE)
	//			{
	//				SetWheelUp();
	//			}
				if (m_keyStatus != NULL) m_keyStatus->SetKey(VK_UP);
				//m_upKey = TRUE;
				m_wheelMoveFlag = TRUE;
	//			m_mouseStatus->SetWheel(120);
				m_wheelMove = 120;//HIWORD(wParam);

				break;
			case VK_DOWN:
			case VK_NUMPAD2:
				OOnamiCommand(1);
				if (m_debugVarFlag)
				{
					if (m_printDebugParam != NULL) m_printDebugParam->AddDebugVarNumber(1,TRUE);
//					m_debugVarDelta++;
//					if (m_debugVarDelta >=20) m_debugVarDelta = 0;
					CAreaControl::SetNextAllPrint();
				}
	//			if (m_gameMode != CG_MODE)
	//			{
	//				SetWheelDown();
	//			}
				if (m_keyStatus != NULL) m_keyStatus->SetKey(VK_DOWN);
				//m_downKey = TRUE;
				m_wheelMoveFlag = TRUE;
	//			m_mouseStatus->SetWheel(-120);
				m_wheelMove = -120;

				break;
			case VK_LEFT:
			case VK_NUMPAD4:
				OOnamiCommand(2);
				if (m_debugVarFlag)
				{
					if (m_printDebugParam != NULL)
					{
						int debugVar = m_printDebugParam->GetDebugVarStart();

						int oldDat = GetVarData(debugVar);
						oldDat--;
						if (m_shiftKey) oldDat -= 9;
						if (m_ctrlKey) oldDat -= 99;
						SetVarData(debugVar,oldDat);

//						m_var[debugVar]--;
//						if (m_shiftKey) m_var[debugVar] -= 9;
//						if (m_ctrlKey) m_var[debugVar] -= 99;

						CAreaControl::SetNextAllPrint();
					}
				}
				if (m_keyStatus != NULL) m_keyStatus->SetKey(VK_LEFT);
				//m_leftKey = TRUE;
				break;
			case VK_RIGHT:
			case VK_NUMPAD6:
				OOnamiCommand(3);
				if (m_debugVarFlag)
				{
					if (m_printDebugParam != NULL) 
					{
						int debugVar = m_printDebugParam->GetDebugVarStart();
						int oldDat = GetVarData(debugVar);
						oldDat++;
						if (m_shiftKey) oldDat += 9;
						if (m_ctrlKey) oldDat += 99;
						SetVarData(debugVar,oldDat);

						//m_var[debugVar]++;
						//if (m_shiftKey) m_var[debugVar] += 9;
						//if (m_ctrlKey) m_var[debugVar] += 99;

						CAreaControl::SetNextAllPrint();
					}
				}
				if (m_keyStatus != NULL) m_keyStatus->SetKey(VK_RIGHT);

				//m_rightKey = TRUE;
				break;


			case VK_INSERT:
			case VK_PRIOR:
				if (m_keyStatus != NULL) m_keyStatus->SetKey(VK_PRIOR);
//				m_pageUpKey = TRUE;
				if (m_debugVarFlag)
				{
					if (m_printDebugParam != NULL) 
					{
						m_printDebugParam->AddDebugVarPage(-1);
						CAreaControl::SetNextAllPrint();
					}
				}
				break;
			case VK_NEXT:
//				m_pageDownKey = TRUE;
//				if (m_keyStatus != NULL) m_keyStatus->SetKey(VK_NEXT);
				if (m_debugVarFlag)
				{
					if (m_printDebugParam != NULL) 
					{
						m_printDebugParam->AddDebugVarPage(1);
						CAreaControl::SetNextAllPrint();
					}
				}
				break;

			case VK_END:
//				m_endKey = TRUE;
				break;

			case VK_DELETE:
				if (m_keyStatus != NULL) m_keyStatus->SetKey(VK_NEXT);

	//			if (m_gameMode == NAMEINPUT_MODE)
	//			{
	//				if (m_nameInput != NULL)
	//				{
	//					m_nameInput->AddChar(0x8);
	//				}
	//			}
//				m_pageDownKey = TRUE;
				break;
			case VK_F12:
//#if !defined _TINYAN3DLIB_
//				ChangeScreenModeYoyaku();
				ChangeScreenMode(TRUE);
//#endif
	//			ToWindowScreen();
				break;

			case VK_F4:
				if (m_f4Ok)
				{
					if (GetGameMode() == PRINTMESSAGE_MODE)
					{
						if (CheckSceneMode() == FALSE)
						{
							if (CheckDemoMode() == FALSE)
							{
								SetMessageRead(m_lastMessageID);
								m_skipF4Mode = TRUE;
								m_skipF5Mode = FALSE;
								m_skipNextCommandFlag = TRUE;
								m_skipEffectCommandFlag = TRUE;
								m_skipToFilmEndFlag = FALSE;

	//							m_effect->ClearAllEffect();
								SetYoyaku();
							}
						}
					}
				}
				break;

			case VK_F5:
//				if (m_gameMode[0] == PRINTMESSAGE_MODE)
				if (m_f5Ok)
				{
					if (GetGameMode() == PRINTMESSAGE_MODE)
					{
						if (CheckSceneMode() == FALSE)
						{
							if (CheckDemoMode() == FALSE)
							{
								SetMessageRead(m_lastMessageID);
								m_skipF4Mode = FALSE;
								m_skipF5Mode = TRUE;
								m_skipNextCommandFlag = TRUE;
								m_skipEffectCommandFlag = TRUE;
								m_skipToFilmEndFlag = FALSE;

								m_effect->ClearAllEffect();
								SetYoyaku();
							}
						}
					}
				}
				break;
			}
			break;
		}

	case WM_KEYUP:
		switch (wParam)
		{
		case VK_SHIFT:
			m_shiftKey = FALSE;
			if (m_keyStatus != NULL)
			{
				m_keyStatus->SetKey((int)wParam,FALSE);
			}
			break;
		case VK_CONTROL:
			if (m_keyStatus != NULL)
			{
				m_keyStatus->SetKey((int)wParam,FALSE);
			}
			SetMessageSkipFlag(FALSE);
			m_ctrlKey = FALSE;
			break;
		}
		break;

	case WM_LBUTTONDOWN:
//OutputDebugString("↓");
		if (m_mouseStatus != NULL)
		{
			m_mouseStatus->SetTrig(0);
		}
//		m_trig1 = TRUE;
		m_downed1 = TRUE;
		break;
	case WM_RBUTTONDOWN:
		if (m_mouseStatus != NULL)
		{
			m_mouseStatus->SetTrig(1);
		}
//		m_trig2 = TRUE;
		m_downed2 = TRUE;
		break;
	case WM_MBUTTONDOWN:
		if (m_mouseStatus != NULL)
		{
			m_mouseStatus->SetTrig(2);
		}
//		m_trig3 = TRUE;
		m_downed3 = TRUE;
		break;

	case WM_LBUTTONUP:
//OutputDebugString("↑");
		if (m_mouseStatus != NULL)
		{
			m_mouseStatus->SetTrig(0,FALSE);
		}
//		m_trig1 = FALSE;
		break;
	case WM_RBUTTONUP:
		if (m_mouseStatus != NULL)
		{
			m_mouseStatus->SetTrig(1,FALSE);
		}
//		m_trig2 = FALSE;
		break;
	case WM_MBUTTONUP:
		if (m_mouseStatus != NULL)
		{
			m_mouseStatus->SetTrig(2,FALSE);
		}
//		m_trig3 = FALSE;
		break;


	case WM_DISPLAYCHANGE:
		if (GetGameMode() == PRINTMOVIE_MODE)
		{
			if (m_directShow != NULL) m_directShow->OnDisplayChanged();
		}
		break;

	case WM_ACTIVATEAPP:
		BOOL fActive;
		fActive = (BOOL)wParam;

		if (m_directDraw != NULL)
		{
#if !defined _TINYAN3DLIB_
			if (fActive)
			{
				if (m_directDraw->Activate(TRUE))
				{
					CAreaControl::SetNextAllPrint();
				}
			}
			else if (fActive == WA_INACTIVE)
			{
				m_directDraw->Activate(FALSE);
			}
#else
			//
#endif
		}
	
		break;



	case WM_SIZE:
		int fwSizeType;
		fwSizeType = (int)wParam;
		if (fwSizeType == SIZE_MAXIMIZED)
		{
//OutputDebugString("[WM_SIZE]");
			ToFullScreen(TRUE);
//			ToFullScreen();
		}
		LogMessage(WM_SIZE,wParam,lParam);
		break;

	case WM_APP+1:
		if (m_directShow != NULL) m_directShow->OnNotify();
		break;

	case WM_CLOSE:
#if defined _MT
		if (m_modalCannotCloseFlag)
		{
			if (GetModalLevel() > 0) return TRUE;
		}
#endif

//		DummyStopBGM();
//		if (m_midi != NULL)
//		{
///@@			m_wave->StopWave();
			Sleep(100);
			StopMusic();
			//StopBGM();
//			m_midi->Stop();
			Sleep(200);
//			m_midi->EndMIDI();
//		}
		EndGame();

		break;






	case WM_MOUSEMOVE:
		if (m_mouseStatus != NULL)
		{
			m_mouseStatus->SetZahyo( LOWORD(lParam), HIWORD(lParam) );
			if (m_viewControl != NULL)
			{
				POINT p = m_mouseStatus->GetZahyo();
				p = m_viewControl->WindowToGame(p.x,p.y);
				m_mouseStatus->SetZahyo(p.x,p.y);
				//m_mouseStatus->AdjustOffset(m_viewControl->GetViewOffsetX(),m_viewControl->GetViewOffsetY());
			}

			if (wParam & MK_LBUTTON)
			{
	//OutputDebugString("M");
				if (m_mouseStatus->GetTrig(0) == FALSE)
				{
	//OutputDebugString("+");
					m_mouseStatus->SetTrigOnly(0);
	//				m_downed1 = TRUE;
				}
			}
			else
			{
				if (m_mouseStatus->GetTrig(0))
				{
					m_mouseStatus->SetTrig(0,FALSE);
				}
			}

			if (wParam & MK_RBUTTON)
			{
				if (m_mouseStatus->GetTrig(1) == FALSE)
				{
					m_mouseStatus->SetTrigOnly(1);
	//				m_downed2 = TRUE;
				}
			}
			else
			{
				if (m_mouseStatus->GetTrig(1))
				{
					m_mouseStatus->SetTrig(1,FALSE);
				}
			}

			if (wParam & MK_MBUTTON)
			{
				if (m_mouseStatus->GetTrig(2) == FALSE)
				{
					m_mouseStatus->SetTrigOnly(2);
	//				m_downed3 = TRUE;
				}
			}
			else
			{
				if (m_mouseStatus->GetTrig(2))
				{
					m_mouseStatus->SetTrig(2,FALSE);
				}
			}
		}

		break;




	case WM_PAINT:
		if (GetGameMode() == PRINTMOVIE_MODE)
		{
//OutputDebugString("P");
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd,&ps);

			if (m_movieEnableFlag)
			{
	//			CCommonPrintMovie* movie = (CCommonPrintMovie*)m_general[PRINTMOVIE_MODE];
	//			if (movie != NULL) movie->OnPaint();
				if (m_directShow != NULL)
				{
					if (hdc != NULL)
					{
						m_directShow->OnPaint(hWnd,hdc);
					}
				}
			}

			EndPaint(hWnd,&ps);
		//	return 0;
			break;
		}
		RECT updateRect;
		RECT rcMax;
		int screenSizeX;
		int screenSizeY;
		screenSizeX = CMyGraphics::GetScreenSizeX();
		screenSizeY = CMyGraphics::GetScreenSizeY();

		SetRect(&rcMax,0,0,screenSizeX,screenSizeY);
		if (GetUpdateRect(hWnd,NULL,FALSE))
		{
			GetUpdateRect(hWnd,&updateRect,FALSE);
			if (IntersectRect(&updateRect,&updateRect,&rcMax))
			{
				YoyakuArea(&updateRect);
			}
		}
		else
		{
				YoyakuArea(&rcMax);
		}
		break;

		//@@@@@@@@@@@@@@@@@@@@@@@@@@@ test20130826
//	case WM_ERASEBKGND:
//		return 1;
//		break;
	case WM_CHAR:
		if (m_textInputBox != NULL)
		{
			m_textInputBox->AddChara(wParam & 0xff);
		}

		if (m_gameMode[0] == NAMEINPUT_MODE)
		{
//			CNameInput* nameInput;
//			nameInput = (CNameInput*)m_general[NAMEINPUT_MODE];
//			if (nameInput != NULL)
//			{
//				nameInput->AddChar(wParam & 0xff);
//			}
		}
		break;

	case WM_MOVE:
		xPos = (int)(short) LOWORD(lParam);    // horizontal position 
		yPos = (int)(short) HIWORD(lParam);    // vertical position 

		LogMessage(WM_MOVE,wParam,lParam);
		
		if (GetSystemParam(NNNPARAM_SCREENMODE) == 0)
		{
			if (!IsZoomed(m_hWnd))
			{
				//最小化チェック

				WINDOWINFO wif;
				BOOL bad;
				bad = FALSE;

				if (GetWindowInfo(hWnd,&wif))
				{
					if (wif.dwStyle & WS_MINIMIZE)
					{
						bad = TRUE;
					}
				}




				if (bad == FALSE)
				{
					m_windowX = xPos - GetSystemMetrics(SM_CXFIXEDFRAME);
					m_windowY = yPos - GetSystemMetrics(SM_CYFIXEDFRAME ) - GetSystemMetrics(SM_CYCAPTION);

					m_systemFile->m_systemdata.windowX = m_windowX;
					m_systemFile->m_systemdata.windowY = m_windowY;

					CAreaControl::SetNextAllPrint();
				}
			}
		}

		if (m_directDraw != NULL)
		{
#if !defined _TINYAN3DLIB_
			m_directDraw->WindowIsMoved(xPos,yPos);
#endif

//char aaa[256];
//sprintf(aaa,"[wm_move %d %d]",xPos,yPos);
//if (GetSystemParam(NNNPARAM_SCREENMODE) == 0)
//{
//	MessageBox(NULL,aaa,"aaa",MB_OK);
	//OutputDebugString(aaa);
//}

//			InvalidateRect(hwnd,NULL,FALSE);
			CAreaControl::SetNextAllPrint();
		}

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void CGameCallBack::EndGame(void)
{
	for (int i=0;i<100;i++)
	{
		m_systemFile->m_systemVar.var[i] = m_var[200+i];
	}

	LPSTR sei = m_systemFile->m_systemdata.sei;
	LPSTR mei = m_systemFile->m_systemdata.mei;

	LPSTR srcSei = CMyMessage::m_sei;
	LPSTR srcMei = CMyMessage::m_mei;

	memcpy(sei,srcSei,strlen(srcSei)+1);
	memcpy(mei,srcMei,strlen(srcMei)+1);


//@@@	if (m_mciOpenCDFlag) CloseCDDevice();

	m_quitFlag = TRUE;

}

void CGameCallBack::YoyakuArea(RECT* lpRect)
{
	if (m_yoyaku >= 100)
	{
		return;
	}

	int x = lpRect->left;
	int y = lpRect->top;
	int sx = lpRect->right - x;
	int sy = lpRect->bottom - y;

	if ((sx<=0) || (sy<=0)) return;

	m_eraseYoyakuX[m_yoyaku] = x;
	m_eraseYoyakuY[m_yoyaku] = y;
	m_eraseYoyakuSizeX[m_yoyaku] = sx;
	m_eraseYoyakuSizeY[m_yoyaku] = sy;
	m_yoyaku++;

}

int CGameCallBack::GetVarData(int varNum)
{
	if ((varNum>=0) && (varNum<1000))
	{
		return m_var[varNum] ;
	}

	if (varNum & 0x8000)
	{
		return varNum & 0x7fff;
	}
	return 0;
}

void CGameCallBack::SetVarData(int varNum, int dat)
{
	if ((varNum<0) || (varNum>=1000))
	{
		return;
	}

	//check layeroff var?
	int layer = m_layerOffVar[varNum];
	if (layer != -1)
	{
		int bt = 1;
		for (int i=0;i<layer;i++)
		{
			bt <<= 1;
		}

		if (dat)
		{
			m_effect->SetEye(layer,FALSE);
			m_layerOff |= bt;
		}
		else
		{
			m_effect->SetEye(layer,TRUE);
			m_layerOff &= ~bt;
		}
	}



	m_var[varNum] = dat;
}

int CGameCallBack::GetCalcuVarData(int varNum)
{
	if (varNum == m_rndVar)
	{
		for (int i=0;i<50;i++)
		{
			int r = rand();
			if (r<30000) return r % 10000;
		}

		return (rand() % 10000);
	}

	if (varNum == m_weekVar)	//0-6 0:日曜
	{
		int daymonth = GetVarData(m_dayMonthVar);
		return GetWeek(daymonth);
	}

	if (varNum == m_holidayVar)	//土曜日曜祭日
	{
		int daymonth = GetVarData(m_dayMonthVar);

		int week = GetWeek(daymonth);
		if ((week == 0) || (week == 6)) return 1;

		int month = daymonth / 100;
		int day = daymonth % 100;
		int year = 2000;
		if (m_yearVar != -1)
		{
			year = GetVarData(m_yearVar);
		}

		if (CheckSaijitsu(year,month,day)) return 1;

		return 0;
	}

	if (varNum == m_systemYearVar) return GetNowSystemTime(varNum);
	if (varNum == m_systemMonthVar) return GetNowSystemTime(varNum);
	if (varNum == m_systemDayVar) return GetNowSystemTime(varNum);
	if (varNum == m_systemHourVar) return GetNowSystemTime(varNum);
	if (varNum == m_systemMinuteVar) return GetNowSystemTime(varNum);
	if (varNum == m_systemSecondVar) return GetNowSystemTime(varNum);
	if (varNum == m_systemWeekVar) return GetNowSystemTime(varNum);
	if (varNum == m_systemMilliSecondVar) return GetNowSystemTime(varNum);


	if (varNum == m_mouseXVar)
	{
		POINT pt = m_mouseStatus->GetZahyo();
		return pt.x;
	}
	if (varNum == m_mouseYVar)
	{
		POINT pt = m_mouseStatus->GetZahyo();
		return pt.y;
	}
	if (varNum == m_trig1Var) return m_mouseStatus->GetTrig(0);
	if (varNum == m_trig2Var) return m_mouseStatus->GetTrig(1);
	if (varNum == m_trig3Var) return m_mouseStatus->GetTrig(2);
	if (varNum == m_click1Var) return m_mouseStatus->CheckClick(0);
	if (varNum == m_click2Var) return m_mouseStatus->CheckClick(1);
	if (varNum == m_click3Var) return m_mouseStatus->CheckClick(2);
	if (varNum == m_wheelVar) return m_mouseStatus->GetWheel();
	if (varNum == m_modeVar) return GetGameMode();

#if !defined _TINYAN3DLIB_
	if (varNum == m_direct3DVar) return 2;
	if (varNum == m_pixelShaderVar) return 0;
	if (varNum == m_vertexShaderVar) return 0;
#else
	if (varNum == m_direct3DVar) return 3;
	if (varNum == m_pixelShaderVar) return CMyDirect3D::GetPixelShaderVersion();
	if (varNum == m_vertexShaderVar) return CMyDirect3D::GetVertexShaderVersion();
#endif


	if (varNum == m_cgPercentVar)
	{
		if (m_cgDataControl == NULL) return 0;
		return m_cgDataControl->GetTotalCGPercent();
	}

	if (varNum == m_scenePercentVar)
	{
		if (m_sceneDataControl == NULL) return 0;
		return m_sceneDataControl->GetTotalScenePercent();
	}


	int i = 0;
	for (i=0;i<m_expButtonKosuu;i++)
	{
		if (m_expButtonVarNumber[i] != -1)
		{
			if (m_expButtonVarNumber[i] == varNum)
			{
				return GetSystemParam(NNNPARAM_EXPMODE + i);
			}
		}
	}

	for (i=0;i<m_expCheckButtonKosuu;i++)
	{
		if (m_expCheckButtonVarNumber[i] != -1)
		{
			if (m_expCheckButtonVarNumber[i] == varNum)
			{
				return GetSystemParam(NNNPARAM_EXPCHECK + i);
			}
		}
	}

	return GetVarData(varNum);
	return 0;
}

BOOL CGameCallBack::CheckSaijitsu(int year,int month, int day)
{
	//外部ファイルにすべき
	if (m_saijitsuList != NULL)
	{
		if (m_saijitsuList->CheckSaijitsu(year,month,day))
		{
			return TRUE;
		}
	}


//	for (int i=0;i<15;i++)
//	{
//		if ((m_saijitsu2000[i*2] == month) && (m_saijitsu2000[i*2+1] == day)) return TRUE;
//	}

	return FALSE;
}


void CGameCallBack::ChangeScreenMode(BOOL directFlag)
{




	if (GetSystemParam(NNNPARAM_SCREENMODE) == 0)
	{
		ToFullScreen(directFlag);
	}
	else
	{
		ToWindowScreen(directFlag);
	}
}


void CGameCallBack::ClearAllKey(void)
{
	m_keyStatus->ClearAllKey();
}



void CGameCallBack::InitLoadGame(void)
{
	CCommonGeneral* general = m_general[m_gameMode[0]];

	//SetCalendarFlag(FALSE);
	SetOption(FALSE);
	SetSceneButton(FALSE);
	SetDemoMode(FALSE);
	SetSceneMode(FALSE);
	SetBackScriptMode(FALSE);

	ClearFontCache();

	m_nameIsSpecialVoiceFlag = -1;

//	m_effect->Calcu(256);
//	m_effect->CalcuZahyo();
	m_skipNextCommandFlag = FALSE;
	m_skipEffectCommandFlag = FALSE;
	m_skipToFilmEndFlag = FALSE;
//	m_skipToFilmEndEnable = FALSE;

//	CKumiawase* pDoc = (CKumiawase*)m_general[KUMIAWASE_MODE];
//	pDoc->GetLoadData(m_kumiawaseVar);	//表示関係の絵の初期化のため

//	general->GeneralInit();//これでいくつか変数がかわるため(KUMIAWASE_MODE)
//
//	if (m_gameMode == KUMIAWASE_MODE)
//	{
//		((CKumiawase*)general)->SetMode(0,TRUE);
//	}

//sprintf(mes,"このじてんでのdate=%d",m_var[0]);
//MessageBox(NULL,mes,"test2.2",MB_OK);



	general->InitByLoad();

//	pDoc->GetLoadData(m_kumiawaseVar);	//2かいめの初期化がひつようにゃ
//sprintf(mes,"このじてんでのdate=%d",m_var[0]);
//MessageBox(NULL,mes,"test3",MB_OK);

	if (m_gameMode[0] == PRINTMESSAGE_MODE)
	{
		CCommonPrintMessage* pDoc = (CCommonPrintMessage*)m_general[PRINTMESSAGE_MODE];
		pDoc->SetMessageKosuu(m_messageKosuu);
		SetBackScriptMode(FALSE);


		pDoc->SetCutinMode(m_cutinFlag);
	}
	else
	{
		CCommonPrintMessage* pDoc = (CCommonPrintMessage*)m_general[PRINTMESSAGE_MODE];
		pDoc->SetCutinMode(m_cutinFlag);
	}

	if (m_gameMode[0] == SELECTMESSAGE_MODE)
	{
		CCommonSelectMessage* pDoc = (CCommonSelectMessage*)m_general[SELECTMESSAGE_MODE];
//		int addMessageKosuu = pDoc->GetAddMessageKosuu();
		pDoc->SetMessageKosuu(m_selectMessageKosuu-m_selectMessageAddKosuu,m_selectMessageAddKosuu);
	}

	general->GeneralInit();

	if (m_omakeClassSupport != NULL)
	{
		if (m_omakeClassSupport->GetOmakeClassExistFlag())
		{
			InitLoadOmake();
//			m_omakeClassSupport->InitLoadOmake();
		}
	}


	m_effect->InitAllParameter();

	RestartLoopSoundAndVoice();


//sprintf(mes,"このじてんでのdate=%d",m_var[0]);
//MessageBox(NULL,mes,"test5",MB_OK);

	AfterInitLoadGame();

}

void CGameCallBack::InitLoadOmake(void)
{
	int newMode = m_gameMode[0];

	if (newMode != -1)
	{
		for (int i=0;i<OMAKEMODE_KOSUU;i++)
		{

			//int omake = m_omakeClass[newMode][i] / 256;
			if (m_omakeClassSupport != NULL)
			{
				int omake = m_omakeClassSupport->GetOmakeClass(newMode,i) / 256;

				if (omake != 0)
				{
					CCommonGeneral* general = m_general[omake];
					if (general != NULL) general->OmakeGeneralInit();
				}
			}
		}
	}
}


void CGameCallBack::SetSystemVarNumber(void)
{
	m_rndVar = m_varNumber->GetVarNumber("rnd");
	m_dayMonthVar = m_varNumber->GetVarNumber("date");
	m_yearVar = m_varNumber->GetVarNumber("year");
	m_holidayVar = m_varNumber->GetVarNumber("holiday");
	m_weekVar = m_varNumber->GetVarNumber("week");
}

void CGameCallBack::PrintInitializeMessage(void)
{
	HDC hdc00 = GetDC(m_hWnd);
	RECT rc00;
	SetRect(&rc00,0,0,m_windowSizeX,m_windowSizeY);
	FillRect(hdc00,&rc00,(HBRUSH)(COLOR_WINDOW + 1));
	TextOut(hdc00,0,0,"Initializing..",(int)strlen("Initializing.."));
	ReleaseDC(m_hWnd,hdc00);
}


BOOL CGameCallBack::CheckInitDirectX(void)
{
	return TRUE;	//
}


BOOL CGameCallBack::NextSceneFilm(void)
{
	if (m_sceneDataControl == NULL) return FALSE;

	int film = m_sceneDataControl->GetNextSceneFilm();
	if (film != -1)
	{
		m_execScript->SetPCByFilmNumber(film);
		return TRUE;
	}

	return FALSE;
}


BOOL CGameCallBack::StartSceneMode(void)
{
	if (m_sceneDataControl != NULL)
	{
		m_sceneDataControl->SetSceneFilmNumber(0);
	}
//	m_sceneFilmNumber = 0;

	if (m_sceneList == NULL)
	{
		return FALSE;
	}



	m_cutinFlag = 0;
	CCommonPrintMessage* obj = (CCommonPrintMessage*)(m_general[PRINTMESSAGE_MODE]);
	if (obj != NULL)
	{
		obj->SetCutinMode(m_cutinFlag);
	}

	int sceneCharaNumber = 0;
	int sceneNumber = 0;
	if (m_sceneDataControl != NULL)
	{
		sceneCharaNumber = m_sceneDataControl->GetSceneCharaNumber();
		sceneNumber = m_sceneDataControl->GetSceneNumber();
	}
	m_sptFileNumber[1] = m_sceneList->GetScriptNumber(sceneCharaNumber,sceneNumber);
//	m_sptFileNumber[1] = m_sceneList->GetScriptNumber(m_sceneCharaNumber,m_sceneNumber);

	m_onSceneFlag = FALSE;


	if (m_optionButton != NULL) m_optionButton->Init();
	if (m_sceneButton != NULL) m_sceneButton->Init();
	if (m_skipFilmButton != NULL) m_skipFilmButton->Init();
	//if (m_quickSaveButton != NULL) m_quickSaveButton->Init();
	//if (m_quickLoadButton != NULL) m_quickLoadButton->Init();
	




	//load script and set pc

	char filename[256];
	wsprintf(filename,"spt\\%s.spt",m_sptList->GetName(m_sptFileNumber[1]));
	m_execScript->LoadScript(filename);	//dummy

	int sceneFilmNumber = 0;
	if (m_sceneDataControl != NULL)
	{
		sceneFilmNumber = m_sceneDataControl->GetSceneFilmNumber();
	}
//	int film = m_sceneList->GetPlayFilmNumber(m_sceneCharaNumber,m_sceneNumber,m_sceneFilmNumber);
	int film = m_sceneList->GetPlayFilmNumber(sceneCharaNumber,sceneNumber,sceneFilmNumber);
	if (m_execScript->SetPCByFilmNumber(film))
	{
		m_scriptRunMode = 1;
		SetYoyaku();
		CAreaControl::SetNextAllPrint();
		return TRUE;
	}


	MessageBox(NULL,"シーン番号が変か、もしくは、コンパイルしたadveditが古いみたいですにゃ","ERROR",MB_OK);
	return FALSE;
}

void CGameCallBack::SetDesktopWindowSize(int sizeX, int sizeY)
{
	m_deskTopWindowSizeX = sizeX;
	m_deskTopWindowSizeY = sizeY;

	if (m_directDraw != NULL)
	{
		m_directDraw->SetWindowSize(sizeX,sizeY);
	}

}



void CGameCallBack::SetDesktopWindowStart(POINT pt)
{
	m_desktopWindowStartX = pt.x;
	m_desktopWindowStartY = pt.y;
	if (m_directDraw != NULL)
	{
		m_directDraw->SetWindowStart(pt);
	}
}

void CGameCallBack::SetDesktopWindowEnd(POINT pt)
{
	m_desktopWindowEndX = pt.x;
	m_desktopWindowEndY = pt.y;
	if (m_directDraw != NULL)
	{
		m_directDraw->SetWindowEnd(pt);
	}
}


void CGameCallBack::Flush(void)
{
	if (m_taihi != NULL) m_taihi->AllFlush();
}

void CGameCallBack::Erase(void)
{
	if (m_taihi != NULL) m_taihi->AllFuque();
}

int CGameCallBack::GetVarNumber(LPSTR name)
{
	return m_varNumber->GetVarNumber(name);
}

void CGameCallBack::AfterInitNewGame(int uraMode, BOOL demoFlag)
{
}


void CGameCallBack::AfterInitLoadGame(void)
{
}

void CGameCallBack::SaveSystemFile(void)
{
	BeforeSaveSystemFile();

	LPSTR sei = m_systemFile->m_systemdata.sei;
	LPSTR mei = m_systemFile->m_systemdata.mei;

	LPSTR srcSei = CMyMessage::m_sei;
	LPSTR srcMei = CMyMessage::m_mei;

	memcpy(sei,srcSei,strlen(srcSei)+1);
	memcpy(mei,srcMei,strlen(srcMei)+1);

	for (int i=0;i<100;i++)
	{
		m_systemFile->m_systemVar.var[i] = m_var[200+i];
	}

	m_systemFile->Save();

	if (m_resultFlag)
	{
		if (m_commonResultData != NULL)
		{
			m_commonResultData->Save();
		}
	}
	
	AfterSaveSystemFile();
}



void CGameCallBack::CursorAnime(int cnt)
{
}


void CGameCallBack::SetMyCursor(int pat)
{
	SetMyCursor(m_cursorPrintX,m_cursorPrintY,pat);
}


void CGameCallBack::SetMyCursor(int x, int y, int pat)
{
	m_cursorPrintX = x;
	m_cursorPrintY = y;
	m_cursorPat = pat;
	m_cursorFlag = TRUE;

	if (pat >= 2)
	{
		m_messageCursor->SetFullZahyo(m_cursorPrintX,m_cursorPrintY);
	}
}



void CGameCallBack::SetBGMVolumeOnly(int vol)
{
	if (GetSystemParam(NNNPARAM_BGMMODE) == 0)
	{
		if (GetSystemParam(NNNPARAM_BGMMODE) == 0)
		{
//			m_mixer->SetMIDIVolume(vol);
		}
		else
		{
//			m_mixer->SetCDVolume(vol);
		}
	}
	else
	{
		if (GetSystemParam(NNNPARAM_BGMMODE) == 0)
		{
//			m_midi->SetVolume(vol);
		}
		else
		{
//			m_mixer->SetCDVolume(vol);
		}
	}
}




void CGameCallBack::SetOptionVarOn(BOOL flg)
{
	if (m_optionOffVar == -1) return;
	int d = 1;
	if (flg) d = 0;
	SetVarData(m_optionOffVar,d);
}

void CGameCallBack::WindowOn(BOOL flg)
{
	CCommonPrintMessage* obj = (CCommonPrintMessage*)m_general[PRINTMESSAGE_MODE];
	if (obj != NULL) obj->WindowOn(flg);
}





void CGameCallBack::SetGameVersion(int highVersion, int middleVersion, int lowVersion)
{
	int version = (highVersion << 16) | (middleVersion << 8) | lowVersion;
	m_gameVersion = version;
}


LPSTR CGameCallBack::GetBGMFileName(int n)
{
	if (m_bgmList == NULL) return NULL;
	return m_bgmList->GetName(n*2);
}

LPSTR CGameCallBack::GetBGMName(int n)
{
	if (m_bgmList == NULL) return NULL;
	return m_bgmList->GetName(n*2+1);
}

void CGameCallBack::PlaySystemWaveFilename(LPSTR filename,int deltaVolume)
{
	if (CheckTotalVolumeOff()) return;
	if (GetSystemParam(NNNPARAM_SOUNDSWITCH) == 0) return;

	char name[256];
	wsprintf(name,"sys\\%s",filename);

	m_useSystemSoundNumber++;
	m_useSystemSoundNumber %= 2;

	m_systemSound[m_useSystemSoundNumber]->Stop();

	if (m_waveData->LoadSystemWave("sys",filename))
	{
		int stereo = m_waveData->GetChannel();
		int sampleRate = m_waveData->GetSampleRate();
		int bitRate = m_waveData->GetBitRate();

		char* realPtr = (char*)(m_waveData->GetRealDataPtr());
		int realSize = m_waveData->GetRealDataSize();

		m_systemSound[m_useSystemSoundNumber]->SetData(realPtr,realSize,stereo,sampleRate,bitRate);

		int vol = GetSystemParam(NNNPARAM_SOUNDVOLUME);
		vol += deltaVolume;
		if (vol<0) vol = 0;
		if (vol>100) vol = 100;

		m_systemSound[m_useSystemSoundNumber]->SetVolume(vol);
		m_systemSound[m_useSystemSoundNumber]->Play();
	}



//@@	m_wave->StopWave();
//	m_wave->LoadWave(name);

//	PlaySoundRoutine(m_wave,0);
	//m_wave->PlayWave();
}


void CGameCallBack::PlaySystemVoiceByFileName(LPSTR filename, BOOL firstOffFlag,BOOL sameBufferFlag)
{
	if (CheckTotalVolumeOff()) return;
	if (GetSystemParam(NNNPARAM_VOICESWITCH) == 0) return;

	char name[256];
	wsprintf(name,"sys\\%s",filename);

	if (sameBufferFlag == FALSE)
	{
		m_useSystemSoundNumber++;
	}
	m_useSystemSoundNumber %= 2;

	m_systemSound[m_useSystemSoundNumber]->Stop();

	if (m_waveData->LoadSystemWave("sys",filename))
	{
		int stereo = m_waveData->GetChannel();
		int sampleRate = m_waveData->GetSampleRate();
		int bitRate = m_waveData->GetBitRate();

		char* realPtr = (char*)(m_waveData->GetRealDataPtr());
		int realSize = m_waveData->GetRealDataSize();

		m_systemSound[m_useSystemSoundNumber]->SetData(realPtr,realSize,stereo,sampleRate,bitRate);

		int vol = GetSystemParam(NNNPARAM_VOICEVOLUME);
		m_systemSound[m_useSystemSoundNumber]->SetVolume(vol);
		m_systemSound[m_useSystemSoundNumber]->Play();
	}
}


//VOICE,にのみ対応
BOOL CGameCallBack::CheckResetVolume(int volumeType)
{
	int vol = GetSystemParam(volumeType);
	if (vol == 0) return FALSE;

	switch (volumeType)
	{
	case NNNPARAM_VOICEVOLUME:
		if (m_lastSoundVoiceVolume != vol)
		{
			if (GetMusicMode() == 0)
			{
				m_mixer->SetWAVEVolume(vol);
			}
			else
			{
				m_directSound->SetVolume(vol);
			}
			m_lastSoundVoiceVolume = vol;
		}
		break;
	}

	return TRUE;
}



void CGameCallBack::PrintDebugParam(void)
{
	if (m_printDebugParam == NULL) return;
	m_printDebugParam->Print();
}

void CGameCallBack::PrintDebugBack(void)
{
	if (m_printDebugParam == NULL) return;
	m_printDebugParam->PrintDebugBack();
}

BOOL CGameCallBack::GetInitGameParam(int* lpVar, LPSTR name,int initData)
{
	*lpVar = initData;
	return GetInitGameParam(lpVar,name);
}

BOOL CGameCallBack::GetInitGameParam(int* lpVar, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpVar = atoi(m_setup->GetName(rNum + 1));

	return TRUE;
}

BOOL CGameCallBack::GetInitGameString(LPSTR* lpStr, LPSTR name,LPSTR initString)
{
	*lpStr = initString;
	return GetInitGameString(lpStr,name);
}

BOOL CGameCallBack::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_setup->GetName(rNum + 1);

	return TRUE;
}

BOOL CGameCallBack::GetInitGameParam3(int* lpVar, LPSTR name)
{
	if (m_setup3 == NULL) return FALSE;

	int rNum = m_setup3->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpVar = atoi(m_setup3->GetName(rNum + 1));

	return TRUE;
}


BOOL CGameCallBack::LoadSetupFile(LPSTR filenameonly, int varKosuu)
{
	if (m_setup == NULL)
	{
		m_setup = new CNameList(varKosuu * 2);
	}

	if (m_setup == NULL) return FALSE;

	return m_setup->LoadInit(filenameonly);
//	char filename2[1024];
//	wsprintf(filename2,"init\\%s.xtx",filenameonly);	

//	return m_setup->LoadFile(filename2);
}


BOOL CGameCallBack::LoadSetupFile2(LPSTR filenameonly, int varKosuu)
{
	if (m_setup2 == NULL)
	{
		m_setup2 = new CNameList(varKosuu * 2);
	}

	if (m_setup2 == NULL) return FALSE;

	return m_setup2->LoadInit(filenameonly);

//	char filename2[1024];
//	wsprintf(filename2,"init\\%s.xtx",filenameonly);	

//	return m_setup2->LoadFile(filename2);
}

BOOL CGameCallBack::LoadSetupFile3(LPSTR filenameonly, int varKosuu)
{
	if (m_setup3 == NULL)
	{
		m_setup3 = new CNameList(varKosuu * 2);
	}

	if (m_setup3 == NULL) return FALSE;

	return m_setup3->LoadInit(filenameonly);

//	char filename3[1024];
//	wsprintf(filename3,"init\\%s.xtx",filenameonly);	

//	return m_setup3->LoadFile(filename3);
}


int CGameCallBack::ExecGameScript(int pc)
{
	CExecScript* lpScript = GetScript();
	return lpScript->Exec(pc);
}


void CGameCallBack::YoyakuExecRoutine(void)
{
	while (m_yoyakuExecFlag)
	{
		int rt = ExecGameScript();

		if (rt == CODE_CONTROL_ENDFILM)
		{
			if (m_sceneMode)
			{
				if (NextSceneFilm()) continue;

				//ここでPrintMessageにCreateExitScreenさせるかどうかの処理をいれる@@@@@@@@@@@@@@@
				CCommonPrintMessage* mesObj = (CCommonPrintMessage*)m_general[PRINTMESSAGE_MODE];
				if (mesObj != NULL)
				{
					mesObj->OnEndFilm();
				}

				m_yoyakuExecFlag = FALSE;
				SetReturnCode(SELECTSCENE_MODE);
				break;
			}
			else
			{
				if (m_skipToFilmEndFlag)
				{
					m_skipToFilmEndFlag = FALSE;
					m_skipNextCommandFlag = FALSE;
					m_skipEffectCommandFlag = FALSE;
					m_skipToFilmEndEnable = FALSE;
				}
			}

			continue;
		}

		if (rt == CODE_CONTROL_ENDKOMA)	continue;
		if (rt == CODE_CONTROL_ENDIF)	continue;
		if (rt == CODE_CONTROL_SCRIPT) continue;
		if (rt == CODE_CONTROL_SUBSCRIPT) continue;
		if (rt == CODE_CONTROL_SCRIPTJUMP) continue;
		


		//このルーチンは削除する?????
//		if (rt == CODE_CONTROL_NEXT)
//		{
//			if (m_cgMode)
//			{
//				m_yoyakuExecFlag = FALSE;
//				SetReturnCode(SELECTSCENE_MODE);
//				break;
//			}
//		}

		if (rt == CODE_CONTROL_NEXT)
		{
			if (m_scriptRunMode > 0)
			{
				m_scriptRunMode--;
			}
			else
			{
				//error!
			}
			continue;
		}

		if (rt == CODE_CONTROL_END)
		{
			m_scriptRunMode = 0;
			m_controlScript->SetPC(0);
			m_controlScript->m_stackPointer = 0;
			continue;
		}


		if (rt == CODE_CONTROL_EXIT)
		{
			Erase();
			m_overrapPic1->GetScreen();

			for (int i=0;i<100;i++)
			{
				m_systemFile->m_systemVar.var[i] = m_var[200+i];
			}

			//last!
			for (int i=0;i<100;i++)
			{
				CCommonGeneral* general = m_general[i];
				if (general != NULL)
				{
					general->ExitGame();
				}
			}
			//save systemfile
			SaveSystemFile();

			ClearF5();
			SetReturnCode(TITLE_MODE);
			m_yoyakuExecFlag = FALSE;
			if (m_autoDebugMode)
			{
				if (m_autoSelectControl != NULL)
				{
					m_autoSelectControl->Finish();
				}
			}
			return;
		}


		if (rt == CODE_USERCOMMAND)
		{
			//auto new Class Set Initialize



			//
			UserCommandCallBack();
		}

		if (m_skipNextCommandFlag == FALSE)
		{
			m_yoyakuExecFlag = FALSE;
		}
	}
}

CPicture* CGameCallBack::GetEffectPicture(int n)
{
	return m_effect->GetPicture(n);
}


void CGameCallBack::PreReceiveScriptData(int cmd, int para1, LPVOID para2)
{
	if (cmd == CODE_SYSTEMFUNCTION_VOICE)
	{
//		int paraKosuu = para1;
//		int* pData = (int*)para2;
		m_preReceiveFileName = (LPSTR)(para2);
	}
}

//////////////////////////////////
void CGameCallBack::SystemFunctionSetCG(int para1,LPVOID para2)
{
	int paraKosuu = para1;
	int* pData = (int*)para2;
	int player = *pData;
	int cgNumber = *(pData+1);
	int layer = -1;
	if (paraKosuu >= 3)
	{
		layer = *(pData + 2);
	}
		//set cg

	BOOL bb = TRUE;
	if (CheckBackScriptMode())
	{
		if (m_backScriptSetCGOkFlag == 0) bb = FALSE;
	}

	if (m_skipNextCommandFlag)
	{
		if (m_mustSetCGFlag == 0) bb = FALSE;
	}


	if (m_offLayerDontSetCG)
	{
		if (layer >= 0)
		{
			int bitPattern = 1;
			if (layer > 0)
			{
				bitPattern = 1 << layer;
			}
	
			if (m_layerOff & bitPattern)
			{
				bb = FALSE;
			}
		}
	}

	if (bb) m_systemFile->SetCG(player-1,cgNumber-1);
}

void CGameCallBack::SetCG(int cgPlayer,int cgParam)
{
	m_systemFile->SetCG(cgPlayer-1,cgParam-1);
}



void CGameCallBack::SystemFunctionSetFilm(int para1,LPVOID para2)
{
	int paraKosuu = para1;
	int* pData = (int*)para2;
	int filmNumber = *pData;
	//set film flag

	BOOL bb = TRUE;
	if (CheckBackScriptMode())
	{
		if (m_backScriptSetCGOkFlag == 0) bb = FALSE;
	}

	if (m_skipNextCommandFlag)
	{
		if (m_mustSetFilmFlag == 0) bb = FALSE;
	}

	if (bb) m_systemFile->SetFilm(m_sptFileNumber[m_scriptRunMode],filmNumber-1);
}

void CGameCallBack::SystemFunctionPrepareOverrap(int para1,LPVOID para2)
{
	if ((m_skipNextCommandFlag == FALSE) || (m_skipEffectCommandFlag == FALSE))
	{
#if defined _TINYAN3DLIB_
		BeginGet(m_overrapPic1);
#endif
		if (CheckBackScriptMode() == FALSE)
		{
			//再描画??
			Erase();
//				PrintMessageWindow(TRUE);
			m_overrapPic1->GetScreen();
		}
		else
		{
			Erase();
//				m_effect->Print(FALSE);
//				PrintMessageWindow(TRUE);
//				m_effect->Print(TRUE);

			//others

			m_overrapPic1->GetScreen();
		}
#if defined _TINYAN3DLIB_
		EndGet();
#endif
	}
}

void CGameCallBack::SystemFunctionVolumeOnlySe(int para1,LPVOID para2)
{

	int paraKosuu = para1;
	int* pData = (int*)para2;
	int ch = *pData;
	int deltaVolume = *(pData+1);

	if (m_skipNextCommandFlag == FALSE)
	{
		/*
		BOOL flg = TRUE;
		if (CheckMessageSkipFlag())
		{
			if (m_scriptSoundControl->CheckVolumeCommandOk(ch) == FALSE)
			{
				flg = FALSE;
			}
		}
*/

		if (m_scriptSoundControl->CheckVolumeCommandOk(ch))
//		if (flg)
		{

			int vol = GetSystemParam(NNNPARAM_SOUNDVOLUME);
			vol += deltaVolume;
			if (vol < 0) vol = 0;
			if (vol > 100) vol = 100;

			if (deltaVolume == -101) vol = 1;

			m_scriptSoundControl->SetVolume(ch,vol,m_nextFadeSe);
			m_scriptSoundControl->SetLoopWork(ch,2,deltaVolume);

		}
	}

#if defined _DEBUG
	char mes[1024];
	sprintf_s(mes,1024,"\n VolumeOnlySe ch=%d vol=%d\n",ch,deltaVolume);
	OutputDebugString(mes);
#endif

	m_nextFadeSe = 0;
}

void CGameCallBack::SystemFunctionVolumeOnlyVoice(int para1,LPVOID para2)
{
	int paraKosuu = para1;
	int* pData = (int*)para2;
	int ch = *pData;
	int deltaVolume = *(pData+1);

	if (m_skipNextCommandFlag == FALSE)
	{
//		if (CheckMessageSkipFlag() == FALSE)
		/*
		BOOL flg = TRUE;
		if (CheckMessageSkipFlag())
		{
			if (m_scriptVoiceControl->CheckVolumeCommandOk(ch) == FALSE)
			{
				flg = FALSE;
			}
		}
*/

//		if (flg)
		if (m_scriptVoiceControl->CheckVolumeCommandOk(ch))
		{

			LPSTR name = &m_loopVoiceFileName[ch*64];


			int vol = deltaVolume;

			if (ch<2)
			{
				vol += GetSystemParam(NNNPARAM_VOICEVOLUME);
			}
			else	//ch<4
			{
				vol += GetSystemParam(NNNPARAM_SOUNDVOICEVOLUME);
			}
			vol += GetVoiceVolumeByName(name);




			if (vol < 0) vol = 0;
			if (vol > 100) vol = 100;

			if (deltaVolume == -101) vol = 1;

			m_scriptVoiceControl->SetVolume(ch,vol,m_nextFadeVoice);
			m_scriptVoiceControl->SetLoopWork(ch,2,deltaVolume);

///			m_scriptSoundControl->SetVolume(ch,vol,m_nextFadeSe);
		}
	}

	m_nextFadeVoice = 0;
}

void CGameCallBack::SystemFunctionNextFadeSe(int para1,LPVOID para2)
{
	int paraKosuu = para1;
	int* pData = (int*)para2;
	m_nextFadeSe = *pData;

#if defined _DEBUG
	char mes[1024];
	sprintf_s(mes,1024,"\nNextFadeSeFunction para=%d\n",m_nextFadeSe);
	OutputDebugString(mes);
#endif
}

void CGameCallBack::SystemFunctionNextFadeVoice(int para1,LPVOID para2)
{
	int paraKosuu = para1;
	int* pData = (int*)para2;
	m_nextFadeVoice = *pData;

	OutputDebugString("\nNextFadeVoiceFunction\n");
}

void CGameCallBack::SystemFunctionMusicVolumeOnly(int para1,LPVOID para2)
{
	int paraKosuu = para1;
	int* pData = (int*)para2;
	int vol = GetSystemParam(NNNPARAM_MUSICVOLUME);
	vol += *pData;
	if (vol < 1) vol = 1;
	if (vol > 100) vol = 100;
	int fadeTime = 0;
	if (paraKosuu> 1)
	{
		fadeTime = *(pData+1);
	}

	m_musicControl->FadeVolume(vol,fadeTime);
}


void CGameCallBack::SystemFunctionSound(int para1,LPVOID para2)
{
	int paraKosuu = para1;
	int* pData = (int*)para2;

	int senum = *pData;
	int ch = *(pData+1);

	if (senum == -1)
	{
		m_scriptSoundControl->Stop(ch,FALSE,m_nextFadeSe);
		m_scriptSoundControl->SetLoopFlag(ch,FALSE);


//		m_scriptSound[ch]->Stop();
//		m_loopSoundWork[ch*16] = FALSE;
	}

	if ((m_skipNextCommandFlag || CheckMessageSkipFlag()) && (m_autoMessage == 0))
	{
		m_scriptSoundControl->StopIfLoops(ch);
		m_scriptSoundControl->InvalidateVolumeCommand(ch);

//		//stop if looping
//		if (m_loopSoundWork[ch*16])
//		{
//			m_scriptSound[ch]->Stop();
//			m_loopSoundWork[ch*16] = FALSE;
//		}
	}
	else
	{
		if (senum != -1)
		{
			m_scriptSoundControl->SetLoopWorkParam(ch,senum,paraKosuu,pData);
/*
			int deltaVolume = 0;
			if (paraKosuu >=3) deltaVolume = *(pData+2);

			int loopFlag = 0;
			if (paraKosuu>=4) loopFlag = *(pData+3);

			int xyz[3];
			int xyz2[3];
			xyz[0] = 0;
			xyz[1] = 0;
			xyz[2] = 0;
			xyz2[0] = 0;
			xyz2[1] = 0;
			xyz2[2] = 0;
			int moveTime = 0;
			int dop = 0;

			if (paraKosuu >= 5) xyz[0] = *(pData+4);
			if (paraKosuu >= 6) xyz[1] = *(pData+5);
			if (paraKosuu >= 7) xyz[2] = *(pData+6);

			int sq = 0;
			for (sq=0;sq<3;sq++)
			{
				if (xyz[sq] >= 128) xyz[sq] -= 256;
			}

			if (paraKosuu >= 8) moveTime = *(pData+7);
				
			if (paraKosuu >= 9) xyz2[0] = *(pData+8);
			if (paraKosuu >= 10) xyz2[1] = *(pData+9);
			if (paraKosuu >= 11) xyz2[2] = *(pData+10);

			for (sq=0;sq<3;sq++)
			{
				if (xyz2[sq] >= 128) xyz2[sq] -= 256;
			}

			if (paraKosuu >= 12) dop = *(pData+11);
*/

			/*
			m_loopSoundWork[ch*16] = loopFlag;

			m_loopSoundWork[ch*16+1] = senum;
			m_loopSoundWork[ch*16+2] = deltaVolume;

			m_loopSoundWork[ch*16+3] = xyz[0];
			m_loopSoundWork[ch*16+4] = xyz[1];
			m_loopSoundWork[ch*16+5] = xyz[2];

			m_loopSoundWork[ch*16+6] = moveTime;

			m_loopSoundWork[ch*16+7] = xyz2[0];
			m_loopSoundWork[ch*16+8] = xyz2[1];
			m_loopSoundWork[ch*16+9] = xyz2[2];

			m_loopSoundWork[ch*16+10] = dop;
*/
			/*
			m_scriptSoundControl->SetLoopWork(ch,0,loopFlag);
			m_scriptSoundControl->SetLoopWork(ch,1,senum);
			m_scriptSoundControl->SetLoopWork(ch,2,deltaVolume);
			m_scriptSoundControl->SetLoopWork(ch,3,xyz[0]);
			m_scriptSoundControl->SetLoopWork(ch,4,xyz[1]);
			m_scriptSoundControl->SetLoopWork(ch,5,xyz[2]);
			m_scriptSoundControl->SetLoopWork(ch,6,moveTime);
			m_scriptSoundControl->SetLoopWork(ch,7,xyz2[0]);
			m_scriptSoundControl->SetLoopWork(ch,8,xyz2[1]);
			m_scriptSoundControl->SetLoopWork(ch,9,xyz2[2]);
			m_scriptSoundControl->SetLoopWork(ch,10,dop);
*/

			PlayScriptSe(ch);
		}
	}

	m_nextFadeSe = 0;
}

BOOL CGameCallBack::PlayScriptSe(int ch)
{
	if (CheckTotalVolumeOff()) return TRUE;

	if (GetSystemParam(NNNPARAM_SOUNDSWITCH))
	{
		m_scriptSoundControl->CalcuTeii(ch);
		/*
//		int loopFlag = m_loopSoundWork[ch*16+0];
//		int senum = m_loopSoundWork[ch*16+1];
//		int deltaVolume = m_loopSoundWork[ch*16+2];
		int loopFlag = m_scriptSoundControl->GetLoopWork(ch,0);
		int senum = m_scriptSoundControl->GetLoopWork(ch,1);
		int deltaVolume = m_scriptSoundControl->GetLoopWork(ch,2);

		int xyz[3];
//		xyz[0] = m_loopSoundWork[ch*16+3];
//		xyz[1] = m_loopSoundWork[ch*16+4];
//		xyz[2] = m_loopSoundWork[ch*16+5];
		xyz[0] = m_scriptSoundControl->GetLoopWork(ch,3);
		xyz[1] = m_scriptSoundControl->GetLoopWork(ch,4);
		xyz[2] = m_scriptSoundControl->GetLoopWork(ch,5);

//		int moveTime = m_loopSoundWork[ch*16+6];
		int moveTime = m_scriptSoundControl->GetLoopWork(ch,6);

		int xyz2[3];
//		xyz2[0] = m_loopSoundWork[ch*16+7];
//		xyz2[1] = m_loopSoundWork[ch*16+8];
//		xyz2[2] = m_loopSoundWork[ch*16+9];
		xyz2[0] = m_scriptSoundControl->GetLoopWork(ch,7);
		xyz2[1] = m_scriptSoundControl->GetLoopWork(ch,8);
		xyz2[2] = m_scriptSoundControl->GetLoopWork(ch,9);

//		int dop = m_loopSoundWork[ch*16+10];
		int dop = m_scriptSoundControl->GetLoopWork(ch,10);
*/

		int loopFlag = m_scriptSoundControl->GetLoopWork(ch,0);
		int senum = m_scriptSoundControl->GetLoopWork(ch,1);
		int deltaVolume = m_scriptSoundControl->GetLoopWork(ch,2);

		int vol = GetSystemParam(NNNPARAM_SOUNDVOLUME);
		vol += deltaVolume;
		if (vol<0) vol = 0;
		if (vol>100) vol = 100;

		if (deltaVolume == -101) vol = 1;


		LPSTR sefilename = m_seList->GetName(senum*2);

		char filename[256];
		wsprintf(filename,"se\\%s",sefilename);

		if (m_waveData->LoadSystemWave("se",sefilename) == FALSE) return FALSE;

//		m_scriptSound[ch]->Stop();
		m_scriptSoundControl->Stop(ch);

		int stereo = m_waveData->GetChannel();
		int sampleRate = m_waveData->GetSampleRate();
		int bitRate = m_waveData->GetBitRate();

		char* realPtr = (char*)(m_waveData->GetRealDataPtr());
		int realSize = m_waveData->GetRealDataSize();

//		m_scriptSound[ch]->SetData(realPtr,realSize,stereo,sampleRate,bitRate);
		m_scriptSoundControl->SetData(ch,realPtr,realSize,stereo,sampleRate,bitRate);
/*
		float fx = (float)xyz[0];
		float fy = (float)xyz[1];
		float fz = (float)xyz[2];
		fx *= 0.1f;
		fy *= 0.1f;
		fz *= 0.1f;

//		m_scriptSound[ch]->SetStartTeii(fx,fy,fz);
//		m_scriptSound[ch]->SetMoveTime(moveTime);
		m_scriptSoundControl->SetStartTeii(ch,fx,fy,fz);
		m_scriptSoundControl->SetMoveTime(ch,moveTime);
		if (moveTime > 0)
		{
			float fx2 = (float)xyz2[0];
			float fy2 = (float)xyz2[1];
			float fz2 = (float)xyz2[2];

			fx2 *= 0.1f;
			fy2 *= 0.1f;
			fz2 *= 0.1f;

//			m_scriptSound[ch]->SetEndTeii(fx2,fy2,fz2);
//			m_scriptSound[ch]->SetDoppler(dop);
			m_scriptSoundControl->SetEndTeii(ch,fx2,fy2,fz2);
			m_scriptSoundControl->SetDoppler(ch,dop);
		}

//		m_scriptSound[ch]->SetVolume(vol);
//		m_scriptSound[ch]->Play(loopFlag);
*/

		m_scriptSoundControl->SetVolume(ch,vol,m_nextFadeSe);
		m_scriptSoundControl->Play(ch,loopFlag,m_nextFadeSe);

		return TRUE;
	}
	return TRUE;
}


void CGameCallBack::SystemFunctionVoice(int para1,LPVOID para2,int defVoiceFlag)
{
	int paraKosuu = para1;
	int* pData = (int*)para2;

	int voiceNum = *pData;


	LPSTR name = m_preReceiveFileName;
	if (defVoiceFlag)
	{
		//check name is default name?
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		if (CheckNameIsSpecialVoice())
		{
			char names[256];
			if (name != NULL)
			{
				int ln = strlen(name);
				memcpy_s(names,256,name,ln+1);
				char c = names[3];
				c += 'a';
				c -= '0';
				names[3] = c;

				name = names;
			}
		}
	}







	int voicenum = *pData;
	int ch = *(pData+1);






	if (voiceNum != -1)
	{
		CCommonBackLog* backlog = (CCommonBackLog*)m_general[BACKLOG_MODE];
		if ((ch>=0) && (ch<=1))
		{
			backlog->AddVoice(name);
		}

		//set voice flag to system file

		//set voice flag
		int vcn = VoiceToCharaNumber(name);
		if (vcn != -1)
		{

			BOOL fff = FALSE;

			if ((m_skipNextCommandFlag == FALSE)  && (m_demoFlag == FALSE))
			{
				if (CheckMessageSkipFlag() == 0)
				{
					fff = TRUE;
				}
			}

			if (m_mustSetVoiceFlag) fff = TRUE;

			if (fff)
			{
				m_systemFile->SetVoice(vcn);
			}
		}
	}


	BOOL koukaonOnOkFlag = FALSE;
	if (ch >= 2)
	{
		koukaonOnOkFlag = m_koukaonOnseiDontStopFlag;
	}


	if (m_skipNextCommandFlag || CheckMessageSkipFlag())
	{
		//stop if looping
		if (m_autoMessage == 0)
		{
//			if (m_loopVoiceWork[ch*16])
			if (koukaonOnOkFlag == FALSE)
			{
				if (m_scriptVoiceControl->GetLoopWork(ch,0))
				{
					m_scriptVoiceControl->Stop(ch,FALSE,m_nextFadeVoice);
					m_scriptVoiceControl->SetLoopWork(ch,0,0);
				}
				else
				{
					if (ch < 2)
					{
						//dont stop
					}
					else
					{
						if (m_skipToScriptVoiceStopFlag)
						{
							if (m_scriptVoiceControl->GetLoopWork(ch,1) != -1)
							{
								m_scriptVoiceControl->Stop(ch,FALSE,m_nextFadeVoice);
								m_scriptVoiceControl->SetLoopWork(ch,1,-1);
								m_scriptVoiceControl->SetLoopFlag(ch,FALSE);
							}
						}
					}
				}
				
//				m_scriptVoice[ch]->Stop();
//				m_loopVoiceWork[ch*16] = FALSE;
			}
		}
	}


//	if ((m_skipNextCommandFlag == FALSE)  && (m_demoFlag == FALSE))
	if (m_skipNextCommandFlag == FALSE)
	{
		BOOL voiceOkFlag = TRUE;
		if (CheckMessageSkipFlag())
		{
			if (m_autoMessage == 0)
			{
				if (koukaonOnOkFlag == FALSE)
				{
					if (GetSystemParam(NNNPARAM_SKIPMODE) == 1)
					{
						voiceOkFlag = FALSE;
					}
					else
					{
						if (CheckMessageRead(m_lastMessageID))
						{
							voiceOkFlag = FALSE;
						}
					}
				}
			}
		}

		//check voice off


		if (m_noVoiceIsDefaultWait)
		{
			if (voiceOkFlag)
			{
				int vsw = 0;
				if (ch<2)
				{
					vsw = GetSystemParam(NNNPARAM_VOICESWITCH);
				}
				else
				{
					vsw = GetSystemParam(NNNPARAM_SOUNDVOICESWITCH);
				}

				if (CheckTotalVolumeOff()) vsw = 0;

				if (vsw)
				{
					if (voicenum != -1)
					{
						if (CheckVoiceOffByName(name))
						{
							voiceOkFlag = FALSE;
						}
					}
				}
				else
				{
					voiceOkFlag = FALSE;
				}
			}
		}




		if (voiceOkFlag)
		{
			if (voicenum == -1)
			{
				m_scriptVoiceControl->Stop(ch,FALSE,m_nextFadeVoice);
				m_scriptVoiceControl->SetLoopFlag(ch,FALSE);
//				m_scriptVoice[ch]->Stop();
//				m_loopVoiceWork[ch*16] = FALSE;
			}
			else
			{
				m_scriptVoiceControl->SetLoopWorkParam(ch,voicenum,GetVoiceVolumeByName(name),paraKosuu,pData);
/*
				int deltaVolume = 0;
				if (paraKosuu >=3) deltaVolume = *(pData+2);


				deltaVolume += GetVoiceVolumeByName(name);

				int loopFlag = 0;
				if (paraKosuu>=4) loopFlag = *(pData+3);


				int xyz[3];
				int xyz2[3];
				xyz[0] = 0;
				xyz[1] = 0;
				xyz[2] = 0;
				xyz2[0] = 0;
				xyz2[1] = 0;
				xyz2[2] = 0;
				int moveTime = 0;
				int dop = 0;

				if (paraKosuu >= 5) xyz[0] = *(pData+4);
				if (paraKosuu >= 6) xyz[1] = *(pData+5);
				if (paraKosuu >= 7) xyz[2] = *(pData+6);

				int sq = 0;
				for (sq=0;sq<3;sq++)
				{
					if (xyz[sq] >= 128) xyz[sq] -= 256;
				}

				if (paraKosuu >= 8) moveTime = *(pData+7);
				
				if (paraKosuu >= 9) xyz2[0] = *(pData+8);
				if (paraKosuu >= 10) xyz2[1] = *(pData+9);
				if (paraKosuu >= 11) xyz2[2] = *(pData+10);

				for (sq=0;sq<3;sq++)
				{
					if (xyz2[sq] >= 128) xyz2[sq] -= 256;
				}

				if (paraKosuu >= 12) dop = *(pData+11);
*/

/*
				m_loopVoiceWork[ch*16+0] = loopFlag;
				m_loopVoiceWork[ch*16+1] = voicenum;
				m_loopVoiceWork[ch*16+2] = deltaVolume;
				m_loopVoiceWork[ch*16+3] = xyz[0];
				m_loopVoiceWork[ch*16+4] = xyz[1];
				m_loopVoiceWork[ch*16+5] = xyz[2];
				m_loopVoiceWork[ch*16+6] = moveTime;
				m_loopVoiceWork[ch*16+7] = xyz2[0];
				m_loopVoiceWork[ch*16+8] = xyz2[1];
				m_loopVoiceWork[ch*16+9] = xyz2[2];
				m_loopVoiceWork[ch*16+10] = dop;
*/
				/*
				m_scriptVoiceControl->SetLoopWork(ch,0,loopFlag);
				m_scriptVoiceControl->SetLoopWork(ch,1,voicenum);
				m_scriptVoiceControl->SetLoopWork(ch,2,deltaVolume);
				m_scriptVoiceControl->SetLoopWork(ch,3,xyz[0]);
				m_scriptVoiceControl->SetLoopWork(ch,4,xyz[1]);
				m_scriptVoiceControl->SetLoopWork(ch,5,xyz[2]);
				m_scriptVoiceControl->SetLoopWork(ch,6,moveTime);
				m_scriptVoiceControl->SetLoopWork(ch,7,xyz2[0]);
				m_scriptVoiceControl->SetLoopWork(ch,8,xyz2[1]);
				m_scriptVoiceControl->SetLoopWork(ch,9,xyz2[2]);
				m_scriptVoiceControl->SetLoopWork(ch,10,dop);
*/




				if (ch<2)
				{
					m_messageHaveVoiceFlag = TRUE;
					m_messageVoiceLength = 7000;	//dummy用心
					m_loadVoiceLength = m_messageVoiceLength;
				}


				int fln = (int)strlen(name);
				if (fln>62)
				{
					fln = 62;	//over予防
#if defined _DEBUG
char mes998[256];
wsprintf(mes998,"[voicefilename too long error! %s]",name);
OutputDebugString(mes998);
#endif
				}

				memcpy(&m_loopVoiceFileName[ch*64],name,fln);
				m_loopVoiceFileName[ch*64+fln] = 0;
				m_loopVoiceFileName[ch*64+fln+1] = 0;

				if (PlayScriptVoice(ch))
				{
					if (ch<2)
					{
						m_messageVoiceLength = m_loadVoiceLength;
						m_voiceSpeakCount = m_messageVoiceLength;
						m_voiceSpeakFlag = TRUE;
					}
				}
			}
		}
	}

	m_nextFadeVoice = 0;
}


BOOL CGameCallBack::PlayScriptVoice(int ch)
{
	int loopFlag = m_scriptVoiceControl->GetLoopWork(ch,0);
	int voicenum = m_scriptVoiceControl->GetLoopWork(ch,1);
	int deltaVolume = m_scriptVoiceControl->GetLoopWork(ch,2);

	m_scriptVoiceControl->CalcuTeii(ch);

//	int loopFlag = m_loopVoiceWork[ch*16+0];
//	int voicenum = m_loopVoiceWork[ch*16+1];
//	int deltaVolume = m_loopVoiceWork[ch*16+2];

//	int xyz[3];

//	xyz[0] = m_loopVoiceWork[ch*16+3];
//	xyz[1] = m_loopVoiceWork[ch*16+4];
//	xyz[2] = m_loopVoiceWork[ch*16+5];
//	int moveTime = m_loopVoiceWork[ch*16+6];

//	int xyz2[3];
//	xyz2[0] = m_loopVoiceWork[ch*16+7];
//	xyz2[1] = m_loopVoiceWork[ch*16+8];
//	xyz2[2] = m_loopVoiceWork[ch*16+9];
//	int dop = m_loopVoiceWork[ch*16+10];

//	m_scriptVoice[ch]->Stop();
	m_scriptVoiceControl->Stop(ch);

	LPSTR name = &m_loopVoiceFileName[ch*64];

#if defined _DEBUG
char mes999[256];
wsprintf(mes999,"[VOICE %s deltavolume=%d]",name,deltaVolume);
OutputDebugString(mes999);
#endif

	BOOL flg = m_waveData->LoadPackedWave(name);
	if (flg == FALSE)
	{
		flg = m_waveData->LoadWave(name);
	}


	if (flg)
	{
		m_loadVoiceLength = m_waveData->GetLength();

		int stereo = m_waveData->GetChannel();
		int sampleRate = m_waveData->GetSampleRate();
		int bitRate = m_waveData->GetBitRate();

		char* realPtr = (char*)(m_waveData->GetRealDataPtr());
		int realSize = m_waveData->GetRealDataSize();

//		m_scriptVoice[ch]->SetData(realPtr,realSize,stereo,sampleRate,bitRate);
		m_scriptVoiceControl->SetData(ch,realPtr,realSize,stereo,sampleRate,bitRate);

/*
		float fx = (float)xyz[0];
		float fy = (float)xyz[1];
		float fz = (float)xyz[2];
		fx *= 0.1f;
		fy *= 0.1f;
		fz *= 0.1f;

		m_scriptVoice[ch]->SetStartTeii(fx,fy,fz);
		m_scriptVoice[ch]->SetMoveTime(moveTime);
		if (moveTime > 0)
		{
			float fx2 = (float)xyz2[0];
			float fy2 = (float)xyz2[1];
			float fz2 = (float)xyz2[2];

			fx2 *= 0.1f;
			fy2 *= 0.1f;
			fz2 *= 0.1f;

			m_scriptVoice[ch]->SetEndTeii(fx2,fy2,fz2);
			m_scriptVoice[ch]->SetDoppler(dop);
		}
*/

		int vsw = 0;
		if (ch<2)
		{
			vsw = GetSystemParam(NNNPARAM_VOICESWITCH);
		}
		else
		{
			vsw = GetSystemParam(NNNPARAM_SOUNDVOICESWITCH);
		}

		if (CheckTotalVolumeOff()) vsw = 0;

		if (vsw)
		{

			int vol = deltaVolume;

			//debug 2010-03-04
			//vol += GetVoiceVolumeByName(name);

			if (ch<2)
			{
				vol += GetSystemParam(NNNPARAM_VOICEVOLUME);
			}
			else	//ch<4
			{
				vol += GetSystemParam(NNNPARAM_SOUNDVOICEVOLUME);
			}

					
			if (vol<0) vol = 0;
			if (vol>100) vol = 100;

#if defined _DEBUG
char mes998[256];
wsprintf(mes998,"\n[VOICE 最終音量:%d]",vol);
OutputDebugString(mes998);
#endif

			if (deltaVolume == -101) vol = 1;

			if (CheckVoiceOffByName(name) == FALSE)
			{
				m_scriptVoiceControl->SetVolume(ch,vol,m_nextFadeVoice);
				m_scriptVoiceControl->Play(ch,loopFlag,m_nextFadeVoice);

//				m_scriptVoiceControl->SetVolume(ch,vol,0);
//				m_scriptVoiceControl->Play(ch,loopFlag);
//				m_scriptVoice[ch]->SetVolume(vol);
//				m_scriptVoice[ch]->Play(loopFlag);
			}
		}

		return TRUE;
	}
	else
	{
		if (m_loadVoiceErrorPrintFlag == 1)
		{
			MessageBox(m_hWnd,name,"Error LoadVoice",MB_ICONEXCLAMATION | MB_OK);
		}
		else if (m_loadVoiceErrorPrintFlag == 2)
		{
			char emes[256];
			wsprintf(emes,"Err LoadVoice:%s",name);
			AddDebugMessage(emes);
		}
	}

	return FALSE;
}


void CGameCallBack::SystemFunctionMusic(int para1,LPVOID para2)
{
	int paraKosuu = para1;
	int* pData = (int*)para2;

	int musicNumber = *(pData+0);

	int fadeOut = -1;
	int loop = 0;
	int vol = -9999;
	int fadeIn = -1;

	if (paraKosuu>=2) loop = *(pData+1);
	if (paraKosuu>=3) vol = *(pData+2);
	if (paraKosuu>=4) fadeIn = *(pData+3);
	if (paraKosuu>=5) fadeOut = *(pData+4);

	if (musicNumber > 0)
	{
		BOOL fff = FALSE;
		if ((m_skipNextCommandFlag == FALSE) || (m_skipEffectCommandFlag == FALSE))
		{
			fff = TRUE;
		}

		if (m_mustSetMusicFlag) fff = TRUE;

		if (fff)
		{
			m_systemFile->SetMusic(musicNumber-1);
		}

		m_lastMusicNumber = musicNumber-1;
		m_musicKaisuu = loop;
	}

	if ((m_skipNextCommandFlag == FALSE) || (m_skipEffectCommandFlag == FALSE))
	{


		if (musicNumber == -1)
		{
			if (paraKosuu>=2) fadeOut = *(pData+1);
			
			StopMusic(fadeOut);
		}
		else if (musicNumber == -2)
		{
			//change volume only
			if (paraKosuu >= 2)
			{
				int deltaVolume = *(pData+1);
				//change music volume only
				int vol3 = GetSystemParam(NNNPARAM_MUSICVOLUME);
				vol3 += deltaVolume;
				if (vol3<1) vol3 = 1;
				if (vol3>100) vol3 = 100;

				m_musicControl->ChangeVolume(vol3);
//					m_waveMusic[m_useWaveMusicNumber]->ChangeVolume(vol3);
			}
		}
		else
		{
			if (GetSystemParam(NNNPARAM_MUSICSWITCH))
			{
				PlayMusic(musicNumber-1,loop,vol,fadeIn,fadeOut);
			}
			else
			{
				m_lastMusicNumber = musicNumber-1;
			}
		}
	}
}

void CGameCallBack::SystemFunctionStartKoma(int para1,LPVOID para2)
{
	//if have message ID then read flag,and F4


	int paraKosuu = para1;
	if (paraKosuu>0)
	{
		int* pData = (int*)para2;
		int id = *pData;
		if (id != -1)
		{
			if (m_skipNextCommandFlag)
			{
				if (m_skipF4Mode)
				{
					if (m_skipEffectCommandFlag)
					{
						if (CheckMessageRead(id) == FALSE)
						{
							m_skipEffectCommandFlag = FALSE;
						}
					}
				}
			}
		}


		int nextType = 3;
		int nextWindowMode = -1;

		if (paraKosuu>1)
		{
			nextType = *(pData+1);
			if (paraKosuu>2)
			{
				nextWindowMode = *(pData+2);
			}
		}

		int winFlag = FALSE;
		if (nextType == 0) winFlag = TRUE;
		m_nextMessageWindowPrintMode = nextWindowMode;
		m_nextMessageType = nextType;


		if (nextWindowMode == 1) winFlag = FALSE;
		if (nextWindowMode == 2) winFlag = TRUE;

		m_messageWindowPrintFlag = winFlag;
	}
}

void CGameCallBack::SystemFunctionStartMessage(int para1,LPVOID para2)
{
	//if have message ID then read flag,and F4


	int paraKosuu = para1;
	if (paraKosuu>0)
	{
		int* pData = (int*)para2;
		int id = *pData;

		if (id >= 0)
		{
			m_lastMessageID = id;
		}

		if (id != -1)
		{
			if (m_skipNextCommandFlag)
			{
				if (m_skipF4Mode)
				{
					if (CheckMessageRead(id) == FALSE)
					{
						m_skipNextCommandFlag = FALSE;
						m_skipEffectCommandFlag = FALSE;
					}
				}
			}
		}

		if (paraKosuu>1)
		{
			int md = *(pData+1);
			if (md == 0) m_nextMessageWindowPrintMode = -1;
			if (md == 1) m_nextMessageWindowPrintMode = 0;
			if (md == 2) m_nextMessageWindowPrintMode = 1;
		}
		else
		{
			m_nextMessageWindowPrintMode = -1;
		}
	}



	m_messageHaveVoiceFlag = FALSE;

}

void CGameCallBack::SystemFunctionChangeMessageFontSizeType(int para1,LPVOID para2)
{
	SetWindowNumberByFontSize(para1);
}


void CGameCallBack::SystemFunctionRenameLayer(int para1,LPVOID para2)
{
	m_renameLayer = para1;
}


void CGameCallBack::SystemFunctionSetCGByVar(int para1,LPVOID para2)
{
	int paraKosuu = para1;
	int* pData = (int*)para2;

	int checkVar = *(pData+3);
	int checkData = *(pData+4);

	if ((checkData == 0) || (checkData == 1))
	{
		int vd = GetVarData(checkVar);
		if ((vd == 0) || (vd == 1))
		{
			SystemFunctionSetCG(3,para2);
		}
	}
	else
	{
		if (GetVarData(checkVar) == checkData)
		{
			SystemFunctionSetCG(3,para2);
		}
	}
}

void CGameCallBack::SystemFunctionSetVar(int para1,LPVOID para2)
{
	int paraKosuu = para1;
	int* pData = (int*)para2;

	int varNumber = *(pData+0);
	int varData = *(pData+1);
	SetVarData(varNumber,varData);
}

void CGameCallBack::SystemFunctionVarControlLayer(int para1,LPVOID para2)
{
	int paraKosuu = para1;
	int* pData = (int*)para2;

	int layer = *(pData+0);
	int var = *(pData+1);

	m_varControlLayer[layer] = (short)var;
}

void CGameCallBack::SystemFunctionFace(int para1,LPVOID para2)
{
	int paraKosuu = para1;
	int* pData = (int*)para2;

	int face = *(pData+0);
	int type = *(pData+1);
	if (type < 0) type = 0;

	if (m_faceControl != NULL)
	{
		m_faceControl->ChangeFace(face,type);
	}
}

void CGameCallBack::SystemFunctionMustFace(int para1,LPVOID para2)
{
	int paraKosuu = para1;
	int* pData = (int*)para2;

	int mustFace = *(pData+0);

	if (m_faceControl != NULL)
	{
		m_faceControl->MustFace(mustFace);
	}
}

void CGameCallBack::SystemCommandPrint(int para1,LPVOID para2,int para3)
{
	//get and set para
	m_messageWindowPrintFlag = TRUE;
	ChangeMessageWindowModeByNext();

	CCommonPrintMessage* mesObj = (CCommonPrintMessage*)m_general[PRINTMESSAGE_MODE];

	LPSTR mes = (LPSTR)para2;

	mesObj->SetMessageMode(CODE_SYSTEMCOMMAND_PRINT,(m_sptFileNumber[m_scriptRunMode]<<16) | (para1 & 0xffff),mes,para3);
	m_lastMessageID = para1;

	if (m_skipNextCommandFlag == FALSE)
	{
		if (GetGameMode() != PRINTMESSAGE_MODE)
		{
			SetReturnCode(PRINTMESSAGE_MODE);
		}
		CAreaControl::SetNextAllPrint();
	}
	else
	{
		SetMessageReadSkipMode(para1);
	}
}


void CGameCallBack::SystemCommandLPrint(int para1,LPVOID para2,int para3)
{
	//get and set para
	m_messageWindowPrintFlag = FALSE;
//	m_messageWindowPrintFlag = TRUE;
	ChangeMessageWindowModeByNext();


	CCommonPrintMessage* mesObj = (CCommonPrintMessage*)m_general[PRINTMESSAGE_MODE];

	LPSTR mes = (LPSTR)para2;

	mesObj->SetMessageMode(CODE_SYSTEMCOMMAND_LPRINT,(m_sptFileNumber[m_scriptRunMode]<<16) | (para1 & 0xffff),mes,para3);
	m_lastMessageID = para1;

	if (m_skipNextCommandFlag == FALSE)
	{
		if (GetGameMode() != PRINTMESSAGE_MODE)
		{
			SetReturnCode(PRINTMESSAGE_MODE);
		}
		CAreaControl::SetNextAllPrint();
	}
	else
	{
		SetMessageReadSkipMode(para1);
	}


//		ResetAllShakin();
}

void CGameCallBack::SystemCommandAppend(int para1,LPVOID para2,int para3)
{
	//get and set para
//	m_messageWindowPrintFlag = FALSE;
	ChangeMessageWindowModeByNext();


	CCommonPrintMessage* mesObj = (CCommonPrintMessage*)m_general[PRINTMESSAGE_MODE];

	LPSTR mes = (LPSTR)para2;

	mesObj->SetMessageMode(CODE_SYSTEMCOMMAND_APPEND,(m_sptFileNumber[m_scriptRunMode]<<16) | (para1 & 0xffff),mes,para3);
	m_lastMessageID = para1;

	if (m_skipNextCommandFlag == FALSE)
	{
		if (GetGameMode() != PRINTMESSAGE_MODE)
		{
			SetReturnCode(PRINTMESSAGE_MODE);
		}
		CAreaControl::SetNextAllPrint();
	}
	else
	{
		SetMessageReadSkipMode(para1);
	}


//		ResetAllShakin();
}


void CGameCallBack::SetMessageReadSkipMode(int mes,int sptNum)
{
	if (m_mustMessageReadSkip)
	{
		SetMessageRead(mes,sptNum);
	}
}

void CGameCallBack::SystemCommandDraw(int para1,LPVOID para2)
{
//		m_messageWindowPrintFlag = TRUE;
	ChangeMessageWindowModeByNext();


	CCommonPrintMessage* mesObj = (CCommonPrintMessage*)m_general[PRINTMESSAGE_MODE];
	int* pData = (int*)para2;
	int count = *pData;

	if (CheckBackScriptMode() == FALSE)
	{
		if (count == 0)
		{
			mesObj->SetDrawMode(count);
			mesObj->Print();
		}
		else
		{
			mesObj->SetDrawMode(count);

			if (m_skipNextCommandFlag == FALSE)
			{
//				m_returnCode[m_modalLevel] = PRINTMESSAGE_MODE;
				if (GetGameMode() != PRINTMESSAGE_MODE)
				{
					SetReturnCode(PRINTMESSAGE_MODE);
				}
				CAreaControl::SetNextAllPrint();
			}
		}
	}
	else
	{
		m_backExecClass->SetDrawMode(count);
		if (count == 0) m_backExecClass->Print();
	}
}

void CGameCallBack::SystemCommandSelect(int para1,LPVOID para2)
{
	m_messageWindowPrintFlag = FALSE;

	CCommonSelectMessage* selObj = (CCommonSelectMessage*)m_general[SELECTMESSAGE_MODE];
	int kosuu = para1;
	
	selObj->SetBackLogMessage();

//		AddBackLogMessage("　");
//		AddBackLogMessage("#足選択肢",64,192,255);



	int* strPtr = (int*)para2;
	int selKosuu = *strPtr;
	strPtr++;
	int mesKosuu = *strPtr;
	strPtr++;
//		selObj->SetMessageKosuu(kosuu);
	selObj->SetMessageKosuu(selKosuu,mesKosuu);
	

//		m_lastSelectID = strPtr[kosuu];
	m_lastSelectID = strPtr[selKosuu+mesKosuu];

	int specialFlag = *(strPtr+selKosuu+mesKosuu+2);
	selObj->SetSpecialFlag(specialFlag);


	CExecScript* lpScript = GetScript();


	for (int i=0;i<selKosuu+mesKosuu;i++)
	{
		LPSTR mes = lpScript->GetStringPtr(strPtr[i]);
		if (i<mesKosuu) mes++;
		selObj->SetMessageData(i,mes);
	}

	int timeLimit = *(strPtr+selKosuu+mesKosuu);
	int autoSelect = *(strPtr+selKosuu+mesKosuu+1);
//	int specialFlag = *(strPtr+selKosuu+mesKosuu+2);

	if (autoSelect == 0)
	{
		autoSelect = selKosuu+1;
	}
	selObj->SetTimeLimit(timeLimit,autoSelect);
	selObj->SetSpecialFlag(specialFlag);


	m_skipNextCommandFlag = FALSE;
	m_skipEffectCommandFlag = FALSE;
	m_skipToFilmEndFlag = FALSE;
	m_skipToFilmEndEnable = FALSE;

//		m_returnCode[m_modalLevel] = SELECTMESSAGE_MODE;
	SetReturnCode(SELECTMESSAGE_MODE);
}

void CGameCallBack::SystemFunctionFilmName(int para1,LPVOID para2)
{
	LPSTR filmname = (LPSTR)para2;
	int ln = (int)strlen(filmname);
	if (ln>62) ln = 62;
	memcpy(m_lastFilmName,filmname,ln);
	m_lastFilmName[ln] = 0;
	m_lastFilmName[ln+1] = 0;
}

void CGameCallBack::SystemFunctionStoryName(int para1,LPVOID para2)
{
	LPSTR storyname = (LPSTR)para2;
	int ln = (int)strlen(storyname);
	if (ln>62) ln = 62;
	memcpy(m_lastStoryName,storyname,ln);
	m_lastStoryName[ln] = 0;
	m_lastStoryName[ln+1] = 0;
}

void CGameCallBack::SystemFunctionLoadDWQ(int para1,LPVOID para2)
{
	if ((m_skipNextCommandFlag == FALSE) || (m_skipEffectCommandFlag == FALSE))
	{
		int layer = para1;
		LPSTR mes = (LPSTR)para2;

		CPicture* pic = m_effect->GetPicture(layer);


		char filename[256+64];
		char c1 = *mes;
		char c2 = *(mes+1);
		wsprintf(filename,"__\\%s",mes);
		filename[0] = c1;
		filename[1] = c2;

		char filename2[256+64];

		BOOL renameFlag = FALSE;


		if (m_varControlLayer[layer] != 0)
		{
			int d = GetVarData(m_varControlLayer[layer]);
			if (d > 1)
			{
				wsprintf(filename2,"__\\%s__%d",mes,d);
				filename2[0] = c1;
				filename2[1] = c2;
				renameFlag = TRUE;
			}
		}

		if (m_renameLayerVarNumber != -1)
		{
			if (m_renameLayer != 0)
			{
				if (m_renameLayer & (1<<layer))
				{
					//rename!!
					int d = GetVarData(m_renameLayerVarNumber);
					if (d > 0)
					{
						if (d < m_renameTagKosuu)
						{
							LPSTR renameTag = m_renameTag + (d-1)*64;

							if ((*renameTag) != 0)
							{
								wsprintf(filename2,"__\\%s%s",mes,renameTag);
							}
							else
							{
								wsprintf(filename2,"__\\%s%d",mes,d);
							}
						}
						else
						{
							wsprintf(filename2,"__\\%s__%d",mes,d);
						}

						filename2[0] = c1;
						filename2[1] = c2;
						renameFlag = TRUE;
					}
				}
			}
		}




		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@たぶんバグってる

//		if ((c1>='A') && (c1<='Z')) c1 -= 32;
//		if ((c2>='A') && (c2<='Z')) c2 -= 32;


		if ((m_dontLoadDWQ[layer] & 1)== 0)
		{
			m_lastLoadLayer = layer;

			if (renameFlag)
			{
				if (pic->LoadDWQ(filename2) == FALSE)
				{
					if (m_varControlLoadDWQErrorPrint)
					{
						MessageBox(NULL,filename2,"SystemCommand LOADDWQ ERROR",MB_OK);
					}
					else
					{
						if (pic->LoadDWQ(filename) == FALSE)
						{
							MessageBox(NULL,filename,"SystemCommand LOADDWQ ERROR",MB_OK);
						}
					}
				}
			}
			else
			{
				if (pic->LoadDWQ(filename) == FALSE)
				{
		//		MessageBox(NULL,mes,"SystemCommand LOADDWQ ERROR",MB_OK);
					MessageBox(NULL,filename,"SystemCommand LOADDWQ ERROR",MB_OK);
				}
			}
		}



//		if (m_cutinFlag)
//		{
//			CCommonPrintMessage* obj = (CCommonPrintMessage*)(m_general[PRINTMESSAGE_MODE]);
//			if (obj != NULL)
//			{
//				obj->SetCutinFile(layer,mes);
//			}
//		}


		if ((m_dontLoadDWQ[layer] & 2)== 0)
		{
			m_effect->SetLayerScript(layer,layer);
		}
		else
		{
			RECT from;
			RECT to;
			RECT dst;
			m_effect->GetMyRect(layer,2,&from);
			m_effect->GetMyRect(layer,3,&to);
			m_effect->GetMyRect(layer,5,&dst);

			m_effect->SetLayerScript(layer,layer);
			
			m_effect->SetMyRect(layer,2,&from);
			m_effect->SetMyRect(layer,3,&to);
			m_effect->SetMyRect(layer,5,&from);
		}

///@@@			PollStream();

//		RECT rc;
//		pic->GetPicSize(&rc);
//
//		for (int i=0;i<6;i++)
//		{
//			m_effect->SetMyRect(layer,i,&rc);
//		}
	}
}


void CGameCallBack::SystemFunctionPreLoadDWQ(int para1,LPVOID para2)
{
	if ((m_skipNextCommandFlag == FALSE) || (m_skipEffectCommandFlag == FALSE))
	{
		int layer = para1;
		LPSTR mes = (LPSTR)para2;

		CPicture* pic = m_effect->GetPicture(layer);


		char filename[256+64];
		char c1 = *mes;
		char c2 = *(mes+1);
		wsprintf(filename,"__\\%s",mes);

//		if ((c1>='A') && (c1<='Z')) c1 -= 32;
//		if ((c2>='A') && (c2<='Z')) c2 -= 32;

		filename[0] = c1;
		filename[1] = c2;

		if ((m_dontLoadDWQ[layer] & 1)== 0)
		{
			m_lastLoadLayer = layer;

			if (pic->LoadDWQ(filename) == FALSE)
			{
		//		MessageBox(NULL,mes,"SystemCommand LOADDWQ ERROR",MB_OK);
				MessageBox(NULL,filename,"SystemCommand PRELOADDWQ ERROR",MB_OK);
			}
		}
	}
}

void CGameCallBack::SystemFunctionSetEffectRect(int para1,LPVOID para2)
{
	RECT from;
	RECT to;

	int paraKosuu = para1-1;
	int* pData = (int*)para2;

	int layer = *pData;
	from.left = *(pData+1);
	from.top = *(pData+2);
	from.right = *(pData+3);
	from.bottom = *(pData+4);
	to.left = *(pData+5);
	to.top = *(pData+6);
	to.right = *(pData+7);
	to.bottom = *(pData+8);

	if ((m_dontLoadDWQ[layer] & 2)== 0)
	{
		m_effect->SetMyRect(layer,2,&from);
		m_effect->SetMyRect(layer,3,&to);
		m_effect->SetMyRect(layer,5,&from);
	}
}

void CGameCallBack::SystemFunctionClearAllEffect(int para1,LPVOID para2)
{
	m_effect->ClearAllEffect();

	for (int i=0;i<m_layerKosuuMax;i++)
	{
		m_varControlLayer[i] = 0;
	}


	CCommonPrintMessage* obj = (CCommonPrintMessage*)(m_general[PRINTMESSAGE_MODE]);
	if (obj != NULL)
	{
		obj->OnClearAllEffect();
	}

}

void CGameCallBack::SystemFunctionClearEffectLayer(int para1,LPVOID para2)
{
	int* pData = (int*)para2;
	int layer = *pData;
	m_effect->ClearEffect(layer);

	CCommonPrintMessage* obj = (CCommonPrintMessage*)(m_general[PRINTMESSAGE_MODE]);
	if (obj != NULL)
	{
		obj->OnClearEffect(layer);
	}

}

/*
void CGameCallBack::SystemFunctionNoMessageWindow(int para1,LPVOID para2)
{
	m_messageWindowPrintFlag = TRUE;
}
*/


/*
void CGameCallBack::SystemFunctionSetDemoFlag(int para1,LPVOID para2)
{
	int dontPlay = para1;
	if (dontPlay == 2) dontPlay = 0;
	SetDontPlay(dontPlay);
}
*/

/*
void CGameCallBack::SystemFunctionDebug(int para1,LPVOID para2)
{
	if (m_debugOkFlag)
	{
		AddDebugMessage((LPSTR)para2);
	}
}
*/


void CGameCallBack::SystemFunctionSetEffect(int para1,LPVOID para2)
{
	if ((m_skipNextCommandFlag == FALSE) || (m_skipEffectCommandFlag == FALSE))
	{
		int paraKosuu = para1-2;
		int* pData = (int*)para2;
		int layer = *pData;
		int effect = *(pData+1);
		if (effect != -1)
		{
			m_effect->SetEffectScript(layer,effect,paraKosuu,pData+2);
		}
		else
		{
			m_effect->ClearEffect(layer);		//いらんのでは??


			CCommonPrintMessage* obj = (CCommonPrintMessage*)(m_general[PRINTMESSAGE_MODE]);
			if (obj != NULL)
			{
				obj->OnClearEffect(layer);
			}


		}
	}
}

void CGameCallBack::SystemFunctionScript(int cmd,int para1,LPVOID para2)
{
	LPSTR sptfile = (LPSTR)para2;
	char filename[256];
	wsprintf(filename,"spt\\%s.spt",sptfile);

	if (cmd != CODE_CONTROL_SCRIPTJUMP)
	{
		if (m_scriptRunMode > 2)
		{
			//error!!
			MessageBox(m_hWnd,filename,"これ以上、下のスクリプトはよべません",MB_OK);
		}
		else
		{
			//set callscript serial
			m_scriptRunMode++;
		}
	}

	int newSptNumber = m_sptList->SearchName(sptfile);

	CExecScript* lpScript = GetScript();
	lpScript->LoadScript(filename);

	lpScript->SetPC(0);

	//m_sptFileNumber[m_scriptRunMode] = m_sptList->SearchName(sptfile);
	m_sptFileNumber[m_scriptRunMode] = newSptNumber;
	if (m_sptFileNumber[m_scriptRunMode] == -1) m_sptFileNumber[m_scriptRunMode] = 0;	//dummy	用心
}

void CGameCallBack::SystemCommandOverrap(int para1,LPVOID para2)
{
	if (CheckBackScriptMode() == FALSE)
	{




//			if (m_skipNextCommandFlag == FALSE)
		if ((m_skipNextCommandFlag == FALSE) || (m_skipEffectCommandFlag == FALSE))
		{
#if defined _TINYAN3DLIB_
			BeginGet(m_overrapPic2);
#endif

			m_effect->Print(FALSE,TRUE);

//??@@
			if (m_messageWindowPrintFlag)
			{
				if (m_nextMessageType == 0)
				{
					PrintMessageWindow(TRUE);
				}

			}


			if ((m_nextMessageType == 1) || (m_nextMessageType == 2))//lprint append
			{
				CCommonPrintMessage* mesObj = (CCommonPrintMessage*)m_general[PRINTMESSAGE_MODE];
				mesObj->CheckAndPrintFillWindow();
			}







			m_effect->Print(TRUE,TRUE);



			
			int paraKosuu = para1;
			int* pData = (int*)para2;

			m_overrapType = *pData;
			m_overrapLength = *(pData+1);
			m_overrapPic2->GetScreen();

			CCommonPrintMessage* mesObj = (CCommonPrintMessage*)m_general[PRINTMESSAGE_MODE];
			mesObj->SetOverrapMode(m_overrapType,m_overrapLength);
			//SetReturnCode(PRINTOVERRAP_MODE);
			if (GetGameMode() != PRINTMESSAGE_MODE)
			{
				SetReturnCode(PRINTMESSAGE_MODE);
			}
			CAreaControl::SetNextAllPrint();
#if defined _TINYAN3DLIB_
			EndGet();
#endif

		}
	}
	else
	{
#if defined _TINYAN3DLIB_
		BeginGet(m_overrapPic1);
#endif

		m_effect->Print(FALSE);
//@@
		if (m_messageWindowPrintFlag)
		{
			PrintMessageWindow(TRUE);
		}


		m_effect->Print(TRUE);
			
			
		int paraKosuu = para1;
		int* pData = (int*)para2;

		m_overrapType = *pData;
		m_overrapLength = *(pData+1);
		m_overrapPic2->GetScreen();
		m_backExecClass->SetOverrapMode();

#if defined _TINYAN3DLIB_
		EndGet();
#endif

//			SetReturnCode(PRINTOVERRAP_MODE);
	}
}

void CGameCallBack::SystemFunctionFrameControl(int para1,LPVOID para2)
{
	int paraKosuu = para1;	//1
	int* pData = (int*)para2;
	int frame = *pData;

	if (frame > 0)
	{
		SetFrameRate(frame);
	}

	if (frame == 0)
	{
		SetDefaultFrameRate();
	}
}

void CGameCallBack::SystemFunctionSetDefaultFrame(int para1,LPVOID para2)
{
	SetDefaultFrameRate();
}

//void CGameCallBack::SystemFunctionFilmTypeTime(int para1,LPVOID para2)
//{
//	char mes[256];
//	wsprintf(mes,"[typeTime=%d]",para1);
//	OutputDebugString(mes);
//}

/*
void CGameCallBack::SystemFunctionConfigMask(int para1,LPVOID para2)
{
	if (para1 > 0)
	{
		SetConfigMask(para1);
	}
	else if (para1<0)
	{
		SetConfigMask(0);
	}
}
*/

/*
void CGameCallBack::SystemFunctionSetWindowNumber(int para1,LPVOID para2)
{
	SetWindowNumberByScript(para1);
}
*/

/*
void CGameCallBack::SystemFunctionSetMouseNumber(int para1,LPVOID para2)
{
	SetMouseNumberByScript(para1);
}
*/

/*
void CGameCallBack::SystemFunctionSetCursorNumber(int para1,LPVOID para2)
{
	SetCursorNumberByScript(para1);
}
*/

/*
void CGameCallBack::SystemFunctionSetAutoMessage(int para1,LPVOID para2)
{
	if (para1 == -1) para1 = 0;
	m_autoMessage = para1;
}
*/

/*
void CGameCallBack::SystemFunctionSetCannotClick(int para1,LPVOID para2)
{
	if (para1 == -1) para1 = 0;
	m_cannotClick = para1;
}
*/

/*
void CGameCallBack::SystemFunctionSetCannotSkip(int para1,LPVOID para2)
{
	if (para1 == -1) para1 = 0;
	m_cannotSkip = para1;
}
*/

/*
void CGameCallBack::SystemFunctionSetOptionOff(int para1,LPVOID para2)
{
	if (para1 == -1) para1 = 0;
	m_optionOff = para1;
}
*/


void CGameCallBack::SystemFunctionCutin(int para1,LPVOID para2)
{
	m_cutinFlag = para1;
	CCommonPrintMessage* obj = (CCommonPrintMessage*)(m_general[PRINTMESSAGE_MODE]);
	if (obj != NULL)
	{
		obj->SetCutinMode(m_cutinFlag);
	}
}

void CGameCallBack::SystemFunctionMessageExpStatus(int para1,LPVOID para2)
{
	CCommonPrintMessage* obj = (CCommonPrintMessage*)(m_general[PRINTMESSAGE_MODE]);
	if (obj != NULL)
	{
		obj->SetMessageExpStatus(para1);
	}
}


void CGameCallBack::SystemFunctionFilmEndEnable(int para1,LPVOID para2)
{
	if (para1 == 1)
	{
		m_skipToFilmEndEnable = TRUE;
		//init skip button


	}
}

void CGameCallBack::SystemFunctionFilmExpStatus(int para1,LPVOID para2)
{
	OnFilmExpStatus(para1);
}



void CGameCallBack::ReceiveScriptCommand(int cmd, int para1, LPVOID para2,int para3)
{
	if (cmd == CODE_SYSTEMCOMMAND_PRINT) SystemCommandPrint(para1,para2,para3);
	if (cmd == CODE_SYSTEMCOMMAND_LPRINT) SystemCommandLPrint(para1,para2,para3);
	if (cmd == CODE_SYSTEMCOMMAND_APPEND) SystemCommandAppend(para1,para2,para3);
	if (cmd == CODE_SYSTEMCOMMAND_DRAW) SystemCommandDraw(para1,para2);
	if (cmd == CODE_SYSTEMCOMMAND_SELECT) SystemCommandSelect(para1,para2);
	
	if (cmd == CODE_SYSTEMFUNCTION_NOMESSAGEWINDOW)
	{
		m_messageWindowPrintFlag = TRUE;
	}

	if (cmd == CODE_SYSTEMFUNCTION_SETDEMOFLAG)
	{
		int dontPlay = para1;
		if (dontPlay == 2) dontPlay = 0;
		SetDontPlay(dontPlay);
	}


	if (cmd == CODE_SYSTEMFUNCTION_DEBUG)
	{
		if (m_debugOkFlag)
		{
			AddDebugMessage((LPSTR)para2);
		}
	}

	if (cmd == CODE_SYSTEMFUNCTION_FILMNAME) SystemFunctionFilmName(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_STORYNAME) SystemFunctionStoryName(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_FILMTYPETIME)
	{
		//nothing to do now version
	}
	
	if (cmd == CODE_SYSTEMFUNCTION_CONFIGMASK)
	{
		if (para1 > 0)
		{
			SetConfigMask(para1);
		}
		else if (para1<0)
		{
			SetConfigMask(0);
		}
	}

	if (cmd == CODE_SYSTEMFUNCTION_WINDOWNUMBER)
	{
		SetWindowNumberByScript(para1);
	}
	
	if (cmd == CODE_SYSTEMFUNCTION_MOUSENUMBER)
	{
		SetMouseNumberByScript(para1);
	}
	
	if (cmd == CODE_SYSTEMFUNCTION_CURSORNUMBER)
	{
			SetCursorNumberByScript(para1);
	}

	if (cmd == CODE_SYSTEMFUNCTION_AUTOMESSAGE)
	{
		if (para1 == -1) para1 = 0;
		m_autoMessage = para1;
		if (m_autoMessage > 0)
		{
			if (m_autoMessageCheckKillShift)
			{
				SetMessageSkipFlag(FALSE);
			}
		}
	}

	if (cmd == CODE_SYSTEMFUNCTION_CANNOTCLICK)
	{
		if (para1 == -1) para1 = 0;
		m_cannotClick = para1;
	}

	if (cmd == CODE_SYSTEMFUNCTION_CANNOTSKIP)
	{
		if (para1 == -1) para1 = 0;
		m_cannotSkip = para1;
		if (m_cannotSkip > 0)
		{
			if (m_cannotSkipCheckKillShift)
			{
				SetMessageSkipFlag(FALSE);
			}
		}

	}

	if (cmd == CODE_SYSTEMFUNCTION_OPTIONOFF)
	{
		if (para1 == -1) para1 = 0;
		m_optionOff = para1;
	}

	if (cmd == CODE_SYSTEMFUNCTION_CUTIN) SystemFunctionCutin(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_MESSAGEEXPSTATUS) SystemFunctionMessageExpStatus(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_FILMENDENABLE) SystemFunctionFilmEndEnable(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_FILMEXPSTATUS) SystemFunctionFilmExpStatus(para1,para2);

	if ((cmd == CODE_CONTROL_SCRIPT) || (cmd == CODE_CONTROL_SUBSCRIPT) || (cmd == CODE_CONTROL_SCRIPTJUMP))
	{
		SystemFunctionScript(cmd,para1,para2);
	}

	if (cmd == CODE_SYSTEMFUNCTION_LOADDWQ) SystemFunctionLoadDWQ(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_PRELOADDWQ) SystemFunctionPreLoadDWQ(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_CLEARALLEFFECT) SystemFunctionClearAllEffect(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_CLEAREFFECTLAYER) SystemFunctionClearEffectLayer(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_SETEFFECTRECT) SystemFunctionSetEffectRect(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_SETEFFECT) SystemFunctionSetEffect(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_PREPAREOVERRAP) SystemFunctionPrepareOverrap(para1,para2);
	if (cmd == CODE_SYSTEMCOMMAND_OVERRAP) SystemCommandOverrap(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_MUSIC) SystemFunctionMusic(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_SOUND) SystemFunctionSound(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_VOICE) SystemFunctionVoice(para1,para2,para3);
	if (cmd == CODE_SYSTEMFUNCTION_SETCG) SystemFunctionSetCG(para1,para2);

	if (cmd == CODE_SYSTEMFUNCTION_VOLUMEONLY_SE) SystemFunctionVolumeOnlySe(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_VOLUMEONLY_VOICE) SystemFunctionVolumeOnlyVoice(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_NEXTFADE_SE) SystemFunctionNextFadeSe(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_NEXTFADE_VOICE) SystemFunctionNextFadeVoice(para1,para2);

	if (cmd == CODE_SYSTEMFUNCTION_MUSICVOLUMEONLY) SystemFunctionMusicVolumeOnly(para1,para2);

	//削除
	if (cmd == CODE_SYSTEMFUNCTION_SETSCENE)
	{
		int paraKosuu = para1;
		int* pData = (int*)para2;
		int sceneNumber = *pData;
//		m_systemFile->SetScene(sceneNumber-1);
	}

	if (cmd == CODE_SYSTEMFUNCTION_SETFILM) SystemFunctionSetFilm(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_STARTKOMA) SystemFunctionStartKoma(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_STARTMESSAGE) SystemFunctionStartMessage(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_FRAMECONTROL) SystemFunctionFrameControl(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_SETDEFAULTFRAME) SystemFunctionSetDefaultFrame(para1,para2);

	if (cmd == CODE_SYSTEMFUNCTION_CHANGEMESSAGEFONTSIZETYPE) SystemFunctionChangeMessageFontSizeType(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_RENAMELAYER) SystemFunctionRenameLayer(para1,para2);

	if (cmd == CODE_SYSTEMFUNCTION_SETCGBYVAR) SystemFunctionSetCGByVar(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_SETVAR) SystemFunctionSetVar(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_VARCONTROLLAYER) SystemFunctionVarControlLayer(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_FACE) SystemFunctionFace(para1,para2);
	if (cmd == CODE_SYSTEMFUNCTION_MUSTFACE) SystemFunctionMustFace(para1,para2);
}


int CGameCallBack::VoiceToCharaNumber(LPSTR name)
{
	if (name == NULL) return -1;

	char c1 = *name;
	char c2 = *(name+1);

	c1 |= 0x20;
	c2 |= 0x20;

	int kosuu = m_charaNameList->GetNameKosuu();

	for (int i=2;i<kosuu;i+=2)
	{
		LPSTR pre = m_charaNameList->GetName(i);
		char c3 = *pre;
		c3 |= 0x20;

		if (c1 == c3)
		{
			char c4 = *(pre+1);
			c4 |= 0x20;
			if (c2 == c4)
			{
				return i / 2;
			}
		}
	}

	return -1;
}


//小文字大文字どちらでもきくようにしゅうせいする@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
BOOL CGameCallBack::CheckVoiceOffByName(LPSTR name)
{
	int cn = VoiceToCharaNumber(name);
	if (cn == -1) return FALSE;

	CCommonConfig* pConfig = (CCommonConfig*)(m_general[CONFIG_MODE]);
	int btnNum = cn;
	if (pConfig != NULL)
	{
		btnNum = pConfig->GetVoiceOffButtonNumberByTable(cn) - 1;
	}

	//ここでテーブルによる変換をいれる
	if (CheckVoiceFlag(btnNum)) return FALSE;

	return TRUE;
}

int CGameCallBack::GetVoiceVolumeByName(LPSTR name)
{
	int cn = VoiceToCharaNumber(name);
	if (cn == -1) return 0;

	CCommonConfig* pConfig = (CCommonConfig*)(m_general[CONFIG_MODE]);
	int btnNum = cn;
	if (pConfig != NULL)
	{
		btnNum = pConfig->GetVoiceOffButtonNumberByTable(cn) - 1;
	}
	if (btnNum < 0) return 0;

	int volSlider = m_systemFile->GetCharaVoiceVolumeSlider(btnNum);
	//slider to delta

	return volSlider * m_charaVoiceVolumeDelta;
}


void CGameCallBack::GetUserPara(int paraKosuu, int* paraPtr)
{
	if (paraKosuu>256) paraKosuu = 256;	//最大256こまで
	m_userParaKosuu = paraKosuu;

	//get parameters
	for (int j=0;j<m_userParaKosuu;j++)
	{
		m_userParam[j] = *(paraPtr+j);
	}
}


void CGameCallBack::PrintBackBuffer(void)
{
//	static int aaa = 0;
//	aaa++;
//	int* p = CMyGraphics::GetScreenBuffer();
//	CAllGeo::BoxFill(100,100,500,400,128,192,64);
//	for (int k=0;k<800*300;k++)
//	{
//		*p++ = 0x4080c0f0;
//	}




	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

#if defined _TINYAN3DLIB_
	return;
#endif


	int realWindowSizeX = m_viewControl->GetRealWindowSizeX();
	int realWindowSizeY = m_viewControl->GetRealWindowSizeY();

	int offsetX = (realWindowSizeX - m_windowSizeX) / 2;
	int offsetY = (realWindowSizeY - m_windowSizeY) / 2;

	//スピードアップさせる必要ありにゃ
	if (m_directDraw->Lock())
	{
		int* dst01 = (int*)(m_directDraw->GetSurfaceAddr());
		int lPitch01 = m_directDraw->GetLPitch();

		//int* src02 = (int*)CPicture::m_lpScreenBuffer;
		int* src02 = CMyGraphics::GetScreenBuffer();
		int lPitch02 = screenSizeX * sizeof(int);

		m_mmx->SetBufferParameter(src02,lPitch02,screenSizeX,screenSizeY);
		m_mmx->SetSurfaceParameter(dst01,lPitch01);




		if (CAreaControl::CheckAllPrintMode())
		{
			m_mmx->MMXPrint(m_bpp,0,0,screenSizeX,screenSizeY);
		}
		else
		{
			int n = CAreaControl::GetAreaKosuu();
			for (int i=0;i<n;i++)
			{
				int startX,startY,sizeX,sizeY;
				CAreaControl::GetArea(i,startX,startY,sizeX,sizeY);
				m_mmx->MMXPrint(m_bpp,startX,startY,sizeX,sizeY);
			}
		}

		m_directDraw->Unlock();
	}


}


void CGameCallBack::BltToFront(void)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	BOOL waitFlag = TRUE;
	if (m_noWaitVSync) waitFlag = FALSE;

#if defined _TINYAN3DLIB_
	return;
#endif

//	int offsetx = m_viewControl->GetViewOffsetX();
//	int offsety = m_viewControl->GetViewOffsetY();
//	offsetx = 0;
//	offsety = 0;

	int realWindowSizeX = m_viewControl->GetRealWindowSizeX();
	int realWindowSizeY = m_viewControl->GetRealWindowSizeY();

	if (CAreaControl::CheckAllPrintMode())
	{
		RECT srcRect = m_viewControl->GetSrcRect(0,0,realWindowSizeX,realWindowSizeY);
		RECT dstRect = m_viewControl->GetDstRect(0,0,realWindowSizeX,realWindowSizeY);
		if (m_notUseDirectDraw == 0)
		{
			m_directDraw->NiseFlip2(dstRect,srcRect, waitFlag);
		}
		else
		{
			m_myGraphics->NiseFlip(m_hWnd,0,0,realWindowSizeX,realWindowSizeY,waitFlag);
		}
	}
	else
	{
		int n = CAreaControl::GetAreaKosuu();
		for (int i=0;i<n;i++)
		{
			int startX,startY,sizeX,sizeY;
			CAreaControl::GetArea(i,startX,startY,sizeX,sizeY);
		//	startX += offsetx;
		//	startY += offsety;

			RECT srcRect = m_viewControl->GetSrcRect(startX,startY,sizeX,sizeY);
			RECT dstRect = m_viewControl->GetDstRect(startX,startY,sizeX,sizeY);


//			BOOL waitFlag = FALSE;
			if (i>0) waitFlag = FALSE;
			if (m_notUseDirectDraw == 0)
			{
				m_directDraw->NiseFlip2(dstRect,srcRect,waitFlag);
//				m_directDraw->NiseFlip2(startX,startY,sizeX,sizeY,waitFlag);
			}
			else
			{
				m_myGraphics->NiseFlip(m_hWnd,startX,startY,sizeX,sizeY,waitFlag);
			}
		}
	}
}

/*
void CGameCallBack::OptionAnime(int cnt)
{
	int type = 0;

	if (m_onOptionFlag) type = 1;
	if (m_optionButton != NULL) m_optionButton->CalcuAnime(cnt);
}


void CGameCallBack::SceneButtonAnime(int cnt)
{
	int type = 0;
	if (m_onSceneFlag) type = 1;

	if (m_sceneButton != NULL) m_sceneButton->CalcuAnime(cnt);
}
*/

/*
void CGameCallBack::PrintOption(void)
{

	if (CheckDemoMode()) return;
	if (CheckOptionOff()) return;

	int type = 0;

	if (m_onOptionFlag) type = 1;
///	if (m_optionButton != NULL) m_optionButton->Print(type);

	m_onOptionFlag = FALSE;
	m_optionFlag = FALSE;
}
*/


/*
void CGameCallBack::PrintSceneButton(void)
{
	if (CheckSceneMode() == FALSE) return;

	int type = 0;
	if (m_onSceneFlag) type = 1;

	if (m_sceneButton != NULL) m_sceneButton->Print(type);

	SetSceneButton(FALSE);
}
*/


void CGameCallBack::CalcuVoiceSpeak(int cnt)
{
	if (m_voiceSpeakFlag)
	{
		m_voiceSpeakCount -= cnt;
		if (m_voiceSpeakCount <= 0)
		{
			m_voiceSpeakCount = 0;
			m_voiceSpeakFlag = FALSE;
		}
	}
}


void CGameCallBack::EraseMouse(void)
{
	if (m_taihi != NULL)
	{
		m_taihi->Fuque(0);
	}
}


SIZE CGameCallBack::GetMiniCGSize(void)
{
	SIZE sz;
	sz.cx = m_miniCGSizeX;
	sz.cy = m_miniCGSizeY;
	return sz;
}




// 0:midi disable
// 1:cd disable
int CGameCallBack::GetConfigData(int n)
{
//	if (n == 0) return m_enableMidiButtonFlag;
//	if (n == 1) return m_enableCDButtonFlag;

	return 0;
}


int CGameCallBack::GetExtDataBlockSize(int extNumber)
{
	if ((extNumber >= 0) && (extNumber < m_extSaveDataKosuu + m_autoExtDataLoadKosuu +m_autoExtSubDataLoadKosuu))
	{
		return m_extSaveDataSizeTable[extNumber];
	}

	return 0;
}


void CGameCallBack::SetReturnCode(int code)
{
	m_returnCode[m_modalLevel] = code;
}

int CGameCallBack::GetReturnCode(void)
{
	return m_returnCode[m_modalLevel];
}


BOOL CALLBACK testproc(  HWND hwnd,      // 子ウィンドウのハンドル
  LPARAM lParam   // アプリケーション定義の値
)
{
	OutputDebugString("\n\n\n■ child window");
/*
	HDC hdc = GetDC(hwnd);
	RECT rc;
	SetRect(&rc,100,100,200,200);
	FillRect(hdc,&rc,(HBRUSH)GetStockObject(WHITE_BRUSH));
	ReleaseDC(hwnd,hdc);
*/

	return TRUE;
}




void CGameCallBack::ChangeMode(void)
{
	int oldGameMode = GetGameMode();

	CCommonGeneral* general = m_general[oldGameMode];

	if (oldGameMode == LOGO_MODE)
	{
		m_pastTime = 0;
		m_pastTime2 = 0;
		m_totalCount = 0;
		m_skipCount = 0;
		m_shakin = 0;
		m_shakin1 = 0;
		m_shakin2 = 0;
		m_shakin3 = 0;
		m_totalTime = 0;
	}

	general->GeneralEndMode();					//2004-01-13		追加
	

	int returnCode = GetReturnCode();
	int newGameMode = returnCode & 0xff;
	SetGameMode(newGameMode);

//	if (newGameMode > 0)
//	{
//		if (m_modeVar != -1)
//		{
//			SetVarData(m_modeVar,newGameMode);
//		}
//	}


	ChangeOmakeEnd(oldGameMode,newGameMode);

	general = m_general[newGameMode];
	if (general != NULL)
	{

		if (newGameMode == PRINTMOVIE_MODE)
		{
#if defined _TINYAN3DLIB_
			SetForegroundWindow(m_hWnd);
			SetFocus(m_hWnd);
#endif
		}

//			SetForegroundWindow(m_hWnd);
//			SetFocus(m_hWnd);


//			CTextureCacheControl::ReleaseAllTexture();
//			((CMyDirect3D*)m_myDirect3D)->ReleaseAllResource();

//			((CMyDirect3D*)m_myDirect3D)->ResetAndWait(m_systemFile->m_systemdata.fullScreenFlag);
			//

//			((CMyDirect3D*)m_myDirect3D)->CreateAllResource();
//			m_myGraphics->ReCreateAllShader();
//			m_effect->ReCreateAllShader();


			//clear
			if (1)
			{
//				InvalidateRect(m_hWnd,NULL,TRUE);
//				HDC hdc = GetDC(m_hWnd);
//				RECT rc;
//				SetRect(&rc,0,0,800,600);
//				FillRect(hdc,&rc,(HBRUSH)GetStockObject(BLACK_BRUSH));
//				ReleaseDC(m_hWnd,hdc);
			}







		general->GeneralInit();

		if (newGameMode == PRINTMOVIE_MODE)
		{
#if defined _TINYAN3DLIB_


		//	EnumChildWindows(m_hWnd,testproc,0);






			if (m_directDraw != NULL)
			{












//			CTextureCacheControl::ReleaseAllTexture();
//			((CMyDirect3D*)m_myDirect3D)->ReleaseAllResource();

//			((CMyDirect3D*)m_myDirect3D)->ResetAndWait(m_systemFile->m_systemdata.fullScreenFlag);
			//

//			((CMyDirect3D*)m_myDirect3D)->CreateAllResource();
//			m_myGraphics->ReCreateAllShader();
//			m_effect->ReCreateAllShader();






///				m_directDraw->OnActivate(TRUE);
			}
#endif
		}
	}
	ChangeOmakeInit(oldGameMode,newGameMode);
#if defined _DEBUG
	OutputDebugString("\nモードが変更されました");
#endif

	CAreaControl::SetNextAllPrint();
}


int CGameCallBack::GetGameMode(void)
{
	return GetGameMode(m_modalLevel);
}

int CGameCallBack::GetGameMode(int level)
{
	return m_gameMode[level];
}


void CGameCallBack::SetGameMode(int gameMode)
{
#if !defined _TINYAN3DLIB_
	CPicture::SetModeNumberForDebug(gameMode);
#endif

	m_gameMode[m_modalLevel] = gameMode;
	if (m_modalLevel == 0)
	{
		SetLastSaveOkGameMode(gameMode);
	}
}

/*
void CGameCallBack::SetThreadAddr(LPVOID addr)
{
	m_threadAddr = addr;
}

HANDLE CGameCallBack::GetThreadHandle(int level)
{
	if (level == -1) level = GetModalLevel();
	return m_threadHandle[level];
}

unsigned int CGameCallBack::GetThreadID(int level)
{
	if (level == -1) level = GetModalLevel();
	return m_threadID[level];
}
*/


void CGameCallBack::StartModeRoutine(int mode)
{
	CCommonGeneral* general = m_general[mode];
	if (general != NULL)
	{
		general->GeneralInit();
	}
}


void CGameCallBack::EndModeRoutine(int mode)
{
	CCommonGeneral* general = m_general[mode];
	if (general != NULL)
	{
		general->GeneralEndMode();
	}
}

int CGameCallBack::GetOmakeClassExistFlag(void)
{
	if (m_omakeClassSupport != NULL)
	{
		return m_omakeClassSupport->GetOmakeClassExistFlag();
	}

	return FALSE;
}


void CGameCallBack::ChangeOmakeClass(int oldMode,int newMode)
{
//OutputDebugString("[changeomakeclass]");
	ChangeOmakeEnd(oldMode,newMode);
	ChangeOmakeInit(oldMode,newMode);
}

void CGameCallBack::ChangeOmakeEnd(int oldMode,int newMode)
{
	int oldOmakeWork[MODE_MAX];
	int newOmakeWork[MODE_MAX];

	int i = 0;
	for (i=0;i<MODE_MAX;i++)
	{
		oldOmakeWork[i] = 0;
		newOmakeWork[i] = 0;
	}

	if (oldMode != -1)
	{
		for (i=0;i<OMAKEMODE_KOSUU;i++)
		{
			if (m_omakeClassSupport != NULL)
			{
				//int omake = m_omakeClass[oldMode][i] / 256;
				int omake = m_omakeClassSupport->GetOmakeClass(oldMode,i) / 256;
				if (omake != 0)
				{
					oldOmakeWork[omake] = omake;
				}
			}
		}
	}

	if (newMode != -1)
	{
		for (i=0;i<OMAKEMODE_KOSUU;i++)
		{
			if (m_omakeClassSupport != NULL)
			{
				int omake = m_omakeClassSupport->GetOmakeClass(newMode,i) / 256;
//				int omake = m_omakeClass[newMode][i] / 256;
				if (omake != 0)
				{
					newOmakeWork[omake] = omake;
				}
			}
		}
	}

	for (i=0;i<MODE_MAX;i++)
	{
		int oldOmake = oldOmakeWork[i];
		int newOmake = newOmakeWork[i];

		if ((oldOmake != 0) && (newOmake == 0))
		{
			CCommonGeneral* general = m_general[oldOmake];
			if (general != NULL) general->OmakeGeneralEndMode();
		}
	}
}


void CGameCallBack::ChangeOmakeInit(int oldMode,int newMode)
{
	int oldOmakeWork[MODE_MAX];
	int newOmakeWork[MODE_MAX];

	int i = 0;
	for (i=0;i<MODE_MAX;i++)
	{
		oldOmakeWork[i] = 0;
		newOmakeWork[i] = 0;
	}

	if (oldMode != -1)
	{
		for (i=0;i<OMAKEMODE_KOSUU;i++)
		{
//			int omake = m_omakeClass[oldMode][i] / 256;

			if (m_omakeClassSupport != NULL)
			{
				int omake = m_omakeClassSupport->GetOmakeClass(oldMode,i) / 256;

				if (omake != 0)
				{
					oldOmakeWork[omake] = omake;
				}
			}
		}
	}

	if (newMode != -1)
	{
		for (i=0;i<OMAKEMODE_KOSUU;i++)
		{
			if (m_omakeClassSupport != NULL)
			{
				int omake = m_omakeClassSupport->GetOmakeClass(newMode,i) / 256;

//			int omake = m_omakeClass[newMode][i] / 256;
				if (omake != 0)
				{
					newOmakeWork[omake] = omake;
				}
			}
		}
	}

	for (i=0;i<MODE_MAX;i++)
	{
		int oldOmake = oldOmakeWork[i];
		int newOmake = newOmakeWork[i];

		if ((oldOmake == 0) && (newOmake != 0))
		{
			CCommonGeneral* general = m_general[newOmake];
			if (general != NULL) general->OmakeGeneralInit();
		}
	}
}





void CGameCallBack::CalcuOmake(void)
{
	int parentMode = GetGameMode();

	for (int i=0;i<OMAKEMODE_KOSUU;i++)
	{
		if (m_omakeClassSupport != NULL)
		{
			//int dat = m_omakeClass[parentMode][i];
			int dat = m_omakeClassSupport->GetOmakeClass(parentMode,i);
			if (dat != 0)
			{
				int omake = dat / 256;
				int mode = dat & 0xff;
				if (mode & 2)
				{
					CCommonGeneral* general = m_general[omake];
					if (general != NULL)
					{
						BOOL b = FALSE;
						if (mode & 0x20) b = TRUE;
						general->OmakeGeneralCalcu(b);
					}
				}
			}
		}
	}
}


void CGameCallBack::PrintOmake(void)
{
	int parentMode = GetGameMode();

	for (int i=0;i<OMAKEMODE_KOSUU;i++)
	{
		if (m_omakeClassSupport != NULL)
		{
//			int dat = m_omakeClass[parentMode][i];
			int dat = m_omakeClassSupport->GetOmakeClass(parentMode,i);
			if (dat != 0)
			{
				int omake = dat / 256;
				int mode = dat & 0xff;
				if (mode & 4)
				{
					CCommonGeneral* general = m_general[omake];
					if (general != NULL)
					{
						BOOL b = FALSE;
						if (mode & 0x40) b = TRUE;
						general->OmakeGeneralPrint(b);
					}
				}
			}
		}
	}
}


int CGameCallBack::GeneralMainLoop(int cnt)
{
//	if (m_startupWindowMode)
//	{
//		m_startupWindowMode = 0;
//		ToFullScreen(TRUE);
//	}



	if (m_quitFlag)
	{
#if defined _MT
	CheckAndWaitMainThread();
//		SetEvent(m_threadControlHandle[0]);
//		WaitForSingleObject(m_threadControlHandle[1],1000*5);
#endif		
		return 0;
	}

#if !defined _TINYAN3DLIB_
	if (m_directDraw != NULL)
	{
		if (GetActiveWindow() == m_hWnd)
		{
			if (m_directDraw->Restore())
			{
				CAreaControl::SetNextAllPrint();
			}
		}
	}
#endif


	static int kkk = 0;
	kkk++;
	if (kkk == 3)
	{
		if (m_systemFile->m_systemdata.fullScreenFlag)
		{
//			ToWindowScreen(TRUE);
//			ToFullScreen(TRUE);
		}
	}


	if (m_adjustFullScreenLost)
	{
		if (m_systemFile->m_systemdata.fullScreenFlag)
		{
			if (m_adjustFullWait > 0)
			{
				m_adjustFullWait--;
				if (m_adjustFullWait <= 0)
				{
					ToWindowScreen();
				}
			}
			else
			{
				DEVMODE devMode;
				ZeroMemory(&devMode,sizeof(DEVMODE));
				devMode.dmSize = sizeof(DEVMODE);
				if (EnumDisplaySettings(NULL,ENUM_CURRENT_SETTINGS,&devMode))
				{
//					int checkX = CMyGraphics::GetScreenSizeX();
//					int checkY = CMyGraphics::GetScreenSizeY();
					int checkX = m_viewControl->GetRealWindowSizeX();
					int checkY = m_viewControl->GetRealWindowSizeY();

					int fs = devMode.dmFields & CDS_FULLSCREEN;

					if ((devMode.dmPelsWidth != checkX) || (devMode.dmPelsHeight != checkY))
		//			if ((devMode.dmDisplayFlags & CDS_FULLSCREEN) == 0)
					{
	//					static int aaa = 0;
	//					aaa++;

	//					if (aaa > 50*2)
	//					{
						if (fs == 0)
						{
							LogMessage("ロスト確認");
							m_adjustFullWait = 5;
			//				ToWindowScreen();
	//						char mes[1024];
	//						wsprintf(mes,"%d %d %d %d f:%d",devMode.dmPelsWidth,devMode.dmPelsHeight,checkX,checkY,fs);
	//						MessageBox(NULL,mes,"Test",MB_OK);
	//						aaa = 0;
						}
	//					}
					}
				}
			}
		}
	}


	if (m_backLogDisableCheckFlag)
	{
		if (m_backLogDisableCount > 0)
		{
			m_backLogDisableCount--;
		}


		SYSTEMTIME systemTime;
		GetSystemTime(&systemTime);
		int tm = systemTime.wSecond + systemTime.wMinute * 60 + systemTime.wHour * 60*60 + systemTime.wDay * 60*60*24;

		if (m_backLogDisableOldTime == 0)
		{
			m_backLogDisableOldTime = tm;
		}

		if ((tm - m_backLogDisableOldTime) >= m_backLogDisableCheckTime)
		{
			m_backLogDisableCount = m_backLogDisableTime;
			m_wheelMove = 0;
			m_wheelMoveFlag = FALSE;
			m_wheelDelta = 0;
			m_mouseStatus->SetWheel(0);

		}

		m_backLogDisableOldTime = tm;
	}



	m_shakinControl->BeginFrame(cnt);

	if (m_fukaPrintFlag) m_fukaPrint->SetStartTime((int)timeGetTime());

#if defined _TINYAN3DLIB_
	CMyDirect3D* myd3d = (CMyDirect3D*)m_myDirect3D;
	LPDIRECT3DDEVICE9 d3dDevice = myd3d->GetD3DDevice();
	BeginScene();
#endif

	StartMainLoop(cnt);


	if (m_scriptSoundControl != NULL)
	{
		m_scriptSoundControl->OnMainLoop(cnt);
	}

	if (m_scriptVoiceControl != NULL)
	{
		m_scriptVoiceControl->OnMainLoop(cnt);
	}

	m_optionButtonPrintYoyaku = FALSE;
	m_sceneButtonPrintYoyaku = FALSE;
	m_skipFilmButtonPrintYoyaku = FALSE;
//	m_quickSaveButtonPrintYoyaku = FALSE;
//	m_quickLoadButtonPrintYoyaku = FALSE;


	FrameControl(cnt);
	AdjustMouseZahyo();
	m_wheelMoveFlag = FALSE;
	
	//
	m_effect->SetMouseZahyo(m_mouseStatus->GetZahyo());


	CAreaControl::StartScene();
	YoyakuShori();

	SetReturnCode(-1);

	BeforeCalcu();
	CCommonGeneral* general = m_general[GetGameMode()];
	if (general != NULL) SetReturnCode(general->GeneralCalcu());
	AfterCalcu();

	BeforeOmakeCalcu();
	CalcuOmake();
	AfterOmakeCalcu();

	m_mouseStatus->TrigToMae();
	ClearAllKey();

#if !defined _TINYAN3DLIB_
	if (CAreaControl::CheckAllPrintMode())
	{
		if (m_floatingLayerFlashFlag)
		{
			Flush();
		}
		else
		{
			Erase();
		}
	}
	else
	{
		Erase();
	}
#endif

	BOOL movieFlag = FALSE;
	if (GetGameMode() == PRINTMOVIE_MODE) movieFlag = TRUE;


	if (movieFlag)
	{
		CCommonPrintMovie* pm = (CCommonPrintMovie*)(m_general[PRINTMOVIE_MODE]);
//		CCommonPrintMovie* pm = (CCommonPrintMovie*)(m_general[PRINTMESSAGE_MODE]);
		if (pm != NULL)
		{
			if (pm->CheckFirstFrame())
			{
				//movieFlag = FALSE;
		//		OutputDebugString("[x]");
			}
			else
			{
		//		OutputDebugString("[o]");
			}
		}
	}




	m_effect->BeginEffect();

	BeforePrint();

	PrintParentClass();

	if (general != NULL) general->GeneralPrint();


	if (m_debugOkFlag)
	{
		char dbgm[256];
		sprintf_s(dbgm,sizeof(dbgm),"遅れ：%d",m_shakinControl->GetShakinTime(0));
		m_message->PrintMessage(0,300,dbgm);
		sprintf_s(dbgm,sizeof(dbgm),"バックスクリプトモード：%d",m_backScriptModeFlag);
		m_message->PrintMessage(0,320,dbgm);
	}


	AfterPrint();

	BeforeOmakePrint();
	PrintOmake();
	AfterOmakePrint();

#if defined _TINYAN3DLIB_
	EndScene();

	//ここでTargetをもどすべきか？？？＠＠＠

	BeginScene(FALSE);
	myd3d->BufferToBackSurface();
#endif

//	OptionAnime();

	//popuplayers

	if (debugMusicNumberPrintFlag)
	{
		char dmes[256];
		sprintf_s(dmes,sizeof(dmes),"曲：%d %d",m_musicNumber,m_lastMusicNumber);
		m_message->PrintMessage(0,0,dmes);
	}

	//

	if (m_quickLoadDelay)
	{
		if (m_quickLoadYoyaku)
		{
			m_quickLoadYoyaku = 0;
			int cmdrt = ExpOptionCommand(LOAD_MODE);
			if (cmdrt == -1)
			{
				if (m_quickLoadErrorSound > 0)
				{
					PlaySystemSound(m_quickLoadErrorSound-1);
				}
			}
			else
			{
				if (m_quickLoadSound > 0)
				{
					PlaySystemSound(m_quickLoadSound-1);
				}
			}

		}
	}


	if (m_noticeFlag)
	{
		int noticeSound = m_notice->Print();
		if (noticeSound > 0)
		{
			PlaySystemSound(noticeSound-1);
		}
	}

	if (m_sceneButtonPrintYoyaku) PrintSceneButton();
///	if (m_calendarFlag) PrintCalendar();
	if (m_optionButtonPrintYoyaku) PrintOptionButton();
	if (m_skipFilmButtonPrintYoyaku) PrintSkipFilmButton();
//	if (m_quickSaveButtonPrintYoyaku) PrintQuickSaveButton();
//	if (m_quickLoadButtonPrintYoyaku) PrintQuickLoadButton();

	if (m_cursorFlag)
	{
		int picNum = 0;
		if (GetSystemParam(NNNPARAM_AUTOMODE)) picNum = 1;

		CCommonPrintMessage* pDoc = (CCommonPrintMessage*)m_general[PRINTMESSAGE_MODE];
		if (pDoc != NULL)
		{
			if (pDoc->CheckFullMessageMode())
			{
				picNum += 2;
			}
		}


		m_messageCursor->Calcu();
		m_messageCursor->Print(picNum);
		m_cursorFlag = FALSE;
	}


	POINT mouse = m_mouseStatus->GetZahyo();
	int mouseX = mouse.x;
	int mouseY = mouse.y;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if ((mouseX>=0) && (mouseX<screenSizeX) && (mouseY>=0) && (mouseY<screenSizeY))
	{
		if (m_gameMouse != NULL)
		{
			m_gameMouse->CalcuMouseAnime();
			if (m_onMiniGameArea)
			{
				m_gameMouse->CalcuMouseAnime(2);
				m_onMiniGameArea = FALSE;
			}
			if (m_gameMouseDontPrintFlag == FALSE)
			{
				m_gameMouse->Print(mouseX,mouseY);
			}
		}
	}
	m_gameMouseDontPrintFlag = FALSE;


	if (general != NULL) general->GeneralFinalExitRoutine();


	if (m_bossComingType > 0)
	{
		if (CheckBossMode())
		{
			PrintBossComing();
		}
	}

	if (m_debugVarFlag) PrintDebugBack();
	if (m_fukaPrintFlag) m_fukaPrint->PrintFuka();
	if (m_fpsPrintFlag)
	{
		if (m_fpsPrint != NULL)
		{
			m_fpsPrint->Print();
		}
	}

	BeforePrintBackBuffer();

//	if ((movieFlag == FALSE) && (debugdebug == 0)) PrintBackBuffer();
	if (movieFlag == FALSE)
	{
		if (m_3dMode == FALSE)
		{
#if !defined _TINYAN3DLIB_
			PrintBackBuffer();
#endif
		}
		else
		{
		}
	}

	BeforeFlip();
//	if ((movieFlag == FALSE) && (debugdebug == 0)) BltToFront();


#if defined _TINYAN3DLIB_
	EndScene();
#endif


#if !defined _TINYAN3DLIB_
	if (movieFlag == FALSE)
	{
		if (m_3dMode == FALSE)
		{
			BltToFront();
		}
		else
		{
		}
	}
#else

	if (GetGameMode() == PRINTMOVIE_MODE)
	{
		LPDIRECT3DDEVICE9 dev9 = myd3d->GetD3DDevice();
		//dev9->Clear();
	//	dev9->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR(rand() % 256),0.0f,0);

		//myd3d->Fill();
	}

	if (movieFlag == FALSE)
	{
		int gmmd = GetGameMode();
		//if (1)
		{
			myd3d->Present();
		}
	}

	BeginScene();
#endif

	AfterFlip();


	if (m_fuqueAllEffectYoyaku)
	{
#if defined _DEBUG
		OutputDebugString("\n\n復旧allエフェクト by 予約\n");
#endif
		FuqueAllEffect();
		m_fuqueAllEffectYoyaku = FALSE;
	}



	YoyakuExecRoutine();


	int returnCode = GetReturnCode();
	if (returnCode > 0)
	{
		if (returnCode == PRINTMOVIE_MODE)
		{

#if defined _TINYAN3DLIB_

	//	LPDIRECT3DDEVICE9 dev = ((CMyDirect3D*)m_myDirect3D)->GetD3DDevice();
	//	dev->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR(rand() % 256),0.0f,0);
	//	myd3d->Present();
#endif
		}


		BeforeChangeMode();
		ChangeMode();
		AfterChangeMode();

		//
//		if ((returnCode != PRINTMESSAGE_MODE) && (returnCode != PRINTOVERRAP_MODE))
		if (returnCode != PRINTMESSAGE_MODE)
//		if (1)
		{
			m_shakinControl->Clear();
		}
	}

	if (m_debugVarFlag) PrintDebugParam();

	if (m_debugOkFlag)
	{
		//print debug script-file

		if (m_noScriptFlag == FALSE)
		{
			PrintScriptFileName();
		}

		if (m_debugMessageKosuu>0)
		{
			HWND hWnd = GetGameHWND();
			HDC hdc = GetDC(hWnd);
			int oldBackMode = SetBkMode(hdc,OPAQUE);
			COLORREF oldTextColor = SetTextColor(hdc,0);
			SetBkColor(hdc,COLORREF(0x008000));

			for (int i=0;i<m_debugMessageKosuu;i++)
			{
				int putX = 16;
				int putY = 26*i + 32;
				LPSTR mes = m_debugMessage[i];
				int ln = (int)strlen(mes);




				SetTextColor(hdc,COLORREF(0x000000));
				TextOut(hdc,putX+1,putY+1,mes,ln);
				SetTextColor(hdc,COLORREF(0xFFFFFF));
				TextOut(hdc,putX,putY,mes,ln);
			}

			if (oldTextColor != CLR_INVALID) SetTextColor(hdc,oldTextColor);
			if (oldBackMode != 0) SetBkMode(hdc,oldBackMode);

			ReleaseDC(hWnd,hdc);
		}
	}


	CAreaControl::EndScene();


#if defined _TINYAN3DLIB_
	EndScene();






#endif

//	m_mouseStatus->TrigToMae();

//	m_wheelMoveFlag = FALSE;
//	m_calendarFlag = FALSE;

//	ClearAllKey();
//	ShakinHensai();

	m_totalCount++;

	if (m_wheelWaitCount>0) m_wheelWaitCount--;

	EndMainLoop();

	if (m_fukaPrintFlag) m_fukaPrint->CalcuFuka((int)timeGetTime());

	m_shakinControl->EndFrame();


#if defined _MT
//	CheckAndWaitMainThread();
#endif


	return 0;
}


void CGameCallBack::PrintParentClass(void)
{
	int printFlag[16];
	int modalLevel = GetModalLevel();

	int i = 0;
	for (i=0;i<16;i++)
	{
		printFlag[i] = 0;
	}

	for (i = modalLevel-1;i>=0;i--)
	{
		int flg = GetModalPrintMode(i);
		printFlag[i] = flg;
		if (flg != 1) break;
	}

	for (i=0;i<modalLevel;i++)
	{
		if (printFlag[i])
		{
			int parent = GetGameMode(i);
			CCommonGeneral* general = m_general[parent];
			if (general != NULL)
			{
				general->GeneralPrint();
			}
		}
	}
}


void CGameCallBack::SetModalPrintMode(int level, int md)
{
	m_modalPrintMode[level] = md;
}

int CGameCallBack::GetModalPrintMode(int level)
{
	return m_modalPrintMode[level];
}

void CGameCallBack::PlaySystemSound(int n,int volumeType)
{
	if (CheckTotalVolumeOff()) return;

	if (volumeType == 0)
	{
		if (GetSystemParam(NNNPARAM_SOUNDSWITCH) == 0) return;
	}
	else
	{
		if (GetSystemParam(NNNPARAM_VOICESWITCH) == 0) return;
	}

//	char mes[256];
//	wsprintf(mes,"システムサウンド:%d",n);
//	AddDebugMessage(mes);

	m_systemSound[m_useSystemSoundNumber]->Stop();

	m_useSystemSoundNumber++;
	m_useSystemSoundNumber %= 2;
	m_systemSound[m_useSystemSoundNumber]->Stop();


	CWaveData* wave = m_waveData;
	if (n <= -1)
	{
		return;

		//
	}
	else if ((n >=0) && (n < m_systemWaveLoadKosuu))
	{
		wave = m_systemWaveArray[n];
	}
	else
	{
		if (m_systemSeList == NULL) return;

		char filename[256];
		wsprintf(filename,"%s",m_systemSeList->GetName(n*2));
		if (wave->LoadSystemWave("sys",filename) == FALSE)
		{
//			MessageBox(NULL,"filename","error",MB_OK);
		}

//char mes[256];
//wsprintf(mes,"sound %d",n+1);
//MessageBox(NULL,mes,"sound",MB_OK);

	}

	int stereo = wave->GetChannel();
	int sampleRate = wave->GetSampleRate();
	int bitRate = wave->GetBitRate();

	char* realPtr = (char*)(wave->GetRealDataPtr());
	int realSize = wave->GetRealDataSize();

	m_systemSound[m_useSystemSoundNumber]->SetData(realPtr,realSize,stereo,sampleRate,bitRate);

	int vol = 0;
	if (volumeType == 0)
	{
		vol = GetSystemParam(NNNPARAM_SOUNDVOLUME);
	}
	else
	{
		vol = GetSystemParam(NNNPARAM_VOICEVOLUME);
		if (m_enableButtonVoiceCharaVolume)
		{
			vol += GetVoiceVolumeByName(m_systemSeList->GetName(n*2));
		}
	}

	m_systemSound[m_useSystemSoundNumber]->SetVolume(vol);
	m_systemSound[m_useSystemSoundNumber]->Play();
}


/*
void CGameCallBack::PlaySoundRoutine(CCommonWave* wave,int n)
{
return;//@@
	if (n == -1)
	{
		if (GetGameVolume(NNNPARAM_SOUNDVOLUME) != 0)
		{
			wave->StopWave();
		}
		return;
	}

	wave->StopWave();


	int vol = GetGameVolume(NNNPARAM_SOUNDVOLUME);
	if (vol != m_lastSoundVoiceVolume)
	{
		m_lastSoundVoiceVolume = vol;
		if (GetMusicMode() == 0)
		{
			m_mixer->SetWAVEVolume(vol);
		}
		else
		{
			if (m_directSound != NULL)
			{
				m_directSound->SetVolume(vol);
			}
		}
	}

	if (vol != 0)
	{
		wave->PlayWave();
	}
}
*/




BOOL CGameCallBack::CheckBackScriptMode(void)
{
	return m_backScriptModeFlag;
}

BOOL CGameCallBack::LoadBackScript(LPSTR filename)
{
	int n = m_sptList->SearchName(filename);
	if (n == -1)
	{
		MessageBox(m_hWnd,filename,"LOAD BACK SCRIPT ERROR",MB_OK);
		return FALSE;
	}
	BOOL b = m_backExecClass->LoadScript(n);

	m_backExecClass->ExecScript(TRUE);
	m_backExecClass->Calcu();
	return b;
}

BOOL CGameCallBack::CalcuBackScript(BOOL loopFlag)
{
	BOOL b = m_backExecClass->ExecScript(FALSE,loopFlag);
	m_backExecClass->Calcu();
	return b;
}

void CGameCallBack::PrintBackScript(void)
{
	m_backExecClass->Print();
}

void CGameCallBack::PrintBackScriptLayers(int startLayer,int endLayer)
{
	m_backExecClass->PrintLayers(startLayer,endLayer);
}

void CGameCallBack::RestartBackScript(void)
{
	m_backExecClass->ReStart();
}


int CGameCallBack::CalcuCommonBackButton(CMyMouseStatus* lpMouse)
{
	if (m_backButton == NULL) return -1;

	return -1;
}

void CGameCallBack::PrintCommonBackButton(BOOL mustPrintFlag, int deltaX ,int deltaY ,int patNum )
{
	if (m_backButton == NULL) return;
}

int CGameCallBack::CalcuCommonUpDownButton(CMyMouseStatus* lpMouse)
{
	if (m_upDown == NULL) return -1;

	return -1;
}

void CGameCallBack::PrintCommonUpDownButton(BOOL mustPrintFlag, int deltaX ,int deltaY ,int patNum )
{
	if (m_upDown == NULL) return;

}


void CGameCallBack::CreateCommonBackButton(void)
{

}

void CGameCallBack::PrintBossComing(void)
{
	//0:nothing
	//1:fill
	//2:pic
	//3～:special

	CAreaControl::SetNextAllPrint();
	if (m_bossComingType == 1)
	{
//		CPicture::FillScreen(m_bossComingColorR,m_bossComingColorG,m_bossComingColorB);
		CAllGraphics::FillScreen(m_bossComingColorR,m_bossComingColorG,m_bossComingColorB);
	}
	else if (m_bossComingType == 2)
	{
		m_bossComingPic->Put(0,0,FALSE);
	}
	else if (m_bossComingType == 3)	//How Many Pages(1-4)
	{
	}
}


void CGameCallBack::BossModeSoundOff(void)
{
	if (m_bossComingType > 0)
	{
//		if (m_wave != NULL)
//		{
//@@			m_wave->StopWave();
//		}
	}
}


////////////////////////////////////////////////////////////////////////////////
void CGameCallBack::SetupBossComing(void)
{
	m_bossComingType = 0;
	GetInitGameParam(&m_bossComingType,"bossComingType");
	m_bossComingColorR = 0;
	m_bossComingColorG = 0;
	m_bossComingColorB = 0;
	m_bossComingPic = NULL;
	if (m_bossComingType > 0)
	{
		GetInitGameParam(&m_bossComingColorR,"bossComingColorR");
		GetInitGameParam(&m_bossComingColorG,"bossComingColorG");
		GetInitGameParam(&m_bossComingColorB,"bossComingColorB");

		if (m_bossComingType == 2)
		{
			m_bossComingPic = new CPicture();
			LPSTR fname = "bosscome";
			GetInitGameString(&fname,"bossComingFileName");
			char filename[256];
			wsprintf(filename,"sys\\%s",fname);
			m_bossComingPic->LoadDWQ(filename);
		}
	}
}

void CGameCallBack::SetupFukaPrint(void)
{
	m_fukaPrintFlag = 0;
	m_fukaPrint = NULL;
	GetInitGameParam(&m_fukaPrintFlag,"fukaPrintFlag");
	if (m_fukaPrintFlag == 0) return;

	m_fukaPrint = new CFukaPrint(m_setup);
//	CPicture* lpPic = GetSystemPicture("nekofont");
//	m_fukaPic = GetSystemPicture("nekofont");
}

void CGameCallBack::SetupFpsPrint(void)
{
	m_fpsPrintFlag = 0;
	m_fpsPrint = NULL;
	GetInitGameParam(&m_fpsPrintFlag,"fpsPrintFlag");
	if (m_fpsPrintFlag == 0) return;

	m_fpsPrint = new CFpsPrint(m_setup);
//	CPicture* lpPic = GetSystemPicture("nekofont");
//	m_fukaPic = GetSystemPicture("nekofont");
}

void CGameCallBack::SetupAndCreateCommonBackButton(void)
{
	m_backButton = NULL;
	m_newBackButton = NULL;

	m_backButtonCreateFlag = 0;
	m_superBackButtonFlag = 1;
	m_superBackButtonSetup = NULL;

	GetInitGameParam(&m_backButtonCreateFlag,"createBackButtonFlag");

	if (m_backButtonCreateFlag)
	{
		CreateBackButton();

	//	GetInitGameParam(&m_superBackButtonFlag,"superBackButtonFlag");
	//	GetInitGameParam(&m_backSizeX,"backSizeX");
	//	GetInitGameParam(&m_backSizeY,"backSizeY");
	//	m_filenameBackButton = m_defaultBackButtonFileName;
	//	GetInitGameString(&m_filenameBackButton,"fileNameBackButton");

/*
		CPicture* lpBackPic = GetSystemPicture(m_filenameBackButton);
		m_backButton = new CBackButton();
		m_backButton->CreateBackButton(lpBackPic, m_backButtonPrintX,m_backButtonPrintY, m_backButtonSizeX,m_backButtonSizeY, TRUE, m_commonBG, FALSE,m_backButtonAnime);

		//sueprButton?

		m_superBackButtonFlag = 0;
		GetInitGameParam(&m_superBackButtonFlag,"superBackButtonFlag");
		if (m_superBackButtonFlag)
		{
			m_superBackButtonSetup = new CSuperButtonSetup(m_setup,"superBack");
		}
*/
	}

}



void CGameCallBack::CreateBackButton(void)
{
	/*
	m_superBackButtonFlag = 1;
	GetInitGameParam(&m_superBackButtonFlag,"superBackButtonFlag");	//現在1のみ有効なので注意


	m_backButtonPrintX = 0;
	m_backButtonPrintY = 0;

	GetInitGameParam(&m_backButtonPrintX,"backPrintX");
	GetInitGameParam(&m_backButtonPrintY,"backPrintY");

	m_backButtonSizeX = 55;
	m_backButtonSizeY = 38;

	GetInitGameParam(&m_backButtonSizeX,"backSizeX");
	GetInitGameParam(&m_backButtonSizeY,"backSizeY");

	LPSTR name = "ta_back_bt";
	GetInitGameString(&name,"fileNameBackButton");


	m_backButtonAnime = 1;
	m_backButtonType = 0;	//0:この設定でつくる 1:CGameからもらう

	GetInitGameParam(&m_backButtonAnime,"backButtonAnime");
//	GetInitGameParam(&m_backButtonType,"backButtonType");


	CPicture* lpBackPic = GetSystemPicture(name);
	m_createBackButton = new CBackButton();
	CPicture* bgPic = m_commonBG;
	if (m_backScriptFlag) bgPic = NULL;

	m_createBackButton->CreateBackButton(lpBackPic, m_backButtonPrintX,m_backButtonPrintY, m_backButtonSizeX,m_backButtonSizeY, TRUE, bgPic, FALSE,m_backButtonAnime);

	//superButton
	if (m_superBackButtonFlag)
	{
//			m_superBackButtonSetup = new CSuperButtonSetup(m_setup,"superBack");

		m_createBackButton->SetSuperMode(m_setup);
//			CMyCommonButton* button = m_createBackButton->GetCommonButton();
//			m_superBackButtonSetup->SetupButtonStatus(button);
	}

	m_back = m_createBackButton;
	*/
}

/*
int CGameCallBack::GetBGMVolume(void)
{
	return 1;
}
int CGameCallBack::SetBGMVolume(int vol)
{
	return 1;
}
BOOL CGameCallBack::CheckBGMOn(void)
{
	return FALSE;
}
void CGameCallBack::SetBGMOn(BOOL flg)
{
}
*/

void CGameCallBack::AddDebugMessage(LPSTR mes)
{
	if (mes == NULL) return;
	
	if (m_debugMessageKosuu >= 20)
	{
		for (int i=0;i<19;i++)
		{
			memcpy(m_debugMessage[i],m_debugMessage[i+1],256);
		}
		m_debugMessageKosuu = 19;
	}

	int ln = (int)strlen(mes);
	if (ln>254) ln = 254;
	memcpy(m_debugMessage[m_debugMessageKosuu],mes,ln);
	m_debugMessage[m_debugMessageKosuu][ln] = 0;
	m_debugMessage[m_debugMessageKosuu][ln+1] = 0;

	m_debugMessageKosuu++;
}


BOOL CGameCallBack::CreateCommonClass(int modeNumber)
{
	if ((modeNumber < 0) || (modeNumber >= 100)) return FALSE;

	if (m_general[modeNumber] != NULL) return FALSE;

	if (m_createModeDisableFlag[modeNumber]) return FALSE;


	CCommonGeneral* general = NULL;

	switch (modeNumber)
	{
	case NOTHING_MODE:
		general = new CCommonNothing(this);
		break;
	case LOGO_MODE:
		general = new CCommonLogo(this);
		break;
	case OPENING_MODE:
		general = new CCommonOpening(this);
		break;
	case TITLE_MODE:
		general = new CCommonTitle(this);
		break;
	case LOAD_MODE:
		general = new CCommonLoad(this);
		break;
	case SAVE_MODE:
		general = new CCommonSave(this);
		break;
	case BACKLOG_MODE:
		general = new CCommonBackLog(this);
		break;
	case LISTENBGM_MODE:
		general = new CCommonListenBGM(this);
		break;
	case SELECTMESSAGE_MODE:
		general = new CCommonSelectMessage(this);
		break;
	case PRINTMESSAGE_MODE:
		general = new CCommonPrintMessage(this);
		break;
	case CONFIG_MODE:
		general = new CCommonConfig(this);
		break;
	case SYSTEMMENU_MODE:
		general = new CCommonSystemMenu(this);
		break;
	case PRINTOVERRAP_MODE:
//		general = new CCommonOverrap(this);
		break;
	case OMAKE_MODE:
		general = new CCommonOmake(this);
		break;
	case SELECTCGCHARA_MODE:
		general = new CCommonSelectCGChara(this);
		break;
	case SELECTCG_MODE:
		general = new CCommonSelectCG(this);
		break;
	case SELECTSCENE_MODE:
		general = new CCommonSelectScene(this);
		break;
	case SELECTSCENECHARA_MODE:
		general = new CCommonSelectSceneChara(this);
		break;
	case SELECTPLACE_MODE:
		general = new CCommonSelectPlace(this);
		break;
	case SELECTPLACE2_MODE:
		general = new CCommonSelectPlace(this,1);
		break;
	case PRINTCG_MODE:
		general = new CCommonPrintCG(this);
		break;
	case SELECTZUKAN_MODE:
		general = new CCommonSelectZukan(this);
		break;
	case SELECTMOVIECHARA_MODE:
		general = new CCommonSelectMovieChara(this);
		break;
	case SELECTMOVIE_MODE:
		general = new CCommonSelectMovie(this);
		break;
	case PRINTMOVIE_MODE:
		general = new CCommonPrintMovie(this);
		break;
	case NAMEINPUT_MODE:
		general = new CCommonNameInput(this);
		break;
	case PRINTCALENDAR_MODE:
//		general = new CCommonPrintCalendar(this);
		break;
	case SELECTHEROIN_MODE:
		general = new CCommonSelectHeroin(this);
		break;
	case CODECERROR_MODE:
		general = new CCommonCodecError(this);
		break;
	case MINIGAME_MODE:
		general = new CCommonMiniGame(this);
		break;
	case MYPRINTRESULT_MODE:
		general = new CCommonPrintResult(this);
		break;
	case SELECTCHART_MODE:
		general = new CCommonChartMenu(this);
		break;
	case CARDSYSTEM_MODE:
		general = new CCommonCardSystem(this);
		break;
	}


	if (general == NULL) return FALSE;

	m_general[modeNumber] = general;


	return TRUE;
}


void CGameCallBack::CheckCreateBadFlag(void)
{
	for (int i=0;i<100;i++)
	{
		//LPSTR modename = m_commonModeName[i];
		LPSTR modename = m_systemModeList->GetModeName(i);

		if ((*modename) != 0)
		{
			char name[256];
			wsprintf(name,"%sClassDisable",modename);
			int flg = 0;
			if (GetInitGameParam(&flg,name))
			{
				if (flg)
				{
					m_createModeDisableFlag[i] = TRUE;
				}
				else
				{
					m_createModeDisableFlag[i] = FALSE;
				}
			}
		}
	}
}
/*
void CGameCallBack::CheckDefaultUserCommandFlag(void)
{
	for (int i=0;i<100;i++)
	{
		LPSTR usercommandname = m_usercommandName[i];
		if ((*usercommandname) != 0)
		{
			char name[256];
			sprintf(name,"%sDefaultProcess",usercommandname);
			int flg = 0;
			GetInitGameParam(&flg,name);
			if (flg)
			{
				m_defaultUserCommandFlag[i] = TRUE;
			}
		}
	}
}
*/


void CGameCallBack::TaihiAllEffect(void)
{
//OutputDebugString("\nvoid CGameCallBack::TaihiAllEffect(void)");
	m_effect->TaihiAllEffect();


	for (int i=0;i<m_layerKosuuMax;i++)
	{
		m_taihiVarControlLayer[i] = m_varControlLayer[i];
	}





	m_taihiMessageWindowPrintFlag = m_messageWindowPrintFlag;

	for (int layer=0;layer<m_layerKosuuMax;layer++)
	{
		LPSTR dst = m_taihiFileName[layer];
		CPicture* pic = m_effect->GetPicture(layer);
		LPSTR src = pic->GetFileName();
//OutputDebugString("\nfilename=");
//OutputDebugString(src);

		int ln = (int)strlen(src);
		if (ln>254) ln = 254;
		memcpy(dst,src,ln);
		*(dst+ln) = 0;
		*(dst+ln+1) = 0;
	}


	m_taihiScriptRunMode = m_scriptRunMode;

	int i = 0;
	for (i=0;i<4;i++)
	{
		m_taihiSptFileNumber[i] = m_sptFileNumber[i];
	}



	m_taihiPC = m_controlScript->GetPC();
	m_taihiPC2 = m_execScript->GetPC();
	m_taihiPC3 = m_execSubScript->GetPC();
	m_taihiPC4 = m_execSubSubScript->GetPC();

	m_taihiStackPointer = m_controlScript->m_stackPointer;
	m_taihiStackPointer2 = m_execScript->m_stackPointer;
	m_taihiStackPointer3 = m_execSubScript->m_stackPointer;
	m_taihiStackPointer4 = m_execSubSubScript->m_stackPointer;

	for (i=0;i<255;i++)
	{
		m_taihiStack[i] = m_controlScript->m_stack[i];
		m_taihiID[i] = m_controlScript->m_ID[i];
	}

	for (i=0;i<255;i++)
	{
		m_taihiStack2[i] = m_execScript->m_stack[i];
		m_taihiID2[i] = m_execScript->m_ID[i];
	}

	for (i=0;i<255;i++)
	{
		m_taihiStack3[i] = m_execSubScript->m_stack[i];
		m_taihiID3[i] = m_execSubScript->m_ID[i];
	}

	for (i=0;i<255;i++)
	{
		m_taihiStack4[i] = m_execSubSubScript->m_stack[i];
		m_taihiID4[i] = m_execSubSubScript->m_ID[i];
	}

	for (i=0;i<4;i++)
	{
		m_taihiSptFileNumber[i] = m_sptFileNumber[i];
	}
}


void CGameCallBack::FuqueAllEffect(void)
{
//OutputDebugString("\nvoid CGameCallBack::FuqueAllEffect(void)");
	m_messageWindowPrintFlag = m_taihiMessageWindowPrintFlag;

	m_effect->FuqueAllEffect();


	for (int i=0;i<m_layerKosuuMax;i++)
	{
		m_varControlLayer[i] = m_taihiVarControlLayer[i];
	}

	for (int layer=0;layer<m_layerKosuuMax;layer++)
	{
		LPSTR name = m_taihiFileName[layer];
//OutputDebugString("\nfilename=");
//OutputDebugString(name);
		if ((*name) != 0) 
		{
			CPicture* pic = m_effect->GetPicture(layer);
			pic->LoadDWQ(name);
		}
	}

	m_scriptRunMode = m_taihiScriptRunMode;
	int i = 0;
	for (i=0;i<4;i++)
	{
		m_sptFileNumber[i] = m_taihiSptFileNumber[i];
	}

	if (m_scriptRunMode >= 1)
	{
		char filename[256];
		wsprintf(filename,"spt\\%s.spt",m_sptList->GetName(m_sptFileNumber[1]));
		m_execScript->LoadScript(filename);
	}
	

	if (m_scriptRunMode >= 2)
	{
		char filename[256];
		wsprintf(filename,"spt\\%s.spt",m_sptList->GetName(m_sptFileNumber[2]));
		m_execSubScript->LoadScript(filename);
	}

	if (m_scriptRunMode >= 3)
	{
		char filename[256];
		wsprintf(filename,"spt\\%s.spt",m_sptList->GetName(m_sptFileNumber[3]));
		m_execSubSubScript->LoadScript(filename);
	}


	m_controlScript->SetPC(m_taihiPC);
	m_execScript->SetPC(m_taihiPC2);
	m_execSubScript->SetPC(m_taihiPC3);
	m_execSubSubScript->SetPC(m_taihiPC4);

	m_controlScript->m_stackPointer = m_taihiStackPointer;
	m_execScript->m_stackPointer = m_taihiStackPointer2;
	m_execSubScript->m_stackPointer = m_taihiStackPointer3;
	m_execSubSubScript->m_stackPointer = m_taihiStackPointer4;

	for (i=0;i<255;i++)
	{
		 m_controlScript->m_stack[i] = m_taihiStack[i];
		 m_controlScript->m_ID[i] = m_taihiID[i];
	}

	for (i=0;i<255;i++)
	{
		m_execScript->m_stack[i] = m_taihiStack2[i];
		m_execScript->m_ID[i] = m_taihiID2[i];
	}

	for (i=0;i<255;i++)
	{
		m_execSubScript->m_stack[i] = m_taihiStack3[i];
		m_execSubScript->m_ID[i] = m_taihiID3[i];
	}

	for (i=0;i<255;i++)
	{
		m_execSubSubScript->m_stack[i] = m_taihiStack4[i];
		m_execSubSubScript->m_ID[i] = m_taihiID4[i];
	}
}


void CGameCallBack::DisableMode(int modeNumber)
{
	if ((modeNumber >= 0) && (modeNumber<100))
	{
		m_createModeDisableFlag[modeNumber] = TRUE;
	}
}

void CGameCallBack::StartInitialMessage(void)
{
	if (m_printStartMessageFlag)
	{
		HDC hdc = GetDC(m_hWnd);
		RECT rc;
		SetRect(&rc,0,0,m_windowSizeX,m_windowSizeY);
		FillRect(hdc,&rc,(HBRUSH)(COLOR_WINDOW + 1));
		TextOut(hdc,0,0,m_startMessage,(int)strlen(m_startMessage));
		ReleaseDC(m_hWnd,hdc);
	}
}


void CGameCallBack::AddDebugLibDesc(void)
{
	char mes[256];

	LPSTR desc;
	LPSTR desc2;

	desc =  CNyanDirectXLibCompileDesc::GetCompileDate();
	desc2 =  CNyanDirectXLibCompileDesc::GetCompileTime();
	wsprintf(mes,"NyanDirectXLib : %s , %s",desc,desc2);
	AddDebugMessage(mes);
	
	desc =  CNyanLibCompileDesc::GetCompileDate();
	desc2 =  CNyanLibCompileDesc::GetCompileTime();
	wsprintf(mes,"NYANLIB : %s , %s",desc,desc2);
	AddDebugMessage(mes);

	desc =  CNNNUtilLibCompileDesc::GetCompileDate();
	desc2 =  CNNNUtilLibCompileDesc::GetCompileTime();
	wsprintf(mes,"NNNUtilLib : %s , %s",desc,desc2);
	AddDebugMessage(mes);

	desc =  CNNNLibCompileDesc::GetCompileDate();
	desc2 =  CNNNLibCompileDesc::GetCompileTime();
	wsprintf(mes,"NNNLib : %s , %s",desc,desc2);
	AddDebugMessage(mes);
}


void CGameCallBack::ChangeMessageWindowModeByNext(void)
{
	if (m_nextMessageWindowPrintMode != -1)
	{
		if (m_nextMessageWindowPrintMode == 0) m_messageWindowPrintFlag = FALSE;
		if (m_nextMessageWindowPrintMode == 1) m_messageWindowPrintFlag = TRUE;
		m_nextMessageWindowPrintMode = -1;
	}
}

int CGameCallBack::ProcessGameKey(int modeNumber)
{
	BOOL loadOk = TRUE;
	BOOL saveOk = TRUE;
	BOOL configOk = TRUE;
	BOOL optionOk = TRUE;
	BOOL backlogOk = TRUE;

	if (m_backLogOkTable[modeNumber] == 0)
	{
		backlogOk = FALSE;
	}

//	if ((modeNumber != PRINTMESSAGE_MODE) && (modeNumber != SELECTMESSAGE_MODE))
//	{
//		backlogOk = FALSE;
//	}

	if (m_general[BACKLOG_MODE] == NULL) backlogOk = FALSE;
	if (m_general[LOAD_MODE] == NULL) loadOk = FALSE;
	if (m_general[SAVE_MODE] == NULL) saveOk = FALSE;
	if (m_general[CONFIG_MODE] == NULL) configOk = FALSE;
	if (m_general[SYSTEMMENU_MODE] == NULL) optionOk = FALSE;

	BOOL createExitScreenFlag = TRUE;

	//各種キーの有効をチェック


	//体験版などでの無効をチェック

	if (CCommonGameVersion::CheckTaikenOrNetVersion())
	{
		if (CCommonGameVersion::CheckLoadCommandOk() == FALSE)
		{
			loadOk = FALSE;
		}
	}


	if (CCommonGameVersion::CheckTaikenOrNetVersion())
	{
		if (CCommonGameVersion::CheckSaveCommandOk() == FALSE)
		{
			saveOk = FALSE;
		}
	}

	BOOL expModeOk = TRUE;

	if (CheckSceneMode())
	{
		loadOk = FALSE;
		saveOk = FALSE;
		expModeOk = FALSE;
	}


	CCommonGeneral* general = m_general[modeNumber];

	if (loadOk)
	{
		if (CheckClickKey(LOAD_KEY))
		{
			TaihiAllEffect();

			if (m_shortCutLoadSound > 0)
			{
				PlaySystemSound(m_shortCutLoadSound-1);
			}

			SetCommonBackMode(LOAD_MODE,modeNumber);
			if (createExitScreenFlag) general->CreateExitScreen();
			return LOAD_MODE;
		}
	}


	if (saveOk)
	{
		if (CheckClickKey(SAVE_KEY))
		{
			TaihiAllEffect();

			if (m_shortCutSaveSound > 0)
			{
				PlaySystemSound(m_shortCutSaveSound-1);
			}

			SetSaveMode(modeNumber);
			MakeMiniCG();

			SetCommonBackMode(SAVE_MODE,modeNumber);
			if (createExitScreenFlag) general->CreateExitScreen();
			return SAVE_MODE;
		}
	}


	if (configOk)
	{
		if (CheckClickKey(CONFIG_KEY))
		{
			TaihiAllEffect();

			if (m_shortCutConfigSound > 0)
			{
				PlaySystemSound(m_shortCutConfigSound-1);
			}


			SetCommonBackMode(CONFIG_MODE,modeNumber);
			if (createExitScreenFlag) general->CreateExitScreen();
			return CONFIG_MODE;

		}
	}


	if (expModeOk)
	{
		for (int i=0;i<m_expSystemMenuKosuu;i++)
		{
			int checkKey = m_expSystemMenuShortCut[m_expSystemMenuStart+i];
			if (checkKey > 0)
			{
				if (CheckClickKey(checkKey))
				{
					int expMode = m_expSystemMenuMode[m_expSystemMenuStart+i];
					if (expMode > 0)
					{
						if (CheckExpModeByVar(expMode))
						{
							//sound?
							int snd = m_expSystemMenuSound[m_expSystemMenuStart+i];
							if (snd > 0)
							{
								PlaySystemSound(snd-1);
							}

							TaihiAllEffect();


							SetCommonBackMode(expMode,modeNumber);
							if (createExitScreenFlag) general->CreateExitScreen();
							return expMode;
						}
					}

					int expCommand = m_expSystemMenuCommand[m_expSystemMenuStart+i];
					if (expCommand > 0)
					{
						//quick load
						if (expCommand == LOAD_MODE)
						{
							if (CheckExistQuickLoadData() == FALSE)
							{
								if (m_quickLoadErrorSound > 0)
								{
									PlaySystemSound(m_quickLoadErrorSound-1);
								}

								return -1;
							}
						}

						int snd = m_expSystemMenuSound[m_expSystemMenuStart+i];
						if (snd > 0)
						{
							PlaySystemSound(snd-1);
						}

						if (expCommand == LOAD_MODE)
						{
							if (m_quickLoadDelay)
							{
								m_quickLoadYoyaku = 1;
//								CheckAndSetQuickLoadButtonEnable();
								return -1;
							}
						}

						if (expCommand == SAVE_MODE)
						{
							TaihiAllEffect();
							SetSaveMode(modeNumber);
							MakeMiniCG();
						}

						int cmdrt = ExpOptionCommand(expCommand);

						CheckAndSetQuickLoadButtonEnable();

						if (cmdrt == -1)
						{
							return -1;
						}

						return -1;
					}
				}
			}
		}

		if (m_quickSaveKey > 0)
		{
			if (CheckClickKey(m_quickSaveKey))
			{
				if (m_quickSaveSound > 0)
				{
					PlaySystemSound(m_quickSaveSound-1);
				}

				TaihiAllEffect();
				SetSaveMode(modeNumber);
				MakeMiniCG();

				int cmdrt = ExpOptionCommand(SAVE_MODE);
				CheckAndSetQuickLoadButtonEnable();

				if (cmdrt == -1)
				{
					return -1;
				}
				return -1;
			}
		}

		if (m_quickLoadKey > 0)
		{
			if (CheckClickKey(m_quickLoadKey))
			{
				if (CheckExistQuickLoadData())
				{
					if (m_quickLoadDelay == 0)
					{
						int cmdrt = ExpOptionCommand(LOAD_MODE);
						if (cmdrt == -1)
						{
							if (m_quickLoadErrorSound > 0)
							{
								PlaySystemSound(m_quickLoadErrorSound-1);
							}
							return -1;
						}

						if (m_quickLoadSound > 0)
						{
							PlaySystemSound(m_quickLoadSound-1);
						}
					}
					else
					{
						m_quickLoadYoyaku = 1;
					}
				}
				else
				{
					if (m_quickLoadSound > 0)
					{
						PlaySystemSound(m_quickLoadSound-1);
					}
				}

				return -1;
			}
		}
	}




	if (optionOk)
	{
		BOOL flg = FALSE;
		if (CheckClickKey(SYSTEMMENU_KEY)) flg = TRUE;
		if (CheckClickKey(OPTIONMENU_KEY)) flg = TRUE;

		if (1)
		{
			if (m_mouseStatus->CheckClick(m_optionStartMouseButton)) flg = TRUE;
		}

		if (flg)
		{
			TaihiAllEffect();

			if (m_shortCutSystemMenuSound > 0)
			{
				PlaySystemSound(m_shortCutSystemMenuSound-1);
			}

			SetSaveMode(modeNumber);
			MakeMiniCG();

			SetCommonBackMode(SAVE_MODE,modeNumber);
			SetCommonBackMode(LOAD_MODE,modeNumber);
			SetCommonBackMode(CONFIG_MODE,modeNumber);
			SetCommonBackMode(SYSTEMMENU_MODE,modeNumber);


			//not create exit screen??? ok?
			if (createExitScreenFlag) general->CreateExitScreen();

			return SYSTEMMENU_MODE;
		}
	}



	return -1;
}


BOOL CGameCallBack::CheckDebugOk(void)
{
	FILE* file00 = CMyFile::Open("debug.txt","rb");
	if (file00 != NULL)
	{
		fclose(file00);
		return TRUE;
	}
	return FALSE;
}


void CGameCallBack::SetDebugFlag(BOOL flg)
{
	m_debugVarFlag = flg;
	m_memPrintFlag = flg;
	m_debugOkFlag = flg;
	CPicture::m_errorPrintFlag = flg;
}

int CGameCallBack::GetNowSystemTime(int varNumber)
{
	int rt = 0;

	SYSTEMTIME systemtime;
	GetLocalTime(&systemtime);

	if (varNumber == m_systemYearVar) rt = systemtime.wYear;
	if (varNumber == m_systemMonthVar) rt = systemtime.wMonth;
	if (varNumber == m_systemDayVar) rt = systemtime.wDay;
	if (varNumber == m_systemHourVar) rt = systemtime.wHour;
	if (varNumber == m_systemMinuteVar) rt = systemtime.wMinute;
	if (varNumber == m_systemSecondVar) rt = systemtime.wSecond;
	if (varNumber == m_systemWeekVar) rt = systemtime.wDayOfWeek;
	if (varNumber == m_systemMilliSecondVar) rt = systemtime.wMilliseconds;

	return rt;
}

void CGameCallBack::StopMusic(int fadeOutTime)
{
	m_musicControl->StopMusic(fadeOutTime);
	m_musicNumber = -1;
	m_lastMusicNumber = -1;
}


void CGameCallBack::PlayMusic(int n,int loopCount,int volume,int fadeInTime, int fadeOutTime)
{
	if (m_allMusicSetFlag)
	{
		m_systemFile->SetMusic(n);
	}

	LPSTR filename = m_bgmList->GetName(n*2);
	if (filename != NULL)
	{
		BOOL played = FALSE;

		if (GetSystemParam(NNNPARAM_MUSICSWITCH))
		{
			if (CheckTotalVolumeOff() == FALSE)
			{
				PlayMusic(filename,loopCount,volume,fadeInTime,fadeOutTime);
				played = TRUE;
			}
		}

		if (played == FALSE)
		{
			int vol = GetSystemParam(NNNPARAM_MUSICVOLUME);

			if (volume != -9999)
			{
				vol += volume;
				if (vol<1) vol = 1;
				if (vol>100) vol = 100;
			}
			m_musicControl->SetVolumeData(vol);
		}
	}

	m_musicNumber = n;
	m_lastMusicNumber = n;
}

//protected??
void CGameCallBack::PlayMusic(LPSTR filename,int loopCount,int volume,int fadeInTime,int fadeOutTime)
{
	int vol = GetSystemParam(NNNPARAM_MUSICVOLUME);

	if (volume != -9999)
	{
		vol += volume;
		if (vol<1) vol = 1;
		if (vol>100) vol = 100;
	}

	m_musicControl->PlayMusic(filename,loopCount,vol,fadeInTime,fadeOutTime);
}


int CGameCallBack::GetNowMusicNumber(void)
{
	return m_musicNumber;
}


void CGameCallBack::CreateNowExitScreen(void)
{
	Erase();
	CPicture* lpPic = GetOverrapPic(0);
	lpPic->GetScreen();
}




int CGameCallBack::CalcuOptionButton(void)
{
	int rt1 = NNNBUTTON_NOTHING;
	int rt2 = NNNBUTTON_NOTHING;
	int rt3 = NNNBUTTON_NOTHING;
	int rt4 = NNNBUTTON_NOTHING;
	int rt5 = NNNBUTTON_NOTHING;

	int rt102 = NNNBUTTON_NOTHING;
	int rt103 = NNNBUTTON_NOTHING;
	int rt106 = NNNBUTTON_NOTHING;
	int rt107 = NNNBUTTON_NOTHING;
	int rt108 = NNNBUTTON_NOTHING;

	int md = GetGameMode();

	if (GetOptionOff() == FALSE)
	{
		if (m_optionButton != NULL)
		{
			rt1 = m_optionButton->Calcu(m_inputStatus);
		}

		if (CheckSceneMode() == FALSE)
		{
			if (m_quickSaveButton != NULL)
			{
				if (CheckQuickButtonOkMode(md,SAVE_MODE))
				{
					rt2 = m_quickSaveButton->Calcu(m_inputStatus);
				}
			}

			if (m_quickLoadButton != NULL)
			{
				if (CheckQuickButtonOkMode(md,LOAD_MODE))
				{
					rt3 = m_quickLoadButton->Calcu(m_inputStatus);
				}
			}

			if (m_freeSaveButton != NULL)
			{
				if (CheckFreeButtonOkMode(md,SAVE_MODE))
				{
					rt102 = m_freeSaveButton->Calcu(m_inputStatus);
				}
			}

			if (m_freeLoadButton != NULL)
			{
				if (CheckFreeButtonOkMode(md,LOAD_MODE))
				{
					rt103 = m_freeLoadButton->Calcu(m_inputStatus);
				}
			}
		}

		if (m_quickConfigButton != NULL)
		{
			if (CheckQuickButtonOkMode(md,CONFIG_MODE))
			{
				rt4 = m_quickConfigButton->Calcu(m_inputStatus);
			}
		}

		if (m_quickBackLogButton != NULL)
		{
			if (m_backLogOkTable[md])
			{
				if (CheckQuickButtonOkMode(md,BACKLOG_MODE))
				{
					rt5 = m_quickBackLogButton->Calcu(m_inputStatus);
				}
			}
		}

		if (m_freeAutoButton != NULL)
		{
			if (CheckFreeButtonOkMode(md,NNN_FREEBUTTON_AUTO))
			{
				rt106 = m_freeAutoButton->Calcu(m_inputStatus);
			}
		}
		if (m_freeSkipButton != NULL)
		{
			if (CheckFreeButtonOkMode(md,NNN_FREEBUTTON_SKIP))
			{
				rt107 = m_freeSkipButton->Calcu(m_inputStatus);
			}
		}
		if (m_freeWindowOffButton != NULL)
		{
			if (CheckFreeButtonOkMode(md,NNN_FREEBUTTON_WINDOWOFF))
			{
				rt108 = m_freeWindowOffButton->Calcu(m_inputStatus);
			}
		}
	}

	int saveProceed = FALSE;
	int sound = 0;
	int st2 = -1;
	if (rt2 != NNNBUTTON_NOTHING)
	{
		st2 = CCommonButton::GetButtonStatus(rt2);
		int requestSoundFlag = CCommonButton::CheckRequestSound(rt2);
		if (requestSoundFlag)
		{
			sound = CCommonButton::GetButtonSound(rt2);
		}

		int existDataFlag = CCommonButton::CheckExistData(rt2);

		int nm = -1;
		if (existDataFlag)
		{
			nm = CCommonButton::GetButtonData(rt2);
			if (nm == 0)
			{
				//quick save

				TaihiAllEffect();
				SetSaveMode(GetGameMode());
				MakeMiniCG();

				int cmdrt = ExpOptionCommand(SAVE_MODE);

				saveProceed = TRUE;

				if (m_quickSaveButton != NULL)
				{
					m_quickSaveButton->Init();
				}

				CheckAndSetQuickLoadButtonEnable();
			}
		}
	}

	int loadProceed = FALSE;

	int st3 = -1;
	if (rt3 != NNNBUTTON_NOTHING)
	{
		st3 = CCommonButton::GetButtonStatus(rt3);
		int requestSoundFlag = CCommonButton::CheckRequestSound(rt3);
		if (requestSoundFlag)
		{
			sound = CCommonButton::GetButtonSound(rt3);
		}

		int nm = -1;
		int existDataFlag = CCommonButton::CheckExistData(rt3);
		if (existDataFlag)
		{
			nm = CCommonButton::GetButtonData(rt3);
			if (nm == 0)
			{
				if (saveProceed == FALSE)
				{
					if (CheckExistQuickLoadData() == FALSE)
					{
						if (m_quickLoadErrorSound > 0)
						{
							PlaySystemSound(m_quickLoadErrorSound-1);
						}
					}
					else
					{
						int cmdrt = ExpOptionCommand(LOAD_MODE);
						loadProceed = TRUE;
					}

					//quick load
				}

				if (m_quickLoadButton != NULL)
				{
					m_quickLoadButton->Init();
					CheckAndSetQuickLoadButtonEnable();
				}
			}
		}
	}

	int st4 = -1;
	int st5 = -1;

	//必要に応じてbuttoncode作成する
	//config:1
	//backlog:2






	int optionProceed = FALSE;

	int st1 = -1;
	if (rt1 != NNNBUTTON_NOTHING)
	{
		st1 = CCommonButton::GetButtonStatus(rt1);
	}

	if (saveProceed || loadProceed)
	{
		int nm = -1;
		int existDataFlag = CCommonButton::CheckExistData(rt1);
		if (existDataFlag)
		{
			nm = CCommonButton::GetButtonData(rt1);
			if (nm == 0)
			{
				if (m_optionButton != NULL)
				{
					m_optionButton->Init();
				}
				optionProceed = TRUE;
			}
		}
	}

	if (optionProceed == FALSE)
	{
		int nm = -1;

		st4 = CCommonButton::GetButtonStatus(rt4);
		int requestSoundFlag = CCommonButton::CheckRequestSound(rt4);
		if (requestSoundFlag)
		{
			sound = CCommonButton::GetButtonSound(rt4);
		}

		int existDataFlag = CCommonButton::CheckExistData(rt4);
		if (existDataFlag)
		{
			nm = CCommonButton::GetButtonData(rt4);
			if (nm == 0)
			{
				if (m_quickConfigButton != NULL)
				{
					m_quickConfigButton->Init();
				}
				optionProceed = TRUE;
				rt1 = CCommonButton::MakeButtonStatus(NNNBUTTON_NUMBER,-1,-1,1);
			}
		}
	}

	if (optionProceed == FALSE)
	{
		int nm = -1;

		st5 = CCommonButton::GetButtonStatus(rt5);
		int requestSoundFlag = CCommonButton::CheckRequestSound(rt5);
		if (requestSoundFlag)
		{
			sound = CCommonButton::GetButtonSound(rt5);
		}

		int existDataFlag = CCommonButton::CheckExistData(rt5);
		if (existDataFlag)
		{
			nm = CCommonButton::GetButtonData(rt5);
			if (nm == 0)
			{
				if (m_quickBackLogButton != NULL)
				{
					m_quickBackLogButton->Init();
				}
				optionProceed = TRUE;
				rt1 = CCommonButton::MakeButtonStatus(NNNBUTTON_NUMBER,-1,-1,2);
			}
		}
	}

	int st102 = -1;
	int st103 = -1;
	int st106 = -1;
	int st107 = -1;
	int st108 = -1;

	if (optionProceed == FALSE)
	{
		st102 = CCommonButton::GetButtonStatus(rt102);
		optionProceed = CalcuFreeButton(m_freeSaveButton,rt102,3,&rt1,&sound);
	}
	if (optionProceed == FALSE)
	{
		st103 = CCommonButton::GetButtonStatus(rt103);
		optionProceed = CalcuFreeButton(m_freeLoadButton,rt103,4,&rt1,&sound);
	}
	if (optionProceed == FALSE)
	{
		st106 = CCommonButton::GetButtonStatus(rt106);
		optionProceed = CalcuFreeButton(m_freeAutoButton,rt106,5,&rt1,&sound);
	}
	if (optionProceed == FALSE)
	{
		st107 = CCommonButton::GetButtonStatus(rt107);
		optionProceed = CalcuFreeButton(m_freeSkipButton,rt107,6,&rt1,&sound);
	}
	if (optionProceed == FALSE)
	{
		st108 = CCommonButton::GetButtonStatus(rt108);
		optionProceed = CalcuFreeButton(m_freeWindowOffButton,rt108,7,&rt1,&sound);
	}


	if (optionProceed == FALSE)
	{
		if ((st1 != NNNBUTTON_STARTCLICK) && (st1 != NNNBUTTON_CLICKING))
		{
			BOOL f = FALSE;

			if ((st2 == NNNBUTTON_STARTCLICK) || (st2 == NNNBUTTON_CLICKING))
			{
				f = TRUE;
			}

			if ((st3 == NNNBUTTON_STARTCLICK) || (st3 == NNNBUTTON_CLICKING) || (st3 == NNNBUTTON_CANNOTCLICK))
			{
				f = TRUE;
			}

			if ((st4 == NNNBUTTON_STARTCLICK) || (st4 == NNNBUTTON_CLICKING))
			{
				f = TRUE;
			}

			if ((st5 == NNNBUTTON_STARTCLICK) || (st5 == NNNBUTTON_CLICKING))
			{
				f = TRUE;
			}

			if ((st102 == NNNBUTTON_STARTCLICK) || (st102 == NNNBUTTON_CLICKING))
			{
				f = TRUE;
			}
			if ((st103 == NNNBUTTON_STARTCLICK) || (st103 == NNNBUTTON_CLICKING))
			{
				f = TRUE;
			}
			if ((st106 == NNNBUTTON_STARTCLICK) || (st106 == NNNBUTTON_CLICKING))
			{
				f = TRUE;
			}
			if ((st107 == NNNBUTTON_STARTCLICK) || (st107 == NNNBUTTON_CLICKING))
			{
				f = TRUE;
			}
			if ((st108 == NNNBUTTON_STARTCLICK) || (st108 == NNNBUTTON_CLICKING))
			{
				f = TRUE;
			}

			if (f)
			{
				rt1 = CCommonButton::MakeButtonStatus(NNNBUTTON_CLICKING);
			}
		}
	}

	return rt1;
}

BOOL CGameCallBack::CalcuFreeButton(CSceneOptionButton* button,int rt,int cmd,int* lpRT,int* lpSound)
{
	if (button == NULL) return FALSE;

	BOOL optionProceed = FALSE;

	int nm = -1;
//	int rt = -1;

//	st102 = CCommonButton::GetButtonStatus(rt102);
	int requestSoundFlag = CCommonButton::CheckRequestSound(rt);
	if (requestSoundFlag)
	{
		*lpSound = CCommonButton::GetButtonSound(rt);
	}

	int existDataFlag = CCommonButton::CheckExistData(rt);
	if (existDataFlag)
	{
		nm = CCommonButton::GetButtonData(rt);
		if (nm == 0)
		{
			if (button != NULL)
			{
				button->Init();
			}

			optionProceed = TRUE;
			*lpRT = CCommonButton::MakeButtonStatus(NNNBUTTON_NUMBER,-1,-1,cmd);
		}
	}
	return optionProceed;
}

BOOL CGameCallBack::CheckOnFreeAutoSkipButton(POINT pt)
{
	if (m_freeAutoButton != NULL)
	{
		if (m_freeAutoButton->CheckOn(pt)) return TRUE;
	}

	if (m_freeSkipButton != NULL)
	{
		if (m_freeSkipButton->CheckOn(pt)) return TRUE;
	}

	return FALSE;
}

int CGameCallBack::CalcuSceneButton(void)
{
	if (m_sceneButton == NULL) return NNNBUTTON_NOTHING;

	return m_sceneButton->Calcu(m_inputStatus);
}

int CGameCallBack::CalcuSkipFilmButton(void)
{
	if (m_skipFilmButton == NULL) return FALSE;
	
	if (m_skipToFilmEndEnable != 1)
	{
		return FALSE;
	}

	int rt = m_skipFilmButton->Calcu(m_inputStatus);
	if (rt != NNNBUTTON_NOTHING)
	{
		int st = rt & NNNBUTTON_STATUSMASK;
		if (st == NNNBUTTON_NUMBER)
		{
			SkipToFilmEnd();
			return TRUE;
		}
	}

	return FALSE;
}

void CGameCallBack::CheckAndSetQuickLoadButtonEnable(void)
{
	if (m_quickLoadButton != NULL)
	{
		if (CheckExistQuickLoadData())
		{
			m_quickLoadButton->SetEnable();
			m_quickLoadButton->Init();
		}
		else
		{
			m_quickLoadButton->SetEnable(FALSE);
		}
	}
}


void CGameCallBack::InitOptionButton(void)
{
	if (m_optionButton != NULL)
	{
		m_optionButton->Init();
	}
	if (m_quickSaveButton != NULL)
	{
		m_quickSaveButton->Init();
	}
	if (m_quickLoadButton != NULL)
	{
		m_quickLoadButton->Init();
		CheckAndSetQuickLoadButtonEnable();
	}
	if (m_quickConfigButton != NULL)
	{
		m_quickConfigButton->Init();
	}
	if (m_quickBackLogButton != NULL)
	{
		m_quickBackLogButton->Init();
	}

	InitFreeButton(m_freeSaveButton,SAVE_MODE);
	InitFreeButton(m_freeLoadButton,LOAD_MODE);
	InitFreeButton(m_freeAutoButton,NNN_FREEBUTTON_AUTO);
	InitFreeButton(m_freeSkipButton,NNN_FREEBUTTON_SKIP);
	InitFreeButton(m_freeWindowOffButton,NNN_FREEBUTTON_WINDOWOFF);
}

void CGameCallBack::InitFreeButton(CSceneOptionButton* button,int md)
{
	int nowMode = GetGameMode();
	if (button != NULL)
	{
		button->Init();
		int f = CheckFreeButtonOkMode(nowMode,md);
		if (f == 0)
		{
			button->SetEnable(0);
		}
		else if (f == 1)
		{
			button->SetEnable();
		}
		else if (f == 2)
		{
			button->SetEnable(0);
		}
		else
		{
			button->SetEnable();//error
		}
		button->Init();
	}
}


void CGameCallBack::InitSceneButton(void)
{
	if (m_sceneButton == NULL) return;
	m_sceneButton->Init();
}

void CGameCallBack::InitSkipFilmButton(void)
{
	if (m_skipFilmButton == NULL) return;
	m_skipFilmButton->Init();
}

/*
void CGameCallBack::InitQuickSaveButton(void)
{
	if (m_quickSaveButton == NULL) return;
	m_quickSaveButton->Init();
}

void CGameCallBack::InitQuickLoadButton(void)
{
	if (m_quickLoadButton == NULL) return;
	m_quickLoadButton->Init();
}
*/

void CGameCallBack::PrintOptionButtonYoyaku(void)
{
	m_optionButtonPrintYoyaku = TRUE;
//	m_quickSaveButtonPrintYoyaku = TRUE;
}

void CGameCallBack::PrintSceneButtonYoyaku(void)
{
	m_sceneButtonPrintYoyaku = TRUE;
}

void CGameCallBack::PrintSkipFilmButtonYoyaku(void)
{
	if (m_skipToFilmEndEnable)
	{
		m_skipFilmButtonPrintYoyaku = TRUE;
	}
}

/*
void CGameCallBack::PrintQuickSaveButtonYoyaku(void)
{
	m_quickSaveButtonPrintYoyaku = TRUE;
}

void CGameCallBack::PrintQuickLoadButtonYoyaku(void)
{
	m_quickLoadButtonPrintYoyaku = TRUE;
}
*/

void CGameCallBack::PrintOptionButton(void)
{
	m_optionButtonPrintYoyaku = FALSE;
	if (GetOptionOff()) return;

	if (m_optionButton != NULL)
	{
		m_optionButton->Print(TRUE);
	}

	int md = GetGameMode();

	if (CheckSceneMode() == FALSE)
	{
		if (m_quickLoadButton != NULL)
		{
			if (CheckQuickButtonOkMode(md,LOAD_MODE))
			{
				m_quickLoadButton->Print();
			}
		}
		if (m_quickSaveButton != NULL)
		{
			if (CheckQuickButtonOkMode(md,SAVE_MODE))
			{
				m_quickSaveButton->Print();
			}
		}
	}

	if (m_quickConfigButton != NULL)
	{
		if (CheckQuickButtonOkMode(md,CONFIG_MODE))
		{
			m_quickConfigButton->Print();
		}
	}
	if (m_quickBackLogButton != NULL)
	{
		int md = GetGameMode();
		if (m_backLogOkTable[md])
		{
			if (CheckQuickButtonOkMode(md,BACKLOG_MODE))
			{
				m_quickBackLogButton->Print();
			}
		}
	}


	if (CheckSceneMode() == FALSE)
	{
		PrintFreeButton(m_freeSaveButton,SAVE_MODE);
		PrintFreeButton(m_freeLoadButton,LOAD_MODE);
	}
	PrintFreeButton(m_freeAutoButton,NNN_FREEBUTTON_AUTO);
	PrintFreeButton(m_freeSkipButton,NNN_FREEBUTTON_SKIP);
	PrintFreeButton(m_freeWindowOffButton,NNN_FREEBUTTON_WINDOWOFF);
}

void CGameCallBack::PrintFreeButton(CSceneOptionButton* button,int md)
{
	if (button != NULL)
	{
		int nowMode = GetGameMode();
		if (CheckFreeButtonOkMode(nowMode,md))
		{
			button->Print();
		}
	}
}



void CGameCallBack::PrintSceneButton(void)
{
	m_sceneButtonPrintYoyaku = FALSE;

	if (m_sceneButton == NULL) return;
	if (CheckSceneMode() == FALSE) return;

	m_sceneButton->Print(TRUE);
}

void CGameCallBack::PrintSkipFilmButton(void)
{
	m_skipFilmButtonPrintYoyaku = FALSE;

	if (m_skipFilmButton == NULL) return;

	if (CheckSceneMode()) return;

	m_skipFilmButton->Print(TRUE);
}
/*
void CGameCallBack::PrintQuickSaveButton(void)
{
	m_quickSaveButtonPrintYoyaku = FALSE;
	if (m_quickSaveButton == NULL) return;

	if (GetOptionOff()) return;

	m_quickSaveButton->Print(TRUE);
}

void CGameCallBack::PrintQuickLoadButton(void)
{
	m_quickLoadButtonPrintYoyaku = FALSE;
	if (m_quickLoadButton == NULL) return;

	if (GetOptionOff()) return;

	m_quickLoadButton->Print(TRUE);
}
*/

void CGameCallBack::SetDontPlay(int md)
{
	m_dontPlayMode = md;
	SetSystemParam(NNNPARAM_AUTOMODE,md);
}


int CGameCallBack::CheckListenMusic(int musicNumber)
{
	return m_systemFile->CheckMusic(musicNumber);
}


int CGameCallBack::SearchMusicNumber(LPSTR filename)
{
	if (m_bgmList == NULL)
	{
		return -1;
	}

	int kosuu = m_bgmList->GetNameKosuu() / 2;
	for (int i=0;i<kosuu;i++)
	{
		if (_stricmp(filename,m_bgmList->GetName(i*2)) == 0) return i;
	}
	return -1;
}

void CGameCallBack::LaunchCountUp(void)
{
	if (m_launchFlag) return;

	int cnt = m_systemFile->m_systemdata.launchCount;
	cnt++;
	if (cnt >= 0x7ffffffe) cnt = 0x7ffffffe;
	m_systemFile->m_systemdata.launchCount = cnt;

	m_launchFlag = TRUE;
}

int CGameCallBack::GetLaunchCount(void)
{
	return m_systemFile->m_systemdata.launchCount;
}

void CGameCallBack::ResetLaunch(void)
{
	m_systemFile->m_systemdata.launchCount = 0;
}


int CGameCallBack::CheckCodec(void)
{
	if (m_codecError == -1)
	{
		CCommonPrintMovie* movie = (CCommonPrintMovie*)m_general[PRINTMOVIE_MODE];
		if ((movie == NULL) || (m_directShow == NULL))
		{
			m_codecError = 0;
		}
		else
		{
			m_codecError = movie->CheckCodec();
		}
	}

	return m_codecError;//cannot use
}


void CGameCallBack::StopScriptSoundAndVoice(void)
{
	int i = 0;
	for (i=0;i<8;i++)
	{
//		if (m_loopSoundWork[i*16])
		if (1)
		{
//			m_scriptSound[i]->Stop();
	//		m_loopSoundWork[i*16] = FALSE;
		}
	}

	if (m_scriptSoundControl != NULL)
	{
		m_scriptSoundControl->AllStop();
	}


	if (m_scriptVoiceControl != NULL)
	{
		m_scriptVoiceControl->AllStop();
	}
	for (i=0;i<4;i++)
	{
		//if (m_loopVoiceWork[i*16])
		if (1)
		{
		//	m_scriptVoiceControl->AllStop();
			
			//			m_scriptVoice[i]->Stop();
	//		m_loopSoundWork[i*16] = FALSE;
		}
	}
}

BOOL CGameCallBack::RegistUserCommand(int classNumber,LPSTR commandName)
{
	if (m_defaultUserCommandKosuu >= 50) return FALSE;


	if (m_createModeDisableFlag[classNumber]) return FALSE;

	m_defaultUserCommandNumber[m_defaultUserCommandKosuu] = m_commandList->SearchName(commandName);
	if (m_defaultUserCommandNumber[m_defaultUserCommandKosuu] >= 0) m_defaultUserCommandNumber[m_defaultUserCommandKosuu] /= 2;

	if (m_defaultUserCommandNumber[m_defaultUserCommandKosuu] != -1)
	{
		m_defaultUserCommandClass[m_defaultUserCommandKosuu] = classNumber;
		m_defaultUserCommandKosuu++;
		return TRUE;
	}

	return FALSE;
}

BOOL CGameCallBack::RegistUserFunction(int classNumber,LPSTR functionName,int functionNumber)
{
	if (m_autoFunctionKosuu >= 50) return FALSE;
	
	if (classNumber < 50)
	{
		if (m_createModeDisableFlag[classNumber]) return FALSE;
	}

	int n = m_functionList->SearchBlock(functionName);
	if (n == -1) return FALSE;

	m_autoFunctionClass[m_autoFunctionKosuu] = classNumber;
	m_autoFunctionNumber[m_autoFunctionKosuu] = n;
	m_autoFunctionParam[m_autoFunctionKosuu] = functionNumber;

	m_autoFunctionKosuu++;

	return TRUE;
}


LPSTR CGameCallBack::GetMovieName(int n)
{
	if (m_movieList == NULL) return NULL;
	if (n <= 0) return NULL;

	int kosuu = m_movieList->GetNameKosuu();
	if (n > kosuu) return NULL;

	return m_movieList->GetName((n-1)*2);
}

/*
CMyDirectSoundBuffer* CGameCallBack::GetScriptSoundBuffer0(int n)
{
	return m_scriptSound[n];
}
*/

void CGameCallBack::EraseCursor(void)
{
	SetCursor(NULL);
}

void CGameCallBack::SetCodecError(int err)
{
	m_codecError = err;
}


void CGameCallBack::PrintScriptFileName(void)
{
	char mes[256];
	int sptNum = m_sptFileNumber[m_scriptRunMode];
	if (m_scriptRunMode == 0) sptNum = 0;
	if (sptNum < 0) return;

	LPSTR scriptName = m_sptList->GetName(sptNum);
	wsprintf(mes,"%s【%s】%s",scriptName,m_lastFilmName,m_lastStoryName);

	HWND hWnd = GetGameHWND();
	HDC hdc = GetDC(hWnd);
//	int oldBackMode = SetBkMode(hdc,TRANSPARENT);
	int oldBackMode = SetBkMode(hdc,OPAQUE);
	COLORREF oldTextColor = SetTextColor(hdc,0);

	SetBkColor(hdc,COLORREF(0x0080ff));

	int putX = 16;
	int putY = 8;

	int ln = (int)strlen(mes);
	SetTextColor(hdc,COLORREF(0x000000));
	TextOut(hdc,putX+1,putY+1,mes,ln);
	SetTextColor(hdc,COLORREF(0xFFFFFF));
	TextOut(hdc,putX,putY,mes,ln);

	if (oldTextColor != CLR_INVALID) SetTextColor(hdc,oldTextColor);
	if (oldBackMode != 0) SetBkMode(hdc,oldBackMode);

	ReleaseDC(hWnd,hdc);
}

void CGameCallBack::SetListenBGMParam(int md,int musicNumber)
{
	SetVarData(m_listenbgmmodeVar,md);
	SetVarData(m_listenbgmnumberVar,musicNumber);
}


void CGameCallBack::GetGetScreen(void)
{
	m_effect->GetGetScreen();
}

void CGameCallBack::PutGetScreen(void)
{
	m_effect->PutGetScreen();
}

int CGameCallBack::GetShakinFrame(int kaeseru)
{
	return m_shakinControl->GetHensaiFrame(kaeseru);
}

/*
void CGameCallBack::ShakinHensaiFrame(int frame)
{
	if (frame >= 0)
	{
		m_shakinControl->HensaiFrame(frame);
	}
	else
	{
		m_shakinControl->Clear();
	}
}
*/

int CGameCallBack::ShakinHensai(int kaeseru)
{
	if (m_backScriptModeFlag)
	{
		if (kaeseru > m_maxSkipFrameBackScript)
		{
			kaeseru = m_maxSkipFrameBackScript;
		}
	}

	if (kaeseru < 0)
	{
		m_shakinControl->Clear();
		return -1;
	}

	if (kaeseru == 0)
	{
		if (m_backScriptModeFlag)
		{
			kaeseru = m_maxSkipFrameBackScript;
		}
		else
		{
			kaeseru = m_maxSkipFrame;
		}
	}


	int kaesu = GetShakinFrame(kaeseru);
	m_shakinControl->HensaiFrame(kaesu);
	return kaesu;
}


void CGameCallBack::SetFrameRate(int frameRate)
{
	m_frameTime = frameRate;
	if (m_shakinControl != NULL)
	{
		m_shakinControl->SetFrame(frameRate);
	}
}

void CGameCallBack::SetSystemMenuSceneMode(BOOL flg)
{
	CCommonSystemMenu* obj = (CCommonSystemMenu*)m_general[SYSTEMMENU_MODE];
	if (obj != NULL)
	{
		obj->SetSceneMode(flg);
	}
}


void CGameCallBack::RestartLoopSoundAndVoice(void)
{
	int i = 0;
	for (i=0;i<8;i++)
	{
//		if (m_loopSoundWork[i*16])
		if (m_scriptSoundControl->GetLoopFlag(i))
		{
			PlayScriptSe(i);
		}
		else
		{
		}
	}

	for (i=0;i<4;i++)
	{
//		if (m_loopVoiceWork[i*16])
		if (m_scriptVoiceControl->GetLoopFlag(i))
		{
			PlayScriptVoice(i);
		}
		else
		{
		}
	}
}


void CGameCallBack::SetLastSaveOkGameMode(int md)
{
	BOOL flg = FALSE;

	if (md == PRINTMESSAGE_MODE) flg = TRUE;
	if (md == SELECTMESSAGE_MODE) flg = TRUE;
	if (md == SELECTPLACE_MODE) flg = TRUE;
	if ((md >= SELECTPLACE2_MODE) && (md < (SELECTPLACE2_MODE+5))) flg = TRUE;
	if (md == SELECTHEROIN_MODE) flg = TRUE;
	if ((md >= 50) && (md<=99)) flg = TRUE;

	if (flg)
	{
		m_lastSaveOkMode = md;
	}
}

int CGameCallBack::ChangeToSystemMode(int nextMode,int nowMode)
{
	if (nowMode == 0) nowMode = m_lastSaveOkMode;

	TaihiAllEffect();

	SetSaveMode(nowMode);
	MakeMiniCG();

	SetCommonBackMode(SAVE_MODE,nowMode);
	SetCommonBackMode(LOAD_MODE,nowMode);
	SetCommonBackMode(CONFIG_MODE,nowMode);
	SetCommonBackMode(SYSTEMMENU_MODE,nowMode);
	
	//CreateExitScreen();
	CCommonGeneral* general = m_general[nowMode];
	if (general != NULL)
	{
		general->CreateExitScreen();
	}

	if (nowMode == PRINTMESSAGE_MODE)
	{
		if (CheckSceneMode())
		{
			SetSystemMenuSceneMode();
		}
	}

	CAreaControl::SetNextAllPrint();

	return nextMode;
}

void CGameCallBack::SetWindowNumberByConfig(int d)
{
	m_systemFile->m_systemdata.windowNumber = d;
	if (m_messageWindow != NULL)
	{
		m_messageWindow->SetWindowNumberByConfig(d);
	}
}

void CGameCallBack::SetWindowNumberByScript(int d)
{
	m_scriptWindowNumber = d;
	if (m_messageWindow != NULL)
	{
		m_messageWindow->SetWindowNumberByScript(d);
	}
}

void CGameCallBack::SetWindowNumberByFontSize(int d)
{
	m_messageFontSizeType = d;
	if (m_messageWindow != NULL)
	{
		m_messageWindow->SetWindowNumberByFontSizeType(d);
	}
}

void CGameCallBack::SetMouseNumberByConfig(int d)
{
	m_systemFile->m_systemdata.mouseNumber = d;
	if (m_gameMouse != NULL)
	{
		m_gameMouse->SetMouseNumberByConfig(d);
	}
}


void CGameCallBack::SetMouseNumberByScript(int d)
{
	m_scriptMouseNumber = d;
	if (m_gameMouse != NULL)
	{
		m_gameMouse->SetMouseNumberByScript(d);
	}
}

void CGameCallBack::SetCursorNumberByConfig(int d)
{
	m_systemFile->m_systemdata.cursorNumber = d;
	if (m_messageCursor != NULL)
	{
		m_messageCursor->SetCursorNumberByConfig(d);
	}
}

void CGameCallBack::SetCursorNumberByScript(int d)
{
	m_scriptCursorNumber = d;
	if (m_messageCursor != NULL)
	{
		m_messageCursor->SetCursorNumberByScript(d);
	}

}

int CGameCallBack::GetWindowNumberByConfig(void)
{
	return m_systemFile->m_systemdata.windowNumber;
}

int CGameCallBack::GetMouseNumberByConfig(void)
{
	return m_systemFile->m_systemdata.mouseNumber;
}

int CGameCallBack::GetCursorNumberByConfig(void)
{
	return m_systemFile->m_systemdata.cursorNumber;
}


void CGameCallBack::ClearWindowMouseCursorNumberByScript(void)
{
	SetWindowNumberByScript(0);
	SetMouseNumberByScript(0);
	SetWindowNumberByFontSize(0);
	SetCursorNumberByScript(0);
}

int CGameCallBack::GetWindowShurui(void)
{
	if (m_messageWindow == NULL) return 1;
	return m_messageWindow->GetWindowShuruiConfig();
}

int CGameCallBack::GetMouseShurui(void)
{
	if (m_gameMouse == NULL) return 1;
	return m_gameMouse->GetMouseShuruiConfig();
}

int CGameCallBack::GetCursorShurui(void)
{
	if (m_messageCursor == NULL) return 1;
	return m_messageCursor->GetCursorShuruiConfig();
}

BOOL CGameCallBack::CheckOnMessageWindowSize(POINT pt)
{
	if (m_messageWindow == NULL) return FALSE;

	return m_messageWindow->CheckOnSize(pt);
}


void CGameCallBack::CheckAndWaitMainThread(void)
{
	SetEvent(m_threadControlHandle[0]);
	
	DWORD flg1 = WaitForSingleObject(m_threadControlHandle[1],1000*5);
	if (flg1 == WAIT_OBJECT_0)
	{
		ResetEvent(m_threadControlHandle[1]);
	}
}



int CGameCallBack::WaitGameThread(void)
{
	int rt = WaitForSingleObject(m_threadControlHandle[0],1000*3);
	if (rt == WAIT_OBJECT_0)
	{
		ResetEvent(m_threadControlHandle[0]);
	}

	return rt;
}

BOOL CGameCallBack::ResumeGameThread(void)
{
	SetEvent(m_threadControlHandle[1]);
	return TRUE;
}


BOOL CGameCallBack::SetTmpThreadHandle(HANDLE threadHandle)
{
	m_tmpThreadHandle = threadHandle;
	SetEvent(m_threadControlHandle[2]);
	WaitForSingleObject(m_threadControlHandle[3],1000*5);
	ResetEvent(m_threadControlHandle[3]);
	return TRUE;
}



BOOL CGameCallBack::StartModalThread(int modeNumber, int printMode, int stackSize)
{
	int param[3];
	param[0] = modeNumber;
	param[1] = printMode;
	param[2] = stackSize;

	HANDLE eventHandle = CreateEvent(NULL,TRUE,FALSE,NULL);
	if (eventHandle == NULL) return FALSE;

	PostMessage(m_hWnd,WM_MYCREATETHREAD,(WPARAM)param,(LPARAM)eventHandle);
	SetEvent(m_threadControlHandle[0]);
	//wait



	WaitForSingleObject(m_threadControlHandle[2],1000*10);
	HANDLE threadHandle = m_tmpThreadHandle;
	ResetEvent(m_threadControlHandle[2]);
	SetEvent(m_threadControlHandle[3]);

	if (threadHandle == NULL)
	{
		CloseHandle(eventHandle);
		return FALSE;	//error etc
	}


	OutputDebugString("[Thread Start]");

	if (m_modalCannotCloseFlag)
	{
		HMENU menu = GetSystemMenu(m_hWnd,FALSE);
		MENUITEMINFO mif;
		ZeroMemory(&mif,sizeof(mif));
		mif.cbSize = sizeof(mif);
		mif.fMask = MIIM_STATE;// | MIIM_ID;
		mif.fState = MFS_DISABLED;
		mif.wID = SC_CLOSE;
		SetMenuItemInfo(menu,SC_CLOSE,FALSE,&mif);
//		if (GetNNNParam(NNNPARAM_SCREENMODE) == 0)
		if (GetSystemParam(NNNPARAM_SCREENMODE) == 0)
		{
			DrawMenuBar(m_hWnd);
	//		HWND closeButton = GetDlgItem(m_hWnd,SC_CLOSE);
	//		if (closeButton != NULL)
	//		{
	//			UpdateWindow(closeButton);
	//		}
	//		UpdateWindow(m_hWnd);
		}
	}


	DWORD rt = WaitForSingleObject(eventHandle,INFINITE);

	if (rt == WAIT_ABANDONED)
	{
#if defined _DEBUG
		OutputDebugString("[×Thread Abandoned]");
#endif
	}

	if (rt == WAIT_OBJECT_0)
	{
#if defined _DEBUG
		OutputDebugString("[Thread End]");
#endif
	}

	if (rt == WAIT_TIMEOUT)
	{
#if defined _DEBUG
		OutputDebugString("[×Thread TimeOut]");
#endif
	}

	CloseHandle(eventHandle);
	CloseHandle(threadHandle);

	return TRUE;
}


BOOL CGameCallBack::EndModalThread(void)
{
	BOOL rt = PostMessage(m_hWnd,WM_MYDESTROYTHREAD,0,0);
	SetEvent(m_threadControlHandle[0]);

	WaitForSingleObject(m_threadControlHandle[2],1000*10);
	ResetEvent(m_threadControlHandle[2]);
	SetEvent(m_threadControlHandle[3]);

	rt = TRUE;

	if (rt == FALSE)
	{
#if defined __DEBUG
		OutputDebugString("[Error:EndModalThread]");
#endif
		return FALSE;
	}

#if defined _MT
	OutputDebugString("[[CoUninit たぶんこっちにくる]]");

	int level = GetModalLevel();
	char mes[256];
	wsprintf(mes,"[level=%d]",level);
	OutputDebugString(mes);

	if (m_modalCannotCloseFlag)
	{
		if (level == 0)
		{
			HMENU menu = GetSystemMenu(m_hWnd,FALSE);
			MENUITEMINFO mif;
			ZeroMemory(&mif,sizeof(mif));
			mif.cbSize = sizeof(mif);
			mif.fMask = MIIM_STATE;// | MIIM_ID;
			mif.fState = MFS_ENABLED;
			mif.wID = SC_CLOSE;
			SetMenuItemInfo(menu,SC_CLOSE,FALSE,&mif);

//			if (GetNNNParam(NNNPARAM_SCREENMODE) == 0)
			if (GetSystemParam(NNNPARAM_SCREENMODE) == 0)
			{
				DrawMenuBar(m_hWnd);

	//			HWND closeButton = GetDlgItem(m_hWnd,SC_CLOSE);
	//			if (closeButton != NULL)
	//			{
	//				UpdateWindow(closeButton);
	//			}
			}
		}
	}


	CoUninitialize();
	_endthreadex(0);
#endif

	return TRUE;
}

BOOL CGameCallBack::CheckAndFree(void)
{
	int flg = WaitForSingleObject(m_threadControlHandle[0],0);
	if (flg == WAIT_OBJECT_0)
	{
		ResumeGameThread();
	}
	return TRUE;
}


void CGameCallBack::ClearWork(void)
{
	SetDontPlay(0);
	SetConfigMask(0);
	SetSystemParam(NNNPARAM_AUTOMODE,0);
	SetMessageSkipFlag(FALSE);

	ClearF5();
	SetOpeningMode(FALSE);

	SetWindowNumberByScript(0);
	SetCursorNumberByScript(0);
	SetWindowNumberByFontSize(0);
	SetMouseNumberByScript(0);

	m_quickLoadYoyaku = 0;

	m_autoMessage = 0;
	m_cannotClick = 0;
	m_cannotSkip = 0;
	m_optionOff = 0;
	m_renameLayer = 0;

	for (int i=0;i<m_layerKosuuMax;i++)
	{
		m_varControlLayer[i] = 0;
	}

	m_cutinFlag = 0;

	int i = 0;
	for (i=0;i<8;i++)
	{
//		m_loopSoundWork[i*16] = FALSE;
		m_scriptSoundControl->SetLoopFlag(i,FALSE);
	}

	for (i=0;i<8;i++)
	{
//		m_loopVoiceWork[i*16] = FALSE;
		m_scriptVoiceControl->SetLoopFlag(i,0);
	}

	if (m_faceControl != NULL)
	{
		m_faceControl->Clear();
	}
}


BOOL CGameCallBack::AddMiniGame(int n)
{
	CCommonMiniGame* miniGame = (CCommonMiniGame*)(m_general[MINIGAME_MODE]);
	if (miniGame == NULL) return FALSE;
	return miniGame->AddMiniGame(n);
}

BOOL CGameCallBack::AddMiniGame(CMiniGameBase* lpMiniGame)
{
	CCommonMiniGame* miniGame = (CCommonMiniGame*)(m_general[MINIGAME_MODE]);
	if (miniGame == NULL) return FALSE;
	return miniGame->AddMiniGame(lpMiniGame);
}


int CGameCallBack::GetSceneButtonMode(void)
{
	return m_sceneButtonMode;
}

BOOL CGameCallBack::Set3DMode(BOOL flg)
{
	m_3dMode = flg;
	return TRUE;
}


void CGameCallBack::InitMiniGameButton(int md)
{
	CCommonMiniGame* miniGame = (CCommonMiniGame*)(m_general[MINIGAME_MODE]);
	if (miniGame == NULL) return;

	miniGame->InitMiniGameButton(md);
}

void CGameCallBack::PrintMiniGameButton(void)
{
	CCommonMiniGame* miniGame = (CCommonMiniGame*)(m_general[MINIGAME_MODE]);
	if (miniGame == NULL) return;

	miniGame->PrintMiniGameButton();
}


BOOL CGameCallBack::CheckMiniGame(int modeNumber)
{
	CCommonMiniGame* miniGame = (CCommonMiniGame*)(m_general[MINIGAME_MODE]);
	if (miniGame == NULL) return FALSE;


	if (miniGame->GetAreaButtonMode() == 0)
	{
		int nm = miniGame->GetOnMiniGame(modeNumber);
		if (nm == -1) return FALSE;

		//
		m_onMiniGameArea = TRUE;

		if (m_mouseStatus->CheckClick())
		{
			m_miniGameNumber = nm;
			return TRUE;
		}

		return FALSE;
	}

	int rt = miniGame->CalcuMiniGameButton();
	//sound?
	if (rt != -1)
	{
		int st = CCommonButton::GetButtonStatus(rt);
		int requestSoundFlag = CCommonButton::CheckRequestSound(rt);
		int sound = 0;
		if (requestSoundFlag)
		{
			sound = CCommonButton::GetButtonSound(rt);
		}
		int existDataFlag = CCommonButton::CheckExistData(rt);
		int nm = -1;
		if (existDataFlag)
		{
			nm = CCommonButton::GetButtonData(rt);
		}

		if (requestSoundFlag)
		{
			if (sound > 0)
			{
				PlaySystemSound(sound - 1);
			}
		}

		if (nm >= 0)
		{
			m_miniGameNumber = nm;
			return TRUE;
		}
	}

	return FALSE;
}

void CGameCallBack::SetLayerOff(int layeroff)
{
	int bt = 1;
	for (int i=0;i<m_layerKosuuMax;i++)
	{
		if ((layeroff & bt) == 0)
		{
			m_effect->SetEye(i,TRUE);
		}
		else
		{
			m_effect->SetEye(i,FALSE);
		}
		bt <<= 1;
	}
	m_layerOff = layeroff;
}


void CGameCallBack::SetMovieEnable(BOOL flg)
{
	m_movieEnableFlag = flg;
#if !defined _TINYAN3DLIB_
	m_directDraw->OnActivate(TRUE);
#endif
}

//for 3D
#if !defined _TINYAN3DLIB_
BOOL CGameCallBack::BeginScene(BOOL targetChangeFlag){return TRUE;}
void CGameCallBack::EndScene(void){}
BOOL CGameCallBack::BeginGet(CPicture* lpPic){return TRUE;}
void CGameCallBack::EndGet(void){}
#else

BOOL CGameCallBack::BeginScene(BOOL targetChangeFlag)
{
	if (m_myDirect3D == NULL) return FALSE;

#if defined _TINYAN3DLIB_
//	if (GetGameMode() == PRINTMOVIE_MODE) return TRUE;
#endif


	CMyDirect3D* d3d = (CMyDirect3D*)m_myDirect3D;
	if (SUCCEEDED(d3d->BeginScene(targetChangeFlag)))
	{
		return TRUE;
	}

	return FALSE;
}

void CGameCallBack::EndScene(void)
{
	if (m_myDirect3D == NULL) return;

#if defined _TINYAN3DLIB_
//	if (GetGameMode() == PRINTMOVIE_MODE) return;
#endif


	CMyDirect3D* d3d = (CMyDirect3D*)m_myDirect3D;
	d3d->EndScene();
}

BOOL CGameCallBack::BeginGet(CPicture* lpPic)
{
	return TRUE;

	if (m_myDirect3D == NULL) return FALSE;
	CMyDirect3D* d3d = (CMyDirect3D*)m_myDirect3D;
	
	CMyTexture* lpTexture = (CMyTexture*)(lpPic->GetTexture());
	LPDIRECT3DTEXTURE9 texture = lpTexture->GetTexture();
	
	d3d->BeginGet(texture);
	return TRUE;
}

void CGameCallBack::EndGet(void)
{
	return;

	if (m_myDirect3D == NULL) return;
	CMyDirect3D* d3d = (CMyDirect3D*)m_myDirect3D;
	
	
	d3d->EndGet();
}


#endif


void CGameCallBack::TaihiForScreenChange0(void)
{
	m_effect->TaihiAllEffectToStaticBuffer();

//	for (int layer=0;layer<16;layer++)
//	{
//		LPSTR dst = m_taihiFileName[layer];
//		CPicture* pic = m_effect->GetPicture(layer);
//		LPSTR src = pic->GetFileName();
//
//		int ln = strlen(src);
//		if (ln>254) ln = 254;
//		memcpy(dst,src,ln);
//		*(dst+ln) = 0;
//		*(dst+ln+1) = 0;
//	}
}

void CGameCallBack::FuqueByScreenChange0(void)
{
	m_effect->FuqueAllEffectByStaticBuffer();

	for (int layer=0;layer<m_layerKosuuMax;layer++)
	{
//		LPSTR name = m_taihiFileName[layer];
//		LPSTR name = m_effect->GetTaihiEffectFileName(layer);
//		if ((*name) != 0) 
//		{
//			CPicture* pic = m_effect->GetPicture(layer);
//			pic->LoadDWQ(name);
//		}
	}

}

//used default
LPSTR CGameCallBack::GetSystemSei(void)
{
	return m_systemFile->m_systemdata.sei;
}

LPSTR CGameCallBack::GetSystemMei(void)
{
	return m_systemFile->m_systemdata.mei;
}

//game default
LPSTR CGameCallBack::GetGameDefaultSei(void)
{
	return GetGameDefaultSeiMei(0);
}

LPSTR CGameCallBack::GetGameDefaultMei(void)
{
	return GetGameDefaultSeiMei(1);
}

void CGameCallBack::SetSeiMei(LPSTR sei,LPSTR mei)
{
	if (sei != NULL)
	{
		int ln1 = (int)strlen(sei);
		memcpy(m_systemFile->m_systemdata.sei,sei,ln1+1);
		memcpy(CMyMessage::m_sei,sei,ln1+1);
	}

	if (mei != NULL)
	{
		int ln2 = (int)strlen(mei);
		memcpy(m_systemFile->m_systemdata.mei,mei,ln2+1);
		memcpy(CMyMessage::m_mei,mei,ln2+1);
	}
}

void CGameCallBack::ClearFontCache(void)
{
	if (m_font != NULL)
	{
		m_font->ClearFontCache();
	}
}

void CGameCallBack::ClearBackLog(void)
{
	CCommonBackLog* obj = (CCommonBackLog*)m_general[BACKLOG_MODE];
	if (obj == NULL) return;
	obj->Clear();
}


int CGameCallBack::ExpOptionCommand(int cmd)
{
	//quick save
	if (cmd == SAVE_MODE)//quick save
	{
		if (m_quickSaveEnable)
		{
			CCommonSave* save = (CCommonSave*)(m_general[SAVE_MODE]);
			if (save != NULL)
			{
				//clear cpmment
				char taihiComment[256];

				if (m_quickSaveCommentFlag == 0)
				{
					for (int i=0;i<m_saveCommentKosuuMax;i++)
					{
						taihiComment[i] = m_saveComment[i][0];
						m_saveComment[i][0] = 0;
					}
				}

				save->QuickSave();
				//quick save message

				if (m_quickSaveCommentFlag == 0)
				{
					for (int i=0;i<m_saveCommentKosuuMax;i++)
					{
						m_saveComment[i][0] = taihiComment[i];
					}
				}



				if (m_quickSavePrint)
				{
					if (m_noticeFlag)
					{
						m_notice->Start(m_saveNoticeNumber-1);
					}
				}

				return -1;
			}
		}
		return -1;
	}

	//quick load if can
	if (cmd == LOAD_MODE)//quick load
	{
		if (m_quickLoadEnable)
		{
			CCommonLoad* load = (CCommonLoad*)(m_general[LOAD_MODE]);
			if (load != NULL)
			{
				//clear all
				for (int i=0;i<m_layerKosuuMax;i++)
				{
					SetDontLoadDWQ(i,0);
				}

				//getput?
				if (m_quickLoadGetScreen)
				{
					CreateNowExitScreen();
				}


				if (load->QuickLoad())
				{
					if (m_quickLoadPrint)
					{
						if (m_noticeFlag)
						{
							m_notice->Start(m_loadNoticeNumber-1);
						}
					}

					//quick load print
					return 0;
				}

				return -1;
			}
		}
	}

	return UserSystemMenu(cmd);
}

int CGameCallBack::UserSystemMenu(int cmd)
{
#if defined _DEBUG
	char mes[256];
	wsprintf(mes,"\nUserSystemMenu:%d\n",cmd);
	OutputDebugString(mes);
#endif
	return -1;
}


void CGameCallBack::SetSaveComment(LPSTR comment,int n)
{
	if (comment == NULL)
	{
		m_saveComment[n][0] = 0;
	}
	else
	{
		if ((n>=0) && (n<m_saveCommentKosuuMax))
		{
			int ln = (int)strlen(comment);
			if (ln>m_saveCommentLength-2)
			{
				ln =m_saveCommentLength-2;
			}
			memcpy(m_saveComment[n],comment,ln);
			m_saveComment[n][ln] = 0;
			m_saveComment[n][ln+1] = 0;
		}
	}
}


void CGameCallBack::GetMiniCGData(int* dst, int type,int customSizeX,int customSizeY)
{
	if (m_miniCG == NULL) return;

	
	int sz = 132*100;
	if (type == 0)
	{
		sz = 80*60;
	}
	else if (type == 1)
	{
		sz = 132*100;
	}
	else if (type == -1)
	{
		sz = customSizeX * customSizeY;
	}
	else if (type == -2)
	{
		sz = m_miniCGSizeX * m_miniCGSizeY;
	}

	for (int i=0;i<sz;i++)
	{
		*dst = m_miniCG[i];
		dst++;
	}
}

int CGameCallBack::GetUseCutin(void)
{
	return m_useCutinFlag;
}

void CGameCallBack::SkipToFilmEnd(void)
{
	if (GetGameMode() == PRINTMESSAGE_MODE)
	{
		if (CheckSceneMode() == FALSE)
		{
			if (CheckDemoMode() == FALSE)
			{
				m_skipF4Mode = FALSE;
				m_skipF5Mode = TRUE;
				m_skipNextCommandFlag = TRUE;
				m_skipEffectCommandFlag = TRUE;

				m_skipToFilmEndFlag = TRUE;
				m_skipToFilmEndEnable = FALSE;

				SetYoyaku();
			}
		}
	}
}


int CGameCallBack::GetSpecialNumberForSave(void)
{
	if (m_specialNumberForSaveSetFlag)
	{
		if (m_specialNumberForSaveVarNumber != -1)
		{
			return GetVarData(m_specialNumberForSaveVarNumber);
		}
	}

	return 0;
}


BOOL CGameCallBack::CheckExistQuickLoadData(void)
{
	if (CheckUseQuickLoad() == FALSE) return FALSE;

	CCommonLoad* load = (CCommonLoad*)(m_general[LOAD_MODE]);
	if (load != NULL)
	{
		return load->CheckQuickLoadDataExist();
	}

	return FALSE;
}


BOOL CGameCallBack::CheckUseQuickLoad(void)
{
	if (m_quickLoadEnable == 0) return FALSE;

	//他の条件は?
	return TRUE;
}

POINT CGameCallBack::GetMouseHotPoint(void)
{
	POINT pt;
	pt.x = 0;
	pt.y = 0;
	if (m_gameMouse != NULL)
	{
		pt = m_gameMouse->GetMouseHotPoint();
	}
	return pt;
}



void CGameCallBack::GetExtDataForSaveGeneral(LPVOID ptr,int extNumber)
{
	if (extNumber < m_autoExtDataLoadKosuu)
	{
		int md = m_autoExtDataLoadMode[extNumber];
		if (md > 0)
		{
			m_general[md]->GetExtDataForSave(ptr,extNumber);
			return;
		}
	}
	else if (extNumber < (m_autoExtDataLoadKosuu + m_autoExtSubDataLoadKosuu))
	{
		int sb = m_autoExtDataLoadSub[extNumber - m_autoExtDataLoadKosuu];
		if (sb > 0)
		{
			CAutoSaveSubData* subClass = m_autoSaveSubDataClass[extNumber - m_autoExtDataLoadKosuu];
			if (subClass != NULL)
			{
				subClass->GetExtDataForSave(ptr,extNumber);
				return;
			}
		}
	}

	GetExtDataForSave(ptr,extNumber);
}

void CGameCallBack::SetExtDataByLoadGeneral(LPVOID ptr,int extNumber)
{
	if (extNumber < m_autoExtDataLoadKosuu)
	{
		int md = m_autoExtDataLoadMode[extNumber];
		if (md > 0)
		{
			m_general[md]->SetExtDataByLoad(ptr,extNumber);
			return;
		}
	}
	else if (extNumber < (m_autoExtDataLoadKosuu + m_autoExtSubDataLoadKosuu))
	{
		int sb = m_autoExtDataLoadSub[extNumber - m_autoExtDataLoadKosuu];
		if (sb > 0)
		{
			CAutoSaveSubData* subClass = m_autoSaveSubDataClass[extNumber - m_autoExtDataLoadKosuu];
			if (subClass != NULL)
			{
				subClass->SetExtDataByLoad(ptr,extNumber);
				return;
			}
		}
	}

	SetExtDataByLoad(ptr,extNumber);
}


void CGameCallBack::SetBackLogOk(int mode,int flg)
{
	if ((mode >= 0) && (mode < 256))
	{
		m_backLogOkTable[mode] = flg;
	}
}

int CGameCallBack::GetBackLogOk(int mode)
{
	if ((mode >= 0) && (mode < 256))
	{
		return m_backLogOkTable[mode];
	}

	return 0;
}


void CGameCallBack::SetMessageWindowPercent(void)
{
	if (m_messageWindow == NULL) return;

	int ps = 100 - GetSystemParam(NNNPARAM_WINDOWPERCENT);
	if (ps<0) ps = 0;
	if (ps>100) ps = 100;
	m_messageWindow->SetWindowPercent(ps);
}


LPSTR CGameCallBack::GetDefaultSeiMei(int md)
{
	LPSTR name = m_errorName;
	if (md == 0)
	{
		GetInitGameString(&name,"seiInitData");
	}
	else if (md == 1)
	{
		GetInitGameString(&name,"meiInitData");
	}

	return name;
}

LPSTR CGameCallBack::GetGameDefaultSeiMei(int md)
{
	LPSTR name = m_errorName;
	if (md == 0)
	{
		GetInitGameString(&name,"defaultNameSei");
	}
	else if (md == 1)
	{
		GetInitGameString(&name,"defaultNameMei");
	}

	return name;
}

BOOL CGameCallBack::CheckExpModeByVar(int mode)
{
	int varNumber = m_expModeCheckVarNumber[mode];
	if (varNumber <= 0) return TRUE;

	if (GetVarData(varNumber)) return TRUE;

	return FALSE;
}

//汎用
int CGameCallBack::SetExpParam(int n,int para,LPVOID lpPara)
{
	if (n == 1)
	{
		m_noVoiceIsDefaultWait = para;
	}

	return -1;
}



void CGameCallBack::ChangeAutoExtDataSize(int mode,int dataSize)
{
	//search
	int found = -1;
	for (int i=0;i<m_autoExtDataLoadKosuu;i++)
	{
		int md = m_autoExtDataLoadMode[i];
		if (md == mode)
		{
			found = i;
			break;
		}
	}

	if (found != -1)
	{
		if (found < (m_extSaveDataKosuu + m_autoExtDataLoadKosuu + m_autoExtSubDataLoadKosuu))
		{
			m_extSaveDataSizeTable[found] = dataSize;

			CCommonLoad* load = (CCommonLoad*)(m_general[LOAD_MODE]);
			if (load != NULL)
			{
				load->ChangeExtDataSize(found,dataSize);
			}

			CCommonSave* save = (CCommonSave*)(m_general[SAVE_MODE]);
			if (save != NULL)
			{
				save->ChangeExtDataSize(found,dataSize);
			}
		}
	}
	else
	{
		char mes[1024];
		wsprintf(mes,"initに自動セーブデータが設定されていません:モード %d(%s)",mode,m_systemModeList->GetModeName(mode));
		MessageBox(NULL,mes,"Error",MB_OK | MB_ICONEXCLAMATION);
	}
}

void CGameCallBack::ChangeAutoExtSubDataSize(int n,int dataSize)
{
	//search
	int found = m_autoExtDataLoadKosuu + n;

	if (found < (m_extSaveDataKosuu + m_autoExtDataLoadKosuu + m_autoExtSubDataLoadKosuu))
	{
		m_extSaveDataSizeTable[found] = dataSize;

		CCommonLoad* load = (CCommonLoad*)(m_general[LOAD_MODE]);
		if (load != NULL)
		{
			load->ChangeExtDataSize(found,dataSize);
		}

		CCommonSave* save = (CCommonSave*)(m_general[SAVE_MODE]);
		if (save != NULL)
		{
			save->ChangeExtDataSize(found,dataSize);
		}
	}
	else
	{
		char mes[1024];
		wsprintf(mes,"initに自動セーブデータが設定されていません:サブモード %d",n);
		MessageBox(NULL,mes,"Error",MB_OK | MB_ICONEXCLAMATION);
	}
}

//FreeButtonも同じものを使う
int CGameCallBack::CheckFreeButtonOkMode(int nowMode,int checkMode)
{
	CCommonGeneral* general = m_general[nowMode];
	if (general != NULL)
	{
		int f = general->CheckOtherSetup(checkMode,1);
		if (f == 0) return 1;
		if (f == 1) return 0;//dont print
		if (f == 2) return 2;//grey拡張よう
		return 0;
//		if (general->CheckOtherSetup(checkMode,1)) return FALSE;
	}

	return 1;
}

BOOL CGameCallBack::CheckQuickButtonOkMode(int nowMode,int checkMode)
{
	CCommonGeneral* general = m_general[nowMode];
	if (general != NULL)
	{
		if (general->CheckOtherSetup(checkMode)) return FALSE;
	}

	return TRUE;
}

void CGameCallBack::StartNotice(int n)
{
	if (m_noticeFlag)
	{
		if (m_notice != NULL)
		{
			m_notice->Start(n);
		}
	}
}


void CGameCallBack::ClickShiftKey(void)
{
	BOOL b = !CheckMessageSkipFlag();
	if (b)
	{
		if (m_shiftSkipMessageOnly)
		{
			if (GetGameMode() != PRINTMESSAGE_MODE)
			{
				return;
			}
		}
	}

	SetMessageSkipFlag(b);
}

void CGameCallBack::SetLastSaveSlot(int slot)
{
	m_systemFile->m_systemdata.lastSaveSlot = slot + 1;
}

int CGameCallBack::GetLastSaveSlot(void)
{
	return m_systemFile->m_systemdata.lastSaveSlot - 1;
}

void CGameCallBack::ClearYoyaku(void)
{
	m_yoyaku = 0;
}

void CGameCallBack::EndMovie(void)
{
#if !defined _TINYAN3DLIB_
	if (m_3dMode == FALSE)
	{
		PrintBackBuffer();
		BltToFront();
	}
#endif

}


void CGameCallBack::CheckAndSetMouseAndCursor(int para,int dat)
{
	if ((para >= NNNPARAM_EXPMODE) && (para < NNNPARAM_EXPMODE+m_expButtonKosuu))
	{
		int n = para - NNNPARAM_EXPMODE;
		if ((n+1) == m_expModeButtonIsMouse)
		{
			SetMouseNumberByConfig(dat);
		}
		if ((n+1) == m_expModeButtonIsMessageCursor)
		{
			SetCursorNumberByConfig(dat);
		}
	}
}





BOOL CGameCallBack::CheckWheelDisable(void)
{
	if (m_backLogDisableCount == 0) return FALSE;
	return TRUE;
}

void CGameCallBack::PrintFace(int check,LPSTR name)
{
	if (check != m_facePrintFlag) return;
	if (m_faceControl == NULL) return;

	CAreaControl::SetNextAllPrint();
	m_faceControl->Print(name);
}

void CGameCallBack::SetAutoSaveSubClass(int type,CAutoSaveSubData* subClass)
{
	for (int i=0;i<m_autoExtSubDataLoadKosuu;i++)
	{
		if (m_autoExtDataLoadSub[i] == type)
		{
			m_autoSaveSubDataClass[i] = subClass;
		}
	}

}

void CGameCallBack::AllOnOmakeFlag(int mask)
{
	if (mask & 1)	//CG
	{
		m_cgDataControl->SetAllOn();
	}

	if (mask & 2)	//scene
	{
		m_sceneDataControl->SetAllOn();
	}

}

void CGameCallBack::SetAnimeOff(int offMode)
{
	m_effect->SetAnimeOff(offMode);
}

BOOL CGameCallBack::AfterChangeSystemParamExpCheck(int para,int dat)
{
	//virtual! nothing to do this class
	return FALSE;
}

BOOL CGameCallBack::AfterChangeSystemParamExpRadio(int para,int dat)
{
	return FALSE;
	//virtual! nothing to do this class
}

BOOL CGameCallBack::CheckVolumeExist(int n)
{
	CCommonConfig* config = (CCommonConfig*)(m_general[CONFIG_MODE]);
	if (config == NULL) return FALSE;
	return config->CheckVolumeExist(n);
}

CPicture* CGameCallBack::GetAnimeBuffer(int n)
{
	return m_effect->GetAnimeBuffer(n);
}

LPSTR CGameCallBack::GetAnimeTag(void)
{
	return m_effect->GetAnimeTag();
}

BOOL CGameCallBack::CheckTotalVolumeOff(void)
{
	if (m_totalVolumeUseFlag == 0) return FALSE;
	if (GetSystemParam(NNNPARAM_TOTALSWITCH)) return FALSE;

	return TRUE;
}

void CGameCallBack::InitFreeButton(int buttonType)
{
	if (buttonType == NNN_FREEBUTTON_SKIP)
	{
		if (m_freeSkipButton != NULL)
		{
			m_freeSkipButton->SetNextIgnore();
//			OutputDebugString("InitFreeButton\n");
		}
	}
}

int CGameCallBack::GetCGBlockNumber(int cgCharaNumber,int cgNumber)
{
	CCommonSelectCG* general = (CCommonSelectCG*)(m_general[SELECTCG_MODE]);
	if (general == NULL) return 0;
	return general->GetCGBlockNumber(cgCharaNumber,cgNumber);
}

void CGameCallBack::DebugF5Routine(void)
{
//	SetMessageRead(m_lastMessageID);
	m_skipF4Mode = FALSE;
	m_skipF5Mode = TRUE;
	m_skipNextCommandFlag = TRUE;
	m_skipEffectCommandFlag = TRUE;
	m_skipToFilmEndFlag = FALSE;

//	m_effect->ClearAllEffect();
	SetYoyaku();
}


POINT CGameCallBack::GameToView(POINT pt)
{
	return m_viewControl->GameToView(pt);
}


BOOL CGameCallBack::CheckNameIsSpecialVoice(void)
{
	if (m_nameIsSpecialVoiceFlag != -1)
	{
		if (m_nameIsSpecialVoiceFlag == 0) return FALSE;
		return TRUE;
	}

	BOOL f = FALSE;
	m_nameIsSpecialVoiceFlag = 0;

	LPSTR checkName = CMyMessage::m_mei;

	for (int i=0;i<m_specialVoiceNameKosuu;i++)
	{
		LPSTR name = &m_specialVoiceName[i*64];
		if ((*name) != 0)
		{
			if (strcmp(name,checkName) == 0)
			{
				m_nameIsSpecialVoiceFlag = 1;
				f = TRUE;
				break;
			}
		}
	}
	
	return f;
}


/*_*/





