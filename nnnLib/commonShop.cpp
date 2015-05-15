//
// CommonShop.cpp
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

#include "..\nnnUtilLib\suuji.h"

#include "..\nnnUtilLib\printGameDate.h"
#include "..\nnnUtilLib\shopItemData.h"

#include "commonMode.h"
#include "commonSystemParamName.h"


#include "commonSystemSoundName.h"

#include "gameCallBack.h"

#include "commonGeneral.h"


#include "commonShop.h"

#include "commonKeyList.h"


//char CCommonShop::m_defaultSuffix[] = "_2";
char CCommonShop::m_defaultNoItemFilename[] = "ta_noshopitem";
char CCommonShop::m_defaultCursorPicFilename[] = "ta_shopitem_cursor";
char CCommonShop::m_defaultPlateFilename[] = "ta_shopitem_plate";
char CCommonShop::m_defaultNotAppearName[] = "？？？";
char CCommonShop::m_defaultPointVarName[] = "ゲーム内ポイント";


CCommonShop::CCommonShop(CGameCallBack* lpGame,int extMode) : CCommonGeneral(lpGame)
{
	SetClassNumber(SHOP_MODE);
	LoadSetupFile("shop",256);


	m_shopItem = new CShopItemData();

	m_message = m_game->GetMyMessage();

	GetBackExecSetup();
	GetAllPrintSetup();
	m_mustAllPrintFlag = TRUE;

	GetInitGameString(&m_filenameBG,"filenameBG");

	int bit = 1;

	for (int i=0;i<32;i++)
	{
		m_bitPattern[i] = bit;
		bit <<= 1;
	}

	m_canSelectLimit = 0;
	m_canSelectNoPoint = 0;
	GetInitGameParam(&m_canSelectLimit,"canSelectLimit");
	GetInitGameParam(&m_canSelectNoPoint,"canSelectNoPoint");




	m_noItemFilename = m_defaultNoItemFilename;
	GetInitGameString(&m_noItemFilename,"filenameNoItem");

	m_itemTypeKosuu = 1;
	GetInitGameParam(&m_itemTypeKosuu,"itemTypeNumber");

	m_plateFilename = m_defaultPlateFilename;
	GetInitGameString(&m_plateFilename,"filenamePlate");

	m_notAppearName = m_defaultNoItemFilename;
	GetInitGameString(&m_notAppearName,"notAppearName");

	LPSTR pointVarNumber = m_defaultPointVarName;
	GetInitGameString(&pointVarNumber,"pointVarName");
	m_pointVarNumber = m_game->GetVarNumber(pointVarNumber);


	m_newMarkPic = NULL;
	m_soldOutPic = NULL;
	m_printNewMarkFlag = 0;
	m_printSoldOutFlag = 0;
	m_newMarkPrintX = 0;
	m_newMarkPrintY = 0;
	m_soldoutPrintX = 0;
	m_soldoutPrintY = 0;
	GetInitGameParam(&m_printNewMarkFlag,"printNewMarkFlag");
	GetInitGameParam(&m_printSoldOutFlag,"printSoldOutFlag");
	if (m_printNewMarkFlag)
	{
		GetInitGameParam(&m_newMarkPrintX,"newMarkPrintX");
		GetInitGameParam(&m_newMarkPrintY,"newMarkPrintY");
		LPSTR picFilename = NULL;
		if (GetInitGameString(&picFilename,"filenameNewMark"))
		{
			m_newMarkPic = new CPicture();
			char filename[256];
			sprintf_s(filename,256,"sys\\%s",picFilename);
			m_newMarkPic->LoadDWQ(filename);
		}
	}
	if (m_printSoldOutFlag)
	{
		GetInitGameParam(&m_soldoutPrintX,"soldoutPrintX");
		GetInitGameParam(&m_soldoutPrintY,"soldoutPrintY");
		LPSTR picFilename = NULL;
		if (GetInitGameString(&picFilename,"filenameSoldOut"))
		{
			m_soldOutPic = new CPicture();
			char filename[256];
			sprintf_s(filename,256,"sys\\%s",picFilename);
			m_soldOutPic->LoadDWQ(filename);
		}
	}



//	m_newMarkPic = new CPicture();
//	m_soldOutPic = new CPicture();
	m_gamePointSuuji = new CSuuji(m_setup,"gamePoint",TRUE);
	m_pricePointSuuji = new CSuuji(m_setup,"pricePoint",TRUE);
	m_gamePointPrintX = 400;
	m_gamePointPrintY = 550;
	m_pricePointPrintX = 50;
	m_pricePointPrintY = 0;
	GetInitGameParam(&m_gamePointPrintX,"gamePointPrintX");
	GetInitGameParam(&m_gamePointPrintY,"gamePointPrintY");
	GetInitGameParam(&m_pricePointPrintX,"pricePointPrintX");
	GetInitGameParam(&m_pricePointPrintY,"pricePointPrintY");


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
		m_radio = new CCommonRadioButtonGroup(m_setup,"shopitemType",NULL,m_itemTypeKosuu);
		for (int i=0;i<m_itemTypeKosuu;i++)
		{
			CPicture* lpPic = CSuperButtonPicture::GetPicture(3+i);
			m_radio->SetPicture(lpPic,i,-1);
		}
	}

	m_okButton = new CCommonButton(m_setup,"ok");
	m_cancelButton = new CCommonButton(m_setup,"cancel");


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


	m_allItemNumber = m_shopItem->GetListKosuu();
	m_itemTable = new int[m_allItemNumber*4+1];
	m_appearFlag = new int[m_allItemNumber+1];
	m_appearControlVarNumber = new int[(m_allItemNumber+31) / 32 + 1];
	for (int i=0;i<(m_allItemNumber+31) / 32;i++)
	{
		m_appearControlVarNumber[i] = -1;
		char name[256];
		sprintf_s(name,"appearVar%d",i+1);
		LPSTR varName = NULL;
		if (GetInitGameString(&varName,name))
		{
			int varNumber = m_game->GetVarNumber(varName);
			if (varNumber != -1)
			{
				m_appearControlVarNumber[i] = varNumber;
			}
		}
	}

	for (int i=0;i<m_allItemNumber;i++)
	{
		LPSTR appearVarName = m_shopItem->GetAppearVarName(i);
		if (appearVarName != NULL)
		{
			if ((*appearVarName) != '@')
			{
				int appearVarNumber = m_game->GetVarNumber(appearVarName);
				m_shopItem->SetAppearVarNumber(i,appearVarNumber);
			}
		}

		LPSTR targetVarName = m_shopItem->GetTargetVarName(i);
		if (targetVarName != NULL)
		{
			if ((*targetVarName) != '@')
			{
				int targetVarNumber = m_game->GetVarNumber(targetVarName);
				m_shopItem->SetTargetVarNumber(i,targetVarNumber);
			}
		}

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



CCommonShop::~CCommonShop()
{
	End();
}

void CCommonShop::End(void)
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

	ENDDELETECLASS(m_soldOutPic);
	ENDDELETECLASS(m_newMarkPic);
	ENDDELETECLASS(m_gamePointSuuji);
	ENDDELETECLASS(m_pricePointSuuji);

	DELETEARRAY(m_appearControlVarNumber);
	DELETEARRAY(m_appearFlag);
	DELETEARRAY(m_itemTable);



	if (m_itemPic != NULL)
	{
		for (int i=0;i<m_itemPerPage;i++)
		{
			ENDDELETECLASS(m_itemPic[i]);
		}
		DELETEARRAY(m_itemPic);
	}

	ENDDELETECLASS(m_cancelButton);
	ENDDELETECLASS(m_okButton);
	ENDDELETECLASS(m_radio);
	ENDDELETECLASS(m_shopItem);
}


