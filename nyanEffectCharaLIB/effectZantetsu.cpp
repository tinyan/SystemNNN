//
// effectZantetsu.cpp
//

#include "..\nyanEffectLib\includer.h"
#include "effectZantetsu.h"


CEffectZantetsu::CEffectZantetsu(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	m_cutTable = NULL;

#if defined _TINYAN3DLIB_
	SetTextureKosuu(1);
	SetConstKosuu(1);
	Create("Zantetsu");
#endif
}

CEffectZantetsu::~CEffectZantetsu()
{
	End();
}

void CEffectZantetsu::End(void)
{
	DELETEARRAY(m_cutTable);
}

void CEffectZantetsu::InitParameter(LPVOID lpEffect, int layer)
{
	int para[16];
	EFFECT* lp = (EFFECT*)lpEffect;
	for (int i=0;i<16;i++)
	{
		para[i] = lp->para[i];
	}
	SetParam(lp,16,para,layer);
}

BOOL CEffectZantetsu::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int para[16];
	int k = paraKosuu;
	if (k>13) k = 13;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}
	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 0;	//Šp“x
	if (paraKosuu<3) para[2] = 100;//ˆÚ“®—Ê
	if (paraKosuu<4) para[3] = screenSizeX / 2;	//centerX
	if (paraKosuu<5) para[4] = screenSizeY / 2;	//centerY
	if (paraKosuu<6) para[5] = 2;	//transMode
	if (paraKosuu<7) para[6] = 1;	//‚¤‚²‚«‘ÎÛ‘I‘ð 1:¶ 2:‰E 3:¶+‰E(‹t)

	if (paraKosuu<8) para[7] = 0;	//speedType
	if (paraKosuu<9) para[8] = 0;	//subframe

	//ˆÈ‰º–¢ŽÀ‘•
	if (paraKosuu<10) para[9] = 100;	//transPercentEnd
	if (paraKosuu<11) para[10] = 0;	//transPercentStart
	if (paraKosuu<12) para[11] = 0;	//transSpeedType
	if (paraKosuu<13) para[12] = 0;	//transSubFrame

	for (i=0;i<13;i++)
	{
		lp->para[i] = para[i];
	}

	lp->flag = TRUE;
	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_ZANTETSU;

	ReCreateBuffer();

	return TRUE;
}


BOOL CEffectZantetsu::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectZantetsu::BeginPrint(LPVOID para,int layer)
{

}

void CEffectZantetsu::Init(LPVOID para,int layer)
{
}

void CEffectZantetsu::Calcu(LPVOID lpEffect,int layer)
{
	ReCreateBuffer();
}


