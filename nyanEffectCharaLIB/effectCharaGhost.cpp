//
// EffectCharaGhost.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "EffectCharaGhost.h"



CEffectCharaGhost::CEffectCharaGhost(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(2);
	Create("CharaGhost");
#endif
}


CEffectCharaGhost::~CEffectCharaGhost()
{
	End();
}

void CEffectCharaGhost::End(void)
{
}

BOOL CEffectCharaGhost::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int para[16];
	int k = paraKosuu;
	if (k>16) k = 16;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;	

	if (paraKosuu<2) para[1] = 200;	//upStart
	if (paraKosuu<3) para[2] = 0;	//upEnd
	if (paraKosuu<4) para[3] = 100;	//downStart
	if (paraKosuu<5) para[4] = -100;	//downEnd

	if (paraKosuu<6) para[5] = 0;	//speedtype
	if (paraKosuu<7) para[6] = 0;	//subframe



	lp->flag = TRUE;
	lp->command = EFFECT_CHARAGHOST;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectCharaGhost::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectCharaGhost::BeginPrint(LPVOID para,int layer)
{

}

void CEffectCharaGhost::Init(LPVOID para,int layer)
{

}




void CEffectCharaGhost::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
}


#if defined _TINYAN3DLIB_
void CEffectCharaGhost::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int dv = lp->countMax;	//not use
	int c = lp->count;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;
	if (lpPic->Check256()) return;
	if (lpPic->CheckMaskExist() == FALSE) return;


	int upStart = lp->para[1];
	int upEnd = lp->para[2];
	int downStart = lp->para[3];
	int downEnd = lp->para[4];

	int speedType = lp->para[5];
	int subFrame = lp->para[6];

	int up = CCalcuSpeed::calcu(c,dv,upStart*255,upEnd*255,subFrame,speedType);
	int down = CCalcuSpeed::calcu(c,dv,downStart*255,downEnd*255,subFrame,speedType);

	up /= 100;
	down /= 100;

	SIZE sz = lpPic->GetPicSize();
	int picSizeX = sz.cx;
	int picSizeY = sz.cy;


	int* transWork = m_allEffect->GetTempWork();

	POINT pt = m_allEffect->GetDstPoint(layer);
	int putX = pt.x;
	int putY = pt.y;
	int srcX = 0;
	int srcY = 0;
	int sizeX = picSizeX;
	int sizeY = picSizeY;

	//genral clip
	if (putX>=screenSizeX) return;
	if (putY>=screenSizeY) return;
	if ((putX+sizeX) <= 0) return;
	if ((putY+sizeY) <= 0) return;


	//clip x
	if (putX<0)
	{
		srcX -= putX;
		sizeX += putX;
		putX = 0;
		if (sizeX<=0) return;
	}

	if (putX+sizeX>screenSizeX)
	{
		sizeX = screenSizeX - putX;
		if (sizeX<=0) return;
	}

	//clipY	
	int deltaY = 0;

	if (putY < 0)
	{
		srcY -= putY;
		sizeY += putY;
		deltaY = -putY;
		putY = 0;
		if (sizeY<=0) return;
	}

	if (putY+sizeY>screenSizeY)
	{
		sizeY = screenSizeY - putY;
		if (sizeY<=0) return;
	}


	int divY = picSizeY;
	if (divY<1) divY = 1;







	int j;
	for (j=0;j<screenSizeY;j++)
	{
		transWork[j] = 0;
	}

	for (j=0;j<sizeY;j++)
	{
	//	int yy = putY + deltaY + j;
		int yy = j - deltaY;

		int tr = up + ((down - up) * yy) / divY;
		if (tr<0) tr = 0;
		if (tr>255) tr = 255;
		unsigned int d0 = (unsigned int)tr;

		unsigned int dd = (d0<<24) | (d0<<16) | (d0<<8) | d0;
		transWork[putY+j] = dd;
	}

	SetWorkV(transWork,screenSizeY);

	CMyTexture* lpTexture = (CMyTexture*)(lpPic->GetTexture());
	if (lpTexture == NULL) return;


	SetTexture(lpTexture->GetTexture());
	SetTexture(GetVTexture(),1);

	POINT dstPoint;
	dstPoint.x = putX;
	dstPoint.y = putY;
	SIZE dstSize;
	dstSize.cx = sizeX;
	dstSize.cy = sizeY;
	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;

	Blt(dstPoint,dstSize,srcPoint);


	return;



}

