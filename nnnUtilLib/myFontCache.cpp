//
// myfont.cpp
//

#include <windows.h>
//#include <d3dx9.h>

#include "..\nyanLib\include\commonmacro.h"

#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGeo.h"


#if defined _TINYAN3DLIB_
	#include "..\..\systemNNN3D\nyanDirectX3DLib/myDirect3D.h"
	#include "..\..\systemNNN3D\nyanDirectX3DLib/myTexture.h"
#endif



//#include "game.h"

#include "myFontCache.h"

int CMyFontCache::m_gradBunkatsu = 8;
int CMyFontCache::m_effectColorR = 255;
int CMyFontCache::m_effectColorG = 255;
int CMyFontCache::m_effectColorB = 255;
int CMyFontCache::m_effectColorA = 255;


CMyFontCache::CMyFontCache(int sizeY,int rubiFlag)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();
	if (sizeY<screenSizeY) sizeY = screenSizeY;

	m_cacheSizeX = screenSizeX;
	m_cacheSizeY = screenSizeY;

	SetEffectColor(255,255,255,100);

#if defined _TINYAN3DLIB_
	LPDIRECT3DDEVICE9 d3dDevice = CMyDirect3D::GetD3DDevice();
#endif

	m_fontTexture = NULL;
	m_fontOffScreen = NULL;

	m_fontPic = new CPicture(m_cacheSizeX,m_cacheSizeY,TRUE);
#if defined _TINYAN3DLIB_
	CMyTexture* lpTexture = (CMyTexture*)(m_fontPic->GetTexture());
	lpTexture->SetFix();
#endif

	m_rubiPic = NULL;
	m_rubiFlag = rubiFlag;
	if (m_rubiFlag)
	{
		m_rubiPic = new CPicture(m_cacheSizeX,m_cacheSizeY,TRUE);
#if defined _TINYAN3DLIB_
		CMyTexture* lpTextureRubi = (CMyTexture*)(m_rubiPic->GetTexture());
		lpTextureRubi->SetFix();
#endif
	}

	m_dataKosuuMax = m_cacheSizeY / 16;

	m_table = new int[m_dataKosuuMax * 16];
	m_messageTable = new char[m_dataKosuuMax * 256];

	m_dataKosuu = 0;
	m_useStart = 0;
	m_bufferStartY = 0;
	m_bufferSizeY = m_cacheSizeY;
}


CMyFontCache::~CMyFontCache()
{
	End();
}

void CMyFontCache::End(void)
{
	DELETEARRAY(m_messageTable);
	DELETEARRAY(m_table);
	ENDDELETECLASS(m_rubiPic);
	ENDDELETECLASS(m_fontPic);
}

#if defined _TINYAN3DLIB_
void CMyFontCache::ClearCache(void)
{
	m_dataKosuu = 0;
	m_useStart = 0;
	m_bufferStartY = 0;
	m_bufferSizeY = m_cacheSizeY;
}
#endif

BOOL CMyFontCache::GetData(int n,CPicture* lpPic)
{
	SIZE sz = lpPic->GetPicSize();
	int dstPitch = sz.cx * sizeof(int);
	int dstMaskPitch = sz.cx;
	int* dst = (int*)(lpPic->GetBuffer());
	char* dstMask = lpPic->GetMaskPic();

	SIZE sz2 = m_fontPic->GetPicSize();
	int srcPitch = sz2.cx * sizeof(int);
	int srcMaskPitch = sz2.cx;
	int* src = (int*)(m_fontPic->GetBuffer());
	char* srcMask = m_fontPic->GetMaskPic();

	int loopX = m_table[n*16+7];
	int loopY = m_table[n*16+8];

	int offsetY = m_table[n*16+9];
	src += sz2.cx * offsetY;
	srcMask += sz2.cx * offsetY;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		cld

		mov edx,loopY
		mov esi,src
		mov edi,dst
LOOP1:
		push esi
		push edi
		mov ecx,loopX
		rep movsd
		pop edi
		pop esi
		add esi,srcPitch
		add edi,dstPitch
		dec edx
		jnz LOOP1

		mov edx,loopY
		mov esi,srcMask
		mov edi,dstMask
LOOP2:
		push esi
		push edi
		mov ecx,loopX
		mov eax,ecx
		shr ecx,2
		or ecx,ecx
		jz SKIP1
		rep movsd
SKIP1:
		and eax,3
		or eax,eax
		jz SKIP2
		mov ecx,eax
		rep movsb
SKIP2:
		pop edi
		pop esi
		add esi,srcMaskPitch
		add edi,dstMaskPitch
		dec edx
		jnz LOOP2

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}


	return TRUE;
}

