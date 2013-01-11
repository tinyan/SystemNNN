//
// gameMouse.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"

#include "..\nyanLib\include\allGeo.h"

#include "taihi.h"

#include "animeControl.h"

#include "FloatingLayer.H"
#include "gameMouse.h"


char CGameMouse::m_defaultMousePicFileName[] = "ta_mouse";



CGameMouse::CGameMouse(CTaihi* lpTaihi, int taihiLayer) : CFloatingLayer(lpTaihi, taihiLayer)
{
	int i = 0;
	int j = 0;

	m_animeCount = 0;
	m_specialMode = 0;
	m_zanzouKosuuMax = 5;
	m_zanzouKosuu = 0;
	m_zanzouNumber = 0;

	for (i=0;i<30;i++)
	{
		m_zanzou[i].x = 0;
		m_zanzou[i].y = 0;
	}

	LoadSetupFile("gameMouse");	

	int zanzouKosuuMax = 5;
	GetInitGameParam(&zanzouKosuuMax,"zanzouNumber");
	SetZanzouKosuuMax(zanzouKosuuMax);

	int specialMode = 0;
	GetInitGameParam(&specialMode,"specialMode");
	SetSpecialMode(specialMode);


	m_hotPointX = 0;
	m_hotPointY = 0;
	LPSTR mousePicFileName = m_defaultMousePicFileName;
	m_mouseSizeX = 32;
	m_mouseSizeY = 32;
	m_mousePrintPercent = 100;
	m_animeCountMax = 1;

	m_loadedMouseNumberConfig = -1;
	m_loadedMouseNumberScript = -1;

	m_mouseShuruiConfig = 1;
	m_mouseShuruiScript = 1;
	GetInitGameParam(&m_mouseShuruiConfig,"mouseNumberConfig");
	GetInitGameParam(&m_mouseShuruiScript,"mouseNumberScript");
	if (m_mouseShuruiConfig<1) m_mouseShuruiConfig = 1;
	if (m_mouseShuruiScript<1) m_mouseShuruiScript = 1;

	m_mouseNumberConfig = 0;
	m_mouseNumberScript = 0;

	GetInitGameParam(&m_mouseSizeX,"sizeX");
	GetInitGameParam(&m_mouseSizeY,"sizeY");
	GetInitGameParam(&m_hotPointX,"hotPointX");
	GetInitGameParam(&m_hotPointY,"hotPointY");
	GetInitGameParam(&m_mousePrintPercent,"percent");
	GetInitGameParam(&m_animeCountMax,"anime");	//not used
	GetInitGameString(&mousePicFileName,"fileNameMouse");


	m_ppMouseFileName = new LPSTR[m_mouseShuruiConfig* m_mouseShuruiScript];
	m_ppMouseFileName[0] = mousePicFileName;

	if ((m_mouseShuruiScript> 1) || (m_mouseShuruiConfig > 1))
	{
		for (j=0;j<m_mouseShuruiScript;j++)
		{
			for (i=0;i<m_mouseShuruiConfig;i++)
			{
				char name[256];
				LPSTR mname = mousePicFileName;

				if ((m_mouseShuruiScript > 1) && (m_mouseShuruiConfig > 1))
				{
					wsprintf(name,"filenameMouse%d_%d",j+1,i+1);
				}
				else
				{
					if (m_mouseShuruiScript <= 1)
					{
						wsprintf(name,"filenameMouse%d",i+1);
					}
					else
					{
						wsprintf(name,"filenameMouse%d",j+1);
					}
				}

				GetInitGameString(&mname,name);
				m_ppMouseFileName[j*m_mouseShuruiConfig+i] = mname;
			}
		}
	}




	CreateLayer(m_mouseSizeX,m_mouseSizeY);

	m_animeType = 1;
	m_animePattern = m_animeCountMax;
	m_animeSpeed = 1;

	GetInitGameParam(&m_animeType,"animeType");
	GetInitGameParam(&m_animePattern,"animePattern");
	GetInitGameParam(&m_animeSpeed,"animeSpeed");
	m_animeControl = new CAnimeControl();
	m_animeControl->SetParam(m_animeType,m_animePattern,m_animeSpeed);

	m_mousePic = new CPicture();
	LoadMyMouse();
}


CGameMouse::~CGameMouse()
{
	End();
}


