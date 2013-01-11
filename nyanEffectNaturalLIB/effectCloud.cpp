//
// effectCloud.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectCloud.h"


CEffectCloud::CEffectCloud(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	m_x = 0;
	m_y = 0;
#if defined _TINYAN3DLIB_
	SetPercentKosuu(1);
	SetTextureKosuu(1);
	Create("Cloud");

	m_hTechniqueCloud = CMyDirect3D::GetShaderTechnique(SHADER_EFFECT_EFFECT,"CloudPhase2");
	if (m_hTechniqueCloud == NULL)
	{
		OutputDebugString("\n\n\nError Create Cloud Phase2 \n\n\n\n");
	}
#endif

}

CEffectCloud::~CEffectCloud()
{
	End();
}

void CEffectCloud::End(void)
{
}


BOOL CEffectCloud::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	EFFECT* lp = (EFFECT*)lpEffect;

	int para[16];
	int k = paraKosuu;
	if (k>14) k = 14;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}



	if (paraKosuu<1) para[0] = 9999;	//dummy

	if (paraKosuu<2) para[1] = 200;	//sizeY
	if (paraKosuu<3) para[2] = 0;	//speedx
	if (paraKosuu<4) para[3] = 50;	//speedy

	if (paraKosuu<5) para[4] = 200;	//high
	if (paraKosuu<6) para[5] = 100;	//near
	if (paraKosuu<7) para[6] = 500;	//far
	if (paraKosuu<8) para[7] = 100;	//ps
	if (paraKosuu<9) para[8] = 0;	//透過

	if (paraKosuu<10) para[9] = 0;	//色加減算フラグ
	

	if (paraKosuu<11) para[10] = 0;	//R
	if (paraKosuu<12) para[11] = para[10];	//G
	if (paraKosuu<13) para[12] = para[11];	//B

	if (paraKosuu<14) para[13] = 0;	//開始Y

	if (para[1]<1) para[1] = 1;
	if (para[1]>screenSizeY) para[1] = screenSizeY;

	if (para[13]<0) para[13] = 0;
	if (para[13]>=screenSizeY) para[13] = screenSizeY-1;
	
	if (para[5]<1) para[5] = 1;
	if (para[6]<=para[5]) para[6] = para[5]+1;
	if (para[7]<1) para[7] = 1;

	if (para[13]>=para[1]) para[13] = para[1]-1;
	if (para[13]<0) para[13] = 0;


	lp->flag = TRUE;
	lp->command = EFFECT_CLOUD;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<14;i++)
	{
		lp->para[i] = para[i];
	}
	lp->para[15] = 0;//oldcount

	m_x = 0;
	m_y = 0;

	return TRUE;
}


BOOL CEffectCloud::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectCloud::BeginPrint(LPVOID para,int layer)
{

}

void CEffectCloud::Init(LPVOID para,int layer)
{
}

void CEffectCloud::Calcu(LPVOID lpEffect,int layer)
{
	/*
	EFFECT* lp = (EFFECT*)lpEffect;
	int c = lp->count;
	int countMax = lp->countMax;

//	CPicture* lpPic = m_effect->GetPicture(layer);
	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	int* src = (int*)(lpPic->GetBuffer());
	if (src == NULL) return;

	int speedX = lp->para[2];
	int speedY = lp->para[3];

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();
	RECT rc;
	lpPic->GetPicSize(&rc);

	int picSizeX = rc.right;
	int picSizeY = rc.bottom;

	if ((picSizeX<=0) || (picSizeY<=0)) return;

	m_x += speedX;
	m_y += speedY;

	int maxX = picSizeX * 100;
	int maxY = picSizeY * 100;

	if (m_x<0)
	{
		m_x *= -1;
		m_x %= maxX;
		m_x *= -1;
		m_x += maxX;
	}
	m_x %= maxX;

	
	if (m_y<0)
	{
		m_y *= -1;
		m_y %= maxY;
		m_y *= -1;
		m_y += maxY;
	}
	m_y %= maxY;
	*/
}	

