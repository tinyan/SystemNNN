//
// commonPrintCG.cpp
//


#include <windows.h>

#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGraphics.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"

#include "..\nnnUtilLib\commonKeyList.h"
#include "commonSystemSoundName.h"
#include "..\nnnUtilLib\myMessage.h"

#include "..\nnnUtilLib\cgDataControl.h"
#include "..\nnnUtilLib\cgVoice.h"

#include "commonMode.h"
#include "commonSystemParamName.h"

#include "..\nyanEffectLIB\commoneffect.h"
#include "..\nyanEffectAnimeLIB\effectAnimation.h"


#include "gameCallBack.h"

#include "commonGeneral.h"
#include "commonPrintCG.h"



char CCommonPrintCG::m_defaultTaBGFileName[]="bg_cgcharaback";



CCommonPrintCG::CCommonPrintCG(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(PRINTCG_MODE);
//	m_classNumber = PRINTCG_MODE;
	LoadSetupFile("PrintCG",64);

//	m_backMode = SELECTCGCHARA_MODE;
	m_backMode = SELECTCG_MODE;

	m_cgDataControl = m_game->GetCGDataControl();

	m_scrollHoukouX = 0;
	m_scrollHoukouY = 0;
	m_scrollFirstWaitBaseX = 10;
	m_scrollFirstWaitBaseY = 10;
	m_scrollTimeBaseX = 30;
	m_scrollTimeBaseY = 30;

	GetInitGameParam(&m_scrollHoukouX,"scrollDirectionX");
	GetInitGameParam(&m_scrollHoukouY,"scrollDirectionY");
	GetInitGameParam(&m_scrollTimeBaseX,"scrollTimeX");
	GetInitGameParam(&m_scrollTimeBaseY,"scrollTimeY");
	GetInitGameParam(&m_scrollFirstWaitBaseX,"scrollWaitX");
	GetInitGameParam(&m_scrollFirstWaitBaseY,"scrollWaitY");

	m_scrollTimeX = m_scrollTimeBaseX;
	m_scrollTimeY = m_scrollTimeBaseY;
	m_scrollFirstWaitX = m_scrollFirstWaitBaseX;
	m_scrollFirstWaitY = m_scrollFirstWaitBaseY;

	m_scrollHoukouXSpecial = -1;
	m_scrollHoukouYSpecial = -1;

	GetInitGameParam(&m_backMode,"backMode");

	m_animeFrame = 1;
	GetInitGameParam(&m_animeFrame,"animeFrame");
	m_animeCount = 0;

	m_taBGFlag = 0;
	GetInitGameParam(&m_taBGFlag,"taBGFlag");
	m_taBGCharaFileName = NULL;

	if (m_taBGFlag == 0)
	{
		m_taBGColorR = 0;
		m_taBGColorG = 0;
		m_taBGColorB = 0;
		GetInitGameParam(&m_taBGColorR,"taBGColorR");
		GetInitGameParam(&m_taBGColorG,"taBGColorG");
		GetInitGameParam(&m_taBGColorB,"taBGColorB");
	}
	else
	{
		if (m_taBGFlag == 1)
		{
			m_taBGFileName = m_defaultTaBGFileName;
			GetInitGameString(&m_taBGFileName,"taBGFileName");
		}
		else
		{
			int ninzu = 1;
			if (m_cgDataControl != NULL)
			{
				ninzu = m_cgDataControl->GetCGCharaKosuu();
			}

			//int ninzu = m_game->GetCGCharaKosuu();
			m_taBGCharaFileName = new LPSTR[ninzu];
			for (int i=0;i<ninzu;i++)
			{
				m_taBGCharaFileName[i] = m_defaultTaBGFileName;
				char name[256];
				wsprintf(name,"taBGCharaFileName%d",i+1);
				GetInitGameString(&m_taBGCharaFileName[i],name);
			}
		}
	}

	m_sabunFlag = 0;
	m_sabunFade = 0;
	m_sabunFadeTime = 1;
	m_sabunFadeCount = 0;

	GetInitGameParam(&m_sabunFade,"diffFadeType");
	if (m_sabunFade > 0)
	{
		GetInitGameParam(&m_sabunFadeTime,"diffFadeTime");
	}

	m_returnOneLookCGSet = 0;
	GetInitGameParam(&m_returnOneLookCGSet,"returnOneLookCGSet");

	m_sabunPic = new CPicture();

	m_nextSound = COMMON_SYSTEMSOUND_PON+1;
	m_prevSound = COMMON_SYSTEMSOUND_PON+1;
	m_backSound = COMMON_SYSTEMSOUND_CANCEL+1;

	GetInitGameParam(&m_nextSound,"nextSound");
	GetInitGameParam(&m_prevSound,"prevSound");
	GetInitGameParam(&m_backSound,"backSound");

	m_cgVoice = new CCGVoice();
	m_cgVoiceFileName = new char[1024];

	m_cgVoiceWaitTime = 10;
	GetInitGameParam(&m_cgVoiceWaitTime,"cgVoiceWaitTime");

	GetBGMSetup();
	GetFadeInOutSetup();
}



