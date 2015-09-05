//
// CommonPrintItem.cpp
//


#include <windows.h>



#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGeo.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"
#include "..\nnnUtilLib\nnnButtonStatus.h"
#include "..\nnnUtilLib\selectObjectSetup.h"

#include "..\nnnUtilLib\commonButton.h"
#include "..\nnnUtilLib\commonButtonGroup.h"
#include "..\nnnUtilLib\commonRadioButtonGroup.h"

#include "..\nnnUtilLib\commonBackButton.h"
#include "..\nnnUtilLib\commonUpDownButtonGroup.h"
#include "..\nnnUtilLib\commonUpDownBack.h"

#include "..\nnnUtilLib\superButtonPicture.h"
#include "..\nnnUtilLib\nameList.h"

#include "..\nnnUtilLib\mymessage.h"

#include "..\nnnUtilLib\commonAnimeParts.h"


#include "..\nnnUtilLib\printGameDate.h"
#include "..\nnnUtilLib\haveItemData.h"

#include "commonMode.h"
#include "commonSystemParamName.h"


#include "commonSystemSoundName.h"

#include "gameCallBack.h"

#include "commonGeneral.h"


#include "commonPrintItem.h"

#include "commonKeyList.h"


char CCommonPrintItem::m_defaultSuffix[] = "_2";
char CCommonPrintItem::m_defaultNoItemFilename[] = "ta_noitem";
char CCommonPrintItem::m_defaultCursorPicFilename[] = "ta_haveitem_cursor";
char CCommonPrintItem::m_defaultPlateFilename[] = "ta_haveitem_plate";