#if defined _TINYAN3DLIB_
void CEffectCloud::Print(LPVOID lpEffect,int layer)
{
	int shader = 0;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


//	int work[MAXSCREENSIZEY*5];	//srcDorY(int), startX(WORD.WORD), deltaX(WORD.WORD), 加算,減算
//	int* work = CEffectSimpleWipe::m_shapeWork;
	int* work = m_allEffect->GetTempWork();

//	ZeroMemory(work,sizeof(work));	//本当はいらないはず。バグったときの用心
	int* workPtr = work;

	EFFECT* lp = (EFFECT*)lpEffect;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	int* src = (int*)(lpPic->GetBuffer());
	if (src == NULL) return;

	RECT rc;
	lpPic->GetPicSize(&rc);

	int picSizeX = rc.right;
	int picSizeY = rc.bottom;

	if (lp->count > 0)
	{
		int speedX = lp->para[2];
		int speedY = lp->para[3];


		if ((picSizeX>0) || (picSizeY>0))
		{
			m_x -= speedX;
			m_y -= speedY;

//			int maxX = picSizeX * 100;
//			int maxY = picSizeY * 100;
			int maxX = picSizeX * lp->para[7];
			int maxY = picSizeY * lp->para[7];

			if (m_x<0)
			{
				m_x *= -1;
				m_x %= maxX;
				m_x *= -1;
				m_x += maxX;
			}
			m_x %= maxX;

			
			if (m_y<0)
			{
				m_y *= -1;
				m_y %= maxY;
				m_y *= -1;
				m_y += maxY;
			}
			m_y %= maxY;
		}

		lp->count = 0;
	}

	int md = lp->para[8];

	//CPicture* lpPic = m_effect->GetPicture(layer);


	char* mask = NULL;
	if (md == 2)
	{
		if (lpPic->CheckMaskExist())
		{
			mask = lpPic->GetMaskPic();
		}
		else
		{
			md = 1;
			md = 0;	//error
		}
	}



	int loopY = lp->para[1];
	if (loopY<1) return;
	if (loopY>screenSizeY) loopY = screenSizeY;


	int loopX = screenSizeX;

	int nearInt = lp->para[5];
	int farInt = lp->para[6];

	float nearDist = (float)(lp->para[5]);
	float farDist = (float)(lp->para[6]);

//	float fScreenWidth = (float)screenSizeX;
//	float fScreen
//	D3DXMatrixPerspectiveLH(&pOut,fScreenWidth,fScreenHeight,nearDist,farDist);



//	float nearWidth = (float)(lp->para[7]);
//	nearWidth *= (float)screenSizeX;
//	float farWidth = farDist / nearDist * nearWidth;


//	float yStart = (float)(lp->para[13]);
//	float yEnd = (float)(lp->para[1] + lp->para[13]);
	float yStart = 0.0f;
	float yEnd = (float)(lp->para[1]);


	float constC = (float)(lp->para[1]);
	constC *= -1.0f;
	constC *= farDist;
	constC *= nearDist;
	constC /= (farDist - nearDist);

	float constD = (farDist*yEnd-nearDist*yStart)/(farDist-nearDist);


//	int i;




	CMyTexture* lpTexture = (CMyTexture*)(lpPic->GetTexture());
	SetTexture(lpTexture->GetTexture());

//	CMyDirect3D::SetWorkV(work,screenSizeY);
//	SetTexture(CMyDirect3D::GetVTexture(),1);


	float addPercent = 0.0f;
	if (md == 0) addPercent = 1.0f;

	SetPercent(addPercent);

	if (CheckEffectError()) return;
	LPD3DXEFFECT effect = m_d3dxEffect;
	if (effect == NULL) return;
	SetAllColor();
	SetAllPercent();
	SetAllConst();
	SetAllTexture();


	if (m_hTechnique[shader] == NULL)
	{
		OutputDebugString("[no tec]");
	}

	HRESULT hr = effect->SetTechnique(m_hTechnique[shader]);
	if (FAILED(hr))
	{
///		DXTRACE_ERR("settech",hr);
	}

	UINT passKosuu0 = 0;
	hr = effect->Begin(&passKosuu0,0);
	int passKosuu = passKosuu0;


	int blockSizeY = (picSizeY * lp->para[7]) / 100;
	if (blockSizeY<1) blockSizeY = 1;
	int blockSizeX = (picSizeX * lp->para[7]) / 100;
	if (blockSizeX<1) blockSizeX = 1;

	int blockStartY = -1;
	int blockEndY = (farInt - nearInt ) / blockSizeY + 2;


	for (int i=0;i<passKosuu;i++)
	{
		effect->BeginPass(i);

//		int blockStartY = -1;
//		int blockEndY = 4;

		for (int blockY=blockStartY;blockY<=blockEndY;blockY++)
//		for (int blockY=-1;blockY<1;blockY++)
		{
//			int z1 = blockY * picSizeY + m_y / 100;
//			int z2 = (blockY+1) * picSizeY + m_y / 100;
			int z1 = blockY * blockSizeY + m_y / 100;
			int z2 = (blockY+1) * blockSizeY + m_y / 100;

			if (z1>=farDist) continue;
			if (z2<nearDist) continue;

			int srcY1 = 0;
			int srcY2 = picSizeY;

			int z11 = z1;

			if (z1<nearDist)
			{
				srcY1 = (picSizeY * ((int)nearDist - z1)) / blockSizeY;
				z1 = (int)nearDist;
			}

			if (z2 > farDist)
			{
				srcY2 *= ((int)farDist - z11);
				srcY2 /= blockSizeY;
				z2 = (int)farDist;
			}

			int yy1 = (int)((constC / ((float)z1)) + constD + 0.5f);
			int yy2 = (int)((constC / ((float)z2)) + constD + 0.5f);
	//OutputDebugString(".");


			if (yy2<=yy1) continue;

			float z1f = (float)z1;
			z1f -= nearDist;
			z1f *= farDist;
			z1f /= (float)z1;
			z1f /= (farDist - nearDist);

			float z2f = (float)z2;
			z2f -= nearDist;
			z2f *= farDist;
			z2f /= (float)z2;
			z2f /= (farDist - nearDist);
//			static int a = 0;
//			a++;
//
//			if (a == 32)
//			{
//				char mes[256];
//				wsprintf(mes,"[z1=%d z2=%d]\n",(int)(z1f*10000),(int)(z2f*10000));
//				OutputDebugString(mes);
//			}


			int pp = blockSizeX * nearInt;
			pp /= z2;
			if (pp<1) pp = 1;
			int blockKosuu = screenSizeX / pp;

			int blockStartX = -blockKosuu / 2 - 2;
			int blockEndX = blockKosuu / 2 + 2;

			for (int blockX=blockStartX;blockX<=blockEndX;blockX++)
//			for (int blockX=0;blockX<1;blockX++)
			{
//				int xL = blockX * picSizeX + m_x / 100 - screenSizeX / 2;
//				int xR = (blockX+1) * picSizeX + m_x / 100 - screenSizeX / 2;
				int xL = blockX * blockSizeX + m_x / 100 - screenSizeX / 2;
				int xR = (blockX+1) * blockSizeX + m_x / 100 - screenSizeX / 2;

				int x1L = (int)(((float)xL)*nearDist / (float)z1 + 0.5f);
				int x1R = (int)(((float)xR)*nearDist / (float)z1 + 0.5f);

				int x2L = (int)(((float)xL)*nearDist / (float)z2 + 0.5f);
				int x2R = (int)(((float)xR)*nearDist / (float)z2 + 0.5f);

				x1L += screenSizeX/2;
				x1R += screenSizeX/2;
				x2L += screenSizeX/2;
				x2R += screenSizeX/2;


				if ((x1L<screenSizeX) || (x2L<screenSizeX) || (x1R>=0) || (x2R>=0))
				{

					POINT dstPoint[4];
					dstPoint[0].x = x1L;
					dstPoint[0].y = yy1;
					dstPoint[1].x = x2L;
					dstPoint[1].y = yy2;
					dstPoint[2].x = x2R;
					dstPoint[2].y = yy2;
					dstPoint[3].x = x1R;
					dstPoint[3].y = yy1;

					POINT srcPoint[4];
					srcPoint[0].x = 0;
					srcPoint[0].y = srcY1;
					srcPoint[1].x = 0;
					srcPoint[1].y = srcY2;
					srcPoint[2].x = picSizeX;
					srcPoint[2].y = srcY2;
					srcPoint[3].x = picSizeX;
					srcPoint[3].y = srcY1;

					float zPoint[8];
					zPoint[0] = (float)z1;
					zPoint[1] = z1f;
					zPoint[2] = (float)z2;
					zPoint[3] = z2f;
					zPoint[4] = (float)z2;
					zPoint[5] = z2f;
					zPoint[6] = (float)z1;
					zPoint[7] = z1f;

		//OutputDebugString("*");
					//PrintPolygon(dstPoint,srcPoint,4);
					CMyDirect3D::DrawPolygonZ(dstPoint,srcPoint,zPoint,4);
				}

			}
		}

		effect->EndPass();
	}

	effect->End();




	if ((md == 0) || (md == 1))
	{
		if (lp->para[9])
		{
			int colorStartY = lp->para[13];
			int gradSizeY = lp->para[1] - colorStartY;
			if (gradSizeY<=0) return;


			int colR = lp->para[10];
			int colG = lp->para[11];
			int colB = lp->para[12];

			colR /= 2;
			colG /= 2;
			colB /= 2;
			colR += 128;
			colG += 128;
			colB += 128;
			float r = (float)colR;
			float g = (float)colG;
			float b = (float)colB;
			r /= 255.0f;
			g /= 255.0f;
			b /= 255.0f;

			float vertexColor[4*3];
			vertexColor[0] = 0.5f;
			vertexColor[1] = 0.5f;
			vertexColor[2] = 0.5f;

			vertexColor[3] = r;
			vertexColor[4] = g;
			vertexColor[5] = b;

			vertexColor[6] = 0.5f;
			vertexColor[7] = 0.5f;
			vertexColor[8] = 0.5f;

			vertexColor[9] = r;
			vertexColor[10] = g;
			vertexColor[11] = b;

			


			//CMyDirect3D::CopyScreenToBuffer();
		//	CMyDirect3D::ExchangeScreenAndBuffer();
			POINT dmyPoint;
			dmyPoint.x = 0;
			dmyPoint.y = 0;
			SIZE dmySize;
			dmySize.cx = screenSizeX;
			dmySize.cy = screenSizeY;

			CMyDirect3D::GetScreenToBuffer(dmyPoint,dmySize);

			SetTexture(CMyDirect3D::GetBufferTexture());
			SetAllTexture();//かずおなじ

			HRESULT hr = effect->SetTechnique(m_hTechniqueCloud);
			if (FAILED(hr))
			{
				OutputDebugString("\n\nError:Cloud2\n\n");
//				DXTRACE_ERR("settech CLOUD",hr);
			}

			passKosuu0 = 0;
			hr = effect->Begin(&passKosuu0,0);
			passKosuu = passKosuu0;

			for (int i=0;i<passKosuu;i++)
			{
				effect->BeginPass(i);


				POINT dstPoint;
				dstPoint.x = 0;
				dstPoint.y = colorStartY;
				SIZE dstSize;
				dstSize.cx = screenSizeX;
				dstSize.cy = gradSizeY;
				POINT srcPoint = dstPoint;
				SIZE srcSize = dstSize;

				SIZE srcPicSize;
				srcPicSize.cx = screenSizeX;
				srcPicSize.cy = screenSizeY;


				CMyDirect3D::GouraudBlt(dstPoint,dstSize,srcPoint,vertexColor);


				effect->EndPass();
			}
			effect->End();


		}
	}


	return;
}
#else


