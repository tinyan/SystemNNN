//
// commonSelectCG.cpp
//


#include <windows.h>

#include <stdio.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"

#include "..\nyanLib\include\allGeo.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"

#include "..\nnnUtilLib\nnnButtonStatus.h"
#include "commonSystemSoundName.h"

#include "..\nnnUtilLib\commonButton.h"
#include "..\nnnUtilLib\commonBackButton.h"
#include "..\nnnUtilLib\commonupDownButtonGroup.h"
#include "..\nnnUtilLib\commonUpDownBack.h"
#include "..\nnnUtilLib\suuji.h"

#include "..\nnnUtilLib\pagePrint.h"

#include "..\nnnUtilLib\cgDataControl.h"

#include "commonMode.h"
#include "commonSystemParamName.h"

#include "gameCallBack.h"

#include "commonGeneral.h"
#include "commonSelectCG.h"





char CCommonSelectCG::m_defaultBGFileName[] = "cg_bg";
char CCommonSelectCG::m_defaultAddFileName[] = "cgbg_title";

char CCommonSelectCG::m_defaultFutaFileName[] = "ta_futa1";
char CCommonSelectCG::m_defaultAnimeFileName[] = "ta_futa1";
char CCommonSelectCG::m_defaultFont1FileName[] = "ta_font_cg1";
char CCommonSelectCG::m_defaultFont2FileName[] = "ta_sl_font3";
char CCommonSelectCG::m_defaultFont3FileName[] = "ta_sl_font3";
char CCommonSelectCG::m_defaultCursorFileName[] = "ta_cg_cur";

//char CCommonSelectCG::m_defaultUpFileName[] = "ta_bgm_cur1";
//char CCommonSelectCG::m_defaultDownFileName[] = "ta_bgm_cur2";

