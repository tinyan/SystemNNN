//
// CommonLoadSave.cpp
//

#include <windows.h>
#include <stdio.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\allGeo.h"
#include "..\nyanLib\include\picture.h"

#include "..\nyanEffectLib\effectstruct.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"

#include "..\nnnUtilLib\nnnButtonStatus.h"

#include "..\nnnUtilLib\commonButton.h"
#include "..\nnnUtilLib\commonButtonGroup.h"

#include "..\nnnUtilLib\commonBackButton.h"

#include "..\nnnUtilLib\commonUpDownBack.h"

#include "..\nnnUtilLib\commonMultiStateButton.h"
#include "..\nnnUtilLib\commonCheckButton.h"
#include "..\nnnUtilLib\commonRadioButton.h"
#include "..\nnnUtilLib\commonRadioButtonGroup.h"

#include "..\nnnUtilLib\suuji.h"

#include "..\nnnUtilLib\pagePrint.h"

#include "commonGeneral.h"

#include "commonDataFile.h"

#include "commonSystemSoundName.h"

#include "commonMode.h"
#include "commonSystemParamName.h"

#include "..\nnnUtilLib\scriptcommand.h"

#include "..\nnnUtilLib\commonKeyList.h"

#include "..\nnnUtilLib\myMessage.h"

#include "..\nnnUtilLib\dataFileSetup.h"

#include "..\\nnnUtilLib\superButtonPicture.h"

#include "..\nnnUtilLib\mytextInputBox.h"

#include "..\\nnnUtilLib\commonAnimeParts.h"

#include "CommonLoadSave.h"

#include "gameCallBack.h"


//char CCommonLoadSave::m_defaultSuujiFileName[] = "ta_sl_font3";

//char CCommonLoadSave::m_defaultBGFileName[] = "save_bg";
//char CCommonLoadSave::m_defaultDialogFileName[] = "ta_dialog_4";
//char CCommonLoadSave::m_defaultButtonFileName[] = "ta_dialog_bt1";