void CEffectCloud::Print(LPVOID lpEffect,int layer)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


//	int work[MAXSCREENSIZEY*5];	//srcDorY(int), startX(WORD.WORD), deltaX(WORD.WORD), 加算,減算
//	int* work = CEffectSimpleWipe::m_shapeWork;
	int* work = m_allEffect->GetTempWork();

//	ZeroMemory(work,sizeof(work));	//本当はいらないはず。バグったときの用心
	int* workPtr = work;

	EFFECT* lp = (EFFECT*)lpEffect;


	int newCount = lp->count;
	if (newCount > 0)
	{
		CPicture* lpPic = m_allEffect->GetPicture(layer);
		if (lpPic != NULL)
		{
			int* src = (int*)(lpPic->GetBuffer());
			if (src != NULL)
			{
				int speedX = lp->para[2];
				int speedY = lp->para[3];

				RECT rc;
				lpPic->GetPicSize(&rc);

				int picSizeX = rc.right;
				int picSizeY = rc.bottom;

				if ((picSizeX>0) && (picSizeY>0))
				{
					m_x += speedX;
					m_y += speedY;

					int maxX = picSizeX * 100;
					int maxY = picSizeY * 100;

					if (m_x<0)
					{
						m_x *= -1;
						m_x %= maxX;
						m_x *= -1;
						m_x += maxX;
					}
					m_x %= maxX;

					
					if (m_y<0)
					{
						m_y *= -1;
						m_y %= maxY;
						m_y *= -1;
						m_y += maxY;
					}
					m_y %= maxY;
				}
			}
		}
		lp->count = 0;
	}









	int md = lp->para[8];

	//CPicture* lpPic = m_effect->GetPicture(layer);
	CPicture* lpPic = m_allEffect->GetPicture(layer);

	if (lpPic == NULL) return;

	int* src = (int*)(lpPic->GetBuffer());
	if (src == NULL) return;

	char* mask = NULL;
	if (md != 0)
	{
		if (lpPic->CheckMaskExist())
		{
			mask = lpPic->GetMaskPic();
		}
		else
		{
			md = 1;
			md = 0;	//error
		}
	}

	RECT rc;
	lpPic->GetPicSize(&rc);

	int picSizeX = rc.right;
	int picSizeY = rc.bottom;

	int loopY = lp->para[1];
	if (loopY<1) return;
	if (loopY>screenSizeY) loopY = screenSizeY;


	int loopX = screenSizeX;


	int* dst = CMyGraphics::GetScreenBuffer();
	int lPitch = screenSizeX * sizeof(int);
	int srcLPitch = picSizeX * sizeof(int);
	int maskPitch = picSizeX * sizeof(char);


