//
// commonListenBGM.cpp
//


#include <windows.h>
#include <math.h>


#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"

#include "..\nyanLib\include\allGeo.h"

#include "..\nnnUtilLib\myFont.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\nnnButtonStatus.h"

#include "..\nnnUtilLib\animeControl.h"

#include "..\nnnUtilLib\musicControl.h"

#include "..\nnnUtilLib\fft.h"

#include "commonMode.h"
#include "commonSystemParamName.h"
#include "commonSystemSoundName.h"

#include "..\nnnUtilLib\inputStatus.h"

#include "..\nnnutilLib\superButtonPicture.h"

#include "..\nnnUtilLib\commonButton.h"
#include "..\nnnUtilLib\commonMultiStateButton.h"
#include "..\nnnUtilLib\commonCheckButton.h"


#include "gameCallBack.h"

#include "commonGeneral.h"
#include "commonListenBGM.h"



#include "..\nnnUtilLib\namelist.h"


#include "..\nnnUtilLib\myMessage.h"
#include "..\nnnUtilLib\mySlider.h"
#include "..\nnnUtilLib\suuji.h"
//#include "..\nnnUtilLib\midiPlayer.h"

#include "..\nnnUtilLib\commonButton.h"
#include "..\nnnUtilLib\commonBackButton.h"
#include "..\nnnUtilLib\commonUpdownButtonGroup.h"
#include "..\nnnUtilLib\commonUpdownBack.h"

#include "..\nnnUtilLib\printSpectrum.h"

//#include "..\nnnUtilLib\myOldRadioButton.h"






#define MUSIC_STOP_MODE 0
#define MUSIC_PLAY_MODE 1
#define MUSIC_PAUSE_MODE 2


//char CCommonListenBGM::m_defaultBGMListFileName[] = "nnndir\\bgmlen.txt";

/*
int CCommonListenBGM::m_musicOrgLength[][2]=
{
	{1,25},
	{1,11},
	{1,15},
	{1,11},
	{1,18},
	{1,17},
	{1,18},
	{1,15},
	{1,40},
	{1,30},
	{1,27},
	{1,30},
	{1,52},
	{2,40},

	{0, 7},	//dummy
};
*/

char CCommonListenBGM::m_defaultBGFileName[] = "bgm_bg";
char CCommonListenBGM::m_defaultButtonFileName[] ="ta_bgm_bt";
char CCommonListenBGM::m_defaultVolumeFileName[] = "ta_opt_bar";
char CCommonListenBGM::m_defaultNumberFileName[] = "ta_bgm_num1";
char CCommonListenBGM::m_defaultCursorFileName[] = "ta_bgm_selc";

char CCommonListenBGM::m_defaultUpFileName[] = "ta_bgm_cur1";
char CCommonListenBGM::m_defaultDownFileName[] = "ta_bgm_cur2";

char CCommonListenBGM::m_defaultMusicTitleGraphicsFilename[] = "ta_musictitle";

int CCommonListenBGM::m_defaultPrintX[] = {66,66+73,66+159,66+232,66+273};
int CCommonListenBGM::m_defaultCheckSizeX[] = {72,85,72,40,42};

char CCommonListenBGM::m_buttonName[][8] = 
{
	"rew",
	"play",
	"ff",
	"pause",
	"stop",
};

char CCommonListenBGM::m_defaultCannotMusicName[] = "HHH";
char CCommonListenBGM::m_defaultCannotMusicName1Byte[] = "???";

