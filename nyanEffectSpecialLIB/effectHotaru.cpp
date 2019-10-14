//
// effectHotaru.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectHotaru.h"


#define HOTARU_KOSUU_MAX 600
#define HOTARU_SCALE 256

CEffectHotaru::CEffectHotaru(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(2);
	Create("Hotaru");
	m_hotaruPic = new CPicture(8,8);
#endif

	m_hotaru = new HOTARU[HOTARU_KOSUU_MAX];
	m_lightTable = new int[8*8*2+7];

	m_setX = 600;
	m_setY = 300;
	m_setSizeX = 100;
	m_setSizeY = 100;
	m_speedX = -100;
	m_speedY = 10;
	m_loopFlag = 0;
	m_yure = 15;

	for (int i=0;i<HOTARU_KOSUU_MAX;i++)
	{
		SetNewHotaru(i);
	}
}


CEffectHotaru::~CEffectHotaru()
{
	End();
}

void CEffectHotaru::End(void)
{
	DELETEARRAY(m_hotaru);
	DELETEARRAY(m_lightTable);
#if defined _TINYAN3DLIB_
	ENDDELETECLASS(m_hotaruPic);
#endif
}



void CEffectHotaru::InitParameter(LPVOID lpEffect, int layer)
{
	int para[20];
	EFFECT* lp = (EFFECT*)lpEffect;
	for (int i=0;i<20;i++)
	{
		para[i] = lp->para[i];
	}
	SetParam(lp,20,para,layer);
}



BOOL CEffectHotaru::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int para[20];
	int k = paraKosuu;
	if (k>20) k = 20;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;	//frame
	
	if (paraKosuu<2) para[1] = 100;	//個数

	if (paraKosuu<3) para[2] = screenSizeX;	//setx
	if (paraKosuu<4) para[3] = screenSizeY-180;	//sety
	if (paraKosuu<5) para[4] = 100;	//sizeX
	if (paraKosuu<6) para[5] = 100;	//sizeY

	if (paraKosuu<7) para[6] = 100;	//speedx
	if (paraKosuu<8) para[7] = 100;	//speedy

	if (paraKosuu<9) para[8] = 255;	//r
	if (paraKosuu<10) para[9] = 255;	//g
	if (paraKosuu<11) para[10] = 255;	//b

	if (paraKosuu<12) para[11] = 0;	//loop flag
	if (paraKosuu<13) para[12] = 0;	//not init flag

	if (paraKosuu<14) para[13] = 0;	//work start number
	if (paraKosuu<15) para[14] = 100;	//半透明終了

	if (paraKosuu<16) para[15] = 15;	//ゆれ周期	1-??
	if (para[15]<1) para[15] = 1;
	if (paraKosuu<17) para[16] = -1;		//ゆれ角度
	if (paraKosuu<18) para[17] = 20;		//ゆれはば

	if (para[4]<1) para[4] = 1;
	if (para[5]<1) para[5] = 1;


	if ((para[13]+para[1]) > HOTARU_KOSUU_MAX)
	{
		para[13] = HOTARU_KOSUU_MAX-para[1];
	}

	lp->flag = TRUE;
	lp->command = EFFECT_HOTARU;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<20;i++)
	{
		lp->para[i] = para[i];
	}

	if (para[12] == 0)
	{
		m_setX = para[2];
		m_setY = para[3];
		m_setSizeX = para[4];
		m_setSizeY = para[5];
		m_speedX = para[6];
		m_speedY = para[7];
		m_loopFlag = para[11];
		m_yure = para[15];
		m_yureKakudo = para[16];
		m_yureHaba = para[17];
		CalcuYureCosSin();
		for (int i=para[13];i<para[13]+para[1];i++)
		{
			SetNewHotaru(i);
		}
	}

	return TRUE;
}


BOOL CEffectHotaru::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectHotaru::BeginPrint(LPVOID para,int layer)
{

}

void CEffectHotaru::Init(LPVOID para,int layer)
{
}

