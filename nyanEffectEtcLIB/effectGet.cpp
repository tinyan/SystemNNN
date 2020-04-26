//
// effectGet.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectGet.h"

CPicture* CEffectGet::m_effectGetBufferPicture = NULL;
int* CEffectGet::m_effectGetBuffer = NULL;

CEffectGet::CEffectGet(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
//	m_effectGetBuffer = NULL;	//確保しにゃい。
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	m_effectGetBufferPicture = new CPicture(screenSizeX,screenSizeY);
	m_effectGetBuffer = (int*)(m_effectGetBufferPicture->GetBuffer());
}


CEffectGet::~CEffectGet()
{
	End();
}

void CEffectGet::End(void)
{
	ENDDELETECLASS(m_effectGetBufferPicture);
//	DELETEARRAY(m_effectGetBuffer);
}


BOOL CEffectGet::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

//	if (m_effectGetBuffer == NULL)
//	{
//		m_effectGetBuffer = new int[screenSizeX * screenSizeY];
//	}
//	if (m_effectGetBuffer == NULL) return FALSE;	//error

	EFFECT* lp = (EFFECT*)lpEffect;

	int para[16];
	int k = paraKosuu;
	if (k>16) k = 16;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;	//frame
	

	lp->flag = TRUE;
	lp->command = EFFECT_GET;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectGet::CountIsMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

//	lp->command = EFFECT_NOP;
//	if (lp->pic == -1)
//	{
//		lp->flag = FALSE;
//	}
//
//	return TRUE;
	return FALSE;
}


void CEffectGet::BeginPrint(LPVOID para,int layer)
{

}

void CEffectGet::Init(LPVOID para,int layer)
{
}

void CEffectGet::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectGet::Print(LPVOID lpEffect,int layer)
{
//	if (m_effectGetBuffer == NULL) return;

	EFFECT* lp = (EFFECT*)lpEffect;

	int dv = lp->countMax;
	int c = lp->count;

	if (dv<1)
	{
		dv = 1;
	}

	GetScreen();
}

#if defined _TINYAN3DLIB_
void CEffectGet::GetScreen(void)
{
	m_effectGetBufferPicture->GetScreen();
	return;
}
#else

void CEffectGet::GetScreen(void)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

//	if (m_effectGetBuffer == NULL)
//	{
//		m_effectGetBuffer = new int[screenSizeX * screenSizeY];
//	}
//	if (m_effectGetBuffer == NULL) return;	//error

	int* src = CMyGraphics::GetScreenBuffer();
	int* dst = m_effectGetBuffer;
//	int* dst = (int*)(m_effectGetBufferPicture->GetBuffer());
	int sz = screenSizeX * screenSizeY;

#if defined _WIN64
#pragma message("***実装したにゃ ここにc++実装が必要にゃ " __FILE__)
	for (int i = 0; i < sz; i++)
	{
		*dst = *src;
		src++;
		dst++;
	}
#else

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		mov esi,src
		mov edi,dst
		mov ecx,sz
		cld
		rep movsd

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

