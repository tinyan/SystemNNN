//
// commonPrintMessage.cpp
//


#include <windows.h>
#include <stdio.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"

#include "..\nyanLib\include\allGeo.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\allGraphics.h"

#include "..\nnnUtilLib\systempicture.h"

#include "..\nnnUtilLib\myFont.h"
#include "..\nnnUtilLib\myFontCache.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"

#include "..\nnnUtilLib\nnnButtonStatus.h"
#include "..\nnnUtilLib\commonButton.h"

#include "..\nnnUtilLib\printAnimeLayer.h"

#include "commonSystemSoundName.h"

#include "commonMode.h"
#include "commonSystemParamName.h"

#include "gameCallBack.h"

#include "commonGeneral.h"
#include "commonPrintMessage.h"



#include "..\nnnUtilLib\scriptcommand.h"

#include "..\nnnUtilLib\commonKeyList.h"

#include "..\nnnUtilLib\myMessage.h"
#include "..\nnnUtilLib\nameColor.h"
#include "..\nnnUtilLib\scriptDefine.h"

#include "..\nnnUtilLib\cutinNameData.h"
#include "..\nnnUtilLib\cutinMessageWindow.h"




char CCommonPrintMessage::m_defualtNameColorFileName[] = "spt\\namecol.xtx";

char CCommonPrintMessage::m_defaultNameFileName[] = "ta_namepic";
char CCommonPrintMessage::m_defaultLprintBGFileName[] = "ta_fullMessageWindow";


//
// m_windowOffFlag
//	FALSE
//	TRUE	ウィンドウ、メッセージ、オプション表示しない。動作は、表示モードにもどるのみ可能
//
// m_commandOffFlag
//	FALSE
//	TRUE	オプション動作不可（autoキー以外のショートカット含む）
//






#define SPECIAL_CR_CODE ( (('続' >> 8) & 0xff) | (('続' << 8) & 0x0ff00) )
#define SPECIAL_CR_CODE_1BYTE '-'








