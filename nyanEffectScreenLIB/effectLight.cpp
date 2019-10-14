//
// effectlight.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectlight.h"


CEffectLight::CEffectLight(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectLight::~CEffectLight()
{
	End();
}

void CEffectLight::End(void)
{
}

BOOL CEffectLight::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[6];
	int k = paraKosuu;
	if (k>6) k = 6;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;
	if (paraKosuu<2) para[1] = 64;
	if (paraKosuu<3) para[2] = para[1];
	if (paraKosuu<4) para[3] = para[2];
	if (paraKosuu<5) para[4] = 0;	//type
	if (paraKosuu<6) para[5] = 0;	//subframe

	lp->flag = TRUE;
	lp->command = EFFECT_LIGHT;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<6;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectLight::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectLight::BeginPrint(LPVOID para,int layer)
{

}

void CEffectLight::Init(LPVOID para,int layer)
{
}

void CEffectLight::Calcu(LPVOID lpEffect,int layer)
{
}


#if defined _TINYAN3DLIB_
void CEffectLight::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int count = lp->count;
	int countMax = lp->countMax;
	int type = lp->para[4];
	int subFrame = lp->para[5];


	int colrr = CCalcuSpeed::calcu(count,countMax,0,lp->para[1],subFrame,type);
	int colgg = CCalcuSpeed::calcu(count,countMax,0,lp->para[2],subFrame,type);
	int colbb = CCalcuSpeed::calcu(count,countMax,0,lp->para[3],subFrame,type);



	CAllGraphics::AddSub(colrr,colgg,colbb);

	return;

}
#else

void CEffectLight::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int count = lp->count;
	int countMax = lp->countMax;
	int type = lp->para[4];
	int subFrame = lp->para[5];


	int colrr = CCalcuSpeed::calcu(count,countMax,0,lp->para[1],subFrame,type);
	int colgg = CCalcuSpeed::calcu(count,countMax,0,lp->para[2],subFrame,type);
	int colbb = CCalcuSpeed::calcu(count,countMax,0,lp->para[3],subFrame,type);

	int* screen = CMyGraphics::GetScreenBuffer();

	int sizeX = CMyGraphics::GetScreenSizeX();
	int sizeY = CMyGraphics::GetScreenSizeY();

	int loopSize = sizeX * sizeY / 4;

#if defined _WIN64
#pragma message("‚±‚±‚Éc++ŽÀ‘•‚ª•K—v‚É‚á " __FILE__)

#else

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		mov eax,colrr
		and eax,0ffffh
		movd mm5,eax

		mov eax,colgg
		and eax,0ffffh
		movd mm6,eax

		mov eax,colbb
		and eax,0ffffh
		movd mm7,eax

		psllq mm5,32
		psllq mm6,16

		por mm5,mm6
		por mm5,mm7

		mov eax,01000100h
		movd mm6,eax
		punpckldq mm6,mm6


		paddw mm5,mm6


		mov esi,screen
		mov ecx,loopSize
		pxor mm4,mm4
LOOP1:
		movq mm0,[esi]
		movq mm1,mm0

		punpcklbw mm0,mm4
		movq mm2,[esi+8]

		punpckhbw mm1,mm4
		movq mm3,mm2

		punpcklbw mm2,mm4
		paddw mm0,mm5

		punpckhbw mm3,mm4
		paddw mm1,mm5

		paddw mm2,mm5
		paddw mm3,mm5

		psubusw mm0,mm6
		psubusw mm1,mm6
		psubusw mm2,mm6
		packuswb mm0,mm1
		psubusw mm3,mm6

		movq [esi],mm0
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

