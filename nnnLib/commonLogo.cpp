//
// commonLogo.cpp
//

#include <windows.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"

#include "..\nyanLib\include\allGraphics.h"

#include "..\nnnUtilLib\myMouseStatus.h"

#include "commonMode.h"
#include "commonSystemParamName.h"

#include "..\nnnUtilLib\inputStatus.h"

#include "gameCallBack.h"

#include "commonGeneral.h"
#include "commonLogo.h"



CCommonLogo::CCommonLogo(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	int i = 0;
	SetClassNumber(LOGO_MODE);
//	m_classNumber = LOGO_MODE;
	LoadSetupFile("logo",64);
	m_logoKosuu = 2;
	m_nextMode = TITLE_MODE;

	GetInitGameParam(&m_logoKosuu,"logoNumber");
//	GetInitGameParam(&m_nextMode,"nextMode");
	GetModeNumberBySetup("nextMode",&m_nextMode);


	m_filename = NULL;
	m_fadeInTime = NULL;
	m_fadeOutTime = NULL;
	m_keepTime = NULL;
	m_fadeInColor = NULL;
	m_fadeOutColor = NULL;
	m_skipOkFlag = NULL;
	m_fadeInBGColorFlag = NULL;
	m_fadeOutBGColorFlag = NULL;


	m_filename = new LPSTR[m_logoKosuu];
	m_fadeInTime = new int[m_logoKosuu];
	m_fadeOutTime = new int[m_logoKosuu];
	m_keepTime = new int[m_logoKosuu];
	m_fadeInColor = new int[m_logoKosuu * 3];
	m_fadeOutColor = new int[m_logoKosuu * 3];
	m_skipOkFlag = new int[m_logoKosuu];
	m_fadeInBGColorFlag = new int[m_logoKosuu];
	m_fadeOutBGColorFlag = new int[m_logoKosuu];

	m_defaultUseBGColor = 0;
	m_defaultFadeInTime = 10;
	m_defaultKeepTime = 20;
	m_defaultFadeOutTime = 10;


	GetInitGameParam(&m_defaultUseBGColor,"defaultUseBGColor");
	GetInitGameParam(&m_defaultFadeInTime,"defaultFadeInTime");
	GetInitGameParam(&m_defaultFadeOutTime,"defaultFadeOutTime");
	GetInitGameParam(&m_defaultKeepTime,"defaultKeepTime");

	m_defaultFadeInColorR = 255;
	m_defaultFadeInColorG = 255;
	m_defaultFadeInColorB = 255;

	m_defaultFadeOutColorR = 255;
	m_defaultFadeOutColorG = 255;
	m_defaultFadeOutColorB = 255;

	GetInitGameParam(&m_defaultFadeInColorR,"defaultFadeInColorR");
	GetInitGameParam(&m_defaultFadeInColorG,"defaultFadeInColorG");
	GetInitGameParam(&m_defaultFadeInColorB,"defaultFadeInColorB");

	GetInitGameParam(&m_defaultFadeOutColorR,"defaultFadeOutColorR");
	GetInitGameParam(&m_defaultFadeOutColorG,"defaultFadeOutColorG");
	GetInitGameParam(&m_defaultFadeOutColorB,"defaultFadeOutColorB");



	for (i=0;i<m_logoKosuu;i++)
	{
		m_filename[i] = NULL;
		m_fadeInTime[i] = m_defaultFadeInTime;
		m_fadeOutTime[i] = m_defaultFadeOutTime;
		m_keepTime[i] = m_defaultKeepTime;
		m_skipOkFlag[i] = 1;
		m_fadeInColor[i*3+0] = m_defaultFadeInColorR;
		m_fadeInColor[i*3+1] = m_defaultFadeInColorG;
		m_fadeInColor[i*3+2] = m_defaultFadeInColorB;
		m_fadeOutColor[i*3+0] = m_defaultFadeOutColorR;
		m_fadeOutColor[i*3+1] = m_defaultFadeOutColorG;
		m_fadeOutColor[i*3+2] = m_defaultFadeOutColorB;
		m_fadeInBGColorFlag[i] = m_defaultUseBGColor;
		m_fadeOutBGColorFlag[i] = m_defaultUseBGColor;
	}

	m_useCustomBGColorFlag = 0;
	m_useCustomFileFlag = 0;
	m_useCustomSkipFlag = 0;
	m_useCustomTimeFlag = 0;
	m_useCustomColorFlag = 0;

	GetInitGameParam(&m_useCustomBGColorFlag,"useCustomBGColorFlag");
	GetInitGameParam(&m_useCustomFileFlag,"useCustomFileFlag");
	GetInitGameParam(&m_useCustomSkipFlag,"useCustomSkipFlag");
	GetInitGameParam(&m_useCustomTimeFlag,"useCustomTimeFlag");
	GetInitGameParam(&m_useCustomColorFlag,"useCustomColorFlag");
	
	if (m_useCustomBGColorFlag)
	{
		for (i=0;i<m_logoKosuu;i++)
		{
			char name[256];
			wsprintf(name,"fadeInBGColorFlag%d",i+1);
			GetInitGameParam(&m_fadeInBGColorFlag[i],name);
			wsprintf(name,"fadeOutBGColorFlag%d",i+1);
			GetInitGameParam(&m_fadeOutBGColorFlag[i],name);
		}
	}

	if (m_useCustomFileFlag)
	{
		for (i=0;i<m_logoKosuu;i++)
		{
			char name[256];
			wsprintf(name,"filename%d",i+1);
			GetInitGameString(&m_filename[i],name);
		}
	}

	if (m_useCustomSkipFlag)
	{
		for (i=0;i<m_logoKosuu;i++)
		{
			char name[256];
			wsprintf(name,"skipOK%d",i+1);
			GetInitGameParam(&m_skipOkFlag[i],name);
		}
	}

	if (m_useCustomTimeFlag)
	{
		for (i=0;i<m_logoKosuu;i++)
		{
			char name[256];
			wsprintf(name,"fadeInTime%d",i+1);
			GetInitGameParam(&m_fadeInTime[i],name);

			wsprintf(name,"fadeOutTime%d",i+1);
			GetInitGameParam(&m_fadeOutTime[i],name);

			wsprintf(name,"keepTime%d",i+1);
			GetInitGameParam(&m_keepTime[i],name);
		}
	}

	if (m_useCustomColorFlag)
	{
		for (i=0;i<m_logoKosuu;i++)
		{
			char name[256];
			wsprintf(name,"fadeInColorR%d",i+1);
			GetInitGameParam(&m_fadeInColor[i*3],name);
			wsprintf(name,"fadeInColorG%d",i+1);
			GetInitGameParam(&m_fadeInColor[i*3+1],name);
			wsprintf(name,"fadeInColorB%d",i+1);
			GetInitGameParam(&m_fadeInColor[i*3+2],name);
			wsprintf(name,"fadeOutColorR%d",i+1);
			GetInitGameParam(&m_fadeOutColor[i*3],name);
			wsprintf(name,"fadeOutColorG%d",i+1);
			GetInitGameParam(&m_fadeOutColor[i*3+1],name);
			wsprintf(name,"fadeOutColorB%d",i+1);
			GetInitGameParam(&m_fadeOutColor[i*3+2],name);
		}
	}


	m_soundOrVoiceKosuu = 0;
	GetInitGameParam(&m_soundOrVoiceKosuu,"soundNumber");
	m_soundOrVoiceTiming = NULL;
	m_soundOrVoiceName = NULL;
	m_soundOrVoicePlayed = NULL;

	if (m_soundOrVoiceKosuu > 0)
	{
		m_soundOrVoiceTiming = new int[m_soundOrVoiceKosuu * 3];
		m_soundOrVoiceName = new LPSTR[m_soundOrVoiceKosuu];
		m_soundOrVoicePlayed = new int[m_soundOrVoiceKosuu];

		for (int i=0;i<m_soundOrVoiceKosuu;i++)
		{
//			m_soundOrVoiceTiming[i*3] = 0;	//sound
//			m_soundOrVoiceTiming[i*3+1] = -1;//mode no
//			m_soundOrVoiceTiming[i*3+2] = 0;//timing

//			m_soundOrVoiceName[i] = NULL;

			//get param
			char name[1024];

			sprintf_s(name,sizeof(name),"soundType%d",i+1);
			int soundType = 0;
			GetInitGameParam(&soundType,name);
			m_soundOrVoiceTiming[i*3+0] = soundType;

			sprintf_s(name,sizeof(name),"soundLogo%d",i+1);
			int soundMode = 1;
			GetInitGameParam(&soundMode,name);
			m_soundOrVoiceTiming[i*3+1] = soundMode;

			sprintf_s(name,sizeof(name),"soundTime%d",i+1);
			int soundTime = 0;
			GetInitGameParam(&soundTime,name);
			m_soundOrVoiceTiming[i*3+2] = soundTime;

			sprintf_s(name,sizeof(name),"soundFilename%d",i+1);
			LPSTR soundName = NULL;
			GetInitGameString(&soundName,name);
			m_soundOrVoiceName[i] = soundName;
		}
	}

//	int* m_soundOrVoiceTiming;//type mode frame
//	LPSTR* m_soundOrVoiceName;
//	int* m_soundOrVoicePlayed;


//	m_cdCheckFlag = 1;
//	GetInitGameParam(&m_cdCheckFlag,"cdCheckFlag");

	GetFadeInOutSetup();
}


