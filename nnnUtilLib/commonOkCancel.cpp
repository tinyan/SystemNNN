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
//#include "commonUpdownButtonGroup.h"

#include "commonOkCancel.h"

CCommonOkCancel::CCommonOkCancel(CCommonButton* okButton,CCommonBackButton* lpBack)
{
	m_ok = okButton;
	m_back = lpBack;
	m_clickingNumber = -1;
}


CCommonOkCancel::~CCommonOkCancel()
{
	End();
}

void CCommonOkCancel::End(void)
{
}


void CCommonOkCancel::Init(void)
{
	m_clickingNumber = -1;
	m_ok->Init();
	m_back->Init();
}


int CCommonOkCancel::Calcu(CInputStatus* lpInput)
{
	int rt = NNNBUTTON_NOTHING;

	if (m_clickingNumber == -1)
	{
		rt = m_back->Calcu(lpInput);
	}
	else
	{
		if (m_clickingNumber == 1)
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
			return CCommonButton::ChangeButtonData(rt,1);
		}

		if (st == NNNBUTTON_STARTCLICK)
		{
			m_clickingNumber = 1;
		}
	}


	int rt2 = NNNBUTTON_NOTHING;

	if (m_clickingNumber == -1)
	{
		rt2 = m_ok->Calcu(lpInput);

		int st = CCommonButton::GetButtonStatus(rt2);
		int nm = CCommonButton::GetButtonData(rt2);

		if (st == NNNBUTTON_NUMBER)
		{
			m_clickingNumber = -1;
			return CCommonButton::ChangeButtonData(rt2,0);
		}

		if (st == NNNBUTTON_STARTCLICK)
		{
			rt = rt2;
			m_clickingNumber = 0;
		}
	}
	else
	{
		if (m_clickingNumber == 0)
		{
			rt2 = m_ok->Calcu(lpInput);

			int st = CCommonButton::GetButtonStatus(rt2);
			int nm = CCommonButton::GetButtonData(rt2);

			if (st == NNNBUTTON_NUMBER)
			{
				m_clickingNumber = -1;
				return CCommonButton::ChangeButtonData(rt2,0);
			}

			rt = rt2;
		}
		else
		{
			m_ok->Calcu(NULL);
		}
	}

	return rt;
}



void CCommonOkCancel::Print(BOOL flg)
{
	m_ok->Print(flg);
	m_back->Print(flg);
}



void CCommonOkCancel::ResetAnimeCount(void)
{
	m_ok->ResetAnimeCount();
	m_back->ResetAnimeCount();
}





/*_*/


