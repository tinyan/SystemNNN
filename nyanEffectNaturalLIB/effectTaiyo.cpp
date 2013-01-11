//
// EffectTaiyo.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "EffectTaiyo.h"


CEffectTaiyo::CEffectTaiyo(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	m_printTable = new int[screenSizeY*4];
}

CEffectTaiyo::~CEffectTaiyo()
{
	End();
}

void CEffectTaiyo::End(void)
{
	DELETEARRAY(m_printTable);
}


void CEffectTaiyo::InitParameter(LPVOID lpEffect, int layer)
{
	int para[32];
	EFFECT* lp = (EFFECT*)lpEffect;
	for (int i=0;i<32;i++)
	{
		para[i] = lp->para[i];
	}
	SetParam(lp,32,para,layer);
}

BOOL CEffectTaiyo::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{

	EFFECT* lp = (EFFECT*)lpEffect;

	int para[32];
	int k = paraKosuu;
	if (k>10) k = 10;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	int sizeX = CMyGraphics::GetScreenSizeX();
	int sizeY = CMyGraphics::GetScreenSizeY();



	if (paraKosuu<1) para[0] = 20;
	if (paraKosuu<2) para[1] = 10;

	if (paraKosuu<3) para[2] = 120;
	if (paraKosuu<4) para[3] = sizeY-40;
	if (paraKosuu<5) para[4] = -100;
	if (paraKosuu<6) para[5] = -100;
	if (paraKosuu<7) para[6] = sizeX-200;
	if (paraKosuu<8) para[7] = (sizeY * 3)/4;
	if (paraKosuu<9) para[8] = sizeX/2;
	if (paraKosuu<10) para[9] = sizeY/2;


	if (paraKosuu<11) para[10] = 2;	//ドーナツ最大数


	if (para[1]>20) para[1] = 20;
	if (para[1]<1) para[1] = 1;

	lp->flag = TRUE;
	lp->command = EFFECT_TAIYO;
	lp->count = 0;
	lp->countMax = para[0];

	for (i=0;i<11;i++)
	{
		lp->para[i] = para[i];
	}
	//InitTaiyo(para[1],para[10]);
	InitTaiyo(para);


	return TRUE;
}


BOOL CEffectTaiyo::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectTaiyo::BeginPrint(LPVOID para,int layer)
{

}

void CEffectTaiyo::Init(LPVOID para,int layer)
{
}

void CEffectTaiyo::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	if (lp->count > lp->countMax)
	{
		lp->count = lp->countMax;
	}
}


void CEffectTaiyo::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int c = lp->count;
	int dv = lp->countMax;
	if (dv<=0)
	{
		dv = 1;
		c = 1;
	}

	int kosuu = lp->para[1];

	int xStart = lp->para[2];
	int yStart = lp->para[3];
	int xEnd = lp->para[4];
	int yEnd = lp->para[5];

	int xx = xStart + ((xEnd - xStart) * c ) / dv;
	int yy = yStart + ((yEnd - yStart) * c ) / dv;

	int cxStart = lp->para[6];
	int cyStart = lp->para[7];
	int cxEnd = lp->para[8];
	int cyEnd = lp->para[9];

	int cx = cxStart + ((cxEnd - cxStart) * c ) / dv;
	int cy = cyStart + ((cyEnd - cyStart) * c ) / dv;

	for (int j=0;j<kosuu;j++)
	{
		int x = xx + ((cx - xx) * m_taiyoKyoriPercent[j]) / 100;
		int y = yy + ((cy - yy) * m_taiyoKyoriPercent[j]) / 100;

		m_taiyoKieru[j]--;
		if (m_taiyoKieru[j]>0)
		{
			if (m_taiyoType[j] == 0)
			{
				PrintLightCircle(x,y,m_taiyoR[j],m_taiyoColorR[j],m_taiyoColorG[j],m_taiyoColorB[j]);
			}
			else
			{
				PrintLightTorus(x,y,m_taiyoR[j],m_taiyoR2[j],m_taiyoColorR[j],m_taiyoColorG[j],m_taiyoColorB[j]);
			}
		}
		else
		{
			m_taiyoKieru[j] = (rand() % 60) + 30;
		}

	}

}


