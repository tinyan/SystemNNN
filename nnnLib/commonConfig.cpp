//
// commonConfig.cpp
//



#include <windows.h>
#include <stdio.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\nnnButtonStatus.h"

#include "..\nnnUtilLib\menuButtonGroup.h"
#include "..\nnnUtilLib\menuButtonSetup.h"

#include "..\nnnUtilLib\commonButton.h"
#include "..\nnnUtilLib\commonMultiStateButton.h"
#include "..\nnnUtilLib\commonCheckButton.h"

#include "..\nnnUtilLib\commonBackButton.h"
#include "..\nnnUtilLib\commonUpDownButtonGroup.h"
#include "..\nnnUtilLib\commonUpDownBack.h"

#include "..\nnnUtilLib\commonRadioButton.h"
#include "..\nnnUtilLib\commonRadioButtonGroup.h"

#include "..\\nnnUtilLib\superButtonPicture.h"

#include "..\\nnnUtilLib\myMessage.h"


#include "..\nnnUtilLib\mySlider.h"
#include "..\nnnUtilLib\namelist.h"

#include "commonMode.h"
#include "commonSystemSoundName.h"
#include "commonSystemParamName.h"

#include "..\nnnUtilLib\inputStatus.h"

#include "..\nyanDirectXLib\\mydirectsound.h"

#include "gameCallBack.h"

#include "commonGeneral.h"
#include "commonConfig.h"





#include "..\nnnUtilLib\commonGameVersion.h"


char CCommonConfig::m_defaultBGFileName[] = "bg_config";





char CCommonConfig::m_defaultBarFileName[] = "ta_opt_bar";
//char CCommonConfig::m_defaultCheckBoxFileName[] = "ta_opt_chk";
//char CCommonConfig::m_defaultRadioButtonFileName[] = "ta_opt_chk";

//char CCommonConfig::m_defaultBadButtonFileName[] = "ta_bad_chk";


char CCommonConfig::m_defaultPageNumberVarName[] = "�R���t�B�O�y�[�W";

char CCommonConfig::m_defaultSampleText[] = "�T���v���e�L�X�g";

//#define VOICEBUTTONNUMBER_OFFSET 100
//#define BACKBUTTONCLICKING_OFFSET 200
//#define ADDRADIOBUTTON_OFFSET 300








#define EXT_SE_SOUND 0
#define EXT_SE_VOICE 1
#define EXT_SE_MESSAGE 2
#define EXT_SE_MOVIE 3
#define EXT_SE_SOUNDVOICE 4
#define EXT_SE_AUTOSLIDER 5
#define EXT_SE_WINDOWPERCENT 6

//#define EXT_SE_WINDOW 3
//#define EXT_SE_READ 4
//#define EXT_SE_AUTO 5
//#define EXT_SE_MIDICDDA 6
//#define EXT_SE_VOICEON 7
//#define EXT_SE_VOICEOFF 8

int CCommonConfig::m_n2VolumeSystemParamTable[]=
{
	NNNPARAM_MESSAGESPEED,
	NNNPARAM_MUSICVOLUME,
	NNNPARAM_SOUNDVOLUME,
	NNNPARAM_VOICEVOLUME,
	NNNPARAM_MOVIEVOLUME,
	NNNPARAM_SOUNDVOICEVOLUME,
	NNNPARAM_WINDOWPERCENT,
	NNNPARAM_AUTOSPEEDSLIDER,
	NNNPARAM_TOTALVOLUME,
	NNNPARAM_SCRIPTSEVOLUME,
};

int CCommonConfig::m_n2VolumeSwitchSystemParamTable[]=
{
	0,
	NNNPARAM_MUSICSWITCH,
	NNNPARAM_SOUNDSWITCH,
	NNNPARAM_VOICESWITCH,
	NNNPARAM_MOVIESWITCH,
	NNNPARAM_SOUNDVOICESWITCH,
	0,
	0,
	NNNPARAM_SCRIPTSESWITCH,
};

char CCommonConfig::m_volumeName[][16]=
{
	"messageSpeed",
		
	"music",
	"sound",
	"voice",
	"movie",
	"soundvoice",

	"windowPercent",
	"autoSpeed",

	"total",
	"scriptse",
};

int CCommonConfig::m_defaultVolumeDevideTable[]=
{
	4,
	100,100,100,100,100,
	100,
	4,

	100,100,100,100,100,100,100,100,//dummy
};

int CCommonConfig::m_defaultBunkatsuTable[]=
{
	3,
	0,0,9,0,0,
	0,3
};

int CCommonConfig::m_defaultIsVoiceTable[]=
{
	1,
	0,0,0,0,0,
	0,1,
};

char CCommonConfig::m_modeButtonName[][16]=
{
	"screen",
	"skip",
	"auto",
};

char CCommonConfig::m_checkButtonName[][32]=
{
	"autoContinue",
	"autoSkip",
	"changeReadColor",
	"changeSelectColor",
	"continueVoice",
};


//
// radioButton	0,1 window,fullscreen
//				2,3 kidoku,subete
//				4,5 autoOff autoOn
//				6,7 midi cdda
//

//char m_defaultBGFileName[] = "config_bg";

