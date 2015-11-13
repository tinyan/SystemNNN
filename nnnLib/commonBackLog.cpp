//
// commonBackLog.cpp
//


#include <windows.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGraphics.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\namelist.h"
#include "..\nnnUtilLib\myFont.h"

#include "..\nnnUtilLib\myMessage.h"


#include "commonMode.h"
#include "commonSystemParamName.h"

#include "..\nnnUtilLib\inputStatus.h"

#include "gameCallBack.h"

#include "commonGeneral.h"
#include "commonBackLog.h"



#include "commonKeyList.h"





char CCommonBackLog::m_defaultTitleMessage[] = "#橙回想・・・・";
char CCommonBackLog::m_defualtFirstMessage[] = "#赤#猫#白　過去、それは単なる通過点の集まり・・・　#赤#猫";
char CCommonBackLog::m_defaultBarMessage[] = "―――――――――――――――――――――――";

char CCommonBackLog::m_defaultUpArrow[] = "#水▲";
char CCommonBackLog::m_defaultDownArrow[] = "#水▼";
char CCommonBackLog::m_defaultVoice[] = "♪";


char CCommonBackLog::m_defaultTitleMessage1byte[] = "#RRecollection...";
char CCommonBackLog::m_defualtFirstMessage1byte[] = "#R#c#W start #R#c";
char CCommonBackLog::m_defaultBarMessage1byte[] = "―――――――――――――――――――――――";

char CCommonBackLog::m_defaultUpArrow1byte[] = "#C^^";
char CCommonBackLog::m_defaultDownArrow1byte[] = "#Cvv";
char CCommonBackLog::m_defaultVoice1byte[] = "SD";



char CCommonBackLog::m_defaultBackFilename[] = "bg_backlog";
char CCommonBackLog::m_defaultTitlePicFileName[] = "ta_backlog_title";

char CCommonBackLog::m_defaultUpdownArrowFileName[]="ta_backlog_updown";
char CCommonBackLog::m_defaultUpArrowFileName[]="ta_backlog_up";
char CCommonBackLog::m_defaultDownArrowFileName[]="ta_backlog_down";


char CCommonBackLog::m_separatorData[][16] = 
{
	"　","―",""
};

char CCommonBackLog::m_separatorData_1byte[][16] = 
{
	" ","-",""
};

