//
// 
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"

#include "basicSetup.h"
#include "commonMessageWindow.h"



char CCommonMessageWindow::m_defaultWindowFileName[] = "ta_meswin";
char CCommonMessageWindow::m_defaultWindowFileName2[] = "ta_namewin";



CCommonMessageWindow::CCommonMessageWindow()
{
	int i,j;

	LoadSetupFile("messageWindow",64);

	m_windowPercent = 100;

	m_loadedWindowNumberConfig = -1;
	m_loadedWindowNumberScript = -1;
	m_loadedWindowNumberFontSizeType = -1;

	m_loadedNameWindowNumberConfig = -1;
	m_loadedNameWindowNumberScript = -1;
	m_loadedNameWindowNumberFontSizeType = -1;

	m_windowShuruiConfig = 1;
	m_windowShuruiScript = 1;
	m_windowShuruiFontSizeType = 1;

	GetInitGameParam(&m_windowShuruiConfig,"windowNumberConfig");
	GetInitGameParam(&m_windowShuruiScript,"windowNumberScript");
	GetInitGameParam(&m_windowShuruiFontSizeType,"windowNumberFontSizeType");

	m_ppWindowFileName = new LPSTR[m_windowShuruiFontSizeType * m_windowShuruiConfig * m_windowShuruiScript];
	m_ppNameWindowFileName = new LPSTR[m_windowShuruiFontSizeType * m_windowShuruiConfig * m_windowShuruiScript];


	LPSTR windowName = m_defaultWindowFileName;
	GetInitGameString(&windowName,"filenameWindow");

	for (int k=0;k<m_windowShuruiFontSizeType;k++)
	{
		for (j=0;j<m_windowShuruiScript;j++)
		{
			for (i=0;i<m_windowShuruiConfig;i++)
			{
				char name0[256];
				LPSTR wname = windowName;
				if ((m_windowShuruiScript > 1) && (m_windowShuruiConfig > 1))
				{
					wsprintf(name0,"filenameWindow%d_%d",j+1,i+1);
				}
				else
				{
					if (m_windowShuruiScript <= 1)
					{
						wsprintf(name0,"filenameWindow%d",i+1);
					}
					else
					{
						wsprintf(name0,"filenameWindow%d",j+1);
					}
				}

				char name1[256];
				if (k == 0)
				{
					wsprintf(name1,"%s",name0);
				}
				else
				{
					wsprintf(name1,"%s_Font%d",name0,k);
				}

				GetInitGameString(&wname,name1);
				m_ppWindowFileName[k*m_windowShuruiScript*m_windowShuruiConfig + j*m_windowShuruiConfig + i] = wname;
			}
		}
	}

	SetWindowNumberByConfig(0);
	SetWindowNumberByScript(0);
	SetWindowNumberByFontSizeType(0);


	m_windowPic = new CPicture();
	LoadWindow();

//	char filename[256];
//	sprintf(filename,"sys\\%s",windowName);
//
//	m_windowPic = new CPicture(filename);

	m_windowPrintX = 0;
	m_windowPrintY = 300;
	m_windowSizeX = 640;
	m_windowSizeY = 180;

	GetInitGameParam(&m_windowPrintX,"printX");
	GetInitGameParam(&m_windowPrintY,"printY");
	GetInitGameParam(&m_windowSizeX,"sizeX");
	GetInitGameParam(&m_windowSizeY,"sizeY");

	m_nameWindowFlag = 0;
	m_nameWindowPic = NULL;

	GetInitGameParam(&m_nameWindowFlag,"nameWindowFlag");
	if (m_nameWindowFlag)
	{
		m_nameWindowPrintX = 0;
		m_nameWindowPrintY = 200;
		m_nameWindowSizeX = 640;
		m_nameWindowSizeY = 100;

		GetInitGameParam(&m_nameWindowPrintX,"namePrintX");
		GetInitGameParam(&m_nameWindowPrintY,"namePrintY");
		GetInitGameParam(&m_nameWindowSizeX,"nameSizeX");
		GetInitGameParam(&m_nameWindowSizeY,"nameSizeY");

		LPSTR nameWindowName = m_defaultWindowFileName2;
		GetInitGameString(&nameWindowName,"filenameNameWindow");



		for (int k=0;k<m_windowShuruiFontSizeType;k++)
		{
			for (j=0;j<m_windowShuruiScript;j++)
			{
				for (i=0;i<m_windowShuruiConfig;i++)
				{
					char name0[256];
					LPSTR wname = nameWindowName;

					if ((m_windowShuruiScript > 1) && (m_windowShuruiConfig > 1))
					{
						wsprintf(name0,"filenameNameWindow%d_%d",j+1,i+1);
					}
					else
					{
						if (m_windowShuruiScript <= 1)
						{
							wsprintf(name0,"filenameNameWindow%d",i+1);
						}
						else
						{
							wsprintf(name0,"filenameNameWindow%d",j+1);
						}
					}

					char name1[256];
					if (k == 0)
					{
						wsprintf(name1,"%s",name0);
					}
					else
					{
						wsprintf(name1,"%s_Font%d",name0,k);
					}

	//				wsprintf(name,"filenameNameWindow%d_%d",j+1,i+1);
					GetInitGameString(&wname,name1);
					m_ppNameWindowFileName[k*m_windowShuruiScript*m_windowShuruiConfig+  j*m_windowShuruiConfig+i] = wname;
				}
			}
		}





//		char filename[256];
//		wsprintf(filename,"sys\\%s",nameWindowName);

//		m_nameWindowPic = new CPicture(filename);
		m_nameWindowPic = new CPicture();
		LoadNameWindow();
	}


}



