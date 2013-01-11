//
// effectBura.cpp
//

#include "..\nyanEffectLib\includer.h"
#include "effectBura.h"



CEffectBura::CEffectBura(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetPercentKosuu(1);
	SetTextureKosuu(1);
	Create("Bura");
#endif
}


CEffectBura::~CEffectBura()
{
	End();
}

void CEffectBura::End(void)
{
}


BOOL CEffectBura::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


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
	if (paraKosuu<2) para[1] = screenSizeX / 2;	//I—¹’†SÀ•W
	if (paraKosuu<3) para[2] = screenSizeY / 2;
	if (paraKosuu<4) para[3] = 105;	//end percentŠg‘å
	if (paraKosuu<5) para[4] = para[3];	//start percent
	if (paraKosuu<6) para[5] = 20;	//end percent“§–¾
	if (paraKosuu<7) para[6] = para[5];	//start percent

	if (paraKosuu<8) para[7] = 0;	//Šg‘åtype
	if (paraKosuu<9) para[8] = 0;	//‚©‚­‚¾‚¢‚³‚Ô

	if (paraKosuu<10) para[9] = 0;	//“§–¾type
	if (paraKosuu<11) para[10] = 0;	//“§–¾‚³‚Ô



	if (para[1]<1) para[1] = 1;
	if (para[2]<1) para[2] = 1;
	if (para[1]>=screenSizeX-1) para[1] = screenSizeX-2;
	if (para[2]>=screenSizeY-1) para[2] = screenSizeY-2;

	if (paraKosuu<12) para[11] = para[1];	//ŠJŽn’†SÀ•W
	if (paraKosuu<13) para[12] = para[2];

//	if (paraKosuu<10) para[9] = 0;

	lp->flag = TRUE;
	lp->command = EFFECT_BURA;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectBura::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectBura::BeginPrint(LPVOID para,int layer)
{

}

void CEffectBura::Init(LPVOID para,int layer)
{
}

void CEffectBura::Calcu(LPVOID lpEffect,int layer)
{
}

#if defined _TINYAN3DLIB_
void CEffectBura::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int count = lp->count;
	int countMax = lp->countMax;
	int kakudaiType = lp->para[7];
	int kakudaiSubFrame = lp->para[8];
	int transType = lp->para[9];
	int transSubFrame = lp->para[10];

	int dv = lp->countMax;
	int c = lp->count;

	if (dv<1)
	{
		dv = 1;
	}

	if (c>=dv)
	{
		c = dv;
	}


	int cx2 = lp->para[1];
	int cy2 = lp->para[2];

	int cx1 = lp->para[11];
	int cy1 = lp->para[12];

	int cx = cx1 + ((cx2 - cx1) * c) / dv;
	int cy = cy1 + ((cy2 - cy1) * c) / dv;

	m_cx = cx;
	m_cy = cy;


	int startMul = lp->para[4] * 100;
	int endMul = lp->para[3] * 100;

	int mul = CCalcuSpeed::calcu(count,countMax,startMul,endMul,kakudaiSubFrame,kakudaiType);

	float ml = (float)mul;
	ml /= 10000.0f;

//	double ml1 = (double)(lp->para[4]);
//	double ml2 = (double)(lp->para[3]);
//	double ml = ml1 + ((ml2 - ml1) * c) / dv;


	if (ml<1.0f) ml = 1.0f;	//Šg‘å‚Ì‚Ý
	ml = 1.0f / ml;
	if (ml<0.01f) ml = 0.01f;	//limit min


	int ps1 = lp->para[6];
	int ps2 = lp->para[5];


	int ps = CCalcuSpeed::calcu(count,countMax,ps1,ps2,transSubFrame,transType);


	int dx1 = (int)((((float)(cx)) * ml) * 0.5f);
	int dx2 = (int)((((float)(screenSizeX-cx)) * ml) * 0.5f);
	int dy1 = (int)((((float)(cy)) * ml) * 0.5f);
	int dy2 = (int)((((float)(screenSizeY-cy)) * ml) * 0.5f);

	int srcSizeX = dx1 + dx2;
	int srcSizeY = dy1 + dy2;
	if (srcSizeX<1) srcSizeX = 1;
	if (srcSizeY<1) srcSizeY = 1;

	int srcX = cx - dx1;
	int srcY = cy - dy1;

	//copy

	ExchangeScreenAndBuffer();
	SetTexture(GetBufferTexture());
	//CMyDirect3D::SetBufferTextureToStage(0);
	SetPercent(100.0f);
	POINT dstPoint;
	dstPoint.x = 0;
	dstPoint.y = 0;
	SIZE dstSize;
	dstSize.cx = screenSizeX;
	dstSize.cy = screenSizeY;
	POINT srcPoint;
	srcPoint.x = 0;
	srcPoint.y = 0;
	Blt(dstPoint,dstSize,srcPoint);

	SetPercent(((float)(ps)) / 100.0f);
	SIZE srcSize;
	srcSize.cx = srcSizeX;
	srcSize.cy = srcSizeY;
	srcPoint.x = cx - dx1;
	srcPoint.y = cy - dy1;
	SIZE srcPicSize;
	srcPicSize.cx = screenSizeX;
	srcPicSize.cy = screenSizeY;
	StretchBlt(&dstPoint,&dstSize,&srcPoint,&srcSize,&srcPicSize);
}
#else
void CEffectBura::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int count = lp->count;
	int countMax = lp->countMax;
	int kakudaiType = lp->para[7];
	int kakudaiSubFrame = lp->para[8];
	int transType = lp->para[9];
	int transSubFrame = lp->para[10];




	int dv = lp->countMax;
	int c = lp->count;

	if (dv<1)
	{
		dv = 1;
	}

	if (c>=dv)
	{
		c = dv;
	}



	int cx2 = lp->para[1];
	int cy2 = lp->para[2];

	int cx1 = lp->para[11];
	int cy1 = lp->para[12];

	int cx = cx1 + ((cx2 - cx1) * c) / dv;
	int cy = cy1 + ((cy2 - cy1) * c) / dv;

	m_cx = cx;
	m_cy = cy;


	int startMul = lp->para[4] * 100;
	int endMul = lp->para[3] * 100;

	int mul = CCalcuSpeed::calcu(count,countMax,startMul,endMul,kakudaiSubFrame,kakudaiType);

	double ml = (double)mul;
	ml /= 100.0;

