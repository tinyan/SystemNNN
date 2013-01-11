//
// 
//

#include <windows.h>
#if defined _TINYAN3DLIB_
#include <d3dx9.h>
#endif

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\allGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\areaControl.h"

#if defined _TINYAN3DLIB_
#include "..\..\systemNNN3D\nyanDirectX3DLib\commonShader.h"
#endif

#include "commonEffect.h"
#include "allEffect.h"

#include "effectList.h"

//nyaneffectanimelib
#include "..\nyanEffectAnimeLib\effectAnime.h"
#include "..\nyanEffectAnimeLib\effectFullAnime.h"
#include "..\nyanEffectAnimeLib\effectKomaAnime.h"
#include "..\nyanEffectAnimeLib\effectMepachiKuchipaku.h"

//nyanEffectCharaLib
#include "..\nyanEffectCharaLib\effectBossDeath.h"
#include "..\nyanEffectCharaLib\effectChange.h"
#include "..\nyanEffectCharaLib\effectCharaAddSub.h"
#include "..\nyanEffectCharaLib\effectCharaBokashi.h"
#include "..\nyanEffectCharaLib\effectCharaBure.h"
#include "..\nyanEffectCharaLib\effectCharaFlash.h"
#include "..\nyanEffectCharaLib\effectCharaGhost.h"
#include "..\nyanEffectCharaLib\effectCharaGrey.h"
#include "..\nyanEffectCharaLib\effectCharaMaskAppear.h"
#include "..\nyanEffectCharaLib\effectCharaRaster.h"
#include "..\nyanEffectCharaLib\effectCharaSepia.h"
#include "..\nyanEffectCharaLib\effectColorAddSub.h"
#include "..\nyanEffectCharaLib\effectColorBalance.h"
#include "..\nyanEffectCharaLib\effectCtrans.h"
#include "..\nyanEffectCharaLib\effectDualMask.h"
#include "..\nyanEffectCharaLib\effectMeisai.h"
#include "..\nyanEffectCharaLib\effectMove.h"
#include "..\nyanEffectCharaLib\effectNoise.h"
#include "..\nyanEffectCharaLib\effectRainbow.h"
#include "..\nyanEffectCharaLib\effectSaike.h"
#include "..\nyanEffectCharaLib\effectSpecialMove.h"
#include "..\nyanEffectCharaLib\effectTaClip.h"
#include "..\nyanEffectCharaLib\effectTrans.h"
#include "..\nyanEffectCharaLib\effectZantetsu.h"



//nyaneffectetclib
#include "..\nyanEffectEtcLib\effectBuffer.h"
#include "..\nyanEffectEtcLib\effectGet.h"
#include "..\nyanEffectEtcLib\effectMovieWarp.h"
#include "..\nyanEffectEtcLib\effectNop.h"
#include "..\nyanEffectEtcLib\effectOnce.h"
#include "..\nyanEffectEtcLib\effectPut.h"


//nyaneffectGeolib
#include "..\nyanEffectGeoLib\effectGeoBox.h"
#include "..\nyanEffectGeoLib\effectGeoBoxAdd.h"
#include "..\nyanEffectGeoLib\effectGeoCircle.h"
#include "..\nyanEffectGeoLib\effectGeoCircleAdd.h"
#include "..\nyanEffectGeoLib\effectGeoPolygon.h"
#include "..\nyanEffectGeoLib\effectGeoPolygonAdd.h"
#include "..\nyanEffectGeoLib\effectGeoTorus.h"
#include "..\nyanEffectGeoLib\effectGeoTorusAdd.h"

//nyaneffectlib
#include "effectMae.h"
#include "effectWaterDrop.h"
#include "effectSnow2.h"
#include "effectHae.h"
#include "effectLupin.h"

//nyaneffectMovelib
#include "..\nyanEffectMoveLib\effectBezierMove.h"
#include "..\nyanEffectMoveLib\effectBSpline2.h"

//nyaneffectNaturallib
#include "..\nyanEffectNaturalLib\effectBeach.h"
#include "..\nyanEffectNaturalLib\effectCloud.h"
#include "..\nyanEffectNaturalLib\effectFlower.h"
#include "..\nyanEffectNaturalLib\effectGrassPlane.h"
#include "..\nyanEffectNaturalLib\effecthaikeiYure.h"
#include "..\nyanEffectNaturalLib\effectKagerou.h"
#include "..\nyanEffectNaturalLib\effectRain.h"
#include "..\nyanEffectNaturalLib\effectRain2.h"
#include "..\nyanEffectNaturalLib\effectRain4.h"
#include "..\nyanEffectNaturalLib\effectSan.h"
#include "..\nyanEffectNaturalLib\effectShake.h"
#include "..\nyanEffectNaturalLib\effectSnow.h"
#include "..\nyanEffectNaturalLib\effectSoyosoyo.h"
#include "..\nyanEffectNaturalLib\effectTaiyo.h"
#include "..\nyanEffectNaturalLib\effectWater.h"
#include "..\nyanEffectNaturalLib\effectWaterFall.h"

//nyanEffectScreenLib
#include "..\nyanEffectScreenLib\effectBura.h"
#include "..\nyanEffectScreenLib\effectFadeIn.h"
#include "..\nyanEffectScreenLib\effectFadeOut.h"
#include "..\nyanEffectScreenLib\effectFill.h"
#include "..\nyanEffectScreenLib\effectFlash.h"
#include "..\nyanEffectScreenLib\effectGradation.h"
#include "..\nyanEffectScreenLib\effecthahen.h"
#include "..\nyanEffectScreenLib\effectLayerGrey.h"
#include "..\nyanEffectScreenLib\effectLayerSepia.h"
#include "..\nyanEffectScreenLib\effectLight.h"
#include "..\nyanEffectScreenLib\effectMeltDown.h"
#include "..\nyanEffectScreenLib\effectMozaic.h"
#include "..\nyanEffectScreenLib\effectNega.h"
#include "..\nyanEffectScreenLib\effectOldFilm.h"
#include "..\nyanEffectScreenLib\effectRaster.h"
#include "..\nyanEffectScreenLib\effectReleaf.h"
#include "..\nyanEffectScreenLib\effectSlash.h"
#include "..\nyanEffectScreenLib\effectSuna.h"

