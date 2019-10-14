//
// effectAnime.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\allGraphics.h"

#include "effectAnimation.h"

char CEffectAnimation::m_animeTag[256] = "bg\\bganime";
int CEffectAnimation::m_animationBufferMax = 60;
int CEffectAnimation::m_bufferDepth = 32;
int CEffectAnimation::m_animeEffectEnable = 0;

//
//この機能は非公開とする(StoneHeads専用)
//機能としてちょっと富豪かよ！って感じなのでまあいいかな
//

void CEffectAnimation::SetAnimeBufferMax(int mx)
{
	m_animationBufferMax = mx;
}

void CEffectAnimation::SetBufferDepth(int depth)
{
	m_bufferDepth = depth;
}

void CEffectAnimation::SetAnimeEffectEnable(BOOL flg)
{
	m_animeEffectEnable = flg;
}

CEffectAnimation::CEffectAnimation(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	int sizeX = CMyGraphics::GetScreenSizeX();
	int sizeY = CMyGraphics::GetScreenSizeY();

	m_lastAnimeNumber = 0;

	if (m_animeEffectEnable == 0) return;

	m_ppAnimationPic = new CPicture*[m_animationBufferMax];
	for (int i=0;i<m_animationBufferMax;i++)
	{
		if (m_bufferDepth == 32)
		{
			m_ppAnimationPic[i] = new CPicture(sizeX,sizeY,TRUE);
		}
		else//8
		{
			m_ppAnimationPic[i] = new CPicture(sizeX,sizeY,FALSE,TRUE);
		}
	}

	if (m_bufferDepth == 32)
	{
		m_oldAnimationPic = new CPicture(sizeX,sizeY,TRUE);
	}
	else
	{
		m_oldAnimationPic = new CPicture(sizeX,sizeY,FALSE,TRUE);
	}
}

CEffectAnimation::~CEffectAnimation()
{
	End();
}

void CEffectAnimation::End(void)
{
	if (m_animeEffectEnable == 0) return;

	ENDDELETECLASS(m_oldAnimationPic);

	if (m_ppAnimationPic != NULL)
	{
		for (int i=0;i<m_animationBufferMax;i++)
		{
			ENDDELETECLASS(m_ppAnimationPic[i]);
		}
		DELETEARRAY(m_ppAnimationPic);
		m_ppAnimationPic = NULL;
	}

}

BOOL CEffectAnimation::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[17];
	int k = paraKosuu;
	if (k>17) k = 17;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}


	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 4;	//pattern数
	if (paraKosuu<3) para[2] = 0;	//anime start number
	if (paraKosuu<4) para[3] = 1;	//loop flag
	if (paraKosuu<5) para[4] = 1;	//koma
	if (paraKosuu<6) para[5] = 5;	//nameraka frame

	if (paraKosuu<7) para[6] = 0;	//buffer start
	if (paraKosuu<8) para[7] = 0;	//cashe flag(count)


	if (para[1]<1) para[1] = 1;
	if (para[4]<1) para[4] = 1;


//	OutputDebugString("anime set param\n");
//	char ddd[256];
//	sprintf_s(ddd,256,"prev:%d\n",lp->previousEffect);
//	OutputDebugString(ddd);

	para[11] = 0;//cacheing

	//mae mo anime??
	para[13] =0;
//	if (lp->flag)
	if (1)
	{
		if (lp->previousEffect == EFFECT_ANIMATION)
		{
	//		para[15] = lp->para[14];//last anime number
			para[15] = m_lastAnimeNumber;
			para[13] = 1;//exist
			OutputDebugString("---- found old effect ----\n");
		}
	}

	para[14] = para[2];


	lp->flag = TRUE;
	lp->command = EFFECT_ANIMATION;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<17;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}







BOOL CEffectAnimation::CountIsMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	if (lp->para[7] == 0)//not cashe mode
	{
		if (lp->para[3])//loop
		{
			if (lp->countMax >= 99999)
			{
				lp->count = 0;
			}
		}
	}
//	lp->command = EFFECT_NOP;
//	if (lp->pic == -1)
//	{
//		lp->flag = FALSE;
//	}
//
//	return TRUE;
	return FALSE;
}


void CEffectAnimation::BeginPrint(LPVOID para,int layer)
{

}

void CEffectAnimation::Init(LPVOID para,int layer)
{
}

void CEffectAnimation::Calcu(LPVOID lpEffect,int layer)
{
	/*
	EFFECT* lp = (EFFECT*)lpEffect;

	if (lp->para[10])
	{
		int dv = lp->para[1] * lp->para[2];
		if (dv<1) dv = 1;

		int c = lp->count;
		c %= dv;
		lp->count = c;
	}
	*/

	EFFECT* lp = (EFFECT*)lpEffect;
	if (lp->para[7])//cashe mode
	{
		lp->previousEffect = EFFECT_NOP;
	}

}


