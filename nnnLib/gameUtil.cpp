//
// gameUtil.cpp
//

#include <windows.h>


#include "gameUtil.h"

CGameUtil::CGameUtil()
{
}

CGameUtil::~CGameUtil()
{
	End();
}

void CGameUtil::End(void)
{

}


BOOL CGameUtil::MakeMiniCG106x80(int* screenBuffer, int* makedBuffer)
{
	if (screenBuffer == NULL) return FALSE;
	if (makedBuffer == NULL) return FALSE;

	int* dst = makedBuffer;
	int* src = screenBuffer;
	src += 2;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		mov esi,src
		mov edi,dst

		mov edx,80
		pxor mm0,mm0

		mov eax,071C071Ch
		movd mm5,eax
		punpckldq mm5,mm5

LOOP1:
		push esi
		mov ecx,106

LOOP2:
		push esi

		pxor mm7,mm7

		mov ebx,6
LOOP3:
		movq mm1,[esi]
		movq mm2,mm1
		punpcklbw mm1,mm0
		punpckhbw mm2,mm0
		paddw mm7,mm1
		paddw mm7,mm2

		movq mm1,[esi+8]
		movq mm2,mm1
		punpcklbw mm1,mm0
		punpckhbw mm2,mm0
		paddw mm7,mm1
		paddw mm7,mm2

		movq mm1,[esi+16]
		movq mm2,mm1
		punpcklbw mm1,mm0
		punpckhbw mm2,mm0
		paddw mm7,mm1
		paddw mm7,mm2

		add esi,640*4
		dec ebx
		jnz LOOP3

		//div 36 = *65536/36 / 65536

		pmulhw mm7,mm5
		packuswb mm7,mm0
		movd eax,mm7
		mov [edi],eax

		add edi,4
		pop esi
		add esi,4*6
		dec ecx
		jnz LOOP2

		pop esi
		add esi,640*4*6
		dec edx
		jnz LOOP1


		emms

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}


	return TRUE;
}



//800x600
BOOL CGameUtil::MakeMiniCG132x100(int* screenBuffer, int* makedBuffer)
{
	if (screenBuffer == NULL) return FALSE;
	if (makedBuffer == NULL) return FALSE;

	int* dst = makedBuffer;
	int* src = screenBuffer;
	src += 4;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		mov esi,src
		mov edi,dst

		mov edx,100
		pxor mm0,mm0

		mov eax,071C071Ch
		movd mm5,eax
		punpckldq mm5,mm5

LOOP1:
		push esi
		mov ecx,132

LOOP2:
		push esi

		pxor mm7,mm7

		mov ebx,6
LOOP3:
		movq mm1,[esi]
		movq mm2,mm1
		punpcklbw mm1,mm0
		punpckhbw mm2,mm0
		paddw mm7,mm1
		paddw mm7,mm2

		movq mm1,[esi+8]
		movq mm2,mm1
		punpcklbw mm1,mm0
		punpckhbw mm2,mm0
		paddw mm7,mm1
		paddw mm7,mm2

		movq mm1,[esi+16]
		movq mm2,mm1
		punpcklbw mm1,mm0
		punpckhbw mm2,mm0
		paddw mm7,mm1
		paddw mm7,mm2

		add esi,800*4
		dec ebx
		jnz LOOP3

		//div 36 = *65536/36 / 65536

		pmulhw mm7,mm5
		packuswb mm7,mm0
		movd eax,mm7
		mov [edi],eax

		add edi,4
		pop esi
		add esi,4*6
		dec ecx
		jnz LOOP2

		pop esi
		add esi,800*4*6
		dec edx
		jnz LOOP1


		emms

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}


	return TRUE;
}