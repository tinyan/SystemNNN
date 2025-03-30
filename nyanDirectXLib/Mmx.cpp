//
// mmx.cpp
//


#include <windows.h>
#include "mmx.h"


CMMX::CMMX()
{
	// check MMX is Exist

	m_565Mode = TRUE;	//dummy
	m_RGB24Mode = TRUE;
	m_RGB32Mode = TRUE;

//	m_offsetX = (1024-800)/2;
//	m_offsetY = (768-600)/2;


	if (CheckMMX())
	{
		m_mmxExistFlag = TRUE;
	}
	else
	{
		m_mmxExistFlag = FALSE;
	}
}


CMMX::~CMMX()
{
	End();
}


void CMMX::End(void)
{
}


void CMMX::SetViewParam(int realSizeX,int realSizeY,int viewOffsetX,int viewOffsetY)
{
	m_offsetX = viewOffsetX;
	m_offsetY = viewOffsetY;
	m_realWindowSizeX = realSizeX;
	m_realWindowSizeY = realSizeY;
}


BOOL CMMX::CheckMMXExist(void)
{
	return m_mmxExistFlag;
}

void CMMX::Set565Mode(BOOL md)
{
	m_565Mode = md;
}

void CMMX::SetRGB24Mode(BOOL md)
{
	m_RGB24Mode = md;
}

void CMMX::SetRGB32Mode(BOOL md)
{
	m_RGB32Mode = md;
}


BOOL CMMX::CheckMMX(void)
{
	int mmxflag = 0;

#if defined _WIN64
	return TRUE;
#else

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx

		pushfd
		pop eax
		mov ebx,eax
		xor eax,00200000h
		push eax
		popfd
		pushfd
		pop eax

		xor eax,ebx
		and eax,00200000h

		mov ebx,0
		or eax,eax
		jz SKIP

		mov eax,1
		cpuid
		test edx,00800000h
		jz SKIP

		mov ebx,1

SKIP:
		mov mmxflag,ebx

		pop edx
		pop ecx
		pop ebx
		pop eax

	}
#endif

	if (mmxflag) return TRUE;

	return FALSE;
}


void CMMX::SetSurfaceParameter(LPVOID lpSurface,int lPitch)
{
	m_lpSurface = lpSurface;
	m_lPitch = lPitch;
}


void CMMX::SetBufferParameter(int* lpScreenBuffer, int screenPitch, int screenSizeX, int screenSizeY)
{
	m_lpScreenBuffer = lpScreenBuffer;
	m_lScreenPitch = screenPitch;
	m_screenSizeX = screenSizeX;
	m_screenSizeY = screenSizeY;
}


BOOL CMMX::Clip(int& srcX,int& srcY,int& dstX,int& dstY,int& sizeX,int& sizeY)
{
	int dltx = dstX & 7;
	dstX &= ~7;
	sizeX += dltx;
	srcX -= dltx;

	sizeX += 7;
	sizeX &= ~7;


	if (srcX<0)
	{
		int delta = -srcX;
		srcX += delta;
		dstX += delta;
		sizeX -= delta;
		if (sizeX <= 0) return FALSE;
	}

	if (srcY<0)
	{
		int delta = -srcY;
		srcY += delta;
		dstY += delta;
		sizeY -= delta;
		if (sizeY <= 0) return FALSE;
	}

	if ((srcX + sizeX) > m_screenSizeX)
	{
		int delta = srcX + sizeX - m_screenSizeX;
		sizeX -= delta;
		if (sizeX <= 0) return FALSE;
	}

	if ((srcY + sizeY) > m_screenSizeY)
	{
		int delta = srcY + sizeY - m_screenSizeY;
		sizeY -= delta;
		if (sizeY <= 0) return FALSE;
	}

	if (dstX<0)
	{
		int delta = -dstX;
		srcX += delta;
		dstX += delta;
		sizeX -= delta;
		if (sizeX <= 0) return FALSE;
	}

	if (dstY<0)
	{
		int delta = -dstY;
		srcY += delta;
		dstY += delta;
		sizeY -= delta;
		if (sizeY <= 0) return FALSE;
	}

	if ((dstX + sizeX) > m_realWindowSizeX)
	{
		int delta = dstX + sizeX - m_realWindowSizeX;
		sizeX -= delta;
		if (sizeX <=0) return FALSE;
	}

	if ((dstY + sizeY) > m_realWindowSizeY)
	{
		int delta = dstY + sizeY - m_realWindowSizeY;
		sizeY -= delta;
		if (sizeY <=0) return FALSE;
	}

	return TRUE;
}

void CMMX::_MMXPrint(int bpp)
{
	if (bpp == 16) _MMX32to16();
	if (bpp == 24) _MMX32to24();
	if (bpp == 32) _MMX32to32();
}