CCommonPrintMessage::CCommonPrintMessage(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(PRINTMESSAGE_MODE);
	int i = 0;
//	m_classNumber = PRINTMESSAGE_MODE;
	LoadSetupFile("PrintMessage",1000);


	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int maxFontSize = CMyFont::GetMaxFontSize();

	m_windowOffMouseButton = m_game->GetWindowOffMouseButton();
	m_useCutinFlag = m_game->GetUseCutin();

	m_messageFontSizeType = 0;
	m_messageEffectSpeed = 0;
	m_messageEffectTimeYoyaku = 0;
	m_messageEffectYoyaku = 0;

	m_kaeshita = 0;
	m_cutinMode = 0;

	m_printX0 = 100;
	m_printY0 = 100;
	m_nextX0 = 0;
	m_mojiTimeAmari = 0;

	int effectFontColorR = 255;
	int effectFontColorG = 255;
	int effectFontColorB = 255;
	int effectFontColorA = 100;
	GetInitGameParam(&effectFontColorR,"effectFontColorR");
	GetInitGameParam(&effectFontColorG,"effectFontColorG");
	GetInitGameParam(&effectFontColorB,"effectFontColorB");
	GetInitGameParam(&effectFontColorA,"effectFontColorA");
	CMyFontCache::SetEffectColor(effectFontColorR,effectFontColorG,effectFontColorB,effectFontColorA);
	m_fontSize0 = 24;
	GetInitGameParam(&m_fontSize0,"fontSize");
	if (m_fontSize0 > maxFontSize)
	{
		m_fontSize0 = maxFontSize;
	}

	m_fontSize = m_fontSize0;
	m_nextY0 = m_fontSize+6;

	GetInitGameParam(&m_printX0,"printX");
	GetInitGameParam(&m_printY0,"printY");
	GetInitGameParam(&m_nextX0,"nextX");
	GetInitGameParam(&m_nextY0,"nextY");
	m_printX = m_printX0;
	m_printY = m_printY0;
	m_nextX = m_nextX0;
	m_nextY = m_nextY0;
	
	m_spaceX0 = 1;
	GetInitGameParam(&m_spaceX0,"space");
	m_spaceX = m_spaceX0;


	m_LPrintX = 100;
	m_LPrintY = 100;
	m_LNextX = m_nextX;
	m_LNextY = m_nextY;

	m_appendSkipName = 1;
	GetInitGameParam(&m_appendSkipName, "appendSkipName");

	m_lprintAddImageFlag = 0;
	GetInitGameParam(&m_lprintAddImageFlag, "LPrintAddImageFlag");
	m_lprintAddImagePic = NULL;
	if (m_lprintAddImageFlag)
	{
		LPSTR imagename = "lprintimage";
		GetInitGameString(&imagename, "FilenameLPrintImage");
		m_lprintAddImagePic = m_game->GetSystemPicture(imagename);
	}

	GetInitGameParam(&m_LPrintX,"LPrintX");
	GetInitGameParam(&m_LPrintY,"LPrintY");
	GetInitGameParam(&m_LNextX,"LNextX");
	GetInitGameParam(&m_LNextY,"LNextY");


	m_fontSizeTypeKosuu = 0;
	GetInitGameParam(&m_fontSizeTypeKosuu,"fontSizeTypeNumber");
	m_fontSizeTypeKosuu++;

	m_fontSizeByFontSizeType = new int[m_fontSizeTypeKosuu];
	m_printXByFontSizeType = new int[m_fontSizeTypeKosuu];
	m_printYByFontSizeType = new int[m_fontSizeTypeKosuu];
	m_nextXByFontSizeType = new int[m_fontSizeTypeKosuu];
	m_nextYByFontSizeType = new int[m_fontSizeTypeKosuu];
	m_spaceByFontSizeType = new int[m_fontSizeTypeKosuu];

	m_fontSizeByFontSizeType[0] = m_fontSize0;
	m_printXByFontSizeType[0] = m_printX0;
	m_printYByFontSizeType[0] = m_printY0;
	m_nextXByFontSizeType[0] = m_nextX0;
	m_nextYByFontSizeType[0] = m_nextY0;
	m_spaceByFontSizeType[0] =  m_spaceX0;

	for (int i=1;i<m_fontSizeTypeKosuu;i++)
	{
		int fontSizeType = m_fontSize0;
		int printXByFontSize = m_printX0;
		int printYByFontSize = m_printY0;
		int nextXByFontSize = m_nextX0;
		int nextYByFontSize = m_nextY0;
		int spaceByFontSize = m_spaceX0;

		char name[256];
		
		wsprintf(name,"fontSizeByFontSizeType%d",i);
		GetInitGameParam(&fontSizeType,name);
		if (fontSizeType > maxFontSize)
		{
			fontSizeType = maxFontSize;
		}

		m_fontSizeByFontSizeType[i] = fontSizeType;

		wsprintf(name,"printXByFontSizeType%d",i);
		GetInitGameParam(&printXByFontSize,name);
		m_printXByFontSizeType[i] = printXByFontSize;

		wsprintf(name,"printYByFontSizeType%d",i);
		GetInitGameParam(&printYByFontSize,name);
		m_printYByFontSizeType[i] = printYByFontSize;

		wsprintf(name,"nextXByFontSizeType%d",i);
		GetInitGameParam(&nextXByFontSize,name);
		m_nextXByFontSizeType[i] = nextXByFontSize;

		wsprintf(name,"nextYByFontSizeType%d",i);
		GetInitGameParam(&nextYByFontSize,name);
		m_nextYByFontSizeType[i] = nextYByFontSize;

		wsprintf(name,"spaceByFontSizeType%d",i);
		GetInitGameParam(&spaceByFontSize,name);
		m_spaceByFontSizeType[i] = spaceByFontSize;

	}


	m_drawWindowWithMessageFlag = 0;
	GetInitGameParam(&m_drawWindowWithMessageFlag,"drawWindowWithMessageFlag");


	m_checkWheelOkuri = 0;
	GetInitGameParam(&m_checkWheelOkuri,"wheelDownIsClick");

	m_noVoiceIsDefaultWait = 0;
	GetInitGameParam(&m_noVoiceIsDefaultWait,"noVoiceIsDefaultWait");
	m_game->SetExpParam(1,m_noVoiceIsDefaultWait);

//	m_drawOverrapPrintOption = 1;
//	GetInitGameParam(&m_drawOverrapPrintOption,"drawOverrapPrintOption");


	m_colorR = 255;
	m_colorG = 255;
	m_colorB = 255;
	m_shadeColor = 0;

	m_colorCustomFlag = 0;
	GetInitGameParam(&m_colorCustomFlag,"colorCustomFlag");

	m_autoNameWindowFlag = 0;
	GetInitGameParam(&m_autoNameWindowFlag,"autoNameWindowFlag");

	m_autoMessageWaitVoiceFlag = 0;
	GetInitGameParam(&m_autoMessageWaitVoiceFlag,"autoMessageWaitVoiceFlag");

	if (m_colorCustomFlag)
	{
		GetInitGameParam(&m_colorR,"colorR");
		GetInitGameParam(&m_colorG,"colorG");
		GetInitGameParam(&m_colorB,"colorB");

		int shadeR = 0;
		int shadeG = 0;
		int shadeB = 0;

		GetInitGameParam(&shadeR,"shadeColorR");
		GetInitGameParam(&shadeG,"shadeColorG");
		GetInitGameParam(&shadeB,"shadeColorB");

		m_shadeColor = (shadeR << 16) | (shadeG << 8) | shadeB;
	}

	m_readMessageColorR = 255;
	m_readMessageColorG = 0;
	m_readMessageColorB = 0;
	GetInitGameParam(&m_readMessageColorR, "readMessageColorR");
	GetInitGameParam(&m_readMessageColorG, "readMessageColorG");
	GetInitGameParam(&m_readMessageColorB, "readMessageColorB");
	m_readNameColorR = m_readMessageColorR;
	m_readNameColorG = m_readMessageColorG;
	m_readNameColorB = m_readMessageColorB;
	GetInitGameParam(&m_readNameColorR, "readNameColorR");
	GetInitGameParam(&m_readNameColorG, "readNameColorG");
	GetInitGameParam(&m_readNameColorB, "readNameColorB");



	m_windowMessageKosuuMax = 4;
	m_fullMessageKosuuMax = ((screenSizeY - m_LPrintY) / m_LNextY ) - 1;

	GetInitGameParam(&m_windowMessageKosuuMax,"windowMessageNumber");
	GetInitGameParam(&m_fullMessageKosuuMax,"fullMessageNumber");

	m_nameX0 = m_printX - m_nextX;
	m_nameY0 = m_printY - m_nextY;

	m_nameFlag = 1;
	GetInitGameParam(&m_nameFlag,"nameFlag");

	m_nameCenterFlag = 1;
	m_nameLengthMax = 5;
	m_nameFontSize = 20;

	m_nameColorR = 255;
	m_nameColorG = 255;
	m_nameColorB = 255;
	m_nameShadeColor = 0x0;
	m_nameSpaceX0 = 1;

	m_nameXByFontSizeType = new int[m_fontSizeTypeKosuu];
	m_nameYByFontSizeType = new int[m_fontSizeTypeKosuu];
	m_nameSpaceByFontSizeType = new int[m_fontSizeTypeKosuu];




	if (m_nameFlag)
	{
		GetInitGameParam(&m_nameX0,"nameX");
		GetInitGameParam(&m_nameY0,"nameY");
		m_nameX = m_nameX0;
		m_nameY = m_nameY0;


		m_nameXByFontSizeType[0] = m_nameX0;
		m_nameYByFontSizeType[0] = m_nameY0;
		m_nameSpaceByFontSizeType[0] = m_nameSpaceX0;

		GetInitGameParam(&m_nameCenterFlag,"nameCenterFlag");
		GetInitGameParam(&m_nameLengthMax,"nameLengthMax");
		GetInitGameParam(&m_nameFontSize,"nameFontSize");

		GetInitGameParam(&m_nameSpaceX0,"nameSpace");
		m_nameSpaceX = m_nameSpaceX0;


		if (m_colorCustomFlag)
		{
			GetInitGameParam(&m_nameColorR,"nameColorR");
			GetInitGameParam(&m_nameColorG,"nameColorG");
			GetInitGameParam(&m_nameColorB,"nameColorB");

			int shadeR = 0;
			int shadeG = 0;
			int shadeB = 0;

			GetInitGameParam(&shadeR,"nameShadeColorR");
			GetInitGameParam(&shadeG,"nameShadeColorG");
			GetInitGameParam(&shadeB,"nameShadeColorB");

			m_nameShadeColor = (shadeR << 16) | (shadeG << 8) | shadeB;
		}


		for (int i=1;i<m_fontSizeTypeKosuu;i++)
		{
			int nameXByFontSize = m_nameX0;
			int nameYByFontSize = m_nameY0;
			int nameSpaceByFontSize = m_nameSpaceX0;

			char name[256];
			

			wsprintf(name,"nameXByFontSizeType%d",i);
			GetInitGameParam(&nameXByFontSize,name);
			m_nameXByFontSizeType[i] = nameXByFontSize;

			wsprintf(name,"nameYByFontSizeType%d",i);
			GetInitGameParam(&nameYByFontSize,name);
			m_nameYByFontSizeType[i] = nameYByFontSize;

			wsprintf(name,"nameSpaceByFontSizeType%d",i);
			GetInitGameParam(&nameSpaceByFontSize,name);
			m_nameSpaceByFontSizeType[i] = nameSpaceByFontSize;

		}

	}


	m_blockX = 1;
	m_blockY = 4;
	m_LBlockX = 1;
	m_LBlockY = 20;

	GetInitGameParam(&m_blockX,"blockX");
	GetInitGameParam(&m_blockY,"blockY");
	GetInitGameParam(&m_LBlockX,"LBlockX");
	GetInitGameParam(&m_LBlockY,"LBlockY");


	m_lprintBGPic = NULL;


	m_lprintBGMode = 0;
	GetInitGameParam(&m_lprintBGMode,"LPrintBGMode");

	if (m_lprintBGMode & 1)
	{
		m_lprintBGFilename = m_defaultLprintBGFileName;
		GetInitGameString(&m_lprintBGFilename,"lprintBGFileName");
		//m_lprintBGPic = new CPicture();
		m_lprintBGPic = CSystemPicture::GetSystemPicture(m_lprintBGFilename);

		m_lprintBGPrintX = 0;
		m_lprintBGPrintY = 0;
		GetInitGameParam(&m_lprintBGPrintX,"LPrintBGPrintX");
		GetInitGameParam(&m_lprintBGPrintY,"LPrintBGPrintY");
	}


	if (m_lprintBGMode & 2)
	{
		m_lprintBGDeltaR = 0;
		GetInitGameParam(&m_lprintBGDeltaR,"lprintBGDeltaR");
		m_lprintBGDeltaG = m_lprintBGDeltaR;
		GetInitGameParam(&m_lprintBGDeltaG,"lprintBGDeltaG");
		m_lprintBGDeltaB = m_lprintBGDeltaG;
		GetInitGameParam(&m_lprintBGDeltaB,"lprintBGDeltaB");

		m_lprintBGMultiR = 100;
		GetInitGameParam(&m_lprintBGMultiR,"lprintBGMultiR");
		m_lprintBGMultiG = m_lprintBGMultiR;
		GetInitGameParam(&m_lprintBGMultiG,"lprintBGMultiG");
		m_lprintBGMultiB = m_lprintBGMultiG;
		GetInitGameParam(&m_lprintBGMultiB,"lprintBGMultiB");

		m_lprintBGScreenEffectNega = 0;
		GetInitGameParam(&m_lprintBGScreenEffectNega,"lprintBGScreenEffectNega");
		m_lprintBGScreenEffectGrey = 0;
		GetInitGameParam(&m_lprintBGScreenEffectGrey,"lprintBGScreenEffectGrey");

		m_lprintBGClipX = 0;
		m_lprintBGClipY = 0;
		m_lprintBGClipSizeX = screenSizeX;
		m_lprintBGClipSizeY = screenSizeY;
		GetInitGameParam(&m_lprintBGClipX,"lprintBGClipX");
		GetInitGameParam(&m_lprintBGClipY,"lprintBGClipY");
		GetInitGameParam(&m_lprintBGClipSizeX,"lprintBGClipSizeX");
		GetInitGameParam(&m_lprintBGClipSizeY,"lprintBGClipSizeY");

		m_lprintBGGreyClipX = m_lprintBGClipX;
		m_lprintBGGreyClipY = m_lprintBGClipY;
		m_lprintBGGreyClipSizeX = m_lprintBGClipSizeX;
		m_lprintBGGreyClipSizeY = m_lprintBGClipSizeY;
		GetInitGameParam(&m_lprintBGGreyClipX,"lprintBGGreyClipX");
		GetInitGameParam(&m_lprintBGGreyClipY,"lprintBGGreyClipY");
		GetInitGameParam(&m_lprintBGGreyClipSizeX,"lprintBGGreyClipSizeX");
		GetInitGameParam(&m_lprintBGGreyClipSizeY,"lprintBGGreyClipSizeY");

		m_lprintBGNegaClipX = m_lprintBGClipX;
		m_lprintBGNegaClipY = m_lprintBGClipY;
		m_lprintBGNegaClipSizeX = m_lprintBGClipSizeX;
		m_lprintBGNegaClipSizeY = m_lprintBGClipSizeY;
		GetInitGameParam(&m_lprintBGNegaClipX,"lprintBGNegaClipX");
		GetInitGameParam(&m_lprintBGNegaClipY,"lprintBGNegaClipY");
		GetInitGameParam(&m_lprintBGNegaClipSizeX,"lprintBGNegaClipSizeX");
		GetInitGameParam(&m_lprintBGNegaClipSizeY,"lprintBGNegaClipSizeY");

		m_lprintBGAddSubClipX = m_lprintBGClipX;
		m_lprintBGAddSubClipY = m_lprintBGClipY;
		m_lprintBGAddSubClipSizeX = m_lprintBGClipSizeX;
		m_lprintBGAddSubClipSizeY = m_lprintBGClipSizeY;
		GetInitGameParam(&m_lprintBGAddSubClipX,"lprintBGAddSubClipX");
		GetInitGameParam(&m_lprintBGAddSubClipY,"lprintBGAddSubClipY");
		GetInitGameParam(&m_lprintBGAddSubClipSizeX,"lprintBGAddSubClipSizeX");
		GetInitGameParam(&m_lprintBGAddSubClipSizeY,"lprintBGAddSubClipSizeY");

		m_lprintBGMultiClipX = m_lprintBGClipX;
		m_lprintBGMultiClipY = m_lprintBGClipY;
		m_lprintBGMultiClipSizeX = m_lprintBGClipSizeX;
		m_lprintBGMultiClipSizeY = m_lprintBGClipSizeY;
		GetInitGameParam(&m_lprintBGMultiClipX,"lprintBGMultiClipX");
		GetInitGameParam(&m_lprintBGMultiClipY,"lprintBGMultiClipY");
		GetInitGameParam(&m_lprintBGMultiClipSizeX,"lprintBGMultiClipSizeX");
		GetInitGameParam(&m_lprintBGMultiClipSizeY,"lprintBGMultiClipSizeY");

	}


	m_drawOverrapOptionFlag = 1;
	GetInitGameParam(&m_drawOverrapOptionFlag,"drawOverrapOptionFlag");


	m_rightSkipOffIsClick = 0;
	GetInitGameParam(&m_rightSkipOffIsClick,"rightSkipOffIsClick");

//not used!!
//	m_optionFlag = 1;
//	GetInitGameParam(&m_optionFlag,"optionFlag");
//	m_drawOptionFlag = 1;
//	GetInitGameParam(&m_drawOptionFlag,"drawOptionFlag");
//	m_LPrintOptionFlag = 0;
//	GetInitGameParam(&m_LPrintOptionFlag,"LPrintOptionFlag");



	m_noVoiceWait = 20;
	GetInitGameParam(&m_noVoiceWait,"noVoiceWait");

	//m_autoVoiceWaitLastTime = 500;
	//GetInitGameParam(&m_autoVoiceWaitLastTime,"voiceLastWait");
	m_voiceLastWait = 500;
	GetInitGameParam(&m_voiceLastWait,"voiceLastWait");

	m_autoMessageVoiceLastWait = m_voiceLastWait;
	GetInitGameParam(&m_autoMessageVoiceLastWait,"autoMessageVoiceLastWait");

	m_noVoiceLastWait = 2000;
	GetInitGameParam(&m_noVoiceLastWait,"noVoiceLastWait");


	for (int i=0;i<5;i++)
	{
		char name[256];

		int wait1 = m_voiceLastWait;
		sprintf_s(name,sizeof(name),"voiceLastWait%d",i+1);
		GetInitGameParam(&wait1,name);
		m_voiceLastWaitTable[i] = wait1;

		int wait2 = m_noVoiceLastWait;
		sprintf_s(name,sizeof(name),"noVoiceLastWait%d",i+1);
		GetInitGameParam(&wait2,name);
		m_noVoiceLastWaitTable[i] = wait2;


	}

	for (int i=0;i<5;i++)
	{
		m_voiceLastWaitTableAutoMode[i] = m_voiceLastWaitTable[i];
		m_noVoiceLastWaitTableAutoMode[i] = m_noVoiceLastWaitTable[i];
	}




	m_nameColorChangeFlag = 1;
	m_jinbutsuNameKosuu = 0;
	GetInitGameParam(&m_nameColorChangeFlag,"nameColorChangeFlag");

	m_nameColor = NULL;
	if (m_nameColorChangeFlag || m_autoNameWindowFlag)
	{
		m_nameColor = new CNameColor();
		LPSTR namecolorfilename = m_defualtNameColorFileName;
		GetInitGameString(&namecolorfilename,"nameColorFileName");
		m_nameColor->Load(namecolorfilename);
		m_jinbutsuNameKosuu = m_nameColor->GetNameKosuu();
	}


	m_messageSpeedTable[0] = 1 * 20;
	m_messageSpeedTable[1] = 2 * 20;
	m_messageSpeedTable[2] = 3 * 20;
	m_messageSpeedTable[3] = 6 * 20;
	m_messageSpeedTable[4] = 500 * 20;

	int flg = 0;
	GetInitGameParam(&flg,"customMessageSpeed");
	if (flg)
	{
		for (i=0;i<5;i++)
		{
			char name[256];
			wsprintf(name,"messageSpeed%d",i+1);
			GetInitGameParam(&m_messageSpeedTable[i],name);
		}
	}

	for (int i=0;i<5;i++)
	{
		m_autoMessageSpeedTable[i] = m_messageSpeedTable[i];


	}
	int flg2 = 0;
	GetInitGameParam(&flg2,"customAutoMessageSpeed");
	if (flg2)
	{
		for (i=0;i<5;i++)
		{
			char name[256];
			wsprintf(name,"autoMessageSpeed%d",i+1);
			GetInitGameParam(&m_autoMessageSpeedTable[i],name);
		}
	}
	m_useAutoModeWait = 0;
	GetInitGameParam(&m_useAutoModeWait,"useAutoModeWait");
	if (m_useAutoModeWait)
	{
		for (int i=0;i<5;i++)
		{
			char name[256];

			int wait1 = m_voiceLastWaitTable[i];
			sprintf_s(name,sizeof(name),"voiceLastWaitAuto%d",i+1);
			GetInitGameParam(&wait1,name);
			m_voiceLastWaitTableAutoMode[i] = wait1;

			int wait2 = m_noVoiceLastWaitTable[i];
			sprintf_s(name,sizeof(name),"noVoiceLastWaitAuto%d",i+1);
			GetInitGameParam(&wait2,name);
			m_noVoiceLastWaitTableAutoMode[i] = wait2;
		}
	}




	m_cutinNameData = NULL;
	m_cutinMessageWindow = NULL;

	if (m_useCutinFlag)
	{
		m_cutinNameData = new CCutinNameData();
		int cutinWindowBuffer = 4;
		GetInitGameParam(&cutinWindowBuffer,"cutinWindowBufferNumber");
		LPSTR filenameCutin = NULL;
		GetInitGameString(&filenameCutin,"filenameCutin");
		m_cutinMessageWindow = new CCutinMessageWindow(filenameCutin,cutinWindowBuffer);
	}
	m_cutinNamePrintFlag = 0;
	GetInitGameParam(&m_cutinNamePrintFlag,"cutinNamePrintFlag");

	m_autoMessageLastTime = 1000*2;
	GetInitGameParam(&m_autoMessageLastTime,"autoMessageLastWait");


	m_namePicFlag = 0;
	GetInitGameParam(&m_namePicFlag,"namePicFlag");
	if (m_namePicFlag)
	{
		LPSTR nameFilename = m_defaultNameFileName;
		GetInitGameString(&nameFilename,"filenameNamePic");
		m_namePic = m_game->GetSystemPicture(nameFilename);
		m_namePicSizeX = 64;
		m_namePicSizeY = 16;
		GetInitGameParam(&m_namePicSizeX,"namePicSizeX");
		GetInitGameParam(&m_namePicSizeY,"namePicSizeY");
		m_namePicDeltaX = 0;
		m_namePicDeltaY = 0;
		GetInitGameParam(&m_namePicDeltaX,"namePicDeltaX");
		GetInitGameParam(&m_namePicDeltaY,"namePicDeltaY");

	}


	m_printAutoAnimeFlag = 0;
	m_printSkipAnimeFlag = 0;
	m_printAutoAnime = NULL;
	m_printSkipAnime = NULL;
	GetInitGameParam(&m_printAutoAnimeFlag,"autoAnimePrintFlag");
	GetInitGameParam(&m_printSkipAnimeFlag,"skipAnimePrintFlag");
	if (m_printAutoAnimeFlag)
	{
		m_printAutoAnime = new CPrintAnimeLayer(m_setup,"autoAnime",NULL,m_game->GetTaihi(),30,TRUE);
	}
	if (m_printSkipAnimeFlag)
	{
		m_printSkipAnime = new CPrintAnimeLayer(m_setup,"skipAnime",NULL,m_game->GetTaihi(),31,TRUE);
	}


	GetFadeInOutSetup();




	m_shakin = 0;

	m_autoFilmFlag = FALSE;


	m_message = new CMyMessage(m_game->GetMyFont());
//	m_cursor = m_game->GetMessageCursor();

//	m_messageWindow = m_game->GetMessageWindow();
//	m_subMode = CODE_SYSTEMCOMMAND_DRAW;
	m_printMode = CODE_SYSTEMCOMMAND_PRINT;

	m_optionPrintX = 589;
	m_optionPrintY = 7;
	m_optionSizeX = 50;
	m_optionSizeY = 54;

	m_backPrintX = 589;
	m_backPrintY = 7;
	m_backSizeX = 50;
	m_backSizeY = 54;

	m_autoLastCount = 1;
	m_autoLastCount2 = 1;

	m_cursorPat = 0;

	m_drawCount = 1;
	m_messageKosuu = 0;

	m_messagePrintSpeed = 2;
	m_autoMessagePrintSpeed = 2;


	m_jinbutsuNameKosuu =10;



	for (i=0;i<MESSAGEKOSUU_MAX;i++)
	{
		m_messageData[i][0] = 0;
	}

//	m_windowOffFlag = FALSE;
	WindowOn();
//	m_commandOffFlag = FALSE;

	m_messagePrintMojisuu = 1;

	m_messageSerialNumber = -1;

//	m_nowSelectNumber = -1;

//	m_cgMode = FALSE;
	m_sceneMode = FALSE;

	m_charaNameList = m_game->GetCharaNamelsit();

//	m_optionPic = m_game->GetSystemPicture("menubutn");
//	m_backPic = m_game->GetSystemPicture("scene_bk");

	m_optionPic = NULL;
	m_backPic = NULL;

	m_backlogSound = -1;
	GetInitGameParam(&m_backlogSound,"backlogSound");

	m_game->SetBackLogOk(PRINTMESSAGE_MODE);


	m_nowMessageLayer = 4;//dummy



	for (int i=0;i<MESSAGEKOSUU_MAX;i++)
	{
		m_messageLength[i] = -1;
		m_messagePrinted[i] = 0;
		m_cutinData[i*2] = 0;
		m_cutinData[i*2+1] = 0;
	}


	/*
	if (m_useCutinFlag)
	{
		for (i=0;i<16;i++)
		{
			m_cutinMessageKosuu[i] = 0;
			m_cutinZahyo[i].x = (i % 2) * 300 + 50;
			m_cutinZahyo[i].y = i * 40 + 50;
			for (int k=0;k<20;k++)
			{
				m_cutinMessage[i][k] = new char[256];
				m_cutinMessage[i][k][0] = 0;
				m_cutinMessageLength[i][k] = 0;
				m_cutinMessagePrinted[i][k] = 0;
			}
		}
	}
	*/

	GetAllPrintSetup();

}


