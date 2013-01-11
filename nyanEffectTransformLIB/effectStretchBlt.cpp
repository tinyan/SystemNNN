//
// effectStretchBlt.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectStretchBlt.h"


CEffectStretchBlt::CEffectStretchBlt(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectStretchBlt::~CEffectStretchBlt()
{
	End();
}

void CEffectStretchBlt::End(void)
{
}

BOOL CEffectStretchBlt::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[25];
	int k = paraKosuu;
	if (k>25) k = 25;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;	//frame
	
	if (paraKosuu<2) para[1] = 0;	//Šg‘å’†SdeltaX
	if (paraKosuu<3) para[2] = 0;	//Šg‘å’†SdeltaY

	if (paraKosuu<4) para[3] = 100;	//Šg‘åk¬xEnd
	if (paraKosuu<5) para[4] = 100;	//Šg‘åk¬yEnd
	if (paraKosuu<6) para[5] = para[3];	//Šg‘åk¬xStart
	if (paraKosuu<7) para[6] = para[4];	//Šg‘åk¬yStart

	if (paraKosuu<8) para[7] = 0;	//type
	if (paraKosuu<9) para[8] = 0;	//subframe
	
	if (paraKosuu<10) para[9] = 0;	//“§‰ßƒtƒ‰ƒO
	if (paraKosuu<11) para[10] = 100;	//end%
	if (paraKosuu<12) para[11] = para[10];	//start%
	if (paraKosuu<13) para[12] = 0;	//transSpeedType
	if (paraKosuu<14) para[13] = 0;	//transSubFrame



	if (paraKosuu < 15) para[14] = 0;//coloraddsubflag
	if (paraKosuu<16) para[15] = 0;	//end r
	if (paraKosuu<17) para[16] = para[15];	//end g
	if (paraKosuu<18) para[17] = para[16];	//end b

	if (paraKosuu<19) para[18] = para[15];	//start r
	if (paraKosuu<20) para[19] = para[16];	//start g
	if (paraKosuu<21) para[20] = para[17];	//start b


	if (paraKosuu<22) para[21] = 0;	//type
	if (paraKosuu<23) para[22] = 0;	//subframe




//	if (paraKosuu<9) para[8] = 0;	//‘Î”“IŒvŽZ				Šg’£—p


	lp->flag = TRUE;
	lp->command = EFFECT_STRETCHBLT;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<25;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectStretchBlt::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectStretchBlt::BeginPrint(LPVOID para,int layer)
{

}

void CEffectStretchBlt::Init(LPVOID para,int layer)
{
}

void CEffectStretchBlt::Calcu(LPVOID lpEffect,int layer)
{
}

#if !defined _TINYAN3DLIB_
void CEffectStretchBlt::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;


	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int count = lp->count;
	int countMax = lp->countMax;
	int multiSpeedType = lp->para[7];
	int multiSubFrame = lp->para[8];
	int transSpeedType = lp->para[12];
	int transSubFrame = lp->para[13];

	int picCenterDeltaX = lp->para[1];
	int picCenterDeltaY = lp->para[2];


	int addsubtype = lp->para[21];
	int addsubsubFrame = lp->para[22];

	int r1 = lp->para[18];
	int g1 = lp->para[19];
	int b1 = lp->para[20];

	int r2 = lp->para[15];
	int g2 = lp->para[16];
	int b2 = lp->para[17];

	int r = CCalcuSpeed::calcu(count,countMax,r1,r2,addsubsubFrame,addsubtype);
	int g = CCalcuSpeed::calcu(count,countMax,g1,g2,addsubsubFrame,addsubtype);
	int b = CCalcuSpeed::calcu(count,countMax,b1,b2,addsubsubFrame,addsubtype);

	int addColorR = r;
	int addColorG = g;
	int addColorB = b;

	int subColorR = -r;
	int subColorG = -g;
	int subColorB = -b;

	if (addColorR<0) addColorR = 0;
	if (addColorG<0) addColorG = 0;
	if (addColorB<0) addColorB = 0;
	if (subColorR<0) subColorR = 0;
	if (subColorG<0) subColorG = 0;
	if (subColorB<0) subColorB = 0;


	int colorAddSubFlag = lp->para[14];


	int transFlag = lp->para[9];

	int multiX1 = lp->para[5];
	int multiX2 = lp->para[3];

	int multiY1 = lp->para[6];
	int multiY2 = lp->para[4];


	double multiX = (double)(CCalcuSpeed::calcu(count,countMax,multiX1*100,multiX2*100,multiSubFrame,multiSpeedType));
	double multiY = (double)(CCalcuSpeed::calcu(count,countMax,multiY1*100,multiY2*100,multiSubFrame,multiSpeedType));

	multiX /= 10000.0;
	multiY /= 10000.0;

	if (multiX<0.001) multiX = 0.001;
	if (multiY<0.001) multiY = 0.001;

	double mulDivX = 1.0 / multiX;
	double mulDivY = 1.0 / multiY;


	int pic = lp->pic;
	if (pic == -1) return;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	RECT rc;
	lpPic->GetPicSize(&rc);

	int picSizeX = rc.right;
	int picSizeY = rc.bottom;

	if ((picSizeX<1) || (picSizeY<1)) return;

	int* src = (int*)(lpPic->GetBuffer());
	if (src == NULL) return;
	char* mask = lpPic->GetMaskPic();




	double zmx = (double)(lp->dst.left + screenSizeX/2);
	double zmy = (double)(lp->dst.top  + screenSizeY/2);

	double pictureCenterX = (double)(picSizeX / 2 + picCenterDeltaX);
	double pictureCenterY = (double)(picSizeY / 2 + picCenterDeltaY);

	double picLeft = (0.0 - pictureCenterX);
	double picRight = ((double)picSizeX) - pictureCenterX;
	double picTop = (0.0 - pictureCenterY);
	double picBottom = ((double)picSizeY) - pictureCenterY;


	double x = 0;
	double y = 0.0;

	double dstXLeft = multiX * picLeft + zmx;
	double dstYTop = multiY * picTop  + zmy;
	double dstXRight = multiX * picRight  + zmx;
	double dstYBottom = multiY * picBottom + zmy;

	if (dstXLeft>=screenSizeX) return;
	if (dstXRight<0) return;
	if (dstYTop>=screenSizeY) return;
	if (dstYBottom<0) return;


	double srcX = 0.0;
	double srcSizeX = picSizeX;
	if (dstXLeft < 0.0)
	{
		double dx = -dstXLeft;
		srcX += dx*mulDivX;
		srcSizeX -= dx*mulDivX; 
		dstXLeft = 0.0;
	}

	if (dstXRight > screenSizeX)
	{
		double dx = dstXRight - screenSizeX;
		srcSizeX -= dx * mulDivX;
		dstXRight = screenSizeX;
	}

	double srcY = 0.0;
	double srcSizeY = picSizeY;
	if (dstYTop < 0.0)
	{
		double dy = -dstYTop;
		srcY += dy*mulDivY;
		srcSizeY -= dy*mulDivY;
		dstYTop = 0.0;
	}

	if (dstYBottom >= screenSizeY)
	{
		double dy = dstYBottom - screenSizeY;
		srcSizeY -= dy * mulDivY;
		dstYBottom = screenSizeY;
	}

	if (srcSizeX<0.0) srcSizeX = 0.0;
	if (srcSizeY<0.0) srcSizeY = 0.0;

	int loopX = (int)(dstXRight) - (int)(dstXLeft);
	int loopY = (int)(dstYBottom) - (int)(dstYTop);
	if (loopX <= 0) return;
	if (loopY <= 0) return;




	double ddx = srcSizeX / ((double)loopX);
	double ddy = srcSizeY / ((double)loopY);

	double ml = 65536.0;

	int ddxInt = (int)ddx;
	int ddxAmari = 0;
	if (ddx>=0)
	{
		ddxAmari = (int)((ddx - ddxInt) * ml);
	}
	else
	{
		ddxInt--;
		ddxAmari = (int)((ddx - ddxInt) * ml);
	}


	int ddyInt = (int)ddy;
	int ddyAmari = 0;
	if (ddy>=0)
	{
		ddyAmari = (int)((ddy - ddyInt) * ml);
	}
	else
	{
		ddyInt--;
		ddyAmari = (int)((ddy - ddyInt) * ml);
	}

	int tmpX = 0;
	tmpX = (int)(srcX);
	int tmpAmariX;
	if (srcX>=0)
	{
		tmpAmariX = (int)((srcX - tmpX) * ml);
	}
	else
	{
		tmpX--;
		tmpAmariX = (int)((srcX - tmpX) * ml);
	}

	int tmpY = (int)(srcY);
	int tmpAmariY;
	if (srcY>=0)
	{
		tmpAmariY = (int)((srcY - tmpY) * ml);
	}
	else
	{
		tmpY--;
		tmpAmariY = (int)((srcY - tmpY) * ml);
	}



	int lPitch = screenSizeX * 4;
	int maskPitch = picSizeX;


	int trans = *src;

	if (transFlag == 2)
	{
		if (mask == NULL) transFlag = 1;
		if (lpPic->CheckMaskExist() == FALSE) transFlag = 1;
	}



	int ps1 = lp->para[11];
	int ps2 = lp->para[10];

	int ps256 = CCalcuSpeed::calcu(count,countMax,ps1*256,ps2*256,transSubFrame,transSpeedType);
	ps256 /= 100;
	if (ps256<0) ps256 = 0;
	if (ps256>256) ps256 = 256;

	if (transFlag == 2)
	{
		if (ps256 != 256)
		{
			transFlag = 3;
		}
	}


	int dstXInt = (int)dstXLeft;
	int dstYInt = (int)dstYTop;








	if (loopX<1) return;
	if (loopY<1) return;

	int addColor = (addColorR << 16) | (addColorG << 8) | addColorB;
	int subColor = (subColorR << 16) | (subColorG << 8) | subColorB;
	LONGLONG addColor64 = (LONGLONG)addColor;
	LONGLONG subColor64 = (LONGLONG)subColor;

	
	__asm
	{
		push eax
//		push ebx
		push ecx
		push edx
		push esi
		push edi


		mov eax,addColorR
		movd mm1,eax
		mov eax,addColor

		mov eax,tmpAmariX
		and eax,0ffffh
		mov edx,tmpX
		shl edx,16
		or eax,edx
		movd mm0,eax

		psllq mm0,32

		mov eax,tmpAmariY
		and eax,0ffffh
		mov edx,tmpY
		shl edx,16
		or eax,edx
		movd mm7,eax

		por mm0,mm7





		mov eax,ddxAmari
		and eax,0ffffh
		mov edx,ddxInt
		shl edx,16
		or eax,edx
		movd mm2,eax

		psllq mm2,32

		mov eax,0
		and eax,0ffffh
		mov edx,0
		shl edx,16
		or eax,edx
		movd mm7,eax

		por mm2,mm7




		mov eax,0
		and eax,0ffffh
		mov edx,0
		shl edx,16
		or eax,edx
		movd mm3,eax

		psllq mm3,32

		mov eax,ddyAmari
		and eax,0ffffh
		mov edx,ddyInt
		shl edx,16
		or eax,edx
		movd mm7,eax

		por mm3,mm7



//		mov esi,src


		mov edi,dst



		mov eax,dstYInt
		mov edx,lPitch
		mul edx
		add edi,eax

		mov eax,dstXInt
		shl eax,2
		add edi,eax





		mov ecx,loopY

		mov eax,transFlag
		cmp eax,0
		jz MODE0
		cmp eax,1
		jz MODE1
		cmp eax,2
		jz MODE2
		jmp MODE3

MODE0:
LOOP1:
		push ecx
		push edi

		movq mm1,mm0


		movq mm6,mm1
		psrad mm6,16
		movd eax,mm6
		cmp eax,picSizeY
		jnb SKIP2
		mov edx,picSizeX
		mul edx
		shl eax,2
		add eax,src
		mov esi,eax

		mov ecx,loopX
LOOP2:
		movq mm7,mm1
		psrlq mm7,48

		push ecx

		movd ecx,mm7

		cmp ecx,picSizeX
		jnb SKIP1
//•\Ž¦?
		shl ecx,2
		mov eax,[ecx+esi]
		
		push edx
		mov edx,colorAddSubFlag
		or edx,edx
		pop edx
		jz NOTADDSUB0

		movd mm4,eax
		paddusb mm4,addColor64
		psubusb mm4,subColor64
		movd eax,mm4

NOTADDSUB0:

		mov [edi],eax

SKIP1:
		pop ecx

		paddd mm1,mm2

		add edi,4
		dec ecx
		jnz LOOP2
SKIP2:
		paddd mm0,mm3


		pop edi
		pop ecx
		add edi,lPitch
		dec ecx
		jnz LOOP1

		jmp EXIT1




MODE1:
LOOP11:
		push ecx
		push edi

		movq mm1,mm0


		movq mm6,mm1
		psrad mm6,16
		movd eax,mm6
		cmp eax,picSizeY
		jnb SKIP12
		mov edx,picSizeX
		mul edx
		shl eax,2
		add eax,src
		mov esi,eax


		mov ecx,loopX
LOOP12:
		movq mm7,mm1
		psrlq mm7,48

		push ecx

		movd ecx,mm7

		cmp ecx,picSizeX
		jnb SKIP11
//•\Ž¦?
		shl ecx,2
		mov eax,[ecx+esi]
		cmp eax,trans
		jz SKIP11

		push edx
		mov edx,colorAddSubFlag
		or edx,edx
		pop edx
		jz NOTADDSUB1

		movd mm4,eax
		paddusb mm4,addColor64
		psubusb mm4,subColor64
		movd eax,mm4

NOTADDSUB1:

		mov [edi],eax

SKIP11:
		pop ecx

		paddd mm1,mm2

		add edi,4
		dec ecx
		jnz LOOP12
SKIP12:
		paddd mm0,mm3

		pop edi
		pop ecx
		add edi,lPitch
		dec ecx
		jnz LOOP11

		jmp EXIT1


MODE2:

LOOP21:
		push ecx
		push edi

		movq mm1,mm0


		movq mm6,mm1
		psrad mm6,16
		movd eax,mm6
		cmp eax,picSizeY
		jnb SKIP22
		mov edx,picSizeX
		mul edx
		shl eax,2
		add eax,src
		mov esi,eax


		movd eax,mm6
		mov edx,picSizeX
		mul edx
		add eax,mask
		mov edx,eax

		mov ecx,loopX
LOOP22:
		movq mm7,mm1
		psrlq mm7,48

		push ecx

		movd ecx,mm7

		cmp ecx,picSizeX
		jnb SKIP21
//•\Ž¦?
		xor eax,eax
		mov al,[ecx+edx]
		shl ecx,2
		or eax,eax
		jz SKIP21
		cmp eax,0ffh
		jz NORMAL2
//”¼“§–¾
		movd mm7,eax
		punpcklwd mm7,mm7
		xor al,0ffh
		punpckldq mm7,mm7
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6


		mov eax,[ecx+esi]

		push edx
		mov edx,colorAddSubFlag
		or edx,edx
		pop edx
		jz NOTADDSUB2A

		movd mm4,eax
		paddusb mm4,addColor64
		psubusb mm4,subColor64
		movd eax,mm4

NOTADDSUB2A:

		pxor mm4,mm4
		movd mm5,eax

		punpcklbw mm5,mm4
		pmullw mm7,mm5

		mov eax,[edi]
		movd mm5,eax
		punpcklbw mm5,mm4

		pmullw mm6,mm5

		psrlw mm7,8
		psrlw mm6,8
		paddw mm7,mm6
		packuswb mm7,mm4

		movd eax,mm7
		mov [edi],eax
		jmp SKIP21

NORMAL2:
		mov eax,[ecx+esi]
		push edx
		mov edx,colorAddSubFlag
		or edx,edx
		pop edx
		jz NOTADDSUB2B

		movd mm4,eax
		paddusb mm4,addColor64
		psubusb mm4,subColor64
		movd eax,mm4

NOTADDSUB2B:

		mov [edi],eax


SKIP21:
		pop ecx

		paddd mm1,mm2

		add edi,4
		dec ecx
		jnz LOOP22
SKIP22:

		paddd mm0,mm3


		pop edi
		pop ecx
		add edi,lPitch
		dec ecx
		jnz LOOP21

		jmp EXIT1


MODE3:

LOOP31:
		push ecx
		push edi

		movq mm1,mm0


		movq mm6,mm1
		psrad mm6,16
		movd eax,mm6
		cmp eax,picSizeY
		jnb SKIP32
		mov edx,picSizeX
		mul edx
		shl eax,2
		add eax,src
		mov esi,eax


		movd eax,mm6
		mov edx,picSizeX
		mul edx
		add eax,mask
		mov edx,eax

		mov ecx,loopX
LOOP32:
		movq mm7,mm1
		psrlq mm7,48

		push ecx

		movd ecx,mm7

		cmp ecx,picSizeX
		jnb SKIP31
//•\Ž¦?
		xor eax,eax
		mov al,[ecx+edx]
		shl ecx,2
		or eax,eax
		jz SKIP31

		push edx
		mov edx,ps256
		mul edx
		pop edx
		shr eax,8

//”¼“§–¾
		movd mm7,eax
		punpcklwd mm7,mm7
		xor al,0ffh
		punpckldq mm7,mm7
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6


		mov eax,[ecx+esi]


		push edx
		mov edx,colorAddSubFlag
		or edx,edx
		pop edx
		jz NOTADDSUB3

		movd mm4,eax
		paddusb mm4,addColor64
		psubusb mm4,subColor64
		movd eax,mm4

NOTADDSUB3:
		pxor mm4,mm4
		movd mm5,eax
		punpcklbw mm5,mm4


		pmullw mm7,mm5

		mov eax,[edi]
		movd mm5,eax
		punpcklbw mm5,mm4

		pmullw mm6,mm5

		psrlw mm7,8
		psrlw mm6,8
		paddw mm7,mm6
		packuswb mm7,mm4

		movd eax,mm7
		mov [edi],eax

SKIP31:
		pop ecx

		paddd mm1,mm2

		add edi,4
		dec ecx
		jnz LOOP32
SKIP32:

		paddd mm0,mm3


		pop edi
		pop ecx
		add edi,lPitch
		dec ecx
		jnz LOOP31

		jmp EXIT1



EXIT1:

		pop edi
		pop esi
		pop edx
		pop ecx
//		pop ebx
		pop eax

		emms
	}
	

}
#else
void CEffectStretchBlt::Print(LPVOID lpEffect,int layer)
{
//	int* dst = CMyGraphics::GetScreenBuffer();
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int count = lp->count;
	int countMax = lp->countMax;
	int multiSpeedType = lp->para[7];
	int multiSubFrame = lp->para[8];
	int transSpeedType = lp->para[12];
	int transSubFrame = lp->para[13];

	int dx = lp->para[1];
	int dy = lp->para[2];

	int transFlag = lp->para[9];

	int multiX1 = lp->para[5];
	int multiX2 = lp->para[3];

	int multiY1 = lp->para[6];
	int multiY2 = lp->para[4];

	float multiX = (float)(CCalcuSpeed::calcu(count,countMax,multiX1*100,multiX2*100,multiSubFrame,multiSpeedType));
	float multiY = (float)(CCalcuSpeed::calcu(count,countMax,multiY1*100,multiY2*100,multiSubFrame,multiSpeedType));

	multiX /= 10000.0;
	multiY /= 10000.0;

	int pic = lp->pic;
	if (pic == -1) return;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	SIZE srcSize = lpPic->GetPicSize();
	if ((srcSize.cx < 1) || (srcSize.cy < 1)) return;

	int putSizeX = (int)(((float)srcSize.cx) * multiX + 0.5f);
	int putSizeY = (int)(((float)srcSize.cy) * multiY + 0.5f);

	if ((putSizeX < 1) || (putSizeY < 1)) return;

	int putX = lp->dst.left;
	int putY = lp->dst.top;
//	putX += srcSize.cx / 2;
//	putY += srcSize.cy / 2;
	putX += screenSizeX / 2;
	putY += screenSizeY / 2;

//	putX += dx;
//	putY += dy;

	putX -= ((srcSize.cx / 2 + dx) * putSizeX) / srcSize.cx;
	putY -= ((srcSize.cy / 2 + dy) * putSizeY) / srcSize.cy;


	SIZE putSize;
	putSize.cx = putSizeX;
	putSize.cy = putSizeY;

//	int trans = *src;
//
//	if (transFlag == 2)
//	{
//		if (mask == NULL) transFlag = 1;
//		if (lpPic->CheckMaskExist() == FALSE) transFlag = 1;
//	}

	int ps1 = lp->para[11];
	int ps2 = lp->para[10];

	int ps = CCalcuSpeed::calcu(count,countMax,ps1,ps2,transSubFrame,transSpeedType);

//	OutputDebugString("*");
	lpPic->StretchBlt1(putX,putY,putSizeX,putSizeY,0,0,srcSize.cx,srcSize.cy,ps,TRUE);
}

#endif



BOOL CEffectStretchBlt::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}