CCommonListenBGM::CCommonListenBGM(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(LISTENBGM_MODE);
//	m_classNumber = LISTENBGM_MODE;
	LoadSetupFile("ListenBGM",256);

	int codeByte = CMyFont::m_codeByte;


	m_musicNameCenterFlag = 1;
	GetInitGameParam(&m_musicNameCenterFlag,"musicNameCenterFlag");

	m_replaceChara = NULL;
	GetInitGameString(&m_replaceChara,"replaceChara");


	m_musicControl = m_game->GetMusicControl();

	GetBackExecSetup();

	m_playRestartScriptFlag = 0;
	GetInitGameParam(&m_playRestartScriptFlag,"playRestartScriptFlag");
	m_stopRestartScriptFlag = 0;
	GetInitGameParam(&m_stopRestartScriptFlag,"stopRestartScriptFlag");
	m_pauseRestartScriptFlag = 0;
	GetInitGameParam(&m_pauseRestartScriptFlag,"pauseRestartScriptFlag");

	CPicture* lpBG = m_commonBG;
	if (m_backScriptFlag) lpBG = NULL;
	int i = 0;
	for (i=0;i<5;i++)
	{
		m_button[i] = new CCommonCheckButton(m_setup,lpBG,m_buttonName[i]);
		m_button[i]->SetPicture(CSuperButtonPicture::GetPicture(3+i*2),0);
		m_button[i]->SetPicture(CSuperButtonPicture::GetPicture(3+i*2+1),1);
	}


	m_filenameBG = m_defaultBGFileName;
	GetInitGameString(&m_filenameBG,"fileNameBG");

//	m_filenameButton = m_defaultButtonFileName;
//	GetInitGameString(&m_filenameButton,"fileNameButton");

//	m_midi = m_game->GetMIDI();

//	m_bgmList = new CNameList();
//	m_bgmList->LoadFile("nnndir\\bgmlist.txt");
//	m_bgmKosuu = m_bgmList->GetNameKosuu() / 2;
	m_bgmKosuu = m_game->GetBGMKosuu();


	//name,tablenumber,minute,second,dmy,dmy,dmy,dmy
	m_bgmList = new CNameList();
	m_bgmList->LoadFile("nya\\listenbgmlist.xtx");

	
	m_volumeMin = 80;
	m_volumeMax = 100;

	GetInitGameParam(&m_volumeMin,"volumeMin");
	GetInitGameParam(&m_volumeMax,"volumeMax");


	int timeIsKosuu = 0;
	m_bgmKosuu = (m_bgmList->GetNameKosuu()) / 8;



	if (codeByte == 1)
	{
		if (m_replaceChara != NULL)
		{
			if ((*m_replaceChara) != 0)
			{
				char replaceChara = *m_replaceChara;

				for (int i=0;i<m_bgmKosuu;i++)
				{
					LPSTR musicName = m_bgmList->GetName(i*8);
					int ln = strlen(musicName);

					for (int k=0;k<ln;k++)
					{
						char c = musicName[k];
						if (c == replaceChara)
						{
							musicName[k] = ' ';
						}
					}
				}
			}
		}
	}






	m_musicNameMax = 12;
	GetInitGameParam(&m_musicNameMax,"musicNameMax");

	m_lengthGetFlag = new BOOL[m_bgmKosuu];
	m_musicLength = new int[m_bgmKosuu];
	m_musicNameLength = new int[m_bgmKosuu];
	m_musicNameLength2 = new int[m_bgmKosuu];

	m_musicName2 = new LPSTR[m_bgmKosuu];

	m_listenedFlag = new int[m_bgmKosuu];
	m_systemMusicNumber = new int[m_bgmKosuu];
	m_checkVar = new int[m_bgmKosuu];


	m_musicPrintKosuu = 8;
	GetInitGameParam(&m_musicPrintKosuu,"musicPrintNumber");

	m_checkListen = 0;
	GetInitGameParam(&m_checkListen,"checklisten");

	if (codeByte == 2)
	{
		m_cannotMusicName = m_defaultCannotMusicName;
	}
	else
	{
		m_cannotMusicName = m_defaultCannotMusicName1Byte;
	}
	GetInitGameString(&m_cannotMusicName,"cannotMusicName");

	m_useCannotByList = 0;
	GetInitGameParam(&m_useCannotByList,"useCannotByList");


	for (i=0;i<m_bgmKosuu;i++)
	{
		if (codeByte != 1)
		{
			m_musicNameLength[i] = (int)strlen(m_bgmList->GetName(i*8)) / 2;
		}
		else
		{
			m_musicNameLength[i] = (int)strlen(m_bgmList->GetName(i*8));
		}

		if (m_checkListen == 0)
		{
			m_musicName2[i] = m_bgmList->GetName(i*8);
		}
		else
		{
			if (m_useCannotByList == 0)
			{
				m_musicName2[i] = m_cannotMusicName;
			}
			else
			{
				m_musicName2[i] = m_bgmList->GetName(i*8+4);
			}
		}


		if (codeByte != 1)
		{
			m_musicNameLength2[i] = (int)strlen(m_musicName2[i]) / 2;
		}
		else
		{
			m_musicNameLength2[i] = (int)strlen(m_musicName2[i]);
		}

		if (codeByte == 1)
		{
			if (m_replaceChara != NULL)
			{
				if ((*m_replaceChara) != 0)
				{
					char replaceChara = *m_replaceChara;
					for (int k=0;k<m_musicNameLength2[i];k++)
					{
						char c = m_musicName2[i][k];
						if (c == replaceChara)
						{
							m_musicName2[i][k] = ' ';
						}
					}
				}
			}
		}





		LPSTR checkName = m_bgmList->GetName(i*8+5);
		int sysnum = 0;
		if ((*checkName) != '@')
		{
			if ((*checkName) != '*')
			{
				sysnum = atoi(checkName);
				if (sysnum>0)
				{
					m_systemMusicNumber[i] = sysnum-1;
				}
			}
			else
			{
				sysnum = -1;
				m_systemMusicNumber[i] = -1;
			}
		}

		if (sysnum == 0)
		{
			m_systemMusicNumber[i] = m_game->SearchMusicNumber(m_bgmList->GetName(i*8+1));
		}


		m_checkVar[i] = -1;
		LPSTR varName = m_bgmList->GetName(i*8+6);
		if ((*varName) != '@')
		{
			m_checkVar[i] = m_game->GetVarNumber(varName);
		}
	}

	m_pageMax = m_bgmKosuu;


//	m_message = new CMyMessage(m_game);
	m_message = new CMyMessage(m_game->GetMyFont());

	LPSTR filenameVolume = m_defaultVolumeFileName;
	GetInitGameString(&filenameVolume,"fileNameVolume");
	CPicture* volPic = m_game->GetSystemPicture(filenameVolume);

	int volumePrintX = 53;
	int volumePrintY = 464;
	int volumeSizeX = 338;
	int volumeSizeY = 17;

	GetInitGameParam(&volumePrintX,"volumePrintX");
	GetInitGameParam(&volumePrintY,"volumePrintY");
	GetInitGameParam(&volumeSizeX,"volumeSizeX");
	GetInitGameParam(&volumeSizeY,"volumeSizeY");

	int volumeSliderTransFlag = 1;
	GetInitGameParam(&volumeSliderTransFlag,"volumeSliderTransFlag");

	if (m_backScriptFlag)
	{
		m_volumeSlider   = new CMySlider(volPic, 100, volumePrintX, volumePrintY, volumeSizeX,volumeSizeY, 0,0, volumeSliderTransFlag, NULL,TRUE);
	}
	else
	{
		m_volumeSlider   = new CMySlider(volPic, 100, volumePrintX, volumePrintY, volumeSizeX,volumeSizeY, 0,0, volumeSliderTransFlag, m_commonBG,TRUE);
	}


//	m_oldSelectCursorType = 0;
//	GetInitGameParam(&m_oldSelectCursorType,"oldSelectCursorType");

//	m_oldCursorPicType = 1;
//	GetInitGameParam(&m_oldCursorPicType,"oldCursorPicType");

//	m_musicPauseTenmetsuCount = 0;
//	m_barPicCount = 0;

	m_page = 0;
	m_scrollY = 0;
	m_timeCount = 0;
	m_nowTime = 0;


	m_musicFadeInTime = 0;
	m_musicFadeOutTime = 20;

	GetInitGameParam(&m_musicFadeInTime,"musicFadeInTime");
	GetInitGameParam(&m_musicFadeOutTime,"musicFadeOutTime");

	m_bgmLoopFlag = 0;
	GetInitGameParam(&m_bgmLoopFlag,"bgmLoopFlag");

//	CPicture* backPic = m_game->GetSystemPicture("back_bt");
//	m_back = new CBack(backPic,570,435,NULL);
//	m_back = m_game->GetBackButton();

//	CPicture* upPic = m_game->GetSystemPicture("ta_bgm_cur1");
//	CPicture* downPic = m_game->GetSystemPicture("ta_bgm_cur2");

//	m_updown = new CUpDown(m_pageMax,41,20,300,145,300,377,upPic,downPic,m_commonBG);
/*
	LPSTR filenameUp = m_defaultUpFileName;
	GetInitGameString(&filenameUp,"fileNameUp");
	LPSTR filenameDown = m_defaultDownFileName;
	GetInitGameString(&filenameDown,"fileNameDown");

	CPicture* pic = m_game->GetSystemPicture(filenameUp);
	CPicture* pic2 = m_game->GetSystemPicture(filenameDown);

	int updownSizeX = 41;
	int updownSizeY = 20;
	int updownAnime = 5;

	int upPrintX = 207;
	int upPrintY = 182;
	int downPrintX = 207;
	int downPrintY = 182 + 230;

	GetInitGameParam(&updownSizeX,"updownSizeX");
	GetInitGameParam(&updownSizeY,"updownSizeY");
	GetInitGameParam(&updownAnime,"updownAnime");
	GetInitGameParam(&upPrintX,"upPrintX");
	GetInitGameParam(&upPrintY,"upPrintY");
	GetInitGameParam(&downPrintX,"downPrintX");
	GetInitGameParam(&downPrintY,"downPrintY");
	m_updown = new CUpDownButtonGroup();
//	m_updown->CreateUpDownButton(pic,pic2,207,182,207,182+230,41,20,TRUE,m_commonBG,FALSE,5);
	m_updown->CreateUpDownButton(pic,pic2,upPrintX,upPrintY,downPrintX,downPrintY,updownSizeX,updownSizeY,TRUE,m_commonBG,FALSE,updownAnime);


*/


	m_musicNameColorR = 255;
	m_musicNameColorG = 255;
	m_musicNameColorB = 255;

	GetInitGameParam(&m_musicNameColorR,"messageColorR");
	GetInitGameParam(&m_musicNameColorG,"messageColorG");
	GetInitGameParam(&m_musicNameColorB,"messageColorB");

	m_cannotMusicNameColorR = 128;
	m_cannotMusicNameColorG = 128;
	m_cannotMusicNameColorB = 128;

	GetInitGameParam(&m_cannotMusicNameColorR,"cannotColorR");
	GetInitGameParam(&m_cannotMusicNameColorG,"cannotColorG");
	GetInitGameParam(&m_cannotMusicNameColorB,"cannotColorB");

	if (m_backScriptFlag)
	{
//@@		m_button = new CMyOldRadioButton(5,m_commonParts,NULL,TRUE);
	}
	else
	{
//@@		m_button = new CMyOldRadioButton(5,m_commonParts,m_commonBG,TRUE);
	}

	LPSTR suujiname = m_defaultNumberFileName;
	GetInitGameString(&suujiname,"filenameNumber");




	LPSTR selname = m_defaultCursorFileName;
	GetInitGameString(&selname,"filenameCursor");
	m_cursorPic = m_game->GetSystemPicture(selname);


	m_messageFontSize = 22;
	GetInitGameParam(&m_messageFontSize,"messageFontSize");

	m_fontSizeX = 16;
	m_fontSizeY = 22;

	GetInitGameParam(&m_fontSizeX,"fontSizeX");
	GetInitGameParam(&m_fontSizeY,"fontSizeY");

	m_fontNextX = m_fontSizeX;
	m_fontNextY = 0;

	GetInitGameParam(&m_fontNextX,"fontNextX");
	GetInitGameParam(&m_fontNextY,"fontNextY");


	m_suuji = NULL;
	m_trackAndTimePrintFlag = 1;
	GetInitGameParam(&m_trackAndTimePrintFlag,"trackAndTimePrintFlag");

	if (m_trackAndTimePrintFlag)
	{
		CPicture* lpSuujiPic = m_game->GetSystemPicture(suujiname);
		m_suuji = new CSuuji(lpSuujiPic,m_fontSizeX,m_fontSizeY,2,m_fontNextX,FALSE,TRUE,FALSE);
	}


	int mmd = m_game->GetMusicMode();





	for (i=0;i<m_bgmKosuu;i++)
	{
		int minute = atoi(m_bgmList->GetName(i*8+2));
		int second = atoi(m_bgmList->GetName(i*8+3));
		m_musicLength[i] = (minute * 60 + second + 1)*1000;	//1•b‚Ô‚ñ‚Í‚²‚Ü‚©‚µ
		m_lengthGetFlag[i] = TRUE;
	}

	m_musicPlayMode = MUSIC_STOP_MODE;

	m_trackNumberPrintX = 162;
	m_trackNumberPrintY = 101;

	GetInitGameParam(&m_trackNumberPrintX,"trackPrintX");
	GetInitGameParam(&m_trackNumberPrintY,"trackPrintY");

	m_minutePrintX = 276;
	m_minutePrintY = 101;

	GetInitGameParam(&m_minutePrintX,"minutePrintX");
	GetInitGameParam(&m_minutePrintY,"minutePrintY");

	m_secondPrintX = 334;
	m_secondPrintY = 101;

	GetInitGameParam(&m_secondPrintX,"secondPrintX");
	GetInitGameParam(&m_secondPrintY,"secondPrintY");


//	m_volumeCursorPrintX = 258;
//	m_volumeCursorPrintY = 410;

//	GetInitGameParam(&m_volumeCursorPrintX,"volumeCursorPrintX");
//	GetInitGameParam(&m_volumeCursorPrintY,"volumeCursorPrintY");
	



	m_cursorPattern1 = 0;
	m_cursorPattern2 = 0;
	m_cursorPercent = 100;
	m_cursorAnimeCount = 0;

	m_cursorAnimeType = 5;
	m_cursorAnimeSpeed = 1;
	m_cursorAnimePattern = 8;

	m_cursorAnimeFlag = 1;

	GetInitGameParam(&m_cursorAnimeFlag,"cursorAnimeFlag");

	GetInitGameParam(&m_cursorAnimeType,"cursorAnimeType");
	GetInitGameParam(&m_cursorAnimeSpeed,"cursorAnimeSpeed");
	GetInitGameParam(&m_cursorAnimePattern,"cursorAnimePattern");

//	m_volumeGazePrintX = 258;
//	m_volumeGazePrintY = 433;
//	m_volumeGazeSizeX = 175;
//	m_volumeGazeSizeY = 3;

//	m_volumeCheckStartX = 256;
//	m_volumeCheckStartY = 410;
//	m_volumeCheckSizeX = m_volumeGazeSizeX;
//	m_volumeCheckSizeY = 36;

//	m_musicNamePrintX = 76;
//	m_musicNamePrintY = 199;
	m_musicNamePrintX = 0;	//‚³‚Ô‚ñ (‚Õ‚ç‚·)
	m_musicNamePrintY = 0;	//‚³‚Ô‚ñ (‚Õ‚ç‚·)

//	m_musicNameSizeX = 294;
//	m_musicNameSizeY = 27;
//	m_musicNameNextY = 26;

	GetInitGameParam(&m_musicNamePrintX,"musicNamePrintX");
	GetInitGameParam(&m_musicNamePrintY,"musicNamePrintY");

	m_cursorPrintX = 76;
	m_cursorPrintY = 199;
	m_cursorSizeX = 294;
	m_cursorSizeY = 27;
	m_cursorNextX = 0;
	m_cursorNextY = 26;

	GetInitGameParam(&m_cursorPrintX,"cursorPrintX");
	GetInitGameParam(&m_cursorPrintY,"cursorPrintY");
	GetInitGameParam(&m_cursorSizeX,"cursorSizeX");
	GetInitGameParam(&m_cursorSizeY,"cursorSizeY");
	GetInitGameParam(&m_cursorNextX,"cursorNextX");
	GetInitGameParam(&m_cursorNextY,"cursorNextY");



	m_useMusicTitleGraphics = 0;
	m_musicTitlePic = NULL;
	m_musicTitleSizeX = m_cursorSizeX;
	m_musicTitleSizeY = m_cursorSizeY;
	m_musicTitlePrintX = 0;
	m_musicTitlePrintY = 0;
	m_musicTitleCount = 0;

	m_musicTitleAnimeControl = NULL;

	GetInitGameParam(&m_useMusicTitleGraphics,"useMusicTitleGraphics");
	if (m_useMusicTitleGraphics)
	{
		LPSTR fname = m_defaultMusicTitleGraphicsFilename;
		GetInitGameString(&fname,"filenameMusicTitle");
		m_musicTitlePic = new CPicture();
		char filename[256];
		wsprintf(filename,"sys\\%s",fname);
		m_musicTitlePic->LoadDWQ(filename);

		GetInitGameParam(&m_musicTitlePrintX,"musicTitlePrintX");
		GetInitGameParam(&m_musicTitlePrintY,"musicTitlePrintY");
		GetInitGameParam(&m_musicTitleSizeX,"musicTitleSizeX");
		GetInitGameParam(&m_musicTitleSizeY,"musicTitleSizeY");

		int musicTitleAnimePattern = 1;
		int musicTitleAnimeSpeed = 1;
		int musicTitleAnimeType = 1;
		GetInitGameParam(&musicTitleAnimePattern,"musicTitleAnimePattern");
		GetInitGameParam(&musicTitleAnimeSpeed,"musicTitleAnimeSpeed");
		GetInitGameParam(&musicTitleAnimeType,"musicTitleAnimeType");

		m_musicTitleAnimeControl = new CAnimeControl();
		m_musicTitleAnimeControl->SetParam(musicTitleAnimeType,musicTitleAnimePattern,musicTitleAnimeSpeed);

	}

	m_cursorIsUpper = 0;
	GetInitGameParam(&m_cursorIsUpper,"cursorIsUpper");


	int buttonPrintY = 133;

	int printX[5];
	int printY[5];
	int sizeX[5];
	int sizeY[5];
	int srcX[5];
	int srcY[5];
	int checkSizeX[5];
	int checkSizeY[5];

	for (i=0;i<5;i++)
	{
		printX[i] = m_defaultPrintX[i];
		printY[i] = buttonPrintY;
		sizeX[i] = 85;
		sizeY[i] = 29;
		srcX[i] = 0;
		srcY[i] = 29*i;
		checkSizeX[i] = m_defaultCheckSizeX[i];	//dummy
		checkSizeY[i] = 29;

		char name[256];

		wsprintf(name,"%sPrintX",m_buttonName[i]);
		GetInitGameParam(&printX[i],name);

		wsprintf(name,"%sPrintY",m_buttonName[i]);
		GetInitGameParam(&printY[i],name);

		wsprintf(name,"%sSizeX",m_buttonName[i]);
		GetInitGameParam(&sizeX[i],name);

		wsprintf(name,"%sSizeY",m_buttonName[i]);
		GetInitGameParam(&sizeY[i],name);

		wsprintf(name,"%sSrcX",m_buttonName[i]);
		GetInitGameParam(&srcX[i],name);

		wsprintf(name,"%sSrcY",m_buttonName[i]);
		GetInitGameParam(&srcY[i],name);

		wsprintf(name,"%sCheckSizeX",m_buttonName[i]);
		GetInitGameParam(&checkSizeX[i],name);

		wsprintf(name,"%sCheckSizeY",m_buttonName[i]);
		GetInitGameParam(&checkSizeY[i],name);
	
///@@@		m_button->SetData(i,printX[i],printY[i],sizeX[i],sizeY[i],srcX[i],srcY[i],checkSizeX[i],checkSizeY[i]);
	}

//	m_spectrumPrintFlag = 0;
	GetInitGameParam(&m_spectrumPrintFlag,"spectrumPrintFlag",0);

	m_ar = NULL;
	m_ai = NULL;
	m_windowFunction = NULL;
	m_logNTable = NULL;
	m_spectrumData = NULL;

	m_printSpectrum = NULL;
	m_fft = NULL;

	if (m_spectrumPrintFlag)
	{
		m_spectrumCalcuPoint = 256;
		GetInitGameParam(&m_spectrumCalcuPoint,"spectrumCalcuPoint");
		if (m_spectrumCalcuPoint >= 1024) m_spectrumCalcuPoint = 1024;
		if (m_spectrumCalcuPoint <= 64) m_spectrumCalcuPoint = 64;

		if (m_spectrumCalcuPoint < 128)
		{
			m_spectrumCalcuPoint = 64;
		}
		else if (m_spectrumCalcuPoint < 256)
		{
			m_spectrumCalcuPoint = 128;
		}
		else if (m_spectrumCalcuPoint < 512)
		{
			m_spectrumCalcuPoint = 256;
		}
		else if (m_spectrumCalcuPoint < 1024)
		{
			m_spectrumCalcuPoint = 512;
		}
		else
		{
			m_spectrumCalcuPoint = 1024;
		}


		m_spectrumPrintKosuu = 16;
		GetInitGameParam(&m_spectrumPrintKosuu,"spectrumPrintNumber");


		m_ar = new float[m_spectrumCalcuPoint];
		m_ai = new float[m_spectrumCalcuPoint];
		m_logNTable = new int[m_spectrumPrintKosuu];
		m_windowFunction = new float[m_spectrumCalcuPoint];
		m_spectrumData = new int[m_spectrumPrintKosuu];
		ZeroMemory(m_spectrumData,m_spectrumPrintKosuu*sizeof(int));


		//create window function

		float dv = (float)(m_spectrumCalcuPoint/2);
//		dv -= 0.5f;

		for (int i=0;i<m_spectrumCalcuPoint;i++)
		{
			float th = (float)i;
//			th -= dv;
			th /= dv;
			th *= 3.14159f*2.0;
			m_windowFunction[i] = (1.0f - (float)cos(th)) * 0.5f;
		}

		int startHz = 200;
		GetInitGameParam(&startHz,"spectrumStartHz");
		int endHz = 10000;
		GetInitGameParam(&endHz,"spectrumEndHz");

		float startLogHz = (float)log((float)startHz);
		float endLogHz = (float)log((float)endHz);


		for (int i=0;i<m_spectrumPrintKosuu;i++)
		{
			float logHz = startLogHz + (endLogHz - startLogHz) * ((float)i) / ((float)(m_spectrumPrintKosuu-1));
			float realHz = (float)exp(logHz);

			int nn = (int)(realHz * ((float)(m_spectrumCalcuPoint/2-1)) / 22050.0f);
			if (nn<1) nn = 1;
			if (nn>(m_spectrumCalcuPoint/2-1)) nn = m_spectrumCalcuPoint/2-1;

			m_logNTable[i] = nn;
		}

		m_fft = new CFFT();
		m_fft->MakeTable(m_spectrumCalcuPoint);

		m_printSpectrum = new CPrintSpectrum(m_spectrumPrintKosuu,m_setup);
	}



//	GetBackButtonPara();
	CreateBackButton();
	CreateUpDownButton();
	CreateUpDownBack();

	GetFadeInOutSetup();
	GetEnterExitVoiceFileName();

//	m_button->SetData(0,66    ,133, 85,29, 0,0, 72,29);	//REW
//	m_button->SetData(1,66+ 73,133, 85,29, 0,29,85,29);	//play
//	m_button->SetData(2,66+159,133, 85,29, 0,29*2,72,29);	//ff
//	m_button->SetData(3,66+232,133, 85,29, 0,29*3,40,29);	//pause
//	m_button->SetData(4,66+273,133, 85,29, 0,29*4,42,29);	//stop
}


