//
// effectTurn.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectTurn.h"


CEffectTurn::CEffectTurn(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(1);
	SetPercentKosuu(1);
	Create("Turn");
#endif
}

CEffectTurn::~CEffectTurn()
{
	End();
}

void CEffectTurn::End(void)
{
}

BOOL CEffectTurn::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[36];
	int k = paraKosuu;
	if (k>36) k = 36;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}




	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 0;	//th1	‰ñ“]end
	if (paraKosuu<3) para[2] = para[1];	//th2	‰ñ“]start
	if (paraKosuu<4) para[3] = 0;	//‰ñ“]’†SdeltaX
	if (paraKosuu<5) para[4] = 0;	//‰ñ“]’†SdeltaY
	if (paraKosuu<7) para[5] = 100;	//Šg‘åk¬1			
	if (paraKosuu<8) para[6] = para[5];	//Šg‘åk¬2			
	
	if (paraKosuu<6) para[7] = 0;	//“§‰ßƒtƒ‰ƒO		
	if (paraKosuu<9) para[8] = 100;	//tranEnd
	if (paraKosuu<10) para[9] = para[8];//transStart

	if (paraKosuu<11) para[10] = 0;	//‰ñ“]speedType
	if (paraKosuu<12) para[11] = 0;	//‰ñ“]subframe

	if (paraKosuu<13) para[12] = 0;	//Šg‘åspeedType
	if (paraKosuu<14) para[13] = 0;	//Šg‘åsubframe
	
	if (paraKosuu<15) para[14] = 0;	//“§‰ßspeedType
	if (paraKosuu<16) para[15] = 0;	//“§‰ßsubframe
	

	if (paraKosuu < 17) para[16] = 0;//coloraddsubflag
	if (paraKosuu<18) para[17] = 0;	//end r
	if (paraKosuu<19) para[18] = para[17];	//end g
	if (paraKosuu<20) para[19] = para[18];	//end b

	if (paraKosuu<21) para[20] = para[17];	//start r
	if (paraKosuu<22) para[21] = para[18];	//start g
	if (paraKosuu<23) para[22] = para[19];	//start b


	if (paraKosuu<24) para[23] = 0;	//type
	if (paraKosuu<25) para[24] = 0;	//subframe

	if (paraKosuu < 26) para[25] = 0;//sprineflag
	if (paraKosuu<27) para[26] = 0;
	if (paraKosuu<28) para[27] = 0;
	if (paraKosuu<29) para[28] = 200;
	if (paraKosuu<30) para[29] = -100;
	if (paraKosuu<31) para[30] = 300;
	if (paraKosuu<32) para[31] = -200;
	if (paraKosuu<33) para[32] = 400;
	if (paraKosuu<34) para[33] = 100;
	
	if (paraKosuu < 35) para[34] = 0;
	if (paraKosuu < 36) para[35] = 0;







//	if (paraKosuu<9) para[8] = 0;	//‘Î”“IŒvŽZ				Šg’£—p
	//max 9 pattern


	lp->flag = TRUE;
	lp->command = EFFECT_TURN;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<36;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectTurn::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectTurn::BeginPrint(LPVOID para,int layer)
{

}

void CEffectTurn::Init(LPVOID para,int layer)
{
}

void CEffectTurn::Calcu(LPVOID lpEffect,int layer)
{
}

#if defined _TINYAN3DLIB_
void CEffectTurn::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int count = lp->count;
	int countMax = lp->countMax;
	
	int turnType = lp->para[10];
	int turnSubFrame = lp->para[11];
	int multiType = lp->para[12];
	int multiSubFrame = lp->para[13];
	int transType = lp->para[14];
	int transSubFrame = lp->para[15];
	
	int th1 = lp->para[2];
	int th2 = lp->para[1];
	int dx = lp->para[3];
	int dy = lp->para[4];

	int multi1 = lp->para[6];
	int multi2 = lp->para[5];

	int transFlag = lp->para[7];
	int transStart = lp->para[9];
	int transEnd = lp->para[8];

	int multi = CCalcuSpeed::calcu(count,countMax,multi1*10,multi2*10,multiSubFrame,multiType) / 10;
	if (multi<1) multi = 1;

	int transPercent = CCalcuSpeed::calcu(count,countMax,transStart,transEnd,transSubFrame,transType);

	int pic = lp->pic;
	if (pic == -1) return;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	RECT rc;
	lpPic->GetPicSize(&rc);

	int sx = rc.right;
	int sy = rc.bottom;

	if ((sx<1) || (sy<1)) return;


	int* src = (int*)(lpPic->GetBuffer());
	if (src == NULL) return;

	char* mask = lpPic->GetMaskPic();


	int cx = sx / 2;
	int cy = sy / 2;

	cx += dx;
	cy += dy;

	int th = CCalcuSpeed::calcu(count,countMax,th1*10,th2*10,turnSubFrame,turnType);
