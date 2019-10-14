//
// EffectRemember.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "EffectRemember.h"


CEffectRemember::CEffectRemember(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	m_rememberCount = 0;

	int sizeX = CMyGraphics::GetScreenSizeX();
	int sizeY = CMyGraphics::GetScreenSizeY();


	m_left = new int [sizeY];
	m_right = new int [sizeY];

#if defined _TINYAN3DLIB_
	SetTextureKosuu(2);
	Create("Remember");
#endif
}

CEffectRemember::~CEffectRemember()
{
	End();
}

void CEffectRemember::End(void)
{
	DELETEARRAY(m_left);
	DELETEARRAY(m_right);
}

void CEffectRemember::InitParameter(LPVOID lpEffect, int layer)
{
	int para[3];
	EFFECT* lp = (EFFECT*)lpEffect;
	for (int i=0;i<3;i++)
	{
		para[i] = lp->para[i];
	}
	SetParam(lp,3,para,layer);
}

BOOL CEffectRemember::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[3];
	int k = paraKosuu;
	if (k>1) k = 1;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;

	lp->flag = TRUE;
	lp->command = EFFECT_REMEMBER;
	lp->count = 0;
	lp->countMax = 99999;

	return TRUE;
}


BOOL CEffectRemember::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectRemember::BeginPrint(LPVOID para,int layer)
{

}

void CEffectRemember::Init(LPVOID para,int layer)
{
}

void CEffectRemember::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectRemember::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	m_rememberCount++;
	if (m_rememberCount>100000000) m_rememberCount = 0;
	
	int count = m_rememberCount;

	double th[4];
	
	double ml[4] = {0.0345698, 0.002178934, 0.04425678, 0.001234786};
	double dlt[4] = {0,4,11,15};
	double omega[4] = {0.05145735, 0.0362343, 0.053232, 0.03417};

	int h[4] = {15,23,17,20};

	double omega2[4] = {0.3, 0.22, 0.27, 0.19};
	double dlt2[4] = {2,3,5,7};

	double h2[4];

	int i,j;
	for (i=0;i<4;i++)
	{
		h2[i] = (double)h[i];
		h2[i] *= (1.5 +cos(count * omega2[i] + dlt2[i]));
	}


	int sizeX = CMyGraphics::GetScreenSizeX();
	int sizeY = CMyGraphics::GetScreenSizeY();



	int* left = m_left;
	int* right = m_right;


	for (j=0;j<sizeY;j++)
	{
		for (i=0;i<4;i++)
		{
			double t = (double)count;
			t *= ml[i];
			t *= 3.14159;
			t += dlt[i];
			t += j*omega[i];
			th[i] = t;
		}

		int d = (int)(cos(th[0]) * h2[0] + cos(th[1]) * h2[1] + 0.5) + 64;
		int d2 = (int)(cos(th[2]) * h2[2] + cos(th[3]) * h2[3] + 0.5) + sizeX-64;

		left[j] = d;
		right[j] = d2;

	}

	int rsize = 100;

	int centerX = sizeX/2;

	for (j=0;j<rsize;j++)
	{
		int sizeX = right[rsize] - left[rsize];

		int d=left[j];
		int d2=right[j];
		double th = (double)(rsize-j);
		th /= rsize*4;
		th *= 3.14159*2;

//		th += 3.14159/2;

		int delta = (int)(sin(th)*.4*sizeX);

		d += delta;
		d2 -= delta;

//		if (d>319) d = 319;
//		if (d2<321) d2 = 321;
		if (d>=centerX) d = centerX-1;
		if (d2<=centerX) d2 = centerX+1;
		left[j] = d;
		right[j] = d2;
	}

	for (j=0;j<rsize;j++)
	{
		int sizeX = right[sizeY-rsize-1] - left[sizeY-rsize-1];

		int d=left[sizeY-rsize+j];
		int d2=right[sizeY-rsize+j];
		double th = (double)(j);
		th /= rsize*4;
		th *= 3.14159*2;

		int delta = (int)(sin(th)*0.4*sizeX);

		d += delta;
		d2 -= delta;

		if (d>(sizeX/2-1)) d = sizeX/2-1;
		if (d2<(sizeX/2+1)) d2 = sizeX/2+1;
		left[sizeY-rsize+j] = d;
		right[sizeY-rsize+j] = d2;
	}



