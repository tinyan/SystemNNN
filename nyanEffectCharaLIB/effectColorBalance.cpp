//
// EffectColorBalance.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "EffectColorBalance.h"


CEffectColorBalance::CEffectColorBalance(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

#if defined _TINYAN3DLIB_
	SetTextureKosuu(3);
	SetConstKosuu(1);
	Create("ColorBalance");
#endif



	for (int i=0;i<10;i++)
	{
		m_balanceSeat[i] = new int[256];
	}

	for (int i=0;i<3;i++)
	{
		m_colorTable[i] = new int[256];
	}


	for (int j=0;j<10;j++)
	{
		for (int i=0;i<256;i++)
		{
			m_balanceSeat[j][i] = 0;
		}
	}

	//0
	for (int i=0;i<256;i++)
	{
		m_balanceSeat[0][i] = 255;
	}

	//1 low
	for (int i=0;i<256;i++)
	{
		m_balanceSeat[1][i] = 255-i;
	}

	//2 mid
	for (int i=0;i<128;i++)
	{
		m_balanceSeat[2][i] = 128+i;
		m_balanceSeat[2][255-i] = 255-i;
	}

	//3high
	for (int i=0;i<256;i++)
	{
		m_balanceSeat[3][i] = i;
	}
	


	//low 2
	for (int i=0;i<128;i++)
	{
		m_balanceSeat[4][i] = (127-i)*2;
	}

	//mid 2
	for (int i=0;i<128;i++)
	{
		m_balanceSeat[5][i] = i*2;
		m_balanceSeat[5][255-i] = i*2;
	}

	//high2
	for (int i=0;i<128;i++)
	{
		m_balanceSeat[6][255-i] = (127-i)*2;
	}

	//low3
	for (int i=0;i<85;i++)
	{
		m_balanceSeat[7][i] = 255;
	}
	for (int i=0;i<170;i++)
	{
		m_balanceSeat[7][85+i] = ((169-i)*3)/2;
	}

	//mid3
	for (int i=0;i<85;i++)
	{
		m_balanceSeat[8][i] = (i*3)/2 + 127;
		m_balanceSeat[8][255-i] = (i*3)/2 + 127;
	}
	for (int i=85;i<=170;i++)
	{
		m_balanceSeat[8][i] = 255;
	}

	//high3
	for (int i=0;i<170;i++)
	{
		m_balanceSeat[9][i] = (i*3)/2;
	}
	for (int i=170;i<256;i++)
	{
		m_balanceSeat[9][i] = 255;
	}
}

CEffectColorBalance::~CEffectColorBalance()
{
	End();
}

void CEffectColorBalance::End(void)
{
	for (int i=0;i<10;i++)
	{
		DELETEARRAY(m_balanceSeat[i]);
	}

	for (int i=0;i<3;i++)
	{
		DELETEARRAY(m_colorTable[i]);
	}
}


BOOL CEffectColorBalance::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[16];
	int k = paraKosuu;
	if (k>14) k = 14;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}


	if (paraKosuu<1) para[0] = 20;	//frame

	if (paraKosuu<2) para[1] = 0;	//end r
	if (paraKosuu<3) para[2] = para[1];	//end g
	if (paraKosuu<4) para[3] = para[2];	//end b

	if (paraKosuu<5) para[4] = para[1];	//start r
	if (paraKosuu<6) para[5] = para[2];	//start g
	if (paraKosuu<7) para[6] = para[3];	//start b


	if (paraKosuu<8) para[7] = 1;	//transflg
	if (paraKosuu<9) para[8] = 0;	//type
	if (paraKosuu<10) para[9] = 0;	//subframe

	if (paraKosuu<11) para[10] = 0;//rType
	if (paraKosuu<12) para[11] = 0;//gType
	if (paraKosuu<13) para[12] = 0;//bType
	if (paraKosuu<14) para[13] = 0;//輝度保持フラグ



	lp->countMax = para[0];
	lp->flag = TRUE;
	lp->command = EFFECT_COLORBALANCE;
	lp->count = 0;

	for (i=0;i<14;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectColorBalance::CountIsMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int r = lp->para[1];
	int g = lp->para[2];
	int b = lp->para[3];

	int typ = lp->para[7];

	if ((r == 0) && (g == 0) && (b == 0))
	{
///		lp->command = EFFECT_NOP;
	}

	return TRUE;
}


