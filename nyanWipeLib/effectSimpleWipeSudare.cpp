//
// effectsimplewipeSudare.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeSudare.h"

#include "allSimpleWipe.h"


CEffectSimpleWipeSudare::CEffectSimpleWipeSudare(CAllSimpleWipe* allWipe,int houkou,int centerType) : CEffectSimpleWipeCommon(allWipe)
{
	m_centerType = centerType;
	SetEffectHoukou(houkou);
}

CEffectSimpleWipeSudare::~CEffectSimpleWipeSudare()
{
	End();
}

void CEffectSimpleWipeSudare::End(void)
{
}


void CEffectSimpleWipeSudare::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax, POINT* lpStartPoint, POINT* lpEndPoint)
{
	if (ClipAndCheck(lpPicStart,lpPicEnd,count,countMax,lpStartPoint,lpEndPoint) == FALSE) return;



	int c = m_count;
	int dv = m_countMax;
	if (dv<1) dv = 1;
	if (c>dv) c = dv;

	if (m_effectHoukou == 1)
	{
		SwapPic();
		c = m_countMax - c;
	}


	int* startPtr = (int*)(m_startPic->GetBuffer());
	int* endPtr = (int*)(m_endPic->GetBuffer());

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();




	int startSrcPitch = m_startPicSize.cx * sizeof(int);
	int endSrcPitch = m_endPicSize.cx * sizeof(int);

	int* dst = CMyGraphics::GetScreenBuffer();

	int dstPitch = screenSizeX * sizeof(int);


	startPtr += m_startPoint.x;
	startPtr += m_startPoint.y * m_startPicSize.cx;

	endPtr += m_endPoint.x;
	endPtr += m_endPoint.y * m_endPicSize.cx;


	//int* shapeWork = CEffectSimpleWipe::m_shapeWork;
	int* shapeWork = m_allSimpleWipe->GetShapeWork();

	for (int i=0;i<screenSizeY;i++)
	{
		shapeWork[i] = -1;
	}

	if (m_centerType == 0)
	{
		int kasokuMax = 8;
		int startLine = screenSizeY;
		startLine -= ((screenSizeY + screenSizeY / kasokuMax + kasokuMax) * c) / dv;

		int kasoku = 0;

		for (int j=0;j<startLine;j++)
		{
			if (j<screenSizeY) shapeWork[j] = j;
		}

		for (int j=startLine;j<screenSizeY;j++)
		{
			if ((startLine >= 0) && (startLine<screenSizeY))
			{
				if ((j>=0) && (j<screenSizeY))
				{
					shapeWork[startLine] = j;
				}
			}

			if (kasoku < kasokuMax) kasoku++;
			startLine += kasoku;
		}
	}
	else if (m_centerType == 1)
	{
		int kasokuMax = 8;
		int startLine = 0;
		startLine += ((screenSizeY + screenSizeY / kasokuMax + kasokuMax) * c) / dv;

		int kasoku = 0;

		for (int j=screenSizeY-1;j>=startLine;j--)
		{
			if (j>=0) shapeWork[j] = j;
		}

		for (int j=startLine;j>=0;j--)
		{
			if ((startLine >= 0) && (startLine<screenSizeY))
			{
				if ((j>=0) && (j<screenSizeY))
				{
					shapeWork[startLine] = j;
				}
			}

			if (kasoku < kasokuMax) kasoku++;
			startLine -= kasoku;
		}

	}
	else if (m_centerType == 2)
	{
		int kasokuMax = 8;
		int startLine = 0;
		startLine += (((screenSizeY + screenSizeY / kasokuMax + kasokuMax)/2) * c) / dv;

		int kasoku = 0;

		for (int j=screenSizeY/2-1;j>=startLine;j--)
		{
			if (j>=0) shapeWork[j] = j;
		}

		for (int j=startLine;j>=0;j--)
		{
			if ((startLine >= 0) && (startLine<screenSizeY/2))
			{
				if ((j>=0) && (j<screenSizeY/2))
				{
					shapeWork[startLine] = j;
				}
			}

			if (kasoku < kasokuMax) kasoku++;
			startLine -= kasoku;
		}





		startLine = screenSizeY;
		startLine -= (((screenSizeY + screenSizeY / kasokuMax + kasokuMax)/2) * c) / dv;

		kasoku = 0;

		for (int j=screenSizeY/2;j<startLine;j++)
		{
			if (j<screenSizeY) shapeWork[j] = j;
		}

		for (int j=startLine;j<screenSizeY;j++)
		{
			if ((startLine >= screenSizeY/2) && (startLine<screenSizeY))
			{
				if ((j>=screenSizeY/2) && (j<screenSizeY))
				{
					shapeWork[startLine] = j;
				}
			}

			if (kasoku < kasokuMax) kasoku++;
			startLine += kasoku;
		}

	}



	int loopX = screenSizeX;
	int loopY = screenSizeY;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		cld

		mov ebx,shapeWork
		mov esi,endPtr

		mov edi,dst
		mov edx,loopY

LOOP1:
		push edx
		push esi
		push edi

		mov eax,[ebx]
		cmp eax,-1
		jz NORMAL

		mov edx,startSrcPitch
		mul edx
		add eax,startPtr
		mov esi,eax
NORMAL:
		mov ecx,loopX
		rep movsd

		pop edi
		pop esi
		pop edx

		add ebx,4
		add edi,dstPitch
		add esi,endSrcPitch
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




/*_*/