CCommonPrintMessage::~CCommonPrintMessage()
{
	End();
}

void CCommonPrintMessage::End(void)
{
	ENDDELETECLASS(m_printSkipAnime);
	ENDDELETECLASS(m_printAutoAnime);

	DELETEARRAY(m_nameSpaceByFontSizeType);
	DELETEARRAY(m_nameYByFontSizeType);
	DELETEARRAY(m_nameXByFontSizeType);

	DELETEARRAY(m_spaceByFontSizeType);
	DELETEARRAY(m_nextYByFontSizeType);
	DELETEARRAY(m_nextXByFontSizeType);
	DELETEARRAY(m_printYByFontSizeType);
	DELETEARRAY(m_printXByFontSizeType);
	DELETEARRAY(m_fontSizeByFontSizeType);

	ENDDELETECLASS(m_cutinMessageWindow);
	ENDDELETECLASS(m_cutinNameData);


//	ENDDELETECLASS(m_lprintBGPic);

	if (m_useCutinFlag)
	{
		for (int i=0;i<16;i++)
		{
			for (int k=0;k<20;k++)
			{
//				DELETEARRAY(m_cutinMessage[i][k]);
			}
		}
	}

	ENDDELETECLASS(m_nameColor);
	ENDDELETECLASS(m_message);
}



int CCommonPrintMessage::Init(void)
{
	m_messageSkipMode = m_game->CheckMessageSkipMode();

	m_messageEffect = 0;
	m_messageEffectYoyaku = 0;
	m_messageEffectTimeYoyaku = 0;
	m_messageEffectSpeed = 0;

	m_mojiTimeAmari = 0;
	m_messagePrintSpeed = m_game->GetSystemParam(NNNPARAM_MESSAGESPEED);

	if (m_messagePrintSpeed<0) m_messagePrintSpeed = 0;
	if (m_messagePrintSpeed>4) m_messagePrintSpeed = 4;

	m_autoMessagePrintSpeed = m_messagePrintSpeed;
	if (m_game->CheckVolumeExist(NNNPARAM_AUTOSPEEDSLIDER))
	{
		m_autoMessagePrintSpeed = m_game->GetSystemParam(NNNPARAM_AUTOSPEEDSLIDER);
	}

	m_messageEffectSpeed = 0;

	
	m_cutinWaitClick = FALSE;

	m_skipFlag = FALSE;
	m_maeSkipFlag = FALSE;

//	m_nowSelectNumber = -1;

	if (m_game->CheckSceneMode())
	{
		int dontPlay = m_game->GetDontPlayMode();

		dontPlay = 0;

		if (dontPlay)
		{
			m_game->InitSceneButton();
		}
		else
		{
			m_game->InitOptionButton();
			m_game->InitSkipFilmButton();
		}
	}
	else
	{
		m_game->InitOptionButton();
		m_game->InitSkipFilmButton();
	}

	m_game->RestartLoopSoundAndVoice();

	if (m_game->GetAutoDebugMode())
	{
		m_game->DebugF5Routine();
	}

	return -1;
}




void CCommonPrintMessage::ShakinHensai(void)
{
	if (m_printMode == CODE_SYSTEMCOMMAND_DRAW)
	{
		int kaeseru = m_drawCount;
		if (kaeseru < 1) kaeseru = 1;
		m_kaeshita = m_game->ShakinHensai(kaeseru);

		m_drawCount -= m_kaeshita;
	}
	else if (m_printMode == CODE_SYSTEMCOMMAND_OVERRAP)
	{
		int kaeseru = m_overrapTime - m_overrapCount;
		if (kaeseru < 1) kaeseru = 1;
		m_kaeshita = m_game->ShakinHensai(kaeseru);

		m_overrapCountForPrint = m_overrapCount;
		m_overrapCount += m_kaeshita;
	}
	else
	{
		m_kaeshita = m_game->ShakinHensai(0);
	}
}


BOOL CCommonPrintMessage::CheckOverrapEnd(void)
{
	if (m_overrapCount >= m_overrapTime) return TRUE;
	return FALSE;
}


int CCommonPrintMessage::CalcuOpeningMode(void)
{
	if ((m_mouseStatus->GetTrig(0)) || (m_mouseStatus->GetTrig(1)))
	{
		m_game->StopVoice();
		return TITLE_MODE;	//でokなのか??
	}
	return -1;
}

BOOL CCommonPrintMessage::CheckSceneEnd(int rt)
{
	if (m_game->CheckSceneMode() == FALSE) return FALSE;
	if (rt == NNNBUTTON_NOTHING) return FALSE;

	int nm = ProcessCommonButton(rt);
	if (nm == 0)
	{
		m_game->PlayCommonSystemSound(COMMON_SYSTEMSOUND_CANCEL);
		CreateExitScreen();
		return TRUE;
	}

	return FALSE;
}

int CCommonPrintMessage::CalcuDrawMode(int rt)
{
	if (CheckSceneEnd(rt))
	{
		return ReturnFadeOut(SELECTSCENE_MODE);
	}

	if (CheckSkipOrClickDrawAndOverrrap(rt))
	{
		m_drawCount = 0;
	}

	if (m_drawCount <= 0)
	{
		m_game->SetYoyaku();
		return -1;
	}

	return -1;
}



int CCommonPrintMessage::CalcuOverrapMode(int rt)
{
	if (CheckSceneEnd(rt))
	{
		return ReturnFadeOut(SELECTSCENE_MODE);
	}

	if (CheckSkipOrClickDrawAndOverrrap(rt))
	{
		m_overrapCount = m_overrapTime;
	}

	if (CheckOverrapEnd())
	{
		m_game->SetYoyaku();
		return -1;
	}

	return -1;
}


int CCommonPrintMessage::CalcuPrintMode(int rt)
{
	int dontPlay = m_game->GetDontPlayMode();
	int wheel = m_mouseStatus->GetWheel();


	if (rt != NNNBUTTON_NOTHING)
	{
		int nm = ProcessCommonButton(rt);

		if (nm == 0)
		{
//			return m_game->ChangeToSystemMode(SYSTEMMENU_MODE,PRINTMESSAGE_MODE);
			return ReturnFadeOut(m_game->ChangeToSystemMode(SYSTEMMENU_MODE,PRINTMESSAGE_MODE));
		}

		if (nm == 1)
		{
			m_game->SetCommonBackMode(CONFIG_MODE,PRINTMESSAGE_MODE);
			return ReturnFadeOut(m_game->ChangeToSystemMode(CONFIG_MODE,PRINTMESSAGE_MODE));
		}

		if (nm == 2)
		{
			m_game->SetCommonBackMode(BACKLOG_MODE,PRINTMESSAGE_MODE);
			return ReturnFadeOut(m_game->ChangeToSystemMode(BACKLOG_MODE,PRINTMESSAGE_MODE));
		}

		if (nm == 3)
		{
			m_game->SetCommonBackMode(SAVE_MODE,PRINTMESSAGE_MODE);
			return ReturnFadeOut(m_game->ChangeToSystemMode(SAVE_MODE,PRINTMESSAGE_MODE));
		}

		if (nm == 4)
		{
			m_game->SetCommonBackMode(LOAD_MODE,PRINTMESSAGE_MODE);
			return ReturnFadeOut(m_game->ChangeToSystemMode(LOAD_MODE,PRINTMESSAGE_MODE));
		}

		if (nm == 5)//auto
		{
			int autoMode = m_game->GetSystemParam(NNNPARAM_AUTOMODE);
			m_game->SetSystemParam(NNNPARAM_AUTOMODE,1-autoMode);
		}
		if (nm == 6)//skip
		{
			m_game->SetMessageSkipFlag();
			m_game->InitFreeButton(NNN_FREEBUTTON_SKIP);

		}
		if (nm == 7)//windowoff
		{
			if (CheckWindowOnOffEnable())
			{
				WindowOn(0);
				m_game->SetSystemParam(NNNPARAM_AUTOMODE,0);
				CAreaControl::SetNextAllPrint();
			}
		}

		int st = CCommonButton::GetButtonStatus(rt);
		if (st == NNNBUTTON_STARTCLICK) return -1;
		if (st == NNNBUTTON_CLICKING) return -1;
	}

	m_autoLastCount2 -= m_game->GetNowFrameCount();

	if (CheckMessagePrintEnd() == FALSE)
	{
		CalcuPrinting();
		return -1;
	}


	//windowoff->onはいつでも可能(用心)
	if (CheckWindowOff())
	{
		BOOL woff = CheckClick() || CheckClick(TRUE) || (m_game->CheckClickKey(WINDOWOFF_KEY));
		if (m_windowOffMouseButton != -1)
		{
			if (m_mouseStatus->CheckClick(m_windowOffMouseButton))
			{
				woff = TRUE;
			}
		}

//		if (CheckClick() || CheckClick(TRUE) || (m_game->CheckClickKey(WINDOWOFF_KEY)))
		if (woff)
		{
			m_game->SetSystemParam(NNNPARAM_AUTOMODE,0);
			WindowOn();
//			m_game->Flush();
//			m_game->ClearYoyaku();
			CAreaControl::SetNextAllPrint();
		}
		return -1;
	}

	//windowoff?
	if (CheckWindowOffOperation())
	{
		if (CheckWindowOnOffEnable())
		{
			WindowOn(!CheckWindowOn());
//			m_windowOffFlag = !m_windowOffFlag;
//			m_game->Flush();
//			m_game->ClearYoyaku();
			CAreaControl::SetNextAllPrint();
			return -1;
		}
	}


	//backlog
	if (wheel>0)
	{
		if (m_game->CheckWheelDisable() == FALSE)
		{
			if (CheckWindowOn())
			{
				if (CheckBackLogOk())
				{
					m_game->TaihiAllEffect();

					if (m_backlogSound > 0)
					{
						m_game->PlaySystemSound(m_backlogSound-1);
					}
	//				m_game->PlayCommonSystemSound(COMMON_SYSTEMSOUND_PON);
					m_game->SetCommonBackMode(BACKLOG_MODE,PRINTMESSAGE_MODE);
					return ReturnFadeOut(BACKLOG_MODE);
					//return BACKLOG_MODE;
				}
			}
		}
	}






	BOOL autoFlag = CheckAuto();
	BOOL clkOkuri = CheckOkuri();

	if (CheckAutoMessage())
	{
		autoFlag = FALSE;
		clkOkuri = FALSE;

		//auto end?

		if (m_autoMessageCount >= m_autoMessageLastTime)
		{
			if (m_autoMessageWaitVoiceFlag)
			{
				if (m_autoLastCount2 <= 0)
				{
					clkOkuri = TRUE;
				}
			}
			else
			{
				clkOkuri = TRUE;
			}
		}

		m_autoMessageCount += m_game->GetNowFrameCount();
	}



	if (clkOkuri || autoFlag)
	{
		if (autoFlag == FALSE)
		{
			m_game->SetSystemParam(NNNPARAM_AUTOMODE,0);
		}

		m_game->StopVoice();//????????????????
		MessageIsRead();
		m_game->SetYoyaku();
		return -1;
	}



	if (m_skipFlag)
	{
//		if ((m_maeSkipFlag == FALSE) || (m_skipMode == TRUE) || (CheckMessageRead()) || CheckAuto())
		if ((m_maeSkipFlag == FALSE) || (m_messageSkipMode == TRUE) || (CheckMessageRead()) || autoFlag)
		{
			MessageIsRead();
			m_game->SetYoyaku();
			return -1;
		}
	}


	//short cut key
	if (m_game->CheckClickKey(AUTO_KEY))
	{
		if (CheckOption())
		{
			m_game->SetSystemParam(NNNPARAM_AUTOMODE,1);
		}
	}

	if (rt == NNNBUTTON_NOTHING)
	{
		if (CheckOption())
		{
			int nextMode = m_game->ProcessGameKey(PRINTMESSAGE_MODE);
			if (nextMode != -1)
			{
				m_game->SetSystemParam(NNNPARAM_AUTOMODE,0);
				if (nextMode == SYSTEMMENU_MODE)
				{
					if (m_game->CheckSceneMode())
					{
						m_game->SetSystemMenuSceneMode();
					}
				}
				return ReturnFadeOut(nextMode);
			}
		}
	}

	return -1;
}