CCommonConfig::CCommonConfig(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	int i = 0;

	SetClassNumber(CONFIG_MODE);
//	m_classNumber = CONFIG_MODE;
	LoadSetupFile("Config",2048);

	m_message = m_game->GetMyMessage();

	for (i = 0; i < 5; i++)
	{
		m_autoSe[i] = 0;
	}

	GetBackExecSetup();
	GetAllPrintSetup();

	m_page = 0;
	m_pageMax = 1;
	GetInitGameParam(&m_pageMax,"modePageMax");

	m_realVolumeLimitMin = 0;
	m_realVolumeLimitMax = 100;

//	m_volumePrintPage--;
//	m_messageSpeedPrintPage--;
//	m_voicePrintPage--;
//	m_modeButtonPrintPage--;



	m_pageMode = 0;
	if (m_pageMax>1) m_pageMode = 1;			//1:updown 2:tab
	GetInitGameParam(&m_pageMode,"pageMode");

	m_mustStartPage1Flag = 0;
	GetInitGameParam(&m_mustStartPage1Flag,"mustStartPage1Flag");

	CPicture* lpBG = m_commonBG;
	if (m_backScriptFlag) lpBG = NULL;
	if (m_mustAllPrintFlag) lpBG = NULL;


	m_pageNumberVarNumber = -1;
	m_pageNumberSetFlag = 0;

	m_pageNumberVarName = m_defaultPageNumberVarName;
	GetInitGameParam(&m_pageNumberSetFlag,"pageNumberSetFlag");
	if (m_pageNumberSetFlag)
	{
		GetInitGameString(&m_pageNumberVarName,"pageNumberVarName");
		m_pageNumberVarNumber = m_game->GetVarNumber(m_pageNumberVarName);
	}

	m_changePageRestartScriptFlag = 0;
	GetInitGameParam(&m_changePageRestartScriptFlag,"changePageRestartScriptFlag");


	m_bgFileName = new LPSTR[m_pageMax];

	m_bgFileName[0] = m_defaultBGFileName;
	GetInitGameString(&m_bgFileName[0],"filenameBG");
	GetInitGameString(&m_bgFileName[0],"filenameBG1");

	for (i=1;i<m_pageMax;i++)
	{
		m_bgFileName[i] = m_bgFileName[i-1];
		char name[256];
		wsprintf(name,"filenameBG%d",i+1);
		GetInitGameString(&m_bgFileName[i],name);
	}



	if (m_pageMax > 0)
	{
		m_useEffectPicKosuu = new int[m_pageMax];
		m_useSuperPicKosuu = new int[m_pageMax];
	}


	for (i=0;i<m_pageMax;i++)
	{
		m_useEffectPicKosuu[i] = 0;
		m_useSuperPicKosuu[i] = 3;

		if (m_backScriptFlag) m_useEffectPicKosuu[i] = 16;//all used
	}

	m_inSetVar = -1;
	m_inSetVarData = 0;

	LPSTR inSetVarName = NULL;
	if (GetInitGameString(&inSetVarName, "inSetVarName"))
	{
		if (inSetVarName != NULL)
		{
			m_inSetVar = m_game->GetVarNumber(inSetVarName);
			GetInitGameParam(&m_inSetVarData, "inSetVarData");
		}
	}

	m_outSetVar = -1;
	m_outSetVarData = 0;

	LPSTR outSetVarName = NULL;
	if (GetInitGameString(&outSetVarName, "outSetVarName"))
	{
		if (outSetVarName != NULL)
		{
			m_outSetVar = m_game->GetVarNumber(outSetVarName);
			GetInitGameParam(&m_outSetVarData, "outSetVarData");
		}
	}


	m_tabButton = NULL;
//	m_ppTabButton = NULL;

	if (m_pageMode == 2)
	{
		m_tabButton = new CCommonRadioButtonGroup(m_setup,"tab",lpBG,m_pageMax,NULL);

		for (i=0;i<m_pageMax;i++)
		{
			CPicture* lpPic = GetUseOkPicture(-1);	//use all
			m_tabButton->SetPicture(lpPic,i,-1);
		}
	}

	m_volumeKosuu = 5+1;//old�Ƃ̌݊����̂���
	GetInitGameParam(&m_volumeKosuu,"volumeNumber");


	m_volumeMin = 80;
	m_volumeMax = 100;

	GetInitGameParam(&m_volumeMin,"volumeMin");
	GetInitGameParam(&m_volumeMax,"volumeMax");

#if defined __USE_XAUDIO2__
	if (CMyDirectSound::m_xAudioFlag)
	{
		GetInitGameParam(&m_volumeMin, "volumeMinXAudio2");
		GetInitGameParam(&m_volumeMax, "volumeMaxXAudio2");
		GetInitGameParam(&m_volumeMin, "volumeMinWin10");
		GetInitGameParam(&m_volumeMax, "volumeMaxWin10");
	}
#endif


	m_seTable = new int[m_volumeKosuu];
	m_volumeDevideTable = new int[m_volumeKosuu];
	m_bunkatsuTable = new int[m_volumeKosuu];
	m_isVoiceTable = new int[m_volumeKosuu];
	for (int i=0;i<m_volumeKosuu;i++)
	{
		m_seTable[i] = -1;
		m_volumeDevideTable[i] = 100;
		m_bunkatsuTable[i] = 0;
	}


	for (i=0;i<m_volumeKosuu;i++)
	{
		char name[256];
		int volumeMaxData = m_defaultVolumeDevideTable[i];
		sprintf_s(name,sizeof(name),"%sVolumeDevide",m_volumeName[i]);
		GetInitGameParam(&volumeMaxData,name);
		m_volumeDevideTable[i] = volumeMaxData;
	}

	m_modeButtonKosuu = 3;
	m_checkButtonKosuu = 5;

	//if use movie volumekosuu++;


	m_windowMessageKosuu = 0;
	GetInitGameParam(&m_windowMessageKosuu,"windowMessageNumber");
	m_windowMessage = new LPSTR[m_windowMessageKosuu+1];
	for (i=0;i<m_windowMessageKosuu;i++)
	{
		m_windowMessage[i] = NULL;
		LPSTR winMes = NULL;
		char name[1024];
		wsprintf(name,"windowMessage%d",i+1);
		if (GetInitGameString(&winMes,name))
		{
			m_windowMessage[i] = winMes;
		}
	}

	m_messagePrintX = 0;
	m_messagePrintY = 0;
	m_messageNextX = 0;
	m_messageNextY = 20;
	m_messageFontSize = 24;
	m_messageColorR = 255;
	m_messageColorG = 255;
	m_messageColorB = 255;
	m_messageColorA = 255;
	GetInitGameParam(&m_messagePrintX,"messagePrintX");
	GetInitGameParam(&m_messagePrintY,"messagePrintY");
	GetInitGameParam(&m_messageNextX,"messageNextX");
	GetInitGameParam(&m_messageNextY,"messageNextY");
	GetInitGameParam(&m_messageFontSize,"messageFontSize");

	GetInitGameParam(&m_messageColorR,"messageColorR");
	GetInitGameParam(&m_messageColorG,"messageColorG");
	GetInitGameParam(&m_messageColorB,"messageColorB");
	GetInitGameParam(&m_messageColorA,"messageColorA");


	m_nameMessage = NULL;
	GetInitGameString(&m_nameMessage,"nameWindowMessage");
	m_namePrintX = 0;
	m_namePrintY = 0;
	GetInitGameParam(&m_namePrintX,"namePrintX");
	GetInitGameParam(&m_namePrintY,"namePrintY");
	m_nameFontSize = m_messageFontSize;
	m_nameColorR = m_messageColorR;
	m_nameColorG = m_messageColorG;
	m_nameColorB = m_messageColorB;
	m_nameColorA = m_messageColorA;
	GetInitGameParam(&m_nameFontSize,"nameFontSize");
	GetInitGameParam(&m_nameColorR,"nameColorR");
	GetInitGameParam(&m_nameColorG,"nameColorG");
	GetInitGameParam(&m_nameColorB,"nameColorB");
	GetInitGameParam(&m_nameColorA,"nameColorA");



	m_volumeExistFlag = new int[m_volumeKosuu];
	m_volumePrintPage = new int[m_volumeKosuu];
	m_modeButtonPrintPage = new int [m_modeButtonKosuu];
	m_checkButtonPrintPage = new int [m_checkButtonKosuu];
	m_modeButtonExistFlag = new int[m_modeButtonKosuu];

	for (i=0;i<m_volumeKosuu;i++)
	{
		char name[256];
		if (i<6)
		{
			m_volumeExistFlag[i] = 1;
		}
		else
		{
			m_volumeExistFlag[i] = 0;
		}

		wsprintf(name,"%sVolumeExistFlag",m_volumeName[i]);
		GetInitGameParam(&m_volumeExistFlag[i],name);

		m_volumePrintPage[i] = 1;
		wsprintf(name,"%sVolumePrintPage",m_volumeName[i]);
		GetInitGameParam(&m_volumePrintPage[i],name);
	}

//	m_messageSpeedPrintPage = 1;
	m_voicePrintPage = 1;

	for (i=0;i<m_modeButtonKosuu;i++)
	{
		m_modeButtonExistFlag[i] = 1;
		char name[256];
		wsprintf(name,"%sModeButtonExistFlag",m_modeButtonName[i]);
		GetInitGameParam(&m_modeButtonExistFlag[i],name);
	}

	for (i=0;i<m_modeButtonKosuu;i++)
	{
		m_modeButtonPrintPage[i] = 1;
		char name[256];
		wsprintf(name,"%sModeButtonPrintPage",m_modeButtonName[i]);
		GetInitGameParam(&m_modeButtonPrintPage[i],name);
	}

	for (i=0;i<m_checkButtonKosuu;i++)
	{
		m_checkButtonPrintPage[i] = 1;
		char name[256];
		wsprintf(name,"%sCheckButtonPrintPage",m_checkButtonName[i]);
		GetInitGameParam(&m_checkButtonPrintPage[i],name);
	}


//	GetInitGameParam(&m_messageSpeedPrintPage,"messageSpeedVolumePrintPage");
	GetInitGameParam(&m_voicePrintPage,"voicePrintPage");



	//
	//check button
	//
	m_ppVoiceButton = NULL;
	m_ppCharaVoiceSlider = NULL;


	m_voiceNameChangeFlag = 0;
	m_voiceCutButtonFlag = 1;
	m_voiceCutNinzu = 0;
	GetInitGameParam(&m_voiceCutButtonFlag,"voiceCutButtonFlag");
	if (m_voiceCutButtonFlag)
	{
		GetInitGameParam(&m_voiceCutNinzu,"voiceCutButtonNumber");
	}

	if (m_voiceCutNinzu == 0)
	{
		m_voiceCutButtonFlag = 0;
	}
	m_charaVoiceVolumeFlag = 0;
	GetInitGameParam(&m_charaVoiceVolumeFlag,"charaVoiceVolumeFlag");

	m_charaVoiceVolumeSE = nullptr;

	m_charaVoiceSliderMin = -15;
	m_charaVoiceSliderMax = 15;
	GetInitGameParam(&m_charaVoiceSliderMin,"charaVoiceVolumeMin");
	GetInitGameParam(&m_charaVoiceSliderMax,"charaVoiceVolumeMax");
	if (m_charaVoiceSliderMin < -15) m_charaVoiceSliderMin = -15;
	if (m_charaVoiceSliderMin > 15) m_charaVoiceSliderMin = 15;
	if (m_charaVoiceSliderMax < -15) m_charaVoiceSliderMax = -15;
	if (m_charaVoiceSliderMax > 15) m_charaVoiceSliderMax = 15;
	if (m_charaVoiceSliderMax < m_charaVoiceSliderMin) m_charaVoiceSliderMax = m_charaVoiceSliderMin;




	m_voiceOffButtonByTableFlag = 0;
	m_ppVoiceCutButtonTable = NULL;

	m_voiceNameCheckChangeVar = NULL;

	m_voiceVoiceChangeFlag = 0;
	m_voiceVoiceCheckChangeVar = NULL;
	m_voiceVoiceChangeVoice = NULL;


	if (m_voiceCutButtonFlag)
	{
		GetInitGameParam(&m_voiceNameChangeFlag,"voiceNameChangeFlag");
		if (m_voiceNameChangeFlag)
		{
			m_voiceNameCheckChangeVar = new int[m_voiceCutNinzu];
			for (i=0;i<m_voiceCutNinzu;i++)
			{
				m_voiceNameCheckChangeVar[i] = -1;
				char name[256];

				wsprintf(name,"voiceNameChangeVar%d",i+1);
				LPSTR checkName = NULL;
				if (GetInitGameString(&checkName,name))
				{
					if (checkName != NULL)
					{
						m_voiceNameCheckChangeVar[i] = m_game->GetVarNumber(checkName);
					}
				}
			}
		}

		GetInitGameParam(&m_voiceVoiceChangeFlag,"voiceVoiceChangeFlag");
		if (m_voiceVoiceChangeFlag)
		{
			m_voiceVoiceCheckChangeVar = new int[m_voiceCutNinzu];
			m_voiceVoiceChangeVoice = new int[m_voiceCutNinzu*16];

			for (i=0;i<m_voiceCutNinzu;i++)
			{
				m_voiceVoiceCheckChangeVar[i] = -1;
				char name[256];

				BOOL changeFlag = FALSE;

				int newVoice = 0;

				newVoice = 0;
				wsprintf(name,"voiceVoiceChangeVoiceOffClick%d",i+1);
				GetInitGameParam(&newVoice,name);
				m_voiceVoiceChangeVoice[i*16+8] = newVoice;
				if (newVoice > 0) {changeFlag = TRUE;}

				newVoice = 0;
				wsprintf(name,"voiceVoiceChangeVoiceOffCannot%d",i+1);
				GetInitGameParam(&newVoice,name);
				m_voiceVoiceChangeVoice[i*16+9] = newVoice;
				if (newVoice > 0) {changeFlag = TRUE;}

				newVoice = 0;
				wsprintf(name,"voiceVoiceChangeVoiceOffEnter%d",i+1);
				GetInitGameParam(&newVoice,name);
				m_voiceVoiceChangeVoice[i*16+10] = newVoice;
				if (newVoice > 0) {changeFlag = TRUE;}

				newVoice = 0;
				wsprintf(name,"voiceVoiceChangeVoiceOffExit%d",i+1);
				GetInitGameParam(&newVoice,name);
				m_voiceVoiceChangeVoice[i*16+11] = newVoice;
				if (newVoice > 0) {changeFlag = TRUE;}

				newVoice = 0;
				wsprintf(name,"voiceVoiceChangeVoiceOnClick%d",i+1);
				GetInitGameParam(&newVoice,name);
				m_voiceVoiceChangeVoice[i*16+12] = newVoice;
				if (newVoice > 0) {changeFlag = TRUE;}

				newVoice = 0;
				wsprintf(name,"voiceVoiceChangeVoiceOnCannot%d",i+1);
				GetInitGameParam(&newVoice,name);
				m_voiceVoiceChangeVoice[i*16+13] = newVoice;
				if (newVoice > 0) {changeFlag = TRUE;}

				newVoice = 0;
				wsprintf(name,"voiceVoiceChangeVoiceOnEnter%d",i+1);
				GetInitGameParam(&newVoice,name);
				m_voiceVoiceChangeVoice[i*16+14] = newVoice;
				if (newVoice > 0) {changeFlag = TRUE;}

				newVoice = 0;
				wsprintf(name,"voiceVoiceChangeVoiceOnExit%d",i+1);
				GetInitGameParam(&newVoice,name);
				m_voiceVoiceChangeVoice[i*16+15] = newVoice;
				if (newVoice > 0) {changeFlag = TRUE;}

				if (changeFlag)
				{
					m_voiceVoiceCheckChangeVar[i] = m_voiceNameCheckChangeVar[i];
					wsprintf(name,"voiceVoiceChangeVar%d",i+1);
					LPSTR checkName = NULL;
					if (GetInitGameString(&checkName,name))
					{
						if (checkName != NULL)
						{
							m_voiceVoiceCheckChangeVar[i] = m_game->GetVarNumber(checkName);
						}
					}
				}
			}
		}




		m_voiceCutButtonCheckAppear = 0;
		GetInitGameParam(&m_voiceCutButtonCheckAppear,"voiceCutButtonCheckAppearFlag");

		m_ppVoiceButton = new CCommonCheckButton*[m_voiceCutNinzu];

		if (m_charaVoiceVolumeFlag)
		{
			m_ppCharaVoiceSlider = new CMySlider*[m_voiceCutNinzu];
		}

		m_voiceAutoLineSetFlag = 0;
		GetInitGameParam(&m_voiceAutoLineSetFlag,"voiceAutoLineSetFlag");

		if (m_voiceAutoLineSetFlag)
		{
			m_voiceAutoLinePrintX = 0;
			m_voiceAutoLinePrintY = 0;
			m_voiceAutoLineNextX = 100;
			m_voiceAutoLineNextY = 30;
			m_voiceAutoLineNumberX = 5;
			m_voiceAutoLineNumberY = 0;

			GetInitGameParam(&m_voiceAutoLinePrintX,"voiceAutoLinePrintX");
			GetInitGameParam(&m_voiceAutoLinePrintY,"voiceAutoLinePrintY");
			GetInitGameParam(&m_voiceAutoLineNextX,"voiceAutoLineNextX");
			GetInitGameParam(&m_voiceAutoLineNextY,"voiceAutoLineNextY");
			GetInitGameParam(&m_voiceAutoLineNumberX,"voiceAutoLineNumberX");
			GetInitGameParam(&m_voiceAutoLineNumberY,"voiceAutoLineNumberY");
		}

		m_charaVoiceVolumeSE = new int[m_voiceCutNinzu];
		for (i = 0; i < m_voiceCutNinzu; i++)
		{
			char name[256];
			sprintf_s(name, 256, "charaVoiceVolumeSE%d", i + 1);
			int se = 0;
			GetInitGameParam(&se,name);
			m_charaVoiceVolumeSE[i] = se;
		}

		CPicture* charaSliderPic = NULL;
		if (m_charaVoiceVolumeFlag)
		{
			LPSTR sliderPicName = NULL;
			GetInitGameString(&sliderPicName,"filenameCharaVoiceVolume");

			charaSliderPic = m_game->GetSystemPicture(sliderPicName);

			m_charaVolumePrintX = 0;
			m_charaVolumePrintY = 30;
			GetInitGameParam(&m_charaVolumePrintX,"charaVolumePrintX");
			GetInitGameParam(&m_charaVolumePrintY,"charaVolumePrintY");
			m_charaVolumeSizeX = 200;
			m_charaVolumeSizeY = 20;
			GetInitGameParam(&m_charaVolumeSizeX,"charaVolumeSizeX");
			GetInitGameParam(&m_charaVolumeSizeY,"charaVolumeSizeY");
		}

		for (i=0;i<m_voiceCutNinzu;i++)
		{
			char name[256];
			wsprintf(name,"voice%dButton",i+1);

			POINT pt;
			POINT* lpPoint = NULL;

			if (m_voiceAutoLineSetFlag)
			{
				if (m_voiceAutoLineNumberY != 0)
				{
					pt.x = m_voiceAutoLinePrintX + (i / m_voiceAutoLineNumberY) * m_voiceAutoLineNextX;
					pt.y = m_voiceAutoLinePrintY + (i % m_voiceAutoLineNumberY) * m_voiceAutoLineNextY;
					lpPoint = &pt;
				}
				else if (m_voiceAutoLineNumberX != 0)
				{
					pt.x = m_voiceAutoLinePrintX + (i % m_voiceAutoLineNumberX) * m_voiceAutoLineNextX;
					pt.y = m_voiceAutoLinePrintY + (i / m_voiceAutoLineNumberX) * m_voiceAutoLineNextY;
					lpPoint = &pt;
				}
			}

			CSuperButtonSetup* lpSuperSetup = NULL;
			if (i>0) lpSuperSetup = m_ppVoiceButton[i-1]->GetSuperButtonSetup(1);

			m_ppVoiceButton[i] = new CCommonCheckButton(m_setup,lpBG,name,lpPoint,lpSuperSetup);

			if (m_charaVoiceVolumeFlag)
			{
				POINT btnPoint = m_ppVoiceButton[i]->GetButton(0)->GetZahyo();
				int sliderX = btnPoint.x  + m_charaVolumePrintX;
				int sliderY = btnPoint.y  + m_charaVolumePrintY;

				BOOL charaSliderTransFlag = TRUE;//
				int maxPara = m_charaVoiceSliderMax - m_charaVoiceSliderMin;
				m_ppCharaVoiceSlider[i] = new CMySlider(charaSliderPic, maxPara,sliderX,sliderY, m_charaVolumeSizeX,m_charaVolumeSizeY, 0,0, charaSliderTransFlag, lpBG,FALSE);
			}


			CPicture* lpPic = GetUseOkPicture(m_voicePrintPage);

			m_ppVoiceButton[i]->SetPicture(lpPic,0);
			m_ppVoiceButton[i]->SetPicture(lpPic,1);

			if (m_voiceVoiceChangeFlag)
			{
				for (int onoff=0;onoff<2;onoff++)
				{
					CCommonButton* button = m_ppVoiceButton[i]->GetButton(onoff);

					m_voiceVoiceChangeVoice[i*16+onoff*4+0] = button->GetClickSound();
					m_voiceVoiceChangeVoice[i*16+onoff*4+1] = button->GetCannotClickSound();
					m_voiceVoiceChangeVoice[i*16+onoff*4+2] = button->GetEnterSound();
					m_voiceVoiceChangeVoice[i*16+onoff*4+3] = button->GetExitSound();

					for (int vv=0;vv<4;vv++)
					{
						if (m_voiceVoiceChangeVoice[i*16+onoff*4+8+vv] <= 0)
						{
							m_voiceVoiceChangeVoice[i*16+onoff*4+8+vv] = m_voiceVoiceChangeVoice[i*16+onoff*4+vv];
						}
					}
				}
			}

		}


		GetInitGameParam(&m_voiceOffButtonByTableFlag,"voiceCutButtonCustomFlag");

//		int tt[256];
//		for (int i=0;i<256;i++)
//		{
//			tt[i] = -2;
//		}

		if (m_voiceOffButtonByTableFlag)
		{
			m_ppVoiceCutButtonTable = new int*[m_voiceCutNinzu];

			int charaNumber = 1;

			for (i=0;i<m_voiceCutNinzu;i++)
			{
				int ninzu = 1;
				//get ninzuu
				char name[256];
				wsprintf(name,"voiceOffNumberByButton%d",i+1);
				GetInitGameParam(&ninzu,name);
				m_ppVoiceCutButtonTable[i] = new int[ninzu + 1];
				m_ppVoiceCutButtonTable[i][0] = ninzu;

				for (int k=0;k<ninzu;k++)
				{
					wsprintf(name,"voiceOffButton%dchara%d",i+1,k+1);
					GetInitGameParam(&charaNumber,name);
					m_ppVoiceCutButtonTable[i][k+1] = charaNumber;
//					tt[charaNumber] = i;
					charaNumber++;
				}
			}
		}
/*
		for (int i=0;i<256;i++)
		{
			char mes[256];
			if ((i % 10) == 0)
			{
				wsprintf(mes,"\n%d:",i);
				OutputDebugString(mes);
			}

			wsprintf(mes," %d",tt[i]);
			OutputDebugString(mes);
		}
*/

	}






	m_ppSlider = new CMySlider*[m_volumeKosuu];
	//messagespeed
	for (i=0;i<m_volumeKosuu;i++)
	{
		m_ppSlider[i] = NULL;
	}


	//volume slider,button
	m_ppVolumeButton = NULL;




	//���ʕ␳�ɂ̂ݎg��
	for (i=0;i<m_volumeKosuu;i++)
	{
		int volumeMin = m_volumeMin;
		int volumeMax = m_volumeMax;

		char name[256];
		
		wsprintf(name,"%sRealVolumeMin",m_volumeName[i]);
		GetInitGameParam(&volumeMin,name);
		m_realVolumeMinTable[i] = volumeMin;

		wsprintf(name,"%sRealVolumeMax",m_volumeName[i]);
		GetInitGameParam(&volumeMax,name);
		m_realVolumeMaxTable[i] = volumeMax;

	}



	if (1)
	{
		m_ppVolumeButton = new CCommonCheckButton*[m_volumeKosuu];

		m_volumeSizeX = 338;
		m_volumeSizeY = 19;

		GetInitGameParam(&m_volumeSizeX,"volumeSizeX");
		GetInitGameParam(&m_volumeSizeY,"volumeSizeY");

		//print,next


		int lastExistSetup = 1;

		for (i=0;i<m_volumeKosuu;i++)
		{
			char name[256];
			m_ppVolumeButton[i] = NULL;

			if (m_volumeExistFlag[i])
			{
				wsprintf(name,"volumeSizeX%d",i+1);
				GetInitGameParam(&m_volumeSizeX,name);
				wsprintf(name,"volumeSizeY%d",i+1);
				GetInitGameParam(&m_volumeSizeY,name);



	//			CPicture* lpBG = m_commonBG;
	//			if (m_backScriptFlag) lpBG = NULL;
	//			if (m_mustAllPrintFlag) lpBG = NULL;

	wsprintf(name,"%sButton",m_volumeName[i]);

				CSuperButtonSetup* lpSuperSetup = NULL;
				if (((i>1) && (i < 6)) || (i >= 8))
				{
//					lpSuperSetup = m_ppVolumeButton[i-1]->GetSuperButtonSetup(1);
					lpSuperSetup = m_ppVolumeButton[lastExistSetup]->GetSuperButtonSetup(1);
				}

				if (((i  > 0) && (i<6)) || (i>=8))
				{
					lastExistSetup = i;
				}

				POINT* lpPoint = NULL;
				if (((i>0) && (i < 6)) || (i>=8))
//				if (m_volumeButtonExistTable[i])
				{
					m_ppVolumeButton[i] = new CCommonCheckButton(m_setup,lpBG,name,lpPoint,lpSuperSetup);

					CPicture* lpPic = GetUseOkPicture(m_volumePrintPage[i]);

					m_ppVolumeButton[i]->SetPicture(lpPic,0);
					m_ppVolumeButton[i]->SetPicture(lpPic,1);
				}

				//slider

				int x = 0;					//dummy
				int y = i * m_volumeSizeY;


				wsprintf(name,"%sVolumePrintX",m_volumeName[i]);
				GetInitGameParam(&x,name);
				wsprintf(name,"%sVolumePrintY",m_volumeName[i]);
				GetInitGameParam(&y,name);

				LPSTR barFileName = m_defaultBarFileName;
				wsprintf(name,"%sBarFileName",m_volumeName[i]);
				GetInitGameString(&barFileName,name);
				CPicture* sliderPic = m_game->GetSystemPicture(barFileName);

				BOOL musicSliderTransFlag = 1;
				wsprintf(name,"%sVolumeTransFlag",m_volumeName[i]);
				GetInitGameParam(&musicSliderTransFlag,name);
				
				//int maxPara = 100;
				//if (i == 0) maxPara = 4;
				//if (i == 7) maxPara = 4;
				int maxPara = m_volumeDevideTable[i];

				m_ppSlider[i] = new CMySlider(sliderPic, maxPara,x,y, m_volumeSizeX,m_volumeSizeY, 0,0, musicSliderTransFlag, lpBG,FALSE);

				int digitalFlag = 0;
				wsprintf(name,"%sVolumeDigitalFlag",m_volumeName[i]);
				GetInitGameParam(&digitalFlag,name);
				if (digitalFlag)
				{
					m_ppSlider[i]->SetDigitalFlag(digitalFlag);
				}

				//�{�^���f�t�H���W�ݒ�
				//IfCan
				if (((i>0) && (i < 6)) || (i >= 8))
				{
					SIZE buttonSize = m_ppVolumeButton[i]->GetSize();

					int buttonX = x - buttonSize.cx;
					int buttonY = y;

					wsprintf(name,"%sButtonPrintX",m_volumeName[i]);
					GetInitGameParam(&buttonX,name);
					wsprintf(name,"%sButtonPrintY",m_volumeName[i]);
					GetInitGameParam(&buttonY,name);

					POINT pt;
					pt.x = buttonX;
					pt.y = buttonY;

					m_ppVolumeButton[i]->SetZahyo(pt);
				}
			}
		}
	}
	


	//radio
	if (1)
	{
		//print,next

//		m_ppRadioButton = new CCommonCheckButton*[m_radioButtonKosuu];
	}

	m_systemVoiceButtonPrintPage = 1;
	GetInitGameParam(&m_systemVoiceButtonPrintPage, "systemVoiceButtonPrintPage");

	m_ppSystemVoiceButton = nullptr;
	m_systemVoiceButtonKosuu = 0;
	int systemVoiceCount = m_game->GetUseSystemVoiceCount();

	m_systemCharaVoiceCheckCharaNumber = nullptr;
	m_systemCharaVoiceCheckVar = nullptr;

	if (systemVoiceCount > 0)
	{
		m_systemVoiceButtonKosuu = systemVoiceCount + 1;

		m_ppSystemVoiceButton = new CCommonRadioButtonGroup(m_setup,"systemVoice" , lpBG, m_systemVoiceButtonKosuu, NULL);


		m_systemCharaVoiceCheckCharaNumber = new int[m_systemVoiceButtonKosuu];
		m_systemCharaVoiceCheckVar = new int[m_systemVoiceButtonKosuu];

		for (int k = 0; k < m_systemVoiceButtonKosuu; k++)
		{
			CPicture* lpPic = GetUseOkPicture(m_systemVoiceButtonPrintPage);
			m_ppSystemVoiceButton->SetPicture(lpPic, k, -1);

			char name[256];
			sprintf_s(name, 256, "systemVoice%dOn", k);
			int target = 0;
			GetInitGameParam(&target, name);
			m_systemCharaVoiceCheckCharaNumber[k] = target;


			m_systemCharaVoiceCheckVar[k] = -1;
			sprintf_s(name, 256, "systemVoice%dOnVarName", k);
			LPSTR varName = nullptr;
			GetInitGameString(&varName, name);
			if (varName != nullptr)
			{
				m_systemCharaVoiceCheckVar[k] = m_game->GetVarNumber(varName);
			}


		}

	}


	m_ppModeButton = new CCommonRadioButtonGroup* [m_modeButtonKosuu];
	for (i=0;i<m_modeButtonKosuu;i++)
	{
		if (m_modeButtonExistFlag[i] == 0)
		{
			m_ppModeButton[i] = NULL;
		}
		else
		{
			m_ppModeButton[i] = new CCommonRadioButtonGroup(m_setup,m_modeButtonName[i],lpBG,2,NULL);

			for (int k=0;k<2;k++)
			{
				CPicture* lpPic = GetUseOkPicture(m_modeButtonPrintPage[i]);
				m_ppModeButton[i]->SetPicture(lpPic,k,-1);
			}
		}
	}

	m_ppCheckButton = new CCommonCheckButton* [m_checkButtonKosuu];
	for (i=0;i<m_checkButtonKosuu;i++)
	{
		m_ppCheckButton[i] = NULL;
		char name[256];
		wsprintf(name,"%sCheckButtonExistFlag",m_checkButtonName[i]);
		int cflag = 0;
		GetInitGameParam(&cflag,name);
		if (cflag)
		{
			char buttonName[256];
//			wsprintf(buttonName,"%sCheckButton",m_checkButtonName[i]);
			wsprintf(buttonName, "%sCheck", m_checkButtonName[i]);
			m_ppCheckButton[i] = new CCommonCheckButton(m_setup,lpBG,buttonName);

			CPicture* lpPic = GetUseOkPicture(m_checkButtonPrintPage[i]);
			m_ppCheckButton[i]->SetPicture(lpPic,0);
			m_ppCheckButton[i]->SetPicture(lpPic,1);
		}
	}


	//addRadio??

	m_expModeButtonKosuu = 0;
	m_ppExpModeButton = NULL;
	m_expModeButtonPrintPage = NULL;
	GetInitGameParam(&m_expModeButtonKosuu,"expRadioNumber");
	if (m_expModeButtonKosuu>0)
	{
		m_ppExpModeButton = new CCommonRadioButtonGroup* [m_expModeButtonKosuu];
		m_expModeButtonPrintPage = new int[m_expModeButtonKosuu];

		for (i=0;i<m_expModeButtonKosuu;i++)
		{
			m_expModeButtonPrintPage[i] = 1;
			char name[256];
			wsprintf(name,"exp%dRadioPrintPage",i+1);
			GetInitGameParam(&m_expModeButtonPrintPage[i],name);

			int radioKosuu = 2;
			wsprintf(name,"exp%dRadio",i+1);
			GetInitGameParam(&radioKosuu,name);

			wsprintf(name,"exp%dRadio",i+1);
			m_ppExpModeButton[i] = new CCommonRadioButtonGroup(m_setup,name,lpBG,radioKosuu,NULL);

			for (int k=0;k<radioKosuu;k++)
			{
				CPicture* lpPic = GetUseOkPicture(m_expModeButtonPrintPage[i]);
				m_ppExpModeButton[i]->SetPicture(lpPic,k,-1);
			}
		}
	}
	

	//addcheck

	m_expCheckButtonKosuu = 0;
	m_ppExpCheckButton = NULL;
	m_expCheckButtonPrintPage = NULL;
	GetInitGameParam(&m_expCheckButtonKosuu,"expCheckNumber");
	if (m_expCheckButtonKosuu>0)
	{
		m_ppExpCheckButton = new CCommonCheckButton* [m_expCheckButtonKosuu];
		m_expCheckButtonPrintPage = new int[m_expCheckButtonKosuu];

		for (i=0;i<m_expCheckButtonKosuu;i++)
		{
			m_expCheckButtonPrintPage[i] = 1;
			char name[256];
			wsprintf(name,"exp%dCheckPrintPage",i+1);
			GetInitGameParam(&m_expCheckButtonPrintPage[i],name);


			wsprintf(name,"exp%dCheck",i+1);
			m_ppExpCheckButton[i] = new CCommonCheckButton(m_setup,lpBG,name);

			CPicture* lpPic = GetUseOkPicture(m_expCheckButtonPrintPage[i]);
			m_ppExpCheckButton[i]->SetPicture(lpPic,0);
			m_ppExpCheckButton[i]->SetPicture(lpPic,1);
		}
	}

	//click button
	m_clickButtonKosuu = 0;
	m_ppClickButton = NULL;
	m_clickButtonPrintPage = NULL;
	GetInitGameParam(&m_clickButtonKosuu,"clickNumber");
	if (m_clickButtonKosuu>0)
	{
		m_ppClickButton = new CCommonButton* [m_clickButtonKosuu];
		m_clickButtonPrintPage = new int[m_clickButtonKosuu];

		for (i=0;i<m_clickButtonKosuu;i++)
		{
			m_clickButtonPrintPage[i] = 1;
			char name[256];
			wsprintf(name,"click%dPrintPage",i+1);
			GetInitGameParam(&m_clickButtonPrintPage[i],name);


			wsprintf(name,"click%d",i+1);
			m_ppClickButton[i] = new CCommonButton(m_setup,name,lpBG);

			CPicture* lpPic = GetUseOkPicture(m_clickButtonPrintPage[i]);
			m_ppClickButton[i]->SetPicture(lpPic);
		}
	}




	//messagewindow
	m_windowKosuu = m_game->GetWindowShurui();
	m_windowPrintFlag = m_windowKosuu-1;
	GetInitGameParam(&m_windowPrintFlag,"windowPrintFlag");

	if (m_windowPrintFlag)
	{
		m_windowPrintPage = 1;
		GetInitGameParam(&m_windowPrintPage,"windowPrintPage");

		int deltaX = 0;
		int deltaY = 0;
		GetInitGameParam(&deltaX,"windowPrintX");
		GetInitGameParam(&deltaY,"windowPrintY");

		m_windowPrint.x = deltaX;
		m_windowPrint.y = deltaY;
	}

	//mousecursor

	//messagecursor



	m_extSeFlag = 0;
	GetInitGameParam(&m_extSeFlag,"extSeFlag");
	m_seList = NULL;








	m_windowPercentSeBunkatsu = 0;



	GetInitGameParam(&m_windowPercentSeBunkatsu,"windowPercentSeBunkatsu");
	m_windowPercentSe = new int[2+m_windowPercentSeBunkatsu];
	m_windowPercentSe[0] = 0;

	m_useConfigSeVoice = 0;
	GetInitGameParam(&m_useConfigSeVoice, "useConfigSeVoice");

	m_seVoice = nullptr;
	if (m_extSeFlag)
	{
		m_seList = new CNameList();
		m_seList->LoadFile("nya\\configSe.xtx");
		m_seListKosuu = m_seList->GetNameKosuu() / 2;

		if (m_useConfigSeVoice)
		{
			if (m_systemVoiceButtonKosuu > 0)
			{
				m_seVoice = new CNameList*[m_systemVoiceButtonKosuu];
				for (int i = 0; i < m_systemVoiceButtonKosuu; i++)
				{
					m_seVoice[i] = new CNameList();
					if (i > 0)
					{
						char filename[256];
						sprintf_s(filename, 256, "nya\\configSeVoice%d.xtx", i);
						m_seVoice[i]->LoadFile(filename);
					}
				}
			}
		}
		


		for (i=0;i<m_volumeKosuu;i++)
		{
			char name[256];

			int bunkatsu = m_defaultBunkatsuTable[i];
			sprintf_s(name,sizeof(name),"%sSeBunkatsu",m_volumeName[i]);
			GetInitGameParam(&bunkatsu,name);
			m_bunkatsuTable[i] = bunkatsu;

			int isVoice = m_defaultIsVoiceTable[i];
			if (i== 0)
			{
				GetInitGameParam(&isVoice,"messageIsVoice");
			}

			sprintf_s(name,sizeof(name),"%sIsVoice",m_volumeName[i]);
			GetInitGameParam(&isVoice,name);
			m_isVoiceTable[i] = isVoice;

			int seNumber = 0;
			sprintf_s(name,sizeof(name),"%sSeNumber",m_volumeName[i]);
			if (i== 0)
			{
				GetInitGameParam(&seNumber,"messageSeNumber");
			}
			GetInitGameParam(&seNumber,name);
			seNumber--;
			m_seTable[i] = seNumber;
/*
			int volumeMaxData = m_defaultVolumeMaxTable[i];
			sprintf_s(name,sizeof(name),"%sVolumeMax",m_volumeName[i]);
			GetInitGameParam(&volumeMaxData,name);
			m_volumeMaxTable[i] = volumeMaxData;
			*/
		}





		int voiceSe = 0;
		GetInitGameParam(&voiceSe,"voiceSeNumber");
		voiceSe -= 1;

		int next = 1;
		if (voiceSe == -1) next = 0;

		for (i=0;i<=10;i++)
		{
			m_voiceSe[i] = voiceSe + i * next;
		}


		
		int messageSe = 0;
		GetInitGameParam(&messageSe,"messageSeNumber");
		messageSe -= 1;

		next = 1;
		if (messageSe == -1) next = 0;

		for (i=0;i<5;i++)
		{
			m_messageSe[i] = messageSe + i * next;
		}

		int autoSe = 0;
		GetInitGameParam(&autoSe,"autoSeNumber");
		GetInitGameParam(&autoSe,"autoSpeedSeNumber");
		autoSe -= 1;

		next = 1;
		if (autoSe == -1) next = 0;

		for (i=0;i<5;i++)
		{
			m_autoSe[i] = autoSe + i * next;
		}


		m_messageIsVoice = 1;
		GetInitGameParam(&m_messageIsVoice,"messageIsVoice");

		m_windowPercentIsVoice = 1;
		GetInitGameParam(&m_windowPercentIsVoice,"windowPercentIsVoice");

		m_autoIsVoice = 1;
		GetInitGameParam(&m_autoIsVoice,"autoIsVoice");
		GetInitGameParam(&m_autoIsVoice,"autoSpeedIsVoice");



		int soundSe = 0;
		GetInitGameParam(&soundSe,"soundSeNumber");
		soundSe -= 1;
		m_soundSe = soundSe;

		int movieSe = 0;
		GetInitGameParam(&movieSe,"movieSeNumber");
		movieSe -= 1;
		m_movieSe = movieSe;

		int soundVoiceSe = 0;
		GetInitGameParam(&soundVoiceSe,"soundVoiceSeNumber");
		soundVoiceSe -= 1;
		m_soundVoiceSe = soundVoiceSe;

		int windowPercentSe = 0;
		GetInitGameParam(&windowPercentSe,"windowPercentSeNumber");
		windowPercentSe -= 1;
		next = 1;
		if (windowPercentSe == -1) next = 0;
		for (int i=0;i<m_windowPercentSeBunkatsu+2;i++)
		{
			m_windowPercentSe[i] = windowPercentSe + i * next;
		}

	}

	m_initWindowPercent = -1;
	m_initWindowNumber = -1;
	m_initTotalVolume = -1;

	for (int i=0;i<10;i++)
	{
		m_initVolume[i] = -1;
		m_initVolumeSwitch[i] = -1;
	}
//	m_initMusicVolume = -1;
//	m_initSoundVolume = -1;
//	m_initVoiceVolume = -1;
//	m_initMovieVolume = -1;
//	m_initSoundVoiceVolume = -1;

	m_initSkipMode = -1;
	m_initMessageSpeed = -1;
	m_initAutoSpeed = -1;
	m_initCharaVoiceVolume = -1;
	m_initCharaVoiceOff = -1;

	m_initAnimeSwitch = -1;

	GetInitGameParam(&m_initWindowPercent,"initWindowPercent");
	GetInitGameParam(&m_initWindowNumber,"initWindowNumber");
	GetInitGameParam(&m_initTotalVolume,"initTotalVolume");
//	GetInitGameParam(&m_initMusicVolume,"initMusicVolume");
//	GetInitGameParam(&m_initSoundVolume,"initSoundVolume");
//	GetInitGameParam(&m_initVoiceVolume,"initVoiceVolume");
//	GetInitGameParam(&m_initSoundVoiceVolume,"initSoundVoiceVolume");
	GetInitGameParam(&m_initSkipMode,"initSkipMode");
	
	for (int i=1;i<=m_volumeKosuu;i++)
	{
		if ((i<6) || (i>=8))
		{
			char name[256];
			wsprintf(name,"init%sVolume",m_volumeName[i]);
			int d = m_initVolume[i];
			GetInitGameParam(&d,name);
			m_initVolume[i] = d;

			wsprintf(name,"init%sVolumeSwitch",m_volumeName[i]);
			d = m_initVolumeSwitch[i];
			GetInitGameParam(&d,name);
			m_initVolumeSwitch[i] = d;
		}
	}



	GetInitGameParam(&m_initMessageSpeed,"initMessageSpeed");
	GetInitGameParam(&m_initAutoSpeed,"initAutoSpeed");
	GetInitGameParam(&m_initCharaVoiceVolume,"initCharaVoiceVolume");
	GetInitGameParam(&m_initCharaVoiceOff,"initCharaVoiceOff");
//	GetInitGameParam(&m_initMovieVolume,"initMovieVolume");


	m_sampleText = nullptr;
	m_useSampleText = 0;
	GetInitGameParam(&m_useSampleText, "useSampleText");

	m_sampleTextPrintX = 0;
	m_sampleTextPrintY = 0;
	m_sampleTextFontSize = 24;
	m_sampleTextCount = 0;
	m_sampleTextPrintPage = 1;
	m_sampleTextColorR = 255;
	m_sampleTextColorG = 255;
	m_sampleTextColorB = 255;
	

	m_sampleTextNextY = 28;
	m_sampleTextWait = 0;
	m_sampleTextLoop = 1;


	m_samplePrintGyoCount = 1;
	m_sampleNowPrintGyo = 0;


	if (m_useSampleText != 0)
	{
		GetInitGameParam(&m_sampleTextPrintX, "sampleTextPrintX");
		GetInitGameParam(&m_sampleTextPrintY, "sampleTextPrintY");
		GetInitGameParam(&m_sampleTextFontSize, "sampleTextFontSize");
		GetInitGameParam(&m_sampleTextPrintPage, "sampleTextPrintPage");
		GetInitGameParam(&m_sampleTextColorR, "sampleTextColorR");
		GetInitGameParam(&m_sampleTextColorG, "sampleTextColorG");
		GetInitGameParam(&m_sampleTextColorB, "sampleTextColorB");

		GetInitGameParam(&m_sampleTextNextY, "sampleTextNextY");
		GetInitGameParam(&m_sampleTextWait, "sampleTextWait");
		GetInitGameParam(&m_sampleTextLoop, "sampleTextLoop");

		GetInitGameParam(&m_samplePrintGyoCount, "sampleTextGyo");
		m_sampleText = new LPSTR[m_samplePrintGyoCount];

		for (int i = 0; i < m_samplePrintGyoCount; i++)
		{
			LPSTR text = m_defaultSampleText;
			char name[256];
			sprintf_s(name, 256, "sampleText%d", i + 1);
			GetInitGameString(&text, name);
			m_sampleText[i] = text;
		}
	}

	GetInitGameParam(&m_initAnimeSwitch,"initAnimeSwitch");

	m_voiceSameBufferFlag = 0;
	GetInitGameParam(&m_voiceSameBufferFlag,"voiceSameBufferFlag");

	CreateBackButton();

	if (m_pageMode == 1)
	{
		CreateUpDownButton();
		CreateUpDownBack();
	}

	m_captureFlag = FALSE;
	m_captureBarNumber = 0;

	m_changingNumber = -1;
	m_changingCount = 1;

	GetBGMSetup();

	m_exitFadeOutSpecialMode = TITLE_MODE;
	m_createExitScreenFlagSpecial = 1;
	GetFadeInOutSetup();

	GetEnterExitVoiceFileName();
}