void CEffectHotaru::Calcu(LPVOID lpEffect,int layer)
{
}

#if defined _TINYAN3DLIB_
void CEffectHotaru::Print(LPVOID lpEffect,int layer)
{
	int shader = 0;

	EFFECT* lp = (EFFECT*)lpEffect;

	int dv = lp->countMax;
	int c = lp->count;

	if (dv<1)
	{
		dv = 1;
	}

//	if (c>=dv) return;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int* dst = CMyGraphics::GetScreenBuffer();




	m_setX = lp->para[2];
	m_setY = lp->para[3];
	m_setSizeX = lp->para[4];
	m_setSizeY = lp->para[5];

	m_speedX = lp->para[6];
	m_speedY = lp->para[7];
	m_loopFlag = lp->para[11];

	m_yure = lp->para[15];
	m_yureKakudo = lp->para[16];
	m_yureHaba = lp->para[17];

	CalcuYureCosSin();

	int picSizeX = 8;
	int picSizeY = 8;

	int leftDot = picSizeX / 2;
	int rightDot = picSizeX - leftDot;
	int upDot = picSizeY / 2;
	int downDot = picSizeY - upDot;

	m_screenClipX1 = leftDot;
	m_screenClipY1 = upDot;
	m_screenClipX2 = screenSizeX - rightDot;
	m_screenClipY2 = screenSizeY - downDot;

	int st = lp->para[12];
	int kosuu = lp->para[1];

	if ((st+kosuu) > HOTARU_KOSUU_MAX)
	{
		kosuu = HOTARU_KOSUU_MAX - st;
	}
	if (kosuu<1) return;

	CalcuHotaru(st,kosuu);

	//print

	int clipX1 = m_screenClipX1;
	int clipY1 = m_screenClipY1;
	int clipX2 = m_screenClipX2;
	int clipY2 = m_screenClipY2;

//	int ps1 = lp->para[15];
//	int ps2 = lp->para[14];
//	int ps = ps1 + ((ps2 - ps1) * c + dv / 2) /dv;
//	if (ps<0) ps = 0;
//	if (ps>100) ps = 100;
//	if (ps==0) return;

	int workSize = sizeof(HOTARU);
	void* work = m_hotaru;

	int startOffset = st;

	int lPitch = screenSizeX * sizeof(int);
	int col1 = 0xffffff;
	int col2 = 0x7f7f7f;



	int pt = (int)m_lightTable;
	pt += 31;
	pt &= ~31;
	int* lightTable = (int*)pt;

//	int minusData[] = {71,56,50,50,56,71,0,0, 56,35,25,25,35,56,0,0, 50,25,0,0,25,50,0,0, 50,25,0,0,25,50,0,0, 56,35,25,25,35,56,0,0, 71,56,50,50,56,71,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,};

	int r0 = lp->para[8];
	int g0 = lp->para[9];
	int b0 = lp->para[10];

	int ps1 = 100;
	int ps = ps1 + ((lp->para[14] - ps1) * c) / dv;
	if (ps<0) ps = 0;
	if (ps>100) ps = 100;

	unsigned int* ptr = (unsigned int*)(m_hotaruPic->GetBuffer());


	for (int i=0;i<64;i++)
	{
		int xx = i % 8;
		int yy = i / 8;

		int x = (xx-4)*2 + 1;
		int y = (yy-4)*2 + 1;


		double rr = sqrt((double)(x*x+y*y));
		if (rr == 0.0) rr = 0.01;

		int mm = (int)(rr*rr *2 );






		int addColR = 0;
		int addColG = 0;
		int addColB = 0;
		int subColR = 0;
		int subColG = 0;
		int subColB = 0;

		if (r0>=0)
		{
			int r = ((r0 - mm)*ps)/100;
			if (r<0) r = 0;
			if (r>255) r = 255;
			addColR = r;
		}
		else
		{
			int r = ((-r0 - mm)*ps)/100;
			if (r<0) r = 0;
			if (r>255) r = 255;
			subColR = r;
		}

		if (g0>=0)
		{
			int g = ((g0 - mm)*ps)/100;
			if (g<0) g = 0;
			if (g>255) g = 255;
			addColG = g;
		}
		else
		{
			int g = ((-g0 - mm)*ps)/100;
			if (g<0) g = 0;
			if (g>255) g = 255;
			subColG = g;
		}

		if (b0>=0)
		{
			int b = ((b0 - mm)*ps)/100;
			if (b<0) b = 0;
			if (b>255) b = 255;
			addColB = b;
		}
		else
		{
			int b = ((-b0 - mm)*ps)/100;
			if (b<0) b = 0;
			if (b>255) b = 255;
			subColB = b;
		}

//		if (i==1) addColR = 255;

		/*
		if (aaa==10)
		{
			char mes[256];
			wsprintf(mes,"[%d %d %d %d %d %d]",addColR,addColG,addColB,subColR,subColG,subColB);
			OutputDebugString(mes);
			if ((i % 8) == 0)
			{
				OutputDebugString("\n");
			}
		}
*/


		addColR -= subColR;
		addColR /= 2;
		addColR += 128;
		addColG -= subColG;
		addColG /= 2;
		addColG += 128;
		addColB -= subColB;
		addColB /= 2;
		addColB += 128;

		unsigned int col = (addColR << 16) | (addColG << 8) | (addColB);
		col |= 0xff000000;

		*(ptr+32+i) = col;



//		int addCol = (addColR << 16) | (addColG<<8) | addColB;
//		int subCol = (subColR << 16) | (subColG<<8) | subColB;
//
//		int dlt = i % 2;
//
//		*(lightTable+(i & ~1)*2+dlt) = addCol;
//		*(lightTable+(i & ~1)*2+dlt+2) = subCol;
	}

/*
	static int aaa = 0;
	if (aaa == 0)
	{
		aaa = 1;
		for (int j=0;j<64;j++)
		{
			char mes[256];
			wsprintf(mes,"[%d]",0xffffff & (*(ptr+32+j)));
			OutputDebugString(mes);
		}
	}
*/

	CMyTexture* lpTexture = (CMyTexture*)(m_hotaruPic->GetTexture());
	lpTexture->CreateTexture(ptr);

	if (CheckEffectError()) return;

	POINT getPoint;
	getPoint.x = 0;
	getPoint.y = 0;
	SIZE getSize;
	getSize.cx = screenSizeX;
	getSize.cy = screenSizeY;
	CMyDirect3D::GetScreenToBuffer(getPoint,getSize);

	//get screen



	SetTexture(GetBufferTexture());
	SetTexture(lpTexture->GetTexture(),1);



	LPD3DXEFFECT effect = m_d3dxEffect;
	if (effect == NULL) return;
	SetAllColor();
	SetAllPercent();
	SetAllConst();
	SetAllTexture();

	if (m_hTechnique == NULL)
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


	int* work2 = (int*)m_hotaru;
	work2 += (sizeof(HOTARU) / sizeof(int)) * st;


	int clipX = screenSizeX - leftDot - rightDot;
	int clipY = screenSizeY - upDot - downDot;

	int a1 = 0;
	int a2 = 0;
	int a3 = 0;

	for (int i=0;i<passKosuu;i++)
	{
		effect->BeginPass(i);


		POINT srcPoint2;
		srcPoint2.x = 0;
		srcPoint2.y = 0;
		SIZE dstSize;
		dstSize.cx = 8;
		dstSize.cy = 8;

		for (int j=0;j<kosuu;j++)
		{
			if ((*(work2+5)) != 0)
			{
				a1++;

				int xx = *(work2+0);
				xx /= 256;
				int yy = *(work2+1);
				yy /= 256;

				xx -= leftDot;
				yy -= upDot;

				if ((xx>=0) && (yy>=0))
				{
					a2++;

					if ((xx<clipX) && (yy<clipY))
					{
						a3++;

						POINT dstPoint;
						dstPoint.x = xx;
						dstPoint.y = yy;
						POINT srcPoint;
						srcPoint.x = xx;
						srcPoint.y = yy;
						CMyDirect3D::Blt2(dstPoint,dstSize,srcPoint,srcPoint2);
					}
				}
			}
			work2 += 6;
		}

		effect->EndPass();
	}

	effect->End();

//	char mes[256];
//	wsprintf(mes,"[flgok=%d xyok1 = %d xyok2=%d kosuu=%d]\n",a1,a2,a3,kosuu);
//	OutputDebugString(mes);

	return;

}
#else