SIZE CMyFontCache::GetSize(int n)
{
	SIZE sz;

	sz.cx = m_table[n*16+7];
	sz.cy = m_table[n*16+8];

	return sz;
}

int CMyFontCache::SearchData(LPSTR message,int fontSize,int colR,int colG,int colB,int sukima,int kageColor)
{
	int ln = strlen(message);
	if (ln > 254) return -1;

	for (int i=0;i<m_dataKosuu;i++)
	{
		int n = (m_useStart+i) % m_dataKosuuMax;
		if (ln != m_table[n*16+0]) continue;
		if (fontSize != m_table[n*16+1]) continue;

		if (strcmp(message,&m_messageTable[n*128]) != 0) continue;

		if (colR != m_table[n*16+2]) continue;
		if (colG != m_table[n*16+3]) continue;
		if (colB != m_table[n*16+4]) continue;
		if (sukima != m_table[n*16+5]) continue;
		if (kageColor != m_table[n*16+6]) continue;

		return n;
	}

	return -1;
}

int CMyFontCache::AddData(LPSTR message,int fontSize,int colR,int colG,int colB,int sukima,int kageColor,int sizeX2,int sizeY2,CPicture* lpPic,CPicture* lpRubiPic)
{
#if defined _TINYAN3DLIB_
	m_fontOffScreen = CMyDirect3D::GetCommonOffScreenTexture(0);
	if (m_fontOffScreen == NULL) return -1;
#endif

	int ln = strlen(message);
	if (ln > 254) return -1;

	if ((fontSize <= m_bufferSizeY) && (m_dataKosuu < m_dataKosuuMax))
	{
		return SetDataSub(ln,fontSize,message,colR,colG,colB,sukima,kageColor,sizeX2,sizeY2,lpPic,lpRubiPic);
	}

	//‚ ‚¯‚é
	int loop = m_dataKosuu;
	BOOL flg = FALSE;
	for (int i=0;i<loop;i++)
	{
		int startY = m_table[m_useStart*16+9];
		int sizeY = m_table[m_useStart*16+8];

		if (startY >= m_bufferStartY)
		{
			m_bufferSizeY += sizeY;
			//‚¢‚¿‚Î‚ñ‚µ‚½‚Ü‚Å‚ ‚¯‚éH
			if (m_dataKosuu>=2)
			{
				int k = (m_useStart+1) % m_dataKosuuMax;
				int y2 = m_table[k*16+9];
				if (y2<m_bufferStartY)
				{
					m_bufferSizeY = m_cacheSizeY - m_bufferStartY;
				}
			}
		}
		else
		{
			m_bufferStartY = 0;
			m_bufferSizeY = startY+sizeY;
		}

		m_useStart++;
		m_useStart %= m_dataKosuuMax;
		m_dataKosuu--;

		if (fontSize <= m_bufferSizeY)
		{
			return SetDataSub(ln,fontSize,message,colR,colG,colB,sukima,kageColor,sizeX2,sizeY2,lpPic,lpRubiPic);
		}
	}

	return -1;
}