CCommonSelectCG::CCommonSelectCG(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(SELECTCG_MODE);
//	m_classNumber = SELECTCG_MODE;

	LoadSetupFile("SelectCG",256);
	m_cgDataControl = m_game->GetCGDataControl();


	m_cgCharaKosuu = 1;
	if (m_cgDataControl != NULL)
	{
		m_cgCharaKosuu = m_cgDataControl->GetCGCharaKosuu();
	}

	GetBackExecSetup();

	m_cgPianoSoundFlag = 0;
	GetInitGameParam(&m_cgPianoSoundFlag,"cgPianoSoundFlag");

	m_superMode = 0;
	GetInitGameParam(&m_superMode,"superButtonFlag");

	m_filenameBG = m_defaultBGFileName;
	GetInitGameString(&m_filenameBG,"filenameBG");

	m_blockKosuuX = 4;
	m_blockKosuuY = 3;

	GetInitGameParam(&m_blockKosuuX,"blockNumberX");
	GetInitGameParam(&m_blockKosuuY,"blockNumberY");

	m_picMustPrintPercent = 0;
	GetInitGameParam(&m_picMustPrintPercent,"picMustPrintPercent");


	m_filenameAdd = m_defaultAddFileName;
	m_addPicFlag = 0;
	m_addPicPrintPercent = 0;	//特例:0はマスクなし100% それ以外はマスクあり透過
	m_addPicPrintX = 217;
	m_addPicPrintY = 26;
	m_addPicSizeX = 355;
	m_addPicSizeY = 22;
	m_addPicSrcKosuuX = 1;
	m_addPicSrcKosuuY = m_cgCharaKosuu;


	GetInitGameParam(&m_addPicFlag,"addPicFlag");
	m_addPic = NULL;
	if (m_addPicFlag != 0)
	{
		GetInitGameParam(&m_addPicPrintPercent,"addPicPrintPercent");
		GetInitGameParam(&m_addPicPrintX,"addPicPrintX");
		GetInitGameParam(&m_addPicPrintY,"addPicPrintY");
		GetInitGameParam(&m_addPicSizeX,"addPicSizeX");
		GetInitGameParam(&m_addPicSizeY,"addPicSizeY");
		GetInitGameParam(&m_addPicSrcKosuuX,"addPicSrcNumX");
		GetInitGameParam(&m_addPicSrcKosuuY,"addPicSrcNumY");
		GetInitGameString(&m_filenameAdd,"filenameAdd");
		m_addPic = new CPicture();
		char filename[256];
		wsprintf(filename,"sys\\%s",m_filenameAdd);
		m_addPic->LoadDWQ(filename);
	}

	m_menuStartWaitTime = 0;
	m_menuStartEffectTime = 0;
	m_menuStartEffectType = 0;

	GetInitGameParam(&m_menuStartWaitTime, "menuStartWaitTime");
	GetInitGameParam(&m_menuStartEffectTime, "menuStartEffectTime");
	GetInitGameParam(&m_menuStartEffectType, "menuStartEffectType");


	m_miniPic = new CPicture*[m_blockKosuuX*m_blockKosuuY];
	int i = 0;
	for (i=0;i<m_blockKosuuX*m_blockKosuuY;i++)
	{
		m_miniPic[i] = new CPicture();
	}

	m_miniPicState = new int[m_blockKosuuX*m_blockKosuuY];
	m_animeFlag = new int[m_blockKosuuX*m_blockKosuuY];

	m_miniPicTransFlag = 0;
	GetInitGameParam(&m_miniPicTransFlag,"miniPicTransFlag");

	m_printX = 85;
	m_printY = 113;
	m_nextX = 166;
	m_nextY = 124;
	m_sizeX = 133;
	m_sizeY = 100;

	m_picPrintX = 0;
	m_picPrintY = 0;


	GetInitGameParam(&m_printX,"printX");
	GetInitGameParam(&m_printY,"printY");
	GetInitGameParam(&m_nextX,"nextX");
	GetInitGameParam(&m_nextY,"nextY");
	GetInitGameParam(&m_sizeX,"sizeX");
	GetInitGameParam(&m_sizeY,"sizeY");

	m_picSizeX = m_sizeX;
	m_picSizeY = m_sizeY;

	GetInitGameParam(&m_picPrintX,"picPrintX");
	GetInitGameParam(&m_picPrintY,"picPrintY");

	GetInitGameParam(&m_picSizeX,"picSizeX");
	GetInitGameParam(&m_picSizeY,"picSizeY");



	m_cursorSizeX = m_picSizeX;
	m_cursorSizeY = m_picSizeY;
	m_cursorPrintX = m_picPrintX;
	m_cursorPrintY = m_picPrintY;

	GetInitGameParam(&m_cursorPrintX,"cursorPrintX");
	GetInitGameParam(&m_cursorPrintY,"cursorPrintY");
	GetInitGameParam(&m_cursorSizeX,"cursorSizeX");
	GetInitGameParam(&m_cursorSizeY,"cursorSizeY");


	m_goreIconFileTag = NULL;
	m_useGoreSMFileTag = 0;
	m_useGoreIcon = 0;
	m_goreIcon = NULL;
	if (m_game->GetUseGoreFlag())
	{
		m_goreIconPrintX = 0;
		m_goreIconPrintY = 0;
		GetInitGameParam(&m_goreIconPrintX, "goreIconPrintX");
		GetInitGameParam(&m_goreIconPrintY, "goreIconPrintY");
		GetInitGameParam(&m_useGoreIcon, "useGoreIcon");
		GetInitGameParam(&m_useGoreSMFileTag, "useGoreSMFileTag");

		if (m_useGoreIcon)
		{
			LPSTR goreIconFileName = "";
			if (GetInitGameString(&goreIconFileName,"filenameGoreIcon"))
			{
				m_goreIcon = m_game->GetSystemPicture(goreIconFileName);
			}
		}

		if (m_useGoreSMFileTag)
		{
			GetInitGameString(&m_goreIconFileTag, "goreIconFileTag");
		}
	}


	m_cgKosuu = new int[m_cgCharaKosuu+1];
	m_blockSabunKosuu = new int[m_cgCharaKosuu+1];
	m_blockSabunStart = new int*[m_cgCharaKosuu+1];

	int maxCGKosuuPerChara = 0;
	for (i=0;i<m_cgCharaKosuu;i++)
	{
		m_cgKosuu[i] = 1;
		if (m_cgDataControl != NULL)
		{
			m_cgKosuu[i] = m_cgDataControl->GetCGKosuu(i);
		}

		if (m_cgKosuu[i] > maxCGKosuuPerChara) maxCGKosuuPerChara = m_cgKosuu[i];
		int block = 0;
		m_blockSabunStart[i] = new int[m_cgKosuu[i] + 1];

		BOOL lastFlag = FALSE;

		for (int k=0;k<m_cgKosuu[i];k++)
		{
			if (m_cgDataControl != NULL)
			{
				LPSTR name = m_cgDataControl->GetCGFileName(i,k,FALSE);
				if (*name == '*')
				{
					name++;
				}

				if ((*name) != '@')
				{
					m_blockSabunStart[i][block] = k;
					block++;
				}
			}
		}

		m_blockSabunStart[i][block] = m_cgKosuu[i];
		m_blockSabunKosuu[i] = block;
	}
	m_cgFlag = new BOOL[maxCGKosuuPerChara];
	m_blockGetKosuu = new int[maxCGKosuuPerChara];

	m_back = m_game->GetBackButton();



	LPSTR futaName = m_defaultFutaFileName;
	GetInitGameString(&futaName,"fileNameFuta");

	m_futaPrintFlag = 1;
	GetInitGameParam(&m_futaPrintFlag,"futaPrintFlag");
	if (m_futaPrintFlag)
	{ 
		m_futaPic = m_game->GetSystemPicture(futaName);
	}

	LPSTR animeName = m_defaultAnimeFileName;
	GetInitGameString(&animeName,"fileNameAnime");

	m_animePrintFlag = 0;
	GetInitGameParam(&m_animePrintFlag,"animePrintFlag");
	if (m_animePrintFlag)
	{ 
		m_animePic = m_game->GetSystemPicture(animeName);
	}


	m_selectPrintMode = 1;
	GetInitGameParam(&m_selectPrintMode,"selectPrintMode");

	m_selectPercent = 50;
	GetInitGameParam(&m_selectPercent,"selectPercent");

	if (m_selectPrintMode == 1)
	{
		m_selectColorR = 230;
		m_selectColorG = 0;
		m_selectColorB = 50;

		GetInitGameParam(&m_selectColorR,"cursorColorR");
		GetInitGameParam(&m_selectColorG,"cursorColorG");
		GetInitGameParam(&m_selectColorB,"cursorColorB");
	}
	else if (m_selectPrintMode == 2)
	{
		LPSTR cursorName = m_defaultCursorFileName;
		GetInitGameString(&cursorName,"fileNameCursor");
		m_cursorPic = m_game->GetSystemPicture(cursorName);

		m_cursorPrintType = 0;
		GetInitGameParam(&m_cursorPrintType,"cursorPrintType");
	}



	m_totalPercentPrintFlag = 1;
	GetInitGameParam(&m_totalPercentPrintFlag,"totalPercentPrintFlag");
	m_suuji = NULL;
	if (m_totalPercentPrintFlag)
	{
		LPSTR font1Name = m_defaultFont1FileName;
		GetInitGameString(&font1Name,"fileNameTotalPercent");
		CPicture* suujiPic = m_game->GetSystemPicture(font1Name);

		m_fontSizeX1 = 16;
		m_fontSizeY1 = 22;
		GetInitGameParam(&m_fontSizeX1,"totalPercentFontSizeX");
		GetInitGameParam(&m_fontSizeY1,"totalPercentFontSizeY");
		m_fontNextX1 = m_fontSizeX1;
		GetInitGameParam(&m_fontNextX1,"totalPercentFontNextX");

		m_totalPercentPrintX = 688;
		m_totalPercentPrintY = 25;
		GetInitGameParam(&m_totalPercentPrintX,"totalPercentPrintX");
		GetInitGameParam(&m_totalPercentPrintY,"totalPercentPrintY");

		m_suuji = new CSuuji(suujiPic,m_fontSizeX1,m_fontSizeY1,3,m_fontNextX1);
	}

	m_sabunPrintFlag = 1;
	GetInitGameParam(&m_sabunPrintFlag,"differencePrintFlag");

	m_suuji2 = NULL;

	m_sabunPrintByGetFlag = 0;

	if (m_sabunPrintFlag)
	{
		GetInitGameParam(&m_sabunPrintByGetFlag,"differencePrintByGetFlag");

		m_fontSizeX2 = 21;
		m_fontSizeY2 = 27;
		GetInitGameParam(&m_fontSizeX2,"differenceFontSizeX");
		GetInitGameParam(&m_fontSizeY2,"differenceFontSizeY");
		m_fontNextX2 = m_fontSizeX2;
		GetInitGameParam(&m_fontNextX2,"differenceFontNextX");

		m_differencePrintX = 0;
		m_differencePrintY = 0;

		GetInitGameParam(&m_differencePrintX,"differencePrintX");
		GetInitGameParam(&m_differencePrintY,"differencePrintY");

		LPSTR font2Name = m_defaultFont2FileName;
		GetInitGameString(&font2Name,"fileNameDifferenceFont");
		CPicture* suujiPic2 = m_game->GetSystemPicture(font2Name);
		m_differentKeta = 2;
		GetInitGameParam(&m_differentKeta, "differentKeta");
		m_suuji2 = new CSuuji(suujiPic2,m_fontSizeX2,m_fontSizeY2, m_differentKeta,m_fontNextX2);
	}


	CPicture* lpBG = m_commonBG;
	if (m_backScriptFlag) lpBG = NULL;

	m_pagePrint = new CPagePrint(m_setup,lpBG);


//	m_pagePrintFlag = 0;
//	GetInitGameParam(&m_pagePrintFlag,"pagePrintFlag");
//	m_suuji3 = NULL;
/*
	m_pagePrintX = 0;
	m_pagePrintY = 0;

	m_pageMaxPrintFlag = 0;
	m_slashPrintFlag = 0;

	if (m_pagePrintFlag)
	{
		int keta = 2;

		m_fontSizeX3 = 21;
		m_fontSizeY3 = 27;

		GetInitGameParam(&m_fontSizeX3,"pageFontSizeX");
		GetInitGameParam(&m_fontSizeY3,"pageFontSizeY");
		m_fontNextX3 = m_fontSizeX3;
		GetInitGameParam(&m_fontNextX3,"pageFontNextX");

		GetInitGameParam(&m_pagePrintX,"pagePrintX");
		GetInitGameParam(&m_pagePrintY,"pagePrintY");

		LPSTR font3Name = m_defaultFont3FileName;
		GetInitGameString(&font3Name,"fileNamePageFont");
		CPicture* suujiPic3 = m_game->GetSystemPicture(font3Name);
		m_suujiPic3 = suujiPic3;
		m_suuji3 = new CSuuji(suujiPic3,m_fontSizeX3,m_fontSizeY3,keta,m_fontNextX3);



		GetInitGameParam(&m_pageMaxPrintFlag,"pageMaxPrintFlag");

		if (m_pageMaxPrintFlag)
		{
			m_pageMaxPrintX = m_pagePrintX + m_fontNextX3 * (keta+1);
			m_pageMaxPrintY = m_pagePrintY;

			GetInitGameParam(&m_pageMaxPrintX,"pageMaxPrintX");
			GetInitGameParam(&m_pageMaxPrintY,"pageMaxPrintY");

			GetInitGameParam(&m_slashPrintFlag,"slashPrintFlag");
			if (m_slashPrintFlag)
			{
				m_slashPrintX = m_pagePrintX + m_fontNextX3 * keta;
				m_slashPrintY = m_pagePrintY;

				GetInitGameParam(&m_slashPrintX,"slashPrintX");
				GetInitGameParam(&m_slashPrintY,"slashPrintY");
			}
		}
	}
*/

	m_length = 8;
	m_selectedNumber = -1;

	m_selectSound = 1;
	GetInitGameParam(&m_selectSound,"selectSound");
	CreateBackButton();
	CreateUpDownButton();
	CreateUpDownBack();

	GetBGMSetup();
	GetFadeInOutSetup();
	GetEnterExitVoiceFileName();
}


