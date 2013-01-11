//
// effectCharaSepia.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectSaike.h"


CEffectSaike::CEffectSaike(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectSaike::~CEffectSaike()
{
	End();
}

void CEffectSaike::End(void)
{
}

BOOL CEffectSaike::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[32];
	int k = paraKosuu;
	if (k>17) k = 17;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}
	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 0;	//type
	if (paraKosuu<3) para[2] = 0;	//subframe

	if (paraKosuu<4) para[3] = 200;	//end mulr
	if (paraKosuu<5) para[4] = 200;	//end mulg
	if (paraKosuu<6) para[5] = 200;	//end mulb

	if (paraKosuu<7) para[6] = para[3];	//start mulr
	if (paraKosuu<8) para[7] = para[4];	//start mulg
	if (paraKosuu<9) para[8] = para[5];	//start mulb

	if (paraKosuu<10) para[9] = 0;	//end dr
	if (paraKosuu<11) para[10] = 0;	//end dg
	if (paraKosuu<12) para[11] = 0;	//end db

	if (paraKosuu<13) para[12] = para[9];	//start dr
	if (paraKosuu<14) para[13] = para[10];	//start dg
	if (paraKosuu<15) para[14] = para[11];	//start db

	//sub
	if (paraKosuu<16) para[15] = para[1];	//type
	if (paraKosuu<17) para[16] = para[2];	//subframe


	lp->flag = TRUE;
	for (i=0;i<20;i++)
	{
		lp->para[i] = para[i];
	}

	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_SAIKE;

	return TRUE;
}


BOOL CEffectSaike::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectSaike::BeginPrint(LPVOID para,int layer)
{

}

void CEffectSaike::Init(LPVOID para,int layer)
{
}

void CEffectSaike::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectSaike::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int subType = lp->para[1];
	int subFrame = lp->para[2];
	int endPs = lp->para[3];
	int startPs = lp->para[4];

	int subType2 = lp->para[15];
	int subFrame2 = lp->para[16];

	int count = lp->count;
	int countMax = lp->countMax;


	int endMulR = lp->para[3];
	int endMulG = lp->para[4];
	int endMulB = lp->para[5];

	int startMulR = lp->para[6];
	int startMulG = lp->para[7];
	int startMulB = lp->para[8];

	int endAddR = lp->para[9];
	int endAddG = lp->para[10];
	int endAddB = lp->para[11];

	int startAddR = lp->para[12];
	int startAddG = lp->para[13];
	int startAddB = lp->para[14];

	int mulR = CCalcuSpeed::calcu(count,countMax,startMulR*256,endMulR*256,subFrame,subType) / 100;
	int mulG = CCalcuSpeed::calcu(count,countMax,startMulG*256,endMulG*256,subFrame,subType) / 100;
	int mulB = CCalcuSpeed::calcu(count,countMax,startMulB*256,endMulB*256,subFrame,subType) / 100;

	int addR = CCalcuSpeed::calcu(count,countMax,startAddR,endAddR,subFrame2,subType2);
	int addG = CCalcuSpeed::calcu(count,countMax,startAddG,endAddG,subFrame2,subType2);
	int addB = CCalcuSpeed::calcu(count,countMax,startAddB,endAddB,subFrame2,subType2);



	int putX = lp->dst.left;
	int putY = lp->dst.top;
	int srcX = lp->src.left;
	int srcY = lp->src.top;
	int sizeX = lp->dst.right;
	int sizeY = lp->dst.bottom;

	int pic = lp->pic;
	if (pic == -1) return;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;


	if (lpPic->Clip(putX,putY,srcX,srcY,sizeX,sizeY) == FALSE) return;
	if (lpPic->CheckMaskExist() == FALSE) return;


	SIZE picSize = lpPic->GetPicSize();

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();
	int picSizeX = picSize.cx;
	int picSizeY = picSize.cy;
	int dstPitch = screenSizeX * sizeof(int);
//	int* dst = CMyGraphics::GetScreenBuffer();
	char* mask = lpPic->GetMaskPic();

	int* src = (int*)(lpPic->GetBuffer());


	src += srcY * picSizeX + srcX;
	dst += putY * screenSizeX + putX;
	mask += srcY * picSizeX + srcX;


	int srcPitch = picSizeX * 4;
	int maskPitch = picSizeX;

	int loopY = sizeY;
	int loopX = sizeX;


	mulR &= 0xffff;
	mulG &= 0xffff;
	mulB &= 0xffff;
	addR &= 0x00ff;
	addG &= 0x00ff;
	addB &= 0x00ff;

	int mul1 = mulR;
	int mul2 = (mulG << 16) | mulB;
	int addColor = (addR << 16) | (addG << 8) | addB;



	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		pxor mm0,mm0

		mov eax,mul1
		movd mm6,eax
		psllq mm6,32
		mov eax,mul2
		movd mm1,eax
		por mm6,mm1

		mov eax,0xff00ff
		movd mm5,eax
		mov eax,0xff
		movd mm4,eax
		psllq mm4,32
		por mm5,mm4


		mov eax,addColor
		movd mm7,eax
		punpcklbw mm7,mm0



		mov esi,src
		mov edi,dst
		mov ebx,mask

		mov ecx,loopY
LOOP_M_1:
		push ecx
		push ebx
		push esi
		push edi

		mov ecx,loopX
LOOP_M_2:
		xor eax,eax
		mov al,[ebx]
		or al,al
		jz SKIP_M

		mov edx,[esi]
		movd mm1,edx
		punpcklbw mm1,mm0
		pmullw mm1,mm6
		psrlw mm1,8
		paddw mm1,mm7
		pand mm1,mm5

		cmp al,255
		jz NORMAL_M

		mov edx,[edi]
		movd mm2,edx
		punpcklbw mm2,mm0

		mov edx,eax
		inc eax
		not dl
		movd mm3,eax
		movd mm4,edx

		punpcklwd mm3,mm3
		punpcklwd mm4,mm4
		punpckldq mm3,mm3
		punpckldq mm4,mm4

		pmullw mm1,mm3
		pmullw mm2,mm4

		paddw mm1,mm2
		psrlw mm1,8
NORMAL_M:
		packuswb mm1,mm0
		movd edx,mm1
		mov [edi],edx

SKIP_M:
		add esi,4
		add edi,4
		inc ebx
		dec ecx
		jnz LOOP_M_2

		pop edi
		pop esi
		pop ebx
		pop ecx
			
		add edi,dstPitch
		add esi,srcPitch
		add ebx,maskPitch

		dec ecx
		jnz LOOP_M_1

		emms

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}



}


BOOL CEffectSaike::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectSaike::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


