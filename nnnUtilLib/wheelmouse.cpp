//
// wheelmouse.cpp
//


#include <windows.h>
#include <windowsx.h>
#include "wheelmouse.h"

#if _MSC_VER >= 1500

#ifdef UNICODE
#define MSH_MOUSEWHEEL L"MSWHEEL_ROLLMSG"
#else
#define MSH_MOUSEWHEEL "MSWHEEL_ROLLMSG"
#endif

#endif


//UINT CWheelMouse::m_wm_message = 0;

UINT CWheelMouse::m_wm_message = 
					(
						(
							(GetVersion() & 0x80000000) 
							&&
							LOBYTE(LOWORD(GetVersion()) == 4)
						)
						||
	   	   		       (!(GetVersion() & 0x80000000) && LOBYTE(LOWORD(GetVersion()) == 3))
					   )
                 ? RegisterWindowMessage(MSH_MOUSEWHEEL) : 0;

       


CWheelMouse::CWheelMouse()
{
}


CWheelMouse::~CWheelMouse()
{
	End();
}

void CWheelMouse::End(void)
{
}


UINT CWheelMouse::TranslateMessage(UINT msg)
{
	if(m_wm_message == msg) msg = WM_MOUSEWHEEL;
	return msg;
}

BOOL CWheelMouse::IsForward(WPARAM wparam)
{
	return ((short)HIWORD(wparam) < 0);
}