int CMyFontCache::SetDataSub(int ln,int fontSize,LPSTR message,int colR,int colG,int colB,int sukima,int kageColor,int sizeX2,int sizeY2,CPicture* lpPic,CPicture* lpRubiPic)
{
	int n = (m_useStart+m_dataKosuu) % m_dataKosuuMax;

	m_table[n*16] = ln;
	m_table[n*16+1] = fontSize;
	m_table[n*16+2] = colR;
	m_table[n*16+3] = colG;
	m_table[n*16+4] = colB;
	m_table[n*16+5] = sukima;
	m_table[n*16+6] = kageColor;
	m_table[n*16+7] = sizeX2;
	m_table[n*16+8] = sizeY2;
	m_table[n*16+9] = m_bufferStartY;

	m_table[n*16+10] = 0;//rubiFlag

	if (m_rubiFlag)
	{
		if (lpRubiPic != NULL)
		{
			m_table[n*16+10] = 1;
		}
	}


	memcpy(m_messageTable+128*n,message,ln);
	m_messageTable[128*n+ln] = 0;
	m_messageTable[128*n+ln+1] = 0;

	m_bufferStartY += sizeY2;
	m_bufferSizeY -= sizeY2;




	m_dataKosuu++;


	int loopX = m_table[n*16+7];
	int loopY = m_table[n*16+8];
	int offsetY = m_table[n*16+9];

	if ((loopX <= 0) || (loopY <= 0)) return n;

	SIZE sz2 = lpPic->GetPicSize();
	int srcPitch = sz2.cx * sizeof(int);
	int srcMaskPitch = sz2.cx;
	int* src = (int*)(lpPic->GetBuffer());
	char* srcMask = lpPic->GetMaskPic();


#if !defined _TINYAN3DLIB_

	SIZE sz = m_fontPic->GetPicSize();
	int dstPitch = sz.cx * sizeof(int);
	int dstMaskPitch = sz.cx;
	int* dst = (int*)(m_fontPic->GetBuffer());
	char* dstMask = m_fontPic->GetMaskPic();

	dst += sz.cx * offsetY;
	dstMask += sz.cx * offsetY;
#else

	//lock
	D3DLOCKED_RECT rected;
	RECT rc;
	SetRect(&rc,0,offsetY,loopX,offsetY+loopY);


//	((LPDIRECT3DSURFACE9)m_fontOffScreen)->LockRect(&rected,&rc,0);
	((LPDIRECT3DTEXTURE9)m_fontOffScreen)->LockRect(0,&rected,&rc,0);
	int dstPitch = rected.Pitch;
	int* dst = (int*)rected.pBits;


#endif

#if !defined _TINYAN3DLIB_
	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		cld

		mov edx,loopY
		mov esi,src
		mov edi,dst
LOOP1:
		push esi
		push edi
		mov ecx,loopX
		rep movsd
		pop edi
		pop esi
		add esi,srcPitch
		add edi,dstPitch
		dec edx
		jnz LOOP1

		mov edx,loopY
		mov esi,srcMask
		mov edi,dstMask
LOOP2:
		push esi
		push edi
		mov ecx,loopX
		mov eax,ecx
		shr ecx,2
		or ecx,ecx
		jz SKIP1
		rep movsd
SKIP1:
		and eax,3
		or eax,eax
		jz SKIP2
		mov ecx,eax
		rep movsb
SKIP2:
		pop edi
		pop esi
		add esi,srcMaskPitch
		add edi,dstMaskPitch
		dec edx
		jnz LOOP2

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
#else

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		cld

		mov edx,loopY
		mov esi,src
		mov ebx,srcMask
		mov edi,dst
LOOP1:
		push edx

		push ebx
		push esi
		push edi

		mov ecx,loopX
LOOP2:
		mov eax,[esi]
		and eax,0ffffffh
		xor edx,edx
		mov dl,[ebx]
		shl edx,24
		or eax,edx
		mov [edi],eax
		inc ebx
		add esi,4
		add edi,4
		dec ecx
		jnz LOOP2


		pop edi
		pop esi
		pop ebx

		add edi,dstPitch
		add esi,srcPitch
		add ebx,srcMaskPitch

		pop edx
		dec edx
		jnz LOOP1

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}

#endif

