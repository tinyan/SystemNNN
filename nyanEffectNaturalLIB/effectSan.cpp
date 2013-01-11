//
// effectsan.cpp
//

#include "..\nyanEffectLib\includer.h"


#include "effectsan.h"


CEffectSan::CEffectSan(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(1);
	SetConstKosuu(1);
	Create("San");
#endif
}

CEffectSan::~CEffectSan()
{
	End();
}

void CEffectSan::End(void)
{
}

void CEffectSan::InitParameter(LPVOID lpEffect, int layer)
{
	int para[3];
	EFFECT* lp = (EFFECT*)lpEffect;
	for (int i=0;i<3;i++)
	{
		para[i] = lp->para[i];
	}
	SetParam(lp,3,para,layer);
}

BOOL CEffectSan::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[3];
	int k = paraKosuu;
	if (k>3) k = 3;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 15;
	if (paraKosuu<2) para[1] = 0;
	if (paraKosuu<3) para[2] = 0;

	lp->flag = TRUE;
	lp->command = EFFECT_SAN;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<3;i++)
	{
		lp->para[i] = para[i];
	}
	InitSan(para[1]);

	return TRUE;
}


BOOL CEffectSan::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectSan::BeginPrint(LPVOID para,int layer)
{

}

void CEffectSan::Init(LPVOID para,int layer)
{
}

void CEffectSan::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectSan::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int c = lp->count;
	int dv = lp->countMax;
	if (dv < 1)
	{
		dv = 1;
		c = 1;
	}

//	int ml = (255 * c ) / dv;

	int clipX1 = -48;
	int clipX2 = screenSizeX + 48;

	int lPitch = screenSizeX * sizeof(int);


	for (int i=0;i<SAN_KOSUU-2;i++)
	{
		int cnt = m_san[i].count;
		cnt--;
		if (cnt<=0)
		{
			m_san[i].mode = !m_san[i].mode;
			if (m_san[i].mode)
			{
				cnt = rand() % 160;
				cnt+= 60;
			}
			else
			{
				cnt = rand() % 2;
				cnt+= 1;
			}
		}
		m_san[i].count = cnt;


		if (m_san[i].mode == FALSE) continue;

		int light = (c * 256*256) / dv;
		light += m_san[i].startLightConst;
//char mes[256];
//sprintf(mes,"%d",light/256);
//MessageBox(NULL,mes,"1",MB_OK);

		int startX = m_san[i].startX;


		int deltaX = m_san[i].deltaX;

		int deltaLight = -256;
		int deltaLight2 = 256*8;

		int* screen = CMyGraphics::GetScreenBuffer();
	
#if defined _TINYAN3DLIB_
		int* workV = m_allEffect->GetTempWork();
		if (CheckEffectError()) return;

		float cc = 8.0f / 256.0f;
		cc *= (float)screenSizeX;
		SetConst(cc);

		float div3 = 1.0f / 3.0f;
		float divSizeX = 1.0f / ((float)screenSizeX);

		POINT dstPoint[3];

		dstPoint[0].x = startX/256;
		dstPoint[0].y = 0;
		dstPoint[1].x = startX/256+48;
		dstPoint[1].y = 0;
		dstPoint[2].x = (startX+deltaX*screenSizeY/2)/256+24;
		dstPoint[2].y = screenSizeY/2;

		for (int j=0;j<screenSizeY;j++)
		{
			float x1 = (float)(startX / 256 + 24);
			float x2 = (float)(light+24*deltaLight2) / 256.0f;

//			x1 /= ((float)screenSizeX);
			x2 /= 255.0f;


			x1 *= divSizeX;
			x1 += 1.0f;
			x1 *= div3;
//			x2 *= divSizeX;
			x2 += 1.0f;
			x2 *= div3;


			if (x1<0.0f) x1 = 0.0f;
			if (x1>0.995f) x1 = 0.995f;
			if (x2<0.0f) x2 = 0.0f;
			if (x2>0.995f) x2 = 0.995f;

			int x1Int = (int)(x1*65536.0f);
			int x2Int = (int)(x2*65536.0f);

			unsigned int x1High = x1Int >> 8;
			unsigned int x1Low  = x1Int & 0xff;
			unsigned int x2High = x2Int >> 8;
			unsigned int x2Low  = x2Int & 0xff;


			//XRGB -> RGBA
			workV[j] = (int)((x2Low << 24) | (x1High << 16) | (x1Low<<8) | x2High);

			startX += deltaX;
			light += deltaLight;
		}

		SetWorkV(workV,screenSizeY);
		SetTexture(GetVTexture(),0);

		//polygon dummy choten color

		FillPolygon(dstPoint);

#else
		__asm
		{
			push eax
			push ebx
			push ecx
			push edx
			push esi
			push edi

			mov edx,screenSizeY
			shr edx,1

			mov edi,screen
			mov ebx,startX
			mov esi,light
			pxor mm4,mm4

			mov eax,16
			movd mm5,eax
			punpcklwd mm5,mm5
			punpckldq mm5,mm5

LOOP1:
			push esi
			push ebx
			push edx
			push edi

			sar ebx,8
			add edi,ebx
			add edi,ebx
			add edi,ebx
			add edi,ebx

			cmp ebx,clipX1
			js SKIP99
			cmp ebx,clipX2
			jns SKIP99

			cmp esi,-256*24*8
			js SKIP99

			mov ecx,24
LOOP2:
			cmp ebx,screenSizeX
			jnb SKIP2
			test esi,esi
			js SKIP2
;
			mov eax,[edi]
			movd mm0,eax
			punpcklbw mm0,mm4

			mov eax,esi
			shr eax,8
			movd mm7,eax
			punpcklwd mm7,mm7
			punpckldq mm7,mm7
			paddusw mm0,mm7
			packuswb mm0,mm4
			movd eax,mm0
			mov [edi],eax

SKIP2:
			add esi,deltaLight2
			add edi,4
			inc ebx
			dec ecx
			jnz LOOP2


			mov ecx,24
LOOP3:
			cmp ebx,screenSizeX
			jnb SKIP3
			test esi,esi
			js SKIP3

			mov eax,[edi]
			movd mm0,eax
			punpcklbw mm0,mm4

			mov eax,esi
			shr eax,8
			movd mm7,eax
			punpcklwd mm7,mm7
			punpckldq mm7,mm7
			paddusw mm0,mm7
			packuswb mm0,mm4
			movd eax,mm0
			mov [edi],eax


SKIP3:
			sub esi,deltaLight2
			add edi,4
			inc ebx
			dec ecx
			jnz LOOP3
SKIP99:
			pop edi
			pop edx
			pop ebx
			pop esi

			add esi,deltaLight
			add ebx,deltaX
			add edi,lPitch

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
	}
}


void CEffectSan::InitSan(int h)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	for (int i=0;i<SAN_KOSUU;i++)
	{
		int startX = screenSizeX*h + (1-2*h) * ((i - SAN_KOSUU/2 + 1) * 96);
		startX *= 256;

		int deltaX = i * 128 + 96;
		deltaX *= (1-2*h);

		int startLightConst = (SAN_KOSUU - i);
//		if (h == 1) startLightConst = i;

		startLightConst *= (screenSizeY/2)*256;
		startLightConst /= SAN_KOSUU;
		startLightConst -= 336*256;

		int count = rand() % 40;
		count += 20;

		m_san[i].mode = TRUE;
		m_san[i].count = count;
		m_san[i].startX = startX;
		m_san[i].deltaX = deltaX;
		m_san[i].startLightConst = startLightConst;
	}
}
