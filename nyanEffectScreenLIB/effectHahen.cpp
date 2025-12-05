//
// effectHahen.cpp
//
#include <windows.h>
#include <stdio.h>

#include "..\nyanEffectLib\includer.h"


#include "..\..\systemNNN\nnnUtilLib\nameList.h"

#include "effectHahen.h"


int CEffectHahen::m_vertex0[]=
{
	0,0, 90,0, 215,0, 255,0, 421,0, 511,0, 639,0, 0,70, 166,65, 188,33,
	251,50, 320,102, 390,72, 494,56, 483,86, 460,58, 639,87, 0,136, 26,121, 123,175,
	188,146, 288,169, 480,177, 576,155, 639,197, 0,188,80,242, 109,249, 180,278, 266,272,
	297,224, 356,265, 444,235, 538,286,639,249, 0,259, 0,309, 40,343,114,338, 274,330,
	393,321, 483,347, 547,331, 0,385, 91,411, 208,402, 315,381, 425,379, 372,408, 493,435,
	553,377, 639,429, 0,479, 22,479, 47,450, 96,456, 121,445,93,479, 215,479, 325,466,
	309,479, 414,479, 453,479, 536,479, 550,479, 639,479,
};
/*
int CEffectHahen::m_vertex[]=
{
	0,0, 90,0, 215,0, 255,0, 421,0, 511,0, 639,0, 0,70, 166,65, 188,33,
	251,50, 320,102, 390,72, 494,56, 483,86, 460,58, 639,87, 0,136, 26,121, 123,175,
	188,146, 288,169, 480,177, 576,155, 639,197, 0,188,80,242, 109,249, 180,278, 266,272,
	297,224, 356,265, 444,235, 538,286,639,249, 0,259, 0,309, 40,343,114,338, 274,330,
	393,321, 483,347, 547,331, 0,385, 91,411, 208,402, 315,381, 425,379, 372,408, 493,435,
	553,377, 639,429, 0,479, 22,479, 47,450, 96,456, 121,445,93,479, 215,479, 325,466,
	309,479, 414,479, 453,479, 536,479, 550,479, 639,479,
};
*/

int CEffectHahen::m_surface[][1+15]=
{
	{7, 0,7,18,19,20,8,1},
	{3, 1,8,2},
	{4, 2,9,10,3},
	{5, 3,10,11,12,4},
	{4, 4,12,13,5},
	{6, 5,14,22,23,16,6},
	{3, 13,15,14},
	{3, 7,17,18},
	{6, 9,8,20,21,11,10},
	{9, 15,12,11,21,30,31,32,22,14},

	{3, 16,23,24},
	{6, 18,17,25,26,27,19},
	{7, 20,19,27,28,29,30,21},
	{6, 23,22,32,33,34,24},
	{3, 25,35,26},
	{7, 26,35,36,37,38,28,27},
	{7, 29,28,38,44,56,45,39},
	{7, 30,29,39,46,47,40,31},
	{6, 32,31,40,41,42,33},
	{4, 34,33,50,51},

	{3, 36,43,37},
	{6, 38,37,43,52,53,44},
	{4, 44,54,55,56},
	{4, 54,53,57,55},
	{4, 45,55,57,58},
	{6, 39,45,58,60,59,46},
	{4, 47,46,59,48},
	{3, 48,60,61},
	{6, 40,48,61,62,49,41},
	{3, 49,62,63},

	{6, 42,41,49,63,64,50},
	{4, 50,64,65,51},
};


//0:default
//1:create
//2:from file

CEffectHahen::CEffectHahen(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	m_createdBunkatsuKosuu = 0;
	m_bunkatsuWorkKosuu = 0;
	m_bunkatsuTypeTable = NULL;
	m_vertexTable = NULL;
	m_surfaceTable = NULL;
	ExpandBunkatsuWork();



	//create default
	int vertexKosuu = 66;
	int surfaceKosuu = 32;
	CreateBuffer(vertexKosuu,surfaceKosuu);
	SetTypeTable(0);
	int* vertexBuffer = GetVertexBuffer(0);
	vertexBuffer[0] = vertexKosuu;
	for (int i=0;i<vertexKosuu;i++)
	{
		int x = m_vertex0[i*2];
		int y = m_vertex0[i*2+1];

		x *= screenSizeX;
		x /= 640;						//特例によりマジックナンバーOK(元データサイズが640x480のため)
		y *= screenSizeY;
		y /= 480;
		if (x>screenSizeX-1) x = screenSizeX-1;
		if (y>screenSizeY-1) y = screenSizeY-1;

		vertexBuffer[1+i*2] = x;
		vertexBuffer[1+i*2+1] = y;
//		m_vertex[i*2] = x;
//		m_vertex[i*2+1] = y;

	}
	int* surfaceBuffer = GetSurfaceBuffer(0);
	surfaceBuffer[0] = surfaceKosuu;
	for (int i=0;i<surfaceKosuu;i++)
	{
		int choten = m_surface[i][0];
		surfaceBuffer[1+i*16+0] = choten;
		for (int k=0;k<choten;k++)
		{
			surfaceBuffer[1+i*16+1+k] = m_surface[i][1+k];
		}
	}



	m_createdBunkatsuKosuu++;



	m_hahenWorkKosuu = 32;
	m_hahen = new HAHEN[m_hahenWorkKosuu];




/*
	m_poliKosuu = 0;
	for (int i=0;i<66;i++)
	{
		int x = m_vertex0[i*2];
		int y = m_vertex0[i*2+1];

		x *= screenSizeX;
		x /= 640;						//特例によりマジックナンバーOK(元データサイズが640x480のため)
		y *= screenSizeY;
		y /= 480;
		if (x>screenSizeX-1) x = screenSizeX-1;
		if (y>screenSizeY-1) y = screenSizeY-1;

		m_vertex[i*2] = x;
		m_vertex[i*2+1] = y;
	}
*/

#if defined _TINYAN3DLIB_
	SetTextureKosuu(1);
	Create("Polygon");//dummy
#endif

}

