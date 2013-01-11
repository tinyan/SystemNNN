//
// commonLogo.cpp
//

#include <windows.h>


#include "..\nyanlib\include\commonMacro.h"
#include "..\nyanlib\include\areaControl.h"
#include "..\nyanlib\include\picture.h"
#include "..\nyanlib\include\myGraphics.h"

#include "..\nnnLib\commonMode.h"
#include "..\nnnLib\commonGeneral.h"
#include "..\nnnLib\gameCallBack.h"

#include "..\\nnnLib\commonSystemParamName.h"

#include "..\\nnnUtilLib\nnnButtonStatus.h"


#include "..\\nnnUtilLib\myMouseStatus.h"
#include "..\\nnnUtilLib\myKeyStatus.h"

#include "..\\nnnUtilLib\nnnButtonStatus.h"
#include "..\\nnnlib\commonSystemSoundName.h"

#include "..\\nnnUtilLib\commonButton.h"
#include "..\\nnnUtilLib\commonBackButton.h"
#include "..\\nnnUtilLib\commonupDownButtonGroup.h"
#include "..\\nnnUtilLib\commonUpDownBack.h"
#include "..\\nnnUtilLib\suuji.h"

#include "..\\nnnUtilLib\pagePrint.h"


#include "..\\nnnUtilLib\superButtonPicture.h"
#include "..\\nnnUtilLib\commonButton.h"



#include "..\\nnnUtilLib\myMouseStatus.h"
#include "..\\nnnUtilLib\mymessage.h"
#include "..\\nnnUtilLib\nameList.h"

#include "..\\nnnUtilLib\suuji.h"

#include "..\\nnnUtilLib\commonResultData.h"


#include "commonMode.h"

#include "commonPrintResult.h"
#include "gameCallBack.h"

char CCommonPrintResult::m_defaultFilenameResultsTag[] = "ta_sys_common_resultPlate";
char CCommonPrintResult::m_defaultFilenameDialogTag[] = "ta_sys_common_result_getdialog";



char CCommonPrintResult::m_defaultResultDescFileName[] = "nya\\resultDesc.xtx";
//char CCommonPrintResult::m_defaultLeftMaskFileName[] = "ta_sys_common_result_leftmask";
//char CCommonPrintResult::m_defaultRightMaskFileName[] = "ta_sys_common_result_rightmask";




