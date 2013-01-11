//
// effectBokashi.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectBokashi.h"


CEffectBokashi::CEffectBokashi(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	m_work = new int[screenSizeX*2 * 2+32];

#if defined _TINYAN3DLIB_
	SetTextureKosuu(1);
	Create("Bokashi");
#endif

}

CEffectBokashi::~CEffectBokashi()
{
	End();
}

void CEffectBokashi::End(void)
{
	DELETEARRAY(m_work);
}


BOOL CEffectBokashi::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
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
	if (paraKosuu<2) para[1] = 8;	//Å‘å‚Ú‚©‚µX
	if (para[1]<1) para[1] = 1;
	if (para[1]>256) para[1] = 256;
	if (paraKosuu<3) para[2] = 8;	//Y
	if (para[2]<1) para[2] = 1;
	if (para[2]>256) para[2] = 256;

	if (para[1] * para[2] > 256)
	{
		para[2] = 256 / para[1];
	}

	if (paraKosuu<4) para[3] = 100;
	if (para[3]<0) para[3] = 0;
	if (para[3]>100) para[3] = 100;

	if (paraKosuu<5) para[4] = para[3];
	if (para[4]<0) para[4] = 0;
	if (para[4]>100) para[4] = 100;

	if (paraKosuu<6) para[5] = 0;
	if (paraKosuu<7) para[6] = 0;
	if (para[6]<0) para[6] = 0;

	if (paraKosuu<8) para[7] = 0;





	lp->flag = TRUE;
	lp->command = EFFECT_BOKASHI;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectBokashi::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectBokashi::BeginPrint(LPVOID para,int layer)
{

}

void CEffectBokashi::Init(LPVOID para,int layer)
{
}

