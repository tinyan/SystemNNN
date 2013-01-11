//
// effectKe.cpp
//
#include "..\nyanEffectLib\includer.h"

#include "effectSentence.h"



CEffectSentence::CEffectSentence(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
}


CEffectSentence::~CEffectSentence()
{
	End();
}

void CEffectSentence::End(void)
{
}

BOOL CEffectSentence::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int para[16];
	int k = paraKosuu;
	if (k>16) k = 16;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;	//frame

	if (paraKosuu<2) para[1] = 32;	//sizeX
	if (paraKosuu<3) para[2] = 32;	//sizeY

	if (paraKosuu<4) para[3] = 0;	//tate
	if (paraKosuu<5) para[4] = 0;	//ƒƒCƒvŽí—Þ
	if (paraKosuu<6) para[5] = 1;	//•ª‰ð”\
	if (para[5] < 1) para[5] = 1;

	if (paraKosuu<7) para[6] = 0;	//subtype
	if (paraKosuu<8) para[7] = 0;	//subframe



	lp->flag = TRUE;
	lp->command = EFFECT_SENTENCE;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectSentence::CountIsMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

//	lp->command = EFFECT_NOP;
//	if (lp->pic == -1)
//	{
//		lp->flag = FALSE;
//	}
//
//	return TRUE;
	return FALSE;
}


void CEffectSentence::BeginPrint(LPVOID para,int layer)
{

}

void CEffectSentence::Init(LPVOID para,int layer)
{

}




void CEffectSentence::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
}



void CEffectSentence::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int countMax = lp->countMax;	
	int count = lp->count;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	int sizeX = lp->para[1];
	int sizeY = lp->para[2];

	SIZE sz = lpPic->GetPicSize();

	int yokoKosuu = sz.cx / sizeX;
	int tateKosuu = sz.cy / sizeY;
	if ((yokoKosuu <= 0) || (tateKosuu <= 0)) return;


	int tateyoko = lp->para[3];
	int wipe = lp->para[4];
	int bunkainou = lp->para[5];

	int subType = lp->para[6];
	int subFrame = lp->para[7];


	int ml = yokoKosuu * tateKosuu;
	int firstDiv = yokoKosuu;
	int lastDiv = tateKosuu;
	if (tateyoko)
	{
		firstDiv = tateKosuu;
		lastDiv = yokoKosuu;
	}

	int d = CCalcuSpeed::calcu(count,countMax,0,ml*bunkainou,subFrame,subType);


	int printed = d / bunkainou;
	int printingPercent = d % bunkainou;
	printingPercent *= 100;
	printingPercent /= bunkainou;

	int writeBlock = printed / firstDiv;
	int centerBlock = printed % firstDiv;

	int printingFirst = (printed) % firstDiv;
	int printingLast = (printed) / firstDiv;


	int putX0 = lp->dst.left;
	int putY0 = lp->dst.top;

	if (printed > 0)
	{
		if (writeBlock > 0)
		{
			if (tateyoko == 0)
			{
				int putSizeX = yokoKosuu * sizeX;
				int putSizeY = writeBlock * sizeY;
				int putX = putX0 + 0;
				int putY = putY0 + 0;
				int srcX = 0;
				int srcY = 0;
				lpPic->Blt(putX,putY,srcX,srcY,putSizeX,putSizeY,TRUE);
			}
			else
			{
				int putSizeX = writeBlock * sizeX;
				int putSizeY = tateKosuu * sizeY;
				int putX = putX0 + (yokoKosuu - writeBlock) * sizeX;
				int putY = putY0 + 0;
				int srcX = (yokoKosuu - writeBlock) * sizeX;
				int srcY = 0;
				lpPic->Blt(putX,putY,srcX,srcY,putSizeX,putSizeY,TRUE);

			}
		}

		if (centerBlock > 0)
		{
			if (tateyoko == 0)
			{
				int putSizeX = centerBlock * sizeX;
				int putSizeY = sizeY;
				int putX = putX0 + 0;
				int putY = putY0 + writeBlock * sizeY;
				int srcX = 0;
				int srcY = writeBlock * sizeY;
				lpPic->Blt(putX,putY,srcX,srcY,putSizeX,putSizeY,TRUE);
			}
			else
			{
				int putSizeX = sizeX;
				int putSizeY = centerBlock * sizeY;
				int putX = putX0 + (yokoKosuu - writeBlock - 1) * sizeX;
				int putY = putY0 + 0;
				int srcX = (yokoKosuu - writeBlock - 1) * sizeX;
				int srcY = 0;
				lpPic->Blt(putX,putY,srcX,srcY,putSizeX,putSizeY,TRUE);

			}

		}
	}

	if (printingPercent > 0)
	{
		int putX = putX0;
		int putY = putY0;
		int srcX = 0;
		int srcY = 0;

		if (tateyoko == 0)
		{
			putX += printingFirst * sizeX;
			putY += printingLast * sizeY;
			srcX += printingFirst * sizeX;
			srcY += printingLast * sizeY;

		}
		else
		{
			putY += printingFirst * sizeY;
			putX += (yokoKosuu - printingLast - 1) * sizeX;
			srcY += printingFirst * sizeY;
			srcX += (yokoKosuu - printingLast - 1) * sizeX;
		}

		if (printingPercent >= 100)
		{
			lpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
		}
		else
		{
			//type

			if (wipe == 0)
			{
				lpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
			}
			else if (wipe == 1)
			{
				lpPic->TransLucentBlt3(putX,putY,srcX,srcY,sizeX,sizeY,printingPercent);
			}
			else if ((wipe == 2) || (wipe == 3))
			{
				int putSizeX = (sizeX * printingPercent) / 100;
				int putSizeY = (sizeY * printingPercent) / 100;
				int deltaX = (sizeX - putSizeX) / 2;
				int deltaY = (sizeY - putSizeY) / 2;

				if ((putSizeX > 0) && (putSizeY > 0))
				{
					if (wipe == 2)
					{
						lpPic->StretchBlt1(putX+deltaX,putY+deltaY,putSizeX,putSizeY,srcX,srcY,sizeX,sizeY);
					}
					else
					{
						lpPic->Blt(putX+deltaX,putY+deltaY,srcX+deltaX,srcY+deltaY,putSizeX,putSizeY,TRUE);
					}
				}
			}
			else if (wipe == 4) 
			{
				int putSizeX = (sizeX * printingPercent) / 100;
				int putSizeY = (sizeY * printingPercent) / 100;

				if (tateyoko == 0)
				{
					putSizeY = sizeY;
				}
				else
				{
					putSizeX = sizeX;
				}


				lpPic->Blt(putX,putY,srcX,srcY,putSizeX,putSizeY,TRUE);

			}
			else if ((wipe == 5) || (wipe == 6))
			{
				int putSizeX = (sizeX * (200-printingPercent)) / 100;
				int putSizeY = (sizeY * (200-printingPercent)) / 100;
				int deltaX = (sizeX - putSizeX) / 2;
				int deltaY = (sizeY - putSizeY) / 2;

				if ((putSizeX > 0) && (putSizeY > 0))
				{
					if (wipe == 5)
					{
						lpPic->StretchBlt1(putX+deltaX,putY+deltaY,putSizeX,putSizeY,srcX,srcY,sizeX,sizeY);
					}
					else
					{
						lpPic->StretchBlt1(putX+deltaX,putY+deltaY,putSizeX,putSizeY,srcX,srcY,sizeX,sizeY,printingPercent);
					}

				}
			}
		}
	}
}


BOOL CEffectSentence::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}



/*_*/

