//
// TaClip.cpp
//

#include "..\nyanEffectLib\includer.h"

//#include "calcuSpeed.h"
#include "effectTaClip.h"



CEffectTaClip::CEffectTaClip(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(1);
	Create("BGZoomIn");//dummy@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#endif

}

CEffectTaClip::~CEffectTaClip()
{
	End();
}

void CEffectTaClip::End(void)
{
}

BOOL CEffectTaClip::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[35];
	int k = paraKosuu;
	if (k>35) k = 35;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	int sizeX = CMyGraphics::GetScreenSizeX();
	int sizeY = CMyGraphics::GetScreenSizeY();


	if (paraKosuu<1) para[0] = 20;	//frame


	if (paraKosuu<2) para[1] = 400;//cx1 (end)
	if (paraKosuu<3) para[2] = 300;//cy1
	if (paraKosuu<4) para[3] = -60;//vx1
	if (paraKosuu<5) para[4] = -40;//vy1
	if (paraKosuu<6) para[5] = 0;//sq-flag




	if (paraKosuu<7) para[6] = 100;	//半透明終了

	if (paraKosuu<8) para[7] = para[6];	//半透明開始
	if (paraKosuu<9) para[8] = 0;	//type
	if (paraKosuu<10) para[9] = 0;	//subframe

	if (paraKosuu < 11) para[10] = 0;	//fadeinFlag
	if (paraKosuu<12) para[11] = 0;	//type
	if (paraKosuu<13) para[12] = 0;	//subframe
	if (paraKosuu<14) para[13] = 255;	//R
	if (paraKosuu<15) para[14] = 255;	//G
	if (paraKosuu<16) para[15] = 255;	//B



	if (paraKosuu < 17) para[16] = 0;//line size(0:no)
	if (paraKosuu < 18) para[17] = 100;//ps
	if (paraKosuu < 19) para[18] = 255;//r
	if (paraKosuu < 20) para[19] = 255;//g
	if (paraKosuu < 21) para[20] = 255;//b



	if (paraKosuu < 22) para[21] = para[17];//ps start
	if (paraKosuu < 23) para[22] = 0;//type
	if (paraKosuu < 24) para[23] = 0;//sub



	if (paraKosuu < 25) para[24] = para[18];//rs
	if (paraKosuu < 26) para[25] = para[19];//gs
	if (paraKosuu < 27) para[26] = para[20];//bs
	if (paraKosuu < 28) para[27] = 0;//type
	if (paraKosuu < 29) para[28] = 0;//sub



	if (paraKosuu<30) para[29] = para[1];//cx2 (start)
	if (paraKosuu<31) para[30] = para[2];//cy2
	if (paraKosuu<32) para[31] = para[3];//vx2
	if (paraKosuu<33) para[32] = para[4];//vy2

	if (paraKosuu<34) para[33] = 0;	//type
	if (paraKosuu<35) para[34] = 0;	//subframe




	lp->flag = TRUE;
	lp->command = EFFECT_TACLIP;
	lp->countMax = para[0];
	lp->count = 0;


	for (i=0;i<35;i++)
	{
		lp->para[i] = para[i];
	}


	return TRUE;
}


BOOL CEffectTaClip::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectTaClip::BeginPrint(LPVOID para,int layer)
{

}

void CEffectTaClip::Init(LPVOID para,int layer)
{
}

void CEffectTaClip::Calcu(LPVOID lpEffect,int layer)
{
}