#if defined _TINYAN3DLIB_
	if (1)
	{
		((LPDIRECT3DTEXTURE9)m_fontOffScreen)->UnlockRect(0);


		//surface update
		LPDIRECT3DSURFACE9 srcSurface = NULL;


		LPDIRECT3DSURFACE9 dstSurface = NULL;
		CMyTexture* myTexture = (CMyTexture*)(m_fontPic->GetTexture());
		LPDIRECT3DTEXTURE9 dstTexture = myTexture->GetTexture();


		HRESULT hr = dstTexture->GetSurfaceLevel(0,&dstSurface);
		if (FAILED(hr))
		{
			OutputDebugString("get surface error");
		}

		hr = ((LPDIRECT3DTEXTURE9)m_fontOffScreen)->GetSurfaceLevel(0,&srcSurface);
		if (FAILED(hr))
		{
			OutputDebugString("get surface error");
		}

		LPDIRECT3DDEVICE9 d3dDevice = CMyDirect3D::GetD3DDevice();
		RECT srcRect;
		SetRect(&srcRect,0,offsetY,loopX,offsetY+loopY);
		POINT dstPoint;
		dstPoint.x = 0;
		dstPoint.y = offsetY;
		hr = d3dDevice->UpdateSurface(srcSurface,&srcRect,dstSurface,&dstPoint);
		if (FAILED(hr))
		{
			OutputDebugString("UpdateSurface error");
		}

		hr = d3dDevice->UpdateTexture((LPDIRECT3DTEXTURE9)m_fontOffScreen,dstTexture);
		if (FAILED(hr))
		{
			OutputDebugString("UpdateTexture error");
		}
			

		if (srcSurface != NULL)
		{
			srcSurface->Release();
		}


		if (dstSurface != NULL)
		{
			dstSurface->Release();
		}

	//	d3dDevice->EndScene();
	//	d3dDevice->BeginScene();
	#if defined _DEBUG
		{
	//		OutputDebugString("\nadd font cache");
	//		OutputDebugString(orgMessage);
	//		char mes[256];
	//		wsprintf(mes,"Y=%d size=(%d,%d)",offsetY,loopX,loopY);
	//		OutputDebugString(mes);
		}
	#endif
	}

