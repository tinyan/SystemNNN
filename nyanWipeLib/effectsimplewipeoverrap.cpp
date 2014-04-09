//
// effectsimplewipeoverrap.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeOverrap.h"

#include "allSimpleWipe.h"


CEffectSimpleWipeOverrap::CEffectSimpleWipeOverrap(CAllSimpleWipe* allWipe) : CEffectSimpleWipeCommon(allWipe)
{
}

CEffectSimpleWipeOverrap::~CEffectSimpleWipeOverrap()
{
	End();
}

void CEffectSimpleWipeOverrap::End(void)
{
}


void CEffectSimpleWipeOverrap::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint, POINT* lpEndPoint)
{
	if (lpPicEnd == NULL) return;
	if (lpPicStart != NULL)
	{
		if (lpPicStart->Check256()) return;
	}
	if (lpPicEnd->Check256()) return;

	m_startPoint.x = 0;
	m_startPoint.y = 0;
	m_endPoint.x = 0;
	m_endPoint.y = 0;

	if (lpStartPoint != NULL)
	{
		m_startPoint.x = lpStartPoint->x;
		m_startPoint.y = lpStartPoint->y;
	}

	if (lpEndPoint != NULL)
	{
		m_endPoint.x = lpEndPoint->x;
		m_endPoint.y = lpEndPoint->y;
	}

	m_startPic = lpPicStart;
	m_endPic = lpPicEnd;

	m_count = count;
	m_countMax = countMax;

	if (m_countMax < 1) m_countMax = 1;
	if (m_count<0) m_count = 0;
	if (m_count > m_countMax) m_count = m_countMax;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (lpPicStart != NULL)
	{
		RECT rcStart;
		lpPicStart->GetPicSize(&rcStart);

		int startPicSizeX = rcStart.right;
		int startPicSizeY = rcStart.bottom;


		m_startPicSize.cx = startPicSizeX;
		m_startPicSize.cy = startPicSizeY;



		//はみだしていたら、なかにいれようと努力してみる
		if ((m_startPoint.x+screenSizeX) > startPicSizeX) m_startPoint.x = startPicSizeX - screenSizeX;
		if ((m_startPoint.y+screenSizeY) > startPicSizeY) m_startPoint.y = startPicSizeY - screenSizeY;

		if (m_startPoint.x<0) m_startPoint.x = 0;
		if (m_startPoint.y<0) m_startPoint.y = 0;

		//それでもだめなら表示しない

		if (m_startPoint.x<0) return;
		if (m_startPoint.y<0) return;
		if ((m_startPoint.x+screenSizeX) > startPicSizeX) return;
		if ((m_startPoint.y+screenSizeY) > startPicSizeY) return;
	}


	//endPointもチェック

	RECT rcEnd;
	lpPicEnd->GetPicSize(&rcEnd);

	int endPicSizeX = rcEnd.right;
	int endPicSizeY = rcEnd.bottom;

	m_endPicSize.cx = endPicSizeX;
	m_endPicSize.cy = endPicSizeY;


	if ((m_endPoint.x+screenSizeX) > endPicSizeX) m_endPoint.x = endPicSizeX - screenSizeX;
	if ((m_endPoint.y+screenSizeY) > endPicSizeY) m_endPoint.y = endPicSizeY - screenSizeY;

	if (m_endPoint.x<0) m_endPoint.x = 0;
	if (m_endPoint.y<0) m_endPoint.y = 0;

	//それでもだめなら表示しない

	if (m_endPoint.x<0) return;
	if (m_endPoint.y<0) return;
	if ((m_endPoint.x+screenSizeX) > endPicSizeX) return;
	if ((m_endPoint.y+screenSizeY) > endPicSizeY) return;


	int ps = (count * 100) / countMax;

	if (m_startPic != NULL)
	{
		m_startPic->Overrap(m_endPic,ps,&m_startPoint,&m_endPoint);
	}
	else
	{
		m_endPic->Overrap2(ps,lpEndPoint);
	}

	return;
}