void CGameMouse::End(void)
{
	ENDDELETECLASS(m_mousePic);
	ENDDELETECLASS(m_animeControl);
	DELETEARRAY(m_ppMouseFileName);
}

void CGameMouse::CalcuMouseAnime(int count)
{
//	m_animeCount += count;
//	m_animeCount %= m_animeCountMax;

	m_animeControl->Calcu(count);
}

void CGameMouse::Print(int x, int y, int type, BOOL taihiFlag)
{
	if (CheckMouseLoaded() == FALSE)
	{
		LoadMyMouse();
	}

	if (taihiFlag)
	{
		Taihi(x-m_hotPointX, y-m_hotPointY);
	}

//	int srcX = m_animeCount * m_mouseSizeX;
//	int srcY = type * m_mouseSizeY;

	
	int putX = x - m_hotPointX;
	int putY = y - m_hotPointY;
	int sizeX = m_mouseSizeX;
	int sizeY = m_mouseSizeY;
	CAreaControl::AddArea(putX,putY,sizeX,sizeY);




	int pat1 = m_animeControl->GetAnimePic1();
	int pat2 = m_animeControl->GetAnimePic2();
	int percent = m_animeControl->GetAnimePercent();

	int srcX1 = sizeX * pat1;
	int srcY1 = sizeY * type;
	int srcX2 = sizeX * pat2;
	int srcY2 = sizeY * type;

	if (m_specialMode != 0)
	{
		CAreaControl::SetNextAllPrint();
		PrintSpecialMode(putX,putY,type,pat1,pat2,percent);
	}


	if (percent == 100)
	{
		m_mousePic->Blt(putX,putY,srcX1,srcY1,sizeX,sizeY,TRUE);
	}
	else if (percent == 0)
	{
		m_mousePic->Blt(putX,putY,srcX2,srcY2,sizeX,sizeY,TRUE);
	}
	else
	{
		int ps2 = 100 - percent;
		int* lpBuffer2 = (int*)(m_mousePic->GetBuffer());
		char* lpMask2 = (char*)(m_mousePic->GetMaskPic());
		
		int deltaX = srcX2 - srcX1;
		int deltaY = srcY2 - srcY1;
	
		SIZE sz = m_mousePic->GetPicSize();

		lpBuffer2 += deltaX;
		lpBuffer2 += deltaY * sz.cx;

		lpMask2 += deltaX;
		lpMask2 += deltaY * sz.cx;

		int srcX = srcX1;
		int srcY = srcY1;

//		m_mousePic->ChangeTranslateBlt(putX,putY,srcX,srcY,sizeX,sizeY,percent,ps2,lpBuffer2,lpMask2,m_mousePic);
		m_mousePic->ChangeTranslateBlt(putX,putY,srcX,srcY,sizeX,sizeY,percent,ps2,m_mousePic,srcX2,srcY2);

	}





	if (m_mousePrintPercent == 100)
	{
//		m_mousePic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
	}
	else if ((m_mousePrintPercent > 0) && (m_mousePrintPercent < 100))
	{
//		m_mousePic->TransLucentBlt_2(putX,putY,srcX,srcY,sizeX,sizeY,m_mousePrintPercent);
	}

}

BOOL CGameMouse::CheckMouseLoaded(void)
{
	if (m_loadedMouseNumberConfig != m_mouseNumberConfig) return FALSE;
	if (m_loadedMouseNumberScript != m_mouseNumberScript) return FALSE;

	return TRUE;
}

void CGameMouse::LoadMyMouse(void)
{
	int n = m_mouseNumberScript * m_mouseShuruiConfig + m_mouseNumberConfig;

	char filename[256];
	wsprintf(filename,"sys\\%s",m_ppMouseFileName[n]);
	m_mousePic->LoadDWQ(filename);

	m_loadedMouseNumberConfig = m_mouseNumberConfig;
	m_loadedMouseNumberScript = m_mouseNumberScript;
}


