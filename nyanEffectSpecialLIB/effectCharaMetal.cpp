//
// effectCharaMetal.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectCharaMetal.h"



CEffectCharaMetal::CEffectCharaMetal(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(1);
	Create("CharaMetal");
#endif
}


CEffectCharaMetal::~CEffectCharaMetal()
{
	End();
}

void CEffectCharaMetal::End(void)
{
}

BOOL CEffectCharaMetal::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int para[16];
	int k = paraKosuu;
	if (k>16) k = 16;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}


	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 0;	//方向 横と斜めが実質同じ処理

	if (paraKosuu<3) para[2] = 64;	//サイズ
	if (paraKosuu<4) para[3] = 25;	//グラデ割合	0-50

	if (paraKosuu<5) para[4] = 0;	//type
	if (paraKosuu<6) para[5] = 0;	//subframe

	if (paraKosuu<7) para[6] = 255;	//あかるさR
	if (paraKosuu<8) para[7] = para[6];	//あかるさG
	if (paraKosuu<9) para[8] = para[7];	//あかるさB


	lp->flag = TRUE;
	lp->command = EFFECT_CHARAMETAL;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}


	return TRUE;
}


BOOL CEffectCharaMetal::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectCharaMetal::BeginPrint(LPVOID para,int layer)
{

}

void CEffectCharaMetal::Init(LPVOID para,int layer)
{
}


void CEffectCharaMetal::Calcu(LPVOID lpEffect,int layer)
{
}


#if defined _TINYAN3DLIB_
void CEffectCharaMetal::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int dv = lp->countMax;	//not use
	int c = lp->count;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;
	if (lpPic->Check256()) return;

	int* metalWork = m_allEffect->GetTempWork();

	SIZE sz = lpPic->GetPicSize();
	int picSizeX = sz.cx;
	int picSizeY = sz.cy;
	int sizeX = sz.cx;
	int sizeY = sz.cy;

	m_picSizeX = picSizeX;
	m_picSizeY = picSizeY;

	POINT pt = m_allEffect->GetDstPoint(layer);
	int putX = pt.x;
	int putY = pt.y;
	m_putX = putX;
	m_putY = putY;

//	int srcX = 0;
//	int srcY = 0;

//	int putX0 = putX;
//	int putY0 = putY;


	int houkou = lp->para[1];
	m_metalHoukou = houkou;
	int metalSize = lp->para[2];
	int gradSize = (lp->para[3] * metalSize) / 100;

	int speedType = lp->para[4];
	int subFrame = lp->para[5];


	m_metalSize = metalSize;

	int divSize = metalSize;
	int metalStart = 0;

	if (houkou == 0)
	{
		divSize += picSizeY;
		metalStart = -metalSize;
	}
	else if (houkou == 1)
	{
		divSize += picSizeX;
		metalStart = -metalSize;
	}
	else if (houkou == 2)
	{
		divSize += picSizeX;
		divSize += picSizeY;
		metalStart = -metalSize -picSizeY;
	}
	else if (houkou == 3)
	{
		divSize += picSizeX;
		divSize += picSizeY;
		metalStart = -metalSize;
	}

	m_metalStart = metalStart;

	int nowMetal = CCalcuSpeed::calcu(c,dv,0,divSize,subFrame,speedType);
	nowMetal += metalStart;
	m_nowMetal = nowMetal;

	//make grad table


	int akarusaR = lp->para[6];
	int akarusaG = lp->para[7];
	int akarusaB = lp->para[8];