//nyanEffectSpecialLib
#include "..\nyanEffectSpecialLib\effectBathWindow.h"
#include "..\nyanEffectSpecialLib\effectBGBokashi.h"
#include "..\nyanEffectSpecialLib\effectBGZoomIn.h"
#include "..\nyanEffectSpecialLib\effectBokashi.h"
#include "..\nyanEffectSpecialLib\effectCharaMetal.h"
#include "..\nyanEffectSpecialLib\effectCircle.h"
#include "..\nyanEffectSpecialLib\effectClipZoomIn.h"
#include "..\nyanEffectSpecialLib\effectCurtain.h"
#include "..\nyanEffectSpecialLib\effectFish.h"
#include "..\nyanEffectSpecialLib\effectFusuma.h"
#include "..\nyanEffectSpecialLib\effectHanabira.h"
#include "..\nyanEffectSpecialLib\effectHotaru.h"
#include "..\nyanEffectSpecialLib\effectKe.h"
#include "..\nyanEffectSpecialLib\effectKira.h"
#include "..\nyanEffectSpecialLib\effectKomorebi.h"
#include "..\nyanEffectSpecialLib\effectKonoha.h"
#include "..\nyanEffectSpecialLib\effectOldLamp.h"
#include "..\nyanEffectSpecialLib\effectpoleScroll.h"
#include "..\nyanEffectSpecialLib\effectRemember.h"
#include "..\nyanEffectSpecialLib\effectScroll.h"
#include "..\nyanEffectSpecialLib\effectSentence.h"
#include "..\nyanEffectSpecialLib\effectSpeedLine.h"
#include "..\nyanEffectSpecialLib\effectStaffRoll.h"
#include "..\nyanEffectSpecialLib\effectTarget1.h"

//nyanEffectTransformLib
#include "..\nyanEffectTransformLib\effectPers.h"
#include "..\nyanEffectTransformLib\effectStretch.h"
#include "..\nyanEffectTransformLib\effectStretchBlt.h"
#include "..\nyanEffectTransformLib\effectTurn.h"

//nyanEffectWipeLib
#include "..\nyanEffectWipeLib\effectHamon.h"
#include "..\nyanEffectWipeLib\effectMaskWipe.h"
#include "..\nyanEffectWipeLib\effectMoveMaskWipe.h"
#include "..\nyanEffectWipeLib\simpleWipe.h"







#if defined _TINYAN3DLIB_
#include "..\..\systemNNN3D\nyanWipe3DLib\effectSimpleWipeCommon.h"
#else
#include "..\nyanWipeLib\effectSimpleWipeCommon.h"
#endif



BOOL CAllEffect::m_renzokuEffectFlag[256]=
{
	FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,
	FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,
	FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,
	FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,
};




