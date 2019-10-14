//
// BGZoomIn.cpp
//

#include "..\nyanEffectLib\includer.h"

//#include "calcuSpeed.h"
#include "effectBGZoomIn.h"


CEffectBGZoomIn::CEffectBGZoomIn(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(1);
	Create("BGZoomIn");
#endif

}

CEffectBGZoomIn::~CEffectBGZoomIn()
{
	End();
}

void CEffectBGZoomIn::End(void)
{
}

BOOL CEffectBGZoomIn::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[9];
	int k = paraKosuu;
	if (k>9) k = 9;
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


	lp->flag = TRUE;
	lp->command = EFFECT_BGZOOMIN;
	lp->countMax = para[0];
	lp->count = 0;


	for (i=0;i<9;i++)
	{
		lp->para[i] = para[i];
	}


	return TRUE;
}


BOOL CEffectBGZoomIn::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectBGZoomIn::BeginPrint(LPVOID para,int layer)
{

}

void CEffectBGZoomIn::Init(LPVOID para,int layer)
{
}

void CEffectBGZoomIn::Calcu(LPVOID lpEffect,int layer)
{
}

#if defined _TINYAN3DLIB_
void CEffectBGZoomIn::Print(LPVOID lpEffect,int layer)
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

void CEffectBGZoomIn::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int* dst = CMyGraphics::GetScreenBuffer();
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

	int dltX = ((x2 - x1) * 65536) / sizeX;
	int dltY = ((y2 - y1) * 65536) / sizeY;

	int* screen = CMyGraphics::GetScreenBuffer();



	int pic = lp->pic;
	if (pic == -1) return;

	RECT rc;
	RECT rc0;
	SetRect(&rc0,0,0,sizeX,sizeY);
//	m_game->m_picture[pic]->GetPicSize(&rc);

	CPicture* lpPic = m_allEffect->GetPicture(layer);	//debug 2005-05-08
	lpPic->GetPicSize(&rc);
	if (!EqualRect(&rc,&rc0)) return;

	if (lpPic->Check256()) return;

	int* srcPtr = lpPic->GetPictureBuffer();

	srcPtr += x1;
	srcPtr += y1 * sizeX;

//	int amariX = 0x8000;
//	int amariY = 0x8000;

	int amariX = 0;
	int amariY = 0;

//	dltX = 0;
//	dltY = 0;

	int srcPitch = sizeX * 4;
	int dstPitch = sizeX * 4;

#if defined _WIN64
#pragma message("‚±‚±‚Éc++ŽÀ‘•‚ª•K—v‚É‚á " __FILE__)

#else

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		mov esi,srcPtr
		mov edi,screen

		mov edx,sizeY
LOOP1:
		push edx
		push esi
		push edi
;

		mov edx,amariX
		mov ebx,dltX
		mov ecx,sizeX
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
;
		pop edi
		pop esi

		mov eax,amariY
		and eax,0ffffh
		add eax,dltY
		mov amariY,eax
		shr eax,16
		mov edx,srcPitch
		mul edx
		add esi,eax

		pop edx
		add edi,dstPitch
		dec edx
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


BOOL CEffectBGZoomIn::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}

