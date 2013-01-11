//
// effecthaikeiYure.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effecthaikeiYure.h"

//int CEffectShake::m_shakeTable[8] = {-16,-12,16,12};

CEffectHaikeiYure::CEffectHaikeiYure(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(1);
	Create("HaikeiYure");
#endif
}

CEffectHaikeiYure::~CEffectHaikeiYure()
{
	End();
}

void CEffectHaikeiYure::End(void)
{
}

BOOL CEffectHaikeiYure::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[14];
	int k = paraKosuu;
	if (k>14) k = 14;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;	//frame

	if (paraKosuu<2) para[1] = 20;	//leftright
	if (paraKosuu<3) para[2] = 0;	//updown

	if (paraKosuu<4) para[3] = 25;	//leftrightspeed
	if (paraKosuu<5) para[4] = 25;	//updown speed

	if (paraKosuu<6) para[5] = 0;	//レイヤーにかける
	if (paraKosuu<7) para[6] = 0;	//0開始をずらす

	if (paraKosuu<8) para[7] = 0;	//0ないぶぶんは元の絵 1:ぬりつぶし

	if (paraKosuu<9) para[8] = 0;	//ぬりつぶし R
	if (paraKosuu<10) para[9] = 0;	//ぬりつぶし G
	if (paraKosuu<11) para[10] = 0;	//ぬりつぶし B

	if (paraKosuu<12) para[11] = 0;	//たいぷsw
	if (paraKosuu<13) para[12] = 0;	//たいぷ
	if (paraKosuu<14) para[13] = 0;//さぶふれーむ


	lp->countMax = para[0];
	lp->flag = TRUE;
	lp->command = EFFECT_HAIKEIYURE;
	lp->count = 0;

	for (i=0;i<14;i++)
	{
		lp->para[i] = para[i];
	}

	lp->para[14] = para[6];
	lp->para[15] = para[6];

	return TRUE;
}


BOOL CEffectHaikeiYure::CountIsMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	lp->command = EFFECT_NOP;
	if (lp->pic == -1)
	{
		lp->flag = FALSE;
	}
	return TRUE;
}


void CEffectHaikeiYure::BeginPrint(LPVOID para,int layer)
{

}

void CEffectHaikeiYure::Init(LPVOID para,int layer)
{
}

void CEffectHaikeiYure::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int ps1 = lp->para[14];
	int ps2 = lp->para[15];

	ps1 += lp->para[3];
	ps2 += lp->para[4];

	if (ps1<0) ps1 = 0;
	if (ps2<0) ps2 = 0;

	ps1 %= 100;
	ps2 %= 100;

	lp->para[14] = ps1;
	lp->para[15] = ps2;
}

#if defined _TINYAN3DLIB_
void CEffectHaikeiYure::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int count = lp->count;
	int countMax = lp->countMax;

	int ml = 100;
	if (lp->para[11])
	{
		ml = CCalcuSpeed::calcu(count,countMax,0,100,lp->para[13],lp->para[12]);
	}

	int leftright = lp->para[1];
	int updown = lp->para[2];

	leftright *= ml;
	leftright /= 100;

	updown *= ml;
	updown /= 100;


	int ps1 = (lp->para[6] + lp->para[3] * count + 100 - 25) % 100;
	int ps2 = (lp->para[6] + lp->para[4] * count + 100 - 25) % 100;