#if defined _TINYAN3DLIB_
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int* workV = m_allEffect->GetTempWork();
	int* workV2 = workV + screenSizeY;

	if (CheckEffectError()) return;


	float div3 = 1.0f / 3.0f;
	float divSizeX = 1.0f / ((float)screenSizeX);


	for (int j=0;j<screenSizeY;j++)
	{
		float x1 = (float)(left[j]);
		float x2 = x1 + 64.0f;
		float x3 = (float)(right[j]);
		float x4 = x3;
		x3 -= 64.0f;

		x1 *= divSizeX;
		x1 += 1.0f;
		x1 *= div3;
		x2 *= divSizeX;
		x2 += 1.0f;
		x2 *= div3;
		x3 *= divSizeX;
		x3 += 1.0f;
		x3 *= div3;
		x4 *= divSizeX;
		x4 += 1.0f;
		x4 *= div3;

		if (x1<0.0f) x1 = 0.0f;
		if (x1>0.995f) x1 = 0.995f;
		if (x2<0.0f) x2 = 0.0f;
		if (x2>0.995f) x2 = 0.995f;
		if (x3<0.0f) x3 = 0.0f;
		if (x3>0.995f) x3 = 0.995f;
		if (x4<0.0f) x4 = 0.0f;
		if (x4>0.995f) x4 = 0.995f;

		int x1Int = (int)(x1*65536.0f);
		int x2Int = (int)(x2*65536.0f);
		int x3Int = (int)(x3*65536.0f);
		int x4Int = (int)(x4*65536.0f);

		unsigned int x1High = x1Int >> 8;
		unsigned int x1Low  = x1Int & 0xff;
		unsigned int x2High = x2Int >> 8;
		unsigned int x2Low  = x2Int & 0xff;
		unsigned int x3High = x3Int >> 8;
		unsigned int x3Low  = x3Int & 0xff;
		unsigned int x4High = x4Int >> 8;
		unsigned int x4Low  = x4Int & 0xff;


		//XRGB -> RGBA
		workV[j] = (int)((x2Low << 24) | (x1High << 16) | (x1Low<<8) | x2High);
		workV2[j] = (int)((x4Low << 24) | (x3High << 16) | (x3Low<<8) | x4High);
	}

	SetWorkV(workV,screenSizeY);
	SetTexture(GetVTexture(0),0);
	SetWorkV(workV2,screenSizeY,1,1);
	SetTexture(GetVTexture(1),1);

	Fill();

#else

	int* leftPtr = left;
	int* rightPtr = right;

//	int* lpBuffer = m_game->m_lpScreenBuffer;
//	int* lpBuffer = m_game->GetScreenBuffer();
	int* lpBuffer = CMyGraphics::GetScreenBuffer();

	int sizeXdiv2 = sizeX / 2;
	int dstPitch = sizeX * 4;

#if defined _WIN64
#pragma message("‚±‚±‚Éc++ŽÀ‘•‚ª•K—v‚É‚á " __FILE__)

#else

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi


		mov edx,sizeY
		mov ebx,leftPtr
		mov esi,rightPtr
		mov edi,lpBuffer
LOOP1:
		push edi

		mov eax,[ebx]
		add eax,64

		test eax,eax
		js SKIP1

		shr eax,1
		mov ecx,eax
		inc ecx
		

		add eax,eax
		add eax,eax
		add eax,eax

		push edi
		add edi,eax

		pxor mm7,mm7
		mov eax,01010101h

		mov eax,04040404h

		movd mm6,eax
		punpckldq mm6,mm6
LOOP2:
		movq mm0,[edi]
		paddusb mm0,mm7
		paddusb mm7,mm6
		movq [edi],mm0
		sub edi,8
		dec ecx
		jnz LOOP2

		pop edi

SKIP1:



		mov eax,[esi]
		sub eax,64

		cmp eax,sizeX
		jnb SKIP2


		shr eax,1
		mov ecx,eax
		neg ecx
		add ecx,sizeXdiv2
		

		add eax,eax
		add eax,eax
		add eax,eax

		push edi
		add edi,eax

		pxor mm7,mm7

		mov eax,04040404h
		movd mm6,eax
		punpckldq mm6,mm6
LOOP3:
		movq mm0,[edi]
		paddusb mm0,mm7
		paddusb mm7,mm6
		movq [edi],mm0
		add edi,8
		dec ecx
		jnz LOOP3

		pop edi

SKIP2:


		pop edi
		add edi,dstPitch
		add ebx,4
		add esi,4
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

#endif

#endif



}