CCommonPrintItem::CCommonPrintItem(CGameCallBack* lpGame,int extMode) : CCommonGeneral(lpGame)
{
	SetClassNumber(PRINTITEM_MODE);
	LoadSetupFile("PrintItem",256);


	m_haveItem = new CHaveItemData();

	m_message = m_game->GetMyMessage();

	GetBackExecSetup();
	GetAllPrintSetup();
	m_mustAllPrintFlag = TRUE;

	GetInitGameString(&m_filenameBG,"filenameBG");

	m_noItemFilename = m_defaultNoItemFilename;
	GetInitGameString(&m_noItemFilename,"filenameNoItem");

	m_itemTypeKosuu = 1;
	GetInitGameParam(&m_itemTypeKosuu,"itemTypeNumber");

	m_plateFilename = m_defaultPlateFilename;
	GetInitGameString(&m_plateFilename,"filenamePlate");



	m_typeTableNumber = new int[m_itemTypeKosuu];
	m_typeTable = new int*[m_itemTypeKosuu];
	for (int i=0;i<m_itemTypeKosuu;i++)
	{
		int kosuu = 1;
		char name[256];
		sprintf_s(name,256,"itemTypeDataNumber%d",i+1);
		GetInitGameParam(&kosuu,name);
		m_typeTableNumber[i] = kosuu;
		m_typeTable[i] = new int[kosuu];

		for (int k=0;k<kosuu;k++)
		{
			int data = i + 1;
			sprintf_s(name,256,"itemTypeData%d_%d",i+1,k+1);
			GetInitGameParam(&data,name);
			m_typeTable[i][k] = data;
		}
	}

	m_radio = NULL;
	if (m_itemTypeKosuu > 1)
	{
		m_radio = new CCommonRadioButtonGroup(m_setup,"haveitemType",NULL,m_itemTypeKosuu);
		for (int i=0;i<m_itemTypeKosuu;i++)
		{
			CPicture* lpPic = CSuperButtonPicture::GetPicture(3+i);
			m_radio->SetPicture(lpPic,i,-1);
		}
	}

	m_suffix = m_defaultSuffix;
	GetInitGameString(&m_suffix,"suffix");


	m_lowCursor = 0;
	GetInitGameParam(&m_lowCursor,"lowCursor");

	m_itemBlockX = 4;
	m_itemBlockY = 3;
	GetInitGameParam(&m_itemBlockX,"itemBlockX");
	GetInitGameParam(&m_itemBlockY,"itemBlockY");
	m_itemPerPage = m_itemBlockX*m_itemBlockY; 

	m_itemPrintX = 100;
	m_itemPrintY = 100;
	GetInitGameParam(&m_itemPrintX,"itemPrintX");
	GetInitGameParam(&m_itemPrintY,"itemPrintY");
	m_itemSizeX = 80;
	m_itemSizeY = 60;
	GetInitGameParam(&m_itemSizeX,"itemSizeX");
	GetInitGameParam(&m_itemSizeY,"itemSizeY");
	m_itemPrintNextX = m_itemSizeX;
	m_itemPrintNextY = m_itemSizeY;
	GetInitGameParam(&m_itemPrintNextX,"itemPrintNextX");
	GetInitGameParam(&m_itemPrintNextY,"itemPrintNextY");



	m_itemNamePrintFlag = 0;
	GetInitGameParam(&m_itemNamePrintFlag,"itemNamePrintFlag");

	m_itemNameFontSize = 24;
	GetInitGameParam(&m_itemNameFontSize,"itemNameFontSize");
	m_itemNamePrintX = 0;
	m_itemNamePrintY = 0;
	GetInitGameParam(&m_itemNamePrintX,"itemNamePrintX");
	GetInitGameParam(&m_itemNamePrintY,"itemNamePrintY");
	m_itemNameFontColorR = 255;
	m_itemNameFontColorG = 255;
	m_itemNameFontColorB = 255;
	GetInitGameParam(&m_itemNameFontColorR,"itemNameFontColorR");
	GetInitGameParam(&m_itemNameFontColorG,"itemNameFontColorG");
	GetInitGameParam(&m_itemNameFontColorB,"itemNameFontColorB");


	m_platePrintX = 100;
	m_platePrintY = 150;
	m_plateItemPrintX = 50;
	m_plateItemPrintY = 50;
	m_descPrintX = 300;
	m_descPrintY = 30;
	m_descPrintNextX = 0;
	m_descPrintNextY = 30;
	m_descFontSize = 24;
	m_descColorR = 255;
	m_descColorG = 255;
	m_descColorB = 255;
	m_plateItemPrintFlag = 1;

	GetInitGameParam(&m_platePrintX,"platePrintX");
	GetInitGameParam(&m_platePrintY,"platePrintY");
	GetInitGameParam(&m_plateItemPrintX,"plateItemPrintX");
	GetInitGameParam(&m_plateItemPrintY,"plateItemPrintY");
	GetInitGameParam(&m_descPrintX,"descPrintX");
	GetInitGameParam(&m_descPrintY,"descPrintY");
	GetInitGameParam(&m_descPrintNextX,"descPrintNextX");
	GetInitGameParam(&m_descPrintNextY,"descPrintNextY");
	GetInitGameParam(&m_descFontSize,"descFontSize");
	GetInitGameParam(&m_descColorR,"descColorR");
	GetInitGameParam(&m_descColorG,"descColorG");
	GetInitGameParam(&m_descColorB,"descColorB");
	GetInitGameParam(&m_plateItemPrintFlag,"plateItemPrintFlag");




	m_itemPic = new CPicture*[m_itemPerPage];
	for (int i=0;i<m_itemPerPage;i++)
	{
		m_itemPic[i] = new CPicture();
	}


	m_allItemNumber = m_haveItem->GetListKosuu();
	m_itemTable = new int[m_allItemNumber*2+1];


	for (int i=0;i<m_allItemNumber;i++)
	{
		LPSTR varName = m_haveItem->GetVarName(i);
		int varNumber = m_game->GetVarNumber(varName);
		m_haveItem->SetVarNumber(i,varNumber);
	}


	m_cursorPic = NULL;
	m_useCursorPic = 0;
	GetInitGameParam(&m_useCursorPic,"useCursorPic");
	if (m_useCursorPic)
	{
		LPSTR cursorFilename = m_defaultCursorPicFilename;
		GetInitGameString(&cursorFilename,"filenameCursor");
		m_cursorPic = new CPicture();
		char fname[256];
		sprintf_s(fname,256,"sys\\%s",cursorFilename);
		m_cursorPic->LoadDWQ(fname);
	}

	m_cursorColorR = 255;
	m_cursorColorG = 255;
	m_cursorColorB = 255;
	m_cursorColorA = 50;
	GetInitGameParam(&m_cursorColorR,"cursorColorR");
	GetInitGameParam(&m_cursorColorG,"cursorColorG");
	GetInitGameParam(&m_cursorColorB,"cursorColorB");
	GetInitGameParam(&m_cursorColorA,"cursorColorA");





	m_typeNumber = 0;

	CreateBackButton();
	CreateUpDownButton();
	CreateUpDownBack();


	GetDisableQuickButtonSetup();
	GetBGMSetup();
	GetFadeInOutSetup();
	GetEnterExitVoiceFileName();
	GetAddLayerSetup();
	GetAnimeLayerSetup();
}



