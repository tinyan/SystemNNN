//
// effectsimplewipeshape.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "allSimpleWipe.h"
#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeShape.h"
//#include "..\commonEffect.h"
//#include "..\simpleWipe.h"

CEffectSimpleWipeShape::CEffectSimpleWipeShape(CAllSimpleWipe* allWipe) : CEffectSimpleWipeCommon(allWipe)
{
	SetMaxDivide(1);
	SetEffectHoukou(0);
	SetGrad(FALSE);
//	m_shapeDivide = 1;
//	m_effectHoukou = 0;
}

CEffectSimpleWipeShape::~CEffectSimpleWipeShape()
{
	End();
}

void CEffectSimpleWipeShape::End(void)
{
}



void CEffectSimpleWipeShape::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax, POINT* lpStartPoint, POINT* lpEndPoint)
{
	if (ClipAndCheck(lpPicStart,lpPicEnd,count,countMax,lpStartPoint,lpEndPoint) == FALSE) return;

	if (m_effectHoukou == 1)
	{
		SwapPic();
		m_count = m_countMax - m_count;
		if (m_count<0) m_count = 0;
	}

	CalcuShapeWork(m_count,m_countMax);	//形ごとにそれぞれのルーチンが呼ばれる
	if (m_gradFlag == FALSE)
	{
		PrintShape();
	}
	else
	{
		PrintGradShape();
	}
}


//virtual (dummy)
void CEffectSimpleWipeShape::CalcuShapeWork(int count, int countMax)
{
	//dummy routine	0でうめて、なにもしない

	int* shapeWork = m_allSimpleWipe->GetShapeWork();
//	int* shapeWork = CEffectSimpleWipe::m_shapeWork;

	if (shapeWork == NULL) return;
	if (m_shapeDivide == 0) return;

	int screenSizeY = CMyGraphics::GetScreenSizeY();

	ZeroMemory(shapeWork,m_shapeDivide * screenSizeY * sizeof(int));
	if (count > countMax)
	{
	}

}



//デフォルトの分割表示処理
void CEffectSimpleWipeShape::PrintShape(void)
{
	if (m_shapeDivide == 1)
	{
		PrintShape1();
		return;
	}

	int shapeDivide = m_shapeDivide;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int loopY = screenSizeY;
//	int* tablePtr = CEffectSimpleWipe::m_shapeWork;
	int* tablePtr = m_allSimpleWipe->GetShapeWork();

	int dstPitch = screenSizeX * sizeof(int);

	int* dst = CMyGraphics::GetScreenBuffer();

//	int* src1 = (int*)(m_startPic->GetBuffer());
//	int* src2 = (int*)(m_endPic->GetBuffer());
//	int src1Pitch = m_startPicSize.cx * sizeof(int);
//	int src2Pitch = m_endPicSize.cx * sizeof(int);

	int* src1 = (int*)m_startBuffer;
	int* src2 = (int*)m_endBuffer;
	int src1Pitch = m_startPitch;
	int src2Pitch = m_endPitch;

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

		mov edi,dst
		mov edx,tablePtr
		mov ebx,src1
		mov esi,src2

		cld

		mov ecx,loopY
LOOP1:
		push ecx
		push ebx
		push esi
		push edi

		mov ecx,[edx]
		add edx,4
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

		mov ecx,[edx]
		add edx,4
		or ecx,ecx
		jz SKIP2
		add ebx,ecx
		add ebx,ecx
		add ebx,ecx
		add ebx,ecx
		rep movsd
SKIP2:
		mov eax,shapeDivide
		cmp eax,2+1
		jb LAST1

		mov ecx,[edx]
		add edx,4
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

		mov ecx,[edx]
		add edx,4
		or ecx,ecx
		jz SKIP4
		add ebx,ecx
		add ebx,ecx
		add ebx,ecx
		add ebx,ecx
		rep movsd
SKIP4:
		mov eax,shapeDivide
		cmp eax,4+1
		jb LAST1


		mov ecx,[edx]
		add edx,4
		or ecx,ecx
		jz SKIP5
		add esi,ecx
		add esi,ecx
		add esi,ecx
		add esi,ecx
		xchg ebx,esi
		rep movsd
		xchg ebx,esi
SKIP5:

		mov ecx,[edx]
		add edx,4
		or ecx,ecx
		jz SKIP6
		add ebx,ecx
		add ebx,ecx
		add ebx,ecx
		add ebx,ecx
		rep movsd
SKIP6:

LAST1:
		pop edi
		pop esi
		pop ebx
		pop ecx
		add edi,dstPitch
		add esi,src2Pitch
		add ebx,src1Pitch
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



void CEffectSimpleWipeShape::PrintShape1(void)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int loopY = screenSizeY;
//	int* tablePtr = CEffectSimpleWipe::m_shapeWork;
	int* tablePtr = m_allSimpleWipe->GetShapeWork();

	int dstPitch = screenSizeX * sizeof(int);

	int* dst = CMyGraphics::GetScreenBuffer();

//	int* src1 = (int*)(m_startPic->GetBuffer());
//	int* src2 = (int*)(m_endPic->GetBuffer());

//	int src1Pitch = m_startPicSize.cx * sizeof(int);
//	int src2Pitch = m_endPicSize.cx * sizeof(int);
	int* src1 = (int*)m_startBuffer;
	int* src2 = (int*)m_endBuffer;
	int src1Pitch = m_startPitch;
	int src2Pitch = m_endPitch;

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

		mov edi,dst
		mov edx,tablePtr
		mov ebx,src2
		mov esi,src1

		cld

		mov ecx,loopY
LOOP1:
		push ecx
		push ebx
		push esi
		push edi

		mov ecx,[edx]
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
		mov ecx,[edx]
		add edx,4
		neg ecx
		add ecx,screenSizeX
		or ecx,ecx
		jz SKIP2
		rep movsd
SKIP2:
		pop edi
		pop esi
		pop ebx
		pop ecx
		add edi,dstPitch
		add esi,src1Pitch
		add ebx,src2Pitch
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


void CEffectSimpleWipeShape::PrintGradShape(void)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int loopY = screenSizeY;

	int* tablePtr = m_allSimpleWipe->GetShapeWork();

	int dstPitch = screenSizeX * sizeof(int);

	int* dst = CMyGraphics::GetScreenBuffer();

//	int* src1 = (int*)(m_startPic->GetBuffer());
//	int* src2 = (int*)(m_endPic->GetBuffer());

//	int src1Pitch = m_startPicSize.cx * sizeof(int);
//	int src2Pitch = m_endPicSize.cx * sizeof(int);

	int* src1 = (int*)m_startBuffer;
	int* src2 = (int*)m_endBuffer;
	int src1Pitch = m_startPitch;
	int src2Pitch = m_endPitch;

	//src1SizeX,gradSizeX,gradStartD,src2SizeX


	int delta = 64;
	if (m_gradSize>0) delta = 256 / m_gradSize;


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

		pxor mm0,mm0
		mov eax,delta
		movd mm4,eax
		punpcklwd mm4,mm4
		punpckldq mm4,mm4

		mov edi,dst
		mov edx,tablePtr
		mov ebx,src2
		mov esi,src1

		cld

		mov ecx,loopY
LOOP1:
		push ecx
		push ebx
		push esi
		push edi

		mov ecx,[edx]
		add edx,4
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

		mov ecx,[edx]
		add edx,4
		or ecx,ecx
		jz SKIP3


		mov eax,[edx]
		movd mm5,eax
		punpcklwd mm5,mm5
		punpckldq mm5,mm5
		neg eax
		add eax,256
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6

LOOP2:
		mov eax,[ebx]
		movd mm1,eax
		mov eax,[esi]
		movd mm2,eax
		punpcklbw mm1,mm0
		punpcklbw mm2,mm0
		pmullw mm1,mm5
		pmullw mm2,mm6
		paddusw mm6,mm4
		psrlw mm1,8
		psrlw mm2,8
		psubusw mm5,mm4
		paddusw mm1,mm2
		packuswb mm1,mm1
		movd eax,mm1
		mov [edi],eax


		add esi,4
		add ebx,4
		add edi,4
		dec ecx
		jnz LOOP2


SKIP3:
		add edx,4


		mov ecx,[edx]
		add edx,4
		or ecx,ecx
		jz SKIP4
		rep movsd
SKIP4:
		pop edi
		pop esi
		pop ebx
		pop ecx
		add edi,dstPitch
		add esi,src1Pitch
		add ebx,src2Pitch
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

	//
}

