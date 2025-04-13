
#include <windows.h>
#include <math.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nnnUtilLib\myMouseStatus.h"


#include "allMiniGame.h"
#include "miniGameBase.h"

#include "miniGameNurie.h"

CMiniGameNurie::CMiniGameNurie(CAllMiniGame* lpAllMiniGame,int layoutParamKosuu,int* layoutParam) : CMiniGameBase(lpAllMiniGame,layoutParamKosuu,layoutParam)
{
	m_sizeX = 64;
	m_sizeY = 64;

	m_mask = new char[m_sizeX*m_sizeY];

	for (int j=0;j<64;j++)
	{
		for (int i=0;i<64;i++)
		{
			int k = i + j * 64;

			int r = int(sqrt((double)((j-32)*(j-32) + (i-32)*(i-32)) * 1.5));
			if (r>=48)
			{
				m_mask[k] = 0;
			}
			else
			{
				int d = 48 - r;
				d += 2;
				d += (rand() % 5);
				m_mask[k] = (char)d;
			}
		}
	}

}


CMiniGameNurie::~CMiniGameNurie()
{
	End();
}


void CMiniGameNurie::End(void)
{
	DELETEARRAY(m_mask);
}

int CMiniGameNurie::Init(void)
{
//	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();

//	m_pic2->Put(0,0,FALSE);
//	m_commonBG->GetScreen();
//	m_commonBG->Flush();
	m_bgCreateFlag = FALSE;

	m_updateFlag = FALSE;
	CAreaControl::SetNextAllPrint();


	m_oldX = -1;
	m_oldY = -1;

	return -1;
}

