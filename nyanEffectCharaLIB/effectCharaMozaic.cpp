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
	if (paraKosuu < 2) return FALSE;	//bad!!

	EFFECT* lp = (EFFECT*)lpEffect;

	int k = paraKosuu;
	if (k > 8) k = 8;

	int para[16];
	int i;
	for (i = 0; i < k; i++)
	{
		para[i] = paraPtr[i];
	}
	//para[0] = 20*10;

	if (paraKosuu < 1) para[0] = 20;
	if (paraKosuu < 2) para[1] = 13;
	if (paraKosuu < 3) para[2] = 100;
	if (paraKosuu < 4) para[3] = para[2];

	if (paraKosuu < 5) para[4] = 0;
	if (paraKosuu < 6) para[5] = 0;

	if (paraKosuu < 6) para[6] = 0;
	if (paraKosuu < 7) para[7] = 0;

	for (i = 0; i < 8; i++)
	{
		lp->para[i] = para[i];
	}
	//char mes[256];
	//sprintf(mes,"ÅySetParam EffectChange %dÅz",para[0]);
	//OutputDebugString(mes);
	lp->flag = TRUE;
	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_CHARAMOZAIC;

	return TRUE;
}



BOOL CEffectCharaMozaic::CountIsMax(LPVOID lpEffect, int layer)
{
	//OutputDebugString("[End EffectChange]");

	EFFECT* lp = (EFFECT*)lpEffect;
	lp->count = lp->countMax;

	int count = lp->count;
	int countMax = lp->countMax;
	int transType = lp->para[6];
	int transSubFrame = lp->para[7];
	int ps01 = lp->para[3];
	int ps02 = lp->para[2];

	int transPS = CCalcuSpeed::calcu(count, countMax, ps01, ps02, transSubFrame, transType);

	int changeType = lp->para[4];
	int changeSubFrame = lp->para[5];

	int changePS = CCalcuSpeed::calcu(count, countMax, 100, 0, changeSubFrame, changeType);

	int ps1 = (changePS * transPS) / 100;
	if (ps1 < 0) ps1 = 0;
	if (ps1 > 100) ps1 = 100;

	int ps2 = ((100 - changePS) * transPS) / 100;
	if (ps2 < 0) ps2 = 0;
	if (ps2 > 100) ps2 = 100;

	int layer2 = lp->para[1];

	if ((ps1 == 0) && (ps2 == 0))
	{
		m_allEffect->ChangeEffectCommandOnly(layer2, EFFECT_BUFFER);
		return TRUE;
	}

	if ((ps1 != 0) && (ps2 != 0))
	{
		return FALSE;
	}



	//é¿ÇÕÇ»Ç…Ç‡Ç‚Ç¡ÇƒÇ»Ç¢
	if (ps1 == 0)
	{
		//		m_allEffect->ExchangeEffectPic(layer,layer2);
		m_allEffect->ChangeEffectCommandOnly(layer2, EFFECT_BUFFER);

		if (ps2 == 100)
		{
			m_allEffect->ChangeEffectCommandOnly(layer, EFFECT_NOP);
		}
		else
		{
			m_allEffect->ChangeEffectCommandOnly(layer, EFFECT_TRANS);
			lp->para[1] = ps2;
		}
	}
	else
	{
		if (ps1 == 100)
		{
			m_allEffect->ChangeEffectCommandOnly(layer, EFFECT_NOP);
		}
		else
		{
			m_allEffect->ChangeEffectCommandOnly(layer, EFFECT_TRANS);
			lp->para[1] = ps1;
		}
	}

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

	//OutputDebugString("ÅyPrint EffectChangeÅz");
	//return;

	int count = lp->count;
	int countMax = lp->countMax;
	int transType = lp->para[6];
	int transSubFrame = lp->para[7];
	int ps01 = lp->para[3];
	int ps02 = lp->para[2];

	int transPS = CCalcuSpeed::calcu(count, countMax, ps01, ps02, transSubFrame, transType);

	int changeType = lp->para[4];
	int changeSubFrame = lp->para[5];

	int changePS = CCalcuSpeed::calcu(count, countMax, 100, 0, changeSubFrame, changeType);

	int ps1 = (changePS * transPS) / 100;
	if (ps1 < 0) ps1 = 0;
	if (ps1 > 100) ps1 = 100;

	int ps2 = ((100 - changePS) * transPS) / 100;
	if (ps2 < 0) ps2 = 0;
	if (ps2 > 100) ps2 = 100;


	int pic1 = lp->pic;
	if (pic1 == -1) return;

	int pic2 = lp->para[1];
	if (pic2 == -1) return;

	if (m_allEffect->GetOtherLayerPic(pic2) == -1) return;

	RECT rc1;
	RECT rc2;

	CPicture* lpPic1 = m_allEffect->GetPicture(layer);
	CPicture* lpPic2 = m_allEffect->GetPicture(pic2);

	if (lpPic1 == NULL) return;
	if (lpPic2 == NULL) return;


	lpPic1->GetPicSize(&rc1);
	lpPic2->GetPicSize(&rc2);



	if (!EqualRect(&rc1, &rc2)) return;

	int* lpBuffer2 = (int*)(lpPic2->GetBuffer());
	if (lpBuffer2 == NULL) return;

	RECT rc = lp->dst;
	int srcX = lp->src.left;
	int srcY = lp->src.top;

	char* lpMask2 = (char*)(lpPic2->GetMaskPic());
	if (lpMask2 == NULL) return;

	//	lpPic1->ChangeTranslateBlt(rc.left,rc.top,srcX,srcY,rc.right,rc.bottom,ps1,ps2,lpBuffer2,lpMask2,lpPic2);
	lpPic1->ChangeTranslateBlt(rc.left, rc.top, srcX, srcY, rc.right, rc.bottom, ps1, ps2, lpPic2, srcX, srcY);

	//char mes[256];
	//sprintf(mes,"(PrintEffectChange X=%d)",rc.left);
	//OutputDebugString(mes);	



}


BOOL CEffectCharaMozaic::CheckNeedPicPrint(LPVOID lpEffect, int layer)
{
	//OutputDebugString("Åú");
	return FALSE;
}



/*_*/

