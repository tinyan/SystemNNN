//
// effectSpeedLine.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectSpeedLine.h"

#define LINE_KOSUU_MAX 100


CEffectSpeedLine::CEffectSpeedLine(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	m_work = NULL;
#if defined _TINYAN3DLIB_
	Create("SpeedLine");
#endif
}


CEffectSpeedLine::~CEffectSpeedLine()
{
	End();
}

void CEffectSpeedLine::End(void)
{
	DELETEARRAY(m_work);
}

BOOL CEffectSpeedLine::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int para[16];
	int k = paraKosuu;
	if (k>12) k = 12;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 10;	//kosuu
	if (paraKosuu<3) para[2] = 100;	//ながさ
	if (paraKosuu<4) para[3] = 3;	//はば
	if (paraKosuu<5) para[4] = 30;	//speed
	if (paraKosuu<6) para[5] = 255;	//r
	if (paraKosuu<7) para[6] = 3;	//g
	if (paraKosuu<8) para[7] = 3;	//b
	
	if (paraKosuu<9) para[8] = 0;
	if (paraKosuu<10) para[9] = 0;
	if (paraKosuu<11) para[10] = screenSizeX;
	if (paraKosuu<12) para[11] = screenSizeY;

	if (para[2]<81) para[2] = 81;

	if (para[8]<0) para[8] = 0;
	if (para[8]>=screenSizeX-1) para[8] = screenSizeX-1;
	if (para[9]<0) para[9] = 0;
	if (para[9]>=screenSizeY-1) para[9] = screenSizeY-1;

	if ((para[8] + para[10]) > screenSizeX) para[10] = screenSizeX - para[8];
	if ((para[9] + para[11]) > screenSizeY) para[11] = screenSizeY - para[9];

	if (para[11]<3)
	{
		para[9] -= 2;
		para[11] = 3;
		if (para[9]<0)
		{
			para[9] += 2;
		}
	}

//	m_r = para[0];
//	m_g = para[1];
//	m_b = para[2];


	lp->flag = TRUE;
	for (i=0;i<12;i++)
	{
		lp->para[i] = para[i];
	}

	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_SPEEDLINE;

	ReCreateBuffer();
	InitParameter(lpEffect,layer);

	return TRUE;
}


BOOL CEffectSpeedLine::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectSpeedLine::BeginPrint(LPVOID para,int layer)
{

}

void CEffectSpeedLine::Init(LPVOID para,int layer)
{
}

void CEffectSpeedLine::Calcu(LPVOID lpEffect,int layer)
{
	ReCreateBuffer();
	EFFECT* lp = (EFFECT*)lpEffect;
	int lineKosuu = lp->para[1];
	int spd = lp->para[4];
	int len = lp->para[2];
	int leftLimit = lp->para[8] - (len*125)/100;
	int rightLimit = lp->para[8] + lp->para[10];

	for (int i=0;i<lineKosuu;i++)
	{
		int x = m_work[i*7] + m_work[i*7+2];
//		m_work[i*6+1] = m_work[i*6+3];			y (dy==0)
		m_work[i*7] = x;
		if (spd>0)
		{
			if (x>rightLimit)
			{
				SetNewLine(lpEffect,i,FALSE,layer);
			}
		}
		else
		{
			if (x<leftLimit)
			{
				SetNewLine(lpEffect,i,FALSE,layer);
			}
		}
	}
}