void CGameMouse::PrintSpecialMode(int putX,int putY, int type,int pat1,int pat2,int percent)
{
	int sizeX = m_mouseSizeX;
	int sizeY = m_mouseSizeY;
	int srcX1 = sizeX * pat1;
	int srcY1 = sizeY * type;
	int srcX2 = sizeX * pat2;
	int srcY2 = sizeY * type;

	if (m_specialMode == 1)
	{
		POINT pt;
		pt.x = putX;
		pt.y = putY;
		m_zanzou[m_zanzouNumber] = pt;

		int n = m_zanzouNumber;
		m_zanzouNumber++;
		m_zanzouNumber %= (m_zanzouKosuuMax*3);
		if (m_zanzouKosuu < m_zanzouKosuuMax)
		{
			m_zanzouKosuu++;
		}
		if (m_zanzouKosuu>m_zanzouKosuuMax) m_zanzouKosuu = m_zanzouKosuuMax;
	}

	if (m_specialMode == 2)
	{
		POINT pt;
		pt.x = putX;
		pt.y = putY;

		for (int i=0;i<10;i++)
		{
			int dx = (rand() % 14)-7;
			int dy = -(rand() % 16)-4;

			m_kiraSpeed[m_zanzouNumber][i].x = dx;
			m_kiraSpeed[m_zanzouNumber][i].y = dy;
			m_kira[m_zanzouNumber][i].x = putX;
			m_kira[m_zanzouNumber][i].y = putY;
		}

		int n = m_zanzouNumber;
		m_zanzouNumber++;
		m_zanzouNumber %= (m_zanzouKosuuMax*3);
		if (m_zanzouKosuu < m_zanzouKosuuMax*3)
		{
			m_zanzouKosuu++;
		}
	}


	if (m_specialMode == 1)	//Žc‘œ
	{
		int n = m_zanzouNumber;
		n -= 3;
		n += (m_zanzouKosuuMax*3);
		n %= (m_zanzouKosuuMax*3);

		for (int i=0;i<m_zanzouKosuu;i++)
		{
			n -= 3;
			n += (m_zanzouKosuuMax*3);
			n %= (m_zanzouKosuuMax*3);
			POINT pt2 = m_zanzou[n];

			int ps1 = percent;
			int ps2 = 100-percent;

			int dv = m_zanzouKosuuMax;
			if (dv<1) dv = 1;

			int ml = ((m_zanzouKosuuMax-i)*60)/dv;
			ml += 10;
			if (ml>100) ml = 100;
			if (ml<1) ml = 1;

			ps1 *= ml;
			ps1 /= 100;

			ps2 *= ml;
			ps2 /= 100;
		
			int srcX = srcX1;
			int srcY = srcY1;

			m_mousePic->TransLucentBlt3(pt2.x,pt2.y,srcX,srcY,sizeX,sizeY,ml);
		//	m_mousePic->ChangeTranslateBlt(pt2.x,pt2.y,srcX,srcY,sizeX,sizeY,percent,ps2,m_mousePic,srcX2,srcY2);
		}
	}

	if (m_specialMode == 2)
	{
		int n = m_zanzouNumber;
		n -= 1;
		n += (m_zanzouKosuuMax*3);
		n %= (m_zanzouKosuuMax*3);

		for (int i=0;i<m_zanzouKosuu;i++)
		{
			n -= 1;
			n += (m_zanzouKosuuMax*3);
			n %= (m_zanzouKosuuMax*3);

			int sx = 1;
			int sy = 1;
			if (i<3)
			{
				sx = 1;
				sy = 1;
			}

			int r = ((m_zanzouKosuu-i) * 96) / m_zanzouKosuu;
			r += 32;
			int g = ((m_zanzouKosuu-i) * 160) / m_zanzouKosuu;
			g += 64;
			int b = ((m_zanzouKosuu-i) * 128) / m_zanzouKosuu;
			b += 48;



			int putX0 = m_zanzou[n].x;
			int putY0 = m_zanzou[n].y;

			int t = i+1;

			int grav = 5;

			for (int k=0;k<4;k++)
			{
				POINT pt2 = m_kira[n][k];
				int spx = m_kiraSpeed[n][k].x;
				int spy = m_kiraSpeed[n][k].y;

				int x = pt2.x + spx * t;
				int y = pt2.y + spy * t + grav*t*t/2;
				
				CAllGeo::AddBoxFill(x,y,sx,sy,r,g,b);
			}
		}
	}
}


void CGameMouse::SetZanzouKosuuMax(int mx)
{
	if (mx>10) mx = 10;
	m_zanzouKosuuMax = mx;
}

POINT CGameMouse::GetMouseHotPoint(void)
{
	POINT pt;
	pt.x = m_hotPointX;
	pt.y = m_hotPointY;
	return pt;
}
