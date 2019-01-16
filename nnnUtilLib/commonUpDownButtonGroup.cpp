//
// UpDownButtonGroup.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\picture.h"


#include "nameList.h"
#include "nnnButtonStatus.h"
#include "myMouseStatus.h"

#include "commonbutton.h"


#include "commonUpDownButtonGroup.h"

//#include "scriptCallBack.h"
#include "superButtonSetup.h"

CCommonUpDownButtonGroup::CCommonUpDownButtonGroup(CNameList* lpSetup, CPicture* lpBG)
{
	Create("up","down",lpSetup,lpBG);
}

CCommonUpDownButtonGroup::CCommonUpDownButtonGroup(LPSTR upName, LPSTR downName,CNameList* lpSetup, CPicture* lpBG)
{
	Create(upName, downName, lpSetup, lpBG);
}

void CCommonUpDownButtonGroup::Create(LPSTR upName, LPSTR downName, CNameList* lpSetup, CPicture* lpBG)
{
	m_buttonKosuu = 2;

	int i = 0;
	for (i=0;i<m_buttonKosuu;i++)
	{
		m_button[i] = new CCommonButton();
	}

	m_superMode = 1;

//	m_updownSetup[0] = new CSuperButtonSetup(lpSetup,"up");
//	m_updownSetup[1] = new CSuperButtonSetup(lpSetup,"down",m_updownSetup[0],NULL);
	m_updownSetup[0] = new CSuperButtonSetup(lpSetup,upName);
	m_updownSetup[1] = new CSuperButtonSetup(lpSetup,downName,m_updownSetup[0],NULL);

	for (i=0;i<m_buttonKosuu;i++)
	{
		m_updownSetup[i]->SetupButtonStatus(m_button[i]);
		if (lpBG != NULL) m_button[i]->SetBG(lpBG);

	}
	int rev = m_updownSetup[0]->GetUpDownReverseFlag();
	m_button[0]->SetUpButtonFlag(TRUE,rev);
	rev = m_updownSetup[1]->GetUpDownReverseFlag();
	m_button[1]->SetDownButtonFlag(TRUE,rev);

	for (i=0;i<m_buttonKosuu;i++)
	{
		m_existFlag[i] = TRUE;
		m_enableFlag[i] = TRUE;
	}


	m_page = 0;
	m_pageMax = 2;
	m_status = 0;
	m_buttonNumber = -1;
}



CCommonUpDownButtonGroup::~CCommonUpDownButtonGroup()
{
	End();
}


void CCommonUpDownButtonGroup::End(void)
{
	int i = 0;
	for (i=0;i<m_buttonKosuu;i++)
	{
		ENDDELETECLASS(m_updownSetup[i]);
	}

	for (i=0;i<m_buttonKosuu;i++)
	{
		ENDDELETECLASS(m_button[i]);
	}
}


int CCommonUpDownButtonGroup::GetPage(void)
{
	return m_page;
}

void CCommonUpDownButtonGroup::SetPage(int page)
{
	m_page = page;
	AdjustPage();
}

void CCommonUpDownButtonGroup::SetPageMax(int pageMax)
{
	m_pageMax = pageMax;
	AdjustPage();
}

void CCommonUpDownButtonGroup::SetPicture(int n,CPicture* lpPic)
{
	CCommonButton* button = m_button[n];
	if (button != NULL)
	{
		button->SetPicture(lpPic);
	}
}


CPicture* CCommonUpDownButtonGroup::GetPicture(int n)
{
	CCommonButton* button = m_button[n];
	if (button != NULL)
	{
		return button->GetPicture();
	}

	return NULL;
}

LPSTR CCommonUpDownButtonGroup::GetFileName(int n)
{
	CCommonButton* button = m_button[n];
	if (button != NULL)
	{
		return button->GetFileName();
	}

	return NULL;
}


void CCommonUpDownButtonGroup::AdjustPage(void)
{
	if (m_page >= m_pageMax) m_page = m_pageMax - 1;
	if (m_page<0) m_page = 0;
}

void CCommonUpDownButtonGroup::Init(void)
{
	m_status = 0;
	m_buttonNumber = -1;
	AdjustPage();

	for (int i=0;i<m_buttonKosuu;i++)
	{
		CCommonButton* button = m_button[i];
		if (button != NULL)
		{
			button->Init();
		}
	}
}


int CCommonUpDownButtonGroup::Calcu(CInputStatus* lpInput)
{
	if (m_superMode)
	{
		return CalcuSuper(lpInput);
	}

	return NNNBUTTON_NOTHING;
}