CCommonLogo::~CCommonLogo()
{
	End();
}

void CCommonLogo::End(void)
{
	DELETEARRAY(m_soundOrVoicePlayed);
	DELETEARRAY(m_soundOrVoiceName);
	DELETEARRAY(m_soundOrVoiceTiming);

	DELETEARRAY(m_filename);
	DELETEARRAY(m_fadeInTime);
	DELETEARRAY(m_fadeOutTime);
	DELETEARRAY(m_keepTime);
	DELETEARRAY(m_fadeInColor);
	DELETEARRAY(m_fadeOutColor);
	DELETEARRAY(m_skipOkFlag);
	DELETEARRAY(m_fadeInBGColorFlag);
	DELETEARRAY(m_fadeOutBGColorFlag);
}


int CCommonLogo::Init(void)
{
	m_mode = 0;
	m_subMode = 0;
	m_count = 0;
	m_soundCount = 0;

	LoadPicture();

	if (m_soundOrVoiceKosuu > 0)
	{
		for (int i=0;i<m_soundOrVoiceKosuu;i++)
		{
			m_soundOrVoicePlayed[i] = 0;
		}
	}


	return -1;
}


int CCommonLogo::Calcu(void)
{
	if (m_skipOkFlag[m_mode] != 0)
	{
		int cnt = m_game->GetLaunchCount() + 1;
		if (m_skipOkFlag[m_mode] <= cnt)
		{
			if (m_mouseStatus->CheckSkipClick())
			{
				CAreaControl::SetNextAllPrint();
				int rt = NextMode();
				if (rt != -1)
				{
					return ReturnFadeOut(rt);
				}
				else
				{
					return -1;
				}
			}
		}
	}

	m_count++;
	m_soundCount++;
	CheckSoundOrVoice();

	int limit = 0;
	if (m_subMode == 0)
	{
		limit = m_fadeInTime[m_mode];
	}

	if (m_subMode == 1)
	{
		limit = m_keepTime[m_mode];
	}

	if (m_subMode == 2)
	{
		limit = m_fadeOutTime[m_mode];
	}

	if (m_count >= limit)
	{
		m_count=0;
		m_subMode++;
		CAreaControl::SetNextAllPrint();
		if (m_subMode >= 3)
		{
			int rt = NextMode();
			if (rt != -1)
			{
				return ReturnFadeOut(rt);
			}
			else
			{
				return -1;
			}
//			return NextMode();
		}
	}

	if (m_subMode != 1) CAreaControl::SetNextAllPrint();

	return -1;
}