CCommonPrintItem::~CCommonPrintItem()
{
	End();
}

void CCommonPrintItem::End(void)
{
	ENDDELETECLASS(m_cursorPic);
	if (m_typeTable != NULL)
	{
		for (int i=0;i<m_itemTypeKosuu;i++)
		{
			DELETEARRAY(m_typeTable[i]);
		}
		DELETEARRAY(m_typeTable);
	}
	DELETEARRAY(m_typeTableNumber);

	DELETEARRAY(m_itemTable);

	if (m_itemPic != NULL)
	{
		for (int i=0;i<m_itemPerPage;i++)
		{
			ENDDELETECLASS(m_itemPic[i]);
		}
		DELETEARRAY(m_itemPic);
	}

	ENDDELETECLASS(m_radio);
	ENDDELETECLASS(m_haveItem);
}


int CCommonPrintItem::Init(void)
{
	LoadBackBG();

	m_typeNumber = 0;
	m_selectedItemNumber = -1;


	CreateTable();
	SetupButton();

	char filename[256];
	sprintf_s(filename,256,"sys\\%s",m_plateFilename);
	m_commonParts->LoadDWQ(filename);


	m_onNumber = -1;

	return -1;
}


int CCommonPrintItem::Calcu(void)
{
	int udb = m_updownBack->Calcu(m_inputStatus);

	if (udb != NNNBUTTON_NOTHING)
	{
		int nm = ProcessUpDownBack(udb);
		if (nm >= 0)
		{
			if (nm == 0)
			{
				if (m_selectedItemNumber != -1)
				{
					m_updownBack->Init();
					m_updownBack->SetPage(m_page);
					m_selectedItemNumber = -1;
					return -1;
				}

//				return ReturnFadeOut(OMAKE_MODE);
				m_game->FuqueAllEffectYoyaku();
				return ReturnFadeOut(m_backMode);
			}
			else
			{
				m_selectedItemNumber = -1;

				if (nm == 1)
				{
					if (m_page>0)
					{
						m_page--;
					}
				}
				else
				{
					if (m_page<m_pageMax-1)
					{
						m_page++;
					}
				}


				m_updownBack->Init();
				m_updownBack->SetPage(m_page);
				LoadItemPic();
			}
		}
	}


	int onNumber = GetOnNumber(m_mouseStatus->GetZahyo());
	if (m_selectedItemNumber == -1)
	{
		m_onNumber = -1;
		if (m_itemTable[(onNumber + m_page * m_itemPerPage)*2+1] > 0)
		{
			m_onNumber = onNumber;
		}
	}


	if (m_mouseStatus->CheckClick(0))
	{
		if (m_onNumber != -1)
		{
			if (m_itemTable[(m_onNumber + m_page * m_itemPerPage)*2+1] > 0)
			{
				m_selectedItemNumber = m_onNumber + m_page * m_itemPerPage;
			}
		}
	}


	if (m_radio != NULL)
	{
		int rt = m_radio->Calcu(m_inputStatus);
		if (rt != -1)
		{
			int nm = ProcessButtonGroup(rt);
			if ((nm >= 0) && (nm < m_itemTypeKosuu))
			{
				m_selectedItemNumber = -1;

				m_typeNumber = nm;

				CreateTable();

				m_updownBack->Init();
				m_updownBack->SetPageMax(m_pageMax);
				m_updownBack->SetPage(m_page);

				m_radio->SetRadio(nm);
				ReloadButtonPic();
				m_radio->Init(nm);

				return -1;
			}
		}
	}


	return -1;
}

