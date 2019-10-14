//
// effectNega.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectNega.h"


CEffectNega::CEffectNega(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(1);
	SetConstKosuu(1);
	Create("Nega");
#endif
}

CEffectNega::~CEffectNega()
{
	End();
}

void CEffectNega::End(void)
{
}

BOOL CEffectNega::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
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

	if (paraKosuu<1) para[0] = 20;
	if (paraKosuu<2) para[1] = 0;	//方向タイプ
	if (paraKosuu<3) para[2] = 0;//sub frame
	if (paraKosuu<4) para[3] = 100;	//終了割合
	if (paraKosuu<5) para[4] = 0;//開始割合


	lp->flag = TRUE;
	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_NEGA;


	for (i=0;i<5;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectNega::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectNega::BeginPrint(LPVOID para,int layer)
{

}

void CEffectNega::Init(LPVOID para,int layer)
{
}

void CEffectNega::Calcu(LPVOID lpEffect,int layer)
{
}

#if defined _TINYAN3DLIB_
void CEffectNega::Print(LPVOID lpEffect,int layer)
{
	ExchangeScreenAndBuffer();
	SetTexture(GetBufferTexture());
	

	EFFECT* lp = (EFFECT*)lpEffect;
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int count = lp->count;
	int countMax = lp->countMax;

	int startData = lp->para[4];
	int endData = lp->para[3];

	int subFrame = lp->para[2];
	int speedType = lp->para[1];
	int negaData = CCalcuSpeed::calcu(count,countMax,startData,endData,subFrame,speedType);

	float nega = (float)(100-negaData);
	nega /= 100.0f;
	nega *= 2.0f;
	nega -= 1.0f;
	CCommonShader::SetConst(nega);

	POINT dstPoint;
	SIZE dstSize;
	POINT srcPoint;

	dstPoint.x = 0;
	dstPoint.y = 0;

	dstSize.cx = screenSizeX;
	dstSize.cy = screenSizeY;

	srcPoint.x = 0;
	srcPoint.y = 0;

	Blt(dstPoint,dstSize,dstPoint);

	return;

}
#else

void CEffectNega::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int count = lp->count;
	int countMax = lp->countMax;

	int startData = lp->para[4];
	int endData = lp->para[3];

	startData *= -254*2;
	startData /= 100;
	startData += 254;

	endData *= -254*2;
	endData /= 100;
	endData += 254;


	int subFrame = lp->para[2];
	int speedType = lp->para[1];

	int negaData = CCalcuSpeed::calcu(count,countMax,startData,endData,subFrame,speedType);

	if (negaData<-254) negaData = -254;
	if (negaData>254) negaData = 254;

	int* screen = CMyGraphics::GetScreenBuffer();

	int loopSize = screenSizeX * screenSizeY / 2 / 2;

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

		mov eax,negaData

		shl eax,6

		movd mm7,eax
		punpcklwd mm7,mm7
		punpckldq mm7,mm7


		mov eax,00800080h
		movd mm6,eax
		punpckldq mm6,mm6

		pxor mm4,mm4

		mov ecx,loopSize
		mov esi,screen
LOOP1:
		movq mm0,[esi]
		movq mm2,[esi+8]
		movq mm1,mm0
		movq mm3,mm2
		
		punpcklbw mm0,mm4
		punpckhbw mm1,mm4
		psubw mm0,mm6
		punpcklbw mm2,mm4
		psubw mm1,mm6
		punpckhbw mm3,mm4

		psubw mm2,mm6
		psllw mm0,2
		psubw mm3,mm6


		psllw mm1,2
		pmulhw mm0,mm7
		psllw mm2,2
		pmulhw mm1,mm7
		psllw mm3,2
		paddw mm0,mm6

		pmulhw mm2,mm7
		paddw mm1,mm6
		pmulhw mm3,mm7

		packuswb mm0,mm1
		paddw mm2,mm6
		
		movq [esi],mm0
		paddw mm3,mm6
		packuswb mm2,mm3

		movq [esi+8],mm2

		add esi,16
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
#endif



/*_*/

