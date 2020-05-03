//
// effectHotaru.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectHotaruNew.h"


#define HOTARU_KOSUU_MAX 600
#define HOTARU_SCALE 256

#define NEWHOTARU_FRAME 0
#define NEWHOTARU_KOSUU 1
#define NEWHOTARU_PARTS_SIZE_X 2
#define NEWHOTARU_PARTS_SIZE_Y 3
#define NEWHOTARU_PRINT_TYPE 4
#define NEWHOTARU_ANIME_SPEED 5
#define NEWHOTARU_TRANS_LOW 6
#define NEWHOTARU_TRANS_HIGH 7

#define NEWHOTARU_SET_X 8
#define NEWHOTARU_SET_Y 9
#define NEWHOTARU_SIZE_X 10
#define NEWHOTARU_SIZE_Y 11

#define NEWHOTARU_SPEED_X 12
#define NEWHOTARU_SPEED_Y 13
#define NEWHOTARU_SPEED_RANDOM 14

#define NEWHOTARU_FRAME_IN 15
#define NEWHOTARU_FRAME_OUT 16
#define NEWHOTARU_FRAME_LENGTH_RANDOM 17
#define NEWHOTARU_FRAME_START_RANDOM 18

#define NEWHOTARU_FRAME_LOOP_FLAG 19
#define NEWHOTARU_FRAME_REPOP_FLAG 20

#define NEWHOTARU_YURE_FRAME 21
#define NEWHOTARU_YURE_ANGLE 22
#define NEWHOTARU_YURE_WIDTH 23


CEffectHotaruNew::CEffectHotaruNew(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(2);
	Create("Hotaru");
	m_hotaruPic = new CPicture(8, 8);
#endif

	m_hotaru = new HOTARUNew[HOTARU_KOSUU_MAX];
	m_lightTable = new int[8 * 8 * 2 + 7];


	m_setX = 600;
	m_setY = 300;
	m_setSizeX = 100;
	m_setSizeY = 100;
	m_speedX = -3;
	m_speedY = -2;
	m_frameLoopFlag = 0;
	m_repopFlag = 0;

	m_yure = 15;


	m_totalFrame = 20;
	m_kosuu = HOTARU_KOSUU_MAX;

	m_partsSizeX = 16;
	m_partsSizeY = 16;
	m_printType = 0;
	m_animeSpeed = 1;


	m_speedRandom = 0;


	m_yureKakudo = 0;
	m_yureHaba = 1;


	m_transLow = 0;
	m_transHigh = 100;

	m_inFrame = 1;
	m_outFrame = 10;

	m_frameLengthRandom = 0;
	m_frameStartRandom = 0;

	m_frameLoopFlag = 0;
	m_repopFlag = 1;



	for (int i = 0; i < HOTARU_KOSUU_MAX; i++)
	{
		SetNewHotaru(i);
	}
}


CEffectHotaruNew::~CEffectHotaruNew()
{
	End();
}

void CEffectHotaruNew::End(void)
{
	DELETEARRAY(m_hotaru);
	DELETEARRAY(m_lightTable);
#if defined _TINYAN3DLIB_
	ENDDELETECLASS(m_hotaruPic);
#endif
}



void CEffectHotaruNew::InitParameter(LPVOID lpEffect, int layer)
{
	int para[20];
	EFFECT* lp = (EFFECT*)lpEffect;
	for (int i = 0; i < 20; i++)
	{
		para[i] = lp->para[i];
	}
	SetParam(lp, 20, para, layer);
}



