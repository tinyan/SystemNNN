//
// effectsimplewipeRadical.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"

#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeRadical.h"

#include "allSimpleWipe.h"


//
// –¢ŽÀ‘•
//

CEffectSimpleWipeRadical::CEffectSimpleWipeRadical(CAllSimpleWipe* allWipe) : CEffectSimpleWipeCommon(allWipe)
{
}

CEffectSimpleWipeRadical::~CEffectSimpleWipeRadical()
{
	End();
}

void CEffectSimpleWipeRadical::End(void)
{
}


void CEffectSimpleWipeRadical::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint, POINT* lpEndPoint)
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


