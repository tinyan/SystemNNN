//
// effectBokashi.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectBGBokashi.h"


CEffectBGBokashi::CEffectBGBokashi(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	m_work0 = new int[(screenSizeX+256*2)*4+32];//rgba
#if defined _WIN64
	long long p = (long long)m_work0;
#else
	int p = (int)m_work0;
#endif
	p += 7;
	p &= ~7;

	m_work = (int*)p;

	m_gyakuTable = new int[256+1];

	m_gyakuTable[0] = 0;

	for (int i=1;i<=256;i++)
	{
		int d = 32768 / i;
		if (d>=32768) d = 32767;
		m_gyakuTable[i] = d;
	}


#if defined _TINYAN3DLIB_
	SetTextureKosuu(1);
	Create("Bokashi");
#endif

}

CEffectBGBokashi::~CEffectBGBokashi()
{
	End();
}

void CEffectBGBokashi::End(void)
{
	DELETEARRAY(m_gyakuTable);
	DELETEARRAY(m_work0);
}


BOOL CEffectBGBokashi::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[16];
	int k = paraKosuu;
	if (k>16) k = 16;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}


	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 8;	//最大ぼかしX
	if (para[1]<1) para[1] = 1;
	if (para[1]>256) para[1] = 256;
	if (paraKosuu<3) para[2] = 8;	//Y
	if (para[2]<1) para[2] = 1;
	if (para[2]>256) para[2] = 256;

	if (para[1] * para[2] > 256)
	{
		para[2] = 256 / para[1];
	}

	if (paraKosuu<4) para[3] = 100;
	if (para[3]<0) para[3] = 0;
	if (para[3]>100) para[3] = 100;

	if (paraKosuu<5) para[4] = para[3];
	if (para[4]<0) para[4] = 0;
	if (para[4]>100) para[4] = 100;

	if (paraKosuu<6) para[5] = 0;
	if (paraKosuu<7) para[6] = 0;
	if (para[6]<0) para[6] = 0;
	if (paraKosuu<8) para[7] = 0;
//	if (paraKosuu<9) para[8] = 0;

//	if (paraKosuu<8) para[7] = 0;





	lp->flag = TRUE;
	lp->command = EFFECT_BGBOKASHI;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectBGBokashi::CountIsMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

//	lp->command = EFFECT_NOP;
//	if (lp->pic == -1)
//	{
//		lp->flag = FALSE;
//	}
//
//	return TRUE;
	return FALSE;
}


void CEffectBGBokashi::BeginPrint(LPVOID para,int layer)
{

}

void CEffectBGBokashi::Init(LPVOID para,int layer)
{
}