CCommonConfig::~CCommonConfig()
{
	End();
}



void CCommonConfig::End(void)
{
	DELETEARRAY(m_bgFileName);
	ENDDELETECLASS(m_tabButton);
	DELETEARRAY(m_windowMessage);
	DELETEARRAY(m_volumeExistFlag);
	DELETEARRAY(m_volumePrintPage);
	DELETEARRAY(m_clickButtonPrintPage);
	DELETEARRAY(m_expCheckButtonPrintPage);
	DELETEARRAY(m_expModeButtonPrintPage);
	DELETEARRAY(m_modeButtonPrintPage);
	DELETEARRAY(m_modeButtonExistFlag);
	DELETEARRAY(m_useSuperPicKosuu);
	DELETEARRAY(m_useEffectPicKosuu);


	DELETEARRAY(m_sampleText);


	DELETEARRAY(m_windowPercentSe);


	if (m_seVoice != nullptr)
	{
		for (int i = 0; i < m_systemVoiceButtonKosuu; i++)
		{
			ENDDELETECLASS(m_seVoice[i]);
		}
		DELETEARRAY(m_seVoice);
	}

	DELETEARRAY(m_isVoiceTable);
	DELETEARRAY(m_bunkatsuTable);
	DELETEARRAY(m_volumeDevideTable);
	DELETEARRAY(m_seTable);


	ENDDELETECLASS(m_seList);

	if (m_ppClickButton != NULL)
	{
		for (int i=0;i<m_clickButtonKosuu;i++)
		{
			ENDDELETECLASS(m_ppClickButton[i]);
		}
		DELETEARRAY(m_ppClickButton);
	}

	if (m_ppExpCheckButton != NULL)
	{
		for (int i=0;i<m_expCheckButtonKosuu;i++)
		{
			ENDDELETECLASS(m_ppExpCheckButton[i]);
		}
		DELETEARRAY(m_ppExpCheckButton);
	}

	if (m_ppExpModeButton != NULL)
	{
		for (int i=0;i<m_expModeButtonKosuu;i++)
		{
			ENDDELETECLASS(m_ppExpModeButton[i]);
		}
		DELETEARRAY(m_ppExpModeButton);
	}

	if (m_ppCheckButton != NULL)
	{
		for (int i=0;i<m_checkButtonKosuu;i++)
		{
			ENDDELETECLASS(m_ppCheckButton[i]);
		}
		DELETEARRAY(m_ppCheckButton);
	}

	if (m_ppModeButton != NULL)
	{
		for (int i=0;i<m_modeButtonKosuu;i++)
		{
			ENDDELETECLASS(m_ppModeButton[i]);
		}
		DELETEARRAY(m_ppModeButton);
	}

	ENDDELETECLASS(m_ppSystemVoiceButton);
	DELETEARRAY(m_systemCharaVoiceCheckCharaNumber);
	DELETEARRAY(m_systemCharaVoiceCheckVar);


	if (m_ppVolumeButton != NULL)
	{
		for (int i=0;i<m_volumeKosuu;i++)
		{
			ENDDELETECLASS(m_ppVolumeButton[i]);
		}
		DELETEARRAY(m_ppVolumeButton);
	}

	DELETEARRAY(m_voiceVoiceChangeVoice);
	DELETEARRAY(m_voiceVoiceCheckChangeVar);
	DELETEARRAY(m_voiceNameCheckChangeVar);

	DELETEARRAY(m_charaVoiceVolumeSE);

	if (m_ppVoiceButton != NULL)
	{
		for (int i=0;i<m_voiceCutNinzu;i++)
		{
			ENDDELETECLASS(m_ppVoiceButton[i]);
			if (m_charaVoiceVolumeFlag)
			{
				ENDDELETECLASS(m_ppCharaVoiceSlider[i]);
			}
		}
		DELETEARRAY(m_ppVoiceButton);
		DELETEARRAY(m_ppCharaVoiceSlider);
	}

	if (m_ppVoiceCutButtonTable != NULL)
	{
		for (int i=0;i<m_voiceCutNinzu;i++)
		{
			DELETEARRAY(m_ppVoiceCutButtonTable[i]);
		}
		DELETEARRAY(m_ppVoiceCutButtonTable);
	}


	if (m_ppSlider != NULL)
	{
		for (int i=0;i<m_volumeKosuu;i++)
		{
			ENDDELETECLASS(m_ppSlider[i]);
		}
		DELETEARRAY(m_ppSlider);
	}
}