CCommonSelectCG::~CCommonSelectCG()
{
	End();
}

void CCommonSelectCG::End(void)
{
	ENDDELETECLASS(m_pagePrint);

	DELETEARRAY(m_animeFlag);
	DELETEARRAY(m_miniPicState);
	if (m_miniPic != NULL)
	{
		for (int i=0;i<m_blockKosuuX*m_blockKosuuY;i++)
		{
			ENDDELETECLASS(m_miniPic[i]);
		}
		DELETEARRAY(m_miniPic);
	}


	ENDDELETECLASS(m_addPic);
	DELETEARRAY(m_blockGetKosuu);
	DELETEARRAY(m_cgFlag);
	DELETEARRAY(m_cgKosuu);

//	ENDDELETECLASS(m_updown);

	if (m_blockSabunStart != NULL)
	{
		for (int i=0;i<m_cgCharaKosuu;i++)
		{
			DELETEARRAY(m_blockSabunStart[i]);
		}
		DELETEARRAY(m_blockSabunStart);
	}

	DELETEARRAY(m_blockSabunKosuu);
//	ENDDELETECLASS(m_suuji3);
	ENDDELETECLASS(m_suuji2);
	ENDDELETECLASS(m_suuji);
}



int CCommonSelectCG::Init(void)
{
	m_appearCount = 1;
	m_appearCountMax = 1;

	//	if (!m_initStartWait)
	{
		m_menuStartCount = 0;
	}


	m_cgCharaNumber = 0;
	m_cgNumber = 0;

	if (m_cgDataControl != NULL)
	{
		m_cgCharaNumber = m_cgDataControl->GetCGCharaNumber();
		m_cgNumber = m_cgDataControl->GetCGNumber();
	}


	m_game->StopScriptSoundAndVoice();

	m_game->SetDefaultFrameRate();

	int kosuu = m_blockSabunKosuu[m_cgCharaNumber];

	if (kosuu<1) kosuu = 1;	//dummy data のときとばないように

	//どのぶろっくか?
	int blockSabunKosuu = 0;
	if (m_cgCharaKosuu > 0)
	{
		blockSabunKosuu = m_blockSabunKosuu[m_cgCharaNumber];
	}

	int block = 0;

	int i = 0;
	for (i=0;i<blockSabunKosuu;i++)
	{
		int from = m_blockSabunStart[m_cgCharaNumber][i];
		int to = m_blockSabunStart[m_cgCharaNumber][i+1];
		if ((m_cgNumber >= from) && (m_cgNumber < to))
		{
			block = i;
			break;
		}
	}

	m_page = block / (m_blockKosuuX * m_blockKosuuY);
	m_pageMax = ((blockSabunKosuu-1) / (m_blockKosuuX * m_blockKosuuY)) + 1;

	SetUpDownZahyo();
	m_updown->SetPageMax(m_pageMax);
	m_updown->SetPage(m_page);


	m_startupWait = 3;

	int cgKosuu = m_cgKosuu[m_cgCharaNumber];
	int cgKosuuDiv = cgKosuu;
	if (cgKosuuDiv<1) cgKosuuDiv = 1;

//	if (cgKosuu<1) cgKosuu = 1;	//for nodata (by debug time)
	int getKosuu = 0;

	for (i=0;i<cgKosuu;i++)
	{
		int fl = 0;
		if (m_cgDataControl != NULL)
		{
			fl = m_cgDataControl->CheckGetCG(m_cgCharaNumber,i);
		}

//		if (m_game->CheckGetCG(m_cgCharaNumber,i))
		if (fl)
		{
			m_cgFlag[i] = TRUE;
			getKosuu++;
		}
		else
		{
			m_cgFlag[i] = FALSE;
		}
	}

	int ps = (getKosuu * 100) / cgKosuuDiv;
	if (ps<0) ps = 0;
	if (ps >= 100) ps = 100;

	if (ps == 0)
	{
		if (getKosuu>0) ps = 1;
	}

	if (ps == 100)
	{
		if (getKosuu < cgKosuu) ps = 99;
	}

	m_percent = ps;

	for (i=0;i<blockSabunKosuu;i++)
	{
		int from = m_blockSabunStart[m_cgCharaNumber][i];
		int to = m_blockSabunStart[m_cgCharaNumber][i+1];
		int getKosuu = 0;
		for (int k=from;k<to;k++)
		{
			if (m_cgFlag[k]) getKosuu++;
		}

		m_blockGetKosuu[i] = getKosuu;
	}



	LoadBackCG();

	
	LoadUpDownButtonPic();
	LoadBackButtonPic();

//	m_updown->Init();



	m_nowSelectNumber = -1;
	m_maeSelectNumber = -1;


//	m_back->Init();
	m_updownBack->Init();

	SetBackButtonZahyo();

	m_selectedNumber = -1;


	return -1;
}



