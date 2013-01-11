//
// maskwipe.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectmaskwipe.h"



CEffectMaskWipe::CEffectMaskWipe(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(4);
//	SetConstKosuu(2);
	Create("MaskWipe");
#endif
}


CEffectMaskWipe::~CEffectMaskWipe()
{
	End();
}


void CEffectMaskWipe::End(void)
{
}


BOOL CEffectMaskWipe::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	if (paraKosuu<3) return FALSE;	//bad!!

	EFFECT* lp = (EFFECT*)lpEffect;

	//éÌóﬁ,buffer,count

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
	if (paraKosuu<4) para[3] = 1;	//multi
	if (paraKosuu<5) para[4] = 0;	//type
	if (paraKosuu<6) para[5] = 0;	//subframe
	if (paraKosuu<7) para[6] = 0;	//srcgetFlag
	if (paraKosuu<8) para[7] = 0;	//dstgetFlag

	if (paraKosuu<9) para[8] = 100;	//last percent
	if (paraKosuu<10) para[9] = 0;	//start percent


	for (i=0;i<10;i++)
	{
		lp->para[i] = para[i];
	}

	lp->flag = TRUE;
	lp->count = 0;
	lp->countMax = para[0];

	lp->command = EFFECT_MASKWIPE;

	return TRUE;
}



BOOL CEffectMaskWipe::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectMaskWipe::BeginPrint(LPVOID para,int layer)
{
}


void CEffectMaskWipe::Init(LPVOID para,int layer)
{
}

void CEffectMaskWipe::Calcu(LPVOID lpEffect,int layer)
{
}

#if defined _TINYAN3DLIB_
void CEffectMaskWipe::Print(LPVOID lpEffect,int layer)
{
	//1.1ÇÕ2DÉãÅ[É`ÉìÇâûóp(íxÇ¢)



	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int count = lp->count;
	int countMax = lp->countMax;
	int type = lp->para[4];
	int subFrame = lp->para[5];

	if (countMax<1) countMax = 1;

	int startPercent = lp->para[9];
	int endPercent = lp->para[8];

	int c = CCalcuSpeed::calcu(count,countMax,startPercent,endPercent,subFrame,type);



	int multiData = lp->para[3];
	int minusWide = 256 * multiData;
	int wide = 256 + minusWide;

	int ml = (c * wide) / 100;
	if (ml<0) ml = 0;
	if (ml>wide) ml = wide;
	ml -= minusWide;

	int* work = m_allEffect->GetTempWork();
	for (int i=0;i<screenSizeX;i++)
	{
		int pl = (i*256) / screenSizeX;

		int d = pl * multiData;
		d += ml;
//		d -= minusWide;
		if (d<0) d = 0;
		if (d>255) d = 255;
		*(work+i) = (d<<16) | (d<<8) | d;
	}

	CMyDirect3D::SetWorkH(work,screenSizeX);
	SetTexture(CMyDirect3D::GetHTexture(),3);


	CPicture* lpPicStart =NULL;
	CPicture* lpPicEnd = NULL;

	RECT rc;
	RECT rc2;


	int* src = NULL;
	int* src2 = NULL;



	int pic1 = lp->pic;

	
	POINT startPoint0;
	if (lp->para[6])
	{
		CMyDirect3D::ExchangeScreenAndBuffer();
		SetTexture(CMyDirect3D::GetBufferTexture());
		SetRect(&rc,0,0,screenSizeX,screenSizeY);
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

		src = (int*)(lpPicStart->GetBuffer());
		CMyTexture* lpTexture = (CMyTexture*)(lpPicStart->GetTexture());
		if (lpTexture == NULL) return;
		SetTexture(lpTexture->GetTexture());
		startPoint0 = m_allEffect->GetDstPoint(layer);
	}


	POINT endPoint0;
	int pic2 = lp->para[1];
	if (lp->para[7])
	{
//		src2 = m_allEffect->GetGetBuffer();
		CMyDirect3D::ExchangeScreenAndBuffer();
		SetTexture(CMyDirect3D::GetBufferTexture(),1);
		SetRect(&rc2,0,0,screenSizeX,screenSizeY);
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

		src2 = (int*)(lpPicEnd->GetBuffer());
		CMyTexture* lpTexture = (CMyTexture*)(lpPicEnd->GetTexture());
		if (lpTexture == NULL) return;
		SetTexture(lpTexture->GetTexture(),1);

		endPoint0 = m_allEffect->GetDstPoint(pic2);
	}



	int pic3 = lp->para[2];
	if (pic3 == -1) return;


	if (src == NULL) return;
	if (src2 == NULL) return;



	CPicture* lpPicMask = m_allEffect->GetPicture(pic3);
	if (lpPicMask == NULL) return;
//	if (lpPicMask->CheckAntiMask() == FALSE) return;


	RECT rc3;
	lpPicMask->GetPicSize(&rc3);
	if (rc3.right < screenSizeX) return;
	if (rc3.bottom < screenSizeY) return;

	POINT maskPoint0 = m_allEffect->GetDstPoint(pic3);


	if (src == NULL) return;


//	char* mask = lpPicMask->GetAntiMask();
	int* mask = (int*)(lpPicMask->GetBuffer());

	if (mask == NULL) return;

	int* dst = CMyGraphics::GetScreenBuffer();

	if (1)
	{
		CMyTexture* lpTexture = (CMyTexture*)(lpPicMask->GetTexture());
		if (lpTexture == NULL) return;
		SetTexture(lpTexture->GetTexture(),2);
	}

	RECT rcStart;
//	RECT rcEnd;
//	RECT rcMask;

	rcStart = lp->dst;

//	rcEnd = m_effect->m_effect[pic2].dst;
//	rcMask = rcEnd;	//dummy

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

	return;
}
#else