CEffectHahen::~CEffectHahen()
{
	End();
}

void CEffectHahen::End(void)
{
	if (m_createdBunkatsuKosuu > 0)
	{
		DELETEARRAY(m_bunkatsuTypeTable);
		for (int i=0;i<m_createdBunkatsuKosuu;i++)
		{
			DELETEARRAY(m_surfaceTable[i]);
			DELETEARRAY(m_vertexTable[i]);
		}
		DELETEARRAY(m_surfaceTable);
		DELETEARRAY(m_vertexTable);

		m_createdBunkatsuKosuu = 0;
	}

	DELETEARRAY(m_hahen);
}


void CEffectHahen::InitParameter(LPVOID lpEffect, int layer)
{
	int para[32];
	EFFECT* lp = (EFFECT*)lpEffect;
	for (int i=0;i<18;i++)
	{
		para[i] = lp->para[i];
	}
	SetParam(lp,18,para,layer);
}

BOOL CEffectHahen::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int para[18];
	int k = paraKosuu;
	if (k>18) k = 18;
	for (int i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}




	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 100;	//v
	if (paraKosuu<3) para[2] = 100;	//g
	if (paraKosuu<4) para[3] = screenSizeX / 2;	//x
	if (paraKosuu<5) para[4] = screenSizeY / 2;	//y

	if (paraKosuu<6) para[5] = 0;	//初期wait
	if (paraKosuu<7) para[6] = 100;	//初期ひび%
	if (para[6]>para[0]) para[6] = para[0];

	if (paraKosuu<8) para[7] = 0;	//type
	if (paraKosuu<9) para[8] = 0;	//subframe

	if (paraKosuu < 10) para[9] = 100;//psEnd
	if (paraKosuu < 11) para[10] = para[9];//psStart
	if (paraKosuu<12) para[11] = 0;	//type
	if (paraKosuu<13) para[12] = 0;	//subframe

	if (paraKosuu < 14) para[13] = 0;//分割タイプ
	if (paraKosuu < 15) para[14] = 0;//分割ぱら
	if (paraKosuu < 16) para[15] = 0;//分割ぱら
	if (paraKosuu < 17) para[16] = 0;//分割ぱら
	if (paraKosuu < 18) para[17] = 0;//分割ぱら

	if (para[13] == 0)
	{
		for (int i=0;i<4;i++)
		{
			para[14+i] = 0;
		}
	}
	else if (para[13] == 2)
	{
		for (int i=1;i<4;i++)
		{
			para[14+i] = 0;
		}
	}

//	if (paraKosuu<8) para[7] = 30;	//rndv
//	if (paraKosuu<9) para[8] = 15;	//rndth
//	if (paraKosuu<10) para[9] = 15;	//vx
//	if (paraKosuu<11) para[10] = 15;	//vy
//	if (paraKosuu<12) para[11] = 0;	//masatu


	lp->flag = TRUE;
	lp->command = EFFECT_HAHEN;
	lp->countMax = para[0];
	lp->count = 0;

	for (int i=0;i<18;i++)
	{
		lp->para[i] = para[i];
	}


	int found = SearchOrCreateBunkatsu(para[13],&para[14]);

	int* vertexBuffer = GetVertexBuffer(found);
	int* surfaceBuffer = GetSurfaceBuffer(found);


	int surfaceKosuu = surfaceBuffer[0];
	if (surfaceKosuu > m_hahenWorkKosuu)
	{
		DELETEARRAY(m_hahen);
		m_hahenWorkKosuu = surfaceKosuu;
		m_hahen = new HAHEN[m_hahenWorkKosuu];
	}


	//m_poliKosuu = 32;

	int centerX = para[3];
	int centerY = para[4];

//	for (i=0;i<m_poliKosuu;i++)
	for (int i=0;i<surfaceKosuu;i++)
	{
		int k = surfaceBuffer[i*16+1];
		int x = 0;
		int y = 0;
		for (int j=0;j<k;j++)
		{
			int p = surfaceBuffer[i*16+1+j];
			x += vertexBuffer[1+p*2];
			y += vertexBuffer[1+p*2+1];
		}
		x /= k;
		y /= k;

//		m_centerXY[i*2] = x;
//		m_centerXY[i*2+1] = y;

		m_hahen[i].x = 0.0f;
		m_hahen[i].y = 0.0f;

		double r2 = (y-centerY)*(y-centerY) + (x-centerX)*(x-centerX);
		double r = sqrt(r2);
		if (r<1.0) r = 1.0;

		double v = (double)para[1];
		v *= 0.01;
		v *= 30.0;

		//距離による修正
		v *= (1.0 + r/200.0);


		double th = atan2((double)(y - centerY), (double)(x - centerX));
		double cosTH = cos(th);
		double sinTH = sin(th);


		m_hahen[i].speedX = (float)(cosTH * v);
		m_hahen[i].speedY = (float)(sinTH * v);

		m_hahen[i].kasokuX = 0.0f;
		m_hahen[i].kasokuY = ((float)para[2]) * 0.01f;

	}

	return TRUE;
}


BOOL CEffectHahen::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectHahen::BeginPrint(LPVOID para,int layer)
{

}

void CEffectHahen::Init(LPVOID para,int layer)
{
}

