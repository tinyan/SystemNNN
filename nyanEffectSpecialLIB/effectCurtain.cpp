//
// effectCurtain.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectCurtain.h"


CEffectCurtain::CEffectCurtain(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectCurtain::~CEffectCurtain()
{
	End();
}

void CEffectCurtain::End(void)
{
}

BOOL CEffectCurtain::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
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
	
	if (paraKosuu<2) para[1] = 100;	//
	if (paraKosuu<3) para[2] = 100;	//size

	if (paraKosuu<4) para[3] = 0;	//rEnd
	if (paraKosuu<5) para[4] = para[3];	//gEnd
	if (paraKosuu<6) para[5] = para[4];	//bEnd


	if (paraKosuu<7) para[6] = 0;	//moveType
	if (paraKosuu<8) para[7] = 0;	//moveSubFrame

	if (paraKosuu<9) para[8] = para[3];
	if (paraKosuu<10) para[9] = para[4];
	if (paraKosuu<11) para[10] = para[5];

	if (paraKosuu<12) para[11] = 0;	//colType
	if (paraKosuu<13) para[12] = 0;	//colSubFrame


	lp->flag = TRUE;
	lp->command = EFFECT_CURTAIN;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectCurtain::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectCurtain::BeginPrint(LPVOID para,int layer)
{

}

void CEffectCurtain::Init(LPVOID para,int layer)
{
}

void CEffectCurtain::Calcu(LPVOID lpEffect,int layer)
{
}



#if defined _TINYAN3DLIB_
void CEffectCurtain::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int count = lp->count;
	int countMax = lp->countMax;

	int moveType = lp->para[6];
	int moveSubFrame = lp->para[7];

	int r1 = lp->para[8];
	int g1 = lp->para[9];
	int b1 = lp->para[10];

	int r2 = lp->para[3];
	int g2 = lp->para[4];
	int b2 = lp->para[5];

	int colType = lp->para[11];
	int colSubFrame = lp->para[12];


	int up = CCalcuSpeed::calcu(count,countMax,0,lp->para[1],moveSubFrame,moveType);
	int down = CCalcuSpeed::calcu(count,countMax,0,screenSizeY-lp->para[1]-lp->para[2],moveSubFrame,moveType);

	int r = CCalcuSpeed::calcu(count,countMax,r1,r2,colSubFrame,colType);
	int g = CCalcuSpeed::calcu(count,countMax,g1,g2,colSubFrame,colType);
	int b = CCalcuSpeed::calcu(count,countMax,b1,b2,colSubFrame,colType);

	int col = (r << 16) | (g<<8) | b;

	if (up+down>screenSizeY)
	{
		down = screenSizeY - up;
	}

	if (up<0) up = 0;
	if (down<0) down = 0;

	if (up>0)
	{
		CAllGeo::BoxFill(0,0,screenSizeX,up,r,g,b);
	}

	if (down>0)
	{
		CAllGeo::BoxFill(0,screenSizeY-down,screenSizeX,down,r,g,b);
	}

}

#else

void CEffectCurtain::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int count = lp->count;
	int countMax = lp->countMax;

	int moveType = lp->para[6];
	int moveSubFrame = lp->para[7];

	int r1 = lp->para[8];
	int g1 = lp->para[9];
	int b1 = lp->para[10];

	int r2 = lp->para[3];
	int g2 = lp->para[4];
	int b2 = lp->para[5];

	int colType = lp->para[11];
	int colSubFrame = lp->para[12];


	int up = CCalcuSpeed::calcu(count,countMax,0,lp->para[1],moveSubFrame,moveType);
	int down = CCalcuSpeed::calcu(count,countMax,0,screenSizeY-lp->para[1]-lp->para[2],moveSubFrame,moveType);

	int r = CCalcuSpeed::calcu(count,countMax,r1,r2,colSubFrame,colType);
	int g = CCalcuSpeed::calcu(count,countMax,g1,g2,colSubFrame,colType);
	int b = CCalcuSpeed::calcu(count,countMax,b1,b2,colSubFrame,colType);

	int col = (r << 16) | (g<<8) | b;

	if (up+down>screenSizeY)
	{
		down = screenSizeY - up;
	}

	if (up<0) up = 0;
	if (down<0) down = 0;

	int lPitch = screenSizeX * 4;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		cld

		mov edi,dst
		mov ecx,up
		or ecx,ecx
		jz SKIP1
		mov eax,screenSizeX
		mul ecx
		mov ecx,eax
		mov eax,col
		rep stosd
SKIP1:

		mov ecx,down
		or ecx,ecx
		jz SKIP2
		mov eax,screenSizeX
		mul ecx
		mov ecx,eax
		mov eax,screenSizeY
		sub eax,down
		mov edx,lPitch
		mul edx
		add eax,dst
		mov edi,eax
		mov eax,col
		rep stosd

SKIP2:
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
}

#endif


/*
BOOL CEffectCurtain::CheckNeedPicPrint(LPVOID lpEffect)
{
	return TRUE;
}
*/