/*
int CCommonPrintMessage::CalcuCutinMode(int rt)
{
	int dontPlay = m_game->GetDontPlayMode();
	int wheel = m_mouseStatus->GetWheel();


	if (CheckMessagePrintEnd() == FALSE)
	{
		CalcuPrinting();
		return -1;
	}

	//backlog
	if (0)
	{
		if (wheel>0)
		{
			if (CheckWindowOn())
			{
				if (CheckBackLogOk())
				{
					m_game->TaihiAllEffect();

					if (m_backlogSound > 0)
					{
						m_game->PlaySystemSound(m_backlogSound-1);
					}
					m_game->SetCommonBackMode(BACKLOG_MODE,PRINTMESSAGE_MODE);
					return ReturnFadeOut(BACKLOG_MODE);
				}
			}
		}
	}


	BOOL autoFlag = CheckAuto();
	BOOL clkOkuri = CheckOkuri();

	if (CheckAutoMessage())
	{
		autoFlag = FALSE;
		clkOkuri = FALSE;

		//auto end?

		if (m_autoMessageCount >= m_autoMessageLastTime)
		{
			clkOkuri = TRUE;
		}

		m_autoMessageCount += m_game->GetNowFrameCount();
	}



	if (clkOkuri || autoFlag)
	{
		if (autoFlag == FALSE)
		{
			m_game->SetSystemParam(NNNPARAM_AUTOMODE,0);
		}

		m_game->StopVoice();//????????????????
		MessageIsRead();
		m_game->SetYoyaku();
		m_cutinWaitClick = FALSE;
		return -1;
	}



	if (m_skipFlag)
	{
		if ((m_maeSkipFlag == FALSE) || (m_messageSkipMode == TRUE) || (CheckMessageRead()) || autoFlag)
		{
			MessageIsRead();
			m_game->SetYoyaku();
			m_cutinWaitClick = FALSE;
			return -1;
		}
	}

	if (m_cutinWaitClick == FALSE)
	{
		MessageIsRead();
		m_game->SetYoyaku();
		return -1;
	}


	return -1;
}
*/


void CCommonPrintMessage::CalcuPrinting(void)
{
	if (m_skipFlag)
	{
		if (m_messageSkipMode || (CheckMessageRead()))
		{
			m_messagePrintMojisuu = 10000;

			BOOL bb0 = m_messageSkipMode;
			if (m_messageSkipMode == FALSE)
			{
				if (CheckMessageRead()) bb0 = TRUE;
			}

			if (bb0)
			{
				m_cutinWaitClick = FALSE;
				m_game->SetYoyaku();
				MessageIsRead();
			}
			m_messagePrintingFlag = FALSE;
			return;
		}
	}

	if (CheckAutoMessage() == FALSE)
	{
		if (CheckOkuri())
		{
			if (CheckCannotClick() == FALSE)
			{
				m_game->SetSystemParam(NNNPARAM_AUTOMODE,0);

				m_messagePrintMojisuu = 10000;
		//		m_messagePrintMojisuuPerSecond = 10000;

				m_messagePrintingFlag = FALSE;
			}
		}
	}
	return;
}

void CCommonPrintMessage::CalcuFrameMoji(void)
{
	int frameTime = m_game->GetFrameTime();

	int mojiTime = 0;

//@@@@@@@@@@@@@@@@@@@@@@@@@ここで実際にかかった時間と調整する必要がある
frameTime = m_game->GetNowFrameCount();

//	if (CheckAutoMessage())
//	if (CheckAuto())
	if (m_game->GetSystemParam(NNNPARAM_AUTOMODE))
	{
//		int messagePrintSpeed = GetAutoMessageSpeed();
//		mojiTime = m_messageSpeedTable[messagePrintSpeed] * frameTime;
		if (m_messageEffectSpeed == 0)
		{
			mojiTime = m_autoMessageSpeedTable[m_autoMessagePrintSpeed] * frameTime;
		}
		else
		{
			mojiTime = m_autoMessageSpeedTable[m_messageEffectSpeed-1] * frameTime;
		}
//		mojiTime = m_autoMessageSpeedTable[m_messagePrintSpeed] * frameTime;
	}
	else
	{
		if (m_messageEffectSpeed == 0)
		{
			mojiTime = m_messageSpeedTable[m_messagePrintSpeed] * frameTime;
		}
		else
		{
			mojiTime = m_autoMessageSpeedTable[m_messageEffectSpeed-1] * frameTime;
		}
	}


	mojiTime += m_mojiTimeAmari;
	m_mojiTimeAmari = mojiTime % 1000;
	m_messagePrintMojisuu = mojiTime / 1000;
}



int CCommonPrintMessage::Calcu(void)
{
	m_messageFontSizeType = m_game->GetMessageFontSizeType();
	//dummy



//	m_fontSize = m_fontSize0 * (m_messageFontSizeType + 1);


	ShakinHensai();
	CalcuFrameMoji();

	m_game->CheckAndPlayPoolVoice();
	
	m_game->CalcuEffectOnly();

	m_maeSkipFlag = m_skipFlag;
	m_skipFlag = m_game->CheckMessageSkipFlag();
	if (CheckCannotSkip())
	{
		m_skipFlag = FALSE;
	}

	//opening modeの場合の処理
	if (m_game->CheckOpeningMode())
	{
		return CalcuOpeningMode();
	}


	if (m_game->CalcuSkipFilmButton())
	{
		m_drawCount = 0;
		m_overrapCount = m_overrapTime;
		m_game->SetYoyaku();
		return -1;
	}


	int rt = CalcuOptionButton();
	CheckUserSkipOff();

	if (m_printMode == CODE_SYSTEMCOMMAND_DRAW)
	{
		return CalcuDrawMode(rt);
	}

	if (m_printMode == CODE_SYSTEMCOMMAND_OVERRAP)
	{
		return CalcuOverrapMode(rt);
	}

	return CalcuPrintMode(rt);


	if (m_cutinMode == 0)
	{
//		return CalcuPrintMode(rt);
	}
	else
	{
//		return CalcuCutinMode(rt);
	}
}



int CCommonPrintMessage::Print(void)
{
	if (m_fontSizeTypeKosuu > 1)
	{
		int fontSizeType = m_game->GetMessageFontSizeType();
		if (fontSizeType >= m_fontSizeTypeKosuu)
		{
			fontSizeType = m_fontSizeTypeKosuu-1;
		}
		if (fontSizeType < 0)
		{
			fontSizeType = 0;
		}

		m_fontSize = m_fontSizeByFontSizeType[fontSizeType];
		m_printX = m_printXByFontSizeType[fontSizeType];
		m_printY = m_printYByFontSizeType[fontSizeType];
		m_nextX = m_nextXByFontSizeType[fontSizeType];
		m_nextY = m_nextYByFontSizeType[fontSizeType];
		m_spaceX = m_spaceByFontSizeType[fontSizeType];

		m_nameX = m_nameXByFontSizeType[fontSizeType];
		m_nameY = m_nameYByFontSizeType[fontSizeType];
		m_nameSpaceX = m_nameSpaceByFontSizeType[fontSizeType];
	}




	if (m_cutinMode)
	{
		CAreaControl::SetNextAllPrint();
	}

	if (m_lprintAddImageFlag)
	{
		CAreaControl::SetNextAllPrint();
	}


	BOOL b = CAreaControl::CheckAllPrintMode();

	if (m_printMode == CODE_SYSTEMCOMMAND_OVERRAP)
	{
		PrintOverrapMode();
		if (m_cutinMode != 0)
		{
//			PrintCutinMode();
		}
	}
	else
	{
		m_game->PrintEffect();

		if (m_lprintAddImageFlag)
		{
			if ((m_printMode == CODE_SYSTEMCOMMAND_LPRINT) || (m_printMode == CODE_SYSTEMCOMMAND_APPEND))
			{
				m_lprintAddImagePic->Put(0, 0, TRUE);

			}
		}


		if (m_printMode == CODE_SYSTEMCOMMAND_DRAW)
		{
			PrintDrawMode();
			if (m_cutinMode != 0)
			{
				//PrintCutinMode();
			}
		}
		else if ((m_printMode == CODE_SYSTEMCOMMAND_PRINT) || (m_printMode == CODE_SYSTEMCOMMAND_LPRINT) || (m_printMode == CODE_SYSTEMCOMMAND_APPEND))
		{
			PrintMessageMode();
			if (m_cutinMode == 0)
			{
		//		PrintMessageMode();
			}
			else
			{
		//		PrintCutinMode();
			}
		}

		m_game->PrintEffect(TRUE);
	//	m_game->CountUpOnly(1+m_deltaPaste);
		m_game->CountUpOnly(m_kaeshita);
	}


	if (CheckOption())
	{
		if (CheckPrintMode())
		{
			if (CheckWindowOn())
			{
				m_game->PrintOptionButtonYoyaku();
			}
		}
		else
		{
			if (m_drawOverrapOptionFlag)
			{
				if (m_game->CheckOpeningMode() == FALSE)
				{
					if (0)
					{
						m_game->PrintSceneButtonYoyaku();
					}
					else
					{
						m_game->PrintOptionButtonYoyaku();
					}
				}
			}
		}
	}

	if (m_printAutoAnimeFlag)
	{
		if (m_game->GetSystemParam(NNNPARAM_AUTOMODE))
		{
			m_printAutoAnime->Print(1);
		}
	}
	if (m_printSkipAnimeFlag)
	{
		//if (m_game->GetSystemParam(NNNPARAM_SKIPMODE))
		if (m_game->CheckMessageSkipFlag())
		{
			if (CheckCannotSkip() == FALSE)
			{
				m_printSkipAnime->Print(1);
			}
		}
	}

	m_game->PrintSkipFilmButtonYoyaku();

	return -1;
}