void CEffectHahen::Calcu(LPVOID lpEffect,int layer)
{
	return;

	EFFECT* lp = (EFFECT*)lpEffect;
	int c = lp->count;
	int countMax = lp->countMax;

//	int dv = lp->countMax;

	//if (c>=countMax) return;
//	int subFrame = lp->para[];
//	int cc = CCalcuSpeed::calcu(c,countMax,0,countMax,subFrame,subType);



	int found = SearchBunkatsu(lp->para[13],&(lp->para[14]));
	if (found == -1) return;//error!

	int* surfaceBuffer = GetSurfaceBuffer(found);
	int surfaceKosuu = surfaceBuffer[0];


	if (c<lp->para[5])
	{
//		float ml = (float)(c+1);
//		ml /= (float)(lp->para[10]);
		float ml = float(lp->para[6]);
		ml *= 0.001f;

		for (int i=0;i<surfaceKosuu;i++)
		{
			m_hahen[i].x += m_hahen[i].speedX * ml;
			m_hahen[i].y += m_hahen[i].speedY * ml;
//			m_hahen[i].speedX += m_hahen[i].kasokuX;
//			m_hahen[i].speedY += m_hahen[i].kasokuY;
		}
	}
	else
	{
		for (int i=0;i<surfaceKosuu;i++)
		{
			m_hahen[i].x += m_hahen[i].speedX;
			m_hahen[i].y += m_hahen[i].speedY;
			m_hahen[i].speedX += m_hahen[i].kasokuX;
			m_hahen[i].speedY += m_hahen[i].kasokuY;
		}
	}






}


void CEffectHahen::Print(LPVOID lpEffect,int layer)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (layer == -1) return;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	int* srcPic = (int*)(lpPic->GetBuffer());
	if (srcPic == NULL) return;

	RECT rc;
	lpPic->GetPicSize(&rc);

	int picSizeX = rc.right;
	int picSizeY = rc.bottom;
	

	EFFECT* lp = (EFFECT*)lpEffect;
	int count = lp->count;
	int countMax = lp->countMax;


	double leftLimit = (double)(-screenSizeX);
	double rightLimit = (double)(screenSizeX*2);
	double topLimit = (double)(-screenSizeY);
	double bottomLimit = (double)(screenSizeY*2);

	int speedType = lp->para[7];
	int subFrame = lp->para[8];

	int count2 = CCalcuSpeed::calcu(count,countMax,0,countMax,subFrame,speedType);


	int transSubType = lp->para[11];
	int transSubFrame = lp->para[12];
	int transStart = lp->para[10];
	int transEnd = lp->para[9];

	int ps256 = CCalcuSpeed::calcu(count,countMax,transStart*256,transEnd*256,transSubFrame,transSubType);
	ps256 /= 100;




#if defined _TINYAN3DLIB_
	CMyTexture* lpTexture1 = (CMyTexture*)(lpPic->GetTexture());
	if (lpTexture1 == NULL) return;
	SetTexture(lpTexture1->GetTexture(),0);
#endif


	int found = SearchBunkatsu(lp->para[13],&(lp->para[14]));
	if (found == -1) return;//error!

	int* surfaceBuffer = GetSurfaceBuffer(found);
	int surfaceKosuu = surfaceBuffer[0];

	int* vertexBuffer = GetVertexBuffer(found);

	int zahyo[16*2];
	for (int i=0;i<surfaceKosuu;i++)
	{
		int hibiCount = count2;
		if (hibiCount >= lp->para[5]) hibiCount = lp->para[5];

		double startMulti = (double)(hibiCount * lp->para[6]);
		startMulti *= 0.001f;

		double xx = startMulti * m_hahen[i].speedX;
		double yy = startMulti * m_hahen[i].speedY;

		int hibiCount2 = count2 - lp->para[5];

		if (hibiCount2 > 0)
		{
			double dt = (double)(hibiCount2);
			xx += m_hahen[i].speedX * dt;
			yy += m_hahen[i].speedY * dt;
			yy += 0.5 * m_hahen[i].kasokuY * dt * dt;
		}

		if ((xx<leftLimit) || (xx>rightLimit) || (yy<topLimit) || (yy>bottomLimit)) continue;

		int putX = (int)(xx + 0.5);
		int putY = (int)(yy + 0.5);

//		int n = m_surface[i][0];
//		int n0 = m_surface[i][1];
		int n = surfaceBuffer[1+i*16+0];
		int n0 = surfaceBuffer[1+i*16+1];

//		int minX = m_vertex[n0*2];
		int minX = vertexBuffer[1+n0*2];
		int maxX = minX;
//		int minY = m_vertex[n0*2+1];
		int minY = vertexBuffer[1+n0*2+1];
		int maxY = minY;

		zahyo[0] = minX;
		zahyo[1] = minY;
		zahyo[n*2] = minX;
		zahyo[n*2+1] = minY;

		for (int k=1;k<n;k++)
		{
	//		int p = m_surface[i][1+k];
			int p = surfaceBuffer[1+i*16+1+k];
//			int x = m_vertex[p*2];
//			int y = m_vertex[p*2+1];
			int x = vertexBuffer[1+p*2];
			int y = vertexBuffer[1+p*2+1];

			zahyo[k*2] = x;
			zahyo[k*2+1] = y;

			if (x<minX) minX = x;
			if (x>maxX) maxX = x;
			if (y<minY) minY = y;
			if (y>maxY) maxY = y;
		}


		//clip
		if ((putX+minX) >= screenSizeX) continue;
		if ((putX+maxX) < 0) continue;
		if ((putY+minY) >= screenSizeY) continue;
		if ((putY+maxY) < 0) continue;
		
//putX = -57;
//putY = -343;
//char mes[256];
//sprintf(mes,"[%d %d %d %d]",i,putX,putY,maxY-minY+1);
//OutputDebugString(mes);

		PrintNormalPoligon(srcPic, picSizeX, picSizeY,n, putX, putY, maxY - minY + 1, zahyo,ps256);
	}

	return;
}

#if defined _TINYAN3DLIB_

