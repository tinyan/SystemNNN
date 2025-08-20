//
// effectshake.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectshake.h"

int CEffectShake::m_shakeTable[8] = {-16,-12,16,12};

CEffectShake::CEffectShake(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(1);
	Create("Shake");
#endif
}

CEffectShake::~CEffectShake()
{
	End();
}

void CEffectShake::End(void)
{
}

BOOL CEffectShake::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[3];
	int k = paraKosuu;
	if (k>3) k = 3;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;
	if (paraKosuu<2) para[1] = 0;
	if (paraKosuu<3) para[2] = 0;


	lp->countMax = para[0];
	lp->flag = TRUE;
	lp->command = EFFECT_SHAKE;
	lp->count = 0;
	
	for (i=0;i<3;i++)
	{
		lp->para[i] = para[i];
	}



	return TRUE;
}


BOOL CEffectShake::CountIsMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	if (lp->para[2] == 0)
	{
		lp->command = EFFECT_NOP;
		if (lp->pic == -1)
		{
			lp->flag = FALSE;
		}
	}
	else
	{
		lp->count = 0;
	}
	return TRUE;
}


void CEffectShake::BeginPrint(LPVOID para,int layer)
{

}

void CEffectShake::Init(LPVOID para,int layer)
{
}

void CEffectShake::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	if (lp->para[2] == 0)
	{
		if (lp->count >= lp->countMax)
		{
			lp->count -= lp->countMax;
		}
	}
}


void CEffectShake::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();



	int c = lp->count;
	int mx = lp->countMax;
	if (c >= mx) return;

	c = mx - c;
	c %= 4;

	int dltx = m_shakeTable[c];

	if (dltx == 0) return;

//char mes[256];
//intf(mes,"[SHAKE %d]",dltx);
//tputDebugString(mes);

	int* src = CMyGraphics::GetScreenBuffer();
	int* dst = CMyGraphics::GetScreenBuffer();

	int ln;

	int srcPitch = screenSizeX * sizeof(int);
	int dstPitch = screenSizeX * sizeof(int);


	if (lp->para[1] == 0)
	{

		if (dltx>0)
		{
			ln = screenSizeX - dltx;
			src += dltx;		
		}
		else
		{
			ln = screenSizeX + dltx;
			dst -= dltx;
			src += ln;
			dst += ln;
			src--;
			dst--;
		}

#if defined _WIN64
		{
			INT32* src64Org = src;
			INT32* dst64Org = dst;

			for (int j = 0; j < screenSizeY; j++)
			{
				INT32* src64 = src64Org;
				INT32* dst64 = dst64Org;
				for (int i = 0; i < ln; i++)
				{
					*dst64 = *src64;
					if (dltx > 0)
					{
						src64++;
						dst64++;
					}
					else
					{
						src64--;
						dst64--;
					}
				}
				src64Org += dstPitch / 4;
				dst64Org += dstPitch / 4;

			}
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

			mov esi,src
			mov edi,dst
			mov eax,dltx

			test eax,80000000h
			jnz SKIP1
			cld
			jmp skip2
SKIP1:
			std
SKIP2:
			mov edx,screenSizeY
LOOP1:
			push esi
			push edi
			mov ecx,ln
			rep movsd
			pop edi
			pop esi
			add esi,srcPitch
			add edi,dstPitch
			dec edx
			jnz LOOP1

			cld
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
	else	//‚½‚Ä
	{
		int dlty = m_shakeTable[c];

		if (dlty == 0) return;


		int lPitch = screenSizeX * 4;

		if (dlty>0)
		{
			ln = screenSizeY - dlty;
			src += dlty * screenSizeX;		
		}
		else
		{
			ln = screenSizeY + dlty;
			dst -= dlty * screenSizeX;

			src += ln*screenSizeX;
			dst += ln*screenSizeX;
			src-=screenSizeX;
			dst-=screenSizeX;
			lPitch = -screenSizeX*4;
		}
#if defined _WIN64
		{
			INT32* src64Org = src;
			INT32* dst64Org = dst;

			for (int j = 0; j < ln; j++)
			{
				INT32* src64 = src64Org;
				INT32* dst64 = dst64Org;
				for (int i = 0; i < screenSizeX; i++)
				{
					*dst64 = *src64;
					src64++;
					dst64++;
				}

				if (dltx > 0)
				{
					src64Org += lPitch / 4;
					dst64Org += lPitch / 4;
				}
				else
				{
					src64Org -= lPitch / 4;
					dst64Org -= lPitch / 4;
				}

			}

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

			mov esi,src
			mov edi,dst
			mov eax,lPitch

			mov edx,ln
			cld
LOOP2:
			push esi
			push edi
			mov ecx,screenSizeX
			rep movsd
			pop edi
			pop esi
			add esi,eax
			add edi,eax
			dec edx
			jnz LOOP2

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

/*_*/