BOOL CEffectHotaruNew::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr, int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int para[32];
	int k = paraKosuu;
	if (k > 32) k = 32;
	int i;
	for (i = 0; i < k; i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu <= NEWHOTARU_FRAME) para[NEWHOTARU_FRAME] = 20;	//frame

	if (paraKosuu <= NEWHOTARU_KOSUU) para[NEWHOTARU_KOSUU] = 100;	//個数

	if (paraKosuu <= NEWHOTARU_PARTS_SIZE_X) para[NEWHOTARU_PARTS_SIZE_X] = 16;	//partsSizeX
	if (paraKosuu <= NEWHOTARU_PARTS_SIZE_Y) para[NEWHOTARU_PARTS_SIZE_Y] = 16;	//partsSizeY
	if (paraKosuu <= NEWHOTARU_PRINT_TYPE) para[NEWHOTARU_PRINT_TYPE] = 0;	//描画タイプ
	if (paraKosuu <= NEWHOTARU_ANIME_SPEED) para[NEWHOTARU_ANIME_SPEED] = 1;	//anime speed

	if (paraKosuu <= NEWHOTARU_TRANS_LOW) para[NEWHOTARU_TRANS_LOW] = 50;	//半透明開始終了
	if (paraKosuu <= NEWHOTARU_TRANS_HIGH) para[NEWHOTARU_TRANS_HIGH] = 100;	//半透明維持


	if (paraKosuu <= NEWHOTARU_SET_X) para[NEWHOTARU_SET_X] = screenSizeX/2;//setX
	if (paraKosuu <= NEWHOTARU_SET_Y) para[NEWHOTARU_SET_Y] = screenSizeY / 2;//setY
	if (paraKosuu <= NEWHOTARU_SIZE_X) para[NEWHOTARU_SIZE_X] = 100;	//sizeX
	if (paraKosuu <= NEWHOTARU_SIZE_Y) para[NEWHOTARU_SIZE_Y] = 100;	//sizeY

	if (paraKosuu <= NEWHOTARU_SPEED_X) para[NEWHOTARU_SPEED_X] = -2;	//speedx
	if (paraKosuu <= NEWHOTARU_SPEED_Y) para[NEWHOTARU_SPEED_Y] = -3;	//speedy
	if (paraKosuu <= NEWHOTARU_SPEED_RANDOM) para[NEWHOTARU_SPEED_RANDOM] = 0;	//speedRandom%



	if (paraKosuu <= NEWHOTARU_FRAME_IN) para[NEWHOTARU_FRAME_IN] = 5;	//InFrame
	if (paraKosuu <= NEWHOTARU_FRAME_OUT) para[NEWHOTARU_FRAME_OUT] = 10;	//OutFrame
	if (paraKosuu <= NEWHOTARU_FRAME_LENGTH_RANDOM) para[NEWHOTARU_FRAME_LENGTH_RANDOM] = 0;	//FrameLengthRandom%
	if (paraKosuu <= NEWHOTARU_FRAME_START_RANDOM) para[NEWHOTARU_FRAME_START_RANDOM] = 0;	//FrameStratRandom% リポップ時は0


	if (paraKosuu <= NEWHOTARU_FRAME_LOOP_FLAG) para[NEWHOTARU_FRAME_LOOP_FLAG] = 0;	//frame loop flag
	if (paraKosuu <= NEWHOTARU_FRAME_REPOP_FLAG) para[NEWHOTARU_FRAME_REPOP_FLAG] = 1;	//repop flag


	if (paraKosuu <= NEWHOTARU_YURE_FRAME) para[NEWHOTARU_YURE_FRAME] = 15;	//ゆれ周期	1-??
	if (paraKosuu <= NEWHOTARU_YURE_ANGLE) para[NEWHOTARU_YURE_ANGLE] = -1;		//ゆれ角度
	if (paraKosuu <= NEWHOTARU_YURE_WIDTH) para[NEWHOTARU_YURE_WIDTH] = 20;		//ゆれはば



//	if (paraKosuu < 9) para[8] = 255;	//r
//	if (paraKosuu < 10) para[9] = 255;	//g
//	if (paraKosuu < 11) para[10] = 255;	//b
//	if (paraKosuu < 13) para[12] = 0;	//not init flag
//	if (paraKosuu < 14) para[13] = 0;	//work start number



	if (para[NEWHOTARU_YURE_FRAME] < 1) para[NEWHOTARU_YURE_FRAME] = 1;




	if (para[NEWHOTARU_SIZE_X] < 1) para[NEWHOTARU_SIZE_X] = 1;
	if (para[NEWHOTARU_SIZE_Y] < 1) para[NEWHOTARU_SIZE_Y] = 1;