int CCommonSelectCG::Calcu(void)
{

	int startMode = GetStartWaitMode();
	if (startMode != 0)
	{
		m_menuStartCount++;
		if (m_menuStartCount >= m_menuStartWaitTime + m_menuStartEffectTime)
		{
			EndStartWaitMode();
		}
		else
		{
			if (m_mouseStatus->CheckClick()) EndStartWaitMode();
			if (m_mouseStatus->CheckClick(1)) EndStartWaitMode();
		}

		return -1;
	}


	POINT pt = m_mouseStatus->GetZahyo();
	int mouseX = pt.x;
	int mouseY = pt.y;

//	if (m_selectedNumber >= 0)
	if ((m_selectedNumber != -1) && (m_selectedNumber != -2))
	{
		m_count--;
		if (m_count<=0)
		{
//			if (m_selectedNumber == -2)
//			{
//				return ReturnFadeOut(m_backMode);
//			}

			int block = m_page * (m_blockKosuuX * m_blockKosuuY) + m_selectedNumber;

			int from = m_blockSabunStart[m_cgCharaNumber][block];
			int to = m_blockSabunStart[m_cgCharaNumber][block+1];

			int found = from;

			for (int k=from;k<to;k++)
			{
				if (m_cgFlag[k])
				{
					found = k;
					break;
				}
			}

			m_game->SetDefaultFrameRate();
			if (m_cgDataControl != NULL)
			{
				m_cgDataControl->SetCGNumber(found);
			}
			return ReturnFadeOut(PRINTCG_MODE);
		}
		return -1;
	}

	int rt = m_updownBack->Calcu(m_inputStatus);

	if (rt != NNNBUTTON_NOTHING)
	{
		//sound
		int nm = ProcessUpDownBack(rt);
		if (nm >= 0)
		{
			if (nm == 0)
			{
				return ReturnFadeOut(m_backMode);
			}

			m_selectedNumber = -1;
			if (nm > 0)
			{
				m_page = nm - 1;

				m_startupWait = 3;
				LoadBackCG();
				CAreaControl::SetNextAllPrint();
				return -1;
			}
		}

		int st = CCommonButton::GetButtonStatus(rt);
		if (st == NNNBUTTON_STARTCLICK)
		{
			int nm = CCommonButton::GetButtonData(rt);
			 m_selectedNumber = -2;
		}
	}

//	if (st == NNNBUTTON_NUMBER)
//	{
//		return ReturnFadeOut(m_backMode);
//	}

//	if (udst == NNNBUTTON_NUMBER)
//	{
//		m_page = udnm;
//		m_updown->Init();
//		if (m_superMode == 0)
//		{
//			m_game->PlayCommonSystemSound(COMMON_SYSTEMSOUND_PON);
//		}
//
//		m_selectedNumber = -1;
//		m_startupWait = 3;
//		LoadBackCG();
//		CAreaControl::SetNextAllPrint();
//		return -1;
//	}

	m_maeSelectNumber = m_nowSelectNumber;
	m_nowSelectNumber = GetOnCG(mouseX,mouseY);

	if (m_mouseStatus->CheckClick())
	{
		if (m_nowSelectNumber != -1)
		{
			m_selectedNumber = m_nowSelectNumber;
			m_count = m_length;
			if (m_selectSound != -1)
			{
				m_game->PlaySystemSound(m_selectSound-1);
			}
			//m_game->PlayCommonSystemSound(COMMON_SYSTEMSOUND_OK2);
			return -1;
		}
	}

	if (m_startupWait>0)
	{
		m_startupWait--;
	}
	else
	{
		if ((m_nowSelectNumber != m_maeSelectNumber) && (m_nowSelectNumber != -1))
		{
			if (m_cgPianoSoundFlag)
			{
				m_game->PlaySystemPiano(m_nowSelectNumber);
			}
		}
	}

	return -1;
}