//	ZeroMemory(metalWork,sizeof(int)*(screenSizeX+screenSizeY));

	int i;
	for (i=0;i<metalSize+1;i++)
	{
		int r = akarusaR;
		int g = akarusaG;
		int b = akarusaB;
		if (gradSize>0)
		{
			if (i<gradSize)
			{
				r = (akarusaR * i) / gradSize;
				g = (akarusaG * i) / gradSize;
				b = (akarusaB * i) / gradSize;
			}
			else if (i>=metalSize-gradSize)
			{
				r = (akarusaR * (metalSize - i)) / gradSize;
				g = (akarusaG * (metalSize - i)) / gradSize;
				b = (akarusaB * (metalSize - i)) / gradSize;
			}

			if (r<0) r = 0;
			if (r>255) r = 255;
			if (g<0) g = 0;
			if (g>255) g = 255;
			if (b<0) b = 0;
			if (b>255) b = 255;
		}

		metalWork[i] = (r<<16) | (g<<8) | b;
		
	}

	if (CheckEffectError()) return;


	CMyTexture* lpTexture = (CMyTexture*)(lpPic->GetTexture());
	SetTexture(lpTexture->GetTexture());

	if (houkou == 0)
	{
		int gradStartY = nowMetal;
		int gradY1 = nowMetal + gradSize;
		int gradY2 = nowMetal + metalSize - gradSize;
		int gradEndY = nowMetal + metalSize;

		PrintBoxSubTate(0,gradStartY,TRUE);
		PrintBoxSubTate(gradStartY,gradY1);
		PrintBoxSubTate(gradY1,gradY2);
		PrintBoxSubTate(gradY2,gradEndY);
		PrintBoxSubTate(gradEndY,picSizeY,TRUE);
	}
	else if (houkou == 1)
	{
		int gradStartX = nowMetal;
		int gradX1 = nowMetal + gradSize;
		int gradX2 = nowMetal + metalSize - gradSize;
		int gradEndX = nowMetal + metalSize;

		PrintBoxSubYoko(0,gradStartX,TRUE);
		PrintBoxSubYoko(gradStartX,gradX1);
		PrintBoxSubYoko(gradX1,gradX2);
		PrintBoxSubYoko(gradX2,gradEndX);
		PrintBoxSubYoko(gradEndX,picSizeX,TRUE);

	}
	else
	{
		int gradStartX = nowMetal;
		int gradX1 = nowMetal + gradSize;
		int gradX2 = nowMetal + metalSize - gradSize;
		int gradEndX = nowMetal + metalSize;

		if (houkou == 2)
		{
			PrintSubClip(-picSizeY-metalSize,gradStartX,TRUE);
		}
		else
		{
			PrintSubClip(-metalSize,gradStartX,TRUE);
		}

		PrintSubClip(gradStartX,gradX1);
		PrintSubClip(gradX1,gradX2);
		PrintSubClip(gradX2,gradEndX);
		if (houkou == 2)
		{
			PrintSubClip(gradEndX,picSizeX,TRUE);
		}
		else
		{
			PrintSubClip(gradEndX,picSizeX+picSizeY,TRUE);
		}
	}
}

void CEffectCharaMetal::PrintBoxSubTate(int startY,int endY,BOOL nonGradFlag)
{
	if (endY<=startY) return;
	if (startY>=m_picSizeY) return;
	if (endY<=0) return;

	int srcY1 = startY;
	int srcY2 = endY;
	if (srcY1<0)
	{
		srcY1 = 0;
	}
	if (srcY2>m_picSizeY) srcY2 = m_picSizeY;
	int sizeY = srcY2 - srcY1;
	if (sizeY<=0) return;

	PrintBoxSub(m_putX,m_putY+srcY1,0,srcY1,m_picSizeX,sizeY,nonGradFlag);
}

void CEffectCharaMetal::PrintBoxSubYoko(int startX,int endX,BOOL nonGradFlag)
{
	if (endX<=startX) return;
	if (startX>=m_picSizeX) return;
	if (endX<=0) return;

	int srcX1 = startX;
	int srcX2 = endX;
	if (srcX1<0)
	{
		srcX1 = 0;
	}
	if (srcX2>m_picSizeX) srcX2 = m_picSizeX;
	int sizeX = srcX2 - srcX1;
	if (sizeX<=0) return;

	PrintBoxSub(m_putX+srcX1,m_putY,srcX1,0,sizeX,m_picSizeY,nonGradFlag);
}


