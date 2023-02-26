//
// commonSelectCGChara.cpp
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

#include "..\nnnUtilLib\cgDataControl.h"

#include "commonMode.h"
#include "commonSystemParamName.h"

#include "gameCallBack.h"

#include "commonGeneral.h"
#include "commonSelectCGChara.h"





#include "..\nnnUtilLib\commonButton.h"
#include "..\nnnUtilLib\commonButton.h"
#include "..\nnnUtilLib\commonBackButton.h"
#include "..\nnnUtilLib\suuji.h"






#include "..\nnnUtilLib\nnnButtonStatus.h"
#include "..\nnnUtilLib\myMouseStatus.h"

//#include "myButtonGroup.h"


#include "commonmode.h"
//#include "commonBgmNumberList.h"
#include "commonSystemSoundName.h"


//#include "messagewindow.h"
//#include "namewindow.h"
//#include "menustatusnumber.h"

//#include "myblockbuttonmenu.h"
//#include "mymessage.h"

//#include "gameVersion.h"


//#include "gradColor.h"


#include "commonMode.h"

#include "..\nnnUtilLib\namelist.h"


#include "commonGeneral.h"
#include "commonSelectCGChara.h"

#include "gameCallBack.h"


char CCommonSelectCGChara::m_defaultBGFileName[] = "sys\\cgm_bg";
char CCommonSelectCGChara::m_defaultCharaFileName[] = "sys\\ta_cgm_bt";
char CCommonSelectCGChara::m_defaultCursorFileName[] = "sys\\ta_cgm_cur";

char CCommonSelectCGChara::m_defaultPercentFileName[] = "ta_font_cgm1";

