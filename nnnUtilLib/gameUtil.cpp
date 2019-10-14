//
// gameUtil.cpp
//

#include <windows.h>

#include "..\nyanLib\include\picture.h"

#include "gameUtil.h"


CGameUtil::CGameUtil()
{
	SetScreenSize(800,600);
	SetMiniCGSize(132,100);
	SetMiniCGReduce(6);
}

CGameUtil::~CGameUtil()
{
	End();
}

void CGameUtil::End(void)
{

}

void CGameUtil::SetScreenSize(int sizeX,int sizeY)
{
	m_screenSizeX = sizeX;
	m_screenSizeY = sizeY;
}

void CGameUtil::SetMiniCGSize(int sizeX,int sizeY)
{
	m_miniCGSizeX = sizeX;
	m_miniCGSizeY = sizeY;
}

void CGameUtil::SetMiniCGReduce(int reduce)
{
	m_miniCGReduce = reduce;
	//check fit
	int dv = reduce;
	if (dv<1) dv = 1;

	int sizeX = m_screenSizeX / dv;
	int sizeY = m_screenSizeY / dv;
	if ((sizeX == m_miniCGSizeX) && (sizeY == m_miniCGSizeY))
	{
		m_reduceFitFlag = TRUE;
	}
	else
	{
		if (CheckSpecialSize())
		{
			m_reduceFitFlag = TRUE;
		}
		else
		{
			m_reduceFitFlag = FALSE;
		}
	}
}

BOOL CGameUtil::CheckSpecialSize(void)
{
	if (m_miniCGReduce != 6) return FALSE;
	if (m_screenSizeX != 800) return FALSE;
	if (m_screenSizeY != 600) return FALSE;
	if (m_miniCGSizeX != 132) return FALSE;
	if (m_miniCGSizeY != 100) return FALSE;

	return TRUE;
}

void CGameUtil::MakeMiniCG(int* screenBuffer, int* makedBuffer)
{
	if (screenBuffer == NULL) return;
	if (makedBuffer == NULL) return;


	if (m_reduceFitFlag)
	{
		MakeFitMiniCG(screenBuffer,makedBuffer);
	}
	else
	{
		MakeNoFitMiniCG(screenBuffer,makedBuffer);
	}
}


void CGameUtil::MakeFitMiniCG(int* screenBuffer, int* makedBuffer)
{
	int dotX = m_miniCGReduce;
	int dotY = m_miniCGReduce;

	int* dst = makedBuffer;
	int* src = screenBuffer;

	int loopX = m_screenSizeX / dotX;
	int loopY = m_screenSizeY / dotY;
	if (CheckSpecialSize())
	{
		loopX -= 1;
	}

	int amariX = m_screenSizeX - dotX * m_miniCGSizeX;
	int amariY = m_screenSizeY - dotY * m_miniCGSizeY;

	src += amariX / 2;
	src += (amariY / 2) * m_screenSizeX;

	int pitchX = dotX * sizeof(int);
	int pitchY = m_screenSizeX * dotY * sizeof(int);

	int lPitch = m_screenSizeX * sizeof(int);

	int divmul = 65536 / (dotX * dotY);

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

		mov esi,src
		mov edi,dst

		mov edx,loopY
		pxor mm0,mm0

		mov eax,divmul
		movd mm5,eax
		punpcklwd mm5,mm5
		punpckldq mm5,mm5


LLOOP1:
		push edx
		push esi
		mov ecx,loopX


LLOOP2:
		push ecx
		push esi
		pxor mm7,mm7
		mov edx,dotY
LLOOP3:
		push esi

		mov ecx,dotX
LLOOP4:
		mov eax,[esi]
		movd mm1,eax
		punpcklbw mm1,mm0
		paddw mm7,mm1
		add esi,4
		dec ecx
		jnz LLOOP4

		pop esi
		add esi,lPitch
		dec edx
		jnz LLOOP3

		pmulhw mm7,mm5
		packuswb mm7,mm0
		movd eax,mm7
		mov [edi],eax
		add edi,4


		pop esi
		pop ecx
		add esi,pitchX
		dec ecx
		jnz LLOOP2



		pop esi
		pop edx
		add esi,pitchY
		dec edx
		jnz LLOOP1


		emms

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
#endif

	return;
}


void CGameUtil::MakeNoFitMiniCG(int* screenBuffer, int* makedBuffer)
{
	int dotX = m_screenSizeX / m_miniCGSizeX;
	int dotY = m_screenSizeY / m_miniCGSizeY;
	if (dotX < 1) dotX = 1;
	if (dotY < 1) dotY = 1;

	int dv = dotX * dotY;

	int* dst = makedBuffer;

	for (int j=0;j<m_miniCGSizeY;j++)
	{
		int y = (m_screenSizeY * j) / m_miniCGSizeY;

		for (int i=0;i<m_miniCGSizeX;i++)
		{
			int x = (m_screenSizeX * i) / m_miniCGSizeX;

			int* src = screenBuffer + x + y * m_screenSizeX;

			int r = 0;
			int g = 0;
			int b = 0;

			for (int jj=0;jj<dotY;jj++)
			{
				int* src0 = src;

				for (int ii=0;ii<dotX;ii++)
				{
					int c = *src;
					r += (c>>16) & 0xff;
					g += (c>> 8) & 0xff;
					b += (c    ) & 0xff;

					src++;
				}

				src = src0;
				src += m_screenSizeX;
			}

			r /= dv;
			g /= dv;
			b /= dv;

			*dst = (r<<16) | (g<<8) | b;

			dst++;
		}
	}
}




