//
// effectHanabira.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectHanabira.h"

#define HANABIRA_KOSUU_MAX 300
#define HANABIRA_SCALE 100


CEffectHanabira::CEffectHanabira(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

	m_hanabira = new HANABIRA[HANABIRA_KOSUU_MAX * LAYER_KOSUU_MAX];

	m_animePartsKosuu = 1;
	m_partsKosuu = 1;
	m_setX = 600;
	m_setY = 300;
	m_setR = 100;
	m_speedX = -100;
	m_speedY = 10;
	m_loopFlag = 0;
	m_animeRevFlag = 0;

	m_animeType = 1;

	for (int i=0;i<HANABIRA_KOSUU_MAX*LAYER_KOSUU_MAX;i++)
	{
		SetNewHanabira(i);
	}
}


CEffectHanabira::~CEffectHanabira()
{
	End();
}

void CEffectHanabira::End(void)
{
	DELETEARRAY(m_hanabira);
}

void CEffectHanabira::InitParameter(LPVOID lpEffect, int layer)
{
	int para[24];
	EFFECT* lp = (EFFECT*)lpEffect;
	for (int i=0;i<24;i++)
	{
		para[i] = lp->para[i];
	}
	SetParam(lp,24,para,layer);
}

BOOL CEffectHanabira::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
//char mes[16];
//sprintf(mes,"layer=%d ",layer);
//OutputDebugString(mes);

	EFFECT* lp = (EFFECT*)lpEffect;

	if (layer == -1) layer = 0;	//dummy

	int para[24];
	int k = paraKosuu;
	if (k>24) k = 24;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 100;	//こすう
	if (paraKosuu<3) para[2] = 100;	//サイズx
	if (paraKosuu<4) para[3] = 100;	//サイズy
	if (paraKosuu<5) para[4] = 0;	//picNumber	//使用しない！必要なら後ろにうつす
	if (paraKosuu<6) para[5] = 1;	//パーツ数
	if (paraKosuu<7) para[6] = 600;	//初期配置x
	if (paraKosuu<8) para[7] = 300;	//初期配置y
	if (paraKosuu<9) para[8] = 100;	//初期配置r
	if (paraKosuu<10) para[9] = -100;	//スピードx
	if (paraKosuu<11) para[10] = 10;	//スピードy
	if (paraKosuu<12) para[11] = 0;	//ループフラグ
	if (paraKosuu<13) para[12] = 0;	//初期化しないフラグ
//	if (paraKosuu<14) para[13] = 0;	//何番目から(未使用)
	if (paraKosuu<15) para[14] = 100;//半透明度合い終了	拡張用
	if (paraKosuu<16) para[15] = 100;//半透明度合い開始	拡張用

	if (paraKosuu<17) para[16] = 100;//ゆれる度合い1
	if (paraKosuu<18) para[17] = 50;//ゆれる度合い2

	if (paraKosuu<19) para[18] = 1;	//アニメパターン数
	if (paraKosuu<20) para[19] = 1;	//アニメ逆有り

	if (paraKosuu<21) para[20] = 0;	//subtype
	if (paraKosuu<22) para[21] = 0;	//dubframe
	if (paraKosuu<23) para[22] = 1;//animeType




	if (para[1]<1) para[1] = 1;
	if (para[1] >= HANABIRA_KOSUU_MAX) para[1] = HANABIRA_KOSUU_MAX;
	if (para[13]<0) para[13]=0;
	if (para[13] >= HANABIRA_KOSUU_MAX) para[13] = HANABIRA_KOSUU_MAX-1;
	if ((para[1] + para[13]) > HANABIRA_KOSUU_MAX) para[1] = HANABIRA_KOSUU_MAX - para[13];
	if (para[1]<0) para[1] = 0;

	if (para[5] <= 0) para[5] = 1;
	if (para[18]<1) para[18] = 1;

	if (para[22] < 1) para[22] = 1;//animeType


	lp->flag = TRUE;
	lp->command = EFFECT_HANABIRA;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<24;i++)
	{
		lp->para[i] = para[i];
	}

	if (para[12] == 0)
	{
		m_partsKosuu = lp->para[5];

		m_setX = para[6];
		m_setY = para[7];
		m_setR = para[8];
		m_speedX = para[9];
		m_speedY= para[10];
		
		m_loopFlag = para[11];

		m_animePartsKosuu = para[18];
		m_animeRevFlag = para[19];
		m_yureTH = para[17];

		m_animeType = para[22];

		for (int i=0;i<para[1];i++)
		{
			SetNewHanabira(layer*HANABIRA_KOSUU_MAX+i);
		}
	}

	return TRUE;
}