CCommonBackLog::CCommonBackLog(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(BACKLOG_MODE);
//	m_classNumber = BACKLOG_MODE;
	LoadSetupFile("BackLog",32);

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int codeByte = CMyFont::m_codeByte;

	m_backlogBGMode = 0;
	GetInitGameParam(&m_backlogBGMode,"bgMode");	//0:fill 1:pic 2:(screen) 3:(script)

	GetBackExecSetup();
	if (m_backScriptFlag) m_backlogBGMode = 3;


	m_backColorR = 0;
	m_backColorG = 0;
	m_backColorB = 0;

	GetInitGameParam(&m_backColorR,"backColorR");
	GetInitGameParam(&m_backColorG,"backColorG");
	GetInitGameParam(&m_backColorB,"backColorB");

	m_returnSoundNumber = -1;
	GetInitGameParam(&m_returnSoundNumber,"returnSoundNumber");


	if (m_backlogBGMode == 1)
	{
		m_backFilename = m_defaultBackFilename;
		GetInitGameString(&m_backFilename,"backlogBGFileName");
	}


	if (m_backlogBGMode == 2)
	{
		m_backDeltaR = 0;
		GetInitGameParam(&m_backDeltaR,"backDeltaR");
		m_backDeltaG = m_backDeltaR;
		GetInitGameParam(&m_backDeltaG,"backDeltaG");
		m_backDeltaB = m_backDeltaG;
		GetInitGameParam(&m_backDeltaB,"backDeltaB");

		m_backMultiR = 100;
		GetInitGameParam(&m_backMultiR,"backMultiR");
		m_backMultiG = m_backMultiR;
		GetInitGameParam(&m_backMultiG,"backMultiG");
		m_backMultiB = m_backMultiG;
		GetInitGameParam(&m_backMultiB,"backMultiB");

		m_backScreenEffectNega = 0;
		GetInitGameParam(&m_backScreenEffectNega,"backScreenEffectNega");
		m_backScreenEffectGrey = 0;
		GetInitGameParam(&m_backScreenEffectGrey,"backScreenEffectGrey");

	}

	m_fontSize = 24;
	GetInitGameParam(&m_fontSize,"fontSize");


	m_sukima = 1;
	GetInitGameParam(&m_sukima,"space");

	m_printGyosuuMax = 12 + 3;


	m_printX = 32 + 78;
	m_printY = 32;

	m_nextX = 0;
	m_nextY = m_fontSize;
	m_voiceFlag = 1;

	m_updownArrowPic = NULL;
	m_upArrowPic = NULL;
	m_downArrowPic = NULL;

	m_voicePic = NULL;

	GetInitGameParam(&m_printGyosuuMax,"printLines");
	GetInitGameParam(&m_printX,"printX");
	GetInitGameParam(&m_printY,"printY");
	GetInitGameParam(&m_nextX,"nextX");
	GetInitGameParam(&m_nextY,"nextY");
	GetInitGameParam(&m_voiceFlag,"voiceFlag");

	m_upArrowPrintX = screenSizeX / 2 - m_fontSize / 2;
	m_upArrowPrintY = m_printY + m_nextY * 2;

	m_downArrowPrintX = screenSizeX / 2 - m_fontSize / 2;
	m_downArrowPrintY = m_printY + m_nextY * (m_printGyosuuMax+3);

	m_updownArrowSizeX = m_fontSize;
	m_updownArrowSizeY = m_fontSize;

	GetInitGameParam(&m_upArrowPrintX,"upArrowPrintX");
	GetInitGameParam(&m_upArrowPrintY,"upArrowPrintY");
	GetInitGameParam(&m_downArrowPrintX,"downArrowPrintX");
	GetInitGameParam(&m_downArrowPrintY,"downArrowPrintY");

	GetInitGameParam(&m_updownArrowSizeX,"updownArrowSizeX");
	GetInitGameParam(&m_updownArrowSizeY,"updownArrowSizeY");

	m_titleMessagePrintX = screenSizeX/2 - m_fontSize*3;
	m_titleMessagePrintY = m_printY;
	GetInitGameParam(&m_titleMessagePrintX,"titlePrintX");
	GetInitGameParam(&m_titleMessagePrintY,"titlePrintY");

	m_titlePrintFlag = 1;
	GetInitGameParam(&m_titlePrintFlag,"titlePrintFlag");

	m_titlePicPrintFlag = 0;
	GetInitGameParam(&m_titlePicPrintFlag,"titlePicPrintFlag");
	if (m_titlePicPrintFlag)
	{
		m_titlePicFileName = m_defaultTitlePicFileName;
		GetInitGameString(&m_titlePicFileName,"titlePicFileName");

		m_titlePicPrintX = 0;
		m_titlePicPrintY = 0;

		GetInitGameParam(&m_titlePicPrintX,"titlePicPrintX");
		GetInitGameParam(&m_titlePicPrintY,"titlePicPrintY");

		m_titlePicUpperFlag = 0;
		GetInitGameParam(&m_titlePicUpperFlag,"titlePicUpperFlag");
	}




	m_updownArrowPicFlag = 0;
	m_voicePicFlag = 0;
	m_updownArrowAnimeFlag = 0;

	m_updownArrowAnimePattern = 1;
	m_updownArrowAnimeSpeed = 1;
	m_updownArrowAnimeType = 1;

	GetInitGameParam(&m_updownArrowPicFlag,"updownArrowPicFlag");
	if (m_updownArrowPicFlag)
	{
		GetInitGameParam(&m_updownArrowAnimeFlag,"updownArrowAnimeFlag");

		LPSTR arrowFileName = m_defaultUpdownArrowFileName;

		GetInitGameString(&arrowFileName,"filenameUpdownArrow");

		if (m_updownArrowAnimeFlag == 0)
		{
			m_updownArrowPic = new CPicture();
			char filename[256];
			wsprintf(filename,"sys\\%s",arrowFileName);
			m_updownArrowPic->LoadDWQ(filename);
		}
		else
		{
			char filename[256];

			m_upArrowPic = new CPicture();
			LPSTR upArrowFileName = m_defaultUpArrowFileName;
			GetInitGameString(&upArrowFileName,"upArrowFileName");
			wsprintf(filename,"sys\\%s",upArrowFileName);
			m_upArrowPic->LoadDWQ(filename);

			m_downArrowPic = new CPicture();
			LPSTR downArrowFileName = m_defaultDownArrowFileName;

			GetInitGameString(&downArrowFileName,"downArrowFileName");
			wsprintf(filename,"sys\\%s",downArrowFileName);
			m_downArrowPic->LoadDWQ(filename);

			m_updownArrowAnimePattern = 2;
			m_updownArrowAnimeSpeed = 10;
			m_updownArrowAnimeType = 5;

			GetInitGameParam(&m_updownArrowAnimePattern,"updownArrowAnimePattern");
			GetInitGameParam(&m_updownArrowAnimeType,"updownArrowAnimeType");
			GetInitGameParam(&m_updownArrowAnimeSpeed,"updownArrowANimeSpeed");
		}
	}

	GetInitGameParam(&m_voicePicFlag,"voicePicFlag");
	
	m_voicePicAnimePattern = 1;
	m_voicePicAnimeSpeed = 1;
	m_voicePicAnimeType = 1;


	if (m_voicePicFlag)
	{
		LPSTR voiceFileName = NULL;
		GetInitGameString(&voiceFileName,"filenameVoice");

		m_voicePic = new CPicture();
		char filename[256];
		wsprintf(filename,"sys\\%s",voiceFileName);
		m_voicePic->LoadDWQ(filename);


		m_voicePicAnimeFlag = 0;
		GetInitGameParam(&m_voicePicAnimeFlag,"voicePicAnimeFlag");

		if (m_voicePicAnimeFlag)
		{
			m_voicePicAnimePattern = 2;
			m_voicePicAnimeSpeed = 10;
			m_voicePicAnimeType = 5;

			GetInitGameParam(&m_voicePicAnimePattern,"voicePicAnimePattern");
			GetInitGameParam(&m_voicePicAnimeSpeed,"voicePicAnimeSpeed");
			GetInitGameParam(&m_voicePicAnimeType,"voicePicAnimeType");
		}
	}

	LPSTR messageReplace = NULL;
	GetInitGameString(&messageReplace,"messageReplaceChara");

	if (codeByte == 2)
	{
		m_titleMessage = m_defaultTitleMessage;
	}
	else
	{
		m_titleMessage = m_defaultTitleMessage1byte;
	}
	GetInitGameString(&m_titleMessage,"titleMessage");

	if (messageReplace != NULL)
	{
		ReplaceMessage(m_titleMessage,messageReplace);
	}

	if (codeByte == 2)
	{
		m_barMessage = m_defaultBarMessage;
	}
	else
	{
		m_barMessage = m_defaultBarMessage1byte;
	}
	GetInitGameString(&m_barMessage,"barMessage");

	if (messageReplace != NULL)
	{
		ReplaceMessage(m_barMessage,messageReplace);
	}


	LPSTR firstMessage = m_defualtFirstMessage;
	if (codeByte != 2)
	{
		firstMessage = m_defualtFirstMessage1byte;
	}
	int firstMessageKosuu = 0;
	GetInitGameParam(&firstMessageKosuu,"firstMessageNumber");
	if (firstMessageKosuu == 0)
	{
		wsprintf(m_firstMessage,firstMessage);
	}
	else
	{
		m_firstMessage[0] = 0;
		for (int i=0;i<firstMessageKosuu;i++)
		{
			char name[256];
			wsprintf(name,"firstMessage%d",i+1);
			GetInitGameString(&firstMessage,name);
			lstrcat(m_firstMessage,firstMessage);
		}
	}


	if (messageReplace != NULL)
	{
		ReplaceMessage(m_firstMessage,messageReplace);
	}


	if (codeByte == 2)
	{
		m_upArrowMessage = m_defaultUpArrow;
		m_downArrowMessage = m_defaultDownArrow;
		m_voiceMessage = m_defaultVoice;
	}
	else
	{
		m_upArrowMessage = m_defaultUpArrow1byte;
		m_downArrowMessage = m_defaultDownArrow1byte;
		m_voiceMessage = m_defaultVoice1byte;
	}

	GetInitGameString(&m_upArrowMessage,"upArrowMessage");
	GetInitGameString(&m_downArrowMessage,"downArrowMessage");
	GetInitGameString(&m_voiceMessage,"voiceMessage");


	m_voicePrintX = -m_fontSize;
	m_voicePrintY = 0;
	m_voiceSizeX = m_fontSize;
	m_voiceSizeY = m_fontSize;

	GetInitGameParam(&m_voicePrintX,"voicePrintX");
	GetInitGameParam(&m_voicePrintY,"voicePrintY");
	GetInitGameParam(&m_voiceSizeX,"voiceSizeX");
	GetInitGameParam(&m_voiceSizeY,"voiceSizeY");

	m_logColor = new int[BACKLOG_KOSUU];
	m_logMessage = new char[BACKLOG_KOSUU * BACKLOG_LENGTH];
	m_voiceFile = new char[BACKLOG_KOSUU * VOICEFILE_LENGTH];

	m_message = new CMyMessage(m_game->GetMyFont());


	m_addSeparator = 0;
	GetInitGameParam(&m_addSeparator,"addSeparator");
	
	m_separatorMessage = NULL;
	m_separatorColorR = 255;
	m_separatorColorG = 255;
	m_separatorColorB = 255;

	if (m_addSeparator)
	{
		int separatorMax = 256;
		int n = 0;


		if (codeByte == 2)
		{
			while(n<256)
			{
				if (m_separatorData[n][0] == 0)
				{
					separatorMax = n;
					break;
				}
				n++;
			}
		}
		else
		{
			while(n<256)
			{
				if (m_separatorData_1byte[n][0] == 0)
				{
					separatorMax = n;
					break;
				}
				n++;
			}
		}


		int separaterLength = 32;
		GetInitGameParam(&separaterLength,"separatorLength");

		GetInitGameParam(&m_separatorColorR,"separatorColorR");
		GetInitGameParam(&m_separatorColorG,"separatorColorG");
		GetInitGameParam(&m_separatorColorB,"separatorColorB");

		m_separatorMessage = new char[256*m_addSeparator];
		for (int i=0;i<m_addSeparator;i++)
		{
			int sepType = 0;//
			char name[256];
			int sepLength = 32;

			wsprintf(name,"separatorType%d",i+1);
			GetInitGameParam(&sepType,name);

			if (sepType >= 0)
			{
				if (sepType>=separatorMax) sepType = separatorMax-1;//max

				int ln = 1;
				if (sepType>0) ln = separaterLength;

				for (int k=0;k<ln;k++)
				{
					if (codeByte == 2)
					{
						memcpy(m_separatorMessage+i*256+k*codeByte,m_separatorData[sepType],codeByte);
					}
					else
					{
						memcpy(m_separatorMessage+i*256+k*codeByte,m_separatorData_1byte[sepType],codeByte);
					}
				}
				m_separatorMessage[i*256+ln*codeByte] = 0;
			}
			else//custom
			{
				//dummy
				if (codeByte == 2)
				{
					memcpy(m_separatorMessage+i*256,"＊",3);
				}
				else
				{
					memcpy(m_separatorMessage+i*256,"*",2);
				}
			}
		}
		
	}



	m_startWait = 1;

	GetFadeInOutSetup();

	Clear();
}