void CMMX::MMXPrint(int bpp, int startX, int startY,int sizeX,int sizeY)
{
	if (bpp == 16) MMX32to16(startX,startY,sizeX,sizeY);
	if (bpp == 24) MMX32to24(startX,startY,sizeX,sizeY);
	if (bpp == 32) MMX32to32(startX,startY,sizeX,sizeY);
}


void CMMX::MMX32to16(int startX,int startY,int sizeX,int sizeY)
{
	int dstX = startX;
	int dstY = startY;
	int srcX = startX;
	int srcY = startY;
	dstX += m_offsetX;
	dstY += m_offsetY;

	if (!Clip(srcX,srcY,dstX,dstY,sizeX,sizeY)) return;
	/*
	int dltx = dstX & 7;
	dstX &= ~7;
	sizeX += dltx;
	srcX -= dltx;

//	startX &= ~7;
//	sizeX += dltx;

	sizeX += 7;
	sizeX &= ~7;
	*/
//clip



	int lPitch = m_lPitch;
	int screenPitch = m_lScreenPitch;
	int* src = m_lpScreenBuffer;
	int* dst = (int*)m_lpSurface;

	src += srcX;
	src += srcY * (screenPitch / 4);

	dst += (dstX / 4 * 2);
	dst += dstY * (lPitch / 4);

	int loopX = sizeX / 8;
	int loopY = sizeY;

	if ((loopX<=0) || (loopY<=0)) return;


	//‚Æ‚è‚ ‚¦‚¸ 5:6:5‚É‘Î‰ž ‚½‚¾‚µÂ‚Í1bit‚¨‚Æ‚·
#if defined _WIN64

	INT32* src64 = (INT32*)m_lpScreenBuffer;
	INT16* dst64Org = (INT16*)m_lpSurface;

	for (int j = 0; j < sizeY; j++)
	{
		INT16* dst64 = dst64Org;
		for (int i = 0; i < sizeX; i++)
		{
			INT32 data = *src64;

			INT16 r = (INT16)((data >> 16) & 0xff);
			INT16 g = (INT16)((data >> 8) & 0xff);
			INT16 b = (INT16)((data) & 0xff);

			if (m_565Mode)
			{
				r <<= 11;
				g <<= 5;
			}
			else
			{
				r <<= 10;
				g <<= 5;
			}

			INT16 color = r | g | b;

			*dst64 = color;
			dst64++;
			src64++;
		}
		dst64Org += lPitch / 2;
	}

#else


	if (m_565Mode)
	{
		__asm
		{
	//		emms

			push eax
			push ebx
			push ecx
			push edx
			push esi
			push edi

			mov eax,00f800f8h
			mov ebx,00f800f8h
			movd mm7,eax
			movd mm0,ebx
			psllq mm7,32
			por mm7,mm0
			
			mov eax,0000fc00h
			mov ebx,0000fc00h
			movd mm6,eax
			movd mm0,ebx
			psllq mm6,32
			por mm6,mm0

			mov eax,20000004h
			mov ebx,20000004h
			movd mm5,eax
			movd mm0,ebx
			psllq mm5,32
			por mm5,mm0

			mov esi,src
			mov edi,dst

			mov ebx,lPitch
			mov eax,screenPitch


			sub edi,8
			mov edx,loopY
LOOP1:
			push eax
			push esi
			push edi
			mov ecx,loopX
LOOP2:
			movq mm0,qword ptr [esi]
			movq mm2,mm0
			movq mm1,qword ptr [esi+8]
			movq mm3,mm1

	//		movq mm2,qword ptr [esi]
	//		movq mm3,qword ptr [esi+8]

			
			pand mm0,mm7
			pand mm1,mm7


			pmaddwd mm0,mm5
			pand mm2,mm6
			pmaddwd mm1,mm5
			pand mm3,mm6



			por mm0,mm2
			por mm1,mm3

//			psrld mm0,6
//			psrld mm1,6

			pslld mm0,11
			pslld mm1,11
			psrad mm0,16
			psrad mm1,16


			add edi,8
			packssdw mm0,mm1


			add esi,16
//			pslld mm0,1

			movq qword ptr [edi],mm0


			//2kaime
			movq mm0,qword ptr [esi]
			movq mm1,qword ptr [esi+8]

			movq mm2,qword ptr [esi]
			movq mm3,qword ptr [esi+8]

			mov eax,[esi+16]	//prefetch to cache
			
			pand mm0,mm7
			pand mm1,mm7

			pand mm2,mm6
			pand mm3,mm6

			pmaddwd mm0,mm5
			pmaddwd mm1,mm5

			por mm0,mm2
			por mm1,mm3

//			psrld mm0,6
//			psrld mm1,6
			pslld mm0,11
			pslld mm1,11
			psrad mm0,16
			psrad mm1,16

			add edi,8
			packssdw mm0,mm1

			add esi,16
//			pslld mm0,1

			movq qword ptr [edi],mm0



			dec ecx
			jnz LOOP2


			pop edi
			pop esi
			pop eax
			add edi,ebx
			add esi,eax

			dec edx
			jnz LOOP1



	//		pmaddwd


			emms


			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax
		}
	}
	else
	{
		//			5:5:5mode
		__asm
		{
	//		emms

			push eax
			push ebx
			push ecx
			push edx
			push esi
			push edi

			mov eax,00f800f8h
			mov ebx,00f800f8h
			movd mm7,eax
			movd mm0,ebx
			psllq mm7,32
			por mm7,mm0
			
			mov eax,0000f800h
			mov ebx,0000f800h
			movd mm6,eax
			movd mm0,ebx
			psllq mm6,32
			por mm6,mm0

			mov eax,20000008h
			mov ebx,20000008h
			movd mm5,eax
			movd mm0,ebx
			psllq mm5,32
			por mm5,mm0

			mov esi,src
			mov edi,dst

			mov ebx,lPitch
			mov eax,screenPitch


			sub edi,8
			mov edx,loopY
LOOP1_555:
			push eax
			push esi
			push edi
			mov ecx,loopX
LOOP2_555:
			movq mm0,qword ptr [esi]
			movq mm2,mm0
			movq mm1,qword ptr [esi+8]
			movq mm3,mm1

	//		movq mm2,qword ptr [esi]
	//		movq mm3,qword ptr [esi+8]

			
			pand mm0,mm7
			pand mm1,mm7


			pmaddwd mm0,mm5
			pand mm2,mm6
			pmaddwd mm1,mm5
			pand mm3,mm6



			por mm0,mm2
			por mm1,mm3

			psrld mm0,6
			psrld mm1,6

			add edi,8
			packssdw mm0,mm1

			add esi,16
//			pslld mm0,1

			movq qword ptr [edi],mm0


			//2kaime
			movq mm0,qword ptr [esi]
			movq mm1,qword ptr [esi+8]

			movq mm2,qword ptr [esi]
			movq mm3,qword ptr [esi+8]

			mov eax,[esi+16]	//prefetch to cache
			
			pand mm0,mm7
			pand mm1,mm7

			pand mm2,mm6
			pand mm3,mm6

			pmaddwd mm0,mm5
			pmaddwd mm1,mm5

			por mm0,mm2
			por mm1,mm3

			psrld mm0,6
			psrld mm1,6

			add edi,8
			packssdw mm0,mm1

			add esi,16
//			pslld mm0,1

			movq qword ptr [edi],mm0



			dec ecx
			jnz LOOP2_555


			pop edi
			pop esi
			pop eax
			add edi,ebx
			add esi,eax

			dec edx
			jnz LOOP1_555



	//		pmaddwd


			emms


			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax
		}
	}
#endif
}