int CCommonSelectCG::Print(void)
{
	PrintBackScriptOrBG();


	BOOL b = CAreaControl::CheckAllPrintMode();

	int startMode = GetStartWaitMode();

	int dva = m_appearCountMax;
	if (dva < 1) dva = 1;

	int appearPercent = 100;
	if (m_menuStartEffectType & 1)
	{
		appearPercent = (100 * m_appearCount) / dva;
		if (appearPercent < 0) appearPercent = 0;
		if (appearPercent > 100) appearPercent = 100;
	}




	if (m_backScriptFlag)
	{
		PrintAllMiniPic();

		if (m_addPicFlag) PrintAddPic();
		//m_pagePrint->Print(m_page+1,m_pageMax);
		m_pagePrint->AppearPrint(m_appearCount, m_appearCountMax, m_menuStartEffectType,m_page + 1, m_pageMax);
		//		if (m_pagePrintFlag) PrintPage();
		if (m_totalPercentPrintFlag) PrintTotalPercent();
	}


//	m_updownBack->Print(TRUE);
	m_updownBack->AppearPrint(m_appearCount, m_appearCountMax, m_menuStartEffectType);
//	m_back->Print(TRUE);
//	m_updown->Print(TRUE);

	bool bPutGoreIcon = FALSE;
	if (m_game->GetUseGoreFlag())
	{
		if (m_game->GetGoreFlag())
		{
			bPutGoreIcon = TRUE;
		}
	}

	for (int j=0;j<m_blockKosuuY;j++)
	{
		for (int i=0;i<m_blockKosuuX;i++)
		{
			int k = i + j * m_blockKosuuX;
			BOOL bb = b;
			if (m_nowSelectNumber != m_maeSelectNumber)
			{
				if ((k == m_nowSelectNumber) || (k == m_maeSelectNumber))
				{
					bb = TRUE;
				}
			}
		
			if (k == m_selectedNumber) bb = TRUE;

			if (bb)
			{
				int putX = m_printX + m_nextX * i;
				int putY = m_printY + m_nextY * j;
				int sizeX = m_sizeX;
				int sizeY = m_sizeY;

				int block = m_page * (m_blockKosuuX * m_blockKosuuY) + k;
				if (m_blockGetKosuu[block]>0)
				{
					if (m_backScriptFlag == 0)
					{
						m_commonBG->Blt(putX,putY,putX,putY,sizeX,sizeY,FALSE);
					}

					if ((k == m_nowSelectNumber) || (k == m_selectedNumber))
					{
						if ((m_selectedNumber == -1) || (m_count & 1))
						{
							int putX1 = putX + m_cursorPrintX;
							int putY1 = putY + m_cursorPrintY;
							int sizeX1 = m_cursorSizeX;
							int sizeY1 = m_cursorSizeY;

							if (m_selectPrintMode == 1)
							{
//								CAllGeo::TransBoxFill(putX1,putY1,sizeX1,sizeY1,m_selectColorR,m_selectColorG,m_selectColorB,m_selectPercent);
								CAllGeo::TransBoxFill(putX1, putY1, sizeX1, sizeY1, m_selectColorR, m_selectColorG, m_selectColorB, (m_selectPercent*appearPercent)/100);
							}
							else if (m_selectPrintMode == 2)
							{
								if (m_cursorPrintType == 0)
								{
//									m_cursorPic->Blt(putX1,putY1,0,0,sizeX1,sizeY1,TRUE);
									m_cursorPic->TransLucentBlt0(putX1, putY1, 0, 0, sizeX1, sizeY1, appearPercent);
								}
								else if (m_cursorPrintType == 1)
								{
									m_cursorPic->TransLucentBlt3(putX1,putY1,0,0,sizeX1,sizeY1,(m_selectPercent*appearPercent)/100);
								}
								else if (m_cursorPrintType == 2)
								{
									if (m_appearCount >= m_appearCountMax)
									{
										m_cursorPic->AddBlt(putX1, putY1, 0, 0, sizeX1, sizeY1);
									}
								}
//								m_cursorPic->Blt(putX,putY,0,0,sizeX,sizeY,TRUE);
							}
							
							if (bPutGoreIcon && m_cgDataControl->CheckGore(m_cgCharaNumber, block))
							{
								if (m_useGoreIcon)
								{
									if (m_goreIcon != NULL)
									{
										m_goreIcon->Put(putX1 + m_goreIconPrintX, putY1 + m_goreIconPrintY, TRUE);
									}
								}
							}

//							CPicture::TransBox(putX,putY,sizeX,sizeY,230,0,255,50);
//							m_cursorPic->AddBlt(putX-1,putY-1,0,0,135,101);
						}
					}

					if (b == FALSE)
					{
						CAreaControl::AddArea(putX,putY,sizeX,sizeY);
					}
				}
			}
		}
	}

	return 0;
}