void CEffectZantetsu::Print(LPVOID lpEffect,int layer)
{
	int i = 0;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	ReCreateBuffer();

	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int count = lp->count;
	int countMax = lp->countMax;

	int speedType = lp->para[7];
	int subFrame = lp->para[8];



//	int dv = countMax;
//	if (dv<1) dv = 1;


	int kakudo = lp->para[1];
	if (kakudo<-90) kakudo = -90;
	if (kakudo>90) kakudo = 90;
	int moveSize = lp->para[2];
	int centerX = lp->para[3];
	int centerY = lp->para[4];
	int moveTarget = lp->para[6];
	int md = lp->para[5];


	if (centerX<1) centerX = 1;
	if (centerY<1) centerY = 1;
	if (centerX >= screenSizeX-1) centerX = screenSizeX-2;
	if (centerY >= screenSizeY-1) centerY = screenSizeY-2;


	double leftMul = 0.0;
	double rightMul = 0.0;
	if (moveTarget == 1) leftMul = 1.0;
	if (moveTarget == 2) rightMul = 1.0;
	if (moveTarget == 3)
	{
		leftMul = 1.0;
		rightMul = -1.0;
	}

//	int ml = count;
//	if (ml>dv) ml = dv;

	int ml = CCalcuSpeed::calcu(count,countMax,0,10000,subFrame,speedType);

	int ps1 = lp->para[10];
	int ps2 = lp->para[9];
	int psSubFrame = lp->para[12];
	int psType = lp->para[11];

	int ps = CCalcuSpeed::calcu(count,countMax,ps1,ps2,psSubFrame,psType);

//kakudo = -30;


	double th = (double)kakudo;
	th /= 360.0;
	th *= 3.14159*2.0;

	double vectorX = -sin(th);
	double vectorY = cos(th);

	double ds = (double)(ml * moveSize);
//	ds /= (double)dv;
	ds /= 10000.0;

	int leftDeltaX = (int)(vectorX * ds * leftMul + 0.5);
	int leftDeltaY = (int)(vectorY * ds * leftMul + 0.5);
	int rightDeltaX = (int)(vectorX * ds * rightMul + 0.5);
	int rightDeltaY = (int)(vectorY * ds * rightMul + 0.5);

	int pic = lp->pic;
	if (pic == -1) return;
	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	int putX = lp->dst.left;
	int putY = lp->dst.top;

#if defined _TINYAN3DLIB_
	int leftChoten = 0;
	int rightChoten = 0;

	POINT leftShape[6];
	POINT rightShape[6];


	if (kakudo == -90)
	{
		//ue right
		if (centerY > 0)
		{
			rightChoten = 4;
			rightShape[0].x = 0;
			rightShape[0].y = 0;
			rightShape[1].x = screenSizeX;
			rightShape[1].y = 0;
			rightShape[2].x = screenSizeX;
			rightShape[2].y = centerY;
			rightShape[3].x = 0;
			rightShape[3].y = centerY;
		}

		if (centerY < screenSizeY)
		{
			leftChoten = 4;
			leftShape[0].x = 0;
			leftShape[0].y = centerY;
			leftShape[1].x = screenSizeX;
			leftShape[1].y = centerY;
			leftShape[2].x = screenSizeX;
			leftShape[2].y = screenSizeY;
			leftShape[3].x = 0;
			leftShape[3].y = screenSizeY;
		}
	}
	else if (kakudo == 90)
	{
		//ue left
		if (centerY > 0)
		{
			leftChoten = 4;
			leftShape[0].x = 0;
			leftShape[0].y = 0;
			leftShape[1].x = screenSizeX;
			leftShape[1].y = 0;
			leftShape[2].x = screenSizeX;
			leftShape[2].y = centerY;
			leftShape[3].x = 0;
			leftShape[3].y = centerY;
		}

		if (centerY < screenSizeY)
		{
			rightChoten = 4;
			rightShape[0].x = 0;
			rightShape[0].y = centerY;
			rightShape[1].x = screenSizeX;
			rightShape[1].y = centerY;
			rightShape[2].x = screenSizeX;
			rightShape[2].y = screenSizeY;
			rightShape[3].x = 0;
			rightShape[3].y = screenSizeY;
		}
	}
	else if (kakudo == 0)
	{
		if (centerX>0)
		{
			leftChoten = 4;
			leftShape[0].x = 0;
			leftShape[0].y = 0;
			leftShape[1].x = centerX;
			leftShape[1].y = 0;
			leftShape[2].x = centerX;
			leftShape[2].y = screenSizeY;
			leftShape[3].x = 0;
			leftShape[3].y = screenSizeY;
		}

		if (centerX<screenSizeX)
		{
			rightChoten = 4;
			rightShape[0].x = centerX;
			rightShape[0].y = 0;
			rightShape[1].x = screenSizeX;
			rightShape[1].y = 0;
			rightShape[2].x = screenSizeX;
			rightShape[2].y = screenSizeY;
			rightShape[3].x = centerX;
			rightShape[3].y = screenSizeY;
		}
	}
	else if (kakudo > 0)
	{
		// ^
		int upright = 0;
		int downleft = 0;

		int upx = centerX;
		int righty = centerY;
		int downx = centerX;
		int lefty = centerY;
		
		if (centerY == 0)
		{
			upright = 0;//up
		}
		else
		{
			upx = (int)(vectorX / vectorY * (double)(-centerY));
			upx += centerX;
			if (upx>=screenSizeX)
			{
				upright = 1;
				//calcu
				if (centerX >= screenSizeX)
				{
					righty = centerY;
				}
				else
				{
					righty = (int)(vectorY / vectorX * (double)(screenSizeX-centerX));
				}
			}
		}

		if (centerY>=screenSizeY)
		{
			downleft = 0;//down
		}
		else
		{
			downx = (int)(vectorX / vectorY * (double)(screenSizeY-centerY));
			downx += centerX;

			if (downx <= 0)
			{
				downleft = 1;
				//calcu
				if (centerX <= 0)
				{
					lefty = centerY;
				}
				else
				{
					lefty = (int)(vectorY / vectorX * (double)(-centerX));
				}
			}
		}

		//set
		leftShape[0].x = 0;
		leftShape[0].y = 0;
		leftChoten++;
		if (upright == 0)
		{
			leftShape[leftChoten].x = upx;
			leftShape[leftChoten].y = 0;
			leftChoten++;
		}
		else
		{
			leftShape[leftChoten].x = screenSizeX;
			leftShape[leftChoten].y = 0;
			leftChoten++;
			leftShape[leftChoten].x = screenSizeX;
			leftShape[leftChoten].y = righty;
			leftChoten++;
		}

		if (downleft == 0)
		{
			leftShape[leftChoten].x = downx;
			leftShape[leftChoten].y = screenSizeY;
			leftChoten++;
			leftShape[leftChoten].x = 0;
			leftShape[leftChoten].y = screenSizeY;
			leftChoten++;
		}
		else
		{
			leftShape[leftChoten].x = 0;
			leftShape[leftChoten].y = lefty;
			leftChoten++;
		}

		if (upright == 0)
		{
			rightShape[0].x = upx;
			rightShape[0].y = 0;
			rightChoten++;
			rightShape[rightChoten].x = screenSizeX;
			rightShape[rightChoten].y = 0;
			rightChoten++;
		}
		else
		{
			rightShape[0].x = screenSizeX;
			rightShape[0].y = righty;
			rightChoten++;
		}

		rightShape[rightChoten].x = screenSizeX;
		rightShape[rightChoten].y = screenSizeY;
		rightChoten++;

		if (downleft == 0)
		{
			rightShape[rightChoten].x = downx;
			rightShape[rightChoten].y = screenSizeY;
			rightChoten++;
		}
		else
		{
			rightShape[rightChoten].x = 0;
			rightShape[rightChoten].y = screenSizeY;
			rightChoten++;
			rightShape[rightChoten].x = 0;
			rightShape[rightChoten].y = lefty;
			rightChoten++;
		}



	}
	else
	{
		// _


		int upleft = 0;
		int downright = 0;

		int upx = centerX;
		int lefty = centerY;
		int downx = centerX;
		int righty = centerY;
		
		if (centerY == 0)
		{
			upleft = 0;//up
		}
		else
		{
			upx = (int)(vectorX / vectorY * (double)(-centerY));
			upx += centerX;
			if (upx<=0)
			{
				upleft = 1;
				//calcu
				if (centerX <= 0)
				{
					lefty = centerY;
				}
				else
				{
					lefty = (int)(vectorY / vectorX * (double)(-centerX));
				}
			}
		}


		if (centerY>=screenSizeY)
		{
			downright = screenSizeY;//down
		}
		else
		{
			downx = (int)(vectorX / vectorY * (double)(screenSizeY-centerY));
			downx += centerX;

			if (downx >= screenSizeX)
			{
				downright = 1;
				//calcu
				if (centerX >= screenSizeX)
				{
					righty = centerY;
				}
				else
				{
					righty = (int)(vectorY / vectorX * (double)(screenSizeX-centerX));
				}
			}
		}

		//set
		if (upleft == 0)
		{
			leftShape[0].x = 0;
			leftShape[0].y = 0;
			leftChoten++;
			leftShape[leftChoten].x = upx;
			leftShape[leftChoten].y = 0;
			leftChoten++;
		}
		else
		{
			leftShape[0].x = 0;
			leftShape[0].y = lefty;
			leftChoten++;
		}

		if (downright == 0)
		{
			leftShape[leftChoten].x = downx;
			leftShape[leftChoten].y = screenSizeY;
			leftChoten++;
		}
		else
		{
			leftShape[leftChoten].x = screenSizeX;
			leftShape[leftChoten].y = righty;
			leftChoten++;
			leftShape[leftChoten].x = screenSizeX;
			leftShape[leftChoten].y = screenSizeY;
			leftChoten++;
		}

		leftShape[leftChoten].x = 0;
		leftShape[leftChoten].y = screenSizeY;
		leftChoten++;

		if (upleft == 0)
		{
			rightShape[0].x = upx;
			rightShape[0].y = 0;
			rightChoten++;
		}
		else
		{
			rightShape[0].x = 0;
			rightShape[0].y = lefty;
			rightChoten++;
			rightShape[rightChoten].x = 0;
			rightShape[rightChoten].y = 0;
			rightChoten++;
		}

		rightShape[rightChoten].x = screenSizeX;
		rightShape[rightChoten].y = 0;
		rightChoten++;

		if (downright == 0)
		{
			rightShape[rightChoten].x = screenSizeX;
			rightShape[rightChoten].y = screenSizeY;
			rightChoten++;
			rightShape[rightChoten].x = downx;
			rightShape[rightChoten].y = screenSizeY;
			rightChoten++;
		}
		else
		{
			rightShape[rightChoten].x = screenSizeX;
			rightShape[rightChoten].y = righty;
			rightChoten++;
		}




	}




	if (CheckEffectError()) return;

	float alfa = (float)ps;
	alfa *= 0.01f;
	SetConst(alfa);

	CMyTexture* lpTexture = (CMyTexture*)(lpPic->GetTexture());
	SetTexture(lpTexture->GetTexture());

	POINT dstPoint[6];
	POINT srcPoint[6];

	if (leftChoten > 0)
	{
		for (int i=0;i<leftChoten;i++)
		{
			dstPoint[i].x = leftShape[i].x + leftDeltaX;
			dstPoint[i].y = leftShape[i].y + leftDeltaY;
			srcPoint[i].x = leftShape[i].x - putX;
			srcPoint[i].y = leftShape[i].y - putY;
		}

		PrintPolygon(dstPoint,srcPoint,leftChoten);
	}

	if (rightChoten > 0)
	{
		for (int i=0;i<rightChoten;i++)
		{
			dstPoint[i].x = rightShape[i].x + rightDeltaX;
			dstPoint[i].y = rightShape[i].y + rightDeltaY;
			srcPoint[i].x = rightShape[i].x - putX;
			srcPoint[i].y = rightShape[i].y - putY;
		}

		PrintPolygon(dstPoint,srcPoint,rightChoten);
	}



#else

	if (kakudo == -90)
	{
		//ue right
		int sp = centerY;
		if (sp>screenSizeY) sp = screenSizeY;
		for (i=0;i<sp;i++) m_cutTable[i] = 0;
		for (i=sp;i<screenSizeY;i++) m_cutTable[i] = screenSizeX;
	}
	else if (kakudo == 90)
	{
		//ue left
		int sp = centerY;
		if (sp>screenSizeY) sp = screenSizeY;
		for (i=0;i<sp;i++) m_cutTable[i] = screenSizeX;
		for (i=sp;i<screenSizeY;i++) m_cutTable[i] = 0;
	}
	else
	{
		for (i=0;i<screenSizeY;i++)
		{
			int dy = i - centerY;
			int dx = (int)(vectorX / vectorY * (double)dy + 0.5);
			int x = centerX + dx;
			if (x<0) x = 0;
			if (x>screenSizeX) x = screenSizeX;
			m_cutTable[i] = x;
		}
	}






	int srcX = 0;
	int srcY = 0;
	
	RECT rc;
	lpPic->GetPicSize(&rc);

	int sizeX = rc.right;
	int sizeY = rc.bottom;

	lpPic->LeftBlt(putX+leftDeltaX,putY+leftDeltaY,srcX,srcY,sizeX,sizeY,TRUE,m_cutTable,ps);
	lpPic->RightBlt(putX+rightDeltaX,putY+rightDeltaY,srcX,srcY,sizeX,sizeY,TRUE,m_cutTable,ps);
#endif

}


BOOL CEffectZantetsu::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectZantetsu::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectZantetsu::ReCreateBuffer(void)
{
	if (m_cutTable == NULL)
	{
		int screenSizeY = CMyGraphics::GetScreenSizeY();
		m_cutTable = new int[screenSizeY];
	}
}
