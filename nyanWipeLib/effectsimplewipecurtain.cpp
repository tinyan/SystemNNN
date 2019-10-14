//
// effectsimplewipecurtain.cpp
//

#include <windows.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeCurtain.h"

#include "allSimpleWipe.h"



CEffectSimpleWipeCurtain::CEffectSimpleWipeCurtain(CAllSimpleWipe* allWipe) : CEffectSimpleWipeCommon(allWipe)
{
}

CEffectSimpleWipeCurtain::~CEffectSimpleWipeCurtain()
{
	End();
}

void CEffectSimpleWipeCurtain::End(void)
{
}


void CEffectSimpleWipeCurtain::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint, POINT* lpEndPoint)
{
	if (ClipAndCheck(lpPicStart,lpPicEnd,count,countMax,lpStartPoint,lpEndPoint) == FALSE) return;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	//int* src1 = (int*)(m_startPic->GetBuffer());
	int* src1 = (int*)m_startBuffer;
	if (src1 == NULL) return;

//	int* src2 = (int*)(m_endPic->GetBuffer());
	int* src2 = (int*)m_endBuffer;
	if (src2 == NULL) return;

//	int lPitch1 = m_startPicSize.cx * 4;
//	int lPitch2 = m_endPicSize.cx * 4;
	int lPitch1 = m_startPitch;
	int lPitch2 = m_endPitch;


//	src1 += m_startPoint.x;
//	src1 += m_startPoint.y * m_startPicSize.cx;
//	src2 += m_endPoint.x;
//	src2 += m_endPoint.y * m_endPicSize.cx;

	int* dst = CMyGraphics::GetScreenBuffer();

	int blockKosuu = (screenSizeX / (16*2));

	int dv = m_countMax;
	if (dv<1) dv = 1;
	int k = (m_count * (blockKosuu + 8 * 2)) / dv;

	int completeCount = (k-15);
	if (completeCount<0) completeCount = 0;
	if (completeCount>blockKosuu) completeCount = blockKosuu;

	int yetCount = blockKosuu - k;
	if (yetCount<0) yetCount = 0;

	int curtainCount = blockKosuu - completeCount - yetCount;
	if (curtainCount<0)
	{
		curtainCount = 0;
		OutputDebugString("Error in Curtain()");
	}

	int startLeft = k + 1;
	if (startLeft > 15) startLeft = 15;

	completeCount *= 16*2;
	yetCount *= 16*2;

//	int allSrc1Skip = allSrc1Count * 4;

	int loopY = screenSizeY;
	int lPitch = screenSizeX * sizeof(int);

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

		mov ecx,loopY
LOOP1:
		push ecx
		push ebx
		push esi
		push edi

		mov ecx,completeCount
		or ecx,ecx
		jz SKIP1

		add ebx,ecx
		add ebx,ecx
		add ebx,ecx
		add ebx,ecx

		rep movsd
SKIP1:


		mov eax,curtainCount
		or eax,eax
		jz SKIP2
		mov edx,startLeft

LOOP2:
//1
		mov ecx,edx
		rep movsd
		add ebx,edx
		add ebx,edx
		add ebx,edx
		add ebx,edx

		mov ecx,edx
		neg ecx
		add ecx,16

		add esi,ecx
		add esi,ecx
		add esi,ecx
		add esi,ecx
		xchg ebx,esi
		rep movsd
		xchg ebx,esi
//2
		mov ecx,edx
		rep movsd
		add ebx,edx
		add ebx,edx
		add ebx,edx
		add ebx,edx

		mov ecx,edx
		neg ecx
		add ecx,16

		add esi,ecx
		add esi,ecx
		add esi,ecx
		add esi,ecx
		xchg ebx,esi
		rep movsd
		xchg ebx,esi

		dec edx
		dec eax
		jnz LOOP2
SKIP2:

		mov ecx,yetCount
		or ecx,ecx
		jz SKIP3

		mov esi,ebx
		rep movsd
SKIP3:

		pop edi
		pop esi
		pop ebx
		pop ecx
		add ebx,lPitch1
		add esi,lPitch2

		add edi,lPitch
		dec ecx
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


