//
// CommonSelectObject.cpp
//


#include <windows.h>



#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGeo.h"

#include "..\nnnUtilLib\Myfont.h"


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

#include "commonMode.h"
#include "commonSystemParamName.h"


#include "commonSystemSoundName.h"

#include "gameCallBack.h"

#include "commonGeneral.h"


#include "commonPrintTerm.h"

#include "commonKeyList.h"

int CCommonPrintTerm::m_sortByType = 0;
int CCommonPrintTerm::m_sortByParam = 0;
int CCommonPrintTerm::m_sortByTitle = 1;


CCommonPrintTerm::CCommonPrintTerm(CGameCallBack* lpGame,int extMode) : CCommonGeneral(lpGame)
{
	SetClassNumber(PRINTTERM_MODE);
	LoadSetupFile("PrintTerm",256);


	m_message = m_game->GetMyMessage();

	GetBackExecSetup();
	GetAllPrintSetup();
	m_mustAllPrintFlag = TRUE;

	GetInitGameString(&m_filenameBG,"filenameBG");


	m_termTypeKosuu = 1;
	GetInitGameParam(&m_termTypeKosuu,"termTypeNumber");


	m_typeTableNumber = new int[m_termTypeKosuu];
	m_typeTable = new int*[m_termTypeKosuu];
	for (int i=0;i<m_termTypeKosuu;i++)
	{
		int kosuu = 1;
		char name[256];
		sprintf_s(name,256,"termTypeDataNumber%d",i+1);
		GetInitGameParam(&kosuu,name);
		m_typeTableNumber[i] = kosuu;
		m_typeTable[i] = new int[kosuu];

		for (int k=0;k<kosuu;k++)
		{
			int data = i + 1;
			sprintf_s(name,256,"termTypeData%d_%d",i+1,k+1);
			GetInitGameParam(&data,name);
			m_typeTable[i][k] = data;
		}
	}

	m_listPrintX = 100;
	m_listPrintY = 200;
	m_listNextX = 30;
	m_listNextY = 50;
	m_listSizeX = 300;
	m_listSizeY = 40;


	m_termList = new CNameList();
	m_termList->LoadFile("spt\\termList.xtx");
	m_allTermNumber = m_termList->GetNameKosuu() / 4;

	m_termData = new TERMDATA[m_allTermNumber+1];


	m_radio = NULL;
	if (m_termTypeKosuu > 1)
	{
		m_radio = new CCommonRadioButtonGroup(m_setup,"termType",NULL,m_termTypeKosuu);
		for (int i=0;i<m_termTypeKosuu;i++)
		{
			CPicture* lpPic = CSuperButtonPicture::GetPicture(3+i);
			m_radio->SetPicture(lpPic,i,-1);
		}
	}

	m_termText = NULL;
	m_termTextNumber = -1;

	m_typeNumber = 0;

	CreateBackButton();
	CreateUpDownButton();
	CreateUpDownBack();


	m_typeNumber;
	m_page = 0;
	m_pageMax = 1;
	m_termPerPage = 10;
	GetInitGameParam(&m_termPerPage,"termPerPage");

	m_newMark = NULL;
	int newMark = 0;
	m_newMarkPrintX = 0;
	m_newMarkPrintY = 0;

	GetInitGameParam(&newMark,"createNewMark");
	if (newMark)
	{
		m_newMark = new CCommonAnimeParts("newMark",m_setup);
		GetInitGameParam(&m_newMarkPrintX,"newMarkPrintDeltaX");
		GetInitGameParam(&m_newMarkPrintY,"newMarkPrintDeltaY");
	}
	GetDisableQuickButtonSetup();
	GetBGMSetup();
	GetFadeInOutSetup();
	GetEnterExitVoiceFileName();
	GetAddLayerSetup();
	GetAnimeLayerSetup();
}



CCommonPrintTerm::~CCommonPrintTerm()
{
	End();
}

void CCommonPrintTerm::End(void)
{
	ENDDELETECLASS(m_newMark);

	ENDDELETECLASS(m_termText);

	if (m_typeTable != NULL)
	{
		for (int i=0;i<m_termTypeKosuu;i++)
		{
			DELETEARRAY(m_typeTable[i]);
		}
		DELETEARRAY(m_typeTable);
	}
	DELETEARRAY(m_typeTableNumber);

	ENDDELETECLASS(m_radio);
	DELETEARRAY(m_termData);
	ENDDELETECLASS(m_termList);
}


