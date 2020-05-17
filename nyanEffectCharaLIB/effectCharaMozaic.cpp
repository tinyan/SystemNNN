//
// effectchange.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectCharaMozaic.h"



CEffectCharaMozaic::CEffectCharaMozaic(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
}


CEffectCharaMozaic::~CEffectCharaMozaic()
{
}


void CEffectCharaMozaic::End(void)
{
}


BOOL CEffectCharaMozaic::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr, int layer)
{
//	if (paraKosuu < 2) return FALSE;	//bad!!

	EFFECT* lp = (EFFECT*)lpEffect;

	int k = paraKosuu;
	if (k > 16) k = 16;

	int para[16];
	int i;
	for (i = 0; i < k; i++)
	{
		para[i] = paraPtr[i];
	}

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (paraKosuu < 1) para[0] = 20;
	if (paraKosuu < 2) para[1] = 8;
	if (paraKosuu < 3) para[2] = 8;

	if (paraKosuu < 4) para[3] = 0;
	if (paraKosuu < 5) para[4] = 0;
	if (paraKosuu < 6) para[5] = 0;
	if (paraKosuu < 7) para[6] = 64;
	if (paraKosuu < 8) para[7] = 64;

	if (paraKosuu < 9) para[8] = 0;
	if (paraKosuu < 10) para[9] = 0;
	if (paraKosuu < 11) para[10] = 0;
	if (paraKosuu < 12) para[11] = screenSizeX;
	if (paraKosuu < 13) para[12] = screenSizeY;

	if (paraKosuu < 14) para[13] = 1;
	if (paraKosuu < 15) para[14] = 0;
	if (paraKosuu < 16) para[15] = 100;

	for (i = 0; i < 16; i++)
	{
		lp->para[i] = para[i];
	}

	lp->flag = TRUE;
	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_CHARAMOZAIC;

	return TRUE;
}



BOOL CEffectCharaMozaic::CountIsMax(LPVOID lpEffect, int layer)
{
	return TRUE;
}


void CEffectCharaMozaic::BeginPrint(LPVOID para, int layer)
{
}


void CEffectCharaMozaic::Init(LPVOID para, int layer)
{
}

void CEffectCharaMozaic::Calcu(LPVOID lpEffect, int layer)
{
}

