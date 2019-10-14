//
// effectsimplewipeHahen.cpp
//

#include <windows.h>
#include <Math.h>



#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeHahen.h"

#include "allSimpleWipe.h"


int CEffectSimpleWipeHahen::m_vertex0[]=
{
	0,0, 90,0, 215,0, 255,0, 421,0, 511,0, 639,0, 0,70, 166,65, 188,33,
	251,50, 320,102, 390,72, 494,56, 483,86, 460,58, 639,87, 0,136, 26,121, 123,175,
	188,146, 288,169, 480,177, 576,155, 639,197, 0,188,80,242, 109,249, 180,278, 266,272,
	297,224, 356,265, 444,235, 538,286,639,249, 0,259, 0,309, 40,343,114,338, 274,330,
	393,321, 483,347, 547,331, 0,385, 91,411, 208,402, 315,381, 425,379, 372,408, 493,435,
	553,377, 639,429, 0,479, 22,479, 47,450, 96,456, 121,445,93,479, 215,479, 325,466,
	309,479, 414,479, 453,479, 536,479, 550,479, 639,479,
};

int CEffectSimpleWipeHahen::m_vertex[]=
{
	0,0, 90,0, 215,0, 255,0, 421,0, 511,0, 639,0, 0,70, 166,65, 188,33,
	251,50, 320,102, 390,72, 494,56, 483,86, 460,58, 639,87, 0,136, 26,121, 123,175,
	188,146, 288,169, 480,177, 576,155, 639,197, 0,188,80,242, 109,249, 180,278, 266,272,
	297,224, 356,265, 444,235, 538,286,639,249, 0,259, 0,309, 40,343,114,338, 274,330,
	393,321, 483,347, 547,331, 0,385, 91,411, 208,402, 315,381, 425,379, 372,408, 493,435,
	553,377, 639,429, 0,479, 22,479, 47,450, 96,456, 121,445,93,479, 215,479, 325,466,
	309,479, 414,479, 453,479, 536,479, 550,479, 639,479,
};


int CEffectSimpleWipeHahen::m_surface[][1+15]=
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


CEffectSimpleWipeHahen::CEffectSimpleWipeHahen(CAllSimpleWipe* allWipe,int houkou) :CEffectSimpleWipeCommon(allWipe)
{
	SetEffectHoukou(houkou);

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	m_poliKosuu = 32;
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

//////////////

//	int k = 14;


	m_para[0] = 20;	//frame
	m_para[1] = 100;	//v
	m_para[2] = 100;	//g
	m_para[3] = screenSizeX / 2;	//x
	m_para[4] = screenSizeY / 2;	//y
	m_para[5] = 30;	//rndv
	m_para[6] = 15;	//rndth
	m_para[7] = 15;	//vx
	m_para[8] = 15;	//vy
	m_para[9] = 0;	//masatu
	m_para[10] = 20;	//初期wait%
	m_para[11] = 10;	//初期ひび%

	m_poliKosuu = 32;

	int centerX = m_para[3];
	int centerY = m_para[4];

	for (int i=0;i<m_poliKosuu;i++)
	{
		int k = m_surface[i][0];
		int x = 0;
		int y = 0;
		for (int j=0;j<k;j++)
		{
			int p = m_surface[i][1+j];
			x += m_vertex[p*2];
			y += m_vertex[p*2+1];
		}
		x /= k;
		y /= k;

		m_centerXY[i*2] = x;
		m_centerXY[i*2+1] = y;

		m_hahen[i].x = 0.0f;
		m_hahen[i].y = 0.0f;

		double r2 = (y-centerY)*(y-centerY) + (x-centerX)*(x-centerX);
		double r = sqrt(r2);
		if (r<1.0) r = 1.0;

		double v = (double)m_para[1];
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
		m_hahen[i].kasokuY = ((float)m_para[2]) * 0.01f;

	}








}

CEffectSimpleWipeHahen::~CEffectSimpleWipeHahen()
{
	End();
}

void CEffectSimpleWipeHahen::End(void)
{
}



