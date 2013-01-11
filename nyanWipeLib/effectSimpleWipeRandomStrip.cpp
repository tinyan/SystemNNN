//
// effectsimplewipeRandomStrip.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeRandomStrip.h"

#include "allSimpleWipe.h"


CEffectSimpleWipeRandomStrip::CEffectSimpleWipeRandomStrip(CAllSimpleWipe* allWipe) : CEffectSimpleWipeCommon(allWipe)
{
}

CEffectSimpleWipeRandomStrip::~CEffectSimpleWipeRandomStrip()
{
	End();
}

void CEffectSimpleWipeRandomStrip::End(void)
{
}




void CEffectSimpleWipeRandomStrip::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax, POINT* lpStartPoint, POINT* lpEndPoint)
{
	if (ClipAndCheck(lpPicStart,lpPicEnd,count,countMax,lpStartPoint,lpEndPoint) == FALSE) return;

	int* startPtr = (int*)(m_startPic->GetBuffer());
	int* endPtr = (int*)(m_endPic->GetBuffer());

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (count<0) count = 0;
	if (countMax < 1) countMax = 1;	// div 0 error ‰ñ”ð
	if (count>countMax) count = countMax;


	int* randomStripTable = m_allSimpleWipe->GetShapeWork();

	int* ptr = randomStripTable;
	//make data
	for (int i=0;i<screenSizeY;i++)
	{
		int r = rand() % countMax;
		if (r < count)
		{
			*ptr = 1;
		}
		else
		{
			*ptr = 0;
		}
		ptr++;
	}


	int startSrcPitch = m_startPicSize.cx * sizeof(int);
	int endSrcPitch = m_endPicSize.cx * sizeof(int);

	int* dst = CMyGraphics::GetScreenBuffer();

	int dstPitch = screenSizeX * sizeof(int);


	startPtr += m_startPoint.x;
	startPtr += m_startPoint.y * m_startPicSize.cx;

	endPtr += m_endPoint.x;
	endPtr += m_endPoint.y * m_endPicSize.cx;

	int loopY = screenSizeY;
	int loopX = screenSizeX;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		cld

		mov esi,startPtr
		mov ebx,endPtr
		mov edx,randomStripTable
		mov edi,dst
		mov ecx,loopY
LOOP1:
		push ecx
		push edx
		push ebx
		push esi
		push edi

		mov eax,[edx]
		or eax,eax
		jz SKIP1
		mov esi,ebx
SKIP1:
		mov ecx,loopX
		rep movsd

		pop edi
		pop esi
		pop ebx
		pop edx
		pop ecx

		add edi,dstPitch
		add esi,startSrcPitch
		add ebx,endSrcPitch
		add edx,4
		dec ecx
		jnz LOOP1

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
}




/*_*/

