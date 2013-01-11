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
	SetDebugVarPage(20);
	SetDebugBackPrintMode(0);
	SetDebugBackPrintColor(64,192,128);
	SetDebugBackTransPercent(75);
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


	int debugVarStart = (n / 20) * 20;
	int debugVarDelta = n % 20;

	int putX = 380;
	int putY = 16;
	int nextY = 20;

	HBRUSH vistaBrush = NULL;

	if (m_vistaPatch)
	{
//		vistaBrush = CreateSolidBrush(GetBkColor(hdc));
		vistaBrush = CreateSolidBrush(COLORREF(0x00ff80));
	}

	for (int i=0;i<20;i++)
	{
		char mes[256];
		int varNum = debugVarStart+i;

		int dat = 0;
		if (varNum>=100)
		{
			dat = m_game->GetVarData(varNum);
		}
		else
		{
			dat = m_game->GetCalcuVarData(varNum);
		}

		wsprintf(mes,"%s:y%dz",m_varList->GetName(debugVarStart+i),dat);
		int ln = (int)strlen(mes);

		if (m_vistaPatch)
		{
			RECT fillRect;
			SetRect(&fillRect,putX-20,putY+i*nextY,putX+8*ln,putY+i*nextY+20);
//			InvalidateRect(hWnd,&fillRect,TRUE);
			FillRect(hdc,&fillRect,vistaBrush);
		}


		SetTextColor(hdc,COLORREF(0x000000));
		TextOut(hdc,putX+1,putY+1+nextY*i,mes,ln);

		if (dat == 0)
		{
			SetTextColor(hdc,COLORREF(0x909090));
		}
		else if (dat == 1)
		{
			SetTextColor(hdc,COLORREF(0xFFFFFF));
		}
		else if (dat == 2)
		{
			SetTextColor(hdc,COLORREF(0x0080FF));
		}
		else
		{
			SetTextColor(hdc,COLORREF(0xFF8000));
		}

		TextOut(hdc,putX,putY+i*nextY,mes,ln);
		if (i == (n % 20))
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
	if (loopFlag == FALSE)
	{
		m_debugVarStart += d;
		m_debugVarStart += 1000*10;
		m_debugVarStart %= 1000;
	}
	else
	{
		int k = m_debugVarStart % 20;
		int dd = m_debugVarStart / 20;

		k += d;
		k += 20*1000;
		k %= 20;

		m_debugVarStart = dd * 20 + k;
	}
}


void CPrintDebugParam::AddDebugVarPage(int page)
{
	AddDebugVarNumber(page * m_page);
}


void CPrintDebugParam::PrintDebugBack(void)
{
	if (m_debugBackPrintMode == 0) return;

	int putX = 360;
	int putY = 8;
	int sizeX = 440-8;
	int sizeY = 600-16;

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