CCommonBackLog::~CCommonBackLog()
{
	End();
}


void CCommonBackLog::End(void)
{
	ENDDELETECLASS(m_voicePic);
	ENDDELETECLASS(m_downArrowPic);
	ENDDELETECLASS(m_upArrowPic);
	ENDDELETECLASS(m_updownArrowPic);

	DELETEARRAY(m_logColor);
	DELETEARRAY(m_voiceFile);
	DELETEARRAY(m_logMessage);
	ENDDELETECLASS(m_message);

	DELETEARRAY(m_separatorMessage);
}



int CCommonBackLog::Init(void)
{
//MessageBox(NULL,"Init","backlog",MB_OK);
	m_game->StopScriptSoundAndVoice();

	int back = m_messageKosuu;
	if (back>m_printGyosuuMax) back = m_printGyosuuMax;

	m_voicePicAnimeCount = 0;
	m_updownArrowAnimeCount = 0;

	if (back == 0)
	{
		m_printPointer = 0;	//dummy
		return -1;
	}

	m_printPointer = m_nowPointer - back;
	m_printPointer += BACKLOG_KOSUU * 2;
	m_printPointer %= BACKLOG_KOSUU;

	m_startWait = 2;

	if (m_backlogBGMode == 1)
	{
		char filename[256];
		wsprintf(filename,"sys\\%s",m_backFilename);
		m_commonBG->LoadDWQ(filename);
	}
	else if (m_backlogBGMode == 2)
	{
		int sizeX = CMyGraphics::GetScreenSizeX();
		int sizeY = CMyGraphics::GetScreenSizeY();

		m_game->Erase();

		CAreaControl::SetNextAllPrint();
		m_game->PrintEffect(FALSE);
		m_game->PrintEffect(TRUE);


		//nega
		if (m_backScreenEffectNega)
		{
			CAllGraphics::Nega();
		}

		//grey
		if (m_backScreenEffectGrey)
		{
			CAllGraphics::Grey();
		}

		//multi
		CAllGraphics::Multi(m_backMultiR,m_backMultiG,m_backMultiB);

		//add
		CAllGraphics::AddSub(m_backDeltaR,m_backDeltaG,m_backDeltaB);

		m_commonBG->ReSize(sizeX,sizeY);
		m_commonBG->GetScreen();
	}



	if (m_titlePicPrintFlag)
	{
		char filename[256];
		wsprintf(filename,"sys\\%s",m_titlePicFileName);
		m_commonParts->LoadDWQ(filename);
	}


//	CPicture* lpPic = m_game->GetEffectPicture(0);
//	lpPic->LoadDWQ("sys\\bg_logo_nnn");

	return -1;
}