void CCommonSelectCG::LoadBackCG(void)
{
	char filename[256];
	if (m_backScriptFlag == 0)
	{
		wsprintf(filename,"sys\\%s",m_filenameBG);
		m_commonBG->LoadDWQ(filename);
		m_commonBG->Put(0,0,FALSE);
	}


	bool bGore = FALSE;
	if (m_game->GetUseGoreFlag())
	{
		if (m_game->GetGoreFlag())
		{
			bGore = TRUE;
		}
	}


	for (int j=0;j<m_blockKosuuY;j++)
	{
		for (int i=0;i<m_blockKosuuX;i++)
		{
			int n0 = j * m_blockKosuuX + i;
			int block = m_page * (m_blockKosuuX * m_blockKosuuY) + n0;

			m_miniPicState[n0] = -1;
			m_animeFlag[n0] = FALSE;


			if (block < m_blockSabunKosuu[m_cgCharaNumber])
			{
				int from = m_blockSabunStart[m_cgCharaNumber][block];
				int to = m_blockSabunStart[m_cgCharaNumber][block+1];

				if (m_blockGetKosuu[block] <= 0)
				{
					m_miniPicState[n0] = 0;

					if (m_picMustPrintPercent != 0)
					{
						m_miniPicState[n0] = 1;
						if (m_cgDataControl != NULL)
						{
							LPSTR name = m_cgDataControl->GetCGFileName(m_cgCharaNumber,from);
							if (bGore && m_useGoreSMFileTag && m_cgDataControl->CheckGore(m_cgCharaNumber, from))
							{
								wsprintf(filename, "sys\\sm\\sm%s%s", name,m_goreIconFileTag);
							}
							else
							{
								wsprintf(filename, "sys\\sm\\sm%s", name);
							}
							m_miniPic[n0]->LoadDWQ(filename);
						}
					}
				}
				else
				{
					m_miniPicState[n0] = 0;

					int found = from;

					for (int k=from;k<to;k++)
					{
						if (m_cgFlag[k])
						{
							found = k;
							break;
						}
					}

					m_miniPicState[n0] = 2;

					if (m_cgDataControl != NULL)
					{
						LPSTR name = m_cgDataControl->GetCGFileName(m_cgCharaNumber,found);

						if (bGore && m_useGoreSMFileTag && m_cgDataControl->CheckGore(m_cgCharaNumber, found))
						{
							wsprintf(filename, "sys\\sm\\sm%s%s", name, m_goreIconFileTag);
						}
						else
						{
							wsprintf(filename, "sys\\sm\\sm%s", name);
						}
						m_miniPic[n0]->LoadDWQ(filename);
					}
				}

				if (m_cgDataControl->CheckCGIsAnime(m_cgCharaNumber,from))
				{
					m_animeFlag[n0] = TRUE;
				}
			}
		}
	}


	if (m_backScriptFlag == 0)
	{
		PrintAllMiniPic();

		//total percent
		if (m_totalPercentPrintFlag)
		{
			PrintTotalPercent();
		}

		//additional parts
		if (m_addPicFlag != 0)
		{
			PrintAddPic();
		}


		m_pagePrint->Print(m_page+1,m_pageMax);

		//page
//		if (m_pagePrintFlag)
//		{
//			PrintPage();
//		}


		m_commonBG->GetScreen();
	}
}