CAllEffect::CAllEffect()
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int sz = screenSizeX;
	if (sz < screenSizeY) sz = screenSizeY;

	m_tempWork = new int[sz*8];


	m_effectKosuu = 256;
	m_ppEffects = new CCommonEffect* [m_effectKosuu];


	int i;
	for (i=0;i<EFFECT_SHURUI_MAX;i++)
	{
		m_ppEffects[i] = NULL;
	}

	m_ppEffects[EFFECT_ANIME] = new CEffectAnime(this);
	m_ppEffects[EFFECT_BATHWINDOW] = new CEffectBathWindow(this);
	m_ppEffects[EFFECT_BEACH] = new CEffectBeach(this);
	m_ppEffects[EFFECT_BEZIERMOVE] = new CEffectBezierMove(this);
	m_ppEffects[EFFECT_BGZOOMIN] = new CEffectBGZoomIn(this);	
	m_ppEffects[EFFECT_BOKASHI] = new CEffectBokashi(this);
	m_ppEffects[EFFECT_BOSSDEATH] = new CEffectBossDeath(this);
	m_ppEffects[EFFECT_BUFFER] = new CEffectBuffer(this);
	m_ppEffects[EFFECT_BURA] = new CEffectBura(this);
	m_ppEffects[EFFECT_CHANGE] = new CEffectChange(this);
	m_ppEffects[EFFECT_CHARAFLASH] = new CEffectCharaFlash(this);
	m_ppEffects[EFFECT_CIRCLE] = new CEffectCircle(this);
	m_ppEffects[EFFECT_CLOUD] = new CEffectCloud(this);
	m_ppEffects[EFFECT_COLORADDSUB] = new CEffectColorAddSub(this);
	m_ppEffects[EFFECT_CTRANS] = new CEffectCTrans(this);
	m_ppEffects[EFFECT_CURTAIN] = new CEffectCurtain(this);
	m_ppEffects[EFFECT_FADEIN] = new CEffectFadein(this);
	m_ppEffects[EFFECT_FADEOUT] = new CEffectFadeout(this);
	m_ppEffects[EFFECT_FILL] = new CEffectFill(this);
	m_ppEffects[EFFECT_FLASH] = new CEffectFlash(this);
	m_ppEffects[EFFECT_FLOWER] = new CEffectFlower(this);
	m_ppEffects[EFFECT_FULLANIME] = new CEffectFullAnime(this);
	m_ppEffects[EFFECT_FUSUMA] = new CEffectFusuma(this);
	m_ppEffects[EFFECT_GEOCIRCLE] = new CEffectGeoCircle(this);
	m_ppEffects[EFFECT_GEOPOLYGON] = new CEffectGeoPolygon(this);
	m_ppEffects[EFFECT_GEOTORUS] = new CEffectGeoTorus(this);
	m_ppEffects[EFFECT_GET] = new CEffectGet(this);
	m_ppEffects[EFFECT_GRADATION] = new CEffectGradation(this);
	m_ppEffects[EFFECT_GRASSPLANE] = new CEffectGrassPlane(this);
	m_ppEffects[EFFECT_HAHEN] = new CEffectHahen(this);
	m_ppEffects[EFFECT_HAIKEIYURE] = new CEffectHaikeiYure(this);
	m_ppEffects[EFFECT_HAMON] = new CEffectHamon(this);
	m_ppEffects[EFFECT_HANABIRA] = new CEffectHanabira(this);
	m_ppEffects[EFFECT_HOTARU] = new CEffectHotaru(this);
	m_ppEffects[EFFECT_KAGEROU] = new CEffectKagerou(this);
	m_ppEffects[EFFECT_KIRA] = new CEffectKira(this);
	m_ppEffects[EFFECT_KOMAANIME] = new CEffectKomaAnime(this);
	m_ppEffects[EFFECT_KOMOREBI] = new CEffectKomorebi(this);
	m_ppEffects[EFFECT_LIGHT] = new CEffectLight(this);
	m_ppEffects[EFFECT_MAE] = new CEffectMae(this);
	m_ppEffects[EFFECT_MASKWIPE] = new CEffectMaskWipe(this);
	m_ppEffects[EFFECT_MEISAI] = new CEffectMeisai(this);
	m_ppEffects[EFFECT_MELTDOWN] = new CEffectMeltDown(this);
	m_ppEffects[EFFECT_MEPACHIKUCHIPAKU] = new CEffectMePachiKuchiPaku(this);
	m_ppEffects[EFFECT_MOVE] = new CEffectMove(this);
	m_ppEffects[EFFECT_MOZAIC] = new CEffectMozaic(this);
	m_ppEffects[EFFECT_NEGA] = new CEffectNega(this);
	m_ppEffects[EFFECT_NOP] = new CEffectNop(this);
	m_ppEffects[EFFECT_OLDFILM] = new CEffectOldFilm(this);
	m_ppEffects[EFFECT_ONCE] = new CEffectOnce(this);
	m_ppEffects[EFFECT_PERS] = new CEffectPers(this);
	m_ppEffects[EFFECT_POLESCROLL] = new CEffectPoleScroll(this);
	m_ppEffects[EFFECT_PUT] = new CEffectPut(this);
	m_ppEffects[EFFECT_RAIN] = new CEffectRain(this);
	m_ppEffects[EFFECT_RAINBOW] = new CEffectRainbow(this);
	m_ppEffects[EFFECT_RASTER] = new CEffectRaster(this);
	m_ppEffects[EFFECT_RELEAF] = new CEffectReleaf(this);
	m_ppEffects[EFFECT_REMEMBER] = new CEffectRemember(this);
	m_ppEffects[EFFECT_SAN] = new CEffectSan(this);
	m_ppEffects[EFFECT_SCROLL] = new CEffectScroll(this);
	m_ppEffects[EFFECT_SHAKE] = new CEffectShake(this);
	m_ppEffects[EFFECT_SIMPLEWIPE] = new CEffectSimpleWipe(this);
	m_ppEffects[EFFECT_SLASH] = new CEffectSlash(this);
	m_ppEffects[EFFECT_SNOW] = new CEffectSnow(this);
	m_ppEffects[EFFECT_SOYOSOYO] = new CEffectSoyosoyo(this);
	m_ppEffects[EFFECT_SPECIALMOVE] = new CEffectSpecialMove(this);
	m_ppEffects[EFFECT_SPEEDLINE] = new CEffectSpeedLine(this);
	m_ppEffects[EFFECT_STAFFROLL] = new CEffectStaffRoll(this);
	m_ppEffects[EFFECT_STRETCH] = new CEffectStretch(this);
	m_ppEffects[EFFECT_STRETCHBLT] = new CEffectStretchBlt(this);
	m_ppEffects[EFFECT_SUNA] = new CEffectSuna(this);
	m_ppEffects[EFFECT_TAIYO] = new CEffectTaiyo(this);
	m_ppEffects[EFFECT_TRANS] = new CEffectTrans(this);
	m_ppEffects[EFFECT_TURN] = new CEffectTurn(this);
	m_ppEffects[EFFECT_WATER] = new CEffectWater(this);
	m_ppEffects[EFFECT_WATERDROP] = new CEffectWaterDrop(this);
	m_ppEffects[EFFECT_WATERFALL] = new CEffectWaterFall(this);
	m_ppEffects[EFFECT_ZANTETSU] = new CEffectZantetsu(this);
	m_ppEffects[EFFECT_MOVEMASKWIPE] = new CEffectMoveMaskWipe(this);
	m_ppEffects[EFFECT_RAIN2] = new CEffectRain2(this);
	m_ppEffects[EFFECT_SNOW2] = new CEffectSnow2(this);
	m_ppEffects[EFFECT_RAIN4] = new CEffectRain4(this);
	m_ppEffects[EFFECT_TARGET1] = new CEffectTarget1(this);
	m_ppEffects[EFFECT_KONOHA] = new CEffectKonoha(this);
	m_ppEffects[EFFECT_MOVIE_WARP] = new CEffectMovieWarp(this);
	m_ppEffects[EFFECT_NOISE] = new CEffectNoise(this);
	m_ppEffects[EFFECT_CHARARASTER] = new CEffectCharaRaster(this);
	m_ppEffects[EFFECT_KE] = new CEffectKe(this);
	m_ppEffects[EFFECT_HAE] = new CEffectHae(this);
	m_ppEffects[EFFECT_OLDLAMP] = new CEffectOldLamp(this);
	m_ppEffects[EFFECT_CHARAGHOST] = new CEffectCharaGhost(this);
	m_ppEffects[EFFECT_FISH] = new CEffectFish(this);
	m_ppEffects[EFFECT_CHARAMETAL] = new CEffectCharaMetal(this);
	m_ppEffects[EFFECT_LUPIN] = new CEffectLupin(this);
	m_ppEffects[EFFECT_GEOBOX] = new CEffectGeoBox(this);
	m_ppEffects[EFFECT_GEOCIRCLEADD] = new CEffectGeoCircleAdd(this);
	m_ppEffects[EFFECT_GEOTORUSADD] = new CEffectGeoTorusAdd(this);
	m_ppEffects[EFFECT_GEOPOLYGONADD] = new CEffectGeoPolygonAdd(this);
	m_ppEffects[EFFECT_GEOBOXADD] = new CEffectGeoBoxAdd(this);
