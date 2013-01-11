//
// EffectStretch.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "EffectStretch.h"


CEffectStretch::CEffectStretch(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	int sizeX = CMyGraphics::GetScreenSizeX();

	m_deltaX = new int [sizeX];
}

CEffectStretch::~CEffectStretch()
{
	End();
}

void CEffectStretch::End(void)
{
	DELETEARRAY(m_deltaX);
}

BOOL CEffectStretch::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int para[8];
	int k = paraKosuu;
	if (k>7) k = 7;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;
	if (paraKosuu<2) para[1] = screenSizeX/4;
	if (para[1]<0) para[1] = 0;
	if (para[1] >= screenSizeX) para[1] = screenSizeX-1;
	if (paraKosuu<3) para[2] = screenSizeY/4;
	if (para[2]<0) para[2] = 0;
	if (para[2]>=screenSizeY) para[2] = screenSizeY-1;
	if (paraKosuu<4) para[3] = screenSizeX - para[1]*2;
	if ((para[1]+para[3]) > screenSizeX) para[3] = screenSizeX - para[1];
	if (para[3]<1) para[3] = 1;
	if (paraKosuu<5) para[4] = screenSizeY - para[2]*2;
	if ((para[2] + para[4]) > screenSizeY) para[4] = screenSizeY - para[2];
	if (para[4]<1) para[4] = 1;

	if (paraKosuu<6) para[5] = 0;	//speedType
	if (paraKosuu<7) para[6] = 0;	//subFrame

	lp->flag = TRUE;
	lp->command = EFFECT_STRETCH;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<7;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectStretch::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectStretch::BeginPrint(LPVOID para,int layer)
{

}

void CEffectStretch::Init(LPVOID para,int layer)
{
}

void CEffectStretch::Calcu(LPVOID lpEffect,int layer)
{
}

#if !defined _TINYAN3DLIB_
void CEffectStretch::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();



	int x1 = lp->para[1];
	int y1 = lp->para[2];
	int x2 = lp->para[3] + lp->para[1];
	int y2 = lp->para[4] + lp->para[2];

	if (x1<0) x1 = 0;
	if (x2>=screenSizeX) x2 = screenSizeX;
	if (y1<0) y1 = 0;
	if (y2>screenSizeY) y2 = screenSizeY;
	
	if (x1>=x2) return;
	if (y1>=y2) return;

	int pic = lp->pic;
	if (pic == -1) return;

//	int sizeX = x2 - x1;
//	int sizeY = y2 - y1;

	RECT rc;
	RECT rc0;
	SetRect(&rc0,0,0,screenSizeX,screenSizeY);
	CPicture* lpPic = m_allEffect->GetPicture(layer);

	lpPic->GetPicSize(&rc);
	if (!EqualRect(&rc,&rc0)) return;

	int picSizeX = rc.right;

	if (lpPic->Check256()) return;

	int* ptr = lpPic->GetPictureBuffer();

	int count = lp->count;
	int countMax = lp->countMax;
	int speedType = lp->para[5];
	int subFrame = lp->para[6];

	int ml = CCalcuSpeed::calcu(count,countMax,0,256,subFrame,speedType);

	int dx1 = -x1;
	int dy1 = -y1;
	int dx2 = screenSizeX-x2;
	int dy2 = screenSizeY-y2;

	int startX = x1 + (dx1 * ml) / 256;
	int startY = y1 + (dy1 * ml) / 256;
	int endX = x2 + (dx2 * ml) / 256;
	int endY = y2 + (dy2 * ml) / 256;

	if (startX >= screenSizeX) return;
	if (startY >= screenSizeY) return;
	if (endX<0) return;
	if (endY<0) return;

	if (startX<0) startX = 0;
	if (startY<0) startY = 0;

	if (endX>screenSizeX) endX = screenSizeX;
	if (endY>screenSizeY) endY = screenSizeY;

	int sx = endX - startX;
	int sy = endY - startY;


	if (sx <= 0) return;
	if (sy <= 0) return;

	int* screen = CMyGraphics::GetScreenBuffer();

	screen += startY * screenSizeX;
	screen += startX;

	int* screen0 = screen;


	int sizeXdiv2 = screenSizeX / 2;
	int sizeYdiv2 = screenSizeY / 2;

