//
// EffectGradation.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "EffectGradation.h"


CEffectGradation::CEffectGradation(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

//	int sizeY = CMyGraphics::GetScreenSizeY();
//	m_delta = new int[sizeY*2];
#if defined _TINYAN3DLIB_
	SetTextureKosuu(1);
	Create("Gradation");
#endif
}

CEffectGradation::~CEffectGradation()
{
	End();
}

void CEffectGradation::End(void)
{
//	DELETEARRAY(m_delta);
}

BOOL CEffectGradation::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int para[18];
	int k = paraKosuu;
	if (k>18) k = 18;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu < 1) para[0] = 20;
	if (paraKosuu < 2) para[1] = 0;
	if (paraKosuu < 3) para[2] = 0;
	if (paraKosuu < 4) para[3] = 0;
	if (paraKosuu < 5) para[4] = 255;
	if (paraKosuu < 6) para[5] = 255;
	if (paraKosuu < 7) para[6] = 255;

	if (paraKosuu < 8) para[7] = 0;	//type
	if (paraKosuu < 9) para[8] = 0;	//subFrame

	if (paraKosuu < 10) para[9] = 0;
	if (paraKosuu < 11) para[10] = 0;
	if (paraKosuu < 12) para[11] = 0;
	if (paraKosuu < 13) para[12] = 0;
	if (paraKosuu < 14) para[13] = 0;
	if (paraKosuu < 15) para[14] = 0;

	if (paraKosuu<16) para[15] = 0;
	if (paraKosuu<17) para[16] = screenSizeY;

	if (para[15] < 0) para[15] = 0;
	if (para[15] >= screenSizeY) para[15] = screenSizeY-1;
	if (para[15] + para[16] > screenSizeY) para[16] = screenSizeY - para[15];


	lp->flag = TRUE;
	lp->command = EFFECT_GRADATION;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<18;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectGradation::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectGradation::BeginPrint(LPVOID para,int layer)
{

}

void CEffectGradation::Init(LPVOID para,int layer)
{
}

void CEffectGradation::Calcu(LPVOID lpEffect,int layer)
{
}


#if defined _TINYAN3DLIB_
void CEffectGradation::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;


	int sizeX = CMyGraphics::GetScreenSizeX();
	int sizeY = CMyGraphics::GetScreenSizeY();


	int count = lp->count;
	int countMax = lp->countMax;
	int type = lp->para[7];
	int subFrame = lp->para[8];

	int r11 = lp->para[1];
	int g11 = lp->para[2];
	int b11 = lp->para[3];

	int r21 = lp->para[4];
	int g21 = lp->para[5];
	int b21 = lp->para[6];

	int r10 = lp->para[9];
	int g10 = lp->para[10];
	int b10 = lp->para[11];

	int r20 = lp->para[12];
	int g20 = lp->para[13];
	int b20 = lp->para[14];


	int dr1 = CCalcuSpeed::calcu(count,countMax,r10,r11,subFrame,type);
	int dg1 = CCalcuSpeed::calcu(count,countMax,g10,g11,subFrame,type);
	int db1 = CCalcuSpeed::calcu(count,countMax,b10,b11,subFrame,type);

	int dr2 = CCalcuSpeed::calcu(count,countMax,r20,r21,subFrame,type);
	int dg2 = CCalcuSpeed::calcu(count,countMax,g20,g21,subFrame,type);
	int db2 = CCalcuSpeed::calcu(count,countMax,b20,b21,subFrame,type);

	float vertexColor[12];

	vertexColor[0] = ((float)(dr1+256))/512.0f;
	vertexColor[1] = ((float)(dg1+256))/512.0f;
	vertexColor[2] = ((float)(db1+256))/512.0f;
//	vertexColor[3] = 1.0f;
	vertexColor[3] = ((float)(dr2+256))/512.0f;
	vertexColor[4] = ((float)(dg2+256))/512.0f;
	vertexColor[5] = ((float)(db2+256))/512.0f;