void CEffectHotaru::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int dv = lp->countMax;
	int c = lp->count;

	if (dv<1)
	{
		dv = 1;
	}

//	if (c>=dv) return;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int* dst = CMyGraphics::GetScreenBuffer();




	m_setX = lp->para[2];
	m_setY = lp->para[3];
	m_setSizeX = lp->para[4];
	m_setSizeY = lp->para[5];

	m_speedX = lp->para[6];
	m_speedY = lp->para[7];
	m_loopFlag = lp->para[11];

	m_yure = lp->para[15];
	m_yureKakudo = lp->para[16];
	m_yureHaba = lp->para[17];

	CalcuYureCosSin();

	int picSizeX = 8;
	int picSizeY = 8;

	int leftDot = picSizeX / 2;
	int rightDot = picSizeX - leftDot;
	int upDot = picSizeY / 2;
	int downDot = picSizeY - upDot;

	m_screenClipX1 = leftDot;
	m_screenClipY1 = upDot;
	m_screenClipX2 = screenSizeX - rightDot;
	m_screenClipY2 = screenSizeY - downDot;

	int st = lp->para[12];
	int kosuu = lp->para[1];

	if ((st+kosuu) > HOTARU_KOSUU_MAX)
	{
		kosuu = HOTARU_KOSUU_MAX - st;
	}
	if (kosuu<1) return;

	CalcuHotaru(st,kosuu);

	//print

	int clipX1 = m_screenClipX1;
	int clipY1 = m_screenClipY1;
	int clipX2 = m_screenClipX2;
	int clipY2 = m_screenClipY2;

