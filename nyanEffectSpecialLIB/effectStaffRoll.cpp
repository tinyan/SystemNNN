//
// EffectStaffRoll.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "EffectStaffRoll.h"


CEffectStaffRoll::CEffectStaffRoll(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	m_percent = new int [screenSizeY];
#if defined _TINYAN3DLIB_
	SetTextureKosuu(2);
	Create("StaffRoll");
#endif
}

CEffectStaffRoll::~CEffectStaffRoll()
{
	End();
}

void CEffectStaffRoll::End(void)
{
	DELETEARRAY(m_percent);
}

void CEffectStaffRoll::InitParameter(LPVOID lpEffect, int layer)
{
	int para[16];
	EFFECT* lp = (EFFECT*)lpEffect;
	for (int i=0;i<16;i++)
	{
		para[i] = lp->para[i];
	}
	SetParam(lp,16,para,layer);
}

BOOL CEffectStaffRoll::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[16];
	int k = paraKosuu;
	if (k>16) k = 16;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	int screenSizeY = CMyGraphics::GetScreenSizeY();


	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 1;


	if (paraKosuu<3) para[2] = 0;	//%1
	if (paraKosuu<4) para[3] = 50;
	if (paraKosuu<5) para[4] = 100;
	if (paraKosuu<6) para[5] = 100;
	if (paraKosuu<7) para[6] = 50;
	if (paraKosuu<8) para[7] = 0;	//%6

	if (paraKosuu<9) para[8] = 100;	//y2
	if (paraKosuu<10) para[9] = 200;
	if (paraKosuu<11) para[10] = 280;
	if (paraKosuu<12) para[11] = 380;	//y5

	if (paraKosuu<13) para[12] = 1;	//画像枚数
	if (paraKosuu<14) para[13] = 0;//下部占有レイヤー

	if (para[8]<0) para[8] = 0;

	if (para[9]<para[8]) para[9] = para[8];
	if (para[10]<para[9]) para[10] = para[9];
	if (para[11]<para[10]) para[11] = para[10];

	if (para[8]>screenSizeY) para[8] = screenSizeY;
	if (para[9]>screenSizeY) para[9] = screenSizeY;
	if (para[10]>screenSizeY) para[10] = screenSizeY;
	if (para[11]>screenSizeY) para[11] = screenSizeY;
	if (para[12] < 1) para[12] = 1;
	if (para[12] == 2)
	{
		para[13] = 1;
	}
	if (para[12] > 2)
	{
		if (para[13] < 2)
		{
			para[13] = 2;
		}
	}

	lp->countMax = para[0];
	lp->flag = TRUE;
	lp->command = EFFECT_STAFFROLL;
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}

	ZeroMemory(m_percent,screenSizeY*sizeof(int));


	//create table
	MakeTableSub(0,para[8],para[2],para[3]);
	for (i=0;i<3;i++)
	{
		MakeTableSub(para[8+i],para[8+i+1],para[3+i],para[3+i+1]);
	}
	MakeTableSub(para[11],screenSizeY,para[6],para[7]);

	return TRUE;
}



BOOL CEffectStaffRoll::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}



void CEffectStaffRoll::BeginPrint(LPVOID para,int layer)
{

}

void CEffectStaffRoll::Init(LPVOID para,int layer)
{
}

void CEffectStaffRoll::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectStaffRoll::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	EFFECT* lp = (EFFECT*)lpEffect;

	//create table
	MakeTableSub(0,lp->para[8],lp->para[2],lp->para[3]);
	for (int i=0;i<3;i++)
	{
		MakeTableSub(lp->para[8+i],lp->para[8+i+1],lp->para[3+i],lp->para[3+1+i]);
	}
	MakeTableSub(lp->para[11],screenSizeY,lp->para[6],lp->para[7]);

	int pic = lp->pic;
	if (pic == -1) return;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	int dv = lp->countMax;
	if (dv<1) dv = 1;
	int c = lp->count;

	RECT rc = lp->dst;

	int srcX = 0;
	int srcY = 0;
	int putX = rc.left;
	int putY = rc.top;
	RECT rc2;
	lpPic->GetPicSize(&rc2);
	int sizeX = rc2.right;
	int sizeY = rc2.bottom;
	int picSizeX = sizeX;


	int maisuu = lp->para[12];
	for (int i=0;i<maisuu;i++)
	{
		PrintStaffRollSub(lpEffect,layer,i);
	}
}

