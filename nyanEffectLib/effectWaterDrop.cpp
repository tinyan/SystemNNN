//
// effectWaterDrop.cpp
//

#include "includer.h"
#include "effectWaterDrop.h"


CEffectWaterDrop::CEffectWaterDrop(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectWaterDrop::~CEffectWaterDrop()
{
	End();
}

void CEffectWaterDrop::End(void)
{
}

BOOL CEffectWaterDrop::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[3];
	int k = paraKosuu;
	if (k>3) k = 3;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}
	if (paraKosuu<1) para[0] = 0;
	if (paraKosuu<2) para[1] = para[0];
	if (paraKosuu<3) para[2] = para[1];

//	m_r = para[0];
//	m_g = para[1];
//	m_b = para[2];


	lp->flag = TRUE;
	lp->para[0] = para[0];
	lp->para[1] = para[1];
	lp->para[2] = para[2];

	lp->count = 0;
	lp->countMax = 9999;
	lp->command = EFFECT_WATERDROP;

	return TRUE;
}


BOOL CEffectWaterDrop::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectWaterDrop::BeginPrint(LPVOID para,int layer)
{

}

void CEffectWaterDrop::Init(LPVOID para,int layer)
{
}

void CEffectWaterDrop::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectWaterDrop::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	EFFECT* lp = (EFFECT*)lpEffect;

	int r = lp->para[0] & 0xff;
	int g = lp->para[1] & 0xff;
	int b = lp->para[2] & 0xff;

	int col = (r << 16) | (g << 8) | b;


	int loopSize = screenSizeX * screenSizeY;

#if defined _WIN64
#pragma message("***ŽÀ‘•‚µ‚½‚É‚á ‚±‚±‚Éc++ŽÀ‘•‚ª•K—v‚É‚á " __FILE__)
	for (int i = 0; i < loopSize; i++)
	{
		*dst = col;
		dst++;
	}
#else

	__asm
	{
		push eax
		push ecx
		push edi

		mov edi,dst
		mov ecx,loopSize
		mov eax,col

		cld
		rep stosd

		pop edi
		pop ecx
		pop eax
	}
#endif

}


BOOL CEffectWaterDrop::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}

BOOL CEffectWaterDrop::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