//	int ps1 = lp->para[15];
//	int ps2 = lp->para[14];
//	int ps = ps1 + ((ps2 - ps1) * c + dv / 2) /dv;
//	if (ps<0) ps = 0;
//	if (ps>100) ps = 100;
//	if (ps==0) return;

	int workSize = sizeof(HOTARU);
	void* work = m_hotaru;

	int startOffset = st;

	int lPitch = screenSizeX * sizeof(int);
	int col1 = 0xffffff;
	int col2 = 0x7f7f7f;


#if defined _WIN64
	long long pt = (long long)m_lightTable;
#else
	int pt = (int)m_lightTable;
#endif
	pt += 31;
	pt &= ~31;
	int* lightTable = (int*)pt;

//	int minusData[] = {71,56,50,50,56,71,0,0, 56,35,25,25,35,56,0,0, 50,25,0,0,25,50,0,0, 50,25,0,0,25,50,0,0, 56,35,25,25,35,56,0,0, 71,56,50,50,56,71,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,};

	int r0 = lp->para[8];
	int g0 = lp->para[9];
	int b0 = lp->para[10];

	int ps1 = 100;
	int ps = ps1 + ((lp->para[14] - ps1) * c) / dv;
	if (ps<0) ps = 0;
	if (ps>100) ps = 100;

	for (int i=0;i<64;i++)
	{
		int xx = i % 8;
		int yy = i / 8;

		int x = (xx-4)*2 + 1;
		int y = (yy-4)*2 + 1;


		double rr = sqrt((double)(x*x+y*y));
		if (rr == 0.0) rr = 0.01;

		int mm = (int)(rr*rr *2 );


		int addColR = 0;
		int addColG = 0;
		int addColB = 0;
		int subColR = 0;
		int subColG = 0;
		int subColB = 0;

		if (r0>=0)
		{
			int r = ((r0 - mm)*ps)/100;
			if (r<0) r = 0;
			if (r>255) r = 255;
			addColR = r;
		}
		else
		{
			int r = ((-r0 - mm)*ps)/100;
			if (r<0) r = 0;
			if (r>255) r = 255;
			subColR = r;
		}

		if (g0>=0)
		{
			int g = ((g0 - mm)*ps)/100;
			if (g<0) g = 0;
			if (g>255) g = 255;
			addColG = g;
		}
		else
		{
			int g = ((-g0 - mm)*ps)/100;
			if (g<0) g = 0;
			if (g>255) g = 255;
			subColG = g;
		}

		if (b0>=0)
		{
			int b = ((b0 - mm)*ps)/100;
			if (b<0) b = 0;
			if (b>255) b = 255;
			addColB = b;
		}
		else
		{
			int b = ((-b0 - mm)*ps)/100;
			if (b<0) b = 0;
			if (b>255) b = 255;
			subColB = b;
		}

		int addCol = (addColR << 16) | (addColG<<8) | addColB;
		int subCol = (subColR << 16) | (subColG<<8) | subColB;


		int dlt = i % 2;

		*(lightTable+(i & ~1)*2+dlt) = addCol;
		*(lightTable+(i & ~1)*2+dlt+2) = subCol;
	}





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

		mov esi,work
		mov eax,startOffset
		mov edx,workSize
		mul edx
		add esi,eax




		mov ecx,kosuu