void CEffectSpeedLine::Print(LPVOID lpEffect,int layer)
{
	ReCreateBuffer();

	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int r = lp->para[5] & 0xff;
	int g = lp->para[6] & 0xff;
	int b = lp->para[7] & 0xff;

	int col = (r << 16) | (g << 8) | b;
	int kosuu = lp->para[1];
	int* workPtr = m_work;

	if (kosuu<1) return;

	int leftLimit = lp->para[8];
	int rightLimit = lp->para[8] + lp->para[10];

	int lPitch = screenSizeX * sizeof(int);

#if defined _TINYAN3DLIB_
	if (CheckEffectError()) return;

	POINT dstPoint[2];
	float color[8];


	float fr = (float)r;
	fr /= 255.0f;
	float fg = (float)g;
	fg /= 255.0f;
	float fb = (float)b;
	fb /= 255.0f;

	color[0] = fr;
	color[1] = fg;
	color[2] = fb;
	color[3] = 1.0f;
	color[4] = fr;
	color[5] = fg;
	color[6] = fb;
	color[7] = 1.0f;





	int shader = 0;

	if (CheckEffectError()) return;
	LPD3DXEFFECT effect = m_d3dxEffect;
	if (effect == NULL) return;

	SetAllColor();
	SetAllPercent();
	SetAllConst();
	SetAllTexture();

	if (m_hTechnique[shader] == NULL)
	{
		OutputDebugString("[no tec]");
	}

	HRESULT hr = effect->SetTechnique(m_hTechnique[shader]);
	if (FAILED(hr))
	{
///		DXTRACE_ERR("settech",hr);
	}

	UINT passKosuu0 = 0;
	hr = effect->Begin(&passKosuu0,0);
	int passKosuu = passKosuu0;

	effect->BeginPass(0);

	int ln = lp->para[2];

	for (int i=0;i<kosuu;i++)
	{
		int x = m_work[i*7+0];
		int y = m_work[i*7+1];

		color[3] = 1.0f;
		color[7] = 1.0f;
		dstPoint[0].x = x-80;
		dstPoint[0].y = y;
		dstPoint[1].x = x-16;
		dstPoint[1].y = y;
		DrawColorLine(dstPoint,color);

		color[3] = 1.0f;
		color[7] = 0.0f;
		dstPoint[0].x = x-16;
		dstPoint[0].y = y;
		dstPoint[1].x = x-80+ln-16;
		dstPoint[1].y = y;
		DrawColorLine(dstPoint,color);

		color[3] = 1.0f;
		color[7] = 1.0f;
		dstPoint[0].x = x-80;
		dstPoint[0].y = y+1;
		dstPoint[1].x = x;
		dstPoint[1].y = y+1;
		DrawColorLine(dstPoint,color);

		color[3] = 1.0f;
		color[7] = 0.0f;
		dstPoint[0].x = x;
		dstPoint[0].y = y+1;
		dstPoint[1].x = x-80+ln;
		dstPoint[1].y = y+1;
		DrawColorLine(dstPoint,color);


		color[3] = 1.0f;
		color[7] = 1.0f;
		dstPoint[0].x = x-80;
		dstPoint[0].y = y+2;
		dstPoint[1].x = x-16;
		dstPoint[1].y = y+2;
		DrawColorLine(dstPoint,color);

		color[3] = 1.0f;
		color[7] = 0.0f;
		dstPoint[0].x = x-16;
		dstPoint[0].y = y+2;
		dstPoint[1].x = x-80+ln-16;
		dstPoint[1].y = y+2;
		DrawColorLine(dstPoint,color);

	}

	effect->EndPass();
	effect->End();







#else

#if defined _WIN64
#pragma message("ここにc++実装が必要にゃ " __FILE__)

#else

	__asm
	{
		push eax
		push ecx
		push edi
	
		pxor mm0,mm0

		mov eax,col
		movd mm1,eax
		punpcklbw mm1,mm0

		mov eax,4
		movd mm7,eax
		punpcklwd mm7,mm7
		punpckldq mm7,mm7

		mov ebx,workPtr
		mov ecx,kosuu
		cld
LOOP1:
		push ebx
		push ecx

		mov eax,[ebx+4]
		mov edx,lPitch
		mul edx
		add eax,dst
		mov esi,eax


		mov edx,[ebx]
		shl edx,2
		add eax,edx
		mov edi,eax


//完全クリップ
		mov edx,[ebx]
		cmp edx,rightLimit
		jns SKIP99

		mov ecx,[ebx+4*4]
		mov eax,edx
		add eax,ecx
		cmp eax,leftLimit
		js SKIP99

		mov eax,[ebx+4*6]
		or eax,eax
		jz SKIP1



		sub ecx,80

		mov eax,edx
		add eax,ecx
		cmp eax,leftLimit
		js NEXT1

		cmp edx,leftLimit
		jns OK1

		mov eax,leftLimit
		sub eax,edx

		sub ecx,eax
		cmp ecx,1
		js NEXT1

		shl eax,2
		add edi,eax
		mov edx,leftLimit
OK1:
		mov eax,edx
		add eax,ecx
		cmp eax,rightLimit
		js OK2
		sub eax,rightLimit
		sub ecx,eax
		cmp ecx,1
		js NEXT1
OK2:
		mov eax,col
		rep stosd
NEXT1:
		mov edx,[ebx]
		add edx,[ebx+4*4]
		sub edx,80
		mov ecx,64
		mov edi,esi
		mov eax,edx
		shl eax,2
		add edi,eax

		cmp edx,rightLimit
		jns SKIP1

		mov eax,edx
		add eax,ecx
		cmp eax,leftLimit
		js SKIP1

		mov eax,00ff00ffh
		movd mm4,eax
		punpckldq mm4,mm4

		cmp edx,leftLimit
		jns OK3

		mov eax,leftLimit
		sub eax,edx

		sub ecx,eax
		cmp ecx,1
		js SKIP1

		shl eax,2
		add edi,eax
		neg eax
		add eax,255
		movd mm4,eax
		punpcklwd mm4,mm4
		punpckldq mm4,mm4

		mov edx,leftLimit
OK3:
		mov eax,edx
		add eax,ecx
		cmp eax,rightLimit
		js OK4
		sub eax,rightLimit
		sub ecx,eax
		cmp ecx,1
		js SKIP1
OK4:
		mov eax,255
		movd mm5,eax
		punpcklwd mm5,mm5
		punpckldq mm5,mm5
		psubusw mm5,mm4
LOOP2:
		movq mm2,mm1
		pmullw mm2,mm4
		mov eax,[edi]
		movd mm3,eax
		punpcklbw mm3,mm0
		pmullw mm3,mm5
		paddw mm2,mm3
		psrlw mm2,8
		packuswb mm2,mm0
		movd eax,mm2
		mov [edi],eax


		psubusb mm4,mm7
		paddusb mm5,mm7
		add edi,4
		dec ecx
		jnz LOOP2

SKIP1:



		add esi,lPitch
		mov edi,esi

		mov edx,[ebx]
		shl edx,2
		add edi,edx
//完全クリップ
		mov edx,[ebx]
		mov ecx,[ebx+4*4]

		sub ecx,64

		mov eax,edx
		add eax,ecx
		cmp eax,leftLimit
		js NEXT1B

		cmp edx,leftLimit
		jns OK1B

		mov eax,leftLimit
		sub eax,edx

		sub ecx,eax
		cmp ecx,1
		js NEXT1B

		shl eax,2
		add edi,eax
		mov edx,leftLimit
OK1B:
		mov eax,edx
		add eax,ecx
		cmp eax,rightLimit
		js OK2B
		sub eax,rightLimit
		sub ecx,eax
		cmp ecx,1
		js NEXT1B
OK2B:
		mov eax,col
		rep stosd
NEXT1B:
		mov edx,[ebx]
		add edx,[ebx+4*4]
		sub edx,64
		mov ecx,64
		mov edi,esi
		mov eax,edx
		shl eax,2
		add edi,eax

		cmp edx,rightLimit
		jns SKIP1B

		mov eax,edx
		add eax,ecx
		cmp eax,leftLimit
		js SKIP1B

		mov eax,00ff00ffh
		movd mm4,eax
		punpckldq mm4,mm4

		cmp edx,leftLimit
		jns OK3B

		mov eax,leftLimit
		sub eax,edx

		sub ecx,eax
		cmp ecx,1
		js SKIP1B

		shl eax,2
		add edi,eax
		neg eax
		add eax,255
		movd mm4,eax
		punpcklwd mm4,mm4
		punpckldq mm4,mm4

		mov edx,leftLimit
OK3B:
		mov eax,edx
		add eax,ecx
		cmp eax,rightLimit
		js OK4B
		sub eax,rightLimit
		sub ecx,eax
		cmp ecx,1
		js SKIP1B
OK4B:
		mov eax,255
		movd mm5,eax
		punpcklwd mm5,mm5
		punpckldq mm5,mm5
		psubusw mm5,mm4
LOOP2B:
		movq mm2,mm1
		pmullw mm2,mm4
		mov eax,[edi]
		movd mm3,eax
		punpcklbw mm3,mm0
		pmullw mm3,mm5
		paddw mm2,mm3
		psrlw mm2,8
		packuswb mm2,mm0
		movd eax,mm2
		mov [edi],eax


		psubusb mm4,mm7
		paddusb mm5,mm7
		add edi,4
		dec ecx
		jnz LOOP2B

SKIP1B:

		mov eax,[ebx+4*6]
		or eax,eax
		jz SKIP99

		add esi,lPitch
		mov edi,esi

		mov edx,[ebx]
		shl edx,2
		add edi,edx
//完全クリップ
		mov edx,[ebx]
		mov ecx,[ebx+4*4]

		sub ecx,64

		mov eax,edx
		add eax,ecx
		cmp eax,leftLimit
		js NEXT1C

		cmp edx,leftLimit
		jns OK1C

		mov eax,leftLimit
		sub eax,edx

		sub ecx,eax
		cmp ecx,1
		js NEXT1C

		shl eax,2
		add edi,eax
		mov edx,leftLimit
OK1C:
		mov eax,edx
		add eax,ecx
		cmp eax,rightLimit
		js OK2C
		sub eax,rightLimit
		sub ecx,eax
		cmp ecx,1
		js NEXT1C
OK2C:
		mov eax,col
		rep stosd
NEXT1C:
		mov edx,[ebx]
		add edx,[ebx+4*4]
		sub edx,80
		mov ecx,64
		mov edi,esi
		mov eax,edx
		shl eax,2
		add edi,eax

		cmp edx,rightLimit
		jns SKIP1C

		mov eax,edx
		add eax,ecx
		cmp eax,leftLimit
		js SKIP1C

		mov eax,00ff00ffh
		movd mm4,eax
		punpckldq mm4,mm4

		cmp edx,leftLimit
		jns OK3C

		mov eax,leftLimit
		sub eax,edx

		sub ecx,eax
		cmp ecx,1
		js SKIP1C

		shl eax,2
		add edi,eax
		neg eax
		add eax,255
		movd mm4,eax
		punpcklwd mm4,mm4
		punpckldq mm4,mm4

		mov edx,leftLimit
OK3C:
		mov eax,edx
		add eax,ecx
		cmp eax,rightLimit
		js OK4C
		sub eax,rightLimit
		sub ecx,eax
		cmp ecx,1
		js SKIP1C
OK4C:
		mov eax,255
		movd mm5,eax
		punpcklwd mm5,mm5
		punpckldq mm5,mm5
		psubusw mm5,mm4
LOOP2C:
		movq mm2,mm1
		pmullw mm2,mm4
		mov eax,[edi]
		movd mm3,eax
		punpcklbw mm3,mm0
		pmullw mm3,mm5
		paddw mm2,mm3
		psrlw mm2,8
		packuswb mm2,mm0
		movd eax,mm2
		mov [edi],eax


		psubusb mm4,mm7
		paddusb mm5,mm7
		add edi,4
		dec ecx
		jnz LOOP2C

SKIP1C:


SKIP99:
		pop ecx
		pop ebx
		add ebx,4*7
		dec ecx
		jnz LOOP1

		emms

		pop edi
		pop ecx
		pop eax
	}
#endif

#endif
}