void CMMX::MMX32to24(int startX,int startY,int sizeX,int sizeY)
{
	if (m_RGB24Mode == FALSE)
	{
		MMX32to24BGR(startX,startY,sizeX,sizeY);
		return;
	}

	int dstX = startX;
	int dstY = startY;
	int srcX = startX;
	int srcY = startY;
	dstX += m_offsetX;
	dstY += m_offsetY;

	if (!Clip(srcX,srcY,dstX,dstY,sizeX,sizeY)) return;
/*
	int dltx = dstX & 7;
	dstX &= ~7;
	sizeX += dltx;
	srcX -= dltx;
	*/

	
//	int dltx = startX & 7;
	//startX &= ~7;
	//sizeX += dltx;

	//sizeX += 7;
	//sizeX &= ~7;

	int lPitch = m_lPitch;
	int screenPitch = m_lScreenPitch;
	int* src = m_lpScreenBuffer;
	int* dst = (int*)m_lpSurface;


	src += srcX;
	src += srcY * (screenPitch / 4);

	dst += (dstX / 4 * 3);
	dst += dstY * (lPitch / 4);

	int loopX = sizeX / 8;
	int loopY = sizeY;

	if ((loopX<=0) || (loopY<=0)) return;

#if defined _WIN64
	INT32* src64Org = (INT32*)src;
	char* dst64Org = (char*)dst;

	for (int j = 0; j < sizeY; j++)
	{
		INT32* src64 = src64Org;
		char* dst64 = dst64Org;
		for (int i = 0; i < sizeX; i++)
		{
			INT32 data = *src64;
			char r = (data >> 16) & 0xff;
			char g = (data >> 8) & 0xff;
			char b = data & 0xff;
			*dst64 = r;
			dst64++;
			*dst64 = g;
			dst64++;
			*dst64 = b;
			dst64++;

			src64++;
		}
		src64Org += screenPitch / 4;
		dst64Org += lPitch;
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

		mov esi,src
		mov edi,dst

		mov eax,0x00ffffff
		movd mm6,eax
		movd mm7,eax
		psllq mm7,32


		mov eax,lPitch
		mov ebx,screenPitch

		mov edx,loopY
LOOP1:
		push esi
		push edi
		mov ecx,loopX
LOOP2:
//		align 16
		movq mm0,qword ptr [esi]
		movq mm1,qword ptr [esi]
		movq mm2,qword ptr [esi+8]
		pand mm0,mm6
		pand mm1,mm7
//		pand mm2,mm6
		psrlq mm1,8
		psllq mm2,48
		por mm0,mm1
		por mm0,mm2
		movq qword ptr [edi],mm0

		movq mm0,qword ptr [esi+8]
		movq mm1,qword ptr [esi+8]
		movq mm2,qword ptr [esi+16]
		movq mm3,qword ptr [esi+16]
		pand mm0,mm6
		pand mm1,mm7
		pand mm2,mm6
		pand mm3,mm7

		psrlq mm0,16
		psrlq mm1,24
		psllq mm2,32
		psllq mm3,24
		por mm0,mm1
		por mm2,mm3
		por mm0,mm2
		movq qword ptr [edi+8],mm0

		movq mm1,qword ptr [esi+16]
		movq mm2,qword ptr [esi+24]
		movq mm3,qword ptr [esi+24]
		pand mm1,mm7
		pand mm2,mm6
		pand mm3,mm7
		psrlq mm1,40
		psllq mm2,16
		psllq mm3,8
		por mm1,mm2
		por mm1,mm3
		movq qword ptr [edi+16],mm1

		add esi,32
		add edi,24

		dec ecx
		jnz LOOP2
		
		pop edi
		pop esi
//		pop eax
		add edi,eax
		add esi,ebx

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


//‚¨‚»‚¢??
void CMMX::MMX32to24BGR(int startX,int startY,int sizeX,int sizeY)
{
	int dstX = startX;
	int dstY = startY;
	int srcX = startX;
	int srcY = startY;
	dstX += m_offsetX;
	dstY += m_offsetY;

	if (!Clip(srcX,srcY,dstX,dstY,sizeX,sizeY)) return;
/*
	int dltx = dstX & 7;
	dstX &= ~7;
	sizeX += dltx;
	srcX -= dltx;
	*/


//	int dltx = startX & 7;
//	startX &= ~7;
//	sizeX += dltx;

//	sizeX += 7;
//	sizeX &= ~7;

	int lPitch = m_lPitch;
	int screenPitch = m_lScreenPitch;
	int* src = m_lpScreenBuffer;
	int* dst = (int*)m_lpSurface;


	src += srcX;
	src += srcY * (screenPitch / 4);

	dst += (dstX / 4 * 3);
	dst += dstY * (lPitch / 4);

	int loopX = sizeX / 8;
	int loopY = sizeY;

	if ((loopX<=0) || (loopY<=0)) return;

#if defined _WIN64
	INT32* src64Org = (INT32*)src;
	char* dst64Org = (char*)dst;

	for (int j = 0; j < sizeY; j++)
	{
		INT32* src64 = src64Org;
		char* dst64 = dst64Org;
		for (int i = 0; i < sizeX; i++)
		{
			INT32 data = *src64;
			char r = (data >> 16) & 0xff;
			char g = (data >> 8) & 0xff;
			char b = data & 0xff;
			*dst64 = b;
			dst64++;
			*dst64 = g;
			dst64++;
			*dst64 = r;
			dst64++;

			src64++;
		}
		src64Org += screenPitch / 4;
		dst64Org += lPitch;
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

		mov esi,src
		mov edi,dst

		mov eax,0x00ffffff
		movd mm6,eax
		movd mm7,eax
		psllq mm7,32


		mov eax,lPitch
		mov ebx,screenPitch

		mov edx,loopY
LOOP1:
		push esi
		push edi
		mov ecx,loopX
LOOP2:
//		align 16
		movq mm0,qword ptr [esi]

		movq mm4,mm0
		movq mm5,mm0
		pslld mm0,16
		psrld mm0,24
		pslld mm0,8
		pslld mm4,16
		psrld mm5,24
		pslld mm5,8
		por mm0,mm4
		por mm0,mm5

		movq mm1,mm0
		movq mm2,qword ptr [esi+8]
		
		movq mm4,mm2
		movq mm5,mm2
		pslld mm2,16
		psrld mm2,24
		pslld mm2,8
		pslld mm4,16
		psrld mm5,24
		pslld mm5,8
		por mm2,mm4
		por mm2,mm5

		pand mm0,mm6
		pand mm1,mm7
//		pand mm2,mm6
		psrlq mm1,8
		psllq mm2,48
		por mm0,mm1
		por mm0,mm2
		movq qword ptr [edi],mm0




		movq mm0,qword ptr [esi+8]

		movq mm4,mm0
		movq mm5,mm0
		pslld mm0,16
		psrld mm0,24
		pslld mm0,8
		pslld mm4,16
		psrld mm5,24
		pslld mm5,8
		por mm0,mm4
		por mm0,mm5

		movq mm1,mm0

		movq mm2,qword ptr [esi+16]

		movq mm4,mm2
		movq mm5,mm2
		pslld mm2,16
		psrld mm2,24
		pslld mm2,8
		pslld mm4,16
		psrld mm5,24
		pslld mm5,8
		por mm2,mm4
		por mm2,mm5

		movq mm3,mm2


		pand mm0,mm6
		pand mm1,mm7
		pand mm2,mm6
		pand mm3,mm7

		psrlq mm0,16
		psrlq mm1,24
		psllq mm2,32
		psllq mm3,24
		por mm0,mm1
		por mm2,mm3
		por mm0,mm2
		movq qword ptr [edi+8],mm0

		movq mm1,qword ptr [esi+16]

		movq mm4,mm1
		movq mm5,mm1
		pslld mm1,16
		psrld mm1,24
		pslld mm1,8
		pslld mm4,16
		psrld mm5,24
		pslld mm5,8
		por mm1,mm4
		por mm1,mm5


		movq mm2,qword ptr [esi+24]

		movq mm4,mm2
		movq mm5,mm2
		pslld mm2,16
		psrld mm2,24
		pslld mm2,8
		pslld mm4,16
		psrld mm5,24
		pslld mm5,8
		por mm2,mm4
		por mm2,mm5

		movq mm3,mm2

		pand mm1,mm7
		pand mm2,mm6
		pand mm3,mm7
		psrlq mm1,40
		psllq mm2,16
		psllq mm3,8
		por mm1,mm2
		por mm1,mm3
		movq qword ptr [edi+16],mm1

		add esi,32
		add edi,24

		dec ecx
		jnz LOOP2
		
		pop edi
		pop esi
//		pop eax
		add edi,eax
		add esi,ebx

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



void CMMX::MMX32to32(int startX,int startY,int sizeX,int sizeY)
{
	if (m_RGB32Mode == FALSE)
	{
		MMX32to32BGR(startX,startY,sizeX,sizeY);
		return;
	}

	int dstX = startX;
	int dstY = startY;
	int srcX = startX;
	int srcY = startY;
	dstX += m_offsetX;
	dstY += m_offsetY;

	if (!Clip(srcX,srcY,dstX,dstY,sizeX,sizeY)) return;

	//clip


	int lPitch = m_lPitch;
	int screenPitch = m_lScreenPitch;
	int* src = m_lpScreenBuffer;
	int* dst = (int*)m_lpSurface;

	src += srcX;
	src += srcY * (screenPitch / 4);

	dst += dstX;
	dst += dstY * (lPitch / 4);

	int loopX = sizeX;
	int loopY = sizeY;

	if ((loopX<=0) || (loopY<=0)) return;

#if defined _WIN64

//	INT32* src0 = src;
//	INT32* dst0 = dst;
	//‚Æ‚è‚ ‚¦‚¸32bitŽÀ‘•
	for (int j = 0; j < loopY; j++)
	{
		INT32* src64 = src;
		INT32* dst64 = dst;

		for (int i = 0; i < loopX; i++)
		{
			*dst64 = *src64;
			dst64++;
			src64++;
		}
		src += screenPitch / 4;
		dst += lPitch / 4;
	}

	/*
	INT64* src64Org = (INT64*)m_lpScreenBuffer;
	INT64* dst64Org = (INT64*)m_lpSurface;
	INT64 lPitch64 = (INT64)m_lPitch;

	for (int j = 0; j < loopY; j++)
	{
		INT64* src64 = src64Org;
		INT64* dst64 = dst64Org;

		for (int i = 0; i < loopX; i++)
		{
			*dst64 = *src64;
			dst64++;
			src64++;
		}
		src64Org += loopX1;
		dst64Org += lPitch64 / 8;
	}
	*/

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

		mov eax,screenPitch
		mov ebx,lPitch
		mov edx,loopY
		cld
LOOP1:
		push esi
		push edi
		mov ecx,loopX
		rep movsd
		pop edi
		pop esi
		add esi,eax
		add edi,ebx
		
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



void CMMX::MMX32to32BGR(int startX,int startY,int sizeX,int sizeY)
{
	int dstX = startX;
	int dstY = startY;
	int srcX = startX;
	int srcY = startY;
	dstX += m_offsetX;
	dstY += m_offsetY;

	if (!Clip(srcX,srcY,dstX,dstY,sizeX,sizeY)) return;

	int lPitch = m_lPitch;
	int screenPitch = m_lScreenPitch;
	int* src = m_lpScreenBuffer;
	int* dst = (int*)m_lpSurface;

	if (dstX & 1)
	{
		srcX--;
		dstX &= ~1;
		sizeX++;
	}

	if (sizeX & 1)
	{
		sizeX++;
	}


	//clip


	src += srcX;
	src += srcY * (screenPitch / 4);

	dst += dstX;
	dst += dstY * (lPitch / 4);

	int loopX = sizeX / 2;
	int loopY = sizeY;

	if (loopX<=0) return;
	if (loopY<=0) return;

#if defined _WIN64

	INT32* src64Org = (INT32*)src;
	INT32* dst64Org = (INT32*)dst;

	for (int j = 0; j < sizeY; j++)
	{
		INT32* src64 = src64Org;
		INT32* dst64 = dst64Org;
		for (int i = 0; i < sizeX; i++)
		{
			INT32 data = *src64;
			INT32 r = (data>> 16) & 0xff;
			INT32 g = ((data >> 8) & 0xff) << 8;;
			INT32 b = (data & 0xff) << 16;;
			INT32 color = r | g | b;
			*dst64 = color;
			src64++;
			dst64++;
		}
		src64Org += screenPitch / 4;
		dst64Org += lPitch / 4;
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

		mov eax,0ffh
		movd mm5,eax
		punpckldq mm5,mm5
		mov eax,0ff00h
		movd mm6,eax
		punpckldq mm6,mm6
		mov eax,0ff0000h
		movd mm7,eax
		punpckldq mm7,mm7


		mov esi,src
		mov edi,dst

		mov eax,screenPitch
		mov ebx,lPitch
		mov edx,loopY
LOOP1:
		push esi
		push edi
		mov ecx,loopX
LOOP2:
		movq mm0,[esi]
		movq mm1,mm0
		movq mm2,mm0
		
		pand mm0,mm5
		pand mm1,mm6
		pand mm2,mm7

		pslld mm0,16
		psrld mm2,16
		por mm0,mm1
		por mm0,mm2

		movq [edi],mm0

		add esi,8
		add edi,8
		dec ecx
		jnz LOOP2

		pop edi
		pop esi
		add esi,eax
		add edi,ebx
		
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

void CMMX::_MMX32to16(void)
{
	int lPitch = m_lPitch;
	LPVOID src = m_lpScreenBuffer;
	LPVOID dst = m_lpSurface;

	int screenSizeX = m_screenSizeX;
	int screenSizeY = m_screenSizeY;

	int loopX1 = screenSizeX /4 /2;
	int loopX2 = screenSizeX /4 /2;

	//‚Æ‚è‚ ‚¦‚¸ 5:6:5‚É‘Î‰ž ‚½‚¾‚µÂ‚Í1bit‚¨‚Æ‚·

#if defined _WIN64

	INT32* src64 = (INT32*)m_lpScreenBuffer;
	INT16* dst64Org = (INT16*)m_lpSurface;

	for (int j = 0; j < screenSizeY; j++)
	{
		INT16* dst64 = dst64Org;
		for (int i = 0; i < screenSizeX; i++)
		{
			INT32 data = *src64;

			INT16 r = (INT16)((data >> 16) & 0xff);
			INT16 g = (INT16)((data >> 8) & 0xff);
			INT16 b = (INT16)((data) & 0xff);

			if (m_565Mode)
			{
				r <<= 11;
				g <<= 5;
			}
			else
			{
				r <<= 10;
				g <<= 5;
			}

			INT16 color = r | g | b;

			*dst64 = color;
			dst64++;
			src64++;
		}
		dst64Org += lPitch/2;
	}

#else

	if (m_565Mode)
	{
		__asm
		{
	//		emms

			push eax
			push ebx
			push ecx
			push edx
			push esi
			push edi




			mov eax,00f800f8h
			mov ebx,00f800f8h
			movd mm7,eax
			movd mm0,ebx
			psllq mm7,32
			por mm7,mm0
			
			mov eax,0000fc00h
			mov ebx,0000fc00h
			movd mm6,eax
			movd mm0,ebx
			psllq mm6,32
			por mm6,mm0

			mov eax,20000004h
			mov ebx,20000004h
			movd mm5,eax
			movd mm0,ebx
			psllq mm5,32
			por mm5,mm0



			mov esi,src
			mov edi,dst
			mov ebx,lPitch



			sub edi,8
			mov edx,screenSizeY
LOOP1:
			push edi
			mov ecx,loopX1

LOOP2:
			movq mm0,qword ptr [esi]
			movq mm1,qword ptr [esi+8]

			movq mm2,qword ptr [esi]
			movq mm3,qword ptr [esi+8]

			
			pand mm0,mm7
			pand mm1,mm7

			pand mm2,mm6
			pand mm3,mm6

			pmaddwd mm0,mm5
			pmaddwd mm1,mm5

			por mm0,mm2
			por mm1,mm3

//			psrld mm0,6
//			psrld mm1,6
			pslld mm0,11
			pslld mm1,11
			psrad mm0,16
			psrad mm1,16

			add edi,8
			packssdw mm0,mm1

			add esi,16
//			pslld mm0,1

			movq qword ptr [edi],mm0


			//2kaime
			movq mm0,qword ptr [esi]
			movq mm1,qword ptr [esi+8]

			movq mm2,qword ptr [esi]
			movq mm3,qword ptr [esi+8]

			mov eax,[esi+16]	//prefetch to cache
			
			pand mm0,mm7
			pand mm1,mm7

			pand mm2,mm6
			pand mm3,mm6

			pmaddwd mm0,mm5
			pmaddwd mm1,mm5

			por mm0,mm2
			por mm1,mm3

//			psrld mm0,6
//			psrld mm1,6
			pslld mm0,11
			pslld mm1,11
			psrad mm0,16
			psrad mm1,16

			add edi,8
			packssdw mm0,mm1

			add esi,16
//			pslld mm0,1

			movq qword ptr [edi],mm0









			dec ecx
			jnz LOOP2


			pop edi
			add edi,ebx
			dec edx
			jnz LOOP1



	//		pmaddwd


			emms


			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax

		}
	}
	else
	{
		//			5:5:5mode
		__asm
		{
	//		emms

			push eax
			push ebx
			push ecx
			push edx
			push esi
			push edi

			mov eax,00f800f8h
			mov ebx,00f800f8h
			movd mm7,eax
			movd mm0,ebx
			psllq mm7,32
			por mm7,mm0
			
			mov eax,0000f800h
			mov ebx,0000f800h
			movd mm6,eax
			movd mm0,ebx
			psllq mm6,32
			por mm6,mm0

			mov eax,20000008h
			mov ebx,20000008h
			movd mm5,eax
			movd mm0,ebx
			psllq mm5,32
			por mm5,mm0

			mov esi,src
			mov edi,dst

			mov ebx,lPitch

			sub edi,8
			mov edx,screenSizeY
LOOP1_555:
			push edi
			mov ecx,loopX2
LOOP2_555:
			movq mm0,qword ptr [esi]
			movq mm2,mm0
			movq mm1,qword ptr [esi+8]
			movq mm3,mm1

	//		movq mm2,qword ptr [esi]
	//		movq mm3,qword ptr [esi+8]

			
			pand mm0,mm7
			pand mm1,mm7


			pmaddwd mm0,mm5
			pand mm2,mm6
			pmaddwd mm1,mm5
			pand mm3,mm6



			por mm0,mm2
			por mm1,mm3

			psrld mm0,6
			psrld mm1,6

			add edi,8
			packssdw mm0,mm1

			add esi,16
//			pslld mm0,1

			movq qword ptr [edi],mm0


			//2kaime
			movq mm0,qword ptr [esi]
			movq mm1,qword ptr [esi+8]

			movq mm2,qword ptr [esi]
			movq mm3,qword ptr [esi+8]

			mov eax,[esi+16]	//prefetch to cache
			
			pand mm0,mm7
			pand mm1,mm7

			pand mm2,mm6
			pand mm3,mm6

			pmaddwd mm0,mm5
			pmaddwd mm1,mm5

			por mm0,mm2
			por mm1,mm3

			psrld mm0,6
			psrld mm1,6

			add edi,8
			packssdw mm0,mm1

			add esi,16
//			pslld mm0,1

			movq qword ptr [edi],mm0



			dec ecx
			jnz LOOP2_555


			pop edi

			add edi,ebx
			dec edx
			jnz LOOP1_555


			emms

			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax
		}
	}
#endif
}


void CMMX::_MMX32to24(void)
{
	int screenSizeX = m_screenSizeX;
	int screenSizeY = m_screenSizeY;

	if (m_RGB24Mode == FALSE)
	{
		MMX32to24BGR(0,0,screenSizeX,screenSizeY);
		return;
	}

	int lPitch = m_lPitch;
	LPVOID src = m_lpScreenBuffer;
	LPVOID dst = m_lpSurface;

	int loopX1 = screenSizeX / 8;
#if defined _WIN64

	INT32* src64 = (INT32*)m_lpScreenBuffer;
	char* dst64Org = (char*)m_lpSurface;

	for (int j = 0; j < screenSizeY; j++)
	{
		char* dst64 = dst64Org;
		for (int i = 0; i < screenSizeX; i++)
		{
			INT32 data = *src64;
			char r = (char)((data >> 16) & 0xff);
			char g = (char)((data >> 8) & 0xff);
			char b = (char)((data ) & 0xff);
			*dst64 = b;
			dst64++;
			*dst64 = g;
			dst64++;
			*dst64 = r;
			dst64++;

			src64++;
		}
		dst64Org += lPitch;
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

//		emms

		mov esi,src
		mov edi,dst

		mov eax,0x00ffffff
		movd mm6,eax
		movd mm7,eax
		psllq mm7,32


		mov eax,lPitch
		mov edx,screenSizeY
LOOP1:
		push edi
		mov ecx,loopX1
LOOP2:
//		align 16
		movq mm0,qword ptr [esi]
		movq mm1,qword ptr [esi]
		movq mm2,qword ptr [esi+8]
		pand mm0,mm6
		pand mm1,mm7
//		pand mm2,mm6
		psrlq mm1,8
		psllq mm2,48
		por mm0,mm1
		por mm0,mm2
		movq qword ptr [edi],mm0

		movq mm0,qword ptr [esi+8]
		movq mm1,qword ptr [esi+8]
		movq mm2,qword ptr [esi+16]
		movq mm3,qword ptr [esi+16]
		pand mm0,mm6
		pand mm1,mm7
		pand mm2,mm6
		pand mm3,mm7

		psrlq mm0,16
		psrlq mm1,24
		psllq mm2,32
		psllq mm3,24
		por mm0,mm1
		por mm2,mm3
		por mm0,mm2
		movq qword ptr [edi+8],mm0

		movq mm1,qword ptr [esi+16]
		movq mm2,qword ptr [esi+24]
		movq mm3,qword ptr [esi+24]
		pand mm1,mm7
		pand mm2,mm6
		pand mm3,mm7
		psrlq mm1,40
		psllq mm2,16
		psllq mm3,8
		por mm1,mm2
		por mm1,mm3
		movq qword ptr [edi+16],mm1

		add esi,32
		add edi,24

		dec ecx
		jnz LOOP2
		
		pop edi
//		pop eax
		add edi,eax
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

void CMMX::_MMX32to32(void)
{
	//MMX‚ð‚Â‚©‚Á‚Ä64byte‚²‚Æ“]‘—‚·‚é‚É‚á

	int screenSizeX = m_screenSizeX;
	int screenSizeY = m_screenSizeY;

	if (m_RGB32Mode == FALSE)
	{
		MMX32to32BGR(0,0,screenSizeX,screenSizeY);
		return;
	}


	int lPitch = m_lPitch;
	LPVOID src = m_lpScreenBuffer;
	LPVOID dst = m_lpSurface;

	int loopX = screenSizeX / (32/4);

#if defined _WIN64
	INT32 lPitch64 = (INT32)m_lPitch;
	INT32* src64 = (INT32*)m_lpScreenBuffer;
	INT32* dst64Org = (INT32*)m_lpSurface;

	for (int j = 0; j < screenSizeY; j++)
	{
		INT32* dst64 = dst64Org;

		for (int i = 0; i < screenSizeX; i++)
		{
			*dst64 = *src64;
			src64++;
			dst64++;
		}
		dst64Org += lPitch / 4;
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

		emms

		mov esi,src
		mov edi,dst

		mov eax,lPitch
		mov edx,screenSizeY
LOOP1:
//		push eax
		push edi
		mov ecx,loopX
LOOP2:
//		align 16
		movq mm0,qword ptr [esi]
		movq mm1,qword ptr [esi + 8*1]
		movq mm2,qword ptr [esi + 8*2]
		movq mm3,qword ptr [esi + 8*3]

//		movq mm4,qword ptr [esi + 8*4]
//		movq mm5,qword ptr [esi + 8*5]
//		movq mm6,qword ptr [esi + 8*6]
//		movq mm7,qword ptr [esi + 8*7]

//		mov ebx,[esi+32]//prefetch cache ‚³‚¢‚²‚Ì‚¢‚Á‚©‚¢‚Í‚â‚Á‚Ä‚Í‚¢‚¯‚É‚á‚¢
//		mov ebx,[esi+64*1+32]


		movq qword ptr[edi],mm0
		movq qword ptr[edi+8*1],mm1
		movq qword ptr[edi+8*2],mm2
		movq qword ptr[edi+8*3],mm3

//		movq qword ptr[edi+8*4],mm4
//		movq qword ptr[edi+8*5],mm5
//		movq qword ptr[edi+8*6],mm6
//		movq qword ptr[edi+8*7],mm7

		add esi,32
		add edi,32
		dec ecx
		jnz LOOP2
		
		pop edi
//		pop eax
		add edi,eax
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

