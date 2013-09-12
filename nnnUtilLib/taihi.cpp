//
// taihi.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\areaControl.h"

#include "taihi.h"


CTaihi::CTaihi()
{
#if defined _TINYAN3DLIB_
	return;
#endif

	m_bufferKosuu = 64;
	m_lpTaihi = new CPicture* [m_bufferKosuu];
	m_lpExistFlag = new BOOL[m_bufferKosuu];
	m_lpZahyo = new POINT[m_bufferKosuu];
	m_lpSize = new SIZE[m_bufferKosuu];
	m_lpBufferSize = new SIZE[m_bufferKosuu];
	for (int i=0;i<m_bufferKosuu;i++)
	{
		*(m_lpTaihi + i) = NULL;
		*(m_lpExistFlag + i) = FALSE;
		SIZE sz;
		sz.cx = 0;
		sz.cy = 0;
		*(m_lpBufferSize) = sz;
		Flush(i);
	}
}


CTaihi::~CTaihi()
{
	End();
}

void CTaihi::End(void)
{
#if defined _TINYAN3DLIB_
	return;
#endif

	DELETEARRAY(m_lpBufferSize);
	DELETEARRAY(m_lpSize);
	if (m_lpTaihi != NULL)
	{
		for (int i=0;i<m_bufferKosuu;i++)
		{
			ENDDELETECLASS(*(m_lpTaihi+i));
		}
		DELETEARRAY(m_lpTaihi);
	}
	DELETEARRAY(m_lpExistFlag);
	DELETEARRAY(m_lpZahyo);

	m_bufferKosuu = 0;
}


BOOL CTaihi::CreateBuffer(int n, int sizeX, int sizeY)
{
#if defined _TINYAN3DLIB_
	return TRUE;
#endif
	if ((n<0) || (n>=m_bufferKosuu)) return FALSE;
	CPicture* lpPic = *(m_lpTaihi + n);
	
	SIZE bufferSize = *(m_lpBufferSize+n);
	SIZE size = *(m_lpSize+n);


	if (lpPic == NULL)
	{
		lpPic = new CPicture(sizeX,sizeY);
		if (lpPic == NULL) return FALSE;

		bufferSize.cx = sizeX;
		bufferSize.cy = sizeY;

		*(m_lpBufferSize + n) = bufferSize;
	}

	if ((sizeX > bufferSize.cx) || (sizeY > bufferSize.cy))
	{
		ENDDELETECLASS(lpPic);
		*(m_lpTaihi + n) = NULL;

		lpPic = new CPicture(sizeX,sizeY);
		if (lpPic == NULL) return FALSE;

		bufferSize.cx = sizeX;
		bufferSize.cy = sizeY;

		*(m_lpBufferSize + n) = bufferSize;
	}

	size.cx = sizeX;
	size.cy = sizeY;
	*(m_lpSize + n) = size;

	*(m_lpTaihi + n) = lpPic;
	Flush(n);

	return TRUE;
}


BOOL CTaihi::Taihi(int n, int x, int y)
{
#if defined _TINYAN3DLIB_
	return TRUE;
#endif

	CPicture* lpPic = GetCPicture(n);
	if (lpPic == NULL) return FALSE;

	SIZE picSize = lpPic->GetPicSize();
	SIZE size = *(m_lpSize+n);

	int sizeX = size.cx;
	int sizeY = size.cy;

	if ((sizeX<picSize.cx) || (sizeY<picSize.cy))
	{
		return FALSE;//unknown error
	}

	if ((sizeX<1) || (sizeY<1)) return FALSE;



	if (lpPic->GetScreen(x,y,sizeX,sizeY) == FALSE) return FALSE;

//char mes[256];
//sprintf(mes,"[%d %d]",x,y);
//OutputDebugString(mes);

	SetExist(n,x,y);
	return TRUE;
}


BOOL CTaihi::Fuque(int n)
{
#if defined _TINYAN3DLIB_

	return TRUE;
#endif

	CPicture* lpPic = GetCPicture(n);
	if (lpPic == NULL) return FALSE;
	if ((*(m_lpExistFlag + n)) == FALSE) return FALSE;

	SIZE size = *(m_lpSize+n);
//	SIZE picSize = lp->GetPicSize();

	int sizeX = size.cx;
	int sizeY = size.cy;

	if ((sizeX<1) || (sizeY<1)) return FALSE;

	int x,y;
	POINT pt = *(m_lpZahyo + n);
	x = pt.x;
	y = pt.y;

//	if (CAreaControl::CheckAllPrintMode() == FALSE)
//	{
		lpPic->Blt(x,y,0,0,sizeX,sizeY,FALSE);
		CAreaControl::AddArea(x,y,sizeX,sizeY);
//	}

	Flush(n);
	return TRUE;
}



BOOL CTaihi::Flush(int n)
{
#if defined _TINYAN3DLIB_
	return TRUE;
#endif

	if ((n<0) || (n>=m_bufferKosuu)) return FALSE;
	if (m_lpExistFlag == NULL) return FALSE;

	*(m_lpExistFlag + n) = FALSE;

	return TRUE;
}

void CTaihi::AllFuque(void)
{
#if defined _TINYAN3DLIB_

	return;
#endif

//	for (int i=m_bufferKosuu-1;i>=0;i--)
	for (int i=0;i<m_bufferKosuu;i++)
	{
		Fuque(i);
	}
}

void CTaihi::AllFlush(void)
{
#if defined _TINYAN3DLIB_

	return;
#endif

//	for (int i=m_bufferKosuu-1;i>=0;i--)
	for (int i=0;i<m_bufferKosuu;i++)
	{
		Flush(i);
	}
}



BOOL CTaihi::SetExist(int n, int x, int y)
{
#if defined _TINYAN3DLIB_
	return TRUE;
#endif

	if ((n<0) || (n>=m_bufferKosuu)) return FALSE;
	if (m_lpExistFlag == NULL) return FALSE;
	*(m_lpExistFlag + n) = TRUE;
	if (m_lpZahyo == NULL) return FALSE;
	POINT pt;
	pt.x = x;
	pt.y = y;
	*(m_lpZahyo + n) = pt;
	return TRUE;
}


CPicture* CTaihi::GetCPicture(int n)
{
#if defined _TINYAN3DLIB_
	return NULL;
#endif

	if ((n<0) || (n>=m_bufferKosuu)) return NULL;
	if (m_lpExistFlag == NULL) return NULL;
	if (m_lpZahyo == NULL) return NULL;
	return *(m_lpTaihi + n);
}


/*_*/

