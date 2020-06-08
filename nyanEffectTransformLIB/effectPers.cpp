//
// effectPers.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectPers.h"


CEffectPers::CEffectPers(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(1);
	Create("Pers");
#endif
}

CEffectPers::~CEffectPers()
{
	End();
}

void CEffectPers::End(void)
{
}

BOOL CEffectPers::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int para[16];
	int k = paraKosuu;
	if (k>16) k = 16;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 0;	//DIST1End
	if (paraKosuu<3) para[2] = 0;	//DIST2End
	if (paraKosuu<4) para[3] = 100;	//HeightEnd
	if (paraKosuu<5) para[4] = 100;	//PerCentEnd

	if (paraKosuu<6) para[5] = 0;	//透過フラグ
	
	if (paraKosuu<7) para[6] = para[1];	//DIST1Start
	if (paraKosuu<8) para[7] = para[2];	//DIST2Start
	if (paraKosuu<9) para[8] = para[3];	//HeightStart
	if (paraKosuu<10) para[9] = para[4];	//PerCentStart

	if (paraKosuu<11) para[10] = 0;	//clipY1End
	if (paraKosuu<12) para[11] = screenSizeY;	//clipY2End

	if (paraKosuu<13) para[12] = para[10];	//clipY1Start
	if (paraKosuu<14) para[13] = para[11];	//clipY2Start


	lp->flag = TRUE;
	lp->command = EFFECT_PERS;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectPers::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectPers::BeginPrint(LPVOID para,int layer)
{

}

void CEffectPers::Init(LPVOID para,int layer)
{
}

void CEffectPers::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectPers::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;


	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();



	int dv = lp->countMax;
	int c = lp->count;

	if (dv<1)
	{
		dv = 1;
	}

	if (c>dv)
	{
		c = dv;
	}


	int transFlag = lp->para[5];

	int dist1 = lp->para[6] + ((lp->para[1] - lp->para[6]) * c ) / dv;
	int dist2 = lp->para[7] + ((lp->para[2] - lp->para[7]) * c ) / dv;

	int height = lp->para[8] + ((lp->para[3] - lp->para[8]) * c ) / dv;
	int percent = lp->para[9] + ((lp->para[4] - lp->para[9]) * c ) / dv;
	int clipY1 = lp->para[12] + ((lp->para[10] - lp->para[12]) * c ) / dv;
	int clipY2 = lp->para[13] + ((lp->para[11] - lp->para[13]) * c ) / dv;

	if (clipY1<0) clipY1 = 0;
	if (clipY2 >= screenSizeY) clipY2 = screenSizeY-1;
	int loopY = clipY2 - clipY1 + 1;
	if (loopY<1) return;

	if (height==0) height = 1;
	if (percent<1) percent = 1;


	double th1 = atan2((double)dist1,(double)height);
	double th2 = atan2((double)dist2,(double)height);
	double dth = th2 - th1;

	double r0 = sqrt((double)(dist1*dist1 + height*height));