void CEffectTaiyo::InitTaiyo(int* lpPara)
{
	int kosuu = *(lpPara+1);
	int maxTorus = *(lpPara+10);

	int colR = 24;
	int colG = 24;
	int colB = 24;
	int colRnd = 64;
	int colR2 = 10;
	int colG2 = 10;
	int colB2 = 10;
	int colRnd2 = 24;

	int rBase = 16;
	int rRnd = 64;
	int rBase1 = 12;
	int rRnd1 = 12;
	int rtBase = 72;
	int rtRnd = 64;
	int rtBaseMinus = 20;
	int rtRndMinus = 16;

	int rtPercent = 18;

	int tk = 0;

	for (int i=0;i<kosuu;i++)
	{
		int ps = ((i+1) * 150) / kosuu;
		ps += rand() % (150/kosuu);

		m_taiyoKyoriPercent[i] = ps;
		m_taiyoR[i] = rBase + (rand() % rRnd);
		if (i == kosuu-1)
		{
			m_taiyoR[i] = rBase1 + (rand() % rRnd1);
		}

		m_taiyoColorR[i] = (rand() % colRnd) + colR;
		m_taiyoColorG[i] = (rand() % colRnd) + colG;
		m_taiyoColorB[i] = (rand() % colRnd) + colB;

		m_taiyoType[i] = 0;
		m_taiyoR2[i] = 0;
		if (tk< maxTorus)
//if (1)
		{
			if (((rand() % 100) < rtPercent) || (i== kosuu - 3))
//if (1)
			{
				m_taiyoType[i] = 1;

				m_taiyoR[i] = rtBase + (rand() % rtRnd);

				m_taiyoR2[i] = m_taiyoR[i] - rtBaseMinus - (rand() % rtRndMinus);
				if (m_taiyoR2[i] < 3) m_taiyoR2[i] = 3;

				m_taiyoColorR[i] = (rand() % colRnd2) + colR2;
				m_taiyoColorG[i] = (rand() % colRnd2) + colG2;
				m_taiyoColorB[i] = (rand() % colRnd2) + colB2;

				tk++;
			}
		}

		m_taiyoKieru[i] = (rand() % 30) + 20;
	}
}

#if defined _TINYAN3DLIB_
void CEffectTaiyo::PrintLightCircle(int x, int y, int r, int colR, int colG, int colB)
{
	CAllGeo::AddCircleFill(x,y,r,r,colR,colG,colB);
}

void CEffectTaiyo::PrintLightTorus(int x, int y, int r, int hole, int colR, int colG, int colB)
{
	CAllGeo::AddTorusFill(x,y,r,r,x,y,hole,hole,colR,colG,colB);
}

#else
void CEffectTaiyo::PrintLightCircle(int x, int y, int r, int colR, int colG, int colB)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int* printTable = m_printTable;


	int startY = y - r;
	if (startY<0) startY = 0;
	if (startY>=screenSizeY) return;

	int endY = y + r;
	if (endY>=screenSizeY) endY = screenSizeY-1;
	if (endY<0) return;

	int loopY = endY - startY + 1;

	double r2 = (double)r;
	r2 *= r2;


	ZeroMemory(printTable,sizeof(printTable));

	for (int j=startY;j<=endY;j++)
	{
		double rr = r2 - (double)((j-y)*(j-y));
		if (rr<0)
		{
			printTable[j*2+1] = 0;
		}
		else
		{
			int sqrr = (int)(sqrt(rr)+0.5);
			
			int xs = x - sqrr;
			int xe = x + sqrr;

			if (xs<0) xs = 0;
			if (xe>=screenSizeX) xe = screenSizeX-1;


			int ln = xe - xs + 1;
			if (ln<=0)
			{
				printTable[j*2+1] = 0;
			}
			else
			{
				printTable[j*2] = xs*4;
				printTable[j*2+1] = ln;
			}
		}
	}

	int* lpPtr = &printTable[startY*2];

	if (loopY<=0) return;

	int col = (colR << 16) | (colG<<8) | colB;

	int* screen = CMyGraphics::GetScreenBuffer();
	int lPitch = screenSizeX*sizeof(int);

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		pxor mm0,mm0

		mov eax,col
		movd mm7,eax
		punpcklbw mm7,mm0

		mov ecx,loopY
		mov ebx,lpPtr
		mov edi,screen

		mov eax,startY
		mov edx,lPitch
		mul edx
		add edi,eax