LOOP1:
		push ecx

		mov eax,[esi+20]
		or eax,eax
		jz SKIP1

		movq mm0,[esi]
		psrad mm0,8
		movd eax,mm0
		cmp eax,clipX1
		js SKIP1
		cmp eax,clipX2
		jns SKIP1

		sub eax,leftDot

		shl eax,2
		mov edi,eax

		psrlq mm0,32
		movd eax,mm0
		cmp eax,clipY1
		js SKIP1
		cmp eax,clipY2
		jns SKIP1

		sub eax,upDot

		mov edx,lPitch
		mul edx
		add edi,eax

		add edi,dst

		mov ebx,lightTable
		mov ecx,picSizeY
LOOP2:
		movq mm0,[edi]
		movq mm1,[ebx]
		movq mm2,[ebx+8]

		movq mm3,[edi+8]
		movq mm4,[ebx+16]
		movq mm5,[ebx+24]

		paddusb mm0,mm1
		paddusb mm3,mm4
		psubusb mm0,mm2
		psubusb mm3,mm5

		movq [edi],mm0
		movq [edi+8],mm3


		movq mm0,[edi+16]
		movq mm1,[ebx+32]
		movq mm2,[ebx+40]

		movq mm3,[edi+24]
		movq mm4,[ebx+48]
		movq mm5,[ebx+56]

		paddusb mm0,mm1
		paddusb mm3,mm4
		psubusb mm0,mm2
		psubusb mm3,mm5

		movq [edi+16],mm0
		movq [edi+24],mm3

		add ebx,8*4*2
		add edi,lPitch
		dec ecx
		jnz LOOP2



SKIP1:
		pop ecx
		add esi,workSize
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
#endif

}
#endif



void CEffectHotaru::CalcuHotaru(int st, int kosuu)
{
	for (int i=st;i<st+kosuu;i++)
	{
		CalcuHotaruSub(i);
	}
}