#else
void CEffectCharaGhost::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int dv = lp->countMax;	//not use
	int c = lp->count;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;
	if (lpPic->Check256()) return;
	if (lpPic->CheckMaskExist() == FALSE) return;


	int upStart = lp->para[1];
	int upEnd = lp->para[2];
	int downStart = lp->para[3];
	int downEnd = lp->para[4];

	int speedType = lp->para[5];
	int subFrame = lp->para[6];

	int up = CCalcuSpeed::calcu(c,dv,upStart*256,upEnd*256,subFrame,speedType);
	int down = CCalcuSpeed::calcu(c,dv,downStart*256,downEnd*256,subFrame,speedType);

	up /= 100;
	down /= 100;

	SIZE sz = lpPic->GetPicSize();
	int picSizeX = sz.cx;
	int picSizeY = sz.cy;


	int* transWork = m_allEffect->GetTempWork();

	POINT pt = m_allEffect->GetDstPoint(layer);
	int putX = pt.x;
	int putY = pt.y;
	int srcX = 0;
	int srcY = 0;
	int sizeX = picSizeX;
	int sizeY = picSizeY;

	//genral clip
	if (putX>=screenSizeX) return;
	if (putY>=screenSizeY) return;
	if ((putX+sizeX) <= 0) return;
	if ((putY+sizeY) <= 0) return;


	//clip x
	if (putX<0)
	{
		srcX -= putX;
		sizeX += putX;
		putX = 0;
		if (sizeX<=0) return;
	}

	if (putX+sizeX>screenSizeX)
	{
		sizeX = screenSizeX - putX;
		if (sizeX<=0) return;
	}

	//clipY	
	int deltaY = 0;

	if (putY < 0)
	{
		srcY -= putY;
		sizeY += putY;
		deltaY = -putY;
		putY = 0;
		if (sizeY<=0) return;
	}

	if (putY+sizeY>screenSizeY)
	{
		sizeY = screenSizeY - putY;
		if (sizeY<=0) return;
	}


	int divY = picSizeY;
	if (divY<1) divY = 1;


	for (int j=0;j<sizeY;j++)
	{
		int yy = putY + deltaY + j;

		int tr = up + ((down - up) * yy) / divY;
		if (tr<0) tr = 0;
		if (tr>256) tr = 256;

		transWork[putY+j] = tr;
	}

	int* src = (int*)(lpPic->GetPictureBuffer());
	char* mask = lpPic->GetMaskPic();
	int lPitch = screenSizeX * sizeof(int);
	int srcPitch = picSizeX * sizeof(int);
	int maskPitch = picSizeX;

	int* dst = CMyGraphics::GetScreenBuffer();
	dst += putX;
	dst += putY * screenSizeX;

	src += srcX;
	src += srcY * picSizeX;

	mask += srcX;
	mask += srcY * picSizeX;

	int* transPtr = transWork;
	transPtr += putY;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		pxor mm0,mm0

		mov ebx,mask
		mov edx,transPtr
		mov esi,src
		mov edi,dst
		mov ecx,sizeY
LOOP1:
		push ebx
		push ecx
		push edx
		push esi
		push edi

		mov eax,[edx]
		movd mm7,eax

		mov ecx,sizeX
LOOP2:
		xor eax,eax
		mov al,[ebx]
		movd mm6,eax
		pmullw mm6,mm7
		mov eax,[esi]
		movd mm1,eax
		movd edx,mm6
		cmp edx,0ff00h
		jz NORMAL

		shr edx,8
		movd mm6,edx
		neg edx
		add edx,256
		movd mm5,edx

		mov eax,[edi]
		movd mm2,eax
		punpcklbw mm1,mm0
		punpcklbw mm2,mm0
		punpcklwd mm6,mm6
		punpckldq mm6,mm6

		punpcklwd mm5,mm5
		punpckldq mm5,mm5

		pmullw mm1,mm6
		pmullw mm2,mm5
		//stall
		psrlw mm1,8
		psrlw mm2,8
		paddw mm1,mm2
		packuswb mm1,mm1
		movd eax,mm1

NORMAL:
		mov [edi],eax

		add esi,4
		add edi,4
		inc ebx
		dec ecx
		jnz LOOP2

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		add edi,lPitch
		add esi,srcPitch
		add edx,4
		add ebx,maskPitch
		dec ecx
		jnz LOOP1


		emms
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax

	}
}
#endif

BOOL CEffectCharaGhost::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


/*_*/