/*
void CEffectSimpleWipeShape::PrintShape6(void)
{
	int screenSizeX = CPicture::m_screenSizeX;
	int screenSizeY = CPicture::m_screenSizeY;

	int loopY = screenSizeY;
	int* tablePtr = CEffectSimpleWipe::m_shapeWork;

	int dstPitch = screenSizeX * sizeof(int);

	int* dst = (int*)(CPicture::m_lpScreenBuffer);

	int* src1 = m_startSrcPicPtr;
	int* src2 = m_endSrcPicPtr;

	int src1Pitch = m_startSrcPitch;
	int src2Pitch = m_endSrcPitch;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		mov edi,dst
		mov edx,tablePtr
		mov ebx,src1
		mov esi,src2

		cld

		mov ecx,loopY
LOOP1:
		push ecx
		push ebx
		push esi
		push edi

		mov ecx,[edx]
		add edx,4
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

		mov ecx,[edx]
		add edx,4
		or ecx,ecx
		jz SKIP2
		add ebx,ecx
		add ebx,ecx
		add ebx,ecx
		add ebx,ecx
		rep movsd
SKIP2:


		mov ecx,[edx]
		add edx,4
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

		mov ecx,[edx]
		add edx,4
		or ecx,ecx
		jz SKIP4
		add ebx,ecx
		add ebx,ecx
		add ebx,ecx
		add ebx,ecx
		rep movsd
SKIP4:


		mov ecx,[edx]
		add edx,4
		or ecx,ecx
		jz SKIP5
		add esi,ecx
		add esi,ecx
		add esi,ecx
		add esi,ecx
		xchg ebx,esi
		rep movsd
		xchg ebx,esi
SKIP5:

		mov ecx,[edx]
		add edx,4
		or ecx,ecx
		jz SKIP6
		add ebx,ecx
		add ebx,ecx
		add ebx,ecx
		add ebx,ecx
		rep movsd
SKIP6:

		pop edi
		pop esi
		pop ebx
		pop ecx
		add edi,dstPitch
		add esi,src2Pitch
		add ebx,src1Pitch
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



/*_*/