//	int ps1 = lp->para[14];
//	int ps2 = lp->para[15];

	ps1 -= 25;
	ps1 += 100;
	ps1 %= 100;

	ps2 -= 25;
	ps2 += 100;
	ps2 %= 100;

	if (ps1>50) ps1 = 100 - ps1;
	if (ps2>50) ps2 = 100 - ps2;

	int dx = -leftright + (leftright * 2 * ps1) / 50;
	int dy = -updown + (updown * 2 * ps2) / 50;

	int fillType = lp->para[7];
	int colorR = lp->para[8];
	int colorG = lp->para[9];
	int colorB = lp->para[10];

	int layerType = lp->para[5];


	int pic = lp->pic;
	if (layerType == 0)
	{
		if (pic == -1) return;
	}

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (layerType == 0)
	{
		if (lpPic == NULL) return;
	}



	if (layerType == 1)
	{
		MoveScreen(dx,dy);
		return;
	}




	lpPic->Blt(dx,dy,0,0,screenSizeX,screenSizeY,FALSE);
	//すきま
	if (dy != 0)
	{
		int putX = 0;
		int putY = 0;
		int sizeX = screenSizeX;
		int sizeY = dy;

		if (dy < 0)
		{
			putY = screenSizeY + dy;
			sizeY = -dy;
		}

		if (sizeY>0)
		{
			if (fillType == 0)
			{
				lpPic->Blt(putX,putY,putX,putY,sizeX,sizeY,FALSE);
			}
			else
			{
				CAllGeo::BoxFill(putX,putY,sizeX,sizeY,colorR,colorG,colorB);
			}
		}
	}


	if (dx != 0)
	{
		int putX = 0;
		int putY = 0;
		int sizeX = dx;
		int sizeY = screenSizeY;

		if (dy>0)
		{
			sizeY -= dy;
			putY += dy;
		}
		else if (dy<0)
		{
			sizeY += dy;
		}

		if (sizeY>0)
		{
			if (dx<0)
			{
				sizeX = -dx;
				putX = screenSizeX + dx;
			}

			if (sizeX>0)
			{
				if (fillType == 0)
				{
					lpPic->Blt(putX,putY,putX,putY,sizeX,sizeY,FALSE);
				}
				else
				{
					CAllGeo::BoxFill(putX,putY,sizeX,sizeY,colorR,colorG,colorB);
				}
			}
		}
	}

}






void CEffectHaikeiYure::MoveScreen(int dx, int dy)
{
	if ((dx == 0) && (dy == 0)) return;
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (dx>=screenSizeX) return;
	if (dy>=screenSizeY) return;

	if (dx <= -screenSizeX) return;
	if (dy <= -screenSizeY) return;

	ExchangeScreenAndBuffer();
	SetTexture(GetBufferTexture());

	POINT dstPoint;
	dstPoint.x = dx;
	dstPoint.y = dy;
	SIZE dstSize;
	dstSize.cx = screenSizeX;// - abs(dx);
	dstSize.cy = screenSizeY;// - abs(dy);
	POINT srcPoint;
	srcPoint.x = 0;
	srcPoint.y = 0;
//	if ((dstSize.cx > 0) && (dstSize.cy > 0))
//	{
		Blt(dstPoint,dstSize,srcPoint);
//	}


	//すきま
	if (dy != 0)
	{
		dstPoint.x = 0;
		if (dy>0)
		{
			dstPoint.y = 0;
		}
		else
		{
			dstPoint.y = screenSizeY + dy;
		}
		dstSize.cx = screenSizeX;
		dstSize.cy = abs(dy);
		srcPoint = dstPoint;
		if ((dstSize.cx > 0) && (dstSize.cy > 0))
		{
			Blt(dstPoint,dstSize,srcPoint);
		}
	}

	if (dx != 0)
	{
		dstPoint.y = 0;
		if (dx>0)
		{
			dstPoint.x = 0;
		}
		else
		{
			dstPoint.x = screenSizeX + dx;
		}
		dstSize.cy = screenSizeY;
		dstSize.cx = abs(dx);
		srcPoint = dstPoint;
		if ((dstSize.cx > 0) && (dstSize.cy > 0))
		{
			Blt(dstPoint,dstSize,srcPoint);
		}
	}

	return;

}

#else

void CEffectHaikeiYure::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int count = lp->count;
	int countMax = lp->countMax;

	int ml = 100;
	if (lp->para[11])
	{
		ml = CCalcuSpeed::calcu(count,countMax,0,100,lp->para[13],lp->para[12]);
	}

	int leftright = lp->para[1];
	int updown = lp->para[2];

	leftright *= ml;
	leftright /= 100;

	updown *= ml;
	updown /= 100;


	int ps1 = (lp->para[6] + lp->para[3] * count + 100 - 25) % 100;
	int ps2 = (lp->para[6] + lp->para[4] * count + 100 - 25) % 100;