int CCommonPrintTerm::Init(void)
{
	LoadBackBG();

	ListAndSortTerm();



	m_selectedTermNumber = -1;


	m_radio->SetRadio(m_typeNumber);
	ReloadButtonPic();
	m_radio->Init(m_typeNumber);

	m_updownBack->Init();
	m_updownBack->SetPageMax(m_pageMax);
	m_updownBack->SetPage(m_page);

	if (m_newMark != NULL)
	{
		m_newMark->Init();
	}

	return -1;
}


int CCommonPrintTerm::Calcu(void)
{

	if (m_newMark != NULL)
	{
		m_newMark->Calcu();
	}

	int udb = m_updownBack->Calcu(m_inputStatus);

	if (udb != NNNBUTTON_NOTHING)
	{
		int nm = ProcessUpDownBack(udb);
		if (nm >= 0)
		{
			if (nm == 0)
			{
//				return ReturnFadeOut(OMAKE_MODE);
				m_game->FuqueAllEffectYoyaku();
				return ReturnFadeOut(m_backMode);
			}
			else
			{
				m_selectedTermNumber = -1;

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


	m_onNumber = GetOnNumber(m_mouseStatus->GetZahyo());

	if (m_mouseStatus->CheckClick(0))
	{
		if (m_onNumber != -1)
		{
			m_selectedTermNumber = m_termData[m_onNumber + m_page * m_termPerPage].n;
			int look = m_game->CheckTermLook(m_selectedTermNumber);
			if (!look)
			{
				m_game->SetTermLook(m_selectedTermNumber);
			}
			ReloadTermText();
		}
	}


	if (m_radio != NULL)
	{
		int rt = m_radio->Calcu(m_inputStatus);
		if (rt != -1)
		{
			int nm = ProcessButtonGroup(rt);
			if ((nm >= 0) && (nm < m_termTypeKosuu))
			{
				m_selectedTermNumber = -1;

				m_typeNumber = nm;
				ListAndSortTerm();

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

int CCommonPrintTerm::Print(void)
{
	CAreaControl::SetNextAllPrint();

	PrintBackScriptOrBG();

	int codeByte = CMyFont::m_codeByte;


	if (m_radio != NULL)
	{
		m_radio->Print();
	}

	if (m_updownBack != NULL)
	{
		m_updownBack->Print(TRUE);
	}

	int st = m_termPerPage * m_page;
	int ed = st + m_termPerPage;
	if (ed >= m_termNumber)
	{
		ed = m_termNumber;
	}

	int lp = ed - st;
	for (int i=0;i<lp;i++)
	{
		int term = m_termData[st+i].n;
		BOOL flag = m_game->CheckTerm(term);
		BOOL look = m_game->CheckTermLook(term);

		POINT pt = GetListPoint(i);
		int x = pt.x;
		int y = pt.y;

		if (!flag)
		{
			if(codeByte == 2)
			{
				m_message->PrintMessage(x,y,"HHH");
			}
			else
			{
				m_message->PrintMessage(x,y,"???");
			}
		}
		else
		{
			LPSTR desc = m_termData[st+i].title;
			m_message->PrintMessage(x,y,desc);

			if (term == m_selectedTermNumber)
			{
				CAllGeo::TransBoxFill(x,y,m_listSizeX,m_listSizeY,220,92,164,50);
			}

			if (!look)
			{
				if (m_newMark != NULL)
				{
					POINT pt;
					pt.x = m_newMarkPrintX + x;
					pt.y = m_newMarkPrintY + y;
					m_newMark->Print(pt);
				}
			}

			if (i == m_onNumber)
			{
				CAllGeo::TransBoxFill(x,y,m_listSizeX,m_listSizeY,120,192,64,50);
			}


		}
	}


	if (m_selectedTermNumber != -1)
	{
		int k = m_termText->GetNameKosuu();
		for (int i=0;i<k;i++)
		{
			LPSTR text = m_termText->GetName(i);
			int x = 400;
			int y = 200 + i * 30;
			m_message->PrintMessage(x,y,text);
		}
	}



//	m_game->PrintOptionButtonYoyaku();

	return -1;
}

int CCommonPrintTerm::GetOnNumber(POINT pt)
{
	//page
	int mx = m_termNumber -  m_page * m_termPerPage;
	if (mx>m_termPerPage) mx = m_termPerPage;

	for (int i=0;i<mx;i++)
	{
		POINT pt2 = GetListPoint(i);
		int dx = pt.x - pt2.x;
		int dy = pt.y - pt2.y;

		if ((dx>=0) && (dx<m_listSizeX) && (dy>=0) && (dy<m_listSizeY))
		{
			return i;
		}


	}

	return -1;
}

POINT CCommonPrintTerm::GetListPoint(int n)
{
	POINT pt;
	pt.x = m_listPrintX + m_listNextX * n;
	pt.y = m_listPrintY + m_listNextY * n;
	return pt;
}

void CCommonPrintTerm::ReloadButtonPic(void)
{
	if (m_radio != NULL)
	{
		int sel = m_radio->GetRadio();

		for (int i=0;i<m_termTypeKosuu;i++)
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

	LoadUpDownButtonPic();
	LoadBackButtonPic();



}





void CCommonPrintTerm::FinalExitRoutine(void)
{

//	if (m_exitModeFlag)
//	{
//		m_game->SetYoyaku();
//	}

}

int CCommonPrintTerm::EndMode(void)
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




void CCommonPrintTerm::CreateStartScreen(void)
{
	Print();
}


void CCommonPrintTerm::ReloadTermText(void)
{
	if (m_selectedTermNumber == -1) return;
	if (m_termTextNumber == m_selectedTermNumber) return;

	m_termTextNumber = m_selectedTermNumber;
	ENDDELETECLASS(m_termText);
	m_termText = new CNameList();
	char filename[256];
	sprintf_s(filename,256,"nya\\term\\%s.xtx",m_termList->GetName(m_termTextNumber*4+3));
	m_termText->LoadFile(filename);
}

void CCommonPrintTerm::ListAndSortTerm(void)
{
	m_termNumber = 0;
	int checkNumber = m_typeTableNumber[m_typeNumber];

	for (int i=0;i<m_allTermNumber;i++)
	{
		LPSTR title = m_termList->GetName(4*i);
		int type = atoi(m_termList->GetName(i*4+1));
		int param = atoi(m_termList->GetName(i*4+2));

		BOOL flag = TRUE;
		for (int k=0;k<checkNumber;k++)
		{
			int check = m_typeTable[m_typeNumber][k];
			if (check != 0)
			{
				flag = FALSE;
				if (type == check)
				{
					flag = TRUE;
					break;
				}
			}
		}

		if (flag)
		{
			m_termData[m_termNumber].n = i;
			m_termData[m_termNumber].type = type;
			m_termData[m_termNumber].param = param;
			m_termData[m_termNumber].title = title;

			m_termNumber++;

		}
	}

	if (m_termNumber > 1)
	{
		//set sort jyoken 
		m_sortByType = 0;
		m_sortByParam = 0;
		m_sortByTitle = 1;

		qsort(m_termData,m_termNumber,sizeof(TERMDATA),MyCompare);
	}


	m_pageMax = (m_termNumber+m_termPerPage-1) / m_termPerPage;
	if (m_pageMax < 1) m_pageMax = 1;
	m_page = 0;
}


int CCommonPrintTerm::MyCompare(const void* a,const void* b)
{
	TERMDATA* term1 = (TERMDATA*)a;
	TERMDATA* term2 = (TERMDATA*)b;

	int rt = 0;

	if (m_sortByType != 0)
	{
		rt = term1->type - term2->type;
		rt *= m_sortByType;
		if (rt != 0) return rt;
	}

	if (m_sortByParam != 0)
	{
		rt = term1->param - term2->param;
		rt *= m_sortByParam;
		if (rt != 0) return rt;
	}

	if (m_sortByTitle != 0)
	{
		rt = _stricmp(term1->title,term2->title);
		rt *= m_sortByTitle;
	}

	return rt;
}






