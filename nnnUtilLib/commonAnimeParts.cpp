#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"


#include "..\nnnUtilLib\nameList.h"


#include "commonAnimeParts.h"

char CCommonAnimeParts::m_defaultPicFileName[]= "ta_anime";


CCommonAnimeParts::CCommonAnimeParts(LPSTR tagName,CNameList* setup,BOOL createFlag)
{
	m_createFlag = createFlag;
	m_setup = setup;

	m_pic = NULL;

	m_animeCountMax = 1;
	m_animePicSize.cx = 16;
	m_animePicSize.cy = 16;
	m_animePattern = 1;
	m_animeSpeed = 1;
	m_animeType = 1;
	m_yokoKosuu = 1;
	m_animePrintZahyo.x = 0;
	m_animePrintZahyo.y = 0;

	m_picFileName = m_defaultPicFileName;
	
	char name[256];
	wsprintf(name,"filename%s",tagName);
	GetInitGameString(&m_picFileName,name);
	
	wsprintf(name,"%sPattern",tagName);
	GetInitGameParam(&m_animePattern,name);

	wsprintf(name,"%sSpeed",tagName);
	GetInitGameParam(&m_animeSpeed,name);

	wsprintf(name,"%sType",tagName);
	GetInitGameParam(&m_animeType,name);

	int sizeX = m_animePicSize.cx;
	wsprintf(name,"%sSizeX",tagName);
	GetInitGameParam(&sizeX,name);
	int sizeY = m_animePicSize.cy;
	wsprintf(name,"%sSizeY",tagName);
	GetInitGameParam(&sizeY,name);
	m_animePicSize.cx = sizeX;
	m_animePicSize.cy = sizeY;

	int putX = m_animePrintZahyo.x;
	int putY = m_animePrintZahyo.y;
	wsprintf(name,"%sPrintX",tagName);
	GetInitGameParam(&putX,name);
	wsprintf(name,"%sPrintY",tagName);
	GetInitGameParam(&putY,name);
	m_animePrintZahyo.x = putX;
	m_animePrintZahyo.y = putY;


	int type = m_animeType;
	int speed = m_animeSpeed;
	int revFlag = 0;
	int pattern = m_animePattern;

	int dv = pattern;

	if ((type == 3) || (type == 4) || (type == 7) || (type == 8))
	{
		dv = (pattern-1) * 2;
		if (dv<1) dv = 1;
		revFlag = 1;
	}

	dv *= speed;
	m_animeCountMax = dv;

	m_limitFlag = 0;
	if ((type == 2) || (type == 4) || (type == 6) || (type == 8))
	{
		m_limitFlag = 1;
	}


	if (m_createFlag)
	{
		char filename[1024];
		sprintf_s(filename,sizeof(filename),"sys\\%s",m_picFileName);
		m_pic = new CPicture(filename);
		SetPicture(m_pic);
	}

	Init();
}



CCommonAnimeParts::~CCommonAnimeParts()
{
	End();
}


void CCommonAnimeParts::End(void)
{
	if (m_createFlag)
	{
		ENDDELETECLASS(m_pic);
	}
}


LPSTR CCommonAnimeParts::GetPictureFileName(void)
{
	return m_picFileName;
}

void CCommonAnimeParts::SetPicture(CPicture* lpPic)
{
	m_pic = lpPic;
	SIZE sz = m_pic->GetPicSize();
	int sizeX = sz.cx;
	int sizeY = sz.cy;
	m_yokoKosuu = sizeX / m_animePicSize.cx;
	if (m_yokoKosuu<1) m_yokoKosuu = 1;
}


void CCommonAnimeParts::Init(void)
{
//	m_animeNumber = -1;
	m_animeCount = 0;
}

void CCommonAnimeParts::Calcu(int cnt)
{
	//anime
	m_animeCount += cnt;

	if (m_limitFlag)
	{
		if (m_animeCount >= m_animeCountMax) m_animeCount = m_animeCountMax;
	}
	else
	{
		m_animeCount %= m_animeCountMax;
	}
}


void CCommonAnimeParts::Print(void)
{
	Print(m_animePrintZahyo);
}

void CCommonAnimeParts::DeltaPrint(POINT pt)
{
	pt.x += m_animePrintZahyo.x;
	pt.y += m_animePrintZahyo.y;
	Print(pt);
}

void CCommonAnimeParts::Print(POINT pt)
{

	int putX = pt.x;
	int putY = pt.y;
	int sizeX = m_animePicSize.cx;
	int sizeY = m_animePicSize.cy;

	CAreaControl::AddArea(putX,putY,sizeX,sizeY);


	int type = m_animeType;
	int speed = m_animeSpeed;
	int count = m_animeCount;
	int pattern = m_animePattern;

	int revFlag = 0;
	int dv = pattern;

	if (speed<1) speed = 1;

	if ((type == 3) || (type == 4) || (type == 7) || (type == 8))
	{
		dv = (pattern-1) * 2;
		if (dv<1) dv = 1;
		revFlag = 1;
	}


	int pic1 = count / speed;
	int pic2 = pic1+1;
	
	if (m_limitFlag)
	{
		int limData = dv-1;
		if (revFlag) limData = dv;

		if (pic1>=dv) pic1 = limData;
		if (pic2>=dv) pic2 = limData;
	}

	pic2 %= dv;

	int percent = 100;

	if (revFlag)
	{
		if (pic1 >= pattern) pic1 = (pattern-1)*2 - pic1;
		if (pic2 >= pattern) pic2 = (pattern-1)*2 - pic2;
	}

	if (type >= 5)
	{
		percent = 100 * (speed - (count - ((count / speed) * speed)));
		percent /= speed;
	}


	//print
	POINT pt1 = GetPicSrc(pic1);
	POINT pt2 = GetPicSrc(pic2);



	if (percent == 100)
	{
		m_pic->Blt(putX,putY,pt1.x,pt1.y,sizeX,sizeY,TRUE);
	}
	else if (percent == 0)
	{
		m_pic->Blt(putX,putY,pt2.x,pt2.y,sizeX,sizeY,TRUE);
	}
	else
	{
		int ps2 = 100 - percent;
		int* lpBuffer2 = (int*)(m_pic->GetBuffer());
		char* lpMask2 = (char*)(m_pic->GetMaskPic());
		
		int deltaX = pt2.x - pt1.x;
		int deltaY = pt2.y - pt1.y;

		SIZE sz = m_pic->GetPicSize();

		lpBuffer2 += deltaX;
		lpBuffer2 += deltaY * sz.cx;

		lpMask2 += deltaX;
		lpMask2 += deltaY * sz.cx;

		int srcX = pt1.x;
		int srcY = pt1.y;

		m_pic->ChangeTranslateBlt(putX,putY,srcX,srcY,sizeX,sizeY,percent,ps2,m_pic,pt2.x,pt2.y);
	}
}