BOOL CEffectHanabira::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectHanabira::BeginPrint(LPVOID para,int layer)
{

}

void CEffectHanabira::Init(LPVOID para,int layer)
{


}

void CEffectHanabira::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectHanabira::Print(LPVOID lpEffect,int layer)
{
//char mes[16];
//sprintf(mes,"layer=%d ",layer);
//OutputDebugString(mes);


	EFFECT* lp = (EFFECT*)lpEffect;
	if (layer == -1) layer = 0;

	int dv = lp->countMax;
	int c = lp->count;

	if (dv<1)
	{
		dv = 1;
	}

	if (c>=dv) return;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int* dst = CMyGraphics::GetScreenBuffer();

	int pic = lp->para[4];
	if (pic == -1) return;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	RECT rc;
	lpPic->GetPicSize(&rc);
	int picSizeX = rc.right;
	int picSizeY = rc.bottom;
	if ((picSizeX<1) || (picSizeY<1)) return;

	m_partsSizeX = lp->para[2];
	m_partsSizeY = lp->para[3];

	if (m_partsSizeX<1) return;
	if (m_partsSizeY<1) return;

	int picKosuuX = picSizeX / m_partsSizeX;
	int picKosuuY = picSizeY / m_partsSizeY;

	if (picKosuuX<1) return;
	if (picKosuuY<1) return;


	m_setX = lp->para[6];
	m_setY = lp->para[7];
	m_setR = lp->para[8];
	m_speedX = lp->para[9];
	m_speedY = lp->para[10];
	m_loopFlag = lp->para[11];
	m_partsKosuu = lp->para[5];

	m_animePartsKosuu = lp->para[18];
	m_animeRevFlag = lp->para[19];

	m_screenClipX1 = - m_partsSizeX / 2;
	m_screenClipY1 = - m_partsSizeY / 2;
	m_screenClipX2 = screenSizeX + m_partsSizeX / 2;
	m_screenClipY2 = screenSizeY + m_partsSizeY / 2;

	int st = layer * HANABIRA_KOSUU_MAX;
	int kosuu = lp->para[1];

//	cosTH *= (double)(m_partsSizeY*HANABIRA_SCALE);


	int absSpeedX = m_speedX;
//	if (absSpeedX<0) absSpeedX *= -1;
	int absSpeedY = -m_speedY;
//	if (absSpeedY<0) absSpeedY *= -1;

	double rt = (double)(absSpeedX * absSpeedX + absSpeedY*absSpeedY);
	if (rt<1.0) rt = 1.0;
	rt = sqrt(rt);

	m_yureX = (double)absSpeedY;
	m_yureX *= (double)(lp->para[16] * HANABIRA_SCALE);
	m_yureX /= 100.0;

	m_yureY = (double)absSpeedX;
	m_yureY *= (double)(lp->para[16] * HANABIRA_SCALE);
	m_yureY /= 100.0;

	m_yureTH = lp->para[17];

	m_animeType = lp->para[22];

	CalcuHanabira(st,kosuu);


	//print

	int clipX1 = m_screenClipX1;
	int clipY1 = m_screenClipY1;
	int clipX2 = m_screenClipX2;
	int clipY2 = m_screenClipY2;

	int sizeX = m_partsSizeX;
	int sizeY = m_partsSizeY;

	int ps1 = lp->para[15];
	int ps2 = lp->para[14];
	int subType = lp->para[20];
	int subFrame = lp->para[21];
	int ps = CCalcuSpeed::calcu(c,dv,ps1,ps2,subFrame,subType);

//	int ps = ps1 + ((ps2 - ps1) * c + dv / 2) /dv;
	if (ps<0) ps = 0;
	if (ps>100) ps = 100;

	if (ps==0) return;


//char mes[16];
//sprintf(mes,"layer=%d ",layer);
//OutputDebugString(mes);

	int animeType = m_animeType;
	int animePartsKosuu = m_animePartsKosuu;

	for (int i=st;i<st+kosuu;i++)
	{
		if ((i>=0) && (i<HANABIRA_KOSUU_MAX*LAYER_KOSUU_MAX))
		{
//OutputDebugString(".");
			int p = m_hanabira[i].pic;
			if (p != -1)
			{
				int pic1 = p / animeType;
				int pic2 = pic1 + 1;
				if ((pic2 % animePartsKosuu) == 0)
				{
					pic2 = (pic1 / animePartsKosuu) * animePartsKosuu;
				}

				if (m_hanabira[i].rev)
				{
					if ((pic1 % animePartsKosuu) == 0)
					{
						pic2 = pic1 + animePartsKosuu - 1;
					}
					else
					{
						pic2 = pic1 - 1;
					}
				}

				int x = m_hanabira[i].x / HANABIRA_SCALE;
				int y = m_hanabira[i].y / HANABIRA_SCALE;

//OutputDebugString(":");
				if ((x>=clipX1) && (x<clipX2) && (y>=clipY1) && (y<clipY2))
				{
					int putX = x - sizeX / 2;
					int putY = y - sizeY / 2;

					if (animeType <= 1)
					{
						int srcX = (p % picKosuuX) * m_partsSizeX;
						int srcY = (p / picKosuuX) * m_partsSizeY;

						if (ps==100)
						{
							lpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
						}
						else
						{
							lpPic->TransLucentBlt3(putX,putY,srcX,srcY,sizeX,sizeY,ps);
						}
					}
					else
					{
						int ps2 = ((p % animeType) * 100) / m_animeType;
						int ps1 = 100-ps2;

						ps1 *= ps;
						ps1 /= 100;
						ps2 *= ps;
						ps2 /= 100;

						int srcX1 = (pic1 % picKosuuX) * m_partsSizeX;
						int srcY1 = (pic1 / picKosuuX) * m_partsSizeY;
						int srcX2 = (pic2 % picKosuuX) * m_partsSizeX;
						int srcY2 = (pic2 / picKosuuX) * m_partsSizeY;

						lpPic->ChangeTranslateBlt(putX,putY,srcX1,srcY1,sizeX,sizeY,ps1,ps2,lpPic,srcX2,srcY2);
					}
				}
			}
		}
	}
}



