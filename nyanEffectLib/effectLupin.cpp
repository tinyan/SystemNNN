//
// effectLupin.cpp
//

#include "includer.h"
#include "effectLupin.h"


CEffectLupin::CEffectLupin(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectLupin::~CEffectLupin()
{
	End();
}

void CEffectLupin::End(void)
{
}

BOOL CEffectLupin::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[4];
	int k = paraKosuu;
	if (k>4) k = 4;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;
	if (paraKosuu<2) para[1] = 0;
	if (paraKosuu<3) para[2] = para[1];
	if (paraKosuu<4) para[3] = para[2];


	lp->flag = TRUE;
	lp->count = 0;
	lp->countMax = 9999;
	lp->command = EFFECT_LUPIN;

	for (i=0;i<4;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectLupin::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectLupin::BeginPrint(LPVOID para,int layer)
{

}

void CEffectLupin::Init(LPVOID para,int layer)
{
}

void CEffectLupin::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectLupin::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	EFFECT* lp = (EFFECT*)lpEffect;

	int r = lp->para[1] & 0xff;
	int g = lp->para[2] & 0xff;
	int b = lp->para[3] & 0xff;

	int col = (r << 16) | (g << 8) | b;

	int sz = screenSizeX * screenSizeY;

#if defined _WIN64
#pragma message("‚±‚±‚Éc++ŽÀ‘•‚ª•K—v‚É‚á " __FILE__)

#else

	__asm
	{
		push eax
		push ecx
		push edi

		mov edi,dst
		mov ecx,sz
		mov eax,col

		cld
		rep stosd

		pop edi
		pop ecx
		pop eax
	}

#endif

}


BOOL CEffectLupin::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectLupin::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


