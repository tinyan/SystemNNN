//
// effectHamon.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "..\nyanEffectEtcLib\effectGet.h"


#include "effectHamon.h"

//#define HAMON_KYORI_MAX 800


#define HAMON_BUNKATSU 32
//かならず偶数



CEffectHamon::CEffectHamon(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	m_clipY1 = -666;

	m_sizeY1 = 1;
	m_clipX1 = -666;
	m_sizeX1 = 1;


	m_vector = NULL;
	m_vectorAdjusted = NULL;
	m_vectorMakedFlag = FALSE;
	m_vectorCenterX = screenSizeX / 2;
	m_vectorCenterY = screenSizeY / 2;

#if defined _WIN64
	m_hamonKyoriMax = int(sqrt(((double)((long long)screenSizeX * screenSizeX + (long long)screenSizeY * screenSizeY))) + 1);
#else
	m_hamonKyoriMax = int(sqrt(((double)(screenSizeX * screenSizeX + screenSizeY * screenSizeY))) + 1);
#endif

	m_table = new int[m_hamonKyoriMax];
	


//	m_calcuTable = new int[(screenSizeX/HAMON_BUNKATSU+2) * (screenSizeY/HAMON_BUNKATSU+2) * 1];
//	m_calcuTable2 = new int[(screenSizeX/HAMON_BUNKATSU+2) * 1];
}

CEffectHamon::~CEffectHamon()
{
	End();
}

void CEffectHamon::End(void)
{
	DELETEARRAY(m_vector);
	DELETEARRAY(m_table);
//	DELETEARRAY(m_calcuTable);
//	DELETEARRAY(m_calcuTable2);
}

void CEffectHamon::InitParameter(LPVOID lpEffect, int layer)
{
	int para[32];
	EFFECT* lp = (EFFECT*)lpEffect;
	for (int i=0;i<32;i++)
	{
		para[i] = lp->para[i];
	}
	SetParam(lp,32,para,layer);
}

BOOL CEffectHamon::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	if (m_vector == NULL)
	{
		int asx = (screenSizeX + 3) & ~3;

			
#if defined _WIN64
		m_vector = new int[((long long)asx * screenSizeY * 3) / 2 + 8];
		long long pt = (long long)m_vector;
#else
		m_vector = new int[(asx * screenSizeY * 3) / 2 + 8];
		int pt = (int)m_vector;
#endif
		pt += 31;
		pt &= ~31;
		m_vectorAdjusted = (int*)pt;
	}


	EFFECT* lp = (EFFECT*)lpEffect;

	int para[32];
	int k = paraKosuu;
	if (k>32) k = 32;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;	//frame

	if (paraKosuu<2) para[1] = 0;	//pic2	-1は1まいできりかえず
	
	if (paraKosuu<3) para[2] = screenSizeX / 2;	//x
	if (paraKosuu<4) para[3] = screenSizeY / 2;	//y

	if (paraKosuu<5) para[4] = 20;	//power
	if (paraKosuu<6) para[5] = 30;	//波長
	if (paraKosuu<7) para[6] = 10;	//速度
	if (paraKosuu<8) para[7] = 8;	//位相速度
	if (paraKosuu<9) para[8] = 100;	//減衰率

	if (paraKosuu<10) para[9] = 100;//*扁平率
	if (paraKosuu<11) para[10] = 0;	//*表示開始Y

	if (paraKosuu<12) para[11] = 0;	//overrap wait
	if (paraKosuu<13) para[12] = 100;//維持

	if (paraKosuu < 14) para[13] = 0;//subType
	if (paraKosuu < 15) para[14] = 0;//subFrame
	if (paraKosuu < 16) para[15] = 0;//もとget
	if (paraKosuu < 17) para[16] = 0;//さきget


	if (para[5]<1) para[5] = 1;
	if (para[6]<1) para[6] = 1;
	if (para[8]<0) para[8] = 0;
	if (para[8]>100) para[8] = 100;

	if (para[9]<1) para[9] = 1;
	if (para[10]<0) para[10] = 0;
	if (para[10]>=screenSizeY) para[10] = screenSizeY - 1;


