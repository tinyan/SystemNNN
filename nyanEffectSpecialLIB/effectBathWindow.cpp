//
// effectBathWindow.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectBathWindow.h"


CEffectBathWindow::CEffectBathWindow(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	m_lastEraseX = -1;
	m_lastEraseY = -1;

	m_yuge0 = new char[32*32 * 4 + 8];
	int pt = (int)m_yuge0;
	pt += 7;
	pt &= (~7);
	m_yuge = (char*)pt;
	ZeroMemory(m_yuge,32*32*4);

	m_kesu0 = new char[128*128 * 2 + 8];
	pt = (int)m_kesu0;
	pt += 7;
	pt &= (~7);
	m_kesu = (char*)pt;
	ZeroMemory(m_kesu,128*128*2);




	//ゆげ用データ作成
	char* ptr = m_yuge;
	int k;
	for (k=0;k<4;k++)
	{
		for (int j=-16;j<16;j++)
		{
			for (int i=-16;i<16;i++)
			{
				int r2 = i*i + j*j;
				double r = sqrt((double)r2);

				int d = 8 - (int)r;
				d += 1;
				d += (rand() % 8);
				if (d<1) d = 1;

				*ptr = d;
				ptr++;
			}
		}
	}


//けし用データ作成
	ptr = m_kesu;
	for (k=0;k<2;k++)
	{
		for (int j=-64;j<64;j++)
		{
			for (int i=-64;i<64;i++)
			{
				int r2 = i*i + j*j;
				double r = sqrt((double)r2);

				int ps = 64 - (int)r;
				if (ps<0) ps = 0;

				int d = 20;
				d += (rand() % 32);
				d *= ps;
				d /= 64;


				*ptr = d;
				ptr++;
			}
		}
	}






}


CEffectBathWindow::~CEffectBathWindow()
{
	End();
}

void CEffectBathWindow::End(void)
{
	DELETEARRAY(m_yuge0);
	DELETEARRAY(m_kesu0);
}

BOOL CEffectBathWindow::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int para[9];
	int k = paraKosuu;
	if (k>9) k = 9;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}
	if (paraKosuu<1) para[0] = 20;	//dummy frame
	if (paraKosuu<2) para[1] = 20;			//size max64
	if (paraKosuu<3) para[2] = 1;		//けし度合い???
	if (paraKosuu<4) para[3] = 5;		//復活スピード max 32

	if (para[1]<8) para[1] = 8;
	if (para[1]>64) para[1] = 128;

	para[2] = 1;

	if (para[3]<0) para[3] = 0;
	if (para[3]>32) para[3] = 32;


	if (paraKosuu<5) para[4] = 0;
	if (paraKosuu<6) para[5] = 0;
	if (paraKosuu<7) para[6] = screenSizeX;
	if (paraKosuu<8) para[7] = screenSizeY;
	if (paraKosuu<9) para[8] = 0;

	if (para[4]<0) para[4] = 0;
	if (para[4]>=screenSizeX) para[4] = screenSizeX-1;
	if (para[5]<0) para[5] = 0;
	if (para[5]>=screenSizeY) para[5] = screenSizeY-1;

	if (para[6]<1) para[6] = 1;
	if (para[6]>screenSizeX) para[6] = screenSizeX;
	if (para[7]<1) para[7] = 1;
	if (para[7]>screenSizeY) para[7] = screenSizeY;

		
	//	m_r = para[0];
//	m_g = para[1];
//	m_b = para[2];


	lp->flag = TRUE;
	for (i=0;i<9;i++)
	{
		lp->para[i] = para[i];
	}


	lp->count = 0;
	lp->countMax = 9999;
	lp->command = EFFECT_BATHWINDOW;

	return TRUE;
}


BOOL CEffectBathWindow::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectBathWindow::BeginPrint(LPVOID para,int layer)
{

}

void CEffectBathWindow::Init(LPVOID para,int layer)
{
}

void CEffectBathWindow::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	lp->count = 0;