BOOL CEffectSpeedLine::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectSpeedLine::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectSpeedLine::ReCreateBuffer(void)
{
	if (m_work == NULL)
	{
		m_work = new int [LINE_KOSUU_MAX * 7];
	}
}


void CEffectSpeedLine::InitParameter(LPVOID lpEffect, int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	int lineKosuu = lp->para[1];
	for (int i=0;i<lineKosuu;i++)
	{
		SetNewLine(lpEffect,i,TRUE,layer);
	}
}


void CEffectSpeedLine::SetNewLine(LPVOID lpEffect, int n, BOOL bInScreen, int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	int len = lp->para[2];
	int wide = lp->para[3];
	int speed = lp->para[4];
	int startX = lp->para[8];
	int startY = lp->para[9];
	int sizeX = lp->para[10];
	int sizeY = lp->para[11];

	int drx = sizeX + len * 2;
	int dry = sizeY - 2;
	
	//いらないはず
	if (drx<1) drx = 1;
	if (dry<1) dry = 1;


	int x,y;

	y = startY + (rand() % dry);

	if (bInScreen == FALSE)
	{
		if (speed<0)
		{
			x = startX + sizeX + (rand() % (len+1));
		}
		else
		{
			x = startX - len * 2 + (rand() % (len+1));
		}
	}
	else
	{
		x = startX - len + (rand() % drx);
	}



	m_work[n*7+0] = x;
	m_work[n*7+1] = y;

	int drs = speed / 4;
	if (drs<0) drs *= -1;
	if (drs<1) drs = 1;

	m_work[n*7+2] = (speed + (rand() % (drs*2)) - drs);
	m_work[n*7+3] = 0;

	int drl = len / 2;
	if (drl<1) drl = 1;
	m_work[n*7+4] = len + (rand() % drl);
	m_work[n*7+5] = wide;

	m_work[n*7+6] = rand() % 2;
}


