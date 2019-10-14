//
// effectSlash.cpp
//
#include "..\nyanEffectLib\includer.h"

#include "effectSlash.h"


CEffectSlash::CEffectSlash(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	m_work = new int[screenSizeX * 2 * 2 + 32];

#if defined _TINYAN3DLIB_
	SetTextureKosuu(1);
	Create("Slash");
#endif

}

CEffectSlash::~CEffectSlash()
{
	End();
}

void CEffectSlash::End(void)
{
	DELETEARRAY(m_work);
}


BOOL CEffectSlash::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[24];
	int k = paraKosuu;

	int i;
	for (i=0;i<6;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;	//frame



	if (paraKosuu<2) para[1] = 0;	//type (houkou)


	if (paraKosuu<3) para[2] = 0;	//speedType
	if (paraKosuu<4) para[3] = 0;	//subFrame




	if (paraKosuu<5) para[4] = 32;	//最大ぼかし
	if (paraKosuu<6) para[5] = para[4] + 4;	//最小はば

	if (para[4]>255) para[4] = 255;
	if (para[4]<1) para[4] = 1;

	if (para[5]<para[4]+4) para[5] = para[4]+4;


	lp->flag = TRUE;
	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_SLASH;
	lp->para[0] = para[0];	//???

	for (i=0;i<6;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectSlash::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectSlash::BeginPrint(LPVOID para,int layer)
{

}

void CEffectSlash::Init(LPVOID para,int layer)
{
}

void CEffectSlash::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectSlash::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	if (layer == -1) layer = 0;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int count = lp->count;
	int countMax = lp->countMax;

	int speedType = lp->para[2];
	int subFrame = lp->para[3];

	int ps = CCalcuSpeed::calcu(count,countMax,0,100,subFrame,speedType);

	if (ps<0) ps = 0;
	if (ps>100) ps = 100;

	int pic = lp->pic;
	if (pic == -1) return;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	if (lpPic->Check256()) return;
	RECT rc;
	lpPic->GetPicSize(&rc);
	if ((rc.right<screenSizeX) || (rc.bottom<screenSizeY)) return;

	int picSizeX = rc.right;
	int picSizeY = rc.bottom;

	int putX = lp->dst.left;
	int putY = lp->dst.top;

	int srcX = -putX;
	int srcY = -putY;

	if ((srcX<0) || (srcY<0)) return;
	if ((srcX+screenSizeX)>picSizeX) return;
	if ((srcY+screenSizeY)>picSizeY) return;

	int srclPitch = picSizeX * sizeof(int);
	int lPitch = screenSizeX * sizeof(int);

	int* src = lpPic->GetPictureBuffer();
	if (src == NULL) return;

#if defined _TINYAN3DLIB_
	src += 128 / sizeof(int);
#endif

	src += srcX;
	src += picSizeX * srcY;

	int* dst = CMyGraphics::GetScreenBuffer();

	int loopX = screenSizeX;
	int loopY = screenSizeY;


	int type = lp->para[1];

	int maxSpace = screenSizeY - lp->para[5];
	if ((type == 2) || (type == 3))
	{
		maxSpace = screenSizeX - lp->para[5];
	}

	if (maxSpace<0) maxSpace = 0;

	int space = (ps * maxSpace) / 100;

	if (space<0) space = 0;
	if (space>maxSpace) space = maxSpace;


#if defined _WIN64
	long long ptr = (long long)m_work;
#else
	int ptr = (int)m_work;
#endif
	ptr += 31;
	ptr &= ~31;
	void* alignedWork = (void*)ptr;


	int bokashiSize = (ps * lp->para[4]) / 100;

	if (bokashiSize<0) bokashiSize = 0;
	if (bokashiSize>256) bokashiSize = 256;

	if ((bokashiSize == 0) || (bokashiSize == 1))	//debug patch 2005-05-09
	{
		lpPic->Blt(putX,putY,0,0,picSizeX,picSizeY,FALSE);
		return;
	}

	int startY = 0;
	int endY = 0;

	int startX = 0;
	int endX = 0;

	if (type == 0)
	{
		startY = space;
		endY = screenSizeY-bokashiSize;
	}
	else if (type == 1)
	{
		startY = 0;
		endY = screenSizeY - space - bokashiSize;
	}
	else if (type == 2)
	{
		startX = space;
		endX = screenSizeX - bokashiSize;
	}
	else if (type == 3)
	{
		startX = 0;
		endX = screenSizeX - space - bokashiSize;
	}


	src += startY * picSizeX;
	src += startX;

	int deltaEDX = bokashiSize * picSizeX * sizeof(int);

//	int div65536 = 65536 / (bokashiSize*bokashiSize);
	int div65536 = 65536 / bokashiSize;
	if (div65536>=32768) div65536 = 32767;


	int maeY = startY;
	int nowY = startY;


	//横ルーチン
	if ((type == 2) || (type == 3))
	{
		deltaEDX = bokashiSize * sizeof(int);	//横

		//make X TABLE
		int* xptr = (int*)alignedWork;
		for (int i=0;i<screenSizeX;i++)
		{
			int xx = (endX - startX) * i;
			xx /= screenSizeX;
			xx += startX;

			*(xptr+i+1) = xx;
		}
		*xptr = *(xptr+1);
	}




//	int tableChangeFlag = 0;

	if ((lp->para[1] == 0) || (lp->para[1] == 1))
	{
#if defined _WIN64
#pragma message("ここにc++実装が必要にゃ " __FILE__)

#else

		__asm
		{
			push eax
			push ebx
			push ecx
			push edx
			push esi
			push edi


	//first make table
			pxor mm0,mm0

			mov edi,alignedWork;
			mov esi,src
			mov ecx,loopX
//			inc ecx
			shr ecx,1
LOOP0:
			push ecx
			push esi
			push edi

			pxor mm1,mm1
			pxor mm2,mm2

			mov edx,bokashiSize
LOOP01:
			movq mm5,[esi]
			add esi,srclPitch
			movq mm6,mm5
			punpcklbw mm5,mm0
			punpckhbw mm6,mm0

			paddw mm1,mm5
			paddw mm2,mm6

			dec edx
			jnz LOOP01

			movq [edi],mm1
			movq [edi+8],mm2

			pop edi
			pop esi
			pop ecx
			add esi,8
			add edi,8*2
			dec ecx
			jnz LOOP0

	//main

			mov eax,div65536
			movd mm7,eax
			punpcklwd mm7,mm7
			punpckldq mm7,mm7

			mov ecx,loopY
			mov ebx,src
			mov edi,dst
LOOP1:
			push ecx
			push ebx
			push edi
	//calcu nowY
			mov eax,ecx
			neg eax
			add eax,loopY
			mov edx,endY
			sub edx,startY
			imul edx
			mov esi,loopY
			idiv esi
			add eax,startY
			mov nowY,eax

			mov edx,0
			cmp eax,maeY
			jz SKIP1
			cmp ecx,1
			jz SKIP1
			mov edx,1
SKIP1:
			mov eax,edx

			mov esi,alignedWork
			mov edx,deltaEDX
			mov ecx,loopX
//			inc ecx
			shr ecx,1
LOOP2:
			movq mm1,[esi]
			movq mm2,[esi+8]

			movq mm3,mm1
			movq mm4,mm2

			psrlw mm3,1
			psrlw mm4,1

			pmulhw mm3,mm7
			pmulhw mm4,mm7

			psllw mm3,1
			psllw mm4,1

			packuswb mm3,mm4
//			psllb mm3,1

			movq [edi],mm3
			
			//calcu?
			or eax,eax
			jz SKIP2
	//change table
			movq mm5,[ebx]
			movq mm6,mm5
			punpcklbw mm5,mm0
			punpckhbw mm6,mm0
			psubw mm1,mm5
			psubw mm2,mm6

			movq mm5,[ebx + edx]
			movq mm6,mm5
			punpcklbw mm5,mm0
			punpckhbw mm6,mm0
			paddw mm1,mm5
			paddw mm2,mm6

			movq [esi],mm1
			movq [esi+8],mm2

SKIP2:
			add esi,8*2
			add ebx,8
			add edi,8
			dec ecx
			jnz LOOP2

			pop edi
			pop ebx
			pop ecx

			cmp ecx,1
			jz EXIT0

			mov eax,nowY
			cmp eax,maeY
			jz SKIP99
			mov maeY,eax
			add ebx,srclPitch
SKIP99:

			add edi,lPitch
			dec ecx
			jnz LOOP1
EXIT0:
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
	else	//よこ
	{
#if defined _WIN64
#pragma message("ここにc++実装が必要にゃ " __FILE__)

#else

		__asm
		{
			push eax
			push ebx
			push ecx
			push edx
			push esi
			push edi


			pxor mm0,mm0

			mov eax,div65536
			movd mm7,eax
			punpcklwd mm7,mm7
			punpckldq mm7,mm7

			mov ecx,loopY
			mov edi,dst
			mov esi,src
LOOPY0:
			push ecx
			push esi
			push edi


//calcu first
			push esi
			pxor mm1,mm1
			mov ecx,bokashiSize
LOOPY00:
			mov eax,[esi]
			movd mm5,eax
			punpcklbw mm5,mm0
			paddw mm1,mm5
			add esi,4
			dec ecx
			jnz LOOPY00
			pop esi

			mov ebx,alignedWork
			mov edx,deltaEDX
			mov ecx,loopX
LOOPY1:
			movq mm2,mm1
			psrlw mm2,1
			pmulhw mm2,mm7
			psllw mm2,1
			packuswb mm2,mm2
			movd eax,mm2
			mov [edi],eax

			cmp ecx,1
			jz SKIPY2
			
			//calcu?
			mov eax,[ebx]
			cmp eax,[ebx+4]
			jz SKIPY2

			mov eax,[esi]
			movd mm2,eax
			punpcklbw mm2,mm0
			psubw mm1,mm2

			mov eax,[esi+edx]
			movd mm2,eax
			punpcklbw mm2,mm0
			paddw mm1,mm2
			add esi,4

SKIPY2:
			add ebx,4
			add edi,4

			dec ecx
			jnz LOOPY1
//EXITY1:
			pop edi
			pop esi
			pop ecx
			add esi,srclPitch
			add edi,lPitch
			dec ecx
			jnz LOOPY0

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


#if defined _TINYAN3DLIB_
	CMyDirect3D::PutMemoryToMemoryTexture(dst);
	CMyDirect3D::PutMemoryTextureToBuffer();

	SetTexture(GetBufferTexture());
	POINT dstPoint;
	SIZE dstSize;
	POINT srcPoint;
	dstPoint.x = 0;
	dstPoint.y = 0;
	dstSize.cx = screenSizeX;
	dstSize.cy = screenSizeY;
	srcPoint.x = 0;
	srcPoint.y = 0;

	Blt(dstPoint,dstSize,srcPoint);
#endif
}


BOOL CEffectSlash::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}

/*_*/