void CCommonConfig::FinalExitRoutine(void)
{
	CCommonGeneral::FinalExitRoutine();
	if (m_outSetVar != -1)
	{
		m_game->SetVarData(m_outSetVar, m_outSetVarData);
	}
}


int CCommonConfig::Init(void)
{
//	char filename[256];

	if (m_inSetVar != -1)
	{
		m_game->SetVarData(m_inSetVar, m_inSetVarData);
	}

	//�����Ŏ擾
	for (int i = 0; i < 5; i++)
	{
		m_messageSpeedTable[i] = m_game->GetMessageSpeedTable(i, false);
		m_autoMessageSpeedTable[i] = m_game->GetMessageSpeedTable(i, true);
	}
	m_mojiTime = 0;

	m_game->StopScriptSoundAndVoice();

	m_pageYoyaku = -1;
	m_pageYoyakuFlag = FALSE;
	m_sampleTextCount = 0;
	m_sampleNowPrintGyo = 0;

	ReLoadBackConfigBG();

	LoadBackButtonPic();
	SetBackButtonZahyo();
	
	ReLoadAllRadioButtonPic();

	if (m_backScriptFlag)
	{
		SetPageNumber();
	}


	if (m_pageMode == 1)
	{
		m_updown->SetPage(m_page);
		m_updown->SetPageMax(m_pageMax);
		LoadUpDownButtonPic();
		SetUpDownZahyo();
	}

	//set button status




	int i = 0;
	for (i=0;i<m_voiceCutNinzu;i++)
	{
	
		BOOL flg = TRUE;
		if (m_voiceCutButtonCheckAppear)
		{
			if (m_voiceOffButtonByTableFlag == 0)
			{
				flg = m_game->CheckVoiceUsedFlag(i+1);
			}
			else
			{
				if (m_ppVoiceCutButtonTable != NULL)
				{
					int* table = m_ppVoiceCutButtonTable[i];
					if (table != NULL)
					{
						int kazu = table[0];
						BOOL flg2 = FALSE;

						for (int k=0;k<kazu;k++)
						{
							if (m_game->CheckVoiceUsedFlag(table[k+1]))
							{
								flg2 = TRUE;
								break;
							}
						}

						flg = flg2;
					}
				}
			}
		}

		if (flg)
		{
			m_ppVoiceButton[i]->SetAllExist();
			//status
			if (m_game->CheckVoiceFlag(i))
			{
				m_ppVoiceButton[i]->SetState(1);
			}
			else
			{
				m_ppVoiceButton[i]->SetState(0);
			}
		}
		else
		{
			m_ppVoiceButton[i]->SetAllExist(FALSE);
		}


		m_ppVoiceButton[i]->Init();
		if (m_charaVoiceVolumeFlag)
		{
			int gaze = m_game->GetSystemParam(NNNPARAM_CHARAVOICEVOLUME+i);
			gaze -= m_charaVoiceSliderMin;
			m_ppCharaVoiceSlider[i]->Init(gaze);
		}
	}

	for (i=0;i<m_modeButtonKosuu;i++)
	{
		if (m_modeButtonExistFlag[i])
		{
			m_ppModeButton[i]->Init();
		}
	}

	for (i=0;i<m_checkButtonKosuu;i++)
	{
		if (m_ppCheckButton[i] != NULL)
		{
			m_ppCheckButton[i]->Init();
		}
	}

	for (i=0;i<m_clickButtonKosuu;i++)
	{
		m_ppClickButton[i]->Init();
	}

	for (i=0;i<m_expModeButtonKosuu;i++)
	{
		m_ppExpModeButton[i]->Init();
	}

	for (i=0;i<m_expCheckButtonKosuu;i++)
	{
		m_ppExpCheckButton[i]->Init();
	}

	for (i=1;i<m_volumeKosuu;i++)
	{
		int md;
		if (i == 1) md = m_game->GetSystemParam(NNNPARAM_MUSICSWITCH);
		if (i == 2) md = m_game->GetSystemParam(NNNPARAM_SOUNDSWITCH);
		if (i == 3) md = m_game->GetSystemParam(NNNPARAM_VOICESWITCH);
		if (i == 4) md = m_game->GetSystemParam(NNNPARAM_MOVIESWITCH);
		if (i == 5) md = m_game->GetSystemParam(NNNPARAM_SOUNDVOICESWITCH);
		if (i == 8) md = m_game->GetSystemParam(NNNPARAM_TOTALSWITCH);
		if (i == 9) md = m_game->GetSystemParam(NNNPARAM_SCRIPTSESWITCH);

		if ((i<6) || (i >= 8))
		{
			if (m_volumeExistFlag[i])
			{
				m_ppVolumeButton[i]->SetState(md);
				m_ppVolumeButton[i]->Init();
			}
		}
	}


	m_ppSlider[0]->Init(m_game->GetSystemParam(NNNPARAM_MESSAGESPEED));
	int wps = 100 - m_game->GetSystemParam(NNNPARAM_WINDOWPERCENT);
	
	if (m_volumeKosuu >= 7)
	{
		if (m_volumeExistFlag[6])
		{
			m_ppSlider[6]->Init(wps);
		}
	}

	if (m_volumeKosuu >= 8)
	{
		if (m_volumeExistFlag[7])
		{
			m_ppSlider[7]->Init(m_game->GetSystemParam(NNNPARAM_AUTOSPEEDSLIDER));
		}
	}

	if (m_volumeKosuu >= 9)
	{
		if (m_volumeExistFlag[8])
		{
			
			m_ppSlider[8]->Init(m_game->GetSystemParam(NNNPARAM_TOTALVOLUME));
		}
	}

	if (m_volumeKosuu >= 10)
	{
		if (m_volumeExistFlag[9])
		{

			m_ppSlider[9]->Init(m_game->GetSystemParam(NNNPARAM_SCRIPTSEVOLUME));
		}
	}

	int vol0[5];
	vol0[0] = m_game->GetSystemParam(NNNPARAM_MUSICVOLUME);
	vol0[1] = m_game->GetSystemParam(NNNPARAM_SOUNDVOLUME);
	vol0[2] = m_game->GetSystemParam(NNNPARAM_VOICEVOLUME);
	vol0[3] = m_game->GetSystemParam(NNNPARAM_MOVIEVOLUME);
	vol0[4] = m_game->GetSystemParam(NNNPARAM_SOUNDVOICEVOLUME);

	for (i=0;i<5;i++)
	{
		//adjust
		int v = vol0[i];
		if (v<m_realVolumeMinTable[i+1]) v = m_realVolumeMinTable[i+1];
		if (v>m_realVolumeMaxTable[i+1]) v = m_realVolumeMaxTable[i+1];
		int dv = (m_realVolumeMaxTable[i+1] - m_realVolumeMinTable[i+1]);
		if (dv<1) dv = 1;

		v -= m_realVolumeMinTable[i+1];
		v *= m_volumeDevideTable[i+1];
		v /= dv;

		if (v<0) v = 0;
		if (v>m_volumeDevideTable[i+1]) v = m_volumeDevideTable[i+1];

		vol0[i] = v;

		if ((i+1) < m_volumeKosuu)
		{
			if (m_volumeExistFlag[i+1])
			{
				m_ppSlider[i+1]->Init(vol0[i]);
			}
		}
	}


#if defined _TINYAN3DLIB_
//	m_ppModeButton[0]->SetEnable(0,FALSE);
//	m_ppModeButton[0]->SetEnable(1,FALSE);
#endif


	if (1)
	{
		int md = m_game->GetSystemParam(NNNPARAM_SCREENMODE);
		if (m_modeButtonExistFlag[0])
		{
			m_ppModeButton[0]->SetRadio(md);
			m_ppModeButton[0]->Init(md);
		}

		md = m_game->GetSystemParam(NNNPARAM_SKIPMODE);
		if (m_modeButtonExistFlag[1])
		{
			m_ppModeButton[1]->SetRadio(md);
			m_ppModeButton[1]->Init(md);
		}

		md = m_game->GetSystemParam(NNNPARAM_AUTOMODE);
		if (m_modeButtonExistFlag[2])
		{
			m_ppModeButton[2]->SetRadio(md);
			m_ppModeButton[2]->Init(md);
		}
	}

	if (1)
	{
		if (m_ppCheckButton[0] != NULL)
		{
			int md = m_game->GetSystemParam(NNNPARAM_AUTOCONTINUESWITCH);
			m_ppCheckButton[0]->SetState(md);
			m_ppCheckButton[0]->Init();
		}
		if (m_ppCheckButton[1] != NULL)
		{
			int md = m_game->GetSystemParam(NNNPARAM_AUTOSKIPSWITCH);
			m_ppCheckButton[1]->SetState(md);
			m_ppCheckButton[1]->Init();
		}
		if (m_ppCheckButton[2] != NULL)
		{
			int md = m_game->GetSystemParam(NNNPARAM_CHANGEREADMESSAGECOLORSWITCH);
			m_ppCheckButton[2]->SetState(md);
			m_ppCheckButton[2]->Init();
		}
		if (m_ppCheckButton[3] != NULL)
		{
			int md = m_game->GetSystemParam(NNNPARAM_CHANGESELECTMESSAGECOLORSWITCH);
			m_ppCheckButton[3]->SetState(md);
			m_ppCheckButton[3]->Init();
		}
		if (m_ppCheckButton[4] != NULL)
		{
			int md = m_game->GetSystemParam(NNNPARAM_CONTINUEVOICESWITCH);
			m_ppCheckButton[4]->SetState(md);
			m_ppCheckButton[4]->Init();
		}
	}

	if (m_ppSystemVoiceButton != nullptr)
	{
		for (int i = 1; i < m_systemVoiceButtonKosuu; i++)
		{
			if (CheckEnableSystemCharaVoice(i))
			{
				m_ppSystemVoiceButton->SetExist(i, true);
			}
			else
			{
				m_ppSystemVoiceButton->SetExist(i, false);
			}
		}


		int md = m_game->GetUseSystemVoice();
		m_ppSystemVoiceButton->SetRadio(md);
		m_ppSystemVoiceButton->Init(md);
	}

	int configMask = m_game->GetConfigMask();

	for (i=0;i<m_expModeButtonKosuu;i++)
	{
		int md = m_game->GetSystemParam(NNNPARAM_EXPMODE+i);
		m_ppExpModeButton[i]->SetRadio(md);

		if (i<8)
		{
			if (configMask & (1<<i))
			{
				m_ppExpModeButton[i]->SetAllEnable(FALSE);
			}
			else
			{
				m_ppExpModeButton[i]->SetAllEnable(TRUE);
			}
		}

		m_ppExpModeButton[i]->Init(md);
	}


	for (i=0;i<m_expCheckButtonKosuu;i++)
	{
		int md = m_game->GetSystemParam(NNNPARAM_EXPCHECK+i);
		m_ppExpCheckButton[i]->SetState(md);

		if (i<8)
		{
			if (configMask & (1<<(i+8)))
			{
				m_ppExpCheckButton[i]->SetAllEnable(FALSE);
			}
			else
			{
				m_ppExpCheckButton[i]->SetAllEnable(TRUE);
			}
		}
		m_ppExpCheckButton[i]->Init();
	}


	//change voice
	if (m_voiceVoiceChangeFlag)
	{
		for (i=0;i<m_voiceCutNinzu;i++)
		{
			int vmd = 0;
			int varNumber = m_voiceVoiceCheckChangeVar[i];
			if (varNumber != -1)
			{
				if (m_game->GetVarData(varNumber) > 0)
				{
					vmd = 1;
				}
			}

			for (int onoff=0;onoff<2;onoff++)
			{
				CCommonButton* button = m_ppVoiceButton[i]->GetButton(onoff);

				button->SetClickSound(m_voiceVoiceChangeVoice[i*16+onoff*4+0+vmd*8]);
				button->SetCannotClickSound(m_voiceVoiceChangeVoice[i*16+onoff*4+1+vmd*8]);
				button->SetEnterSound(m_voiceVoiceChangeVoice[i*16+onoff*4+2+vmd*8]);
				button->SetExitSound(m_voiceVoiceChangeVoice[i*16+onoff*4+3+vmd*8]);
			}
		}
	}






	//reload all button pic
	ReLoadAllButtonPic();

	m_changingNumber = -1;
	m_changingCount = 1;

	m_mode = -1;

	//slider


//	m_musicSlider->Init(m_game->GetGameVolume(NNNPARAM_MUSICVOLUME));
//	m_seSlider->Init(m_game->GetGameVolume(NNNPARAM_SOUNDVOLUME));
//	m_voiceSlider->Init(m_game->GetGameVolume(NNNPARAM_VOICEVOLUME));
//	m_messageSlider->Init(m_game->GetSystemParam(NNNPARAM_MESSAGESPEED));

	m_captureFlag = FALSE;

	if (m_pageMode == 0)
	{
		m_back->Init();
	}
	else if (m_pageMode == 1)
	{
		m_updownBack->Init();
	}
	else if (m_pageMode == 2)
	{
		m_back->Init();
		ReLoadTabPic();
		m_tabButton->Init(m_page);
	}


//	PlayCommonBGM();

	return -1;
}



