//
// effectsuna.cpp			
//

#include "..\nyanEffectLib\includer.h"

#include "effectsuna.h"


CEffectSuna::CEffectSuna(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	int pictureSizeX = 128;
	int pictureSizeY = 128;

	m_sunaPic = new CPicture(pictureSizeX,pictureSizeY);

	int* picBuffer = (int*)(m_sunaPic->GetBuffer());
	char* mask = (char*)(m_sunaPic->GetMaskPic());


	CMyTexture* lpTexture = (CMyTexture*)(m_sunaPic->GetTexture());

	int lp = pictureSizeX*pictureSizeY;
	for (int i=0;i<lp;i++)
	{
		unsigned int r = rand() % 256;
		unsigned int d = (0xff<<24) | (r<<16) | (r<<8) | r;
		*(picBuffer+i+32) = d;
		*(mask+i) = r;
	}

	lpTexture->CreateTexture(picBuffer,FALSE);
#else

	int sizeX = CMyGraphics::GetScreenSizeX();
	int sizeY = CMyGraphics::GetScreenSizeY();

	int sz = sizeX * sizeY / 2 / 2 / 4;

	m_suna = new int[sz];
#endif
}

CEffectSuna::~CEffectSuna()
{
	End();
}

void CEffectSuna::End(void)
{
#if defined _TINYAN3DLIB_
	ENDDELETECLASS(m_sunaPic);
#else
	DELETEARRAY(m_suna);
#endif
}

void CEffectSuna::InitParameter(LPVOID lpEffect, int layer)
{
	int para[16];
	EFFECT* lp = (EFFECT*)lpEffect;
	int count = lp->count;
	for (int i=0;i<16;i++)
	{
		para[i] = lp->para[i];
	}
	SetParam(lp,16,para,layer);
	lp->count = count;
}

BOOL CEffectSuna::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[16];
	int k = paraKosuu;
	if (k>10) k = 10;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}


	int sizeX = CMyGraphics::GetScreenSizeX();
	int sizeY = CMyGraphics::GetScreenSizeY();


	if (paraKosuu<1) para[0] = 0;	//FRAME
	if (paraKosuu<2) para[1] = 0;	//半透明フラグ

	if (paraKosuu<3) para[2] = 100;		//終了%
	if (paraKosuu<4) para[3] = para[6];	//開始%

	if (paraKosuu<5) para[4] = 0;	//type
	if (paraKosuu<6) para[5] = 0;	//subframe


	if (paraKosuu<7) para[6] = 0;		//開始X
	if (paraKosuu<8) para[7] = 0;		//開始Y

	if (paraKosuu<9) para[8] = sizeX;	//SizeX
	if (paraKosuu<10) para[9] = sizeY;	//SIzeY

	if (paraKosuu<11) para[10] = 0;	//loopflag

	if (para[8]>sizeX) para[8] = sizeX;
	if (para[9]>sizeY) para[9] = sizeY;



	if (para[6]<0) para[6] = 0;
	if (para[6]>=sizeX) para[6] = sizeX - 1;

	if (para[7]<0) para[7] = 0;
	if (para[7]>=sizeY) para[7] = sizeY - 1;

	if ((para[6]+para[8])>sizeX) para[8] = sizeX - para[6];
	if ((para[7]+para[9])>sizeY) para[9] = sizeY - para[7];
	for (i=0;i<10;i++)
	{
		lp->para[i] = para[i];
	}

	lp->flag = TRUE;
	lp->command = EFFECT_SUNA;
	lp->countMax = lp->para[0];
	lp->count = 0;

	InitSuna();

	return TRUE;
}


BOOL CEffectSuna::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectSuna::BeginPrint(LPVOID para,int layer)
{

}

void CEffectSuna::Init(LPVOID para,int layer)
{
}

void CEffectSuna::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	if (lp->count > lp->countMax)
	{
		lp->count = lp->countMax;
	}
}

#if defined _TINYAN3DLIB_
void CEffectSuna::Print(LPVOID lpEffect,int layer)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


//	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

//	m_sunaCount++;
//	m_sunaCount &= 1;