//	double ml1 = (double)(lp->para[4]);
//	double ml2 = (double)(lp->para[3]);
//	double ml = ml1 + ((ml2 - ml1) * c) / dv;

	if (ml<100.0) ml = 100.0;	//Šg‘å‚Ì‚Ý
	if (ml<0.01) ml = 0.01;	//limit min

	int sizeX = cx - 0;
	int sizeY = cy - 0;

	double dSizeX = (double)sizeX;
	double dSizeY = (double)sizeY;

	double startX = (double)cx;
	double startY = (double)cy;

	startX -= dSizeX * 100.0 / ml;
	startY -= dSizeY * 100.0 / ml;


	int ps1 = lp->para[6];
	int ps2 = lp->para[5];


	int ps = CCalcuSpeed::calcu(count,countMax,ps1,ps2,transSubFrame,transType);
	//int ps = ps1 + ((ps2 - ps1) * c ) / dv;



	PrintBuraSub(lpEffect,0,0,startX,startY,sizeX,sizeY,ps);


	sizeX = screenSizeX - cx;
	sizeY = cy - 0;
	startX = (double)cx;
	startY = (double)cy;
	dSizeX = (double)sizeX;
	dSizeY = (double)sizeY;
	startX += (dSizeX-0.0) * 100.0 / ml;
	startY -= dSizeY * 100.0 / ml;

	PrintBuraSub(lpEffect,screenSizeX-1,0,startX,startY,-sizeX,sizeY,ps);



	sizeX = cx;
	sizeY = screenSizeY - cy;
	startX = (double)cx;
	startY = (double)cy;
	dSizeX = (double)sizeX;
	dSizeY = (double)sizeY;
	startX -= dSizeX * 100.0 / ml;
	startY += (dSizeY-0.0) * 100.0 / ml;

	PrintBuraSub(lpEffect,0,screenSizeY-1,startX,startY,sizeX,-sizeY,ps);



	sizeX = screenSizeX - cx;
	sizeY = screenSizeY - cy;
	startX = (double)cx;
	startY = (double)cy;
	dSizeX = (double)sizeX;
	dSizeY = (double)sizeY;
	startX += (dSizeX-0.0) * 100.0 / ml;
	startY += (dSizeY-0.0) * 100.0 / ml;

	PrintBuraSub(lpEffect,screenSizeX-1,screenSizeY-1,startX,startY,-sizeX,-sizeY,ps);

	return;

}
#endif



void CEffectBura::PrintBuraSub(LPVOID lpEffect, int startX, int startY, double dSrcX,double dSrcY,int sizeX,int sizeY,int ps)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int* dst = CMyGraphics::GetScreenBuffer();
	int* src = dst;

//	int srcXInt = (int)dSrcX;
//	if (dSrcX<0.0) srcXInt--;
//	int srcXAmari = (int)((dSrcX - (double)srcXInt) * 65536.0);
//
//	if (srcXInt<0)
//	{
//		srcXInt = 0;
//		srcXAmari = 0;
//	}
//	if (srcXInt>=screenSizeX)
//	{
//		srcXInt = screenSizeX - 1;
//		srcXAmari = 0xffff;
//	}
//	int srcXMMX = (srcXInt << 16) | (srcXAmari & 0xffff);

	int srcXMMX = (int)(dSrcX * 65536.0);

	if (srcXMMX < 0) srcXMMX = 0;
	if (srcXMMX >= screenSizeX * 0x10000)
	{
		srcXMMX = ((screenSizeX-1) << 16) | 0xffff;
	}