//	int tables[MAXSCREENSIZEY*2];	//deltaY dotX
//	int* tables = CEffectSimpleWipe::m_shapeWork;
	int* tables = m_allEffect->GetTempWork();


	double yy = 0;
	double divY = (double)loopY;
	double height0 = (double)height;
	double percent0 = (double)percent;
	percent0 /= 100.0;

	double scale = 1.0 / r0;
	scale /= percent0;

	int yLast = -1;

	int pic = lp->pic;
	if (pic == -1) return;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	RECT rc;
	lpPic->GetPicSize(&rc);

	int sx = rc.right;
	int sy = rc.bottom;

	if ((sx<1) || (sy<1)) return;

	int cx = sx / 2;
	int cy = sy / 2;


	int zX = lp->dst.left;
	int zY = lp->dst.top;


	int addX = -zX + cx;
	int addY = -zY;




	double yy3D = (double)addY;

	int dst3DY1 = -1;
	int dst3DY2 = -1;
	
	int src3DY1 = -1;
	int src3DY2 = -1;


	int startSy = -1;
	int lastSy = sy;
	int startDy = 0;





	double srcDot1 = 1.0;
	double srcDot2 = 1.0;


	for (int i=0;i<loopY;i++)
	{
		tables[i*2] = (int)(yy+0.5);

		double th = th1 + (dth * (double)i) / divY;

		double dist = height0 * tan(th);
		double r = height0 / cos(th);

		double dot = r * scale;

		int dotXHigh = (int)dot;
		int dotXLow = (int)((dot - (double)dotXHigh) * 65536.0);

	//	dotXHigh = 1;
	//	dotXLow = 0;

		tables[i*2+1] = (dotXHigh << 16) | dotXLow;

		if (yy3D >= 0.0)
		{
			if (dst3DY1 == -1)
			{
				dst3DY1 = i;
			}

			if (src3DY1 == -1)
			{
				src3DY1 = (int)yy3D;
				srcDot1 = dot;
			}
		}

		if ((((int)(yy3D+dot)) >= sy) || (i == (loopY-1)))
		{
			if (dst3DY2 == -1)
			{
				dst3DY2 = i;
			}

			if (src3DY2 == -1)
			{
				src3DY2 = (int)(yy3D);
				srcDot2 = dot;
			}
		}

		yy3D += dot;
		yy += dot;

		if (yy >= (double)sy)
		{
			if (yLast == -1)
			{
				yLast = i;
			}
		}

		if (i == loopY-1)
		{
			if (yLast == -1)
			{
				lastSy = (int)yy;
			}
		}

		if (yy >= 0.0)
		{
			if (startDy < 0)
			{
				startDy = i;
				startSy = 0;
			}
		}

	}

	if (yLast == -1)
	{
		yLast = loopY;
	}



	int* src = (int*)(lpPic->GetBuffer());
	if (src == NULL) return;

	char* mask = lpPic->GetMaskPic();



	int loopX = screenSizeX;

	int trans = *src;

	if (transFlag == 2)
	{
		if (mask == NULL) transFlag = 1;
		if (lpPic->CheckMaskExist() == FALSE) transFlag = 1;
	}


	if (loopX<1) return;
	if (loopY<1) return;

	int* table = tables;

	int lPitch = screenSizeX * 4;

#if defined _TINYAN3DLIB_

	if (CheckEffectError()) return;

	if ((dst3DY1 == -1) || (dst3DY2 == -1)) return;

//	int srcX1 = -zX;
//	int srcX2 = sx-zX;
	int srcX1 = 0;
	int srcX2 = sx;


//	int srcY1 = startSy + addY;
//	int srcY2 = lastSy + addY;

//	int y1 = startDy;
//	int y2 = yLast;

	int srcY1 = src3DY1;
	int srcY2 = src3DY2;
	int y1 = dst3DY1;
	int y2 = dst3DY2;







//	double thth1 = th1 + (dth * (double)y1) / divY;
//	double thth2 = th1 + (dth * (double)y2) / divY;
	double thth0 = th1 + (dth * (double)0) / divY;
	double thth1 = th1 + (dth * (double)y1) / divY;
	double thth2 = th1 + (dth * (double)y2) / divY;

	double rrr1 = cos(thth1) / cos(thth0);
	double rrr2 = cos(thth2) / cos(thth0);
	double mul1 = percent0 * rrr1;
	double mul2 = percent0 * rrr2;


	double mm1 = (double)(10000 / dist1);
	double mm2 = (double)(10000 / dist2);
mm1=1.0;
mm2=1.0;

	int dstX11 = (int)(((double)(sx/2)) - mm1*mul1 * ((double)(sx/2)) + zX/srcDot1);
	int dstX12 = (int)(((double)(sx/2)) + mm1*mul1 * ((double)(sx/2)) + zX/srcDot1);

	int dstX21 = (int)(((double)(sx/2)) - mm2*mul2 * ((double)(sx/2)) + zX/srcDot2);
	int dstX22 = (int)(((double)(sx/2)) + mm2*mul2 * ((double)(sx/2)) + zX/srcDot2);

	int dstY1 = dst3DY1;
	int dstY2 = dst3DY2;