#endif


	if (lpRubiPic != NULL) 
	{

//		SIZE sz = m_fontPic->GetPicSize();
//		int dstPitch = sz.cx * sizeof(int);
//		int dstMaskPitch = sz.cx;
//		int* dst = (int*)(m_fontPic->GetBuffer());
//		char* dstMask = m_fontPic->GetMaskPic();

		SIZE sz3 = lpRubiPic->GetPicSize();
		int rubiPitch = sz3.cx * sizeof(int);
		int rubiMaskPitch = sz3.cx;
		int* rubiSrc = (int*)(lpRubiPic->GetBuffer());
		char* rubiSrcMask = lpRubiPic->GetMaskPic();


#if !defined _TINYAN3DLIB_

		SIZE sz4 = m_rubiPic->GetPicSize();
		int dstRubiPitch = sz4.cx * sizeof(int);
		int dstRubiMaskPitch = sz4.cx;
		int* dstRubi = (int*)(m_rubiPic->GetBuffer());
		char* dstRubiMask = m_rubiPic->GetMaskPic();


		dstRubi += sz4.cx * offsetY;
		dstRubiMask += sz4.cx * offsetY;
#else
	//lock
	D3DLOCKED_RECT rected2;
	RECT rc2;
	SetRect(&rc2,0,offsetY,loopX,offsetY+loopY);


//	((LPDIRECT3DSURFACE9)m_fontOffScreen)->LockRect(&rected2,&rc2,0);
	((LPDIRECT3DTEXTURE9)m_fontOffScreen)->LockRect(0,&rected2,&rc2,0);
	int dstRubiPitch = rected2.Pitch;
	int* dstRubi = (int*)rected2.pBits;


#endif



//		int loopX = m_table[n*16+7];
//		int loopY = m_table[n*16+8];


//		int offsetY = m_table[n*16+9];
//		dst += sz.cx * offsetY;
//		dstMask += sz.cx * offsetY;

#if !defined _TINYAN3DLIB_
		__asm
		{
			push eax
			push ebx
			push ecx
			push edx
			push esi
			push edi

			cld

			mov edx,loopY
			mov esi,rubiSrc
			mov edi,dstRubi
LOOP1RUBI:
			push esi
			push edi
			mov ecx,loopX
			rep movsd
			pop edi
			pop esi
			add esi,rubiPitch
			add edi,dstRubiPitch
			dec edx
			jnz LOOP1RUBI

			mov edx,loopY
			mov esi,rubiSrcMask
			mov edi,dstRubiMask
LOOP2RUBI:
			push esi
			push edi
			mov ecx,loopX
			mov eax,ecx
			shr ecx,2
			or ecx,ecx
			jz SKIP1RUBI
			rep movsd
SKIP1RUBI:
			and eax,3
			or eax,eax
			jz SKIP2RUBI
			mov ecx,eax
			rep movsb
SKIP2RUBI:
			pop edi
			pop esi
			add esi,rubiMaskPitch
			add edi,dstRubiMaskPitch
			dec edx
			jnz LOOP2RUBI

			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax
		}
#else
	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		cld

		mov edx,loopY
		mov esi,rubiSrc
		mov ebx,rubiSrcMask
		mov edi,dstRubi
LOOP1R:
		push edx

		push ebx
		push esi
		push edi

		mov ecx,loopX
LOOP2R:
		mov eax,[esi]
		and eax,0ffffffh
		xor edx,edx
		mov dl,[ebx]
		shl edx,24
		or eax,edx
		mov [edi],eax
		inc ebx
		add esi,4
		add edi,4
		dec ecx
		jnz LOOP2R


		pop edi
		pop esi
		pop ebx

		add edi,dstRubiPitch
		add esi,rubiPitch
		add ebx,rubiMaskPitch

		pop edx
		dec edx
		jnz LOOP1R

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}

#endif


#if defined _TINYAN3DLIB_
	((LPDIRECT3DTEXTURE9)m_fontOffScreen)->UnlockRect(0);


	//surface update
	LPDIRECT3DSURFACE9 srcSurface = NULL;


	LPDIRECT3DSURFACE9 dstSurface = NULL;
	CMyTexture* myTexture = (CMyTexture*)(m_fontPic->GetTexture());
	LPDIRECT3DTEXTURE9 dstTexture = myTexture->GetTexture();


	HRESULT hr = dstTexture->GetSurfaceLevel(0,&dstSurface);
	if (FAILED(hr))
	{
		OutputDebugString("get surface error");
	}

	hr = ((LPDIRECT3DTEXTURE9)m_fontOffScreen)->GetSurfaceLevel(0,&srcSurface);
	if (FAILED(hr))
	{
		OutputDebugString("get surface error");
	}

	LPDIRECT3DDEVICE9 d3dDevice = CMyDirect3D::GetD3DDevice();
	RECT srcRect;
	SetRect(&srcRect,0,offsetY,loopX,offsetY+loopY);
	POINT dstPoint;
	dstPoint.x = 0;
	dstPoint.y = offsetY;
	hr = d3dDevice->UpdateSurface(srcSurface,&srcRect,dstSurface,&dstPoint);
	if (FAILED(hr))
	{
		OutputDebugString("UpdateSurface error");
	}

	hr = d3dDevice->UpdateTexture((LPDIRECT3DTEXTURE9)m_fontOffScreen,dstTexture);
	if (FAILED(hr))
	{
		OutputDebugString("UpdateTexture error");
	}
		

	if (srcSurface != NULL)
	{
		srcSurface->Release();
	}


	if (dstSurface != NULL)
	{
		dstSurface->Release();
	}