CCommonSelectCGChara::CCommonSelectCGChara(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	int i = 0;
	SetClassNumber(SELECTCGCHARA_MODE);
//	m_classNumber = SELECTCGCHARA_MODE;

	m_cgDataControl = m_game->GetCGDataControl();

	m_cgCharaKosuu = 1;
	if (m_cgDataControl != NULL)
	{
		m_cgCharaKosuu = m_cgDataControl->GetCGCharaKosuu();
	}

	LoadSetupFile("selectcgchara",8192);

	GetBackExecSetup();

	m_filenameBG = m_defaultBGFileName;
	m_filenameChara = m_defaultCharaFileName;


	m_totalPercent = 0;
	m_pictureMode = 0;
	m_cursorMode = 1;
	GetInitGameParam(&m_pictureMode,"pictureMode");
	GetInitGameParam(&m_cursorMode,"cursorMode");

	m_checkOnByPicFlag = 0;
	GetInitGameParam(&m_checkOnByPicFlag,"checkOnByPicFlag");


	GetInitGameString(&m_filenameBG,"filenameBG");

	if (m_pictureMode != 0)
	{
		GetInitGameString(&m_filenameChara,"filenameChara");
	}

	if (m_cursorMode >= 2)
	{
		m_filenameCursor = m_defaultCursorFileName;
		GetInitGameString(&m_filenameCursor,"filenameCursor");
		m_cursorPic = m_game->GetSystemPicture(m_filenameCursor);
	}

	m_picNumberX = m_cgCharaKosuu;
	GetInitGameParam(&m_picNumberX,"picNumberX");
	if (m_picNumberX < 1) m_picNumberX = 1;

	m_cursorPrintType = 0;
	GetInitGameParam(&m_cursorPrintType,"cursorPrintType");





	m_cgCustomPrintFlag = 0;
	GetInitGameParam(&m_cgCustomPrintFlag,"customPrintFlag");

	m_cursorColorR = 128;
	m_cursorColorG = 0;
	m_cursorColorB = 255;

	if (m_cursorMode == 1)
	{
		GetInitGameParam(&m_cursorColorR,"cursorColorR");
		GetInitGameParam(&m_cursorColorG,"cursorColorG");
		GetInitGameParam(&m_cursorColorB,"cursorColorB");
	}

	m_cursorPrintType = 1;
	if (m_cursorMode == 2)
	{
		GetInitGameParam(&m_cursorPrintType,"cursorPrintType");
	}

	m_cursorPercent = 50;
	if (m_cursorMode != 0)
	{
		GetInitGameParam(&m_cursorPercent,"cursorPercent");
	}

	m_zahyo = new POINT[m_cgCharaKosuu];



	m_sizeX = 32;
	m_sizeY = 32;

	GetInitGameParam(&m_sizeX,"sizeX");
	GetInitGameParam(&m_sizeY,"sizeY");

	m_numberX = m_cgCharaKosuu;
	m_numberY = 1;
	m_basePrintX = 0;
	m_basePrintY = 0;
	m_baseNextX = m_sizeX;
	m_baseNextY = 0;

	GetInitGameParam(&m_numberX,"numberX");
	GetInitGameParam(&m_numberY,"numberY");
	GetInitGameParam(&m_basePrintX,"baseX");
	GetInitGameParam(&m_basePrintY,"baseY");
	GetInitGameParam(&m_baseNextX,"baseNextX");
	GetInitGameParam(&m_baseNextY,"baseNextY");

	if (m_numberX < 1) m_numberX = 1;

	for (i=0;i<m_cgCharaKosuu;i++)
	{
		m_zahyo[i].x = m_basePrintX + (i % m_numberX) * m_baseNextX;
		m_zahyo[i].y = m_basePrintY + (i / m_numberX) * m_baseNextY;
	}

	if (m_cgCustomPrintFlag)
	{
		char name[1024];
		for (i=0;i<m_cgCharaKosuu;i++)
		{
			wsprintf(name,"printX%d",i+1);
			int px = m_zahyo[i].x;
			GetInitGameParam(&px,name);
			wsprintf(name,"printY%d",i+1);
			int py = m_zahyo[i].y;
			GetInitGameParam(&py,name);
			m_zahyo[i].x = px;
			m_zahyo[i].y = py;
		}
	}




	m_totalPercentPrintFlag = 1;
	m_charaPercentPrintFlag = 1;

	GetInitGameParam(&m_totalPercentPrintFlag,"totalPercentPrintFlag");
	GetInitGameParam(&m_charaPercentPrintFlag,"charaPercentPrintFlag");

	m_totalPercentSuuji = NULL;
	m_percentSuuji = NULL;


	if (m_totalPercentPrintFlag)
	{
		m_totalPercentPercentFlag = 1;
		GetInitGameParam(&m_totalPercentPercentFlag,"totalPercentPercentFlag");
		LPSTR name = m_defaultPercentFileName;
		GetInitGameString(&name,"fileNameTotalPercentPic");
		CPicture* pic = m_game->GetSystemPicture(name);

		GetInitGameParam(&m_totalPercentPrintX,"totalPercentPrintX");
		GetInitGameParam(&m_totalPercentPrintY,"totalPercentPrintY");
		GetInitGameParam(&m_totalPercentFontSizeX,"totalPercentSizeX");
		GetInitGameParam(&m_totalPercentFontSizeY,"totalPercentSizeY");
		GetInitGameParam(&m_totalPercentFontNextX,"totalPercentNextX");
		m_totalPercentSuuji = new CSuuji(pic,m_totalPercentFontSizeX,m_totalPercentFontSizeY,3,m_totalPercentFontNextX);
	}


	m_percentSuuji0 = nullptr;
	m_percentSuuji100 = nullptr;
	m_percentPrintDelta = nullptr;
	m_useCharaPercentPrintDeltaFlag = 0;
	GetInitGameParam(&m_useCharaPercentPrintDeltaFlag, "useCharaPercentPrintDeltaFlag");

	m_changePercentPicFlag = 0;
	GetInitGameParam(&m_changePercentPicFlag, "changePercentPicFlag");

	if (m_charaPercentPrintFlag)
	{
		m_charaPercentPercentFlag = 1;
		GetInitGameParam(&m_charaPercentPercentFlag,"percentPercentFlag");
		LPSTR name = m_defaultPercentFileName;
		GetInitGameString(&name,"fileNamePercentPic");
		CPicture* pic = m_game->GetSystemPicture(name);

		GetInitGameParam(&m_percentPrintX,"percentPrintX");
		GetInitGameParam(&m_percentPrintY,"percentPrintY");
		GetInitGameParam(&m_percentFontSizeX,"percentSizeX");
		GetInitGameParam(&m_percentFontSizeY,"percentSizeY");
		GetInitGameParam(&m_percentFontNextX,"percentNextX");
		m_percentSuuji = new CSuuji(pic,m_percentFontSizeX,m_percentFontSizeY,3,m_percentFontNextX);

		if (m_changePercentPicFlag)
		{
			name = m_defaultPercentFileName;
			GetInitGameString(&name, "fileNamePercentPic0");
			pic = m_game->GetSystemPicture(name);
			m_percentSuuji0 = new CSuuji(pic, m_percentFontSizeX, m_percentFontSizeY, 3, m_percentFontNextX);

			name = m_defaultPercentFileName;
			GetInitGameString(&name, "fileNamePercentPic100");
			pic = m_game->GetSystemPicture(name);
			m_percentSuuji100 = new CSuuji(pic, m_percentFontSizeX, m_percentFontSizeY, 3, m_percentFontNextX);
		}

		if (m_useCharaPercentPrintDeltaFlag)
		{
			m_percentPrintDelta = new int[m_cgCharaKosuu*2];
			for (int i = 0; i < m_cgCharaKosuu; i++)
			{
				char namex[256];
				char namey[256];
				wsprintf(namex, "charaPercentDeltaX%d", i + 1);
				wsprintf(namey, "charaPercentDeltaY%d", i + 1);
				int x = m_percentPrintX;
				int y = m_percentPrintY;
				GetInitGameParam(&x, namex);
				GetInitGameParam(&y, namey);
				m_percentPrintDelta[i * 2 + 0] = x;
				m_percentPrintDelta[i * 2 + 1] = y;
			}

		}
	}


	m_charaVoiceFlag = 0;
	GetInitGameParam(&m_charaVoiceFlag,"charaVoiceFlag");

	m_charaVoiceFileName = NULL;
	m_charaVoiceWaitTime = 10;

	if (m_charaVoiceFlag)
	{
		GetInitGameParam(&m_charaVoiceWaitTime,"charaVoiceWaitTime");
		m_charaVoiceFileName = new char* [m_cgCharaKosuu];
		for (int i=0;i<m_cgCharaKosuu;i++)
		{
			char name[256];
			wsprintf(name,"charaVoiceFileName%d",i);
			GetInitGameString(&m_charaVoiceFileName[i],name);
		}
	}

	m_charaExistFlag = new int[m_cgCharaKosuu];
	m_charaExistCheckPercent = new int[m_cgCharaKosuu];
	m_charaExistCheckVar = new int[m_cgCharaKosuu];

	for (int i=0;i<m_cgCharaKosuu;i++)
	{
		m_charaExistFlag[i] = 1;
		
		m_charaExistCheckPercent[i] = 0;
		m_charaExistCheckVar[i] = -1;

		char name[256];
		wsprintf(name,"charaAppearPercent%d",i+1);
		int ps = 0;
		GetInitGameParam(&ps,name);
		m_charaExistCheckPercent[i] = ps;

		LPSTR varName = NULL;
		wsprintf(name,"charaAppearVarName%d",i+1);
		if (GetInitGameString(&varName,name))
		{
			if (varName != NULL)
			{
				int varNumber = m_game->GetVarNumber(varName);
				m_charaExistCheckVar[i] = varNumber;
			}
		}
	}

	m_selectCommonCGCharaSound = -1;
	GetInitGameParam(&m_selectCommonCGCharaSound, "selectSound");


	m_length = 8;

//	m_back = m_game->GetBackButton();
//	m_newBack = m_game->GetNewBackButton();


//	m_buttonSizeX = 127;
//	m_buttonSizeY = 127;
	
	m_startupWait = 2;

	GetBGMSetup();
	GetFadeInOutSetup();
	GetEnterExitVoiceFileName();

//	GetBackButtonPara();
	CreateBackButton();
}