int CCommonSelectCG::GetOnCG(int mouseX, int mouseY)
{
	int x = mouseX - m_printX;
	int y = mouseY - m_printY;

	if ((x<0) || (x>=m_nextX*m_blockKosuuX)) return -1;
	if ((y<0) || (y>=m_nextY*m_blockKosuuY)) return -1;

	int ax = x % m_nextX;
	int ay = y % m_nextY;
	if (ax >= m_sizeX) return -1;
	if (ay >= m_sizeY) return -1;

	int d = x / m_nextX;
	d += ((y / m_nextY) * m_blockKosuuX);
	int block = d + m_page * (m_blockKosuuX * m_blockKosuuY);

	if ((block<0) || (block>=m_blockSabunKosuu[m_cgCharaNumber])) return -1;
	if (m_blockGetKosuu[block] <= 0) return -1;

	return d;
}


void CCommonSelectCG::CreateStartScreen(void)
{
	//menu setup?

	//script exec?

	Print();
}

/*
void CCommonSelectCG::PrintPage(void)
{
	int pg = m_updown->GetPage() + 1;
	m_suuji3->Print(m_pagePrintX,m_pagePrintY,pg);

	if (m_pageMaxPrintFlag)
	{
		m_suuji3->Print(m_pageMaxPrintX,m_pageMaxPrintY,m_pageMax);
	}

	//slash?
	if (m_slashPrintFlag)
	{
		int sizeX = m_fontSizeX3;
		int sizeY = m_fontSizeY3;
		int srcX = sizeX * 11;
		int srcY = 0;

		m_suujiPic3->Blt(m_slashPrintX,m_slashPrintY,srcX,srcY,sizeX,sizeY,TRUE);
	}

}
*/



void CCommonSelectCG::PrintTotalPercent(void)
{
//	m_suuji->Print(m_totalPercentPrintX,m_totalPercentPrintY,m_percent);
//	m_suuji->Put(m_totalPercentPrintX+m_fontNextX1*3,m_totalPercentPrintY,12,0);
	m_suuji->AppearPrint(m_appearCount, m_appearCountMax, m_menuStartEffectType, m_totalPercentPrintX, m_totalPercentPrintY, m_percent);
	m_suuji->AppearPut(m_appearCount, m_appearCountMax, m_menuStartEffectType, m_totalPercentPrintX + m_fontNextX1 * 3, m_totalPercentPrintY, 12, 0);
}


void CCommonSelectCG::PrintAddPic(void)
{
	int dva = m_appearCountMax;
	if (dva < 1) dva = 1;

	int appearPercent = 100;
	if (m_menuStartEffectType & 1)
	{
		appearPercent = (100 * m_appearCount) / dva;
		if (appearPercent < 0) appearPercent = 0;
		if (appearPercent > 100) appearPercent = 100;
	}

	char filename[256];
	wsprintf(filename,"sys\\%s",m_filenameAdd);
	m_commonParts->LoadDWQ(filename);

	int srcX = (m_cgCharaNumber % m_addPicSrcKosuuX) * m_addPicSizeX;
	int srcY = (m_cgCharaNumber / m_addPicSrcKosuuX) * m_addPicSizeY;

	if (m_addPicPrintPercent == 0)
	{
//		m_addPic->Blt(m_addPicPrintX,m_addPicPrintY,srcX,srcY,m_addPicSizeX,m_addPicSizeY,FALSE);
		m_addPic->TransLucentBlt0(m_addPicPrintX, m_addPicPrintY, srcX, srcY, m_addPicSizeX, m_addPicSizeY, appearPercent);
	}
	else if (m_addPicPrintPercent == 100)
	{
//		m_addPic->Blt(m_addPicPrintX,m_addPicPrintY,srcX,srcY,m_addPicSizeX,m_addPicSizeY,TRUE);
		m_addPic->TransLucentBlt3(m_addPicPrintX, m_addPicPrintY, srcX, srcY, m_addPicSizeX, m_addPicSizeY, appearPercent);
	}
	else
	{
		m_addPic->TransLucentBlt3(m_addPicPrintX,m_addPicPrintY,srcX,srcY,m_addPicSizeX,m_addPicSizeY,(m_addPicPrintPercent*appearPercent)/100);
	}
}


