#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "overrapBlt.h"


COverrapBlt::COverrapBlt()
{
}

COverrapBlt::~COverrapBlt()
{
	End();
}

void COverrapBlt::End(void)
{
}

void COverrapBlt::PrintWithScreen(POINT endPoint,LPVOID endPic,SIZE endPicSize,int startPercent,int endPercent)
{
	POINT orgPoint;
	POINT nextPoint = endPoint;
	orgPoint.x = 0;
	orgPoint.y = 0;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();




	RECT rc;
	RECT rc2;

//	orgPic->GetPicSize(&rc);
	SetRect(&rc,0,0,screenSizeX,screenSizeY);
//	nextPic->GetPicSize(&rc2);
	SetRect(&rc2,0,0,endPicSize.cx,endPicSize.cy);

	//check

//	if (rc.right<screenSizeX) return;
//	if (rc.bottom<screenSizeY) return;


	if (rc2.right<screenSizeX) return;
	if (rc2.bottom<screenSizeY) return;

	if (nextPoint.x<0) return;
	if (nextPoint.y<0) return;
	if ((nextPoint.x + screenSizeX) > rc2.right) return;
	if ((nextPoint.y + screenSizeY) > rc2.bottom) return;






	int lPitchSrc = screenSizeX * 4;
	int lPitchDst = rc2.right * 4;

	int ps1 = (startPercent * 256) / 100;
	if (ps1<0) ps1 = 0;
	if (ps1>256) ps1 = 256;

	int ps2 = (endPercent * 256) / 100;
	if (ps2<0) ps2 = 0;
	if (ps2>256) ps2 = 256;

//	int* org = (int*)(orgPic->GetBuffer());
	
	int* next = (int*)endPic;
	int* dst = CMyGraphics::GetScreenBuffer();
	int* org = dst;

	org += orgPoint.x;
	org += orgPoint.y * rc.right;

	next += nextPoint.x;
	next += nextPoint.y * rc2.right;


//	int tmp[64];
//	int ptr = (int)tmp;
//	ptr += 31;
//	ptr &= ~31;

//	void* tmp1 = (void*)(ptr);
//	void* tmp2 = (void*)(ptr+32);
//
//	double tmp1;
//	double tmp2;


	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		pxor mm0,mm0

		mov eax,ps1
		movd mm5,eax
		punpcklwd mm5,mm5
		punpckldq mm5,mm5

		mov ebx,ps2
		movd mm6,ebx
		punpcklwd mm6,mm6
		punpckldq mm6,mm6


		mov ebx,org
		mov esi,next
		mov edi,dst

		mov edx,screenSizeY
LOOP1:
		push ebx
		push esi
//		push edi


		mov ecx,screenSizeX
		shr ecx,1
LOOP2:

		movq mm1,[ebx]
		movq mm2,mm1
		movq mm3,[esi]
		punpcklbw mm1,mm0
		movq mm4,mm3
		punpckhbw mm2,mm0
		punpcklbw mm3,mm0
		punpckhbw mm4,mm0


		pmullw mm1,mm5
		pmullw mm2,mm5
		pmullw mm3,mm6
		pmullw mm4,mm6

		paddw mm1,mm3
		paddw mm2,mm4

		psrlw mm1,8
		psrlw mm2,8

		packuswb mm1,mm2

		movq [edi],mm1

		add ebx,8
		add esi,8
		add edi,8

		dec ecx
		jnz LOOP2

//		pop edi
		pop esi
		pop ebx
		add ebx,lPitchSrc
		add esi,lPitchDst

		dec edx
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


void COverrapBlt::Print(POINT startPoint,LPVOID startPic,SIZE startPicSize,POINT endPoint,LPVOID endPic,SIZE endPicSize,int startPercent,int endPercent)
{
	POINT orgPoint = startPoint;
	POINT nextPoint = endPoint;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	RECT rc;
	RECT rc2;

	SetRect(&rc,0,0,startPicSize.cx,startPicSize.cy);
	SetRect(&rc2,0,0,endPicSize.cx,endPicSize.cy);


	//check

	if (rc.right<screenSizeX) return;
	if (rc.bottom<screenSizeY) return;

	if (orgPoint.x<0) return;
	if (orgPoint.y<0) return;
	if ((orgPoint.x + screenSizeX) > rc.right) return;
	if ((orgPoint.y + screenSizeY) > rc.bottom) return;


	if (rc2.right<screenSizeX) return;
	if (rc2.bottom<screenSizeY) return;

	if (nextPoint.x<0) return;
	if (nextPoint.y<0) return;
	if ((nextPoint.x + screenSizeX) > rc2.right) return;
	if ((nextPoint.y + screenSizeY) > rc2.bottom) return;






	int lPitchSrc = rc.right * 4;
	int lPitchDst = rc2.right * 4;

	int ps1 = (startPercent * 256) / 100;
	if (ps1<0) ps1 = 0;
	if (ps1>256) ps1 = 256;

	int ps2 = (endPercent * 256) / 100;
	if (ps2<0) ps2 = 0;
	if (ps2>256) ps2 = 256;

	int* org = (int*)startPic;
	int* next = (int*)endPic;
	int* dst = CMyGraphics::GetScreenBuffer();

	org += orgPoint.x;
	org += orgPoint.y * rc.right;

	next += nextPoint.x;
	next += nextPoint.y * rc2.right;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		pxor mm0,mm0

		mov eax,ps1
		movd mm5,eax
		punpcklwd mm5,mm5
		punpckldq mm5,mm5

		mov ebx,ps2
		movd mm6,ebx
		punpcklwd mm6,mm6
		punpckldq mm6,mm6


		mov ebx,org
		mov esi,next
		mov edi,dst

		mov edx,screenSizeY
LOOP1:
		push ebx
		push esi
//		push edi


		mov ecx,screenSizeX
		shr ecx,1
LOOP2:

		movq mm1,[ebx]
		movq mm2,mm1
		movq mm3,[esi]
		punpcklbw mm1,mm0
		movq mm4,mm3
		punpckhbw mm2,mm0
		punpcklbw mm3,mm0
		punpckhbw mm4,mm0


		pmullw mm1,mm5
		pmullw mm2,mm5
		pmullw mm3,mm6
		pmullw mm4,mm6

		paddw mm1,mm3
		paddw mm2,mm4

		psrlw mm1,8
		psrlw mm2,8

		packuswb mm1,mm2

		movq [edi],mm1

		add ebx,8
		add esi,8
		add edi,8
		dec ecx
		jnz LOOP2

//		pop edi
		pop esi
		pop ebx
		add ebx,lPitchSrc
		add esi,lPitchDst

		dec edx
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


/*_*/