CCommonListenBGM::~CCommonListenBGM()
{
	End();
}

void CCommonListenBGM::End(void)
{
	ENDDELETECLASS(m_printSpectrum);
	ENDDELETECLASS(m_fft);
	DELETEARRAY(m_spectrumData);
	DELETEARRAY(m_logNTable);
	DELETEARRAY(m_windowFunction);
	DELETEARRAY(m_ai);
	DELETEARRAY(m_ar);

	DELETEARRAY(m_checkVar);
	DELETEARRAY(m_systemMusicNumber);
	DELETEARRAY(m_listenedFlag);
	DELETEARRAY(m_musicName2);

	DELETEARRAY(m_lengthGetFlag);
	DELETEARRAY(m_musicLength);
	DELETEARRAY(m_musicNameLength2);
	DELETEARRAY(m_musicNameLength);

	ENDDELETECLASS(m_bgmList);
//	ENDDELETECLASS(m_bgmList);

//	ENDDELETECLASS(m_updown);
//	ENDDELETECLASS(m_back);
//@@@	ENDDELETECLASS(m_button);
	ENDDELETECLASS(m_suuji);
//	ENDDELETECLASS(m_cursorPic);
	ENDDELETECLASS(m_message);

	ENDDELETECLASS(m_volumeSlider);

	ENDDELETECLASS(m_musicTitleAnimeControl);
	ENDDELETECLASS(m_musicTitlePic);

	for (int i=0;i<5;i++)
	{
		ENDDELETECLASS(m_button[i]);
	}
}