CCommonMessageWindow::~CCommonMessageWindow()
{
	End();
}

void CCommonMessageWindow::SetWindowNumberByFontSizeType(int n)
{
	if (n >= m_windowShuruiFontSizeType)
	{
		n = m_windowShuruiFontSizeType-1;
	}

	m_windowNumberFontSizeType = n;
}

void CCommonMessageWindow::End(void)
{
	DELETEARRAY(m_ppWindowFileName);
	DELETEARRAY(m_ppNameWindowFileName);

	ENDDELETECLASS(m_nameWindowPic);
	ENDDELETECLASS(m_windowPic);
}

void CCommonMessageWindow::PrintDirect(BOOL flg,BOOL namePrintFlag,POINT* lpPoint)
{
	POINT deltaPoint;
	deltaPoint.x = lpPoint->x - m_windowPrintX;
	deltaPoint.y = lpPoint->y - m_windowPrintY;
	Print(flg,namePrintFlag,&deltaPoint);
}


void CCommonMessageWindow::Print(BOOL flg,BOOL namePrintFlag,POINT* lpDeltaPoint)
{
	if (flg)
	{
		POINT deltaPoint;
		deltaPoint.x = 0;
		deltaPoint.y = 0;
		if (lpDeltaPoint != NULL)
		{
			deltaPoint = *lpDeltaPoint;
		}

		if (CheckWindowLoaded() == FALSE)
		{
			LoadWindow();
		}

		if (m_windowPercent >= 100)
		{
			m_windowPic->Blt(m_windowPrintX+deltaPoint.x,m_windowPrintY+deltaPoint.y,0,0,m_windowSizeX,m_windowSizeY,TRUE);
		}
		else if (m_windowPercent > 0)
		{
			m_windowPic->TransLucentBlt3(m_windowPrintX+deltaPoint.x,m_windowPrintY+deltaPoint.y,0,0,m_windowSizeX,m_windowSizeY,m_windowPercent);
		}

		if (namePrintFlag)
		{
			if (m_nameWindowFlag)
			{
				if (CheckNameWindowLoaded() == FALSE)
				{
					LoadNameWindow();
				}

				if (m_windowPercent >= 100)
				{
					m_nameWindowPic->Blt(m_nameWindowPrintX+deltaPoint.x,m_nameWindowPrintY+deltaPoint.y,0,0,m_nameWindowSizeX,m_nameWindowSizeY,TRUE);
				}
				else if (m_windowPercent > 0)
				{
					m_nameWindowPic->TransLucentBlt3(m_nameWindowPrintX+deltaPoint.x,m_nameWindowPrintY+deltaPoint.y,0,0,m_nameWindowSizeX,m_nameWindowSizeY,m_windowPercent);
				}
			}
		}
	}
}