CCommonSelectCGChara::~CCommonSelectCGChara()
{
	End();
}


void CCommonSelectCGChara::End(void)
{
	DELETEARRAY(m_charaExistCheckVar);
	DELETEARRAY(m_charaExistCheckPercent);
	DELETEARRAY(m_charaExistFlag);

	DELETEARRAY(m_zahyo);
	ENDDELETECLASS(m_totalPercentSuuji);
	ENDDELETECLASS(m_percentSuuji);
	ENDDELETECLASS(m_percentSuuji0);
	ENDDELETECLASS(m_percentSuuji100);

//	ENDDELETECLASS(m_suuji);
	DELETEARRAY(m_charaVoiceFileName);
	DELETEARRAY(m_percentPrintDelta);

//	ENDDELETECLASS(m_menu);
}

int CCommonSelectCGChara::Init(void)
{
//	m_game->CheckAllCGAndSetFilm();
//	m_game->PreInitSelectCGCharaCallBack();


	m_game->SetDefaultFrameRate();


	m_back->Init();

	SetBackButtonZahyo();

//	m_commonBG->LoadDWQ("sys\\cgm_bg");
	char filename[1024];
	if (m_backScriptFlag == 0)
	{
		wsprintf(filename,"sys\\%s",m_filenameBG);
		m_commonBG->LoadDWQ(filename);
	}


	if (m_pictureMode != 0)
	{
		wsprintf(filename,"sys\\%s",m_filenameChara);
		m_commonParts->LoadDWQ(filename);
	}

	m_nowSelectNumber = -1;
	m_maeSelectNumber = -1;
	m_selectedNumber = -1;


	for (int i=0;i<m_cgCharaKosuu;i++)
	{
		m_charaExistFlag[i] = 1;
		int checkPercent = m_charaExistCheckPercent[i];

		int ps = 0;
		if (m_cgDataControl != NULL)
		{
			ps = m_cgDataControl->GetCGPercent(i);
		}
//		int ps = m_game->GetCGPercent(i);
		if (ps < checkPercent)
		{
			m_charaExistFlag[i] = 0;
		}

		int checkVar = m_charaExistCheckVar[i];
		if (checkVar > 0)
		{
			if (m_game->GetVarData(checkVar) == 0)
			{
				m_charaExistFlag[i] = 0;
			}
		}
	}


	m_commonBG->Put(0,0,FALSE);
	for (int i=0;i<m_cgCharaKosuu;i++)
	{
		//‚¨‚¨‚à‚Æ‚ð‚©‚­???

		if (m_charaExistFlag[i])
		{
			if (m_pictureMode == 1)
			{
				POINT pt = GetZahyo(i);
				int srcX = (i % m_picNumberX) * m_sizeX;
				int srcY = (i / m_picNumberX) * m_sizeY;

				m_commonParts->Blt(pt.x,pt.y,srcX,srcY,m_sizeX,m_sizeY,TRUE);
			}


	//		if (m_pictureMode == 3)
	//		{
	//			POINT pt = GetZahyo(i);
	//			int srcX = (i % m_picNumberX) * m_sizeX;
	//			int srcY = (i / m_picNumberX) * (m_sizeY * 2) + m_sizeY;
	//
	//			m_commonParts->Blt(pt.x,pt.y,srcX,srcY,m_sizeX,m_sizeY,TRUE);
	//		}

	//		if (m_charaPercentPrintFlag)
	//		{
	//			PrintCharaPercent(i);
	//		}
		}
	}

	int totalPercent = 0;
	if (m_cgDataControl != NULL)
	{
		totalPercent = m_cgDataControl->GetTotalCGPercent();
	}
	m_totalPercent = totalPercent;

	//put percent
	if (m_totalPercentPrintFlag)
	{
		m_totalPercentSuuji->Print(m_totalPercentPrintX,m_totalPercentPrintY,totalPercent);
		if (m_totalPercentPercentFlag)
		{
			m_totalPercentSuuji->Put(m_totalPercentPrintX+m_totalPercentFontNextX*3,m_totalPercentPrintY,12,0);
		}
	}

	m_commonBG->GetScreen();


	m_game->ClearF5();

	LoadBackButtonPic();
///	m_commonBG->LoadDWQ(m_filenameBG);
///	m_commonParts->LoadDWQ(m_filenameButton);


///	m_menu->Init();

///	m_game->PlayCommonBgm(COMMONBGM_SELECTCGCHARA,TRUE);

//	m_game->PlayBGM(-1);
//	m_game->PlayBGM(0);

	m_game->StopVoice();

	return -1;
}


