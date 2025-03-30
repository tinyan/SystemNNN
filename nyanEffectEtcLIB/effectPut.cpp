//
// effectPut.cpp
//

#include "..\nyanEffectLib\includer.h"
#include "effectGet.h"
#include "effectPut.h"



CEffectPut::CEffectPut(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
}


CEffectPut::~CEffectPut()
{
	End();
}

void CEffectPut::End(void)
{
}


BOOL CEffectPut::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


//	if (CEffectGet::m_effectGetBuffer == NULL) return FALSE;	//error

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
	if (paraKosuu<2) para[1] = 0;			//r
	if (paraKosuu<3) para[2] = para[1];		//g
	if (paraKosuu<4) para[3] = para[2];		//b
	if (paraKosuu<5) para[4] = 0;			//1–‡–Ú“ÁŽêˆ—‚µ‚È‚¢ƒtƒ‰ƒO

	lp->flag = TRUE;
	lp->command = EFFECT_PUT;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectPut::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectPut::BeginPrint(LPVOID para,int layer)
{

}

void CEffectPut::Init(LPVOID para,int layer)
{
}

void CEffectPut::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectPut::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int dv = lp->countMax;
	int c = lp->count;

	if (dv<1)
	{
		dv = 1;
	}

//	if (((c == 0) && (lp->para[4] == 0))|| (CEffectGet::m_effectGetBuffer == NULL))
	if ((c == 0) && (lp->para[4] == 0))
	{
		//not put and fill color or put org_pic

		int pic = lp->pic;
		CPicture* lpPic = NULL;
		if (pic != -1)
		{
			lpPic = m_allEffect->GetPicture(layer);
		}

		if (lpPic != NULL)
		{
//			RECT rc = m_effect->m_effect[pic].dst;
			POINT dstPoint = m_allEffect->GetDstPoint(pic);
			
			RECT rc2;
			lpPic->GetPicSize(&rc2);

//			int x = rc.left;
//			int y = rc.top;
			int x = dstPoint.x;
			int y = dstPoint.y;

			int sizeX = rc2.right;
			int sizeY = rc2.bottom;

			lpPic->Blt(x,y,0,0,sizeX,sizeY,FALSE);
		}
		else
		{
			CAllGraphics::FillScreen(lp->para[1],lp->para[2],lp->para[3]);
		}

		return;
	}


	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	INT32* dst = CMyGraphics::GetScreenBuffer();
	INT32* src = CEffectGet::m_effectGetBuffer;
	int sz = screenSizeX * screenSizeY;

#if defined _WIN64
	
	for (int i = 0; i < sz;i++)
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


void CEffectPut::PutScreen(void)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	INT32* dst = CMyGraphics::GetScreenBuffer();
	INT32* src = CEffectGet::m_effectGetBuffer;
	int sz = screenSizeX * screenSizeY;

#if defined _WIN64
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


BOOL CEffectPut::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}

/*_*/

