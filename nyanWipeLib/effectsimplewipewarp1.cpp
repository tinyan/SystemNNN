//
// effectsimplewipewarp1.cpp
//

#include <windows.h>
#include <Math.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeWarp1.h"

#include "allSimpleWipe.h"



CEffectSimpleWipeWarp1::CEffectSimpleWipeWarp1(CAllSimpleWipe* allWipe) : CEffectSimpleWipeCommon(allWipe)
{
}

CEffectSimpleWipeWarp1::~CEffectSimpleWipeWarp1()
{
	End();
}

void CEffectSimpleWipeWarp1::End(void)
{
}


void CEffectSimpleWipeWarp1::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint, POINT* lpEndPoint)
{
	if (ClipAndCheck(lpPicStart,lpPicEnd,count,countMax,lpStartPoint,lpEndPoint) == FALSE) return;


	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

//	int* src1 = (int*)(m_startPic->GetBuffer());
//	int* src2 = (int*)(m_endPic->GetBuffer());

//	int lPitch1 = m_startPicSize.cx * 4;
//	int lPitch2 = m_endPicSize.cx * 4;

	int* src1 = (int*)m_startBuffer;
	if (src1 == NULL) return;
	int* src2 = (int*)m_endBuffer;
	if (src2 == NULL) return;
	int lPitch1 = m_startPitch;
	int lPitch2 = m_endPitch;


	int* dst = CMyGraphics::GetScreenBuffer();

	int dv = m_countMax;
	if (dv < 1) dv = 1;
	int c = m_count;
	if (c>dv) c = dv;


	int rr = int(sqrt((double)((screenSizeX/2)*(screenSizeX/2) + (screenSizeY/2)*(screenSizeY/2))) + 1);
	int r = (c * rr) / dv;

//	int rx[MAXSCREENSIZEY];
	//int* rx = CEffectSimpleWipe::m_shapeWork;
	int* rx = m_allSimpleWipe->GetShapeWork();


	int centerX = screenSizeX / 2;
	int centerY = screenSizeY / 2;


	for (int i=0;i<screenSizeY;i++)
	{
		int y = i - centerY;
		int x2 = r*r - y*y;
		if (x2<=0)
		{
			rx[i] = 0;
		}
		else
		{
			int xx = (int)(sqrt((double)x2) + 0.5);
			if (xx>centerX) xx = centerX;
			rx[i] = xx;
		}
	}

	int* table = rx;

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

		mov ecx,screenSizeY
		mov eax,table
LOOP1:
		push ecx
		push eax
		push ebx
		push esi

		mov ecx,[eax]
		neg ecx
		add ecx,centerX

		push ecx

		cmp ecx,1
		js SKIP1
		xchg ebx,esi
		rep movsd
		xchg ebx,esi
SKIP1:
		mov ecx,[eax]
		add ecx,ecx
		cmp ecx,1
		js SKIP2
		rep movsd
SKIP2:

		pop ecx

		cmp ecx,1
		js SKIP3
		xchg ebx,esi
		rep movsd
		xchg ebx,esi
SKIP3:

		pop esi
		pop ebx
		add ebx,lPitch1
		add esi,lPitch2

		pop eax
		add eax,4
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

#endif

}