//char mes[256];
//sprintf(mes,"[%d]",lp->para[4]);
//OutputDebugString(mes);


	double h = (double)(lp->para[4]);
	double dist1 = (double)(lp->para[5]);
	double dist2 = (double)(lp->para[6]);

	double h2 = h * (dist2 - dist1) / dist2;



	double startDotPara = 100.0 / ((double)(lp->para[7]));
	double divY = (double)loopY;

	double startDotX = (double)m_x;
	double startDotY = (double)m_y;
	startDotX *= 0.01;
	startDotY *= 0.01;

	int addSubFlag = lp->para[9];

//	if (md == 2) addSubFlag = FALSE;

	int addR = lp->para[10];
	int addG = lp->para[11];
	int addB = lp->para[12];
	int subR = -addR;
	int subG = -addG;
	int subB = -addB;

	if (addR<0) addR = 0;
	if (addG<0) addG = 0;
	if (addB<0) addB = 0;

	if (subR<0) subR = 0;
	if (subG<0) subG = 0;
	if (subB<0) subB = 0;



	for (int i=0;i<loopY;i++)
	{
		double hk = (double)(i+1);
		hk *= h2;
		hk /= divY;

		double nk = h * dist1 / (h - hk);

		double dotPara = startDotPara * nk / dist1;
		double deltaDotY = (nk - dist1) * startDotPara;

		double dotY = startDotY + deltaDotY;
/*
if (i == loopY/2)
{
char mes[256];
sprintf(mes,"[h=%d h-hk=%d hk=%d nk=%d]\n",(int)(h*100),(int)(h-hk),(int)(hk*100),(int)(nk*100));
OutputDebugString(mes);
}
*/


		int iDotY = (int)dotY;
		iDotY %= picSizeY;

		work[i*5] = iDotY;


		int dotParaHigh = (int)dotPara;
		double amari = dotPara- (double)dotParaHigh;

		dotParaHigh %= picSizeX;
		int dotParaLow = (int)(amari * 65536 + 0.5);
		if (dotParaLow >= 65536) dotParaLow = 65535;


		int dxHigh = screenSizeX / 2;
		int dxLow = 0;
		dxHigh += m_x / 100;
		dxLow += ((m_x % 100)*65536)/100;
		dxHigh += (dxLow >>16) & 0xffff;
		dxHigh %= picSizeX;
		dxLow &= 0xffff;

		int ddxHigh = dotParaHigh * (screenSizeX/2);
		int ddxLow = dotParaLow * (screenSizeX / 2);
		ddxHigh += ((ddxLow>>16) & 0xffff);
		ddxHigh %= picSizeX;
		ddxLow &= 0xffff;

		ddxHigh = picSizeX - ddxHigh;
		ddxHigh %= picSizeX;
		if (ddxLow>0)
		{
			ddxHigh -= 1;
			ddxHigh += picSizeX;
			ddxHigh %= picSizeX;
			ddxLow = 65536 - ddxLow;
		}

		dxHigh += ddxHigh;
		dxLow += ddxLow;
		dxHigh += ((dxLow >> 16) & 0xffff);
		dxHigh %= picSizeX;
		dxLow &= 0xffff;


		work[i*5+1] = (dxHigh << 16) | dxLow;
		work[i*5+2] = (dotParaHigh << 16) | (dotParaLow);


		int addRGB = 0;
		int subRGB = 0;

		if (addSubFlag)
		{
			int limY = lp->para[13];

			if (i>=limY)
			{
				int cc = i - limY;
				int dv = loopY - limY;
				if (dv<1) dv = 1;
				if (cc>dv) cc = dv;
				int dv2 = dv / 2;

				int r1 = (addR * cc + dv2) / dv;
				int g1 = (addG * cc + dv2) / dv;
				int b1 = (addB * cc + dv2) / dv;

				int r2 = (subR * cc + dv2) / dv;
				int g2 = (subG * cc + dv2) / dv;
				int b2 = (subB * cc + dv2) / dv;

				addRGB = (r1<<16) | (g1<<8) | b1;
				subRGB = (r2<<16) | (g2<<8) | b2;
			}
		}

		work[i*5+3] = addRGB;
		work[i*5+4] = subRGB;
	}

	LONGLONG tmpmm7 = 0;