CCommonPrintResult::CCommonPrintResult(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(MYPRINTRESULT_MODE);
//	m_classNumber = MYPRINTRESULT_MODE;
//	m_game2 = lpGame;

	LoadSetupFile("printResult",256);

	m_nextMode = OMAKE_MODE;
	GetModeNumberBySetup("nextMode",&m_nextMode);

	m_resultsData = m_game->GetCommonResultData();

	m_message = m_game->GetMyMessage();

	GetBackExecSetup();
	GetAllPrintSetup();


	m_resultsDesc = new CNameList();
	LPSTR resultDescFileName = m_defaultResultDescFileName;
	GetInitGameString(&resultDescFileName,"resultDescName");
	m_resultsDesc->LoadFile(resultDescFileName);
	
//	m_resultsDesc->LoadFile("asa\\resultsDesc.xtx");

	m_descPrintType = 1;
	GetInitGameParam(&m_descPrintType,"descprintType");

	if (m_descPrintType == 1)
	{
//		LPSTR leftMaskFileName = m_defaultLeftMaskFileName;
//		LPSTR rightMaskFileName = m_defaultRightMaskFileName;
//		GetInitGameString(&leftMaskFileName,"filenameLeftMask");
//		GetInitGameString(&rightMaskFileName,"filenameRightMask");

//		m_leftMaskPic = m_game->GetSystemPicture(leftMaskFileName);
//		m_rightMaskPic = m_game->GetSystemPicture(rightMaskFileName);
		//m_leftMaskPic = new CPicture("sys\\ta_asa_result_hide_l");
		//m_rightMaskPic = new CPicture("sys\\ta_asa_result_hide_r");

//		m_leftMaskPrintX = 0;
//		m_leftMaskPrintY = 475;
//		m_rightMaskPrintX = m_leftMaskPrintX + 745;
//		m_rightMaskPrintY = 475;
//		SIZE sz = m_leftMaskPic->GetPicSize();

//		m_maskSizeX = sz.cx;
//		m_maskSizeY = sz.cy;

//		GetInitGameParam(&m_leftMaskPrintX,"leftMaskPrintX");
//		GetInitGameParam(&m_leftMaskPrintY,"leftMaskPrintY");
//		GetInitGameParam(&m_rightMaskPrintX,"rightMaskPrintX");
//		GetInitGameParam(&m_rightMaskPrintY,"rightMaskPrintY");
//		GetInitGameParam(&m_maskSizeX,"maskSizeX");
//		GetInitGameParam(&m_maskSizeY,"maskSizeY");
	}




	m_messagePrintX = 56;
	m_messagePrintY = 484;
	m_messageFontSize = 22;
	m_messageColorR = 255;
	m_messageColorG = 247;
	m_messageColorB = 153;
	m_messageSukima = 1;
	m_messageLength = 33;
//	m_messageGyo = 1;

	GetInitGameParam(&m_messagePrintX,"messagePrintX");
	GetInitGameParam(&m_messagePrintY,"messagePrintY");
	GetInitGameParam(&m_messageFontSize,"messageFontSize");
	GetInitGameParam(&m_messageColorR,"messageColorR");
	GetInitGameParam(&m_messageColorG,"messageColorG");
	GetInitGameParam(&m_messageColorB,"messageColorB");
	GetInitGameParam(&m_messageSukima,"messageSukima");
	GetInitGameParam(&m_messageLength,"messageLength");
//	GetInitGameParam(&m_messageGyo,"messageGyo");
	m_messageNextY = m_messageFontSize + m_messageFontSize / 2;
	GetInitGameParam(&m_messageNextY,"messageNextY");


	m_resultsPrintX = 25;
	m_resultsPrintY = 70;
	m_resultsSizeX = 150;
	m_resultsSizeY = 200;
	GetInitGameParam(&m_resultsPrintX,"resultsPrintX");
	GetInitGameParam(&m_resultsPrintY,"resultsPrintY");
	GetInitGameParam(&m_resultsSizeX,"resultsSizeX");
	GetInitGameParam(&m_resultsSizeY,"resultsSizeY");
	m_resultsNextX = m_resultsSizeX;
	m_resultsNextY = m_resultsSizeY;
	GetInitGameParam(&m_resultsNextX,"resultsNextX");
	GetInitGameParam(&m_resultsNextY,"resultsNextY");

	m_resultsKosuu = 20;
	m_resultsNumberX = 5;
	m_resultsNumberY = 2;

	GetInitGameParam(&m_resultsKosuu,"resultsMax");
	GetInitGameParam(&m_resultsNumberX,"resultsNumberX");
	GetInitGameParam(&m_resultsNumberY,"resultsNumberY");

	m_resultsInPage = m_resultsNumberX * m_resultsNumberY;
	m_pageMax = (m_resultsKosuu + m_resultsInPage - 1) / m_resultsInPage;

	m_pagePrint = new CPagePrint(m_setup);
	m_resultsPic = new CPicture*[m_pageMax];

	m_resultsDataTable = new int[m_resultsKosuu];

	for (int i=0;i<m_pageMax;i++)
	{
		m_resultsPic[i] = CSuperButtonPicture::GetPicture(4+i);
	}

	m_dialogFlag = 1;
	GetInitGameParam(&m_dialogFlag,"dialogFlag");

	m_filenameResultsTag = m_defaultFilenameResultsTag;
	GetInitGameString(&m_filenameResultsTag,"filenameResultsTag");

	m_filenameDialogTag = m_defaultFilenameDialogTag;
	GetInitGameString(&m_filenameDialogTag,"filenameDialogTag");

	m_dialogPrintX = 170;
	m_dialogPrintY = 130;
	m_dialogSizeX = 460;
	m_dialogSizeY = 260;
	GetInitGameParam(&m_dialogPrintX,"dialogPrintX");
	GetInitGameParam(&m_dialogPrintY,"dialogPrintY");
	GetInitGameParam(&m_dialogSizeX,"dialogSizeX");
	GetInitGameParam(&m_dialogSizeY,"dialogSizeY");

	m_nowOnNumber = -1;
	m_nowOnNumber = -1;


	m_voiceStartWaitTime = 25;
	GetInitGameParam(&m_voiceStartWaitTime,"voiceStartWait");

	m_scrollStartWaitTime = 150;
	m_scrollSpeed = 3;
	GetInitGameParam(&m_scrollStartWaitTime,"scrollStartWait");
	GetInitGameParam(&m_scrollSpeed,"scrollSpeed");



	CreateBackButton();
	if (m_pageMax > 1)
	{
		CreateUpDownButton();
		CreateUpDownBack();
	}

	m_okButton = new CCommonButton(m_setup,"ok");
	POINT pt = m_okButton->GetZahyo();
	pt.x += m_dialogPrintX;
	pt.y += m_dialogPrintY;
	m_okButton->SetZahyo(pt);

	m_okButton->SetPicture(CSuperButtonPicture::GetPicture(3));

	m_messageBlockMax = 4;
	GetInitGameParam(&m_messageBlockMax,"messageBlockMax");
	m_resultsMessageAll = new char*[m_resultsKosuu];
	m_resultsMessageLength = new int[m_resultsKosuu];

	for (int i=0;i<m_resultsKosuu;i++)
	{
		int mesLen = 0;
		for (int k=0;k<m_messageBlockMax;k++)
		{
			LPSTR mes = m_resultsDesc->GetName((i+1)*8+2+k);
			if (mes != NULL)
			{
				if ((*mes) != '@')
				{
					mesLen += (int)strlen(mes);
				}
			}
		}

		m_resultsMessageAll[i] = new char[mesLen+2];
		m_resultsMessageAll[i][mesLen] = 0;
		m_resultsMessageAll[i][mesLen+1] = 0;

		int p = 0;
		for (int k=0;k<m_messageBlockMax;k++)
		{
			LPSTR mes = m_resultsDesc->GetName((i+1)*8+2+k);
			if (mes != NULL)
			{
				if ((*mes) != '@')
				{
					int ln = (int)strlen(mes);
					memcpy(&m_resultsMessageAll[i][p],mes,ln);
					p += ln;
				}
			}
		}
		m_resultsMessageLength[i] = p / 2;
	}

	m_voiceFlag = 0;
	GetInitGameParam(&m_voiceFlag,"voiceFlag");
	GetFadeInOutSetup();
	GetBGMSetup();




}


