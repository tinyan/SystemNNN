//
// EffectCTrans.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "EffectCTrans.h"


CEffectCTrans::CEffectCTrans(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectCTrans::~CEffectCTrans()
{
	End();
}

void CEffectCTrans::End(void)
{
}

BOOL CEffectCTrans::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int para[24];
	int k = paraKosuu;
	if (k>23) k = 23;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}


	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 50;	//end percent
	if (paraKosuu<3) para[2] = 100;	//start percent

	if (paraKosuu<4) para[3] = 0;	//type
	if (paraKosuu<5) para[4] = 0;	//subframe

	if (paraKosuu<6) para[5] = 0;	//clipflag
	
	if (paraKosuu<7) para[6] = 0;
	if (paraKosuu<8) para[7] = 0;
	if (paraKosuu<9) para[8] = screenSizeX;
	if (paraKosuu<10) para[9] = screenSizeY;

	if (paraKosuu<11) para[10] = para[6];
	if (paraKosuu<12) para[11] = para[7];
	if (paraKosuu<13) para[12] = para[8];
	if (paraKosuu<14) para[13] = para[9];

	if (paraKosuu < 15) para[14] = 0;



	if (paraKosuu<16) para[15] = 0;	//end r
	if (paraKosuu<17) para[16] = para[15];	//end g
	if (paraKosuu<18) para[17] = para[16];	//end b

	if (paraKosuu<19) para[18] = para[15];	//start r
	if (paraKosuu<20) para[19] = para[16];	//start g
	if (paraKosuu<21) para[20] = para[17];	//start b


	if (paraKosuu<22) para[21] = 0;	//type
	if (paraKosuu<23) para[22] = 0;	//subframe





	lp->countMax = para[0];
	lp->flag = TRUE;
	lp->command = EFFECT_CTRANS;
	lp->count = 0;

	for (i=0;i<23;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectCTrans::CountIsMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	return TRUE;
}


void CEffectCTrans::BeginPrint(LPVOID para,int layer)
{

}

void CEffectCTrans::Init(LPVOID para,int layer)
{
}

void CEffectCTrans::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectCTrans::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;
	int pic = lp->pic;
	if (pic == -1) return;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;


	int count = lp->count;
	int countMax = lp->countMax;
	int type = lp->para[3];
	int subFrame = lp->para[4];
	int ps1 = lp->para[2];
	int ps2 = lp->para[1];

	int ps = CCalcuSpeed::calcu(count,countMax,ps1,ps2,subFrame,type);

	if (ps<0) ps = 0;
	if (ps>100) ps = 100;

	int x = lp->dst.left;
	int y = lp->dst.top;
	int srcX = lp->src.left;
	int srcY = lp->src.top;
	int sizeX = lp->dst.right;
	int sizeY = lp->dst.bottom;


	int addsubtype = lp->para[21];
	int addsubsubFrame = lp->para[22];

	int r1 = lp->para[18];
	int g1 = lp->para[19];
	int b1 = lp->para[20];

	int r2 = lp->para[15];
	int g2 = lp->para[16];
	int b2 = lp->para[17];

	int r = CCalcuSpeed::calcu(count,countMax,r1,r2,addsubsubFrame,addsubtype);
	int g = CCalcuSpeed::calcu(count,countMax,g1,g2,addsubsubFrame,addsubtype);
	int b = CCalcuSpeed::calcu(count,countMax,b1,b2,addsubsubFrame,addsubtype);





	//clip area
	if (lp->para[5])
	{
		int clipStartX = lp->para[10];
		int clipStartY = lp->para[11];
		int clipEndX = lp->para[6];
		int clipEndY = lp->para[7];

		int clipStartSizeX = lp->para[12];
		int clipStartSizeY = lp->para[13];
		int clipEndSizeX = lp->para[8];
		int clipEndSizeY = lp->para[9];

		int subFrame = 0;
		int speedType = 0;

		int clipX = CCalcuSpeed::calcu(count,countMax,clipStartX,clipEndX,subFrame,speedType);
		int clipY = CCalcuSpeed::calcu(count,countMax,clipStartY,clipEndY,subFrame,speedType);
		int clipSizeX = CCalcuSpeed::calcu(count,countMax,clipStartSizeX,clipEndSizeX,subFrame,speedType);
		int clipSizeY = CCalcuSpeed::calcu(count,countMax,clipStartSizeY,clipEndSizeY,subFrame,speedType);

		if ((clipSizeX<1) || (clipSizeY<1)) return;

		//clip

		int clipX2 = clipX + clipSizeX;
		int clipY2 = clipY + clipSizeY;

		if (x>clipX2) return;
		if (y>clipY2) return;
		if ((x+sizeX)<clipX) return;
		if ((y+sizeY)<clipY) return;

		if (x<clipX)
		{
			int delta = clipX - x;
			sizeX -= delta;
			x = clipX;
			srcX += delta;
		}

		if (y<clipY)
		{
			int delta = clipY - y;
			sizeY -= delta;
			y = clipY;
			srcY += delta;
		}

		if ((sizeX<1) || (sizeY<1)) return;


		if ((x+sizeX) > clipX2)
		{
			int delta = x+sizeX-clipX2;
			sizeX -= delta;
		}

		if ((y+sizeY) > clipY2)
		{
			int delta = y+sizeY-clipY2;
			sizeY -= delta;
		}

		if ((sizeX<1) || (sizeY<1)) return;
	}

	
//	if (lp->notTransFlag)

	if (lp->para[14] == 0)
	{
		if (lpPic->CheckMaskExist() == FALSE)
		{
			lpPic->TransLucentBlt0(x ,y ,srcX ,srcY ,sizeX,sizeY,ps);
		}
		else
		{
			lpPic->TransLucentBlt3(x ,y ,srcX ,srcY ,sizeX,sizeY,ps);
		}
	}
	else
	{
		lpPic->ColorAddBlt(x,y,srcX,srcY,sizeX,sizeY,TRUE,r,g,b,ps);

		//trans and co
	}
}


BOOL CEffectCTrans::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}