#if !defined _TINYAN3DLIB_
	m_ppEffects[EFFECT_BSPLINE2] = new CEffectBSpline2(this);
	m_ppEffects[EFFECT_COLORBALANCE] = new CEffectColorBalance(this);
	m_ppEffects[EFFECT_DUALMASK] = new CEffectDualMask(this);
	m_ppEffects[EFFECT_CLIPZOOMIN] = new CEffectClipZoomIn(this);
	m_ppEffects[EFFECT_CHARAMASKAPPEAR] = new CEffectCharaMaskAppear(this);
	m_ppEffects[EFFECT_CHARAGREY] = new CEffectCharaGrey(this);
	m_ppEffects[EFFECT_CHARABOKASHI] = new CEffectCharaBokashi(this);
	m_ppEffects[EFFECT_BGBOKASHI] = new CEffectBGBokashi(this);
	m_ppEffects[EFFECT_SEPIA] = new CEffectCharaSepia(this);
	m_ppEffects[EFFECT_LAYERSEPIA] = new CEffectLayerSepia(this);
	m_ppEffects[EFFECT_LAYERGREY] = new CEffectLayerGrey(this);
	m_ppEffects[EFFECT_SAIKE] = new CEffectSaike(this);
	m_ppEffects[EFFECT_CHARABURE] = new CEffectCharaBure(this);
	m_ppEffects[EFFECT_ADDSUB] =  new CEffectCharaAddSub(this);
	m_ppEffects[EFFECT_SENTENCE] =  new CEffectSentence(this);

	m_ppEffects[EFFECT_TACLIP] = new CEffectTaClip(this);
#endif

	for (i=0;i<EFFECT_SHURUI_MAX;i++)
	{
		CCommonEffect* lp = m_ppEffects[i];
		if (lp != NULL)
		{
			m_renzokuEffectFlag[i] = lp->CheckRenzokuEffect();
		}
		else
		{
			m_renzokuEffectFlag[i] = FALSE;
		}
	}


	for (i=0;i<PICTURE_KOSUU_MAX;i++)
	{
		m_effect[i].flag = FALSE;
		m_effect[i].command = -1;
		m_effect[i].pic = i;
	}


	for (i=0;i<PICTURE_KOSUU_MAX;i++)
	{
		m_pic[i] = new CPicture();
	}

	for (i=0;i<PICTURE_KOSUU_MAX;i++)
	{
		SetEye(i);
	}

	m_makeCGPicNum = 0;

	for (i=0;i<EFFECT_SHURUI_MAX;i++)
	{
		CCommonEffect* lp = m_ppEffects[i];
		if (lp != NULL) lp->Init();
	}

	for (i=0;i<PICTURE_KOSUU_MAX;i++)
	{
		m_filename[i][0] = 0;
		m_makeFilename[i][0] = 0;
	}

	ClearAllEffect(TRUE);

	SetSpeakingFlag();

}




CAllEffect::~CAllEffect()
{
	End();
}

void CAllEffect::End(void)
{
	int i;
	for (i=0;i<PICTURE_KOSUU_MAX;i++)
	{
		ENDDELETECLASS(m_pic[i]);
	}

	if (m_ppEffects != NULL)
	{
		for (i=0;i<m_effectKosuu;i++)
		{
			ENDDELETECLASS(m_ppEffects[i]);
		}

		DELETEARRAY(m_ppEffects);
		m_ppEffects = NULL;
	}

	DELETEARRAY(m_tempWork);
}

CPicture* CAllEffect::GetPicture(int layer)
{
	if (layer<0) layer = 0;
	if (layer>=PICTURE_KOSUU_MAX) layer = PICTURE_KOSUU_MAX-1;

	return m_pic[layer];
}


POINT CAllEffect::GetDstPoint(int layer)
{
	POINT pt;

	pt.x = m_effect[layer].dst.left;
	pt.y = m_effect[layer].dst.top;

	return pt;
}

POINT CAllEffect::GetSrcPoint(int layer)
{
	POINT pt;

	pt.x = 0;
	pt.y = 0;

	return pt;
}

SIZE CAllEffect::GetDstSize(int layer)
{
	SIZE sz;

	sz.cx = m_effect[layer].dst.right;
	sz.cy = m_effect[layer].dst.bottom;


	return sz;
}


BOOL CAllEffect::CheckBGLayer(int layer)
{
	if (layer<4) return TRUE;
	if (layer==14) return TRUE;

	return FALSE;
}


void CAllEffect::ExchangeEffectPic(int layer1,int layer2)
{
	CPicture* pic1 = m_pic[layer1];
	CPicture* pic2 = m_pic[layer2];

	m_pic[layer1] = pic2;
	m_pic[layer2] = pic1;
}

BOOL CAllEffect::ChangeEffectCommandOnly(int layer,int cmd)
{
//	m_effect[layer].command = cmd;

	return TRUE;
}

int CAllEffect::GetOtherLayerPic(int layer)
{
	//int pic2 = m_effect->m_effect[lp->para[1]].pic;

	return m_effect[layer].pic;
	return -1;
}

int* CAllEffect::GetGetBuffer(void)
{
	int* ptr = CEffectGet::m_effectGetBuffer;
	if (ptr  == NULL)
	{
		((CEffectGet*)(m_ppEffects[EFFECT_GET]))->GetScreen();
		ptr = CEffectGet::m_effectGetBuffer;
	}

	return ptr;
}



void CAllEffect::SetEye(int n, BOOL md)
{
	if ((n>=0) && (n<PICTURE_KOSUU_MAX)) m_eyeFlag[n] = md;
}


void CAllEffect::ClearAllEffect(BOOL b)
{
	for (int i=0;i<LAYER_KOSUU_MAX;i++)
	{
		ClearEffect(i);
		if (b) ClearMakeCGEffect(i);
		if (b)
		{
			for (int ii=0;ii<PICTURE_KOSUU_MAX;ii++)
			{
				m_filename[ii][0] = 0;
				m_makeFilename[ii][0] = 0;
			}
		}

	}
}

void CAllEffect::ClearEffect(int n)
{
	RECT drc;
	int sizeX = CMyGraphics::GetScreenSizeX();
	int sizeY = CMyGraphics::GetScreenSizeY();

	SetRect(&drc,0,0,sizeX,sizeY);

	m_effect[n].flag = FALSE;
	m_effect[n].pic = -1;
	m_effect[n].command = EFFECT_NOP;
	m_effect[n].src = drc;
	m_effect[n].dst = drc;
	m_effect[n].srcFrom = drc;
	m_effect[n].dstFrom = drc;
	m_effect[n].srcTo = drc;
	m_effect[n].dstTo = drc;
	m_effect[n].count = 0;
	m_effect[n].countMax = 0;
	m_effect[n].notTransFlag = CheckBGLayer(n);
}