CCommonLoadSave::CCommonLoadSave(CGameCallBack* lpGame,LPSTR modename) : CCommonGeneral(lpGame)
{
	m_classNumber = SAVE_MODE;
	LoadSetupFile(modename,1000);

	m_dataFileSetup = m_game->GetDataFileSetup();

	m_quickLoadEnable = m_game->GetQuickLoadEnable();
	m_quickSaveEnable = m_game->GetQuickSaveEnable();

	m_savePicSize = m_dataFileSetup->GetSavePicSize();


	m_quickLoadSelectOk = 0;
	m_quickSaveSelectOk = 0;

	m_quickLoadSlotNumber = m_dataFileSetup->GetQuickSlotNumber();
	m_quickSaveSlotNumber = m_dataFileSetup->GetQuickSlotNumber();

//	m_quickLoadSelectOk = m_dataFileSetup->GetQuickLoadSelectOk();
//	m_quickSaveSelectOk = m_dataFileSetup->GetQuickSaveSelectOk();


	GetBackExecSetup();
	GetAllPrintSetup();


	wsprintf(m_defaultBGFileName,"%s_bg",modename);

	m_bgFileName = m_defaultBGFileName;
	GetInitGameString(&m_bgFileName,"fileNameBG");

	m_pageMax = 10;
	GetInitGameParam(&m_pageMax,"page");

	m_pageMode = 0;
	if (m_pageMax > 1)
	{
		m_pageMode = 1;
	}
	GetInitGameParam(&m_pageMode,"pageMode");



	m_printLastSelect = NULL;
	int lastSelectFlag = 0;
	GetInitGameParam(&lastSelectFlag,"lastSelectFlag");
	if (lastSelectFlag)
	{
		m_printLastSelect = m_dataFileSetup->GetPrintLastSelect();
	}



	m_warningUpDownBackPrintFlag = 1;
	GetInitGameParam(&m_warningUpDownBackPrintFlag,"warningUpDownBackPrintFlag");

	m_blockX = 4;
	m_blockY = 3;

	GetInitGameParam(&m_blockX,"blockNumberX");
	GetInitGameParam(&m_blockY,"blockNumberY");

	m_nextX = 166;
	m_nextY = 124;
	m_printX = 85;
	m_printY = 113;

	GetInitGameParam(&m_printX,"printX");
	GetInitGameParam(&m_printY,"printY");
	GetInitGameParam(&m_nextX,"nextX");
	GetInitGameParam(&m_nextY,"nextY");


	CPicture* lpBG = m_commonBG;
	if (m_backScriptFlag) lpBG = NULL;
	if (m_mustAllPrintFlag) lpBG = NULL;


	m_ppDataFile = new CCommonDataFile*[m_blockX*m_blockY];

	m_dataPrintCustomFlag = 0;
	GetInitGameParam(&m_dataPrintCustomFlag,"dataPrintCustomFlag");
	for (int i=0;i<m_blockX * m_blockY;i++)
	{
		int x = m_printX + (i % m_blockX) * m_nextX;
		int y = m_printY + (i / m_blockX) * m_nextY;

		if (m_dataPrintCustomFlag)
		{
			char name[256];
			wsprintf(name,"dataPrintX%d",i+1);
			GetInitGameParam(&x,name);

			wsprintf(name,"dataPrintY%d",i+1);
			GetInitGameParam(&y,name);
		}

		m_ppDataFile[i] = new CCommonDataFile(m_game,x,y,lpBG);
	}

	m_nowSelect = -1;
	m_maeSelect = -1;

	m_page = 0;
	m_warningFlag = 0;
	m_commentInputFlag = 0;

	m_pagePrint = new CPagePrint(m_setup,lpBG);

	m_warningPrintFlag = 0;

	m_clickTime = 8;
	GetInitGameParam(&m_clickTime,"clickTime");
	m_dialogButton = NULL;
	m_dialogButton2 = NULL;


	m_menuStartWaitTime = 0;
	m_menuStartEffectTime = 0;
	m_menuStartEffectType = 0;

	GetInitGameParam(&m_menuStartWaitTime, "menuStartWaitTime");
	GetInitGameParam(&m_menuStartEffectTime, "menuStartEffectTime");
	GetInitGameParam(&m_menuStartEffectType, "menuStartEffectType");


	CreateBackButton();
	if (m_pageMode == 1)
	{
		CreateUpDownButton();
		CreateUpDownBack();
	}

	m_tabButton = NULL;
	if (m_pageMode == 2)
	{
		m_tabButton = new CCommonRadioButtonGroup(m_setup,"tab",lpBG,m_pageMax,NULL);

		for (int i=0;i<m_pageMax;i++)
		{
//			CPicture* lpPic = GetUseOkPicture(-1);	//use all
			CPicture* lpPic = CSuperButtonPicture::GetPicture(7+i);
			m_tabButton->SetPicture(lpPic,i,-1);
		}
	}


	m_textInputBox = NULL;

	m_inputDialog = NULL;

	GetBGMSetup();

	m_notInitPage = false;

	if (_stricmp(modename,"load") == 0)
	{
		m_exitFadeOutSpecialMode = TITLE_MODE;
		m_createExitScreenFlagSpecial = 1;
	}

	GetFadeInOutSetup();
	GetEnterExitVoiceFileName();
	GetDialogVoiceFileName();

	m_initStartWait = false;

}




CCommonLoadSave::~CCommonLoadSave()
{
	End();
}

void CCommonLoadSave::End(void)
{
	ENDDELETECLASS(m_tabButton);

	if (m_ppDataFile != NULL)
	{
		for (int i=0;i<m_blockX*m_blockY;i++)
		{
			ENDDELETECLASS(m_ppDataFile[i]);
		}
		DELETEARRAY(m_ppDataFile);
	}
	ENDDELETECLASS(m_pagePrint);
}