LOOP1:
		push ecx
		push edi

		mov ecx,[ebx+4]
		or ecx,ecx
		jz SKIP1
		add edi,[ebx]
LOOP2:
		mov eax,[edi]
		movd mm1,eax
		punpcklbw mm1,mm0
		paddusw mm1,mm7
		packuswb mm1,mm1
		movd edx,mm1
		mov [edi],edx
		add edi,4
		dec ecx
		jnz LOOP2


SKIP1:
		pop edi
		pop ecx
		add ebx,4*2
		add edi,lPitch
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


void CEffectTaiyo::PrintLightTorus(int x, int y, int r, int hole, int colR, int colG, int colB)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int* printTable = m_printTable;

	int startY = y - r;
	if (startY<0) startY = 0;
	if (startY>=screenSizeY) return;

	int endY = y + r;
	if (endY>=screenSizeY) endY = screenSizeY-1;
	if (endY<0) return;

	int loopY = endY - startY + 1;

	double r2 = (double)r;
	r2 *= r2;

	double hole2 = (double)hole;
	hole2 *= hole2;

	ZeroMemory(printTable,sizeof(printTable));

	for (int j=startY;j<=endY;j++)
	{
		double rr = r2 - (double)((j-y)*(j-y));
		double holehole = hole2 - (double)((j-y)*(j-y));

		if (rr<0)
		{
			printTable[j*4+1] = 0;
			printTable[j*4+3] = 0;
		}
		else
		{
			int sqrr = (int)(sqrt(rr)+0.5);
			
			int xs = x - sqrr;
			int xe = x + sqrr;


			if (holehole<0)
			{
				if (xs<0) xs = 0;
				if (xe>=screenSizeX) xe = screenSizeX-1;
				int ln = xe - xs + 1;
				if (ln<=0)
				{
					printTable[j*4+1] = 0;
					printTable[j*4+3] = 0;
				}
				else
				{
					printTable[j*4] = xs*4;
					printTable[j*4+1] = ln;
					printTable[j*4+3] = 0;
				}
			}
			else
			{
				int hole3 = (int)(sqrt(holehole)+0.5);
				
				int xs2 = x - hole3;
				int xe2 = x + hole3;

				if (xs<0) xs = 0;
				if (xe>=screenSizeX) xe = screenSizeX-1;
				if (xs2>=screenSizeX) xs2 = screenSizeX-1;
				if (xe2<0) xe2 = 0;

				int ln = xs2 - xs;
				if (ln<=0)
				{
					printTable[j*4+1] = 0;
				}
				else
				{
					printTable[j*4] = xs*4;
					printTable[j*4+1] = ln;
				}



				ln = xe - xe2;
				if (ln<=0)
				{
					printTable[j*4+3] = 0;
				}
				else
				{
					printTable[j*4+2] = xe2*4;
					printTable[j*4+3] = ln;
				}

			}
		}
	}



	int* lpPtr = &printTable[startY*4];

	if (loopY<=0) return;

	int col = (colR << 16) | (colG<<8) | colB;

	int* screen = CMyGraphics::GetScreenBuffer();
	int lPitch = screenSizeX * sizeof(int);

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		pxor mm0,mm0

		mov eax,col
		movd mm7,eax
		punpcklbw mm7,mm0

		mov ecx,loopY
		mov ebx,lpPtr
		mov edi,screen

		mov eax,startY
		mov edx,lPitch
		mul edx
		add edi,eax

LOOP1:
		push ecx
		push edi

		mov ecx,[ebx+4]
		or ecx,ecx
		jz SKIP1
		add edi,[ebx]
LOOP2:
		mov eax,[edi]
		movd mm1,eax
		punpcklbw mm1,mm0
		paddusw mm1,mm7
		packuswb mm1,mm1
		movd edx,mm1
		mov [edi],edx
		add edi,4
		dec ecx
		jnz LOOP2
SKIP1:

		pop edi
		push edi

		mov ecx,[ebx+12]
		or ecx,ecx
		jz SKIP2
		add edi,[ebx+8]
LOOP3:
		mov eax,[edi]
		movd mm1,eax
		punpcklbw mm1,mm0
		paddusw mm1,mm7
		packuswb mm1,mm1
		movd edx,mm1
		mov [edi],edx
		add edi,4
		dec ecx
		jnz LOOP3
SKIP2:


		pop edi
		pop ecx
		add ebx,4*4
		add edi,lPitch
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