void CCommonLogo::CheckSoundOrVoice(void)
{
	if (m_soundOrVoiceKosuu <= 0) return;

	for (int i=0;i<m_soundOrVoiceKosuu;i++)
	{
		if (m_soundOrVoicePlayed[i] == 0)
		{
			if (m_soundOrVoiceTiming[i*3+1] == (m_mode+1))
			{
				if (m_soundCount >= m_soundOrVoiceTiming[i*3+2])
				{
					PlaySoundOrVoice(i);
				}
			}
		}
	}
}

void CCommonLogo::PlaySoundOrVoice(int n)
{
	m_soundOrVoicePlayed[n] = 1;
	int type = m_soundOrVoiceTiming[n*3];
	LPSTR name = m_soundOrVoiceName[n];
	if (name != NULL)
	{
		//play!!
		if (type == 0)
		{
			m_game->PlaySystemWaveFilename(name);
		}
		else
		{
			m_game->ReplayVoice(name);
		}
	}
}



int CCommonLogo::Print(void)
{
	if (m_subMode == 1)
	{
		if (CAreaControl::CheckAllPrintMode())
		{
			m_commonBG->Put(0,0,FALSE);
		}
		else
		{
			if (m_count <= 1)
			{
				CAreaControl::SetNextAllPrint();
				m_commonBG->Put(0,0,FALSE);
			}
		}
		return -1;
	}

	CAreaControl::SetNextAllPrint();

	int mode = m_mode;
	int subMode = m_subMode;
	int count = m_count;

	if (mode >= m_logoKosuu)
	{
		mode = m_logoKosuu - 1;	//‚æ‚¤‚¶‚ñ
		subMode = 2;
		count = m_fadeOutTime[mode];
	}


	int* dst = CMyGraphics::GetScreenBuffer();
	int* src = (int*)(m_commonBG->GetBuffer());

	//fill

	int colR = 0;
	int colG = 0;
	int colB = 0;

	if (subMode == 0)
	{
		if (m_fadeInBGColorFlag[mode])
		{
			int d = *src;
			colR = (d >> 16) & 0xff;
			colG = (d >>  8) & 0xff;
			colB = (d      ) & 0xff;
		}
		else
		{
			colR = m_fadeInColor[mode*3+0];
			colG = m_fadeInColor[mode*3+1];
			colB = m_fadeInColor[mode*3+2];
		}
	}

	if (subMode == 2)
	{
		if (m_fadeOutBGColorFlag[mode])
		{
			int d = *src;
			colR = (d >> 16) & 0xff;
			colG = (d >>  8) & 0xff;
			colB = (d      ) & 0xff;
		}
		else
		{
			colR = m_fadeOutColor[mode*3+0];
			colG = m_fadeOutColor[mode*3+1];
			colB = m_fadeOutColor[mode*3+2];
		}
	}


	int col = (colR << 16) | (colR << 8) | colB;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	CAllGraphics::FillScreen(colR,colG,colB);

	/*
	//clear back
	__asm
	{
		push eax
		push ecx
		push esi
		push edi


//		mov esi,src
		mov edi,dst

		mov eax,screenSizeX;
		mov edx,screenSizeY;
		mul edx
		mov ecx,eax

		mov eax,col
		cld
		rep stosd

		pop edi
		pop esi
		pop ecx
		pop eax
	}
	*/

	int ps = 100;

	int dv = 1;
	if (subMode == 0)
	{
		dv = m_fadeInTime[mode];
		if (dv<1) dv = 1;
		ps = (count * 100) / dv;
	}

	if (subMode == 2)
	{
		dv = m_fadeOutTime[mode];
		if (dv<1) dv = 1;
		ps = ((dv - count) * 100) / dv;
	}

	if (ps<0) ps = 0;
	if (ps>100) ps = 100;


	if (ps != 100)
	{
		m_commonBG->TransLucentBlt(0,0,0,0,screenSizeX,screenSizeY,ps);
	}
	else
	{
		m_commonBG->Put(0,0,FALSE);
	}

	return -1;
}