//	int th = th1 + ((th2 - th1) * c ) / dv;

	if (th<0)
	{
		th *= -1;
		if (th>=3600)
		{
			th %= 3600;
		}
		th *= -1;
		th += 3600;
	}

	if (th>=3600)
	{
		th %= 3600;
	}

	double kaitenTh = (double)th;
	kaitenTh *= (3.14159*2 / 3600.0);
	kaitenTh *= -1.0;

	int zX = lp->dst.left;
	int zY = lp->dst.top;


	float cosTH = (float)(cos(kaitenTh));
	float sinTH = (float)(sin(kaitenTh));


	cosTH *= (float)multi;
	cosTH /= 100.0;

	sinTH *= (float)multi;
	sinTH /= 100.0;



	float putX0[4];
	float putY0[4];
	putX0[0] = (float)(- sx/2 - dx );
	putY0[0] = (float)(- sy/2 - dy );
	putX0[1] = (float)(- sx/2 - dx );
	putY0[1] = (float)(  sy/2 - dy );
	putX0[2] = (float)(  sx/2 - dx );
	putY0[2] = (float)(  sy/2 - dy );
	putX0[3] = (float)(  sx/2 - dx );
	putY0[3] = (float)(- sy/2 - dy );

	POINT srcPoint[4];
	srcPoint[0].x = 0;
	srcPoint[0].y = 0;
	srcPoint[1].x = 0;
	srcPoint[1].y = sy;
	srcPoint[2].x = sx;
	srcPoint[2].y = sy;
	srcPoint[3].x = sx;
	srcPoint[3].y = 0;


	CMyTexture* lpTexture = (CMyTexture*)(lpPic->GetTexture());
	if (lpTexture == NULL) return;
	SetTexture(lpTexture->GetTexture());

	float ps = 100.0f;
	if (transFlag == 2)
	{
		ps = (float)transPercent;
		ps /= 100.0f;
	}


	SetPercent(ps);

	POINT dstPoint[4];
	for (int i=0;i<4;i++)
	{
		float x = putX0[i];
		float y = putY0[i];
		float xx = x * cosTH - y * sinTH;
		float yy = x * sinTH + y * cosTH;
		dstPoint[i].x = (int)(xx+0.5f);
		dstPoint[i].y = (int)(yy+0.5f);
		dstPoint[i].x += zX;
		dstPoint[i].y += zY;

		dstPoint[i].x += sx / 2;		//Žd—l‚Æ‚µ‚Ä‚Í‚Ö‚ñ‚¾‚ªA2D‚ÌŽd—l‚É‚ ‚í‚¹‚é
		dstPoint[i].y += sy / 2;
	//	dstPoint[i].x -= dx;
	//	dstPoint[i].y -= dy;
	}
//char mes[256];
//wsprintf(mes,"dx=%d dy=%d th=%d ml=%d putX=%d putY=%d\n",dx,dy,th,multi,dstPoint[0].x,dstPoint[0].y);
//OutputDebugString(mes);
	PrintPolygon(dstPoint,srcPoint,4);

	return;


}
#else