void CEffectHahen::PrintNormalPoligon(int*lpPicSrc,int picSizeX,int picSizeY,int n, int putX, int putY, int sizeY,int* lpZahyo,int ps)
{
	POINT srcPoint[16];
	POINT dstPoint[16];

	for (int i=0;i<n;i++)
	{
		srcPoint[i].x = lpZahyo[i*2];
		srcPoint[i].y = lpZahyo[i*2+1];
		dstPoint[i].x = putX + lpZahyo[i*2];
		dstPoint[i].y = putY + lpZahyo[i*2+1];
	}

	PrintPolygon(dstPoint,srcPoint,n);
}

#else
void CEffectHahen::PrintNormalPoligon(int* lpPicSrc, int picSizeX, int picSizeY,int n, int putX, int putY, int sizeY, int* lpZahyo,int ps256)
{
//	int work[MAXSCREENSIZEY*2];
//	int* work = CEffectSimpleWipe::m_shapeWork;
	int* work = m_allEffect->GetTempWork();


	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int lPitch = screenSizeX * sizeof(int);

	int* workPtr = work;
	int* dst = CMyGraphics::GetScreenBuffer();

	int* src = lpPicSrc;
	int srcLPitch = picSizeX * sizeof(int);

	int leftN = 0;
	int rightN = n;

	int y1 = lpZahyo[leftN*2+1];
	int y2 = lpZahyo[rightN*2+1];
	int y3 = lpZahyo[(rightN-1)*2+1];

	if (y2 == y3)
	{
		rightN--;
	}

	int startY = y1 + putY;
	int endY = y1 + sizeY + putY;
	int srcY = y1;

	if (startY>=screenSizeY) return;
	if (endY<0) return;

	if (startY<0)
	{
		workPtr += 2 * (-startY);
//		src += picSizeX * (-startY);
		srcY += (-startY);

		startY = 0;
	}


	src += picSizeX * srcY;


	if (endY>=screenSizeY) endY = screenSizeY - 1;
	int sy = endY - startY + 1;
	if (sy<=0) return;




	dst += screenSizeX * startY;





	float leftFromX = (float)lpZahyo[leftN*2];
	float leftToX = (float)lpZahyo[(leftN+1)*2];

	float rightFromX = (float)lpZahyo[rightN*2];
	float rightToX = (float)lpZahyo[(rightN-1)*2];

	int leftCount = 0;
	int rightCount = 0;

	int leftSizeY = lpZahyo[(leftN+1)*2+1] - lpZahyo[leftN*2+1];
	int rightSizeY = lpZahyo[(rightN-1)*2+1] - lpZahyo[rightN*2+1];

	int loopY = 0;
	int y = y1 + putY; 

	float leftDiv = (float)leftSizeY;
	if (leftDiv <= 1.0f) leftDiv = 1.0f;
	float leftDivRev = 1.0f / leftDiv;

	float rightDiv = (float)rightSizeY;
	if (rightDiv <= 1.0f) rightDiv = 1.0f;
	float rightDivRev = 1.0f / rightDiv;


	for (int i=0;i<sizeY;i++)
	{
		if (y<0)
		{
			work[i*2] = 0;
			work[i*2+1] = 0;
		}
		else
		{

			float leftX = leftFromX + ((leftToX - leftFromX) * ((float)leftCount)) * leftDivRev + 0.5f;
			float rightX = rightFromX + ((rightToX - rightFromX) * ((float)rightCount)) * rightDivRev + 0.5f;

			int startX = (int)leftX;
			int endX = (int)rightX;

			int sizeX = endX - startX;

			int xx1 = putX + startX;
			int xx2 = putX + endX;

			if ((xx1>=screenSizeX) || (xx2<0) || (sizeX<=0))
			{
				work[i*2] = 0;
				work[i*2+1] = 0;
			}
			else
			{
				if (xx1<0)
				{
					startX += (-xx1);
					xx1 = 0;
				}

				if (xx2>=screenSizeX)
				{
					xx2 = screenSizeX - 1;
				}
				sizeX = xx2 - xx1 + 1;
				
				if (sizeX<=0)
				{
					work[i*2] = 0;
					work[i*2+1] = 0;
				}
				else
				{
					work[i*2] = sizeX;
					work[i*2+1] = startX;
				}
			}
			loopY++;
		}

		y++;
		if (y>=screenSizeY) break;

		//left next??
		leftCount++;
		if (leftCount>=leftSizeY)
		{
			leftN++;
			leftCount = 0;
			leftFromX = (float)lpZahyo[leftN*2];
			leftToX = (float)lpZahyo[(leftN+1)*2];
			leftSizeY = lpZahyo[(leftN+1)*2+1] - lpZahyo[leftN*2+1];
			leftDiv = (float)leftSizeY;
			if (leftDiv <= 1.0f) leftDiv = 1.0f;
			leftDivRev = 1.0f / leftDiv;
		}

		//right next??
		rightCount++;
		if (rightCount>=rightSizeY)
		{
			rightN--;
			rightCount = 0;
			rightFromX = (float)lpZahyo[rightN*2];
			rightToX = (float)lpZahyo[(rightN-1)*2];
			rightSizeY = lpZahyo[(rightN-1)*2+1] - lpZahyo[rightN*2+1];
			rightDiv = (float)rightSizeY;
			if (rightDiv <= 1.0f) rightDiv = 1.0f;
			rightDivRev = 1.0f / rightDiv;
		}

		//last line??
		if (i == (sizeY-2))
		{
			if ((leftSizeY==0) || (rightSizeY==0))
			{
				leftN--;
				rightN++;
				leftFromX = (float)lpZahyo[leftN*2];
				leftToX = (float)lpZahyo[(leftN+1)*2];
				leftSizeY = lpZahyo[(leftN+1)*2+1] - lpZahyo[leftN*2+1];
				rightFromX = (float)lpZahyo[rightN*2];
				rightToX = (float)lpZahyo[(rightN-1)*2];
				rightSizeY = lpZahyo[(rightN-1)*2+1] - lpZahyo[rightN*2+1];
				
				leftCount = leftSizeY;
				rightCount = rightSizeY;
				leftDiv = (float)leftSizeY;
				if (leftDiv <= 1.0f) leftDiv = 1.0f;
				rightDiv = (float)rightSizeY;
				if (rightDiv <= 1.0f) rightDiv = 1.0f;
				leftDivRev = 1.0f / leftDiv;
				rightDivRev = 1.0f / rightDiv;
			}
		}
	}

	if (srcY + loopY >= picSizeY)
	{
		loopY = picSizeY - srcY;
	}

	if (loopY<=0) return;

	int deltaX = putX * 4;

	int trans = ps256;

#if defined _WIN64
#pragma message("ここにc++実装が必要にゃ " __FILE__)

#else

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		pxor mm0,mm0
		mov eax,trans
		cmp eax,256
		jz NORMAL

		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6

		neg eax
		add eax,256
		movd mm7,eax
		punpcklwd mm7,mm7
		punpckldq mm7,mm7



		mov edx,loopY
		mov esi,src
		mov edi,dst
		mov ebx,workPtr
LOOP2:
		push ebx
		push edx
		push esi
		push edi

		mov ecx,[ebx]
		cmp ecx,1
		js SKIP2

		mov eax,[ebx+4]
		shl eax,2
		add esi,eax
		add edi,eax
		add edi,deltaX

LOOP3:
		//rep movsd
		mov eax,[esi]
		movd mm1,eax
		punpcklbw mm1,mm0
		mov eax,[edi]
		movd mm2,eax
		punpcklbw mm2,mm0
		pmullw mm1,mm6
		pmullw mm2,mm7
		paddw mm1,mm2
		psrlw mm1,8
		packuswb mm1,mm0
		movd eax,mm1
		mov [edi],eax




		add esi,4
		add edi,4
		dec ecx
		jnz LOOP3

SKIP2:
		pop edi
		pop esi
		pop edx
		pop ebx
		add edi,lPitch
		add esi,srcLPitch
		add ebx,4*2

		dec edx
		jnz LOOP2

		JMP EXIT1




NORMAL:
		cld
		mov edx,loopY
		mov esi,src
		mov edi,dst
		mov ebx,workPtr
LOOP1:
		push ebx
		push edx
		push esi
		push edi

		mov ecx,[ebx]
		cmp ecx,1
		js SKIP1

		mov eax,[ebx+4]
		shl eax,2
		add esi,eax
		add edi,eax
		add edi,deltaX

		rep movsd

SKIP1:
		pop edi
		pop esi
		pop edx
		pop ebx
		add edi,lPitch
		add esi,srcLPitch
		add ebx,4*2

		dec edx
		jnz LOOP1
EXIT1:
		emms
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
#endif

}