void CEffectBGBokashi::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectBGBokashi::Print(LPVOID lpEffect,int layer)
{
	if (layer == -1) layer = 0;

	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();




	int count = lp->count;
	int countMax = lp->countMax;
	int speedType = lp->para[5];
	int subFrame = lp->para[6];
	int startPercent = lp->para[4];
	int endPercent = lp->para[3];



	int ps = CCalcuSpeed::calcu(count,countMax,startPercent,endPercent,subFrame,speedType);


	int bokashiSizeX = (lp->para[1] * ps) / (100*1);
	int bokashiSizeY = (lp->para[2] * ps) / (100*1);
	
	if (lp->para[7])
	{
		if (bokashiSizeX > 1)
		{
			if ((bokashiSizeX & 1) == 0)
			{
				bokashiSizeX--;
			}
		}
		if (bokashiSizeY > 1)
		{
			if ((bokashiSizeY & 1) == 0)
			{
				bokashiSizeY--;
			}
		}
	}



	if (bokashiSizeX<1) bokashiSizeX = 1;
	if (bokashiSizeX>256) bokashiSizeX = 256;
	if (bokashiSizeY<1) bokashiSizeY = 1;
	if (bokashiSizeY>256) bokashiSizeY = 256;

	if (bokashiSizeX * bokashiSizeY > 256)
	{
		bokashiSizeY = 256 / bokashiSizeX;
	}

	CPicture* lpPic = m_allEffect->GetPicture(layer);	//debug 2005-05-08
	if (lpPic == NULL) return;

	POINT dstPoint = m_allEffect->GetDstPoint(layer);
	SIZE sz = m_allEffect->GetDstSize(layer);

	int putX = dstPoint.x;
	int putY = dstPoint.y;

	int sizeX = sz.cx;
	int sizeY = sz.cy;

	if ((bokashiSizeX * bokashiSizeY) == 1)
	{
		lpPic->Blt(dstPoint.x,dstPoint.y,0,0,sz.cx,sz.cy,FALSE);

		return;
	}

	if (lpPic->Check256()) return;

	int* src = (int*)lpPic->GetPictureBuffer();
	if (src == NULL) return;

	char* mask = lpPic->GetMaskPic();
//	if (mask == NULL) return;

	SIZE sz2 = lpPic->GetPicSize();
	int srcPitch = sz2.cx;
//	int srcPitchInt = srcPitch / sizeof(int);

	int srcX = 0;
	int srcY = 0;

	//clip chara
	int clipStartX = lpPic->m_charaClipXStart;
	int clipStartY = lpPic->m_charaClipYStart;
	int clipEndX = lpPic->m_charaClipXEnd;
	int clipEndY = lpPic->m_charaClipYEnd;

	if (srcX < clipStartX)
	{
		int deltaX = clipStartX - srcX;
		sizeX -= deltaX;
		srcX += deltaX;
		putX += deltaX;
	}

	if (srcY < clipStartY)
	{
		int deltaY = clipStartY - srcY;
		sizeY -= deltaY;
		srcY += deltaY;
		putY += deltaY;
	}

	if ((srcX + sizeX) > clipEndX)
	{
		int deltaX = srcX + sizeX - clipEndX;
		sizeX -= deltaX;
	}

	if ((srcY + sizeY) > clipEndY)
	{
		int deltaY = srcY + sizeY - clipEndY;
		sizeY -= deltaY;
	}

	int bokashiXLeft = bokashiSizeX / 2;
	int bokashiXRight = bokashiSizeX - bokashiXLeft;
	int bokashiYTop = bokashiSizeY / 2;
	int bokashiYBottom = bokashiSizeY - bokashiYTop;

	srcX -= bokashiXLeft;
	putX -= bokashiXLeft;
	sizeX += bokashiXLeft;
	sizeX += bokashiXRight;

	srcY -= bokashiYTop;
	putY -= bokashiYTop;
	sizeY += bokashiYTop;
	sizeY += bokashiYBottom;


	//screen clip
	if (putX < 0)
	{
		int deltaX = 0 - putX;
		srcX += deltaX;
		putX += deltaX;
		sizeX -= deltaX;
	}

	if (putY < 0)
	{
		int deltaY = 0 - putY;
		srcY += deltaY;
		putY += deltaY;
		sizeY -= deltaY;
	}

	if ((putX + sizeX) > screenSizeX)
	{
		int deltaX = putX + sizeX - screenSizeX;
		sizeX -= deltaX;
	}

	if ((putY + sizeY) > screenSizeY)
	{
		int deltaY = putY + sizeY - screenSizeY;
		sizeY -= deltaY;
	}

	//clip print
	if ((sizeX <= 0) || (sizeY <= 0)) return;







	int calcuXLeft = putX - bokashiXLeft * 2;
	int calcuXRight = putX + sizeX + bokashiXRight * 2;
	int calcuXLeftSrc = srcX - bokashiXLeft * 2;
	int calcuXRightSrc = srcX + sizeX + bokashiXRight * 2;


	int calcuYTop = srcY - bokashiYTop;
	int calcuYBottom = srcY + sizeY + bokashiYBottom;

	if (calcuXLeftSrc < clipStartX)
	{
		int deltaX = clipStartX - calcuXLeftSrc;

		calcuXLeft += deltaX;
		calcuXLeftSrc += deltaX;
	}

	if (calcuXRightSrc > clipEndX)
	{
		int deltaX = calcuXRightSrc - clipEndX;

		calcuXRight -= deltaX;
		calcuXRightSrc -= deltaX;
	}
//	if (calcuYTop < clipStartY) calcuYTop = clipStartY;
//	if (calcuYBottom > clipEndY) calcuYBottom = clipEndY;


	//初期テーブル作成
	ZeroMemory(m_work,(screenSizeX + 256*2) * 4 * sizeof(int));

	int firstYStart = srcY - bokashiYTop;
	int firstYEnd = srcY + bokashiYBottom;
	if (firstYStart < clipStartY) firstYStart = clipStartY;
	if (firstYEnd > clipEndY) firstYEnd = clipEndY;

	int calcuSizeX = calcuXRight - calcuXLeft;

//	for (int i=calcuXLeft;i<calcuXRight;i++)
	for (int i=0;i<calcuSizeX;i++)
	{
		unsigned int r = 0;
		unsigned int g = 0;
		unsigned int b = 0;
		unsigned int a = 0;

		for (int j=firstYStart;j<firstYEnd;j++)
		{
			int c = *(src + i+calcuXLeftSrc + j * srcPitch);

			unsigned int rr = (c >> 16) & 0xff;
			unsigned int gg = (c >>  8) & 0xff;
			unsigned int bb = (c      ) & 0xff;

			r += rr;
			g += gg;
			b += bb;
			a += 1;
		}

		m_work[(i+calcuXLeft+256)*2+0] = (g<<16) | b;
		m_work[(i+calcuXLeft+256)*2+1] = (a << 16) | r;
	}
/*
	if (1)
	{
		int b = m_work[(calcuXLeft+256)*4+0];
		int g = m_work[(calcuXLeft+256)*4+1];
		int r = m_work[(calcuXLeft+256)*4+2];
		int a = m_work[(calcuXLeft+256)*4+3];

		for (int i=0;i<calcuXLeft+256;i++)
		{
			m_work[i*4+0] = b;
			m_work[i*4+1] = g;
			m_work[i*4+2] = r;
			m_work[i*4+3] = a;
		}

		b = m_work[(calcuSizeX-1+calcuXLeft+256)*4+0];
		g = m_work[(calcuSizeX-1+calcuXLeft+256)*4+1];
		r = m_work[(calcuSizeX-1+calcuXLeft+256)*4+2];
		a = m_work[(calcuSizeX-1+calcuXLeft+256)*4+3];

		for (int i=calcuXLeft+calcuXSize+256;i<screenSizeX*2+256*2;i++)
		{
			m_work[i*4+0] = b;
			m_work[i*4+1] = g;
			m_work[i*4+2] = r;
			m_work[i*4+3] = a;
		}
	}
*/


	int firstXStart = putX - bokashiXLeft;
	int firstXEnd = putX + bokashiXRight;

	int* screen = CMyGraphics::GetScreenBuffer();

	int bokashiSizeXY = bokashiSizeX * bokashiSizeY;

/*
	for (int j=0;j<sizeY;j++)
	{
		//calcu first point data
		int r = 0;
		int g = 0;
		int b = 0;
		int a = 0;

		for (int i=firstXStart;i<firstXEnd;i++)
		{
			r += m_work[(i+256)*4+0];
			g += m_work[(i+256)*4+1];
			b += m_work[(i+256)*4+2];
			a += m_work[(i+256)*4+3];
		}


		int* dst = screen + screenSizeX * (putY + j) + putX;

		//calcu dot
		for (int i=0;i<sizeX;i++)
		{
			if (a>0)
			{
//				int rr = r / a;
//				int gg = g / a;
//				int bb = b / a;
				int aa = a / bokashiSizeXY;

				int rra = r / bokashiSizeXY;
				int gga = g / bokashiSizeXY;
				int bba = b / bokashiSizeXY;


				int cc = *dst;
				int r1 = (cc >> 16) & 0xff;
				int g1 = (cc >>  8) & 0xff;
				int b1 = (cc      ) & 0xff;

//				int rrr = (r1 * (255-aa) + rr * aa) / 255;
//				int ggg = (g1 * (255-aa) + gg * aa) / 255;
//				int bbb = (b1 * (255-aa) + bb * aa) / 255;
				int rrr = (r1 * (255-aa) + rra) / 255;
				int ggg = (g1 * (255-aa) + gga) / 255;
				int bbb = (b1 * (255-aa) + bba) / 255;

				int c = (rrr << 16) | (ggg << 8) | bbb;
				*dst = c;
			}



			//dot next
			int checkXLeft = putX + i - bokashiXLeft;
			if ((checkXLeft >= calcuXLeft) && (checkXLeft <calcuXRight))
			{
				r -= m_work[(checkXLeft+256)*4+0];
				g -= m_work[(checkXLeft+256)*4+1];
				b -= m_work[(checkXLeft+256)*4+2];
				a -= m_work[(checkXLeft+256)*4+3];
			}

			int checkXRight = putX + i + bokashiXRight;
			if ((checkXRight >= calcuXLeft) && (checkXRight <calcuXRight))
			{
				r += m_work[(checkXRight+256)*4+0];
				g += m_work[(checkXRight+256)*4+1];
				b += m_work[(checkXRight+256)*4+2];
				a += m_work[(checkXRight+256)*4+3];
			}

			dst++;
		}


		//next line

		//sub upper data
		int checkYTop = srcY + j - bokashiYTop;
		if ((checkYTop >= clipStartY) && (checkYTop < clipEndY))
		{
//			for (int i=calcuXLeft;i<calcuXRight;i++)
			for (int i=0;i<calcuSizeX;i++)
			{
				int c = *(src + i + calcuXLeftSrc + checkYTop * srcPitch);
				int rr = (c >> 16) & 0xff;
				int gg = (c >>  8) & 0xff;
				int bb = (c      ) & 0xff;
				int aa = 0xff & (int)(*(mask + i + calcuXLeftSrc + checkYTop * srcPitch));

				rr *= aa;
				gg *= aa;
				bb *= aa;

				m_work[(calcuXLeft + i + 256)*4+0] -= rr;
				m_work[(calcuXLeft + i + 256)*4+1] -= gg;
				m_work[(calcuXLeft + i + 256)*4+2] -= bb;
				m_work[(calcuXLeft + i + 256)*4+3] -= aa;
			}
		}

		//add lower data
		int checkYBottom = srcY + j + bokashiYBottom;
		if ((checkYBottom >= clipStartY) && (checkYBottom < clipEndY))
		{
			for (int i=0;i<calcuSizeX;i++)
//			for (int i=calcuXLeft;i<calcuXRight;i++)
			{
				int c = *(src + i + calcuXLeftSrc + checkYBottom * srcPitch);
				int rr = (c >> 16) & 0xff;
				int gg = (c >>  8) & 0xff;
				int bb = (c      ) & 0xff;
				int aa = 0xff & (int)(*(mask + i + calcuXLeftSrc + checkYBottom * srcPitch));

				rr *= aa;
				gg *= aa;
				bb *= aa;

				m_work[(calcuXLeft + i + 256)*4+0] += rr;
				m_work[(calcuXLeft + i + 256)*4+1] += gg;
				m_work[(calcuXLeft + i + 256)*4+2] += bb;
				m_work[(calcuXLeft + i + 256)*4+3] += aa;
			}
		}
	}
*/


	int bottomSpecial = 0;
//	if (lp->para[8])
//	{
//		bottomSpecial = clipEndY - 1;
//	}


	int checkYTopEAX = srcY - bokashiYTop;
	int checkYBottomEAX = srcY + bokashiYBottom;
	int* workStartAsm = m_work;
	int* workStart = m_work;

	workStartAsm += (calcuXLeft + 256) * 2;
	int dstPitch = screenSizeX * sizeof(int);

	int* dstAsm = screen + screenSizeX * putY + putX;

	int bokashiXLeftInt8 = -bokashiXLeft * 8;
	int bokashiXRightInt8 = bokashiXRight * 8;

	int bokashiDivXY65535 = 65536 / (bokashiSizeX * bokashiSizeY);
	if (bokashiDivXY65535 >= 32768) bokashiDivXY65535 = 32767;

	int* gyakuTable = m_gyakuTable;

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

		mov eax,bokashiDivXY65535
		movd mm7,eax
		punpcklwd mm7,mm7
		punpckldq mm7,mm7

		mov ebx,gyakuTable


		mov edi,dstAsm
		mov ecx,sizeY
LOOP1:
		push ecx
		push edi


		//calcu first point data
		pxor mm1,mm1
//		pxor mm2,mm2
		mov eax,firstXStart
		mov ecx,firstXEnd
		sub ecx,eax
		js SKIP1
		jz SKIP1
		add eax,256
//		shl eax,1
		shl eax,1
		shl eax,1
		shl eax,1
		mov esi,workStart
		add esi,eax
LOOP2:
		paddw mm1,[esi]
//		paddd mm2,[esi+8]
		add esi,8
		dec ecx
		jnz LOOP2
SKIP1:


		mov ecx,sizeX

		mov eax,putX
		add eax,256
//		shl eax,1
		shl eax,1
		shl eax,1
		shl eax,1
		add eax,workStart
		mov esi,eax
LOOP3:
		//slow
		movq mm3,mm1
		psrlq mm3,48
		movd eax,mm3
		or eax,eax
		jz SKIP2

		add eax,eax
		add eax,eax
		mov eax,[ebx+eax];
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6


		movq mm3,mm1
		psrlw mm3,1
		movq mm4,mm3
		pmulhw mm3,mm6
		pmullw mm4,mm6
		psllw mm3,2
		psrlw mm4,14
		por mm3,mm4

		packuswb mm3,mm0
		movd eax,mm3
		mov [edi],eax


SKIP2:
		//dot next
		mov eax,bokashiXLeftInt8
		psubw mm1,[esi+eax]
		mov eax,bokashiXRightInt8
		paddw mm1,[esi+eax]

		add edi,4
		add esi,8
		dec ecx
		jnz LOOP3



		//sub upper data
		mov eax,[checkYTopEAX]
		inc eax
		mov [checkYTopEAX],eax
		dec eax

		cmp eax,clipStartY
		js SKIP10
		cmp eax,clipEndY
		jns SKIP10

		mov edx,srcPitch
		mul edx
//		mov ebx,eax
		shl eax,1
		shl eax,1
		add eax,src

		mov edx,calcuXLeftSrc
		shl edx,1
		shl edx,1
		add eax,edx

		mov esi,eax

//		add ebx,calcuXLeftSrc
//		add ebx,mask

		mov edi,workStartAsm

		mov ecx,calcuSizeX
LOOP10:
		mov eax,[esi]
		and eax,00ffffffh
		add eax,01000000h
		movd mm1,eax
		punpcklbw mm1,mm0

		movq mm3,[edi]
		psubw mm3,mm1
		movq [edi],mm3

		add esi,4
//		inc ebx
		add edi,8

		dec ecx
		jnz LOOP10
SKIP10:



		//add lower data
		mov eax,[checkYBottomEAX]
		inc eax
		mov [checkYBottomEAX],eax
		dec eax

		cmp eax,clipStartY
		js SKIP20
		cmp eax,clipEndY
		jns SKIP20

		mov edx,srcPitch
		mul edx
//		mov ebx,eax
		shl eax,1
		shl eax,1
		add eax,src

		mov edx,calcuXLeftSrc
		shl edx,1
		shl edx,1
		add eax,edx

		mov esi,eax

//		add ebx,calcuXLeftSrc
//		add ebx,mask

		mov edi,workStartAsm

		mov ecx,calcuSizeX
LOOP20:
		mov eax,[esi]
		and eax,00ffffffh
		add eax,01000000h
		movd mm1,eax
		punpcklbw mm1,mm0

		movq mm3,[edi]
		paddw mm3,mm1
		movq [edi],mm3

		add esi,4
//		inc ebx
		add edi,8

		dec ecx
		jnz LOOP20
SKIP20:




		pop edi
		add edi,dstPitch
		pop ecx
		dec ecx
		jnz LOOP1






		jmp EXIT1

EXIT1:
		emms
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax

	}
