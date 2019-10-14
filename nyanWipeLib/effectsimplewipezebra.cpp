//
// effectsimplewipezebra.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeZebra.h"

#include "allSimpleWipe.h"


CEffectSimpleWipeZebra::CEffectSimpleWipeZebra(CAllSimpleWipe* allWipe) : CEffectSimpleWipeCommon(allWipe)
{
}

CEffectSimpleWipeZebra::~CEffectSimpleWipeZebra()
{
	End();
}

void CEffectSimpleWipeZebra::End(void)
{
}


void CEffectSimpleWipeZebra::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint, POINT* lpEndPoint)
{
	if (ClipAndCheck(lpPicStart,lpPicEnd,count,countMax,lpStartPoint,lpEndPoint) == FALSE) return;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int* src1 = (int*)(m_startPic->GetBuffer());
	int* src2 = (int*)(m_endPic->GetBuffer());

	int lPitch1 = m_startPicSize.cx * 4;
	int lPitch2 = m_endPicSize.cx * 4;

	int* dst = CMyGraphics::GetScreenBuffer();

	int halfScreenSizeY = screenSizeY / 2;

	int c = m_count;
	int dv = m_countMax;
	if (dv<1) dv = 1;
	if (c>dv) c = dv;

	int limitLine1 = (c * (screenSizeY/2)) / dv;
	int limitLine2 = (screenSizeY/2) - limitLine1;

#if defined _WIN64
#pragma message("‚±‚±‚Éc++ŽÀ‘•‚ª•K—v‚É‚á " __FILE__)

#else

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

		mov eax,halfScreenSizeY
LOOP1:
		push eax

		push esi
		cmp eax,limitLine1
		jb SKIP1
		mov esi,ebx
SKIP1:
		mov ecx,screenSizeX
		rep movsd

		pop esi
		add ebx,lPitch1
		add esi,lPitch2



		push esi
		cmp eax,limitLine2
		jnb SKIP2
		mov esi,ebx
SKIP2:
		mov ecx,screenSizeX
		rep movsd

		pop esi
		add ebx,lPitch1
		add esi,lPitch2


		pop eax
		dec eax
		jnz LOOP1


		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
#endif

}


