//
// effectsimplewipecurtain2.cpp
//

#include <windows.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeCurtain2.h"

#include "allSimpleWipe.h"



CEffectSimpleWipeCurtain2::CEffectSimpleWipeCurtain2(CAllSimpleWipe* allWipe) : CEffectSimpleWipeCommon(allWipe)
{
}

CEffectSimpleWipeCurtain2::~CEffectSimpleWipeCurtain2()
{
	End();
}

void CEffectSimpleWipeCurtain2::End(void)
{
}


void CEffectSimpleWipeCurtain2::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint, POINT* lpEndPoint)
{
	if (ClipAndCheck(lpPicStart,lpPicEnd,count,countMax,lpStartPoint,lpEndPoint) == FALSE) return;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int* src1 = (int*)m_startBuffer;
	if (src1 == NULL) return;
	int* src2 = (int*)m_endBuffer;
	if (src2 == NULL) return;
	int lPitch1 = m_startPitch;
	int lPitch2 = m_endPitch;

	int* dst = CMyGraphics::GetScreenBuffer();

	int blockKosuu = ((screenSizeY+31) / (16*2));

	int dv = m_countMax;
	if (dv < 1) dv = 1;

	int k = (m_count * (blockKosuu + 8*2)) / dv;

	int completeCount = (k-15);
	if (completeCount<0) completeCount = 0;
	if (completeCount>blockKosuu) completeCount = blockKosuu;

	int yetCount = blockKosuu - k;
	if (yetCount<0) yetCount = 0;

	int curtainCount = blockKosuu - completeCount - yetCount;
	if (curtainCount<0)
	{
		curtainCount = 0;
#if defined _DEBUG
		OutputDebugString("Error in Curtain2()");
#endif
	}

	int startUp = k + 1;
	if (startUp > 15) startUp = 15;

	completeCount *= 16*2;
	yetCount *= 16*2;

	int yZahyo = 0;

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

		mov edx,completeCount
		or edx,edx
		jz SKIP1
LOOP1:
		mov ecx,yZahyo
		cmp ecx,screenSizeY
		jnb SKIP1

		push ebx
		push esi

		mov ecx,screenSizeX
		rep movsd

		pop esi
		pop ebx
		add ebx,lPitch1
		add esi,lPitch2

		mov ecx,yZahyo
		inc ecx
		mov yZahyo,ecx

		dec edx
		jnz LOOP1
SKIP1:




		mov eax,curtainCount
		or eax,eax
		jz SKIP2

		mov edx,startUp
LOOP2:

		mov ecx,2
LOOP20:
		push ecx
		push edx

		push edx
LOOP2A:
		mov ecx,yZahyo
		cmp ecx,screenSizeY
		jnb SKIP2A

		push ebx
		push esi
		mov ecx,screenSizeX
		rep movsd
		pop esi
		pop ebx
		add ebx,lPitch1
		add esi,lPitch2
		mov ecx,yZahyo
		inc ecx
		mov yZahyo,ecx
		dec edx
		jnz LOOP2A

SKIP2A:

		pop edx

		neg edx
		add edx,16
LOOP2B:
		mov ecx,yZahyo
		cmp ecx,screenSizeY
		jnb SKIP2B

		push ebx
		push esi
		mov ecx,screenSizeX
		mov esi,ebx
		rep movsd
		pop esi
		pop ebx
		add ebx,lPitch1
		add esi,lPitch2
		mov ecx,yZahyo
		inc ecx
		mov yZahyo,ecx
		dec edx
		jnz LOOP2B
SKIP2B:
		pop edx
		pop ecx
		dec ecx
		jnz LOOP20


		dec edx
		dec eax
		jnz LOOP2

SKIP2:


		mov edx,yetCount
		or edx,edx
		jz SKIP3
LOOP3:
		mov ecx,yZahyo
		cmp ecx,screenSizeY
		jnb SKIP3

		push ebx
		push esi

		mov ecx,screenSizeX
		mov esi,ebx
		rep movsd

		pop esi
		pop ebx
		add ebx,lPitch1
		add esi,lPitch2

		mov ecx,yZahyo
		inc ecx
		mov yZahyo,ecx

		dec edx
		jnz LOOP3
SKIP3:

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
}


