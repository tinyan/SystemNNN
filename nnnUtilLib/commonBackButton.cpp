//
//
//


#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"

#include "nameList.h"
#include "commonButton.h"
#include "commonBackButton.h"


CCommonBackButton::CCommonBackButton(CNameList* lpSetup,LPSTR buttonName,CPicture* lpBG) : CCommonButton(lpSetup,buttonName,lpBG)
{
	SetCancelButtonFlag();
}


CCommonBackButton::~CCommonBackButton()
{
	End();
}

void CCommonBackButton::End(void)
{
}


/*_*/



