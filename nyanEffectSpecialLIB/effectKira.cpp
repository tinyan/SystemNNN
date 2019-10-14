//
// EffectKira.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "EffectKira.h"


CEffectKira::CEffectKira(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	m_picFlag = FALSE;

	m_pic = new CPicture(64,64);
	
	if (m_pic->LoadDWQ("sys\\kirakira") == FALSE) return;

	m_picFlag = TRUE;

	int* pic = (int*)(m_pic->GetBuffer());
	if (pic == NULL) return;
	
	RECT rc;
	m_pic->GetPicSize(&rc);

	int sx = rc.right;
	int sy = rc.bottom;
	int szx = sx;

	if (sx>64) sx = 64;
	if (sy>64) sy = 64;


	int i,j;

	for (i=0;i<64*64;i++) m_kiraTable[i] = 0;


	if ((sx<64) || (sy<64)) return;


	for (j=0;j<sy;j++)
	{
		for (i=0;i<sx;i++)
		{
			int c = *(pic + i + j * szx);
			c &= 0xff;
			m_kiraTable[i+j*64] = c;
		}
	}

#if defined _TINYAN3DLIB_
	SetTextureKosuu(1);
	SetConstKosuu(1);
	Create("Kirakira");
#endif
}


CEffectKira::~CEffectKira()
{
	End();
}

void CEffectKira::End(void)
{
	ENDDELETECLASS(m_pic);
}

void CEffectKira::InitParameter(LPVOID lpEffect, int layer)
{
	int para[6];
	EFFECT* lp = (EFFECT*)lpEffect;
	for (int i=0;i<6;i++)
	{
		para[i] = lp->para[i];
	}
	SetParam(lp,6,para,layer);
}

BOOL CEffectKira::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int para[6];
	int k = paraKosuu;
	if (k>6) k = 6;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}




	if (paraKosuu<2) para[1] = KIRA_KOSUU;
	if (para[1]<1) para[1] = 1;
	if (para[1]>KIRA_KOSUU) para[1] = KIRA_KOSUU;

	if (paraKosuu<3) para[2] = 32;
	if (paraKosuu<4) para[3] = 32;
	if (paraKosuu<5) para[4] = screenSizeX-32*2;
	if (paraKosuu<6) para[5] = screenSizeY-32*2;

	if (para[2]<32) para[2] = 32;
	if (para[2]>screenSizeX-32) para[2] = screenSizeX-32;
	if (para[3]<32) para[3] = 32;
	if (para[3]>screenSizeY-32) para[3] = screenSizeY-32;
	if (para[4]<1) para[4] = 1;
	if (para[5]<1) para[5] = 1;

	if ((para[2]+para[4]) > screenSizeX-33) para[4] = screenSizeX-33-para[2];
	if ((para[3]+para[5]) > screenSizeY-33) para[5] = screenSizeY-33-para[3];

	if (para[4]<1) para[4] = 1;
	if (para[5]<1) para[5] = 1;


	lp->flag = TRUE;
	lp->command = EFFECT_KIRA;
	lp->count = 0;
	lp->countMax = 99999;

	for (i=0;i<6;i++)
	{
		lp->para[i] = para[i];
	}

	InitKira(lpEffect);

	return TRUE;
}


BOOL CEffectKira::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectKira::BeginPrint(LPVOID para,int layer)
{

}

void CEffectKira::Init(LPVOID para,int layer)
{
}

