//
// wheelmouse.h
//


#if !defined __NYANLIB_WHEELMOUSE__
#define __NYANLIB_WHEELMOUSE__

#ifndef WM_MOUSEWHEEL
#include <zmouse.h>
#endif

        
class CWheelMouse
{
public:
	CWheelMouse();
	~CWheelMouse();
	UINT TranslateMessage(UINT msg);
	BOOL IsForward(WPARAM wparam);
	void End(void);

private:
	static UINT m_wm_message;
};

#endif

/*_*/


