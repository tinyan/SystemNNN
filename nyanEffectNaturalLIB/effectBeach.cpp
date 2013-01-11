//
// effectBeach.cpp
//

#include "..\nyanEffectLib\includer.h"
#include "effectBeach.h"

//R,É÷,É∆
CEffectBeach::BEACH CEffectBeach::m_rwt[2][3]=
{
	{
		{30.0 , 33.2 , 8130},
		{21.0 , -18.0 , 121},
		{10.0 , 16.7 , 71},
	},

	{
		{30.0 , 22.6 , 105},
		{23.0 , -17.1 , 40},
		{10.0 , 35.7 , 8102},
	},
};



CEffectBeach::CEffectBeach(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	int i,j;

	for (j=0;j<2;j++)
	{
		for (i=0;i<3;i++)
		{
			m_th[j][i] = rand() & 0x1fff;
		}
	}

	for (i=0;i<2;i++)
	{
		m_move[i] = rand() & 0x07ff;
	}

#if defined _TINYAN3DLIB_
	SetColorKosuu(2);
	SetTextureKosuu(2);
	Create("Beach");
#endif

}


CEffectBeach::~CEffectBeach()
{
	End();
}

void CEffectBeach::End(void)
{
}

BOOL CEffectBeach::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	EFFECT* lp = (EFFECT*)lpEffect;

	int para[16];
	int k = paraKosuu;
	if (k>15) k = 15;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}


	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 20;	//percent
	if (paraKosuu<3) para[2] = 128;	//R
	if (paraKosuu<4) para[3] = 192;	//G
	if (paraKosuu<5) para[4] = 255;	//B
	if (paraKosuu<6) para[5] = 0;	//startY
	if (paraKosuu<7) para[6] = screenSizeY;	//sizeY
	if (paraKosuu<8) para[7] = 30;	//é¸ä˙1
	if (paraKosuu<9) para[8] = 43;	//é¸ä˙2
	if (paraKosuu<10) para[9] = 300;	//à⁄ìÆïù1
	if (paraKosuu<11) para[10] = 250;	//à⁄ìÆïù2
	if (paraKosuu<12) para[11] = 100;	//îgïù1
	if (paraKosuu<13) para[12] = 100;	//îgïù2
	if (paraKosuu<14) para[13] = 700;	//âEë§å¿äE
	if (paraKosuu<15) para[14] = 100;	//ÉpÅ[ÉXÉpÉâ

	if (para[6]>screenSizeY) para[6] = screenSizeY;
	if (para[7]<1) para[7] = 1;
	if (para[8]<1) para[8] = 1;
	if (para[14]<1) para[14] = 1;

	lp->flag = TRUE;
	lp->command = EFFECT_BEACH;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<15;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectBeach::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectBeach::BeginPrint(LPVOID para,int layer)
{

}

void CEffectBeach::Init(LPVOID para,int layer)
{
}

void CEffectBeach::Calcu(LPVOID lpEffect,int layer)
{
	int i,j;

	EFFECT* lp = (EFFECT*)lpEffect;
	int c = lp->count;
	int countMax = lp->countMax;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();
//	m_count++;
//	if (m_count>=screenSizeY) m_count -= screenSizeY;

	for (j=0;j<2;j++)
	{
		for (i=0;i<3;i++)
		{
			m_th[j][i] += m_rwt[j][i].th;
			m_th[j][i] &= 0x1fff;
		}
	}

	for (i=0;i<2;i++)
	{
		m_move[i] += lp->para[7+i];
		m_move[i] &= 0x7ff;
	}
}