void CEffectHanabira::CalcuHanabira(int st, int kosuu)
{
	for (int i=st;i<st+kosuu;i++)
	{
		CalcuHanabiraSub(i);
	}
}

void CEffectHanabira::CalcuHanabiraSub(int n)
{
	if ((n<0) || (n>=HANABIRA_KOSUU_MAX* LAYER_KOSUU_MAX)) return;

	int pic = m_hanabira[n].pic;
	if (pic == -1)
	{
		if (m_loopFlag)
		{
			SetNewHanabira(n);
		}
		else
		{
			return;
		}
	}

	if (m_animePartsKosuu>1)
	{
		int pt = m_hanabira[n].pic;
		int base = pt / (m_animePartsKosuu * m_animeType);
		base *= (m_animePartsKosuu * m_animeType);

		int amari = pt % (m_animePartsKosuu * m_animeType);

		amari += m_animePartsKosuu * m_animeType;
		if (m_hanabira[n].rev == 0)
		{
			amari++;
		}
		else
		{
			amari--;
		}

		amari %= (m_animePartsKosuu * m_animeType);

		m_hanabira[n].pic = base + amari;
	}

	int x = m_hanabira[n].x;
	int y = m_hanabira[n].y;
	int speedX = m_hanabira[n].speedX;
	int speedY = m_hanabira[n].speedY;

	x += speedX;
	y += speedY;

	//ふらふら移動??

	int th = m_hanabira[n].th;
	int thMax = m_hanabira[n].thMax;
	th++;
	th %= thMax;
	m_hanabira[n].th = th;

	double th1 = (double)th;
	th1 *= 3.14159*2;
	th1 /= (double)thMax;

	double sinTH = sin(th1);
//	cosTH *= (double)(m_partsSizeY*HANABIRA_SCALE);

	double yureX = sinTH * m_yureX;
	double yureY = sinTH * m_yureY;

	int deltaX = 0;
	int deltaY = 0;

	int absSpeedX = speedX;
//	if (absSpeedX<0) absSpeedX = -speedX;

	int absSpeedY = speedY;
//	if (absSpeedY<0) absSpeedY = -speedY;
	
//	if (absSpeedX>absSpeedY)
//	{
//		deltaY = (int)(cosTH * 0.2 + 0.5);
//	}
//	else
//	{
//		deltaX = (int)(cosTH * 0.2 + 0.5);
//	}

	deltaX = (int)(yureX * 0.2 + 0.5);
	deltaY = (int)(yureY * 0.2 + 0.5);


	x += deltaX;
	y += deltaY;





	m_hanabira[n].x = x;
	m_hanabira[n].y = y;


	x /= HANABIRA_SCALE;
	y /= HANABIRA_SCALE;



	//outof area?
	if (speedX<0)
	{
		if (x<m_screenClipX1)
		{
			m_hanabira[n].pic = -1;
			return;
		}
	}
	else
	{
		if (x>m_screenClipX2)
		{
			m_hanabira[n].pic = -1;
			return;
		}
	}

	if (speedY<0)
	{
		if (y<m_screenClipY1)
		{
			m_hanabira[n].pic = -1;
			return;
		}
	}
	else
	{
		if (y>m_screenClipY2)
		{
			m_hanabira[n].pic = -1;
			return;
		}
	}
}



