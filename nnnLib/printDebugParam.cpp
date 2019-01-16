//
// printDebugParam.cpp
//

#include <windows.h>
#include <stdio.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\allGeo.h"

#include "..\nnnUtilLib\myKeyStatus.h"

#include "..\nnnUtilLib\namelist.h"


#include "gameCallBack.h"
#include "printDebugParam.h"

CPrintDebugParam::CPrintDebugParam(CGameCallBack* lpGame)
{
	m_game = lpGame;
	m_varList = m_game->GetVarList();
	m_debugVarStart = 0;
	m_vistaPatch = FALSE;




	int printX = 380;
	int printY = 16;
	int nextY = 20;

	m_game->GetInitGameParam(&printX, "debugPrintX");
	m_game->GetInitGameParam(&printY, "debugPrintY");
	m_game->GetInitGameParam(&nextY, "debugnextY");
	m_printX = printX;
	m_printY = printY;
	m_nextY = nextY;


	int backPrintX = 360;
	int backPrintY = 8;
	int backSizeX = 432;
	int backSizeY = 584;
	int backR = 64;
	int backG = 192;
	int backB = 128;
	int backPercent = 75;
	int backTransMode = 0;
	m_game->GetInitGameParam(&backPrintX, "debugBackPrintX");
	m_game->GetInitGameParam(&backPrintY, "debugBackPrintY");
	m_game->GetInitGameParam(&backSizeX, "debugBackSizeX");
	m_game->GetInitGameParam(&backSizeY, "debugBackSizeY");
	m_backPrintX = backPrintX;
	m_backPrintY = backPrintY;
	m_backSizeX = backSizeX;
	m_backSizeY = backSizeY;
	m_game->GetInitGameParam(&backR, "debugBackR");
	m_game->GetInitGameParam(&backG, "debugBackG");
	m_game->GetInitGameParam(&backB, "debugBackB");
	m_game->GetInitGameParam(&backPercent, "debugBackA");
	m_game->GetInitGameParam(&backTransMode, "debugBackTrans");


	SetDebugBackPrintMode(backTransMode);
	SetDebugBackPrintColor(backR, backG, backB);
	SetDebugBackTransPercent(backPercent);


	int numberOfPage = 20;
	m_game->GetInitGameParam(&numberOfPage, "debugNumberOfPage");
	SetDebugVarPage(numberOfPage);


}


CPrintDebugParam::~CPrintDebugParam()
{
	End();
}


void CPrintDebugParam::End(void)
{
}


void CPrintDebugParam::Print(int n)
{
	HWND hWnd = m_game->GetGameHWND();

	HDC hdc = GetDC(hWnd);

	int oldBackMode = SetBkMode(hdc,TRANSPARENT);

	COLORREF oldTextColor = SetTextColor(hdc,0);

	if (n == -1) n = m_debugVarStart;


	int debugVarStart = (n / m_numberOfPage) * m_numberOfPage;
//	int debugVarDelta = n % 20;

	int putX = m_printX;
	int putY = m_printY;
	int nextY = m_nextY;

	HBRUSH vistaBrush = NULL;

	if (m_vistaPatch)
	{
//		vistaBrush = CreateSolidBrush(GetBkColor(hdc));
		vistaBrush = CreateSolidBrush(COLORREF(0x00ff80));
	}

	int varNumber = m_game->GetVarMax();

	for (int i=0;i<m_numberOfPage;i++)
	{
		char mes[256];
		int varNum = debugVarStart+i;

		if ((varNum >= 0) && (varNum < varNumber))
		{
			int dat = 0;
			if (varNum >= 100)
			{
				dat = m_game->GetVarData(varNum);
			}
			else
			{
				dat = m_game->GetCalcuVarData(varNum);
			}

			wsprintf(mes, "%s:y%dz", m_varList->GetName(debugVarStart + i), dat);
			int ln = (int)strlen(mes);

			if (m_vistaPatch)
			{
				RECT fillRect;
				SetRect(&fillRect, putX - 20, putY + i * nextY, putX + 8 * ln, putY + i * nextY + 20);
				//			InvalidateRect(hWnd,&fillRect,TRUE);
				FillRect(hdc, &fillRect, vistaBrush);
			}


			SetTextColor(hdc, COLORREF(0x000000));
			TextOut(hdc, putX + 1, putY + 1 + nextY * i, mes, ln);

			if (dat == 0)
			{
				SetTextColor(hdc, COLORREF(0x909090));
			}
			else if (dat == 1)
			{
				SetTextColor(hdc, COLORREF(0xFFFFFF));
			}
			else if (dat == 2)
			{
				SetTextColor(hdc, COLORREF(0x0080FF));
			}
			else
			{
				SetTextColor(hdc, COLORREF(0xFF8000));
			}

			TextOut(hdc, putX, putY + i * nextY, mes, ln);
		}

		if (i == (n % m_numberOfPage))
		{
			TextOut(hdc,putX-16+1,putY+1+i*nextY,"œ",2);
		}
	}

	if (vistaBrush != NULL)
	{
		DeleteObject(vistaBrush);
	}

	if (oldTextColor != CLR_INVALID) SetTextColor(hdc,oldTextColor);
	if (oldBackMode != 0) SetBkMode(hdc,oldBackMode);

	ReleaseDC(hWnd,hdc);
}


void CPrintDebugParam::AddDebugVarNumber(int d,BOOL loopFlag)
{
	int varType = m_game->GetVarType();
	int varNumber = m_game->GetVarMax();

	if (loopFlag == FALSE)
	{
		m_debugVarStart += d;
		m_debugVarStart += varNumber*10;
		m_debugVarStart %= varNumber;
	}
	else
	{
		int k = m_debugVarStart % m_numberOfPage;
		int dd = m_debugVarStart / m_numberOfPage;

		k += d;
		k += m_numberOfPage * 10000;
		k %= m_numberOfPage;

		m_debugVarStart = dd * m_numberOfPage + k;
	}
}


void CPrintDebugParam::AddDebugVarPage(int page)
{
	int varNumber = m_game->GetVarMax();
	if (page > 0)
	{
		m_debugVarStart += page * m_numberOfPage;
		if (m_debugVarStart >= varNumber)
		{
			m_debugVarStart = 0;
		}
	}
	else
	{
		if (m_debugVarStart <= 0)
		{
			m_debugVarStart = varNumber - m_numberOfPage;
		}
		else
		{
			m_debugVarStart += page * m_numberOfPage;
			if (m_debugVarStart < 0)
			{
				m_debugVarStart = 0;
			}
		}
	}
}


void CPrintDebugParam::PrintDebugBack(void)
{
	if (m_debugBackPrintMode == 0) return;

	int putX = m_backPrintX;
	int putY = m_backPrintY;
	int sizeX = m_backSizeX;
	int sizeY = m_backSizeY;

	if (m_backPercent == 100)
	{
		CAllGeo::BoxFill(putX,putY,sizeX,sizeY,m_backR,m_backG,m_backB);
	}
	else
	{
		CAllGeo::TransBoxFill(putX,putY,sizeX,sizeY,m_backR,m_backG,m_backB,m_backPercent);
	}

	CAreaControl::SetNextAllPrint();
}

void CPrintDebugParam::ChangeDebugBackPrintMode(void)
{
	m_debugBackPrintMode = 1;
	m_backPercent += 25;
	if (m_backPercent > 100)
	{
		m_backPercent = 0;
		m_debugBackPrintMode = 0;
	}
}

/*_*/