//	int dx = m_sunaCount & 1;

	int putX = lp->para[6] & (~7);
	int putY = lp->para[7] & (~1);

	int sizeX = lp->para[8] & (~7);
	int sizeY = lp->para[9] & (~1);

	if (putX<0) putX = 0;
	if (putY<0) putY = 0;
	if (putX>=screenSizeX) return;
	if (putY>=screenSizeY) return;


	if ((putX+sizeX)>screenSizeX)
	{
		sizeX = screenSizeX - putX;
	}
	if ((putY+sizeY)>screenSizeY)
	{
		sizeY = screenSizeY - putY;
	}

	if ((sizeX<1) || (sizeY<1)) return;




	int loopX = sizeX / 128;
	int amariX = sizeX % 128;
	int loopY = sizeY /  128;
	int amariY = sizeY % 128;

	int loopY2 = loopY;
	if (amariY>0) loopY2 += 1;

	int loopX2 = loopX;
	if (amariX>0) loopX2 += 1;

//	CMyTexture* lpTexture = m_sunaPic->GetTexture();
//	if (lpTexture == NULL) return;
//	SetTexture(lpTexture->GetTexture());


	int transFlag = lp->para[1];
	int ps1 = lp->para[3];
	int ps2 = lp->para[2];
	int count = lp->count;
	int countMax = lp->para[0];
	if (countMax<1) countMax = 1;
	if (count<0) count = 0;
	if (count>countMax) count = countMax;

	int ps = 100;

	int type = lp->para[4];
	int subFrame = lp->para[5];

	if (transFlag != 0)
	{
		ps = CCalcuSpeed::calcu(count,countMax,ps1,ps2,subFrame,type);
	}


	for (int j=0;j<loopY2;j++)
	{
		int putSizeY = 128;
		if (j >= loopY)
		{
			putSizeY = amariY;
		}


		for (int i=0;i<loopX2;i++)
		{
			int putSizeX = 128;
			if (i >= loopX)
			{
				putSizeX = amariX;
			}

			int srcX = rand() % 64;
			int srcY = rand() % 64;

//			m_sunaPic->TransLucentBlt_2(putX+i*128,putY+j*128,srcX,srcY,putSizeX,putSizeY,ps);
			m_sunaPic->StretchBlt1(putX+i*128,putY+j*128,putSizeX,putSizeY,srcX,srcY,putSizeX/2,putSizeY/2,ps,TRUE);
		}
	}
}

#else

void CEffectSuna::Print(LPVOID lpEffect,int layer)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	m_sunaCount++;
	m_sunaCount &= 1;

	int dx = m_sunaCount & 1;

	int putX = lp->para[6] & (~7);
	int putY = lp->para[7] & (~1);

	int sizeX = lp->para[8] & (~7);
	int sizeY = lp->para[9] & (~1);

	if (putX<0) putX = 0;
	if (putY<0) putY = 0;
	if (putX>=screenSizeX) return;
	if (putY>=screenSizeY) return;


	if ((putX+sizeX)>screenSizeX)
	{
		sizeX = screenSizeX - putX;
	}
	if ((putY+sizeY)>screenSizeY)
	{
		sizeY = screenSizeY - putY;
	}

	if ((sizeX<1) || (sizeY<1)) return;


	dst += putX;
	dst += putY * screenSizeX;

//	int sizeX = CPicture::m_screenSizeX;
//	int sizeY = CPicture::m_screenSizeY;
	int sz = sizeX * sizeY / 2 / 2 / 4;

	int sz2 = sz / 2;
	//dummy size
	for (int i=0;i<sz2;i++)
	{
		m_suna[i*2+dx] ^= ((rand() & 0x7fff) | ((rand() & 0x7fff)<<16));
	}

//	int* scr = (int*)CPicture::m_lpScreenBuffer;
	int* dat = (int*)m_suna;

	int lPitch = screenSizeX * sizeof(int);

	int lPitchDelta = 8 - lPitch;


//	int loopX = screenSizeX /2 /4;
//	int loopY = screenSizeY / 2;
	int loopX = sizeX /2 /4;
	int loopY = sizeY / 2;

	if (loopX<1) return;
	if (loopY<1) return;




	int transFlag = lp->para[1];
	int ps1 = lp->para[3];
	int ps2 = lp->para[2];
	int count = lp->count;
	int countMax = lp->para[0];
	if (countMax<1) countMax = 1;
	if (count<0) count = 0;
	if (count>countMax) count = countMax;