int CCommonListenBGM::Init(void)
{
	if (m_spectrumPrintFlag)
	{
		m_musicControl->StartSpectrum();
		m_printSpectrum->Init();
	}

	if (m_backScriptFlag == FALSE)
	{
		char filename[256];
		wsprintf(filename,"sys\\%s",m_filenameBG);
		m_commonBG->LoadDWQ(filename);
	}

//	wsprintf(filename,"sys\\%s",m_filenameButton);
//	m_commonParts->LoadDWQ(filename);

	int i = 0;
	for (i=0;i<5;i++)
	{
		char filename999[256];

		CPicture* lpPic = m_button[i]->GetPicture(0);
		LPSTR name = m_button[i]->GetFileName(0);
		wsprintf(filename999,"sys\\%s",name);
		lpPic->LoadDWQ(filename999);

		lpPic = m_button[i]->GetPicture(1);
		name = m_button[i]->GetFileName(1);
		wsprintf(filename999,"sys\\%s",name);
		lpPic->LoadDWQ(filename999);

		m_button[i]->SetState(0);
		if (i == 4) m_button[i]->SetState(1);
		m_button[i]->Init();
	}

	LoadBackButtonPic();
	LoadUpDownButtonPic();


//	m_back->Init();
	SetBackButtonZahyo();

	if (m_musicTitleAnimeControl != NULL)
	{
		m_musicTitleAnimeControl->Init();
	}


	m_page = 0;
	m_pageMax = m_bgmKosuu;

	m_lastMusicNumber = 0;
	m_game->SetListenBGMParam(0,m_lastMusicNumber+1);

	m_updown->SetPage(m_page);
	m_updown->SetPageMax(m_pageMax);

	m_updownBack->Init();

	m_scrollY = 0;

	for (i=0;i<m_bgmKosuu;i++)
	{
		m_listenedFlag[i] = 1;
		if (m_checkListen)
		{
			if (m_systemMusicNumber[i] != -1)
			{
				m_listenedFlag[i] = m_game->CheckListenMusic(m_systemMusicNumber[i]);
			}
		}

		if (m_checkVar[i] != -1)
		{
			if (m_game->GetVarData(m_checkVar[i]))
			{
				m_listenedFlag[i] = 1;
			}
			else
			{
				m_listenedFlag[i] = 0;
			}
		}
	}

	m_timeCount = 0;
	m_nowTime = 0;
//	m_fwbkCount = 0;

//	m_game->PlayBGM(-1);

//	StopBGM();

	int vol = m_game->GetSystemParam(NNNPARAM_MUSICVOLUME);
	m_backVolume = vol;


	//adjust
	int v = vol;
	if (v<m_volumeMin) v = m_volumeMin;
	if (v>m_volumeMax) v = m_volumeMax;
	int dv = (m_volumeMax - m_volumeMin);
	if (dv<1) dv = 1;

	v -= m_volumeMin;
	v *= 100;
	v /= dv;

	if (v<0) v = 0;
	if (v>100) v = 100;

	m_volumeSlider->Init(v);


	vol = m_volumeMin + ((m_volumeMax - m_volumeMin) * v) / 100;

	m_maeVolume = vol;
	m_nowVolume = vol;

	m_musicControl->ChangeVolume(m_nowVolume);

	StopButton();
	return -1;
}