int CMiniGameNurie::Calcu(void)
{
	if (m_bgCreateFlag == FALSE)
	{
		m_bgCreateFlag = TRUE;
		m_pic2->Put(0,0,FALSE);
		m_commonBG->GetScreen();
		m_commonBG->Flush();
	}

	m_updateFlag = FALSE;

//	if (m_mouseStatus->CheckClick(1)) return 0;

	POINT pt = m_mouseStatus->GetZahyo();
	int newX = pt.x;
	int newY = pt.y;

	BOOL flg = FALSE;

	BOOL right = FALSE;

	if (m_mouseStatus->CheckClick())
	{
		flg = TRUE;
	}

	if (m_mouseStatus->CheckClick(1))
	{
		flg = TRUE;
		right = TRUE;
	}

	if (m_mouseStatus->GetTrig(0))
	{
		if ((newX != m_oldX) || (newY != m_oldY))
		{
			flg = TRUE;
		}
	}
	if (m_mouseStatus->GetTrig(1))
	{
		if ((newX != m_oldX) || (newY != m_oldY))
		{
			flg = TRUE;
			right = TRUE;
		}
	}

	m_oldX = newX;
	m_oldY = newY;

	if (flg)
	{
		int startX = pt.x - m_sizeX / 2;
		int startY = pt.y - m_sizeY / 2;
		int endX = pt.x + m_sizeX / 2;
		int endY = pt.y + m_sizeY / 2;

		int srcX = 0;
		int srcY = 0;

		int screenSizeX = CMyGraphics::GetScreenSizeX();
		int screenSizeY = CMyGraphics::GetScreenSizeY();

		if ((startX<screenSizeX) && (startY<screenSizeY) && (endX>0) && (endY>0))
		{

			if (startX < 0)
			{
				srcX = - startX;
				startX = 0;
			}

			if (startY < 0)
			{
				srcY = -startY;
				startY = 0;
			}

			if (endX > screenSizeX)
			{
				endX = screenSizeX;
			}

			if (endY >= screenSizeY)
			{
				endY = screenSizeY;
			}

			int sizeX = endX - startX;
			int sizeY = endY - startY;

			if ((sizeX > 0) && (sizeY > 0))
			{
				m_updateFlag = TRUE;
				m_updateAreaX = startX;
				m_updateAreaY = startY;
				m_updateAreaSizeX = sizeX;
				m_updateAreaSizeY = sizeY;

				CPicture* pic1 = m_pic1;
				CPicture* pic2 = m_pic2;

				if (right)
				{
					CPicture* tmp = pic1;
					pic1 = pic2;
					pic2 = tmp;
				}

				int* dst = (int*)(m_commonBG->GetBuffer());
				SIZE sz = m_commonBG->GetPicSize();
				int dstPitch = sz.cx * sizeof(int);
	
				dst += startX;
				dst += startY * sz.cx;
				
				int* src = (int*)(pic1->GetBuffer());
				SIZE sz2 = pic1->GetPicSize();
				int srcPitch = sz2.cx * sizeof(int);

				src += startX;
				src += startY * sz2.cx;

				int maskPitch = m_sizeX;
				char* mask = m_mask;
				mask += srcX;
				mask += srcY * m_sizeX;

				int loopX = sizeX;
				int loopY = sizeY;

#if defined _WIN64
				INT32* src64Org = src;
				INT32* dst64Org = dst;
				char* mask64Org = mask;

				for (int j = 0; j < loopY; j++)
				{
					INT32* src64 = src64Org;
					INT32* dst64 = dst64Org;
					char* mask64 = mask64Org;
					for (int i = 0; i < loopX; i++)
					{
						INT32 maskData = ((INT32)(*mask64)) & 0xff;
						if (maskData == 255)
						{
							*dst64 = *src64;
						}
						else if (maskData > 0)
						{
							INT32 maskMul = maskData;
							INT32 srcData = *src64;
							INT32 dstData = *dst64;
							INT32 srcR = (srcData >> 16) & 0xff;
							INT32 srcG = (srcData >> 8) & 0xff;
							INT32 srcB = (srcData) & 0xff;
							INT32 dstR = (dstData >> 16) & 0xff;
							INT32 dstG = (dstData >> 8) & 0xff;
							INT32 dstB = (dstData) & 0xff;
							INT32 r = srcR * maskMul + (256 - maskMul) * dstR;
							INT32 g = srcG * maskMul + (256 - maskMul) * dstG;
							INT32 b = srcB * maskMul + (256 - maskMul) * dstB;
							r >>= 8;
							g >>= 8;
							b >>= 8;
							INT32 color = (r << 16) | (g << 8) | b;
							*dst64 = color;
						}
						src64++;
						dst64++;
						mask64++;
					}
					src64Org += srcPitch / 4;
					dst64Org += dstPitch / 4;
					mask64Org += maskPitch;
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

					pxor mm0,mm0

					mov esi,src
					mov edi,dst
					mov ebx,mask

					mov edx,loopY
LOOP1:
					push esi
					push edi
					push ebx


					mov ecx,loopX
LOOP2:
					mov eax,[esi]
					movd mm1,eax
					mov eax,[edi]
					movd mm2,eax
					punpcklbw mm1,mm0
					punpcklbw mm2,mm0

					xor eax,eax
					mov al,[ebx]
					or eax,eax
					jz SKIP1

					movd mm3,eax
					neg eax
					add eax,256
					movd mm4,eax

					punpcklwd mm3,mm3
					punpcklwd mm4,mm4
					punpckldq mm3,mm3
					punpckldq mm4,mm4

					pmullw mm1,mm3
					pmullw mm2,mm4

					paddw mm1,mm2
					psrlw mm1,8
					packuswb mm1,mm1
					movd eax,mm1

					mov [edi],eax
SKIP1:
					add esi,4
					add edi,4
					inc ebx
					dec ecx
					jnz LOOP2

					pop ebx
					pop edi
					pop esi
					add ebx,maskPitch
					add edi,dstPitch
					add esi,srcPitch
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
#endif
			}
		}
	}

	return -1;
}

int CMiniGameNurie::Print(void)
{
	BOOL b = CAreaControl::CheckAllPrintMode();
	if (b)
	{
//		m_pic2->Put(0,0,FALSE);
		m_commonBG->Put(0,0,FALSE);
		return -1;
	}

//	m_pic2->Blt(m_updateAreaX,m_updateAreaY,m_updateAreaX,m_updateAreaY,m_updateAreaSizeX,m_updateAreaSizeY,FALSE);
	m_commonBG->Blt(m_updateAreaX,m_updateAreaY,m_updateAreaX,m_updateAreaY,m_updateAreaSizeX,m_updateAreaSizeY,FALSE);
	CAreaControl::AddArea(m_updateAreaX,m_updateAreaY,m_updateAreaSizeX,m_updateAreaSizeY);

	return -1;
}




/*_*/

