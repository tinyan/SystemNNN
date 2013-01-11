//
//
//


#include <windows.h>

#include "..\nyanlib\include\commonMacro.h"
#include "..\nyanlib\include\picture.h"

#include "namelist.h"


#include "commonButton.h"
#include "commonMultiStateButton.h"
#include "commonCheckButton.h"



CCommonCheckButton::CCommonCheckButton(CNameList* lpSetup,CPicture* lpBG,LPSTR buttonName,POINT* lpPoint,CSuperButtonSetup* lpSuperSetup) : CCommonMultiStateButton(lpSetup,lpBG,buttonName,2,lpPoint,lpSuperSetup)
{

}



CCommonCheckButton::~CCommonCheckButton()
{
	End();
}


void CCommonCheckButton::End(void)
{
}



/*_*/