//	int srcYInt = (int)dSrcY;
//	int srcYAmari = (int)((dSrcY - (double)srcYInt) * 65536.0);
//	if (dSrcY<0.0)
//	{
//
//		srcYInt--;
//	}
//
//	if (srcYInt<0)
//	{
//		srcYInt = 0;
//		srcYAmari = 0;
//	}
//	if (srcYInt >= screenSizeY)
//	{
//		srcYInt = screenSizeY - 1;
//		srcYAmari = 0xffff;
//	}
//	int srcYMMX = (srcYInt << 16) | (srcYAmari & 0xffff);

	int srcYMMX = (int)(dSrcY * 65536.0);
	if (srcYMMX<0) srcYMMX = 0;
	if (srcYMMX >= screenSizeY*0x10000)
	{
		srcYMMX = ((screenSizeY-1) << 16) | 0xffff;
	}

	double sizeX2 = (double)(m_cx);
	sizeX2 -= dSrcX;

	double sizeY2 = (double)(m_cy);
	sizeY2 -= dSrcY;

	double divX = (double)sizeX;
	double divY = (double)sizeY;

	if (divX<0) divX *= -1.0;
	if (divY<0) divY *= -1.0;

	sizeX2 /= divX;
	sizeY2 /= divY;

//	int deltaXInt = (int)sizeX2;
//	if (sizeX2<0.0) deltaXInt--;
//	int deltaXAmari = (int)((sizeX2 - (double)deltaXInt) * 65536.0);
//
//	int deltaXMMX = (deltaXInt << 16) | (deltaXAmari & 0xffff);

	int deltaXMMX = (int)(sizeX2 * 65536.0);

//	int deltaYInt = (int)sizeY2;
//	if (sizeY2<0.0) deltaYInt--;
//	int deltaYAmari = (int)((sizeY2 - (double)deltaYInt) * 65536.0);

//	int deltaYMMX = (deltaYInt << 16) | (deltaYAmari & 0xffff);

	int deltaYMMX = (int)(sizeY2 * 65536.0);


	int lPitch = screenSizeX * sizeof(int);
	if (sizeY<0) lPitch *= -1;

	int lPitchX = sizeof(int);
	if (sizeX<0) lPitchX *= -1;

	dst += startX;
	dst += startY * screenSizeX;


	int loopY = sizeY;
	int loopX = sizeX;

	if (loopX<0) loopX *= -1;
	if (loopY<0) loopY *= -1;

	if ((loopX==0) || (loopY==0)) return;

	int ps1 = (ps * 256) / 100;
	int ps2 = ((100-ps) * 256) / 100;

	if (ps1<0) ps1 = 0;
	if (ps1>256) ps1 = 256;
	if (ps2<0) ps2 = 0;
	if (ps2>256) ps2 = 256;

	//left up routine
	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		pxor mm0,mm0

		mov eax,ps1
		movd mm3,eax
		punpcklwd mm3,mm3
		punpckldq mm3,mm3

		mov eax,ps2
		movd mm4,eax
		punpcklwd mm4,mm4
		punpckldq mm4,mm4

		mov eax,srcYMMX
		movd mm7,eax

		mov edi,dst
		mov ecx,loopY
LOOP1:
		push ecx
		push edi

		mov eax,srcXMMX
		movd mm5,eax

		mov eax,deltaXMMX
		movd mm6,eax

		movq mm1,mm7
		psrad mm1,16
		movd eax,mm1
		cmp eax,screenSizeY
		jnb SKIP2

		mov edx,screenSizeX
		shl edx,2
		mul edx
		mov esi,src
		add esi,eax

//		movq mm1,mm5
//		psrad mm1,16
//		movd eax,mm1
//		shl eax,2
//		add esi,eax

		mov ecx,loopX
LOOP2:
		movq mm1,mm5
		psrad mm1,16
		movd ebx,mm1
		shl ebx,2
		mov edx,[edi]

		mov eax,[ebx+esi]
		movd mm1,eax
		movd mm2,edx
		
		punpcklbw mm1,mm0
		punpcklbw mm2,mm0


		pmullw mm1,mm3
		pmullw mm2,mm4
		paddw mm1,mm2
		psrlw mm1,8
		packuswb mm1,mm1
		movd eax,mm1

		mov [edi],eax


		paddd mm5,mm6
		add edi,lPitchX
//		sub edi,4
		dec ecx
		jnz LOOP2
SKIP2:
		pop edi
		pop ecx


		mov eax,deltaYMMX
		movd mm1,eax
		paddd mm7,mm1

		add edi,lPitch
//		sub edi,lPitch
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

}


/*_*/