void CEffectBeach::Print(LPVOID lpEffect,int layer)
{
	int i,j,k;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

//	int work[MAXSCREENSIZEY*4];	//loop1,offset1,loop2,offset2
	//int* work = CEffectSimpleWipe::m_shapeWork;
	int* work = m_allEffect->GetTempWork();

	int* workPtr = work;

	EFFECT* lp = (EFFECT*)lpEffect;


	int startY = lp->para[5];
	if (startY<0) startY = 0;
	if (startY>=screenSizeY) startY = screenSizeY - 1;
	int loopY = lp->para[6];
	if ((startY+loopY)>screenSizeY)
	{
		loopY = screenSizeY - startY;
	}
	if (loopY<1) return;


	int* dst = CMyGraphics::GetScreenBuffer();
	int lPitch = screenSizeX * sizeof(int);
	dst += screenSizeX * startY;


	int ps = lp->para[1];
	int colR = lp->para[2];
	int colG = lp->para[3];
	int colB = lp->para[4];

	int ps1 = ps;
	int ps2 = ps*2 - (ps*ps)/100;


	double divTHRev = 1.0 / (double)screenSizeY;

	double constTH[2][3];
	for (j=0;j<2;j++)
	{
		for (i=0;i<3;i++)
		{
			double th = (double)m_th[j][i];
			th /= 8192.0;
			th *= 3.1415926*2;
			constTH[j][i] = th;
		}
	}

	double namiMulti[2];
	for (i=0;i<2;i++)
	{
		namiMulti[i] = (double)(lp->para[11+i]);
		namiMulti[i] *= 0.01;
	}

//	double rightX1 = 560.0;
//	double rightX2 = rightX1 * ;


	double divSizeYRev = 1.0 / ((double)screenSizeY);

	double moveDelta[2];
	for (i=0;i<2;i++)
	{
		double th = (double)(m_move[i]);
		th /= 2048.0;
		th *= 3.14159*2.0;
		moveDelta[i] = (1.0+cos(th)) * ((double)(lp->para[9+i])) * 0.5;
	}

	for (k=0;k<loopY;k++)
	{
		double ml = (double)(lp->para[5]+k);
		ml *= divSizeYRev;

		double perseMulti = (double)(lp->para[14]);
		perseMulti *= 0.01;
		perseMulti += (1.0 - perseMulti)*ml;

		double rightX = (double)(lp->para[13] - screenSizeX / 2);
		rightX *= perseMulti;
		rightX += (double)(screenSizeX / 2);


		double hakei[2];
		for (j=0;j<2;j++)
		{
			hakei[j] = 0.0;
			for (i=0;i<3;i++)
			{
				double wt = (double)k;
				wt *= divTHRev;
				wt *= m_rwt[j][i].w;

				hakei[j] += m_rwt[j][i].r * cos(wt + constTH[j][i]);
			}

			hakei[j] *= namiMulti[j];
		}





		int x1 = (int)(rightX - moveDelta[0]*perseMulti - hakei[0]);
		int x2 = (int)(rightX - moveDelta[1]*perseMulti - hakei[1]);



		int xEnd = (int)(rightX);
		if (xEnd>screenSizeX) xEnd = screenSizeX;
		if (xEnd<1) xEnd = 1;

		if (x1<0) x1 = 0;
		if (x2<0) x2 = 0;

		if (x1>=x2)
		{
			int d = x1;
			x1 = x2;
			x2 = d;
		}

		int ln1 = x2 - x1;
		if ((x1+ln1) > screenSizeX)
		{
			ln1 = screenSizeX - x1;
		}
		if (ln1<0) ln1 = 0;
		if (x1>=screenSizeX) ln1 = 0;


		int ln2 = xEnd - x2;
		if ((x2+ln2) > screenSizeX)
		{
			ln2 = screenSizeX - x2;
		}
		if (ln2<0) ln2 = 0;
		if (x2>=screenSizeX) ln2 = 0;

		work[k*4] = ln1;
		work[k*4+1] = x1*4;
		work[k*4+2] = ln2;
		work[k*4+3] = x2*4;
	}

	int percent1_128 = ((100-ps1) * 128) / 100;
	
	int r = (colR * ps1) / 100;
	int g = (colG * ps1) / 100;
	int b = (colB * ps1) / 100;

	int addR1_128 = r<<7;
	int addG1_128 = g<<7;
	int addB1_128 = b<<7;



	int percent2_128 = ((100-ps2) * 128) / 100;

	int r2 = (colR * ps2) / 100;
	int g2 = (colG * ps2) / 100;
	int b2 = (colB * ps2) / 100;

	int addR2_128 = r2<<7;
	int addG2_128 = g2<<7;
	int addB2_128 = b2<<7;


#if defined _TINYAN3DLIB_

	if (CheckEffectError()) return;
	float col1[4];
	col1[0] = ((float)colR) / 255.0f;
	col1[1] = ((float)colG) / 255.0f;
	col1[2] = ((float)colB) / 255.0f;
	col1[3] = ((float)ps1) / 100.0f;
	SetColor(col1);

	float col2[4];
	col2[0] = ((float)colR) / 255.0f;
	col2[1] = ((float)colG) / 255.0f;
	col2[2] = ((float)colB) / 255.0f;
	col2[3] = ((float)ps2) / 100.0f;
	SetColor(col2,1);

	int* workV = m_allEffect->GetTempWork();
	workV += screenSizeY * 4;
	int* workV2 = workV + screenSizeY;

	float div3 = 1.0f / 3.0f;
	float divSizeX = 1.0f / ((float)screenSizeX);


	for (int j=0;j<screenSizeY;j++)
	{
		float x1 = (float)(work[j*4+1] / 4);
		float x2 = (float)(work[j*4+3] / 4);
		float x3 = x2 + (float)(work[j*4+2]);

		x1 *= divSizeX;
		x1 += 1.0f;
		x1 *= div3;
		x2 *= divSizeX;
		x2 += 1.0f;
		x2 *= div3;
		x3 *= divSizeX;
		x3 += 1.0f;
		x3 *= div3;

		if (x1<0.0f) x1 = 0.0f;
		if (x1>0.995f) x1 = 0.995f;
		if (x2<0.0f) x2 = 0.0f;
		if (x2>0.995f) x2 = 0.995f;
		if (x3<0.0f) x3 = 0.0f;
		if (x3>0.995f) x3 = 0.995f;

		int x1Int = (int)(x1*65536.0f);
		int x2Int = (int)(x2*65536.0f);
		int x3Int = (int)(x3*65536.0f);

		unsigned int x1High = x1Int >> 8;
		unsigned int x1Low  = x1Int & 0xff;
		unsigned int x2High = x2Int >> 8;
		unsigned int x2Low  = x2Int & 0xff;
		unsigned int x3High = x3Int >> 8;
		unsigned int x3Low  = x3Int & 0xff;


		//XRGB -> RGBA
		workV[j] = (int)((x2Low << 24) | (x1High << 16) | (x1Low<<8) | x2High);
		workV2[j] = (int)((0 << 24) | (x3High << 16) | (x3Low<<8) | 0);
	}

	SetWorkV(workV,screenSizeY);
	SetWorkV(workV2,screenSizeY,1,1);

	SetTexture(GetVTexture(),0);
	SetTexture(GetVTexture(1),1);

	Fill();

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

		mov eax,[percent1_128]
		movd mm2,eax
		punpcklwd mm2,mm2
		punpckldq mm2,mm2

		mov eax,[addR1_128]
		movd mm3,eax
		psllq mm3,32
		mov eax,[addG1_128]
		movd mm6,eax
		psllq mm6,16
		mov eax,[addB1_128]
		movd mm7,eax
		paddw mm3,mm6
		paddw mm3,mm7


		mov eax,[percent2_128]
		movd mm4,eax
		punpcklwd mm4,mm4
		punpckldq mm4,mm4

		mov eax,[addR2_128]
		movd mm5,eax
		psllq mm5,32
		mov eax,[addG2_128]
		movd mm6,eax
		psllq mm6,16
		mov eax,[addB2_128]
		movd mm7,eax
		paddw mm5,mm6
		paddw mm5,mm7

		mov ebx,workPtr
		mov edi,dst
		mov ecx,loopY
LOOP1:
		push ebx
		push ecx
		push edi

		mov ecx,[ebx]
		or ecx,ecx
		jz SKIP1
		
		push edi

		add edi,[ebx+4]
LOOP2A:
		mov eax,[edi]
		movd mm1,eax
		punpcklbw mm1,mm0
		pmullw mm1,mm2
//		stall
//		stall
		paddw mm1,mm3
		psrlw mm1,7
		packuswb mm1,mm0
		movd eax,mm1
		mov [edi],eax

		add edi,4
		dec ecx
		jnz LOOP2A

		pop edi

SKIP1:
		mov ecx,[ebx+8]
		or ecx,ecx
		jz SKIP2
		add edi,[ebx+12]
LOOP2B:
		mov eax,[edi]
		movd mm1,eax
		punpcklbw mm1,mm0
		pmullw mm1,mm4
//		stall
//		stall
		paddw mm1,mm5
		psrlw mm1,7
		packuswb mm1,mm0
		movd eax,mm1
		mov [edi],eax

		add edi,4
		dec ecx
		jnz LOOP2B

SKIP2:
		pop edi
		pop ecx
		pop ebx

		add ebx,4*4
		add edi,lPitch
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
#endif

}


BOOL CEffectBeach::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

/*_*/