CCommonPrintResult::~CCommonPrintResult()
{
	End();
}

void CCommonPrintResult::End(void)
{
	DELETEARRAY(m_resultsMessageLength);
	if (m_resultsMessageAll != NULL)
	{
		for (int i=0;i<m_resultsKosuu;i++)
		{
			DELETEARRAY(m_resultsMessageAll[i]);
		}
		DELETEARRAY(m_resultsMessageAll);
	}

	ENDDELETECLASS(m_okButton);

	DELETEARRAY(m_resultsDataTable);
	DELETEARRAY(m_resultsPic);

	ENDDELETECLASS(m_pagePrint);

//	ENDDELETECLASS(m_rightMaskPic);
//	ENDDELETECLASS(m_leftMaskPic);

	ENDDELETECLASS(m_resultsDesc);

}


int CCommonPrintResult::Init(void)
{
	//bgmode?


	m_page = 0;

	m_nowOnNumber = -1;
	m_nowOnNumber = -1;

	for (int i=0;i<m_pageMax;i++)
	{
		char filename[256];
		wsprintf(filename,"sys\\%s%d",m_filenameResultsTag,i+1);
		m_resultsPic[i]->LoadDWQ(filename);
	}


	if (m_pageMax > 1)
	{
		SetUpDownZahyo();
		m_updown->SetPageMax(m_pageMax);
		m_updown->SetPage(m_page);

		LoadUpDownButtonPic();
	}
	LoadBackButtonPic();

	if (m_pageMax > 1)
	{
		m_updownBack->Init();
	}
	else
	{
		m_back->Init();
	}
	SetBackButtonZahyo();

	if (m_dialogFlag)
	{
		char filename[256];
		CPicture* lpPic = m_okButton->GetPicture();
		wsprintf(filename,"sys\\%s",m_okButton->GetFileName());
		lpPic->LoadDWQ(filename);
		m_okButton->Init();
	}

	for (int i=0;i<m_resultsKosuu;i++)
	{
		m_resultsDataTable[i] = m_resultsData->GetData(i+1);
	}


	m_voiceCount = m_voiceStartWaitTime;

	m_newResults = -1;
	m_newResults = CheckNewResults();

	m_scrollCount = 0;


	return -1;
}