int CCommonConfig::Calcu(void)
{
	if (m_game->CheckClickKey(36))
	{
		if (m_game->CheckDebugFlag())
		{
			m_game->ResetLaunch();
		}
	}


	if (m_mode != -1)
	{
		if (m_pageMode == 0)
		{
			int rt = m_back->Calcu(m_inputStatus);
			if (rt != NNNBUTTON_NOTHING)
			{
				int nm = ProcessUpDownBack(rt);
				if (nm >= 0)
				{
					return MyReturnRoutine();
				}
			}
		}
		else if (m_pageMode == 1)
		{
			int rt = m_updownBack->Calcu(m_inputStatus);
			if (rt != NNNBUTTON_NOTHING)
			{
				int nm = ProcessUpDownBack(rt);
				if (nm >= 0)
				{
					if (nm == 0)
					{
						return MyReturnRoutine();
					}
					else
					{
						m_pageYoyaku = nm - 1;
						ChangePageYoyaku();
						return -1;
					}
				}
			}
		}
		else if (m_pageMode == 2)
		{
			if (m_mode == -2)	//back
			{
				int rt = m_back->Calcu(m_inputStatus);
				if (rt != NNNBUTTON_NOTHING)
				{
					int nm = ProcessCommonButton(rt);
					if (nm >= 0)
					{
						return MyReturnRoutine();
					}
				}
				m_tabButton->Calcu(NULL);
			}
			else	//tab
			{
				m_back->Calcu(NULL);

				int rt2 = m_tabButton->Calcu(m_inputStatus);
				if (rt2 != NNNBUTTON_NOTHING)
				{
					int nm2 = ProcessButtonGroup(rt2);
					if (nm2 >= 0)
					{
						m_pageYoyaku = nm2;
						ChangePageYoyaku();
						return -1;
					}
				}
			}
		}
	}
	else
	{
		if (m_pageMode == 0)
		{
			int rt = m_back->Calcu(m_inputStatus);
			if (rt != NNNBUTTON_NOTHING)
			{
				int nm = ProcessCommonButton(rt);
				if (nm >= 0)
				{
					return MyReturnRoutine();
				}

				int st = CCommonButton::GetButtonStatus(rt);
				if (st == NNNBUTTON_STARTCLICK)
				{
					m_mode = -2;	//back clicking
					return -1;
				}
			}
		}
		else if (m_pageMode == 1)
		{
			int rt = m_updownBack->Calcu(m_inputStatus);
			if (rt != NNNBUTTON_NOTHING)
			{
				int nm = ProcessUpDownBack(rt);
				if (nm >= 0)
				{
					if (nm == 0)
					{
						return MyReturnRoutine();
					}
					else
					{
						m_pageYoyaku = nm - 1;
						ChangePageYoyaku();
						return -1;
					}
				}

				int st = CCommonButton::GetButtonStatus(rt);
				if (st == NNNBUTTON_STARTCLICK)
				{
					m_mode = -2;//back updown����
					return -1;
				}
			}
		}
		else if (m_pageMode == 2)
		{
			int rt = m_back->Calcu(m_inputStatus);
			if (rt != NNNBUTTON_NOTHING)
			{
				int nm = ProcessCommonButton(rt);
				if (nm >= 0)
				{
					return MyReturnRoutine();
				}

				int st = CCommonButton::GetButtonStatus(rt);
				if (st == NNNBUTTON_STARTCLICK)
				{
					m_mode = -2;//back����
					return -1;
				}
			}

			int rt2 = m_tabButton->Calcu(m_inputStatus);
			if (rt2 != NNNBUTTON_NOTHING)
			{
				int nm2 = ProcessButtonGroup(rt2);
				if (nm2 >= 0)
				{
					m_pageYoyaku = nm2;
					ChangePageYoyaku();
					return -1;
				}

				int st2 = CCommonButton::GetButtonStatus(rt2);
				if (st2 == NNNBUTTON_STARTCLICK)
				{
					m_mode = nm2;
				}
			}
		}
	}


	if (m_page == m_voicePrintPage - 1)
	{
		for (int i=0;i<m_voiceCutNinzu;i++)
		{
			int rt = NNNBUTTON_NOTHING;

			if (m_charaVoiceVolumeFlag)
			{
//				if (m_ppVoiceButton[i]->GetButton(0)->GetExist())
				if (m_ppVoiceButton[i]->GetAllExist())
				{
					bool off = false;
					if (m_ppVoiceButton[i]->GetState() == 0) off = true;
						
					if (!CheckAppearCharaVoice(i)) off = true;

					if ((m_mode != -1) || off)
					{
						m_ppCharaVoiceSlider[i]->Calcu(NULL);
					}
					else
					{
						int vol = m_ppCharaVoiceSlider[i]->Calcu(m_mouseStatus);
						if (vol != -1)
						{
							m_game->SetSystemParam(NNNPARAM_CHARAVOICEVOLUME+i,vol + m_charaVoiceSliderMin);

							if (m_ppCharaVoiceSlider[i]->GetCaptureFlag() == FALSE)
							{
								//sound?
								int st = m_ppVoiceButton[i]->GetState();
								int snd = m_ppVoiceButton[i]->GetButton(1-st)->GetClickSound();

								if (m_charaVoiceVolumeSE[i] != 0)
								{
									snd = m_charaVoiceVolumeSE[i];
								}

								if (snd > 0)
								{
									int volumeType = m_ppVoiceButton[i]->GetButton(st)->GetVolumeType();
									m_game->PlaySystemSound(snd - 1,volumeType);
								}
							}
						}
					}
				}
			}

			if ((m_mode != -1) || !CheckAppearCharaVoice(i))
			{
				m_ppVoiceButton[i]->Calcu(NULL);
			}
			else
			{
				rt = m_ppVoiceButton[i]->Calcu(m_inputStatus);
			}

			if (rt != NNNBUTTON_NOTHING)
			{
				//���낢��
				int nm = ProcessButtonGroup(rt);

				if (nm >= 0)
				{
					if (nm == 0)	//off
					{
						m_game->SetVoiceFlag(i,TRUE);
						m_ppVoiceButton[i]->SetState(1);
					}
					else	//on
					{
						m_game->SetVoiceFlag(i,FALSE);
						m_ppVoiceButton[i]->SetState(0);
					}

					ReLoadVoiceButtonPic(i);
					m_ppVoiceButton[i]->Init();
				}


//				int st = CCommonButton::GetButtonStatus(rt);
//				if (st == NNNBUTTON_STARTCLICK)
//				{
//					m_mode = i;
//				}
			}
		}
	}


	int i = 0;
	for (i=0;i<m_modeButtonKosuu;i++)
	{
		if (m_modeButtonExistFlag[i])
		{
			if (m_page == m_modeButtonPrintPage[i]-1)
			{
				int rt = NNNBUTTON_NOTHING;

				if (m_mode != -1)
				{
					rt = m_ppModeButton[i]->Calcu(NULL);
				}
				else
				{
					rt = m_ppModeButton[i]->Calcu(m_inputStatus);
				}

				if (rt != NNNBUTTON_NOTHING)
				{
					int nm = ProcessButtonGroup(rt);
					if (nm >= 0)
					{
						if (i == 0)	//screen
						{
							if (nm == 0)
							{
								m_game->ToWindowScreen(FALSE);
							}
							else
							{
								m_game->ToFullScreen(FALSE);
							}
							m_game->SetSystemParam(NNNPARAM_SCREENMODE,nm);
						}
						else if (i == 1)	//skip
						{
							m_game->SetSystemParam(NNNPARAM_SKIPMODE,nm);
						}
						else if (i == 2)	//auto
						{
							m_game->SetSystemParam(NNNPARAM_AUTOMODE,nm);
						}

						m_ppModeButton[i]->SetRadio(nm);
						ReLoadModeButtonPic(i);
						m_ppModeButton[i]->Init(nm);
					}

					int st = CCommonButton::GetButtonStatus(rt);
					if (st == NNNBUTTON_STARTCLICK)
					{
	//					m_mode = i + m_voiceCutNinzu;
					}
				}
			}
		}
	}


	for (i=0;i<m_checkButtonKosuu;i++)
	{
		if (m_page == m_checkButtonPrintPage[i]-1)
		{
			if (m_ppCheckButton[i] != NULL)
			{
				int rt = NNNBUTTON_NOTHING;

				if (m_mode != -1)
				{
					rt = m_ppCheckButton[i]->Calcu(NULL);
				}
				else
				{
					rt = m_ppCheckButton[i]->Calcu(m_inputStatus);
				}

				if (rt != NNNBUTTON_NOTHING)
				{
					int nm = ProcessButtonGroup(rt);
					if (nm >= 0)
					{
						if (i == 0)	//autoContinue
						{
							m_game->SetSystemParam(NNNPARAM_AUTOCONTINUESWITCH,1-nm);
						}

						if (i == 1)	//autoSkip
						{
							m_game->SetSystemParam(NNNPARAM_AUTOSKIPSWITCH, 1 - nm);
						}

						if (i == 2)	//changereadcolor
						{
							m_game->SetSystemParam(NNNPARAM_CHANGEREADMESSAGECOLORSWITCH, 1 - nm);
						}

						if (i == 3)	//changeselectcolor
						{
							m_game->SetSystemParam(NNNPARAM_CHANGESELECTMESSAGECOLORSWITCH, 1 - nm);
						}

						if (i == 4)	//continuevoice
						{
							m_game->SetSystemParam(NNNPARAM_CONTINUEVOICESWITCH, 1 - nm);
						}

						m_ppCheckButton[i]->SetState(1-nm);
						ReLoadCheckButtonPic(i);
						m_ppCheckButton[i]->Init();
					}

					int st = CCommonButton::GetButtonStatus(rt);
					if (st == NNNBUTTON_STARTCLICK)
					{
	//					m_mode = i + m_voiceCutNinzu;
					}
				}
			}
		}
	}



	for (i=0;i<m_expModeButtonKosuu;i++)
	{
		if (m_page == m_expModeButtonPrintPage[i]-1)
		{
			int rt = NNNBUTTON_NOTHING;

			if (m_mode != -1)
			{
				rt = m_ppExpModeButton[i]->Calcu(NULL);
			}
			else
			{
				rt = m_ppExpModeButton[i]->Calcu(m_inputStatus);
			}

			if (rt != NNNBUTTON_NOTHING)
			{
				int nm = ProcessButtonGroup(rt);
				if (nm >= 0)
				{
					m_game->SetSystemParam(NNNPARAM_EXPMODE+i,nm);

					m_ppExpModeButton[i]->SetRadio(nm);
					ReLoadExpModeButtonPic(i);
					m_ppExpModeButton[i]->Init(nm);
				}

				int st = CCommonButton::GetButtonStatus(rt);
				if (st == NNNBUTTON_STARTCLICK)
				{
//					m_mode = i + m_voiceCutNinzu;
				}
			}
		}
	}


	for (i=0;i<m_expCheckButtonKosuu;i++)
	{
		if (m_page == m_expCheckButtonPrintPage[i]-1)
		{
			int rt = NNNBUTTON_NOTHING;

			if (m_mode != -1)
			{
				m_ppExpCheckButton[i]->Calcu(NULL);
			}
			else
			{
				rt = m_ppExpCheckButton[i]->Calcu(m_inputStatus);
			}

			if (rt != NNNBUTTON_NOTHING)
			{
				//���낢��
				int nm = ProcessButtonGroup(rt);

				if (nm >= 0)
				{
					m_ppExpCheckButton[i]->SetState(1-nm);
					m_game->SetSystemParam(NNNPARAM_EXPCHECK+i,1-nm);
					ReLoadExpCheckButtonPic(i);
					m_ppExpCheckButton[i]->Init();
				}
			}
		}
	}

	if (m_ppSystemVoiceButton != nullptr)
	{
		if (m_page == m_systemVoiceButtonPrintPage - 1)
		{
			int rt = NNNBUTTON_NOTHING;


			if (m_mode != -1)
			{
				rt = m_ppSystemVoiceButton->Calcu(NULL);
			}
			else
			{
				rt = m_ppSystemVoiceButton->Calcu(m_inputStatus);
			}

			if (rt != NNNBUTTON_NOTHING)
			{
				int nm = ProcessButtonGroup(rt);
				if (nm >= 0)
				{
					m_game->SetUseSystemVoice(nm);
					m_game->ReLoadSystemSound();

					m_ppSystemVoiceButton->SetRadio(nm);
					m_ppSystemVoiceButton->Init(nm);
					ReLoadSystemVoicePic();
				}

				int st = CCommonButton::GetButtonStatus(rt);
				if (st == NNNBUTTON_STARTCLICK)
				{
					//					m_mode = i + m_voiceCutNinzu;
				}
			}

		}
	}

	for (int i=0;i<m_clickButtonKosuu;i++)
	{
		if (m_page == m_clickButtonPrintPage[i]-1)
		{
			int rt = NNNBUTTON_NOTHING;

			if (m_mode != -1)
			{
				m_ppClickButton[i]->Calcu(NULL);
			}
			else
			{
				rt = m_ppClickButton[i]->Calcu(m_inputStatus);
			}

			if (rt != NNNBUTTON_NOTHING)
			{
				//���낢��
				int nm = ProcessButtonGroup(rt);

				if (nm >= 0)
				{
					if (i == 0)
					{
						InitAllConfig();
					}

					m_ppClickButton[i]->Init();
					ReLoadClickButtonPic(i);
				}
			}
		}
	}


	/*
	if (m_mode != -1)
	{
		if (m_mode == BACKBUTTONCLICKING_OFFSET)
		{
			//@@@@int rt = m_back->Calcu(m_mouseStatus);
			int rt = -1;
			if (rt == NNNBUTTON_NOTHING) return -1;

			int st = rt & NNNBUTTON_STATUSMASK;
			int nm = rt & NNNBUTTON_DATAMASK;

			if (st == NNNBUTTON_NUMBER)
			{
				if (nm == 0)
				{
//					if (m_backMode == KUMIAWASE_MODE)
//					{
//						m_game->BackToKumiawaseMode();
//						return -1;
//					}
					return ReturnFadeOut(m_backMode);

//					return m_backMode;
				}
			}

			return -1;
		}

		if ((m_mode >= 0) && (m_mode < m_radioButtonKosuu))
		{
			m_count--;
			if (m_count<=0)
			{
				CAreaControl::SetNextAllPrint();

				if (m_mode == 0) //window
				{
					m_game->ToWindowScreen();
					m_game->SetSystemParam(NNNPARAM_SCREENMODE,0);
				}
				else if (m_mode == 1) //fullscreen
				{
					m_game->ToFullScreen();
					m_game->SetSystemParam(NNNPARAM_SCREENMODE,1);
				}
				else if (m_mode == 2) //kidoku
				{
					m_game->SetSystemParam(NNNPARAM_SKIPMODE,0);
				}
				else if (m_mode == 3) //midoku
				{
					m_game->SetSystemParam(NNNPARAM_SKIPMODE,1);
				}
				else if (m_mode == 4)	//auto off
				{
					m_game->SetSystemParam(NNNPARAM_AUTOMODE,0);
				}
				else if (m_mode == 5)	//auto on
				{
					m_game->SetSystemParam(NNNPARAM_AUTOMODE,1);
				}
				else if (m_mode == 6)
				{
					//BGM MIDI
//					m_game->SetSystemParam(NNNPARAM_BGMMODE,0);
//					m_game->ToMIDIMode();
//					m_musicSlider->Init(m_game->GetGameVolume(NNNPARAM_MUSICVOLUME));
				}
				else if (m_mode == 7)
				{
					//BGM CD-DA

//					if (m_game->CheckCD())
//					{
//						m_game->SetSystemParam(NNNPARAM_BGMMODE,1);
//						m_game->ToCDDAMode();
//						m_musicSlider->Init(m_game->GetGameVolume(NNNPARAM_MUSICVOLUME));
//					}
//					else
//					{
//						m_game->SetCommonBackMode(CDERROR_MODE,CONFIG_MODE);
//						return ReturnFadeOut(CDERROR_MODE);
//					}
				}

				m_mode = -1;
				return -1;
			}
		}


		if ((m_mode >= VOICEBUTTONNUMBER_OFFSET) && (m_mode < VOICEBUTTONNUMBER_OFFSET+m_voiceCutNinzu))
		{
			m_count--;
			if (m_count<=0)
			{
				CAreaControl::SetNextAllPrint();
				BOOL vb = m_game->CheckVoiceFlag(m_mode-VOICEBUTTONNUMBER_OFFSET);
				m_game->SetVoiceFlag(m_mode - VOICEBUTTONNUMBER_OFFSET, !vb);

				m_mode = -1;
				return -1;
			}
		}

		//
		if ((m_mode >= ADDRADIOBUTTON_OFFSET) && (m_mode < ADDRADIOBUTTON_OFFSET + m_addRadioButtonTotalKosuu))
		{
			m_count--;
			if (m_count<=0)
			{
				CAreaControl::SetNextAllPrint();

				int addGroup = GetAddRadioButtonGroupNumber(m_mode - ADDRADIOBUTTON_OFFSET);
				if (addGroup != -1)
				{
					int addNum = GetAddRadioButtonNumber(m_mode - ADDRADIOBUTTON_OFFSET);
					m_game->SetAdditionalSystemParam(addGroup,addNum);
				}

				m_mode = -1;
				return -1;
			}
		}


		return -1;
	}
*/

/*
	int rt = m_back->Calcu(m_inputStatus);
	//int rt = -1;
	if (rt != NNNBUTTON_NOTHING)
	{
		int st = rt & NNNBUTTON_STATUSMASK;
		int nm = rt & NNNBUTTON_DATAMASK;
		if (st == NNNBUTTON_STARTCLICK)
		{
			m_mode = BACKBUTTONCLICKING_OFFSET;
			return -1;
		}
	}
*/



	BOOL trig1 = m_mouseStatus->GetTrig(0);
	POINT pt = m_mouseStatus->GetZahyo();
	int mouseX = pt.x;
	int mouseY = pt.y;
/*
	if (trig1)
	{
		int smd = m_game->GetSystemParam(NNNPARAM_SCREENMODE);
		int skp = m_game->GetSystemParam(NNNPARAM_SKIPMODE);
		int bgm = m_game->GetSystemParam(NNNPARAM_BGMMODE);
		int aut = m_game->GetSystemParam(NNNPARAM_AUTOMODE);

		int om = GetOnRadioCheckButton(mouseX,mouseY);
		if ((om == 0) && (smd == 1)) m_mode = om;
		if ((om == 1) && (smd == 0)) m_mode = om;
		if ((om == 2) && (skp == 1)) m_mode = om;
		if ((om == 3) && (skp == 0)) m_mode = om;
		if ((om == 4) && (aut == 1)) m_mode = om;
		if ((om == 5) && (aut == 0)) m_mode = om;


		if (m_disableMidiButtonFlag == FALSE)
		{
			if ((om == 6) && (bgm == 1)) m_mode = om;
		}

		if (m_disableCDButtonFlag == FALSE)
		{
			if ((om == 7) && (bgm == 0)) m_mode = om;
		}

		if ((om >= VOICEBUTTONNUMBER_OFFSET) && (om < VOICEBUTTONNUMBER_OFFSET+m_voiceCutNinzu))
		{
			m_mode = om;
		}


		int addom = GetOnAddRadioButton(mouseX,mouseY);
		if (addom != -1)
		{
			int addMode = GetAddRadioButtonGroupNumber(addom);
			int addNum = GetAddRadioButtonNumber(addom);

			if (addMode != -1)
			{
				int oldNum = m_game->GetAdditionalSystemParam(addMode);
				if (oldNum != addNum)
				{
					m_mode = addom + ADDRADIOBUTTON_OFFSET;
				}
			}
		}



		if (m_mode != -1)
		{
			m_count = 8;
			if (m_extSeFlag)
			{
				if (m_mode == 0) PlayExtSe(EXT_SE_WINDOW,0);
				if (m_mode == 1) PlayExtSe(EXT_SE_WINDOW,1);
				if (m_mode == 2) PlayExtSe(EXT_SE_READ,0);
				if (m_mode == 3) PlayExtSe(EXT_SE_READ,1);
				if (m_mode == 4) PlayExtSe(EXT_SE_AUTO,0);
				if (m_mode == 5) PlayExtSe(EXT_SE_AUTO,1);
				if (m_mode == 6) PlayExtSe(EXT_SE_MIDICDDA,0);
				if (m_mode == 7) PlayExtSe(EXT_SE_MIDICDDA,1);

				if ((m_mode >= VOICEBUTTONNUMBER_OFFSET) && (m_mode < VOICEBUTTONNUMBER_OFFSET+m_voiceCutNinzu))
				{
					int sese = m_mode - VOICEBUTTONNUMBER_OFFSET;
					BOOL onoff = TRUE;

					BOOL vb = m_game->CheckVoiceFlag(m_mode-VOICEBUTTONNUMBER_OFFSET);
					if (vb) onoff = FALSE;	//on�������炨����off�ɂȂ�̂�

					if (onoff)
					{
						PlayExtSe(EXT_SE_VOICEON,sese);
					}
					else
					{
						PlayExtSe(EXT_SE_VOICEOFF,sese);
					}
				}

			}
			else
			{
			}

			return -1;
		}
	}
*/


	for (i=0;i<m_volumeKosuu;i++)
	{
		if (m_volumeExistFlag[i])
		{
			if (m_page == m_volumePrintPage[i]-1)
			{
				BOOL ok = TRUE;
				if (((i>=1) && (i<=5)) || (i>=8))
				{
					if (i == 1) ok = m_game->GetSystemParam(NNNPARAM_MUSICSWITCH);
					if (i == 2) ok = m_game->GetSystemParam(NNNPARAM_SOUNDSWITCH);
					if (i == 3) ok = m_game->GetSystemParam(NNNPARAM_VOICESWITCH);
					if (i == 4) ok = m_game->GetSystemParam(NNNPARAM_MOVIESWITCH);
					if (i == 5) ok = m_game->GetSystemParam(NNNPARAM_SOUNDVOICESWITCH);
					if (i == 8) ok = m_game->GetSystemParam(NNNPARAM_TOTALSWITCH);
					if (i == 9) ok = m_game->GetSystemParam(NNNPARAM_SCRIPTSESWITCH);
				}

				if (ok)
				{
					int vol = m_ppSlider[i]->Calcu(m_mouseStatus);
					if (vol != -1)
					{
						if (i == 0)
						{
							m_game->SetSystemParam(NNNPARAM_MESSAGESPEED, vol);
							m_mojiTime = 0;
							m_sampleNowPrintGyo = 0;
						}
						if (i == 6) m_game->SetSystemParam(NNNPARAM_WINDOWPERCENT,100 - vol);
						if (i == 7) m_game->SetSystemParam(NNNPARAM_AUTOSPEEDSLIDER,vol);

						int vol2 = vol;
						if (((i>=1) && (i<=5)) || (i==9))
						{
							vol2 = m_realVolumeMinTable[i] + ((m_realVolumeMaxTable[i]-m_realVolumeMinTable[i])*vol)/m_volumeDevideTable[i];
							if (vol2<m_realVolumeLimitMin) vol2 = m_realVolumeLimitMin;
							if (vol2>m_realVolumeLimitMax) vol2 = m_realVolumeLimitMax;
						}

						if (i == 1) m_game->SetSystemParam(NNNPARAM_MUSICVOLUME,vol2);
						if (i == 2) m_game->SetSystemParam(NNNPARAM_SOUNDVOLUME,vol2);
						if (i == 3) m_game->SetSystemParam(NNNPARAM_VOICEVOLUME,vol2);
						if (i == 4) m_game->SetSystemParam(NNNPARAM_MOVIEVOLUME,vol2);
						if (i == 5) m_game->SetSystemParam(NNNPARAM_SOUNDVOICEVOLUME,vol2);
						if (i == 8) m_game->SetSystemParam(NNNPARAM_TOTALVOLUME,vol2);
						if (i == 9) m_game->SetSystemParam(NNNPARAM_SCRIPTSEVOLUME, vol2);

						if (m_extSeFlag)
						{
							if (m_ppSlider[i]->GetCaptureFlag() == FALSE)
							{
								if (1)
								{
									PlayExtSe2(i,vol);
								}
								else //old
								{
									BOOL voiceFlag = FALSE;

									if (i == 0)
									{
										if (m_messageIsVoice)
										{
											voiceFlag = TRUE;
										}
										PlayExtSe(EXT_SE_MESSAGE,vol,voiceFlag);
									}

									if (i == 2) PlayExtSe(EXT_SE_SOUND);
									if (i == 3)
									{
										int vn = 0;
									//	if (vol > 0) vn = (vol-1) / 11 + 1;
										if (vol > 0) vn = (vol-1) / ((m_volumeDevideTable[i]-1)/9) + 1;
										if (vn >= 9) vn = 9;
										if (vol >= m_volumeDevideTable[i]) vn = 10;
										PlayExtSe(EXT_SE_VOICE,vn,TRUE);
									}
									if (i == 4)
									{
										PlayExtSe(EXT_SE_MOVIE);
										//movie
									}
									if (i == 5)
									{
										PlayExtSe(EXT_SE_SOUNDVOICE);
									}
									if (i == 6)
									{
										if (m_windowPercentIsVoice)
										{
											voiceFlag = TRUE;
										}
										int vn = 0;
										if (m_windowPercentSeBunkatsu > 0)
										{
											if ((vol > 0) && (vol < 100))
											{
												int dv = 99 / m_windowPercentSeBunkatsu;
												if (dv < 1) dv = 1;
												vn = 1 + vol / dv;
												if (vn >= 1 + m_windowPercentSeBunkatsu)
												{
													vn = 1 + m_windowPercentSeBunkatsu - 1;
												}
											}
											if (vol == 100)
											{
												vn = 1 + m_windowPercentSeBunkatsu;
											}
										}

										PlayExtSe(EXT_SE_WINDOWPERCENT,vn,voiceFlag);
									}
									if (i == 7)
									{
										if (m_autoIsVoice)
										{
											voiceFlag = TRUE;
										}
										PlayExtSe(EXT_SE_AUTOSLIDER,vol,voiceFlag);

									}
								}
							}
						}
					}
				}
			}
		}
	}

	//volume switch
//	int vm = m_volumeKosuu;
//	if (vm > 6) vm = 6;
//	for (i=1;i<vm;i++)
	for (i=1;i<m_volumeKosuu;i++)
	{
		if ((i>=6) && (i< 8)) continue;

		if (m_volumeExistFlag[i])
		{
			if (m_page == m_volumePrintPage[i]-1)
			{
				int rt = m_ppVolumeButton[i]->Calcu(m_inputStatus);
				if (rt != NNNBUTTON_NOTHING)
				{
					int nm = ProcessCommonButton(rt);
					if (nm >= 0)
					{
						if (i == 1)
						{
							m_game->SetSystemParam(NNNPARAM_MUSICSWITCH,1-nm);
						}


						if (i == 2) m_game->SetSystemParam(NNNPARAM_SOUNDSWITCH,1-nm);
						if (i == 3) m_game->SetSystemParam(NNNPARAM_VOICESWITCH,1-nm);
						if (i == 4) m_game->SetSystemParam(NNNPARAM_MOVIESWITCH,1-nm);
						if (i == 5) m_game->SetSystemParam(NNNPARAM_SOUNDVOICESWITCH,1-nm);
						if (i == 8) m_game->SetSystemParam(NNNPARAM_TOTALSWITCH,1-nm);
						if (i == 9)
						{
							m_game->SetSystemParam(NNNPARAM_SCRIPTSESWITCH, 1 - nm);
						}

						m_ppVolumeButton[i]->SetState(1-nm);
						ReLoadVolumeButtonPic(i);
						m_ppVolumeButton[i]->Init();

						if ((i == 2) && (nm == 0))
						{
							//replay
							CCommonButton* onButton = m_ppVolumeButton[i]->GetButton(0);
							int cs = onButton->GetClickSound();
							if (cs > 0)
							{
								int volumeType = onButton->GetVolumeType();
								m_game->PlaySystemSound(cs - 1,volumeType);
							}

						}
					}
				}
			}
		}
	}




/*
	int vol = m_musicSlider->Calcu(m_mouseStatus);
	if (vol != -1) m_game->SetGameVolume(NNNPARAM_MUSICVOLUME,vol);
	
	vol = m_seSlider->Calcu(m_mouseStatus);
	if (vol != -1)
	{
		m_game->SetGameVolume(NNNPARAM_SOUNDVOLUME,vol);
		if (m_seSlider->GetCaptureFlag() == FALSE)
		{
			if (m_extSeFlag)
			{
				PlayExtSe(EXT_SE_SOUND);
			}
			else
			{
			}
		}
	}

	vol = m_voiceSlider->Calcu(m_mouseStatus);
	if (vol != -1)
	{
		m_game->SetGameVolume(NNNPARAM_VOICEVOLUME,vol);
		if (m_voiceSlider->GetCaptureFlag() == FALSE)
		{
			if (m_extSeFlag)
			{
				int vn = 0;
				if (vol > 0) vn = (vol-1) / 11 + 1;
				if (vol == 100) vn = 10;
				PlayExtSe(EXT_SE_VOICE,vn,TRUE);
			}
			else
			{
////@@@			m_game->PlayVoiceVolumeVoice();
			}
		}
	}

	vol = m_messageSlider->Calcu(m_mouseStatus);
	if (vol != -1)
	{
		m_game->SetSystemParam(NNNPARAM_MESSAGESPEED,vol);
		if (m_messageSlider->GetCaptureFlag() == FALSE)
		{
			if (m_extSeFlag)
			{
				PlayExtSe(EXT_SE_MESSAGE,vol);

			}
			else
			{

			}
////@@@			m_game->PlayMessageSpeedVoice();
		}
	}
*/

	if (m_windowKosuu > 1)
	{
		if ((m_windowPrintPage-1) == m_page)
		{
			if (m_mouseStatus->CheckClick())
			{
				POINT checkPt = pt;
				checkPt.x -= m_windowPrint.x;
				checkPt.y -= m_windowPrint.y;

				if (m_game->CheckOnMessageWindowSize(checkPt))
				{
					int windowNumber = m_game->GetWindowNumberByConfig();
					windowNumber++;
					windowNumber %= m_windowKosuu;
//OutputDebugString("windowchanged[config]\n");
					m_game->SetWindowNumberByConfig(windowNumber);
					CAreaControl::SetNextAllPrint();
				}
			}
		}
	}


	return -1;
}