void CEffectTurn::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int count = lp->count;
	int countMax = lp->countMax;
	
	int turnType = lp->para[10];
	int turnSubFrame = lp->para[11];
	int multiType = lp->para[12];
	int multiSubFrame = lp->para[13];
	int transType = lp->para[14];
	int transSubFrame = lp->para[15];
	
	int th1 = lp->para[2];
	int th2 = lp->para[1];
	int dx = lp->para[3];
	int dy = lp->para[4];

	int multi1 = lp->para[6];
	int multi2 = lp->para[5];

	int transFlag = lp->para[7];
	int transStart = lp->para[9];
	int transEnd = lp->para[8];

	int transPercent = CCalcuSpeed::calcu(count,countMax,transStart,transEnd,transSubFrame,transType);
	int transPercent256 = (256*transPercent) / 100;


	int multi = CCalcuSpeed::calcu(count,countMax,multi1*10,multi2*10,multiSubFrame,multiType) / 10;
	if (multi<1) multi = 1;

	int addsubtype = lp->para[23];
	int addsubsubFrame = lp->para[24];

	int r1 = lp->para[20];
	int g1 = lp->para[21];
	int b1 = lp->para[22];

	int r2 = lp->para[17];
	int g2 = lp->para[18];
	int b2 = lp->para[19];

	int r = CCalcuSpeed::calcu(count,countMax,r1,r2,addsubsubFrame,addsubtype);
	int g = CCalcuSpeed::calcu(count,countMax,g1,g2,addsubsubFrame,addsubtype);
	int b = CCalcuSpeed::calcu(count,countMax,b1,b2,addsubsubFrame,addsubtype);

	int addColorR = r;
	int addColorG = g;
	int addColorB = b;

	int subColorR = -r;
	int subColorG = -g;
	int subColorB = -b;

	if (addColorR<0) addColorR = 0;
	if (addColorG<0) addColorG = 0;
	if (addColorB<0) addColorB = 0;
	if (subColorR<0) subColorR = 0;
	if (subColorG<0) subColorG = 0;
	if (subColorB<0) subColorB = 0;


	int colorAddSubFlag = lp->para[16];


	int pic = lp->pic;
	if (pic == -1) return;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	RECT rc;
	lpPic->GetPicSize(&rc);

	int sx = rc.right;
	int sy = rc.bottom;

	if ((sx<1) || (sy<1)) return;


	int* src = (int*)(lpPic->GetBuffer());
	if (src == NULL) return;

	char* mask = lpPic->GetMaskPic();


	int cx = sx / 2;
	int cy = sy / 2;

	cx += dx;
	cy += dy;

	int th = CCalcuSpeed::calcu(count,countMax,th1*10,th2*10,turnSubFrame,turnType);