//	d3dDevice->EndScene();
//	d3dDevice->BeginScene();
#if defined _DEBUG
	{
//		OutputDebugString("\nadd font cache");
//		OutputDebugString(orgMessage);
//		char mes[256];
//		wsprintf(mes,"Y=%d size=(%d,%d)",offsetY,loopX,loopY);
//		OutputDebugString(mes);
	}
#endif

#endif

	}


	return n;
}

POINT CMyFontCache::GetSrc(int n)
{
	POINT pt;
	int offsetY = m_table[n*16+9];
	pt.x = 0;
	pt.y = offsetY;
	return pt;
}


void CMyFontCache::Blt(int putX,int putY,int srcX,int srcY,int sizeX,int sizeY,BOOL transFlag)
{
	m_fontPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,transFlag);
}

void CMyFontCache::BltRubi(int putX,int putY,int srcX,int srcY,int sizeX,int sizeY,BOOL transFlag)
{
	if (m_rubiFlag == FALSE) return;

	m_rubiPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,transFlag);
}

void CMyFontCache::GradBlt(int startX,int endX,int fontSize,int putX,int putY,int srcX,int srcY,int sizeX,int sizeY,BOOL transFlag)
{
	//left
	int dv = m_gradBunkatsu;

	for (int i=0;i<dv;i++)
	{
		int ps = ((i+1) * 100) / (dv+1);
		int clipX1 = startX + (fontSize*i) / dv;
		int clipX2 = startX + (fontSize*(i+1)) / dv;

		int putXX = putX;
		int sizeXX = sizeX;
		int srcXX = srcX;

		if (putXX<clipX1)
		{
			srcXX += (clipX1 - putXX);
			sizeXX -= (clipX1 - putXX);
			putXX = clipX1;
		}

		if ((putXX+sizeXX) > clipX2)
		{
			sizeXX -= (putXX+sizeXX-clipX2);
		}

		if (sizeXX > 0)
		{
			m_fontPic->TransLucentBlt3(putXX,putY,srcXX,srcY,sizeXX,sizeY,ps);
		}
	}

	//right
	for (int i=0;i<dv;i++)
	{
		int ps = ((dv-i) * 100) / (dv+1);
		int clipX1 = endX - fontSize + (fontSize*i) / dv;
		int clipX2 = endX - fontSize + (fontSize*(i+1)) / dv;

		int putXX = putX;
		int sizeXX = sizeX;
		int srcXX = srcX;

		if (putXX<clipX1)
		{
			srcXX += (clipX1 - putXX);
			sizeXX -= (clipX1 - putXX);
			putXX = clipX1;
		}

		if ((putXX+sizeXX) > clipX2)
		{
			sizeXX -= (putXX+sizeXX-clipX2);
		}

		if (sizeXX > 0)
		{
			m_fontPic->TransLucentBlt3(putXX,putY,srcXX,srcY,sizeXX,sizeY,ps);
		}
	}

	//center

	if (1)
	{
		int clipX1 = startX + fontSize;
		int clipX2 = endX - fontSize;

		if (putX<clipX1)
		{
			srcX += (clipX1 - putX);
			sizeX -= (clipX1 - putX);
			putX = clipX1;
		}

		if ((putX+sizeX) > clipX2)
		{
			sizeX -= (putX+sizeX-clipX2);
		}

		if (sizeX > 0)
		{
			m_fontPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,transFlag);

		}
	}
}