CCommonPrintCG::~CCommonPrintCG()
{
	End();
}

void CCommonPrintCG::End(void)
{
	ENDDELETECLASS(m_sabunPic);

	DELETEARRAY(m_cgVoiceFileName);
	ENDDELETECLASS(m_cgVoice);

	DELETEARRAY(m_taBGCharaFileName);
}



int CCommonPrintCG::Init(void)
{
	ClearLastCGVoice();
	ChangeCGVoice();

	m_animeCount = 0;
	m_sabunFadeCount = 0;
	m_sabunFlag = 0;

	LoadCG();
	return -1;
}

int CCommonPrintCG::Calcu(void)
{
	if (m_mouseStatus->CheckClick(1))
	{
		m_game->PlayCommonSystemSound(m_backSound-1);
		return ReturnFadeOut(m_backMode);
//		return m_backMode;
	}

	CheckAndPlayCGVoice();


	int wheel = m_mouseStatus->GetWheel();
	POINT pt = m_mouseStatus->GetZahyo();
	int mouseX = pt.x;
	int mouseY = pt.y;


	int dlt = 0;
	if (wheel>0) dlt = -1;
	if (wheel<0) dlt = 1;

	int ctrl = GetAsyncKeyState(VK_CONTROL) & 0x80000000;
	
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (CheckClick())
	{
		if (m_scrollFlagX || m_scrollFlagY || (ctrl==0))
		{
			if ((m_scrollFlagX || m_scrollFlagY) && (ctrl))
			{
				if (m_scrollFlagX)
				{
					m_scrollCountX = 0;
					m_scrollFlagX = FALSE;
				}

				if (m_scrollFlagY)
				{
					m_scrollCountY = 0;
					m_scrollFlagY = FALSE;
				}

				m_dragFlag = TRUE;
				m_dragStartX = mouseX;
				m_dragStartY = mouseY;
				CAreaControl::SetNextAllPrint();

			}
			else
			{
				dlt = 1;
			}
		}
		else
		{
			m_dragFlag = TRUE;
			m_dragStartX = mouseX;
			m_dragStartY = mouseY;
			CAreaControl::SetNextAllPrint();
		}
	}
	else
	{
		if (m_mouseStatus->GetTrig(0))
		{
			if (m_dragFlag)
			{
				CAreaControl::SetNextAllPrint();
				int dx = mouseX-m_dragStartX;
				int dy = mouseY-m_dragStartY;

				m_dragedX -= dx;
				m_dragedY -= dy;

				if (m_dragedX<0) m_dragedX = 0;
				if (m_dragedY<0) m_dragedY = 0;

				if (m_dragedX > m_picRect.right - screenSizeX)
				{
					m_dragedX = m_picRect.right - screenSizeX;
				}

				if (m_dragedY > m_picRect.bottom - screenSizeY)
				{
					m_dragedY = m_picRect.bottom - screenSizeY;
				}

				m_dragedFlag = TRUE;

				m_dragStartX = mouseX;
				m_dragStartY = mouseY;
			}
		}
		else
		{
			m_dragFlag = FALSE;
		}
	}



	if (m_mouseStatus->GetTrig(2)) dlt = 1;

	if (dlt != 0)
	{


		int old = 0;
		if (m_cgDataControl != NULL)
		{
			old = m_cgDataControl->GetCGNumber();
		}





		int cg = old;
		m_sabunFlag = 0;

		if (m_cgDataControl != NULL)
		{
			if (dlt>0)
			{
				cg = m_cgDataControl->SearchNextCG();
			}
			else
			{
				cg = m_cgDataControl->SearchPreCG();
			}

			int 	m_cgCharaNumber = m_cgDataControl->GetCGCharaNumber();

			if (m_game->GetCGBlockNumber(m_cgCharaNumber,old) == m_game->GetCGBlockNumber(m_cgCharaNumber,cg))
			{
				m_sabunFlag = 1;
			}

			if (m_returnOneLookCGSet)
			{
				//last?
				if (m_sabunFlag == 0)
				{
					m_game->PlayCommonSystemSound(m_backSound-1);
					return ReturnFadeOut(m_backMode);
				}
			}

			if (m_sabunFlag)
			{
				//anime
				if (	m_cgDataControl->CheckCGIsAnime(m_cgCharaNumber,cg))
				{
					m_sabunFlag = 0;
				}
			}
		}

		if (cg != old)
		{
			if (m_sabunFlag && m_sabunFade)
			{
				m_sabunFadeCount = 0;
				LoadCG(TRUE,old);//load old
			}

			if (m_cgDataControl != NULL)
			{
				m_cgDataControl->SetCGNumber(cg);
			}

			if (dlt>0)
			{
				m_game->PlaySystemSound(m_nextSound-1);
			}
			else
			{
				m_game->PlaySystemSound(m_prevSound-1);
			}

			LoadCG();
			ChangeCGVoice();
			CAreaControl::SetNextAllPrint();
			return -1;
		}
	}

	if (m_scrollFlagX)
	{
		m_scrollCountX--;
		if (m_scrollCountX<=0)
		{
			m_scrollCountX = 0;
			m_scrollFlagX = FALSE;
		}
	}

	if (m_scrollFlagY)
	{
		m_scrollCountY--;
		if (m_scrollCountY<=0)
		{
			m_scrollCountY = 0;
			m_scrollFlagY = FALSE;
		}
	}

	return -1;
}


