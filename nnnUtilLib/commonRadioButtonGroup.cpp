//
//
//


#include <windows.h>

#include "..\nyanlib\include\commonMacro.h"
#include "..\nyanlib\include\picture.h"
#include "..\nyanlib\include\areaControl.h"

#include "superButtonSetup.h"

#include "nnnButtonStatus.h"

#include "commonButton.h"
#include "commonMultiStateButton.h"
#include "commonRadioButton.h"
#include "commonRadioButtonGroup.h"



CCommonRadioButtonGroup::CCommonRadioButtonGroup(CNameList* lpSetup,LPSTR buttonName,CPicture* lpBG,int buttonKosuu,CSuperButtonSetup* lpCopySetup)
{
	m_setup = lpSetup;
	m_buttonKosuu = buttonKosuu;

	m_ppButton = new CCommonRadioButton* [m_buttonKosuu];


	//CPicture* lpBG = NULL;
//	LPSTR name = NULL;
	POINT* lpPoint = NULL;

	for (int i=0;i<m_buttonKosuu;i++)
	{
		CSuperButtonSetup* preSetup = lpCopySetup;
		POINT pt;

		if (i>0)
		{
			preSetup = m_ppButton[i-1]->GetSuperButtonSetup(1);
			pt = preSetup->GetZahyo();
			SIZE sz = preSetup->GetSize();
			pt.x += sz.cx * 1;
			lpPoint = &pt;
		}

		char name[256];
		wsprintf(name,"%s%dButton",buttonName,i+1);

		m_ppButton[i] = new CCommonRadioButton(lpSetup,lpBG,name,lpPoint,preSetup);
	}

	m_radio = 0;
}


CCommonRadioButtonGroup::~CCommonRadioButtonGroup()
{
	End();
}

void CCommonRadioButtonGroup::End(void)
{
	if (m_ppButton != NULL)
	{
		for (int i=0;i<m_buttonKosuu;i++)
		{
			ENDDELETECLASS(m_ppButton[i]);
		}

		DELETEARRAY(m_ppButton);
	}
}



void CCommonRadioButtonGroup::Init(int radio)
{
	m_radio = radio;
	for (int i=0;i<m_buttonKosuu;i++)
	{
		int state = 0;
		if (i == m_radio)
		{
			state = 1;
		}

		m_ppButton[i]->SetState(state);
		m_ppButton[i]->Init();
	}

	m_clickingNumber = -1;
}


int CCommonRadioButtonGroup::Calcu(CInputStatus* lpInput)
{
	int returnCode = NNNBUTTON_NOTHING;

	int lvl = 0;

	for (int i=0;i<m_buttonKosuu;i++)
	{
		CCommonRadioButton* button = m_ppButton[i];
		int rt = NNNBUTTON_NOTHING;

		if (button != NULL)
		{
			BOOL flg = TRUE;
			if (1)
			{
				if (i == m_radio) flg = FALSE;
			}

			if (m_clickingNumber != -1)
			{
				if (i != m_clickingNumber)
				{
					flg = FALSE;
				}
			}

			if (flg)
			{
				rt = button->Calcu(lpInput);
			}
			else
			{
				button->Calcu(NULL);
			}
		}

		if (rt != NNNBUTTON_NOTHING)
		{
			int lvl2 = 1;

			int st = CCommonButton::GetButtonStatus(rt);
			if (st == NNNBUTTON_STARTCLICK)
			{
				m_clickingNumber = i;
				lvl2 = 3;
			}

			if (st == NNNBUTTON_NUMBER) lvl2 = 5;

			if (lvl2>lvl)
			{
				lvl = lvl2;
				returnCode = rt;
			}

			if (st == NNNBUTTON_NUMBER)
			{
				returnCode = CCommonButton::ChangeButtonData(rt,i);
				m_radio = i;
			}
		}
	}

	return returnCode;
}




void CCommonRadioButtonGroup::Print(BOOL flg)
{
	for (int i=0;i<m_buttonKosuu;i++)
	{
		m_ppButton[i]->Print(flg);
	}
}

void CCommonRadioButtonGroup::SetAllEnable(BOOL flg)
{
	for (int i=0;i<m_buttonKosuu;i++)
	{
		SetEnable(i,flg);
	}
}

void CCommonRadioButtonGroup::SetAllExist(BOOL flg)
{
	for (int i=0;i<m_buttonKosuu;i++)
	{
		SetExist(i,flg);
	}
}


void CCommonRadioButtonGroup::SetEnable(int n,BOOL flg)
{
	m_ppButton[n]->SetAllEnable(flg);
}

void CCommonRadioButtonGroup::SetExist(int n,BOOL flg)
{
	m_ppButton[n]->SetAllExist(flg);
}

BOOL CCommonRadioButtonGroup::CheckEnable(int n)
{
	return TRUE;
}

BOOL CCommonRadioButtonGroup::CheckExist(int n)
{
	return TRUE;
}


CSuperButtonSetup* CCommonRadioButtonGroup::GetSuperSetup(int n,int k)
{
	if (n == -1) n = m_buttonKosuu-1;
	if (k == -1) k = 1;

	return m_ppButton[n]->GetSuperButtonSetup(k);
}


CPicture* CCommonRadioButtonGroup::GetPicture(int n,int k)
{
	return m_ppButton[n]->GetPicture(k);
}

void CCommonRadioButtonGroup::SetPicture(CPicture* lpPic,int n,int k)
{
	int st = k;
	int ed = k;
	if (k == -1)
	{
		st = 0;
		ed = 1;
	}

	for (int i=st;i<=ed;i++)
	{
		int st2 = n;
		int ed2 = n;
		if (n == -1)
		{
			st2 = 0;
			ed2 = m_buttonKosuu-1;
		}

		for (int p=st2;p<=ed2;p++)
		{
			m_ppButton[p]->SetPicture(lpPic,i);
		}
	}
}

LPSTR CCommonRadioButtonGroup::GetFileName(int n,int k)
{
	if (k == -1)
	{
		if (n == m_radio)
		{
			k = 1;
		}
		else
		{
			k = 0;
		}
	}

	return m_ppButton[n]->GetFileName(k);
}


int CCommonRadioButtonGroup::GetRadio(void)
{
	return m_radio;
}

void CCommonRadioButtonGroup::SetRadio(int radio)
{
	m_radio = radio;
	//
	m_radio = radio;
	for (int i=0;i<m_buttonKosuu;i++)
	{
		int state = 0;
		if (i == m_radio)
		{
			state = 1;
		}

		m_ppButton[i]->SetState(state);
		m_ppButton[i]->Init();
	}

	m_clickingNumber = -1;

}


void CCommonRadioButtonGroup::ResetAnimeCount(void)
{
	for (int i=0;i<m_buttonKosuu;i++)
	{
		m_ppButton[i]->ResetAnimeCount();
	}
}


void CCommonRadioButtonGroup::AppearPrint(int count, int countMax, int type, POINT deltaPoint)
{
	for (int i = 0; i < m_buttonKosuu; i++)
	{
		m_ppButton[i]->AppearPrint(count,countMax,type,deltaPoint);
	}
}

/*_*/