//	int th = th1 + ((th2 - th1) * c ) / dv;

	if (th<0)
	{
		th *= -1;
		if (th>=3600)
		{
			th %= 3600;
		}
		th *= -1;
		th += 3600;
	}

	if (th>=3600)
	{
		th %= 3600;
	}

	double kaitenTh = (double)th;
	kaitenTh *= (3.14159*2 / 3600.0);

	int zX = lp->dst.left;
	int zY = lp->dst.top;

	int sprineFlag = lp->para[25];

	if ((sprineFlag == 2) || (sprineFlag == 3))
	{
		int spSubType = lp->para[34];
		int spSubFrame = lp->para[35];

		float x1 = (float)(lp->para[26]);
		float y1 = (float)(lp->para[27]);
		float x2 = (float)(lp->para[28]);
		float y2 = (float)(lp->para[29]);
		float x3 = (float)(lp->para[30]);
		float y3 = (float)(lp->para[31]);
		float x4 = (float)(lp->para[32]);
		float y4 = (float)(lp->para[33]);

		int s = CCalcuSpeed::calcu(count,countMax,0,10000,spSubFrame,spSubType);

		float t = (float)s;
		t *= 0.0001f;

		if (sprineFlag == 3)
		{
			float t3 = t*t*t;
			float t2 = t*t*(1.0f-t);
			float t1 = t*(1.0f-t)*(1.0f-t);
			float t0 = (1.0f-t)*(1.0f-t)*(1.0f-t);

			float sprx = t0*x1 + 3.0f*t1*x2 + 3.0f*t2*x3 + t3*x4;
			float spry = t0*y1 + 3.0f*t1*y2 + 3.0f*t2*y3 + t3*y4;

			zX += (int)(sprx+0.5f);
			zY += (int)(spry+0.5f);
		}
		else
		{
			float t2 = t*t;
			float t1 = t*(1.0f-t);
			float t0 = (1.0f-t)*(1.0f-t);

			float sprx = t0*x1 + 2.0f*t1*x2 + t2*x3;
			float spry = t0*y1 + 2.0f*t1*y2 + t2*y3;

			zX += (int)(sprx+0.5f);
			zY += (int)(spry+0.5f);
		}
	}


	double cosTH = cos(kaitenTh);
	double sinTH = sin(kaitenTh);


	cosTH /= (double)multi;
	cosTH *= 100.0;

	sinTH /= (double)multi;
	sinTH *= 100.0;





	double pX = (double)(sx / 2 + dx);
	double pY = (double)(sy / 2 + dy);



	double x = 0;
	double y = 0.0;

	double mx = (double)(screenSizeX / 2);
	double my = (double)(screenSizeY / 2);


	x = 0.0 - (mx + zX);
	y = 0.0 - (my + zY);
	double x0 = cosTH * x - sinTH * y + pX;
	double y0 = sinTH * x + cosTH * y + pY;

	x = (double)screenSizeX - (mx + zX);
	y = 0.0 - (my + zY);
	double x1 = cosTH * x - sinTH * y + pX;
	double y1 = sinTH * x + cosTH * y + pY;

	x = 0.0 - (mx + zX);
	y = (double)screenSizeY - (my + zY);
	double x2 = cosTH * x - sinTH * y + pX;
	double y2 = sinTH * x + cosTH * y + pY;

	x = (double)screenSizeX - (mx + zX);
	y = (double)screenSizeY - (my + zY);
	double x3 = cosTH * x - sinTH * y + pX;
	double y3 = sinTH * x + cosTH * y + pY;

	x0 += 0.5;
	y0 += 0.5;
	x1 += 0.5;
	y1 += 0.5;
	x2 += 0.5;
	y2 += 0.5;
	x3 += 0.5;
	y3 += 0.5;


	double ddx = (x1 - x0) / ((double)screenSizeX);
	double ddy = (y1 - y0) / ((double)screenSizeX);

	double ddx2 = (x2 - x0) / ((double)screenSizeY);
	double ddy2 = (y2 - y0) / ((double)screenSizeY);


	double ml = 65536.0;

	int ddxInt = (int)ddx;
	int ddxAmari = 0;
	if (ddx>=0)
	{
		ddxAmari = (int)((ddx - ddxInt) * ml);
	}
	else
	{
		ddxInt--;
		ddxAmari = (int)((ddx - ddxInt) * ml);
	}

	int ddyInt = (int)ddy;
	int ddyAmari = 0;
	if (ddy>=0)
	{
		ddyAmari = (int)((ddy - ddyInt) * ml);
	}
	else
	{
		ddyInt--;
		ddyAmari = (int)((ddy - ddyInt) * ml);
	}


	int ddx2Int = (int)ddx2;
	int ddx2Amari = 0;
	if (ddx2>=0)
	{
		ddx2Amari = (int)((ddx2 - ddx2Int) * ml);
	}
	else
	{
		ddx2Int--;
		ddx2Amari = (int)((ddx2 - ddx2Int) * ml);
	}

	int ddy2Int = (int)ddy2;
	int ddy2Amari = 0;
	if (ddy2>=0)
	{
		ddy2Amari = (int)((ddy2 - ddy2Int) * ml);
	}
	else
	{
		ddy2Int--;
		ddy2Amari = (int)((ddy2 - ddy2Int) * ml);
	}



	int lPitch = screenSizeX * 4;
	int maskPitch = sx;


	int tmpX = (int)(x0);
	int tmpAmariX;
	if (x0>=0)
	{
		tmpAmariX = (int)((x0 - tmpX) * ml);
	}
	else
	{
		tmpX--;
		tmpAmariX = (int)((x0 - tmpX) * ml);
	}

	int tmpY = (int)(y0);
	int tmpAmariY;
	if (y0>=0)
	{
		tmpAmariY = (int)((y0 - tmpY) * ml);
	}
	else
	{
		tmpY--;
		tmpAmariY = (int)((y0 - tmpY) * ml);
	}

	int tmpX2 = tmpX;
	int tmpAmariX2 = tmpAmariX;
	int tmpY2 = tmpY;
	int tmpAmariY2 = tmpAmariY;

	int trans = *src;


	if (transFlag == 2)
	{
		if (mask == NULL) transFlag = 1;
		if (lpPic->CheckMaskExist() == FALSE) transFlag = 1;
	}


	int addColor = (addColorR << 16) | (addColorG << 8) | addColorB;
	int subColor = (subColorR << 16) | (subColorG << 8) | subColorB;
	LONGLONG addColor64 = (LONGLONG)addColor;
	LONGLONG subColor64 = (LONGLONG)subColor;


	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi



		mov eax,tmpAmariX
		and eax,0ffffh
		mov ebx,tmpX
		shl ebx,16
		or eax,ebx
		movd mm0,eax

		psllq mm0,32

		mov eax,tmpAmariY
		and eax,0ffffh
		mov ebx,tmpY
		shl ebx,16
		or eax,ebx
		movd mm7,eax

		por mm0,mm7





		mov eax,ddxAmari
		and eax,0ffffh
		mov ebx,ddxInt
		shl ebx,16
		or eax,ebx
		movd mm2,eax

		psllq mm2,32

		mov eax,ddyAmari
		and eax,0ffffh
		mov ebx,ddyInt
		shl ebx,16
		or eax,ebx
		movd mm7,eax

		por mm2,mm7




		mov eax,ddx2Amari
		and eax,0ffffh
		mov ebx,ddx2Int
		shl ebx,16
		or eax,ebx
		movd mm3,eax

		psllq mm3,32

		mov eax,ddy2Amari
		and eax,0ffffh
		mov ebx,ddy2Int
		shl ebx,16
		or eax,ebx
		movd mm7,eax

		por mm3,mm7