int CCommonPrintCG::Print(void)
{
	BOOL b = CAreaControl::CheckAllPrintMode();

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int cgCharaNumber = 0;
	int cgNumber = 0;

	BOOL animeFlag = FALSE;

	if (m_cgDataControl != NULL)
	{
		cgCharaNumber = m_cgDataControl->GetCGCharaNumber();
		cgNumber = m_cgDataControl->GetCGNumber();
		animeFlag = m_cgDataControl->CheckCGIsAnime(cgCharaNumber,cgNumber);
		if (animeFlag)
		{
			b = TRUE;
			CAreaControl::SetNextAllPrint();
		}

	}

	if (m_sabunFlag && m_sabunFade)
	{
		if (m_sabunFade)
		{
			if (m_sabunFadeCount < m_sabunFadeTime)
			{
				b = TRUE;
				CAreaControl::SetNextAllPrint();
			}
		}
	}


	if (b || m_scrollFlagX || m_scrollFlagY)
	{
		int divX = m_scrollTimeX;
		int mulX = m_scrollCountX;
		if (mulX >= m_scrollTimeX) mulX = divX;
		if (m_scrollHoukouXSpecial != -1)
		{
			if (m_scrollHoukouXSpecial) mulX = divX - mulX;
		}
		else
		{
			if (m_scrollHoukouX) mulX = divX - mulX;
		}

		int scrollSizeX = m_picRect.right - screenSizeX;
		int dx = (scrollSizeX * mulX) / divX;


		int divY = m_scrollTimeY;
		int mulY = m_scrollCountY;
		if (mulY >= m_scrollTimeY) mulY = divY;
		if (m_scrollHoukouYSpecial != -1)
		{
			if (m_scrollHoukouYSpecial) mulY = divY - mulY;
		}
		else
		{
			if (m_scrollHoukouY) mulY = divY - mulY;
		}

		int scrollSizeY = m_picRect.bottom - screenSizeY;
		int dy = (scrollSizeY * mulY) / divY;

		if (m_dragedFlag == FALSE)
		{
			m_dragedX = dx;
			m_dragedY = dy;
		}
		else
		{
			dx = m_dragedX;
			dy = m_dragedY;
		}

//		m_commonBG->Blt(0,0,dx,dy,screenSizeX,screenSizeY,FALSE);

		//SIZE sz = m_commonBG->GetPicSize();

		CPicture* lpPicBG = m_game->GetEffectPicture(0);
		SIZE sz = lpPicBG->GetPicSize();

		int maisuu = m_maisuuX * m_maisuuY;
		if (maisuu > 0)
		{
			CheckAndEraseBG();

			if (animeFlag)
			{
				int animeMaisuu = m_cgDataControl->GetAnimeMaisuu(cgCharaNumber,cgNumber);
				int dv = m_animeFrame;
				if (dv<1) dv = 1;

				int anime = m_animeCount / dv;
				if (anime>=animeMaisuu)
				{
					anime %= animeMaisuu;
				}

				CPicture* lpPic = m_game->GetAnimeBuffer(anime);
				if (lpPic != NULL)
				{
					if (m_sabunFlag && m_sabunFade)
					{
						PrintSabunFade(lpPic);
					}
					else
					{
						lpPic->Put(0,0,FALSE);
					}
				}
			}
			else
			{
				for (int j=0;j<m_maisuuY;j++)
				{
					for (int i=0;i<m_maisuuX;i++)
					{
						//CPicture* lpPic = m_commonBG;

						int n = i + j * m_maisuuX;
						CPicture* lpPic = m_game->GetEffectPicture(n);
						if ((i == 0) && m_sabunFlag && m_sabunFade)
						{
							PrintSabunFade(lpPic);
						}
						else
						{
							lpPic->Blt(i*sz.cx-dx,j*sz.cy-dy,0,0,sz.cx,sz.cy,m_taFlag[n]);
						}
					}
				}
			}
		}


		if (m_scrollFlagX || m_scrollFlagY)
		{
			CAreaControl::SetNextAllPrint();
		}
	}


	//sabun fade
	if (m_sabunFlag && m_sabunFade)
	{
		if (m_sabunFadeCount < m_sabunFadeTime)
		{
			m_sabunFadeCount++;
		}
	}

	//anime?
	if (m_cgDataControl != NULL)
	{
		int cgCharaNumber = m_cgDataControl->GetCGCharaNumber();
		int cgNumber = m_cgDataControl->GetCGNumber();
		if (m_cgDataControl->CheckCGIsAnime(cgCharaNumber,cgNumber))
		{
			int animeMaisuu = m_cgDataControl->GetAnimeMaisuu(cgCharaNumber,cgNumber);
			m_animeCount++;
			if (m_animeCount >= animeMaisuu * m_animeFrame)
			{
				m_animeCount = 0;
			}
		}
	}
	return -1;
}