int CCommonConfig::Print(void)
{
	BOOL b = CAreaControl::CheckAllPrintMode();

	PrintBackScriptOrBG();

	if (b)
	{
//		m_commonBG->Put(0,0,FALSE);
	}

//	m_musicSlider->Print(b);
//	m_seSlider->Print(b);
//	m_voiceSlider->Print(b);
//	m_messageSlider->Print(b);

	if (m_page == m_voicePrintPage - 1)
	{
		if (m_voiceCutButtonFlag)
		{
			for (int i=0;i<m_voiceCutNinzu;i++)
			{
				//�o��`�F�b�N


				if (CheckAppearCharaVoice(i))
				{
					m_ppVoiceButton[i]->Print(TRUE);
					if (m_charaVoiceVolumeFlag)
					{
						//					if (m_ppVoiceButton[i]->GetButton(0)->GetExist())
						if (m_ppVoiceButton[i]->GetAllExist())
						{
							//bad�`�F�b�N
							BOOL bad = FALSE;
							if (m_ppVoiceButton[i]->GetState() == 0)
							{
								bad = TRUE;
							}


							m_ppCharaVoiceSlider[i]->Print(TRUE, bad);
						}
					}
				}
			}
		}
	}

	int i = 0;
	for (i=0;i<m_modeButtonKosuu;i++)
	{
		if (m_modeButtonExistFlag[i])
		{
			if (m_page == m_modeButtonPrintPage[i]-1)
			{
				m_ppModeButton[i]->Print(TRUE);
			}
		}
	}

	for (i=0;i<m_checkButtonKosuu;i++)
	{
		if (m_page == m_checkButtonPrintPage[i]-1)
		{
			if (m_ppCheckButton[i] != NULL)
			{
				m_ppCheckButton[i]->Print(TRUE);
			}
		}
	}

	for (int i=0;i<m_clickButtonKosuu;i++)
	{
		if (m_page == m_clickButtonPrintPage[i]-1)
		{
			if (m_ppClickButton[i] != NULL)
			{
				m_ppClickButton[i]->Print(TRUE);
			}
		}
	}

	if (m_ppSystemVoiceButton != nullptr)
	{
		if (m_page == m_systemVoiceButtonPrintPage - 1)
		{
			m_ppSystemVoiceButton->Print(true);
		}
	}


	for (i=0;i<m_expModeButtonKosuu;i++)
	{
		if (m_page == m_expModeButtonPrintPage[i]-1)
		{
			if (m_ppExpModeButton[i] != NULL)
			{
				m_ppExpModeButton[i]->Print(TRUE);
			}
		}
	}

	for (i=0;i<m_expCheckButtonKosuu;i++)
	{
		if (m_page == m_expCheckButtonPrintPage[i]-1)
		{
			m_ppExpCheckButton[i]->Print(TRUE);
		}
	}


	for (i=0;i<m_volumeKosuu;i++)
	{
		if (m_page == m_volumePrintPage[i]-1)
		{
			if (m_volumeExistFlag[i])
			{
				BOOL bad = FALSE;
				if (i == 1) if (m_game->GetSystemParam(NNNPARAM_MUSICSWITCH) == 0) bad = TRUE;
				if (i == 2) if (m_game->GetSystemParam(NNNPARAM_SOUNDSWITCH) == 0) bad = TRUE;
				if (i == 3) if (m_game->GetSystemParam(NNNPARAM_VOICESWITCH) == 0) bad = TRUE;
				if (i == 4) if (m_game->GetSystemParam(NNNPARAM_MOVIESWITCH) == 0) bad = TRUE;
				if (i == 5) if (m_game->GetSystemParam(NNNPARAM_SOUNDVOICESWITCH) == 0) bad = TRUE;
				if (i == 8) if (m_game->GetSystemParam(NNNPARAM_TOTALSWITCH) == 0) bad = TRUE;
				if (i == 9) if (m_game->GetSystemParam(NNNPARAM_SCRIPTSESWITCH) == 0) bad = TRUE;


				m_ppSlider[i]->Print(TRUE,bad);
				if (((i>=1) && (i<=5)) || (i>=8)) m_ppVolumeButton[i]->Print(TRUE);
			}
		}
	}

//	if (m_windowKosuu > 1)
	if (m_windowPrintFlag)
	{
		if (m_page == (m_windowPrintPage - 1))
		{
			if (b)
			{
				m_game->PrintMessageWindowDirect(b,TRUE,&m_windowPrint);
				//message
				for (int i=0;i<m_windowMessageKosuu;i++)
				{
					LPSTR mes = m_windowMessage[i];
					if (mes != NULL)
					{
						if ((*mes) != '@')
						{
							int putX = m_windowPrint.x + m_messagePrintX + m_messageNextX * i;
							int putY = m_windowPrint.y + m_messagePrintY + m_messageNextY * i;

							m_message->PrintMessage(putX,putY,mes,m_messageFontSize,m_messageColorR,m_messageColorG,m_messageColorB);
						}
					}
				}
				//name
				if (m_nameMessage != NULL)
				{
					m_message->PrintMessage(m_windowPrint.x + m_namePrintX,m_windowPrint.y + m_namePrintY,m_nameMessage,m_nameFontSize,m_nameColorR,m_nameColorG,m_nameColorB);
				}
			}
		}
	}

	if (m_pageMode == 0)
	{
		m_back->Print(TRUE);
	}
	else if (m_pageMode == 1)
	{
		m_updownBack->Print(TRUE);
	}
	else if (m_pageMode == 2)
	{
		m_back->Print(TRUE);
		m_tabButton->Print(TRUE);
	}

/*
	if (b || (m_mode != -1))
	{
		for (int i=0;i<m_radioButtonKosuu;i++)
		{
			PrintRadioButtonSub(i);
		}

		int n = 0;
		for (i=0;i<m_addRadioButtonGroupKosuu;i++)
		{
			int kosuu = m_addRadioButtonKosuu[i];
			for (int k=0;k<kosuu;k++)
			{
				PrintAddRadioButtonSub(i,k,n);
				n++;
			}
		}

		if (m_voiceCutButtonFlag)
		{
			for (i=0;i<m_voiceCutNinzu;i++)
			{
///				PrintCheckButtonSub(i);
			}
		}
	}
*/

	if (m_useSampleText != 0)
	{
		if ((m_sampleTextPrintPage-1) == m_page)
		{
			PrintSampleText();
		}
	}

	if (m_pageYoyakuFlag)
	{
		m_page = m_pageYoyaku;
		m_pageYoyakuFlag = FALSE;
		ChangePage();
	}
	return -1;
}

