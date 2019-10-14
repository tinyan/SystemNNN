#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "stretchAddSubBlt.h"

CStretchAddSubBlt::CStretchAddSubBlt()
{
}

CStretchAddSubBlt::~CStretchAddSubBlt()
{
}

void CStretchAddSubBlt::End(void)
{
}


void CStretchAddSubBlt::Print(POINT dstPoint,POINT srcPoint,SIZE dstSize,SIZE srcSize,LPVOID picData,LPVOID maskData,SIZE picSize,BOOL bTransFlag,int transPercent,int deltaR,int deltaG,int deltaB)
{
	int dstSizeX = dstSize.cx;
	int dstSizeY = dstSize.cy;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();
	int* dst = CMyGraphics::GetScreenBuffer();

	int transFlag = 2;
	if (bTransFlag == FALSE) transFlag = 0;

	int picSizeX = picSize.cx;
	int picSizeY = picSize.cy;

	if (picSizeX<=0) return;
	if (picSizeY<=0) return;

	int srcX = srcPoint.x;
	int srcY = srcPoint.y;

	if (srcX<0) return;
	if (srcY<0) return;
	if (srcX >= picSizeX) return;
	if (srcY >= picSizeY) return;

	int srcSizeX = srcSize.cx;
	int srcSizeY = srcSize.cy;

	if (srcSizeX == 0) return;
	if (srcSizeY == 0) return;


	if (srcSizeX>0)
	{
		if ((srcX+srcSizeX) > picSizeX) return;
	}
	if (srcSizeX<0)
	{
		if ((srcX+srcSizeX) <0) return;
	}


	if (srcSizeY>0)
	{
		if ((srcY+srcSizeY) > picSizeY) return;
	}
	if (srcSizeY<0)
	{
		if ((srcY+srcSizeY) <0) return;
	}


	int* src = (int*)picData;
	if (src == NULL) return;

	char* mask = (char*)maskData;

	int sizeX = dstSize.cx;
	int sizeY = dstSize.cy;

	if (sizeX<=0) return;
	if (sizeY<=0) return;

	int putX = dstPoint.x;
	int putY = dstPoint.y;

	int putStartX = putX;
	int putStartY = putY;
	int putEndX = putX + sizeX;
	int putEndY = putY + sizeY;

	int putDeltaX = 0;
	int putDeltaY = 0;

	if (putStartX<0)
	{
		putDeltaX = -putStartX;
		putStartX = 0;
		sizeX -= putDeltaX;
		if (sizeX<=0) return;
	}

	if (putStartY<0)
	{
		putDeltaY = -putStartY;
		putStartY = 0;
		sizeY -= putDeltaY;
		if (sizeY<=0) return;
	}

	if (putEndX > screenSizeX)
	{
		sizeX -= (putEndX - screenSizeX);
		putEndX = screenSizeX;
		if (sizeX<=0) return;
	}

	if (putEndY > screenSizeY)
	{
		sizeY -= (putEndY - screenSizeY);
		putEndY = screenSizeY;
		if (sizeY <= 0) return;
	}

	int loopX = putEndX - putStartX;
	int loopY = putEndY - putStartY;

	if (loopX <= 0) return;
	if (loopY <= 0) return;


	double ddx = (double)srcSizeX;
	ddx /= (double)dstSizeX;

	double ddy = (double)srcSizeY;
	ddy /= (double)dstSizeY;

	double ml = 65536.0;

	int ddxInt = (int)ddx;
	int ddxAmari = 0;
	if (ddx>=0)
	{
		ddxAmari = (int)((ddx - ddxInt) * ml);
	}
	else
	{
		ddxInt--;
		ddxAmari = (int)((ddx - ddxInt) * ml);
	}


	int ddyInt = (int)ddy;
	int ddyAmari = 0;
	if (ddy >= 0)
	{
		ddyAmari = (int)((ddy - ddyInt) * ml);
	}
	else
	{
		ddyInt--;
		ddyAmari = (int)((ddy - ddyInt) * ml);
	}



	double skipX = ddx * putDeltaX;
	double skipY = ddy * putDeltaY;


	int tmpXInt = (int)skipX;
	int tmpXAmari = 0;
	if (skipX>=0)
	{
		tmpXAmari = (int)((skipX - tmpXInt) * ml);
	}
	else
	{
		tmpXInt--;
		tmpXAmari = (int)((skipX - tmpXInt) * ml);
	}


	int tmpYInt = (int)skipY;
	int tmpYAmari = 0;
	if (skipY>=0)
	{
		tmpYAmari = (int)((skipY - tmpYInt) * ml);
	}
	else
	{
		tmpYInt--;
		tmpYAmari = (int)((skipY - tmpYInt) * ml);
	}


	tmpXInt += srcX;
	tmpYInt += srcY;



	int lPitch = screenSizeX * 4;
//	int maskPitch = picSizeX;


	int trans = *src;

	if (transFlag == 2)
	{
//		if (mask == NULL) transFlag = 1;
	//	if (CheckAntiMask() == FALSE) transFlag = 1;
		if (maskData == NULL) transFlag = 1;
	}


//	int ps1 = lp->para[10];
//	int ps2 = lp->para[9];

//	int ps = ps1 + ((ps2 - ps1) * c ) / dv;

	int ps = transPercent;
	int ps256 = (ps * 256) / 100;

	if (transFlag == 2)
	{
		if (ps != 100)
		{
			transFlag = 3;//マスク有り半透明
		}
	}

	if (transFlag == 1)
	{
		if (ps != 100)
		{
			transFlag = 4;	//ぬきあり半透明
		}
	}


	if (transFlag == 0)
	{
		if (ps != 100)
		{
//			transFlag = 5;	//ぬきなし半透明
		}
	}








	if (loopX<1) return;
	if (loopY<1) return;

	int addColorR = deltaR;
	int addColorG = deltaG;
	int addColorB = deltaB;

	int subColorR = -deltaR;
	int subColorG = -deltaG;
	int subColorB = -deltaB;

	if (addColorR<0) addColorR = 0;
	if (addColorG<0) addColorG = 0;
	if (addColorB<0) addColorB = 0;
	if (subColorR<0) subColorR = 0;
	if (subColorG<0) subColorG = 0;
	if (subColorB<0) subColorB = 0;

	int addColor = (addColorR << 16) | (addColorG << 8) | addColorB;
	int subColor = (subColorR << 16) | (subColorG << 8) | subColorB;
	LONGLONG addColor64 = (LONGLONG)addColor;
	LONGLONG subColor64 = (LONGLONG)subColor;

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



		mov eax,tmpXAmari
		and eax,0ffffh
		mov ebx,tmpXInt
		shl ebx,16
		or eax,ebx
		movd mm0,eax

		psllq mm0,32

		mov eax,tmpYAmari
		and eax,0ffffh
		mov ebx,tmpYInt
		shl ebx,16
		or eax,ebx
		movd mm7,eax

		por mm0,mm7





		mov eax,ddxAmari
		and eax,0ffffh
		mov ebx,ddxInt
		shl ebx,16
		or eax,ebx
		movd mm2,eax

		psllq mm2,32

		mov eax,0
		and eax,0ffffh
		mov ebx,0
		shl ebx,16
		or eax,ebx
		movd mm7,eax

		por mm2,mm7




		mov eax,0
		and eax,0ffffh
		mov ebx,0
		shl ebx,16
		or eax,ebx
		movd mm3,eax

		psllq mm3,32

		mov eax,ddyAmari
		and eax,0ffffh
		mov ebx,ddyInt
		shl ebx,16
		or eax,ebx
		movd mm7,eax

		por mm3,mm7



//		mov esi,src


		mov edi,dst



		mov eax,putStartY
		mov edx,lPitch
		mul edx
		add edi,eax

		mov eax,putStartX
		shl eax,2
		add edi,eax





		mov ecx,loopY

		mov eax,transFlag
		cmp eax,0
		jz MODE0
		cmp eax,1
		jz MODE1
		cmp eax,2
		jz MODE2
		cmp eax,3
		jz MODE3
		jmp MODE4

MODE0:
LOOP1:
		push ecx
		push edi

		movq mm1,mm0


		movq mm6,mm1
		psrad mm6,16
		movd eax,mm6
		cmp eax,picSizeY
		jnb SKIP2
		mov edx,picSizeX
		mul edx
		shl eax,2
		add eax,src
		mov esi,eax

		mov ecx,loopX
LOOP2:
		movq mm7,mm1
		psrlq mm7,48

		movd ebx,mm7

		cmp ebx,picSizeX
		jnb SKIP1
//表示?
		shl ebx,2
		mov eax,[ebx+esi]

		movd mm4,eax
		paddusb mm4,addColor64
		psubusb mm4,subColor64
		movd eax,mm4

		mov [edi],eax

SKIP1:
		paddd mm1,mm2

		add edi,4
		dec ecx
		jnz LOOP2
SKIP2:
		paddd mm0,mm3


		pop edi
		pop ecx
		add edi,lPitch
		dec ecx
		jnz LOOP1

		jmp EXIT1




MODE1:
LOOP11:
		push ecx
		push edi

		movq mm1,mm0


		movq mm6,mm1
		psrad mm6,16
		movd eax,mm6
		cmp eax,picSizeY
		jnb SKIP12
		mov edx,picSizeX
		mul edx
		shl eax,2
		add eax,src
		mov esi,eax


		mov ecx,loopX
LOOP12:
		movq mm7,mm1
		psrlq mm7,48

		movd ebx,mm7

		cmp ebx,picSizeX
		jnb SKIP11
//表示?
		shl ebx,2
		mov eax,[ebx+esi]
		cmp eax,trans
		jz SKIP11

		movd mm4,eax
		paddusb mm4,addColor64
		psubusb mm4,subColor64
		movd eax,mm4

		mov [edi],eax

SKIP11:
		paddd mm1,mm2

		add edi,4
		dec ecx
		jnz LOOP12
SKIP12:
		paddd mm0,mm3

		pop edi
		pop ecx
		add edi,lPitch
		dec ecx
		jnz LOOP11

		jmp EXIT1


MODE2:

LOOP21:
		push ecx
		push edi

		movq mm1,mm0


		movq mm6,mm1
		psrad mm6,16
		movd eax,mm6
		cmp eax,picSizeY
		jnb SKIP22
		mov edx,picSizeX
		mul edx
		shl eax,2
		add eax,src
		mov esi,eax


		movd eax,mm6
		mov edx,picSizeX
		mul edx
		add eax,mask
		mov edx,eax

		mov ecx,loopX
LOOP22:
		movq mm7,mm1
		psrlq mm7,48

		movd ebx,mm7

		cmp ebx,picSizeX
		jnb SKIP21
//表示?
		xor eax,eax
		mov al,[ebx+edx]
		shl ebx,2
		or eax,eax
		jz SKIP21
		cmp eax,0ffh
		jz NORMAL2
//半透明
		movd mm7,eax
		punpcklwd mm7,mm7
		xor al,0ffh
		punpckldq mm7,mm7
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6


		mov eax,[ebx+esi]
		movd mm4,eax
		paddusb mm4,addColor64
		psubusb mm4,subColor64
		movd eax,mm4

		pxor mm4,mm4
		movd mm5,eax

		punpcklbw mm5,mm4
		pmullw mm7,mm5

		mov eax,[edi]
		movd mm5,eax
		punpcklbw mm5,mm4

		pmullw mm6,mm5

		psrlw mm7,8
		psrlw mm6,8
		paddw mm7,mm6
		packuswb mm7,mm4

		movd eax,mm7
		mov [edi],eax
		jmp SKIP21

NORMAL2:
		mov eax,[ebx+esi]
		movd mm4,eax
		paddusb mm4,addColor64
		psubusb mm4,subColor64
		movd eax,mm4

		mov [edi],eax


SKIP21:
		paddd mm1,mm2

		add edi,4
		dec ecx
		jnz LOOP22
SKIP22:

		paddd mm0,mm3


		pop edi
		pop ecx
		add edi,lPitch
		dec ecx
		jnz LOOP21

		jmp EXIT1


MODE3:

LOOP31:
		push ecx
		push edi

		movq mm1,mm0


		movq mm6,mm1
		psrad mm6,16
		movd eax,mm6
		cmp eax,picSizeY
		jnb SKIP32
		mov edx,picSizeX
		mul edx
		shl eax,2
		add eax,src
		mov esi,eax


		movd eax,mm6
		mov edx,picSizeX
		mul edx
		add eax,mask
		mov edx,eax

		mov ecx,loopX
LOOP32:
		movq mm7,mm1
		psrlq mm7,48

		movd ebx,mm7

		cmp ebx,picSizeX
		jnb SKIP31
//表示?
		xor eax,eax
		mov al,[ebx+edx]
		shl ebx,2
		or eax,eax
		jz SKIP31

		push edx
		mov edx,ps256
		mul edx
		pop edx
		shr eax,8

//半透明
		movd mm7,eax
		punpcklwd mm7,mm7
		xor al,0ffh
		punpckldq mm7,mm7
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6


		mov eax,[ebx+esi]
		movd mm4,eax
		paddusb mm4,addColor64
		psubusb mm4,subColor64
		movd eax,mm4

		pxor mm4,mm4
		movd mm5,eax

		punpcklbw mm5,mm4
		pmullw mm7,mm5

		mov eax,[edi]
		movd mm5,eax
		punpcklbw mm5,mm4

		pmullw mm6,mm5

		psrlw mm7,8
		psrlw mm6,8
		paddw mm7,mm6
		packuswb mm7,mm4

		movd eax,mm7
		mov [edi],eax

SKIP31:
		paddd mm1,mm2

		add edi,4
		dec ecx
		jnz LOOP32
SKIP32:

		paddd mm0,mm3


		pop edi
		pop ecx
		add edi,lPitch
		dec ecx
		jnz LOOP31

		jmp EXIT1



MODE4:

LOOP41:
		push ecx
		push edi

		movq mm1,mm0


		movq mm6,mm1
		psrad mm6,16
		movd eax,mm6
		cmp eax,picSizeY
		jnb SKIP42
		mov edx,picSizeX
		mul edx
		shl eax,2
		add eax,src
		mov esi,eax


		movd eax,mm6
		mov edx,picSizeX
		mul edx
		add eax,mask
		mov edx,eax

		mov ecx,loopX
LOOP42:
		movq mm7,mm1
		psrlq mm7,48

		movd ebx,mm7

		cmp ebx,picSizeX
		jnb SKIP41
//表示?
		shl ebx,2
		mov eax,[ebx+esi]
		cmp eax,trans
		jz SKIP41


//		push edx
//		mov edx,ps256
//		mul edx
//		pop edx
//		shr eax,8

		mov eax,ps256

//半透明
		movd mm7,eax
		punpcklwd mm7,mm7
		xor al,0ffh
		punpckldq mm7,mm7
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6


		mov eax,[ebx+esi]
		movd mm4,eax
		paddusb mm4,addColor64
		psubusb mm4,subColor64
		movd eax,mm4

		pxor mm4,mm4
		movd mm5,eax

		punpcklbw mm5,mm4
		pmullw mm7,mm5

		mov eax,[edi]
		movd mm5,eax
		punpcklbw mm5,mm4

		pmullw mm6,mm5

		psrlw mm7,8
		psrlw mm6,8
		paddw mm7,mm6
		packuswb mm7,mm4

		movd eax,mm7
		mov [edi],eax

SKIP41:
		paddd mm1,mm2

		add edi,4
		dec ecx
		jnz LOOP42
SKIP42:

		paddd mm0,mm3


		pop edi
		pop ecx
		add edi,lPitch
		dec ecx
		jnz LOOP41

		jmp EXIT1


EXIT1:
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


/*_*/