int CCommonShop::Init(void)
{
	LoadBackBG();

	m_typeNumber = 0;
	m_selectedItemNumber = -1;


	for (int i=0;i<m_allItemNumber;i++)
	{
		m_appearFlag[i] = CheckAppearFlag(i);
	}

	CreateTable();
	SetupButton();
	GetGamePoint();

	char filename[256];
	sprintf_s(filename,256,"sys\\%s",m_plateFilename);
	m_commonParts->LoadDWQ(filename);


	m_onNumber = -1;

	return -1;
}


int CCommonShop::Calcu(void)
{
	int udb = m_updownBack->Calcu(m_inputStatus);
	if (m_selectedItemNumber == -1)
	{
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
				}
			}
		}
	}

	int ok = NNNBUTTON_NOTHING;
	int cancel = NNNBUTTON_NOTHING;

	if (m_selectedItemNumber != -1)
	{
		ok = m_okButton->Calcu(m_inputStatus);
		cancel = m_cancelButton->Calcu(m_inputStatus);

		if (cancel != NNNBUTTON_NOTHING)
		{
			int nm = ProcessCommonButton(cancel);
			if (nm == 0)
			{
				m_selectedItemNumber = -1;

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

		if (ok != NNNBUTTON_NOTHING)
		{
			int nm = ProcessCommonButton(ok);
			if (nm == 0)
			{
				BuyItem();

				m_selectedItemNumber = -1;

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


	int onNumber = GetOnNumber(m_mouseStatus->GetZahyo());
	if (m_selectedItemNumber == -1)
	{
		m_onNumber = -1;
		if (m_itemTable[(onNumber + m_page * m_itemPerPage)*4+3] > 0)
		{

			m_onNumber = onNumber;
		}
	}


	if (m_mouseStatus->CheckClick(0))
	{
		if (m_onNumber != -1)
		{
			if (m_itemTable[(m_onNumber + m_page * m_itemPerPage)*4+3] > 0)
			{
				m_selectedItemNumber = m_onNumber + m_page * m_itemPerPage;
				SetAppearFlag(m_selectedItemNumber);
				SetOkCancelStatus();
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

int CCommonShop::Print(void)
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
			int item = m_itemTable[(st+i)*4];
			int md = m_itemTable[(st+i)*4+1];
			LPSTR itemName = m_shopItem->GetName(item,md);
			m_message->PrintMessage(pt.x+m_itemNamePrintX,pt.y+m_itemNamePrintY,itemName,m_itemNameFontSize,m_itemNameFontColorR,m_itemNameFontColorG,m_itemNameFontColorB);


			//price
			int price = m_shopItem->GetPrice(item);
			m_pricePointSuuji->Print(pt.x+m_pricePointPrintX,pt.y+m_pricePointPrintY,price);


			//new
			if ((m_newMarkPic != NULL) && (m_printNewMarkFlag))
			{
				if (m_appearFlag[item] == 0)
				{
					m_newMarkPic->Put(pt.x+m_newMarkPrintX,pt.y+m_newMarkPrintY,TRUE);
				}
			}

			//soldout
			if ((m_soldOutPic != NULL) && (m_printSoldOutFlag))
			{
				if (m_soldOutFlag[i])
				{
					m_soldOutPic->Put(pt.x+m_soldoutPrintX,pt.y+m_soldoutPrintY,TRUE);
				}
			}
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

		int item = m_itemTable[m_selectedItemNumber*4];
		int md = m_itemTable[m_selectedItemNumber*4+1];
		int descNumber = m_shopItem->GetDescNumber(item,md);

		for (int i=0;i<descNumber;i++)
		{
			LPSTR desc = m_shopItem->GetDesc(item,i,md);
			if (desc != NULL)
			{
				int x = m_platePrintX + m_descPrintX + i * m_descPrintNextX;
				int y = m_platePrintY + m_descPrintY + i * m_descPrintNextY;
				m_message->PrintMessage(x,y,desc,m_descFontSize,m_descColorR,m_descColorG,m_descColorB);
			}
		}

		m_okButton->Print();
		m_cancelButton->Print();
	}

	m_gamePointSuuji->Print(m_gamePointPrintX,m_gamePointPrintY,m_gamePoint);


//	m_game->PrintOptionButtonYoyaku();

	return -1;
}


void CCommonShop::BuyItem(void)
{
	int item = m_itemTable[m_selectedItemNumber*4+0];
	int price = m_shopItem->GetPrice(item);
	int limit = m_shopItem->GetLimit(item);
	int targetVar = m_shopItem->GetTargetVarNumber(item);


	int ok = 1;
	if (m_gamePoint < price)
	{
		ok = 0;
	}

	if (limit > 0)
	{
		if (targetVar != -1)
		{
			int d = m_game->GetVarData(targetVar);
			if (d >= limit)
			{
				ok = 0;
			}
		}
	}

	if (ok == 1)
	{
		int d = m_game->GetVarData(targetVar);
		d++;
		m_game->SetVarData(targetVar,d);
		UseGamePoint(price);
	}
}

void CCommonShop::SetOkCancelStatus(void)
{
	int item = m_itemTable[m_selectedItemNumber*4+0];
	int price = m_shopItem->GetPrice(item);
	int limit = m_shopItem->GetLimit(item);
	int targetVar = m_shopItem->GetTargetVarNumber(item);


	int ok = 1;
	if (m_gamePoint < price)
	{
		ok = 0;
	}

	if (limit > 0)
	{
		if (targetVar != -1)
		{
			int d = m_game->GetVarData(targetVar);
			if (d >= limit)
			{
				ok = 0;
			}
		}
	}

	if (ok==0)
	{
		m_okButton->SetEnable(FALSE);
	}
	else
	{
		m_okButton->SetEnable(TRUE);
	}

	m_okButton->Init();
	m_cancelButton->Init();

}


void CCommonShop::PutCursor(int n)
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


POINT CCommonShop::GetItemZahyo(int nx,int ny)
{
	POINT pt;
	pt.x = m_itemPrintX + m_itemPrintNextX * nx;
	pt.y = m_itemPrintY + m_itemPrintNextY * ny;
	return pt;
}

POINT CCommonShop::GetItemZahyo(int n)
{
	int nx = n % m_itemBlockX;
	int ny = (n / m_itemBlockX) % m_itemBlockY;
	return GetItemZahyo(nx,ny);
}



void CCommonShop::CreateTable(void)
{
	m_itemListNumber = 0;

	for (int i=0;i<m_allItemNumber;i++)
	{
		m_soldOutFlag[m_itemListNumber] = 0;

		int type = m_shopItem->GetType(i);
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
//			SetAppearFlag(i);

			m_itemTable[m_itemListNumber*4] = i;

			int varNumber = m_shopItem->GetAppearVarNumber(i);
			int varData = 0;
			if (varNumber != -1)
			{
				varData = m_game->GetVarData(varNumber);
			}
			m_itemTable[m_itemListNumber*4+1] = varData;

			varNumber = m_shopItem->GetTargetVarNumber(i);
			varData = 0;
			if (varNumber != -1)
			{
				varData = m_game->GetVarData(varNumber);
			}
			m_itemTable[m_itemListNumber*4+2] = varData;


			int selok = 1;
			if (m_canSelectLimit == 0)
			{
				//check limit
				int limitVarNumber = m_shopItem->GetTargetVarNumber(i);
				if (limitVarNumber != -1)
				{
					int limit = m_shopItem->GetLimit(i);
					if (limit > 0)
					{
						if (m_game->GetVarData(limitVarNumber) >= limit)
						{
							selok = 0;
							m_soldOutFlag[m_itemListNumber] = 1;
						}
					}
				}
			}

			if (m_canSelectNoPoint == 0)
			{
				//check point
				int price = m_shopItem->GetPrice(i);
				if (m_gamePoint < price)
				{
					selok = 0;
				}
			}


			m_itemTable[m_itemListNumber*4+3] = selok;


			m_itemListNumber++;
		}
	}

	m_page = 0;
	m_pageMax = (m_itemListNumber+m_itemPerPage-1) / m_itemPerPage;
	if (m_pageMax == 0) m_pageMax = 1;



}

void CCommonShop::SetupButton(void)
{
	m_radio->SetRadio(m_typeNumber);
	ReloadButtonPic();
	m_radio->Init(m_typeNumber);

	m_updownBack->Init();
	m_updownBack->SetPageMax(m_pageMax);
	m_updownBack->SetPage(m_page);
	
	//ok cancel init picload

}


int CCommonShop::GetOnNumber(POINT pt)
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


void CCommonShop::ReloadButtonPic(void)
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





void CCommonShop::FinalExitRoutine(void)
{

//	if (m_exitModeFlag)
//	{
//		m_game->SetYoyaku();
//	}

}

int CCommonShop::EndMode(void)
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




void CCommonShop::CreateStartScreen(void)
{
	Print();
}



void CCommonShop::LoadItemPic(void)
{
	int mx = m_itemListNumber -  m_page * m_itemPerPage;
	if (mx>m_itemPerPage) mx = m_itemPerPage;

	for (int i=0;i<mx;i++)
	{
		int n = m_page * m_itemPerPage + i;
		int k = m_itemTable[n*3];
		int st = m_itemTable[n*3+1];
		//int serial = m_haveItem->GetSerial(k);
		LPSTR filenamebase = m_shopItem->GetFilename(k);
		char filename[256];
		if (st < 1)
		{
			sprintf_s(filename,256,"sys\\%s",m_noItemFilename);
		}
		else if (st >= 1)
		{
			sprintf_s(filename,256,"sys\\%s",filenamebase);
		}
//		else
//		{
//			sprintf_s(filename,256,"sys\\%s%s",filenamebase,m_suffix);
//		}

		m_itemPic[i]->LoadDWQ(filename);
	}
}

void CCommonShop::GetGamePoint(void)
{
	m_gamePoint = 0;
	if (m_pointVarNumber != -1)
	{
		m_gamePoint = m_game->GetVarData(m_pointVarNumber);
	}
}

void CCommonShop::UseGamePoint(int p)
{
	if (m_pointVarNumber != -1)
	{
		GetGamePoint();
		m_gamePoint -= p;
		if (m_gamePoint < 0) m_gamePoint = 0;
		m_game->SetVarData(m_pointVarNumber,m_gamePoint);
	}
}

BOOL CCommonShop::CheckAppearFlag(int n)
{
	int bit = m_bitPattern[n & 31];
	int v = n / 32;
	int var = m_appearControlVarNumber[v];
	if (var != -1)
	{
		int d = m_game->GetVarData(var);
		if ((d & bit) != 0)
		{
			return TRUE;
		}
		return FALSE;

	}

	return TRUE;
}

void CCommonShop::SetAppearFlag(int n)
{
	int bit = m_bitPattern[n & 31];
	int v = n / 32;
	int var = m_appearControlVarNumber[v];
	if (var != -1)
	{
		int d = m_game->GetVarData(var);
		d |= bit;
		m_game->SetVarData(var,d);
	}

}