//	if ((md == 0) || (md == 1))
	if (md == 0)
	{
		__asm
		{
			push eax
			push ebx
			push ecx
			push edx
			push esi
			push edi


			pxor mm0,mm0
			mov eax,picSizeX
			movd mm6,eax
			pslld mm6,16
			dec eax
			movd mm5,eax
			pslld mm5,16


			mov ebx,workPtr
			mov edi,dst
			mov ecx,loopY
LOOP1:
			push ebx
			push ecx
			push edi





			mov eax,[ebx+4]
			movd mm1,eax

			mov eax,[ebx+8]
			movd mm3,eax

			mov eax,[ebx+12]
			movd mm2,eax
			mov eax,[ebx+16]
			movd mm7,eax

			punpckldq mm2,mm2
			punpckldq mm7,mm7

			mov eax,[ebx]
			mov edx,srcLPitch
			mul edx
			add eax,src
			mov ebx,eax

			mov eax,addSubFlag
			or eax,eax
			jnz ADDSUBROUTINE

			mov ecx,loopX
LOOP2:
			movq mm4,mm1
		
			psrld mm4,16
			paddd mm1,mm3

			movd esi,mm4

			movq mm4,mm1
			mov eax,[ebx+esi*4]

			pcmpgtw mm4,mm5
			mov [edi],eax

			pand mm4,mm6
			add edi,4

			psubw mm1,mm4
			
	//		mov al,[edx+ebx]
	//		or al,al
	//		jz SKIP1


	//SKIP1:
			dec ecx
			jnz LOOP2

			jmp NEXT1

ADDSUBROUTINE:

			mov ecx,loopX
			shr ecx,1
LOOP2A:
			movq mm4,mm1
			psrld mm4,16
			paddd mm1,mm3

			movd esi,mm4

			movq mm4,mm1
			mov eax,[ebx+esi*4]

			pcmpgtw mm4,mm5
			movd mm0,eax

			pand mm4,mm6
			psubw mm1,mm4



			movq mm4,mm1
			psrld mm4,16
			paddd mm1,mm3

			movd esi,mm4

			movq mm4,mm1
			mov eax,[ebx+esi*4]

			pcmpgtw mm4,mm5

			pand mm4,mm6
			psubw mm1,mm4

			movd mm4,eax
			psllq mm4,32


			por mm0,mm4

			paddusb mm0,mm2
			psubusb mm0,mm7

			movq [edi],mm0
			add edi,8

			
	//		mov al,[edx+ebx]
	//		or al,al
	//		jz SKIP1


//SKIP1:
			dec ecx
			jnz LOOP2A




NEXT1:
			pop edi
			pop ecx
			pop ebx
			add edi,lPitch
			add ebx,4*5
			dec ecx
			jnz LOOP1



			emms
			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax

		}
	}

