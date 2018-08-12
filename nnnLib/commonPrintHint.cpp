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


#include "commonPrintHint.h"

#include "commonKeyList.h"



CCommonPrintHint::CCommonPrintHint(CGameCallBack* lpGame, int extMode) : CCommonGeneral(lpGame)
{
	SetClassNumber(PRINTHINT_MODE);
	LoadSetupFile("PrintHint", 256);






	m_allHintNumber = 1;
	m_nowHintNumber = 0;
	GetInitGameParam(&m_allHintNumber, "hintAllNumber");


	m_picNumX = 2;
	m_picNumY = 1;
	GetInitGameParam(&m_picNumX, "picNumX");
	GetInitGameParam(&m_picNumY, "picNumY");
	m_picPrintX = 100;
	m_picPrintY = 100;
	GetInitGameParam(&m_picPrintX, "picPrintX");
	GetInitGameParam(&m_picPrintY, "picPrintY");
	m_picNextX = 300;
	m_picNextY = 300;
	GetInitGameParam(&m_picNextX, "picNextX");
	GetInitGameParam(&m_picNextY, "picNextY");


	m_hintNumber = new int[m_allHintNumber];
	m_hintFilename = new LPSTR*[m_allHintNumber];
	m_hintPrintZahyo = new POINT*[m_allHintNumber];
	m_hintPrintSize = new SIZE*[m_allHintNumber];
	m_flagVarNumber = new int*[m_allHintNumber];
	for (int i = 0; i < m_allHintNumber; i++)
	{
		int hintNumber = 1;
		char name[256];
		sprintf_s(name, "hint%dNumber", i + 1);
		GetInitGameParam(&hintNumber, name);
		m_hintNumber[i] = hintNumber;
		m_hintFilename[i] = new LPSTR[hintNumber];
		for (int k = 0; k < hintNumber; k++)
		{
			LPSTR filename = NULL;
			sprintf_s(name, "hint%dfilename%d", i + 1, k + 1);
			GetInitGameString(&filename, name);
			m_hintFilename[i][k] = filename;
		}

		m_hintPrintZahyo[i] = new POINT[hintNumber];
		m_hintPrintSize[i] = new SIZE[hintNumber];


		for (int k = 0; k < hintNumber; k++)
		{
			int n = k % (m_picNumX * m_picNumY);
			int nx = n % m_picNumX;
			int ny = n / m_picNumX;

			int printX = m_picPrintX + m_picNextX * nx;
			int printY = m_picPrintY + m_picNextY * ny;

			int sizeX = 0;
			int sizeY = 0;

			sprintf_s(name, 256, "hint%d_%dPrintX", i+1, k+1);
			GetInitGameParam(&printX, name);
			sprintf_s(name, 256, "hint%d_%dPrintY", i+1, k+1);
			GetInitGameParam(&printY, name);
			sprintf_s(name, 256, "hint%d_%dSizeX", i+1, k+1);
			GetInitGameParam(&sizeX, name);
			sprintf_s(name, 256, "hint%d_%dSizeY", i+1, k+1);
			GetInitGameParam(&sizeY, name);


			POINT pt;
			pt.x = printX;
			pt.y = printY;
			SIZE sz;
			sz.cx = sizeX;
			sz.cy = sizeY;

			m_hintPrintZahyo[i][k] = pt;
			m_hintPrintSize[i][k] = sz;

		}


		m_flagVarNumber[i] = new int[hintNumber];
		for (int k = 0; k < hintNumber; k++)
		{
			int varNumber = -1;
			LPSTR varname = NULL;
			sprintf_s(name, "hint%dflag%d", i + 1, k + 1);
			GetInitGameString(&varname, name);
			if (varname)
			{
				varNumber = m_game->GetVarNumber(varname);
			}

			m_flagVarNumber[i][k] = varNumber;
		}




	}



	m_picWork = new CPicture*[m_picNumX * m_picNumY];
	for (int i = 0; i < m_picNumX*m_picNumY; i++)
	{
		m_picWork[i] = new CPicture();
	}


	m_noPicFilename = NULL;
	GetInitGameString(&m_noPicFilename, "nopicFilename");

//	m_haveItem = new CHaveItemData();

	GetInitGameString(&m_filenameBG, "fileNameBG");


	m_message = m_game->GetMyMessage();

	GetBackExecSetup();
	GetAllPrintSetup();
	m_mustAllPrintFlag = TRUE;


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

CCommonPrintHint::~CCommonPrintHint()
{
	End();
}

void CCommonPrintHint::End(void)
{
	if (m_picWork)
	{
		for (int i = 0; i < m_picNumX*m_picNumY; i++)
		{
			ENDDELETECLASS(m_picWork[i]);
		}
		DELETEARRAY(m_picWork);
	}


	DELETEARRAY(m_hintNumber);

	if (m_hintFilename)
	{

		for (int i = 0; i < m_allHintNumber; i++)
		{
			DELETEARRAY(m_hintFilename[i]);
		}
		DELETEARRAY(m_hintFilename);
	}

	if (m_hintPrintZahyo)
	{
		for (int i = 0; i < m_allHintNumber; i++)
		{
			DELETEARRAY(m_hintPrintZahyo[i]);
		}

		DELETEARRAY(m_hintPrintZahyo);
	}

	if (m_hintPrintSize)
	{
		for (int i = 0; i < m_allHintNumber; i++)
		{
			DELETEARRAY(m_hintPrintSize[i]);
		}

		DELETEARRAY(m_hintPrintSize);
	}

	if (m_flagVarNumber)
	{
		for (int i = 0; i < m_allHintNumber; i++)
		{
			DELETEARRAY(m_flagVarNumber[i]);
		}

		DELETEARRAY(m_flagVarNumber);
	}
}


int CCommonPrintHint::Init(void)
{
	LoadBackBG();

	m_nowHintNumber = m_game->GetHintNumber();


	LoadUpDownButtonPic();
	m_updownBack->Init();


	int pageMax = (m_hintNumber[m_nowHintNumber]  + (m_picNumX * m_picNumY - 1)) / (m_picNumX * m_picNumY);
	m_updownBack->SetPageMax(pageMax);
	m_updownBack->SetPage(0);


	GetNowPic();
	


//	char filename[256];
//	sprintf_s(filename, 256, "sys\\%s", m_plateFilename);
//	m_commonParts->LoadDWQ(filename);



	return -1;
}


int CCommonPrintHint::Calcu(void)
{
	int rt = m_updownBack->Calcu(m_inputStatus);
	if (rt != NNNBUTTON_NOTHING)
	{
		int nm = ProcessCommonButton(rt);
		if (nm == 0)
		{
			return ReturnFadeOut(SELECTHINT_MODE);
		}
		else if ((nm == 1) || (nm == 2))
		{
			GetNowPic();
			m_updownBack->Init();
		}
	}


	return -1;
}

int CCommonPrintHint::Print(void)
{
	CAreaControl::SetNextAllPrint();

	PrintBackScriptOrBG();

	m_message->PrintMessage(100, 100, "‚o‚q‚h‚m‚s‚g‚h‚m‚s");



	int page = m_updown->GetPage();
	for (int j = 0; j < m_picNumY; j++)
	{
		for (int i = 0; i < m_picNumX; i++)
		{
			int n = page * m_picNumX * m_picNumY + i + j * m_picNumX;
			if ((n >= 0) && (n < m_hintNumber[m_nowHintNumber]))
			{
				int workNumber = i + j * m_picNumX;
				//				int x = m_picPrintX + m_picNextX * i;
				//				int y= m_picPrintY + m_picNextY * j;
				int x = m_hintPrintZahyo[m_nowHintNumber][n].x;
				int y = m_hintPrintZahyo[m_nowHintNumber][n].y;
				int sizeX = m_hintPrintSize[m_nowHintNumber][n].cx;
				int sizeY = m_hintPrintSize[m_nowHintNumber][n].cy;

				if ((sizeX > 0) && (sizeY > 0))
				{
					m_picWork[workNumber]->Blt(x, y, 0,0,sizeX,sizeY,TRUE);
				}
				else
				{
					m_picWork[workNumber]->Put(x, y, TRUE);
				}
			}
		}
	}


	m_updownBack->Print(TRUE);

	return -1;
}


void CCommonPrintHint::CreateStartScreen(void)
{
	Print();
}



void CCommonPrintHint::GetNowPic(void)
{
	int page = m_updown->GetPage();
	for (int j = 0; j < m_picNumY; j++)
	{
		for (int i = 0; i < m_picNumX; i++)
		{
			int n = page * m_picNumX * m_picNumY + i + j * m_picNumX;
			if ((n >= 0) && (n < m_hintNumber[m_nowHintNumber]))
			{
				int workNumber = i + j * m_picNumX;
				char filename[256];

				BOOL flag = FALSE;

				int varNumber = m_flagVarNumber[m_nowHintNumber][n];
				if (varNumber != -1)
				{
					if (m_game->GetVarData(varNumber) != 0)
					{
						flag = TRUE;
					}
				}

				if (flag)
				{
					sprintf_s(filename, 256, "sys\\%s", m_hintFilename[m_nowHintNumber][n]);
				}
				else
				{
					sprintf_s(filename, 256, "sys\\%s", m_noPicFilename);
				}

				m_picWork[workNumber]->LoadDWQ(filename);
			}
		}
	}

}

