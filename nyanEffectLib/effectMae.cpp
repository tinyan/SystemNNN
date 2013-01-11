//
// EffectMae.cpp
//

#include "includer.h"
#include "EffectMae.h"


CEffectMae::CEffectMae(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectMae::~CEffectMae()
{
	End();
}

void CEffectMae::End(void)
{
}

BOOL CEffectMae::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	return TRUE;
}



BOOL CEffectMae::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectMae::BeginPrint(LPVOID para,int layer)
{

}

void CEffectMae::Init(LPVOID para,int layer)
{
}

void CEffectMae::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectMae::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	return;


}


BOOL CEffectMae::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}

BOOL CEffectMae::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}

/*_*/