void CAllEffect::ClearMakeCGEffect(int n)
{
	int sizeX = CMyGraphics::GetScreenSizeX();
	int sizeY = CMyGraphics::GetScreenSizeY();

	RECT drc;
	SetRect(&drc,0,0,sizeX,sizeY);

	m_makeEffect[n].flag = FALSE;
//	m_makeEffect[n].pic = -1;
	m_makeEffect[n].command = EFFECT_NOP;
	m_makeEffect[n].src = drc;
	m_makeEffect[n].dst = drc;
	m_makeEffect[n].srcFrom = drc;
	m_makeEffect[n].dstFrom = drc;
	m_makeEffect[n].srcTo = drc;
	m_makeEffect[n].dstTo = drc;
	m_makeEffect[n].count = 0;
	m_makeEffect[n].countMax = 0;
	m_makeEffect[n].notTransFlag = CheckBGLayer(n);
}

void CAllEffect::SetLayerScript(int n,int d)
{
	if ((n<0) || (n>15)) return;

	m_effect[n].flag = TRUE;
	m_effect[n].pic = d;

	RECT drc;

	if (d != -1)
	{
		CPicture* lpPic = m_pic[d];
		if (lpPic != NULL)
		{
			lpPic->GetPicSize(&drc);

			m_effect[n].src = drc;
			m_effect[n].dst = drc;
			m_effect[n].srcFrom = drc;
			m_effect[n].dstFrom = drc;
			m_effect[n].srcTo = drc;
			m_effect[n].dstTo = drc;		}
	}
	else
	{
		m_effect[n].flag = FALSE;
		ClearEffect(n);
	}
}

void CAllEffect::SkipAllEffectCount(void)
{
	for (int i=0;i<LAYER_KOSUU_MAX;i++)
	{
		m_effect[i].count = m_effect[i].countMax;
	}
	CalcuZahyo();
}

void CAllEffect::CalcuZahyo(void)
{
//	m_rememberCount++;
//	if (m_rememberCount>100000000) m_rememberCount = 0;

//	m_effectWaterCount++;
//	if (m_effectWaterCount > 1000000) m_effectWaterCount = 0;

	for (int i=0;i<LAYER_KOSUU_MAX;i++)
	{
		if (m_effect[i].flag)
		{
			int countmax = m_effect[i].countMax;
			if (countmax > 0)
			{
				int c = m_effect[i].count;
				if (c<=countmax)
				{
					if (c<countmax)
					{
						c++;
						m_effect[i].count = c;
					}

					int c2 = countmax >> 1;


					//putXY
					int dx = m_effect[i].dstTo.left - m_effect[i].dstFrom.left;
					int dy = m_effect[i].dstTo.top - m_effect[i].dstFrom.top;
					dx *= c;
					if (dx>=0)
					{
						dx += c2;
						dx /= countmax;
					}
					else
					{
						dx = -dx;
						dx += c2;
						dx /= countmax;
						dx = -dx;						
					}

					dy *= c;
					if (dy>=0)
					{
						dy += c2;
						dy /= countmax;
					}
					else
					{
						dy = -dy;
						dy += c2;
						dy /= countmax;
						dy = -dy;						
					}

					m_effect[i].dst.left = m_effect[i].dstFrom.left + dx;
					m_effect[i].dst.top = m_effect[i].dstFrom.top + dy;

					//



				}
			}
		}
	}
}


void CAllEffect::Calcu(int cnt)
{
	CountUp(cnt);
	CalcuOnly();
}


void CAllEffect::CalcuOnly(void)
{
//	m_rememberCount++;
//	if (m_rememberCount>100000000) m_rememberCount = 0;

//	m_effectWaterCount++;
//	if (m_effectWaterCount > 1000000) m_effectWaterCount = 0;

	for (int i=0;i<LAYER_KOSUU_MAX;i++)
	{
		if (m_effect[i].flag)
		{
			int countmax = m_effect[i].countMax;
			int c = m_effect[i].count;

			//effect
			int effect = m_effect[i].command;
			if (effect != -1)
			{
			//	CCommonEffect* lp = m_effectClass[effect];
				CCommonEffect* lp = m_ppEffects[effect];
				if (lp != NULL)
				{
					lp->Calcu(&m_effect[i],i);
				}
			}


			if (m_effect[i].pic != -1)
			{
				if ((c>=countmax) || (countmax==0))
				{
					m_effect[i].dst = m_effect[i].dstTo;
					continue;
				}

				if (c<=countmax)
				{
					int c2 = countmax >> 1;

					//putXY
					int dx = m_effect[i].dstTo.left - m_effect[i].dstFrom.left;
					int dy = m_effect[i].dstTo.top - m_effect[i].dstFrom.top;
					dx *= c;
					if (dx>=0)
					{
						dx += c2;
						dx /= countmax;
					}
					else
					{
						dx = -dx;
						dx += c2;
						dx /= countmax;
						dx = -dx;						
					}

					dy *= c;
					if (dy>=0)
					{
						dy += c2;
						dy /= countmax;
					}
					else
					{
						dy = -dy;
						dy += c2;
						dy /= countmax;
						dy = -dy;						
					}

					m_effect[i].dst.left = m_effect[i].dstFrom.left + dx;
					m_effect[i].dst.top = m_effect[i].dstFrom.top + dy;
					m_effect[i].dst.right = m_effect[i].dstFrom.right;
					m_effect[i].dst.bottom = m_effect[i].dstFrom.bottom;


//OutputDebugString(":");
//if (m_effect[i].dstFrom.left != m_effect[i].dstTo.left)
//if (i == 6)
//{
	//char mes[1024];
	//sprintf(mes,"[%d %d %d %d]",c,countmax,m_effect[i].dstFrom.top,m_effect[i].dstTo.top);
	//OutputDebugString(mes);
//}

				}
			}
		}
	}
}

void CAllEffect::SkipPrint(void)
{
	CalcuZahyo();
}