void CEffectCharaMetal::PrintBoxSub(int putX,int putY,int srcX,int srcY,int sizeX,int sizeY,BOOL nonGradFlag)
{
	POINT dstPoint[4];
	POINT srcPoint[4];
	int color[4];

	dstPoint[0].x = putX;
	dstPoint[0].y = putY;
	dstPoint[1].x = putX;
	dstPoint[1].y = putY+sizeY;
	dstPoint[2].x = putX+sizeX;
	dstPoint[2].y = putY+sizeY;
	dstPoint[3].x = putX+sizeX;
	dstPoint[3].y = putY;
	
	srcPoint[0].x = srcX;
	srcPoint[0].y = srcY;
	srcPoint[1].x = srcX;
	srcPoint[1].y = srcY+sizeY;
	srcPoint[2].x = srcX+sizeX;
	srcPoint[2].y = srcY+sizeY;
	srcPoint[3].x = srcX+sizeX;
	srcPoint[3].y = srcY;

	for (int i=0;i<4;i++)
	{
		if (nonGradFlag == FALSE)
		{
			color[i] = GetMetalData(srcPoint[i].x,srcPoint[i].y);
		}
		else
		{
			color[i] = 0;
		}
	}

	PrintPolygonColor(dstPoint,srcPoint,color,4);

}