int CCommonPrintMessage::PrintMessageMode(BOOL fromDraw)
{
	BOOL b = CAreaControl::CheckAllPrintMode();
///	m_game->PrintEffect();

	int checkPrintMode = m_printMode;
	if (fromDraw)
	{
		checkPrintMode = CODE_SYSTEMCOMMAND_PRINT;
	}

	if (m_cutinMode == 0)
	{
		if (checkPrintMode == CODE_SYSTEMCOMMAND_PRINT)
		{
			if (checkPrintMode == CODE_SYSTEMCOMMAND_PRINT) 
			{
	//			if (m_windowOffFlag == FALSE)
				if (CheckWindowOn())
				{
					m_game->PrintFace(1,m_messageData[0]);

					BOOL nameWindowFlag = FALSE;

					if (m_autoNameWindowFlag)
					{
						nameWindowFlag = CheckHaveName();
					}
					m_game->PrintMessageWindow(b,nameWindowFlag);

					m_game->PrintFace(2,m_messageData[0]);

				}
			}
			else	//LPRINT APPEND
			{
				//if (m_windowOffFlag == FALSE)
				if (CheckWindowOn())
				{
					//full専用メッセージウィンドウ??
				}
			}
		}
		
		if ((m_printMode == CODE_SYSTEMCOMMAND_LPRINT) || (m_printMode == CODE_SYSTEMCOMMAND_APPEND))
		{
			if (m_lprintBGMode > 0)
			{
				if (CheckWindowOn())
				{
					PrintFullWindow();
				}
			}
		}



	}


	int codeByte = CMyFont::m_codeByte;


	int debugDeltaY = -10;

//OutputDebugString("@");

//	if ((m_windowOffFlag == FALSE) || (m_printMode != CODE_SYSTEMCOMMAND_PRINT))
//	if (m_windowOffFlag == FALSE)
	if (CheckWindowOn())
	{
		//名前特殊?

		BOOL nameFlag = m_nameFlag;

		if (checkPrintMode == CODE_SYSTEMCOMMAND_PRINT)
		{
			if (m_autoNameWindowFlag)
			{
				if (CheckHaveName() == FALSE) nameFlag = FALSE;
			}
		}
		else
		{
			nameFlag = FALSE;
		}


		if (m_cutinMode)
		{
			nameFlag = FALSE;
		}

//		if (m_nameFlag)
		if (nameFlag)
		{
			if (checkPrintMode == CODE_SYSTEMCOMMAND_PRINT)
			{
				int putX = m_nameX;
				int putY = m_nameY;

				int sukima = m_nameSpaceX;
				int kageColor = m_nameShadeColor;

//				int lnln = strlen(m_messageData[0]);
//				lnln /= 2;
				int lnln = m_message->GetMessageRealLength(m_messageData[0]);






				int dlt = m_nameLengthMax-lnln;
				if (dlt<0) dlt = 0;

				
				if (m_nameCenterFlag == 0) dlt = 0;

				int dltdiv = 1;
				if (m_nameCenterFlag == 1) dltdiv = 2;

				if (codeByte != 1)
				{
					putX += (dlt * (m_nameFontSize + sukima)) / dltdiv;
				}
				else
				{
					putX += (dlt * (m_nameFontSize/2 + sukima)) / dltdiv;
				}

				int colR = m_nameColorR;
				int colG = m_nameColorG;
				int colB = m_nameColorB;





				//change color?

				if (m_nameColor != NULL)
				{
					int nameColor = m_nameColor->GetColor(m_messageData[0]);
					colR = (nameColor >> 16) & 0xff;
					colG = (nameColor >>  8) & 0xff;
					colB = (nameColor      ) & 0xff;
				}

				bool rubiColorIsMessageColor = false;
#if defined __SYSTEMNNN_VER2__
				if (m_nowMessageIsReadMessage)
				{
					if (m_game->GetSystemParam(NNNPARAM_CHANGEREADMESSAGECOLORSWITCH))
					{
						colR = m_readNameColorR;
						colG = m_readNameColorG;
						colB = m_readNameColorB;
						rubiColorIsMessageColor = true;
					}
				}
#endif


				//かげ色変化?


				if (b || (m_namePrintedFlag == FALSE))
				{
//					if (m_windowOffFlag == FALSE)
					if (CheckWindowOn())
					{
						if (m_messageKosuu>=1)
						{
							m_nameNumber = m_nameColor->SearchName(m_messageData[0]);

							if ((m_namePicFlag == 0) || (m_nameNumber == -1))
							{
								m_message->PrintMessage(putX,putY,&m_messageData[0][0],m_nameFontSize,colR,colG,colB,sukima,m_nameFontSize,kageColor,true,rubiColorIsMessageColor);
							}
							else
							{
								SIZE nsz = m_namePic->GetPicSize();
								int kosuuX = nsz.cx / m_namePicSizeX;
								if (kosuuX <= 0) kosuuX = 1;

								int nx = m_nameNumber % kosuuX;
								int ny = m_nameNumber / kosuuX;
								int nsrcX = m_namePicSizeX * nx;
								int nsrcY = m_namePicSizeY * ny;
								m_namePic->Blt(m_nameX+m_namePicDeltaX,m_nameY+m_namePicDeltaY,nsrcX,nsrcY,m_namePicSizeX,m_namePicSizeY,TRUE);

							}


							m_namePrintedFlag = TRUE;
						}
					}
				}
			}
		}
		

		int st = 0;
		int kosuu = m_messagePrintMojisuu;
		int ed = m_messageKosuu;

//		if (m_nameFlag)
		if (nameFlag)
		{
			if (m_cutinMode == 0)
			{
				st = 1;
			}
		}

		int cutinGyoLast = 0;

		for (int j=st;j<ed;j++)
		{
			int printed = m_messagePrinted[j];
			int maxLen = m_messageLength[j];

			int putX = m_printX + (j - st) * m_nextX;
			int putY = m_printY + (j - st) * m_nextY;

			if (checkPrintMode == CODE_SYSTEMCOMMAND_LPRINT)
			{
				putX = m_LPrintX + (j - st) * m_LNextX;
				putY = m_LPrintY + (j - st) * m_LNextY;
			}

			int fontSize = m_fontSize;

			if (m_cutinMode != 0)
			{
				int cutinType = m_cutinData[j*2];
				int cutinGyo = m_cutinData[j*2+1];
				if (cutinType > 0)
				{
					POINT cutinPoint = m_cutinNameData->GetZahyo(cutinType);
					POINT cutinNextPoint = m_cutinNameData->GetNextZahyo(cutinType);

					putX = cutinPoint.x + cutinNextPoint.x * j;
					putY = cutinPoint.y + cutinNextPoint.y * j;


					//window?
					if (cutinGyo > cutinGyoLast)
					{
						//print window
						int cutinWindowType = m_cutinNameData->GetWindowType(cutinType);
						if (cutinWindowType >= 1)
						{
							//boxfill



							int cutinMessageMax = m_message->GetMessageRealLength(m_messageData[j]);
							for (int ct = 1;ct<cutinGyo;ct++)
							{
								int cm = m_message->GetMessageRealLength(m_messageData[j+ct]);
								if (cm>cutinMessageMax)
								{
									cutinMessageMax = cm;
								}
							}


							POINT cutinWindowZahyo = m_cutinNameData->GetWindowZahyo(cutinType);
							SIZE cutinWindowSize = m_cutinNameData->GetWindowSize(cutinType,fontSize,cutinGyo,cutinMessageMax);
							int cutinWindowColorR = m_cutinNameData->GetWindowColorR(cutinType);
							int cutinWindowColorG = m_cutinNameData->GetWindowColorG(cutinType);
							int cutinWindowColorB = m_cutinNameData->GetWindowColorB(cutinType);
							int cutinWindowColorA = m_cutinNameData->GetWindowColorA(cutinType);
							CAllGeo::TransBoxFill(cutinWindowZahyo.x, cutinWindowZahyo.y, cutinWindowSize.cx, cutinWindowSize.cy, cutinWindowColorR, cutinWindowColorG, cutinWindowColorB, cutinWindowColorA);
						}
						else if (cutinWindowType < 0)
						{
							//pic
							if (m_cutinMessageWindow != NULL)
							{
								m_cutinMessageWindow->LoadPic(-cutinWindowType);
								POINT cutinWindowZahyo = m_cutinNameData->GetWindowZahyo(cutinType);
								int wps = 100 - m_game->GetSystemParam(NNNPARAM_WINDOWPERCENT);
								m_cutinMessageWindow->SetWindowPercent(wps);
								m_cutinMessageWindow->Print(cutinWindowZahyo);
							}
						}
					}

					//fontsize?
					fontSize = m_fontSize + m_cutinNameData->GetFontSizeDelta(cutinType);

					cutinGyoLast = cutinGyo;
				}
			}





			int colR = m_colorR;
			int colG = m_colorG;
			int colB = m_colorB;

			bool rubiColorIsMessageColor = false;
#if defined __SYSTEMNNN_VER2__
			if (m_nowMessageIsReadMessage)
			{
				if (m_game->GetSystemParam(NNNPARAM_CHANGEREADMESSAGECOLORSWITCH))
				{
					colR = m_readMessageColorR;
					colG = m_readMessageColorG;
					colB = m_readMessageColorB;
					rubiColorIsMessageColor = true;
				}
			}
#endif



			int sukima = m_spaceX;

			//色へんか?
			if (j == st)
			{
				//@@@@@@@@
			}


			//かげへんか?
			int kageColor = m_shadeColor;




			if ((maxLen != -1) && (printed >= maxLen))	//old line
			{
			//	OutputDebugString("o");
				if (b)
				{
					m_message->PrintMessage(putX ,putY,&m_messageData[j][0],fontSize,colR,colG,colB,sukima,m_nextY,kageColor,true, rubiColorIsMessageColor);
//					m_message->PrintMessage(putX,putY+30*j,&m_messageData[j][0],m_fontSize,colR,colG,colB,sukima,m_nextY,kageColor);
				}
				m_messagePrintedGyo = j;
			}
			else	//new or now line
			{
			//	OutputDebugString("n");
				if (b)
				{
					kosuu += printed;
					printed = 0;
				}

				if (kosuu>=0)
				{
			//		OutputDebugString("c");
					int amari = 0;
					
					BOOL bbb = FALSE;
					if (j>0)
					{
			//		OutputDebugString("d");
						if ((j == m_messagePrintedGyo) || (j == m_messagePrintedGyo + 1))
						{
			//		OutputDebugString("e");
							if (m_messagePrinted[j-1] >= m_messageLength[j-1]) bbb = TRUE;
						}
					}

					if ((kosuu > 0) || (j == 0) || bbb)
					{

					if (m_messageEffect > 0)
					{

						amari = m_message->PrintEffectMessageParts(printed,kosuu,putX ,putY,&m_messageData[j][0],fontSize,colR,colG,colB,sukima,m_nextY,kageColor,TRUE,m_messageEffect,m_mojiTimeAmari, rubiColorIsMessageColor);
					//	char mmm[256];
					//	sprintf_s(mmm,256,"\x00d\x00a [%d] gyo=%d printed=%d kosuu=%d timeamari=%d amari=%d",m_messagePrintMojisuu,j,printed,kosuu,m_mojiTimeAmari,amari);
					//	OutputDebugString(mmm);
					}
					else
					{
						amari = m_message->PrintMessageParts(printed,kosuu,putX ,putY,&m_messageData[j][0],fontSize,colR,colG,colB,sukima,m_nextY,kageColor, true,rubiColorIsMessageColor);
					}

					m_messagePrintedGyo = j;

//					int amari = m_message->PrintMessageParts(printed,kosuu,putX,putY+m_nextY*(j - st),&m_messageData[j][0],m_fontSize,colR,colG,colB,sukima,m_nextY,kageColor);
					if (amari == 0)
					{
				//	OutputDebugString("f");
						m_messagePrinted[j] = printed + kosuu;
						m_messageLength[j] = printed + kosuu;
						kosuu = 0;
						//new line
						if (m_messagePrintedGyo < ed-1)
						{
				//	OutputDebugString("g");
							m_messagePrintedGyo++;
						}
					}
					else if (amari>0)
					{
						m_messagePrinted[j] = printed + kosuu;
						m_messageLength[j] = printed + kosuu + amari;
						kosuu = 0;
					}
					else
					{
						m_messagePrinted[j] = printed + kosuu + amari;
						m_messageLength[j] = printed + kosuu + amari;
						kosuu = -amari;
					}


					if (j == (ed-1))
					{
						if (m_messagePrinted[j] >= m_messageLength[j])
						{
//							MessageIsRead();
							m_messagePrintingFlag = FALSE;
							break;
						}
					}
					}
				}
			}
		}

	}

//	if ((m_printMode == CODE_SYSTEMCOMMAND_PRINT) && (m_messageKosuu<=1))
//	{
//		MessageIsRead();
//		m_messagePrintingFlag = FALSE;
//	}


//	if ((m_messagePrintingFlag == FALSE) && (m_windowOffFlag == FALSE))
	if (((m_messagePrintingFlag == FALSE) && CheckWindowOn()) && fromDraw == FALSE)
	{
		if (checkPrintMode != CODE_SYSTEMCOMMAND_DRAW)
		{
			if (CheckAutoMessage() == FALSE)
			{
			//print lprintでわける
				if (checkPrintMode == CODE_SYSTEMCOMMAND_PRINT)
				{
					//カーソル計算、せっと
	//				m_cursorPat++;
	//				m_cursorPat %= 20;
					m_game->CursorAnime();
					m_game->SetMyCursor();

	//				m_game->SetMyCursor(714,536,m_cursorPat);
				}
				else
				{
					m_game->CursorAnime();


					int fcpat = 2;	//3も含む

					int x = m_LPrintX + m_messageLength[m_messageKosuu-1] * (m_fontSize + m_spaceX);
					int y = m_LPrintY + (m_messageKosuu-1) * m_LNextY;

					m_game->SetMyCursor(x,y,fcpat);	//座標指定する



	///				CMessageCursor::SetPrint(600,20+30*m_messageKosuu);	//???
				}
			}
		}
	}


	return -1;
}

void CCommonPrintMessage::CheckAndPrintFillWindow(void)
{
	if (m_lprintBGMode > 0)
	{
		if (CheckWindowOn())
		{
			PrintFullWindow();
		}
	}
}

void CCommonPrintMessage::PrintFullWindow(void)
{
	CAreaControl::SetNextAllPrint();


	if (m_lprintBGMode & 2)
	{

		//nega
		if (m_lprintBGScreenEffectNega)
		{
			CAllGraphics::NegaClip(m_lprintBGNegaClipX,m_lprintBGNegaClipY,m_lprintBGNegaClipSizeX,m_lprintBGNegaClipSizeY);
		}

		//grey
		if (m_lprintBGScreenEffectGrey)
		{
			CAllGraphics::GreyClip(m_lprintBGGreyClipX,m_lprintBGGreyClipY,m_lprintBGGreyClipSizeX,m_lprintBGGreyClipSizeY);
		}

		//multi
		if ((m_lprintBGMultiR != 100) || (m_lprintBGMultiG != 100) || (m_lprintBGMultiB != 100))
		{
			CAllGraphics::MultiClip(m_lprintBGMultiClipX,m_lprintBGMultiClipY,m_lprintBGMultiClipSizeX,m_lprintBGMultiClipSizeY,m_lprintBGMultiR,m_lprintBGMultiG,m_lprintBGMultiB);
		}

		//add
		if ((m_lprintBGDeltaR != 0) || (m_lprintBGDeltaG != 0) || (m_lprintBGDeltaB != 0))
		{
			CAllGraphics::AddSubClip(m_lprintBGAddSubClipX,m_lprintBGAddSubClipY,m_lprintBGAddSubClipSizeX,m_lprintBGAddSubClipSizeY,m_lprintBGDeltaR,m_lprintBGDeltaG,m_lprintBGDeltaB);
		}

	}

	if (m_lprintBGMode & 1)
	{
		m_lprintBGPic->Put(m_lprintBGPrintX,m_lprintBGPrintY,TRUE);
	}

}



