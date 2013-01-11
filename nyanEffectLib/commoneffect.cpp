//
// commoneffect.cpp
//

//#include <windows.h>

//#include "..\nyanlib\include\commonmacro.h"

//#include "commoneffect.h"
//#include "allEffect.h"
#include "includer.h"

//CCommonEffect::CCommonEffect(CEffect* lpCEffect)
#if defined _TINYAN3DLIB_
CCommonEffect::CCommonEffect(CAllEffect* lpAll,int shaderKosuu) : CCommonShader(SHADER_EFFECT_EFFECT,shaderKosuu)
#else
CCommonEffect::CCommonEffect(CAllEffect* lpAll,int shaderKosuu)
#endif
{
//	m_effect = lpCEffect;
	m_allEffect = lpAll;

	m_calcuedFlag = FALSE;
	m_renzokuEffectFlag = FALSE;
#if defined _TINYAN3DLIB_
	m_pixelShader = NULL;
#endif
}

CCommonEffect::~CCommonEffect()
{
	End();
}

void CCommonEffect::End(void)
{
#if defined _TINYAN3DLIB_
	ENDDELETECLASS(m_pixelShader);
#endif
}


//void CCommonEffect::GeneralSetParam(int paraKosuu, int* paraPtr)
//{
//	SetParam(paraKosuu,paraPtr);
//}

void CCommonEffect::GeneralBeginPrint(LPVOID para,int layer)
{
	BeginPrint(para,layer);
	m_calcuedFlag = FALSE;
}

void CCommonEffect::GeneralInit(LPVOID para,int layer)
{
	Init(para,layer);
}

void CCommonEffect::GeneralCalcu(LPVOID para,int layer)
{
	Calcu(para,layer);
	m_calcuedFlag = TRUE;
}

void CCommonEffect::GeneralPrint(LPVOID para,int layer)
{
	Print(para,layer);
}


BOOL CCommonEffect::CheckRenzokuEffect(void)
{
	return m_renzokuEffectFlag;
}


BOOL CCommonEffect::CountIsMax(LPVOID lpEffect, int layer)
{
	// if effect is changed return true


	return FALSE;
}


//virtual method
BOOL CCommonEffect::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	return FALSE;
}

void CCommonEffect::BeginPrint(LPVOID para,int layer)
{
}

void CCommonEffect::Init(LPVOID para,int layer)
{
}

void CCommonEffect::Calcu(LPVOID para,int layer)
{
}

void CCommonEffect::Print(LPVOID para,int layer)
{
}

BOOL CCommonEffect::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CCommonEffect::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

void CCommonEffect::InitParameter(LPVOID lpEffect, int layer)
{
	if (layer == -1) return;

}


int CCommonEffect::GetEternalType(void)
{
	return 0;	//dummy
	//0:í èÌ
	//1:âië±
	//2:Ç¶ÇÁÇ◊ÇÈ
}

int CCommonEffect::GetLayerOrPicType(void)
{
	return 0;	//dummy
	//0:pic
	//1:layer
}

int CCommonEffect::GetOnlyOneType(void)
{
	return 0;	//dummy
	//0:Ç¢Ç≠Ç¬Ç≈Ç‡
	//1:ÇPÇ¬ÇÃÇ›
	//2:ÇPÇ¬ÇÃÇ›Åiï™äÑâ¬î\Åj
}

#if defined _TINYAN3DLIB_
void CCommonEffect::ShaderPass(int n,POINT* lpDstPoint,SIZE* lpDstSize,POINT* lpSrcPoint,SIZE* lpSrcSize)
{
	OutputDebugString("[default effect pass]");
}
#endif


/*_*/