//	if ((para[13] + para[1]) > HOTARU_KOSUU_MAX)
//	{
//		para[13] = HOTARU_KOSUU_MAX - para[1];
//	}

	lp->flag = TRUE;
	lp->command = EFFECT_HOTARUNEW;
	lp->countMax = para[0];
	lp->count = 0;

	for (i = 0; i < 32; i++)
	{
		lp->para[i] = para[i];
	}


	GetInitParam(lp);
	CalcuYureCosSin();
	for (int i=0;i<m_kosuu;i++)
	{
		SetNewHotaru(i, m_frameStartRandom);
	}

	return TRUE;
}

void CEffectHotaruNew::GetInitParam(void* lp)
{
	EFFECT* p = (EFFECT*)lp;

	m_totalFrame = p->para[NEWHOTARU_FRAME];
	m_kosuu = p->para[NEWHOTARU_KOSUU];

	m_partsSizeX = p->para[NEWHOTARU_PARTS_SIZE_X];
	m_partsSizeY = p->para[NEWHOTARU_PARTS_SIZE_Y];
	m_printType = p->para[NEWHOTARU_PRINT_TYPE];
	m_animeSpeed = p->para[NEWHOTARU_ANIME_SPEED];


	m_setX = p->para[NEWHOTARU_SET_X];
	m_setY = p->para[NEWHOTARU_SET_Y];
	m_setSizeX = p->para[NEWHOTARU_SIZE_X];
	m_setSizeY = p->para[NEWHOTARU_SIZE_Y];
	m_speedX = p->para[NEWHOTARU_SPEED_X];
	m_speedY = p->para[NEWHOTARU_SPEED_Y];
	m_speedRandom = p->para[NEWHOTARU_SPEED_RANDOM];

	//m_loopFlag = p->para[11];

	m_yure = p->para[NEWHOTARU_YURE_FRAME];
	m_yureKakudo = p->para[NEWHOTARU_YURE_ANGLE];
	m_yureHaba = p->para[NEWHOTARU_YURE_WIDTH];


	m_transLow = p->para[NEWHOTARU_TRANS_LOW];
	m_transHigh = p->para[NEWHOTARU_TRANS_HIGH];

	m_inFrame = p->para[NEWHOTARU_FRAME_IN];
	m_outFrame = p->para[NEWHOTARU_FRAME_OUT];

	m_frameLengthRandom = p->para[NEWHOTARU_FRAME_LENGTH_RANDOM];
	m_frameStartRandom = p->para[NEWHOTARU_FRAME_START_RANDOM];

	m_frameLoopFlag = p->para[NEWHOTARU_FRAME_LOOP_FLAG];
	m_repopFlag = p->para[NEWHOTARU_FRAME_REPOP_FLAG];

}



BOOL CEffectHotaruNew::CountIsMax(LPVOID lpEffect, int layer)
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


void CEffectHotaruNew::BeginPrint(LPVOID para, int layer)
{

}

void CEffectHotaruNew::Init(LPVOID para, int layer)
{
}

void CEffectHotaruNew::Calcu(LPVOID lpEffect, int layer)
{
}