int CCommonPrintResult::Calcu(void)
{
	if (m_newResults == -1)
	{
		int rt;
		if (m_pageMax > 1)
		{
			rt = m_updownBack->Calcu(m_inputStatus);
		}
		else
		{
			rt = m_back->Calcu(m_inputStatus);
		}

		if (rt != -1)
		{
			int nm = ProcessCommonButton(rt);
			if (nm == 0)
			{
				return ReturnFadeOut(m_nextMode);
			}
			else if (nm > 0)
			{
				m_page = nm - 1;

			}
		}

		POINT pt = m_mouseStatus->GetZahyo();
		m_maeOnNumber = m_nowOnNumber;
		m_nowOnNumber = GetOnResults(pt);


		if (m_nowOnNumber == m_maeOnNumber)
		{
			if (m_nowOnNumber != -1)
			{
				if (m_voiceCount > 0)
				{
					m_voiceCount--;
					if (m_voiceCount <= 0)
					{
						//play voice
						if (m_voiceFlag)
						{
							PlayVoice(m_nowOnNumber);
						}
					}
				}

				if (m_scrollCount < m_scrollMax)
				{
					m_scrollCount++;
				}
			}
		}
		else
		{
			m_voiceCount = m_voiceStartWaitTime;
			m_scrollCount = 0;
			if (m_nowOnNumber != -1)
			{
				CalcuScrollMax(m_nowOnNumber);
			}
		}


	}
	else
	{
		int rt = m_okButton->Calcu(m_inputStatus);
		if (rt != -1)
		{
			int nm = ProcessCommonButton(rt);
			if (nm == 0)
			{
				m_newResults = CheckNewResults();
				m_okButton->Init();
			}
		}
	}




	return -1;
}


int CCommonPrintResult::Print(void)
{
	CAreaControl::SetAllPrintMode();
	PrintBackScriptOrBG();



	int limit = 2;
	if (m_dialogFlag == 0)
	{
		limit = 1;
	}

	for (int i=0;i<m_resultsInPage;i++)
	{
		int n = i + m_page * m_resultsInPage;
		if (n<m_resultsKosuu)
		{

			if (GetResultsData(n) >= limit)
			{
				PutResultsPic(n);
			}
		}
	}


	if (m_newResults == -1)
	{
		if (m_nowOnNumber != -1)
		{
			if (m_descPrintType == 0)
			{
				for (int i=0;i<m_messageBlockMax;i++)
				{
					int putX = m_messagePrintX;
					int putY = m_messagePrintY + i * m_messageNextY;
					LPSTR mes = m_resultsDesc->GetName(m_nowOnNumber*8+2+i);
					if ((*mes) != '@')
					{
						m_message->PrintMessage(putX,putY,mes,m_messageFontSize,m_messageColorR,m_messageColorG,m_messageColorB,m_messageSukima);
					}
				}
			}
			else if (m_descPrintType == 1)
			{
				char mes[1024];
				int dx = 0;
				int nx = 0;

				int putDX = 0;
				int srcDX = 0;

				if (m_scrollCount > m_scrollStartWaitTime)
				{
					dx = m_scrollCount - m_scrollStartWaitTime;
					dx *= m_scrollSpeed;
				
					putDX = dx;

					if (dx > m_messageFontSize * 2)
					{
						putDX = (dx % m_messageFontSize) + m_messageFontSize;
						srcDX += (dx-m_messageFontSize) / m_messageFontSize;
					}
				}

				int ln = m_resultsMessageLength[m_nowOnNumber] - srcDX;
				if (ln>m_messageLength) ln = m_messageLength;

				memcpy(mes,&m_resultsMessageAll[m_nowOnNumber][srcDX*2],ln*2);
				mes[ln*2] = 0;

				int startX = m_messagePrintX - m_messageFontSize - m_messageSukima;
				int endX = m_messagePrintX + (m_messageFontSize - m_messageSukima) * (m_messageLength + 1);
	//			m_message->PrintMessage(m_messagePrintX-putDX,m_messagePrintY,mes,m_messageFontSize,m_messageColorR,m_messageColorG,m_messageColorB,m_messageSukima);
				m_message->GradPrintMessage(startX,endX,m_messagePrintX-putDX,m_messagePrintY,mes,m_messageFontSize,m_messageColorR,m_messageColorG,m_messageColorB,m_messageSukima);
			}
		}

///		PutMessageMask();
	}
	else
	{
		if (m_dialogFlag)
		{
			m_commonParts->Blt(m_dialogPrintX,m_dialogPrintY,0,0,m_dialogSizeX,m_dialogSizeY,TRUE);
		}
	}

	m_pagePrint->Print(m_page+1,m_pageMax);


	if (m_newResults == -1)
	{
		if (m_pageMax > 1)
		{
			m_updownBack->Print(TRUE);
		}
		else
		{
			m_back->Print(TRUE);
		}
	}
	else
	{
		if (m_dialogFlag)
		{
			m_okButton->Print(TRUE);
		}
	}

	return -1;
}


void CCommonPrintResult::PutResultsPic(int n)
{
	POINT pt = GetResultsZahyo(n);
	POINT pt2 = GetResultsPicSrc(n);
	CPicture* lpPic = GetResultsPic(n);

	int putX = pt.x;
	int putY = pt.y;
	int srcX = pt2.x;
	int srcY = pt2.y;
	int sizeX = m_resultsSizeX;
	int sizeY = m_resultsSizeY;
	lpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
}