#if defined _TINYAN3DLIB_
void CEffectTaClip::Print(LPVOID lpEffect,int layer)
{
	CPicture* lpPic = m_allEffect->GetPicture(layer);
	CMyTexture* lpTexture = (CMyTexture*)(lpPic->GetTexture());

	LPDIRECT3DTEXTURE9 tex = lpTexture->GetTexture();
	SetTexture(tex);

	SIZE picSize = lpTexture->GetTextureSize();


	EFFECT* lp = (EFFECT*)lpEffect;

	int sizeX = CMyGraphics::GetScreenSizeX();
	int sizeY = CMyGraphics::GetScreenSizeY();


	int count = lp->count;
	int countMax = lp->countMax;
	int speedType = lp->para[5];
	int subFrame = lp->para[6];
	int endPercent10000 = lp->para[7] * 100;
	int startPercent10000 = lp->para[8] * 100;

	int percent10000 = CCalcuSpeed::calcu(count,countMax,startPercent10000,endPercent10000,subFrame,speedType);



	int dx1 = lp->para[1] - 0;
	int dy1 = lp->para[2] - 0;
	int dx2 = lp->para[1] + lp->para[3] - 1 - sizeX;
	int dy2 = lp->para[2] + lp->para[4] - 1 - sizeY;

	int x1 = 0 + (dx1 * percent10000 + 5000) / 10000;
	int y1 = 0 + (dy1 * percent10000 + 5000) / 10000;
	int x2 = sizeX + (dx2 * percent10000 + 5000) / 10000;
	int y2 = sizeY + (dy2 * percent10000 + 5000) / 10000;

	if (x1<0) x1 = 0;
	if (y1<0) y1 = 0;
	if (x2>sizeX) x2 = sizeX;
	if (y2>sizeY) y2 = sizeY;

	if (x2<=x1) return;
	if (y2<=y1) return;


	SIZE srcSize;
	srcSize.cx = x2 - x1;
	srcSize.cy = y2 - y1;
	SIZE putSize;
	putSize.cx = sizeX;
	putSize.cy = sizeY;
	POINT putPoint;
	putPoint.x = 0;
	putPoint.y = 0;
	POINT srcPoint;
	srcPoint.x = x1;
	srcPoint.y = y1;

	StretchBlt(&putPoint,&putSize,&srcPoint,&srcSize,&picSize);

	//stretchblt
	return;

/*

	HRESULT hr = effect->SetTexture(m_hTexture,tex);

	effect->SetTechnique(m_hTechnique);
	effect->Begin(NULL,0);
	effect->BeginPass(0);

	CMyDirect3D::DrawTextureOne(lpTexture,putPoint,srcPoint,putSize,&srcSize);

	effect->EndPass();
	effect->End();
*/

}

#else

void CEffectTaClip::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	int* dst = CMyGraphics::GetScreenBuffer();


	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int count = lp->count;
	int countMax = lp->countMax;


/*




	if (paraKosuu<7) para[6] = 100;	//半透明終了

	if (paraKosuu<8) para[7] = para[6];	//半透明開始
	if (paraKosuu<9) para[8] = 0;	//type
	if (paraKosuu<10) para[9] = 0;	//subframe

	if (paraKosuu < 11) para[10] = 0;	//fadeinFlag
	if (paraKosuu<12) para[11] = 0;	//type
	if (paraKosuu<13) para[12] = 0;	//subframe
	if (paraKosuu<14) para[13] = 255;	//R
	if (paraKosuu<15) para[14] = 255;	//G
	if (paraKosuu<16) para[15] = 255;	//B






	





*/



	int cx1 = lp->para[1];
	int cy1 = lp->para[2];
	int vx1 = lp->para[3];
	int vy1 = lp->para[4];

	int squareFlag = lp->para[5];

	int cx2 = lp->para[29];
	int cy2 = lp->para[30];
	int vx2 = lp->para[31];
	int vy2 = lp->para[32];

	int vecSubType = lp->para[33];
	int vecSubFrame = lp->para[34];

	int vectorPercent10000 = CCalcuSpeed::calcu(count,countMax,0,10000,vecSubFrame,vecSubType);


	int cx = cx2 + ((cx1-cx2) * vectorPercent10000) / 10000;
	int cy = cy2 + ((cy1-cy2) * vectorPercent10000) / 10000;
	int vx = vx2 + ((vx1-vx2) * vectorPercent10000) / 10000;
	int vy = vy2 + ((vy1-vy2) * vectorPercent10000) / 10000;

