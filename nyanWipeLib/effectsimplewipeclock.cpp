//
// effectsimplewipeclock.cpp
//

#include <windows.h>
#include <Math.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectsimplewipecommon.h"
#include "effectsimplewipeShape.h"
#include "effectsimplewipeClock.h"
#include "allSimpleWipe.h"



CEffectSimpleWipeClock::CEffectSimpleWipeClock(CAllSimpleWipe* allWipe) : CEffectSimpleWipeShape(allWipe)
{
	SetMaxDivide(4);
}

CEffectSimpleWipeClock::~CEffectSimpleWipeClock()
{
	End();
}

void CEffectSimpleWipeClock::End(void)
{
}

void CEffectSimpleWipeClock::CalcuShapeWork(int count, int countMax)
{
	if (countMax<1) countMax = 1;
	if (count>countMax) count = countMax;

	double th = (double)count;
	th *= 3.14159 * 2;
	th /= (double)countMax;
//	th -= 3.14159/2;

	double tanTH = 0.0;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (count == countMax /4)
	{
		tanTH = screenSizeX/2+1;
	}
	else if (count == countMax * 3 / 4)
	{
		tanTH = -(screenSizeX/2+1);
	}
	else
	{
		tanTH = tan(th);
	}

	int* xtable = m_allSimpleWipe->GetShapeWork();

	int centerX = screenSizeX / 2;
	int centerY = screenSizeY / 2;

	if (count == 0)
	{
		for (int i=0;i<screenSizeY;i++)
		{
			xtable[i*4] = screenSizeX;
			xtable[i*4+1] = 0;
			xtable[i*4+2] = 0;
			xtable[i*4+3] = 0;
		}
		return;
	}

	if (count == countMax)
	{
		for (int i=0;i<screenSizeY;i++)
		{
			xtable[i*4] = 0;
			xtable[i*4+1] = screenSizeX;
			xtable[i*4+2] = 0;
			xtable[i*4+3] = 0;
		}
		return;
	}


	for (int j=0;j<screenSizeY;j++)
	{
		double d = (double)(j-centerY);
		d *= tanTH;
		if (d<0) d *= -1;

		int x = (int)(d + 0.5);

		if (count <= countMax / 4)
		{
			if (j<=centerY)
			{
				if (x>centerX) x = centerX;
				xtable[j*4] = centerX;
				xtable[j*4+1] = x;
				int ax = centerX - x;
				if (ax<0) ax = 0;
				xtable[j*4+2] = ax;
			}
			else
			{
				xtable[j*4] = screenSizeX;
				xtable[j*4+1] = 0;
				xtable[j*4+2] = 0;
			}
			xtable[j*4+3] = 0;
		}
		else if (count <= countMax / 2)
		{
			if (j<=centerY)
			{
				xtable[j*4] = centerX;
				xtable[j*4+1] = centerX;
			}
			else
			{
				if (x>centerX) x = centerX;
				xtable[j*4+0] = centerX+x;
				int ax = centerX - x;
				if (ax<0) ax = 0;
				xtable[j*4+1] = ax;
			}
			xtable[j*4+2] = 0;
			xtable[j*4+3] = 0;
		}
		else if (count <= countMax*3 / 4)
		{
			if (j<=centerY)
			{
				xtable[j*4] = centerX;
				xtable[j*4+1] = centerX;
			}
			else
			{
				if (x>centerX) x = centerX;
				xtable[j*4+0] = centerX-x;
				int ax = centerX + x;
				if (ax>screenSizeX) ax = screenSizeX;
				xtable[j*4+1] = ax;
			}
			xtable[j*4+2] = 0;
			xtable[j*4+3] = 0;
		}
		else
		{
			if (j<=centerY)
			{
				if (x>centerX) x = centerX;

				xtable[j*4+0] = 0;
				int ax = centerX - x;
				if (ax<0) ax = 0;
				xtable[j*4+1] = ax;
				xtable[j*4+2] = x;
				xtable[j*4+3] = centerX;
			}
			else
			{
				xtable[j*4+0] = 0;
				xtable[j*4+1] = screenSizeX;
				xtable[j*4+2] = 0;
				xtable[j*4+3] = 0;
			}
		}
	}

}

