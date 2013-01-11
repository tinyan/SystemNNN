//
// effectkagerou.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectkagerou.h"


CEffectKagerou::CEffectKagerou(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetPercentKosuu(1);
	SetTextureKosuu(1);
	Create("Kagerou");
#endif
}

CEffectKagerou::~CEffectKagerou()
{
	End();
}

void CEffectKagerou::End(void)
{
}

BOOL CEffectKagerou::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int para[24];
	int k = paraKosuu;
	if (k>17) k = 17;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[1] = 9999;
	if (paraKosuu<2) para[1] = 0;
	if (para[1]<0) para[1] = 0;
	if (para[1]>=screenSizeY) para[1] = screenSizeY-1;

	if (paraKosuu<3) para[2] = screenSizeY;
	if (para[2]<0) para[2] = 0;
	if (para[2]>=screenSizeY) para[2] = screenSizeY;

	if ((para[1]+para[2]) > screenSizeY) para[2] = screenSizeY - para[1];


	if (paraKosuu<4) para[3] = 0;	//開始ウエイト

	if (paraKosuu<5) para[4] = 100;
	if (paraKosuu<6) para[5] = 100;
	if (paraKosuu<7) para[6] = 100;

	if (paraKosuu<8) para[7] = 9;
	if (paraKosuu<9) para[8] = 7;
	if (paraKosuu<10) para[9] = 11;

	if (paraKosuu<11) para[10] = 4;
	if (paraKosuu<12) para[11] = 17;
	if (paraKosuu<13) para[12] = -23;

	if (paraKosuu<14) para[13] = 6;
	if (paraKosuu<15) para[14] = 2;
	if (paraKosuu<16) para[15] = -5;

//	if (paraKosuu<16) para[15] = 0;

	lp->flag = TRUE;
	lp->command = EFFECT_KAGEROU;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<17;i++)
	{
		lp->para[i] = para[i];
	}
	return TRUE;
}


BOOL CEffectKagerou::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectKagerou::BeginPrint(LPVOID para,int layer)
{

}

void CEffectKagerou::Init(LPVOID para,int layer)
{
}

void CEffectKagerou::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	//int dv = lp->para[15];
	
	int dv = 9000;

	int startWait = lp->para[3];

	if (dv>0)
	{
		int c = lp->count;
		if (c>=startWait)
		{
			c -= startWait;
			c %= dv;
			c += startWait;
			lp->count = c;
		}
	}
}


#if defined _TINYAN3DLIB_
void CEffectKagerou::Print(LPVOID lpEffect,int layer)
{
	int shader = 0;

	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


//	int kagerou[MAXSCREENSIZEY];
//	int* kagerou = CEffectSimpleWipe::m_shapeWork;
	int* kagerou = m_allEffect->GetTempWork();



	int c = lp->count;

	int startWait = lp->para[3];
	double totalMulti = 1.0;

	if (startWait > 0)
	{
		if (c<startWait)
		{
			totalMulti = (double)c;
			totalMulti /= (double)startWait;
		}
	}

	double h1 = (double)(lp->para[7]);
	double h2 = (double)(lp->para[10]);
	double h3 = (double)(lp->para[13]);

	double w1 = (double)(lp->para[8]);
	double w2 = (double)(lp->para[11]);
	double w3 = (double)(lp->para[14]);

	double sp1 = (double)(lp->para[9]);
	double sp2 = (double)(lp->para[12]);
	double sp3 = (double)(lp->para[15]);

	double mulH = (double)(lp->para[4]);
	double mulW = (double)(lp->para[5]);
	double mulS = (double)(lp->para[6]);

	int startY = lp->para[1];
	int lenY = lp->para[2];

	if (startY<0) startY = 0;
	if (startY>=screenSizeY-1) startY = screenSizeY-1;

	if (lenY<1) lenY = 1;
	if (lenY>screenSizeY) lenY = screenSizeY;

//	lenY -= startY;
	if (lenY<1) return;


	mulH /= 100;
	mulW /= 100;
	mulS /= 100;

	h1 *= mulH;
	h2 *= mulH;
	h3 *= mulH;

	w1 *= mulW;
	w2 *= mulW;
	w3 *= mulW;

	sp1 *= mulS;
	sp2 *= mulS;
	sp3 *= mulS;

	double dScreenSizeY = (double)screenSizeY;
	double cal = 1.0 / dScreenSizeY;

	for (int i=0;i<screenSizeY;i++)
	{
		kagerou[i] = 0;
	}







	CMyDirect3D::ExchangeScreenAndBuffer();

	if (CheckEffectError()) return;

	SetTexture(CMyDirect3D::GetBufferTexture());
	//CMyDirect3D::SetBufferTextureToStage(0);
	SetPercent(100.0f);
	POINT dstPoint;
	dstPoint.x = 0;
	dstPoint.y = 0;
	SIZE dstSize;
	dstSize.cx = screenSizeX;
	dstSize.cy = screenSizeY;
	POINT srcPoint;
	srcPoint.x = 0;
	srcPoint.y = 0;
	Blt(dstPoint,dstSize,srcPoint);


	SetPercent(0.6f);

	LPD3DXEFFECT effect = m_d3dxEffect;
	if (effect == NULL) return;
	SetAllColor();
	SetAllPercent();
	SetAllConst();
	SetAllTexture();

	if (m_hTechnique == NULL)
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


	for (int i=0;i<passKosuu;i++)
	{
		effect->BeginPass(i);


		for (int j=startY;j<startY+lenY;j++)
		{
			double th = (double)(j*w1 + sp1 * c );
			double th2 = (double)(j*w2 - sp2 * c);
			double th3 = (double)(j*w3 - sp3 * c);


			th *= (3.14159 * 2.0 * cal);
			th2 *= (3.14159 * 2.0 * cal);
			th3 *= (3.14159 * 2.0 * cal);


			int d = (int)(totalMulti * (cos(th)*h1 + cos(th2)*h2 + cos(th3) * h3) + 0.5);

			POINT dstPoint[2];
			dstPoint[0].x = d;
			dstPoint[0].y = j;
			dstPoint[1].x = dstPoint[0].x + screenSizeX;
			dstPoint[1].y = j;
			POINT srcPoint[2];
			srcPoint[0].x = 0;
			srcPoint[0].y = j;
			srcPoint[1].x = screenSizeX;
			srcPoint[1].y = j;

			CMyDirect3D::DrawLine(dstPoint,srcPoint);
		}

		effect->EndPass();
	}

	effect->End();









	return;
}
#else