void CEffectCharaMozaic::Print(LPVOID lpEffect, int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	//OutputDebugString("yPrint EffectChangez");
	//return;

	int count = lp->count;
	int countMax = lp->countMax;

	int pic1 = lp->pic;
	if (pic1 == -1) return;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == nullptr) return;

	SIZE sz = lpPic->GetPicSize();
	int picSizeX = sz.cx;
	int picSizeY = sz.cy;

	int srcStartX = 0;
	int srcStartY = 0;
	int srcSizeX = picSizeX;
	int srcSizeY = picSizeY;

	int blockSizeX = lp->para[1];
	int blockSizeY = lp->para[2];

	if (lp->para[3] == 1)
	{
		srcStartX = picSizeX / 2 + lp->para[4];
		srcStartY = picSizeY / 2 + lp->para[5];
		srcSizeX = lp->para[6];
		srcSizeY = lp->para[7];
	}

	bool allClip = false;

	if (srcStartX >= picSizeX) allClip = true;
	if (srcStartY >= picSizeY) allClip = true;
	if (srcStartX + srcSizeX <= 0) allClip = true;
	if (srcStartY + srcSizeY <= 0) allClip = true;


	if ((srcStartX < 0) && !allClip)
	{
		int delta = 0-srcStartX;
		srcSizeX -= delta;
		srcStartX = 0;
		if (srcSizeX <= 0) allClip = true;
	}
	if ((srcStartY < 0) && !allClip)
	{
		int delta = 0 - srcStartY;
		srcSizeY -= delta;
		srcStartY = 0;
		if (srcSizeY <= 0) allClip = true;
	}
	if ((srcStartX + srcSizeX > picSizeX) && !allClip)
	{
		int delta = srcStartX + srcSizeX - picSizeX;
		srcSizeX -= delta;
		if (srcSizeX <= 0) allClip = true;
	}
	if ((srcStartY + srcSizeY > picSizeY) && !allClip)
	{
		int delta = srcStartY + srcSizeY - picSizeY;
		srcSizeY -= delta;
		if (srcSizeY <= 0) allClip = true;
	}





	int targetStartX = 0;
	int targetStartY = 0;
	int targetSizeX = screenSizeX;
	int targetSizeY = screenSizeY;

	if (lp->para[8] == 1)
	{
		targetStartX = lp->para[9];
		targetStartY = lp->para[10];
		targetSizeX = lp->para[11];
		targetSizeY = lp->para[12];
	}


	RECT rc = lp->dst;
	int dstX = srcStartX + rc.left;
	int dstY = srcStartY + rc.top;

	int srcX = srcStartX;
	int srcY = srcStartY;

	if ((targetStartX < 0) && !allClip)
	{
		targetSizeX += targetStartX;
		targetStartX = 0;
		if (targetSizeX <= 0) allClip = true;
	}
	if ((targetStartY < 0) && !allClip)
	{
		targetSizeY += targetStartY;
		targetStartY = 0;
		if (targetSizeY <= 0) allClip = true;
	}
	if ((targetStartX + targetSizeX >= screenSizeX) && !allClip)
	{
		int deltaX = targetStartX + targetSizeX - screenSizeX;
		targetSizeX -= deltaX;
		if (targetSizeX <= 0) allClip = true;
	}
	if ((targetStartY + targetSizeY >= screenSizeY) && !allClip)
	{
		int deltaY = targetStartY + targetSizeY - screenSizeY;
		targetSizeY -= deltaY;
		if (targetSizeY <= 0) allClip = true;
	}




	if (dstX >= targetStartX+targetSizeX) allClip = true;
	if (dstY >= targetStartY+targetSizeY) allClip = true;
	if (dstX + srcSizeX < targetStartX) allClip = true;
	if (dstY + srcSizeY < targetStartY) allClip = true;


	if ((dstX < targetStartX) && !allClip)
	{
		int delta = targetStartX - dstX;
		srcX += delta;
		srcSizeX -= delta;
		dstX = targetStartX;

		if (srcSizeX <= 0) allClip = true;
	}

	if ((dstY < targetStartY) && !allClip)
	{
		int delta = targetStartY - dstY;
		srcY += delta;
		srcSizeY -= delta;
		dstY = targetStartY;

		if (srcSizeY <= 0) allClip = true;
	}


	if ((dstX + srcSizeX >= targetStartX + targetSizeX) && !allClip)
	{
		int deltaX = (dstX + srcSizeX) - (targetStartX + targetSizeX);
		srcSizeX -= deltaX;
		if (srcSizeX <= 0) allClip = true;
	}

	if ((dstY + srcSizeY >= targetStartY + targetSizeY) && !allClip)
	{
		int deltaY = (dstY+srcSizeY) - (targetStartY + targetSizeY);
		srcSizeY -= deltaY;
		if (srcSizeY <= 0) allClip = true;
	}

	int* lpSrcPic = (int*)(lpPic->GetBuffer());
	char* lpMask = lpPic->GetMaskPic();
	if (lpMask == nullptr) return;

	int* screenBuffer = CMyGraphics::GetScreenBuffer();



	//ŠO‘¤

	if (!allClip)
	{
		//ã
		int outSrcX = 0;
		int outSrcY = 0;
		int outSizeX = picSizeX;
		int outSizeY = srcY;
		int outPutX = dstX - srcX;
		int outPutY = dstY - srcY;
		if ((outSizeX > 0) && (outSizeY > 0))
		{
			lpPic->Blt(outPutX, outPutY, outSrcX, outSrcY, outSizeX, outSizeY, TRUE);
		}

		//‰º
		outSrcX = 0;
		outSrcY = srcY + srcSizeY;
		outSizeX = picSizeX;
		outSizeY = picSizeY - (srcY + srcSizeY);
		outPutX = dstX - srcX;
		outPutY = dstY + srcSizeY;
		if ((outSizeX > 0) && (outSizeY > 0))
		{
			lpPic->Blt(outPutX, outPutY, outSrcX, outSrcY, outSizeX, outSizeY, TRUE);
		}

		//‚Ð‚¾‚è
		outSrcX = 0;
		outSrcY = srcY;
		outSizeX = srcX;
		outSizeY = srcSizeY;
		outPutX = dstX - srcX;
		outPutY = dstY;
		if ((outSizeX > 0) && (outSizeY > 0))
		{
			lpPic->Blt(outPutX, outPutY, outSrcX, outSrcY, outSizeX, outSizeY, TRUE);
		}

		//‰E
		outSrcX = srcX + srcSizeX;
		outSrcY = srcY;
		outSizeX = picSizeX - (srcX + srcSizeX);
		outSizeY = srcSizeY;
		outPutX = dstX + srcSizeX;
		outPutY = dstY;
		if ((outSizeX > 0) && (outSizeY > 0))
		{
			lpPic->Blt(outPutX, outPutY, outSrcX, outSrcY, outSizeX, outSizeY, TRUE);
		}
	}
	else
	{
		lpPic->Blt(rc.left , rc.top, 0,0,picSizeX,picSizeY, TRUE);

	}


	if (!allClip)
	{
		for (int offsetY = 0; offsetY < srcSizeY; offsetY += blockSizeY)
		{
			int sizeY = blockSizeY;
			if (offsetY + sizeY > srcSizeY)
			{
				sizeY = srcSizeY - offsetY;
			}



			for (int offsetX = 0; offsetX < srcSizeX; offsetX += blockSizeX)
			{
				int sizeX = blockSizeX;
				if (offsetX + sizeX > srcSizeX)
				{
					sizeX = srcSizeX - offsetX;
				}

				int rx = rand() % sizeX;
				int ry = rand() % sizeY;

				char alpha = *(lpMask + srcX + offsetX + rx + (srcY + offsetY + ry) * picSizeX);

				if (alpha == 0)
				{
					//“§–¾‚Å‚È‚¢dot‚ð‚³‚ª‚·
					if (lp->para[13] == 1)
					{
						for (int i = 0; i < sizeX*sizeY; i++)
						{
							rx = rand() % sizeX;
							ry = rand() % sizeY;

							alpha = *(lpMask + srcX + offsetX + rx + (srcY + offsetY + ry) * picSizeX);
							if (alpha != 0)
							{
								break;
							}

						}

						for (int i = 0; i < sizeX*sizeY; i++)
						{
							rx++;
							if (rx >= sizeX)
							{
								rx = 0;
								ry++;
								ry %= sizeY;
							}

							alpha = *(lpMask + srcX + offsetX + rx + (srcY + offsetY + ry) * picSizeX);
							if (alpha != 0)
							{
								break;
							}

						}

					}
				}

				if (alpha != 0)
				{
					int col = *(lpSrcPic + srcX + offsetX + rx + (srcY + offsetY + ry) * picSizeX);

					int r = (col >> 16) & 0xff;
					int g = (col >> 8) & 0xff;
					int b = (col) & 0xff;

					if (lp->para[13] == 0)
					{
						lpPic->ColorBlt(dstX + offsetX, dstY + offsetY, srcX + offsetX, srcY + offsetY, sizeX, sizeY, true, r, g, b);
					}
					else
					{
						int a = (int)alpha;
						a &= 0xff;

						if (lp->para[14] == 0)
						{
							if (a == 0xff)
							{
								a = 100;
							}
							else
							{
								a = (a * 100) / 255;
							}

						}
						else
						{
							a = lp->para[15];
						}

						if (a == 100)
						{
							CAllGeo::BoxFill(dstX + offsetX, dstY + offsetY, sizeX, sizeY, r, g, b);
						}
						else if (a > 0)
						{
							CAllGeo::TransBoxFill(dstX + offsetX, dstY + offsetY, sizeX, sizeY, r, g, b, a);
						}
					}

				}
			}
		}
	}

}


BOOL CEffectCharaMozaic::CheckNeedPicPrint(LPVOID lpEffect, int layer)
{
	return FALSE;
}



/*_*/

