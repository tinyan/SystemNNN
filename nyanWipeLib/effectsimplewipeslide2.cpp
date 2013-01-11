//
// effectsimplewipeslide2.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeSlide2.h"

#include "allSimpleWipe.h"




CEffectSimpleWipeSlide2::CEffectSimpleWipeSlide2(CAllSimpleWipe* allWipe) : CEffectSimpleWipeCommon(allWipe)
{
}

CEffectSimpleWipeSlide2::~CEffectSimpleWipeSlide2()
{
	End();
}

void CEffectSimpleWipeSlide2::End(void)
{
}


void CEffectSimpleWipeSlide2::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint, POINT* lpEndPoint)
{
	if (ClipAndCheck(lpPicStart,lpPicEnd,count,countMax,lpStartPoint,lpEndPoint) == FALSE) return;


	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int* src1 = (int*)(m_startPic->GetBuffer());
	int* src2 = (int*)(m_endPic->GetBuffer());

	src1 += m_startPoint.x;
	src1 += m_startPoint.y * m_startPicSize.cx;

	src2 += m_endPoint.x;
	src2 += m_endPoint.y * m_endPicSize.cx;

	int lPitch1 = m_startPicSize.cx * 4;
	int lPitch2 = m_endPicSize.cx * 4;


	int* dst = CMyGraphics::GetScreenBuffer();

	if (countMax<1) countMax = 1;
	if (count>countMax) count = countMax;

	int start = ((countMax - count) * (screenSizeX+screenSizeY)) / countMax;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		cld

		mov ebx,src1
		mov esi,src2

		mov edi,dst

		mov ecx,screenSizeY
		mov eax,start
LOOP1:
		push ecx
		push eax
		push ebx
		push esi

		cmp eax,0
		jns SKIP1
		mov eax,0
SKIP1:
		cmp eax,screenSizeX
		jb SKIP2
		mov eax,screenSizeX
SKIP2:
		mov ecx,eax
		or ecx,ecx
		jz SKIP3
		xchg ebx,esi
		neg ecx
		add ecx,screenSizeX
		add ecx,ecx
		add ecx,ecx
		add esi,ecx
		mov ecx,eax
		rep movsd
		xchg ebx,esi
SKIP3:
		mov ecx,eax
		neg ecx
		add ecx,screenSizeX
		cmp ecx,1
		js SKIP4
		rep movsd
SKIP4:

		pop esi
		pop ebx
		add ebx,lPitch1
		add esi,lPitch2

		pop eax
		dec eax
		pop ecx
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