int CCommonPrintItem::Print(void)
{
	CAreaControl::SetNextAllPrint();

	PrintBackScriptOrBG();



	if (m_radio != NULL)
	{
		m_radio->Print();
	}

	if (m_updownBack != NULL)
	{
		m_updownBack->Print(TRUE);
	}





	int st = m_itemPerPage * m_page;
	int ed = st + m_itemPerPage;
	if (ed >= m_itemListNumber)
	{
		ed = m_itemListNumber;
	}

	//low cursor

	if (m_lowCursor)
	{
		if (m_onNumber != -1)
		{
			PutCursor(m_onNumber);
		}
	}


	int lp = ed - st;
	for (int i=0;i<lp;i++)
	{
		POINT pt = GetItemZahyo(i);
		m_itemPic[i]->Put(pt.x,pt.y,TRUE);
		if (m_itemNamePrintFlag)
		{
			int item = m_itemTable[(st+i)*2];
			int md = m_itemTable[(st+i)*2+1];
			LPSTR itemName = m_haveItem->GetName(item,md);
			m_message->PrintMessage(pt.x+m_itemNamePrintX,pt.y+m_itemNamePrintY,itemName,m_itemNameFontSize,m_itemNameFontColorR,m_itemNameFontColorG,m_itemNameFontColorB);
		}
	}



	if (!m_lowCursor)
	{
		if (m_onNumber != -1)
		{
			PutCursor(m_onNumber);
		}
	}


	if (m_selectedItemNumber != -1)
	{
		//plate
		m_commonParts->Put(m_platePrintX,m_platePrintY,TRUE);
		if (m_plateItemPrintFlag)
		{
			int k = m_selectedItemNumber % m_itemPerPage;
			m_itemPic[k]->Put(m_platePrintX+m_plateItemPrintX,m_platePrintY+m_plateItemPrintY,TRUE);
		}

		int item = m_itemTable[m_selectedItemNumber*2];
		int md = m_itemTable[m_selectedItemNumber*2+1];
		int descNumber = m_haveItem->GetDescNumber(item,md);

		for (int i=0;i<descNumber;i++)
		{
			LPSTR desc = m_haveItem->GetDesc(item,i,md);
			if (desc != NULL)
			{
				int x = m_platePrintX + m_descPrintX + i * m_descPrintNextX;
				int y = m_platePrintY + m_descPrintY + i * m_descPrintNextY;
				m_message->PrintMessage(x,y,desc,m_descFontSize,m_descColorR,m_descColorG,m_descColorB);
			}
		}
	}


	if (m_selectedItemNumber != -1)
	{
	}


//	m_game->PrintOptionButtonYoyaku();

	return -1;
}

void CCommonPrintItem::PutCursor(int n)
{
	POINT pt = GetItemZahyo(n);
	if (m_useCursorPic)
	{
		m_cursorPic->Put(pt.x,pt.y,TRUE);
	}
	else
	{
		CAllGeo::TransBoxFill(pt.x,pt.y,m_itemSizeX,m_itemSizeY,m_cursorColorR,m_cursorColorG,m_cursorColorB,m_cursorColorA);
	}
}


POINT CCommonPrintItem::GetItemZahyo(int nx,int ny)
{
	POINT pt;
	pt.x = m_itemPrintX + m_itemPrintNextX * nx;
	pt.y = m_itemPrintY + m_itemPrintNextY * ny;
	return pt;
}

POINT CCommonPrintItem::GetItemZahyo(int n)
{
	int nx = n % m_itemBlockX;
	int ny = (n / m_itemBlockX) % m_itemBlockY;
	return GetItemZahyo(nx,ny);
}