void CEffectHotaruNew::Print(LPVOID lpEffect, int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int dv = lp->countMax;
	int c = lp->count;

	if (dv < 1)
	{
		dv = 1;
	}

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int* dst = CMyGraphics::GetScreenBuffer();

	m_screenClipX1 = -m_partsSizeX / 2;
	m_screenClipY1 = -m_partsSizeY / 2;
	m_screenClipX2 = screenSizeX + m_partsSizeX / 2;
	m_screenClipY2 = screenSizeY + m_partsSizeY / 2;


	GetInitParam(lp);
	CalcuYureCosSin();

	CalcuHotaru(0, m_kosuu);

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == nullptr) return;

	SIZE sz = lpPic->GetPicSize();
	int picSizeX = sz.cx;
	int picSizeY = sz.cy;
	if (picSizeX <= 0) return;
	if (picSizeY <= 0) return;
	if (m_partsSizeX <= 0) return;
	if (m_partsSizeY <= 0) return;

	int srcPartsKosuuX = picSizeX / m_partsSizeX;
	int srcPartsKosuuY = picSizeY / m_partsSizeY;

	if (srcPartsKosuuX <= 0) return;
	if (srcPartsKosuuY <= 0) return;



	for (int i = 0; i < m_kosuu; i++)
	{
		if (m_hotaru[i].thMax == 0) continue;


		int sizeX = m_partsSizeX;
		int sizeY = m_partsSizeY;
		int x = (int) m_hotaru[i].x - sizeX / 2;
		int y = (int) m_hotaru[i].y - sizeY / 2;

		int frame = m_hotaru[i].frame;
		int anime = frame;
		if (m_animeSpeed > 1)
		{
			anime /= m_animeSpeed;
		}
		anime %= srcPartsKosuuX;

		int srcX = anime * m_partsSizeX;
		int srcY = (i % srcPartsKosuuY) * m_partsSizeY;

		int ps = 100;

		int frameIn = m_hotaru[i].frameIn;
		int frameOut = m_hotaru[i].frameOut;
		int frameKeep = m_hotaru[i].frameKeep;

		if (frame < frameIn)
		{
			int dv = frameIn;
			if (dv <= 0) dv = 1;

			ps = m_transLow + ((m_transHigh - m_transLow) * frame) / dv;
		}
		else if (frame < frameIn + frameKeep)
		{
			ps = m_transHigh;
		}
		else if (frame < frameIn + frameKeep + frameOut)
		{
			int dv = frameOut;
			if (dv <= 0) dv = 1;

			int c = frame - (frameIn + frameKeep);
			ps = m_transHigh - ((m_transHigh - m_transLow) * c) / dv;
		}
		else
		{
			ps = m_transLow;
		}

		if (ps < m_transLow) ps = m_transLow;
		if (ps > m_transHigh) ps = m_transHigh;

		if (m_printType == 1)
		{
			ps *= -1;
		}



		lpPic->AddSubBlt(x, y, srcX, srcY, sizeX, sizeY, ps);

//		lpPic->Blt(x, y, 0, 0, sizeX, sizeY, true);
	}
}




void CEffectHotaruNew::CalcuHotaru(int st, int kosuu)
{
	for (int i = st; i < st + kosuu; i++)
	{
		CalcuHotaruSub(i);
	}
}


void CEffectHotaruNew::CalcuHotaruSub(int n)
{
	if ((n < 0) || (n >= HOTARU_KOSUU_MAX)) return;

	int thMax = m_hotaru[n].thMax;

	if (thMax == 0)
	{
		if (m_repopFlag)
		{
			SetNewHotaru(n);
			return;
		}
		else
		{
			return;
		}
	}


	int frame = m_hotaru[n].frame;
	int inFrame = m_hotaru[n].frameIn;
	int keepFrame = m_hotaru[n].frameKeep;
	int outFrame = m_hotaru[n].frameOut;
	frame++;
	m_hotaru[n].frame = frame;

	if (frame > inFrame + keepFrame + outFrame)
	{
		if (m_frameLoopFlag == 0)
		{
			m_hotaru[n].thMax = 0;
			return;
		}
		m_hotaru[n].frame = 0;
	}


	float x = m_hotaru[n].x;
	float y = m_hotaru[n].y;
	float speedX = m_hotaru[n].speedX;
	float speedY = m_hotaru[n].speedY;

	x += speedX;
	y += speedY;

	//ふらふら移動??

	int th = m_hotaru[n].th;

	th++;
	if (th >= thMax)
	{
		th -= thMax;
	}
	m_hotaru[n].th = th;

	double th1 = (double)th;
	th1 *= 3.14159 * 2;
	th1 /= (double)thMax;

	double cosTH = cos(th1);
	cosTH *= (double)(m_yureHaba);

	float deltaX = 0;
	float deltaY = 0;

	if (m_yureKakudo == -1)
	{
		float absSpeedX = speedX;
		if (absSpeedX < 0) absSpeedX = -speedX;

		float absSpeedY = speedY;
		if (absSpeedY < 0) absSpeedY = -speedY;

		if (absSpeedX > absSpeedY)
		{
			deltaY = (float)(cosTH * 0.2f + 0.5f);
		}
		else
		{
			deltaX = (float)(cosTH * 0.2f + 0.5f);
		}
	}
	else
	{
		deltaX = (float)(cosTH * m_yureCos + 0.5f);
		deltaY = (float)(cosTH * m_yureSin + 0.5f);
	}

	x += deltaX;
	y += deltaY;



	m_hotaru[n].x = x;
	m_hotaru[n].y = y;





	//outof area?
	if (speedX < 0)
	{
		if (x < m_screenClipX1)
		{
			m_hotaru[n].thMax = 0;
			return;
		}
	}
	else
	{
		if (x > m_screenClipX2)
		{
			m_hotaru[n].thMax = 0;
			return;
		}
	}

	if (speedY < 0)
	{
		if (y < m_screenClipY1)
		{
			m_hotaru[n].thMax = 0;
			return;
		}
	}
	else
	{
		if (y > m_screenClipY2)
		{
			m_hotaru[n].thMax = 0;
			return;
		}
	}
}


