//
// effectsimplewipeChecker.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"


#include "effectsimplewipecommon.h"
#include "effectsimplewipeChecker.h"
#include "allSimpleWipe.h"

//
//–¢ŽÀ‘•
//


CEffectSimpleWipeChecker::CEffectSimpleWipeChecker(CAllSimpleWipe* allWipe) : CEffectSimpleWipeCommon(allWipe)
{
}

CEffectSimpleWipeChecker::~CEffectSimpleWipeChecker()
{
	End();
}

void CEffectSimpleWipeChecker::End(void)
{
}


void CEffectSimpleWipeChecker::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint, POINT* lpEndPoint)
{
//	if (lpPicStart == NULL) return;
	if (lpPicEnd == NULL) return;


	if (lpPicStart != NULL)
	{
		if (lpPicStart->Check256()) return;
	}
	if (lpPicEnd->Check256()) return;

	int ps = (count * 100) / countMax;

	if (lpPicStart != NULL)
	{
		lpPicStart->Overrap(lpPicEnd,ps,lpStartPoint,lpEndPoint);
	}
	else
	{
		lpPicEnd->Overrap2(ps,lpEndPoint);
	}

	return;
}