int CCommonListenBGM::Calcu(void)
{


	m_timeCount++;
	if (m_musicPlayMode == MUSIC_PLAY_MODE)
	{
		if (m_musicControl->CheckPlaying() == 0)
		{
			StopButton();
		}
	}


	if (m_musicPlayMode == MUSIC_PLAY_MODE)
	{
		CalcuCursorAnime();
	}







	m_maeVolume = m_nowVolume;

//	int bk = m_back->Calcu(m_mouseX,m_mouseY,m_trig1,m_trig1Mae,m_trig2,m_trig2Mae);
	int rt = m_updownBack->Calcu(m_inputStatus);
	if (rt != NNNBUTTON_NOTHING)
	{
		int nm = ProcessButtonGroup(rt);

		if (nm == 0)
		{
			m_game->SetSystemParam(NNNPARAM_MUSICVOLUME,m_backVolume);
			m_musicControl->StopMusic();
			
			if (m_spectrumPrintFlag)
			{
				m_musicControl->StopSpectrum();
			}

			m_game->StopMusic();
			m_game->SetBackScriptMode(FALSE);
			return ReturnFadeOut(OMAKE_MODE);
		}


		if (nm > 0)
		{
			m_page = nm-1;
			if (m_page<m_scrollY) m_scrollY = m_page;
			if (m_page>m_scrollY+(m_musicPrintKosuu-1)) m_scrollY = m_page-(m_musicPrintKosuu-1);
			m_updownBack->Init();
			CAreaControl::SetNextAllPrint();
			return -1;
		}
	}



	if (m_musicPlayMode == MUSIC_STOP_MODE)
	{
		rt = m_button[4]->Calcu(NULL);
	}
	else
	{
		rt = m_button[4]->Calcu(m_inputStatus);		//stop
	}
	if (rt != NNNBUTTON_NOTHING)
	{
		int nm = ProcessButtonGroup(rt);
		if (nm >= 0)
		{
			StopButton();
			m_button[4]->Init();
		}
	}


	rt = m_button[0]->Calcu(m_inputStatus);	//rew
	if (rt != NNNBUTTON_NOTHING)
	{
		int nm = ProcessButtonGroup(rt);
		if (nm >= 0)
		{
			BKButton();
			m_button[0]->Init();
		}
	}

	rt = m_button[2]->Calcu(m_inputStatus);		//ff
	if (rt != NNNBUTTON_NOTHING)
	{
		int nm = ProcessButtonGroup(rt);
		if (nm >= 0)
		{
			FWButton();
			m_button[2]->Init();
		}
	}
	



	if (m_musicPlayMode == MUSIC_STOP_MODE)
	{
		rt = m_button[1]->Calcu(m_inputStatus);	//play
	}
	else if (m_musicPlayMode == MUSIC_PAUSE_MODE)
	{
		rt = m_button[1]->Calcu(m_inputStatus);
	}
	else
	{
		if (m_playingNumber != m_page)
		{
			rt = m_button[1]->Calcu(m_inputStatus);
		}
		else
		{
			rt = m_button[1]->Calcu(NULL);
		}
	}

	if (rt != NNNBUTTON_NOTHING)
	{
		int nm = ProcessButtonGroup(rt);
		if (nm >= 0)
		{
			if (m_musicPlayMode == MUSIC_PAUSE_MODE)
			{
				PauseButton();
			}
			else
			{
				PlayButton();
			}
			m_button[1]->Init();
		}
	}


	if (m_musicPlayMode == MUSIC_PLAY_MODE)
	{
		rt = m_button[3]->Calcu(m_inputStatus);		//pause
	}
	else if (m_musicPlayMode == MUSIC_PAUSE_MODE)
	{
		rt = m_button[3]->Calcu(m_inputStatus);		//pause
	}
	else
	{
		rt = m_button[3]->Calcu(NULL);
	}

	if (rt != NNNBUTTON_NOTHING)
	{
		int nm = ProcessButtonGroup(rt);
		if (nm == 0)
		{
			PauseButton();
			m_button[3]->Init();
		}
		else if (nm == 1)
		{
			PauseButton();
			m_button[3]->Init();
		}
	}



//	if (m_musicPlayMode == MUSIC_PLAY_MODE)
//	{
//		m_barPicCount++;
//		m_barPicCount &= 0x7;
//	}


	int vol = m_volumeSlider->Calcu(m_mouseStatus);

	if (vol != -1)
	{
//char mes[256];
//sprintf(mes,"[vol=%d]",vol);
//OutputDebugString(mes);

		int vol2 = m_volumeMin + ((m_volumeMax-m_volumeMin)*vol)/100;
		if (vol2<0) vol2 = 0;
		if (vol2>100) vol2 = 100;

		m_nowVolume = vol2;
		if (m_nowVolume != m_maeVolume)
		{
//sprintf(mes,"[real vol=%d]",vol2);
//OutputDebugString(mes);

			//set volume
			m_musicControl->ChangeVolume(m_nowVolume);
		}
	}

	if (CheckClick())
	{
		POINT pt = m_mouseStatus->GetZahyo();
		int mouseX = pt.x;
		int mouseY = pt.y;

		int om = GetOnMouse(mouseX,mouseY);
		if (om != -1)
		{
			//‚¢‚Ü‚Æ‚¿‚ª‚Á‚½‚ç
			int ud = m_scrollY + om;

			if (ud != m_page)
			{
				m_page = ud;
				if (m_page<m_scrollY) m_scrollY = m_page;
				if (m_page>m_scrollY+(m_musicPrintKosuu - 1)) m_scrollY = m_page-(m_musicPrintKosuu - 1);

//				m_updown->SetPage(m_page);
				m_updown->SetPage(m_page);
				m_updown->SetPageMax(m_pageMax);

				PlayButton();
				CAreaControl::SetNextAllPrint();
				return -1;
			}
			else
			{
				if (m_musicPlayMode == MUSIC_PAUSE_MODE)
				{
					PauseButton();
				}
				else
				{
					PlayButton();
				}
			}
		}
	}

	return -1;
//	return m_nextMode;
}