BOOL CGameUtil::MakeMiniCG106x80(int* screenBuffer, int* makedBuffer)
{
	if (screenBuffer == NULL) return FALSE;
	if (makedBuffer == NULL) return FALSE;

	int* dst = makedBuffer;
	int* src = screenBuffer;
	src += 2;
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

		mov esi,src
		mov edi,dst

		mov edx,80
		pxor mm0,mm0

		mov eax,071C071Ch
		movd mm5,eax
		punpckldq mm5,mm5

LOOP1:
		push esi
		mov ecx,106

LOOP2:
		push esi

		pxor mm7,mm7

		mov ebx,6
LOOP3:
		movq mm1,[esi]
		movq mm2,mm1
		punpcklbw mm1,mm0
		punpckhbw mm2,mm0
		paddw mm7,mm1
		paddw mm7,mm2

		movq mm1,[esi+8]
		movq mm2,mm1
		punpcklbw mm1,mm0
		punpckhbw mm2,mm0
		paddw mm7,mm1
		paddw mm7,mm2

		movq mm1,[esi+16]
		movq mm2,mm1
		punpcklbw mm1,mm0
		punpckhbw mm2,mm0
		paddw mm7,mm1
		paddw mm7,mm2

		add esi,640*4
		dec ebx
		jnz LOOP3

		//div 36 = *65536/36 / 65536

		pmulhw mm7,mm5
		packuswb mm7,mm0
		movd eax,mm7
		mov [edi],eax

		add edi,4
		pop esi
		add esi,4*6
		dec ecx
		jnz LOOP2

		pop esi
		add esi,640*4*6
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

	return TRUE;
}



//800x600
BOOL CGameUtil::MakeMiniCG132x100(int* screenBuffer, int* makedBuffer)
{
	if (screenBuffer == NULL) return FALSE;
	if (makedBuffer == NULL) return FALSE;

	int* dst = makedBuffer;
	int* src = screenBuffer;
	src += 4;

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

		mov esi,src
		mov edi,dst

		mov edx,100
		pxor mm0,mm0

		mov eax,071C071Ch
		movd mm5,eax
		punpckldq mm5,mm5

LOOP1:
		push esi
		mov ecx,132

LOOP2:
		push esi

		pxor mm7,mm7

		mov ebx,6
LOOP3:
		movq mm1,[esi]
		movq mm2,mm1
		punpcklbw mm1,mm0
		punpckhbw mm2,mm0
		paddw mm7,mm1
		paddw mm7,mm2

		movq mm1,[esi+8]
		movq mm2,mm1
		punpcklbw mm1,mm0
		punpckhbw mm2,mm0
		paddw mm7,mm1
		paddw mm7,mm2

		movq mm1,[esi+16]
		movq mm2,mm1
		punpcklbw mm1,mm0
		punpckhbw mm2,mm0
		paddw mm7,mm1
		paddw mm7,mm2

		add esi,800*4
		dec ebx
		jnz LOOP3

		//div 36 = *65536/36 / 65536

		pmulhw mm7,mm5
		packuswb mm7,mm0
		movd eax,mm7
		mov [edi],eax

		add edi,4
		pop esi
		add esi,4*6
		dec ecx
		jnz LOOP2

		pop esi
		add esi,800*4*6
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

	return TRUE;
}


void CGameUtil::AddMaskToMiniPic(int* buffer, CPicture* lpPic)
{
	SIZE srcSize = lpPic->GetPicSize();
	int srcPicth = srcSize.cx * 4;

	int loopX = m_miniCGSizeX;
	int loopY = m_miniCGSizeY;
	if (srcSize.cx<loopX) loopX = srcSize.cx;
	if (srcSize.cy<loopY) loopY = srcSize.cy;

	int dstPitch = m_miniCGSizeX * 4;
	int maskPitch = srcSize.cx;

	int* src = lpPic->GetPictureBuffer();
	int* dst = buffer;
	char* mask = lpPic->GetMaskPic();

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

		mov esi,src
		mov edi,dst
		mov ebx,mask
		mov ecx,loopY
LOOP1:
		push ecx
		push ebx
		push esi
		push edi

		mov ecx,loopX
LOOP2:
		mov eax,[esi]
		movd mm1,eax
		mov eax,[edi]
		movd mm2,eax
		punpcklbw mm1,mm0
		punpcklbw mm2,mm0

		xor eax,eax
		mov al,[ebx]
		shr eax,1
		movd mm5,eax
		neg eax
		add eax,127
		movd mm6,eax
		punpcklwd mm5,mm5
		punpcklwd mm6,mm6
		punpckldq mm5,mm5
		punpckldq mm6,mm6

		pmullw mm1,mm5
		pmullw mm2,mm6
		paddw mm1,mm2
		psrlw mm1,7

		packuswb mm1,mm1
		movd eax,mm1

		mov [edi],eax

		add esi,4
		add edi,4
		inc ebx
		dec ecx
		jnz LOOP2

		pop edi
		pop esi
		pop ebx
		pop ecx
		add edi,dstPitch
		add esi,srcPicth
		add ebx,maskPitch
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