//	int ps1 = lp->para[14];
//	int ps2 = lp->para[15];

	ps1 -= 25;
	ps1 += 100;
	ps1 %= 100;

	ps2 -= 25;
	ps2 += 100;
	ps2 %= 100;

	if (ps1>50) ps1 = 100 - ps1;
	if (ps2>50) ps2 = 100 - ps2;

	int dx = -leftright + (leftright * 2 * ps1) / 50;
	int dy = -updown + (updown * 2 * ps2) / 50;

	int fillType = lp->para[7];
	int colorR = lp->para[8];
	int colorG = lp->para[9];
	int colorB = lp->para[10];

	int layerType = lp->para[5];


	int pic = lp->pic;
	if (layerType == 0)
	{
		if (pic == -1) return;
	}

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (layerType == 0)
	{
		if (lpPic == NULL) return;
	}



	if (layerType == 1)
	{
		MoveScreen(dx,dy);
		return;
	}




	lpPic->Blt(dx,dy,0,0,screenSizeX,screenSizeY,FALSE);
	//すきま
	if (dy != 0)
	{
		int putX = 0;
		int putY = 0;
		int sizeX = screenSizeX;
		int sizeY = dy;

		if (dy < 0)
		{
			putY = screenSizeY + dy;
			sizeY = -dy;
		}

		if (sizeY>0)
		{
			if (fillType == 0)
			{
				lpPic->Blt(putX,putY,putX,putY,sizeX,sizeY,FALSE);
			}
			else
			{
				CAllGeo::BoxFill(putX,putY,sizeX,sizeY,colorR,colorG,colorB);
			}
		}
	}


	if (dx != 0)
	{
		int putX = 0;
		int putY = 0;
		int sizeX = dx;
		int sizeY = screenSizeY;

		if (dy>0)
		{
			sizeY -= dy;
			putY += dy;
		}
		else if (dy<0)
		{
			sizeY += dy;
		}

		if (sizeY>0)
		{
			if (dx<0)
			{
				sizeX = -dx;
				putX = screenSizeX + dx;
			}

			if (sizeX>0)
			{
				if (fillType == 0)
				{
					lpPic->Blt(putX,putY,putX,putY,sizeX,sizeY,FALSE);
				}
				else
				{
					CAllGeo::BoxFill(putX,putY,sizeX,sizeY,colorR,colorG,colorB);
				}
			}
		}
	}

}






void CEffectHaikeiYure::MoveScreen(int dx, int dy)
{
	if ((dx == 0) && (dy == 0)) return;
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (dx>=screenSizeX) return;
	if (dy>=screenSizeY) return;

	if (dx <= -screenSizeX) return;
	if (dy <= -screenSizeY) return;


	int* src = CMyGraphics::GetScreenBuffer();
	int* dst = CMyGraphics::GetScreenBuffer();

	int srcPitch = screenSizeX * sizeof(int);
	int dstPitch = screenSizeX * sizeof(int);


	int dstX = 0;
	int dstY = 0;
	int srcX = 0;
	int srcY = 0;


	int sizeX = screenSizeX;

	if (dx>0)
	{
		dstX = dx;
		sizeX -= dx;
	}
	else if (dx<0)
	{
		srcX = -dx;
		sizeX += dx;
	}
	if (sizeX<=0) return;


	int sizeY = screenSizeY;
	if (dy>0)
	{
		dstY = dy;
		sizeY -= dy;
	}
	else if (dy<0)
	{
		srcY = -dy;
		sizeY += dy;
	}
	if (sizeY<=0) return;


	if (dy>0)
	{
		srcY += (sizeY-1);
		dstY += (sizeY-1);

		srcPitch *= -1;
		dstPitch *= -1;
	}


	if (dx>=0)
	{
		srcX += (sizeX-1);
		dstX += (sizeX-1);

	}

	src += (srcY * screenSizeX);
	dst += (dstY * screenSizeX);

	src += srcX;
	dst += dstX;

	int ddx = dx;

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

		mov eax,ddx
		test eax,80000000h
		jnz MINUS
		std
		jmp START
MINUS:
		cld
START:

		mov edx,sizeY
LOOP1:
		push esi
		push edi

		mov ecx,sizeX
		rep movsd

		pop edi
		pop esi
		add esi,srcPitch
		add edi,dstPitch
		dec edx
		jnz LOOP1

		cld

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}


}
#endif



BOOL CEffectHaikeiYure::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	if (lp->para[5] == 0) return FALSE;

	return TRUE;
}