void CEffectKagerou::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


//	int kagerou[MAXSCREENSIZEY];
//	int* kagerou = CEffectSimpleWipe::m_shapeWork;
	int* kagerou = m_allEffect->GetTempWork();



	int c = lp->count;

	int startWait = lp->para[3];
	double totalMulti = 1.0;

	if (startWait > 0)
	{
		if (c<startWait)
		{
			totalMulti = (double)c;
			totalMulti /= (double)startWait;
		}
	}

	double h1 = (double)(lp->para[7]);
	double h2 = (double)(lp->para[10]);
	double h3 = (double)(lp->para[13]);

	double w1 = (double)(lp->para[8]);
	double w2 = (double)(lp->para[11]);
	double w3 = (double)(lp->para[14]);

	double sp1 = (double)(lp->para[9]);
	double sp2 = (double)(lp->para[12]);
	double sp3 = (double)(lp->para[15]);

	double mulH = (double)(lp->para[4]);
	double mulW = (double)(lp->para[5]);
	double mulS = (double)(lp->para[6]);

	int startY = lp->para[1];
	int lenY = lp->para[2];

	if (startY<0) startY = 0;
	if (startY>=screenSizeY-1) startY = screenSizeY-1;

	if (lenY<1) lenY = 1;
	if (lenY>screenSizeY) lenY = screenSizeY;

//	lenY -= startY;
	if (lenY<1) return;


	mulH /= 100;
	mulW /= 100;
	mulS /= 100;

	h1 *= mulH;
	h2 *= mulH;
	h3 *= mulH;

	w1 *= mulW;
	w2 *= mulW;
	w3 *= mulW;

	sp1 *= mulS;
	sp2 *= mulS;
	sp3 *= mulS;

	double dScreenSizeY = (double)screenSizeY;
	double cal = 1.0 / dScreenSizeY;

	for (int i=0;i<screenSizeY;i++)
	{
		kagerou[i] = 0;
	}

	for (int i=startY;i<startY+lenY;i++)
	{
		double th = (double)(i*w1 + sp1 * c );
		double th2 = (double)(i*w2 - sp2 * c);
		double th3 = (double)(i*w3 - sp3 * c);


		th *= (3.14159 * 2.0 * cal);
		th2 *= (3.14159 * 2.0 * cal);
		th3 *= (3.14159 * 2.0 * cal);


		int d = (int)(totalMulti * (cos(th)*h1 + cos(th2)*h2 + cos(th3) * h3) + 0.5);
		kagerou[i] = d;
	}

	int* kage = kagerou;
	
	kage += startY;
	int* screen = CMyGraphics::GetScreenBuffer();

	screen += screenSizeX * startY;

	int srcPitch = screenSizeX * sizeof(int);

	int screenPitchMinus1 = (screenSizeX-1) * sizeof(int);

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		mov eax,160
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6
		psllw mm6,6

		neg eax
		add eax,256
		movd mm7,eax
		punpcklwd mm7,mm7
		punpckldq mm7,mm7
		psllw mm7,6

		pxor mm4,mm4

		mov ebx,kage
		mov edx,lenY
		mov esi,screen
LOOP1:
		push ebx
		push edx
		push esi

		mov eax,[ebx]
		test eax,80000000h
		jnz MINUS

		mov ecx,eax
		neg ecx
		add ecx,screenSizeX

		shl eax,2
		mov edi,esi
		add esi,eax

		mov ebx,4
START2:
LOOP2:
		mov edx,[esi]
		mov eax,[edi]

		movd mm0,eax
		movd mm1,edx

		punpcklbw mm0,mm4
		punpcklbw mm1,mm4

		psllw mm0,2
		psllw mm1,2

		pmulhw mm0,mm6
		pmulhw mm1,mm7
		paddw mm0,mm1

		packuswb mm0,mm0
		movd eax,mm0

		mov [edi],eax

		add esi,ebx
		add edi,ebx
		dec ecx
		jnz LOOP2
		jmp SKIP

MINUS:
		mov ecx,eax
		add ecx,screenSizeX

		neg eax
		shl eax,2

		mov edi,esi
//		add edi,639*4
		add edi,screenPitchMinus1
		mov esi,edi
		sub esi,eax
		mov ebx,-4
		jmp START2

SKIP:
		pop esi
		pop edx
		pop ebx
		add esi,srcPitch
		add ebx,4

		dec edx
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


/*_*/