void CEffectBokashi::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectBokashi::Print(LPVOID lpEffect,int layer)
{
	if (layer == -1) layer = 0;

	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int dv = lp->countMax;
	int c = lp->count;

//	if (dv<1)
//	{
//		dv = 1;
//		c = 0;
//	}
//
//	if (c<0) c = 0;
//	if (c>dv) c = dv;

	int count = lp->count;
	int countMax = lp->countMax;
	int speedType = lp->para[5];
	int subFrame = lp->para[6];
	int startPercent = lp->para[4];
	int endPercent = lp->para[3];



	int ps = CCalcuSpeed::calcu(count,countMax,startPercent,endPercent,subFrame,speedType);


	int bokashiSizeX = (lp->para[1] * ps) / (100*1);
	int bokashiSizeY = (lp->para[2] * ps) / (100*1);
	

	if (lp->para[7])
	{
		if (bokashiSizeX > 1)
		{
			if ((bokashiSizeX & 1) == 0)
			{
				bokashiSizeX--;
			}
		}
		if (bokashiSizeY > 1)
		{
			if ((bokashiSizeY & 1) == 0)
			{
				bokashiSizeY--;
			}
		}
	}

	if (bokashiSizeX<1) bokashiSizeX = 1;
	if (bokashiSizeX>256) bokashiSizeX = 256;
	if (bokashiSizeY<1) bokashiSizeY = 1;
	if (bokashiSizeY>256) bokashiSizeY = 256;


	if (bokashiSizeX * bokashiSizeY > 256)
	{
		bokashiSizeY = 256 / bokashiSizeX;
	}


//char mes[256];
//sprintf(mes,"[%d %d]",bokashiSizeX,bokashiSizeY);
//OutputDebugString(mes);



//	int pic = lp->pic;


	CPicture* lpPic = m_allEffect->GetPicture(layer);	//debug 2005-05-08
	if (lpPic == NULL) return;

	if (lpPic->Check256()) return;

	POINT dstPoint = m_allEffect->GetDstPoint(layer);
	SIZE sz = m_allEffect->GetDstSize(layer);

	
//	int putX = m_effect->m_effect[layer].dst.left;
//	int putY = m_effect->m_effect[layer].dst.top;
////	int srcX = m_effect->m_effect[layer].src.left;
//	//int srcY = m_effect->m_effect[layer].src.top;
//	int sizeX = m_effect->m_effect[layer].dst.right;
//	int sizeY = m_effect->m_effect[layer].dst.bottom;

	int putX = dstPoint.x;
	int putY = dstPoint.y;

	int sizeX = sz.cx;
	int sizeY = sz.cy;

	int srcX = -putX;
	int srcY = -putY;

	if ((srcX<0) || (srcX+screenSizeX>sizeX) || (srcY<0) || (srcY+screenSizeY>sizeY)) return;

	if ((bokashiSizeX == 1) && (bokashiSizeY == 1))
	{
		lpPic->Blt(putX,putY,0,0,sizeX,sizeY,FALSE);
		return;
	}


	int loopY = screenSizeY;
	int loopX = screenSizeX;

	int lPitch = screenSizeX * sizeof(int);
	int srclPitch = sizeX * sizeof(int);

	long double mm1Buffer = 0.0;

	int startY = 0;
	int endY = screenSizeY - (bokashiSizeY-1);

//	int maeY = (c * (endY - startY)) / dv;
	int maeY = startY;



	int* src = (int*)lpPic->GetPictureBuffer();
	if (src == NULL) return;

#if defined _TINYAN3DLIB_
	src += 128 / sizeof(int);
#endif

	src += srcX;
	src += srcY * sizeX;

	int p = (int)m_work;
	p += 31;
	p &= ~31;
	int* alignedWork = (int*)p;
	int* xTable = alignedWork + screenSizeX * 2;

	int div65536 = (65536 * 1) / (bokashiSizeX * bokashiSizeY);
	if (div65536 >= 32768) div65536 = 32767;

	int startX = 0;
	int endX = screenSizeX - (bokashiSizeX - 1);

	for (int i=0;i<screenSizeX;i++)
	{
		*(xTable+i+1) = (i * (endX - startX)) / screenSizeX + startX;
	}
	*xTable = *(xTable+1);

	int deltaEDX = 8 * bokashiSizeX;
	int deltaGET = srclPitch * bokashiSizeY;


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
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6

//
// first calcu table
//
		mov edx,screenSizeX
		mov edi,alignedWork
//		mov ebx,xTable
		mov esi,src
LOOP00:
		push esi

		mov ecx,bokashiSizeY
		pxor mm2,mm2
LOOP001:
		mov eax,[esi]
		movd mm3,eax
		add esi,srclPitch
		punpcklbw mm3,mm0
		paddw mm2,mm3
		dec ecx
		jnz LOOP001
		
		movq [edi],mm2

		pop esi
		add esi,4
//		add ebx,4
		add edi,8
		dec edx
		jnz LOOP00


//calcu start block
		pxor mm1,mm1
		mov esi,alignedWork
		mov ecx,bokashiSizeX
LOOP0:
		paddw mm1,[esi]
		add esi,8
		dec ecx
		jnz LOOP0


		mov ecx,loopY
		mov edi,dst
		mov esi,src
LOOP1:
		push ecx
		push esi
		push edi


		movq mm1Buffer,mm1

		mov ecx,loopX
		mov esi,alignedWork
		mov ebx,xTable

		add ebx,4

LOOP2:
		movq mm2,mm1
		psrlw mm2,1
		pmulhw mm2,mm6
		psllw mm2,1
		packuswb mm2,mm0
		movd eax,mm2
		mov [edi],eax
		add edi,4
		cmp ecx,1
		jz SKIP1

		mov eax,[ebx]
		add ebx,4
		cmp eax,[ebx]
		jz SKIP1
//change
		mov edx,deltaEDX
		psubw mm1,[esi]
		paddw mm1,[esi+edx]
		add esi,8
SKIP1:
		dec ecx
		jnz LOOP2

		pop edi
		pop esi
		pop ecx
		movq mm1,mm1Buffer
		add edi,lPitch
		cmp ecx,1
		jz EXIT1
//
//	next??
//
		mov eax,ecx
		dec eax
		neg eax
		add eax,loopY
//		mov edx,bokashiSize
		mov edx,endY
		sub edx,startY
		imul edx
		mov ebx,loopY
		idiv ebx
		add eax,startY
		cmp eax,maeY
		mov maeY,eax
		jz SKIP2
//
		push ecx
		push esi
		mov ebx,alignedWork
		mov edx,deltaGET
		mov ecx,loopX
LOOP30:
		movq mm3,[ebx]

		mov eax,[esi]
		movd mm2,eax
		punpcklbw mm2,mm0
		psubw mm3,mm2

		mov eax,[esi+edx]
		movd mm2,eax
		punpcklbw mm2,mm0
		paddw mm3,mm2

		movq [ebx],mm3

		add ebx,8
		add esi,4
		dec ecx
		jnz LOOP30
		pop esi
		pop ecx


		push ecx
		push esi
		mov ecx,bokashiSizeX
LOOP31:
		mov eax,[esi]
		movd mm5,eax
		punpcklbw mm5,mm0
		psubw mm1,mm5
		add esi,4
		dec ecx
		jnz LOOP31
		pop esi
		pop ecx

		mov eax,srclPitch
		mov edx,bokashiSizeY
		mul edx
		push ecx
		push esi
		add esi,eax
		mov ecx,bokashiSizeX
LOOP32:
		mov eax,[esi]
		movd mm5,eax
		punpcklbw mm5,mm0
		paddw mm1,mm5
		add esi,4
		dec ecx
		jnz LOOP32
		pop esi
		pop ecx


		add esi,srclPitch
SKIP2:
		dec ecx
		jnz LOOP1
EXIT1:
		emms
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
#if defined _TINYAN3DLIB_
	CMyDirect3D::PutMemoryToMemoryTexture(dst);
	CMyDirect3D::PutMemoryTextureToBuffer();

	SetTexture(GetBufferTexture());
	POINT dstPoint2;
	SIZE dstSize;
	POINT srcPoint;
	dstPoint2.x = 0;
	dstPoint2.y = 0;
	dstSize.cx = screenSizeX;
	dstSize.cy = screenSizeY;
	srcPoint.x = 0;
	srcPoint.y = 0;

	Blt(dstPoint2,dstSize,srcPoint);
#endif

}



BOOL CEffectBokashi::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}