int CCommonListenBGM::Print(void)
{
	PrintBackScriptOrBG();

	BOOL b = CAreaControl::CheckAllPrintMode();

	m_button[0]->Print();
	m_button[1]->Print();
	m_button[2]->Print();
	m_button[3]->Print();
	m_button[4]->Print();

//	CursorPicAnime();
	GetCursorAnimePic();

	if (b)
	{
		for (int i=0;i<m_musicPrintKosuu;i++)
		{
			PrintMusicName(m_scrollY + i);
		}
	}

	PrintMusicName(m_page);


//	if (m_eyeAnimeWait == 0) PrintEyeAnime();

	if (m_musicPlayMode != MUSIC_PAUSE_MODE)
	{
		int d;
		if (m_musicPlayMode == MUSIC_PLAY_MODE)
		{
			d = (m_musicLength[m_playingNumber] - m_nowTime) / 1000;
		}
		else if (m_musicPlayMode == MUSIC_PAUSE_MODE)
		{
			if (m_playingNumber == m_page)
			{
				d = (m_musicLength[m_page] - m_nowTime) / 1000;
			}
			else
			{
				d = m_musicLength[m_page] / 1000;
			}
		}
		else
		{
			d = m_musicLength[m_page] / 1000;
		}
		int minute = d / 60;
		int second = d % 60;

//		PrintSuuji(383,98,minute);
//		PrintSuuji(420,98,second);

		if (m_trackAndTimePrintFlag)
		{
			if (m_backScriptFlag == FALSE)
			{
				m_commonBG->Blt(m_minutePrintX,m_minutePrintY,m_minutePrintX,m_minutePrintY,m_fontNextX*1+m_fontSizeX,m_fontSizeY,FALSE);
				m_commonBG->Blt(m_secondPrintX,m_secondPrintY,m_secondPrintX,m_secondPrintY,m_fontNextX*1+m_fontSizeX,m_fontSizeY,FALSE);
			}

//			m_suuji->PrintSuuji(m_minutePrintX,m_minutePrintY,minute,0,2);
//			m_suuji->PrintSuuji(m_secondPrintX,m_secondPrintY,second,0,2);


			m_suuji->Print(m_minutePrintX,m_minutePrintY,minute);
			m_suuji->Print(m_secondPrintX,m_secondPrintY,second);

			CAreaControl::AddArea(m_minutePrintX,m_minutePrintY,m_fontNextX*1+m_fontSizeX,m_fontSizeY);
			CAreaControl::AddArea(m_secondPrintX,m_secondPrintY,m_fontNextX*1+m_fontSizeX,m_fontSizeY);

			if (m_backScriptFlag == FALSE)
			{
				m_commonBG->Blt(m_trackNumberPrintX,m_trackNumberPrintY,m_trackNumberPrintX,m_trackNumberPrintY,m_fontNextX*1+m_fontSizeX,m_fontSizeY,FALSE);
			}

			if (m_musicPlayMode == MUSIC_PLAY_MODE)
			{
//				m_suuji->PrintSuuji(m_trackNumberPrintX,m_trackNumberPrintY,m_playingNumber+1,0,2);
				m_suuji->Print(m_trackNumberPrintX,m_trackNumberPrintY,m_playingNumber+1);
			}
			else
			{
//				m_suuji->PrintSuuji(m_trackNumberPrintX,m_trackNumberPrintY,m_page+1,0,2);
				m_suuji->Print(m_trackNumberPrintX,m_trackNumberPrintY,m_page+1);
			}
			CAreaControl::AddArea(m_trackNumberPrintX,m_trackNumberPrintY,m_fontNextX*1+m_fontSizeX,m_fontSizeY);
		}
	}



	if (m_spectrumPrintFlag)
	{
		PrintSpectrum();
	}


//	m_suuji->PrintSuuji(m_trackNumberPrintX,m_trackNumberPrintY,m_page,0,2);
//	m_suuji->PrintSuuji(m_minutePrintX,m_minutePrintY,m_12,0,2);
//	m_suuji->PrintSuuji(m_secondPrintX,m_secondPrintY,34,0,2);

	m_back->Print(TRUE);

//@@@	m_button->Print(TRUE);
	if (m_musicPlayMode == MUSIC_PAUSE_MODE)
	{
		if ((m_timeCount & 0x7) < 4)
		{
//@@@			m_button->PutButton(3,TRUE);
		}
	}	

	m_updown->Print(TRUE);

	m_volumeSlider->Print(TRUE);

	if (m_musicTitleAnimeControl != NULL)
	{
		m_musicTitleAnimeControl->Calcu();
	}

	return -1;
}

void CCommonListenBGM::PlayButton(void)
{
//	StopBGM();

	if (m_lengthGetFlag[m_page] == FALSE)
	{
////		m_musicLength[m_page] = m_midi->GetLength(m_page);
		m_lengthGetFlag[m_page] = TRUE;
	}

	if (m_listenedFlag[m_page])
	{
		PlayBGM(m_page,1);
		m_musicPlayMode = 1;
		m_playingNumber = m_page;
		m_timeCount = 0;
		m_nowTime = 0;
		m_button[1]->SetState(1);	//playButton
		ChangeMusicMode(MUSIC_PLAY_MODE);
	}
	else
	{
	}


	m_button[3]->SetState(0);	//pausebutton off
	m_button[4]->SetState(0);	//stopbutton off

	m_button[1]->Init();
	m_button[3]->Init();
	m_button[4]->Init();

	CAreaControl::SetNextAllPrint();
}

void CCommonListenBGM::FWButton(void)
{
	if (m_checkListen == 0)
	{
		ChangePage(1);
	}
	else
	{
		int found = -1;

		for (int i=m_page+1;i<m_bgmKosuu;i++)
		{
			if (m_listenedFlag[i])
			{
				found = i;
				break;
			}
		}

		if (found == -1) found = m_page+1;
		ChangePage(found-m_page);
	}

	PlayButton();
}

void CCommonListenBGM::BKButton(void)
{
	if (m_checkListen == 0)
	{
		ChangePage(-1);
	}
	else
	{
		int found = -1;

		for (int i=m_page-1;i>=0;i--)
		{
			if (m_listenedFlag[i])
			{
				found = i;
				break;
			}
		}

		if (found == -1) found = m_page-1;
		ChangePage(found-m_page);
	}

	PlayButton();
}