#endif


/*

	
//	int putX = m_effect->m_effect[layer].dst.left;
//	int putY = m_effect->m_effect[layer].dst.top;
////	int srcX = m_effect->m_effect[layer].src.left;
//	//int srcY = m_effect->m_effect[layer].src.top;
//	int sizeX = m_effect->m_effect[layer].dst.right;
//	int sizeY = m_effect->m_effect[layer].dst.bottom;


	int srcX = -putX;
	int srcY = -putY;

	if ((srcX<0) || (srcX+screenSizeX>sizeX) || (srcY<0) || (srcY+screenSizeY>sizeY)) return;

	if ((bokashiSizeX == 1) && (bokashiSizeY == 1))
	{
		lpPic->Blt(putX,putY,0,0,sizeX,sizeY,FALSE);
		return;
	}


	int loopY = screenSizeY;
	int loopX = screenSizeX;

	int lPitch = screenSizeX * sizeof(int);
	int srclPitch = sizeX * sizeof(int);

	long double mm1Buffer = 0.0;

	int startY = 0;
	int endY = screenSizeY - (bokashiSizeY-1);

//	int maeY = (c * (endY - startY)) / dv;
	int maeY = startY;



	int* src = (int*)lpPic->GetPictureBuffer();
	if (src == NULL) return;

#if defined _TINYAN3DLIB_
	src += 128 / sizeof(int);
#endif

	src += srcX;
	src += srcY * sizeX;

	int p = (int)m_work;
	p += 31;
	p &= ~31;
	int* alignedWork = (int*)p;
	int* xTable = alignedWork + screenSizeX * 2;

	int div65536 = (65536 * 1) / (bokashiSizeX * bokashiSizeY);
	if (div65536 >= 32768) div65536 = 32767;

	int startX = 0;
	int endX = screenSizeX - (bokashiSizeX - 1);

	for (int i=0;i<screenSizeX;i++)
	{
		*(xTable+i+1) = (i * (endX - startX)) / screenSizeX + startX;
	}
	*xTable = *(xTable+1);

	int deltaEDX = 8 * bokashiSizeX;
	int deltaGET = srclPitch * bokashiSizeY;


	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi




		movq mm1,[esi]
		movq mm7,mm1
		psubd mm7,[ebx]
		paddd mm7,[edx]
		movq [esi],mm7

		add esi,8
		add ebx,8
		add edx,8

		movq mm2,[esi]
		movq mm7,mm2
		psubd mm7,[ebx]
		paddd mm7,[edx]
		movq [esi],mm7


		psrld mm1,8+1
		psrld mm2,8+1

		packssdw mm1,mm2


//




		add esi,8
		add ebx,8
		add edx,8

		movq mm2,[esi]
		mov eax,[esi+4]
		add esi,8
		


		pxor mm0,mm0

		mov eax,div65536
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6

//
// first calcu table
//
		mov edx,screenSizeX
		mov edi,alignedWork
//		mov ebx,xTable
		mov esi,src
LOOP00:
		push esi

		mov ecx,bokashiSizeY
		pxor mm2,mm2
LOOP001:
		mov eax,[esi]
		movd mm3,eax
		add esi,srclPitch
		punpcklbw mm3,mm0
		paddw mm2,mm3
		dec ecx
		jnz LOOP001
		
		movq [edi],mm2

		pop esi
		add esi,4
//		add ebx,4
		add edi,8
		dec edx
		jnz LOOP00


//calcu start block
		pxor mm1,mm1
		mov esi,alignedWork
		mov ecx,bokashiSizeX
LOOP0:
		paddw mm1,[esi]
		add esi,8
		dec ecx
		jnz LOOP0


		mov ecx,loopY
		mov edi,dst
		mov esi,src
LOOP1:
		push ecx
		push esi
		push edi


		movq mm1Buffer,mm1

		mov ecx,loopX
		mov esi,alignedWork
		mov ebx,xTable

		add ebx,4

LOOP2:
		movq mm2,mm1
		psrlw mm2,1
		pmulhw mm2,mm6
		psllw mm2,1
		packuswb mm2,mm0
		movd eax,mm2
		mov [edi],eax
		add edi,4
		cmp ecx,1
		jz SKIP1

		mov eax,[ebx]
		add ebx,4
		cmp eax,[ebx]
		jz SKIP1
//change
		mov edx,deltaEDX
		psubw mm1,[esi]
		paddw mm1,[esi+edx]
		add esi,8
SKIP1:
		dec ecx
		jnz LOOP2

		pop edi
		pop esi
		pop ecx
		movq mm1,mm1Buffer
		add edi,lPitch
		cmp ecx,1
		jz EXIT1
//
//	next??
//
		mov eax,ecx
		dec eax
		neg eax
		add eax,loopY
//		mov edx,bokashiSize
		mov edx,endY
		sub edx,startY
		imul edx
		mov ebx,loopY
		idiv ebx
		add eax,startY
		cmp eax,maeY
		mov maeY,eax
		jz SKIP2
//
		push ecx
		push esi
		mov ebx,alignedWork
		mov edx,deltaGET
		mov ecx,loopX
LOOP30:
		movq mm3,[ebx]

		mov eax,[esi]
		movd mm2,eax
		punpcklbw mm2,mm0
		psubw mm3,mm2

		mov eax,[esi+edx]
		movd mm2,eax
		punpcklbw mm2,mm0
		paddw mm3,mm2

		movq [ebx],mm3

		add ebx,8
		add esi,4
		dec ecx
		jnz LOOP30
		pop esi
		pop ecx


		push ecx
		push esi
		mov ecx,bokashiSizeX
LOOP31:
		mov eax,[esi]
		movd mm5,eax
		punpcklbw mm5,mm0
		psubw mm1,mm5
		add esi,4
		dec ecx
		jnz LOOP31
		pop esi
		pop ecx

		mov eax,srclPitch
		mov edx,bokashiSizeY
		mul edx
		push ecx
		push esi
		add esi,eax
		mov ecx,bokashiSizeX
LOOP32:
		mov eax,[esi]
		movd mm5,eax
		punpcklbw mm5,mm0
		paddw mm1,mm5
		add esi,4
		dec ecx
		jnz LOOP32
		pop esi
		pop ecx


		add esi,srclPitch
SKIP2:
		dec ecx
		jnz LOOP1
EXIT1:
		emms
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
#if defined _TINYAN3DLIB_
	CMyDirect3D::PutMemoryToMemoryTexture(dst);
	CMyDirect3D::PutMemoryTextureToBuffer();

	SetTexture(GetBufferTexture());
	POINT dstPoint2;
	SIZE dstSize;
	POINT srcPoint;
	dstPoint2.x = 0;
	dstPoint2.y = 0;
	dstSize.cx = screenSizeX;
	dstSize.cy = screenSizeY;
	srcPoint.x = 0;
	srcPoint.y = 0;

	Blt(dstPoint2,dstSize,srcPoint);
#endif

	*/

}



BOOL CEffectBGBokashi::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}
