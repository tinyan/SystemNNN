//
//
//

#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\myFile.h"


#include "userFont.h"


CUserFont::CUserFont(LPSTR fontfilename)
{
	m_userFontData0 = NULL;
	m_makedFontWork0 = NULL;
	m_makedFont0 = NULL;

	char filename[256];
	wsprintf(filename,"nya\\%s.mft",fontfilename);
	FILE* file = CMyFile::Open(filename,"rb");
	if (file == NULL)
	{
		MessageBox(NULL,fontfilename,"ユーザーフォントLOADエラー",MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	fseek(file,0,SEEK_END);
	int sz = ftell(file);
	fseek(file,0,SEEK_SET);

	m_userFontData0 = new char[sz+64];
	int p = (int)m_userFontData0;
	p += 63;
	p &= ~63;
	m_userFontData = (char*)p;

	fread(m_userFontData,sizeof(char),sz,file);

	fclose(file);



	int h = m_userFontData[32+9];
	int l = m_userFontData[32+10];
	int m = m_userFontData[32+11];

	h -= '0';
	l -= '0';
	m -= '0';

	h &= 0xff;
	l &= 0xff;
	m &= 0xff;

	m_userFontSize = h * 100 + l * 10 + m;

	int t = m_userFontData[48+9];
	t -= '0';
	t &= 0xff;

	m_userFontType = t;
	m_fontDataSize = (m_userFontSize + 7) & (~7);

	m_makedFontWork0 = new char[m_fontDataSize*m_fontDataSize+63];
	int p2 = (int)m_makedFontWork0;
	p2 += 63;
	p2 &= (~63);
	m_makedFontWork = (char*)p2;

	m_makedFont0 = new char[m_userFontSize*m_userFontSize+63];
	int p3 = (int)m_makedFont0;
	p3 += 63;
	p3 &= (~63);
	m_makedFont = (char*)p3;
}


CUserFont::~CUserFont()
{
	End();
}


void CUserFont::End(void)
{
	DELETEARRAY(m_makedFont0);
	DELETEARRAY(m_makedFontWork0);
	DELETEARRAY(m_userFontData0);
}


char* CUserFont::GetFont1Moji(char* mes)
{
	char h = *mes;
	char l = *(mes+1);

	int ch = (h & 0xff);
	int cl = (l & 0xff);
	
	BOOL f = TRUE;

	if (ch < 0x81) f = FALSE;
	if (ch > 0xef) f = FALSE;
	if ((ch >=0xa0) && (ch<=0xbf)) f = FALSE;
	if (cl<0x3f) f = FALSE;

	if (f == FALSE)
	{
		ZeroMemory(m_makedFontWork,m_fontDataSize*m_fontDataSize);
		return MakedToData();
	}

	cl -= 0x3f;
	if (ch < 0xa0)
	{
		ch -= 0x81;
	}
	else
	{
		ch -= 0xe0;
		ch += 0x1f;
	}

	int cd = ch * 0xc0 + cl;

	if (m_userFontType == 2)
	{
		MakeFont2(cd);
	}
	else if (m_userFontType == 4)
	{
		MakeFont4(cd);
	}
	else if (m_userFontType == 8)
	{
		MakeFont8(cd);
	}

	return MakedToData();
}


void CUserFont::MakeFont2(int cd)
{
	char* src = m_userFontData + 64 + m_fontDataSize * m_fontDataSize * m_userFontType / 8 * cd;
	char* dst = m_makedFontWork;

	int loopX = m_fontDataSize / 8;
	int loopY = m_fontDataSize / (8/m_userFontType);


	int dstPitch1 = m_fontDataSize;
	int dstPitch = m_fontDataSize * (8/m_userFontType);


	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		pxor mm0,mm0

		mov eax,03030303h
		movd mm7,eax
		punpckldq mm7,mm7

		mov ebx,dstPitch1

		mov esi,src
		mov edi,dst

		mov ecx,loopY
LOOP10:
		push ecx
		push edi

		mov edx,edi
		add edx,ebx
		add edx,ebx

		mov ecx,loopX
LOOP11:
		movq mm1,[esi]
		movq mm2,mm1
		movq mm3,mm1
		movq mm4,mm1

		pand mm1,mm7
		movq mm5,mm1
		psllw mm5,2
		por mm1,mm5
		movq mm5,mm1
		psllw mm5,4
		por mm1,mm5
		movq [edi],mm1

		psrlw mm2,2
		pand mm2,mm7
		movq mm5,mm2
		psllw mm5,2
		por mm2,mm5
		movq mm5,mm2
		psllw mm5,4
		por mm2,mm5
		movq [edi+ebx],mm2

		psrlw mm3,4
		pand mm3,mm7
		movq mm5,mm3
		psllw mm5,2
		por mm3,mm5
		movq mm5,mm3
		psllw mm5,4
		por mm3,mm5
		movq [edx],mm3

		psrlw mm4,6
		pand mm4,mm7
		movq mm5,mm4
		psllw mm5,2
		por mm4,mm5
		movq mm5,mm4
		psllw mm5,4
		por mm4,mm5

		movq [edx+ebx],mm4

		add edi,8
		add edx,8
		add esi,8

		dec ecx
		jnz LOOP11

		pop edi
		pop ecx
		add edi,dstPitch
		dec ecx
		jnz LOOP10

		emms

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
}

void CUserFont::MakeFont4(int cd)
{
	char* src = m_userFontData + 64 + m_fontDataSize * m_fontDataSize * m_userFontType / 8 * cd;
	char* dst = m_makedFontWork;

	int loopX = m_fontDataSize / 8;
	int loopY = m_fontDataSize / (8/m_userFontType);

	int dstPitch1 = m_fontDataSize;
	int dstPitch = m_fontDataSize * (8/m_userFontType);

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		pxor mm0,mm0

		mov eax,0f0f0f0fh
		movd mm7,eax
		punpckldq mm7,mm7


		mov ebx,dstPitch1

		mov esi,src
		mov edi,dst

		mov ecx,loopY
LOOP20:
		push ecx
		push edi

//		mov edx,edi
//		add edx,ebx

		mov ecx,loopX
LOOP21:
		movq mm1,[esi]
		movq mm2,mm1
		pand mm1,mm7
		psrlw mm2,4
		pand mm2,mm7

		movq mm4,mm1
		movq mm5,mm2

		psllw mm4,4
		psllw mm5,4

		por mm1,mm4
		por mm2,mm5

		movq [edi],mm1
		movq [edi+ebx],mm2

		add edi,8
//		add edx,8
		add esi,8

		dec ecx
		jnz LOOP21

		pop edi
		pop ecx
		add edi,dstPitch
		dec ecx
		jnz LOOP20

		emms

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}

}

void CUserFont::MakeFont8(int cd)
{
	char* src = m_userFontData + 64 + m_fontDataSize * m_fontDataSize * m_userFontType / 8 * cd;
	char* dst = m_makedFontWork;


	int loopX = m_fontDataSize / 8;
	int loopY = m_fontDataSize / (8/m_userFontType);

	int sz = m_fontDataSize * m_fontDataSize;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		pxor mm0,mm0

		mov esi,src
		mov edi,dst

		mov ecx,sz
		shr ecx,2
		cld
		rep movsd

		emms

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
}



char* CUserFont::MakedToData(void)
{
	if (m_userFontSize == m_fontDataSize)
	{
		return m_makedFontWork;
	}

	char* src = m_makedFontWork;
	char* dst = m_makedFont;

	int sz0 = m_fontDataSize;
	int sz = m_userFontSize;
	for (int j=0;j<m_userFontSize;j++)
	{
		memcpy(dst,src,sz);
		src += sz0;
		dst += sz;
	}

	return m_makedFont;
}


/*_*/