void CAllEffect::CheckNeedAllPrint(void)
{
	for (int i=0;i<LAYER_KOSUU_MAX;i++)
	{
		if (m_effect[i].flag)
		{
			if ((m_effect[i].command != EFFECT_NOP) && (m_effect[i].command != EFFECT_BUFFER) && (m_effect[i].command != EFFECT_FILL))
			{
				CAreaControl::SetAllPrintMode();
				return;
			}

			if (!EqualRect(&m_effect[i].dstFrom,&m_effect[i].dstTo))
			{
//				char mes[256];
//				sprintf(mes,"%d %d %d %d:%d %d %d %d    \n",
//					m_effect[i].dstFrom.left,
//					m_effect[i].dstFrom.top,
//					m_effect[i].dstFrom.right,
//					m_effect[i].dstFrom.bottom,
//					m_effect[i].dstTo.left,
//					m_effect[i].dstTo.top,
//					m_effect[i].dstTo.right,
//					m_effect[i].dstTo.bottom);
				CAreaControl::SetAllPrintMode();
				return;
			}

			if (!EqualRect(&m_effect[i].srcFrom,&m_effect[i].srcTo))
			{
				CAreaControl::SetAllPrintMode();
				return;
			}

		}
	}
}


int CAllEffect::GetParaSize(void)
{
	return sizeof(EFFECT);
}


void* CAllEffect::GetEffectDataPointer(int n)
{
	return &m_effect[n];
}


void CAllEffect::GetGetScreen(void)
{
	CEffectGet* effect = (CEffectGet*)m_ppEffects[EFFECT_GET];
	effect->GetScreen();
}

void CAllEffect::PutGetScreen(void)
{
	CEffectPut* effect = (CEffectPut*)m_ppEffects[EFFECT_PUT];
	effect->PutScreen();
}


void CAllEffect::EndEffect(void)
{
	BOOL flg = FALSE;


	int i;
	for (i=0;i<LAYER_KOSUU_MAX;i++)
	{
		int effect = m_effect[i].command;
		if (effect != -1)
		{
			if (m_renzokuEffectFlag[i] == FALSE)
			{
				if (m_effect[i].count >= m_effect[i].countMax)
				{
					CCommonEffect* lp = m_ppEffects[effect];
					if (lp != NULL)
					{
						if (lp->CountIsMax(&m_effect[i],i)) flg = TRUE;
					}
				}
			}
		}
	}


	for (i=0;i<LAYER_KOSUU_MAX;i++)
	{
		if (m_effect[i].flag)
		{
			if (m_effect[i].count >= m_effect[i].countMax)
			{
				m_effect[i].dstFrom = m_effect[i].dstTo;
				m_effect[i].srcFrom = m_effect[i].srcTo;

				if ( (!EqualRect(&m_effect[i].dstFrom,&m_effect[i].dstTo)) || (!EqualRect(&m_effect[i].srcFrom,&m_effect[i].srcTo)) )
				{
					flg = TRUE;
				}
			}
		}
	}


	if (flg)
	{
		CAreaControl::SetNextAllPrint();
	}
}

void CAllEffect::SetEffectFileName(int n, LPSTR filename)
{
	if ((n<0) || (n>=PICTURE_KOSUU_MAX)) return;
	int ln = strlen(filename);
	if (ln>254) ln = 254;
	memcpy(&m_filename[n][0],filename,ln);
	m_filename[n][ln] = 0;
	m_filename[n][ln+1] = 0;
}


void CAllEffect::SetMakeFileName(int n,LPSTR filename)
{
	if ((n<0) || (n>=PICTURE_KOSUU_MAX)) return;
	int ln = strlen(filename);
	if (ln>254) ln = 254;
	memcpy(&m_makeFilename[n][0],filename,ln);
	m_makeFilename[n][ln] = 0;
	m_makeFilename[n][ln+1] = 0;
}


LPSTR CAllEffect::GetEffectFileName(int n)
{
	if ((n<0) || (n>=PICTURE_KOSUU_MAX)) n = 0;

	return &m_filename[n][0];
}


LPSTR CAllEffect::GetMakeFileName(int n)
{
	if ((n<0) || (n>=PICTURE_KOSUU_MAX)) n = 0;
	return &m_makeFilename[n][0];
}

void CAllEffect::PreMakeCG(int n)
{
	m_makeCGPicNum = n;
	memcpy(m_makeEffect,m_effect,sizeof(m_effect));
	memcpy(&m_makeFilename[0][0],&m_filename[0][0],sizeof(m_filename));
}

void CAllEffect::PostMakeCG(int n)
{
	if (n == -1) return;

	m_filename[n][0] = 0;
}

void CAllEffect::GetMyRect(int layer, int n, RECT* lpRect)
{
	switch (n)
	{
	case 0:
		*lpRect = m_effect[layer].srcFrom;
		break;
	case 1:
		*lpRect = m_effect[layer].srcTo;
		break;
	case 2:
		*lpRect = m_effect[layer].dstFrom;
		break;
	case 3:
		*lpRect = m_effect[layer].dstTo;
		break;
	case 4:
		*lpRect = m_effect[layer].src;
		break;
	case 5:
		*lpRect = m_effect[layer].dst;
		break;
	}
}


void CAllEffect::SetMyRect(int layer, int n, RECT* lpRect)
{
	switch (n)
	{
	case 0:
		m_effect[layer].srcFrom = *lpRect;
		break;
	case 1:
		m_effect[layer].srcTo = *lpRect;
		break;
	case 2:
		m_effect[layer].dstFrom = *lpRect;
		break;
	case 3:
		m_effect[layer].dstTo = *lpRect;
		break;
	case 4:
		m_effect[layer].src = *lpRect;
		break;
	case 5:
		m_effect[layer].dst = *lpRect;
		break;
	}
}


void CAllEffect::ResetCount(int n)
{
	int st = n;
	int ed = n;

	if (n == -1)
	{
		st = 0;
		ed = 15;
	}

	for (int i=st;i<=ed;i++)
	{
		if ((i>=0) && (i<LAYER_KOSUU_MAX))
		{
			m_effect[i].count = 0;
		}
	}
}

void CAllEffect::SetCountToLast(void)
{
	for (int i=0;i<LAYER_KOSUU_MAX;i++)
	{
		int c = m_effect[i].countMax;
		if (c>0) c--;
		m_effect[i].count = c;
	}
}

void CAllEffect::BeginEffect(void)
{
	for (int i=0;i<LAYER_KOSUU_MAX;i++)
	{
		if (m_effect[i].flag)
		{
			int effect = m_effect[i].command;
			if (effect != -1)
			{
				CCommonEffect* lpEffect = m_ppEffects[effect];
				if (lpEffect != NULL)
				{
					lpEffect->BeginPrint(&m_effect[i],i);
				}
			}
		}
	}
}