int CCommonBackLog::Calcu(void)
{
//MessageBox(NULL,"Calcu","backlog",MB_OK);

	int wheel = m_mouseStatus->GetWheel();
	POINT pt = m_mouseStatus->GetZahyo();
	int mouseX = pt.x;
	int mouseY = pt.y;

	if (m_startWait>0)
	{
		m_startWait--;
		return -1;
	}

	if (wheel>0)
	{
		if (UpScroll(2)) return -1;
	}

	if (wheel<0)
	{
		if (CheckDownOk() == FALSE)
		{
			return ReturnToBackMode();
		}

		if (DownScroll(2)) return -1;
	}

	if (m_game->CheckClickKey(MYRIGHT_KEY))
	{
		if (CheckDownOk() == FALSE)
		{
			return ReturnToBackMode();
		}
		if (DownScroll(5)) return -1;
	}

	if (m_game->CheckClickKey(MYLEFT_KEY))
	{
		if (UpScroll(5)) return -1;
	}


	if (m_game->CheckClickKey(MYNEXT_KEY))
	{
		if (CheckDownOk() == FALSE)
		{
			return ReturnToBackMode();
		}
		if (DownScroll(10)) return -1;
	}

	if (m_game->CheckClickKey(MYBACK_KEY))
	{
		if (UpScroll(10)) return -1;
	}


	if (m_mouseStatus->CheckClick(1))
	{
		return ReturnToBackMode();
	}

	m_onVoiceNumber = CheckOnVoice(mouseX,mouseY);

	m_onUpArrow = FALSE;
	m_onDownArrow = FALSE;

	if (m_mouseStatus->CheckClick())
	{
		int om = CheckOnArrow(mouseX,mouseY);

		if (om == 0)
		{
			m_onUpArrow = TRUE;
			if (CheckUpOk())
			{
				UpScroll(1);
			}

			return -1;
		}

		if (om == 1)
		{
			m_onDownArrow = TRUE;
			if (CheckDownOk())
			{
				DownScroll(1);
			}

			return -1;
		}

		int ov = m_onVoiceNumber;
		if (ov != -1)
		{
			LPSTR fileName = m_voiceFile + ov * VOICEFILE_LENGTH;

			if ((*fileName) != 0)
			{
				m_game->ReplayVoice(fileName);
				return -1;
			}
		}

		if (om == -1)
		{
		//	if (UpScroll(5)) return -1;
		}

	}


	return -1;
}