//	if (paraKosuu<11) para[10] = 0;	//初期化しない


	lp->flag = TRUE;
	lp->command = EFFECT_HAMON;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<32;i++)
	{
		lp->para[i] = para[i];
	}

	//make vector table
	if ((m_vectorCenterX != para[2]) || (m_vectorCenterY != para[3])) m_vectorMakedFlag = FALSE;
	if (m_clipY1 != para[10]) m_vectorMakedFlag = FALSE;

	int hamonKyoriMax = m_hamonKyoriMax;
	int hamonKyoriMax1 = hamonKyoriMax - 1;

	int* ptr = m_vectorAdjusted;
	if (m_vectorMakedFlag == FALSE)
	{
		m_vectorCenterX = para[2];
		m_vectorCenterY = para[3];
		m_clipY1 = para[10];

		m_sizeY1 = screenSizeY - m_clipY1;

		for (int y=0;y<screenSizeY;y++)
		{
#if defined _WIN64
			double yy = (double)((long long)y - para[3]);
			int y_2 = ((long long)y-para[3]) * ((long long)y-para[3]);
#else
			double yy = (double)(y - para[3]);
			int y_2 = (y - para[3]) * (y - para[3]);
#endif

			for (int x=0;x<screenSizeX;x+=4)
			{
				int rr0 = (x - para[2])*(x-para[2]) + y_2;
				int rr1 = (x - para[2]+1)*(x-para[2]+1) + y_2;
				int rr2 = (x - para[2]+2)*(x-para[2]+2) + y_2;
				int rr3 = (x - para[2]+3)*(x-para[2]+3) + y_2;

				if (rr0<1) rr0 = 1;
				if (rr1<1) rr1 = 1;
				if (rr2<1) rr2 = 1;
				if (rr3<1) rr3 = 1;

#if defined _WIN64
				double xx0 = (double)((long long)x - para[2]);
				double xx1 = (double)((long long)x - para[2] +1);
				double xx2 = (double)((long long)x - para[2] +2);
				double xx3 = (double)((long long)x - para[2] +3);
#else
				double xx0 = (double)(x - para[2]);
				double xx1 = (double)(x - para[2] + 1);
				double xx2 = (double)(x - para[2] + 2);
				double xx3 = (double)(x - para[2] + 3);
#endif

				double r0 = sqrt((double)rr0);
				double r1 = sqrt((double)rr1);
				double r2 = sqrt((double)rr2);
				double r3 = sqrt((double)rr3);
				
				double dx0 = (xx0 * 256.0) / r0;
				double dy0 = (yy * 256.0) / r0;
				double dx1 = (xx1 * 256.0) / r1;
				double dy1 = (yy * 256.0) / r1;
				double dx2 = (xx1 * 256.0) / r2;
				double dy2 = (yy * 256.0) / r2;
				double dx3 = (xx1 * 256.0) / r3;
				double dy3 = (yy * 256.0) / r3;

				int x0 = (int)(dx0+0.5);
				int y0 = (int)(dy0+0.5);

				int x1 = (int)(dx1+0.5);
				int y1 = (int)(dy1+0.5);

				int x2 = (int)(dx2+0.5);
				int y2 = (int)(dy2+0.5);

				int x3 = (int)(dx3+0.5);
				int y3 = (int)(dy3+0.5);

				int dr0 = (int)(r0 + 0.5);
				int dr1 = (int)(r1 + 0.5);
				int dr2 = (int)(r2 + 0.5);
				int dr3 = (int)(r3 + 0.5);

				if (dr0<1) dr0 = 1;
				if (dr1<1) dr1 = 1;
				if (dr2<1) dr2 = 1;
				if (dr3<1) dr3 = 1;
				if (dr0>=hamonKyoriMax1) dr0 = hamonKyoriMax1;
				if (dr1>=hamonKyoriMax1) dr1 = hamonKyoriMax1;
				if (dr2>=hamonKyoriMax1) dr2 = hamonKyoriMax1;
				if (dr3>=hamonKyoriMax1) dr3 = hamonKyoriMax1;

				//dummy@@@@@@@@@@@@@@@@@@
				//単位ベクトル4つ
				*ptr = ((y0<<16) & 0xffff0000) | (x0 & 0xffff);
				ptr++;
				*ptr = ((y1<<16) & 0xffff0000) | (x1 & 0xffff);
				ptr++;
				*ptr = ((y2<<16) & 0xffff0000) | (x2 & 0xffff);
				ptr++;
				*ptr = ((y3<<16) & 0xffff0000) | (x3 & 0xffff);
				ptr++;

				//距離*sizeof(int)4つ
				*ptr = ((dr1<<2)<<16) | ((dr0<<2) & 0xffff);
				ptr++;
				*ptr = ((dr3<<2)<<16) | ((dr2<<2) & 0xffff);
				ptr++;
			}
		}




		m_vectorMakedFlag = TRUE;
	}


	return TRUE;
}


