#include <windows.h>
#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"



#include "taihi.h"
//#include "namelist.h"
#include "setupList.h"
#include "CViewControl.h"


CViewControl::CViewControl()
{
//	m_realWindowSizeX = 800;
//	m_realWindowSizeY = 600;
//	m_viewOffsetX = (1024-800)/2;
//	m_viewOffsetY = (768-600) / 2;
}


CViewControl::~CViewControl()
{
	End();
}


void CViewControl::End(void)
{
}

void CViewControl::SetBufferSize(int sizeX,int sizeY)
{
	m_bufferSizeX = sizeX;
	m_bufferSizeY = sizeY;
}

void CViewControl::SetRealWindowSize(int sizeX,int sizeY)
{
	m_realWindowSizeX = sizeX;
	m_realWindowSizeY = sizeY;
}

void CViewControl::SetStretchFlag(BOOL flg)
{
	m_stretchFlag = flg;
}

void CViewControl::CalcuParam(void)
{
	m_backBufferOffsetX = (m_realWindowSizeX - m_bufferSizeX) / 2;
	m_backBufferOffsetY = (m_realWindowSizeY - m_bufferSizeY) / 2;

	m_viewSizeX = m_bufferSizeX;
	m_viewSizeY = m_bufferSizeY;

	if (m_stretchFlag)
	{
		if ((m_realWindowSizeX > m_bufferSizeX) && (m_realWindowSizeY > m_bufferSizeY))
		{
			if ((m_realWindowSizeX * m_bufferSizeY) > (m_realWindowSizeY * m_bufferSizeX))
			{
				//x 
				m_viewSizeX = (m_bufferSizeX * m_realWindowSizeY) / m_bufferSizeY;
				m_viewSizeY = m_realWindowSizeY;
			}
			else
			{
				m_viewSizeY = (m_bufferSizeY * m_realWindowSizeX) / m_bufferSizeX;
				m_viewSizeX = m_realWindowSizeX;
			}


		}
	}

	m_viewOffsetX = (m_realWindowSizeX - m_viewSizeX) / 2;
	m_viewOffsetY = (m_realWindowSizeY - m_viewSizeY) / 2;

}


POINT CViewControl::WindowToGame(int windowMouseX,int windowMouseY)
{
	POINT pt;
	int x = windowMouseX - m_viewOffsetX;
	int y = windowMouseY - m_viewOffsetY;

	x *= m_bufferSizeX;
	x /= m_viewSizeX;
	y *= m_bufferSizeY;
	y /= m_viewSizeY;

	pt.x = x;
	pt.y = y;

	return pt;
}

RECT CViewControl::GetSrcRect(int x,int y,int sizeX,int sizeY)
{
	RECT rect;

	x -= m_viewOffsetX;
	y -= m_viewOffsetY;

	x *= m_bufferSizeX;
	x /= m_viewSizeX;
	y *= m_bufferSizeY;
	y /= m_viewSizeY;
	sizeX *= m_bufferSizeX;
	sizeX /= m_viewSizeX;
	sizeY *= m_bufferSizeY;
	sizeY /= m_viewSizeY;

	x += m_backBufferOffsetX;
	y += m_backBufferOffsetY;

	//clip?


	SetRect(&rect,x,y,sizeX,sizeY);
	return rect;
}

RECT CViewControl::GetDstRect(int x,int y,int sizeX,int sizeY)
{
	RECT rect;
	/*
	x *= m_viewSizeX;
	x /= m_bufferSizeX;
	y *= m_viewSizeY;
	y /= m_bufferSizeY;

	x += m_backBufferOffsetX;
	y += m_backBufferOffsetY;

	sizeX *= m_viewSizeX;
	sizeX /= m_bufferSizeX;
	sizeX *= m_viewSizeY;
	sizeY /= m_bufferSizeY;
	*/
	SetRect(&rect,x,y,sizeX,sizeY);

	return rect;
}

POINT CViewControl::GameToView(POINT pt)
{
	POINT pt2;

	int x = pt.x;
	int y = pt.y;
	x *= m_viewSizeX;
	x /= m_bufferSizeX;
	y *= m_viewSizeY;
	y /= m_bufferSizeY;

	x += m_viewOffsetX;
	y += m_viewOffsetY;

	pt2.x = x;
	pt2.y = y;

	return pt2;
}

SIZE CViewControl::GetAspectFitSize(void)
{
	int sizeX = m_bufferSizeX;
	int sizeY = m_bufferSizeY;

	if (m_stretchFlag)
	{
		if ((m_realWindowSizeX >= m_bufferSizeX) && (m_realWindowSizeY >= m_bufferSizeY))
		{

			if ((m_realWindowSizeX * m_bufferSizeY) > (m_realWindowSizeY * m_bufferSizeX))
			{
				//x 
				sizeX = (m_bufferSizeX * m_realWindowSizeY) / m_bufferSizeY;
				sizeY = m_realWindowSizeY;
			}
			else
			{
				sizeY = (m_bufferSizeY * m_realWindowSizeX) / m_bufferSizeX;
				sizeX = m_realWindowSizeX;
			}
		}
	}

	SIZE sz;
	sz.cx = sizeX;
	sz.cy = sizeY;

	return sz;
}



/*_*/