void CCommonPrintCG::PrintSabunFade(CPicture* lpToPic)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (m_sabunFadeTime <= 1)
	{
		lpToPic->Blt(0,0,0,0,screenSizeX,screenSizeY,FALSE);
		return;
	}

	m_game->PrintSimpleWipe(m_sabunPic,lpToPic,m_sabunFadeCount,m_sabunFadeTime,m_sabunFade-1);
}

void CCommonPrintCG::LoadCG(BOOL oldFlag,int oldNumber)
{
	m_dragedFlag = FALSE;
	m_dragFlag = FALSE;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	m_scrollHoukouXSpecial = -1;
	m_scrollHoukouYSpecial = -1;


	int cgCharaNumber = 0;
	int cgNumber = 0;

	BOOL animeFlag = FALSE;
	if (m_cgDataControl != NULL)
	{
		cgCharaNumber = m_cgDataControl->GetCGCharaNumber();
		cgNumber = m_cgDataControl->GetCGNumber();
	}

	if (oldFlag)
	{
		cgNumber = oldNumber;
	}

	if (m_cgDataControl != NULL)
	{
//		cgCharaNumber = m_cgDataControl->GetCGCharaNumber();
//		cgNumber = m_cgDataControl->GetCGNumber();
		animeFlag = m_cgDataControl->CheckCGIsAnime(cgCharaNumber,cgNumber);
	}

	if (m_cgDataControl != NULL)
	{
//		cgCharaNumber = m_cgDataControl->GetCGCharaNumber();
//		cgNumber = m_cgDataControl->GetCGNumber();

		m_scrollHoukouXSpecial = m_cgDataControl->GetCGScrollSpecial(0,cgCharaNumber,cgNumber);
		m_scrollHoukouYSpecial = m_cgDataControl->GetCGScrollSpecial(1,cgCharaNumber,cgNumber);
	}

	//CGが複数枚で構成されているかチェックする
	m_maisuuX = 1;
	m_maisuuY = 1;

	if (m_scrollHoukouXSpecial != -1)
	{
		if (m_cgDataControl != NULL)
		{
//			cgCharaNumber = m_cgDataControl->GetCGCharaNumber();
//			cgNumber = m_cgDataControl->GetCGNumber();

			m_maisuuX = m_cgDataControl->GetCGScrollSpecial(2,cgCharaNumber,cgNumber);
		}
//		m_maisuuX = 1;
	}

	if (m_scrollHoukouYSpecial != -1)
	{
		if (m_cgDataControl != NULL)
		{
//			cgCharaNumber = m_cgDataControl->GetCGCharaNumber();
//			cgNumber = m_cgDataControl->GetCGNumber();

			m_maisuuY = m_cgDataControl->GetCGScrollSpecial(3,cgCharaNumber,cgNumber);
		}
//		m_maisuuY = 1;
	}

	if (animeFlag)
	{
		m_maisuuX = 1;
		m_maisuuY = 1;
	}


	int maisuu = m_maisuuX * m_maisuuY;


	if (m_cgDataControl != NULL)
	{
		LPSTR cgName = m_cgDataControl->GetCGFileName(cgCharaNumber,cgNumber);
		if (cgName != NULL)
		{
			char fname[256];
			if (animeFlag)
			{
				int animeStart = m_cgDataControl->GetAnimeStart(cgCharaNumber,cgNumber);
				int animeMaisuu = m_cgDataControl->GetAnimeMaisuu(cgCharaNumber,cgNumber);

				LPSTR tag = m_game->GetAnimeTag();

				for (int i=0;i<animeMaisuu;i++)
				{
					CPicture* lpPic = m_game->GetAnimeBuffer(i);
					if (oldFlag)
					{
						lpPic = m_sabunPic;
					}

					wsprintf(fname,"%s%d",tag,animeStart+i);
			//		fname[0] = *tag;
			//		fname[1] = *(tag+1);
					BOOL b256 = CEffectAnimation::Check256();
					if (lpPic != NULL) lpPic->LoadDWQ(fname,b256);
				}
				m_taFlag[0] = FALSE;
			}
			else
			{
				for (int i=0;i<maisuu;i++)
				{
					if (i == 0)
					{
						wsprintf(fname,"__\\%s",cgName);
						fname[0] = *cgName;
						fname[1] = *(cgName+1);

						CPicture* lpPic = m_game->GetEffectPicture(i);
						if (oldFlag)
						{
							lpPic = m_sabunPic;
						}
						lpPic->LoadDWQ(fname);
		//				m_commonBG->LoadDWQ(fname);
					}
					else
					{
						wsprintf(fname,"__\\%s_%d",cgName,i+1);
						fname[0] = *cgName;
						fname[1] = *(cgName+1);

		//				CPicture* lpPic = m_game->GetEffectPicture(i-1);
						CPicture* lpPic = m_game->GetEffectPicture(i);
						lpPic->LoadDWQ(fname);
					}

					fname[2] = 0;
					fname[3] = 0;
				
					if (_stricmp(fname,"ta") == 0)
					{
						m_taFlag[i] = TRUE;
					}
					else
					{
						m_taFlag[i] = FALSE;
					}
				}
			}
		}
	}


	//m_commonBG->GetPicSize(&m_picRect);
	CPicture* lpPicBG = m_game->GetEffectPicture(0);
	if (animeFlag)
	{
		CPicture* lpPic = m_game->GetAnimeBuffer(0);
		if (oldFlag)
		{
			lpPic = m_sabunPic;
		}
		if (lpPic != NULL)
		{
			lpPic->GetPicSize(&m_picRect);
		}
		else
		{

			SetRect(&m_picRect,0,0,screenSizeX,screenSizeY);//dummy
		}
	}
	else
	{
		if (oldFlag)
		{
			lpPicBG = m_sabunPic;
		}
		lpPicBG->GetPicSize(&m_picRect);
	}

	int picX = m_picRect.right;
	int picY = m_picRect.bottom;

	if (m_maisuuX > 1)
	{
		for (int i=1;i<m_maisuuX;i++)
		{
			//int n = i - 1;
			int n = i;
			CPicture* lpPic = m_game->GetEffectPicture(n);
			SIZE sz = lpPic->GetPicSize();
			picX += sz.cx;
		}
	}

	if (m_maisuuY > 1)
	{
		for (int j=1;j<m_maisuuY;j++)
		{
			//int n = j * m_maisuuX - 1;
			int n = j * m_maisuuX;

			CPicture* lpPic = m_game->GetEffectPicture(n);
			SIZE sz = lpPic->GetPicSize();
			picY += sz.cy;
		}
	}

	m_picRect.right = picX;
	m_picRect.bottom = picY;


	m_scrollTimeX = m_scrollTimeBaseX;
	m_scrollTimeY = m_scrollTimeBaseY;
	m_scrollFirstWaitX = m_scrollFirstWaitBaseX;
	m_scrollFirstWaitY = m_scrollFirstWaitBaseY;

	if (m_cgDataControl != NULL)
	{
		int newTimeX = m_cgDataControl->GetCGScrollSpecial(4,cgCharaNumber,cgNumber);
		int newTimeY = m_cgDataControl->GetCGScrollSpecial(5,cgCharaNumber,cgNumber);
		int newWaitX = m_cgDataControl->GetCGScrollSpecial(6,cgCharaNumber,cgNumber);
		int newWaitY = m_cgDataControl->GetCGScrollSpecial(7,cgCharaNumber,cgNumber);

		if (newTimeX >= 1)
		{
			m_scrollTimeX = newTimeX;
		}
		if (newTimeY >= 1)
		{
			m_scrollTimeY = newTimeY;
		}
		if (newWaitX >= 0)
		{
			m_scrollFirstWaitX = newWaitX;
		}
		if (newWaitY >= 0)
		{
			m_scrollFirstWaitY = newWaitY;
		}
	}

	if (m_picRect.right <= screenSizeX)
	{
		m_scrollFlagX = FALSE;
		m_scrollCountX = 0;
	}
	else
	{
		m_scrollFlagX = TRUE;
		m_scrollCountX = m_scrollTimeX + m_scrollFirstWaitX;
	}

	if (m_picRect.bottom <= screenSizeY)
	{
		m_scrollFlagY = FALSE;
		m_scrollCountY = 0;
	}
	else
	{
		m_scrollFlagY = TRUE;
		m_scrollCountY = m_scrollTimeY + m_scrollFirstWaitY;
	}


	if (m_taBGFlag)
	{
		BOOL flg = FALSE;
		for (int t=0;t<maisuu;t++)
		{
			if (m_taFlag[t]) flg = TRUE;
		}

		if (flg)
		{
			char filename[256];
			if (m_taBGFlag == 2)
			{
		//		int cgChara = 0;
		//		if (m_cgDataControl != NULL)
		//		{
				//	cgChara = m_cgDataControl->GetCGCharaNumber();
		//		}

				wsprintf(filename,"bg\\%s",m_taBGCharaFileName[cgCharaNumber]);
			}
			else
			{
				wsprintf(filename,"bg\\%s",m_taBGFileName);
			}

			m_commonBG->LoadDWQ(filename);
		}
	}
}






