//
// effectsimplewipeMekuri.cpp
//

#include <windows.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeMekuri.h"

#include "allSimpleWipe.h"

CEffectSimpleWipeMekuri::CEffectSimpleWipeMekuri(CAllSimpleWipe* allWipe) : CEffectSimpleWipeCommon(allWipe)
{
}

CEffectSimpleWipeMekuri::~CEffectSimpleWipeMekuri()
{
	End();
}

void CEffectSimpleWipeMekuri::End(void)
{
}




void CEffectSimpleWipeMekuri::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax, POINT* lpStartPoint, POINT* lpEndPoint)
{
	if (ClipAndCheck(lpPicStart,lpPicEnd,count,countMax,lpStartPoint,lpEndPoint) == FALSE) return;

	int c = m_count;
	int dv = countMax;
	if (dv<1) dv = 1;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();






	int startSrcPitch = m_startPicSize.cx * sizeof(int);
	int endSrcPitch = m_endPicSize.cx * sizeof(int);

	int* dst = CMyGraphics::GetScreenBuffer();

	int dstPitch = screenSizeX * sizeof(int);



	int* startPtr = (int*)(m_startPic->GetBuffer());
	int* endPtr = (int*)(m_endPic->GetBuffer());

	startPtr += m_startPoint.x;
	startPtr += m_startPoint.y * m_startPicSize.cx;

	endPtr += m_endPoint.x;
	endPtr += m_endPoint.y * m_endPicSize.cx;


	int firstLoopY = (c * screenSizeY) / dv;
	if (firstLoopY<0) firstLoopY = 0;
	if (firstLoopY > screenSizeY) firstLoopY = screenSizeY;

	int secondLoopY = firstLoopY - 1;
	if (secondLoopY<0) secondLoopY = 0;
	if ((firstLoopY+secondLoopY) > screenSizeY)
	{
		secondLoopY = screenSizeY - firstLoopY;
		if (secondLoopY<0) secondLoopY = 0;
	}

	int thirdLoopY = screenSizeY - firstLoopY - secondLoopY;
	if (thirdLoopY<0) thirdLoopY = 0;

	startPtr += m_startPicSize.cx * (firstLoopY + secondLoopY);

	int loopX = screenSizeX;

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

		mov esi,endPtr
		mov edi,dst
		mov edx,firstLoopY
		or edx,edx
		jz SKIP1
LOOP1:
		push esi
		push edi
		mov ecx,loopX
		rep movsd
		pop edi
		pop esi
		add esi,endSrcPitch
		add edi,dstPitch
		dec edx
		jnz LOOP1
		sub esi,endSrcPitch
		sub esi,endSrcPitch
SKIP1:

		mov edx,secondLoopY
		or edx,edx
		jz SKIP2
LOOP2:
		push esi
		push edi
		mov ecx,loopX
		rep movsd
		pop edi
		pop esi
		sub esi,endSrcPitch
		add edi,dstPitch
		dec edx
		jnz LOOP2
SKIP2:
		
		mov edx,thirdLoopY
		mov esi,startPtr
		or edx,edx
		jz SKIP3
LOOP3:
		push esi
		push edi
		mov ecx,loopX
		rep movsd
		pop edi
		pop esi
		add esi,startSrcPitch
		add edi,dstPitch
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
#endif

}




/*_*/