void CEffectKira::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectKira::Print(LPVOID lpEffect,int layer)
{
	if (m_picFlag == FALSE) return;

	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int* buf = (int*)(m_pic->GetBuffer());
	if (buf == NULL) return;

	RECT rc;
	m_pic->GetPicSize(&rc);
	if ((rc.right<64) || (rc.bottom<64)) return;


#if defined _TINYAN3DLIB_
	if (CheckEffectError()) return;
	CMyTexture* lpTexture = (CMyTexture*)(m_pic->GetTexture());
	SetTexture(lpTexture->GetTexture());
#endif

	int i;
	int k = lp->para[1];


	for (i=0;i<k;i++)
	{
		int cc = m_kira[i].count;
		cc++;
		if (cc>=m_kira[i].countMax)
		{
			SetKiraSub(lpEffect,i);
		}
		else
		{
			m_kira[i].count = cc;
		}
	}

	//print

	for (i=0;i<k;i++)
	{
		int c = m_kira[i].count;
		int dv = m_kira[i].countMax;
		if (dv<=0) dv = 1;
		int dv2 = (dv * 7 + 5) / 10;
		if (dv2<=0) dv2 = 1;

		int dv3 = dv - dv2;
		if (dv3<=0) dv3 = 1;

		int ps = 0;

		if (c<=dv2)
		{
			ps = (c * 100) / dv2;
		}
		else
		{
			ps = ((dv - c) * 100 ) / dv3;
		}

		if (ps<0) ps = 0;
		if (ps>100) ps = 100;

		int x = m_kira[i].x;
		int y = m_kira[i].y;
		PrintKiraSub(x,y,ps);
	}


}

void CEffectKira::InitKira(LPVOID lpEffect)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int k = lp->para[1];
	for (int i=0;i<k;i++)
	{
		SetKiraSub(lpEffect,i);
		int r = rand() % m_kira[i].countMax;
		m_kira[i].count = r;
	}
}


void CEffectKira::SetKiraSub(LPVOID lpEffect,int k)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int r = rand() % 8;
	r += 5;
	m_kira[k].count = 0;
	m_kira[k].countMax = r;

	int x = lp->para[2];
	int y = lp->para[3];

	int dx = rand() % lp->para[4];
	int dy = rand() % lp->para[5];

	x += dx;
	y += dy;

	x -= 32;
	y -= 32;

	int sizeX = CMyGraphics::GetScreenSizeX();
	int sizeY = CMyGraphics::GetScreenSizeY();


	if (x<32) x = 32;
	if (x>sizeX-32) x = sizeX-32;
	if (y<32) y = 32;
	if (y>sizeY-32) y = sizeY-32;


	m_kira[k].x = x;
	m_kira[k].y = y;
}

void CEffectKira::PrintKiraSub(int x, int y, int ps)
{
	int* pic = m_kiraTable;

	int sizeX = CMyGraphics::GetScreenSizeX();
	int sizeY = CMyGraphics::GetScreenSizeY();


	if (x<32) x = 32;
	if (y<32) y = 32;
	if (x>=sizeX-32) x = sizeX - 32;
	if (y>=sizeY-32) y = sizeY - 32;

#if defined _TINYAN3DLIB_
	float alfa = (float)ps;
	alfa /= 100.0f;
	alfa = 1.0f - alfa;

	SetConst(alfa);
	POINT dstPoint;
	dstPoint.x = x;
	dstPoint.y = y;
	SIZE dstSize;
	dstSize.cx = 64;
	dstSize.cy = 64;
	POINT srcPoint;
	srcPoint.x = 0;
	srcPoint.y = 0;

	Blt(dstPoint,dstSize,srcPoint);



#else


	int* dst = CMyGraphics::GetScreenBuffer();
	dst += x;
	dst += sizeX * y;

	int lPitch = sizeX*4;


	int loopX = 64;
	int loopY = 64;

	int ps2 = ps * 255;
	ps2 /= 100;

	ps2 = 255 - ps2;

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


		mov eax,ps2
		movd mm7,eax
		punpcklwd mm7,mm7
		punpckldq mm7,mm7
		pxor mm0,mm0

		mov esi,pic
		mov edi,dst


		mov ecx,loopY
LOOP1:
		push ecx
		push edi

		mov ecx,loopX
LOOP2:
		mov eax,[esi]
		or eax,eax
		jz SKIP1

		movd mm1,eax
		punpcklwd mm1,mm1
		punpckldq mm1,mm1
		psubusw mm1,mm7

		mov ebx,[edi]
		movd mm2,ebx
		punpcklbw mm2,mm0

		paddw mm2,mm1
		packuswb mm2,mm0

		movd eax,mm2
		mov [edi],eax
SKIP1:
		add esi,4
		add edi,4
		dec ecx
		jnz LOOP2

		pop edi
		pop ecx
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

#endif

#endif

}