void CCommonAnimeParts::AppearPrint(POINT pt,int appearCount, int appearCountMax, int appearType)
{
//	POINT pt = m_animePrintZahyo;


	int dva = appearCountMax;
	if (dva < 1) dva = 1;

	int appearPercent = 100;
	if (appearType & 1)
	{
		appearPercent = (100 * appearCount) / dva;
		if (appearPercent < 0) appearPercent = 0;
		if (appearPercent > 100) appearPercent = 100;
	}

	int putX = pt.x;
	int putY = pt.y;
	int sizeX = m_animePicSize.cx;
	int sizeY = m_animePicSize.cy;

	CAreaControl::AddArea(putX, putY, sizeX, sizeY);


	int type = m_animeType;
	int speed = m_animeSpeed;
	int count = m_animeCount;
	int pattern = m_animePattern;

	int revFlag = 0;
	int dv = pattern;

	if (speed < 1) speed = 1;

	if ((type == 3) || (type == 4) || (type == 7) || (type == 8))
	{
		dv = (pattern - 1) * 2;
		if (dv < 1) dv = 1;
		revFlag = 1;
	}


	int pic1 = count / speed;
	int pic2 = pic1 + 1;

	if (m_limitFlag)
	{
		int limData = dv - 1;
		if (revFlag) limData = dv;

		if (pic1 >= dv) pic1 = limData;
		if (pic2 >= dv) pic2 = limData;
	}

	pic2 %= dv;

	int percent = 100;

	if (revFlag)
	{
		if (pic1 >= pattern) pic1 = (pattern - 1) * 2 - pic1;
		if (pic2 >= pattern) pic2 = (pattern - 1) * 2 - pic2;
	}

	if (type >= 5)
	{
		percent = 100 * (speed - (count - ((count / speed) * speed)));
		percent /= speed;
	}


	//print
	POINT pt1 = GetPicSrc(pic1);
	POINT pt2 = GetPicSrc(pic2);



	if (percent == 100)
	{
//		m_pic->Blt(putX, putY, pt1.x, pt1.y, sizeX, sizeY, TRUE);
		m_pic->TransLucentBlt3(putX, putY, pt1.x, pt1.y, sizeX, sizeY, appearPercent);
	}
	else if (percent == 0)
	{
//		m_pic->Blt(putX, putY, pt2.x, pt2.y, sizeX, sizeY, TRUE);
		m_pic->TransLucentBlt3(putX, putY, pt2.x, pt2.y, sizeX, sizeY, appearPercent);
	}
	else
	{
		int ps2 = 100 - percent;
		int* lpBuffer2 = (int*)(m_pic->GetBuffer());
		char* lpMask2 = (char*)(m_pic->GetMaskPic());

		int deltaX = pt2.x - pt1.x;
		int deltaY = pt2.y - pt1.y;

		SIZE sz = m_pic->GetPicSize();

		lpBuffer2 += deltaX;
		lpBuffer2 += deltaY * sz.cx;

		lpMask2 += deltaX;
		lpMask2 += deltaY * sz.cx;

		int srcX = pt1.x;
		int srcY = pt1.y;

//		m_pic->ChangeTranslateBlt(putX, putY, srcX, srcY, sizeX, sizeY, percent, ps2, m_pic, pt2.x, pt2.y);
		m_pic->ChangeTranslateBlt(putX, putY, srcX, srcY, sizeX, sizeY, (percent*appearPercent)/100, (ps2*appearPercent)/100, m_pic, pt2.x, pt2.y);
	}

}


POINT CCommonAnimeParts::GetPicSrc(int n)
{
	int nx = n % m_yokoKosuu;
	int ny = n / m_yokoKosuu;
	POINT pt;
	pt.x = nx * m_animePicSize.cx;
	pt.y = ny * m_animePicSize.cy;
	return pt;
}

BOOL CCommonAnimeParts::GetInitGameParam(int* lpVar, LPSTR name,int initData)
{
	*lpVar = initData;
	return GetInitGameParam(lpVar,name);
}

BOOL CCommonAnimeParts::GetInitGameParam(int* lpVar, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpVar = atoi(m_setup->GetName(rNum + 1));

	return TRUE;
}

BOOL CCommonAnimeParts::GetInitGameString(LPSTR* lpStr, LPSTR name,LPSTR initString)
{
	*lpStr = initString;
	return GetInitGameString(lpStr,name);
}

BOOL CCommonAnimeParts::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_setup->GetName(rNum + 1);

	return TRUE;
}



/*_*/