//	vertexColor[7] = 1.0f;
	int i;
	for (i=0;i<6;i++)
	{
		vertexColor[i+6] = vertexColor[i];
	}


	ExchangeScreenAndBuffer();
	SetTexture(GetBufferTexture());


	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	POINT dstPoint;
	dstPoint.x = 0;
	dstPoint.y = 0;
	SIZE dstSize;
	dstSize.cx = screenSizeX;
	dstSize.cy = screenSizeY;
	POINT srcPoint;
	srcPoint.x = 0;
	srcPoint.y = 0;


	GouradBlt(dstPoint,dstSize,srcPoint,vertexColor,NULL);

	return;
}
#else

void CEffectGradation::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;


	int sizeX = CMyGraphics::GetScreenSizeX();
	int sizeY = CMyGraphics::GetScreenSizeY();


	int count = lp->count;
	int countMax = lp->countMax;
	int type = lp->para[7];
	int subFrame = lp->para[8];

	int r11 = lp->para[1];
	int g11 = lp->para[2];
	int b11 = lp->para[3];

	int r21 = lp->para[4];
	int g21 = lp->para[5];
	int b21 = lp->para[6];

	int r10 = lp->para[9];
	int g10 = lp->para[10];
	int b10 = lp->para[11];

	int r20 = lp->para[12];
	int g20 = lp->para[13];
	int b20 = lp->para[14];


	int dr1 = CCalcuSpeed::calcu(count,countMax,r10,r11,subFrame,type);
	int dg1 = CCalcuSpeed::calcu(count,countMax,g10,g11,subFrame,type);
	int db1 = CCalcuSpeed::calcu(count,countMax,b10,b11,subFrame,type);

	int dr2 = CCalcuSpeed::calcu(count,countMax,r20,r21,subFrame,type);
	int dg2 = CCalcuSpeed::calcu(count,countMax,g20,g21,subFrame,type);
	int db2 = CCalcuSpeed::calcu(count,countMax,b20,b21,subFrame,type);

	int* delta = m_allEffect->GetTempWork();

	int dr = dr2 - dr1;
	int dg = dg2 - dg1;
	int db = db2 - db1;


	int startY = lp->para[15];
	int printSizeY = lp->para[16];

	for (int i=0;i<printSizeY;i++)
	{
		int rr = dr1 + ((dr * i) / printSizeY);
		int gg = dg1 + ((dg * i) / printSizeY);
		int bb = db1 + ((db * i) / printSizeY);

		rr += 256;
		gg += 256;
		bb += 256;

		delta[i*2] = (bb & 0xffff) | ((gg<<16) & 0xffff0000);
		delta[i*2+1] = (rr & 0xffff);
	}


	int* deltaPtr = delta;

	int lPitch = sizeX*4;

	dst += startY * sizeX;

	int sizeXdiv4 = sizeX / 4;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		mov edi,dst
		mov ebx,deltaPtr
		mov ecx,printSizeY
		pxor mm0,mm0

		mov eax,256
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6

LOOP1:
		push ecx
		push edi

		movq mm7,[ebx]


		mov ecx,sizeXdiv4

LOOP2:
		movq mm1,[edi]
		movq mm2,mm1
		
		movq mm3,[edi+8]
		movq mm4,mm3

		punpcklbw mm1,mm0
		punpckhbw mm2,mm0
		punpcklbw mm3,mm0
		punpckhbw mm4,mm0

		paddw mm1,mm7
		paddw mm2,mm7
		paddw mm3,mm7
		paddw mm4,mm7

		psubusw mm1,mm6
		psubusw mm2,mm6
		psubusw mm3,mm6
		psubusw mm4,mm6

		packuswb mm1,mm2
		packuswb mm3,mm4

		movq [edi],mm1
		movq [edi+8],mm3

		add edi,16
		dec ecx
		jnz LOOP2

		pop edi
		pop ecx
		add edi,lPitch
		add ebx,4*2
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