void CEffectCharaMetal::PrintSubClip(int startX,int endX,BOOL nonGradFlag)
{
	if (startX>=endX) return;

	int startX2 = startX + m_picSizeY;
	int endX2 = endX + m_picSizeY;
	if (m_metalHoukou == 3)
	{
		startX2 = startX - m_picSizeY;
		endX2 = endX - m_picSizeY;
	}

	//max clip
	if ((startX>=m_picSizeX) && (startX2 >= m_picSizeX)) return;
	if ((endX<0) && (endX2<0)) return;


	POINT pt[6];
	int chotenKosuu = 4;
	if (m_metalHoukou == 2)
	{
		pt[0].x = startX;
		pt[0].y = 0;
		pt[1].x = startX2;
		pt[1].y = m_picSizeY;
		pt[2].x = endX2;
		pt[2].y = m_picSizeY;
		pt[3].x = endX;
		pt[3].y = 0;
	}
	else
	{
		pt[3].x = startX;
		pt[3].y = 0;
		pt[0].x = startX2;
		pt[0].y = m_picSizeY;
		pt[1].x = endX2;
		pt[1].y = m_picSizeY;
		pt[2].x = endX;
		pt[2].y = 0;
	}


	//left clip 1
	POINT pt2[6];
	int clip1 = -1;
	int clip2 = -1;

	int i;

	for (i=0;i<chotenKosuu;i++)
	{
		if (clip1 == -1)
		{
			int n1 = i;
			int n2 = (i+1) % chotenKosuu;
			int x1 = pt[n1].x;
			int x2 = pt[n2].x;
			if ((x1<0) && (x2>=0))
			{
				clip1 = n2;
			}
		}

		if (clip2 == -1)
		{
			int n1 = chotenKosuu-i;
			int n2 = n1-1;
			int x1 = pt[n1].x;
			int x2 = pt[n2].x;
			if ((x1<0) && (x2>=0))
			{
				clip2 = n2;
			}
		}
	}

	if ((clip1 != -1) && (clip2 != -1))
	{
		int n1 = clip1-1;
		int n2 = clip1;

		int x1 = pt[n1].x;
		int x2 = pt[n2].x;
		int dx = x2 - x1;
		int y1 = pt[n1].y;
		int y2 = pt[n2].y;
		int d = -x1;
		int y = y1 + ((y2-y1) * d) / dx;
		pt2[0].x = 0;
		pt2[0].y = y;
		int p = 1;
		for (i=clip1;i<=clip2;i++)
		{
			pt2[p] = pt[i];
			p++;
		}

		
		n1 = (clip2+1) % chotenKosuu;
		n2 = clip2;

		x1 = pt[n1].x;
		x2 = pt[n2].x;
		dx = x2 - x1;
		y1 = pt[n1].y;
		y2 = pt[n2].y;
		d = -x1;
		y = y1 + ((y2-y1) * d) / dx;
		pt2[p].x = 0;
		pt2[p].y = y;

		chotenKosuu = 1 + (clip2 - clip1 + 1) + 1;

		for (i=0;i<chotenKosuu;i++)
		{
			pt[i] = pt2[i];
		}
	}




	//right
	clip1 = -1;
	clip2 = -1;

	int rightN = 0;
	int rightD= pt[0].x;
	for (i=1;i<chotenKosuu;i++)
	{
		int r = pt[i].x;
		if (r > rightD)
		{
			rightD = r;
			rightN = i;
		}
	}

	for (i=0;i<chotenKosuu;i++)
	{
		int nn = (i+rightN) % chotenKosuu;
		pt2[i] = pt[nn];
	}

	for (i=0;i<chotenKosuu;i++)
	{
		pt[i] = pt2[i];
	}

	int picSizeX = m_picSizeX;
	int picSizeY = m_picSizeY;

	for (i=0;i<chotenKosuu;i++)
	{
		if (clip1 == -1)
		{
			int n1 = i;
			int n2 = (i+1) % chotenKosuu;
			int x1 = pt[n1].x;
			int x2 = pt[n2].x;
			if ((x1>=picSizeX) && (x2<picSizeX))
			{
				clip1 = n2;
			}
		}

		if (clip2 == -1)
		{
			int n1 = chotenKosuu-i;
			int n2 = n1-1;
			int x1 = pt[n1].x;
			int x2 = pt[n2].x;
			if ((x1>=picSizeX) && (x2<picSizeX))
			{
				clip2 = n2;
			}
		}
	}



	if ((clip1 != -1) && (clip2 != -1))
	{
		int n1 = clip1-1;
		int n2 = clip1;

		int x1 = pt[n1].x;
		int x2 = pt[n2].x;
		int dx = -(x2 - x1);
		int y1 = pt[n1].y;
		int y2 = pt[n2].y;
		int d = x1 - picSizeX;
		int y = y1 + ((y2-y1) * d) / dx;

		pt2[0].x = picSizeX;
		pt2[0].y = y;
		int p = 1;
		for (i=clip1;i<=clip2;i++)
		{
			pt2[p] = pt[i];
			p++;
		}

		
		n1 = (clip2+1) % chotenKosuu;
		n2 = clip2;

		x1 = pt[n1].x;
		x2 = pt[n2].x;
		dx = -(x2 - x1);
		y1 = pt[n1].y;
		y2 = pt[n2].y;
		d = x1 - picSizeX;
		y = y1 + ((y2-y1) * d) / dx;
		pt2[p].x = picSizeX;
		pt2[p].y = y;

		chotenKosuu = 1 + (clip2 - clip1 + 1) + 1;

		for (i=0;i<chotenKosuu;i++)
		{
			pt[i] = pt2[i];
		}
	}
	if (chotenKosuu<3) return;



	POINT dstPoint[6];
//	POINT srcPoint[6];
	int color[6];

	for (i=0;i<chotenKosuu;i++)
	{
		dstPoint[i].x = m_putX + pt[i].x;
		dstPoint[i].y = m_putY + pt[i].y;
	}

	for (i=0;i<chotenKosuu;i++)
	{
		if (nonGradFlag == FALSE)
		{
			color[i] = GetMetalData(pt[i].x,pt[i].y);
		}
		else
		{
			color[i] = 0;
		}
	}

	PrintPolygonColor(dstPoint,pt,color,chotenKosuu);
/*
	if (color[0] != color[2])
	{
		char mes[256];

		for (int p=0;p<chotenKosuu;p++)
		{
			wsprintf(mes,"(%d %d)",pt[p].x,pt[p].y);
			OutputDebugString(mes);
		}
		wsprintf(mes,"[%d:%d %d %d %d %d %d]\n",chotenKosuu,color[0]&0xff,color[1]&0xff,color[2]&0xff,color[3]&0xff,color[4]&0xff,color[5]&0xff);
		OutputDebugString(mes);

	}*/

}