int CCommonLoadSave::Init(void)
{
	m_loadCommandFlag = FALSE;
	if (m_printLastSelect != NULL)
	{
		m_printLastSelect->Init();
	}

	m_appearCount = 1;
	m_appearCountMax = 1;

	if (!m_initStartWait)
	{
		m_menuStartCount = 0;
	}

	if (!m_notInitPage)
	{
		int last = m_game->GetLastSelectSaveLoad();
		if (last >= 0)
		{
			m_page = last / (m_blockX * m_blockY);
			if (m_page >= m_pageMax)
			{
				m_page = m_pageMax - 1;
			}
			if (m_page < 0)
			{
				m_page = 0;
			}
		}
	}



	m_game->StopScriptSoundAndVoice();

	if (m_backScriptFlag == FALSE)
	{
		LoadBG();
	}

	if (m_warningPrintFlag)
	{
		char filename[256];
		wsprintf(filename,"sys\\%s",m_dialogFileName);
		m_commonParts->LoadDWQ(filename);
	}

	if (m_pageMode == 1)
	{
		m_updownBack->SetPage(m_page);
		m_updownBack->SetPageMax(m_pageMax);
		m_updownBack->Init();
	}
	else if (m_pageMode == 2)
	{
		m_tabButton->SetRadio(m_page);
		m_tabButton->Init(m_page);
	}


	int i = 0;
	for (i=0;i<m_blockX * m_blockY;i++)
	{
		int n = i + m_page * m_blockX * m_blockY;
		m_ppDataFile[i]->LoadHeaderAndPic(n);
		m_ppDataFile[i]->InitAnime();
	}

	LoadBackButtonPic();
	SetBackButtonZahyo();


	if (m_pageMode == 0)
	{
		m_back->Init();
	}
	else if (m_pageMode == 1)
	{
		LoadUpDownButtonPic();
		m_updownBack->Init();
		m_updownBack->SetPage(m_page);
	}
	else if (m_pageMode == 2)
	{
		m_back->Init();
		ReLoadTabPic();
		m_tabButton->Init(m_page);
	}






	if (m_warningPrintFlag)
	{
		for (i=0;i<2;i++)
		{
			CPicture* lpPic = m_dialogButton->GetPicture(i);
			LPSTR name = m_dialogButton->GetFileName(i);
			char filename[256];
			wsprintf(filename,"sys\\%s",name);
			lpPic->LoadDWQ(filename);
		}
	}

	if (m_commentInputFlag)
	{
		for (int i=0;i<2;i++)
		{
			CPicture* lpPic = m_dialogButton2->GetPicture(i);
			LPSTR name = m_dialogButton2->GetFileName(i);
			char filename[256];
			wsprintf(filename,"sys\\%s",name);
			lpPic->LoadDWQ(filename);
		}
	}


	m_nowSelect = -1;
	m_maeSelect = -1;

	m_clickingFlag = FALSE;
	m_clickingCount = 0;
	m_warningFlag = 0;

	return -1;
}