//	POINT pt = m_effect->GetMouseZahyo();
	POINT pt = m_allEffect->GetMouseZahyo();
	int mouseX = pt.x;
	int mouseY = pt.y;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;
	if (lpPic->CheckMaskExist() == FALSE) return;

	if (lp->para[8])
	{
		lpPic->Flush();
	}

	char* maskPtr = lpPic->GetMaskPic();
	RECT rc;
	lpPic->GetPicSize(&rc);

	int picSizeX = rc.right;
	int picSizeY = rc.bottom;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int dstPitch = picSizeX;

	//ゆげ



	int yugeParam[32*6];
	int kosuu = lp->para[3];


	int blockX = picSizeX / 8;
	if (blockX<1) blockX = 1;

	for (int i=0;i<kosuu;i++)
	{
		int x = rand() % (blockX);
		int y = rand() % (picSizeY);
		int yugeSizeX = 4;
		int yugeSizeY = 32;
		int yugeSrcX = 0;
		int yugeSrcY = 0;

		x -= 2;
		y -= 16;
		if (x<0)
		{
			yugeSizeX -= (-x);
			yugeSrcX += (-x);
			x = 0;
			if (yugeSizeX<0) yugeSizeX = 0;
		}
		if ((x+yugeSizeX) > blockX)
		{
			yugeSizeX -= ( x+yugeSizeX-blockX);
			x = blockX - yugeSizeX;
		}
		if (yugeSizeX<0) yugeSizeX = 0;

		if (y<0)
		{
			yugeSizeY -= (-y);
			yugeSrcY += (-y);
			y = 0;
			if (yugeSizeY<0) yugeSizeY = 0;
		}

		if ((y+yugeSizeY) > picSizeY)
		{
			yugeSizeY -= (y+yugeSizeY-picSizeY);
			y = picSizeY - yugeSizeY;
		}
		if (yugeSizeY<0) yugeSizeY = 0;
		if (yugeSizeX==0) yugeSizeY = 0;
		if (yugeSizeY==0) yugeSizeX = 0;

		yugeSrcX *= 8;
		x *= 8;

		yugeParam[i*6+0] = yugeSizeX;
		yugeParam[i*6+1] = yugeSizeY;
		yugeParam[i*6+2] = x;
		yugeParam[i*6+3] = y;
		yugeParam[i*6+4] = yugeSrcX;
		yugeParam[i*6+5] = yugeSrcY;



//		char* yugePtr = maskPtr;
//		yugePtr += x;
//		yugePtr += y * picSizeX;
//
//		m_yugeAppear[i] = yugePtr;
	}


	char* yugePtr = maskPtr;
	char* src = &m_yuge[0];
	int* tbl2 = yugeParam;

	int yugePat = rand() % 4;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		pxor mm0,mm0
		mov edx,kosuu
		or edx,edx
		jz EXIT1
		mov ebx,tbl2
		mov eax,yugePat
LOOP1:
		push eax
		push ebx
		push edx

		shl eax,10
		mov esi,src
		add esi,eax


		mov ecx,[ebx+0]	//からよみ
		mov ecx,[ebx+4]
		or ecx,ecx
		jz SKIP2


		mov edi,yugePtr
		add edi,[ebx+8]
		
		mov eax,[ebx+12]
		mov edx,picSizeX
		mul edx
		add edi,eax

		mov eax,[ebx+16]
		add esi,eax
		mov eax,[ebx+20]
		shl eax,5
		add esi,eax

LOOP2:
		push ecx
		push esi
		push edi
		mov ecx,[ebx+0]
LOOP3:
		movq mm1,[esi]
		movq mm2,[edi]
		paddusb mm2,mm1
		movq [edi],mm2
		add esi,8
		add edi,8
		dec ecx
		jnz LOOP3

		pop edi
		pop esi
		pop ecx
		add edi,dstPitch
		add esi,32
		dec ecx
		jnz LOOP2

SKIP2:
		pop edx
		pop ebx
		pop eax
		inc eax
		and eax,3
		add ebx,4*6
		dec edx
		jnz LOOP1

EXIT1:		
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
		emms
	}