int CCommonSelectCGChara::Calcu(void)
{


	POINT pt = m_mouseStatus->GetZahyo();
	int mouseX = pt.x;
	int mouseY = pt.y;


	if (m_selectedNumber >= 0)
	{
		m_count--;
		if (m_count<=0)
		{
//			if (m_selectedNumber == -2)
//			{
//				return ReturnFadeOut(OMAKE_MODE);
//				return OMAKE_MODE;
//			}

			if (m_cgDataControl != NULL)
			{
				m_cgDataControl->SetCGCharaNumber(m_selectedNumber);
				m_cgDataControl->SetCGNumber(0);
			}
			m_game->SetCommonBackMode(SELECTCG_MODE,SELECTCGCHARA_MODE);
			m_game->SetDefaultFrameRate();

			return ReturnFadeOut(SELECTCG_MODE);
//			return SELECTCG_MODE;
		}
		return -1;
	}


	int rt = m_back->Calcu(m_inputStatus);
	if (rt != NNNBUTTON_NOTHING)
	{
		int st = CCommonButton::GetButtonStatus(rt);
		int nm = ProcessCommonButton(rt);
		if (nm >= 0)
		{
			return ReturnFadeOut(OMAKE_MODE);
		}

		if (st == NNNBUTTON_STARTCLICK)
		{
			m_selectedNumber = -2;
			return -1;
		}
	}

	m_maeSelectNumber = m_nowSelectNumber;
	m_nowSelectNumber = GetOnButton(mouseX,mouseY);

	if (m_mouseStatus->CheckClick())
	{
		if (m_nowSelectNumber != -1)
		{
			m_selectedNumber = m_nowSelectNumber;
			m_count = m_length;
			if (m_selectCommonCGCharaSound != -1)
			{
				m_game->PlayCommonSystemSound(m_selectCommonCGCharaSound-1);
			}
			else
			{
				m_game->PlayCommonSystemSound(COMMON_SYSTEMSOUND_OK2);
			}
			return -1;
		}
	}


	if (m_startupWait>0)
	{
		m_startupWait--;
	}
	else
	{
		if (m_nowSelectNumber != m_maeSelectNumber)
		{
			if (m_nowSelectNumber >= 0)
			{
//				m_game->PlaySystemPiano(m_musicTable[m_placeTable[m_nowSelectNumber]]);
			}
		}
	}




//	int rt = m_menu->Calcu(m_mouseStatus);
//
//	int st = rt & NNNBUTTON_STATUSMASK;
//	int nm = rt & NNNBUTTON_DATAMASK;
//
//	if (st == NNNBUTTON_STARTCLICK)
//	{
//		m_game->PlayCommonSystemSound(COMMON_SYSTEMSOUND_OK);
//	}
//
//
//	if (st == MYBUTTON_NUMBER)
//	{
//		m_game->SetCGCharaNumber(nm);
//		return SELECTCG_MODE;
//	}

	return -1;
}


