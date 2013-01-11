//
// ClipZoomIn.cpp
//

#include "..\nyanEffectLib\includer.h"

//#include "calcuSpeed.h"
#include "effectClipZoomIn.h"


CEffectClipZoomIn::CEffectClipZoomIn(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(1);
	Create("BGZoomIn");//dummy@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#endif

}

CEffectClipZoomIn::~CEffectClipZoomIn()
{
	End();
}

void CEffectClipZoomIn::End(void)
{
}

BOOL CEffectClipZoomIn::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[33];
	int k = paraKosuu;
	if (k>33) k = 33;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	int sizeX = CMyGraphics::GetScreenSizeX();
	int sizeY = CMyGraphics::GetScreenSizeY();


	if (paraKosuu<1) para[0] = 20;	//frame

	if (paraKosuu<2) para[1] = sizeX / 4;
	if (paraKosuu<3) para[2] = sizeY / 4;
	if (paraKosuu<4) para[3] = sizeX / 2;
	if (paraKosuu<5) para[4] = sizeY / 2;

	if (para[1]<0) para[1] = 0;
	if (para[1] >= sizeX) para[1] = sizeX - 1;
	if (para[2]<0) para[2] = 0;
	if (para[2] >= sizeY) para[2] = sizeY -1;

	if ((para[1]+para[3]) > sizeX) para[3] = sizeX-para[1];
	if ((para[2]+para[4]) > sizeY) para[4] = sizeY-para[2];

	if (paraKosuu<6) para[5] = 0;	//speedType
	if (paraKosuu<7) para[6] = 0;	//subFRame
	if (paraKosuu<8) para[7] = 100;	//end%
	if (paraKosuu<9) para[8] = 0;	//start%

	if (paraKosuu<10) para[9] = para[1] + para[3]/2;//cx1 (end)
	if (paraKosuu<11) para[10] = para[2] + para[4]/2;//cy1
	if (paraKosuu<12) para[11] = -60;//vx1
	if (paraKosuu<13) para[12] = -40;//vy1

	if (paraKosuu<14) para[13] = 0;//sq-flag


	if (paraKosuu<15) para[14] = para[9];//cx2 (start)
	if (paraKosuu<16) para[15] = para[10];//cy2
	if (paraKosuu<17) para[16] = para[11];//vx2
	if (paraKosuu<18) para[17] = para[12];//vy2


	if (paraKosuu<19) para[18] = 0;	//type
	if (paraKosuu<20) para[19] = 0;	//subframe


	if (paraKosuu < 21) para[20] = 0;//line size(0:no)
	if (paraKosuu < 22) para[21] = 100;//ps
	if (paraKosuu < 23) para[22] = 255;//r
	if (paraKosuu < 24) para[23] = 255;//g
	if (paraKosuu < 25) para[24] = 255;//b
	if (paraKosuu < 26) para[25] = para[21];//ps start
	if (paraKosuu < 27) para[26] = 0;//type
	if (paraKosuu < 28) para[27] = 0;//sub
	if (paraKosuu < 29) para[28] = para[22];//rs
	if (paraKosuu < 30) para[29] = para[23];//gs
	if (paraKosuu < 31) para[30] = para[24];//bs
	if (paraKosuu < 32) para[31] = para[26];//type
	if (paraKosuu < 33) para[32] = para[27];//sub





	lp->flag = TRUE;
	lp->command = EFFECT_CLIPZOOMIN;
	lp->countMax = para[0];
	lp->count = 0;


	for (i=0;i<33;i++)
	{
		lp->para[i] = para[i];
	}


	return TRUE;
}


BOOL CEffectClipZoomIn::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectClipZoomIn::BeginPrint(LPVOID para,int layer)
{

}

void CEffectClipZoomIn::Init(LPVOID para,int layer)
{
}

void CEffectClipZoomIn::Calcu(LPVOID lpEffect,int layer)
{
}

#if defined _TINYAN3DLIB_
void CEffectClipZoomIn::Print(LPVOID lpEffect,int layer)
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