//	int dstY2 = (int)(((double)yLast));
//	int dstY2 = (int)(((double)yLast) * percent0);
//	int dstY2 = (int)(((double)loopY)/rrr);

	float rFar = (float)(sqrt(10000.0*10000.0 + height0*height0));
	float rNear = (float)height0;

	float h0 = (float)height0;

	float rz1 = h0 / cos((float)thth1);
	float rz2 = h0 / cos((float)thth2);

	float wz1 = rFar / rz1 * (rz1-rNear) / (rFar-rNear);
	float wz2 = rFar / rz2 * (rz2-rNear) / (rFar-rNear);

//z1=0.0f;
//z2=0.0f;


	dstY1 += clipY1;
	dstY2 += clipY1;




	POINT dstPoint[4];
	POINT srcPoint[4];
	float lpZ[4*2];


	dstPoint[0].x = dstX11;
	dstPoint[0].y = dstY1;
	srcPoint[0].x = srcX1;
	srcPoint[0].y = srcY1;
	lpZ[0*2] = rz1;
	lpZ[0*2+1] = wz1;

	dstPoint[1].x = dstX12;
	dstPoint[1].y = dstY1;
	srcPoint[1].x = srcX2;
	srcPoint[1].y = srcY1;
	lpZ[1*2] = rz1;
	lpZ[1*2+1] = wz1;

	dstPoint[2].x = dstX22;
	dstPoint[2].y = dstY2;
	srcPoint[2].x = srcX2;
	srcPoint[2].y = srcY2;
	lpZ[2*2] = rz2;
	lpZ[2*2+1] = wz2;

	dstPoint[3].x = dstX21;
	dstPoint[3].y = dstY2;
	srcPoint[3].x = srcX1;
	srcPoint[3].y = srcY2;
	lpZ[3*2] = rz2;
	lpZ[3*2+1] = wz2;

	CMyTexture* lpTexture = (CMyTexture*)(lpPic->GetTexture());
	SetTexture(lpTexture->GetTexture());

	int shader = 0;
	LPD3DXEFFECT effect = m_d3dxEffect;
	if (effect == NULL) return;

	SetAllColor(shader);
	SetAllPercent(shader);
	SetAllConst(shader);
	SetAllTexture(shader);
	SetAllMatrix(shader);

	if (m_hTechnique[shader] == NULL)
	{
	OutputDebugString("[no tec]");
	}

	HRESULT hr = effect->SetTechnique(m_hTechnique[shader]);
	if (FAILED(hr))
	{
//		DXTRACE_ERR("settech",hr);
	}

	UINT passKosuu0 = 0;
	hr = effect->Begin(&passKosuu0,0);
	int passKosuu = passKosuu0;


	effect->BeginPass(0);
	CMyDirect3D::DrawPolygonZ(dstPoint,srcPoint,lpZ,4);
	effect->EndPass();
	effect->End();


#else

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

		xor eax,eax
		movd mm0,eax
		punpcklwd mm0,mm0

		mov eax,clipY1
		mov edx,lPitch
		mul edx
		add eax,dst
		mov edi,eax







		mov ecx,loopY
		mov ebx,table

		mov eax,transFlag
		cmp eax,0
		jz MODE0
//		cmp eax,1
//		jz MODE1
//		jmp MODE2

MODE0:




LOOP1:
		push ebx
		push ecx
		push edi

		mov eax, [ebx]
		add eax, addY
		cmp eax, sy
		jnb SKIP2

		mov edx, sx
		shl edx, 2
		mul edx
		add eax, src
		mov esi, eax

		//mask
		mov eax, [ebx]
		add eax, addY

		mov edx, sx
//		shl edx, 2
		mul edx
		add eax, mask
		mov ecx, eax




		mov eax,[ebx+4]
		movd mm2,eax
		mov edx,screenSizeX
		shr edx,1
		mul edx
		mov edx,addX
		shl edx,16
		sub edx,eax
		movd mm1,edx

		mov ebx,ecx

		mov ecx,loopX