void CEffectColorBalance::BeginPrint(LPVOID para,int layer)
{

}

void CEffectColorBalance::Init(LPVOID para,int layer)
{
}

void CEffectColorBalance::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectColorBalance::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int pic = lp->pic;
	if (pic == -1) return;
	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	int count = lp->count;
	int countMax = lp->countMax;
	int type = lp->para[8];
	int subFrame = lp->para[9];

	int r1 = lp->para[4];
	int g1 = lp->para[5];
	int b1 = lp->para[6];

	int r2 = lp->para[1];
	int g2 = lp->para[2];
	int b2 = lp->para[3];

	int r = CCalcuSpeed::calcu(count,countMax,r1,r2,subFrame,type);
	int g = CCalcuSpeed::calcu(count,countMax,g1,g2,subFrame,type);
	int b = CCalcuSpeed::calcu(count,countMax,b1,b2,subFrame,type);

	int rgb[3];
	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;

	int colorType[3];
	colorType[0] = lp->para[10];
	colorType[1] = lp->para[11];
	colorType[2] = lp->para[12];

	int lightAdjustFlag = lp->para[13];

	//make color add sub table256
	for (int i=0;i<3;i++)
	{
		int baranceSeat = colorType[i];

		for (int k=0;k<256;k++)
		{
			m_colorTable[i][k]  = (rgb[i] * m_balanceSeat[baranceSeat][k]) / 256;
		}
	}


	//adjust?
	if (lightAdjustFlag)
	{
		for (int i=0;i<256;i++)
		{
			float rr = (float)(m_colorTable[0][i]);
			float gg = (float)(m_colorTable[1][i]);
			float bb = (float)(m_colorTable[2][i]);
			float deltaLight = rr * 0.299f + gg * 0.587f + bb * 0.114f;

			rr -= deltaLight / 0.299f * 0.33333f;
			gg -= deltaLight / 0.587f * 0.33333f;
			bb -= deltaLight / 0.114f * 0.33333f;
			

			int rrr = (int)rr;
			int ggg = (int)gg;
			int bbb = (int)bb;
			if (rrr<-255) rrr = -255;
			if (rrr> 255) rrr = 255;
			if (ggg<-255) ggg = -255;
			if (ggg> 255) ggg = 255;
			if (bbb<-255) bbb = -255;
			if (bbb> 255) bbb = 255;

			m_colorTable[0][i] = rrr;
			m_colorTable[1][i] = ggg;
			m_colorTable[2][i] = bbb;
		}
	}


	int colorAddSub[256*2];

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	//clip
//	int putX = 0;
//	int putY = 0;
//	int srcX = 0;
//	int srcY = 0;
//	int sizeX = screenSizeX;
//	int sizeY = screenSizeY;

	int putX = lp->dst.left;
	int putY = lp->dst.top;
	int srcX = lp->src.left;
	int srcY = lp->src.top;
	int sizeX = lp->dst.right;
	int sizeY = lp->dst.bottom;



	int* src = (int*)(lpPic->GetBuffer());
	char* mask = lpPic->GetMaskPic();


	SIZE picSize = lpPic->GetPicSize();

	int maskPitch = picSize.cx;
	int srcPitch = picSize.cx * sizeof(int);
	int dstPitch = screenSizeX * sizeof(int);

	int* dst = CMyGraphics::GetScreenBuffer();

	if (lpPic->Clip(putX,putY,srcX,srcY,sizeX,sizeY) == FALSE) return;


	src += srcX;
	src += (srcPitch / sizeof(int)) * srcY;

	dst += putX;
	dst += (dstPitch / sizeof(int)) * putY;

	mask += srcX;
	mask += maskPitch * srcY;




	int* colorAddSubTable = colorAddSub;

	LONGLONG rgb2yuvConst = 0x0000004D0096001D;

//Y =  0.299R + 0.587G + 0.114B
//77 150 29
//4D 96 1d