void CEffectClipZoomIn::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	int* dst = CMyGraphics::GetScreenBuffer();


	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int count = lp->count;
	int countMax = lp->countMax;

	int dx1 = lp->para[1] - 0;
	int dy1 = lp->para[2] - 0;
	int dx2 = lp->para[1] + lp->para[3] - 1 - screenSizeX;
	int dy2 = lp->para[2] + lp->para[4] - 1 - screenSizeY;

	int speedType = lp->para[5];
	int subFrame = lp->para[6];
	int endPercent10000 = lp->para[7] * 100;
	int startPercent10000 = lp->para[8] * 100;

	int percent10000 = CCalcuSpeed::calcu(count,countMax,startPercent10000,endPercent10000,subFrame,speedType);


	int cx1 = lp->para[9];
	int cy1 = lp->para[10];
	int vx1 = lp->para[11];
	int vy1 = lp->para[12];

	int squareFlag = lp->para[13];

	int cx2 = lp->para[14];
	int cy2 = lp->para[15];
	int vx2 = lp->para[16];
	int vy2 = lp->para[17];

	int vecSubType = lp->para[18];
	int vecSubFrame = lp->para[19];

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


	int lineSize = lp->para[20];
	int linePercentEnd = lp->para[21];
	int lineColorRedEnd = lp->para[22];
	int lineColorGreenEnd = lp->para[23];
	int lineColorBlueEnd = lp->para[24];
	int linePercentStart = lp->para[25];
	int linePercentSubType = lp->para[26];
	int linePercentSubFrame = lp->para[27];
	int lineColorRedStart = lp->para[28];
	int lineColorGreenStart = lp->para[29];
	int lineColorBlueStart = lp->para[30];
	int lineColorSubType = lp->para[31];
	int lineColorSubFrame = lp->para[32];


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







	int* cutTable = m_allEffect->GetTempWork();



	//dummy set
	for (int i=0;i<screenSizeY;i++)
	{
		*(cutTable+i*2+0) = 0;
		*(cutTable+i*2+1) = 0;
	}

	if (squareFlag == 0)
	{
		if (vy == 0)	//äÆëSêÖïΩ
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
		else if (vx == 0)	//äÆëSêÇíº
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
				lr = 0.0f;	//èCê≥Ç»ÇµÇ…Ç∑ÇÈ
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

		if (squareFlag == 2)
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


	int x1 = 0 + (dx1 * percent10000 + 5000) / 10000;
	int y1 = 0 + (dy1 * percent10000 + 5000) / 10000;
	int x2 = screenSizeX + (dx2 * percent10000 + 5000) / 10000;
	int y2 = screenSizeY + (dy2 * percent10000 + 5000) / 10000;

	if (x1<0) x1 = 0;
	if (y1<0) y1 = 0;
	if (x2>screenSizeX) x2 = screenSizeX;
	if (y2>screenSizeY) y2 = screenSizeY;

	if (x2<=x1) return;
	if (y2<=y1) return;

	int dltX = ((x2 - x1) * 65536) / screenSizeX;
	int dltY = ((y2 - y1) * 65536) / screenSizeY;

//	int* screen = CMyGraphics::GetScreenBuffer();



	int pic = lp->pic;
	if (pic == -1) return;

	RECT rc;
	RECT rc0;
	SetRect(&rc0,0,0,screenSizeX,screenSizeY);
//	m_game->m_picture[pic]->GetPicSize(&rc);

	CPicture* lpPic = m_allEffect->GetPicture(layer);	//debug 2005-05-08
	lpPic->GetPicSize(&rc);
//	if (!EqualRect(&rc,&rc0)) return;

	if (lpPic->Check256()) return;

	int* srcPtr = lpPic->GetPictureBuffer();

	int srcPitch = rc.right;
	if (srcPitch < screenSizeX) return;
	int srcPitch4 = srcPitch * sizeof(int);

	srcPtr += x1;
	srcPtr += y1 * srcPitch;

//	int amariX = 0x8000;
//	int amariY = 0x8000;

	int amariX = 0;
	int amariY = 0;

//	dltX = 0;
//	dltY = 0;

//	int srcPitch = screenSizeX * 4;
	int dstPitch = screenSizeX * 4;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		mov esi,srcPtr
		mov edi,dst

		mov ebx,cutTable
		mov ecx,screenSizeY
LOOP1:
		push ebx
		push ecx
		push edx
		push esi
		push edi

		mov eax,[ebx]
		shl eax,1
		shl eax,1
		add edi,eax

		mov ecx,[ebx+4]
		cmp ecx,1
		js SKIP1

		mov edx,dltX
		shr eax,1
		shr eax,1
		mul edx
		add eax,amariX
		mov edx,eax
		and edx,0ffffh
		shr eax,16
		shl eax,2
		add esi,eax

//		mov edx,amariX
		mov ebx,dltX

//		mov ecx,screenSizeX
LOOP2:
		mov eax,[esi]
		mov [edi],eax
;
		add edx,ebx
		mov eax,edx
		and edx,0ffffh
		shr eax,16
		shl eax,2
		add esi,eax
		add edi,4
		dec ecx
		jnz LOOP2


SKIP1:
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx

		mov eax,amariY
		and eax,0ffffh
		add eax,dltY
		mov amariY,eax
		shr eax,16
		mov edx,srcPitch4
		mul edx
		add esi,eax

		add edi,dstPitch

		add ebx,4*2
		dec ecx
		jnz LOOP1


		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
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

				//êÖïΩÇ…ÇøÇ©Ç¢
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

				//êÇíºÇ…ÇøÇ©Ç¢
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

			if (squareFlag == 2)
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


BOOL CEffectClipZoomIn::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}