void CCommonConfig::PrintSampleText(void)
{
	int frameTime = m_game->GetFrameTime();

	int mojiTime = 0;

	//@@@@@@@@@@@@@@@@@@@@@@@@@�����Ŏ��ۂɂ����������Ԃƒ�������K�v������
	frameTime = m_game->GetNowFrameCount();

	int messageSpeed = m_game->GetSystemParam(NNNPARAM_MESSAGESPEED);
	//	if (CheckAutoMessage())
	//	if (CheckAuto())
	int ml = 1;
	if (m_game->GetSystemParam(NNNPARAM_AUTOMODE))
	{
		ml = m_autoMessageSpeedTable[messageSpeed];
//		mojiTime = m_autoMessageSpeedTable[messageSpeed] * frameTime;
	}
	else
	{
		ml = m_messageSpeedTable[messageSpeed];
//		mojiTime = m_messageSpeedTable[messageSpeed] * frameTime;
	}
	mojiTime = ml * frameTime;

	m_mojiTime += mojiTime;
	int printMojisuu = m_mojiTime / 1000;
	int textLen = strlen(m_sampleText[m_sampleNowPrintGyo]) / 2;
	if (printMojisuu > textLen)
	{
		printMojisuu = textLen;

		if (m_sampleNowPrintGyo == m_samplePrintGyoCount-1)
		{
			if (m_mojiTime >= textLen * 1000 + m_sampleTextWait*ml)
			{
				if (m_sampleTextLoop != 0)
				{
					//top
					printMojisuu = 0;
					m_sampleNowPrintGyo = 0;
					m_mojiTime = 0;
				}
			}
		}
		else if (m_sampleNowPrintGyo <= m_samplePrintGyoCount - 1)
		{
			//next
			printMojisuu = 0;
			m_mojiTime = 0;
			m_sampleNowPrintGyo++;
		}
	}

	for (int i = 0; i <= m_sampleNowPrintGyo; i++)
	{
		int putX = m_sampleTextPrintX;
		int putY = m_sampleTextPrintY + m_sampleTextNextY * i;

		if (i < m_sampleNowPrintGyo)
		{
			m_message->PrintMessage(putX,putY, m_sampleText[i], m_sampleTextFontSize,
				m_sampleTextColorR, m_sampleTextColorG, m_sampleTextColorB);

		}
		else
		{
			m_message->PrintMessageParts(0, printMojisuu, putX,putY, m_sampleText[i], m_sampleTextFontSize,
					m_sampleTextColorR, m_sampleTextColorG, m_sampleTextColorB);

		}
	}

}



/*
int CCommonConfig::GetOnRadioCheckButton(int mouseX, int mouseY)
{
	for (int i=0;i<m_radioButtonKosuu;i++)
	{
		if (1)		//check enable
		{
			int x = mouseX - m_radioButtonZahyoX[i];
			int y = mouseY - m_radioButtonZahyoY[i];

			if ((x>=0) && (x<m_radioButtonSizeX) && (y>=0) && (y<m_radioButtonSizeY))
			{
				return i;
			}
		}
	}

	if (m_voiceCutButtonFlag)
	{
		for (int i=0;i<m_voiceCutNinzu;i++)
		{
			if (1)	//check enable
			{
//				int x = mouseX - m_voiceCheckBoxZahyoX[i];
//				int y = mouseY - m_voiceCheckBoxZahyoY[i];
//				if ((x>=0) && (x<m_voiceCheckBoxSizeX) && (y>=0) && (y<m_voiceCheckBoxSizeY))
//				{
//					return i + VOICEBUTTONNUMBER_OFFSET;
//				}
			}
		}
	}

	return -1;
}
*/

/*
void CCommonConfig::PrintRadioButtonSub(int n)
{
	//erase
	int sizeX = m_radioButtonSizeX;
	int sizeY = m_radioButtonSizeY;

	int putX = m_radioButtonZahyoX[n];
	int putY = m_radioButtonZahyoY[n];

	CAreaControl::AddArea(putX,putY,sizeX,sizeY);

	m_commonBG->Blt(putX,putY,putX,putY,sizeX,sizeY,FALSE);

	BOOL b = FALSE;
	if (n == m_mode) b = TRUE;

	int smd = m_game->GetSystemParam(NNNPARAM_SCREENMODE);
	int skp = m_game->GetSystemParam(NNNPARAM_SKIPMODE);
	int aut = m_game->GetSystemParam(NNNPARAM_AUTOMODE);
	int bgm = m_game->GetSystemParam(NNNPARAM_BGMMODE);

	if ((n == 0) && (smd == 0)) b = TRUE;
	if ((n == 1) && (smd == 1)) b = TRUE;
	if ((n == 2) && (skp == 0)) b = TRUE;
	if ((n == 3) && (skp == 1)) b = TRUE;
	if ((n == 4) && (aut == 0)) b = TRUE;
	if ((n == 5) && (aut == 1)) b = TRUE;
	if ((n == 6) && (bgm == 0)) b = TRUE;
	if ((n == 7) && (bgm == 1)) b = TRUE;
	

	BOOL badButton = FALSE;



	if (n == 6)
	{
		if (m_disableMidiButtonFlag) badButton = TRUE;
	}

	if (n == 7)
	{
		if (m_disableCDButtonFlag) badButton = TRUE;
	}

	if (badButton)
	{
		if (m_badButtonPrintFlag == 1)
		{
			m_radioButtonPic->GreyBlt(putX,putY,0,0,sizeX,sizeY,TRUE);
		}
		else if (m_badButtonPrintFlag == 2)
		{
			if (m_badButtonPic != NULL)
			{
				m_badButtonPic->GreyBlt(putX,putY,0,0,sizeX,sizeY,TRUE);
			}
		}
		return;
	}







	if (m_mode != -1)
	{
		if (m_mode == n)
		{
			if (m_count & 1) b = FALSE;
		}
	}

	if (b)
	{
		m_radioButtonPic->Blt(putX,putY,0,0,sizeX,sizeY,TRUE);
	}
}
*/

/*
void CCommonConfig::PrintAddRadioButtonSub(int group,int nm,int n)
{
	//erase
	int sizeX = m_radioButtonSizeX;
	int sizeY = m_radioButtonSizeY;

	int putX = m_addRadioButtonZahyo[n].x;
	int putY = m_addRadioButtonZahyo[n].y;

	CAreaControl::AddArea(putX,putY,sizeX,sizeY);
	m_commonBG->Blt(putX,putY,putX,putY,sizeX,sizeY,FALSE);

	BOOL b = FALSE;
	if ((n+ADDRADIOBUTTON_OFFSET) == m_mode) b = TRUE;


	if (m_game->GetAdditionalSystemParam(group) == nm) b = TRUE;
*/

/*
	if (badButton)
	{
		if (m_badButtonPrintFlag == 1)
		{
			m_radioButtonPic->GreyBlt(putX,putY,0,0,sizeX,sizeY,TRUE);
		}
		else if (m_badButtonPrintFlag == 2)
		{
			if (m_badButtonPic != NULL)
			{
				m_badButtonPic->GreyBlt(putX,putY,0,0,sizeX,sizeY,TRUE);
			}
		}
		return;
	}
*/

/*




	if (m_mode != -1)
	{
		if (m_mode == (n + ADDRADIOBUTTON_OFFSET))
		{
			if (m_count & 1) b = FALSE;
		}
	}

	if (b)
	{
		m_radioButtonPic->Blt(putX,putY,0,0,sizeX,sizeY,TRUE);
	}

}
*/

/*
void CCommonConfig::PrintCheckButtonSub(int n)
{
	//erase
	int sizeX = m_radioButtonSizeX;
	int sizeY = m_radioButtonSizeY;

	int putX = m_voiceCheckBoxZahyoX[n];
	int putY = m_voiceCheckBoxZahyoY[n];

	CAreaControl::AddArea(putX,putY,sizeX,sizeY);

	m_commonBG->Blt(putX,putY,putX,putY,sizeX,sizeY,FALSE);

	BOOL b = FALSE;
	if ((n + VOICEBUTTONNUMBER_OFFSET) == m_mode) b = TRUE;



	if (m_game->CheckVoiceFlag(n)) b = TRUE;

	if (m_mode != -1)
	{
		if (m_mode == (n + VOICEBUTTONNUMBER_OFFSET))
		{
			if (m_count & 1) b = FALSE;
		}
	}



	if (b)
	{
		m_checkBoxPic->Blt(putX,putY,0,0,sizeX,sizeY,TRUE);
	}
}
*/

int CCommonConfig::GetVoiceOffButtonNumberByTable(int charaNumber)
{
	if (m_voiceOffButtonByTableFlag == 0)
	{
		return charaNumber;
	}

	if (m_ppVoiceCutButtonTable == NULL) return charaNumber;

	for (int i=0;i<m_voiceCutNinzu;i++)
	{
		int* table = m_ppVoiceCutButtonTable[i];
		if (table != NULL)
		{
			int kazu = table[0];
			for (int k=0;k<kazu;k++)
			{
				if (charaNumber == table[k+1]) return i+1;
			}
		}
	}

	//not found

//	char mes[256];
//	wsprintf(mes,"�����{�^�����Ή������L�����ԍ�%d",charaNumber);
//	MessageBox(NULL,mes,"��",MB_OK);

	return charaNumber;
}


void CCommonConfig::PlayExtSe2(int md,int vol)
{
	if (m_extSeFlag == 0) return;
	int nm = -1;

	int voiceFlag = m_isVoiceTable[md];
	int bunkatsu = m_bunkatsuTable[md];
	int volumeMax = m_volumeDevideTable[md];
	//int vn = m_seTable[md];
	nm = m_seTable[md];
	if ((bunkatsu > 0) && (nm != -1))
	{
		if (vol >= volumeMax)
		{
			nm += (bunkatsu+1);
		}
		else if (vol > 0)
		{
			int dv = volumeMax / bunkatsu;
			if (dv<1) dv = 1;
			int delta = (vol+(dv-1)) / dv;
			if (delta > bunkatsu) delta = bunkatsu;
			nm += delta;
		}
	}


	if (nm != -1)
	{
		if (nm < m_seListKosuu)
		{
			//LPSTR soundName = m_seList->GetName(nm * 2);
			LPSTR soundName = GetSoundName(nm);

			if (voiceFlag == FALSE)
			{
				int deltaVol = 0;

				if (md == EXT_SE_MOVIE)
				{
					deltaVol = m_game->GetSystemParam(NNNPARAM_MOVIEVOLUME) - m_game->GetSystemParam(NNNPARAM_SOUNDVOLUME);
				}

				m_game->PlaySystemWaveFilename(soundName,deltaVol);
			}
			else
			{
				m_game->PlaySystemVoiceByFileName(soundName,TRUE,m_voiceSameBufferFlag);
			}
		}
	}
}


void CCommonConfig::PlayExtSe(int md,int n,BOOL voiceFlag)
{
	if (m_extSeFlag == 0) return;


	int nm = -1;

	switch (md)
	{
	case EXT_SE_VOICE:
		nm = m_voiceSe[n];
		break;
	case EXT_SE_MESSAGE:
		nm = m_messageSe[n];
		break;
	case EXT_SE_SOUND:
		nm = m_soundSe;
		break;
	case EXT_SE_MOVIE:
		nm = m_movieSe;
		break;
	case EXT_SE_SOUNDVOICE:
		nm = m_soundVoiceSe;
		break;
	case EXT_SE_AUTOSLIDER:
		nm = m_autoSe[n];
		break;
	case EXT_SE_WINDOWPERCENT:
		nm = m_windowPercentSe[n];
		break;
	}


	if (nm != -1)
	{
		if (nm < m_seListKosuu)
		{
//			LPSTR soundName = m_seList->GetName(nm * 2);
			LPSTR soundName = GetSoundName(nm);

			if (voiceFlag == FALSE)
			{
				int deltaVol = 0;

				if (md == EXT_SE_MOVIE)
				{
					deltaVol = m_game->GetSystemParam(NNNPARAM_MOVIEVOLUME) - m_game->GetSystemParam(NNNPARAM_SOUNDVOLUME);
				}

				m_game->PlaySystemWaveFilename(soundName,deltaVol);
			}
			else
			{
				m_game->PlaySystemVoiceByFileName(soundName,TRUE,m_voiceSameBufferFlag);
			}
		}
	}
}

LPSTR CCommonConfig::GetSoundName(int nm)
{
	int type = 0;
	if (m_useConfigSeVoice)
	{
		if (m_systemVoiceButtonKosuu > 0)
		{
			type = m_game->GetUseSystemVoice();
		}
	}

	if (type == 0)
	{
		return m_seList->GetName(nm * 2);
	}
	
	return m_seVoice[type]->GetName(nm * 2);
}





/*
int CCommonConfig::GetAddRadioButtonGroupNumber(int n)
{
	int kmin = 0;
	for (int i=0;i<m_addRadioButtonGroupKosuu;i++)
	{
		int kosuu = m_addRadioButtonKosuu[i];
		if ((n>=kmin) && (n<(kmin+kosuu)))
		{
			return i;
		}
		kmin += kosuu;
	}

	return -1;
}

int CCommonConfig::GetAddRadioButtonNumber(int n)
{
	int kmin = 0;
	for (int i=0;i<m_addRadioButtonGroupKosuu;i++)
	{
		int kosuu = m_addRadioButtonKosuu[i];
		if ((n>=kmin) && (n<(kmin+kosuu)))
		{
			return n - kmin;
		}
		kmin += kosuu;
	}

	return 0;	//dummy
}

*/

/*
int CCommonConfig::GetOnAddRadioButton(int mouseX,int mouseY)
{
	int n = 0;

	int sizeX = m_radioButtonSizeX;
	int sizeY = m_radioButtonSizeY;

	for (int i=0;i<m_addRadioButtonGroupKosuu;i++)
	{
		int kosuu = m_addRadioButtonKosuu[i];

		for (int k=0;k<kosuu;k++)
		{
			int x = mouseX - m_addRadioButtonZahyo[n].x;
			int y = mouseY - m_addRadioButtonZahyo[n].y;

			if ((x>=0) && (y>=0) && (x<sizeX) && (y<sizeY))
			{
				return n;
			}

			n++;
		}
	}

	return -1;
}
*/


CPicture* CCommonConfig::GetUseOkPicture(int page)
{
	BOOL allFlag = FALSE;
	if (page == -1)
	{
		allFlag = TRUE;
		page = 0;
	}
	else
	{
		page--;
	}


	CPicture* lpPic = NULL;
	if (m_useEffectPicKosuu[page] < 16)
	{
		lpPic = m_game->GetEffectPicture(m_useEffectPicKosuu[page]);
		m_useEffectPicKosuu[page]++;
	}
	else
	{
		lpPic = CSuperButtonPicture::GetPicture(m_useSuperPicKosuu[page]);
		m_useSuperPicKosuu[page]++;
	}

	if (allFlag)
	{
		for (int i=1;i<m_pageMax;i++)
		{
			m_useEffectPicKosuu[i]++;
			m_useSuperPicKosuu[i]++;
		}
	}

	return lpPic;
}



void CCommonConfig::ReLoadAllButtonPic(void)
{
	//voice
	if (m_voiceCutButtonFlag)
	{
		if (m_page == m_voicePrintPage-1)
		{
			for (int i=0;i<m_voiceCutNinzu;i++)
			{
				ReLoadVoiceButtonPic(i);
			}
		}
	}

	//volume
	int n = 1;
	for (n=1;n<m_volumeKosuu;n++)
	{
		if (m_volumeExistFlag[n])
		{
			if (m_page == m_volumePrintPage[n]-1)
			{
				if ((n<6) || (n>=8))
				{
					int md = m_ppVolumeButton[n]->GetState();

					CPicture* lpPic = m_ppVolumeButton[n]->GetPicture(md);
					LPSTR name = m_ppVolumeButton[n]->GetFileName(md);
					char filename[256];
					wsprintf(filename,"sys\\%s",name);
					lpPic->LoadDWQ(filename);
				}
			}
		}
	}


	//message
//	if (m_page == m_messageSpeedPrintPage-1)
//	{
//		//load
//	}

	//modeButton
	for (n=0;n<m_modeButtonKosuu;n++)
	{
		if (m_modeButtonExistFlag[n])
		{
			int md = m_ppModeButton[n]->GetRadio();

			if (m_page == m_modeButtonPrintPage[n]-1)
			{
				for (int i=0;i<2;i++)
				{
					int st = 0;
					if (i == md) st = 1;

					CPicture* lpPic = m_ppModeButton[n]->GetPicture(i,st);
					LPSTR name = m_ppModeButton[n]->GetFileName(i,st);
					char filename[256];
					wsprintf(filename,"sys\\%s",name);
					lpPic->LoadDWQ(filename);
				}
			}
		}


		//load
	}


	for (n=0;n<m_checkButtonKosuu;n++)
	{
		if (m_ppCheckButton[n] != NULL)
		{
			if (m_page == m_checkButtonPrintPage[n]-1)
			{
				int md = m_ppCheckButton[n]->GetState();

				CPicture* lpPic = m_ppCheckButton[n]->GetPicture(md);
				LPSTR name = m_ppCheckButton[n]->GetFileName(md);
				char filename[256];
				wsprintf(filename,"sys\\%s",name);
				lpPic->LoadDWQ(filename);
			}
		}
	}

//systemvoice

	if (m_ppSystemVoiceButton != nullptr)
	{
		int md = m_ppSystemVoiceButton->GetRadio();

		if (m_page == m_systemVoiceButtonPrintPage - 1)
		{
			int radioKosuu = m_ppSystemVoiceButton->GetButtonKosuu();

			for (int i = 0; i < radioKosuu; i++)
			{
				int st = 0;
				if (i == md) st = 1;

				CPicture* lpPic = m_ppSystemVoiceButton->GetPicture(i, st);
				LPSTR name = m_ppSystemVoiceButton->GetFileName(i, st);
				char filename[256];
				wsprintf(filename, "sys\\%s", name);
				lpPic->LoadDWQ(filename);
			}
		}
	}


	for (n=0;n<m_expModeButtonKosuu;n++)
	{
		int md = m_ppExpModeButton[n]->GetRadio();

		if (m_page == m_expModeButtonPrintPage[n]-1)
		{
			int radioKosuu = m_ppExpModeButton[n]->GetButtonKosuu();

			for (int i=0;i<radioKosuu;i++)
			{
				int st = 0;
				if (i == md) st = 1;

				CPicture* lpPic = m_ppExpModeButton[n]->GetPicture(i,st);
				LPSTR name = m_ppExpModeButton[n]->GetFileName(i,st);
				char filename[256];
				wsprintf(filename,"sys\\%s",name);
				lpPic->LoadDWQ(filename);
			}
		}


		//load
	}

	for (n=0;n<m_expCheckButtonKosuu;n++)
	{
		if (m_page == m_expCheckButtonPrintPage[n]-1)
		{
			int md = m_ppExpCheckButton[n]->GetState();

			CPicture* lpPic = m_ppExpCheckButton[n]->GetPicture(md);
			LPSTR name = m_ppExpCheckButton[n]->GetFileName(md);
			char filename[256];
			wsprintf(filename,"sys\\%s",name);
			lpPic->LoadDWQ(filename);
		}
	}


	for (n=0;n<m_clickButtonKosuu;n++)
	{
		if (m_page == m_clickButtonPrintPage[n]-1)
		{
			CPicture* lpPic = m_ppClickButton[n]->GetPicture();
			LPSTR name = m_ppClickButton[n]->GetFileName();
			char filename[256];
			wsprintf(filename,"sys\\%s",name);
			lpPic->LoadDWQ(filename);
		}
	}
}


