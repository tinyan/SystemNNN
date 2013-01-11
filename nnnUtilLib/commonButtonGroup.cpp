//
// ButtonGroup.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\picture.h"



#include "nnnButtonStatus.h"
#include "nameList.h"
#include "myMouseStatus.h"

#include "commonbutton.h"


#include "commonButtonGroup.h"

#include "superButtonSetup.h"

CCommonButtonGroup::CCommonButtonGroup(CNameList* lpSetup,int buttonKosuu,CPicture* lpBG,LPSTR defaultButtonName,LPSTR* customButtonName)
{
	m_buttonKosuu = buttonKosuu;

	m_ppButton = new CCommonButton* [m_buttonKosuu];
	int i = 0;
	for (i=0;i<m_buttonKosuu;i++)
	{
		m_ppButton[i] = new CCommonButton();
	}

	m_superMode = 1;

	
	m_ppSuperSetup = new CSuperButtonSetup* [m_buttonKosuu];
	for (i=0;i<m_buttonKosuu;i++)
	{
		char buttonName[256];
		if (customButtonName != NULL)
		{
			wsprintf(buttonName,"%s",*(customButtonName+i));
		}
		else if (defaultButtonName != NULL)
		{
			wsprintf(buttonName,"%s%d",defaultButtonName,i+1);
		}
		else
		{
			wsprintf(buttonName,"button%d",defaultButtonName,i+1);
		}

		if (i == 0)
		{
			m_ppSuperSetup[i] = new CSuperButtonSetup(lpSetup,buttonName);
		}
		else
		{
			m_ppSuperSetup[i] = new CSuperButtonSetup(lpSetup,buttonName,m_ppSuperSetup[i-1]);
		}
	}


	for (i=0;i<m_buttonKosuu;i++)
	{
		m_ppSuperSetup[i]->SetupButtonStatus(m_ppButton[i]);
		if (lpBG != NULL) m_ppButton[i]->SetBG(lpBG);
	}

//	m_pExistFlag = new BOOL[m_buttonKosuu];
//	m_pEnableFlag = new BOOL[m_buttonKosuu];

	for (i=0;i<m_buttonKosuu;i++)
	{
//		m_pExistFlag[i] = TRUE;
//		m_pEnableFlag[i] = TRUE;
	}

	m_status = 0;
	m_buttonNumber = -1;
}




CCommonButtonGroup::~CCommonButtonGroup()
{
	End();
}


void CCommonButtonGroup::End(void)
{
	if (m_ppSuperSetup != NULL)
	{
		for (int i=0;i<m_buttonKosuu;i++)
		{
			ENDDELETECLASS(m_ppSuperSetup[i]);
		}
		DELETEARRAY(m_ppSuperSetup);
	}

	if (m_ppButton != NULL)
	{
		for (int i=0;i<m_buttonKosuu;i++)
		{
			ENDDELETECLASS(m_ppButton[i]);
		}
		DELETEARRAY(m_ppButton);
	}

//	DELETEARRAY(m_pExistFlag);
//	DELETEARRAY(m_pEnableFlag);
}


void CCommonButtonGroup::SetPicture(int n,CPicture* lpPic)
{
	CCommonButton* button = m_ppButton[n];
	if (button != NULL)
	{
		button->SetPicture(lpPic);
	}
}


CPicture* CCommonButtonGroup::GetPicture(int n)
{
	CCommonButton* button = m_ppButton[n];
	if (button != NULL)
	{
		return button->GetPicture();
	}

	return NULL;
}

LPSTR CCommonButtonGroup::GetFileName(int n)
{
	CCommonButton* button = m_ppButton[n];
	if (button != NULL)
	{
		return button->GetFileName();
	}

	return NULL;
}

void CCommonButtonGroup::SetFileName(int n,LPSTR filename)
{
	CCommonButton* button = m_ppButton[n];
	if (button != NULL)
	{
		button->SetFileName(filename);
	}

	return;
}


void CCommonButtonGroup::Init(void)
{
	m_status = 0;
	m_buttonNumber = -1;

	for (int i=0;i<m_buttonKosuu;i++)
	{
		CCommonButton* button = m_ppButton[i];
		if (button != NULL)
		{
			button->Init();
		}
	}
}


