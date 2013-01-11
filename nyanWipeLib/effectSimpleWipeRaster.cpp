//
// effectsimplewipeRaster.cpp
//

#include <windows.h>
#include <Math.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeRaster.h"

#include "allSimpleWipe.h"




CEffectSimpleWipeRaster::CEffectSimpleWipeRaster(CAllSimpleWipe* allWipe,int colorType) : CEffectSimpleWipeCommon(allWipe)
{
	m_colorType = colorType;
}


CEffectSimpleWipeRaster::~CEffectSimpleWipeRaster()
{
	End();
}

void CEffectSimpleWipeRaster::End(void)
{
}




void CEffectSimpleWipeRaster::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax, POINT* lpStartPoint, POINT* lpEndPoint)
{
	if (ClipAndCheck(lpPicStart,lpPicEnd,count,countMax,lpStartPoint,lpEndPoint) == FALSE) return;


//	int* startPtr = (int*)(m_startPic->GetBuffer());
//	int* endPtr = (int*)(m_endPic->GetBuffer());

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();



//	int startSrcPitch = m_startPicSize.cx * sizeof(int);
//	int endSrcPitch = m_endPicSize.cx * sizeof(int);


//	startPtr += m_startPoint.x;
//	startPtr += m_startPoint.y * m_startPicSize.cx;

//	endPtr += m_endPoint.x;
//	endPtr += m_endPoint.y * m_endPicSize.cx;
	int* startPtr = (int*)m_startBuffer;
	if (startPtr == NULL) return;

//	int* src2 = (int*)(m_endPic->GetBuffer());
	int* endPtr = (int*)m_endBuffer;
	if (endPtr == NULL) return;

//	int lPitch1 = m_startPicSize.cx * 4;
//	int lPitch2 = m_endPicSize.cx * 4;
	int startSrcPitch = m_startPitch;
	int endSrcPitch = m_endPitch;


	int loopX = screenSizeX;
	int loopY = screenSizeY;

	int* src = startPtr;
	int srcPitch = startSrcPitch;

	if (count >= countMax / 2)
	{
		src = endPtr;
		srcPitch = endSrcPitch;
	}
	
	//int* tablePtr = CEffectSimpleWipe::m_shapeWork;
	int* tablePtr = m_allSimpleWipe->GetShapeWork();

	//ラスター計算

	int c = m_count;
	int dv0 = m_countMax;
	if (dv0<1) dv0 = 1;
	if (c>dv0) c = dv0;



	double dv = (double)dv0;



	double ml = (double)screenSizeX;
	ml *= 0.9;

	if (c < countMax / 2)
	{
		ml *= c;
		ml /= (dv / 2);
	}
	else
	{
		ml *= (countMax - c);
		ml /= (dv / 2);
	}
	
	if (c >= countMax)
	{
		ml = 0.0;
	}
	
	double dScreenSizeY = (double)screenSizeY;

	for (int i=0;i<screenSizeY;i++)
	{
		double th = (double)(i + c * 10 );
		th *= (3.14159 * 2.0 / dScreenSizeY * 4);
		int d = (int)(cos(th)*ml+0.5);
		if (d <= -screenSizeX) d = -(screenSizeX-1);
		if (d >= screenSizeX) d = screenSizeX-1;
		
		tablePtr[i] = d;
	}


	int* dst = CMyGraphics::GetScreenBuffer();
	int dstPitch = screenSizeX * sizeof(int);

	int outMaskColor = 0xffffffff;
	if (m_colorType == 1) outMaskColor = 0;


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
		mov esi,src
		mov edi,dst
		mov ebx,tablePtr
LOOP1:
		push ecx
		push ebx
		push esi
		push edi

		mov ecx,[ebx]
		cmp ecx,0
		jns LEFT1

		neg ecx
		mov eax,[esi]
		and eax,outMaskColor
		rep stosd

		mov ecx,[ebx]
		add ecx,loopX
		rep movsd
		jmp NEXT1

LEFT1:
		mov eax,ecx
		add eax,eax
		add eax,eax
		add esi,eax
		neg ecx
		add ecx,loopX
		rep movsd
		mov ecx,[ebx]
		mov eax,[esi-4]
		and eax,outMaskColor
		rep stosd
NEXT1:

		pop edi
		pop esi
		pop ebx
		pop ecx
		add edi,dstPitch
		add esi,srcPitch
		add ebx,4
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




/*_*/