void CCommonConfig::ChangePageYoyaku(void)
{
	m_pageYoyakuFlag = TRUE;
}

void CCommonConfig::ChangePage(void)
{
	ReLoadBackConfigBG();

	if (m_pageMode == 0)
	{
		m_back->Init();
	}

	//reload radioTab
	//
	if (m_pageMode == 2)
	{
		m_back->Init();
		ReLoadTabPic();
		m_tabButton->Init(m_page);
	}



	ReLoadAllButtonPic();

	if (m_pageMode == 1)
	{
		m_updown->SetPage(m_page);
		m_updownBack->Init();
	}

	//init voice button???
	for (int i=0;i<m_voiceCutNinzu;i++)
	{
		m_ppVoiceButton[i]->Init();
	}

	m_mode = -1;


	if (m_backScriptFlag)
	{
		SetPageNumber();

		if (m_changePageRestartScriptFlag)
		{
			m_game->RestartBackScript();
		}
	}

	CAreaControl::SetNextAllPrint();
}

int CCommonConfig::MyReturnRoutine(void)
{
//	OutputDebugString("[G::E]");
//	CCommonGeneral::CreateExitScreen();
//	OutputDebugString("[F]");

	m_game->FuqueAllEffectYoyaku();

	return ReturnFadeOut(m_backMode);
}


void CCommonConfig::ReLoadBackConfigBG(void)
{
	if (m_backScriptFlag == 0)
	{
		char filename[256];
		wsprintf(filename,"sys\\%s",m_bgFileName[m_page]);
		m_commonBG->LoadDWQ(filename);
	}
}

void CCommonConfig::ReLoadAllRadioButtonPic(void)
{
	if (m_pageMode == 2)
	{
		//check and load

	}
}


void CCommonConfig::ReLoadTabPic(void)
{
	if (m_pageMode != 2) return;

	for (int i=0;i<m_pageMax;i++)
	{
		int st = 0;
		if (i == m_page) st = 1;

		CPicture* lpPic = m_tabButton->GetPicture(i,st);
		LPSTR name = m_tabButton->GetFileName(i,st);
		char filename[256];
		wsprintf(filename,"sys\\%s",name);
		lpPic->LoadDWQ(filename);
	}
}

void CCommonConfig::SetPageNumber(void)
{
	if (m_pageNumberSetFlag)
	{
		if (m_pageNumberVarNumber != -1)
		{
			m_game->SetVarData(m_pageNumberVarNumber,m_page+1);
		}
	}
}


void CCommonConfig::CreateStartScreen(void)
{
	Print();
}

/*
void CCommonConfig::CreateExitScreen(void)
{
	//nothing to do
}
*/

void CCommonConfig::ReLoadVoiceButtonPic(int n)
{
	int md = m_ppVoiceButton[n]->GetState();

	CPicture* lpPic = m_ppVoiceButton[n]->GetPicture(md);
	LPSTR name = m_ppVoiceButton[n]->GetFileName(md);
	char filename[256];

	int k = 0;

	if (m_voiceNameChangeFlag)
	{
		int varNumber = m_voiceNameCheckChangeVar[n];
		if (varNumber != -1)
		{
			k = m_game->GetVarData(varNumber);
		}
	}

	if (k <= 0)
	{
		wsprintf(filename,"sys\\%s",name);
	}
	else
	{
		wsprintf(filename,"sys\\%s_%d",name,k);
	}


	lpPic->LoadDWQ(filename);
}


void CCommonConfig::ReLoadModeButtonPic(int n)
{
	//modeButton
	if (m_ppModeButton[n] == NULL) return;

	int md = m_ppModeButton[n]->GetRadio();

	for (int i=0;i<2;i++)
	{
		int st = 0;
		if (i == md) st = 1;

		CPicture* lpPic = m_ppModeButton[n]->GetPicture(i,st);
		LPSTR name = m_ppModeButton[n]->GetFileName(i,st);
		char filename[256];
		wsprintf(filename,"sys\\%s",name);
		lpPic->LoadDWQ(filename);
	}
}

void CCommonConfig::ReLoadSystemVoicePic(void)
{
	if (m_ppSystemVoiceButton == nullptr) return;

	int md = m_ppSystemVoiceButton->GetRadio();

	for (int i = 0; i < m_systemVoiceButtonKosuu; i++)
	{
		int st = 0;
		if (i == md) st = 1;

		CPicture* lpPic = m_ppSystemVoiceButton->GetPicture(i, st);
		LPSTR name = m_ppSystemVoiceButton->GetFileName(i, st);
		char filename[256];
		wsprintf(filename, "sys\\%s", name);
		lpPic->LoadDWQ(filename);
	}
}


void CCommonConfig::ReLoadClickButtonPic(int n)
{
	//modeButton

	CPicture* lpPic = m_ppClickButton[n]->GetPicture();
	LPSTR name = m_ppClickButton[n]->GetFileName();
	char filename[256];
	wsprintf(filename,"sys\\%s",name);
	lpPic->LoadDWQ(filename);
}

void CCommonConfig::ReLoadExpModeButtonPic(int n)
{
	//modeButton
	int md = m_ppExpModeButton[n]->GetRadio();
	int radioKosuu = m_ppExpModeButton[n]->GetButtonKosuu();

	for (int i=0;i<radioKosuu;i++)
	{
		int st = 0;
		if (i == md) st = 1;

		CPicture* lpPic = m_ppExpModeButton[n]->GetPicture(i,st);
		LPSTR name = m_ppExpModeButton[n]->GetFileName(i,st);
		char filename[256];
		wsprintf(filename,"sys\\%s",name);
		lpPic->LoadDWQ(filename);
	}
}

void CCommonConfig::ReLoadCheckButtonPic(int n)
{
	if (m_ppCheckButton[n] != NULL)
	{
		int md = m_ppCheckButton[n]->GetState();

		CPicture* lpPic = m_ppCheckButton[n]->GetPicture(md);
		LPSTR name = m_ppCheckButton[n]->GetFileName(md);
		char filename[256];
		wsprintf(filename,"sys\\%s",name);
		lpPic->LoadDWQ(filename);
	}
}

void CCommonConfig::ReLoadExpCheckButtonPic(int n)
{
	int md = m_ppExpCheckButton[n]->GetState();

	CPicture* lpPic = m_ppExpCheckButton[n]->GetPicture(md);
	LPSTR name = m_ppExpCheckButton[n]->GetFileName(md);
	char filename[256];
	wsprintf(filename,"sys\\%s",name);
	lpPic->LoadDWQ(filename);
}


void CCommonConfig::ReLoadVolumeButtonPic(int n)
{
	int md = m_ppVolumeButton[n]->GetState();

	CPicture* lpPic = m_ppVolumeButton[n]->GetPicture(md);
	LPSTR name = m_ppVolumeButton[n]->GetFileName(md);
	char filename[256];
	wsprintf(filename,"sys\\%s",name);
	lpPic->LoadDWQ(filename);
}


void CCommonConfig::ReloadScreenButton(void)
{
	//modeButton
	int n = 0;

	int md = m_game->GetSystemParam(NNNPARAM_SCREENMODE);
	if (m_ppModeButton[n] == NULL) return;

	m_ppModeButton[n]->SetRadio(md);
	m_ppModeButton[n]->Init(md);


	if (m_page == m_modeButtonPrintPage[n]-1)
	{
		if (m_modeButtonExistFlag[n])
		{
			for (int i=0;i<2;i++)
			{
				int st = 0;
				if (i == md) st = 1;

				CPicture* lpPic = m_ppModeButton[n]->GetPicture(i,st);
				LPSTR name = m_ppModeButton[n]->GetFileName(i,st);
				char filename[256];
				wsprintf(filename,"sys\\%s",name);
				lpPic->LoadDWQ(filename);
			}
		}
	}
}

void CCommonConfig::BeforeInit(void)
{
	if (m_mustStartPage1Flag)
	{
		m_page = 0;
	}

	if (m_backScriptFlag)
	{
		SetPageNumber();
	}
}


BOOL CCommonConfig::CheckVolumeExist(int n)
{
	int k = -1;
	if (n == NNNPARAM_MESSAGESPEED) k = 0;
	if (n == NNNPARAM_MUSICVOLUME) k = 1;
	if (n == NNNPARAM_SOUNDVOICEVOLUME) k = 2;
	if (n == NNNPARAM_VOICEVOLUME) k = 3;
	if (n == NNNPARAM_MOVIEVOLUME) k = 4;
	if (n == NNNPARAM_SOUNDVOICEVOLUME) k = 5;
	if (n == NNNPARAM_WINDOWPERCENT) k = 6;
	if (n == NNNPARAM_AUTOSPEEDSLIDER) k = 7;
	if (n == NNNPARAM_TOTALVOLUME) k = 8;
	if (n == NNNPARAM_SCRIPTSEVOLUME) k = 9;


	if ((k<0) || (k>=m_volumeKosuu)) return FALSE;

	return m_volumeExistFlag[k];
}

void CCommonConfig::InitAllConfig(void)
{
	if (m_initWindowPercent >= 0)
	{
		m_game->SetSystemParam(NNNPARAM_WINDOWPERCENT,100-m_initWindowPercent);
		CheckAndSetSlider(6,m_initWindowPercent);
	}

	if (m_initWindowNumber >= 0)
	{
		m_game->SetWindowNumberByConfig(m_initWindowNumber);
	}

	if (m_initTotalVolume >= 0)
	{
		m_game->SetSystemParam(NNNPARAM_TOTALVOLUME,m_initTotalVolume);
		CheckAndSetSlider(8,m_initTotalVolume);
	}

	for (int i=1;i<m_volumeKosuu;i++)
//	for (int i=1;i<=5;i++)
	{
//		if ((i<6) || (i==8))
		if ((i<6) || (i>=9))//total volume�͏�Őݒ肳��Ă���
		{
			if (m_initVolume[i] >= 0)
			{
				int vol2 = m_realVolumeMinTable[i] + ((m_realVolumeMaxTable[i]-m_realVolumeMinTable[i])*m_initVolume[i])/100;
				if (vol2<m_realVolumeLimitMin) vol2 = m_realVolumeLimitMin;
				if (vol2>m_realVolumeLimitMax) vol2 = m_realVolumeLimitMax;
				int param = m_n2VolumeSystemParamTable[i];
				m_game->SetSystemParam(param,vol2);
				CheckAndSetSlider(i,(m_initVolume[i]*m_volumeDevideTable[i])/100);

			}
		}
	}

	for (int i=1;i<m_volumeKosuu;i++)
	{
		if ((i<6) || (i>=8))
		{
			if (m_initVolumeSwitch[i] >= 0)
			{
				int param = m_n2VolumeSwitchSystemParamTable[i];

				BOOL ok = TRUE;
				if ((i == 1) || (i >= 8))
				{
					int oldSwitch = m_game->GetSystemParam(param);
					if (oldSwitch == m_initVolumeSwitch[i])
					{
						ok = FALSE;
					}
				}
			

				if (ok)
				{
					m_game->SetSystemParam(param,m_initVolumeSwitch[i]);
				}


				if (m_ppVolumeButton[i] != NULL)
				{
					m_ppVolumeButton[i]->SetState(m_initVolumeSwitch[i]);
					ReLoadVolumeButtonPic(i);
					m_ppVolumeButton[i]->Init();
				}
			}
		}
	}


	/*


	if (m_initMusicVolume >= 0)
	{
		int vol2 = m_volumeMin + ((m_volumeMax-m_volumeMin)*m_initMusicVolume)/100;
		if (vol2<0) vol2 = 0;
		if (vol2>100) vol2 = 100;
		m_game->SetSystemParam(NNNPARAM_MUSICVOLUME,vol2);
		CheckAndSetSlider(1,m_initMusicVolume);
	}
	
	if (m_initSoundVolume >= 0)
	{
		int vol2 = m_volumeMin + ((m_volumeMax-m_volumeMin)*m_initSoundVolume)/100;
		if (vol2<0) vol2 = 0;
		if (vol2>100) vol2 = 100;
		m_game->SetSystemParam(NNNPARAM_SOUNDVOLUME,vol2);
		CheckAndSetSlider(2,m_initSoundVolume);
	}

	if (m_initVoiceVolume >= 0)
	{
		int vol2 = m_volumeMin + ((m_volumeMax-m_volumeMin)*m_initVoiceVolume)/100;
		if (vol2<0) vol2 = 0;
		if (vol2>100) vol2 = 100;

		m_game->SetSystemParam(NNNPARAM_VOICEVOLUME,vol2);
		CheckAndSetSlider(3,m_initVoiceVolume);
	}

	if (m_initMovieVolume >= 0)
	{
		int vol2 = m_volumeMin + ((m_volumeMax-m_volumeMin)*m_initMovieVolume)/100;
		if (vol2<0) vol2 = 0;
		if (vol2>100) vol2 = 100;

		m_game->SetSystemParam(NNNPARAM_MOVIEVOLUME,vol2);
		CheckAndSetSlider(4,m_initMovieVolume);
	}

	if (m_initSoundVoiceVolume >= 0)
	{
		int vol2 = m_volumeMin + ((m_volumeMax-m_volumeMin)*m_initSoundVoiceVolume)/100;
		if (vol2<0) vol2 = 0;
		if (vol2>100) vol2 = 100;

		m_game->SetSystemParam(NNNPARAM_SOUNDVOICEVOLUME,vol2);
		CheckAndSetSlider(5,m_initSoundVoiceVolume);
	}
	*/



	if (m_initMessageSpeed >= 0)
	{
		m_game->SetSystemParam(NNNPARAM_MESSAGESPEED,m_initMessageSpeed);
		CheckAndSetSlider(0,m_initMessageSpeed);
	}

	if (m_initAutoSpeed >= 0)
	{
		m_game->SetSystemParam(NNNPARAM_AUTOSPEEDSLIDER,m_initAutoSpeed);
		CheckAndSetSlider(7,m_initAutoSpeed);
	}


	if (m_initSkipMode >= 0)
	{
		m_game->SetSystemParam(NNNPARAM_SKIPMODE,m_initSkipMode);
		if (m_ppModeButton[1] != NULL)
		{
			m_ppModeButton[1]->SetRadio(m_initSkipMode);
			m_ppModeButton[1]->Init(m_initSkipMode);
			ReLoadModeButtonPic(1);
			m_ppModeButton[1]->Init(m_initSkipMode);
		}
	}




	if (m_initCharaVoiceVolume >= 0)
	{
		if (m_charaVoiceVolumeFlag)
		{
			for (int i=0;i<m_voiceCutNinzu;i++)
			{
				if (m_ppCharaVoiceSlider[i] != NULL)
				{
					m_ppCharaVoiceSlider[i]->Init(m_initCharaVoiceVolume);
					m_game->SetSystemParam(NNNPARAM_CHARAVOICEVOLUME+i,m_initCharaVoiceVolume + m_charaVoiceSliderMin);
				}
			}
		}
	}

	if (m_initCharaVoiceOff >= 0)
	{
		if (m_charaVoiceVolumeFlag)
		{
			for (int i=0;i<m_voiceCutNinzu;i++)
			{
				if (m_ppVoiceButton[i] != NULL)
				{
					if (m_initCharaVoiceOff == 0)	//off
					{
						m_game->SetVoiceFlag(i,TRUE);
						m_ppVoiceButton[i]->SetState(1);
					}
					else	//on
					{
						m_game->SetVoiceFlag(i,FALSE);
						m_ppVoiceButton[i]->SetState(0);
					}

					ReLoadVoiceButtonPic(i);
					m_ppVoiceButton[i]->Init();
				}
			}
		}
	}




	//custom for stoneheads
	if (m_initAnimeSwitch >= 0)
	{
		if (m_expModeButtonKosuu > 0)
		{
			if (m_ppExpModeButton[0] != NULL)
			{
				m_game->SetSystemParam(NNNPARAM_EXPMODE+0,m_initAnimeSwitch);
				m_game->SetAnimeOff(m_initAnimeSwitch);
				m_ppExpModeButton[0]->SetRadio(m_initAnimeSwitch);
				ReLoadExpModeButtonPic(0);
				m_ppExpModeButton[0]->Init(m_initAnimeSwitch);
			}
		}
	}
}


void CCommonConfig::CheckAndSetSlider(int n,int vol)
{
	if (m_volumeKosuu >= (n+1))
	{
		if (m_volumeExistFlag[n])
		{
			if (m_ppSlider[n] != NULL)
			{
				m_ppSlider[n]->Init(vol);
			}
		}
	}

}


bool CCommonConfig::CheckAppearCharaVoice(int n)
{
	return true;
}



bool CCommonConfig::CheckEnableSystemCharaVoice(int n)
{
	bool f = false;

	int cn = m_systemCharaVoiceCheckCharaNumber[n];
	if (cn == 0)
	{
		f = true;
	}

	if (cn > 0)
	{
		//cn-1?
		if (m_game->CheckPlayerVoice(cn))
		{
			f = true;
		}

	}


	int varNumber = m_systemCharaVoiceCheckVar[n];
	if (varNumber != -1)
	{
		if (m_game->GetVarData(varNumber) != 0)
		{
			f = true;
		}
	}

	return f;
}

/*_*/