//		mov eax,16
//		movd mm4,eax
//		mov eax,48
//		movd mm5,eax


		mov esi,src
		mov edi,dst

		mov ecx,screenSizeY


		mov eax,transFlag
		cmp eax,0
		jz MODE0
		cmp eax,1
		jz MODE1
		jmp MODE2

MODE0:
LOOP1:
		push ecx
		push edi

		movq mm1,mm0

		mov ecx,screenSizeX
LOOP2:
		movq mm6,mm1
		movq mm7,mm1
		psrad mm6,16
		psrlq mm7,48

		movd edx,mm6
		movd ebx,mm7

		cmp ebx,sx
		jnb SKIP1
		cmp edx,sy
		jnb SKIP1
//•\Ž¦?
		mov eax,sx
		mul edx
		add ebx,eax
		shl ebx,2
		mov eax,[ebx+esi]
		push edx
		mov edx,colorAddSubFlag
		or edx,edx
		pop edx
		jz NOTADDSUB0
		
		movd mm4,eax
		paddusb mm4,addColor64
		psubusb mm4,subColor64
		movd eax,mm4

NOTADDSUB0:
		mov [edi],eax

SKIP1:
		paddd mm1,mm2

		add edi,4
		dec ecx
		jnz LOOP2

		paddd mm0,mm3


		pop edi
		pop ecx
		add edi,lPitch
		dec ecx
		jnz LOOP1

		jmp EXIT1



MODE1:
LOOP11:
		push ecx
		push edi

		movq mm1,mm0

		mov ecx,screenSizeX
LOOP12:
		movq mm6,mm1
		movq mm7,mm1
		psrad mm6,16
		psrlq mm7,48

		movd edx,mm6
		movd ebx,mm7

		cmp ebx,sx
		jnb SKIP11
		cmp edx,sy
		jnb SKIP11
//•\Ž¦?
		mov eax,sx
		mul edx
		add ebx,eax
		shl ebx,2
		mov eax,[ebx+esi]
		cmp eax,trans
		jz SKIP11

		push edx
		mov edx,colorAddSubFlag
		or edx,edx
		pop edx
		jz NOTADDSUB1
		
		movd mm4,eax
		paddusb mm4,addColor64
		psubusb mm4,subColor64
		movd eax,mm4

NOTADDSUB1:

		mov [edi],eax

SKIP11:
		paddd mm1,mm2

		add edi,4
		dec ecx
		jnz LOOP12

		paddd mm0,mm3


		pop edi
		pop ecx
		add edi,lPitch
		dec ecx
		jnz LOOP11

		jmp EXIT1


MODE2:

		mov edx,mask
LOOP21:
		push ecx
		push edx
		push edi

		movq mm1,mm0

		mov ecx,screenSizeX