void CCommonPrintItem::CreateTable(void)
{
	m_itemListNumber = 0;

	for (int i=0;i<m_allItemNumber;i++)
	{
		int type = m_haveItem->GetType(i);
		BOOL f = FALSE;
		int checkTypeNumber = m_typeTableNumber[m_typeNumber];
		for (int k=0;k<checkTypeNumber;k++)
		{
			if (type == m_typeTable[m_typeNumber][k])
			{
				f = TRUE;
				break;
			}
		}

		if (f)
		{
			int varNumber = m_haveItem->GetVarNumber(i);
			int varData = 0;
			if (varNumber != -1)
			{
				varData = m_game->GetVarData(varNumber);
			}
			m_itemTable[m_itemListNumber*2] = i;
			m_itemTable[m_itemListNumber*2+1] = varData;
			m_itemListNumber++;
		}
	}

	m_page = 0;
	m_pageMax = (m_itemListNumber+m_itemPerPage-1) / m_itemPerPage;
	if (m_pageMax == 0) m_pageMax = 1;



}

void CCommonPrintItem::SetupButton(void)
{
	m_radio->SetRadio(m_typeNumber);
	ReloadButtonPic();
	m_radio->Init(m_typeNumber);

	m_updownBack->Init();
	m_updownBack->SetPageMax(m_pageMax);
	m_updownBack->SetPage(m_page);
}


int CCommonPrintItem::GetOnNumber(POINT pt)
{
	//page
	int mx = m_itemListNumber -  m_page * m_itemPerPage;
	if (mx>m_itemPerPage) mx = m_itemPerPage;

	for (int i=0;i<mx;i++)
	{
		POINT pt2 = GetItemZahyo(i);
		int dx = pt.x - pt2.x;
		int dy = pt.y - pt2.y;

		if ((dx>=0) && (dx<m_itemSizeX) && (dy>=0) && (dy<m_itemSizeY))
		{
			return i;
		}


	}

	return -1;
}


void CCommonPrintItem::ReloadButtonPic(void)
{
	if (m_radio != NULL)
	{
		int sel = m_radio->GetRadio();

		for (int i=0;i<m_itemTypeKosuu;i++)
		{
			int st = 0;
			if (i == sel) st = 1;

			CPicture* lpPic = m_radio->GetPicture(i,st);
			LPSTR name = m_radio->GetFileName(i,st);
			char filename[256];
			wsprintf(filename,"sys\\%s",name);
			lpPic->LoadDWQ(filename);
		}

	}
	LoadItemPic();
	LoadUpDownButtonPic();
	LoadBackButtonPic();



}





void CCommonPrintItem::FinalExitRoutine(void)
{

//	if (m_exitModeFlag)
//	{
//		m_game->SetYoyaku();
//	}

}

int CCommonPrintItem::EndMode(void)
{
	return -1;

	/*
	if (m_exitModeFlag)
	{
		m_game->SetVarData(m_selectPlaceResultVarNumber,m_selectedNumber + 1);


		m_game->SetYoyaku();
	}
	*/

}




void CCommonPrintItem::CreateStartScreen(void)
{
	Print();
}



void CCommonPrintItem::LoadItemPic(void)
{
	int mx = m_itemListNumber -  m_page * m_itemPerPage;
	if (mx>m_itemPerPage) mx = m_itemPerPage;

	for (int i=0;i<mx;i++)
	{
		int n = m_page * m_itemPerPage + i;
		int k = m_itemTable[n*2];
		int st = m_itemTable[n*2+1];
		//int serial = m_haveItem->GetSerial(k);
		LPSTR filenamebase = m_haveItem->GetFilename(k);
		char filename[256];
		if (st < 1)
		{
			sprintf_s(filename,256,"sys\\%s",m_noItemFilename);
		}
		else if (st == 1)
		{
			sprintf_s(filename,256,"sys\\%s",filenamebase);
		}
		else
		{
			sprintf_s(filename,256,"sys\\%s%s",filenamebase,m_suffix);
		}

		m_itemPic[i]->LoadDWQ(filename);
	}
}




