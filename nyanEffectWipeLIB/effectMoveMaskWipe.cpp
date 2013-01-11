//
// maskwipe.cpp
//

#include "..\nyanEffectLib\includer.h"


#include "effectMovemaskwipe.h"



CEffectMoveMaskWipe::CEffectMoveMaskWipe(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(3);
	SetConstKosuu(3);
	Create("MoveMaskWipe");
#endif
}



CEffectMoveMaskWipe::~CEffectMoveMaskWipe()
{
	End();
}


void CEffectMoveMaskWipe::End(void)
{
}


BOOL CEffectMoveMaskWipe::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	if (paraKosuu<3) return FALSE;	//bad!!

	EFFECT* lp = (EFFECT*)lpEffect;

	//Ží—Þ,buffer,count

	int para[10];
	int k = paraKosuu;
	if (k>10) k = 10;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 12;	//buffer
	if (paraKosuu<3) para[2] = 13;	//mask

//	if (paraKosuu<4) para[3] = 1;	//multi

	if (paraKosuu<4) para[3] = 0;	//type
	if (paraKosuu<5) para[4] = 0;	//subframe
	if (paraKosuu<6) para[5] = 0;	//srcgetFlag
	if (paraKosuu<7) para[6] = 0;	//dstgetFlag
	if (paraKosuu<8) para[7] = 0;	//moveonly

	if (paraKosuu<9) para[8] = 100;	//last percent
	if (paraKosuu<10) para[9] = 0;	//start percent


	for (i=0;i<10;i++)
	{
		lp->para[i] = para[i];
	}

	lp->flag = TRUE;
	lp->count = 0;
	lp->countMax = para[0];

	lp->command = EFFECT_MOVEMASKWIPE;

	return TRUE;
}



BOOL CEffectMoveMaskWipe::CountIsMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	lp->count = lp->countMax;

	int buf = lp->para[1];
	if (buf != -1)
	{
//		lp->command = EFFECT_BUFFER;
//		m_allEffect->ChangeEffectCommandOnly(buf,EFFECT_NOP);
	}

	return TRUE;
}


void CEffectMoveMaskWipe::BeginPrint(LPVOID para,int layer)
{
}


void CEffectMoveMaskWipe::Init(LPVOID para,int layer)
{
}

void CEffectMoveMaskWipe::Calcu(LPVOID lpEffect,int layer)
{
}



void CEffectMoveMaskWipe::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int count = lp->count;
	int countMax = lp->countMax;
	int type = lp->para[3];
	int subFrame = lp->para[4];

	if (countMax<1) countMax = 1;

	int startPercent = lp->para[9];
	int endPercent = lp->para[8];
	startPercent *= 256*2;
	startPercent /= 100;
	endPercent *= 256*2;
	endPercent /= 100;

	int c = CCalcuSpeed::calcu(count,countMax,startPercent,endPercent,subFrame,type);

//	int c = CCalcuSpeed::calcu(count,countMax,0,256*2,subFrame,type);

	int alfa = c / 2;
	if (alfa<0) alfa = 0;
	if (alfa>256) alfa = 256;

	if (lp->para[7])
	{
		if (alfa<128)
		{
			alfa = 0;
		}
		else
		{
			alfa = 256;
		}
	}

	int multiData = c;
	if (multiData > 256) multiData = 512 - multiData;
	if (multiData<0) multiData = 0;
	if (multiData>256) multiData = 256;

	CPicture* lpPicStart =NULL;
	CPicture* lpPicEnd = NULL;

	RECT rc;
	RECT rc2;

	int* src = NULL;
	int* src2 = NULL;


