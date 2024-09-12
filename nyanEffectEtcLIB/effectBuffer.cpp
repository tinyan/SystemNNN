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
	if (k>2) k = 2;
	

	for (int i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;
	if (paraKosuu < 2) para[1] = 0;
//	para[2] = 0;

	lp->flag = TRUE;

	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_BUFFER;

	for (int i = 0; i < 3; i++)
	{
		lp->para[i] = para[i];
	}

	if (lp->para[1] != 0)
	{
		CPicture* lpPic = m_allEffect->GetPicture(layer);
		if (lpPic != nullptr)
		{
			lpPic->Shrink();
		}
	}

	return TRUE;
}



BOOL CEffectBuffer::CountIsMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

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



