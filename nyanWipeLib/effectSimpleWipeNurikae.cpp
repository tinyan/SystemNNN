//
// effectsimplewipeNurikae.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeNurikae.h"

#include "allSimpleWipe.h"

CEffectSimpleWipeNurikae::CEffectSimpleWipeNurikae(CAllSimpleWipe* allWipe) : CEffectSimpleWipeCommon(allWipe)
{
}

CEffectSimpleWipeNurikae::~CEffectSimpleWipeNurikae()
{
	End();
}

void CEffectSimpleWipeNurikae::End(void)
{
}




void CEffectSimpleWipeNurikae::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax, POINT* lpStartPoint, POINT* lpEndPoint)
{
	if (ClipAndCheck(lpPicStart,lpPicEnd,count,countMax,lpStartPoint,lpEndPoint) == FALSE) return;


	int* startPtr = (int*)(m_startPic->GetBuffer());
	int* endPtr = (int*)(m_endPic->GetBuffer());

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();



	if (count<0) count = 0;
	if (countMax < 1) countMax = 1;	// div 0 error 回避
	if (count>countMax) count = countMax;


	int startSrcPitch = m_startPicSize.cx * sizeof(int);
	int endSrcPitch = m_endPicSize.cx * sizeof(int);


	startPtr += m_startPoint.x;
	startPtr += m_startPoint.y * m_startPicSize.cx;

	endPtr += m_endPoint.x;
	endPtr += m_endPoint.y * m_endPicSize.cx;


	int loopY = screenSizeY;
	int nuriType = 0;


	int delta = ((screenSizeX * 2) * count) / countMax;
	if (delta<0) delta = 0;
	if (delta>screenSizeX*2)delta = screenSizeX * 2;

	int leftCount = 0;

	if (delta < screenSizeX)
	{
		nuriType = 0;
		leftCount = delta;
	}
	else
	{
		nuriType = 1;
		leftCount = delta - screenSizeX;
	}


	int* dst = CMyGraphics::GetScreenBuffer();
	int dstPitch = screenSizeX * sizeof(int);

	if (nuriType == 0)
	{
#if defined _WIN64
#pragma message("ここにc++実装が必要にゃ " __FILE__)

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

			mov ecx,loopY
			mov esi,startPtr
			mov edi,dst
LOOP1:
			push ecx
			push esi
			push edi

			mov ecx,leftCount
			or ecx,ecx
			jz SKIP1

			mov edx,ecx
			add edx,edx
			add edx,edx
			add esi,edx
			mov eax,[esi-4]
			rep stosd
SKIP1:
			mov ecx,leftCount
			neg ecx
			add ecx,screenSizeX
			or ecx,ecx
			jz SKIP1B
			rep movsd
SKIP1B:
			pop edi
			pop esi
			pop ecx
			add edi,dstPitch
			add esi,startSrcPitch
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
	else
	{
#if defined _WIN64
#pragma message("ここにc++実装が必要にゃ " __FILE__)

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

			mov ecx,loopY
			mov esi,endPtr
			mov edi,dst
LOOP2:
			push ecx
			push esi
			push edi

			mov ecx,leftCount
			or ecx,ecx
			jz SKIP2
			rep movsd
SKIP2:
			mov ecx,leftCount
			neg ecx
			add ecx,screenSizeX
			or ecx,ecx
			jz SKIP2B

			mov eax,[esi]
			rep stosd
SKIP2B:
			pop edi
			pop esi
			pop ecx
			add edi,dstPitch
			add esi,endSrcPitch
			dec ecx
			jnz LOOP2

			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax
		}
#endif

	}
}




/*_*/