int CCommonLoadSave::Calcu(void)
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



	if (m_warningFlag == 1)
	{
		CAreaControl::SetNextAllPrint();
		return CalcuWarning();
	}

	if (m_warningFlag == 2)
	{
		CAreaControl::SetNextAllPrint();
		return CalcuComment();
	}

	if (m_clickingFlag)
	{
		if (m_clickButtonNumber < -1)
		{
			int rt = NNNBUTTON_NOTHING;
			int rt2 = NNNBUTTON_NOTHING;

			if (m_pageMode == 0)
			{
				rt = m_back->Calcu(m_inputStatus);
			}
			else if (m_pageMode == 1)
			{
				rt = m_updownBack->Calcu(m_inputStatus);
			}
			else if (m_pageMode == 2)
			{
				rt = m_tabButton->Calcu(m_inputStatus);
				rt2 = m_back->Calcu(m_inputStatus);

			}

			if ((m_pageMode == 0) || (m_pageMode == 1))
			{
				int nm;

				if (m_pageMode == 0)
				{
					nm = ProcessCommonButton(rt);
				}
				else
				{
					nm = ProcessUpDownBack(rt);
				}

				if (nm == 0)
				{
					m_game->FuqueAllEffectYoyaku();
					return ReturnFadeOut(m_backMode);
				}
				else if (nm > 0)
				{
					ChangePage(nm-1);
				}

				return -1;
			}

			if (m_pageMode == 2)
			{
				if (rt2 != NNNBUTTON_NOTHING)
				{
					int nm = ProcessCommonButton(rt2);
					if (nm == 0)
					{
						m_game->FuqueAllEffectYoyaku();
						return ReturnFadeOut(m_backMode);
					}
				}

				if (rt != NNNBUTTON_NOTHING)
				{
					int nm = ProcessButtonGroup(rt);
					if (nm >= 0)
					{
						ChangePage(nm);
						return -1;
					}
				}

				return -1;
			}

			return -1;
		}
		else if (m_clickButtonNumber >= 0)
		{
			if (m_pageMode == 0)
			{
				m_back->Calcu(NULL);
			}
			else if (m_pageMode == 1)
			{
				m_updownBack->Calcu(NULL);
			}
			else if (m_pageMode == 2)
			{
				m_tabButton->Calcu(NULL);
			}
			
			m_clickingCount++;
			if (m_clickingCount >= m_clickTime)
			{
				//load or save
				if (m_classNumber != LOAD_MODE)
				{
					return ProcessDataClicked(m_clickButtonNumber);
				}

				int rtcd = m_ppDataFile[m_clickButtonNumber]->GetSaveMode();
				m_loadCommandFlag = TRUE;
				return ReturnFadeOut(-1);
				//return ReturnFadeOut(rtcd);


/*
				if (m_exitFadeOutType == 0)
				{
					return ProcessDataClicked(m_clickButtonNumber);
				}

				m_loadFadeOutPrintFlag = TRUE;
				CAreaControl::SetNextAllPrint();
				int fadeOutTime = m_exitFadeOutTime;
				if (m_clickingCount >= (m_clickTime + m_exitFadeOutTime))
				{
					return ProcessDataClicked(m_clickButtonNumber);
				}

				return -1;
				return ProcessDataClicked(m_clickButtonNumber);
*/
				//•ÏX—\’è
				//int rt666 = ReturnFadeOut(0);
				//if (rt666 == 0) rt666= ProcessDataClicked(m_clickButtonNumber);
				//return rt666;
			}
			return -1;
			//clicking data area
		}
		else
		{
			//error
			m_clickingFlag = FALSE;
			return -1;
		}
	}

	if (m_printLastSelect != NULL)
	{
		m_printLastSelect->Calcu();
	}

	int rt = NNNBUTTON_NOTHING;
	int rt2 = NNNBUTTON_NOTHING;

	if (m_pageMode == 0)
	{
		rt = m_back->Calcu(m_inputStatus);
	}
	else if (m_pageMode == 1)
	{
		rt = m_updownBack->Calcu(m_inputStatus);
	}
	else if (m_pageMode == 2)
	{
		rt = m_tabButton->Calcu(m_inputStatus);
		rt2 = m_back->Calcu(m_inputStatus);
	}

	if ((m_pageMode == 0) || (m_pageMode == 1))
	{
		if (rt != NNNBUTTON_NOTHING)
		{
			int nm;

			if (m_pageMode == 0)
			{
				nm = ProcessCommonButton(rt);
			}
			else
			{
				nm = ProcessUpDownBack(rt);
			}

			if (nm == 0)
			{
				m_game->FuqueAllEffectYoyaku();
	//			m_game->FuqueAllEffect();
				return ReturnFadeOut(m_backMode);
			}
			else if (nm > 0)
			{
				ChangePage(nm-1);
				return -1;
			}
		
			int st = CCommonButton::GetButtonStatus(rt);
			
			if (st == NNNBUTTON_STARTCLICK)
			{
				m_clickingCount = 0;
				m_clickingFlag = TRUE;
				m_clickButtonNumber = -2;
				return -1;
			}
		}
	}
	else if (m_pageMode == 2)
	{
		if (rt2 != NNNBUTTON_NOTHING)
		{
			int nm = ProcessCommonButton(rt2);
			if (nm == 0)
			{
				m_game->FuqueAllEffectYoyaku();
				return ReturnFadeOut(m_backMode);
			}
		}

		if (rt != NNNBUTTON_NOTHING)
		{
			int nm = ProcessButtonGroup(rt);
			if (nm >= 0)
			{
				ChangePage(nm);
				return -1;
			}
		
			int st = CCommonButton::GetButtonStatus(rt);
			
			if (st == NNNBUTTON_STARTCLICK)
			{
				m_clickingCount = 0;
				m_clickingFlag = TRUE;
				m_clickButtonNumber = -2;
				return -1;
			}
		}

	}

	int buttonKosuu = m_blockX * m_blockY;

	int onButton = -1;
	POINT mousePoint = m_mouseStatus->GetZahyo();

	int mouseX = mousePoint.x;
	int mouseY = mousePoint.y;

	int onLoadSlot = -1;

	for (int i=0;i<buttonKosuu;i++)
	{
		int n = m_page * m_blockX * m_blockY + i;

		if (m_ppDataFile[i]->CheckOn(mouseX,mouseY))
		{
			if (m_classNumber == SAVE_MODE)
			{
				if (m_quickSaveEnable && (n == m_quickSaveSlotNumber))
				{
					if (m_quickSaveSelectOk)
					{
						onButton = i;
					}
				}
				else
				{
					onButton = i;
				}
				break;
			}

			onLoadSlot = i;

			if (CheckDataExist(i))
			{
				if (CheckDataVersion(i))
				{
					if (m_quickLoadEnable && (n == m_quickLoadSlotNumber))
					{
						if (m_quickLoadSelectOk)
						{
							onButton = i;
						}
					}
					else
					{
						onButton = i;
					}
					break;
				}
			}

		}
	}

	m_maeSelect = m_nowSelect;
	m_nowSelect = onButton;

	if (m_maeSelect != m_nowSelect)
	{
		if (m_maeSelect != -1)
		{
			m_ppDataFile[m_maeSelect]->InitAnime();
		}

		if (m_nowSelect != -1)
		{
			m_ppDataFile[m_nowSelect]->InitAnime();
		}
	}

	if (m_nowSelect != -1)
	{
		if (CheckClick())
		{
		//	m_clickButtonNumber = m_nowSelect;
			if (CheckDataExist(m_nowSelect))
			{
				if (m_classNumber == SAVE_MODE)
				{
					return ProcessStartClickExistData(m_nowSelect);
				}

				if (CheckDataVersion(m_nowSelect))
				{
					return ProcessStartClickExistData(m_nowSelect);
				}
			}

			return ProcessStartClickNotExistData(m_nowSelect);
		}
	}
	else
	{
		//check on slot
		if (m_classNumber == LOAD_MODE)
		{
			if (onLoadSlot != -1)
			{
				if (CheckClick())
				{
					return ProcessStartClickNotExistData(m_nowSelect);
				}
			}
		}
	}

	return -1;
}