void CMyFontCache::GradBltRubi(int startX,int endX,int fontSize,int putX,int putY,int srcX,int srcY,int sizeX,int sizeY,BOOL transFlag)
{
	if (m_rubiFlag == FALSE) return;


	//left
	int dv = m_gradBunkatsu;

	for (int i=0;i<dv;i++)
	{
		int ps = ((i+1) * 100) / (dv+1);
		int clipX1 = startX + (fontSize*i) / dv;
		int clipX2 = startX + (fontSize*(i+1)) / dv;

		int putXX = putX;
		int sizeXX = sizeX;
		int srcXX = srcX;

		if (putXX<clipX1)
		{
			srcXX += (clipX1 - putXX);
			sizeXX -= (clipX1 - putXX);
			putXX = clipX1;
		}

		if ((putXX+sizeXX) > clipX2)
		{
			sizeXX -= (putXX+sizeXX-clipX2);
		}

		if (sizeXX > 0)
		{
			m_rubiPic->TransLucentBlt3(putXX,putY,srcXX,srcY,sizeXX,sizeY,ps);
		}
	}

	//right
	for (int i=0;i<dv;i++)
	{
		int ps = ((dv-i) * 100) / (dv+1);
		int clipX1 = endX - fontSize + (fontSize*i) / dv;
		int clipX2 = endX - fontSize + (fontSize*(i+1)) / dv;

		int putXX = putX;
		int sizeXX = sizeX;
		int srcXX = srcX;

		if (putXX<clipX1)
		{
			srcXX += (clipX1 - putXX);
			sizeXX -= (clipX1 - putXX);
			putXX = clipX1;
		}

		if ((putXX+sizeXX) > clipX2)
		{
			sizeXX -= (putXX+sizeXX-clipX2);
		}

		if (sizeXX > 0)
		{
			m_rubiPic->TransLucentBlt3(putXX,putY,srcXX,srcY,sizeXX,sizeY,ps);
		}
	}

	//center

	if (1)
	{
		int clipX1 = startX + fontSize;
		int clipX2 = endX - fontSize;

		if (putX<clipX1)
		{
			srcX += (clipX1 - putX);
			sizeX -= (clipX1 - putX);
			putX = clipX1;
		}

		if ((putX+sizeX) > clipX2)
		{
			sizeX -= (putX+sizeX-clipX2);
		}

		if (sizeX > 0)
		{
			m_rubiPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,transFlag);

		}
	}


//	m_rubiPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,transFlag);
}

void CMyFontCache::EffectBlt(int putX,int putY,int srcX,int srcY,int sizeX,int sizeY,BOOL transFlag,int effectType,int effectCount1000)
{
	if (effectCount1000 <= 0) return;

	int putSizeX = sizeX;
	int putSizeY = sizeY;
	if (effectType & 1)
	{
		putSizeX = (sizeX * effectCount1000) / 1000;
	}
	if (effectType & 2)
	{
		putSizeY = (sizeY * effectCount1000) / 1000;
	}
	if ((putSizeX <= 0) || (putSizeY <= 0)) return;

	int ps = m_effectColorA;
	if (effectType & 8)
	{
		ps = (ps * effectCount1000) / 1000;
	}
	if (ps < 1) return;


	int deltaX = (sizeX - putSizeX) / 2;
	int deltaY = (sizeY - putSizeY) / 2;

	int putXX = putX + deltaX;
	int putYY = putY + deltaY;
	int srcXX = srcX + deltaX;
	int srcYY = srcY + deltaY;



	if (effectType & 16)
	{
		CAllGeo::TransBoxFill(putXX,putYY,putSizeX,putSizeY,m_effectColorR,m_effectColorG,m_effectColorB,ps);
	}
	else
	{
		if (effectType & 4)
		{
			m_fontPic->StretchBlt1(putXX,putYY,putSizeX,putSizeY,srcX,srcY,sizeX,sizeY,ps,TRUE);
//			m_fontPic->StretchBlt1(putXX,putYY,putSizeX,putSizeY,0,0,sizeX,sizeY,ps,TRUE);
		}
		else
		{
			m_fontPic->TransLucentBlt2(putXX,putYY,srcXX,srcYY,putSizeX,putSizeY,ps);
		}
	}
}


void CMyFontCache::ClearFontCache(void)
{
	m_dataKosuu = 0;
	m_useStart = 0;
	m_bufferStartY = 0;
	m_bufferSizeY = m_cacheSizeY;
}

void CMyFontCache::SetEffectColor(int r,int g,int b,int a)
{
	m_effectColorR = r;
	m_effectColorG = g;
	m_effectColorB = b;
	m_effectColorA = a;
}

/*_*/