//	int sizeXdiv4 = screenSizeX / 4;
//	int sizeYdiv4 = screenSizeY / 4;

	int srclPitch = picSizeX * 4;
	int dstPitch = screenSizeX * 4;

//	if ((houkou == 0) && (c == 0))
//	if (ml == 0)

	int justMode = -1;

	for (int b=2;b<=5;b++)
	{
//		if ((x2-x1) == (screenSizeX/b))
		if (sx == (screenSizeX/b))
		{
//			if ((y2-y1) == (screenSizeY/b))
			if (sy == (screenSizeY/b))
			{
				justMode = b;
				break;
			}
		}
	}


	if (justMode != -1)
	{
		//•½‹Ï‚ÅA‚©‚­ 128x96(5x5) or 160x120(4x4) 213x160(3x3) 320x240(2x2)

//		if ( ((x2-x1)== sizeXdiv2) && ((y2-y1)==sizeYdiv2) )
		if (justMode == 2)
		{
			int* dst00 = screen0;
//			CPicture* lpPic = m_pic[pic];
			int* ptr00 = lpPic->GetPictureBuffer();


			int srcPitch = picSizeX*4 * 2;


			__asm
			{
				push eax
				push ebx
				push ecx
				push edx
				push esi
				push edi

				mov esi,ptr00
				mov edi,dst00

				pxor mm0,mm0

				mov ecx,sizeYdiv2
LOOP01:
				push ecx
				push esi
				push edi

				mov ecx,sizeXdiv2
LOOP02:
				movq mm1,[esi]
				movq mm2,mm1

				add esi,srclPitch
				movq mm3,[esi]
				punpcklbw mm1,mm0
				sub esi,srclPitch

				movq mm4,mm3
				punpckhbw mm2,mm0

				punpcklbw mm3,mm0
				paddw mm1,mm2

				punpcklbw mm4,mm0

				paddw mm3,mm4

				paddw mm1,mm3

				psrlw mm1,2
				packuswb mm1,mm1
				movd eax,mm1

				mov [edi],eax

				add esi,8
				add edi,4

				dec ecx
				jnz LOOP02


				pop edi
				pop esi
				pop ecx
				add esi,srcPitch
				add edi,dstPitch
				dec ecx
				jnz LOOP01


				pop edi
				pop esi
				pop edx
				pop ecx
				pop ebx
				pop eax
				emms
			}
			return;
		}



//		if ((((x2-x1)== 128) && ((y2-y1)==96)) || (((x2-x1)== 160) && ((y2-y1)==120)) || (((x2-x1)== 213) && ((y2-y1)==160)))
//		if ( ((x2-x1)== sizeXdiv4) && ((y2-y1)==sizeYdiv4) )
		if (justMode != -1)
		{
			int lx = x2 - x1;
			int ly = y2 - y1;
			int sx = screenSizeX / lx;
			int sy = screenSizeY / ly;

			int dv = sx * sy;

			int* dst0 = screen0;

			int* src0 = ptr;
			for (int j=0;j<ly;j++)
			{
				int* dst = dst0;
				int* src00 = src0;

				for (int i=0;i<lx;i++)
				{
					int r = 0;
					int g = 0;
					int b = 0;
					int* src000 = src00;

					for (int jj=0;jj<sy;jj++)
					{
						int* src = src000;
						for (int ii=0;ii<sx;ii++)
						{
							int c = *src++;
							r += ((c >> 16) & 0xff);
							g += ((c >> 8) & 0xff);
							b += (c & 0xff);
						}
						src000 += picSizeX;
					}

					r /= dv;
					g /= dv;
					b /= dv;

					src00 += sx;
					*dst++ = (r<<16) | (g<<8) | b;
				}

				src0 += picSizeX * sy;
				dst0 += screenSizeX;
			}

			return;
		}
	}



	int ddx = screenSizeX*256 / sx;
	int ddy = screenSizeY*256 / sy;

	int* src = ptr;

	int* deltaX = m_deltaX;


	int ssx = sx;
	if (ssx<1) ssx = 1;
	int ssdx = 0;
	for (int i=0;i<sx;i++)
	{
		int sxsx2 = screenSizeX*(i+1)/sx;	//@@

		int dlt = sxsx2 - ssdx;
		deltaX[i] = dlt << 2;

		ssdx = sxsx2;
	}


	int* deltaXPtr = deltaX;

	int sizeXmul4 = picSizeX * 4;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		mov edi,screen
		mov esi,src
		mov edx,sy
		mov ebx,0	;yyy
