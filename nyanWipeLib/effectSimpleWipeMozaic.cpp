//
// effectsimplewipeMozaic.cpp
//

#include <windows.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeMozaic.h"

#include "allSimpleWipe.h"



CEffectSimpleWipeMozaic::CEffectSimpleWipeMozaic(CAllSimpleWipe* allWipe) : CEffectSimpleWipeCommon(allWipe)
{
}

CEffectSimpleWipeMozaic::~CEffectSimpleWipeMozaic()
{
	End();
}

void CEffectSimpleWipeMozaic::End(void)
{
}


void CEffectSimpleWipeMozaic::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint, POINT* lpEndPoint)
{
	if (ClipAndCheck(lpPicStart,lpPicEnd,count,countMax,lpStartPoint,lpEndPoint) == FALSE) return;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (countMax<1) countMax = 1;

	int limit = countMax / 2;
	if (limit<1) limit = 1;

	if (count >= limit)
	{
		count = countMax - count;
		if (count<0) count = 0;
		if (count>limit) count = limit;

		SwapPic();
	}

	if (count<0) count = 0;
	if (count>limit) count = limit;



	//ï™äÑêîÇÇ´ÇﬂÇÈ
	int bunkatsu = ((count +1) * 64) / limit;
	if (bunkatsu<1) bunkatsu = 1;
	if (bunkatsu>64) bunkatsu = 64;


	if (bunkatsu == 1)
	{
		m_startPic->Blt(0,0,m_startPoint.x,m_startPoint.y,screenSizeX,screenSizeY,FALSE);
		return;
	}



	int loopYOut = screenSizeY / bunkatsu;
	int yTotal = loopYOut * bunkatsu;
	int yAmari = screenSizeY - yTotal;

	if (yAmari > 0)
	{
		loopYOut++;
	}

	int loopXOut = screenSizeX / bunkatsu;
	int xTotal = loopXOut * bunkatsu;
	int xAmari = screenSizeX - xTotal;


	int* dst = CMyGraphics::GetScreenBuffer();

	int bunkatsu4 = bunkatsu * sizeof(int);

	int dstPitch = screenSizeX * sizeof(int);
	int dstPitch1 = dstPitch - bunkatsu4;
	int dstPitch2 = screenSizeX * sizeof(int) * bunkatsu;

//	int srcPitch = m_startPicSize.cx * sizeof(int);
	int srcPitch2 = m_startPicSize.cx * sizeof(int) * bunkatsu;

	int dstPitch1B = dstPitch - xAmari * sizeof(int);

	int* src = 	(int*)(m_startPic->GetBuffer());

	int rndX = 0;
	if (xAmari == 0)
	{
		rndX = rand() % bunkatsu;
	}
	else
	{
		rndX = rand() % xAmari;
	}

	int rndY = 0;
	if (yAmari == 0)
	{
		rndY = rand() % bunkatsu;
	}
	else
	{
		rndY = rand() % yAmari;
	}

	src += (m_startPoint.x + rndX) + (m_startPoint.y + rndY) * m_startPicSize.cx;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi
	
		cld

		mov esi,src
		mov edi,dst
		mov edx,loopYOut
LOOP1:
		push edx
		push esi
		push edi

		cmp edx,1
		mov edx,bunkatsu
		jnz SKIP1
		mov edx,yAmari
		or edx,edx
		jz EXIT1
SKIP1:




		mov ecx,loopXOut
LOOP3:
		push ecx
		push edx
		push edi

		mov eax,[esi]
LOOP4:
		mov ecx,bunkatsu
		rep stosd
		add edi,dstPitch1
		dec edx
		jnz LOOP4
		pop edi
		pop edx
		pop ecx
		add esi,bunkatsu4
		add edi,bunkatsu4
		dec ecx
		jnz LOOP3

		mov ecx,xAmari
		or ecx,ecx
		jz SKIP2

		push edx
		push edi
		mov eax,[esi]
LOOP4B:
		mov ecx,xAmari
		rep stosd
		add edi,dstPitch1B
		dec edx
		jnz LOOP4B
		pop edi
		pop edx
SKIP2:
		



EXIT1:
		pop edi
		pop esi
		pop edx
		add edi,dstPitch2
		add esi,srcPitch2
		dec edx
		jnz LOOP1

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}



}