void CEffectMaskWipe::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int count = lp->count;
	int countMax = lp->countMax;
	int type = lp->para[4];
	int subFrame = lp->para[5];

	if (countMax<1) countMax = 1;

	int startPercent = lp->para[9];
	int endPercent = lp->para[8];

	int c = CCalcuSpeed::calcu(count,countMax,startPercent,endPercent,subFrame,type);

//	int c = CCalcuSpeed::calcu(count,countMax,0,100,subFrame,type);



	int multiData = lp->para[3];
	int minusWide = 256 * multiData;
	int wide = 256 + minusWide;

	int ml = (c * wide) / 100;
	if (ml<0) ml = 0;
	if (ml>wide) ml = wide;
	ml -= minusWide;

	CPicture* lpPicStart =NULL;
	CPicture* lpPicEnd = NULL;

	RECT rc;
	RECT rc2;


	int* src = NULL;
	int* src2 = NULL;



//	int pic1 = lp->pic;
	int pic1 = layer;
static int aaa = 0;

	POINT startPoint0;
	if (lp->para[6])
	{
		src = m_allEffect->GetGetBuffer();
		SetRect(&rc,0,0,screenSizeX,screenSizeY);
		startPoint0.x = 0;
		startPoint0.y = 0;
	}
	else
	{
		if (pic1 != -1)
		{
			lpPicStart = m_allEffect->GetPicture(layer);
		}
		if (lpPicStart == NULL)
		{
			if (aaa == 0)
			{
				aaa = 1;
//				MessageBox(NULL,"1","1",MB_OK);
			}

			return;
		}

		lpPicStart->GetPicSize(&rc);

		if (rc.right < screenSizeX)
		{
			if (aaa == 0)
			{
				aaa = 1;
//				MessageBox(NULL,"2","2",MB_OK);
			}

			return;
		}

		if (rc.bottom < screenSizeY)
		{
			if (aaa == 0)
			{
				aaa = 1;
//				MessageBox(NULL,"3","3",MB_OK);
			}
			
			return;
		}

		src = (int*)(lpPicStart->GetBuffer());
		startPoint0 = m_allEffect->GetDstPoint(layer);
	}


	POINT endPoint0;
	int pic2 = lp->para[1];
	if (lp->para[7])
	{
		src2 = m_allEffect->GetGetBuffer();
		SetRect(&rc2,0,0,screenSizeX,screenSizeY);
		endPoint0.x = 0;
		endPoint0.y = 0;
	}
	else
	{
		if (pic2 != -1)
		{
			lpPicEnd = m_allEffect->GetPicture(pic2);
		}
		if (lpPicEnd == NULL)
		{
			if (aaa == 0)
			{
				aaa = 1;
//				MessageBox(NULL,"4","4",MB_OK);
			}

			return;
		}

		lpPicEnd->GetPicSize(&rc2);

		if (rc2.right < screenSizeX)
		{
			if (aaa == 0)
			{
				aaa = 1;
//				MessageBox(NULL,"5","5",MB_OK);
			}

			return;
		}

		if (rc2.bottom < screenSizeY)
		{
			if (aaa == 0)
			{
				aaa = 1;
//				MessageBox(NULL,"6","6",MB_OK);
			}

			return;
		}

		src2 = (int*)(lpPicEnd->GetBuffer());
		endPoint0 = m_allEffect->GetDstPoint(pic2);
	}



	int pic3 = lp->para[2];
	if (pic3 == -1)
	{
			if (aaa == 0)
			{
				aaa = 1;
//				MessageBox(NULL,"7","7",MB_OK);
			}

		return;
	}


	if (src == NULL)
	{
			if (aaa == 0)
			{
				aaa = 1;
//				MessageBox(NULL,"8","8",MB_OK);
			}

		return;
	}

	if (src2 == NULL)
	{
			if (aaa == 0)
			{
				aaa = 1;
//				MessageBox(NULL,"9","9",MB_OK);
			}

		return;
	}



	CPicture* lpPicMask = m_allEffect->GetPicture(pic3);
	if (lpPicMask == NULL)
	{
			if (aaa == 0)
			{
				aaa = 1;
//				MessageBox(NULL,"10","10",MB_OK);
			}

		return;
	}