#if defined _TINYAN3DLIB_
	float color[256*4];
	for (int i=0;i<256;i++)
	{
		color[i*4+0] = ((float)(m_colorTable[0][i])) / 255.0f;
		color[i*4+1] = ((float)(m_colorTable[1][i])) / 255.0f;
		color[i*4+2] = ((float)(m_colorTable[2][i])) / 255.0f;
		color[i*4+3] = 0.0f;
	}

	if (CheckEffectError()) return;

	float div3 = 1.0f / 3.0f;


	int* workV = m_colorTable[0];//流用
	int* workV2 = m_colorTable[1];//流用

	for (int j=0;j<256;j++)
	{
//color[j*4+0] = ((float)(rand() % 256)) / 256.0f;

		float x1 = color[j*4+0];
		float x2 = color[j*4+1];
		float x3 = color[j*4+2];
		float x4 = color[j*4+3];

		x1 += 1.0f;
		x2 += 1.0f;
		x3 += 1.0f;
		x4 += 1.0f;

		x1 *= div3;
		x2 *= div3;
		x3 *= div3;
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
		*(workV +j)   = (int)((x2Low << 24) | (x1High << 16) | (x1Low<<8) | x2High);
		*(workV2+j)   = (int)((x4Low << 24) | (x3High << 16) | (x3Low<<8) | x4High);
	}


	float const1 = 255.0f / ((float)screenSizeY);
	SetConst(const1);


	SetWorkV(workV,256);
	LPDIRECT3DTEXTURE9 vTexture = CMyDirect3D::GetVTexture();
	SetTexture(vTexture,1);


	SetWorkV(workV2,256,1,1);
	LPDIRECT3DTEXTURE9 vTexture2 = CMyDirect3D::GetVTexture(1);
	SetTexture(vTexture2,2);

	CMyTexture* lpTexture = (CMyTexture*)(lpPic->GetTexture());
	SetTexture(lpTexture->GetTexture(),0);

	POINT dstPoint = m_allEffect->GetDstPoint(layer);
	SIZE dstSize = picSize;
	POINT srcPoint;
	srcPoint.x = 0;
	srcPoint.y = 0;


	Blt(dstPoint,dstSize,srcPoint);




#else
	if (mask == NULL) return;
	for (int i=0;i<256;i++)
	{
		int addR = m_colorTable[0][i];
		int addG = m_colorTable[1][i];
		int addB = m_colorTable[2][i];
		int subR = -addR;
		int subG = -addG;
		int subB = -addB;

		if (addR<0) addR = 0;
		if (addG<0) addG = 0;
		if (addB<0) addB = 0;
		if (subR<0) subR = 0;
		if (subG<0) subG = 0;
		if (subB<0) subB = 0;


		colorAddSub[i*2] = (addR << 16) | (addG<<8) | addB;
		colorAddSub[i*2+1] = (subR << 16) | (subG<<8) | subB;
	}

#if defined _WIN64
#pragma message("ここにc++実装が必要にゃ " __FILE__)

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

		mov ebx,mask
		mov esi,src
		mov edi,dst
		mov ecx,sizeY
LOOP1:
		push ebx
		push ecx
		push esi
		push edi

		mov ecx,sizeX
LOOP2:
		push ecx

		xor eax,eax
		mov al,[ebx]
		or eax,eax
		jz SKIP1

		movd mm2,eax
		punpcklwd mm2,mm2
		punpckldq mm2,mm2

		mov ecx,eax
		neg ecx
		add ecx,256
		movd mm6,ecx
		punpcklwd mm6,mm6
		punpckldq mm6,mm6

		mov eax,[esi]
		movd mm3,eax
		movq mm4,mm3
		punpcklbw mm4,mm0

		movq mm5,rgb2yuvConst
		pmaddwd mm5,mm4
		movq mm4,mm5
		punpckhdq mm5,mm5
		paddd mm5,mm4
		psrlw mm5,8
		movd ecx,mm5
		and ecx,0xff
		add ecx,ecx
		add ecx,ecx
		add ecx,ecx
		add ecx,colorAddSubTable
		mov edx,[ecx]
		mov ecx,[ecx+4]
		movd mm4,edx
		movd mm5,ecx
		paddusb mm3,mm4
		psubusb mm3,mm5

		punpcklbw mm3,mm0
		pmullw mm3,mm2

		mov eax,[edi]
		movd mm7,eax
		punpcklbw mm7,mm0
		pmullw mm7,mm6
		paddw mm7,mm3
		psrlw mm7,8
		packuswb mm7,mm7
		movd eax,mm7

		mov [edi],eax

SKIP1:

		add edi,4
		add esi,4
		inc ebx
		pop ecx
		dec ecx
		jnz LOOP2

		pop edi
		pop esi
		pop ecx
		pop ebx
		add edi,dstPitch
		add esi,srcPitch
		add ebx,maskPitch
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


BOOL CEffectColorBalance::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}



