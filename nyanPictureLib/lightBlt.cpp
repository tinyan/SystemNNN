#include <windows.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "lightBlt.h"


CLightBlt::CLightBlt()
{
}

CLightBlt::~CLightBlt()
{
	End();
}

void CLightBlt::End(void)
{
}

void CLightBlt::Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize,int lightPercent)
{
	if (lightPercent < 0) lightPercent = 0;
	if (lightPercent > 100) lightPercent = 100;

	lightPercent *= 128;
	lightPercent /= 100;
     

	DWORD dwAlpha = (DWORD)lightPercent;
	DWORD dwAlpha2 = 128;


	int* src = (int*)picData;
	int* dst = CMyGraphics::GetScreenBuffer();

	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();

	src += (SSIZE_T)srcPoint.y * srcSize.cx + srcPoint.x;
	dst += (SSIZE_T)putPoint.y * screenSizeX + putPoint.x;

	int srcPitch = srcSize.cx * sizeof(int);
	int dstPitch = screenSizeX * 4;

	int loopY = putSize.cy;
	int loopX = putSize.cx;

	if ((loopY<=0) || (loopX<=0)) return;

#if defined _WIN64
#pragma message("������c++�������K�v�ɂ� " __FILE__)

#else

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		mov esi,src
		mov edi,dst
		mov edx,loopY

	    movd mm4,dwAlpha 
		punpcklwd mm4,mm4
		punpckldq mm4,mm4 // mm4 =  0��0��0��0��
		movd mm5,dwAlpha2 
		punpcklwd mm5,mm5
		punpckldq mm5,mm5 // mm5 = 0(1)0(1)0(1)0(1)

		pxor mm6,mm6
		pxor mm7,mm7
LOOP1:
		push esi
		push edi

		mov ecx,loopX
LOOP2:
		movd mm0,dword ptr [esi]
		movd mm1,dword ptr [edi]

//        punpcklbw mm0,mm6
//      punpcklbw mm1,mm7

        // byte -> word �ɃA���p�b�N
        punpcklbw mm0,mm6
        punpcklbw mm1,mm7

        // �p�b�N�|���Z
        pmullw mm0,mm4
        pmullw mm1,mm5

        //  word �P�ʂő�����128�Ŋ���
        paddw mm0,mm1
        psrlw mm0,7

        // word->byte �Ƀp�b�N���ē]��
        packuswb mm0,mm6
        movd dword ptr [edi],mm0


		add esi,4
		add edi,4
		dec ecx
		jnz LOOP2

		pop edi
		pop esi
		add edi,dstPitch
		add esi,srcPitch
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

