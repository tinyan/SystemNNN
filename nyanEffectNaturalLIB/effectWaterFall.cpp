//
// effectWaterFall.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectWaterFall.h"


CEffectWaterFall::CEffectWaterFall(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectWaterFall::~CEffectWaterFall()
{
	End();
}

void CEffectWaterFall::End(void)
{
}

BOOL CEffectWaterFall::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[8];
	int k = paraKosuu;
	if (k>8) k = 8;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}


	if (paraKosuu<1) para[0] = 20;	//frame dummy
	if (paraKosuu<2) para[1] = 0;	//x
	if (paraKosuu<3) para[2] = 0;	//y
	if (paraKosuu<4) para[3] = 24;	//height
	if (paraKosuu<5) para[4] = -1;	//piclayer
	if (paraKosuu<6) para[5] = 100;	//v0
	if (paraKosuu<7) para[6] = 20;	//g
	if (paraKosuu<8) para[7] = 2;	//trans


	lp->flag = TRUE;
	for (i=0;i<8;i++)
	{
		lp->para[i] = para[i];
	}

	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_WATERFALL;

	return TRUE;
}


BOOL CEffectWaterFall::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectWaterFall::BeginPrint(LPVOID para,int layer)
{

}

void CEffectWaterFall::Init(LPVOID para,int layer)
{
}

void CEffectWaterFall::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	int c = lp->count;

	int pl = lp->para[4];
	if (pl == -1) pl = layer;

	CPicture* lpPic = m_allEffect->GetPicture(pl);
	if (lpPic == NULL) return;

	RECT rc;
	lpPic->GetPicSize(&rc);
	int picSizeY = rc.bottom;
	if (picSizeY<1) return;

	int v0 = lp->para[5];
	if (v0<1) return;

	int k = (c * v0) / 100;
	if (k>=picSizeY)
	{
		k %= picSizeY;
		k *= 100;
		k /= v0;
		lp->count = k;
	}
}


void CEffectWaterFall::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	EFFECT* lp = (EFFECT*)lpEffect;

	int c = lp->count;

	int pl = lp->para[4];
	if (pl == -1) pl = layer;

	CPicture* lpPic = m_allEffect->GetPicture(pl);
	if (lpPic == NULL) return;

	int* src = (int*)(lpPic->GetBuffer());
	if (src == NULL) return;

	char* mask = NULL;
	if (lpPic->CheckMaskExist())
	{
		mask = lpPic->GetMaskPic();
	}

	int md = lp->para[7];
	if (md == 2)
	{
		if (mask == NULL) md = 1;
	}

	RECT rc;
	lpPic->GetPicSize(&rc);
	int picSizeX = rc.right;
	int picSizeY = rc.bottom;

	if (picSizeX<1) return;
	if (picSizeY<1) return;

	int putX = lp->para[1];
	int putY = lp->para[2];
	int sizeX = picSizeX;


	if (putX>=screenSizeX) return;
	if (putY>=screenSizeY) return;

	int sizeY = lp->para[3];

	if ((putX+sizeX)>screenSizeX)
	{
		sizeX = screenSizeX - putX;
	}

	if ((putY+sizeY)>screenSizeY)
	{
		sizeY = screenSizeY - putY;
	}

	if ((sizeX<1) || (sizeY<1)) return;

	double v0 = (double)(lp->para[5]);
	v0 /= 100.0;

	double grav = (double)(lp->para[6]);
	grav /= 100.0;



	int picStartY = 0;
	
//	int work[MAXSCREENSIZEY*2];
//	int* work = CEffectSimpleWipe::m_shapeWork;
	int* work = m_allEffect->GetTempWork();
	int* table = work;


	double dc = (double)c;
	dc *= v0;

	for (int i=0;i<screenSizeY;i++)
	{
		double s = (double)i;
		double vv = sqrt(v0*v0 + 2.0*grav*s);

		double t = (vv - v0) / grav;

		double lo = v0 / vv;


		int ps = (int)(lo * 256.0 + 0.5);
		if (ps<0) ps = 0;
		if (ps>256) ps = 256;

		int dy = (int)(t * v0 - dc + 0.5);

		if (dy<0)
		{
			dy *= -1;
			dy %= picSizeY;
			dy *= -1;
			dy += picSizeY;
		}

		dy %= picSizeY;
		



		work[i*2] = dy;	//deltaPicY
		work[i*2+1] = ps;	//trans percent(256)
	}

	dst += putX;
	dst += putY * screenSizeX;

	int lPitch = screenSizeX * sizeof(int);
	int srcPitch = picSizeX * sizeof(int);
	int maskPitch = picSizeX;

if (md != 2) return;

#if defined _WIN64
#pragma message("‚±‚±‚Éc++ŽÀ‘•‚ª•K—v‚É‚á " __FILE__)

#else

	__asm
	{
		push eax
		push ecx
		push edi

		pxor mm0,mm0

		mov eax,255
		movd mm7,eax
		punpcklwd mm7,mm7
		punpckldq mm7,mm7

		mov ebx,table
		mov ecx,sizeY
		mov edi,dst
LOOP1:
		push ebx
		push ecx
		push edi

		mov eax,[ebx]
		mov edx,srcPitch
		mul edx
		add eax,src
		mov esi,eax

		mov eax,[ebx]
		mov edx,maskPitch
		mul edx
		add eax,mask
		mov edx,[ebx+4]
		mov ebx,eax

		movd mm1,edx
		neg edx
		add edx,256
		movd mm2,edx

		punpcklwd mm1,mm1
		punpcklwd mm2,mm2
		punpckldq mm1,mm1
		punpckldq mm2,mm2

		mov ecx,sizeX
LOOP2:
		xor eax,eax
		mov al,[ebx]
		or eax,eax
		jz SKIP1

		movq mm3,mm1
		movq mm4,mm2

		cmp eax,255
		jz NORMAL1

		movd mm5,eax

		punpcklwd mm5,mm5
		punpckldq mm5,mm5
		pmullw mm3,mm5
		psrlw mm3,8

		movq mm4,mm7
		psubw mm4,mm3

NORMAL1:
		mov eax,[esi]
		mov edx,[edi]
		movd mm5,eax
		movd mm6,edx
		punpcklbw mm5,mm0
		punpcklbw mm6,mm0

		pmullw mm5,mm3
		pmullw mm6,mm4

		paddw mm5,mm6
		psrlw mm5,8
		packuswb mm5,mm0
		movd eax,mm5

		mov [edi],eax

SKIP1:
		add esi,4
		inc ebx
		add edi,4
		dec ecx
		jnz LOOP2


		pop edi
		pop ecx
		pop ebx
		add edi,lPitch
		add ebx,4*2
		dec ecx
		jnz LOOP1

		emms

		pop edi
		pop ecx
		pop eax
	}

#endif

}


BOOL CEffectWaterFall::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectWaterFall::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


