//
// EffectBuffer.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "EffectBuffer.h"


CEffectBuffer::CEffectBuffer(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectBuffer::~CEffectBuffer()
{
	End();
}

void CEffectBuffer::End(void)
{
}

BOOL CEffectBuffer::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[3];
	int k = paraKosuu;
	if (k>1) k = 1;
	

	for (int i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;

	lp->flag = TRUE;

	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_BUFFER;

	return TRUE;
}



BOOL CEffectBuffer::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectBuffer::BeginPrint(LPVOID para,int layer)
{

}

void CEffectBuffer::Init(LPVOID para,int layer)
{
}

void CEffectBuffer::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectBuffer::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	return;


}


BOOL CEffectBuffer::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}

BOOL CEffectBuffer::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}

/*_*/