/*
	int kosuu = lp->para[3];
	for (int i=0;i<kosuu;i++)
	{
		int x = rand() % (picSizeX - 32 + 7);
		int y = rand() % (picSizeY - 32);

		x &= (~7);
		if ((x+32) > picSizeX)
		{
			x = picSizeX - 32;
			x &= (~7);
		}

		char* yugePtr = maskPtr;
		yugePtr += x;
		yugePtr += y * picSizeX;

		m_yugeAppear[i] = yugePtr;
	}



	char** tbl = m_yugeAppear;
	char* src = &m_yuge[0];

	int yugePat = rand() % 4;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		pxor mm0,mm0
		mov edx,kosuu
		or edx,edx
		jz EXIT1
		mov ebx,tbl
		mov eax,yugePat
LOOP1:
		push eax
		push ebx
		push edx

		shl eax,10
		mov esi,src
		add esi,eax

		mov edi,[ebx]

		mov edx,32
LOOP2:
		push edi
		mov ecx,4
LOOP3:
		movq mm1,[esi]
		movq mm2,[edi]
		paddusb mm2,mm1
		movq [edi],mm2
		add esi,8
		add edi,8
		dec ecx
		jnz LOOP3

		pop edi
		add edi,dstPitch
		dec edx
		jnz LOOP2

		pop edx
		pop ebx
		pop eax
		inc eax
		and eax,3
		add ebx,4
		dec edx
		jnz LOOP1

EXIT1:		
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
		emms
	}
*/



	//けす
	int srcPitch = 128;
	BOOL dontErase = FALSE;
	if ((mouseX == m_lastEraseX) && (mouseY == m_lastEraseY)) dontErase = TRUE;
	if ((mouseX<0) || (mouseY<0) || (mouseX>=screenSizeX) || (mouseY>=screenSizeY)) dontErase = TRUE;

	m_lastEraseX = mouseX;
	m_lastEraseY = mouseY;

	int sizeX = lp->para[1];
	int sizeY = lp->para[1];

	int startX = mouseX - sizeX / 2;
	int startY = mouseY - sizeY / 2;

	int endX = mouseX + sizeX / 2;
	int endY = mouseY + sizeY / 2;

	int kesuSrcX = 0;
	int kesuSrcY = 0;

	int kesuSizeX = endX - startX;
	int kesuSizeY = endY - startY;

	int kesuDivX = kesuSizeX;
	int kesuDivY = kesuSizeY;

	if (startX<0)
	{
		kesuSizeX -= (-startX);
		kesuSrcX += (-startX);
		startX = 0;
		if (kesuSizeX<0) kesuSizeX = 0;
	}
	if ((startX+kesuSizeX) > picSizeX)
	{
		kesuSizeX -= (startX+kesuSizeX-picSizeX);
	}


	if (startY<0)
	{
		kesuSizeY -= (-startY);
		kesuSrcY += (-startY);
		startY = 0;
		if (kesuSizeY < 0) kesuSizeY = 0;
	}
	if ((startY+kesuSizeY) > picSizeY)
	{
		kesuSizeY -= (startY+kesuSizeY-picSizeY);
	}


	if (dontErase == FALSE)
	{
		if ((kesuSizeX > 0) && (kesuSizeX > 0))
		{
			int kesuPat = rand() % 2;
			unsigned char* src2 = (unsigned char*)(&m_kesu[kesuPat * 128*128]);

			for (int j=0;j<kesuSizeY;j++)
			{
				unsigned char* kesuDst = (unsigned char*)maskPtr;
				kesuDst += (startY+j) * picSizeX;
				kesuDst += startX;

				unsigned char* kesuSrc0 = src2 + (((kesuSrcY + j)*128) / kesuDivY) * 128;

				for (int i=0;i<kesuSizeX;i++)
				{
					unsigned char* kesuSrc = kesuSrc0 + ((kesuSrcX + i)*128) / kesuDivX;

					unsigned char minusData = *kesuSrc;

					unsigned char targetData = *kesuDst;

					if (minusData > targetData)
					{
						targetData = 0;
					}
					else
					{
						targetData -= minusData;
					}

					*kesuDst = targetData;

					kesuDst++;
				}
			}
		}
	}