/*
int CCommonPrintMessage::PrintCutinMode(void)
{
	BOOL b = CAreaControl::CheckAllPrintMode();



	//fukidashi?
	if (m_printMode == CODE_SYSTEMCOMMAND_PRINT)
	{
		if (m_printMode == CODE_SYSTEMCOMMAND_PRINT)
		{
//			if (m_windowOffFlag == FALSE)
			if (CheckWindowOn())
			{
				BOOL nameWindowFlag = FALSE;

				if (m_autoNameWindowFlag)
				{
					nameWindowFlag = CheckHaveName();
				}
//////				m_game->PrintMessageWindow(b,nameWindowFlag);
			}
		}
		else	//LPRINT APPEND
		{
			//if (m_windowOffFlag == FALSE)
			if (CheckWindowOn())
			{
				//full専用メッセージウィンドウ??
			}
		}
	}


	for (int layer = 0;layer<16;layer++)
	{
		int meskosuu = m_cutinMessageKosuu[layer];
		if (meskosuu <= 0) continue;

		int putX0 = m_cutinZahyo[layer].x;
		int putY0 = m_cutinZahyo[layer].y;

		CAllGeo::TransBoxFill(putX0,putY0,500,meskosuu*30,32,64,96,70);

		for (int j=0;j<meskosuu;j++)
		{
			int printed = m_cutinMessagePrinted[layer][j];
			int maxLen = m_cutinMessageLength[layer][j];

			int putX = putX0 + j*0;
			int putY = putY0 + j*30;//dummy

			if (m_printMode == CODE_SYSTEMCOMMAND_LPRINT)
			{
//				putX = m_LPrintX + (j - st) * m_LNextX;
//				putY = m_LPrintY + (j - st) * m_LNextY;
			}

			int colR = m_colorR;
			int colG = m_colorG;
			int colB = m_colorB;

			int sukima = m_spaceX;

			//色へんか?
//			if (j == st)
//			{
//				//@@@@@@@@
//			}
			//かげへんか?
			int kageColor = m_shadeColor;

			int kosuu = m_messagePrintMojisuu;

			if ((maxLen != -1) && (printed >= maxLen))	//old line
			{
				if (b)
				{
					m_message->PrintMessage(putX,putY,m_cutinMessage[layer][j],m_fontSize,colR,colG,colB,sukima,m_nextY,kageColor);
				}
				m_messagePrintedGyo = j;
			}
			else	//new or now line
			{
				if (b)
				{
					kosuu += printed;
					printed = 0;
				}

				if (kosuu>0)
				{
					int amari = m_message->PrintMessageParts(printed,kosuu,putX,putY,m_cutinMessage[layer][j],m_fontSize,colR,colG,colB,sukima,m_nextY,kageColor);

					if (amari == 0)
					{
						m_cutinMessagePrinted[layer][j] = printed + kosuu;
						m_cutinMessageLength[layer][j] = printed + kosuu;
						kosuu = 0;
					}
					else if (amari>0)
					{
						m_cutinMessagePrinted[layer][j] = printed + kosuu;
						m_cutinMessageLength[layer][j] = printed + kosuu + amari;
						kosuu = 0;
					}
					else
					{
						m_cutinMessagePrinted[layer][j] = printed + kosuu + amari;
						m_cutinMessageLength[layer][j] = printed + kosuu + amari;
						kosuu = -amari;
					}

					m_messagePrintedGyo = j;

					if (j == (meskosuu-1))
					{
						if (m_cutinMessagePrinted[layer][j] >= m_cutinMessageLength[layer][j])
						{
//							MessageIsRead();
							m_messagePrintingFlag = FALSE;
							break;
						}
					}
				}
			}
		}
	}

	if ((m_messagePrintingFlag == FALSE) && CheckWindowOn())
	{
		if (m_printMode != CODE_SYSTEMCOMMAND_DRAW)
		{
			if (CheckAutoMessage() == FALSE)
			{
			//print lprintでわける
				if (m_printMode == CODE_SYSTEMCOMMAND_PRINT)
				{
					//カーソル計算、せっと
			//		m_game->CursorAnime();
//@@					m_game->SetMyCursor();
				}
				else
				{
			//		m_game->CursorAnime();

					int fcpat = 2;	//3も含む

			//		int x = m_LPrintX + m_cutinMessageLength[m_messageKosuu-1] * (m_fontSize + m_spaceX);
			//		int y = m_LPrintY + (m_messageKosuu-1) * m_LNextY;

//@@				m_game->SetMyCursor(x,y,fcpat);	//座標指定する



	///				CMessageCursor::SetPrint(600,20+30*m_messageKosuu);	//???
				}
			}
		}
	}


	return -1;
}

*/

int CCommonPrintMessage::PrintDrawMode(void)
{
	BOOL b = CAreaControl::CheckAllPrintMode();
///	m_game->PrintEffect();

	if (m_game->CheckOpeningMode() == FALSE)
	{
		if (m_game->CheckDemoMode() == FALSE)
		{
			BOOL fromDraw = FALSE;
			if (m_drawWindowWithMessageFlag)
			{
//				if (CheckWindowOn())
				if (m_game->CheckMessageWindowFlag())
				{
					fromDraw = TRUE;
				}
			}



			int ntype = m_game->GetNextMessageType();

			if ((ntype == 0) || (ntype == 3))
			{
				if (fromDraw)
				{
					PrintMessageMode(TRUE);
				}
				else
				{
					m_game->PrintMessageWindowByCheck(b);
				}
			}
			else if ((ntype == 1) || (ntype == 2))
			{
				if (m_lprintBGMode > 0)
				{
					if (CheckWindowOn())
					{
						PrintFullWindow();
					}
				}
			}

			//message!


		}
	}

	return -1;
}


int CCommonPrintMessage::PrintOverrapMode(void)
{
	CAreaControl::SetNextAllPrint();
	m_game->PrintOverrap(m_overrapCount);
	return -1;
}



void CCommonPrintMessage::WindowOn(BOOL flag)
{
	BOOL mae = m_windowOffFlag;
	m_windowOffFlag = !flag;
	if (mae != m_windowOffFlag)
	{
		CAreaControl::SetNextAllPrint();
	}
}

/*
void CCommonPrintMessage::CommandOn(BOOL flag)
{
	m_commandOffFlag = !flag;
}
*/

void CCommonPrintMessage::SetNextMessageEffect(int md)
{
	m_messageEffectYoyaku = md;
}

void CCommonPrintMessage::SetNextMessageEffectTime(int md)
{
	m_messageEffectTimeYoyaku = md;
}

