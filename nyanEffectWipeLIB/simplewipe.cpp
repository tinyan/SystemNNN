//
// simplewipe.cpp
//

#include "..\nyanEffectLib\includer.h"


#include "..\nyanEffectEtcLib\effectGet.h"

#if defined _TINYAN3DLIB_
#include "..\..\systemNNN3D\nyanWipe3DLib\allSimpleWipe.h"
#else
#include "..\nyanWipeLib\allSimpleWipe.h"
#endif

#include "simplewipe.h"



CEffectSimpleWipe::CEffectSimpleWipe(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	m_allWipe = new CAllSimpleWipe();
}


CEffectSimpleWipe::~CEffectSimpleWipe()
{
	End();
}


void CEffectSimpleWipe::End(void)
{
	ENDDELETECLASS(m_allWipe);
}





BOOL CEffectSimpleWipe::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	if (paraKosuu<2) return FALSE;	//bad!!

	EFFECT* lp = (EFFECT*)lpEffect;

	//Ží—Þ,buffer,count

	int para[9];
	int k = paraKosuu;
	if (k>9) k = 9;

	int i;
	for (i=0;i<paraKosuu;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;	//frame

	if (paraKosuu<2) para[1] = 0;	//Ží—Þ
	if (paraKosuu<3) para[2] = 13;	//buffer
	if (paraKosuu<4) para[3] = 0;	//subframe type
	if (paraKosuu<5) para[4] = 0;	//subframe num
	if (paraKosuu<6) para[5] = 100;	//%end
	if (paraKosuu<7) para[6] = 0;	//%start
	if (paraKosuu<8) para[7] = 0;	//end buffer flag
	if (paraKosuu<9) para[8] = 0;	//start buffer flag

	if (para[1]<0) para[1] = 0;


//	if (para[0] >= WIPES_KOSUU) para[0] = WIPES_KOSUU-1;


	for (i=0;i<9;i++)
	{
		lp->para[i] = para[i];
	}

	lp->count = 0;
	lp->countMax = para[0];
	lp->flag = TRUE;
	lp->command = EFFECT_SIMPLEWIPE;

	return TRUE;
}



BOOL CEffectSimpleWipe::CountIsMax(LPVOID lpEffect,int layer)
{
/*
	EFFECT* lp = (EFFECT*)lpEffect;
	lp->count = lp->countMax;

	if (lp->para[8] != 0) return TRUE;

	int typ = lp->para[3];
	int md = 0;
	if ((typ == 3) || (typ == 4))
	{
		md = 1;
	}
	int last = lp->para[5];

	if (md == 1)
	{
		last = lp->para[6];
	}


	int buf = lp->para[1];
	if (buf != -1) 
	{
		if (last == 100)
		{
			lp->command = EFFECT_BUFFER;
			m_allEffect->ChangeEffectCommandOnly(buf,EFFECT_NOP);
		}
		if ((last == 0) && (lp->para[7] == 0))
		{
			lp->command = EFFECT_NOP;
		}
	}
*/
	return TRUE;
}


void CEffectSimpleWipe::BeginPrint(LPVOID para,int layer)
{
}


void CEffectSimpleWipe::Init(LPVOID para,int layer)
{
}

void CEffectSimpleWipe::Calcu(LPVOID lpEffect,int layer)
{
}

void CEffectSimpleWipe::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int count = lp->count;
	int countMax = lp->countMax;
	int speedType = lp->para[3];
	int subFrame = lp->para[4];

	int endBufferFlag = lp->para[7];
	int startBufferFlag = lp->para[8];


	int pic1 = lp->pic;
	if ((pic1 == -1) && (startBufferFlag == 0)) return;

	int pic2 = lp->para[2];
	if ((pic2 == -1) && (endBufferFlag == 0)) return;

	CPicture* lpPicStart = NULL;
	RECT rc;

	if (startBufferFlag == 0)
	{
		lpPicStart = m_allEffect->GetPicture(layer);
		if (lpPicStart == NULL)
		{
			return;
		}
		lpPicStart->GetPicSize(&rc);
		if (rc.right < screenSizeX) return;
		if (rc.bottom < screenSizeY) return;
	}
	else
	{
		lpPicStart = CEffectGet::m_effectGetBufferPicture;
		SetRect(&rc,0,0,screenSizeX,screenSizeY);
	}


	CPicture* lpPicEnd = NULL;
	RECT rc2;
	if (endBufferFlag == 0)
	{
		lpPicEnd = m_allEffect->GetPicture(pic2);
		if (lpPicEnd == NULL) return;

		lpPicEnd->GetPicSize(&rc2);
		if (rc2.right < screenSizeX) return;
		if (rc2.bottom < screenSizeY) return;
	}
	else
	{
		lpPicEnd = CEffectGet::m_effectGetBufferPicture;
		SetRect(&rc2,0,0,screenSizeX,screenSizeY);
	}



	POINT startPoint0;

	if (startBufferFlag == 0)
	{
		startPoint0 = m_allEffect->GetDstPoint(pic1);
	}
	else
	{
		startPoint0.x = 0;
		startPoint0.y = 0;
	}

	POINT endPoint0;

	if (endBufferFlag == 0)
	{
		endPoint0 = m_allEffect->GetDstPoint(pic2);
	}
	else
	{
		endPoint0.x = 0;
		endPoint0.y = 0;
	}

	int startX = -startPoint0.x;
	int startY = -startPoint0.y;
	int endX = -endPoint0.x;
	int endY = -endPoint0.y;



	POINT startPoint;
	POINT endPoint;

	startPoint.x = startX;
	startPoint.y = startY;
	endPoint.x = endX;
	endPoint.y = endY;


	int ps = CCalcuSpeed::calcu(count,countMax,lp->para[6]*100,lp->para[5]*100,subFrame,speedType);

	m_allWipe->PrintWipe(lp->para[1],lpPicStart,lpPicEnd,ps,10000,&startPoint,&endPoint);
}

CEffectSimpleWipeCommon* CEffectSimpleWipe::GetWipeObject(int n)
{
	return m_allWipe->GetWipeObject(n);
}

BOOL CEffectSimpleWipe::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectSimpleWipe::ReCreateAllShader(void)
{
#if defined _TINYAN3DLIB_
	m_allWipe->ReCreateAllShader();
#endif
}


/*_*/