int CCommonButtonGroup::Calcu(CInputStatus* lpInput)
{
	if (m_superMode)
	{
		return CalcuSuper(lpInput);
	}

	return NNNBUTTON_NOTHING;
}



int CCommonButtonGroup::CalcuSuper(CInputStatus* lpInput)
{
	if (m_status != 0)
	{
		for (int i=0;i<m_buttonKosuu;i++)
		{
			if (i != m_buttonNumber)
			{
				CCommonButton* button = m_ppButton[i];
				if (button != NULL)
				{
					button->Calcu(NULL);
				}
			}
		}

		CCommonButton* button = m_ppButton[m_buttonNumber];
		if (button != NULL)
		{
			int rt = button->Calcu(lpInput);	//NULL‚Å‚à‚¢‚¢‚©?

			int st = rt & NNNBUTTON_STATUSMASK;
			if (st == NNNBUTTON_NUMBER)
			{
//				ChangePage(m_buttonNumber);
				int rt2 = CCommonButton::ChangeButtonData(rt,m_buttonNumber);
				return rt2;
			}

			return rt;
		}

		//error
		return NNNBUTTON_NOTHING;
	}

	int returnCode = NNNBUTTON_NOTHING;

	for (int i=0;i<m_buttonKosuu;i++)
	{
		CCommonButton* button = m_ppButton[i];
		if (button != NULL)
		{
			if (m_status == 0)
			{
				int rt = button->Calcu(lpInput);

				if (rt != NNNBUTTON_NOTHING)
				{
					int st = rt & NNNBUTTON_STATUSMASK;

					if (st == NNNBUTTON_STARTCLICK)
					{
						m_status = 1;
						m_buttonNumber = i;
						returnCode = CCommonButton::ChangeButtonData(rt,m_buttonNumber);
					}
					else if (st == NNNBUTTON_NUMBER)
					{
						m_status = 1;
						m_buttonNumber = i;
						returnCode = CCommonButton::ChangeButtonData(rt,m_buttonNumber);
					}
					else
					{
						returnCode = rt;//sound etc
					}

					if ((st == NNNBUTTON_ENTER) || (st == NNNBUTTON_EXIT))
					{
						if (0)
//						if (m_menuButtonSetup->GetMenuAnimeAdjustFlag())
						{
							for (int i=0;i<m_buttonKosuu;i++)
							{
								CCommonButton* button2 = m_ppButton[i];
								if (button2 != NULL)
								{
									button2->ResetAnimeCount();
								}
							}
						}
					}
				}
			}
			else
			{
				button->Calcu(NULL);
			}
		}
	}

	return returnCode;
}



void CCommonButtonGroup::Print(BOOL mustPrintFlag)
{
	for (int i=0;i<m_buttonKosuu;i++)
	{
		CCommonButton* button = m_ppButton[i];
		if (button != NULL)
		{
			if (button->GetExist())
			{
				button->Print(mustPrintFlag);
			}
		}
	}
}



POINT CCommonButtonGroup::GetZahyo(int n)
{
	POINT pt;
	pt.x = 0;
	pt.y = 0;
	CCommonButton* button = m_ppButton[n];
	if (button != NULL)
	{
		pt = button->GetZahyo();
	}
	return pt;
}

void CCommonButtonGroup::SetZahyo(int n,POINT pt)
{
	CCommonButton* button = m_ppButton[n];
	if (button != NULL)
	{
		button->SetZahyo(pt);
	}
}

void CCommonButtonGroup::SetCancelButton(int n,BOOL flg)
{
	CCommonButton* button = m_ppButton[n];
	if (button != NULL)
	{
		button->SetCancelButtonFlag(flg);
	}
}


void CCommonButtonGroup::SetExist(int n, BOOL flg)
{
	CCommonButton* button = m_ppButton[n];
	if (button != NULL)
	{
		button->SetExist(flg);
	}
}

void CCommonButtonGroup::SetEnable(int n, BOOL flg)
{
	CCommonButton* button = m_ppButton[n];
	if (button != NULL)
	{
		button->SetEnable(flg);
	}
}

void CCommonButtonGroup::ResetAnimeCount(void)
{
	for (int i=0;i<m_buttonKosuu;i++)
	{
		CCommonButton* button = m_ppButton[i];
		if (button != NULL)
		{
			if (button->GetExist())
			{
				button->ResetAnimeCount();
			}
		}
	}
}


/*_*/