int CEffectCharaMetal::GetMetalData(int srcX,int srcY)
{
	int k = 0;
	if (m_metalHoukou == 0)
	{
		k = srcY - m_nowMetal;
	}
	else if (m_metalHoukou == 1)
	{
		k = srcX - m_nowMetal;
	}
	else if (m_metalHoukou == 2)
	{
		k = srcX - srcY - m_nowMetal;
	}
	else
	{
		k = srcX + srcY - m_nowMetal;
	}
	if ((k<0) || (k>m_metalSize)) return 0;

	int* metalWork = m_allEffect->GetTempWork();

	return metalWork[k];
}

#else
void CEffectCharaMetal::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int dv = lp->countMax;	//not use
	int c = lp->count;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;
	if (lpPic->Check256()) return;

	int* metalWork = m_allEffect->GetTempWork();

	SIZE sz = lpPic->GetPicSize();
	int picSizeX = sz.cx;
	int picSizeY = sz.cy;
	int sizeX = sz.cx;
	int sizeY = sz.cy;

	POINT pt = m_allEffect->GetDstPoint(layer);
	int putX = pt.x;
	int putY = pt.y;
	int srcX = 0;
	int srcY = 0;

	int putX0 = putX;
	int putY0 = putY;


	int houkou = lp->para[1];
	int metalSize = lp->para[2];
	int gradSize = (lp->para[3] * metalSize) / 100;

	int speedType = lp->para[4];
	int subFrame = lp->para[5];

	int divSize = metalSize;
	if (houkou == 0)	//tate
	{
		divSize += picSizeY;
	}
	else if(houkou == 1)	//yoko
	{
		divSize += picSizeX;
	}
	else
	{
		divSize += picSizeX + picSizeY;
	}

	int start = CCalcuSpeed::calcu(c,dv,0,divSize,subFrame,speedType);

	int maxSize = screenSizeX + screenSizeY+metalSize;
	for (int i=0;i<divSize+maxSize;i++)
	{
		metalWork[i] = 0;
	}

	int startDelta = 0;
	int nanameDelta = 0;



	if (putY<0)
	{
		srcY -= putY;
		sizeY += putY;
		putY = 0;
		if (sizeY<=0) return;
	}

	if (putY+sizeY>screenSizeY)
	{
		sizeY = screenSizeY - putY;
		if (sizeY<=0) return;
	}

	if (putX<0)
	{
		srcX -= putX;
		sizeX += putX;
		putX = 0;
		if (sizeX<=0) return;
	}

	if ((putX+sizeX)>screenSizeX)
	{
		sizeX = screenSizeX - putX;
		if (sizeX<=0) return;
	}


	int startNanameDelta = 0;
	int deltaNaname = 0;

	if (houkou == 0)
	{
	}
	else if (houkou == 1)
	{
	}
	else if (houkou == 2)
	{
		// ＼
		nanameDelta = screenSizeY;
		startNanameDelta = screenSizeY;
		deltaNaname = -4;
	}
	else if (houkou == 3)
	{
		// ／
		nanameDelta = screenSizeY;
		deltaNaname = 4;
	}




	int akarusaR = lp->para[6];
	int akarusaG = lp->para[7];
	int akarusaB = lp->para[8];

	for (int i=0;i<metalSize;i++)
	{
		int n = start-metalSize + i;
		if (houkou == 0)
		{
			n += putY0;
		}
		else if (houkou == 1)
		{
			n += putX0;
		}
		else
		{
			n += putX0;
			n += putY0;
		}

		if ((n>=0) && (n<maxSize))
		{
			int r = akarusaR;
			int g = akarusaG;
			int b = akarusaB;
			if (gradSize>0)
			{
				if (i<gradSize)
				{
					r = (akarusaR * i) / gradSize;
					g = (akarusaG * i) / gradSize;
					b = (akarusaB * i) / gradSize;
				}
				else if (i>=metalSize-gradSize)
				{
					r = (akarusaR * (metalSize - i)) / gradSize;
					g = (akarusaG * (metalSize - i)) / gradSize;
					b = (akarusaB * (metalSize - i)) / gradSize;
				}

				if (r<0) r = 0;
				if (r>255) r = 255;
				if (g<0) g = 0;
				if (g>255) g = 255;
				if (b<0) b = 0;
				if (b>255) b = 255;
			}

			metalWork[n] = (r<<16) | (g<<8) | b;
		}
	}

	int* screen = CMyGraphics::GetScreenBuffer();
	
	int srcPitch = picSizeX * sizeof(int);
	int lPitch = screenSizeX * sizeof(int);
	int maskPitch = picSizeX;

	int* dst = CMyGraphics::GetScreenBuffer();
	dst += putX;
	dst += putY * screenSizeX;

	int* src = lpPic->GetPictureBuffer();
	src += srcX;
	src += srcY * picSizeX;

	char* mask = lpPic->GetMaskPic();
	if (mask == NULL) return;
	mask += srcX;
	mask += srcY * picSizeX;


	if (houkou == 0)
	{
		int* tablePtr = metalWork;
		tablePtr += putY;

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

			mov ebx,mask
			mov esi,src
			mov edi,dst
			mov edx,tablePtr
			mov ecx,sizeY
LOOP1:
			push ebx
			push ecx
			push edx
			push esi
			push edi

			mov eax,[edx]
			movd mm7,eax
//			punpcklbw mm7,mm0


			mov ecx,sizeX
LOOP2:
			mov eax,[esi]
			movd mm1,eax
			paddusb mm1,mm7
			xor edx,edx
			mov dl,[ebx]
			or edx,edx
			jz SKIP1
			cmp edx,0ffh
			jz NORMAL1

			punpcklbw mm1,mm0

			movd mm5,edx
			neg edx
			add edx,256
			movd mm6,edx
			punpcklwd mm5,mm5
			punpckldq mm5,mm5
			punpcklwd mm6,mm6
			punpckldq mm6,mm6
			mov edx,[edi]
			movd mm2,edx
			punpcklbw mm2,mm0
			pmullw mm1,mm5
			pmullw mm2,mm6
			psrlw mm1,8
			psrlw mm2,8
			paddw mm1,mm2
			packuswb mm1,mm0
NORMAL1:
			movd eax,mm1
			mov [edi],eax
SKIP1:
			add esi,4
			add edi,4
			inc ebx
			dec ecx
			jnz LOOP2


			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			add esi,srcPitch
			add edi,lPitch
			add ebx,maskPitch
			add edx,4
			dec ecx
			jnz LOOP1

			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax
			emms
		}