void CEffectHotaru::CalcuHotaruSub(int n)
{
	if ((n<0) || (n>=HOTARU_KOSUU_MAX)) return;

	int thMax = m_hotaru[n].thMax;

	if (thMax == 0)
	{
		if (m_loopFlag)
		{
			SetNewHotaru(n);
			return;
		}
		else
		{
			return;
		}
	}

	int x = m_hotaru[n].x;
	int y = m_hotaru[n].y;
	int speedX = m_hotaru[n].speedX;
	int speedY = m_hotaru[n].speedY;

	x += speedX;
	y += speedY;

	//ふらふら移動??

	int th = m_hotaru[n].th;

	th++;
	if (th >= thMax)
	{
		th -= thMax;
	}
	m_hotaru[n].th = th;

	double th1 = (double)th;
	th1 *= 3.14159*2;
	th1 /= (double)thMax;

	double cosTH = cos(th1);
	cosTH *= (double)(m_yureHaba*HOTARU_SCALE);

	int deltaX = 0;
	int deltaY = 0;

	if (m_yureKakudo == -1)
	{
		int absSpeedX = speedX;
		if (absSpeedX<0) absSpeedX = -speedX;

		int absSpeedY = speedY;
		if (absSpeedY<0) absSpeedY = -speedY;
		
		if (absSpeedX>absSpeedY)
		{
			deltaY = (int)(cosTH * 0.2 + 0.5);
		}
		else
		{
			deltaX = (int)(cosTH * 0.2 + 0.5);
		}
	}
	else
	{
		deltaX = (int)(cosTH * m_yureCos + 0.5);
		deltaY = (int)(cosTH * m_yureSin + 0.5);
	}

	x += deltaX;
	y += deltaY;





	m_hotaru[n].x = x;
	m_hotaru[n].y = y;


	x /= HOTARU_SCALE;
	y /= HOTARU_SCALE;



	//outof area?
	if (speedX<0)
	{
		if (x<m_screenClipX1)
		{
			m_hotaru[n].thMax = 0;
			return;
		}
	}
	else
	{
		if (x>m_screenClipX2)
		{
			m_hotaru[n].thMax = 0;
			return;
		}
	}

	if (speedY<0)
	{
		if (y<m_screenClipY1)
		{
			m_hotaru[n].thMax = 0;
			return;
		}
	}
	else
	{
		if (y>m_screenClipY2)
		{
			m_hotaru[n].thMax = 0;
			return;
		}
	}
}


void CEffectHotaru::SetNewHotaru(int n)
{
	if ((n<0) || (n>=HOTARU_KOSUU_MAX)) return;

//	m_hotaru[n].x = m_setX + (rand() % (m_setSizeX*2)) - m_setSizeX / 2;
//	m_hotaru[n].y = m_setY + (rand() % (m_setSizeY*2)) - m_setSizeY / 2;
	m_hotaru[n].x = m_setX + (rand() % m_setSizeX);
	m_hotaru[n].y = m_setY + (rand() % m_setSizeY);
	m_hotaru[n].x *= HOTARU_SCALE;
	m_hotaru[n].y *= HOTARU_SCALE;


	
	int speedX = m_speedX * HOTARU_SCALE;
	int speedY = m_speedY * HOTARU_SCALE;
	int divX = speedX / 2;
	int divY = speedY / 2;
	if (divX<0) divX *= -1;
	if (divY<0) divY *= -1;
	if (divX<1) divX = 1;
	if (divY<1) divY = 1;
	speedX += (rand() % divX);
	speedY += (rand() % divY);
	speedX -= divX / 2;
	speedY -= divY / 2;

	m_hotaru[n].speedX = speedX;
	m_hotaru[n].speedY = speedY;

	int thMax = (rand() % (m_yure*4)) + m_yure;
	m_hotaru[n].thMax = thMax;
	m_hotaru[n].th = rand() % thMax;
}

void CEffectHotaru::CalcuYureCosSin(void)
{
	if (m_yureKakudo == -1)
	{
		m_yureCos = 0.2;	//用心
		m_yureSin = 0.0;
		return;
	}

	double th = (double)m_yureKakudo;
	th *= 3.14159*2;
	th /= 360.0;

	m_yureCos = 0.2 * cos(th);
	m_yureSin = 0.2 * sin(th);
}

/*_*/