LOOP2:
		movq mm7,mm1
		psrad mm7,16
		movd edx,mm7

		cmp edx,sx
		jnb SKIP1
//表示?
		mov eax,transFlag
		cmp eax,2
		jb NORMAL


		xor eax,eax
		mov al,[edx+ebx]
		movd mm3,eax
		punpcklwd mm3, mm3
		punpckldq mm3, mm3
		xor al,0xff
		movd mm4, eax
		punpcklwd mm4, mm4
		punpckldq mm4, mm4

		shl edx, 2
		mov eax, [edx + esi]
		movd mm5,eax
		punpcklbw mm5,mm0
		pmullw mm3,mm5

		mov eax, [edi]
		movd mm5, eax
		punpcklbw mm5, mm0
		pmullw mm4, mm5

		paddw mm4,mm3
		psrlw mm4,8
		packuswb mm4,mm4
		movd eax,mm4
		mov[edi], eax

		jmp SKIP1
NORMAL:
		shl edx,2
		mov eax,[edx+esi]
		mov [edi],eax

SKIP1:
		paddd mm1,mm2

		add edi,4
		dec ecx
		jnz LOOP2
SKIP2:

		pop edi
		pop ecx
		pop ebx
		add edi,lPitch
		add ebx,4*2
		dec ecx
		jnz LOOP1

		jmp EXIT1


/*

MODE1:
LOOP11:
		push ecx
		push edi

		movq mm1,mm0


		movq mm6,mm1
		psrad mm6,16
		movd eax,mm6
		cmp eax,sy
		jnb SKIP12
		mov edx,sx
		mul edx
		shl eax,2
		add eax,src
		mov esi,eax


		mov ecx,loopX
LOOP12:
		movq mm7,mm1
		psrlq mm7,48

		movd ebx,mm7

		cmp ebx,sx
		jnb SKIP11
//表示?
		shl ebx,2
		mov eax,[ebx+esi]
		cmp eax,trans
		jz SKIP11
		mov [edi],eax

SKIP11:
		paddd mm1,mm2

		add edi,4
		dec ecx
		jnz LOOP12
SKIP12:
		paddd mm0,mm3

		pop edi
		pop ecx
		add edi,lPitch
		dec ecx
		jnz LOOP11

		jmp EXIT1


MODE2:

LOOP21:
		push ecx
		push edi

		movq mm1,mm0


		movq mm6,mm1
		psrad mm6,16
		movd eax,mm6
		cmp eax,sy
		jnb SKIP22
		mov edx,sx
		mul edx
		shl eax,2
		add eax,src
		mov esi,eax


		movd eax,mm6
		mov edx,sx
		mul edx
		add eax,mask
		mov edx,eax

		mov ecx,loopX
LOOP22:
		movq mm7,mm1
		psrlq mm7,48

		movd ebx,mm7

		cmp ebx,sx
		jnb SKIP21
//表示?
		xor eax,eax
		mov al,[ebx+edx]
		shl ebx,2
		or eax,eax
		jz SKIP21
		cmp eax,0ffh
		jz NORMAL2
//半透明
		movd mm7,eax
		punpcklwd mm7,mm7
		xor al,0ffh
		punpckldq mm7,mm7
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6

		pxor mm4,mm4

		mov eax,[ebx+esi]
		movd mm5,eax

		punpcklbw mm5,mm4
		pmullw mm7,mm5

		mov eax,[edi]
		movd mm5,eax
		punpcklbw mm5,mm4

		pmullw mm6,mm5

		psrlw mm7,8
		psrlw mm6,8
		paddw mm7,mm6
		packuswb mm7,mm4

		movd eax,mm7
		mov [edi],eax
		jmp SKIP21

NORMAL2:
		mov eax,[ebx+esi]
		mov [edi],eax


SKIP21:
		paddd mm1,mm2

		add edi,4
		dec ecx
		jnz LOOP22
SKIP22:

		paddd mm0,mm3


		pop edi
		pop ecx
		add edi,lPitch
		dec ecx
		jnz LOOP21
*/

		jmp EXIT1


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


#endif

}




BOOL CEffectPers::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}
