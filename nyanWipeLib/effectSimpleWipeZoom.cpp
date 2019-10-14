//
// effectsimplewipeZoom.cpp					///移動タイプの共通クラスひながた。現時点ではshapeのコピーにすぎない
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeZoom.h"

#include "allSimpleWipe.h"

CEffectSimpleWipeZoom::CEffectSimpleWipeZoom(CAllSimpleWipe* allWipe,int scale,int placeType) : CEffectSimpleWipeCommon(allWipe)
{
	m_scale = scale;
	m_placeType = placeType;
//	SetEffectHoukou(houkou);
}


CEffectSimpleWipeZoom::~CEffectSimpleWipeZoom()
{
	End();
}

void CEffectSimpleWipeZoom::End(void)
{
}

/*
void CEffectSimpleWipeZoom::SetMoveType(int inOut,int houkou)
{
	m_houkou = houkou;
	m_inOut = inOut;
}
*/


void CEffectSimpleWipeZoom::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax, POINT* lpStartPoint, POINT* lpEndPoint)
{
	if (ClipAndCheck(lpPicStart,lpPicEnd,count,countMax,lpStartPoint,lpEndPoint) == FALSE) return;

	int c = m_count;
	int dv = m_countMax;
	if (dv<1) dv = 1;
	
	int limit = dv / 2;
	if (limit<1) limit = 1;

	if (c >= limit)
	{
		SwapPic();
		c = m_countMax - c;
		if (c > limit) c = limit;
	}

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int scale = 2 << (m_scale+1);

	int areaSizeX = screenSizeX / scale;
	int areaSizeY = screenSizeY / scale;

	int areaX1 = screenSizeX/2 - areaSizeX/2;
	int areaY1 = screenSizeY/2 - areaSizeY/2;
	int areaX2 = screenSizeX/2 + areaSizeX/2;
	int areaY2 = screenSizeY/2 + areaSizeY/2;


	int dx1 = areaX1 - 0;
	int dy1 = areaY1 - 0;
	int dx2 = areaX2 - screenSizeX;
	int dy2 = areaY2 - screenSizeY;


	int x1 = 0 + (dx1 * c) / limit;
	int y1 = 0 + (dy1 * c) / limit;

	int x2 = screenSizeX + (dx2 * c) / limit;
	int y2 = screenSizeY + (dy2 * c) / limit;


	if (x1<0) x1 = 0;
	if (y1<0) y1 = 0;
	if (x2>screenSizeX) x2 = screenSizeX;
	if (y2>screenSizeY) y2 = screenSizeY;



//	int startX = m_startPoint.x;
//	int startY = m_startPoint.y;

//	m_startPic->Blt(0,0,startX,startY,screenSizeX,y1,FALSE);
//	m_startPic->Blt(0,y2,startX,startY+y2,screenSizeX,screenSizeY-y2,FALSE);
//	m_startPic->Blt(0,y1,startX,startY+y1,x1,y2-y1,FALSE);
//	m_startPic->Blt(x2,y1,startX+x2,startY+y1,screenSizeX-x2,y2-y1,FALSE);


	int sizeX = x2 - x1;
	int sizeY = y2 - y1;
	if (sizeX<=0) return;
	if (sizeY<=0) return;

	int dltX = ((x2 - x1) * 65536) / screenSizeX;
	int dltY = ((y2 - y1) * 65536) / screenSizeY;

	int* screen = CMyGraphics::GetScreenBuffer();



	int srcPicSizeX = m_startPicSize.cx;
//	int srcPicSizeY = m_startPicSize.cy;
	int* srcPtr = (int*)m_startBuffer;

	srcPtr += x1;
	srcPtr += y1 * srcPicSizeX;

	int amariX = 0;
	int amariY = 0;

	int srcPitch = srcPicSizeX * 4;
	int dstPitch = screenSizeX * 4;

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

		mov esi,srcPtr
		mov edi,screen

		mov edx,screenSizeY
LOOP1:
		push edx
		push esi
		push edi
;

		mov edx,amariX
		mov ebx,dltX
		mov ecx,screenSizeX
LOOP2:
		mov eax,[esi]
		mov [edi],eax
;
		add edx,ebx
		mov eax,edx
		and edx,0ffffh
		shr eax,16
		shl eax,2
		add esi,eax
		add edi,4
		dec ecx
		jnz LOOP2
;
		pop edi
		pop esi

		mov eax,amariY
		and eax,0ffffh
		add eax,dltY
		mov amariY,eax
		shr eax,16
		mov edx,srcPitch
		mul edx
		add esi,eax

		pop edx
		add edi,dstPitch
		dec edx
		jnz LOOP1


		emms
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

