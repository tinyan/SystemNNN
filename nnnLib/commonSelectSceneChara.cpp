//
// commonSelectSceneChara.cpp
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

#include "commonMode.h"
#include "commonSystemParamName.h"

#include "..\nnnUtilLib\commonButton.h"
#include "..\nnnUtilLib\commonBackButton.h"

#include "..\nnnUtilLib\sceneDataControl.h"

#include "gameCallBack.h"

#include "commonGeneral.h"

#include "commonSelectSceneChara.h"

#include "..\nnnUtilLib\suuji.h"



char CCommonSelectSceneChara::m_defaultBGFileName[] = "scenem_bg";
char CCommonSelectSceneChara::m_defaultButtonFileName[] = "ta_scenem_bt";
char CCommonSelectSceneChara::m_defaultCursorFileName[] = "ta_cgm_cur";

char CCommonSelectSceneChara::m_defaultFontFileName[] = "ta_font_cgm1";
//char CCommonSelectSceneChara::m_defaultFont2FileName[] = "ta_font_cgm1";

char CCommonSelectSceneChara::m_defaultHeartFileName[] = "ta_heart";


CCommonSelectSceneChara::CCommonSelectSceneChara(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(SELECTSCENECHARA_MODE);
//	m_classNumber = SELECTSCENECHARA_MODE;


	LoadSetupFile("SelectSceneChara",32);

	m_sceneDataControl = m_game->GetSceneDataControl();

	m_sceneCharaKosuu = 1;
	if (m_sceneDataControl != NULL)
	{
		m_sceneCharaKosuu = m_sceneDataControl->GetSceneCharaKosuu();
	}


	GetBackExecSetup();

	m_filenameBG = m_defaultBGFileName;
	m_filenameButton = m_defaultButtonFileName;

	m_pictureMode = 0;
	m_cursorMode = 1;
	GetInitGameParam(&m_pictureMode,"pictureMode");
	GetInitGameParam(&m_cursorMode,"cursorMode");

	m_checkOnByPicFlag = 0;
	GetInitGameParam(&m_checkOnByPicFlag,"checkOnByPicFlag");

	GetInitGameString(&m_filenameBG,"filenameBG");

	if (m_pictureMode != 0)
	{
		GetInitGameString(&m_filenameButton,"filenameButton");
	}

	m_filenameCursor = m_defaultCursorFileName;
	if (m_cursorMode >= 2)
	{
		GetInitGameString(&m_filenameCursor,"filenameCursor");
	}

	m_picNumberX = m_sceneCharaKosuu;
	GetInitGameParam(&m_picNumberX,"picNumberX");
	if (m_picNumberX < 1) m_picNumberX = 1;

	m_cursorPrintType = 0;
	GetInitGameParam(&m_cursorPrintType,"cursorPrintType");

	m_sceneCustomPrintFlag = 0;
	GetInitGameParam(&m_sceneCustomPrintFlag,"customPrintFlag");

	m_cursorColorR = 128;
	m_cursorColorG = 0;
	m_cursorColorB = 255;

	if (m_cursorMode == 1)
	{
		GetInitGameParam(&m_cursorColorR,"cursorColorR");
		GetInitGameParam(&m_cursorColorG,"cursorColorG");
		GetInitGameParam(&m_cursorColorB,"cursorColorB");
	}

	m_kazariPrintFlag = 0;
	GetInitGameParam(&m_kazariPrintFlag, "kazariPrintFlag");
	m_kazariPic = nullptr;
	m_kazariSizeX = 29;
	m_kazariSizeY = 31;
	m_kazariPrintX = 3;
	m_kazariPrintY = 5;

	if (m_kazariPrintFlag)
	{
		LPSTR kazariFileName = "ta_sigunaru1";
		GetInitGameString(&kazariFileName, "kazariFilename");
		m_kazariPic = m_game->GetSystemPicture(kazariFileName);
		GetInitGameParam(&m_kazariSizeX,"kazariSizeX");
		GetInitGameParam(&m_kazariSizeY, "kazariSizeY");
		GetInitGameParam(&m_kazariPrintX, "kazariPrintX");
		GetInitGameParam(&m_kazariPrintY, "kazariPrintY");
	}

	m_cursorPrintType = 1;
	m_cursorPic = NULL;
	if (m_cursorMode == 2)
	{
		GetInitGameParam(&m_cursorPrintType,"cursorPrintType");
		m_cursorPic = new CPicture();
		char cfilename[256];
		sprintf_s(cfilename,256,"sys\\%s",m_filenameCursor);
		m_cursorPic->LoadDWQ(cfilename);
	}

	m_cursorPercent = 50;
	if (m_cursorMode != 0)
	{
		GetInitGameParam(&m_cursorPercent,"cursorPercent");
	}

	m_zahyo = new POINT[m_sceneCharaKosuu];
	m_sceneHMode = new int[m_sceneCharaKosuu+1];


	m_sizeX = 127;
	m_sizeY = 127;

	GetInitGameParam(&m_sizeX,"sizeX");
	GetInitGameParam(&m_sizeY,"sizeY");

	m_numberX = m_sceneCharaKosuu;
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

	for (int i=0;i<m_sceneCharaKosuu;i++)
	{
		m_zahyo[i].x = m_basePrintX + (i % m_numberX) * m_baseNextX;
		m_zahyo[i].y = m_basePrintY + (i / m_numberX) * m_baseNextY;
	}


	m_kumiawaseFlag = 0;
	GetInitGameParam(&m_kumiawaseFlag,"combineFlag");

	if (m_kumiawaseFlag)
	{
		int combineKosuu = 1;
		int combineType = 0;
		GetInitGameParam(&combineType,"combineType");
		GetInitGameParam(&combineKosuu,"combineNumber");

		int k = 0;


		if (combineType == 0)
		{
			for (int j=0;j<combineKosuu;j++)
			{
				for (int i=j;i<combineKosuu;i++)
				{
					if (k<m_sceneCharaKosuu)
					{

						int x = m_basePrintX + i * m_baseNextX;
						int y = m_basePrintY + j * m_baseNextY;

						m_zahyo[i].x = x;
						m_zahyo[i].y = y;
					}
					k++;
				}
			}
		}
		else
		{
			for (int j=0;j<combineKosuu;j++)
			{
				for (int i=0;i<=j;i++)
				{
					if (k<m_sceneCharaKosuu)
					{

						int x = m_basePrintX + i * m_baseNextX;
						int y = m_basePrintY + j * m_baseNextY;

						m_zahyo[i].x = x;
						m_zahyo[i].y = y;
					}
					k++;
				}
			}
		}
	}



	int customStart = 1;
	int customEnd = m_sceneCharaKosuu;

	GetInitGameParam(&customStart,"customStart");
	GetInitGameParam(&customEnd,"customEnd");

	customStart--;
	customEnd--;

	int customPrintFlag = 0;
	GetInitGameParam(&customPrintFlag,"customPrintFlag");

	if (customPrintFlag)
	{
		for (int i=customStart;i<=customEnd;i++)
		{
			if ((i>=0) && (i<m_sceneCharaKosuu))
			{
				char name[256];
				int x = m_zahyo[i].x;
				int y = m_zahyo[i].y;

				wsprintf(name,"printX%d",i+1);
				GetInitGameParam(&x,name);
				wsprintf(name,"printY%d",i+1);
				GetInitGameParam(&y,name);

				m_zahyo[i].x = x;
				m_zahyo[i].y = y;
			}
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
		GetInitGameParam(&m_totalPercentPercentFlag,"totalPercentPercentFlag");
		LPSTR name = m_defaultFontFileName;
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
	m_changePercentPicFlag = 0;
	GetInitGameParam(&m_changePercentPicFlag, "changePercentPicFlag");

	if (m_charaPercentPrintFlag)
	{
		GetInitGameParam(&m_charaPercentPercentFlag,"percentPercentFlag");
		LPSTR name = m_defaultFontFileName;
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
			name = m_defaultFontFileName;
			GetInitGameString(&name, "fileNamePercentPic0");
			pic = m_game->GetSystemPicture(name);
			m_percentSuuji0 = new CSuuji(pic, m_percentFontSizeX, m_percentFontSizeY, 3, m_percentFontNextX);

			name = m_defaultFontFileName;
			GetInitGameString(&name, "fileNamePercentPic100");
			pic = m_game->GetSystemPicture(name);
			m_percentSuuji100 = new CSuuji(pic, m_percentFontSizeX, m_percentFontSizeY, 3, m_percentFontNextX);
		}


	}

	//Šg’£—p
	m_charaVoiceFlag = 0;
	GetInitGameParam(&m_charaVoiceFlag,"charaVoiceFlag");

	m_charaVoiceFileName = NULL;
	m_charaVoiceWaitTime = 10;

	if (m_charaVoiceFlag)
	{
		GetInitGameParam(&m_charaVoiceWaitTime,"charaVoiceWaitTime");
		m_charaVoiceFileName = new char* [m_sceneCharaKosuu];
		for (int i=0;i<m_sceneCharaKosuu;i++)
		{
			char name[256];
			wsprintf(name,"charaVoiceFileName%d",i);
			//GetInitGameString(&m_charaVoiceFileName[i],name);
		}
	}

	m_length = 8;
	m_back = m_game->GetBackButton();



	m_heartPrintX = 0;
	m_heartPrintY = 0;
	m_heartSizeX = 16;
	m_heartSizeY = 16;

	m_heartPic = NULL;

	m_heartPrintFlag = 0;
	GetInitGameParam(&m_heartPrintFlag,"heartPrintFlag");

	if (m_heartPrintFlag)
	{
		GetInitGameParam(&m_heartPrintX,"heartPrintX");
		GetInitGameParam(&m_heartPrintY,"heartPrintY");

		GetInitGameParam(&m_heartSizeX,"heartSizeX");
		GetInitGameParam(&m_heartSizeY,"heartSizeY");

		LPSTR filenameHeart = m_defaultHeartFileName;
		GetInitGameString(&filenameHeart,"filenameHeart");


		char filename[256];
		wsprintf(filename,"sys\\%s",filenameHeart);
		m_heartPic = new CPicture(filename);
	}

	m_selectCommonSceneCharaSound = -1;
	GetInitGameParam(&m_selectCommonSceneCharaSound,"selectSound");

//	m_back = m_game->GetBackButton();
	
	m_startupWait = 2;

//	GetBackButtonPara();
	CreateBackButton();

	GetBGMSetup();
	GetFadeInOutSetup();
	GetEnterExitVoiceFileName();

}


CCommonSelectSceneChara::~CCommonSelectSceneChara()
{
	End();
}

void CCommonSelectSceneChara::End(void)
{
//	ENDDELETECLASS(m_kazariPic);
	ENDDELETECLASS(m_cursorPic);
	ENDDELETECLASS(m_heartPic);
	DELETEARRAY(m_sceneHMode);
	DELETEARRAY(m_zahyo);
	ENDDELETECLASS(m_totalPercentSuuji);
	ENDDELETECLASS(m_percentSuuji);
	ENDDELETECLASS(m_percentSuuji0);
	ENDDELETECLASS(m_percentSuuji100);
	DELETEARRAY(m_charaVoiceFileName);
}



int CCommonSelectSceneChara::Init(void)
{
	m_game->SetDefaultFrameRate();

	m_back->Init();
	SetBackButtonZahyo();

	char filename[1024];
	wsprintf(filename,"sys\\%s",m_filenameBG);
	
	if (m_backScriptFlag == 0)
	{
		m_commonBG->LoadDWQ(filename);
	}

	if (m_pictureMode != 0)
	{
		wsprintf(filename,"sys\\%s",m_filenameButton);
		m_commonParts->LoadDWQ(filename);
	}



//	m_commonParts->LoadDWQ("sys\\ta_cgm_cur");

	m_nowSelectNumber = -1;
	m_maeSelectNumber = -1;
	m_selectedNumber = -1;

	if (m_backScriptEndFlag == 0)
	{
		m_commonBG->Put(0,0,FALSE);
	}


	for (int i=0;i<m_sceneCharaKosuu;i++)
	{
		int sceneKosuu = 0;
		int hSceneKosuu = 0;
		if (m_sceneDataControl != NULL)
		{
			sceneKosuu = m_sceneDataControl->GetSceneKosuu(i);
			hSceneKosuu = m_sceneDataControl->GetHSceneKosuu(i);
		}

		int scene = 0;
		int hScene = 0;

		for (int k=0;k<sceneKosuu;k++)
		{
			BOOL fl = 0;
			if (m_sceneDataControl != NULL)
			{
				fl = m_sceneDataControl->CheckGetScene(i,k);
			}

//			if (m_game->CheckGetScene(i,k))
			if (fl)
			{
				scene++;
				int fl2 = 0;
				if (m_sceneDataControl != NULL)
				{
					fl2 = m_sceneDataControl->CheckHScene(i,k);
				}

//				if (m_game->CheckHScene(i,k))
				if (fl2)
				{
					hScene++;
				}
			}
		}

		if (hSceneKosuu == 0)
		{
			m_sceneHMode[i] = 0;
		}
		else
		{
			if (hScene == 0)
			{
				m_sceneHMode[i] = 1;
			}
			else if (hScene < hSceneKosuu)
			{
				m_sceneHMode[i] = 2;
			}
			else
			{
				m_sceneHMode[i] = 3;
			}
		}

		if (m_pictureMode == 1)
		{
			POINT pt = GetZahyo(i);
			int srcX = (i % m_picNumberX) * m_sizeX;
			int srcY = (i / m_picNumberX) * m_sizeY;

			if (m_backScriptFlag == 0)
			{
				m_commonParts->Blt(pt.x,pt.y,srcX,srcY,m_sizeX,m_sizeY,TRUE);
			}
		}


		if (m_backScriptFlag == 0)
		{
			if ((m_pictureMode == 0) || (m_pictureMode == 1))
			{
				if (m_kazariPrintFlag)
				{
					PrintKazari(i);
				}
				if (m_charaPercentPrintFlag)
				{
					PrintCharaPercent(i);
				}

				if (m_heartPrintFlag)
				{
					PrintCharaHeart(i);
				}
			}
		}
	}

	int totalPercent = 0;
	if (m_sceneDataControl != NULL)
	{
		totalPercent = m_sceneDataControl->GetTotalScenePercent();
	}
	m_totalPercent = totalPercent;
	//put percent
	if (m_totalPercentPrintFlag)
	{
		m_totalPercentSuuji->Print(m_totalPercentPrintX,m_totalPercentPrintY,totalPercent);
		if (m_totalPercentPercentFlag)
		{
			if (m_backScriptFlag == 0)
			{
				m_totalPercentSuuji->Put(m_totalPercentPrintX+m_totalPercentFontNextX*3,m_totalPercentPrintY,12,0);
			}
		}
	}

	//m_game->StopVoice();	‚¢‚ç‚È‚¢‚Ì‚Å‚Í???

	LoadBackButtonPic();

	if (m_backScriptFlag == 0)
	{
		m_commonBG->GetScreen();
	}

	return -1;
}


int CCommonSelectSceneChara::Calcu(void)
{
	if (m_backScriptFlag)
	{
		m_game->CalcuBackScript();
	}

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

			m_game->SetDefaultFrameRate();
			if (m_sceneDataControl != NULL)
			{
				m_sceneDataControl->SetSceneCharaNumber(m_selectedNumber);
			}
//			m_game->SetSceneNumber(0);
			if (m_sceneDataControl != NULL)
			{
				m_sceneDataControl->SetSceneNumber(0);
			}
			m_game->SetCommonBackMode(SELECTSCENE_MODE,SELECTSCENECHARA_MODE);
			
			return ReturnFadeOut(SELECTSCENE_MODE);
//			return SELECTSCENE_MODE;
		}
		return -1;
	}


	int rt = m_back->Calcu(m_inputStatus);
	if (rt != NNNBUTTON_NOTHING)
	{
		int nm = ProcessCommonButton(rt);
		int st = CCommonButton::GetButtonStatus(rt);
		if (nm == 0)
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
			if (m_selectCommonSceneCharaSound != -1)
			{
				m_game->PlayCommonSystemSound(m_selectCommonSceneCharaSound-1);
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


	return -1;
//	return m_nextMode;
}

int CCommonSelectSceneChara::Print(void)
{
	PrintBackScriptOrBG();

	BOOL b = CAreaControl::CheckAllPrintMode();


	//put percent
	if (m_totalPercentPrintFlag)
	{
		if (m_backScriptFlag)
		{
			m_totalPercentSuuji->Print(m_totalPercentPrintX,m_totalPercentPrintY,m_totalPercent);
			if (m_totalPercentPercentFlag)
			{
				m_totalPercentSuuji->Put(m_totalPercentPrintX+m_totalPercentFontNextX*3,m_totalPercentPrintY,12,0);
			}
		}
	}


	m_back->Print(TRUE);


	for (int i=0;i<m_sceneCharaKosuu;i++)
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

	return -1;
}

BOOL CCommonSelectSceneChara::CheckOnButton(int n, int mouseX, int mouseY)
{
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



int CCommonSelectSceneChara::GetOnButton(int mouseX,int mouseY)
{
	for (int i=0;i<m_sceneCharaKosuu;i++)
	{
		if (CheckOnButton(i,mouseX,mouseY)) return i;
	}

	return -1;
}

POINT CCommonSelectSceneChara::GetPicSrcZahyo(int n,BOOL eraseFlag)
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


void CCommonSelectSceneChara::EraseChara(int n)
{
	POINT pt = GetZahyo(n);
	int putX = pt.x;
	int putY = pt.y;
	int sizeX = m_sizeX;
	int sizeY = m_sizeY;

	if (m_backScriptFlag == 0)
	{
		m_commonBG->Blt(putX,putY,putX,putY,sizeX,sizeY,FALSE);
	}


	if ((m_pictureMode == 1) || (m_pictureMode == 3))
	{
		POINT pt = GetZahyo(n);
		POINT pt2 = GetPicSrcZahyo(n,TRUE);

//		int srcX = (n % m_picNumberX) * m_sizeX;
//		int srcY = (n / m_picNumberX) * (m_sizeY * 2);
		int srcX = pt2.x;
		int srcY = pt2.y;

		m_commonParts->Blt(pt.x,pt.y,srcX,srcY,m_sizeX,m_sizeY,TRUE);
	}

	if (m_kazariPrintFlag)
	{
		PrintKazari(n);
	}

	if (m_charaPercentPrintFlag)
	{
		PrintCharaPercent(n);
	}

	CAreaControl::AddArea(putX,putY,sizeX,sizeY);
}



void CCommonSelectSceneChara::PrintChara(int n)
{
	POINT pt = GetZahyo(n);
	int putX = pt.x;
	int putY = pt.y;
	int sizeX = m_sizeX;
	int sizeY = m_sizeY;

	POINT pt2 = GetPicSrcZahyo(n);
	int srcX = pt2.x;
	int srcY = pt2.y;

	if (m_backScriptFlag == 0)
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

		if (m_kazariPrintFlag)
		{
			PrintKazari(n);
		}
		if (m_charaPercentPrintFlag)
		{
			PrintCharaPercent(n);
		}
	}
	

	if ((m_pictureMode == 2) || (m_pictureMode == 3))
	{
		if (m_heartPrintFlag)
		{
			PrintCharaHeart(n);
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





//POINT CCommonSelectSceneChara::GetZahyo(int n)
//{
	//return m_buttonZahyo[n];
//}

void CCommonSelectSceneChara::PrintKazari(int n)
{
	if (m_kazariPrintFlag)
	{
		int ps = 0;
		if (m_sceneDataControl != NULL)
		{
			ps = m_sceneDataControl->GetScenePercent(n);
		}

		int picNumber = 0;

		if (ps == 0)
		{
			picNumber = 1;
		}
		else if (ps < 100)
		{
			picNumber = 2;
		}
		else
		{
			picNumber = 3;
		}

		POINT pt = GetZahyo(n);

		m_kazariPic->Blt(pt.x+m_kazariPrintX,pt.y+m_kazariPrintY, m_kazariSizeX * picNumber, 0, m_kazariSizeX, m_kazariSizeY, TRUE);
	}

}


void CCommonSelectSceneChara::PrintCharaHeart(int n)
{
	POINT pt = GetZahyo(n);

	int putX = pt.x + m_heartPrintX;
	int putY = pt.y + m_heartPrintY;

	int sizeX = m_heartSizeX;
	int sizeY = m_heartSizeY;

		//heart
	int hMode = m_sceneHMode[n];
	if (hMode > 0)
	{
		if (hMode == 1) m_heartPic->Blt(putX,putY,sizeX*0,0,sizeX,sizeY,TRUE);
		if (hMode == 2) m_heartPic->Blt(putX,putY,sizeX*1,0,sizeX,sizeY,TRUE);
		if (hMode == 3) m_heartPic->Blt(putX,putY,sizeX*3,0,sizeX,sizeY,TRUE);
	}
	else
	{
		int ps = 0;
		if (m_sceneDataControl != NULL)
		{
			ps = m_sceneDataControl->GetScenePercent(n);
		}

		if (ps>=100)
		{
			m_heartPic->Blt(putX,putY,sizeX*2,0,sizeX,sizeY,TRUE);
		}
	}
}

void CCommonSelectSceneChara::PrintCharaPercent(int n)
{
	int ps = 0;
	if (m_sceneDataControl != NULL)
	{
		ps = m_sceneDataControl->GetScenePercent(n);
	}
	POINT pt = GetZahyo(n);

	int x = pt.x + m_percentPrintX;
	int y = pt.y + m_percentPrintY;

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

void CCommonSelectSceneChara::CreateStartScreen(void)
{
	//menu setup?

	//script exec?

	Print();
}