//virtual dummy
int CCommonLoadSave::CalcuWarning(void)
{
	return -1;
}

//virtual dummy
int CCommonLoadSave::CalcuComment(void)
{
	return -1;
}

int CCommonLoadSave::Print(void)
{
	PrintBackScriptOrBG();

	int lastSaveSlot = m_game->GetLastSaveSlot();


	int startMode = GetStartWaitMode();



	BOOL b = CAreaControl::CheckAllPrintMode();

	if (b)
	{
		if (m_backScriptFlag == FALSE)
		{
			m_commonBG->Put(0,0,FALSE);
		}
	}

	if (m_warningFlag == 1)
	{
		if ((b == FALSE) && (m_backScriptFlag == FALSE))
		{
			m_commonBG->Blt(m_dialogX,m_dialogY,m_dialogX,m_dialogY,m_dialogSizeX,m_dialogSizeY,FALSE);
		}
	}

	if (m_warningFlag == 2)
	{
		if ((b == FALSE) && (m_backScriptFlag == FALSE))
		{
			m_commonBG->Blt(m_dialogX2,m_dialogY2,m_dialogX2,m_dialogY2,m_dialogSizeX2,m_dialogSizeY2,FALSE);
		}
	}

	if ((m_warningFlag == 0) || m_backScriptFlag || m_mustAllPrintFlag || b)
	{
		int loadsave = 0;
		if (m_classNumber == SAVE_MODE)
		{
			loadsave = 1;
		}

		for (int i=0;i<m_blockX*m_blockY;i++)
		{
			int col = 0;
			int nm = m_page * m_blockX*m_blockY + i;

			if (i == m_nowSelect) col = 1;

			if (m_clickingFlag)
			{
				if (i == m_clickButtonNumber)
				{
					col = 1;
//					col = m_clickingCount & 1;
				}
			}

			if (col == 1)
			{
				if (m_classNumber == LOAD_MODE)
				{
					col = 2;
				}
				else
				{
					if (m_ppDataFile[i]->CheckDataExist())
					{
						col = 3;
					}
				}
			}


			int clicking = 0;
			if (m_clickingFlag)
			{
				if (i == m_clickButtonNumber)
				{
					clicking = m_clickingCount + 1;
				}
			}


			if (m_classNumber == LOAD_MODE)
			{
				if (m_ppDataFile[i]->CheckDataExist() == FALSE)
				{
					col = 0;
				}
			}
			else
			{
			}

			BOOL f = b;
			if (m_backScriptFlag) f = TRUE;
			if (i == m_nowSelect) f = TRUE;
			if (i == m_maeSelect) f = TRUE;
			if (i == m_clickButtonNumber) f = TRUE;

			if (m_warningFlag > 0)
			{
				clicking = 0;
			}

			int lastCount = 0;
			if (m_printLastSelect != NULL)
			{
				if (nm == lastSaveSlot)
				{
					f = TRUE;
					lastCount = 1;
				}
			}


			if (f)
			{
//				m_ppDataFile[i]->Print(col,clicking,nm,loadsave,lastCount);

				m_ppDataFile[i]->AppearPrint(m_appearCount, m_appearCountMax, m_menuStartEffectType,col, clicking, nm, loadsave, lastCount);

				//AppearPrint(m_appearCount, m_appearCountMax, m_menuStartEffectType);
			}
		}
	}






	if (m_warningFlag == 0)
	{
		if (m_pageMode == 0)
		{
//			m_back->Print(TRUE);
			m_back->AppearPrint(m_appearCount, m_appearCountMax, m_menuStartEffectType);

		}
		else if (m_pageMode == 1)
		{
//			m_updownBack->Print(TRUE);
			m_updownBack->AppearPrint(m_appearCount, m_appearCountMax, m_menuStartEffectType);
		}
		else if (m_pageMode == 2)
		{
//			m_back->Print(TRUE);
//			m_tabButton->Print(TRUE);
			m_back->AppearPrint(m_appearCount, m_appearCountMax, m_menuStartEffectType);
			m_tabButton->AppearPrint(m_appearCount, m_appearCountMax, m_menuStartEffectType);
		}
//		m_updownBack->Print(TRUE);
	}
	else if (m_warningFlag == 1)
	{

		m_commonParts->Put(m_dialogX,m_dialogY,TRUE);
		if (m_dialogButton != NULL) m_dialogButton->Print(TRUE);
		CAreaControl::AddArea(m_dialogX,m_dialogY,m_dialogSizeX,m_dialogSizeY);
		
		if (m_warningUpDownBackPrintFlag)
		{

			if (m_pageMode == 0)
			{
				m_back->ResetAnimeCount();
				m_back->Print(TRUE);
			}
			else if (m_pageMode == 1)
			{
				m_updownBack->ResetAnimeCount();
				m_updownBack->Print(TRUE);
			}
			else if (m_pageMode == 2)
			{
				m_back->ResetAnimeCount();
				m_back->Print(TRUE);
				m_tabButton->ResetAnimeCount();
				m_tabButton->Print(TRUE);
			}
		}

	}
	else if (m_warningFlag == 2)
	{
		if (m_dialogButton2 != NULL) m_dialogButton2->Print(TRUE);
		CAreaControl::AddArea(m_dialogX2,m_dialogY2,m_dialogSizeX2,m_dialogSizeY2);

		m_inputDialog->Put(m_dialogX2,m_dialogY2,TRUE);
		if (m_dialogButton2 != NULL) m_dialogButton2->Print(TRUE);
		CAreaControl::AddArea(m_dialogX2,m_dialogY2,m_dialogSizeX2,m_dialogSizeY2);
		
		PrintInputBoxStatus();

		if (m_textInputBox != NULL)
		{
			m_textInputBox->Print();
		}

		if (m_warningUpDownBackPrintFlag)
		{

			if (m_pageMode == 0)
			{
				m_back->ResetAnimeCount();
				m_back->Print(TRUE);
			}
			else if (m_pageMode == 1)
			{
				m_updownBack->ResetAnimeCount();
				m_updownBack->Print(TRUE);
			}
			else if (m_pageMode == 2)
			{
				m_back->ResetAnimeCount();
				m_back->Print(TRUE);
				m_tabButton->ResetAnimeCount();
				m_tabButton->Print(TRUE);
			}
		}

	}


//	m_pagePrint->Print(m_page+1,m_pageMax);
	m_pagePrint->AppearPrint(m_appearCount,m_appearCountMax,m_menuStartEffectType, m_page + 1, m_pageMax);

/*
	if (m_classNumber == LOAD_MODE)
	{
		if (m_loadFadeOutPrintFlag)
		{
			int fadeOutTime = m_exitFadeOutTime;
			int c = m_clickingCount - m_clickTime;
			int dv = fadeOutTime;
			if (dv<1) dv = 1;
			int ps = (c * 100) / dv;
			if (ps<1) ps = 1;
			if (ps>100) ps = 100;
			int colR = m_exitFadeOutColorR;
			int colG = m_exitFadeOutColorG;
			int colB = m_exitFadeOutColorB;

			int screenSizeX = CMyGraphics::GetScreenSizeX();
			int screenSizeY = CMyGraphics::GetScreenSizeY();
			CAllGeo::TransBoxFill(0,0,screenSizeX,screenSizeY,colR,colG,colB,ps);
		}
	}
*/

	return -1;
}


