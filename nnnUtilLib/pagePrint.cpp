//
// pagePrint
//

#include <windows.h>

#include "..\nyanlib\include\commonMacro.h"
#include "..\nyanlib\include\picture.h"
#include "..\nyanlib\include\areaControl.h"

#include "nameList.h"

#include "suuji.h"


#include "pagePrint.h"

char CPagePrint::m_defaultPageFontFileName[]="ta_font_sl3";

CPagePrint::CPagePrint(CNameList* namelist,CPicture* lpBG)
{
	m_setup = namelist;
	m_bg = lpBG;

	m_pagePrintFlag = 0;
	GetInitGameParam(&m_pagePrintFlag,"pagePrintFlag");
	m_suuji = NULL;
	m_suujiMax = NULL;
	m_fontPic = NULL;

	m_pageMaxPrintFlag = 0;
	m_slashPrintFlag = 0;

	m_pagePrintX = 0;
	m_pagePrintY = 0;

	m_upZeroPrintFlag = 0;

	if (m_pagePrintFlag)
	{
		GetInitGameParam(&m_upZeroPrintFlag,"pageUpZeroPrintFlag");
		m_keta = 2;
		GetInitGameParam(&m_keta,"pageKeta");

		m_fontSizeX = 21;
		m_fontSizeY = 27;

		GetInitGameParam(&m_fontSizeX,"pageFontSizeX");
		GetInitGameParam(&m_fontSizeY,"pageFontSizeY");
		m_fontNextX = m_fontSizeX;
		GetInitGameParam(&m_fontNextX,"pageFontNextX");

		GetInitGameParam(&m_pagePrintX,"pagePrintX");
		GetInitGameParam(&m_pagePrintY,"pagePrintY");

		LPSTR fontName = m_defaultPageFontFileName;

		GetInitGameString(&fontName,"fileNamePageFont");
		m_fontPic = new CPicture();

		char filename[256];
		wsprintf(filename,"sys\\%s",fontName);
		m_fontPic->LoadDWQ(filename);


		m_suuji = new CSuuji(m_fontPic,m_fontSizeX,m_fontSizeY,m_keta,m_fontNextX,m_upZeroPrintFlag,TRUE);



		GetInitGameParam(&m_pageMaxPrintFlag,"pageMaxPrintFlag");

		if (m_pageMaxPrintFlag)
		{
			m_upZeroPrintFlagMax = m_upZeroPrintFlag;
			GetInitGameParam(&m_upZeroPrintFlagMax,"maxPageUpZeroPrintFlag");

			m_pageMaxPrintX = m_pagePrintX + m_fontNextX * (m_keta+1);
			m_pageMaxPrintY = m_pagePrintY;

			GetInitGameParam(&m_pageMaxPrintX,"pageMaxPrintX");
			GetInitGameParam(&m_pageMaxPrintY,"pageMaxPrintY");

			int flg = 0;
			GetInitGameParam(&flg,"pageMaxLeftAlign");
			m_suujiMax = new CSuuji(m_fontPic,m_fontSizeX,m_fontSizeY,m_keta,m_fontNextX,m_upZeroPrintFlagMax,TRUE,flg);

			GetInitGameParam(&m_slashPrintFlag,"slashPrintFlag");
			if (m_slashPrintFlag)
			{
				m_slashPrintX = m_pagePrintX + m_fontNextX * m_keta;
				m_slashPrintY = m_pagePrintY;

				GetInitGameParam(&m_slashPrintX,"slashPrintX");
				GetInitGameParam(&m_slashPrintY,"slashPrintY");
			}
		}
	}

}

CPagePrint::~CPagePrint()
{
	End();
}


void CPagePrint::End(void)
{
	ENDDELETECLASS(m_suujiMax);
	ENDDELETECLASS(m_suuji);
	ENDDELETECLASS(m_fontPic);
}



void CPagePrint::Print(int page,int pageMax)
{
	if (m_pagePrintFlag)
	{
		if (m_bg != NULL)
		{
			m_bg->Blt(m_pagePrintX,m_pagePrintY,m_pagePrintX,m_pagePrintY,m_fontNextX*m_keta,m_fontSizeY,FALSE);
		}

		m_suuji->Print(m_pagePrintX,m_pagePrintY,page);
		if (m_pageMaxPrintFlag)
		{
			if (m_bg != NULL)
			{
				m_bg->Blt(m_pageMaxPrintX,m_pageMaxPrintY,m_pageMaxPrintX,m_pageMaxPrintY,m_fontNextX*m_keta,m_fontSizeY,FALSE);
			}

			m_suujiMax->Print(m_pageMaxPrintX,m_pageMaxPrintY,pageMax);
			if (m_slashPrintFlag)
			{
				if (m_bg != NULL)
				{
					m_bg->Blt(m_slashPrintX,m_slashPrintY,m_slashPrintX,m_slashPrintY,m_fontSizeX,m_fontSizeY,FALSE);
				}

				m_suuji->Put(m_slashPrintX,m_slashPrintY,11);
			}
		}
	}
}


void CPagePrint::AppearPrint(int appearCount, int appearCountMax, int appearType, int page, int pageMax)
{
	int dv = appearCountMax;
	if (dv < 1) dv = 1;

	int percent = 100;
	if (appearType & 1)
	{
		percent = (100 * appearCount) / dv;
		if (percent < 0) percent = 0;
		if (percent > 100) percent = 100;
	}


	if (m_pagePrintFlag)
	{
		if (m_bg != NULL)
		{
			m_bg->Blt(m_pagePrintX, m_pagePrintY, m_pagePrintX, m_pagePrintY, m_fontNextX*m_keta, m_fontSizeY, FALSE);
		}

	//	m_suuji->Print(m_pagePrintX, m_pagePrintY, page);
		m_suuji->AppearPrint(appearCount,appearCountMax,appearType,m_pagePrintX, m_pagePrintY, page);


		if (m_pageMaxPrintFlag)
		{
			if (m_bg != NULL)
			{
				m_bg->Blt(m_pageMaxPrintX, m_pageMaxPrintY, m_pageMaxPrintX, m_pageMaxPrintY, m_fontNextX*m_keta, m_fontSizeY, FALSE);
			}

//			m_suujiMax->Print(m_pageMaxPrintX, m_pageMaxPrintY, pageMax);
			m_suujiMax->AppearPrint(appearCount, appearCountMax, appearType, m_pageMaxPrintX, m_pageMaxPrintY, pageMax);

			if (m_slashPrintFlag)
			{
				if (m_bg != NULL)
				{
					m_bg->Blt(m_slashPrintX, m_slashPrintY, m_slashPrintX, m_slashPrintY, m_fontSizeX, m_fontSizeY, FALSE);
				}

//				m_suuji->Put(m_slashPrintX, m_slashPrintY, 11);
				m_suuji->AppearPut(appearCount, appearCountMax, appearType, m_slashPrintX, m_slashPrintY, 11);
			}
		}
	}
}


BOOL CPagePrint::GetInitGameParam(int* lpVar, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpVar = atoi(m_setup->GetName(rNum + 1));

	return TRUE;
}


BOOL CPagePrint::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_setup->GetName(rNum + 1);

	return TRUE;
}