void CEffectHotaruNew::SetNewHotaru(int n,int randomStartFrame)
{
	if ((n < 0) || (n >= HOTARU_KOSUU_MAX)) return;

	//	m_hotaru[n].x = m_setX + (rand() % (m_setSizeX*2)) - m_setSizeX / 2;
	//	m_hotaru[n].y = m_setY + (rand() % (m_setSizeY*2)) - m_setSizeY / 2;
	m_hotaru[n].x = (float)(m_setX + (rand() % m_setSizeX));
	m_hotaru[n].y = (float)(m_setY + (rand() % m_setSizeY));

	float mlx = 1.0f;
	float mly = 1.0f;
	if (m_speedRandom > 0)
	{
		mlx = 100.0f + (rand() % ( m_speedRandom * 2)) - m_speedRandom / 2;
		if (mlx < 1) mlx = 1;
		mlx /= 100.0f;
		mly = 100.0f + (rand() % (m_speedRandom * 2)) - m_speedRandom / 2;
		if (mly < 1) mly = 1;
		mly /= 100.0f;
	}

	float speedX = m_speedX * mlx;
	float speedY = m_speedY * mly;


	m_hotaru[n].speedX = speedX;
	m_hotaru[n].speedY = speedY;

	int thMax = (rand() % (m_yure * 4)) + m_yure;
	m_hotaru[n].thMax = thMax;
	m_hotaru[n].th = rand() % thMax;


	int inFrame = m_inFrame;
	int outFrame = m_outFrame;

	if (m_frameLengthRandom > 0)
	{
		float ml = 100.0f + (rand() % (m_frameLengthRandom * 2)) - m_frameLengthRandom / 2;
		inFrame = (int)((inFrame * ml) / 100);
		if (inFrame < 0) inFrame = 0;

		ml = 100.0f + (rand() % (m_frameLengthRandom * 2)) - m_frameLengthRandom / 2;
		outFrame = (int)((outFrame * ml) / 100);
		if (outFrame < 0) outFrame = 0;

	}

	int keepFrame = m_totalFrame - inFrame - outFrame;
	if (keepFrame <= 0) keepFrame = 1;
	if (m_frameLengthRandom > 0)
	{
		float ml = 100.0f + (rand() % (m_frameLengthRandom * 2)) - m_frameLengthRandom / 2;
		keepFrame = (int)((keepFrame * ml) / 100);
		if (keepFrame <= 0) keepFrame = 1;
	}


	m_hotaru[n].frameIn = inFrame;
	m_hotaru[n].frameKeep = keepFrame;
	m_hotaru[n].frameOut = outFrame;

	int startFrame = 0;
	if (randomStartFrame > 0)
	{
		int dv = inFrame + keepFrame + outFrame;
		if (dv > 0)
		{
			startFrame = rand() % dv;
		}
	}
	m_hotaru[n].frame = startFrame;
}

void CEffectHotaruNew::CalcuYureCosSin(void)
{
	if (m_yureKakudo == -1)
	{
		m_yureCos = 0.2;	//用心
		m_yureSin = 0.0;
		return;
	}

	double th = (double)m_yureKakudo;
	th *= 3.14159 * 2;
	th /= 360.0;

	m_yureCos = 0.2 * cos(th);
	m_yureSin = 0.2 * sin(th);
}

BOOL CEffectHotaruNew::CheckNeedPicPrint(LPVOID lpEffect, int layer)
{
	return FALSE;
}

/*_*/