LOOP1:
		push edx
		push edi
		
		push ebx
		push esi

//		mov ebx,0	;xxx
		mov ebx,deltaXPtr
		mov ecx,sx
LOOP2:
		mov eax,[esi]
		mov [edi],eax

//		add ebx,ddx
//		mov eax,ebx

//		shr eax,8
		
//		shl eax,2
		
//		add esi,eax
		
//		and ebx,0ffh
		add esi,[ebx]
		add ebx,4

		add edi,4
		dec ecx
		jnz LOOP2

		pop esi
		pop ebx

		add ebx,ddy
		mov eax,ebx
		shr eax,8
;;		shl eax,2
		mov edx,sizeXmul4
		mul edx
		add esi,eax
		and ebx,0ffh
		pop edi
		pop edx
		add edi,sizeXmul4
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

	return;
}
#else
void CEffectStretch::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


//	int putX = lp->para[1];
//	int putY = lp->para[2];
//	int putSizeX = lp->para[3];
//	int putSizeY = lp->apra[4];

	int count = lp->count;
	int countMax = lp->countMax;
	int speedType = lp->para[5];
	int subFrame = lp->para[6];

	int ml = CCalcuSpeed::calcu(count,countMax,0,256,subFrame,speedType);

	int x1 = lp->para[1];
	int y1 = lp->para[2];
	int x2 = lp->para[3] + lp->para[1];
	int y2 = lp->para[4] + lp->para[2];

	if (x1<0) x1 = 0;
	if (x2>=screenSizeX) x2 = screenSizeX;
	if (y1<0) y1 = 0;
	if (y2>screenSizeY) y2 = screenSizeY;
	
	if (x1>=x2) return;
	if (y1>=y2) return;

	int pic = lp->pic;
	if (pic == -1) return;

	RECT rc;
	RECT rc0;
	SetRect(&rc0,0,0,screenSizeX,screenSizeY);
	CPicture* lpPic = m_allEffect->GetPicture(layer);

	lpPic->GetPicSize(&rc);
	if (!EqualRect(&rc,&rc0)) return;

	int picSizeX = rc.right;

	if (lpPic->Check256()) return;

	int dx1 = -x1;
	int dy1 = -y1;
	int dx2 = screenSizeX-x2;
	int dy2 = screenSizeY-y2;

	int startX = x1 + (dx1 * ml) / 256;
	int startY = y1 + (dy1 * ml) / 256;
	int endX = x2 + (dx2 * ml) / 256;
	int endY = y2 + (dy2 * ml) / 256;

	if (startX >= screenSizeX) return;
	if (startY >= screenSizeY) return;
	if (endX<0) return;
	if (endY<0) return;

	if (startX<0) startX = 0;
	if (startY<0) startY = 0;

	if (endX>screenSizeX) endX = screenSizeX;
	if (endY>screenSizeY) endY = screenSizeY;

	int sx = endX - startX;
	int sy = endY - startY;


	if (sx <= 0) return;
	if (sy <= 0) return;


	int ps = 100;
	lpPic->StretchBlt1(startX,startY,sx,sy,0,0,screenSizeX,screenSizeY,ps);
}

#endif


BOOL CEffectStretch::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}