void CEffectHanabira::SetNewHanabira(int n)
{
	if ((n<0) || (n>=HANABIRA_KOSUU_MAX* LAYER_KOSUU_MAX)) return;

	m_hanabira[n].pic = rand() % (m_partsKosuu * m_animePartsKosuu * m_animeType);
	m_hanabira[n].x = m_setX + (rand() % (m_setR*2)) - m_setR / 2;
	m_hanabira[n].y = m_setY + (rand() % (m_setR*2)) - m_setR / 2;
	m_hanabira[n].x *= HANABIRA_SCALE;
	m_hanabira[n].y *= HANABIRA_SCALE;
	
	int speedX = m_speedX * HANABIRA_SCALE;
	int speedY = m_speedY * HANABIRA_SCALE;
	int divX = speedX / 2;
	int divY = speedY / 2;
	if (divX<0) divX *= -1;
	if (divY<0) divY *= -1;
	if (divX<1) divX = 1;
	if (divY<1) divY = 1;
	speedX += (rand() % divX);
	speedY += (rand() % divY);
	speedX -= divX / 2;
	speedY -= divY / 2;

	m_hanabira[n].speedX = speedX;
	m_hanabira[n].speedY = speedY;

	int rd = m_yureTH;
	if (rd<1) rd = 1;
	int thMax = (rand() % rd) + m_yureTH/2 + 2;

	m_hanabira[n].thMax = thMax;
	m_hanabira[n].th = rand() % thMax;

	m_hanabira[n].rev = 0;
	if (m_animeRevFlag)
	{
		if ((rand() % 100) < 50)
		{
			m_hanabira[n].rev = 1;
		}
	}
}

BOOL CEffectHanabira::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}