int CCommonBackLog::Print(void)
{
//MessageBox(NULL,"Print","backlog",MB_OK);

	CAreaControl::SetNextAllPrint();

	VoicePicAnime();
//MessageBox(NULL,"Print1","backlog",MB_OK);

	UpdownArrowPicAnime();
//MessageBox(NULL,"Print2","backlog",MB_OK);

//CAreaControl::SetNextAllPrint();

	//ClearScreen;
	BOOL b = CAreaControl::CheckAllPrintMode();

	if (b)
	{
		if (m_backlogBGMode == 0)
		{
			CAllGraphics::FillScreen(m_backColorR,m_backColorG,m_backColorB);
		}
		else
		{
			PrintBackScriptOrBG();
		}

//	CPicture* lpPic = m_game->GetEffectPicture(0);
//	lpPic->Put(0,0,FALSE);



		int gyo = m_messageKosuu;
		if (gyo > m_printGyosuuMax) gyo = m_printGyosuuMax;

		int putX = m_printX;
		int putY = m_printY;

		if (m_titlePicPrintFlag)
		{
			if (m_titlePicUpperFlag == 0)
			{
				m_commonParts->Put(m_titlePicPrintX,m_titlePicPrintY,TRUE);
			}
		}

		if (m_titlePrintFlag)
		{
			m_message->PrintMessage(m_titleMessagePrintX,m_titleMessagePrintY,m_titleMessage,m_fontSize,255,255,255,m_sukima,m_nextY,0);
		}
//		m_message->PrintMessage(400-25*3,putY,"#橙蟲の育成日記",m_fontSize,255,255,255,1,m_nextY,0);
//		m_message->PrintMessage(400-25*3,putY,"#橙幻惑の微笑み",m_fontSize,255,255,255,1,m_nextY,0);
		putY += m_nextY;
		putY += m_nextY;

		putY += m_nextY;

		int k = m_printPointer;

		for (int i=0;i<gyo;i++)
		{
			int c = m_logColor[k];
			int colR = (c >> 16) & 0xff;
			int colG = (c >> 8 ) & 0xff;
			int colB = (c      ) & 0xff;

			if ((*(m_voiceFile + k * VOICEFILE_LENGTH)) != 0)
			{
				POINT pt = GetVoicePrintZahyo(i);
				if (m_voicePicFlag == 0)
				{
					m_message->PrintMessage(pt.x, pt.y, m_voiceMessage, m_fontSize,255,255,255,m_sukima,m_nextY,0);
				}
				else
				{
					int md = 0;
					if (m_onVoiceNumber != -1)
					{
						if (((i+ m_printPointer + BACKLOG_KOSUU) % BACKLOG_KOSUU) == m_onVoiceNumber)
						{
							md = 1;
						}
					}

					PutVoicePic(pt.x,pt.y,md);
					//m_voicePic->Blt(pt.x,pt.y,0,0,m_voiceSizeX,m_voiceSizeY,TRUE);
				}
			}

			m_message->PrintMessage(putX,putY,m_logMessage + k * BACKLOG_LENGTH,m_fontSize,colR,colG,colB,m_sukima,m_nextY,0);

			k++;
			k %= BACKLOG_KOSUU;
			putY += m_nextY;
		}

		if (m_titlePicPrintFlag)
		{
			if (m_titlePicUpperFlag == 2)
			{
				m_commonParts->Put(m_titlePicPrintX,m_titlePicPrintY,TRUE);
			}
		}

		if (CheckUpOk())
		{
			if (m_updownArrowPicFlag == 0)
			{
				m_message->PrintMessage(m_upArrowPrintX,m_upArrowPrintY,m_upArrowMessage,m_fontSize,255,255,255,m_sukima,m_nextY,0);
			}
			else
			{
				int md = 0;
				if (m_onUpArrow) md = 1;
				PutUpdownArrowPic(0,m_upArrowPrintX,m_upArrowPrintY,md);
//				m_updownArrowPic->Blt(m_upArrowPrintX,m_upArrowPrintY,0,0,m_updownArrowSizeX,m_updownArrowSizeY,TRUE);
			}
//			m_message->PrintMessage(400-11,putY,"#水▲",m_fontSize,255,255,255,1,m_nextY,0);
		}

		if (CheckDownOk())
		{
			if (m_updownArrowPicFlag == 0)
			{
				m_message->PrintMessage(m_downArrowPrintX,m_downArrowPrintY,m_downArrowMessage,m_fontSize,255,255,255,m_sukima,m_nextY,0);
			}
			else
			{
				int md = 0;
				if (m_onDownArrow) md = 1;
				PutUpdownArrowPic(1,m_downArrowPrintX,m_downArrowPrintY,md);
//				m_updownArrowPic->Blt(m_upArrowPrintX,m_upArrowPrintY,0,0,m_updownArrowSizeX,m_updownArrowSizeY,TRUE);
			}

//				m_updownArrowPic->Blt(m_downArrowPrintX,m_downArrowPrintY,m_updownArrowSizeX,0,m_updownArrowSizeX,m_updownArrowSizeY,TRUE);
//			}
//			m_message->PrintMessage(400-11,putY,"#水▼",m_fontSize,255,255,255,1,m_nextY,0);
//			m_message->PrintMessage(400-11,putY,"#水▼",m_fontSize,255,255,255,1,m_nextY,0);
		}

		if (m_titlePicPrintFlag)
		{
			if (m_titlePicUpperFlag == 1)
			{
				m_commonParts->Put(m_titlePicPrintX,m_titlePicPrintY,TRUE);
			}
		}


		putY += m_nextY;


	}

//MessageBox(NULL,"Print3","backlog",MB_OK);

//	CPicture::FillScreen(m_fillColorR,m_fillColorG,m_fillColorB);
	return 0;
}



