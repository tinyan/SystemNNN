//
// effectsimplewipeMulti.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeMulti.h"

#include "allSimpleWipe.h"


CEffectSimpleWipeMulti::CEffectSimpleWipeMulti(CAllSimpleWipe* allWipe) : CEffectSimpleWipeCommon(allWipe)
{
}

CEffectSimpleWipeMulti::~CEffectSimpleWipeMulti()
{
	End();
}

void CEffectSimpleWipeMulti::End(void)
{
}


void CEffectSimpleWipeMulti::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint, POINT* lpEndPoint)
{
	if (ClipAndCheck(lpPicStart,lpPicEnd,count,countMax,lpStartPoint,lpEndPoint) == FALSE) return;

	int* startPtr = (int*)(m_startPic->GetBuffer());
	int* endPtr = (int*)(m_endPic->GetBuffer());

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (count<0) count = 0;
	if (countMax < 1) countMax = 1;	// div 0 error ‰ñ”ð
	if (count>countMax) count = countMax;

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



	if (countMax < 1) countMax = 1;
	if (count<0) count = 0;
	if (count > countMax) count = countMax;



	int limit = countMax / 2;
	if (limit<1) limit = 1;

	if (count > limit)
	{
		count = countMax - count;
		int* tmpPtr = startPtr;
		startPtr = endPtr;
		endPtr = tmpPtr;
		int tmp = startSrcPitch;
		startSrcPitch = endSrcPitch;
		endSrcPitch = tmp;
	}


	int ps256 = (count * 256) / limit;
	if (ps256<0) ps256 = 0;
	if (ps256>256) ps256 = 256;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		pxor mm0,mm0

		mov eax,ps256
		movd mm5,eax
		punpcklwd mm5,mm5
		punpckldq mm5,mm5
		neg eax
		add eax,256
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6


		mov ebx,startPtr
		mov esi,endPtr
		mov edi,dst

		mov ecx,loopY
LOOP1:
		push ecx
		push ebx
		push esi
		push edi

		mov ecx,loopX
LOOP2:
		mov eax,[esi]
		movd mm1,eax
		mov eax,[ebx]
		movd mm2,eax
		punpcklbw mm1,mm0
		punpcklbw mm2,mm0
		pmullw mm1,mm2
		psrlw mm1,8
		pmullw mm2,mm6
		pmullw mm1,mm5
		add ebx,4
		add esi,4
		paddw mm1,mm2
		psrlw mm1,8
		packuswb mm1,mm1
		movd eax,mm1
		mov [edi],eax

		add edi,4
		dec ecx
		jnz LOOP2

		pop edi
		pop esi
		pop ebx
		pop ecx
		add ebx,startSrcPitch
		add esi,endSrcPitch
		add edi,dstPitch
		dec ecx
		jnz LOOP1
		emms

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}


	return;
}


