//
// effectreleaf.cpp	
//

#include "..\nyanEffectLib\includer.h"

#include "effectreleaf.h"


CEffectReleaf::CEffectReleaf(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(1);
	SetConstKosuu(2);
	Create("Releaf");
#endif
}


CEffectReleaf::~CEffectReleaf()
{
	End();
}

void CEffectReleaf::End(void)
{
}

BOOL CEffectReleaf::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[16];
	int k = paraKosuu;
	if (k>5) k = 5;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;
	if (paraKosuu<2) para[1] = 0;	//方向タイプ
	if (paraKosuu<3) para[2] = 100;	//終了割合
	if (paraKosuu<4) para[3] = 0;//開始割合
	if (paraKosuu<5) para[4] = 0;//sub frame

	for (i=0;i<5;i++)
	{
		lp->para[i] = para[i];
	}

	lp->flag = TRUE;
	lp->command = EFFECT_RELEAF;
	lp->countMax = para[0];
	lp->count = 0;

	return TRUE;
}


BOOL CEffectReleaf::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectReleaf::BeginPrint(LPVOID para,int layer)
{

}

void CEffectReleaf::Init(LPVOID para,int layer)
{
}

void CEffectReleaf::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectReleaf::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int count = lp->count;
	int countMax = lp->countMax;

	int startData = (lp->para[3] * 256);
	int endData = (lp->para[2] * 256);

	int subFrame = lp->para[4];
	int speedType = lp->para[1];

	int tr = CCalcuSpeed::calcu(count,countMax,startData,endData,subFrame,speedType);
	tr /= 100;

	if (tr<0) tr = 0;
	if (tr>256) tr = 256;


#if defined _TINYAN3DLIB_

	if (CheckEffectError()) return;
	float alfa = (float)tr;
	alfa /= 256.0f;
	SetConst(alfa);

	float dot1 = 1.0f / ((float)screenSizeX);
	SetConst(dot1,1);

//	ExchangeScreenAndBuffer();
	CopyScreenToBuffer();
	SetTexture(GetBufferTexture(),0);


	POINT srcPoint;
	srcPoint.x = 0;
	srcPoint.y = 0;

	POINT dstPoint;
	dstPoint.x = 0;
	dstPoint.y = 0;

	SIZE dstSize;
	dstSize.cx = screenSizeX;
	dstSize.cy = screenSizeY;

	Blt(dstPoint,dstSize,srcPoint);
#else




	int* screen = CMyGraphics::GetScreenBuffer();

	int loopCount = screenSizeX * screenSizeY / 2 - 1;

	int lPitch = screenSizeX * 4;
	int loopY = screenSizeY;

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


		pxor mm4,mm4
		mov eax,00800080h
		movd mm5,eax
		punpckldq mm5,mm5


		mov eax,tr
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6
		psllw mm6,6

		mov eax,tr
		neg eax
		add eax,256
		movd mm7,eax
		punpcklwd mm7,mm7
		punpckldq mm7,mm7
		psllw mm7,6


		mov esi,screen
		mov ecx,loopCount
LOOP1:
		movq mm0,[esi]
		movq mm1,mm0

		punpcklbw mm0,mm4
		punpckhbw mm1,mm4
		movq mm2,mm0

		psubw mm0,mm1
		psraw mm0,1
		paddw mm0,mm5
		
		psllw mm0,2
		psllw mm2,2

		pmulhw mm0,mm6
		pmulhw mm2,mm7

		paddw mm0,mm2
		packuswb mm0,mm4

		movd eax,mm0
		mov [esi],eax

		mov eax,[esi+4]
		movd mm0,eax
		mov eax,[esi+8]
		movd mm1,eax


		punpcklbw mm0,mm4
		punpcklbw mm1,mm4
		movq mm2,mm0

		psubw mm0,mm1
		psraw mm0,1
		paddw mm0,mm5
		
		psllw mm0,2
		psllw mm2,2

		pmulhw mm0,mm6
		pmulhw mm2,mm7

		paddw mm0,mm2
		packuswb mm0,mm4

		movd eax,mm0
		mov [esi+4],eax

		add esi,8

		dec ecx
		jnz LOOP1



		mov esi,screen
		mov eax,lPitch

//		add esi,638*4
		add esi,lPitch
		sub esi,4*2
		mov ecx,loopY
LOOP2:
		mov eax,[esi]
		mov [esi+4],eax
		add esi,lPitch
		dec ecx
		jnz LOOP2

		emms
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}

#endif

#endif

}