void CCommonBackLog::Clear(void)
{
	m_messageKosuu = 0;
	m_nowPointer = 0;
	m_printPointer = 0;

	for (int i=0;i<BACKLOG_KOSUU;i++)
	{
		*(m_voiceFile + i * VOICEFILE_LENGTH) = 0;
	}
//	AddMessage("#赤#猫#白　過去、それは単なる通過点の集まり・・・　#赤#猫");
	AddMessage(m_firstMessage);
	AddBar();
}

void CCommonBackLog::AddSeparator(void)
{
	if (m_addSeparator)
	{
		for (int i=0;i<m_addSeparator;i++)
		{
			AddMessage((LPSTR)(&(m_separatorMessage[i*256])),m_separatorColorR,m_separatorColorG,m_separatorColorB);
		}
	}
}

void CCommonBackLog::AddMessage(LPSTR mes,int colR, int colG , int colB)
{
	if (mes == NULL) return;

	int ln = (int)strlen(mes);
	if (ln >= (BACKLOG_LENGTH))
	{
		ln = BACKLOG_LENGTH -2;
	}



	char* ptr = m_logMessage + m_nowPointer * BACKLOG_LENGTH;
	memcpy(ptr,mes,ln);
	*(ptr+ln) = 0;
	*(ptr+ln+1) = 0;

///	*(m_voiceFile+m_nowPointer * VOICEFILE_LENGTH) = 0;

	m_logColor[m_nowPointer] = (colR << 16) | (colG << 8) | colB;

//クリアー

	//以下をクリアー
	for (int i=0;i<m_printGyosuuMax;i++)
	{
		int k=(m_nowPointer+4+i);
		k %= BACKLOG_KOSUU;

		char* ptr2 = m_voiceFile + k * VOICEFILE_LENGTH;
		*ptr2 = 0;
	}


	m_nowPointer++;
	m_nowPointer %= BACKLOG_KOSUU;

	if (m_messageKosuu<BACKLOG_KOSUU-30) m_messageKosuu++;
}


void CCommonBackLog::AddVoice(LPSTR filename)
{
	int n = m_nowPointer;
//	n--;
//	n += BACKLOG_KOSUU;
	n %= BACKLOG_KOSUU;

	char* ptr = m_voiceFile + n * VOICEFILE_LENGTH;
	ZeroMemory(ptr,VOICEFILE_LENGTH);
	if (filename == NULL) return;
	int ln = (int)strlen(filename);
	if (ln>14) ln = 14;

	memcpy(ptr,filename,ln);
	*(ptr+ln) = 0;
	*(ptr+ln+1) = 0;

	//以下をクリアー
	for (int i=1;i<m_printGyosuuMax;i++)
	{
		int k=(n+i);
		k %= BACKLOG_KOSUU;

		ptr = m_voiceFile + k * VOICEFILE_LENGTH;
		*ptr = 0;
	}
}



void CCommonBackLog::ChangePreColor(int backNumber, int colR, int colG, int colB)
{
	int n = m_nowPointer - backNumber;
	n += BACKLOG_KOSUU;
	n %= BACKLOG_KOSUU;

	m_logColor[n] = (colR << 16) | (colG << 8) | colB;
}

void CCommonBackLog::AddBar(void)
{
//	AddMessage("―――――――――――――――――――――――");
	AddMessage(m_barMessage);
}