void CEffectAnimation::Print(LPVOID lpEffect,int layer)
{
	if (m_animeEffectEnable == 0) return;

	EFFECT* lp = (EFFECT*)lpEffect;

	int animeOff = m_allEffect->GetAnimeOff();

	int* dst = CMyGraphics::GetScreenBuffer();


	int count = lp->count;
	int countMax = lp->countMax;
	int patternKosuu = lp->para[1];
	int animeStart = lp->para[2];
	int loopFlag = lp->para[3];
	int frameDiv = lp->para[4];
	int transitTime = lp->para[5];

	if (frameDiv<1) frameDiv = 1;

	int n = count / frameDiv;
	if (loopFlag)
	{
		n %= patternKosuu;
	}
	else
	{
		if (n>=patternKosuu)
		{
			n = patternKosuu-1;
		}
	}
	if (lp->para[7])
	{
		n = lp->para[11];
		lp->para[11]++;
		lp->para[11] %= patternKosuu;
	}

	if (animeOff) n = 0;

	if (n<0) n = 0;
	int anime = animeStart + n;
//	lp->para[14] = anime;//last anime
	
	int bufferNumber = n + lp->para[6];
	if (bufferNumber<0) bufferNumber = 0;
	if (bufferNumber >= m_animationBufferMax-1) bufferNumber = m_animationBufferMax-1;

	CPicture* lpPic = m_ppAnimationPic[bufferNumber];
	char filename[1024];
	sprintf_s(filename,1024,"%s%d",m_animeTag,anime);
	BOOL b256Flag = FALSE;
	if (m_bufferDepth != 32) b256Flag = TRUE;
	if (lpPic->LoadDWQ(filename,b256Flag) == FALSE) return;

	if (lp->para[7]) return;//cashe mode

	m_lastAnimeNumber = anime;



	int ps1 = 0;
	int ps2 = 10000;

	int speedType = 0;
	int subFrame = 0;

	int ps = CCalcuSpeed::calcu(count,countMax,ps1,ps2,subFrame,speedType);

	int startX = lp->dstFrom.left;
	int startY = lp->dstFrom.top;
	int endX = lp->dstTo.left;
	int endY = lp->dstTo.top;

	int putX = startX + ((endX - startX) * ps) / 10000;
	int putY = startY + ((endY - startY) * ps) / 10000;


	int srcX = 0;
	int srcY = 0;
	SIZE sz = lpPic->GetPicSize();
	int sizeX = sz.cx;
	int sizeY = sz.cy;


	//transit?
	if (lp->para[13] && (transitTime > 0) && (count < transitTime) && (lp->para[7] == 0))
	{
		char filename2[1024];
		sprintf_s(filename2,1024,"%s%d",m_animeTag,lp->para[15]);
		BOOL b256Flag = FALSE;
		if (m_bufferDepth != 32) b256Flag = TRUE;
	
		if (m_oldAnimationPic->LoadDWQ(filename2,b256Flag))
		{
			//transit
			int transPS = 100 - (count * 100) / transitTime;
			if (transPS < 0) transPS = 0;
			if (transPS > 100) transPS = 100;

			if (b256Flag)
			{
				m_oldAnimationPic->ChangeBlt(putX,putY,srcX,srcY,sizeX,sizeY,transPS,100-transPS,lpPic,srcX,srcY);
			}
			else
			{
				m_oldAnimationPic->ChangeTranslateBlt(putX,putY,srcX,srcY,sizeX,sizeY,transPS,100-transPS,lpPic,srcX,srcY);
			}

			return;
		}
		//error! normal print
	}

	if (m_allEffect->CheckBGLayer(layer))
	{
		lpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,FALSE);
	}
	else
	{
		lpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
	}
}



BOOL CEffectAnimation::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectAnimation::SetAnimeTageName(LPSTR name)
{
	int ln = (int)strlen(name);
	if (ln>254) ln = 254;
	memcpy_s(m_animeTag,256,name,ln);
	m_animeTag[ln] = 0;
	m_animeTag[ln+1] = 0;
}


CPicture* CEffectAnimation::GetAnimeBuffer(int n)
{
	if (m_animeEffectEnable == 0) return NULL;

	if (n>=m_animationBufferMax) n= m_animationBufferMax-1;
	if (n<0) n = 0;
	return m_ppAnimationPic[n];
}

BOOL CEffectAnimation::Check256(void)
{
	if (m_bufferDepth == 32) return FALSE;

	return TRUE;
}