#endif


void CEffectHahen::ExpandBunkatsuWork(int add)
{
	int n = m_bunkatsuWorkKosuu + add;

	int* typeTable = new int[n*16];
	int** vertexTable = new int*[n];
	int** surfaceTable = new int*[n];

	for (int i=0;i<m_createdBunkatsuKosuu;i++)
	{
		for (int p=0;p<16;p++)
		{
			typeTable[i*16+p] = m_bunkatsuTypeTable[i*16+p];

		}

		vertexTable[i] = m_vertexTable[i];
		surfaceTable[i] = m_surfaceTable[i];
	}

	DELETEARRAY(m_bunkatsuTypeTable);
	DELETEARRAY(m_vertexTable);
	DELETEARRAY(m_surfaceTable);

	m_bunkatsuTypeTable = typeTable;
	m_vertexTable = vertexTable;
	m_surfaceTable = surfaceTable;

	m_bunkatsuWorkKosuu = n;
}


void CEffectHahen::CreateBuffer(int vertexKosuu,int surfaceKosuu)
{
	m_vertexTable[m_createdBunkatsuKosuu] = new int[1+vertexKosuu*2];
	m_surfaceTable[m_createdBunkatsuKosuu] = new int[1+surfaceKosuu*16];
}

int* CEffectHahen::GetVertexBuffer(int n)
{
	return m_vertexTable[n];
}

int* CEffectHahen::GetSurfaceBuffer(int n)
{
	return m_surfaceTable[n];
}

int CEffectHahen::SearchOrCreateBunkatsu(int type,int* param)
{
	int found = SearchBunkatsu(type,param);
	if (found == -1)
	{
		if (m_createdBunkatsuKosuu >= m_bunkatsuWorkKosuu)
		{
			ExpandBunkatsuWork();
		}

		//create!
		found = m_createdBunkatsuKosuu;
		CreateNewBunkatsu(type,param);
	}

	return found;
}


