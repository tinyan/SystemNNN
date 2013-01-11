//
// messageCursor.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"


#include "floatinglayer.h"
#include "messageCursor.h"


char CMessageCursor::m_defaultCursorFileName[] = "mes_cur";

CMessageCursor::CMessageCursor(CTaihi* lpTaihi, int n) : CFloatingLayer(lpTaihi,n)
{
	LoadSetupFile("messageCursor",64);

	int i = 0;
	int j = 0;
	int k = 0;

	for (i=0;i<4;i++)
	{
		m_sizeX[i] = 32;
		m_sizeY[i] = 32;
		m_printX[i] = 0;
		m_printY[i] = 0;
	}

	m_fullFixX = 0;
	m_fullFixY = 0;

	GetInitGameParam(&m_fullFixX,"fullFixX");
	GetInitGameParam(&m_fullFixY,"fullFixY");



	for (i=0;i<4;i++)
	{
		m_loadedCursorNumberConfig[i] = -1;
		m_loadedCursorNumberScript[i] = -1;
	}

	m_cursorShuruiConfig = 1;
	m_cursorShuruiScript = 1;
	GetInitGameParam(&m_cursorShuruiConfig,"cursorNumberConfig");
	GetInitGameParam(&m_cursorShuruiScript,"cursorNumberScript");

	if (m_cursorShuruiConfig<1) m_cursorShuruiConfig = 1;
	if (m_cursorShuruiScript<1) m_cursorShuruiScript = 1;

	m_ppCursorFileName = new LPSTR[m_cursorShuruiConfig * m_cursorShuruiScript*4];

	m_cursorNumberScript = 0;
	m_cursorNumberConfig = 0;

	for (i=0;i<4;i++)
	{
		m_cursorPic[i] = new CPicture();
	}


	LPSTR cursorfilename = m_defaultCursorFileName;
	GetInitGameString(&cursorfilename,"filenameCursor1");
	m_ppCursorFileName[0] = cursorfilename;


	for (i=1;i<4;i++)
	{
		LPSTR cursorfilename2 = cursorfilename;
		char name[256];
		wsprintf(name,"filenameCursor%d",i+1);
		GetInitGameString(&cursorfilename2,name);
		m_ppCursorFileName[i] = cursorfilename2;
	}


	if ((m_cursorShuruiConfig > 1) || (m_cursorShuruiScript>1))
	{
		for (j=0;j<m_cursorShuruiScript;j++)
		{
			for (i=0;i<m_cursorShuruiConfig;i++)
			{
				for (k=0;k<4;k++)
				{
					char name[256];
					LPSTR cname = m_ppCursorFileName[k];
					if ((m_cursorShuruiScript > 1) && (m_cursorShuruiConfig > 1))
					{
						wsprintf(name,"filenameCursor%d_%d_%d",k+1,j+1,i+1);
					}
					else
					{
						if (m_cursorShuruiScript <= 1)
						{
							wsprintf(name,"filenameCursor%d_%d",k+1,i+1);
						}
						else
						{
							wsprintf(name,"filenameCursor%d_%d",k+1,j+1);
						}
					}

					GetInitGameString(&cname,name);
					m_ppCursorFileName[(j*m_cursorShuruiConfig+i)*4+k] = cname;
				}
			}
		}
	}







	GetInitGameParam(&m_sizeX[0],"sizeX1");
	GetInitGameParam(&m_sizeY[0],"sizeY1");
	GetInitGameParam(&m_printX[0],"printX1");
	GetInitGameParam(&m_printY[0],"printY1");

	for (i=1;i<4;i++)
	{
		m_sizeX[i] = m_sizeX[0];
		m_sizeY[i] = m_sizeY[0];

		m_printX[i] = m_printX[i-1];
		m_printY[i] = m_printY[i-1];

		if (i==2)
		{
			m_printX[i] = 0;
			m_printY[i] = 0;
		}


		char name[256];
		wsprintf(name,"sizeX%d",i+1);
		GetInitGameParam(&m_sizeX[i],name);
		wsprintf(name,"sizeY%d",i+1);
		GetInitGameParam(&m_sizeY[i],name);
		wsprintf(name,"printX%d",i+1);
		GetInitGameParam(&m_printX[i],name);
		wsprintf(name,"printY%d",i+1);
		GetInitGameParam(&m_printY[i],name);
	}




	int sizeX = m_sizeX[0];
	int sizeY = m_sizeY[0];

	for (i=1;i<4;i++)
	{
		if (m_sizeX[i] > sizeX) sizeX = m_sizeX[i];
		if (m_sizeY[i] > sizeY) sizeY = m_sizeY[i];
	}


	CreateLayer(sizeX,sizeY);	//1‚±!


	m_animePatternKosuu[0] = 1;
	GetInitGameParam(&m_animePatternKosuu[0],"animePattern1");
	m_animeSpeed[0] = 1;
	GetInitGameParam(&m_animeSpeed[0],"animeSpeed1");
	m_animeReverse[0] = 0;
	GetInitGameParam(&m_animeReverse[0],"animeReverse1");

	for (i=1;i<4;i++)
	{
		char name[256];
		m_animePatternKosuu[i] = m_animePatternKosuu[0];
		wsprintf(name,"animePattern%d",i+1);
		GetInitGameParam(&m_animePatternKosuu[i],name);

		m_animeSpeed[i] = m_animeSpeed[0];
		wsprintf(name,"animeSpeed%d",i+1);
		GetInitGameParam(&m_animeSpeed[i],name);

		m_animeReverse[i] = m_animeReverse[0];
		wsprintf(name,"animeReverse%d",i+1);
		GetInitGameParam(&m_animeReverse[i],name);
	}




	m_percentStart[0] = 100;
	m_percentEnd[0] = 100;
	m_percentReverseFlag[0] = 1;
	m_percentLoop[0] = 1;

	GetInitGameParam(&m_percentStart[0],"percentStart1");
	GetInitGameParam(&m_percentEnd[0],"percentEnd1");
	GetInitGameParam(&m_percentLoop[0],"percentLoop1");
	GetInitGameParam(&m_percentReverseFlag[0],"percentReverse1");

	for (i=1;i<4;i++)
	{
		m_percentStart[i] = m_percentStart[0];
		m_percentEnd[i] = m_percentEnd[0];
		m_percentReverseFlag[i] = m_percentReverseFlag[0];
		m_percentLoop[i] = m_percentLoop[0];

		char name[256];
		
		wsprintf(name,"percentStart%d",i+1);
		GetInitGameParam(&m_percentStart[i],name);

		wsprintf(name,"percentEnd%d",i+1);
		GetInitGameParam(&m_percentEnd[i],name);

		wsprintf(name,"percentLoop%d",i+1);
		GetInitGameParam(&m_percentLoop[i],name);

		wsprintf(name,"percentReverse%d",i+1);
		GetInitGameParam(&m_percentReverseFlag[i],name);
	}


	for (i=0;i<4;i++)
	{
		m_animeCount[i] = 0;
		m_animePattern[i] = 0;
		m_percentCount[i] = 0;
	}

	for (i=0;i<4;i++)
	{
		LoadMyCursor(i);
	}
}



