//
// effectsimplewipecommon.cpp
//

#include <windows.h>

#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "allSimpleWipe.h"
#include "effectsimplewipecommon.h"

CEffectSimpleWipeCommon::CEffectSimpleWipeCommon(CAllSimpleWipe* allWipe)
{
	m_256OkFlag = FALSE;
	m_allSimpleWipe = allWipe;
}

CEffectSimpleWipeCommon::~CEffectSimpleWipeCommon()
{
	End();
}

void CEffectSimpleWipeCommon::SetEffectHoukou(int houkou)
{
	m_effectHoukou = houkou;
}



BOOL CEffectSimpleWipeCommon::ClipAndCheck(CPicture* lpPicStart, CPicture* lpPicEnd, int count,int countMax, POINT* lpStartPoint, POINT* lpEndPoint)
{
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

	if (m_startPic == NULL) return FALSE;
	if (m_endPic == NULL) return FALSE;

	if (m_256OkFlag == FALSE)
	{
		if (m_startPic->Check256()) return FALSE;
		if (m_endPic->Check256()) return FALSE;
	}


	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	RECT rcStart;
	SetRect(&rcStart,0,0,screenSizeX,screenSizeY);
	if (lpPicStart != NULL)
	{
		lpPicStart->GetPicSize(&rcStart);
	}

	RECT rcEnd;
	SetRect(&rcEnd,0,0,screenSizeX,screenSizeY);
	if (lpPicEnd != NULL)
	{
		lpPicEnd->GetPicSize(&rcEnd);
	}

	int startPicSizeX = rcStart.right;
	int startPicSizeY = rcStart.bottom;

	int endPicSizeX = rcEnd.right;
	int endPicSizeY = rcEnd.bottom;

	m_startPicSize.cx = startPicSizeX;
	m_startPicSize.cy = startPicSizeY;

	m_endPicSize.cx = endPicSizeX;
	m_endPicSize.cy = endPicSizeY;


	//はみだしていたら、なかにいれようと努力してみる
	if ((m_startPoint.x+screenSizeX) > startPicSizeX) m_startPoint.x = startPicSizeX - screenSizeX;
	if ((m_startPoint.y+screenSizeY) > startPicSizeY) m_startPoint.y = startPicSizeY - screenSizeY;

	if (m_startPoint.x<0) m_startPoint.x = 0;
	if (m_startPoint.y<0) m_startPoint.y = 0;

	//それでもだめなら表示しない

	if (m_startPoint.x<0) return FALSE;
	if (m_startPoint.y<0) return FALSE;
	if ((m_startPoint.x+screenSizeX) > startPicSizeX) return FALSE;
	if ((m_startPoint.y+screenSizeY) > startPicSizeY) return FALSE;


	//endPointもチェック

	if ((m_endPoint.x+screenSizeX) > endPicSizeX) m_endPoint.x = endPicSizeX - screenSizeX;
	if ((m_endPoint.y+screenSizeY) > endPicSizeY) m_endPoint.y = endPicSizeY - screenSizeY;

	if (m_endPoint.x<0) m_endPoint.x = 0;
	if (m_endPoint.y<0) m_endPoint.y = 0;

	//それでもだめなら表示しない

	if (m_endPoint.x<0) return FALSE;
	if (m_endPoint.y<0) return FALSE;
	if ((m_endPoint.x+screenSizeX) > endPicSizeX) return FALSE;
	if ((m_endPoint.y+screenSizeY) > endPicSizeY) return FALSE;

	if (m_startPic->Check256())
	{
		char* buf = (char*)(m_startPic->GetBuffer());
		buf += m_startPoint.x;
		buf += m_startPoint.y * startPicSizeX;
		m_startBuffer = buf;
		m_startPitch = startPicSizeX;
	}
	else
	{
		int* buf = (int*)(m_startPic->GetBuffer());
		buf += m_startPoint.x;
		buf += m_startPoint.y * startPicSizeX;
		m_startBuffer = buf;
		m_startPitch = startPicSizeX * sizeof(int);
	}

	if (m_endPic->Check256())
	{
		char* buf = (char*)(m_endPic->GetBuffer());
		buf += m_endPoint.x;
		buf += m_endPoint.y * endPicSizeX;
		m_endBuffer = buf;
		m_endPitch = endPicSizeX;
	}
	else
	{
		int* buf = (int*)(m_endPic->GetBuffer());
		buf += m_endPoint.x;
		buf += m_endPoint.y * endPicSizeX;
		m_endBuffer = buf;
		m_endPitch = endPicSizeX * sizeof(int);
	}


	return TRUE;
}


void CEffectSimpleWipeCommon::SwapPic(void)
{
	CPicture* tmpPic = m_startPic;
	m_startPic = m_endPic;
	m_endPic = tmpPic;

	POINT tmpPoint = m_startPoint;
	m_startPoint = m_endPoint;
	m_endPoint = tmpPoint;

	SIZE tmpSize = m_startPicSize;
	m_startPicSize = m_endPicSize;
	m_endPicSize = tmpSize;

	int tmpPitch = m_startPitch;
	m_startPitch = m_endPitch;
	m_endPitch = tmpPitch;

	LPVOID tmpBuffer = m_startBuffer;
	m_startBuffer = m_endBuffer;
	m_endBuffer = tmpBuffer;
}


void CEffectSimpleWipeCommon::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint, POINT* lpEndPoint)
{
	//dummy routine virtual

	if (lpPicStart == NULL) return;
	if (lpPicEnd == NULL) return;
	if (count < 0) return;
	if (countMax <= 0) return;
	if (lpStartPoint == NULL) return;
	if (lpEndPoint == NULL) return;
}

/*_*/


