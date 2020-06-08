//
//
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"


#include "nnnButtonStatus.h"

#include "myMouseStatus.h"
#include "inputStatus.h"

#include "commonButton.h"
#include "commonBackButton.h"
#include "commonUpdownButtonGroup.h"

#include "commonUpdownBack.h"

CCommonUpdownBack::CCommonUpdownBack(CCommonBackButton* lpBack,CCommonUpDownButtonGroup* lpUpDown)
{
	m_back = lpBack;
	m_updown = lpUpDown;
	m_clickingNumber = -1;
}


CCommonUpdownBack::~CCommonUpdownBack()
{
	End();
}

void CCommonUpdownBack::End(void)
{
}


void CCommonUpdownBack::Init(void)
{
	m_clickingNumber = -1;
	m_back->Init();
	m_updown->Init();
}


int CCommonUpdownBack::Calcu(CInputStatus* lpInput)
{
	int rt = NNNBUTTON_NOTHING;

	if (m_clickingNumber == -1)
	{
		rt = m_back->Calcu(lpInput);
	}
	else
	{
		if (m_clickingNumber == 0)
		{
			rt = m_back->Calcu(lpInput);
		}
		else
		{
			m_back->Calcu(NULL);
		}
	}

	if (rt != NNNBUTTON_NOTHING)
	{
		int st = CCommonButton::GetButtonStatus(rt);
		if (st == NNNBUTTON_NUMBER)
		{
			return CCommonButton::ChangeButtonData(rt,0);
		}

		if (st == NNNBUTTON_STARTCLICK)
		{
			m_clickingNumber = 0;
		}
	}


	int rt2 = NNNBUTTON_NOTHING;

	if (m_clickingNumber == -1)
	{
		rt2 = m_updown->Calcu(lpInput);

		int st = CCommonButton::GetButtonStatus(rt2);
		int nm = CCommonButton::GetButtonData(rt2);

		if (st == NNNBUTTON_NUMBER)
		{
			m_clickingNumber = -1;
			return CCommonButton::ChangeButtonData(rt2,nm+1);
		}

		if (st == NNNBUTTON_STARTCLICK)
		{
			rt = rt2;
			m_clickingNumber = nm+1;
		}
	}
	else
	{
		if ((m_clickingNumber == 1) || (m_clickingNumber == 2))
		{
			rt2 = m_updown->Calcu(lpInput);

			int st = CCommonButton::GetButtonStatus(rt2);
			int nm = CCommonButton::GetButtonData(rt2);

			if (st == NNNBUTTON_NUMBER)
			{
				m_clickingNumber = -1;
				return CCommonButton::ChangeButtonData(rt2,nm+1);
			}

			rt = rt2;
		}
		else
		{
			m_updown->Calcu(NULL);
		}
	}

	return rt;
}



void CCommonUpdownBack::Print(BOOL flg)
{
	m_updown->Print(flg);
	m_back->Print(flg);
}

void CCommonUpdownBack::AppearPrint(int count, int countMax, int type , POINT deltaPoint )
{
	m_updown->AppearPrint(count,countMax,type,deltaPoint);
	m_back->AppearPrint(count, countMax, type, deltaPoint);
}


void CCommonUpdownBack::SetPageMax(int pageMax)
{
	m_updown->SetPageMax(pageMax);
}

int CCommonUpdownBack::GetPageMax(void)
{
	return m_updown->GetPageMax();
}

void CCommonUpdownBack::SetPage(int page)
{
	m_updown->SetPage(page);
}

int CCommonUpdownBack::GetPage(void)
{
	return m_updown->GetPage();
}

void CCommonUpdownBack::ResetAnimeCount(void)
{
	m_updown->ResetAnimeCount();
	m_back->ResetAnimeCount();
}





/*_*/