int CCommonSelectCGChara::Print(void)
{
	PrintBackScriptOrBG();
	BOOL b = CAreaControl::CheckAllPrintMode();



	if (m_backScriptFlag)
	{
		if (m_totalPercentPrintFlag)
		{
			m_totalPercentSuuji->Print(m_totalPercentPrintX,m_totalPercentPrintY,m_totalPercent);
			if (m_totalPercentPercentFlag)
			{
				m_totalPercentSuuji->Put(m_totalPercentPrintX+m_totalPercentFontNextX*3,m_totalPercentPrintY,12,0);
			}
		}
	}



	m_back->Print(TRUE);

	for (int i=0;i<m_cgCharaKosuu;i++)
	{
		if (m_charaExistFlag[i])
		{
			int mv1 = -1;
			int mv2 = -1;
			if (m_nowSelectNumber != m_maeSelectNumber)
			{
				mv1 = m_maeSelectNumber;
				mv2 = m_nowSelectNumber;
			}

			if (b || (i == mv1) || (i == mv2) || i == m_selectedNumber)
			{
				EraseChara(i);

				if (i == m_selectedNumber)
				{
					if ((m_count % 2) == 0)
					{
						PrintChara(i);
					}
				}
				else if (i == m_nowSelectNumber)
				{
					PrintChara(i);
				}
			}
		}
	}

	return -1;
}




