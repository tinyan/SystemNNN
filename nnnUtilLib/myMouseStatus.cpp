//
// myMouseStatus.cpp
//

#include <windows.h>
#include <winuser.h>
#include "myMouseStatus.h"


CMyMouseStatus::CMyMouseStatus()
{
	CheckButtonSwap();


}

CMyMouseStatus::~CMyMouseStatus()
{
	End();
}

void CMyMouseStatus::End(void)
{
}

void CMyMouseStatus::CheckButtonSwap(void)
{
	m_swapFlag = GetSystemMetrics(SM_SWAPBUTTON);
}

void CMyMouseStatus::SetStatus(LPMYMOUSESTRUCT lpMouse)
{
	m_mouseStatus = *lpMouse;
}

/*
BOOL CMyMouseStatus::CheckClick(BOOL trigFlag)
{
	int md = 0;
	if (trigFlag) md = 1;
	return CheckClick(md);
}
*/


BOOL CMyMouseStatus::CheckSkipClick(void)
{
	if (CheckClick(0)) return TRUE;
	if (CheckClick(1)) return TRUE;

	return FALSE;
}


//old routine
/*
BOOL CMyMouseStatus::CheckClick(int trigNumber)
{
	switch (trigNumber)
	{
	case 0:
		if (m_mouseStatus.trig1)
		{
			if (m_mouseStatus.trig1Mae == FALSE)
			{
				return TRUE;
			}
		}
		break;
	case 1:
		if (m_mouseStatus.trig2)
		{
			if (m_mouseStatus.trig2Mae == FALSE)
			{
				return TRUE;
			}
		}
		break;
	case 2:
		if (m_mouseStatus.trig3)
		{
			if (m_mouseStatus.trig3Mae == FALSE)
			{
				return TRUE;
			}
		}
		break;
	}

	return FALSE;
}
*/



BOOL CMyMouseStatus::CheckClick(int trigNumber)
{
	switch (trigNumber)
	{
	case 0:
		return m_mouseStatus.click1;
		break;
	case 1:
		return m_mouseStatus.click2;
		break;
	case 2:
		return m_mouseStatus.click3;
		break;
	}

	return FALSE;
}

POINT CMyMouseStatus::GetZahyo(void)
{
	POINT pt;
	pt.x = m_mouseStatus.mouseX;
	pt.y = m_mouseStatus.mouseY;

	return pt;
}


BOOL CMyMouseStatus::GetTrig(int trigNumber)
{
	switch (trigNumber)
	{
	case 0:
		return m_mouseStatus.trig1;
		break;
	case 1:
		return m_mouseStatus.trig2;
		break;
	case 2:
		return m_mouseStatus.trig3;
		break;
	}
	return FALSE;
}

BOOL CMyMouseStatus::GetTrigMae(int trigNumber)
{
	switch (trigNumber)
	{
	case 0:
		return m_mouseStatus.trig1Mae;
		break;
	case 1:
		return m_mouseStatus.trig2Mae;
		break;
	case 2:
		return m_mouseStatus.trig3Mae;
		break;
	}
	return FALSE;
}

int CMyMouseStatus::GetWheel(void)
{
	return m_mouseStatus.wheel;
}


void CMyMouseStatus::Init(BOOL generalInitFlag)
{
	m_mouseStatus.trig1Mae = TRUE;
	m_mouseStatus.trig2Mae = TRUE;
	m_mouseStatus.trig3Mae = TRUE;

	m_mouseStatus.click1 = FALSE;
	m_mouseStatus.click2 = FALSE;
	m_mouseStatus.click3 = FALSE;

	if (generalInitFlag)
	{
		m_mouseStatus.mouseX = 0;
		m_mouseStatus.mouseY = 0;
		m_mouseStatus.trig1 = FALSE;
		m_mouseStatus.trig2 = FALSE;
		m_mouseStatus.trig3 = FALSE;
		m_mouseStatus.wheel = 0;
		m_mouseStatus.shiftKey = FALSE;
		m_mouseStatus.ctrlKey = FALSE;
	}
}

void CMyMouseStatus::TrigToMae(void)
{
	m_mouseStatus.trig1Mae = m_mouseStatus.trig1;
	m_mouseStatus.trig2Mae = m_mouseStatus.trig2;
	m_mouseStatus.trig3Mae = m_mouseStatus.trig3;

	m_mouseStatus.click1 = FALSE;
	m_mouseStatus.click2 = FALSE;
	m_mouseStatus.click3 = FALSE;

	if (m_mouseStatus.trig1)
	{
		if (m_swapFlag == 0)
		{
			if ((GetAsyncKeyState(VK_LBUTTON) & 0x80000000) == 0)
			{
				m_mouseStatus.trig1 = FALSE;
			}
		}
		else
		{
			if ((GetAsyncKeyState(VK_RBUTTON) & 0x80000000) == 0)
			{
				m_mouseStatus.trig1 = FALSE;
			}
		}
	}


	if (m_mouseStatus.trig2)
	{
		if (m_swapFlag == 0)
		{
			if ((GetAsyncKeyState(VK_RBUTTON) & 0x80000000) == 0)
			{
				m_mouseStatus.trig2 = FALSE;
			}
		}
		else
		{
			if ((GetAsyncKeyState(VK_LBUTTON) & 0x80000000) == 0)
			{
				m_mouseStatus.trig2 = FALSE;
			}
		}
	}

	if (m_mouseStatus.trig3)
	{
		if ((GetAsyncKeyState(VK_MBUTTON) & 0x80000000) == 0)
		{
			m_mouseStatus.trig3 = FALSE;
		}
	}





}


void CMyMouseStatus::SetTrig(int n, BOOL flg)
{
	switch (n)
	{
	case 0:
		m_mouseStatus.trig1 = flg;
		if (flg)
		{
//			if (m_mouseStatus.trig1Mae == FALSE)
//			{
				m_mouseStatus.click1 = TRUE;
//			}
		}
		break;
	case 1:
		m_mouseStatus.trig2 = flg;
		if (flg)
		{
//			if (m_mouseStatus.trig2Mae == FALSE)
//			{
				m_mouseStatus.click2 = TRUE;
//			}
		}
		break;
	case 2:
		m_mouseStatus.trig3 = flg;
		if (flg)
		{
//			if (m_mouseStatus.trig3Mae == FALSE)
//			{
				m_mouseStatus.click3 = TRUE;
//			}
		}
		break;
	}
}


void CMyMouseStatus::SetTrigOnly(int n, BOOL flg)
{
	switch (n)
	{
	case 0:
		m_mouseStatus.trig1 = flg;
		if (flg)
		{
//			if (m_mouseStatus.trig1Mae == FALSE)
//			{
////				m_mouseStatus.click1 = TRUE;
//			}
		}
		break;
	case 1:
		m_mouseStatus.trig2 = flg;
		if (flg)
		{
//			if (m_mouseStatus.trig2Mae == FALSE)
//			{
////				m_mouseStatus.click2 = TRUE;
//			}
		}
		break;
	case 2:
		m_mouseStatus.trig3 = flg;
		if (flg)
		{
//			if (m_mouseStatus.trig3Mae == FALSE)
//			{
////				m_mouseStatus.click3 = TRUE;
//			}
		}
		break;
	}
}

void CMyMouseStatus::SetZahyo(int x, int y)
{
	m_mouseStatus.mouseX = x;
	m_mouseStatus.mouseY = y;
}

void CMyMouseStatus::SetWheel(int wheel)
{
	m_mouseStatus.wheel = wheel;
}


/*_*/