//	int dv = lp->para[5];

	int ps = 256;

	int type = lp->para[4];
	int subFrame = lp->para[5];



	if (transFlag != 0)
	{
		ps = CCalcuSpeed::calcu(count,countMax,(ps1*256)/100,(ps2*256)/100,subFrame,type);

			/*
//OutputDebugString("*");
		ps = (ps1 * 256) / 100;
		if (dv>0)
		{
			int c = count;
			if (c>dv) c = dv;

			double d = (double)ps1;
			d += ((double)((ps2-ps1)*c)) / (double)dv;
			d *= 256.0;
			d /= 100.0;
			ps = (int)d;

//char mes[256];
//sprintf(mes,"[c=%d dv=%d ps1=%d ps2=%d ps=%d]",c,dv,ps1,ps2,ps);
//OutputDebugString(mes);
		}
		*/
	}

	if (ps>256) ps = 256;
	if (ps<0) ps = 0;

	if (ps==0) return;

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

		mov eax,ps
		cmp eax,256
		jnz TRANSMODE

		mov edi,dst
		mov ecx,loopY
		mov esi,dat
		mov eax,0ffffffh
		movd mm7,eax
		punpckldq mm7,mm7


LOOP0:
		mov ebx,loopX
		push edi
LOOP1:
		mov eax,[esi]
		add eax,eax

		add esi,4
		mov edx,4
LOOP2:
		movd mm1,eax
		punpcklbw mm1,mm1
		punpcklwd mm1,mm1
		punpckldq mm1,mm1
		pand mm1,mm7

		movq [edi],mm1
		add edi,lPitch
		movq [edi],mm1
		shr eax,8
		add edi,lPitchDelta

		dec edx
		jnz LOOP2
;
		dec ebx
		jnz LOOP1
;
		pop edi
		add edi,lPitch
		add edi,lPitch
		dec ecx
		jnz LOOP0

		jmp ALLEXIT


TRANSMODE:
		mov edi,dst
		mov ecx,loopY
		mov esi,dat
		mov eax,0ffffffh
		movd mm7,eax
		punpckldq mm7,mm7

		mov eax,ps
		movd mm5,eax
		punpcklwd mm5,mm5
		punpckldq mm5,mm5	//ps	for src

		neg eax
		add eax,256

		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6	//256-ps	for dst

LOOP0A:
		push edi
		mov ebx,loopX
LOOP1A:
		mov eax,[esi]
		add eax,eax

		add esi,4
		mov edx,4
LOOP2A:
		movd mm7,eax
		punpcklbw mm7,mm7
		punpcklwd mm7,mm7
		punpcklbw mm7,mm0

		pmullw mm7,mm5
		psrlw mm7,8			//calced src



		movq mm2,[edi]
		movq mm3,mm2
		punpcklbw mm2,mm0	//dst00
		punpckhbw mm3,mm0	//dst01

		pmullw mm2,mm6
		pmullw mm3,mm6
		//
		psrlw mm2,8
		psrlw mm3,8
		paddw mm2,mm7
		paddw mm3,mm7
		packuswb mm2,mm0
		packuswb mm3,mm0
		punpckldq mm2,mm3
		movq [edi],mm2


		add edi,lPitch

		movq mm2,[edi]
		movq mm3,mm2
		punpcklbw mm2,mm0	//dst10
		punpckhbw mm3,mm0	//dst11

		pmullw mm2,mm6
		pmullw mm3,mm6
		//
		psrlw mm2,8
		psrlw mm3,8
		paddw mm2,mm7
		paddw mm3,mm7
		packuswb mm2,mm0
		packuswb mm3,mm0
		punpckldq mm2,mm3
		movq [edi],mm2

		shr eax,8

		add edi,lPitchDelta


		dec edx
		jnz LOOP2A
;
		dec ebx
		jnz LOOP1A
;
		pop edi
		add edi,lPitch
		add edi,lPitch
		dec ecx
		jnz LOOP0A


ALLEXIT:
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

#endif


void CEffectSuna::InitSuna(void)
{
#if defined _TINYAN3DLIB_
	return;
#endif
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	m_sunaCount = 0;

	int sz = (screenSizeX / 2) * (screenSizeY / 2) / 4;

	for (int i=0;i<sz;i++)
	{
		m_suna[i] = (rand() & 0x7fff) | ((rand() & 0x7fff)<<16);
	}
}

/*_*/


