//
//
//

#include <windows.h>

//#include "..\nyanLib\include\commonMacro.h"


#include "myMouseStatus.h"
#include "myKeyStatus.h"

#include "inputStatus.h"

CInputStatus::CInputStatus()
{
	m_mouseStatus = NULL;
	m_keyStatus = NULL;
}

CInputStatus::~CInputStatus()
{
	End();
}

void CInputStatus::End(void)
{
}



/*_*/