BOOL CCommonBackLog::CheckUpOk(void)
{
	if (m_messageKosuu > m_printGyosuuMax)
	{
		if (((m_printPointer+m_messageKosuu) % BACKLOG_KOSUU) != m_nowPointer)
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CCommonBackLog::CheckDownOk(void)
{
	if (m_messageKosuu > m_printGyosuuMax)
	{
		if (((m_printPointer+m_printGyosuuMax) % BACKLOG_KOSUU) != m_nowPointer)
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CCommonBackLog::UpScroll(int n)
{
	BOOL b = FALSE;

	for (int i=0;i<n;i++)
	{
		if (CheckUpOk())
		{
			m_printPointer--;
			m_printPointer += BACKLOG_KOSUU;
			m_printPointer %= BACKLOG_KOSUU;
			b = TRUE;
		}
	}

	if (b) CAreaControl::SetNextAllPrint();

	return b;
}

BOOL CCommonBackLog::DownScroll(int n)
{
	BOOL b = FALSE;

	for (int i=0;i<n;i++)
	{
		if (CheckDownOk())
		{
			m_printPointer++;
			m_printPointer += BACKLOG_KOSUU;
			m_printPointer %= BACKLOG_KOSUU;
			b = TRUE;
		}
	}

	if (b) CAreaControl::SetNextAllPrint();

	return b;
}

int CCommonBackLog::CheckOnArrow(int mouseX,int mouseY)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();

	int x = mouseX - m_upArrowPrintX;
	int y = mouseY - m_upArrowPrintY;

	if ((x>=0) && (x<m_updownArrowSizeX) && (y>=0) && (y<m_updownArrowSizeY))
	{
//		if (CheckUpOk())
//		{
			return 0;
//		}
	}

	x = mouseX - m_downArrowPrintX;
	y = mouseY - m_downArrowPrintY;

	if ((x>=0) && (x<m_updownArrowSizeX) && (y>=0) && (y<m_updownArrowSizeY))
	{
//		if (CheckDownOk())
//		{
			return 1;
//		}
	}

	return -1;
}


int CCommonBackLog::CheckOnVoice(int mouseX, int mouseY)
{
	int check = m_messageKosuu;
	if (check>m_printGyosuuMax) check = m_printGyosuuMax;

//	for (int i=0;i<m_messageKosuu;i++)
	for (int i=0;i<check;i++)
	{
		int k = m_printPointer + i;
		k %= BACKLOG_KOSUU;
		LPSTR fileName = m_voiceFile + k * VOICEFILE_LENGTH;
		if ((*fileName) != 0)
		{
			POINT pt = GetVoicePrintZahyo(i);
			int x = mouseX - pt.x;
			int y = mouseY - pt.y;

			if ((x>=0) && (x<m_voiceSizeX) && (y>=0) && (y<m_voiceSizeY))
			{
				return k;
			}
		}
	}

	return -1;
}


POINT CCommonBackLog::GetVoicePrintZahyo(int n)
{
	POINT pt;

//	pt.x = m_printX  - m_fontSize;
//	pt.y = m_printY + m_nextY * (3 + n);

	pt.x = m_printX + m_voicePrintX;
	pt.y = m_printY + m_nextY * (3 + n) + m_voicePrintY;

	return pt;
}

int CCommonBackLog::ReturnToBackMode(void)
{
	m_game->StopScriptSoundAndVoice();

	if (m_returnSoundNumber > 0)
	{
		m_game->PlaySystemSound(m_returnSoundNumber-1);
	}

	return ReturnFadeOut(m_backMode);
//	m_game->FuqueAllEffect();
//	return m_backMode;
}

void CCommonBackLog::FinalExitRoutine(void)
{
	m_game->FuqueAllEffect();
}

int CCommonBackLog::EndMode(void)
{
	return -1;
	m_game->FuqueAllEffect();
	return -1;
}

void CCommonBackLog::VoicePicAnime(void)
{
	int type = m_voicePicAnimeType;
	int speed = m_voicePicAnimeSpeed;
	int count = m_voicePicAnimeCount;
	int pattern = m_voicePicAnimePattern;

	if (m_voicePicAnimeFlag)
	{
//		int type = m_voicePicAnimeType;
//		int speed = m_voicePicAnimeSpeed;
//		int count = m_voicePicAnimeCount;
//		int pattern = m_voicePicAnimePattern;
	
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

		m_voicePicAnimeCount = count;
	}

	//pat
	type = m_voicePicAnimeType;
	speed = m_voicePicAnimeSpeed;
	count = m_voicePicAnimeCount;
	pattern = m_voicePicAnimePattern;

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
		percent = 100 * (count - ((count / speed) * speed));
		percent /= speed;
	}

	m_voicePicPattern1 = pic1;
	m_voicePicPattern2 = pic2;
	m_voicePicPercent = percent;
}


void CCommonBackLog::UpdownArrowPicAnime(void)
{
	int type = m_updownArrowAnimeType;
	int speed = m_updownArrowAnimeSpeed;
	int count = m_updownArrowAnimeCount;
	int pattern = m_updownArrowAnimePattern;

//MessageBox(NULL,"Print1-1","backlog",MB_OK);

	if (m_updownArrowAnimeFlag)
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

		m_updownArrowAnimeCount = count;
	}

//MessageBox(NULL,"Print1-2","backlog",MB_OK);

	//pat
	type = m_updownArrowAnimeType;
	speed = m_updownArrowAnimeSpeed;
	count = m_updownArrowAnimeCount;
	pattern = m_updownArrowAnimePattern;

	int revFlag = 0;
	int dv = pattern;

	if (speed<1) speed = 1;

	if ((type == 3) || (type == 4) || (type == 7) || (type == 8))
	{
		dv = (pattern-1) * 2;
		if (dv<1) dv = 1;
		revFlag = 1;
	}
//MessageBox(NULL,"Print1-2-A","backlog",MB_OK);

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
//MessageBox(NULL,"Print1-2-B","backlog",MB_OK);

	pic2 %= dv;
//MessageBox(NULL,"Print1-2-C","backlog",MB_OK);

	int percent = 100;

//MessageBox(NULL,"Print1-3","backlog",MB_OK);

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

//MessageBox(NULL,"Print1-4","backlog",MB_OK);

	m_updownArrowPattern1 = pic1;
	m_updownArrowPattern2 = pic2;
	m_updownArrowPercent = percent;
}

void CCommonBackLog::PutVoicePic(int x,int y, int pt)
{
	if (m_voicePicAnimeFlag == 0) pt = 0;

	CPicture* lpPic = m_voicePic;
	if (lpPic == NULL) return;
//	if (lpPic->CheckDataExsit() == FALSE) return;

	int sizeX = m_voiceSizeX;
	int sizeY = m_voiceSizeY;

	int srcX = sizeX * pt;
	int srcY = sizeY * m_voicePicPattern1;
	int srcY2 = sizeY * m_voicePicPattern2;
	if (m_voicePicAnimeFlag == 0)
	{
		srcX = 0;
		srcY = 0;
	}

	int putX = x;
	int putY = y;


	if (m_voicePicPercent == 100)
	{
		lpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
	}
	else if (m_voicePicPercent == 0)
	{
		lpPic->Blt(putX,putY,srcX,srcY2,sizeX,sizeY,TRUE);
	}
	else
	{
		int ps2 = 100 - m_voicePicPercent;
		int* lpBuffer2 = (int*)(lpPic->GetBuffer());
		char* lpMask2 = (char*)(lpPic->GetMaskPic());
	
		int deltaX = 0;
		int deltaY = srcY2 - srcY;

		SIZE sz = lpPic->GetPicSize();

		lpBuffer2 += deltaX;
		lpBuffer2 += deltaY * sz.cx;

		lpMask2 += deltaX;
		lpMask2 += deltaY * sz.cx;


//		lpPic->ChangeTranslateBlt(putX,putY,srcX,srcY,sizeX,sizeY,m_voicePicPercent,ps2,lpBuffer2,lpMask2,lpPic);
		lpPic->ChangeTranslateBlt(putX,putY,srcX,srcY,sizeX,sizeY,m_voicePicPercent,ps2,lpPic,srcX,srcY2);

	}
}

void CCommonBackLog::PutUpdownArrowPic(int n,int x,int y, int md)
{
	if (m_updownArrowAnimeFlag == 0) md = 0;

	CPicture* lpPic = m_updownArrowPic;

	if (m_updownArrowAnimeFlag)
	{
		lpPic = m_upArrowPic;
		if (n == 1) lpPic = m_downArrowPic;
	}

	if (lpPic == NULL) return;

	int sizeX = m_updownArrowSizeX;
	int sizeY = m_updownArrowSizeY;

	int srcX = sizeX * md;
	int srcY = sizeY * m_updownArrowPattern1;
	int srcY2 = sizeY * m_updownArrowPattern2;
	if (m_updownArrowAnimeFlag == 0)
	{
		srcX = 0;
		srcY = 0;
	}

	int putX = x;
	int putY = y;


	if (m_updownArrowPercent == 100)
	{
		lpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
	}
	else if (m_updownArrowPercent == 0)
	{
		lpPic->Blt(putX,putY,srcX,srcY2,sizeX,sizeY,TRUE);
	}
	else
	{
		int ps2 = 100 - m_updownArrowPercent;
		int* lpBuffer2 = (int*)(lpPic->GetBuffer());
		char* lpMask2 = (char*)(lpPic->GetMaskPic());
	
		int deltaX = 0;
		int deltaY = srcY2 - srcY;

		SIZE sz = lpPic->GetPicSize();

		lpBuffer2 += deltaX;
		lpBuffer2 += deltaY * sz.cx;

		lpMask2 += deltaX;
		lpMask2 += deltaY * sz.cx;


//		lpPic->ChangeTranslateBlt(putX,putY,srcX,srcY,sizeX,sizeY,m_updownArrowPercent,ps2,lpBuffer2,lpMask2,lpPic);
		lpPic->ChangeTranslateBlt(putX,putY,srcX,srcY,sizeX,sizeY,m_updownArrowPercent,ps2,lpPic,srcX,srcY2);

	}

}

void CCommonBackLog::ReplaceMessage(LPSTR message,LPSTR replace)
{
	int ln = strlen(message);
	char c = *replace;

	for (int i=0;i<ln;i++)
	{
		char cc = *(message+i);
		if (cc == c)
		{
			*(message+i) = ' ';
		}
	}
}


/*_*/