void CEffectHahen::CreateNewBunkatsu(int type,int* param)
{
	//dummy routine

	BOOL errorFlag = TRUE;
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (type == 1)
	{
		if (param[0] == 0)	//3角分割
		{
			int lv = param[1];
			if (lv<0) lv = 0;

			int bunkatsuY = (lv+1) * 2;
			int bunkatsuX = (bunkatsuY*4)/3;

			int vertexKosuu = (bunkatsuX+2)*(bunkatsuY+1);
			int surfaceKosuu = (bunkatsuX*2+1) * bunkatsuY;

			CreateBuffer(vertexKosuu,surfaceKosuu);
			SetTypeTable(type,4,param);
			int* vertexBuffer = GetVertexBuffer(m_createdBunkatsuKosuu);
			int* surfaceBuffer = GetSurfaceBuffer(m_createdBunkatsuKosuu);


			int blockBaseSizeX = screenSizeX / bunkatsuX;
			int blockBaseSizeY = screenSizeY / bunkatsuY;

			int rd = param[2];
			if (rd<0) rd = 0;
			if (rd>4) rd = 4;

			int rx = (blockBaseSizeX * rd) / 10;
			int modX = rx*2+1;
			int ry = (blockBaseSizeY * rd) / 10;
			int modY = ry*2+1;

			vertexBuffer[0] = vertexKosuu;
			int n = 0;
			for (int j=0;j<=bunkatsuY;j++)
			{
				for (int i=0;i<=bunkatsuX+1;i++)
				{
					int x = (screenSizeX * i) / bunkatsuX;
					int y = (screenSizeY * j) / bunkatsuY;

					if (j & 1)
					{
						x -= blockBaseSizeX/2;
					}

					if (rd > 0)
					{
						x += (rand() % modX);
						x -= rx;
						y += (rand() % modY);
						y -= ry;
					}

					if (j == 0)
					{
						y = 0;
					}
					if (j == bunkatsuY)
					{
						y = screenSizeY-1;
					}
					if (i == 0)
					{
						x = 0;
					}
					if ((j & 1) == 0)
					{
						if (i >= bunkatsuX)
						{
							x = screenSizeX-1;
						}
					}
					else
					{
						if (i == (bunkatsuX+1))
						{
							x = screenSizeX-1;
						}
					}


					vertexBuffer[1+n*2+0] = x;
					vertexBuffer[1+n*2+1] = y;

					n++;
				}
			}
		

			surfaceBuffer[0] = surfaceKosuu;

			n = 0;
			for (int j=0;j<bunkatsuY;j+=2)
			{
				int upN = (bunkatsuX+2)*j;
				int centerN = (bunkatsuX + 2)*(j+1);
				int downN = (bunkatsuX + 2)*(j+2);

				for (int i=0;i<bunkatsuX;i++)
				{
					surfaceBuffer[1+n*16+0] = 3;
					int y1 = vertexBuffer[1+(upN+i)*2+1];
					int y2 = vertexBuffer[1+(upN+i+1)*2+1];

					if (y1<y2)
					{
						surfaceBuffer[1+n*16+1] = (upN+i);
						surfaceBuffer[1+n*16+2] = (centerN+i+1);
						surfaceBuffer[1+n*16+3] = (upN+i+1);
					}
					else
					{
						surfaceBuffer[1+n*16+1] = (upN+i+1);
						surfaceBuffer[1+n*16+2] = (upN+i);
						surfaceBuffer[1+n*16+3] = (centerN+i+1);
					}
					n++;

					surfaceBuffer[1+n*16+0] = 3;
					surfaceBuffer[1+n*16+1] = (upN+i);
					surfaceBuffer[1+n*16+2] = (centerN+i);
					surfaceBuffer[1+n*16+3] = (centerN+i+1);
					n++;
				}
				//last one
				surfaceBuffer[1+n*16+0] = 3;
				surfaceBuffer[1+n*16+1] = (upN+bunkatsuX);
				surfaceBuffer[1+n*16+2] = (centerN+bunkatsuX);
				surfaceBuffer[1+n*16+3] = (centerN+bunkatsuX+1);
				n++;

				for (int i=0;i<bunkatsuX;i++)
				{
					surfaceBuffer[1+n*16+0] = 3;
					int y1 = vertexBuffer[1+(centerN+i)*2+1];
					int y2 = vertexBuffer[1+(centerN+i+1)*2+1];

					if (y1<y2)
					{
						surfaceBuffer[1+n*16+1] = (centerN+i);
						surfaceBuffer[1+n*16+2] = (downN+i);
						surfaceBuffer[1+n*16+3] = (centerN+i+1);
					}
					else
					{
						surfaceBuffer[1+n*16+1] = (centerN+i+1);
						surfaceBuffer[1+n*16+2] = (centerN+i);
						surfaceBuffer[1+n*16+3] = (downN+i);
					}
					n++;

					surfaceBuffer[1+n*16+0] = 3;
					surfaceBuffer[1+n*16+1] = (centerN+i+1);
					surfaceBuffer[1+n*16+2] = (downN+i);
					surfaceBuffer[1+n*16+3] = (downN+i+1);
					n++;
				}

				if (1)
				{
					int y1 = vertexBuffer[1+(centerN+bunkatsuX)*2+1];
					int y2 = vertexBuffer[1+(centerN+bunkatsuX+1)*2+1];

					surfaceBuffer[1+n*16+0] = 3;
					if (y1<y2)
					{
						surfaceBuffer[1+n*16+1] = (centerN+bunkatsuX);
						surfaceBuffer[1+n*16+2] = (downN+bunkatsuX);
						surfaceBuffer[1+n*16+3] = (centerN+bunkatsuX+1);
					}
					else
					{
						surfaceBuffer[1+n*16+1] = (centerN+bunkatsuX+1);
						surfaceBuffer[1+n*16+2] = (centerN+bunkatsuX);
						surfaceBuffer[1+n*16+3] = (downN+bunkatsuX);
					}

					n++;

				}

			}

			errorFlag = FALSE;
		}
		else if (param[0] == 1)	//4角分割
		{
			int lv = param[1];
			if (lv<0) lv = 0;

			int bunkatsuY = (lv+1) * 2;
			int bunkatsuX = (bunkatsuY*4)/3;

			int vertexKosuu = (bunkatsuX+1)*(bunkatsuY+1);
			int surfaceKosuu = bunkatsuX * bunkatsuY;

			CreateBuffer(vertexKosuu,surfaceKosuu);
			SetTypeTable(type,4,param);
			int* vertexBuffer = GetVertexBuffer(m_createdBunkatsuKosuu);
			int* surfaceBuffer = GetSurfaceBuffer(m_createdBunkatsuKosuu);


			int blockBaseSizeX = screenSizeX / bunkatsuX;
			int blockBaseSizeY = screenSizeY / bunkatsuY;

			int rd = param[2];
			if (rd<0) rd = 0;
			if (rd>4) rd = 4;

			int rx = (blockBaseSizeX * rd) / 10;
			int modX = rx*2+1;
			int ry = (blockBaseSizeY * rd) / 10;
			int modY = ry*2+1;



			vertexBuffer[0] = vertexKosuu;
			int n = 0;
			for (int j=0;j<=bunkatsuY;j++)
			{
				for (int i=0;i<=bunkatsuX;i++)
				{
					int x = (screenSizeX * i) / bunkatsuX;
					int y = (screenSizeY * j) / bunkatsuY;

					if (rd > 0)
					{
						x += (rand() % modX);
						x -= rx;
						y += (rand() % modY);
						y -= ry;
					}

					if (j == 0)
					{
						y = 0;
					}
					if (j == bunkatsuY)
					{
						y = screenSizeY-1;
					}
					if (i == 0)
					{
						x = 0;
					}
					if (i == bunkatsuX)
					{
						x = screenSizeX-1;
					}


					vertexBuffer[1+n*2+0] = x;
					vertexBuffer[1+n*2+1] = y;

					n++;
				}
			}

			surfaceBuffer[0] = surfaceKosuu;

			n=0;
			for (int j=0;j<bunkatsuY;j++)
			{
				int upN = (bunkatsuX+1)*j;
				int downN = (bunkatsuX + 1)*(j+1);

				for (int i=0;i<bunkatsuX;i++)
				{
					surfaceBuffer[1+n*16+0] = 4;
					int y1 = vertexBuffer[1+(upN+i)*2+1];
					int y2 = vertexBuffer[1+(upN+i+1)*2+1];
					if (y1<y2)
					{
						surfaceBuffer[1+n*16+1] = (upN+i);
						surfaceBuffer[1+n*16+2] = (downN+i);
						surfaceBuffer[1+n*16+3] = (downN+i+1);
						surfaceBuffer[1+n*16+4] = (upN+i+1);
					}
					else
					{
						surfaceBuffer[1+n*16+1] = (upN+i+1);
						surfaceBuffer[1+n*16+2] = (upN+i);
						surfaceBuffer[1+n*16+3] = (downN+i);
						surfaceBuffer[1+n*16+4] = (downN+i+1);
					}

					n++;
				}
			}
			errorFlag = FALSE;

		}
		else if (param[0] == 2)	//レンガ積み
		{
			int lv = param[1];
			if (lv<0) lv = 0;

			int bunkatsuY = (lv+1) * 2;
			int bunkatsuX = (bunkatsuY*4)/3;

			int vertexKosuu = (bunkatsuX+2)*bunkatsuY*2;
			int surfaceKosuu = (bunkatsuX*2+1) * bunkatsuY / 2;

			CreateBuffer(vertexKosuu,surfaceKosuu);
			SetTypeTable(type,4,param);
			int* vertexBuffer = GetVertexBuffer(m_createdBunkatsuKosuu);
			int* surfaceBuffer = GetSurfaceBuffer(m_createdBunkatsuKosuu);


			int blockBaseSizeX = screenSizeX / bunkatsuX;
			int blockBaseSizeY = screenSizeY / bunkatsuY;

			int rd = param[2];
			if (rd<0) rd = 0;
			if (rd>4) rd = 4;

			int rx = (blockBaseSizeX * rd) / 10 / 2;
			int modX = rx*2+1;
			int ry = (blockBaseSizeY * rd) / 10;
			int modY = ry*2+1;



			int yUp = 0;
			int yDown = 0;
			int n = 0;

			vertexBuffer[0] = vertexKosuu;

			for (int j=0;j<bunkatsuY;j++)
			{
				yUp = yDown;
				yDown = (j+1)*blockBaseSizeY;


				if (rd > 0)
				{
					yDown += (rand() % modY);
					yDown -= ry;
				}


				if (j == (bunkatsuY-1))
				{
					yDown = screenSizeY - 1;
				}


				for (int i=0;i<=bunkatsuX+1;i++)
				{
					int x = i * blockBaseSizeX;
					if (j & 1)
					{
						x -= blockBaseSizeX / 2;
					}

					if (rd > 0)
					{
						x += (rand() % modX);
						x -= rx;
					}

					if (i == 0) x = 0;
					if ((j & 1) == 0)
					{
						if (i >= bunkatsuX)
						{
							x = screenSizeX - 1;
						}
					}
					else
					{
						if (i == (bunkatsuX + 1))
						{
							x = screenSizeX - 1;
						}
					}

					vertexBuffer[1+n*2+0] = x;
					vertexBuffer[1+n*2+1] = yUp;
					n++;
					vertexBuffer[1+n*2+0] = x;
					vertexBuffer[1+n*2+1] = yDown;
					n++;

				}

			}


			surfaceBuffer[0] = surfaceKosuu;
			n = 0;
			for (int j=0;j<bunkatsuY;j++)
			{
				int loop = bunkatsuX + (j & 1);
				for (int i=0;i<loop;i++)
				{
					surfaceBuffer[1+n*16+0] = 4;

					surfaceBuffer[1+n*16+1] = (j*(bunkatsuX+2)+i)*2+0;
					surfaceBuffer[1+n*16+2] = (j*(bunkatsuX+2)+i)*2+1;
					surfaceBuffer[1+n*16+3] = (j*(bunkatsuX+2)+i+1)*2+1;
					surfaceBuffer[1+n*16+4] = (j*(bunkatsuX+2)+i+1)*2+0;

					n++;
				}
			}

			errorFlag = FALSE;

		}
	}
	else if (type == 2)//file
	{
		char filename[1024];
		sprintf_s(filename,sizeof(filename),"nya\\hahen%d.xtx",param[0]);
		CNameList* list = new CNameList();
		if (list->LoadFile(filename))
		{
			int kosuu = list->GetNameKosuu();
			if (kosuu > 0)
			{
				int dataFlag = atoi(list->GetName(0));

				int vertexKosuu = atoi(list->GetName(1));
				if (vertexKosuu > 0)
				{
					if (kosuu > vertexKosuu*2+1)
					{
						BOOL vOk = TRUE;

						for (int i=0;i<vertexKosuu;i++)
						{
							int x = atoi(list->GetName(2+i*2+0));
							int y = atoi(list->GetName(2+i*2+1));
							if ((x<0) || (y<0) || (x>=screenSizeX) || (y>=screenSizeY))
							{
								vOk = FALSE;
								break;
							}
						}


						int surfaceKosuu = atoi(list->GetName(2+vertexKosuu*2));
						if (vOk && (surfaceKosuu > 0))
						{
							//check
							int n = 2+vertexKosuu*2+1;
							int foundSurfaceKosuu = 0;

							while (n<kosuu)
							{
								int choten = atoi(list->GetName(n));
								if ((choten < 3) || (choten > 15)) break;
								if ((n+choten+1) > kosuu) break;

								BOOL bad = FALSE;
								for (int i=0;i<choten;i++)
								{
									int p = atoi(list->GetName(n+1+i));
									if ((p<0) || (p>=vertexKosuu))
									{
										bad = TRUE;
										break;
									}
								}
								if (bad) break;

								foundSurfaceKosuu++;
								if (foundSurfaceKosuu > surfaceKosuu) break;

								n++;
								n += choten;
							}

							if (foundSurfaceKosuu == surfaceKosuu)
							{
								errorFlag = FALSE;

								CreateBuffer(vertexKosuu,surfaceKosuu);
								SetTypeTable(type,4,param);
								int* vertexBuffer = GetVertexBuffer(m_createdBunkatsuKosuu);
								int* surfaceBuffer = GetSurfaceBuffer(m_createdBunkatsuKosuu);

								vertexBuffer[0] = vertexKosuu;
								for (int i=0;i<vertexKosuu;i++)
								{
									vertexBuffer[1+i*2+0] = atoi(list->GetName(2+i*2+0));
									vertexBuffer[1+i*2+1] = atoi(list->GetName(2+i*2+1));
								}

								surfaceBuffer[0] = surfaceKosuu;
								int n = 2+vertexKosuu*2+1;
								for (int i=0;i<surfaceKosuu;i++)
								{
									int choten = atoi(list->GetName(n));
									surfaceBuffer[1+i*16+0] = choten;
									for (int k=0;k<choten;k++)
									{
										surfaceBuffer[1+i*16+1+k] = atoi(list->GetName(n+1+k));
									}

									n++;
									n += choten;
								}

							}
						}
					}
				}
			}



			if (errorFlag)
			{
#if defined _DEBUG
			OutputDebugString("\n分割File Format Error:");
			OutputDebugString(filename);
#else
			MessageBox(NULL,filename,"分割File Format Error",MB_OK | MB_ICONEXCLAMATION);
#endif
			}

			delete list;
		}
		else
		{
#if defined _DEBUG
			OutputDebugString("\n分割File Not Found:");
			OutputDebugString(filename);
#else
			MessageBox(NULL,filename,"分割File Not Found",MB_OK | MB_ICONEXCLAMATION);
#endif
		}
	}




	if (errorFlag)
	{
		int vertexKosuu = 66;
		int surfaceKosuu = 32;
		CreateBuffer(vertexKosuu,surfaceKosuu);
		SetTypeTable(type,4,param);

		int* dummyVertexSrc = GetVertexBuffer(0);
		int* dummyVertexDst = GetVertexBuffer(m_createdBunkatsuKosuu);
		for (int i=0;i<vertexKosuu*2+1;i++)
		{
			dummyVertexDst[i] = dummyVertexSrc[i];
		}

		int* dummySurfaceSrc = GetSurfaceBuffer(0);
		int* dummySurfaceDst = GetSurfaceBuffer(m_createdBunkatsuKosuu);
		for (int i=0;i<surfaceKosuu*16+1;i++)
		{
			dummySurfaceDst[i] = dummySurfaceSrc[i];
		}
	}




	OutputDebugString("\n\nCreate New Bunkatus!!\n");






	m_createdBunkatsuKosuu++;
}

void CEffectHahen::SetTypeTable(int type,int paraKosuu,int* lpParam)
{
	m_bunkatsuTypeTable[m_createdBunkatsuKosuu*16+0] = type;
	for (int i=0;i<4;i++)
	{
		if ((i<paraKosuu) && (lpParam != NULL))
		{
			m_bunkatsuTypeTable[m_createdBunkatsuKosuu*16+1+i] = lpParam[i];
		}
		else
		{
			m_bunkatsuTypeTable[m_createdBunkatsuKosuu*16+1+i] = 0;
		}
	}
}

int CEffectHahen::SearchBunkatsu(int type,int* lpParam)
{
	for (int i=0;i<m_createdBunkatsuKosuu;i++)
	{
		if (type == m_bunkatsuTypeTable[i*16])
		{
			BOOL ok = TRUE;
			for (int k=0;k<4;k++)
			{
				if (lpParam[k] != m_bunkatsuTypeTable[i*16+1+k])
				{
					ok = FALSE;
					break;
				}
			}
			if (ok)
			{
				return i;
			}
		}
	}
	return -1;
}


BOOL CEffectHahen::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}

/*_*/
