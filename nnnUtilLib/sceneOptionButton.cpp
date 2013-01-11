//
// SceneOptionButton.cpp
//

#include <windows.h>
#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"


#include "nameList.h"
#include "setupList.h"

#include "nnnButtonStatus.h"

#include "commonButton.h"


#include "taihi.h"

#include "FloatingLayer.h"
#include "SceneOptionButton.h"


char CSceneOptionButton::m_defaultButtonFileName[] = "ta_scene_bt1";



CSceneOptionButton::CSceneOptionButton(LPSTR initName, CTaihi* lpTaihi, int taihiLayer) : CFloatingLayer(lpTaihi, taihiLayer,0)
{
//	LoadSetupFile("SceneOptionButton");	
	LoadSetupFile(initName);

	m_kazariKosuu = 0;
	GetInitGameParam(&m_kazariKosuu,"addPartsNumber");
	ChangeLayerKosuu(m_kazariKosuu+1);



	m_zahyo = new POINT[m_kazariKosuu+1];
	m_size = new SIZE[m_kazariKosuu+1];
	m_ppPic = new CPicture* [m_kazariKosuu+1];

	int i = 0;
	for (i=0;i<m_kazariKosuu+1;i++)
	{
		m_ppPic[i] = new CPicture();
	}

	//ƒ{ƒ^ƒ“À•W
	m_button = new CCommonButton(m_setup->m_setup,initName);

	m_zahyo[0] = m_button->GetZahyo();
	m_size[0] = m_button->GetSize();
	CreateLayer(m_size[0].cx,m_size[0].cy,0);

	
	LPSTR fname = m_button->GetFileName();
	char bfilename[256];
	wsprintf(bfilename,"sys\\%s",fname);
	m_ppPic[0]->LoadDWQ(bfilename);
	m_button->SetPicture(m_ppPic[0]);


	char name[256];
	for (i=1;i<m_kazariKosuu+1;i++)
	{
		int x = 0;
		int y = 0;

		wsprintf(name,"kazari%dPrintX",i);
		GetInitGameParam(&x,name);
		wsprintf(name,"kazari%dPrintY",i);
		GetInitGameParam(&y,name);

		x += m_zahyo[0].x;
		y += m_zahyo[0].y;

		m_zahyo[i].x = x;
		m_zahyo[i].y = y;

		int sizeX = 16;
		int sizeY = 16;
		wsprintf(name,"kazari%dSizeX",i);
		GetInitGameParam(&sizeX,name);
		wsprintf(name,"kazari%dSizeY",i);
		GetInitGameParam(&sizeY,name);
		m_size[i].cx = sizeX;
		m_size[i].cy = sizeY;

		LPSTR filename = m_defaultButtonFileName;
		wsprintf(name,"kazari%dFileName",i);
		GetInitGameString(&filename,name);

		char picfilename[256];
		wsprintf(picfilename,"sys\\%s",filename);
		m_ppPic[i]->LoadDWQ(picfilename);

		CreateLayer(m_size[i].cx,m_size[i].cy,i);
	}
}


CSceneOptionButton::~CSceneOptionButton()
{
	End();
}


void CSceneOptionButton::End(void)
{
	ENDDELETECLASS(m_button);

	if (m_ppPic != NULL)
	{
		for (int i=0;i<m_kazariKosuu+1;i++)
		{
			ENDDELETECLASS(m_ppPic[i]);
		}
		DELETEARRAY(m_ppPic);
	}


	DELETEARRAY(m_size);
	DELETEARRAY(m_zahyo);
}

void CSceneOptionButton::Init(void)
{
	if (m_button != NULL) m_button->Init();
}

int CSceneOptionButton::Calcu(CInputStatus* lpInput)
{
	if (m_button == NULL) return NNNBUTTON_NOTHING;

	return m_button->Calcu(lpInput);
}

void CSceneOptionButton::Print(BOOL taihiFlag)
{
	for (int i=m_kazariKosuu;i>=1;i--)
	{
		int putX = m_zahyo[i].x;
		int putY = m_zahyo[i].y;

		int sizeX = m_size[i].cx;
		int sizeY = m_size[i].cy;

		if (taihiFlag)
		{
			Taihi(putX,putY,i);
		}

		int srcX = 0;
		int srcY = 0;

		CAreaControl::AddArea(putX,putY,sizeX,sizeY);

		m_ppPic[i]->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
	}

	if (taihiFlag)
	{
		int putX = m_zahyo[0].x;
		int putY = m_zahyo[0].y;
		Taihi(putX,putY,0);
	}

	if (m_button != NULL) m_button->Print();
}

void CSceneOptionButton::SetExist(BOOL flg)
{
	if (m_button != NULL)
	{
		m_button->SetExist(flg);
	}
}

void CSceneOptionButton::SetReturnCannotClick(BOOL flg)
{
	if (m_button != NULL)
	{
		m_button->SetReturnCannotClick(flg);
	}
}

void CSceneOptionButton::SetEnable(BOOL flg)
{
	if (m_button != NULL)
	{
		m_button->SetEnable(flg);
	}
}


/*
BOOL CSceneOptionButton::CheckOn(int mouseX,int mouseY)
{
	int x = mouseX - m_pPrintX[0];
	int y = mouseY - m_pPrintY[0];
	int sizeX = m_pSizeX[0];
	int sizeY = m_pSizeY[0];

	if ((x>=0) && (y>=0) && (x<sizeX) && (y<sizeY))
	{
		if (m_ppPic[0]->CheckOnPic(x,y)) return TRUE;
	}

	return FALSE;
}


void CSceneOptionButton::MoveZahyo(int deltaX, int deltaY)
{
	m_pPrintX[0] = m_printX + deltaX;
	m_pPrintY[0] = m_printY + deltaY;

}
*/


/*_*/