void CAllEffect::CountUp(int delta)
{
	BOOL flg = FALSE;

	for (int i=0;i<LAYER_KOSUU_MAX;i++)
	{
		if (m_effect[i].flag)
		{
			int effect = m_effect[i].command;
			if (effect != -1)
			{
				int count = m_effect[i].count;
				int mx = m_effect[i].countMax;
				if (count<mx)
				{
					count += delta;
					if (count >= mx) count = mx;
					m_effect[i].count = count;

					if (count == mx)
					{
						CCommonEffect* lp = m_ppEffects[effect];
						if (lp != NULL)
						{
							if (lp->CountIsMax(&m_effect[i],i)) flg = TRUE;
						}
					}
				}
			}
		}
	}
	
	if (flg)
	{
		CAreaControl::SetNextAllPrint();
	}
}

int CAllEffect::GetEffectEndIsChangeLayer(int effect)
{
	if (effect == EFFECT_CHANGE)
	{
///		return 1;
	}


	return -1;
}


//ŠO•”ŒÄ‚Ño‚µ—p
void CAllEffect::PrintSimpleWipe(int n, CPicture* lpPicStart, CPicture* lpPicEnd, int count, int countMax)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	CEffectSimpleWipe* lp = (CEffectSimpleWipe*)m_ppEffects[EFFECT_SIMPLEWIPE];
	if (lp == NULL) return;

	CEffectSimpleWipeCommon* lpWipe = lp->GetWipeObject(n);
	if (lpWipe == NULL) return;

	//check data

	if (lpPicStart == NULL) return;
	if (lpPicEnd == NULL) return;

	//check size

	RECT rc;
	lpPicStart->GetPicSize(&rc);
	if (rc.right < screenSizeX) return;
	if (rc.bottom < screenSizeY) return;


	RECT rc2;
	lpPicEnd->GetPicSize(&rc2);
	if (rc2.right < screenSizeX) return;
	if (rc2.bottom < screenSizeY) return;

	if (countMax<1) countMax = 1;
	if (count<0) count = 0;
	if (count>countMax) count = countMax;


	lpWipe->Print(lpPicStart,lpPicEnd,count,countMax);
}

BOOL CAllEffect::ResizePicture(int n, int sizeX, int sizeY)
{
	if ((sizeX<=0) || (sizeY<=0))
	{
		sizeX = CMyGraphics::GetScreenSizeX();
		sizeY = CMyGraphics::GetScreenSizeY();
	}

	if ((n>=0) && (n<=15))
	{
		CPicture* pic = m_pic[n];
		if (pic != NULL)
		{
			return pic->ReSize(sizeX,sizeY);
		}
	}

	return FALSE;
}


void CAllEffect::InitAllParameter(void)
{
	for (int i=0;i<LAYER_KOSUU_MAX;i++)
	{
		InitParameter(i);
	}
}

void CAllEffect::InitParameter(int layer)
{
	if (m_effect[layer].flag)
	{
		int effect = m_effect[layer].command;
		if (effect != -1)
		{
			CCommonEffect* commonEffect = m_ppEffects[effect];
			if (commonEffect != NULL)
			{
				commonEffect->InitParameter(&m_effect[layer],layer);
			}
		}
	}
}


CPicture* CAllEffect::GetOverrapPic(int n)
{
	if (n == 0) return m_overrapPic0;
	if (n == 1) return m_overrapPic1;

	return NULL;
}

void CAllEffect::SetOverrapPic(int n, CPicture* lpPic)
{
	if (n == 0) m_overrapPic0 = lpPic;
	if (n == 1) m_overrapPic1 = lpPic;
}

void CAllEffect::SetNowNoClearFlag(BOOL b)
{
	m_nowNoClearFlag = b;
}

BOOL CAllEffect::SetEffectScript(int num,int effect,int paraKosuu,int* paraPtr)
{
//char mes[256];
//sprintf(mes,"[E=%d]",effect);
//OutputDebugString(mes);
	if ((num<0) || (num>15)) return FALSE;

	if (effect == -1) return FALSE;

	int para[256];
	for (int i=0;i<paraKosuu;i++)
	{
		para[i] = *(paraPtr+i);
	}
//	RECT rc;

	if ((effect>=0) && (effect<EFFECT_SHURUI_MAX))
	{
		CCommonEffect* lp = m_ppEffects[effect];
		if (lp != NULL)
		{
			if (effect != EFFECT_MAE)
			{
				return lp->SetParam(&m_effect[num],paraKosuu,paraPtr,num);
			}
			return TRUE;
		}
	}

	return FALSE;
}

void CAllEffect::PrintLayers(int startLayer,int endLayer,BOOL bScreenFlag,BOOL bEyeCheckFlag)
{
/*
	if (bScreenFlag == FALSE)
	{
		BOOL flg = FALSE;
		int iiStart = 0;
		int iiEnd = 4;
		if (iiStart<startLayer) iiStart = startLayer;
		if (iiEnd >= (endLayer+1)) iiEnd = endLayer+1;

		for (int ii=iiStart;ii<iiEnd;ii++)
		{
			if (flg == FALSE)
			{
				if (m_effect[ii].flag)
				{
					if (m_effect[ii].pic != -1)
					{
						if (m_effect[ii].command != EFFECT_BUFFER)
						{
							flg = TRUE;
							break;
						}
					}

					if (m_effect[ii].command == EFFECT_FULLANIME) flg = TRUE;
					if (m_effect[ii].command == EFFECT_FILL) flg = TRUE;
				}
			}
		}


		if (m_nowNoClearFlag) flg = TRUE;
		m_nowNoClearFlag = FALSE;

//		if (((m_effect[0].flag == FALSE) || (m_effect[0].pic == -1) || (m_effect[0].command == EFFECT_BUFFER)) && ((m_effect[1].flag == FALSE) || (m_effect[1].pic == -1) || (m_effect[1].command == EFFECT_BUFFER)))
		if (flg == FALSE)
		{
			//Clear BG
//			if ((m_effect[0].command != EFFECT_FULLANIME) && (m_effect[1].command != EFFECT_FULLANIME))
//			{
///@@				CAllGraphics::FillScreen();
//			}
		}
	}
*/


	for (int i=startLayer;i<=endLayer;i++)
	{
		if ((m_eyeFlag[i] == FALSE) && (bEyeCheckFlag == TRUE)) continue;

		if (m_effect[i].flag)
		{
			int pic = m_effect[i].pic;
			int effect = m_effect[i].command;

			if (effect != -1)
			{
				CCommonEffect* lpEffect = m_ppEffects[effect];
				if (lpEffect != NULL)
				{
					if (pic != -1)
					{
						if (lpEffect->CheckNeedPicPrint(&m_effect[i],i))
						{
							CPicture* lpPic = GetPicture(i);

							int x = m_effect[i].dst.left;
							int y = m_effect[i].dst.top;
							int srcX = m_effect[i].src.left;
							int srcY = m_effect[i].src.top;
							int sizeX = m_effect[i].dst.right;
							int sizeY = m_effect[i].dst.bottom;

							
//if (y != m_effect[i].dstFrom.top)
//{
//OutputDebugString("MOVE ");
//}

//if ((i==13) && (effect == 66))
//{
//OutputDebugString("[BUF]");
//}

							if (CheckBGLayer(i))
							{
								lpPic->Blt(x ,y ,srcX ,srcY ,sizeX,sizeY,FALSE);
							}
							else
							{
								lpPic->Blt(x ,y ,srcX ,srcY ,sizeX,sizeY,TRUE);
							}
						}
					}

					lpEffect->Print(&m_effect[i],i);

				}

//				case EFFECT_CHANGE:
//					PrintChange(i);
//					break;
			}
		}
	}

}