BOOL CCommonMessageWindow::CheckWindowLoaded(void)
{
	if (m_loadedWindowNumberConfig != m_windowNumberConfig) return FALSE;
	if (m_loadedWindowNumberScript != m_windowNumberScript) return FALSE;
	if (m_loadedWindowNumberFontSizeType != m_windowNumberFontSizeType) return FALSE;

	return TRUE;
}

BOOL CCommonMessageWindow::CheckNameWindowLoaded(void)
{
	if (m_loadedNameWindowNumberConfig != m_windowNumberConfig) return FALSE;
	if (m_loadedNameWindowNumberScript != m_windowNumberScript) return FALSE;
	if (m_loadedNameWindowNumberFontSizeType != m_windowNumberFontSizeType) return FALSE;

	return TRUE;
}

void CCommonMessageWindow::LoadWindow(void)
{
	int n = m_windowNumberFontSizeType * m_windowShuruiScript * m_windowShuruiConfig + m_windowNumberScript * m_windowShuruiConfig + m_windowNumberConfig;

	char filename[256];
	wsprintf(filename,"sys\\%s",m_ppWindowFileName[n]);
	if (m_windowPic == NULL) m_windowPic = new CPicture();
	//m_windowPic = new CPicture(filename);
	m_windowPic->LoadDWQ(filename);

	m_loadedWindowNumberConfig = m_windowNumberConfig;
	m_loadedWindowNumberScript = m_windowNumberScript;
	m_loadedWindowNumberFontSizeType = m_windowNumberFontSizeType;
}


void CCommonMessageWindow::LoadNameWindow(void)
{
	int n = m_windowNumberFontSizeType * m_windowShuruiScript * m_windowShuruiConfig + m_windowNumberScript * m_windowShuruiConfig + m_windowNumberConfig;

	char filename[256];
	wsprintf(filename,"sys\\%s",m_ppNameWindowFileName[n]);
	//m_nameWindowPic = new CPicture(filename);
	if (m_nameWindowPic == NULL) m_nameWindowPic = new CPicture();
	m_nameWindowPic->LoadDWQ(filename);

	m_loadedNameWindowNumberConfig = m_windowNumberConfig;
	m_loadedNameWindowNumberScript = m_windowNumberScript;
	m_loadedNameWindowNumberFontSizeType = m_windowNumberFontSizeType;
}


BOOL CCommonMessageWindow::CheckOn(POINT pt, BOOL nameCheckFlag)
{
	int x = pt.x - m_windowPrintX;
	int y = pt.y - m_windowPrintY;
	if ((x>=0) && (x<m_windowSizeX) && (y>=0) && (y<m_windowSizeY)) return TRUE;
	if (m_nameWindowFlag)
	{
		if (nameCheckFlag)
		{
			int x2 = pt.x - m_nameWindowPrintX;
			int y2 = pt.y - m_nameWindowPrintY;
			 
			if ((x2>=0) && (x2<m_nameWindowSizeX) && (y2>=0) && (y2<m_nameWindowSizeY)) return TRUE;
		}
	}

	return FALSE;
}

//
BOOL CCommonMessageWindow::CheckOnSize(POINT pt, BOOL nameCheckFlag)
{
	POINT pt2;
	pt2.x = m_windowPrintX + pt.x;
	pt2.y = m_windowPrintY + pt.y;
	return CheckOn(pt2,nameCheckFlag);
}



/*_*/