//	if (lpPicMask->CheckAntiMask() == FALSE) return;


	RECT rc3;
	lpPicMask->GetPicSize(&rc3);
	if (rc3.right < screenSizeX)
	{
			if (aaa == 0)
			{
				aaa = 1;
//				MessageBox(NULL,"11","11",MB_OK);
			}

		return;
	}

	if (rc3.bottom < screenSizeY)
	{
			if (aaa == 0)
			{
				aaa = 1;
//				MessageBox(NULL,"12","12",MB_OK);
			}

		return;
	}

	POINT maskPoint0 = m_allEffect->GetDstPoint(pic3);


	if (src == NULL)
	{
			if (aaa == 0)
			{
				aaa = 1;
//				MessageBox(NULL,"13","13",MB_OK);
			}

		return;
	}


//	char* mask = lpPicMask->GetAntiMask();
	int* mask = (int*)(lpPicMask->GetBuffer());

	if (mask == NULL)
	{
			if (aaa == 0)
			{
				aaa = 1;
//				MessageBox(NULL,"14","14",MB_OK);
			}

		return;
	}

	int* dst = CMyGraphics::GetScreenBuffer();

	RECT rcStart;
//	RECT rcEnd;
//	RECT rcMask;

	rcStart = lp->dst;

//	rcEnd = m_effect->m_effect[pic2].dst;
//	rcMask = rcEnd;	//dummy

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

	src += startX;
	src += startY * rc.right;
	src2 += endX;
	src2 += endY * rc2.right;
	mask += maskX;
	mask += maskY * rc3.right;

//	POINT startPoint;
//	POINT endPoint;

//	startPoint.x = startX;
//	startPoint.y = startY;
//	endPoint.x = endX;
//	endPoint.y = endY;



	//ï\é¶


	int lPitchStart = rc.right * 4;
	int lPitchEnd = rc2.right * 4;
	int lPitchMask = rc3.right * 4;


	int loopX = screenSizeX;
	int loopY = screenSizeY;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi


		pxor mm0,mm0
		mov eax,ml
		movd mm7,eax
		punpcklwd mm7,mm7
		punpckldq mm7,mm7

		mov eax,0ff00ff00h
		movd mm6,eax
		punpckldq mm6,mm6

//		mov eax,01000100h
//		movd mm3,eax
//		punpckldq mm3,mm3

		mov eax,minusWide
		movd mm3,eax
		punpcklwd mm3,mm3
		punpckldq mm3,mm3


		mov ebx,src
		mov esi,src2
		mov edx,mask

		mov edi,dst
		mov ecx,loopY
LOOP1:
		push ecx

		push ebx
		push esi
		push edx


		mov ecx,loopX
LOOP2:
		push ecx

		mov eax,[edx]
		movd mm4,eax
		punpcklbw mm4,mm0

		mov eax,multiData
		cmp eax,1
		jz SKIP21

		movd mm1,eax
		punpcklwd mm1,mm1
		punpckldq mm1,mm1
		pmullw mm4,mm1

SKIP21:

		paddw mm4,mm7

//ïâÇÃêîÇÕ0Ç…Ç∑ÇÈ
		paddw mm4,mm3
		psubusw mm4,mm3

//ñOòaÇ…ÇÊÇ¡Çƒ256ÇÇ±Ç¶ÇƒÇÈÇÃÇ0-256Ç¢Ç»Ç¢Ç…Ç∑ÇÈ
		paddusw mm4,mm6
		psubusw mm4,mm6

		mov eax,01000100h
		movd mm5,eax
		punpckldq mm5,mm5
		psubw mm5,mm4

		mov eax,[ebx]
		movd mm1,eax
		punpcklbw mm1,mm0
		
		mov eax,[esi]
		movd mm2,eax
		punpcklbw mm2,mm0

		pmullw mm1,mm5
		pmullw mm2,mm4

		paddw mm1,mm2
		psrlw mm1,8
		packuswb mm1,mm0

		movd eax,mm1

		mov [edi],eax


		add ebx,4
		add esi,4
		add edx,4
		add edi,4

		pop ecx

		dec ecx
		jnz LOOP2

		pop edx
		pop esi
		pop ebx
		add edx,lPitchMask
		add esi,lPitchEnd
		add ebx,lPitchStart

		pop ecx
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
}
#endif


BOOL CEffectMaskWipe::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}



/*_*/

