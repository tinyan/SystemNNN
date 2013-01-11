//
// effectmeltdown.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectMeltDown.h"


CEffectMeltDown::CEffectMeltDown(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(1);
	Create("MeltDown");
#endif
}

CEffectMeltDown::~CEffectMeltDown()
{
	End();
}

void CEffectMeltDown::End(void)
{
}

BOOL CEffectMeltDown::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
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

	if (paraKosuu<1) para[0] = 20;
	if (paraKosuu<2) para[1] = 0;//type
	if (paraKosuu<3) para[2] = 0;//subframe


	lp->flag = TRUE;
	lp->command = EFFECT_MELTDOWN;
	lp->count = 0;
	lp->countMax = para[0];
	
	for (i=0;i<3;i++)
	{
		lp->para[i] = para[i];
	}


	return TRUE;
}


BOOL CEffectMeltDown::CountIsMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	if (lp->para[1] == 1)
	{
//		lp->command = EFFECT_NOP;
//		if (lp->pic == -1)
//		{
//			lp->flag = FALSE;
//		}
	}
	return TRUE;
}


void CEffectMeltDown::BeginPrint(LPVOID para,int layer)
{

}

void CEffectMeltDown::Init(LPVOID para,int layer)
{
}

void CEffectMeltDown::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectMeltDown::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int count = lp->count;
	int countMax = lp->countMax;
	int type = lp->para[1];
	int subFrame = lp->para[2];


	int sizeY = CCalcuSpeed::calcu(count,countMax,0,screenSizeY-1,subFrame,type);
	int y = screenSizeY-1 - sizeY;

	if (y<0) y = 0;

	if (y>=(screenSizeY-1)) return;

#if defined _TINYAN3DLIB_
	CopyScreenToBuffer();
	SetTexture(GetBufferTexture());
	POINT dstPoint;
	SIZE dstSize;
	POINT srcPoint;
	SIZE srcSize;
	SIZE srcPicSize;

	dstPoint.x = 0;
	dstPoint.y = y;
	dstSize.cx = screenSizeX;
	dstSize.cy = screenSizeY - y;
	srcPoint.x = 0;
	srcPoint.y = y;
	srcSize.cx = screenSizeX;
	srcSize.cy = 1;
	srcPicSize.cx = screenSizeX;
	srcPicSize.cy = screenSizeY;

	StretchBlt(&dstPoint,&dstSize,&srcPoint,&srcSize,&srcPicSize);

#else
	int* screen = CMyGraphics::GetScreenBuffer();

	int lPitch = screenSizeX * sizeof(int);

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		mov esi,screen
		mov eax,y
		mov edx,lPitch
		mul edx
		add esi,eax
		mov edi,esi
		add edi,lPitch
		mov eax,y
		neg eax
		add eax,screenSizeY
		dec eax
		mov edx,screenSizeX
		mul edx
		mov ecx,eax
		cld
		rep movsd

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