int CCommonUpDownButtonGroup::CalcuSuper(CInputStatus* lpInput)
{
	if (m_status != 0)
	{
		for (int i=0;i<m_buttonKosuu;i++)
		{
			if (i != m_buttonNumber)
			{
				CCommonButton* button = m_button[i];
				if (button != NULL)
				{
					button->Calcu(NULL);
				}
			}
		}

		CCommonButton* button = m_button[m_buttonNumber];
		if (button != NULL)
		{
			int rt = button->Calcu(lpInput);	//NULL‚Å‚à‚¢‚¢‚©?

			int st = rt & NNNBUTTON_STATUSMASK;
			if (st == NNNBUTTON_NUMBER)
			{
				ChangePage(m_buttonNumber);
				int rt2 = CCommonButton::ChangeButtonData(rt,m_page);
				return rt2;
			}

			return rt;
		}

		//error
		return NNNBUTTON_NOTHING;
	}

	int returnCode = NNNBUTTON_NOTHING;

	CalcuAppear();

	for (int i=0;i<m_buttonKosuu;i++)
	{
		CCommonButton* button = m_button[i];
		if ((button != NULL) && m_appearFlag[i])
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
						ChangePage(m_buttonNumber);
						returnCode = CCommonButton::ChangeButtonData(rt,m_page);
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
								CCommonButton* button2 = m_button[i];
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


void CCommonUpDownButtonGroup::CalcuAppear(void)
{
	m_appearFlag[0] = TRUE;
	m_appearFlag[1] = TRUE;
	if (1)
	{
		if ((m_page==0) || (m_pageMax <= 1)) m_appearFlag[0] = FALSE;
		if ((m_page>=m_pageMax-1) || (m_pageMax <= 1)) m_appearFlag[1] = FALSE;
	}
}



void CCommonUpDownButtonGroup::Print(BOOL mustPrintFlag)
{
	CalcuAppear();

	for (int i=0;i<m_buttonKosuu;i++)
	{
		CCommonButton* button = m_button[i];
		if (button != NULL)
		{
			if (button->GetExist())
			{
				if (m_appearFlag[i])
				{
					button->Print(mustPrintFlag);
				}
			}
		}
	}
}



void CCommonUpDownButtonGroup::SetUpDownZahyo(int upPrintX, int upPrintY, int downPrintX, int downPrintY)
{
	POINT pt;
	pt.x = upPrintX;
	pt.y = upPrintY;
	m_button[0]->SetZahyo(pt);
	pt.x = downPrintX;
	pt.y = downPrintY;
	m_button[1]->SetZahyo(pt);
}


void CCommonUpDownButtonGroup::ChangePage(int btn)
{
	if (btn == 0)
	{
		m_page--;
	}
	else if (btn == 1)
	{
		m_page++;
	}
	AdjustPage();

	m_status = 0;
	for (int i=0;i<2;i++)
	{
		CCommonButton* button = m_button[i];
		if (button != NULL)
		{
			button->Init();
		}
	}
}

void CCommonUpDownButtonGroup::SetBG(CPicture* lpBG,int n)
{
	int st = n;
	int ed = n;
	if (n == -1)
	{
		st = 0;
		ed = 1;
	}

	for (int i=st;i<=ed;i++)
	{
		m_button[i]->SetBG(lpBG);
	}
}


void CCommonUpDownButtonGroup::ResetAnimeCount(void)
{
	for (int i=0;i<2;i++)
	{
		CCommonButton* button = m_button[i];
		if (button != NULL)
		{
			button->ResetAnimeCount();
		}
	}
}


POINT CCommonUpDownButtonGroup::GetUpZahyo(void)
{
	if (m_button[0] == NULL)
	{
		POINT pt;
		pt.x = 0;
		pt.y = 0;
		return pt;
	}

	return m_button[0]->GetZahyo();
}


POINT CCommonUpDownButtonGroup::GetDownZahyo(void)
{
	if (m_button[1] == NULL)
	{
		POINT pt;
		pt.x = 0;
		pt.y = 0;
		return pt;
	}

	return m_button[1]->GetZahyo();
}

void CCommonUpDownButtonGroup::ClearAccelKey(void)
{
	for (int i = 0; i < 2; i++)
	{
		m_button[i]->ClearAccelKey();
		m_button[i]->SetUpButtonFlag(FALSE);
		m_button[i]->SetDownButtonFlag(FALSE);
	}
}


/*_*/