void CCommonListenBGM::PauseButton(void)
{
	CAreaControl::SetNextAllPrint();

	m_timeCount = 0;

	if (m_musicPlayMode == MUSIC_PAUSE_MODE)
	{
		MusicResume();
		m_musicPlayMode = MUSIC_PLAY_MODE;

		ChangeMusicMode(MUSIC_PLAY_MODE);

		m_button[1]->SetState(1);	//playButton
		m_button[3]->SetState(0);	//pausebutton off
		m_button[4]->SetState(0);	//stopbutton off

		m_button[1]->Init();
		m_button[3]->Init();
		m_button[4]->Init();


		return;
	}

	if (m_musicPlayMode == MUSIC_PLAY_MODE)
	{
		MusicPause();
		m_musicPlayMode = MUSIC_PAUSE_MODE;

		ChangeMusicMode(MUSIC_PAUSE_MODE);

		m_button[1]->SetState(0);	//playButton
		m_button[3]->SetState(1);	//pausebutton off
		m_button[4]->SetState(0);	//stopbutton off

		m_button[1]->Init();
		m_button[3]->Init();
		m_button[4]->Init();

		return;
	}
}


void CCommonListenBGM::StopButton(void)
{
	CAreaControl::SetNextAllPrint();

	StopBGM();
	m_playingNumber = -1;
	m_musicPlayMode = MUSIC_STOP_MODE;

	ChangeMusicMode(MUSIC_STOP_MODE);

	m_button[1]->SetState(0);	//playButton
	m_button[3]->SetState(0);	//pausebutton off
	m_button[4]->SetState(1);	//stopbutton off

	m_button[1]->Init();
	m_button[3]->Init();
	m_button[4]->Init();
}


void CCommonListenBGM::ChangePage(int deltaPage)
{
	if (deltaPage < 0)
	{
		if (m_page>0)
		{
			m_page += deltaPage;
			if (m_page<m_scrollY) m_scrollY = m_page;
		}
	}

	if (deltaPage > 0)
	{
		if (m_page<m_pageMax-1)
		{
			m_page += deltaPage;
			if (m_page >= (m_scrollY + m_musicPrintKosuu))
			{
				m_scrollY = m_page - (m_musicPrintKosuu - 1);
			}
		}
	}

	m_updown->SetPage(m_page);
	m_updown->SetPageMax(m_pageMax);

	CAreaControl::SetNextAllPrint();
}

int CCommonListenBGM::GetOnMouse(int mouseX,int mouseY)
{
	for (int i=0;i<m_musicPrintKosuu;i++)
	{
		int x = mouseX - (m_cursorPrintX + i * m_cursorNextX);
		int y = mouseY - (m_cursorPrintY + i * m_cursorNextY);

		if ((x>=0) && (x<m_cursorSizeX) && (y>=0) && (y<m_cursorNextY)) return i;
	}

	return -1;
}



void CCommonListenBGM::PrintMusicName(int n)
{
	int codeByte = CMyFont::m_codeByte;

	//erase
	int y = n - m_scrollY;
	if ((y<0) || (y>(m_musicPrintKosuu-1))) return;

	//erase
	int putX = m_cursorPrintX + y * m_cursorNextX;
	int putY = m_cursorPrintY + y * m_cursorNextY;
	int sizeX = m_cursorSizeX;
	int sizeY = m_cursorSizeY;

	if (m_backScriptFlag == FALSE)
	{
		m_commonBG->Blt(putX,putY,putX,putY,sizeX,sizeY,FALSE);
	}

	CAreaControl::AddArea(putX,putY,sizeX,sizeY);

	//cursor
	if (n == m_page)
	{
		if (m_cursorIsUpper == 0)
		{
			PrintCursor(y);
		}
	}


	//message
	putX = m_cursorPrintX + m_musicNamePrintX + y * m_cursorNextX;
	putY = m_cursorPrintY + m_musicNamePrintY + y * m_cursorNextY;
	int ln = m_musicNameLength[n];

	int colR = m_musicNameColorR;
	int colG = m_musicNameColorG;
	int colB = m_musicNameColorB;

	LPSTR musicName	= m_bgmList->GetName(n*8);

	int musicPicN = n+1;

	if (m_checkListen)
	{
		if (m_listenedFlag[n] == 0)
		{
			ln = m_musicNameLength2[n];
			musicName = m_musicName2[n];
			colR = m_cannotMusicNameColorR;
			colG = m_cannotMusicNameColorG;
			colB = m_cannotMusicNameColorB;

			musicPicN = 0;
		}
	}

	if (m_musicNameCenterFlag)
	{
		if (codeByte != 1)
		{
			putX += ((m_musicNameMax-ln)*(m_messageFontSize+1))/2;
		}
		else
		{
			putX += ((m_musicNameMax-ln)*(m_messageFontSize/2+1))/2;
		}
	}


	if (m_useMusicTitleGraphics == 0)
	{
		m_message->PrintMessage(putX,putY,musicName,m_messageFontSize,colR,colG,colB,2,24,0);
	}
	else
	{
		int putXX = m_cursorPrintX + m_musicNamePrintX + y * m_cursorNextX;
		int putYY = m_cursorPrintY + m_musicNamePrintY + y * m_cursorNextY;
		putXX += m_musicTitlePrintX;
		putYY += m_musicTitlePrintY;

		int pic1 = m_musicTitleAnimeControl->GetAnimePic1();
		int pic2 = m_musicTitleAnimeControl->GetAnimePic2();
		int ps = m_musicTitleAnimeControl->GetAnimePercent();
		int srcX1 = pic1 * m_musicTitleSizeX;
		int srcY1 = musicPicN * m_musicTitleSizeY;
		int srcX2 = pic2 * m_musicTitleSizeX;
		int srcY2 = musicPicN * m_musicTitleSizeY;

		if ((pic1 == pic2) || (ps == 100))
		{
			m_musicTitlePic->Blt(putXX,putYY,srcX1,srcY1,m_musicTitleSizeX,m_musicTitleSizeY,TRUE);
		}
		else
		{
			m_musicTitlePic->ChangeTranslateBlt(putXX,putYY,srcX1,srcY1,m_musicTitleSizeX,m_musicTitleSizeY,ps,100-ps,m_musicTitlePic,srcX2,srcY2);
		}
	}


	if (n == m_page)
	{
		//cursor print upper title graphics
		if (m_cursorIsUpper)
		{
			PrintCursor(y);
		}
	}
}



void CCommonListenBGM::PrintCursor(int y)
{
	CPicture* lpPic = m_cursorPic;
	if (lpPic == NULL) return;

	int sizeX = m_cursorSizeX;
	int sizeY = m_cursorSizeY;

	int srcX = 0;
	int srcY = sizeY * m_cursorPattern1;
	int srcY2 = sizeY * m_cursorPattern2;

	if (m_cursorAnimeFlag == 0)
	{
		srcX = 0;
		srcY = 0;
	}

	int putX = m_cursorPrintX + y * m_cursorNextX;
	int putY = m_cursorPrintY + y * m_cursorNextY;

	if (m_cursorPercent == 100)
	{
		lpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
	}
	else if (m_cursorPercent == 0)
	{
		lpPic->Blt(putX,putY,srcX,srcY2,sizeX,sizeY,TRUE);
	}
	else
	{
		int ps2 = 100 - m_cursorPercent;
		int* lpBuffer2 = (int*)(lpPic->GetBuffer());
		char* lpMask2 = (char*)(lpPic->GetMaskPic());
	
		int deltaX = 0;
		int deltaY = srcY2 - srcY;

		SIZE sz = lpPic->GetPicSize();

		lpBuffer2 += deltaX;
		lpBuffer2 += deltaY * sz.cx;

		lpMask2 += deltaX;
		lpMask2 += deltaY * sz.cx;


//		lpPic->ChangeTranslateBlt(putX,putY,srcX,srcY,sizeX,sizeY,m_cursorPercent,ps2,lpBuffer2,lpMask2,lpPic);
		lpPic->ChangeTranslateBlt(putX,putY,srcX,srcY,sizeX,sizeY,m_cursorPercent,ps2,lpPic,srcX,srcY2);

	}
}