void CCommonLoadSave::LoadBG(void)
{
	char filename[256];

	wsprintf(filename,"sys\\%s",m_bgFileName);
	m_commonBG->LoadDWQ(filename);
}

void CCommonLoadSave::ChangePage(int page)
{
	m_page = page;
	if (m_page<0) m_page = 0;
	if (m_page >= m_pageMax) m_page = m_pageMax - 1;

	//reload

	CAreaControl::SetNextAllPrint();
	m_notInitPage = true;
	m_initStartWait = true;
	Init();
	m_initStartWait = false;
	m_notInitPage = false;
}


BOOL CCommonLoadSave::CheckDataExist(int n)
{
	int nm = n * (m_page * m_blockX * m_blockY);
	return m_ppDataFile[n]->CheckDataExist();
}

BOOL CCommonLoadSave::CheckDataVersion(int n)
{
	int nm = n * (m_page * m_blockX * m_blockY);
	return m_ppDataFile[n]->CheckLoadOkVersion();
}

void CCommonLoadSave::InitAnime(void)
{
	for (int i=0;i<m_blockX * m_blockY;i++)
	{
		m_ppDataFile[i]->InitAnime();
	}
}


void CCommonLoadSave::ReLoadTabPic(void)
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

void CCommonLoadSave::ChangeExtDataSize(int extNumber,int dataSize)
{
	for (int i=0;i<m_blockX * m_blockY;i++)
	{
		m_ppDataFile[i]->ChangeExtDataSize(extNumber,dataSize);
	}

}


int CCommonLoadSave::GetStartWaitMode(void)
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

void CCommonLoadSave::EndStartWaitMode(void)
{
	m_menuStartCount = m_menuStartWaitTime + m_menuStartEffectTime;
	//m_game->InitMiniGameButton(OMAKE_MODE);
}

/*_*/



