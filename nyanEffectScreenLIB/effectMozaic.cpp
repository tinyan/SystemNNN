//
// effectmozaic.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectmozaic.h"


CEffectMozaic::CEffectMozaic(CAllEffect* lpAll) : CCommonEffect(lpAll,2)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(1,0);
	SetTextureKosuu(1,1);
	SetConstKosuu(2,1);
	Create("Mozaic",0);
	Create("MozaicPart2",1);
#endif
}


CEffectMozaic::~CEffectMozaic()
{
	End();
}

void CEffectMozaic::End(void)
{
}

BOOL CEffectMozaic::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int para[16];
	int k = paraKosuu;
	if (k>7) k = 7;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 10000;
	lp->flag = TRUE;
	lp->command = EFFECT_MOZAIC;
	lp->count = 0;
	lp->countMax = para[0];

	if (paraKosuu<2) para[1] = 16;
	if (paraKosuu<3) para[2] = 16;
	if (paraKosuu<7)
	{
		para[3] = 0;
		para[4] = 0;
		para[5] = screenSizeX;
		para[6] = screenSizeY;
	}

	////////////////////////
//		para[3] = 0;
//		para[4] = 0;
//		para[5] = screenSizeX;
//		para[6] = screenSizeY;

	for (i=0;i<7;i++)
	{
		lp->para[i] = para[i];
	}
	return TRUE;
}


BOOL CEffectMozaic::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectMozaic::BeginPrint(LPVOID para,int layer)
{

}

void CEffectMozaic::Init(LPVOID para,int layer)
{
}

void CEffectMozaic::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectMozaic::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int sizeX = lp->para[1];
	int sizeY = lp->para[2];
	int startX = lp->para[3];
	int startY = lp->para[4];
	int endX = startX + lp->para[5];
	int endY = startY + lp->para[6];

	PrintMozaicMain(startX,startY,endX,endY,sizeX,sizeY);
}


void CEffectMozaic::PrintMozaicMain(int sx, int sy, int ex, int ey,int sizeX,int sizeY)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int startX = sx;
	int startY = sy;
	int endX = ex;
	int endY = ey;


	if (sizeX<1) sizeX = 1;
	if (sizeY<1) sizeY = 1;

	if ((sizeX == 1) && (sizeY == 1)) return;

//	int startX = m_effect[n].para[3];
//	int startY = m_effect[n].para[4];
//	int endX = m_effect[n].para[5];
//	int endY = m_effect[n].para[6];

	if (startX<0) startX = 0;
	if (startY<0) startY = 0;
	if (endX<0) endX = 0;
	if (endY<0) endY = 0;
	if (startX>screenSizeX) startX = screenSizeX;
	if (startY>screenSizeY) startY = screenSizeY;
	if (endX>screenSizeX) endX = screenSizeX;
	if (endY>screenSizeY) endY = screenSizeY;

	if (startX>=endX) return;
	if (startY>=endY) return;

	int loopX = (endX - startX) / sizeX;
	int loopY = (endY - startY) / sizeY;

	if ((startX + loopX * sizeX) > screenSizeX) loopX--;
	if ((startY + loopY * sizeY) > screenSizeY) loopY--;

	if (loopX<=0) return;
	if (loopY<=0) return;

#if defined _TINYAN3DLIB_
	if (CheckEffectError(0)) return;
	CopyScreenToBuffer();


	int dx = rand() % sizeX;
	int dy = rand() % sizeY;

	int psizeX = screenSizeX / sizeX;
	int psizeY = screenSizeY / sizeY;

	POINT dstPoint;
	POINT srcPoint;
	SIZE dstSize;
	dstSize.cx = psizeX;
	dstSize.cy = psizeY;
	srcPoint.x = dx;
	srcPoint.y = dy;
	dstPoint.x = 0;
	dstPoint.y = 0;
	SIZE srcSize;
	srcSize.cx = screenSizeX - dx;
	srcSize.cy = screenSizeY - dy;
	SIZE srcPicSize;
	srcPicSize.cx = screenSizeX;
	srcPicSize.cy = screenSizeY;

	SetTexture(GetBufferTexture(),0,0);
	StretchBlt(&dstPoint,&dstSize,&srcPoint,&srcSize,&srcPicSize);


	ExchangeScreenAndBuffer();
//	CopyScreenToBuffer();

	//part-2

	if (CheckEffectError(1)) return;

	SetTexture(GetBufferTexture(),0,1);
	dstPoint.x = startX;
	dstPoint.y = startY;
	dstSize.cx = endX-startX;
	dstSize.cy = endY-startY;
	srcPoint.x = 0;
	srcPoint.y = 0;


	float fSizeX = ((float)psizeX) / ((float)screenSizeX);
	float fSizeY = ((float)psizeY) / ((float)screenSizeY);
	SetConst(fSizeX,0,1);
	SetConst(fSizeY,1,1);

	Blt(dstPoint,dstSize,srcPoint,1);
#else
	int rndData[101*2];

	int* dst = CMyGraphics::GetScreenBuffer();
	dst += startX;
	dst += startY * screenSizeX;

	int lPitch = screenSizeX*4;
	int lPitch2 = screenSizeX*4 * sizeY;

	int nextX = 4 * sizeX;


	for (int i=0;i<101;i++)
	{
		int r = rand() % 16384;
		int dx = (r & 0xff) % sizeX;
		int dy = (r >> 8) % sizeY;

		rndData[i] = dx * 4 + dy * 4 * screenSizeX;
	}

	int* rndTable = rndData;

#if defined _WIN64
#pragma message("‚±‚±‚Éc++ŽÀ‘•‚ª•K—v‚É‚á " __FILE__)

#else

	__asm
	{
		__asm
		{
			push eax
			push ebx
			push ecx
			push edx
			push esi
			push edi

			mov edi,dst
			mov ecx,loopY
			mov ebx,0
LOOP1:
			push ecx
			push edi

			mov ecx,loopX
LOOP2:
			push ecx
			push edi


			mov eax,rndTable
			add eax,ebx
			mov esi,[eax]
			add esi,edi
			mov eax,[esi]

			cld
			mov edx,sizeY
LOOP3:
			push edi
			mov ecx,sizeX
			rep stosd
			pop edi
			add edi,lPitch
			dec edx
			jnz LOOP3

			add ebx,4
			cmp ebx,101*4
			jb SKIP1
			mov ebx,0
SKIP1:

			pop edi
			pop ecx
			add edi,nextX
			dec ecx
			jnz LOOP2

			pop edi
			pop ecx
			add edi,lPitch2
			dec ecx
			jnz LOOP1


			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax
			emms
		}
	}

#endif


#endif

}
