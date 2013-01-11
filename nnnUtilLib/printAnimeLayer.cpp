#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"


#include "..\nnnUtilLib\nameList.h"


#include "printAnimeLayer.h"

char CPrintAnimeLayer::m_defaultPicFileName[]= "ta_anime";


CPrintAnimeLayer::CPrintAnimeLayer(CNameList* setup,LPSTR tagName,CPicture* lpBG)
{
	m_setup = setup;
	m_commonBG = lpBG;

	m_pic = NULL;
	m_animeCountMax = 1;
	m_animePicSize.cx = 16;
	m_animePicSize.cy = 16;
	m_animePattern = 1;
	m_animeSpeed = 1;
	m_animeType = 1;
	m_yokoKosuu = 1;
	m_varNumber = -1;
	m_varName = NULL;
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

	wsprintf(name,"%sVarName",tagName);
	GetInitGameString(&m_varName,name);

	if (lpBG == NULL)
	{
		m_bgPrintFlag = 0;
	}
	else
	{
		m_bgPrintFlag = 1;
		int allPrint = 0;
		GetInitGameParam(&allPrint,"mustAllPrint");
		if (allPrint)
		{
			m_bgPrintFlag = 0;
		}
		int backScript = 0;
		GetInitGameParam(&backScript,"backScriptFlag");
		if (backScript)
		{
			m_bgPrintFlag = 0;
		}

	}


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

	Clear();
}



CPrintAnimeLayer::~CPrintAnimeLayer()
{
	End();
}


void CPrintAnimeLayer::End(void)
{
}


LPSTR CPrintAnimeLayer::GetPictureFileName(void)
{
	return m_picFileName;
}

void CPrintAnimeLayer::SetPicture(CPicture* lpPic)
{
	m_pic = lpPic;
	SIZE sz = m_pic->GetPicSize();
	int sizeX = sz.cx;
	int sizeY = sz.cy;
	m_yokoKosuu = sizeX / m_animePicSize.cx;
	if (m_yokoKosuu<1) m_yokoKosuu = 1;
}


void CPrintAnimeLayer::Clear(void)
{
	m_animeNumber = -1;
	m_animeCount = 0;
}

void CPrintAnimeLayer::Print(int anime,BOOL dontErase)
{
	Print(m_animePrintZahyo,anime,dontErase);
}
void CPrintAnimeLayer::Print(POINT pt,int anime,BOOL dontErase)
{
	if (anime != m_animeNumber)
	{
		m_animeNumber = anime;
		m_animeCount = 0;
	}

	if (m_animeNumber < 1) return;

	int putX = pt.x;
	int putY = pt.y;
	int sizeX = m_animePicSize.cx;
	int sizeY = m_animePicSize.cy;

	if (dontErase == FALSE)
	{
		if (m_commonBG != NULL)
		{
			if (m_bgPrintFlag)
			{
				m_commonBG->Blt(putX,putY,putX,putY,sizeX,sizeY,FALSE);
			}
		}
	}
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
	POINT pt1 = GetPicSrc((m_animeNumber-1) * m_animePattern + pic1);
	POINT pt2 = GetPicSrc((m_animeNumber-1) * m_animePattern + pic2);



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



	//anime
	m_animeCount++;
	if (m_limitFlag)
	{
		if (m_animeCount >= m_animeCountMax) m_animeCount = m_animeCountMax;
	}
	else
	{
		m_animeCount %= m_animeCountMax;
	}
}




POINT CPrintAnimeLayer::GetPicSrc(int n)
{
	int nx = n % m_yokoKosuu;
	int ny = n / m_yokoKosuu;
	POINT pt;
	pt.x = nx * m_animePicSize.cx;
	pt.y = ny * m_animePicSize.cy;
	return pt;
}

BOOL CPrintAnimeLayer::GetInitGameParam(int* lpVar, LPSTR name,int initData)
{
	*lpVar = initData;
	return GetInitGameParam(lpVar,name);
}

BOOL CPrintAnimeLayer::GetInitGameParam(int* lpVar, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpVar = atoi(m_setup->GetName(rNum + 1));

	return TRUE;
}

BOOL CPrintAnimeLayer::GetInitGameString(LPSTR* lpStr, LPSTR name,LPSTR initString)
{
	*lpStr = initString;
	return GetInitGameString(lpStr,name);
}

BOOL CPrintAnimeLayer::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_setup->GetName(rNum + 1);

	return TRUE;
}
