//
//
//


#include <windows.h>

#include "..\nyanlib\include\commonMacro.h"

#include "commonButton.h"

#include "commonMultiStateButton.h"
#include "commonRadioButton.h"

//CCommonRadioButton::CCommonRadioButton() : CCommonMultiStateButton(2)
//CCommonRadioButton::CCommonRadioButton()
CCommonRadioButton::CCommonRadioButton(CNameList* lpSetup,CPicture* lpBG,LPSTR buttonName,POINT* lpPoint,CSuperButtonSetup* lpSuperSetup) : CCommonMultiStateButton(lpSetup,lpBG,buttonName,2,lpPoint,lpSuperSetup,TRUE)
{

}



CCommonRadioButton::~CCommonRadioButton()
{
	End();
}


void CCommonRadioButton::End(void)
{
}




/*_*/

