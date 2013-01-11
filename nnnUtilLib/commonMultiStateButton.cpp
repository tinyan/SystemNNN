//
//
//

#include <windows.h>
#include <stdio.h>

#include "..\nyanlib\include\commonMacro.h"


#include "nnnButtonStatus.h"
#include "superButtonSetup.h"
#include "nameList.h"

#include "commonButton.h"
#include "commonMultiStateButton.h"


char CCommonMultiStateButton::m_defaultButtonName[] = "button";

CCommonMultiStateButton::CCommonMultiStateButton(CNameList* lpSetup,CPicture* lpBG,LPSTR buttonName,int n,POINT* lpPoint,CSuperButtonSetup* lpCopySetup)
{
	m_buttonKosuu = n;
	if (buttonName == NULL) buttonName = m_defaultButtonName;
	m_setup = lpSetup;

	m_button = new CCommonButton* [n];
	m_state = 0;

	int i = 0;
	for (i=0;i<n;i++)
	{
		m_button[i] = new CCommonButton();
	}

	m_superSetup = new CSuperButtonSetup* [n];


	char name[256];
	wsprintf(name,"%s%d",buttonName,0+1);
	m_superSetup[0] = new CSuperButtonSetup(m_setup,name,lpCopySetup,NULL);
	if (lpPoint != NULL) m_superSetup[0]->SetZahyoIfCan(*lpPoint);

	POINT orgPoint = m_superSetup[0]->GetZahyo();

	for (i=1;i<n;i++)
	{
		wsprintf(name,"%s%d",buttonName,i+1);
		m_superSetup[i] = new CSuperButtonSetup(m_setup,name,m_superSetup[i-1],NULL);
		m_superSetup[i]->SetZahyoIfCan(orgPoint);
	}

	for (i=0;i<n;i++)
	{
		m_superSetup[i]->SetupButtonStatus(m_button[i]);
		if (lpBG != NULL) m_button[i]->SetBG(lpBG);
	}

	m_existFlag = new BOOL[n];
	m_enableFlag = new BOOL[n];

	for (i=0;i<n;i++)
	{
		m_existFlag[i] = FALSE;
		m_enableFlag[i] = TRUE;
	}
	m_existFlag[0] = TRUE;
	m_enableFlag[0] = TRUE;

	m_allEnableFlag = TRUE;
	m_allExistFlag = TRUE;
}



CCommonMultiStateButton::~CCommonMultiStateButton()
{
	End();
}


void CCommonMultiStateButton::End(void)
{
	DELETEARRAY(m_enableFlag);
	DELETEARRAY(m_existFlag);
	if (m_superSetup != NULL)
	{
		for (int i=0;i<m_buttonKosuu;i++)
		{
			ENDDELETECLASS(m_superSetup[i]);
		}
		DELETEARRAY(m_superSetup);
	}

	if (m_button != NULL)
	{
		for (int i=0;i<m_buttonKosuu;i++)
		{
			ENDDELETECLASS(m_button[i]);
		}
		DELETEARRAY(m_button);
	}

	DELETEARRAY(m_button);
//	for (int i=0;i<2;i++)
//	{
//		ENDDELETECLASS(m_button[i]);
//	}
}


void CCommonMultiStateButton::SetState(int n)
{
	m_state = n;
	for (int i=0;i<m_buttonKosuu;i++)
	{
		if (m_state == i)
		{
			m_existFlag[i] = TRUE;
		}
		else
		{
			m_existFlag[i] = FALSE;
		}
	}
}

int CCommonMultiStateButton::GetState(void)
{
	return m_state;
}


void CCommonMultiStateButton::Init(void)
{
	for (int i=0;i<m_buttonKosuu;i++)
	{
		if (m_existFlag[i])
		{
			CCommonButton* button = m_button[i];
			if (button != NULL)
			{
				BOOL flg = m_allEnableFlag;
				if (flg)
				{
					flg = m_enableFlag[i];
				}
				button->SetEnable(flg);
				button->Init();
			}
		}
	}
}

int CCommonMultiStateButton::Calcu(CInputStatus* lpInput)
{
	if (m_allExistFlag)
	{
		if (m_existFlag[m_state])
		{
			CCommonButton* button = m_button[m_state];
			if (button != NULL)
			{
				int rt = button->Calcu(lpInput);

				if (CCommonButton::CheckExistData(rt))
				{
					rt = CCommonButton::ChangeButtonData(rt,m_state);
				}
				return rt;
			}
		}
	}

	return NNNBUTTON_NOTHING;
}


void CCommonMultiStateButton::Print(BOOL flg)
{
	if (m_allExistFlag)
	{
		if (m_existFlag[m_state])
		{
			CCommonButton* button = m_button[m_state];
			if (button != NULL)
			{
				button->Print();
			}
		}
	}
}

CPicture* CCommonMultiStateButton::GetPicture(int n)
{
	CCommonButton* button = m_button[n];
	if (button == NULL) return NULL;
	return button->GetPicture();
}

void CCommonMultiStateButton::SetPicture(CPicture* lpPic,int n)
{
	int st = n;
	int ed = n;

	if (n == -1)
	{
		st = 0;
		ed = m_buttonKosuu - 1;
	}

	for (int i=st;i<=ed;i++)
	{
		CCommonButton* button = m_button[i];
		if (button != NULL)
		{
			button->SetPicture(lpPic);
		}
	}
}


LPSTR CCommonMultiStateButton::GetFileName(int n)
{
	CCommonButton* button = m_button[n];
	if (button == NULL) return NULL;
	return button->GetFileName();
}

void CCommonMultiStateButton::SetAllEnable(BOOL flg)
{
	m_allEnableFlag = flg;

	for (int i=0;i<m_buttonKosuu;i++)
	{
		CCommonButton* button = m_button[i];
		if (button != NULL)
		{
			if (flg)
			{
				button->SetEnable(m_enableFlag[i]);
			}
			else
			{
				button->SetEnable(FALSE);
			}
		}
	}
}

void CCommonMultiStateButton::SetAllExist(BOOL flg)
{
	m_allExistFlag = flg;
}

BOOL CCommonMultiStateButton::GetAllEnable(void)
{
	return m_allEnableFlag;
}

BOOL CCommonMultiStateButton::GetAllExist(void)
{
	return m_allExistFlag;
}

SIZE CCommonMultiStateButton::GetSize(int n)
{
	CCommonButton* button = m_button[n];
	return button->GetSize();
}

void CCommonMultiStateButton::SetZahyo(POINT pt,int n)
{
	int st = n;
	int ed = n;
	if (n == -1)
	{
		st = 0;
		ed = m_buttonKosuu-1;
	}

	for (int i=st;i<=ed;i++)
	{
		m_button[i]->SetZahyo(pt);
	}
}

void CCommonMultiStateButton::ResetAnimeCount(void)
{
	if (m_allExistFlag)
	{
		if (m_existFlag[m_state])
		{
			CCommonButton* button = m_button[m_state];
			if (button != NULL)
			{
				button->ResetAnimeCount();
			}
		}
	}
}



//void CCommonMultiStateButton::SetButton(int n,CCommonButton* button)
//{
	//m_button[n] = button;
//}


/*_*/

