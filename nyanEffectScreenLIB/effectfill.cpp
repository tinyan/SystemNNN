//
// effectfill.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectfill.h"


CEffectFill::CEffectFill(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectFill::~CEffectFill()
{
	End();
}

void CEffectFill::End(void)
{
}

BOOL CEffectFill::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
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
	lp->command = EFFECT_FILL;

	for (i=0;i<4;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectFill::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectFill::BeginPrint(LPVOID para,int layer)
{

}

void CEffectFill::Init(LPVOID para,int layer)
{
}

void CEffectFill::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectFill::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int r = lp->para[1] & 0xff;
	int g = lp->para[2] & 0xff;
	int b = lp->para[3] & 0xff;

	CAllGraphics::FillScreen(r,g,b);
	return;

	int* dst = CMyGraphics::GetScreenBuffer();

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


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


BOOL CEffectFill::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectFill::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