//	if ((vx == 0) || (vy == 0)) return;



	if ((vx == 0) && (vy == 0))
	{
		vx = 1;
	}


	int lineSize = lp->para[16];
	int linePercentEnd = lp->para[17];
	int lineColorRedEnd = lp->para[18];
	int lineColorGreenEnd = lp->para[19];
	int lineColorBlueEnd = lp->para[20];

	int linePercentStart = lp->para[21];
	int linePercentSubType = lp->para[22];
	int linePercentSubFrame = lp->para[23];



	int lineColorRedStart = lp->para[24];
	int lineColorGreenStart = lp->para[25];
	int lineColorBlueStart = lp->para[26];
	int lineColorSubType = lp->para[27];
	int lineColorSubFrame = lp->para[28];


	int lineColorRed = lineColorRedEnd;
	int lineColorGreen = lineColorGreenEnd;
	int lineColorBlue = lineColorBlueEnd;
	int linePercent = linePercentEnd;

	if (lineSize > 0)
	{
		lineColorRed = CCalcuSpeed::calcu(count,countMax,lineColorRedStart,lineColorRedEnd,lineColorSubFrame,lineColorSubType);
		lineColorGreen = CCalcuSpeed::calcu(count,countMax,lineColorGreenStart,lineColorGreenEnd,lineColorSubFrame,lineColorSubType);
		lineColorBlue = CCalcuSpeed::calcu(count,countMax,lineColorBlueStart,lineColorBlueEnd,lineColorSubFrame,lineColorSubType);

		linePercent = CCalcuSpeed::calcu(count,countMax,linePercentStart,linePercentEnd,linePercentSubFrame,linePercentSubType);
	}




	int pic = lp->pic;
	if (pic == -1) return;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;
	if (lpPic->Check256()) return;


	POINT pt1 = m_allEffect->GetDstPoint(layer);
	int putX = pt1.x;
	int putY = pt1.y;
	SIZE sz = lpPic->GetPicSize();
	int sizeX = sz.cx;
	int sizeY = sz.cy;
	int srcX = 0;
	int srcY = 0;
	//clip1


	if (putX < 0)
	{
		sizeX -= (-putX);
		srcX += (-putX);
		putX = 0;
	}
	if (sizeX > 0)
	{
		if (putX + sizeX > screenSizeX)
		{
			sizeX = screenSizeX - putX;
		}
	}

	if (putY < 0)
	{
		sizeY -= (-putY);
		srcY += (-putY);
		putY = 0;
	}
	if (sizeY > 0)
	{
		if (putY + sizeY > screenSizeY)
		{
			sizeY = screenSizeY - putY;
		}
	}


	int* cutTable = m_allEffect->GetTempWork();



	//dummy set
	for (int i=0;i<screenSizeY;i++)
	{
		*(cutTable+i*2+0) = 0;
		*(cutTable+i*2+1) = 0;
	}

	int maxSizeX = screenSizeX;
	if (maxSizeX > sizeX)
	{
		maxSizeX = sizeX;
		if (maxSizeX<0) maxSizeX = 0;
	}

	if (squareFlag == 0)
	{
		if (vy == 0)	//完全水平
		{
			if (vx > 0)
			{
				for (int j=cy;j<screenSizeY;j++)
				{
					*(cutTable+j*2+0) = 0;
					*(cutTable+j*2+1) = screenSizeX;
				}
			}
			else
			{
				for (int j=0;j<=cy;j++)
				{
					*(cutTable+j*2+0) = 0;
					*(cutTable+j*2+1) = screenSizeX;
				}
			}
		}
		else if (vx == 0)	//完全垂直
		{
			if (vy < 0)
			{
				for (int j=0;j<screenSizeY;j++)
				{
					*(cutTable+j*2+0) = cx;
					*(cutTable+j*2+1) = screenSizeX-cx;
				}
			}
			else
			{
				for (int j=0;j<screenSizeY;j++)
				{
					*(cutTable+j*2+0) = 0;
					*(cutTable+j*2+1) = cx+1;
				}
			}
		}
		else
		{

			float f = ((float)vx) / ((float)vy);

			float lr = f * 0.5f;
			if (lr < 0.0f) lr *= -1.0f;

			if (vy >= 0)
			{
				lr *= -1.0f;
				
//				lr = -0.5f;
				lr = -1.0f;

			}
			else
			{
				lr = 0.0f;	//修正なしにする
			}

			for (int j=0;j<screenSizeY;j++)
			{
				float fdx = (float)(j-cy);


				int limitX = cx + (int)(fdx * f + lr  + 0.5f);

				if (vy < 0)
				{
					if (limitX<screenSizeX)
					{
						if (limitX<0) limitX = 0;
						*(cutTable+j*2+0) = limitX;
						*(cutTable+j*2+1) = screenSizeX-limitX;
					}
				}
				else
				{
					if (limitX>=0)
					{
						if (limitX>=screenSizeX) limitX = screenSizeX-1;
						*(cutTable+j*2+0) = 0;
						*(cutTable+j*2+1) = limitX+1;
					}
				}
			}
		}
	}
	else
	{
		if ((vx == 0) || (vy == 0)) return;



		int sqcx = cx1;
		int sqcy = cy1;
		int sqvx = vx1;
		int sqvy = vy1;

//		if (squareFlag == 2)
		if (1)
		{
			sqcx = cx;
			sqcy = cy;
			sqvx = vx;
			sqvy = vy;
		}

		int sqx1 = sqcx;
		int sqy1 = sqcy;
		int sqx2 = sqcx + sqvx;
		int sqy2 = sqcy + sqvy;


		if (sqvy > 0)
		{
			sqy2 -= 1;
		}
		else
		{
			sqy2 += 1;
		}

		if (sqx1 > sqx2)
		{
			int tmp = sqx1;
			sqx1 = sqx2;
			sqx2 = tmp;
		}

		if (sqy1 > sqy2)
		{
			int tmp = sqy1;
			sqy1 = sqy2;
			sqy2 = tmp;
		}

		if (sqx1 >= screenSizeX) return;
		if (sqy1 >= screenSizeY) return;
		if (sqx2 < 0) return;
		if (sqy2 < 0) return;

		if (sqx1 < 0) sqx1 = 0;
		if (sqx2 < 0) sqx2 = 0;
		if (sqx2 > screenSizeX) sqx2 = screenSizeX;

		if (sqy1<0) sqy1 = 0;
		if (sqy2 >= screenSizeY) sqy2 = screenSizeY-1;

		int sqsz = sqx2 - sqx1;
		for (int j=sqy1;j<=sqy2;j++)
		{
			*(cutTable+j*2+0) = sqx1;
			*(cutTable+j*2+1) = sqsz;
		}
	}




	int psEnd = lp->para[6];
	int psStart = lp->para[7];
	int psType = lp->para[8];
	int psSubFrame = lp->para[9];
	
	int ps = CCalcuSpeed::calcu(count,countMax,psStart*100,psEnd*100,psSubFrame,psType);
	int ps256 = (ps * 255) / 10000;



	int fadeinFlag = lp->para[10];
	int fadeinMulti = 0;
	LONGLONG fadeinAdd = 0;

	float f3dps = 0.0f;

	if (fadeinFlag)
	{
		int fpsSubFrame = lp->para[11];
		int fpsSubType = lp->para[12];
		int fps = CCalcuSpeed::calcu(count,countMax,0,255,fpsSubFrame,fpsSubType);

		f3dps = ((float)(255-fps)) / 255.0f;

		int flashR = ((255-fps) * (lp->para[13])) /255;
		int flashG = ((255-fps) * (lp->para[14])) /255;
		int flashB = ((255-fps) * (lp->para[15])) /255;

		fadeinMulti = (fps<<16) | (fps<<8) | fps;

		LONGLONG fr = (LONGLONG)flashR;
		LONGLONG fg = (LONGLONG)flashG;
		LONGLONG fb = (LONGLONG)flashB;

		fr <<= 32;
		fg <<= 16;
		fadeinAdd = fr | fg | fb;
	}






	if ((sizeX > 0) && (sizeY > 0))
	{
		int* dst = CMyGraphics::GetScreenBuffer();
		dst += screenSizeX * putY;

		int* src = (int*)(lpPic->GetBuffer());
//		src += screenSizeX * srcY;	bug@@
		src += sz.cx * srcY;

//		src += putX;

		char* mask = lpPic->GetMaskPic();
//		mask += screenSizeX * srcY;@@bug
		mask += sz.cx * srcY;
//		mask += putX;

		int srcPitch = sz.cx * sizeof(int);
		int maskPitch = sz.cx;
		int dstPitch = screenSizeX * sizeof(int);
		int workPitch = sizeof(int) * 2;
		int* work = cutTable + putY * 2;

		int putX0 = pt1.x;
		int srcSizeX0 = sz.cx;

//		int checkSizeX = putX0 + srcSizeX0;

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

			mov eax,ps256
			movd mm6,eax
			punpcklwd mm6,mm6
			punpckldq mm6,mm6

			mov eax,01000100h
			movd mm7,eax
			punpckldq mm7,mm7

			mov edx,work
			mov edi,dst
			mov esi,src
			mov ebx,mask
			mov ecx,sizeY
LOOP1:
			push ebx
			push ecx
			push edx
			push esi
			push edi


			mov eax,[edx]
			mov ecx,[edx+4]

			cmp eax,putX0
			jns TEST01
			add ecx,eax
			mov eax,putX0
			sub ecx,eax
			cmp ecx,1
			js SKIP1

TEST01:
			add ecx,eax
			sub ecx,putX0
			cmp ecx,srcSizeX0
			js OK1
			mov ecx,srcSizeX0
Ok1:
			add ecx,putX0
			sub ecx,eax


			push eax
			shl eax,1
			shl eax,1
			add edi,eax
			pop eax

			sub eax,putX0
			add ebx,eax
			shl eax,1
			shl eax,1
			add esi,eax

			cmp ecx,1
			js SKIP1
LOOP2:



			xor eax,eax
			mov al,[ebx]
			or eax,eax
			jz SKIP0


			inc eax
			movd mm4,eax
			punpcklwd mm4,mm4
			punpckldq mm4,mm4

			pmullw mm4,mm6
			psrlw mm4,8

			movq mm5,mm7
			psubw mm5,mm4

			mov eax,[esi]
			movd mm1,eax
			punpcklbw mm1,mm0

			mov eax,fadeinFlag
			or eax,eax
			jz SKIP00

			mov eax,fadeinMulti
			movd mm2,eax
			punpcklbw mm2,mm0
			pmullw mm1,mm2
			psrlw mm1,8
			paddw mm1,fadeinAdd

SKIP00:


			mov eax,[edi]
			movd mm2,eax
			punpcklbw mm2,mm0

			pmullw mm4,mm1
			pmullw mm5,mm2
			paddw mm4,mm5
			psrlw mm4,8
			packuswb mm4,mm0
			movd eax,mm4

			mov [edi],eax

SKIP0:




			add esi,4
			add edi,4
			inc ebx
			dec ecx
			jnz LOOP2



SKIP1:

			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx

			add edx,workPitch
			add esi,srcPitch
			add ebx,maskPitch
			add edi,dstPitch

			dec ecx
			jnz LOOP1


			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax
			emms
		}