CMessageCursor::~CMessageCursor()
{
	End();
}


void CMessageCursor::End(void)
{
	for (int i=0;i<4;i++)
	{
		ENDDELETECLASS(m_cursorPic[i]);
	}
	DELETEARRAY(m_ppCursorFileName);
}


void CMessageCursor::Calcu(int count)
{
	for (int i=0;i<4;i++)
	{
		int c = m_animeCount[i] + count;
		if (c >= m_animeSpeed[i])
		{
			int dlt = c / m_animeSpeed[i];
			int dv = m_animePatternKosuu[i];
			if (m_animeReverse[i])
			{
				dv += (dv - 2);
				if (dv<1) dv = 1;
			}
			c %= m_animeSpeed[i];

			m_animePattern[i] += dlt;
			m_animePattern[i] %= dv;
		}

		m_animeCount[i] = c;



		m_percentCount[i]++;
		int dv = m_percentLoop[i];
		if (m_percentReverseFlag[i] != 0)
		{
			dv *= 2;
		}
		m_percentCount[i] %= dv;
	}

}


void CMessageCursor::Print(int type, BOOL taihiFlag)
{
	if (CheckCursorLoaded(type) == FALSE)
	{
		LoadMyCursor(type);
	}

	int putX = m_printX[type];
	int putY = m_printY[type];
	int sizeX = m_sizeX[type];
	int sizeY = m_sizeY[type];

	if (type >= 2)
	{
		if (m_fullFixX == 0) putX += m_fullPrintX;
		if (m_fullFixY == 0) putY += m_fullPrintY;
	}


	int pt = m_animePattern[type];
	if (m_animeReverse[type])
	{
		int ptdv = m_animePatternKosuu[type];
		ptdv += (ptdv - 2);
		if (ptdv<1) ptdv = 1;

		if (pt >= m_animePattern[type])
		{
			pt = ptdv - pt;
		}
	}




//	int srcX = m_animePattern[type] * sizeX;
	int srcX = pt * sizeX;
	int srcY = type * sizeY;
	srcY = 0;
	CPicture* lpPic = m_cursorPic[type];

//	if (type > 0)
//	{
//		if (m_cursorPicFlag[type])
//		{
//			srcY = 0;
//			lpPic = m_cursorPic[type];
//		}
//	}

	if (taihiFlag) Taihi(putX,putY);

	CAreaControl::AddArea(putX,putY,sizeX,sizeY);

	int ps = m_percentStart[type];
	if (m_percentStart[type] != m_percentEnd[type])
	{
		int dv = m_percentLoop[type];
		int ps1 = m_percentStart[type];
		int ps2 = m_percentEnd[type];
		int c = m_percentCount[type];

		if (m_percentReverseFlag[type] != 0)
		{
//			dv /= 2;
//			if (dv<=0) dv = 1;
			if (c >= dv)
			{
				c = 2*dv - c;
//				ps1 = m_percentEnd[type];
//				ps2 = m_percentStart[type];
			}
		}

		ps = ps1 + ((ps2 - ps1) * c) / dv;
		if (ps<0) ps = 0;
		if (ps>100) ps = 100;
	}

	if (ps == 100)
	{
		lpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
	}
	else if (ps>0)
	{
		lpPic->TransLucentBlt3(putX,putY,srcX,srcY,sizeX,sizeY,ps);
	}
}


void CMessageCursor::SetFullZahyo(int x, int y)
{
	m_fullPrintX = x;
	m_fullPrintY = y;
}


BOOL CMessageCursor::CheckCursorLoaded(int type)
{
	if (m_loadedCursorNumberConfig[type] != m_cursorNumberConfig) return FALSE;
	if (m_loadedCursorNumberScript[type] != m_cursorNumberScript) return FALSE;

	return TRUE;
}


void CMessageCursor::LoadMyCursor(int type)
{
	int n = m_cursorNumberScript * m_cursorShuruiConfig + m_cursorNumberConfig;
	n *= 4;
	n += type;

	char filename[256];
	wsprintf(filename,"sys\\%s",m_ppCursorFileName[n]);

	m_cursorPic[type]->LoadDWQ(filename);


	m_loadedCursorNumberConfig[type] = m_cursorNumberConfig;
	m_loadedCursorNumberScript[type] = m_cursorNumberScript;
}