//	int pic1 = lp->pic;
	int pic1 = layer;


	POINT startPoint0;
	if (lp->para[5])
	{
#if defined _TINYAN3DLIB_
		CMyDirect3D::CopyScreenToBuffer();
#else
		src = m_allEffect->GetGetBuffer();
		SetRect(&rc,0,0,screenSizeX,screenSizeY);

		if (c == 0)
		{
			m_allEffect->PutGetScreen();
			return;
		}
#endif



		startPoint0.x = 0;
		startPoint0.y = 0;

	}
	else
	{
		if (pic1 != -1)
		{
			lpPicStart = m_allEffect->GetPicture(layer);
		}
		if (lpPicStart == NULL) return;

		lpPicStart->GetPicSize(&rc);

		if (rc.right < screenSizeX) return;
		if (rc.bottom < screenSizeY) return;

		if (c == 0)
		{
			lpPicStart->Put(0,0,FALSE);
			return;
		}
		src = (int*)(lpPicStart->GetBuffer());
		startPoint0 = m_allEffect->GetDstPoint(layer);

	}

	POINT endPoint0;
	int pic2 = lp->para[1];
	if (lp->para[6])
	{
#if defined _TINYAN3DLIB_
		CMyDirect3D::CopyScreenToBuffer();
#else

		src2 = m_allEffect->GetGetBuffer();
		SetRect(&rc2,0,0,screenSizeX,screenSizeY);
		if (c >= 256*2)
		{
			m_allEffect->PutGetScreen();
			return;
		}
#endif

		endPoint0.x = 0;
		endPoint0.y = 0;
	}
	else
	{
		if (pic2 != -1)
		{
			lpPicEnd = m_allEffect->GetPicture(pic2);
		}
		if (lpPicEnd == NULL) return;
		lpPicEnd->GetPicSize(&rc2);

		if (rc2.right < screenSizeX) return;
		if (rc2.bottom < screenSizeY) return;

		if (c >= 256*2)
		{
			lpPicEnd->Put(0,0,FALSE);
			return;
		}
		src2 = (int*)(lpPicEnd->GetBuffer());
		endPoint0 = m_allEffect->GetDstPoint(pic2);

	}



	int pic3 = lp->para[2];
	if (pic3 == -1)
	{
		return;
	}

	POINT maskPoint0 = m_allEffect->GetDstPoint(pic3);

	if (src == NULL)
	{
		return;
	}

	if (src2 == NULL)
	{
		return;
	}


	//check

	CPicture* lpPicMask = m_allEffect->GetPicture(pic3);
	if (lpPicMask == NULL)
	{
		return;
	}
//	if (lpPicMask->CheckAntiMask() == FALSE) return;


	RECT rc3;
	lpPicMask->GetPicSize(&rc3);
	if (rc3.right < screenSizeX)
	{
		return;
	}

	if (rc3.bottom < screenSizeY)
	{
		return;

	}


	if (src == NULL)
	{
		return;
	}


//	char* mask = lpPicMask->GetAntiMask();
	int* mask = (int*)(lpPicMask->GetBuffer());

	if (mask == NULL)
	{
		return;
	}

	int* dst = CMyGraphics::GetScreenBuffer();

	RECT rcStart;

	rcStart = lp->dst;

	int startX = -startPoint0.x;
	int startY = -startPoint0.y;
	int endX = -endPoint0.x;
	int endY = -endPoint0.y;
	int maskX = -maskPoint0.x;
	int maskY = -maskPoint0.y;

	if (startX<0) startX = 0;
	if ((startX+screenSizeX) > rc.right) startX = rc.right - screenSizeX;
	if (startY<0) startY = 0;
	if ((startY+screenSizeY) > rc.bottom) startY = rc.bottom - screenSizeY;

	if (endX<0) endX = 0;
	if ((endX+screenSizeX) > rc2.right) endX = rc2.right - screenSizeX;
	if (endY<0) endY = 0;
	if ((endY+screenSizeY) > rc2.bottom) endY = rc2.bottom - screenSizeY;

	if (maskX<0) maskX = 0;
	if ((maskX+screenSizeX) > rc3.right) maskX = rc3.right - screenSizeX;
	if (maskY<0) maskY = 0;
	if ((maskY+screenSizeY) > rc3.bottom) maskY = rc3.bottom - screenSizeY;



#if defined _TINYAN3DLIB_

	if (CheckEffectError()) return;

	float a = (float)alfa;
	a /= 256.0f;
	SetConst(a);

	float m = (float)multiData;
//	m /= 256.0f;


	float px = m / (float)(screenSizeX);
	float py = m / (float)(screenSizeY);

	SetConst(px,1);
	SetConst(py,2);


	if (lp->para[5])
	{
		SetTexture(GetBufferTexture());
	}
	else
	{
		CMyTexture* lpTexture = (CMyTexture*)(lpPicStart->GetTexture());
		SetTexture(lpTexture->GetTexture());
	}

	if (lp->para[6])
	{
		SetTexture(GetBufferTexture(),1);
	}
	else
	{
		CMyTexture* lpTexture = (CMyTexture*)(lpPicEnd->GetTexture());
		SetTexture(lpTexture->GetTexture(),1);
	}

	if (1)
	{
		CMyTexture* lpTexture = (CMyTexture*)(lpPicMask->GetTexture());
		SetTexture(lpTexture->GetTexture(),2);
	}

	POINT dstPoint;
	dstPoint.x = 0;
	dstPoint.y = 0;
	SIZE dstSize;
	dstSize.cx = screenSizeX;
	dstSize.cy = screenSizeY;
	POINT srcPoint;
	srcPoint.x = startX;
	srcPoint.y = startY;
	POINT srcPoint2;
	srcPoint2.x = endX;
	srcPoint2.y = endY;

	Blt2(dstPoint,dstSize,srcPoint,srcPoint2);