#endif





	}



	//cx,cy,vx,vy
	int absVx = vx;
	int absVy = vy;
	if (absVx < -1) absVx *= -1;
	if (absVy < -1) absVy *= -1;


	if (lineSize > 0)
	{
		if (squareFlag == 0)
		{
			//line





			if (absVx > absVy)
			{
				float lx1 = (float)(-lineSize);
				float ly1 = (float)(cx+lineSize);
				float lf= (float)vy / (float)vx;
				ly1 *= -lf;
				ly1 += (float)cy;


				float lx2 = (float)(screenSizeX + lineSize);
//				int lx2 = screenSizeX + lineSize;

				float ly2 = (lf * (float)(screenSizeX + lineSize - cx));
				ly2 += (float)cy;

				float minusY = (float)(lineSize / 2);
//				minusY *= 0.5f;

				//水平にちかい
				for (int i=0;i<lineSize;i++)
				{
//					CAllGeo::Line(cx,cy+i,cx+vx,cy+vy+i,lineColorRed,lineColorGreen,lineColorBlue,linePercent);
					CAllGeo::LineF(lx1,ly1+(float)i-minusY,lx2,ly2+(float)i-minusY,lineColorRed,lineColorGreen,lineColorBlue,linePercent);
				}

			}
			else
			{
				float ly1 = (float)(-lineSize);
				float lx1 = (float)(cy+lineSize);
				float lf= (float)vx / (float)vy;
				lx1 *= -lf;
				lx1 += (float)cx;


				float ly2 = (float)(screenSizeY + lineSize);
//				int lx2 = screenSizeX + lineSize;

				float lx2 = (lf * (float)(screenSizeY + lineSize - cy));
				lx2 += (float)cx;

				float minusX = (float)(lineSize / 2);
//				minusX *= 0.5f;

				//垂直にちかい
				for (int i=0;i<lineSize;i++)
				{
//					CAllGeo::Line(cx,cy+i,cx+vx,cy+vy+i,lineColorRed,lineColorGreen,lineColorBlue,linePercent);
					CAllGeo::LineF(lx1+(float)i-minusX,ly1,lx2+(float)i-minusX,ly2,lineColorRed,lineColorGreen,lineColorBlue,linePercent);
				}

			}
		}
		else
		{
			//square
			int dlt = lineSize / 2;


			int sqcx = cx1;
			int sqcy = cy1;
			int sqvx = vx1;
			int sqvy = vy1;

//			if (squareFlag == 2)
			if (1)
			{
				sqcx = cx;
				sqcy = cy;
				sqvx = vx;
				sqvy = vy;
			}



			int stx = sqcx;
			int sty = sqcy;
			int edx = sqcx + sqvx;
			int edy = sqcy + sqvy;


			if (stx > edx)
			{
				int tmp = stx;
				stx = edx;
				edx = tmp;
			}

			if (sty > edy)
			{
				int tmp = sty;
				sty = edy;
				edy = tmp;
			}


			int x1 = stx - dlt;
			int sizeX1 = edx - stx + lineSize;
			int y1 = sty - dlt;
			int sizeY1 = lineSize;
			CAllGeo::TransBoxFill(x1,y1,sizeX1,sizeY1,lineColorRed,lineColorGreen,lineColorBlue,linePercent);

			int y2 = edy - dlt;
			int sizeY2 = lineSize;
			if (y2  < y1 + sizeY1)
			{
				sizeY2 -= (y1 + sizeY1 - y2);
				y2 = y1 + sizeY1;
			}

			if (sizeY2 > 0)
			{
				CAllGeo::TransBoxFill(x1,y2,sizeX1,sizeY2,lineColorRed,lineColorGreen,lineColorBlue,linePercent);
			}

			int sukimaY = y2 - (y1 + sizeY1);
			if (sukimaY > 0)
			{
				CAllGeo::TransBoxFill(x1,y1+sizeY1,lineSize,sukimaY,lineColorRed,lineColorGreen,lineColorBlue,linePercent);
				int x2 = edx - dlt;
				int sizeX2 = lineSize;
				if (x2 < x1 + sizeX2)
				{
					sizeX2 -= ( x2 + sizeX1 - x2);
					x2 = x1 + sizeX1;
				}

				if (sizeX2 > 0)
				{
					CAllGeo::TransBoxFill(x2,y1+sizeY1,sizeX2,sukimaY,lineColorRed,lineColorGreen,lineColorBlue,linePercent);
				}
			}


		}
	}


}
#endif


BOOL CEffectTaClip::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}