void CCommonPrintMessage::SetMessageMode(int cmd, int nm, LPSTR mes,int cutin)
{
	m_autoMessageCount = 0;

	m_messageEffect = 0;
	if (m_messageEffectYoyaku > 0)
	{
		m_messageEffect = m_messageEffectYoyaku;
#if defined _DEBUG
		char debugmes[256];
		sprintf_s(debugmes,256,"[messageEffect = %d]\x00d\x00a",m_messageEffect);
		OutputDebugString(debugmes);
#endif
	}
	m_messageEffectYoyaku = 0;

	m_messageEffectSpeed = 0;
	if (m_messageEffectTimeYoyaku > 0)
	{
		m_messageEffectSpeed = m_messageEffectTimeYoyaku;
		if (m_messageEffectSpeed > 5) m_messageEffectSpeed = 5;
	}
	m_messageEffectTimeYoyaku = 0;


	//長さ取得
	int frameRate = m_game->GetFrameTime();
	if (frameRate < 1) frameRate = 1;

	int autoSlider = m_game->GetSystemParam(NNNPARAM_MESSAGESPEED);
	int autoSlider2 = m_game->GetSystemParam(NNNPARAM_AUTOSPEEDSLIDER);

	if (m_messageEffectSpeed > 0)
	{
		autoSlider = m_messageEffectSpeed-1;
		autoSlider2 = m_messageEffectSpeed-1;
	}

	if (m_game->CheckMessageHaveVoice())
	{
		m_autoLastCount = m_game->GetVoiceLength();
		m_autoLastCount2 = m_autoLastCount;
//		m_autoLastCount += m_voiceLastWait;
		if (m_useAutoModeWait)
		{
			m_autoLastCount += m_voiceLastWaitTableAutoMode[autoSlider2];
		}
		else
		{
			m_autoLastCount += m_voiceLastWaitTable[autoSlider];
		}
		m_autoLastCount2 += m_autoMessageVoiceLastWait;
	}
	else
	{
//		m_autoLastCount = m_noVoiceLastWait;
		if (m_useAutoModeWait)
		{
			m_autoLastCount = m_noVoiceLastWaitTableAutoMode[autoSlider2];
		}
		else
		{
			m_autoLastCount = m_noVoiceLastWaitTable[autoSlider];
		}
		m_autoLastCount2 = 1;
	}
//	m_autoLastCount2 = m_autoLastCount;






	if (cmd != CODE_SYSTEMCOMMAND_APPEND) m_printMode = cmd;
	if (m_printMode == CODE_SYSTEMCOMMAND_DRAW) m_printMode = CODE_SYSTEMCOMMAND_PRINT;	//1行目にアペンドを使ったばあいにとばないように

	//test 2010-04-30
	if (m_printMode == CODE_SYSTEMCOMMAND_OVERRAP) m_printMode = CODE_SYSTEMCOMMAND_PRINT;	//1行目にアペンドを使ったばあいにとばないように

//	m_subMode = cmd;
	if (cmd == CODE_SYSTEMCOMMAND_PRINT)
	{
		WindowOn();
	}
	else
	{
		//WindowOff();	//??
	}

	 m_messageSerialNumber = nm;
	if ((nm & 0xffff) == 0xffff)
	{
		m_messageSerialNumber = -1;
	}

	m_nowMessageIsReadMessage = CheckMessageRead();




	m_messagePrintingFlag = TRUE;
	m_namePrintedFlag = FALSE;

	if (m_printMode == CODE_SYSTEMCOMMAND_PRINT)
	{
//		CommandOn();
//		m_windowOffFlag = FALSE;
		WindowOn();
	}
	else
	{
//		CommandOn();
//		m_windowOffFlag = FALSE;
		WindowOn();
	}

	if ((cmd == CODE_SYSTEMCOMMAND_PRINT) || (cmd == CODE_SYSTEMCOMMAND_LPRINT))
	{
//		m_printMode = m_subMode;
		m_messageKosuu = 0;
		m_messagePrintedGyo = 0;
		for (int i=0;i<MESSAGEKOSUU_MAX;i++)
		{
			m_messageLength[i] = -1;
			m_messagePrinted[i] = 0;
			m_cutinData[i*2] = 0;
			m_cutinData[i*2+1] = 0;

		}
	}

	//appendで先頭が人名だったら飛ばす
	if (cmd == CODE_SYSTEMCOMMAND_APPEND)
	{
		char check[256];
		int ln = (int)strlen(mes);
		check[0] = 0;
		int skps = 0;
		for (int i=0;i<ln;i++)
		{
			char c = *(mes+i);
			if ((c == 0) || (c == 0x0d))
			{
				check[i] = 0;
				if (c == 0) skps = i+1;
				if (c == 0x0d) skps = i+2;
				break;
			}
			check[i] = c;
		}
		check[ln]=0;
		if (m_nameColor->SearchName(check) != -1)
		{
			if (m_appendSkipName)
			{
				mes += skps;
			}
		}
	}



	//メッセージ分割

	int ln = (int)strlen(mes);

	int kosuu = 0;

	int gyosuu = 0;
	int firstAppend = 0;

	int specialAppendMode = 0;
	if ((cmd == CODE_SYSTEMCOMMAND_APPEND) && (m_printMode == CODE_SYSTEMCOMMAND_PRINT))
	{
		specialAppendMode = 1;
		WindowOn();
		m_game->SetMessageWindowFlag();

		//現状の表示末端を取得


		for (int i=0;i<m_messageKosuu;i++)
		{
			m_messagePrinted[i] = m_messageLength[i];
		}
/*
		for (int i=m_messageKosuu;i<MESSAGEKOSUU_MAX;i++)
		{
			m_messageLength[i] = -1;
			m_messagePrinted[i] = 0;
			m_cutinData[i*2] = 0;
			m_cutinData[i*2+1] = 0;

		}
*/

		if (m_messageKosuu > 0)
		{
			m_messageLength[m_messageKosuu-1] = -1;

		}

		if (m_messagePrintedGyo>0) m_messagePrintedGyo--;

	}

	int specialCR = 0;
	int tsunagu = 0;


	int codeByte = CMyFont::m_codeByte;


	int n = 0;
	while (n < ln)
	{
		//改行か0まで
		int ln1 = -1;
		char c;

		int n1 = n;

		while (n1<ln)
		{
			c = *(mes+n1);
			n1++;

			if (c == 0xd)
			{
				if (ln1 == -1) ln1 = 0;
				n1 += 1;	//skip 0xa
				c = *(mes+n1);
				break;
			}

			if (c == 0) break;

			if (ln1 == -1) ln1 = 0;
			ln1++;
		}

		//特殊改行ちぇっく
//		if (specialAppendMode)
//		{
			if (firstAppend == 0)
			{
				BOOL spcheck = FALSE;
				if (codeByte == 2)
				{
					if (ln1 > 3)
					{
						if ((*(mes+n)) == '#')
						{
							short* crPtr = (short*)(mes+n+1);

							if ((*crPtr) == (short)SPECIAL_CR_CODE)
							{
								spcheck = TRUE;
							}
						}
					}
				}
				else if (codeByte == 1)
				{
					if (ln1 > 2)
					{
						if ((*(mes+n)) == '#')
						{
							short* crPtr = (short*)(mes+n+1);

							if (*(mes+n+1) == SPECIAL_CR_CODE_1BYTE)
							{
								spcheck = TRUE;
							}
						}
					}
				}

				
//				if (ln1 > 3)
				if (spcheck)
				{
//					if ((*(mes+n)) == '#')
//					{
//						short* crPtr = (short*)(mes+n+1);
						//
						//
//						if ((*crPtr) == (short)SPECIAL_CR_CODE)
//						{
					BOOL spa = FALSE;

					if (specialAppendMode)
					{
						spa = TRUE;
					}
					else
					{
							//	OutputDebugString("[a]");
						if ((cmd == CODE_SYSTEMCOMMAND_APPEND) && (m_printMode == CODE_SYSTEMCOMMAND_LPRINT))
						{
							//	OutputDebugString("[b]");
							if (tsunagu == 0)
							{
							//	OutputDebugString("[c]");

								for (int i00=0;i00<m_messageKosuu;i00++)
								{
									m_messagePrinted[i00] = m_messageLength[i00];
								}

								if (m_messageKosuu > 0)
								{
									m_messageLength[m_messageKosuu-1] = -1;
								}

								if (m_messagePrintedGyo>0) m_messagePrintedGyo--;

								specialAppendMode = 1;
								spa = TRUE;
							}
						}
					}
					
					if (spa)
					{
						if (codeByte == 2)
						{
							ln1 -= 3;
							n += 3;
						}
						else if (codeByte == 1)
						{
							ln1 -= 2;
							n += 2;
						}

						tsunagu = 1;
					}
				}
			}
//		}

		if (ln1 != -1)
		{
			BOOL setok = TRUE;
			char cutinName[256];

			if (cutin != 0)
			{
				if (m_useCutinFlag)
				{
					if (m_cutinMode>0)
					{
						if (kosuu == 0)
						{
							if (m_cutinNamePrintFlag == 0)
							{
								memcpy(cutinName,mes+n,ln1);
								cutinName[ln1] = 0;
								cutinName[ln1+1] = 0;

								if (m_cutinNameData->CheckNameIsNotAll(cutin))
								{
									//compare
									if (strcmp(cutinName,m_cutinNameData->GetCharaName(cutin)) == 0)
									{
										setok = FALSE;
									}
								}
								else
								{
									setok = FALSE;
								}
							}
						}
					}
				}
			}

			if (specialAppendMode)
			{
				if (gyosuu == 0)
				{
					//name? cutinのあとしまつしょりを流用

					if (m_nameColor != NULL)
					{
						memcpy(cutinName,mes+n,ln1);
						cutinName[ln1] = 0;
						cutinName[ln1+1] = 0;

						int saNameNumber = m_nameColor->SearchName(cutinName);
						if (saNameNumber != -1)
						{
							setok = FALSE;
						}
					}
				}
			}


//			if (setok == FALSE)
//			{
//				memcpy(cutinName,mes+n,ln);
//				cutinName[ln] = 0;
//				cutinName[ln+1] = 0;
//			}

			if (setok)
			{

	//			if (m_messageKosuu>=MESSAGEPRINT_MAX) break;
				if ((m_messageKosuu>=MESSAGEKOSUU_MAX) && ((firstAppend > 0) || (specialAppendMode == 0)))
				{
					MessageScroll();
					if (m_messagePrintedGyo>0) m_messagePrintedGyo--;
					m_messageKosuu--;
				}

				if (m_messageKosuu>=MESSAGEKOSUU_MAX) break;	//用心

				if (ln1 > (MESSAGEBYTE_MAX-2)) ln1 = MESSAGEBYTE_MAX-2;

				if ((firstAppend > 0) || (specialAppendMode == 0) || (m_messageKosuu == 0) || specialCR || (tsunagu == 0))
				{
					if (ln1 > 0)
					{
						memcpy(&m_messageData[m_messageKosuu][0],mes+n,ln1);
					}
					m_messageData[m_messageKosuu][ln1] = 0;
					m_messageData[m_messageKosuu][ln1+1] = 0;
				}
				else//現在位置に追加
				{
					int apln = (int)strlen(m_messageData[m_messageKosuu-1]);
					if ((apln + ln1) > (MESSAGEBYTE_MAX-2))
					{
						ln1 = MESSAGEBYTE_MAX-2 - apln;
					}
					if (ln1 > 0)
					{
						memcpy(&(m_messageData[m_messageKosuu-1][apln]),mes+n,ln1);
						m_messageData[m_messageKosuu-1][apln+ln1] = 0;
						m_messageData[m_messageKosuu-1][apln+ln1+1] = 0;
					}

					m_messageLength[m_messageKosuu-1] = m_message->GetMessageRealLength(m_messageData[m_messageKosuu-1]);

				}

				if ((m_printMode == CODE_SYSTEMCOMMAND_PRINT) && (kosuu==0) && m_nameColorChangeFlag)
				{
					int nameColor = m_nameColor->GetColor(m_messageData[m_messageKosuu]);
					int r = (nameColor >> 16) & 0xff;
					int g = (nameColor >>  8) & 0xff;
					int b = (nameColor      ) & 0xff;

//					if ((m_cutinMode == 0) || (kosuu>0))
//					{
					if ((m_messageKosuu > 0) && specialAppendMode && (specialCR == 0) && (tsunagu == 1) )
					{
//						m_game->AddBackLogMessage(m_messageData[m_messageKosuu-1],r,g,b);
						char tmplog[1024];
						memcpy(tmplog,mes+n,ln1);
						tmplog[ln1] = 0;
						tmplog[ln1+1] = 0;
						m_game->AddBackLogMessage(tmplog,r,g,b);
					}
					else
					{
						m_game->AddBackLogMessage(m_messageData[m_messageKosuu],r,g,b);
					}

//					}
				}
				else
				{
					if ((firstAppend == 0) && specialAppendMode)
					{
					//	OutputDebugString("[f]");
						char tmplog[1024];
						memcpy(tmplog,mes+n,ln1);
						tmplog[ln1] = 0;
						tmplog[ln1+1] = 0;
						m_game->AddBackLogMessage(tmplog);
					}
					else
					{
//						OutputDebugString("[g]");

//					if ((m_cutinMode == 0) || (kosuu>0))
//					{
						m_game->AddBackLogMessage(&m_messageData[m_messageKosuu][0]);
//					}
					}
				}


				if ((specialAppendMode == 0) || (firstAppend) || specialCR || (tsunagu == 0))
				{
					m_messageKosuu++;
				}

				if (tsunagu)
				{
					specialCR = 1;
				}

				firstAppend = 1;

				kosuu++;
			}
			else
			{
				if ((m_printMode == CODE_SYSTEMCOMMAND_PRINT) && m_nameColorChangeFlag)
				{
					int nameColor = m_nameColor->GetColor(cutinName);
					int r = (nameColor >> 16) & 0xff;
					int g = (nameColor >>  8) & 0xff;
					int b = (nameColor      ) & 0xff;

					m_game->AddBackLogMessage(cutinName,r,g,b);
				}
				else
				{
					m_game->AddBackLogMessage(cutinName);
				}
				kosuu++;
			}
		}

		n = n1;

		if (c == 0) break;
	}


	if (m_cutinMode>0)
	{
		if (m_useCutinFlag)
		{
			if (kosuu > 0)
			{
				if (cutin != 0)
				{
					for (int k=0;k<kosuu;k++)
					{
						int p = m_messageKosuu-1-k;
						m_cutinData[p*2+0] = cutin;
						m_cutinData[p*2+1] = k+1;
					}
				}
			}
		}
	}


	//backlogについかするもの
	m_game->AddBacklogSeparator();











	if (m_printMode == CODE_SYSTEMCOMMAND_PRINT)
	{
		if (m_messageKosuu>m_windowMessageKosuuMax) m_messageKosuu = m_windowMessageKosuuMax;
	}
	else
	{
//		if (m_messageKosuu>MESSAGEPRINT_MAX) m_messageKosuu = MESSAGEPRINT_MAX;
		if (m_messageKosuu>m_fullMessageKosuuMax)
		{
			int loop = m_messageKosuu-m_fullMessageKosuuMax;
			for (int i=0;i<loop;i++)
			{
				MessageScroll();
				if (m_messagePrintedGyo>0)
				{
					m_messagePrintedGyo--;
				}
				m_messageKosuu--;
			}
		}
	}


/*
	if (m_cutinMode)
	{
		//copy to cutin message
		m_nowMessageLayer++;
		if (m_nowMessageLayer>=8) m_nowMessageLayer = 4;	//dummy

		//1行目をもとに人物確定
		//対象のレイヤー検索
		

		if (m_messageKosuu > 1)
		{
			//追加もありか

			m_cutinMessageKosuu[m_nowMessageLayer] = m_messageKosuu-1;
			for (int i=1;i<m_messageKosuu;i++)
			{
				int ln = strlen(m_messageData[i]);
				memcpy(m_cutinMessage[m_nowMessageLayer][i-1],m_messageData[i],ln+1);
				m_cutinMessageLength[m_nowMessageLayer][i-1] = -1;
				m_cutinMessagePrinted[m_nowMessageLayer][i-1] = 0;
			}
		}
	}
*/

}


void CCommonPrintMessage::SetDrawMode(int count)
{
	m_printMode = CODE_SYSTEMCOMMAND_DRAW;
	m_drawCount = count ;
}

void CCommonPrintMessage::SetOverrapMode(int overrapType,int overrapTime)
{
	m_printMode = CODE_SYSTEMCOMMAND_OVERRAP;
	m_overrapType = overrapType;
	m_overrapTime = overrapTime;
	m_overrapCount = 0;
}


void CCommonPrintMessage::Clear(void)
{
	m_messageKosuu = 0;
}

/*
int CCommonPrintMessage::GetJinbutsuColor(int pl, int rgbNum)
{
	if (rgbNum == 0) return m_jinbustu[pl].colR;
	if (rgbNum == 1) return m_jinbustu[pl].colG;
	if (rgbNum == 2) return m_jinbustu[pl].colB;

	return 255;
}
*/

/*
int CCommonPrintMessage::GetJinbutsuNumber(LPSTR name)
{
	if (*name == 0) return 0;

	for (int i=0;i<m_jinbutsuNameKosuu;i++)
	{
		if (strcmp(m_jinbustu[i].name,name)==0) return i;
	}

	return 0;	// not found
}
*/


int CCommonPrintMessage::GetMessageKosuu(void)
{
	return m_messageKosuu;
}

void CCommonPrintMessage::SetMessageKosuu(int n)
{
	m_messageKosuu = n;
}

void CCommonPrintMessage::InitByLoad(void)
{
	m_messagePrintedGyo = 0;
	for (int i=0;i<MESSAGEKOSUU_MAX;i++)
	{
		m_messageLength[i] = -1;
		m_messagePrinted[i] = 0;
	}
	m_messageSerialNumber = m_game->GetMessageSerial();

	m_nowMessageIsReadMessage = CheckMessageRead();

}


LPSTR CCommonPrintMessage::GetMessagePointer(int n)
{
	return &m_messageData[n][0];
}

void CCommonPrintMessage::SetMessageData(int n,LPSTR mes)
{
	int ln = (int)strlen(mes);
	if (ln>254) ln = 254;
	memcpy(&m_messageData[n][0],mes,ln);
	m_messageData[n][ln] = 0;
	m_messageData[n][ln+1] = 0;

//	m_game->AddBackLogMessage(mes);
}

//not used!???
void CCommonPrintMessage::SetMessageRead(void)
{
	//all read

	m_messagePrintedGyo = m_messageKosuu;
	m_messagePrintingFlag = FALSE;

	m_printMode = CODE_SYSTEMCOMMAND_PRINT;
//	m_subMode = CODE_SYSTEMCOMMAND_PRINT;

	//window on
	WindowOn();
//	m_windowOffFlag = FALSE;
//	m_commandOffFlag = FALSE;
}

void CCommonPrintMessage::MessageIsRead(void)
{
	if (m_messageSerialNumber == -1) return;

	int mesNum = m_messageSerialNumber & 0xffff;
	m_game->SetMessageRead(mesNum);
}


