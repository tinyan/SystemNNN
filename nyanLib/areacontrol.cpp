//
// areacontrol.cpp
//


#include <windows.h>

#include "include\commonmacro.h"
#include "include\myGraphics.h"
#include "include\areacontrol.h"


CAreaControl::AREACONTROL CAreaControl::m_area[256];
int CAreaControl::m_areaKosuu = 0;
int CAreaControl::m_areaSize = 0;
BOOL CAreaControl::m_allPrintFlag = TRUE;
BOOL CAreaControl::m_nextAllPrintFlag = TRUE;
int CAreaControl::m_nextAllPrintFlag2 = 0;
BOOL CAreaControl::m_skipPrintFlag = FALSE;
BOOL CAreaControl::m_skippedFlag = FALSE;
BOOL CAreaControl::m_fullScreenFlag = FALSE;

int CAreaControl::m_fullScreenCount = 0;
int CAreaControl::m_vista = FALSE;

CAreaControl::CAreaControl()
{
}

CAreaControl::~CAreaControl()
{
}


void CAreaControl::StartScene(void)
{
	ClearArea();
	m_allPrintFlag = FALSE;

	if (m_nextAllPrintFlag)
	{
		m_nextAllPrintFlag = FALSE;
		m_allPrintFlag = TRUE;
	}

	if (m_nextAllPrintFlag2 > 0)
	{
		m_nextAllPrintFlag2--;
		m_allPrintFlag = TRUE;
	}

	if (m_fullScreenCount > 0)
	{
		m_nextAllPrintFlag = FALSE;
		m_allPrintFlag = TRUE;
		m_fullScreenCount--;
	}

	if (m_vista)
	{
		m_allPrintFlag = TRUE;
	}
}


void CAreaControl::EndScene(void)
{
	if (m_skipPrintFlag)
	{
		m_skippedFlag = TRUE;
	}
	m_skipPrintFlag = FALSE;
}


void CAreaControl::ClearArea(void)
{
	m_areaKosuu = 0;
	m_areaSize = 0;
}

void CAreaControl::SetAllPrintMode(BOOL bFlag)
{
	m_allPrintFlag = bFlag;
	if (bFlag)
	{	
		m_skipPrintFlag = FALSE;
		m_skippedFlag = FALSE;
	}
}



void CAreaControl::AddArea(int startX,int startY,int sizeX,int sizeY)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (m_areaKosuu<0) return;	//fuyou

	if (m_areaKosuu>=255)
	{
		m_allPrintFlag = TRUE;
		return;
	}

	//clip
	int ex = startX + sizeX;
	int ey = startY + sizeY;

	if ( (ex <= 0) || (ey <= 0) || (startX >= screenSizeX) || (startY >= screenSizeY) ) return ;

	if (startX<0)
	{
		int dx = 0 - startX;
		startX = 0;
		sizeX -= dx;
	}

	if (startY<0)
	{
		int dy = 0 - startY;
		startY = 0;
		sizeY -= dy;
	}


	if (ex>screenSizeX) sizeX -= (ex - screenSizeX);
	if (ey>screenSizeY)	sizeY -= (ey - screenSizeY);


	if ((sizeX<=0) || (sizeY<=0)) return;

	//“¯ˆê‹y‚ÑŠÜ‚Ü‚ê‚Ä‚¢‚é‚ð‚Í‚Ô‚­
	for (int i=0;i<m_areaKosuu;i++)
	{
		int x = m_area[i].startX;
		int y = m_area[i].startY;
		int sx = m_area[i].sizeX;
		int sy = m_area[i].sizeY;

		if ((x == startX) && (y == startY) && (sx == sizeX) && (sy == sizeY)) return;

		if ((sizeX<=sx) && (sy<=sizeY))
		{
			if ((startX>=x) && (startY>=y))
			{
				if ((startX+sizeX) <= (x+sx))
				{
					if ((startY+sizeY) <= (y+sy))
					{
						return;
					}
				}
			}
		}
	}


	m_area[m_areaKosuu].startX = startX;
	m_area[m_areaKosuu].startY = startY;
	m_area[m_areaKosuu].sizeX = sizeX;
	m_area[m_areaKosuu].sizeY = sizeY;

	m_areaSize += (sizeX * sizeY);

	m_areaKosuu++;

	if (m_areaSize >= (screenSizeX*screenSizeY)) m_allPrintFlag = TRUE;
}


int CAreaControl::GetAreaKosuu(void)
{
	return m_areaKosuu;
}

BOOL CAreaControl::GetArea(int n, int& startX, int& startY, int& sizeX, int& sizeY)
{
	if ((n<0) || (n>=m_areaKosuu))
	{
		startX = 0;
		startY = 0;
		sizeX = 8;
		sizeY = 8;
		return FALSE;
	}

	startX = m_area[n].startX;
	startY = m_area[n].startY;
	sizeX = m_area[n].sizeX;
	sizeY = m_area[n].sizeY;

	return TRUE;
}

void CAreaControl::SetNextAllPrint(int cnt)
{
	m_nextAllPrintFlag = TRUE;
	m_nextAllPrintFlag2 = cnt;
	m_allPrintFlag = TRUE;
	m_skippedFlag = FALSE;
	m_skipPrintFlag = FALSE;
//	if (m_fullScreenFlag)
//	{
//		m_fullScreenCount = 2;
//	}
}


void CAreaControl::ToSkipMode(void)
{
	if (m_allPrintFlag)
	{
		m_skipPrintFlag = FALSE;
		m_skippedFlag = FALSE;
		return;
	}

	if (m_skippedFlag == TRUE)
	{
		m_skippedFlag = FALSE;
	}
	else
	{
		m_skipPrintFlag = TRUE;
	}
}

BOOL CAreaControl::CheckSkipMode(void)
{
	return m_skipPrintFlag;
}

BOOL CAreaControl::CheckAllPrintMode(void)
{
	if (m_vista) return TRUE;

	return m_allPrintFlag;
}

void CAreaControl::ToFullScreen(void)
{
//	m_fullScreenCount = 2;
	m_fullScreenFlag = TRUE;
}

void CAreaControl::ToWindowScreen(void)
{
	m_fullScreenFlag = FALSE;
}

void CAreaControl::SetVista(void)
{
	m_vista = TRUE;
}

/*_*/