void CCommonListenBGM::StopBGM(void)
{
	m_musicControl->StopMusic();
}


int CCommonListenBGM::GetPlayTime(void)
{
	if (m_game->GetSystemParam(NNNPARAM_BGMMODE) == 0) return 0;//m_midi->GetTime();

//	int tm = m_game->GetNowCdTime();
	int tm = 0;
	tm *= 1000;

	return tm;
}


BOOL CCommonListenBGM::CheckPlaying(void)
{
	if (m_game->GetSystemParam(NNNPARAM_BGMMODE) == 0) return 0;//m_midi->CheckPlaying();

	return FALSE;
//	return m_game->CheckCDPlaying();
}


int CCommonListenBGM::GetMusicLength(int n)
{
	if (m_game->GetSystemParam(NNNPARAM_BGMMODE) == 0) return m_musicLength[n] - 5;
	return m_musicLength[n];
}



void CCommonListenBGM::PlayBGM(int n, int lp)
{
	m_lastMusicNumber = n;

	LPSTR musicname = m_bgmList->GetName(m_page*8+1);
	int loopCount = 1;

	if (m_bgmLoopFlag)
	{
		loopCount = 0;
	}

//char mes[256];
//sprintf(mes,"[play vol=%d]",m_nowVolume);
//OutputDebugString(mes);
	//m_game->PlayMusic(musicname,loopCount,m_nowVolume,m_musicFadeInTime,m_musicFadeOutTime);
	m_musicControl->PlayMusic(musicname,loopCount,m_nowVolume,m_musicFadeInTime,m_musicFadeOutTime);
}


void CCommonListenBGM::MusicResume(void)
{
	m_musicControl->ResumeMusic();
}

void CCommonListenBGM::MusicPause(void)
{
	m_musicControl->PauseMusic();
}


void CCommonListenBGM::CreateStartScreen(void)
{
	//menu setup?

	//script exec?

	Print();
}


void CCommonListenBGM::CalcuCursorAnime(void)
{
	int type = m_cursorAnimeType;
	int speed = m_cursorAnimeSpeed;
	int count = m_cursorAnimeCount;
	int pattern = m_cursorAnimePattern;

	if (m_cursorAnimeFlag)
	{
		if (speed<1) speed = 1;

		int revFlag = 0;
		int dv = pattern;

		if ((type == 3) || (type == 4) || (type == 7) || (type == 8))
		{
			dv = (pattern-1) * 2;
			if (dv<1) dv = 1;
			revFlag = 1;
		}

		dv *= speed;

		int limitFlag = 0;
		if ((type == 2) || (type == 4) || (type == 6) || (type == 8))
		{
			limitFlag = 1;
		}

		count += 1;
		if (limitFlag)
		{
			if (count >= dv) count = dv;
		}
		else
		{
			count %= dv;
		}

		m_cursorAnimeCount = count;
	}
}

void CCommonListenBGM::GetCursorAnimePic(void)
{
	int type = m_cursorAnimeType;
	int speed = m_cursorAnimeSpeed;
	int count = m_cursorAnimeCount;
	int pattern = m_cursorAnimePattern;

	int revFlag = 0;
	int dv = pattern;

	if (speed<1) speed = 1;

	if ((type == 3) || (type == 4) || (type == 7) || (type == 8))
	{
		dv = (pattern-1) * 2;
		if (dv<1) dv = 1;
		revFlag = 1;
	}

	int limitFlag = 0;
	if ((type == 2) || (type == 4) || (type == 6) || (type == 8))
	{
		limitFlag = 1;
	}

	int pic1 = count / speed;
	int pic2 = pic1+1;
	
	if (limitFlag)
	{
		int limData = dv-1;
		if (revFlag) limData = dv;

		if (pic1>=dv) pic1 = limData;
		if (pic2>=dv) pic2 = limData;
	}

	pic2 %= dv;

	int percent = 100;


	if (revFlag)
	{
		if (pic1 >= pattern) pic1 = (pattern-1)*2 - pic1;
		if (pic2 >= pattern) pic2 = (pattern-1)*2 - pic2;
	}

	if (type >= 5)
	{
		percent = 100 * (speed - (count - ((count / speed) * speed)));
		percent /= speed;
	}


	m_cursorPattern1 = pic1;
	m_cursorPattern2 = pic2;
	m_cursorPercent = percent;
}


void CCommonListenBGM::ChangeMusicMode(int md)
{
	m_game->SetListenBGMParam(md,m_lastMusicNumber+1);

	//
	if (m_backScriptFlag)
	{
		if (md == MUSIC_PLAY_MODE)
		{
			if (m_playRestartScriptFlag)
			{
				m_game->RestartBackScript();
			}
		}
		else if (md == MUSIC_STOP_MODE)
		{
			if (m_stopRestartScriptFlag)
			{
				m_game->RestartBackScript();
			}
		}
		else if (md == MUSIC_PAUSE_MODE)
		{
			if (m_pauseRestartScriptFlag)
			{
				m_game->RestartBackScript();
			}
		}
	}

	CAreaControl::SetNextAllPrint();
}


void CCommonListenBGM::PrintSpectrum(void)
{
	if (m_musicPlayMode == MUSIC_PLAY_MODE)
	{
		m_musicControl->GetWaveCut(m_ar,m_spectrumCalcuPoint);


		for (int i=0;i<m_spectrumCalcuPoint;i++)
		{
			m_ai[i] = 0.0f;
		}

		for (int i=0;i<m_spectrumCalcuPoint;i++)
		{
			m_ar[i] *= m_windowFunction[i];
		}

		m_fft->Calcu(m_spectrumCalcuPoint,m_ar,m_ai);

		for (int i=0;i<m_spectrumPrintKosuu;i++)
		{
			int nn = m_logNTable[i];
			int nn2;
			if (i < m_spectrumPrintKosuu-1)
			{
				nn2 = m_logNTable[i+1];
			}
			else
			{
				nn2 = m_spectrumPrintKosuu;
			}

			int k = nn2 - nn;
			if (k<1) k = 1;


			float rsum = 0.0;

			for (int p=0;p<k;p++)
			{
				float ar = m_ar[nn+p];
				float ai = m_ai[nn+p];
				float rr = (float)sqrt(ar*ar + ai*ai);
				rr = (float)log(rr+0.00001f);
				rr /= (float)log(10.0f);
				rr *= 20.0f;
				if (rr<-100.0f) rr = -100.0f;
				rsum += rr;
			}
			rsum /= ((float)k);


			int sizeY = (int)(100.0f+rsum);
			m_spectrumData[i] = sizeY;
		}
	}
	else if (m_musicPlayMode == MUSIC_STOP_MODE)
	{
		ZeroMemory(m_spectrumData,m_spectrumPrintKosuu*sizeof(int));
	}

	//print
	m_printSpectrum->Print(m_spectrumData);
}



/*_*/