void CEffectStaffRoll::PrintStaffRollSub(LPVOID lpEffect,int layerStart, int deltaLayer)
{
	int* dst = CMyGraphics::GetScreenBuffer();
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	EFFECT* lp = (EFFECT*)lpEffect;

//	//create table
//	MakeTableSub(0,lp->para[8],lp->para[2],lp->para[3]);
//	for (int i=0;i<3;i++)
//	{
//		MakeTableSub(lp->para[8+i],lp->para[8+i+1],lp->para[3+i],lp->para[3+1+i]);
//	}
//	MakeTableSub(lp->para[11],screenSizeY,lp->para[6],lp->para[7]);

//	int pic = lp->pic;
//	if (pic == -1) return;

	CPicture* lpPicBase = m_allEffect->GetPicture(layerStart);
	if (lpPicBase == NULL) return;

	SIZE basePicSize = lpPicBase->GetPicSize();
	int picSizeY = basePicSize.cy;


	CPicture* lpPic = NULL;

	int layer = layerStart + deltaLayer;
	if (deltaLayer > 0)
	{
		int dv = lp->para[13];
		if (dv<1) dv = 1;
		int dlt = (deltaLayer - 1) % dv;
		layer = layerStart + 1 + dlt;

		if (layer > 16) return;
		if (layer < 0) return;

		lpPic = m_allEffect->GetPicture(layer);
		if (lpPic == NULL) return;

		//load data
		char filename[1024];
		char dirname[3];
		LPSTR srcFileName = lpPicBase->GetFileName();
		memcpy(dirname,srcFileName,2);
		dirname[2] = 0;

		wsprintf(filename,"%s_%d",srcFileName,deltaLayer+1);
		if (lpPic->LoadDWQ(filename) == FALSE) return;
	}
	else
	{
		lpPic = m_allEffect->GetPicture(layerStart);
		if (lpPic == NULL) return;
	}

	int dv = lp->countMax;
	if (dv<1) dv = 1;
	int c = lp->count;

	RECT rc = lp->dst;

	int srcX = 0;
	int srcY = 0;
	int putX = rc.left;
	int putY = rc.top;

	putY += picSizeY * deltaLayer;

	RECT rc2;
	lpPic->GetPicSize(&rc2);
	int sizeX = rc2.right;
	int sizeY = rc2.bottom;
	int picSizeX = sizeX;


	int srcPitch = sizeX * sizeof(int);

	//clip x

	if (putX>=screenSizeX) return;
	if ((putX+sizeX)<=0) return;

	if (putX<0)
	{
		sizeX -= (-putX);
		srcX += (-putX);
		putX = 0;
		if (sizeX<=0) return;
	}

	if ((putX + sizeX) > screenSizeX)
	{
		sizeX = screenSizeX - putX;
		if (sizeX <= 0) return;
	}

	//y clip
	if (putY>=screenSizeY) return;
	if ((putY+sizeY)<=0) return;


	if (putY<0)
	{
		sizeY -= (-putY);
		srcY += (-putY);
		putY = 0;
		if (sizeY<=0) return;
	}

	if ((putY + sizeY) > screenSizeY)
	{
		sizeY = screenSizeY - putY;
		if (sizeY <= 0) return;
	}


	int* src = (int*)(lpPic->GetBuffer());
	if (src == NULL) return;

	int trans = *src;

	int loopX = sizeX;
	int loopY = sizeY;
	int* table = m_percent;
	int yZahyo = putY;

	int lPitch = screenSizeX * sizeof(int);

	src += srcX;
	src += srcY * picSizeX;

	dst += putX;
	dst += screenSizeX * putY;

	int maskFlag = lp->para[1];
	char* mask = NULL;
	int maskPitch = picSizeX;

	if (maskFlag == 2)
	{
		mask = lpPic->GetMaskPic();
		mask += srcX;
		mask += srcY * picSizeX;

		if (mask == NULL) return;
	}

#if defined _TINYAN3DLIB_
	if (CheckEffectError()) return;

	CMyTexture* lpTexture = (CMyTexture*)(lpPic->GetTexture());
	SetTexture(lpTexture->GetTexture());


	int* workV = m_allEffect->GetTempWork();

	float div3 = 1.0f / 3.0f;

	for (int j=0;j<screenSizeY;j++)
	{
		int d = (m_percent[j] * 255) / 256;

		workV[j] = (int)((0 << 24) | (d << 16) | (0<<8) | 0);
	}

	SetWorkV(workV,screenSizeY);
	SetTexture(GetVTexture(),1);


	POINT dstPoint;
	SIZE dstSize;
	POINT srcPoint;

	dstPoint.x = putX;
	dstPoint.y = putY;
	dstSize.cx = sizeX;
	dstSize.cy = sizeY;
	srcPoint.x = srcX;
	srcPoint.y = srcY;

	Blt(dstPoint,dstSize,srcPoint);


#else

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

		mov eax,maskFlag
		cmp eax,2
		jz MASKTYPE

		pxor mm0,mm0

		mov eax,yZahyo
		shl eax,2
		mov ebx,table
		add ebx,eax

		mov esi,src
		mov edi,dst
		mov edx,loopY
LOOP1:
		push esi
		push edi

		mov ecx,loopX

		mov eax,[ebx]
		or eax,eax
		jz SKIP99

		cmp eax,256
		jz NORMAL

		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6

		neg eax
		add eax,256
		movd mm7,eax
		punpcklwd mm7,mm7
		punpckldq mm7,mm7
LOOP2:
		mov eax,[esi]
		cmp eax,trans
		jz SKIP2

		movd mm1,eax
		punpcklbw mm1,mm0
		mov eax,[edi]
		movd mm2,eax
		punpcklbw mm2,mm0

		pmullw mm1,mm6
		pmullw mm2,mm7
		psrlw mm1,8
		psrlw mm2,8

		paddw mm1,mm2
		packuswb mm1,mm0

		movd eax,mm1

		mov [edi],eax
SKIP2:
		add esi,4
		add edi,4
		dec ecx
		jnz LOOP2
		jmp SKIP99
			
NORMAL:
LOOP2A:
		mov eax,[esi]
		cmp eax,trans
		jz SKIP2A
		mov [edi],eax
SKIP2A:
		add esi,4
		add edi,4
		dec ecx
		jnz LOOP2A

SKIP99:
		pop edi
		pop esi
		add esi,srcPitch
		add edi,lPitch
		add ebx,4
		dec edx
		jnz LOOP1

		jmp EXIT99



MASKTYPE:
		pxor mm0,mm0

		mov eax,256
		movd mm7,eax
		punpcklwd mm7,mm7
		punpckldq mm7,mm7


		mov eax,yZahyo
		shl eax,2
		mov ebx,table
		add ebx,eax

		mov esi,src
		mov edi,dst
		mov edx,mask

		mov ecx,loopY
MLOOP1:
		push ecx
		push esi
		push edi
		push edx


		mov ecx,loopX

		mov eax,[ebx]
		or eax,eax
		jz MSKIP99

		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6

MLOOP2:
		xor eax,eax
		mov al,[edx]
		or eax,eax
		jz MSKIP2

		movd mm3,eax

		pmullw mm3,mm6
		psrlw mm3,8
		punpcklwd mm3,mm3
		punpckldq mm3,mm3

		movq mm4,mm7
		psubw mm4,mm3

		mov eax,[esi]

		movd mm1,eax
		punpcklbw mm1,mm0
		mov eax,[edi]
		movd mm2,eax
		punpcklbw mm2,mm0

		pmullw mm1,mm3
		pmullw mm2,mm4
		psrlw mm1,8
		psrlw mm2,8

		paddw mm1,mm2
		packuswb mm1,mm0

		movd eax,mm1

		mov [edi],eax
MSKIP2:
		add esi,4
		add edi,4
		inc edx
		dec ecx
		jnz MLOOP2
		jmp MSKIP99

MSKIP99:
		pop edx
		pop edi
		pop esi
		pop ecx
		add esi,srcPitch
		add edi,lPitch
		add ebx,4
		add edx,maskPitch
		dec ecx
		jnz MLOOP1

EXIT99:
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


BOOL CEffectStaffRoll::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectStaffRoll::MakeTableSub(int yStart, int yEnd, int percent1, int percent2)
{
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int dv = yEnd - yStart;
	if (dv<1) return;

	for (int i=yStart;i<yEnd;i++)
	{
		if ((i>=0) && (i<screenSizeY))
		{
			int ps = percent1 + ((i-yStart) * (percent2 - percent1)) / dv;
			ps *= 256;
			ps /= 100;
			if (ps<0) ps = 0;
			if (ps>256) ps = 256;
			m_percent[i] = ps;
		}
	}
}