LOOP22:
		movq mm6,mm1
		movq mm7,mm1
		psrad mm6,16
		psrlq mm7,48

		movd eax,mm6
		movd ebx,mm7

		cmp ebx,sx
		jnb SKIP21
		cmp eax,sy
		jnb SKIP21
//•\Ž¦?
		push edx
		mul dword ptr sx
		pop edx
		add ebx,eax
		xor eax,eax
		mov al,[ebx+edx]
		shl ebx,2
		or eax,eax
		jz SKIP21
//		cmp eax,0ffh
//		jz NORMAL2
//”¼“§–¾
		movd mm7,eax
		mov eax,transPercent256
		movd mm6,eax
		pmullw mm7,mm6
		psrlw mm7,8
		movd eax,mm7
		cmp al,0ffh
		jz NORMAL2

		punpcklwd mm7,mm7
		punpckldq mm7,mm7
		mov eax,01000100h
		movd mm6,eax
		punpckldq mm6,mm6
		psubw mm6,mm7


		mov eax,[ebx+esi]

		push edx
		mov edx,colorAddSubFlag
		or edx,edx
		pop edx
		jz NOTADDSUB2
		
		movd mm4,eax
		paddusb mm4,addColor64
		psubusb mm4,subColor64
		movd eax,mm4

NOTADDSUB2:


		pxor mm4,mm4
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

		push edx
		mov edx,colorAddSubFlag
		or edx,edx
		pop edx
		jz NOTADDSUB2B
		
		movd mm4,eax
		paddusb mm4,addColor64
		psubusb mm4,subColor64
		movd eax,mm4

NOTADDSUB2B:

		mov [edi],eax


SKIP21:
		paddd mm1,mm2

		add edi,4
		dec ecx
		jnz LOOP22

		paddd mm0,mm3


		pop edi
		pop edx
		pop ecx
		add edi,lPitch
		dec ecx
		jnz LOOP21

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





/*
	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		mov eax,ddxAmari
		shl eax,8
		mov ddxAmari,eax

		mov eax,ddyAmari
		shl eax,8
		mov ddyAmari,eax
		
		mov eax,ddx2Amari
		shl eax,8
		mov ddx2Amari,eax

		mov eax,ddy2Amari
		shl eax,8
		mov ddy2Amari,eax

		mov eax,tmpAmariX
		shl eax,8
		mov tmpAmariX,eax

		mov eax,tmpAmariY
		shl eax,8
		mov tmpAmariY,eax

		mov eax,tmpAmariX2
		shl eax,8
		mov tmpAmariX2,eax

		mov eax,tmpAmariY2
		shl eax,8
		mov tmpAmariY2,eax

		mov esi,src
		mov edi,dst

		mov ecx,screenSizeY
LOOP1:
		push ecx
		push edi

		mov ecx,tmpX2
		mov tmpX,ecx
		mov ecx,tmpY2
		mov tmpY,ecx

		mov ecx,tmpAmariX2
		mov tmpAmariX,ecx
		mov ecx,tmpAmariY2
		mov tmpAmariY,ecx

		mov ecx,screenSizeX
LOOP2:
		mov ebx,ddxAmari
		add tmpAmariX,ebx
		mov ebx,ddxInt
		adc ebx,tmpX
		mov tmpX,ebx

		mov edx,ddyAmari
		add tmpAmariY,edx
		mov edx,ddyInt
		adc edx,tmpY
		mov tmpY,edx

		cmp ebx,sx
		jnb SKIP1
		cmp edx,sy
		jnb SKIP1
//•\Ž¦?
		mov eax,sx
		mul edx
		add ebx,eax
		shl ebx,2
		mov eax,[ebx+esi]
		mov [edi],eax

SKIP1:
		add edi,4
		dec ecx
		jnz LOOP2


		mov ecx,ddx2Amari
		add tmpAmariX2,ecx
		mov edi,ddx2Int
		adc tmpX2,edi

		mov ecx,ddy2Amari
		add tmpAmariY2,ecx
		mov edi,ddy2Int
		adc tmpY2,edi

		pop edi
		pop ecx
		add edi,lPitch
		dec ecx
		jnz LOOP1

//		pckhdw mm1,mm2

		emms

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
*/


}
#endif



BOOL CEffectTurn::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}
