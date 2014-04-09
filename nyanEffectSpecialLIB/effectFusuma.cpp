//
// effectFusuma.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectFusuma.h"



CEffectFusuma::CEffectFusuma(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
}


CEffectFusuma::~CEffectFusuma()
{
	End();
}

void CEffectFusuma::End(void)
{
}

BOOL CEffectFusuma::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	EFFECT* lp = (EFFECT*)lpEffect;

	int para[16];
	int k = paraKosuu;
	if (k>7) k = 7;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

//	"フレーム",0,9999,20,
//	"サイズ",0,9999,160,
//	"次の絵",0,15,13,
//	"開始待ち",0,9999,0,
//	"終了ため",0,9999,0,
//	"*方向",0,0,0,





	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 160;	//size
	if (paraKosuu<3) para[2] = 13;	//pic2

	if (paraKosuu<4) para[3] = 0;	//たいぷ
	if (paraKosuu<5) para[4] = 0;	//さぶふれ
//	if (paraKosuu<6) para[5] = 0;	//houkou
//	if (paraKosuu<7) para[6] = 0;	//加速タイプ

	if (para[1]>screenSizeX / 2) para[1] = screenSizeX / 2;


	lp->flag = TRUE;
	lp->command = EFFECT_FUSUMA;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<7;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectFusuma::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectFusuma::BeginPrint(LPVOID para,int layer)
{

}

void CEffectFusuma::Init(LPVOID para,int layer)
{
}

void CEffectFusuma::Calcu(LPVOID lpEffect,int layer)
{
}



void CEffectFusuma::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	CPicture* lpPic1 = m_allEffect->GetPicture(layer);
	if (lpPic1 == NULL) return;
	RECT rc;
	lpPic1->GetPicSize(&rc);
	int picSizeX1 = rc.right;
	int picSizeY1 = rc.bottom;
	if (picSizeX1<screenSizeX) return;
	if (picSizeY1<screenSizeY) return;

	CPicture* lpPic2 = m_allEffect->GetPicture(lp->para[2]);
	if (lpPic2 == NULL) return;
	RECT rc2;
	lpPic2->GetPicSize(&rc2);
	int picSizeX2 = rc2.right;
	int picSizeY2 = rc2.bottom;
	if (picSizeX2<screenSizeX) return;
	if (picSizeY2<screenSizeY) return;

	int* src1 = (int*)(lpPic1->GetBuffer());
	if (src1 == NULL) return;

	int* src2 = (int*)(lpPic2->GetBuffer());
	if (src2 == NULL) return;

	int count = lp->count;
	int frame = lp->countMax;
	int type = lp->para[3];
	int subFrame = lp->para[4];

	//int startWait = lp->para[3];
	//int endWait = lp->para[4];
	int fusumaSize = lp->para[1];

	int dot = CCalcuSpeed::calcu(count,frame,0,fusumaSize,subFrame,type);

	if (dot == 0)
	{
		lpPic1->Blt(0,0,0,0,screenSizeX,screenSizeY,FALSE);
		return;
	}


	int leftLoop1 = screenSizeX / 2 - fusumaSize;
	int leftLoop2 = fusumaSize - dot;
	int rightLoop1 = fusumaSize - dot;
	int rightLoop2 = screenSizeX / 2 - fusumaSize;
	int centerLoop = (fusumaSize - leftLoop2 + fusumaSize - rightLoop1);

	int leftDelta1 = 0;
	int leftDelta2 = dot * sizeof(int);
	int rightDelta1 = 0;
	int rightDelta2 = dot * sizeof(int);




	lpPic1->Blt(0,0,0,0,leftLoop1,screenSizeY,FALSE);
	lpPic1->Blt(leftLoop1,0,leftLoop1+dot,0,leftLoop2,screenSizeY,FALSE);
	
	lpPic1->Blt(screenSizeX-rightLoop2-rightLoop1,0,screenSizeX/2,0,rightLoop1,screenSizeY,FALSE);
	lpPic1->Blt(screenSizeX-rightLoop2,0,screenSizeX-rightLoop2,0,rightLoop2,screenSizeY,FALSE);
	
	lpPic2->Blt(leftLoop1+leftLoop2,0,leftLoop1+leftLoop2,0,centerLoop,screenSizeY,FALSE);

	return;






	int src1Pitch = picSizeX1 * sizeof(int);
	int src2Pitch = picSizeX2 * sizeof(int);


	src2 += leftLoop1;
	src2 += leftLoop2;


	int lPitch = screenSizeX * sizeof(int);
	int loopY = screenSizeY;

	int* dst = CMyGraphics::GetScreenBuffer();

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		cld

		mov ecx,loopY
		mov esi,src1
		mov ebx,src2
		mov edi,dst
LOOP1:
		push ebx
		push ecx
		push esi
		push edi

		mov ecx,leftLoop1
		or ecx,ecx
		jz SKIP1
		rep movsd
SKIP1:
		add esi,leftDelta2
		mov ecx,leftLoop2
		or ecx,ecx
		jz SKIP2
		rep movsd
SKIP2:
		xchg ebx,esi
		mov ecx,centerLoop
		or ecx,ecx
		jz SKIP3
		rep movsd
SKIP3:
		xchg ebx,esi

		mov ecx,rightLoop1
		or ecx,ecx
		jz SKIP4
		rep movsd
SKIP4:
		add esi,rightDelta2
		mov ecx,rightLoop2
		or ecx,ecx
		jz SKIP5
		rep movsd
SKIP5:


		pop edi
		pop esi
		pop ecx
		pop ebx
		add edi,lPitch
		add esi,src1Pitch
		add ebx,src2Pitch
		dec ecx
		jnz LOOP1

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax

	}
}


BOOL CEffectFusuma::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}

BOOL CEffectFusuma::CheckAllPrint(LPVOID lpEffect, int layer)
{
	return TRUE;
}


/*_*/