void CCommonSelectCG::PrintAllMiniPic(void)
{

	int dva = m_appearCountMax;
	if (dva < 1) dva = 1;

	int appearPercent = 100;
	if (m_menuStartEffectType & 1)
	{
		appearPercent = (100 * m_appearCount) / dva;
		if (appearPercent < 0) appearPercent = 0;
		if (appearPercent > 100) appearPercent = 100;
	}



	for (int j=0;j<m_blockKosuuY;j++)
	{
		for (int i=0;i<m_blockKosuuX;i++)
		{
			int n0 = j * m_blockKosuuX + i;
			int block = m_page * (m_blockKosuuX * m_blockKosuuY) + n0;

			int putX = m_printX + i * m_nextX;
			int putY = m_printY + j * m_nextY;

			if (m_miniPicState[n0] != -1)
			{
				if (m_futaPrintFlag)
				{


					BOOL msk = TRUE;
					if (m_futaPrintFlag == 2) msk = FALSE;
					SIZE sz = m_futaPic->GetPicSize();
					if (msk)
					{
						m_futaPic->TransLucentBlt3(putX, putY, 0,0,sz.cx, sz.cy, appearPercent);
					}
					else
					{
						m_futaPic->TransLucentBlt0(putX, putY, 0, 0, sz.cx, sz.cy, appearPercent);
					}
					//m_futaPic->Put(putX,putY,msk);
				}

				int from = m_blockSabunStart[m_cgCharaNumber][block];
				int to = m_blockSabunStart[m_cgCharaNumber][block+1];

				if (m_miniPicState[n0] == 1)
				{
					if (m_picMustPrintPercent != 0)
					{
						SIZE sz = m_miniPic[n0]->GetPicSize();
						int sizeX = sz.cx;
						int sizeY = sz.cy;

						if (m_picMustPrintPercent < 0)
						{
							if (m_appearCount >= m_appearCountMax)
							{
								if (m_miniPicTransFlag)
								{
									m_miniPic[n0]->GreyBlt(putX + m_picPrintX, putY + m_picPrintY, 0, 0, sizeX, sizeY, TRUE);
								}
								else
								{
									m_miniPic[n0]->GreyBlt(putX + m_picPrintX, putY + m_picPrintY, 0, 0, sizeX, sizeY, FALSE);
								}
							}
						}
						else
						{
							if (m_miniPicTransFlag)
							{
								m_miniPic[n0]->TransLucentBlt3(putX+m_picPrintX,putY+m_picPrintY,0,0,sizeX,sizeY,(m_picMustPrintPercent*appearPercent)/100);
							}
							else
							{
								m_miniPic[n0]->TransLucentBlt(putX+m_picPrintX,putY+m_picPrintY,0,0,sizeX,sizeY,(m_picMustPrintPercent*appearPercent)/100);
							}
						}
					}
				}
				else if (m_miniPicState[n0] == 2)
				{
					SIZE sz = m_miniPic[n0]->GetPicSize();

					if (m_miniPicTransFlag)
					{
//						m_miniPic[n0]->Put(putX+m_picPrintX,putY+m_picPrintY,TRUE);
						m_miniPic[n0]->TransLucentBlt3(putX + m_picPrintX, putY + m_picPrintY, 0,0,sz.cx,sz.cy,appearPercent);
					}
					else
					{
//						m_miniPic[n0]->Put(putX+m_picPrintX,putY+m_picPrintY,FALSE);
						m_miniPic[n0]->TransLucentBlt0(putX + m_picPrintX, putY + m_picPrintY, 0, 0, sz.cx, sz.cy, appearPercent);
					}
				}

				if (m_animePrintFlag)
				{
					if ((m_miniPicState[n0] == 1) || (m_miniPicState[n0] == 2))
					{
						if (m_animeFlag[n0])
						{
//							m_animePic->Put(putX+m_picPrintX,putY+m_picPrintY,TRUE);
							SIZE sz = m_animePic->GetPicSize();
							m_animePic->TransLucentBlt3(putX + m_picPrintX, putY + m_picPrintY, 0,0,sz.cx,sz.cy,appearPercent);
						}
					}
				}

				//get kosuu hyoji

				int total = to - from;
				int getKosuu = m_blockGetKosuu[block];

				int putX2 = putX + m_differencePrintX;
				int putY2 = putY + m_differencePrintY;
				int putX3 = putX2 + m_fontNextX2 * m_differentKeta;
				int putX4 = putX2 + m_fontNextX2 * (m_differentKeta+1);
					

				if (total < 10)
				{
					putX4 -= m_fontNextX2;
				}

				int col = 0;

				if (m_sabunPrintFlag & 1)
				{
					BOOL ff = FALSE;
					if (m_sabunPrintFlag & 2)
					{
						ff = TRUE;
					}
					else
					{
						if (total >= 2) ff = TRUE;
					}

					if (m_sabunPrintByGetFlag == 0)
					{
						if (getKosuu == 0) ff = FALSE;
					}

					if (ff)
					{
//						m_suuji2->Print(putX4,putY2,total,-1,col);
//						m_suuji2->Put(putX3,putY2,11,col);
//						m_suuji2->Print(putX2,putY2,getKosuu,-1,col);
						m_suuji2->AppearPrint(m_appearCount, m_appearCountMax, m_menuStartEffectType, putX4, putY2, total, -1, col);
						m_suuji2->AppearPut(m_appearCount, m_appearCountMax, m_menuStartEffectType, putX3, putY2, 11, col);
						m_suuji2->AppearPrint(m_appearCount, m_appearCountMax, m_menuStartEffectType, putX2, putY2, getKosuu, -1, col);
					}
				}
			}
		}
	}
}

int CCommonSelectCG::GetCGBlockNumber(int cgCharaNumber,int cgNumber)
{
	int block = 0;
	int blockSabunKosuu = 0;
	if (m_cgCharaKosuu > 0)
	{
		blockSabunKosuu = m_blockSabunKosuu[cgCharaNumber];
	}


	int i = 0;
	for (i=0;i<blockSabunKosuu;i++)
	{
		int from = m_blockSabunStart[cgCharaNumber][i];
		int to = m_blockSabunStart[cgCharaNumber][i+1];
		if ((cgNumber >= from) && (cgNumber < to))
		{
			block = i;
			break;
		}
	}

	return block;
}



int CCommonSelectCG::GetStartWaitMode(void)
{
	if (m_menuStartCount < m_menuStartWaitTime)
	{
		m_appearCount = 0;
		m_appearCountMax = 1;
		return 1;
	}

	if (m_menuStartCount < m_menuStartWaitTime + m_menuStartEffectTime)
	{
		m_appearCount = m_menuStartCount - m_menuStartWaitTime;
		m_appearCountMax = m_menuStartEffectTime;
		return 2;
	}

	m_appearCount = 1;
	m_appearCountMax = 1;

	return 0;
}

void CCommonSelectCG::EndStartWaitMode(void)
{
	m_menuStartCount = m_menuStartWaitTime + m_menuStartEffectTime;
	//m_game->InitMiniGameButton(OMAKE_MODE);
}