void CAllEffect::Print(BOOL bScreenFlag,BOOL bEyeCheckFlag)
{
	if (bScreenFlag == FALSE)
	{
		BOOL flg = FALSE;
		for (int ii=0;ii<4;ii++)
		{
			if (flg == FALSE)
			{
				if (m_effect[ii].flag)
				{
					if (m_effect[ii].pic != -1)
					{
						if (m_effect[ii].command != EFFECT_BUFFER)
						{
							flg = TRUE;
							break;
						}
					}

					if (m_effect[ii].command == EFFECT_FULLANIME) flg = TRUE;
					if (m_effect[ii].command == EFFECT_FILL) flg = TRUE;
				}
			}
		}


		if (m_nowNoClearFlag) flg = TRUE;
		m_nowNoClearFlag = FALSE;

//		if (((m_effect[0].flag == FALSE) || (m_effect[0].pic == -1) || (m_effect[0].command == EFFECT_BUFFER)) && ((m_effect[1].flag == FALSE) || (m_effect[1].pic == -1) || (m_effect[1].command == EFFECT_BUFFER)))
		if (flg == FALSE)
		{
			//Clear BG
//			if ((m_effect[0].command != EFFECT_FULLANIME) && (m_effect[1].command != EFFECT_FULLANIME))
//			{
				CAllGraphics::FillScreen();
//			}
		}
	}

	int st = 0;
	int ed = LAYER_KOSUU_MAX-2;

	if (bScreenFlag)
	{
		st = LAYER_KOSUU_MAX-1;
		ed = st;
	}
	
	for (int i=st;i<=ed;i++)
	{
		if ((m_eyeFlag[i] == FALSE) && (bEyeCheckFlag == TRUE)) continue;

		if (m_effect[i].flag)
		{
			int pic = m_effect[i].pic;
			int effect = m_effect[i].command;

			if (effect != -1)
			{
				CCommonEffect* lpEffect = m_ppEffects[effect];
				if (lpEffect != NULL)
				{
					if (pic != -1)
					{
						if (lpEffect->CheckNeedPicPrint(&m_effect[i],i))
						{
							CPicture* lpPic = GetPicture(i);

							int x = m_effect[i].dst.left;
							int y = m_effect[i].dst.top;
							int srcX = m_effect[i].src.left;
							int srcY = m_effect[i].src.top;
							int sizeX = m_effect[i].dst.right;
							int sizeY = m_effect[i].dst.bottom;

							
//if (y != m_effect[i].dstFrom.top)
//{
//OutputDebugString("MOVE ");
//}

//if ((i==13) && (effect == 66))
//{
//OutputDebugString("[BUF]");
//}

							if (CheckBGLayer(i))
							{
								lpPic->Blt(x ,y ,srcX ,srcY ,sizeX,sizeY,FALSE);
							}
							else
							{
								lpPic->Blt(x ,y ,srcX ,srcY ,sizeX,sizeY,TRUE);
							}
						}
					}

					lpEffect->Print(&m_effect[i],i);

				}

//				case EFFECT_CHANGE:
//					PrintChange(i);
//					break;
			}
		}
	}
}

void CAllEffect::TaihiAllEffect(void)
{
	int i;


	for (i=0;i<LAYER_KOSUU_MAX;i++)
	{
		m_taihiEffect[i] = m_effect[i];
	}

	for (i=0;i<PICTURE_KOSUU_MAX;i++)
	{
		memcpy(m_taihiFilename[i],m_filename[i],256);
	}
}

void CAllEffect::FuqueAllEffect(void)
{
	int i;
	for (i=0;i<LAYER_KOSUU_MAX;i++)
	{
		m_effect[i] = m_taihiEffect[i];
	}

	for (i=0;i<PICTURE_KOSUU_MAX;i++)
	{
		memcpy(m_filename[i],m_taihiFilename[i],256);
	}

	//load file
	for (i=0;i<PICTURE_KOSUU_MAX;i++)
	{
		if (m_filename[i][0] != 0)
		{
			CPicture* lpPic = GetPicture(i);
			if (lpPic != NULL)
			{
				lpPic->LoadDWQ(m_filename[i]);
			}
		}
	}


	//set effect
	InitAllParameter();
}

LPSTR CAllEffect::GetTaihiEffectFileName(int n)
{
	if ((n<0) || (n>=PICTURE_KOSUU_MAX)) n = 0;

	return m_taihiFilename[n];
}

void* CAllEffect::GetTaihiEffectDataPointer(int n)
{
	return &m_taihiEffect[n];
}


void CAllEffect::ReCreateAllShader(void)
{
#if defined _TINYAN3DLIB_
	int i;
	for (i=0;i<256;i++)
	{
		if (m_ppEffects[i] != NULL)
		{
			m_ppEffects[i]->Create(NULL);
		}
	}

	if (m_ppEffects[EFFECT_SIMPLEWIPE] != NULL)
	{
		((CEffectSimpleWipe*)(m_ppEffects[EFFECT_SIMPLEWIPE]))->ReCreateAllShader();

	}
#endif
}



/*_*/