/*
void CEffectSimpleWipeClock::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint, POINT* lpEndPoint)
{
	if (lpPicStart->Check256()) return;
	if (lpPicEnd->Check256()) return;

	int screenSizeX = CPicture::m_screenSizeX;
	int screenSizeY = CPicture::m_screenSizeY;

	int* src1 = (int*)(lpPicStart->GetBuffer());
	if (src1 == NULL) return;

	int* src2 = (int*)(lpPicEnd->GetBuffer());
	if (src2 == NULL) return;

	RECT rc;
	lpPicStart->GetPicSize(&rc);
	int lPitch1 = rc.right * 4;

	RECT rc2;
	lpPicEnd->GetPicSize(&rc2);
	int lPitch2 = rc2.right * 4;

	int* dst = (int*)CPicture::m_lpScreenBuffer;

	if (countMax<1) countMax = 1;
	if (count>countMax) count = countMax;

	double th = (double)count;
	th *= 3.14159 * 2;
	th /= (double)countMax;
//	th -= 3.14159/2;

	double tanTH = 0.0;



	if (count == countMax /4)
	{
		tanTH = screenSizeX/2+1;
	}
	else if (count == countMax * 3 / 4)
	{
		tanTH = -(screenSizeX/2+1);
	}
	else
	{
		tanTH = tan(th);
	}

//	int xtable[MAXSCREENSIZEY*4];
	int* xtable = CEffectSimpleWipe::m_shapeWork;


	int centerX = screenSizeX / 2;
	int centerY = screenSizeY / 2;

	for (int j=0;j<screenSizeY;j++)
	{
		double d = (double)(j-centerY);
		d *= tanTH;
		if (d<0) d *= -1;

		int x = (int)(d + 0.5);

		if (count <= countMax / 4)
		{
			if (j<=centerY)
			{
				if (x>centerX) x = centerX;
				xtable[j*4] = centerX;
				xtable[j*4+1] = x;
				int ax = centerX - x;
				if (ax<0) ax = 0;
				xtable[j*4+2] = ax;
				xtable[j*4+3] = 0;
			}
			else
			{
				xtable[j*4] = screenSizeX;
				xtable[j*4+1] = 0;
				xtable[j*4+2] = 0;
				xtable[j*4+3] = 0;
			}
		}
		else if (count <= countMax / 2)
		{
			if (j<=centerY)
			{
				xtable[j*4] = centerX;
				xtable[j*4+1] = centerX;
				xtable[j*4+2] = 0;
				xtable[j*4+3] = 0;
			}
			else
			{
				if (x>centerX) x = centerX;
				xtable[j*4+0] = centerX+x;
				int ax = centerX - x;
				if (ax<0) ax = 0;
				xtable[j*4+1] = ax;
				xtable[j*4+2] = 0;
				xtable[j*4+3] = 0;
			}
		}
		else if (count <= countMax*3 / 4)
		{
			if (j<=centerY)
			{
				xtable[j*4] = centerX;
				xtable[j*4+1] = centerX;
				xtable[j*4+2] = 0;
				xtable[j*4+3] = 0;
			}
			else
			{
				if (x>centerX) x = centerX;
				xtable[j*4+0] = centerX-x;
				int ax = centerX + x;
				if (ax>screenSizeX) ax = screenSizeX;
				xtable[j*4+1] = ax;
				xtable[j*4+2] = 0;
				xtable[j*4+3] = 0;
			}
		}
		else
		{
			if (j<=centerY)
			{
				if (x>centerX) x = centerX;

				xtable[j*4+0] = 0;
				int ax = centerX - x;
				if (ax<0) ax = 0;
				xtable[j*4+1] = ax;
				xtable[j*4+2] = x;
				xtable[j*4+3] = centerX;
			}
			else
			{
				xtable[j*4+0] = 0;
				xtable[j*4+1] = screenSizeX;
				xtable[j*4+2] = 0;
				xtable[j*4+3] = 0;
			}
		}
	}

	if (count == 0)
	{
		for (int i=0;i<screenSizeY;i++)
		{
			xtable[i*4] = screenSizeX;
			xtable[i*4+1] = 0;
			xtable[i*4+2] = 0;
			xtable[i*4+3] = 0;
		}
	}
	if (count == countMax)
	{
		for (int i=0;i<screenSizeY;i++)
		{
			xtable[i*4] = 0;
			xtable[i*4+1] = screenSizeX;
			xtable[i*4+2] = 0;
			xtable[i*4+3] = 0;
		}
	}


	int* table = xtable;

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
		or ecx,ecx
		jz SKIP1
		add esi,ecx
		add esi,ecx
		add esi,ecx
		add esi,ecx
		xchg ebx,esi
		rep movsd
		xchg ebx,esi
SKIP1:

		mov ecx,[eax+4]
		or ecx,ecx
		jz SKIP2
		add ebx,ecx
		add ebx,ecx
		add ebx,ecx
		add ebx,ecx
		rep movsd
SKIP2:
		mov ecx,[eax+8]
		or ecx,ecx
		jz SKIP3
		add esi,ecx
		add esi,ecx
		add esi,ecx
		add esi,ecx
		xchg ebx,esi
		rep movsd
		xchg ebx,esi
SKIP3:

		mov ecx,[eax+12]
		or ecx,ecx
		jz SKIP4
		add ebx,ecx
		add ebx,ecx
		add ebx,ecx
		add ebx,ecx
		rep movsd
SKIP4:


		pop esi
		pop ebx
		add ebx,lPitch1
		add esi,lPitch2

		pop eax
		add eax,4*4
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
*/