BOOL CCommonSelectCGChara::CheckOnButton(int n, int mouseX, int mouseY)
{
	if (m_charaExistFlag[n] == 0) return FALSE;

	POINT pt = GetZahyo(n);
	int x = mouseX - pt.x;
	int y = mouseY - pt.y;

	if ((x>=0) && (y>=0) && (x<m_sizeX) && (y<m_sizeY))
	{
		if (m_checkOnByPicFlag == 0) return TRUE;

		if ((m_pictureMode == 2) || (m_pictureMode == 3))
		{
			POINT pt2 = GetPicSrcZahyo(n);
			if (m_commonParts->CheckOnPic(x+pt2.x,y+pt2.y)) return TRUE;

			return FALSE;
		}
		return TRUE;
	}

	return FALSE;
}

int CCommonSelectCGChara::GetOnButton(int mouseX,int mouseY)
{
	for (int i=0;i<m_cgCharaKosuu;i++)
	{
		if (CheckOnButton(i,mouseX,mouseY)) return i;
	}

	return -1;
}


POINT CCommonSelectCGChara::GetPicSrcZahyo(int n,BOOL eraseFlag)
{
	POINT pt;

	int k = 1;
	if (m_pictureMode == 3) k= 2;

	int srcX = (n % m_picNumberX) * m_sizeX;
	int srcY = (n / m_picNumberX) * (m_sizeY * k);

	if (m_pictureMode == 3)
	{
		if (eraseFlag == FALSE)
		{
			srcY += m_sizeY;
		}
	}

	pt.x = srcX;
	pt.y = srcY;

	return pt;
}


void CCommonSelectCGChara::EraseChara(int n)
{
	POINT pt = GetZahyo(n);
	int putX = pt.x;
	int putY = pt.y;
	int sizeX = m_sizeX;
	int sizeY = m_sizeY;

	if ((m_mustAllPrintFlag == FALSE) && (m_backScriptFlag == 0))
	{
		m_commonBG->Blt(putX,putY,putX,putY,sizeX,sizeY,FALSE);
	}


	if ((m_pictureMode == 1) || (m_pictureMode == 3))
	{
		POINT pt = GetZahyo(n);
		POINT pt2 = GetPicSrcZahyo(n,TRUE);
		int srcX = pt2.x;
		int srcY = pt2.y;

//		int srcX = (n % m_picNumberX) * m_sizeX;
//		int srcY = (n / m_picNumberX) * (m_sizeY * 2);

		m_commonParts->Blt(pt.x,pt.y,srcX,srcY,m_sizeX,m_sizeY,TRUE);
	}


	if (m_charaPercentPrintFlag)
	{
		PrintCharaPercent(n);
	}


	CAreaControl::AddArea(putX,putY,sizeX,sizeY);
}