POINT CCommonPrintResult::GetResultsZahyo(int n)
{
	n %= m_resultsInPage;
	POINT pt;
	int nx = n % m_resultsNumberX;
	int ny = n / m_resultsNumberX;
	pt.x = m_resultsPrintX + nx * m_resultsNextX;
	pt.y = m_resultsPrintY + ny * m_resultsNextY;
	return pt;
}

POINT CCommonPrintResult::GetResultsPicSrc(int n)
{
	n %= m_resultsInPage;
	POINT pt;
	int nx = n % m_resultsNumberX;
	int ny = n / m_resultsNumberX;
	pt.x = m_resultsSizeX * nx;
	pt.y = m_resultsSizeY * ny;
	return pt;
}

CPicture* CCommonPrintResult::GetResultsPic(int n)
{
	n /= m_resultsInPage;
	return m_resultsPic[n];
}

/*
void CCommonPrintResult::PutMessageMask(void)
{
	m_leftMaskPic->Blt(m_leftMaskPrintX,m_leftMaskPrintY,0,0,m_maskSizeX,m_maskSizeY,TRUE);
	m_rightMaskPic->Blt(m_rightMaskPrintX,m_rightMaskPrintY,0,0,m_maskSizeX,m_maskSizeY,TRUE);
}
*/


int CCommonPrintResult::GetOnResults(POINT pt)
{
	for (int i=0;i<m_resultsInPage;i++)
	{
		int n = m_page * m_resultsInPage + i;
		if (GetResultsData(n) != 0)
		{
			if (CheckOnResults(n,pt))
			{
				return n;
			}
		}
	}
	return -1;
}

BOOL CCommonPrintResult::CheckOnResults(int n,POINT pt)
{
	POINT pt2 = GetResultsZahyo(n);
	POINT pt3 = GetResultsPicSrc(n);
	CPicture* lpPic = GetResultsPic(n);

	int dx = pt.x - pt2.x;
	int dy = pt.y - pt2.y;
	if ((dx<0) || (dy<0)) return FALSE;
	int sizeX = m_resultsSizeX;
	int sizeY = m_resultsSizeY;
	if ((dx>=sizeX) || (dy>=sizeY)) return FALSE;

	int checkX = pt3.x + dx;
	int checkY = pt3.y + dy;

	if (lpPic->CheckOnPic(checkX,checkY)) return TRUE;

	return FALSE;
}

void CCommonPrintResult::LoadGetDialog(int n)
{
	char filename[256];
	int n1 = (n+1) / 10;
	int n2 = (n+1) % 10;
	wsprintf(filename,"sys\\%s%d%d",m_filenameDialogTag,n1,n2);
	m_commonParts->LoadDWQ(filename);
}

int CCommonPrintResult::CheckNewResults(void)
{
	if (m_dialogFlag == 0)
	{
		return -1;
	}

	if (m_newResults != -1)
	{
		//flga 1 to 2
		SetResultsData(m_newResults,2);
	}

	//search
	for (int i=0;i<m_resultsKosuu;i++)
	{
		if (GetResultsData(i) == 1)
		{
			//found!
			LoadGetDialog(i);
			m_page = i / m_resultsInPage;
			if (m_pageMax > 1)
			{
				m_updown->SetPage(m_page);
			}
			return i;
		}
	}

	return -1;
}

int CCommonPrintResult::GetResultsData(int n)
{
	return m_resultsDataTable[n];
}

void CCommonPrintResult::SetResultsData(int n,int d)
{
	m_resultsDataTable[n] = d;
	m_resultsData->SetData(n+1,d);
}

void CCommonPrintResult::CalcuScrollMax(int n)
{
	m_scrollMax = 0;
	int mx = 0;
	int over = m_resultsMessageLength[n] - 30;

	if (over > 0)
	{
		over *= m_messageFontSize;
		over /= m_scrollSpeed;
		m_scrollMax += over;
	}

	m_scrollMax += m_scrollStartWaitTime;
}


void CCommonPrintResult::PlayVoice(int voiceNumber)
{
	LPSTR voiceName = m_resultsDesc->GetName((voiceNumber+1)*8+1);
	if ((*voiceName) == '!') return;

	m_game->ReplayVoice(voiceName);
}


void CCommonPrintResult::FinalExitRoutine(void)
{
	m_game->StopScriptSoundAndVoice();
//	m_game->StopVoice();
}



/*_*/