BOOL CCommonPrintMessage::CheckMessageRead(void)
{
	if (m_messageSerialNumber == -1) return TRUE;

	int mesNum = m_messageSerialNumber & 0xffff;
//	int sptNum = (m_messageSerialNumber>>16) & 0xffff;

	return m_game->CheckMessageRead(mesNum);
}

/*
void CCommonPrintMessage::SetCGMode(BOOL b)
{
	m_cgMode = b;
}
*/

void CCommonPrintMessage::SetSceneMode(BOOL b)
{
	m_sceneMode = b;
}

int CCommonPrintMessage::GetPrintModeForSave(void)
{
	return m_printMode;
}


void CCommonPrintMessage::SetPrintModeByLoad(int md)
{
	m_printMode = md;
}


/*
void CCommonPrintMessage::SetPrintModeByLoad(int md)
{
	m_printMode = md;
//	m_printMode = CODE_SYSTEMCOMMAND_PRINT;
//	m_subMode = CODE_SYSTEMCOMMAND_PRINT;

	m_messagePrintingFlag = FALSE;
	m_messagePrintMojisuu = 10000;
	m_windowOffFlag = FALSE;


	for (int i=0;i<m_messageKosuu;i++)
	{
		if ((i==0) && m_nameColorChangeFlag)
		{
			int nameColor = m_nameColor->GetColor(m_messageData[i]);
			int r = (nameColor >> 16) & 0xff;
			int g = (nameColor >>  8) & 0xff;
			int b = (nameColor      ) & 0xff;

			m_game->AddBackLogMessage(m_messageData[i],r,g,b);
		}
		else
		{
			m_game->AddBackLogMessage(&m_messageData[i][0]);
		}
	}
}
*/


/*
int CCommonPrintMessage::GetOnButton(int mouseX, int mouseY)
{
	int x,y;
	int sizeX,sizeY;
	int printX,printY;
	CPicture* pic;

	if (m_sceneMode == FALSE)
	{
		sizeX = m_optionSizeX;
		sizeY = m_optionSizeY;
		printX = m_optionPrintX;
		printY = m_optionPrintY;
		pic = m_optionPic;
	}
	else
	{
		sizeX = m_backSizeX;
		sizeY = m_backSizeY;
		printX = m_backPrintX;
		printY = m_backPrintY;
		pic = m_backPic;
	}

	x = mouseX - printX;
	y = mouseY - printY;

	if ((x>=0) && (x<sizeX) && (y>=0) && (y<sizeY))
	{
		if (pic == NULL) return -1;
		if (pic->CheckOnPic(x,y)) return 0;
	}

	return -1;
}
*/


void CCommonPrintMessage::ResetShakin(void)
{
	m_shakin = 0;
}

int CCommonPrintMessage::GetShakin(void)
{
	return m_shakin;
}



BOOL CCommonPrintMessage::CheckAuto(void)
{
	if (m_game->GetSystemParam(NNNPARAM_AUTOMODE))
	{
		if (m_game->CheckMessageHaveVoice())
		{
			m_autoLastCount -= m_game->GetNowFrameCount();
			if (m_autoLastCount>0) return FALSE;
			return TRUE;
		}
		else
		{
			if (CheckMessagePrintEnd())
			{
				m_autoLastCount -= m_game->GetNowFrameCount();
				if (m_autoLastCount>0) return FALSE;
				return TRUE;
			}
		}
	}

	m_autoLastCount = 1;
	return FALSE;
}

void CCommonPrintMessage::FinalExitRoutine(void)
{
//	m_game->EraseMouse();
//	m_exitScreen->GetScreen();
}

int CCommonPrintMessage::EndMode(void)
{
	return -1;
}

void CCommonPrintMessage::OnEndFilm(void)
{
	if (m_createExitScreenFlag)
	{
		m_game->EraseMouse();
		CreateExitScreen();
	}
}


void CCommonPrintMessage::MessageScroll(void)
{
	for (int i=0;i<MESSAGEKOSUU_MAX-1;i++)
	{
		m_messagePrinted[i] = m_messagePrinted[i+1];
		m_messageLength[i] = m_messageLength[i+1];
		m_cutinData[i*2+0] = m_cutinData[(i+1)*2+0];
		m_cutinData[i*2+1] = m_cutinData[(i+1)*2+1];
		memcpy(m_messageData[i],m_messageData[i+1],MESSAGEBYTE_MAX);
	}

	m_messagePrinted[MESSAGEKOSUU_MAX-1] = 0;
	m_messageLength[MESSAGEKOSUU_MAX-1] = 0;
	m_messageData[MESSAGEKOSUU_MAX-1][0] = 0;
	m_cutinData[(MESSAGEKOSUU_MAX-1)*2+0] = 0;
	m_cutinData[(MESSAGEKOSUU_MAX-1)*2+1] = 0;
}

BOOL CCommonPrintMessage::CheckFullMessageMode(void)
{
//	if ((m_subMode == CODE_SYSTEMCOMMAND_LPRINT) || (CODE_SYSTEMCOMMAND_APPEND)) return TRUE;
	if ((m_printMode == CODE_SYSTEMCOMMAND_LPRINT) || (m_printMode == CODE_SYSTEMCOMMAND_APPEND)) return TRUE;

	return FALSE;
}


BOOL CCommonPrintMessage::CheckHaveName(void)
{
	if (m_nameColor == NULL) return FALSE;
	int n = m_nameColor->SearchName(m_messageData[0]);
	if (n != -1) return TRUE;

	m_nameNumber = n / 4;

//	int n = m_charaNameList->GetNameKosuu();
//	for (int i=1;i<n/2;i++)
//	{
//		LPSTR name = m_charaNameList->GetName(i*2+1);
//		if (strcmp(name,m_messageData[0]) == 0) return TRUE;
//	}

	return FALSE;
}


BOOL CCommonPrintMessage::CheckWindowOff(void)
{
	return !CheckWindowOn();
}

BOOL CCommonPrintMessage::CheckWindowOn(void)
{
	if (m_windowOffFlag) return FALSE;
	return TRUE;
}


BOOL CCommonPrintMessage::CheckPrintMode(void)
{
	if (m_printMode == CODE_SYSTEMCOMMAND_DRAW) return FALSE;
	if (m_printMode == CODE_SYSTEMCOMMAND_OVERRAP) return FALSE;
	
	return TRUE;
}
/*
BOOL CCommonPrintMessage::CheckCommandOn(void)
{
	if (m_commandOffFlag) return FALSE;
	return TRUE;
}

BOOL CCommonPrintMessage::CheckCommandOff(void)
{
	return !CheckCommandOn();
}
*/

BOOL CCommonPrintMessage::CheckWindowOffOperation(void)
{
	if (m_windowOffMouseButton != -1)
	{
		if (m_mouseStatus->CheckClick(m_windowOffMouseButton)) return TRUE;
	}

	if (m_game->CheckClickKey(WINDOWOFF_KEY)) return TRUE;

	return FALSE;
}

BOOL CCommonPrintMessage::CheckAutoMessage(void)
{
	int spd = m_game->GetAutoMessage();
	if (spd > 0) return TRUE;
	return FALSE;
}

int CCommonPrintMessage::GetAutoMessageSpeed(void)
{
	int spd = m_game->GetAutoMessage();
	if (spd>0) spd--;
	return spd;
}

BOOL CCommonPrintMessage::CheckWindowOnOffEnable(void)
{
//	if (m_game->CheckDemoMode()) return FALSE;

	if (m_game->GetDontPlayMode()) return FALSE;	//dummy

//	if (CheckCannotClick()) return FALSE;
	if (CheckAutoMessage()) return FALSE;
	if (CheckOption() == FALSE) return FALSE;
//	if (m_game->GetAutoMessage() > 0) return FALSE;
//	if (m_game->GetCannotClick()) return FALSE;
//	if (m_game->GetOptionOff()) return FALSE;

	return TRUE;
}


BOOL CCommonPrintMessage::CheckCannotSkip(void)
{
	if (CheckAutoMessage()) return TRUE;
	return m_game->GetCannotSkip();
}

BOOL CCommonPrintMessage::CheckCannotClick(void)
{
	if (CheckAutoMessage()) return TRUE;
	return m_game->GetCannotClick();
}

BOOL CCommonPrintMessage::CheckOkuri(void)
{
	if (CheckClick()) return TRUE;
	if (m_game->CheckClickKey(MESSAGEOKURI_KEY)) return TRUE;
	
	if (m_checkWheelOkuri)
	{
		if ((m_mouseStatus->GetWheel()) < 0)
		{
			return TRUE;
		}
	}

	return FALSE;
}


BOOL CCommonPrintMessage::CheckSkipOrClickDrawAndOverrrap(int rt)
{
	if (rt != NNNBUTTON_NOTHING) return FALSE;
	
	if (m_skipFlag) return TRUE;
	if (CheckCannotClick()) return FALSE;

	if (CheckOkuri()) return TRUE;

	return FALSE;
}

BOOL CCommonPrintMessage::CheckOption(void)
{
	if (CheckAutoMessage()) return FALSE;
	if (m_game->GetOptionOff()) return FALSE;

	return TRUE;
}

void CCommonPrintMessage::CheckUserSkipOff(void)
{
	BOOL rightCheck = FALSE;
	if (m_rightSkipOffIsClick)
	{
		if (m_mouseStatus->CheckClick(1))
		{
			rightCheck = TRUE;
		}
	}
	else
	{
		if (m_mouseStatus->GetTrig(1))
		{
			rightCheck = TRUE;
		}
	}

	BOOL leftClick = FALSE;
	if (CheckClick())
	{
		POINT pt = m_mouseStatus->GetZahyo();

		if (m_game->CheckOnFreeAutoSkipButton(pt) == FALSE)
		{
			leftClick = TRUE;
		}
	}


//	if ((CheckClick()) || (m_mouseStatus->GetTrig(1)) || (m_mouseStatus->GetWheel()>0))
	if (leftClick || rightCheck || (m_mouseStatus->GetWheel()>0))
	{
		m_game->SetSystemParam(NNNPARAM_AUTOMODE,0);
		if (m_skipFlag)
		{
			m_game->SetMessageSkipFlag(FALSE);
			m_skipFlag = FALSE;
		}
	}
}


int CCommonPrintMessage::CalcuOptionButton(void)
{
	int rt = NNNBUTTON_NOTHING;


	if (CheckOption() && CheckPrintMode())
	{
		if (CheckPrintMode())
		{
			if (CheckMessagePrintEnd())
			{
				if (CheckWindowOff() == FALSE)
				{
					if (CheckSceneMode() == FALSE)
					{
						rt = m_game->CalcuOptionButton();
					}
					else
					{
						if (0)
						{
							rt = m_game->CalcuSceneButton();
						}
						else
						{
							rt = m_game->CalcuOptionButton();
						}
					}
				}
			}
		}
	}

	return rt;
}

BOOL CCommonPrintMessage::CheckMessagePrintEnd(void)
{
	if (m_messagePrintingFlag) return FALSE;
	return TRUE;
}

BOOL CCommonPrintMessage::CheckSceneMode(void)
{
	return m_game->CheckSceneMode();
}

BOOL CCommonPrintMessage::CheckBackLogOk(void)
{
//	if (CheckCannotClick()) return FALSE;
	if (CheckAutoMessage()) return FALSE;
	if (CheckOption() == FALSE) return FALSE;

	if (CheckMessagePrintEnd() == FALSE) return FALSE;

	return TRUE;
}


void CCommonPrintMessage::SetCutinMode(int md)
{
	if (m_useCutinFlag == 0) return;

	m_cutinMode = md;
#if defined _DEBUG
	if (md != 0)
	{
		OutputDebugString("\nカットインモード開始");
	}
	else
	{
		OutputDebugString("\nカットインモード終了");
	}
#endif
}

/*
void CCommonPrintMessage::SetCutinFile(int layer,LPSTR filename)
{
	if (m_useCutinFlag == 0) return;

#if defined _DEBUG
	char mes[256];
	wsprintf(mes,"\nカットインファイル %d=%s",layer,filename);
	OutputDebugString(mes);
#endif
}
*/


void CCommonPrintMessage::SetMessageExpStatus(int st)
{
	if (st == 1)
	{
		m_cutinWaitClick = TRUE;
	}
}

void CCommonPrintMessage::OnClearAllEffect(void)
{
	for (int i=0;i<16;i++)
	{
//		m_cutinMessageKosuu[i] = 0;
	}
	m_cutinWaitClick = FALSE;
}

void CCommonPrintMessage::OnClearEffect(int layer)
{
//	m_cutinMessageKosuu[layer] = 0;
}


void CCommonPrintMessage::SetCutinByLoad(int* ptr)
{
	for (int i=0;i<64*2;i++)
	{
		m_cutinData[i] = *(ptr+i);
	}
}

void CCommonPrintMessage::GetCutinForSave(int* ptr)
{
	for (int i=0;i<64*2;i++)
	{
		*(ptr+i) = m_cutinData[i];
	}
}


int CCommonPrintMessage::GetMessageSpeedTable(int n, bool autoFlag)
{
	if (autoFlag)
	{
		return m_autoMessageSpeedTable[n];
	}

	return m_messageSpeedTable[n];
}

/*_*/

