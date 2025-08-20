//
// effectsimplewipeAdd.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanlib\include\myGraphics.h"
#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeAdd.h"

#include "allSimpleWipe.h"



CEffectSimpleWipeAdd::CEffectSimpleWipeAdd(CAllSimpleWipe* allWipe) : CEffectSimpleWipeCommon(allWipe)
{
}

CEffectSimpleWipeAdd::~CEffectSimpleWipeAdd()
{
	End();
}

void CEffectSimpleWipeAdd::End(void)
{
}

void CEffectSimpleWipeAdd::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax, POINT* lpStartPoint, POINT* lpEndPoint)
{
	if (ClipAndCheck(lpPicStart,lpPicEnd,count,countMax,lpStartPoint,lpEndPoint) == FALSE) return;

	int limit = m_countMax / 2;
	if (limit<1) limit = 1;
	int dv = limit;

	int c = m_count;
	if (c >= limit)
	{
		dv = m_countMax - limit;
		if (dv<1) dv = 1;
		c = m_countMax - count;

		SwapPic();
	}

	int* startPtr = (int*)(m_startPic->GetBuffer());
	int* endPtr = (int*)(m_endPic->GetBuffer());

	if (startPtr == NULL) return;
	if (endPtr == NULL) return;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int ml256 = (256 * c) / dv;
	if (ml256<0) ml256 = 0;
	if (ml256>256) ml256 = 256;


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

#if defined _WIN64
	INT32* src64Org1 = startPtr;
	INT32* src64Org2 = endPtr;
	INT32* dst64Org = dst;

	for (int j = 0; j < loopY; j++)
	{
		INT32* src64_1 = src64Org1;
		INT32* src64_2 = src64Org2;
		INT32* dst64 = dst64Org;

		for (int i = 0; i < loopX; i++)
		{
			INT32 srcData1 = *src64_1;
			INT32 srcData2 = *src64_2;

			INT32 srcR1 = (srcData1 >> 16) & 0xff;
			INT32 srcG1 = (srcData1 >> 8) & 0xff;
			INT32 srcB1 = (srcData1 ) & 0xff;

			INT32 srcR2 = (srcData2 >> 16) & 0xff;
			INT32 srcG2 = (srcData2 >> 8) & 0xff;
			INT32 srcB2 = (srcData2) & 0xff;

			INT32 r = srcR1 * 256 + srcR2 * ml256;
			INT32 g = srcG1 * 256 + srcG2 * ml256;
			INT32 b = srcB1 * 256 + srcB2 * ml256;

			r >>= 8;
			g >>= 8;
			b >>= 8;
			if (r > 255) r = 255;
			if (g > 255) g = 255;
			if (b > 255) b = 255;

			INT32 color = (r << 16) | (g << 8) | b;

			*dst64 = color;

			src64_1++;
			src64_2++;
			dst64++;
		}

		src64Org1 += startSrcPitch / 4;
		src64Org2 += endSrcPitch / 4;
		dst64Org += dstPitch / 4;
	}
#else

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi


		pxor mm0,mm0

		mov eax,0ffffffffh
		movd mm6,eax

		mov eax,ml256
		movd mm7,eax
		punpcklwd mm7,mm7
		punpckldq mm7,mm7

		mov esi,startPtr
		mov ebx,endPtr
		mov edi,dst
		mov ecx,loopY
LOOP1:
		push ecx
		push edx
		push ebx
		push esi
		push edi

		mov ecx,loopX
		shr ecx,1
LOOP2:
		movq mm1,[ebx]
		movq mm2,mm1

		punpcklbw mm1,mm0
		punpckhbw mm2,mm0

		pmullw mm1,mm7
		pmullw mm2,mm7
		
		movq mm3,[esi]

		psrlw mm1,8
		psrlw mm2,8

		packuswb mm1,mm1
		packuswb mm2,mm2
		pand mm1,mm6
		psllq mm2,32

		por mm1,mm2
		paddusb mm1,mm3

		movq [edi],mm1

		add ebx,8
		add esi,8
		add edi,8

		dec ecx
		jnz LOOP2

		pop edi
		pop esi
		pop ebx
		pop edx
		pop ecx

		add edi,dstPitch
		add esi,startSrcPitch
		add ebx,endSrcPitch
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
#endif

}




/*_*/