#else

	src += startX;
	src += startY * rc.right;
	src2 += endX;
	src2 += endY * rc2.right;
	mask += maskX;
	mask += maskY * rc3.right;

//	int startX = 0;
//	int startY = 0;
//	int endX = 0;
//	int endY = 0;


	//–¢Žg—p
//	POINT startPoint;
//	POINT endPoint;

//	startPoint.x = startX;
//	startPoint.y = startY;
//	endPoint.x = endX;
//	endPoint.y = endY;


	//•\Ž¦


	int lPitchStart = rc.right * 4;
	int lPitchEnd = rc2.right * 4;
	int lPitchMask = rc3.right * 4;

	int lPitch = screenSizeX * sizeof(int);

	int loopX = screenSizeX;
	int loopY = screenSizeY;

	int yZahyo = 0;


	__int64 alfa64;
	__int64 alfa64m;
	__int64 multiData64;
	__int64 src1src2;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi


		pxor mm0,mm0
		
		mov eax,alfa
		shr eax,1
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6
		movq alfa64m,mm6

		neg eax
		add eax,128
		movd mm7,eax
		punpcklwd mm7,mm7
		punpckldq mm7,mm7
		movq alfa64,mm7

		mov eax,multiData
		movd mm5,eax
		punpcklwd mm5,mm5
		punpckldq mm5,mm5
		movq multiData64,mm5



		mov eax,128
		movd mm4,eax
		punpcklwd mm4,mm4
		punpckldq mm4,mm4

		mov eax,0ffffh
		movd mm5,eax
		punpcklwd mm5,mm5
		
		mov eax,loopX
		dec eax
		movd mm1,eax
		psubw mm5,mm1

		mov eax,loopY
		dec eax
		movd mm1,eax
		pslld mm1,16
		psubw mm5,mm1


		mov eax,lPitchEnd
		shl eax,16
		add eax,4
		movd mm6,eax
		psllq mm6,32

		mov eax,lPitchStart
		shl eax,16
		add eax,4
		movd mm1,eax
		paddd mm6,mm1


		mov eax,src
		movd mm1,eax

		mov eax,src2
		movd mm2,eax
		psllq mm2,32

		por mm1,mm2
		movq src1src2,mm1


		mov eax,256
		movd mm7,eax
		punpcklwd mm7,mm7


		mov ebx,mask
		mov edi,dst

		pxor mm3,mm3
		mov ecx,loopY
LOOP1:
		push ecx
		push ebx
		push edi

		mov ecx,loopX
LOOP2:
		mov eax,[ebx]
		movd mm1,eax
		movq mm2,multiData64
		punpcklbw mm1,mm0
		psubw mm1,mm4
		pmullw mm1,mm2
		
		psraw mm1,8
		paddw mm1,mm3

		paddw mm1,mm7
		psubusw mm1,mm7

		paddusw mm1,mm5
		psubusw mm1,mm5


		punpckldq mm1,mm1
		pmaddwd mm1,mm6

		paddd mm1,src1src2

		movd eax,mm1
		psrlq mm1,32
		movd esi,mm1

		mov eax,[eax]
		movd mm1,eax
		punpcklbw mm1,mm0

		mov eax,[esi]
		movd mm2,eax
		punpcklbw mm2,mm0

		pmullw mm1,alfa64
		pmullw mm2,alfa64m
		//stall
		psrlw mm1,7
		psrlw mm2,7
		paddw mm1,mm2
		packuswb mm1,mm1
		movd eax,mm1

		mov [edi],eax

		movd eax,mm3
		inc eax
		movd mm3,eax

		add ebx,4
		add edi,4
		dec ecx
		jnz LOOP2


		movd eax,mm3
		and eax,0ffff0000h
		add eax,10000h
		movd mm3,eax
		
		pop edi
		pop ebx
		pop ecx

		add edi,lPitch
		add ebx,lPitchMask
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



BOOL CEffectMoveMaskWipe::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


/*_*/