BOOL CEffectHamon::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectHamon::BeginPrint(LPVOID para,int layer)
{

}

void CEffectHamon::Init(LPVOID para,int layer)
{
}

void CEffectHamon::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectHamon::Print(LPVOID lpEffect,int layer)
{
	if (m_vector == NULL) return;

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

	int frame = lp->para[0];	//フレーム
	int nextPic = lp->para[1];	//nextPic (-1 to 15)
	int centerX = lp->para[2];
	int centerY = lp->para[3];
	double power = (double)(lp->para[4]);
	int rambda = lp->para[5];	//波長
	int speed = lp->para[6];	//速度
	int omega = lp->para[7];	//位相速度
	double down = (double)(lp->para[8]);		//減衰値x100
	double ab = (double)(lp->para[9]);		//扁平率
	int printStartY = lp->para[10];

	int overrapWait = lp->para[11];
	int iji = lp->para[12];



	int subType = lp->para[13];
	int subFrame = lp->para[14];
	c = CCalcuSpeed::calcu(c,frame,0,frame,subFrame,subType);

//	if (paraKosuu < 16) para[15] = 0;//もとget
//	if (paraKosuu < 17) para[16] = 0;//さきget



	ab *= 0.01;

	power -= ((double)c) * (down * 0.01);
	if (power<0.0) power = 0.0;


	//calcuTable
	int nx = screenSizeX / HAMON_BUNKATSU;
	int ny = screenSizeY / HAMON_BUNKATSU;

	if ((nx<1) || (ny<1)) return;

/*
	for (int j=0;j<ny+2;j++)
	{
		int yy = j * HAMON_BUNKATSU - centerY;

		for (int i=0;i<nx+2;i++)
		{
			int xx = i * HAMON_BUNKATSU - centerX;
			int rr = xx*xx + yy*yy;
			if (rr<0) rr = 0;
			double r = sqrt((double)rr);

			r *= 1.0;
			if (r>HAMON_KYORI_MAX-1) r = HAMON_KYORI_MAX-1;

			*(m_calcuTable+(i+j*(nx+2))*1) = (int)(r + 0.5);
		}
	}
*/


	int lim1 = 10;
	int lim2 = lim1 + iji;

	int hamonKyoriMax = m_hamonKyoriMax;

	for (int i=0;i<hamonKyoriMax;i++)
	{
		int d = 0;
		int k = c * speed - i;
		double pw = 0.0;

		if ((k>=0) && (k<lim2))
		{
			if (k<lim1)
			{
				pw = (power * k) / lim1;
			}
			else if (k<lim2)
			{
#if defined _WIN64
				pw = (power * ((long long)lim2 - k)) / ((long long)lim2 - lim1);
#else
				pw = (power * (lim2 - k)) / (lim2 - lim1);
#endif

			}

			int n = (c * (-omega) + i) % rambda;
			double th = (double)n;
			th *= 3.14159*2;
			th /= rambda;

			double dd = cos(th) * pw + 0.5;
			d = (int)dd;
			d *= 256;
			d &= 0xffff;
		}

		*(m_table + i) = (d<<16) | d;
	}




	int lPitch = screenSizeX * 4;

	int loopX = screenSizeX;
	int loopY = screenSizeY;

	int tableYAdd = (nx+2)*sizeof(int)*1;

//	int* calcuTable = m_calcuTable;
//	int* calcuTable2 = m_calcuTable2;
	int* table = m_table;

	CPicture* lpPic;
	CPicture* lpPic2;

	int pic = lp->pic;
	if (lp->para[15] == 0)
	{
		if (pic == -1) return;
		lpPic = m_allEffect->GetPicture(layer);
	}
	else
	{
		lpPic = CEffectGet::m_effectGetBufferPicture;
	}


	if (nextPic == -1)
	{
		//dummy
		lpPic2 = lpPic;
	}
	else
	{
		lpPic2 = m_allEffect->GetPicture(nextPic);
	}

	if (lp->para[16])
	{
		lpPic2 = CEffectGet::m_effectGetBufferPicture;
	}

	if (nextPic == -1)
	{
		lpPic2 = lpPic;
	}

	if (lpPic == NULL) return;
	if (lpPic2 == NULL) return;

	int* src1 = lpPic->GetPictureBuffer();
	if (src1 == NULL) return;

	int* src2 = lpPic2->GetPictureBuffer();
	if (src2 == NULL) return;



	RECT rcStart;
//	RECT rcEnd;

	rcStart = lp->dst;

//	rcEnd = m_effect->m_effect[nextPic].dst;
	POINT rcEndPoint = m_allEffect->GetDstPoint(nextPic);	

	int deltaX1 = -rcStart.left;
	int deltaY1 = -rcStart.top;
//	int deltaX2 = -rcEnd.left;
//	int deltaY2 = -rcEnd.top;
	int deltaX2 = -rcEndPoint.x;
	int deltaY2 = -rcEndPoint.y;

	RECT rc;
	lpPic->GetPicSize(&rc);
	int picSizeX1 = rc.right;
	int picSizeY1 = rc.bottom;

	if (picSizeX1<1) return;
	if (picSizeY1<1) return;

	RECT rc2;
	lpPic2->GetPicSize(&rc2);
	int picSizeX2 = rc2.right;
	int picSizeY2 = rc2.bottom;

	if (picSizeX2<1) return;
	if (picSizeY2<1) return;

	int srcPitch1 = picSizeX1 * 4;
	int srcPitch2 = picSizeX2 * 4;

	int tmpX = 0;
	int tmpY = 0;

	int tmpDeltaX = 0;
	int tmpDeltaY = 0;


	int dv2 = dv - overrapWait;
	if (dv2<1) dv2 = 1;

	int ps1 = 256;
	int ps2 = 0;

	if (c>=overrapWait)
	{
		int cc = c - overrapWait;

		ps1 = ((((dv2 - cc) * 100) / dv2) * 256) / 100;
		ps2 = (((cc * 100) / dv2) * 256) / 100;
	}

	if (m_vectorAdjusted == nullptr) return;


	int* vectorTable = m_vectorAdjusted;

	int asx = (screenSizeX + 3) & ~3;
	int tablePitch = asx / 4 * sizeof(int) * 6;

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


		mov eax,ps1
		movd mm5,eax
		punpcklwd mm5,mm5
		punpckldq mm5,mm5

		mov eax,ps2
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6


		mov esi,vectorTable
		mov edi,dst
		mov ecx,0

LOOP1:
		push ecx
		push esi
		push edi

			mov tmpY,ecx

			mov ecx,0
LOOP2:
			push ecx

			
				test ecx,2
				jnz SKIP1
				movq mm1,[esi]
				mov ebx,[esi+16]
				jmp SKIP2
SKIP1:
				movq mm1,[esi+8]
				mov ebx,[esi+20]
				add esi,24
SKIP2:
				mov edx,ebx
				mov ecx,table
		
				and ebx,0ffffh
				shr edx,16
		


				mov eax,[ebx+ecx]
				movd mm2,eax
				mov eax,[edx+ecx]
				movd mm3,eax
				psllq mm3,32
				por mm2,mm3




				pmulhw mm1,mm2

			pop ecx

			push ecx
			push esi

				pxor mm3,mm3
				pxor mm4,mm4


				movq mm7,mm1
				psllq mm7,16
				psrad mm7,16
				movd eax,mm7
				add eax,ecx
				add eax,deltaX1
				cmp eax,picSizeX1
				jnb SKIP3
				shl eax,2
				mov esi,eax

				movq mm7,mm1
				psrad mm7,16
				movd eax,mm7
				add eax,tmpY
				add eax,deltaY1
				cmp eax,picSizeY1
				jnb SKIP3

				mov edx,srcPitch1
				mul edx
				add esi,eax

				add esi,src1
				mov eax,[esi]
				movd mm3,eax

SKIP3:

		
				movq mm7,mm1
				psllq mm7,16
				psrad mm7,16
		//		psrlq mm7,32
				movd eax,mm7
				add eax,ecx
				add eax,deltaX2
				cmp eax,picSizeX2
				jnb SKIP4
				shl eax,2
				mov esi,eax

				movq mm7,mm1
				psrad mm7,16
		//		psrlq mm7,32
				movd eax,mm7
				add eax,tmpY
				add eax,deltaY2
				cmp eax,picSizeY2
				jnb SKIP4

				mov edx,srcPitch2
				mul edx
				add esi,eax

				add esi,src2
				mov eax,[esi]
				movd mm4,eax
SKIP4:




				pxor mm0,mm0

				punpcklbw mm3,mm0
				pmullw mm3,mm5

				punpcklbw mm4,mm0
				pmullw mm4,mm6

				paddw mm3,mm4
				psrlw mm3,8
				packuswb mm3,mm0
				movd eax,mm3
				mov [edi],eax



				pxor mm3,mm3
				pxor mm4,mm4


				movq mm7,mm1
				psllq mm7,16
				psrad mm7,16
				psrlq mm7,32
				movd eax,mm7
				add eax,ecx
				inc eax
				add eax,deltaX1
				cmp eax,picSizeX1
				jnb SKIP5
				shl eax,2
				mov esi,eax

				movq mm7,mm1
				psrad mm7,16
				psrlq mm7,32
				movd eax,mm7
				add eax,tmpY
				add eax,deltaY1
				cmp eax,picSizeY1
				jnb SKIP5

				mov edx,srcPitch1
				mul edx
				add esi,eax

				add esi,src1
				mov eax,[esi]
				movd mm3,eax
SKIP5:



				movq mm7,mm1
				psllq mm7,16
				psrad mm7,16
				psrlq mm7,32
				movd eax,mm7
				add eax,ecx
				inc eax
				add eax,deltaX2
				cmp eax,picSizeX2
				jnb SKIP6
				shl eax,2
				mov esi,eax

				movq mm7,mm1
				psrad mm7,16
				psrlq mm7,32
				movd eax,mm7
				add eax,tmpY
				add eax,deltaY2
				cmp eax,picSizeY2
				jnb SKIP6

				mov edx,srcPitch2
				mul edx
				add esi,eax

				add esi,src2
				mov eax,[esi]
				movd mm4,eax
SKIP6:

				pxor mm0,mm0

				punpcklbw mm3,mm0
				pmullw mm3,mm5

				punpcklbw mm4,mm0
				pmullw mm4,mm6

				paddw mm3,mm4
				psrlw mm3,8
				packuswb mm3,mm0
				movd eax,mm3
				mov [edi+4],eax

			pop esi
			pop ecx
		
			add edi,8
			add ecx,2
			cmp ecx,screenSizeX
			jb LOOP2


		pop edi
		pop esi
		pop ecx

		add esi,tablePitch
		add edi,lPitch
		inc ecx
		cmp ecx,screenSizeY
		jnz LOOP1

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



BOOL CEffectHamon::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}