void CCommonSelectCGChara::PrintChara(int n)
{
	POINT pt = GetZahyo(n);
	int putX = pt.x;
	int putY = pt.y;
	int sizeX = m_sizeX;
	int sizeY = m_sizeY;

	POINT pt2 = GetPicSrcZahyo(n);
	int srcX = pt2.x;
	int srcY = pt2.y;

	if ((m_mustAllPrintFlag == FALSE) && (m_backScriptFlag == 0))
	{
		m_commonBG->Blt(putX,putY,putX,putY,sizeX,sizeY,FALSE);
	}

//	if ((m_pictureMode == 1) || (m_pictureMode == 2))
//	{
//		srcX = (n % m_picNumberX) * m_sizeX;
//		srcY = (n / m_picNumberX) * m_sizeY;
//	}

//	if (m_pictureMode == 3)
//	{
//		srcX = (n % m_picNumberX) * m_sizeX;
//		srcY = (n / m_picNumberX) * (m_sizeY * 2) + m_sizeY;
//	}

	if ((m_pictureMode == 1) || (m_pictureMode == 2) || (m_pictureMode == 3))
	{
		m_commonParts->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
		if (m_charaPercentPrintFlag)
		{
			PrintCharaPercent(n);
		}
	}

	//cursor
	if (m_cursorMode == 1)	//color
	{
		CAllGeo::TransBoxFill(putX,putY,sizeX,sizeY,m_cursorColorR,m_cursorColorG,m_cursorColorB,m_cursorPercent);
	}

	if (m_cursorMode == 2)	//pic
	{
		if (m_cursorPrintType == 0)
		{
			m_cursorPic->Blt(putX,putY,0,0,sizeX,sizeY,TRUE);
		}
		else if (m_cursorPrintType == 1)
		{
			m_cursorPic->TransLucentBlt3(putX,putY,0,0,sizeX,sizeY,m_cursorPercent);
		}
		else if (m_cursorPrintType == 2)
		{
			m_cursorPic->AddBlt(putX,putY,0,0,sizeX,sizeY);
		}
	}



//	m_commonParts->AddBlt(putX,putY,0,0,sizeX,sizeY);
}



void CCommonSelectCGChara::PrintCharaPercent(int n)
{
	int ps = 0;
	if (m_cgDataControl != NULL)
	{
		ps = m_cgDataControl->GetCGPercent(n);
	}

	//put percent
	POINT pt = GetZahyo(n);

	int x = pt.x + m_percentPrintX;
	int y = pt.y + m_percentPrintY;

	if (m_useCharaPercentPrintDeltaFlag)
	{
		x = pt.x + m_percentPrintDelta[n*2+0];
		y = pt.y + m_percentPrintDelta[n*2+1];
	}

	CSuuji* suuji = m_percentSuuji;
	if (m_changePercentPicFlag)
	{
		if (ps == 0)
		{
			if (m_percentSuuji0 != nullptr)
			{
				suuji = m_percentSuuji0;
			}
		}
		else if (ps == 100)
		{
			if (m_percentSuuji100 != nullptr)
			{
				suuji = m_percentSuuji100;
			}
		}
	}

	suuji->Print(x,y,ps);
	if (m_charaPercentPercentFlag)
	{
		suuji->Put(x+m_percentFontNextX*3,y,12,0);
	}
}


void CCommonSelectCGChara::CreateStartScreen(void)
{
	//menu setup?

	//script exec?

	Print();
}

/*_*/