#endif

	}
	else
	{
		int* tablePtr = metalWork;
		tablePtr += putX;
		tablePtr += startNanameDelta;

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

			mov ebx,mask
			mov esi,src
			mov edi,dst
			mov edx,tablePtr
			mov ecx,sizeY
LOOP1B:
			push ebx
			push ecx
			push edx
			push esi
			push edi

			mov ecx,sizeX
LOOP2B:
			mov eax,[edx]
			movd mm7,eax

			mov eax,[esi]
			movd mm1,eax
			paddusb mm1,mm7

			xor eax,eax
			mov al,[ebx]
			or eax,eax
			jz SKIP1B
			cmp eax,0ffh
			jz NORMAL1B

			punpcklbw mm1,mm0

			movd mm5,eax
			neg eax
			add eax,256
			movd mm6,eax
			punpcklwd mm5,mm5
			punpckldq mm5,mm5
			punpcklwd mm6,mm6
			punpckldq mm6,mm6
			mov eax,[edi]
			movd mm2,eax
			punpcklbw mm2,mm0
			pmullw mm1,mm5
			pmullw mm2,mm6
			psrlw mm1,8
			psrlw mm2,8
			paddw mm1,mm2
			packuswb mm1,mm0
NORMAL1B:
			movd eax,mm1
			mov [edi],eax
SKIP1B:
			add esi,4
			add edi,4
			add edx,4

			inc ebx
			dec ecx
			jnz LOOP2B


			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			add esi,srcPitch
			add edi,lPitch
			add ebx,maskPitch
			add edx,deltaNaname
			dec ecx
			jnz LOOP1B

			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax
			emms
		}
#endif

	}
}
#endif


BOOL CEffectCharaMetal::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


/*_*/