void CCommonPrintCG::CreateEnterScreen(void)
{
	//LoadCGは実行されている
//	CreateStartScreen();

	BOOL animeFlag = FALSE;

	if (m_cgDataControl != NULL)
	{
		int cgCharaNumber = m_cgDataControl->GetCGCharaNumber();
		int cgNumber = m_cgDataControl->GetCGNumber();
		animeFlag = m_cgDataControl->CheckCGIsAnime(cgCharaNumber,cgNumber);
		if (animeFlag) CAreaControl::SetNextAllPrint();
	}


	BOOL b = CAreaControl::CheckAllPrintMode();

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int divX = m_scrollTimeX;
	int mulX = m_scrollCountX;
	if (mulX >= m_scrollTimeX) mulX = divX;

	if (m_scrollHoukouXSpecial != -1)
	{
		if (m_scrollHoukouXSpecial == 1) mulX = divX - mulX;
	}
	else
	{
		if (m_scrollHoukouX) mulX = divX - mulX;
	}

	int scrollSizeX = m_picRect.right - screenSizeX;
	int dx = (scrollSizeX * mulX) / divX;


	int divY = m_scrollTimeY;
	int mulY = m_scrollCountY;
	if (mulY >= m_scrollTimeY) mulY = divY;
	if (m_scrollHoukouYSpecial != -1)
	{
		if (m_scrollHoukouYSpecial == 1) mulY = divY - mulY;
	}
	else
	{
		if (m_scrollHoukouY) mulY = divY - mulY;
	}

	int scrollSizeY = m_picRect.bottom - screenSizeY;
	int dy = (scrollSizeY * mulY) / divY;


//	m_commonBG->Blt(0,0,dx,dy,screenSizeX,screenSizeY,FALSE);

//	SIZE sz = m_commonBG->GetPicSize();
	CPicture* lpPicBG = m_game->GetEffectPicture(0);
	SIZE sz = lpPicBG->GetPicSize();

	int maisuu = m_maisuuX * m_maisuuY;
	if (maisuu > 0)
	{
		if (animeFlag)
		{
			CPicture* lpPic = m_game->GetAnimeBuffer(0);
			if (lpPic != NULL) lpPic->Put(0,0,FALSE);
		}
		else
		{
			CheckAndEraseBG();

			for (int j=0;j<m_maisuuY;j++)
			{
				for (int i=0;i<m_maisuuX;i++)
				{
	//				CPicture* lpPic = m_commonBG;
					int n = i + j * m_maisuuX;
					CPicture* lpPic = m_game->GetEffectPicture(n);
					lpPic->Blt(i*sz.cx-dx,j*sz.cy-dy,0,0,sz.cx,sz.cy,m_taFlag[n]);
				}
			}
		}
	}


	m_enterScreen->GetScreen();

	//必要ならexitScreenぬりつぶし
	if (m_enterFadeInType == 1)
	{
		FillPicture(m_exitScreen,m_enterFadeInColorR,m_enterFadeInColorG,m_enterFadeInColorB);
	}
}