void CEffectSimpleWipeHahen::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count, int countMax,POINT* lpStartPoint, POINT* lpEndPoint)
{
	if (ClipAndCheck(lpPicStart,lpPicEnd,count,countMax,lpStartPoint,lpEndPoint) == FALSE) return;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int c = m_count;
	int dv = m_countMax;
	if (dv<1) dv = 1;

	if (m_effectHoukou == 1)
	{
		SwapPic();
		c = m_countMax - c;
	}

	int* shapeWork = m_allSimpleWipe->GetShapeWork();
	if (shapeWork == NULL) return;


	int limit = (dv * m_para[10]) / 100;

	if (c<=limit)
	{
//		float ml = (float)(c+1);
//		ml /= (float)(lp->para[10]);
		float ml = float(m_para[11]);
		ml *= 0.001f;
		ml *= c;

		for (int i=0;i<m_poliKosuu;i++)
		{
			m_hahen[i].x = m_hahen[i].speedX * ml;
			m_hahen[i].y = m_hahen[i].speedY * ml;
//			m_hahen[i].speedX += m_hahen[i].kasokuX;
//			m_hahen[i].speedY += m_hahen[i].kasokuY;
		}
	}
	else
	{
		float ml = float(m_para[11]);
		ml *= 0.001f;
		ml *= limit;

		float dvf = (float)(dv-limit);
		if (dvf <= 0.0f) dvf = 1.0f;

		double ml2 = (double)(screenSizeX*screenSizeX + screenSizeY*screenSizeY);
		float ml3 = (float)(sqrt(ml2));

		ml3 /= 30.0;
		ml3 *= 0.3f;
		
		for (int i=0;i<m_poliKosuu;i++)
		{
			float dx = m_hahen[i].speedX * ml;
			float dy = m_hahen[i].speedY * ml;

			m_hahen[i].x = dx + m_hahen[i].speedX * (c-limit) * ml3 / dvf;
			m_hahen[i].y = dy + m_hahen[i].speedY * (c-limit) * ml3 / dvf;
//			m_hahen[i].speedX += m_hahen[i].kasokuX;
//			m_hahen[i].speedY += m_hahen[i].kasokuY;
		}
	}







//////////////////////



	//サイズ、ポイント、カウント、からポインタをもとめ、範囲内なら、描画OK

//	int startSrcPitch = startPicSizeX * sizeof(int);
//	int endSrcPitch = endPicSizeX * sizeof(int);

	m_endPic->Blt(0,0,m_endPoint.x,m_endPoint.y,screenSizeX,screenSizeY,FALSE);


	int* startPtr = (int*)(m_startPic->GetBuffer());
	startPtr += m_startPoint.x;
	startPtr += m_startPoint.x * m_startPicSize.cx;
//	endPtr += endPointX;
//	endPtr += endPointY * endPicSizeX;


//	int picSizeX = rcStart.right;
	int picSizeX = m_startPicSize.cx;

	int zahyo[16*2];
	for (int i=0;i<m_poliKosuu;i++)
	{
		int n = m_surface[i][0];
		int n0 = m_surface[i][1];
		int minX = m_vertex[n0*2];
		int maxX = minX;
		int minY = m_vertex[n0*2+1];
		int maxY = minY;

		int putX = (int)(m_hahen[i].x + 0.5f);
		int putY = (int)(m_hahen[i].y + 0.5f);

		zahyo[0] = minX;
		zahyo[1] = minY;
		zahyo[n*2] = minX;
		zahyo[n*2+1] = minY;

		for (int k=1;k<n;k++)
		{
			int p = m_surface[i][1+k];
			int x = m_vertex[p*2];
			int y = m_vertex[p*2+1];

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
		
		PrintNormalPoligon(startPtr, picSizeX, n, putX, putY, maxY - minY + 1, zahyo);
	}

	return;

}



void CEffectSimpleWipeHahen::PrintNormalPoligon(int* lpPicSrc, int picSizeX, int n, int putX, int putY, int sizeY, int* lpZahyo)
{
//	int work[MAXSCREENSIZEY*2];
//	int* work = CEffectSimpleWipe::m_shapeWork;
	int* work = m_allSimpleWipe->GetShapeWork();


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

	if (loopY<=0) return;

	int deltaX = putX * 4;

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

//		emms
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
#endif

}