////////////////////////////////////////////mask

	if (md != 0)
	{
		__asm
		{
			push eax
			push ebx
			push ecx
			push edx
			push esi
			push edi


			pxor mm0,mm0
			mov eax,picSizeX
			movd mm6,eax
			pslld mm6,16
			dec eax
			movd mm5,eax
			pslld mm5,16


			mov ebx,workPtr
			mov edi,dst
			mov ecx,loopY
LOOP1_TRANS:
			push ebx
			push ecx
			push edi





			mov eax,[ebx+4]
			movd mm1,eax

			mov eax,[ebx+8]
			movd mm3,eax


			mov eax,[ebx+12]
			movd mm2,eax
			mov eax,[ebx+16]
			movd mm7,eax

			punpckldq mm2,mm2
			punpckldq mm7,mm7

			movq tmpmm7,mm7


			mov eax,[ebx]
			mov edx,srcLPitch
			mul edx
			add eax,src
			xchg eax,ebx

			mov edx,[eax]
			mov eax,maskPitch
			mul edx
			add eax,mask
			mov edx,eax

			mov eax,addSubFlag
			or eax,eax
			jnz ADDSUBROUTINE_TRANS

			mov ecx,loopX
LOOP2_TRANS:
			movq mm4,mm1
			psrld mm4,16
			paddd mm1,mm3
			movd esi,mm4
			movq mm4,mm1
			pcmpgtw mm4,mm5
			pand mm4,mm6
			psubw mm1,mm4

			xor eax,eax
			mov al,[edx+esi]
			or eax,eax
			jz SKIP2B_TRANS

			//半透明加算@@@@@@@@@@@@@@@@@@@@@@
			cmp eax,255
			jz NOTRANS

			movd mm2,eax
			punpcklwd mm2,mm2
			punpckldq mm2,mm2

			neg eax
			add eax,256
			movd mm7,eax
			punpcklwd mm7,mm7
			punpckldq mm7,mm7

			mov eax,[ebx+esi*4]

			
			
			
			movd mm4,eax
			punpcklbw mm4,mm0
			pmullw mm2,mm4

			mov eax,[edi]
			movd mm4,eax
			punpcklbw mm4,mm0
			pmullw mm7,mm4

			paddw mm7,mm2
			psrlw mm7,8

			packuswb mm7,mm0
			movd eax,mm7
			mov [edi],eax

			jmp SKIP2B_TRANS
NOTRANS:
			mov eax,[ebx+esi*4]
			mov [edi],eax


SKIP2B_TRANS:
			
	//		mov al,[edx+ebx]
	//		or al,al
	//		jz SKIP1


	//SKIP1:


			add edi,4
			dec ecx
			jnz LOOP2_TRANS

			jmp NEXT1_TRANS






ADDSUBROUTINE_TRANS:

			mov ecx,loopX
///@@@			shr ecx,1
LOOP2A_TRANS:
			movq mm4,mm1
			psrld mm4,16
			paddd mm1,mm3
			movd esi,mm4
			movq mm4,mm1
			pcmpgtw mm4,mm5
			pand mm4,mm6
			psubw mm1,mm4

			xor eax,eax
			mov al,[edx+esi]
			or eax,eax
			jz SKIP2A_TRANS



			//半透明加算@@@@@@@@@@@@@@@@@@@@@@
			cmp eax,255
			jz NOTRANS2


			movd mm4,eax
			punpcklwd mm4,mm4
			punpckldq mm4,mm4

			mov eax,[ebx+esi*4]
			movd mm7,eax
			paddusb mm7,mm2
			psubusb mm7,tmpmm7
			punpcklbw mm7,mm0

			pmullw mm4,mm7

			mov eax,[edi]
			movd mm7,eax
			punpcklbw mm7,mm0

			xor eax,eax
			mov al,[edx+esi]
			neg eax
			add eax,256
			movd mm0,eax
			punpcklwd mm0,mm0
			punpckldq mm0,mm0
			
			pmullw mm7,mm0

			paddw mm7,mm4
			psrlw mm7,8

			pxor mm0,mm0

			packuswb mm7,mm0
			movd eax,mm7
			mov [edi],eax

			jmp SKIP2A_TRANS

NOTRANS2:
			mov eax,[ebx+esi*4]
			movd mm4,eax
			paddusb mm4,mm2
			psubusb mm4,mm7
			movd eax,mm4
			mov [edi],eax
//			jmp SKIP2A_TRANS


SKIP2A_TRANS:
			add edi,4
			dec ecx
			jnz LOOP2A_TRANS




NEXT1_TRANS:
			pop edi
			pop ecx
			pop ebx
			add edi,lPitch
			add ebx,4*5
			dec ecx
			jnz LOOP1_TRANS



			emms
			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax

		}
	}

	return;
}
#endif


BOOL CEffectCloud::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}

/*_*/
