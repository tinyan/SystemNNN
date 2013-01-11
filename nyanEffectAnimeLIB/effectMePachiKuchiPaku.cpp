//
// effectMePachiKuchiPaku.cpp
//

#include "..\nyanEffectLib\includer.h"
#include "..\nyanlib\include\areaControl.h"
#include "effectMePachiKuchiPaku.h"


CEffectMePachiKuchiPaku::CEffectMePachiKuchiPaku(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectMePachiKuchiPaku::~CEffectMePachiKuchiPaku()
{
	End();
}

void CEffectMePachiKuchiPaku::End(void)
{
}

BOOL CEffectMePachiKuchiPaku::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[16];
	int k = paraKosuu;
	if (k>13) k = 13;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}
	if (paraKosuu<1) para[0] = 20;	//dummy frame
	if (paraKosuu<2) para[1] = 32;	//sizeX
	if (paraKosuu<3) para[2] = 32;	//sizeY
	if (paraKosuu<4) para[3] = 2;	//pattern kosuu
	if (paraKosuu<5) para[4] = -1;	//buffer 

	if (paraKosuu<6) para[5] = 0;	//reverseFlag
	if (paraKosuu<7) para[6] = 0;	//0:目 1: +2 抜きあり
	if (paraKosuu<8) para[7] = 1;	//speed wait

	if (paraKosuu<9) para[8] = 40;	//平均ウエイトタイム目
	if (paraKosuu<10) para[9] = 80;	//ランダム率0-100

	if (paraKosuu<11) para[10] = 4;	//平均ウエイトタイム口
	if (paraKosuu<12) para[11] = 80;	//ランダム率0-100

	if (paraKosuu<13) para[12] = 0;	//ショート表示ランダム率0-99

	lp->flag = TRUE;
	for (i=0;i<13;i++)
	{
		lp->para[i] = para[i];
	}

	lp->para[13] = 0;	//animecount
	SetNewAnimeCountMax(lpEffect,layer);	//para[14]

	lp->count = 0;
	lp->countMax = 9999;
	lp->command = EFFECT_MEPACHIKUCHIPAKU;


	return TRUE;
}


BOOL CEffectMePachiKuchiPaku::CountIsMax(LPVOID lpEffect,int layer)
{
	if (lpEffect != NULL)
	{
		layer += 0;
	}

	return FALSE;
}


void CEffectMePachiKuchiPaku::BeginPrint(LPVOID para,int layer)
{

}

void CEffectMePachiKuchiPaku::Init(LPVOID para,int layer)
{
}


void CEffectMePachiKuchiPaku::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	lp->count = 0;	//無限ループ

	int c = lp->para[13];
	c++;
	lp->para[13] = c;

	int limit = lp->para[14];

	if (c < limit) return;

	int kosuu = lp->para[3];
	int rev = lp->para[5];
	int speed = lp->para[7];

	int dv = kosuu;
	if (rev)
	{
		dv += (kosuu - 2);
	}

	dv *= speed;

	c -= limit;

	BOOL b = FALSE;

	//check short
	if (lp->para[12])
	{
		if (c == ((kosuu-1)*speed))
		{
			if ((rand() % 100) < (lp->para[12]))
			{
				if (rev)
				{
					lp->para[13] += speed * 2;
					c += speed * 2;
				}
				else
				{
					b = TRUE;
				}
			}
		}
	}



	if ((c >= dv) || b)
	{
		SetNewAnimeCountMax(lpEffect,layer);
		CAreaControl::SetNextAllPrint();
	}
}


void CEffectMePachiKuchiPaku::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int c = lp->para[13];

	int limit = lp->para[14];

	if (c < limit) return;


	if (lp->para[6] & 1)	//くちぱくチェック
	{
		if (m_allEffect->CheckSpeaking() == FALSE)
		{
			return;
		}
	}




	int kosuu = lp->para[3];
	int rev = lp->para[5];
	int speed = lp->para[7];

	int dv = kosuu;
	if (rev)
	{
		dv += (kosuu - 2);
	}

	dv *= speed;

	c -= limit;
	c /= speed;

	if (rev)
	{
		if (c >= kosuu)
		{
			c -= kosuu;
			c = kosuu - 1 - c;
		}
	}

	if (c < 0) c = 0;

	int sizeX = lp->para[1];
	int sizeY = lp->para[2];
	int srcX = sizeX * c;
	int srcY = 0;

	int buf = lp->para[4];
	if (buf == -1) buf = layer;

	CPicture* lpPic = m_allEffect->GetPicture(buf);
	if (lpPic == NULL) return;


//	RECT rc;
//	m_effect->GetMyRect(buf,5,&rc);
	POINT rcPoint = m_allEffect->GetDstPoint(buf);

//	int putX = rc.left;
//	int putY = rc.top;
	int putX = rcPoint.x;
	int putY = rcPoint.y;


	if (lp->para[6] & 2)
	{
		lpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
	}
	else
	{
		lpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,FALSE);
	}
	CAreaControl::AddArea(putX,putY,sizeX,sizeY);
}



BOOL CEffectMePachiKuchiPaku::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}

BOOL CEffectMePachiKuchiPaku::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}

void CEffectMePachiKuchiPaku::SetNewAnimeCountMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	lp->para[13] = 0;

	int avr = lp->para[8];
	int rnd = lp->para[9];

	if (lp->para[6] & 1)
	{
		avr = lp->para[10];
		rnd = lp->para[11];
	}

	int dv = (rnd * 2 * avr) / 100;
	if (dv<1) dv = 1;

	int r = rand() % dv;
	r -= dv / 2;
	r += avr;
	if (r<1) r = 1;

	lp->para[14] = r;
}