int CCommonLogo::NextMode(void)
{
	m_mode++;
	m_count = 0;
	m_soundCount = 0;
	m_subMode = 0;

	if (m_mode>=m_logoKosuu)
	{
//		if (m_cdCheckFlag != 0)
//		{
//			if (m_game->GetSystemParam(NNNPARAM_BGMMODE) == NNNBGMMODE_CDDA)
//			{
//				if (m_game->CheckCD())
//				{
//					return m_nextMode;
//				}
//
//				m_game->SetCommonBackMode(CDERROR_MODE,m_nextMode);
//				return CDERROR_MODE;
//			}
//		}

		return m_nextMode;
	}

	LoadPicture();
	CAreaControl::SetNextAllPrint();
	return -1;
}

void CCommonLogo::LoadPicture(void)
{
	if (m_filename[m_mode] == NULL)
	{
		char filename[1024];
		wsprintf(filename,"sys\\logo%d",m_mode+1);
		m_commonBG->LoadDWQ(filename);
	}
	else
	{
		BOOL enFlag = FALSE;

		if (m_filename[m_mode][2] == '\\')
		{
			enFlag = TRUE;
		}
		if (m_filename[m_mode][3] == '\\')
		{
			enFlag = TRUE;
		}

		if (enFlag)
		{
			m_commonBG->LoadDWQ(m_filename[m_mode]);
		}
		else
		{
			char filename[1024];
			wsprintf(filename,"sys\\%s",m_filename[m_mode]);
			m_commonBG->LoadDWQ(filename);
		}
	}
}

void CCommonLogo::ReCreateExitScreen(void)
{
	Print();
}

/*_*/