void CCommonPrintCG::CheckAndEraseBG(void)
{
	int maisuu = m_maisuuX * m_maisuuY;
	BOOL flg = FALSE;
	for (int i=0;i<maisuu;i++)
	{
		if (m_taFlag[i]) flg = TRUE;
	}

	if (flg == FALSE) return;

	if (m_taBGFlag)
	{
		m_commonBG->Put(0,0,FALSE);
	}
	else
	{
		CAllGraphics::FillScreen(m_taBGColorR,m_taBGColorG,m_taBGColorB);
	}



}



void CCommonPrintCG::ClearLastCGVoice(void)
{
	m_cgVoiceFileName[0] = 0;
	m_cgVoicePlayedFlag = FALSE;

}

void CCommonPrintCG::ChangeCGVoice(void)
{
	int cgCharaNumber = m_cgDataControl->GetCGCharaNumber();
	int cgNumber = m_cgDataControl->GetCGNumber();

	LPSTR voice = m_cgVoice->GetVoice(cgCharaNumber,cgNumber);
	if (voice != NULL)
	{
		if (_stricmp(m_cgVoiceFileName,voice) != 0)
		{
			memcpy(m_cgVoiceFileName,voice,strlen(voice)+1);
			m_cgVoicePlayedFlag = FALSE;
			m_cgVoiceCount = m_cgVoiceWaitTime;
		}
	}
}

void CCommonPrintCG::CheckAndPlayCGVoice(void)
{
	if (m_cgVoiceFileName[0] == 0) return;
	if (m_cgVoiceCount > 0)
	{
		m_cgVoiceCount--;
		if (m_cgVoiceCount <= 0)
		{
			//play!
			if (m_cgVoiceFileName[0] != '-')
			{
				m_game->ReplayVoice(m_cgVoiceFileName);
			}
			else
			{
				m_game->StopScriptSoundAndVoice();
			}

			m_cgVoicePlayedFlag = TRUE;
		}
	}
}