/*
	//けす
	int srcPitch = 128;

	BOOL dontErase = FALSE;

	if ((mouseX == m_lastEraseX) && (mouseY == m_lastEraseY)) dontErase = TRUE;

	if ((mouseX<0) || (mouseY<0) || (mouseX>=screenSizeX) || (mouseY>=screenSizeY)) dontErase = TRUE;


	m_lastEraseX = mouseX;
	m_lastEraseY = mouseY;

	int sizeX = lp->para[1];
	int sizeY = lp->para[1];

	int startX = mouseX - sizeX / 2;
	int startY = mouseY - sizeY / 2;

	int endX = mouseX + sizeX / 2;
	int endY = mouseY + sizeY / 2;

	startX &= (~7);
	endX += 7;
	endX &= (~7);

	if (startX<0)
	{
		startX = 0;
	}


	if (startY<0) startY = 0;
	if (endX>screenSizeX) endX = screenSizeX;
	if (endY>screenSizeY) endY = screenSizeY;

	int loopX = endX - startX;
	int loopY = endY - startY;
	if ((loopX<1) || (loopY<1)) dontErase = TRUE;

	if (loopX > 128)
	{
		loopX = 128;
		endX = startX + loopX;
	}


	loopX /= 8;
	int deltaX = (16 - loopX) / 2;
	int deltaY = (128 - loopY) / 2;

	if ((loopX<1) || (loopY<1)) dontErase = TRUE;

	int kesuPat = rand() % 2;
	char* src2 = &m_kesu[kesuPat * 64*64];
	char* dst2 = maskPtr;
	dst2 += startX;
	dst2 += startY * picSizeX;


	src2 += deltaX * 8;
	src2 += deltaY * 128;









	if (dontErase == FALSE)
	{
		__asm
		{
			push eax
			push ebx
			push ecx
			push edx
			push esi
			push edi

			pxor mm0,mm0
			mov esi,src2
			mov edi,dst2


			mov edx,loopY
	LOOP201:
			push esi
			push edi

			mov ecx,loopX
	LOOP202:
			movq mm1,[esi]
			movq mm2,[edi]
			psubusb mm2,mm1
			movq [edi],mm2

			add esi,8
			add edi,8
			dec ecx
			jnz LOOP202

			pop edi
			pop esi
			add edi,dstPitch
			add esi,srcPitch
			dec edx
			jnz LOOP201

			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax
			emms
		}
	}
*/



#if defined _TINYAN3DLIB_
	CMyTexture* lpTexture = (CMyTexture*)(lpPic->GetTexture());

	//mask to pic gousei
	MaskMergeToScreen(lpPic);

	lpTexture->CreateTexture(lpPic->GetBuffer());
#endif

}


void CEffectBathWindow::Print(LPVOID lpEffect,int layer)
{
	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	EFFECT* lp = (EFFECT*)lpEffect;

	int putX = lp->para[4];
	int putY = lp->para[5];
	int sizeX = lp->para[6];
	int sizeY = lp->para[7];


	lpPic->Blt(putX,putY,putX,putY,sizeX,sizeY,TRUE);

	//lpPic->Put(0,0,TRUE);
}


BOOL CEffectBathWindow::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectBathWindow::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}

void CEffectBathWindow::MaskMergeToScreen(CPicture* lpPic)
{
//mask to pic or fill 255
	int* srcPtr = (int*)(lpPic->GetBuffer());
	srcPtr += 128 / sizeof(int);

	SIZE sz = lpPic->GetPicSize();
	int picSizeX = sz.cx;
	int picSizeY = sz.cy;

	int loopMMX = picSizeX * picSizeY / 4;
	int loopAmari = (picSizeX * picSizeY) & 3;

	char* maskPtr = lpPic->GetMaskPic();
	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		pxor mm0,mm0

		mov esi,srcPtr
		mov ebx,maskPtr

		mov ecx,loopMMX
		or ecx,ecx
		jz SKIP1M

		mov eax,0ffffffh
		movd mm7,eax
		punpckldq mm7,mm7


LOOP1M:
		movq mm1,[esi]
		movq mm2,[esi+8]
		pand mm1,mm7
		pand mm2,mm7

		mov eax,[ebx]
		movd mm3,eax
		punpcklbw mm3,mm0
		movq mm4,mm3
		punpcklwd mm3,mm0
		punpckhwd mm4,mm0
		pslld mm3,24
		pslld mm4,24
		por mm1,mm3
		por mm2,mm4
		movq [esi],mm1
		movq [esi+8],mm2
		add esi,16
		add ebx,4
		dec ecx
		jnz LOOP1M


SKIP1M:
		mov ecx,loopAmari
		or ecx,ecx
		jz SKIP2M


LOOP2M:
		mov edx,[esi]
		xor eax,eax
		mov al,[ebx]
		shl eax,24
		or edx,eax
		mov [esi],edx
		add esi,4
		add ebx,1
		dec ecx
		jnz LOOP2M

SKIP2M:


		emms
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}

}
