//
//
//

#include <windows.h>
//#include <stdio.h>

#include "..\nyanlib\include\commonmacro.h"
#include "..\nyanlib\include\myGraphics.h"


#include "greyblt.h"
#include "redblt.h"
#include "colorblt.h"
#include "transLucentBlt.h"
#include "transLucentBlt0.h"
#include "transLucentBlt2.h"
#include "transLucentBlt3.h"
#include "maskBlt.h"
#include "negaBlt.h"
#include "blt.h"
#include "bltBeta.h"
#include "blt256.h"
#include "blt256Beta.h"
#include "shapeBlt.h"
#include "gradationShapeBlt.h"
#include "addBlt.h"
#include "lightBlt.h"
#include "stretchBlt.h"
#include "colorAddBlt.h"
#include "changeTransLucentBlt.h"
#include "overrapblt.h"
#include "yuvChangeBlt.h"
#include "greyBlt2.h"
#include "sepiaBlt.h"
#include "addSubBlt.h"
#include "stretchAddSubBlt.h"

#include "..\nyanLib\include\allPicture.h"


CGreyBlt* CAllPicture::m_greyBlt = NULL;
CRedBlt* CAllPicture::m_redBlt = NULL;
CColorBlt* CAllPicture::m_colorBlt = NULL;
CTransLucentBlt* CAllPicture::m_transLucentBlt = NULL;
CTransLucentBlt0* CAllPicture::m_transLucentBlt0 = NULL;
CTransLucentBlt2* CAllPicture::m_transLucentBlt2 = NULL;
CTransLucentBlt3* CAllPicture::m_transLucentBlt3 = NULL;
CMaskBlt* CAllPicture::m_maskBlt = NULL;
CNegaBlt* CAllPicture::m_negaBlt = NULL;
CBlt* CAllPicture::m_blt = NULL;
CBltBeta* CAllPicture::m_bltBeta = NULL;
CBlt256* CAllPicture::m_blt256 = NULL;
CBlt256Beta* CAllPicture::m_blt256Beta = NULL;
CShapeBlt* CAllPicture::m_shapeBlt = NULL;
CGradationShapeBlt* CAllPicture::m_gradationShapeBlt = NULL;
CAddBlt* CAllPicture::m_addBlt = NULL;
CLightBlt* CAllPicture::m_lightBlt = NULL;
CStretchBlt* CAllPicture::m_stretchBlt = NULL;
CColorAddBlt* CAllPicture::m_colorAddBlt = NULL;
CChangeTransLucentBlt* CAllPicture::m_changeTransLucentBlt = NULL;
COverrapBlt* CAllPicture::m_overrapBlt = NULL;
CYUVChangeBlt* CAllPicture::m_yuvChangeBlt = NULL;
CGreyBlt2* CAllPicture::m_greyBlt2 = NULL;
CSepiaBlt* CAllPicture::m_sepiaBlt = NULL;
CAddSubBlt* CAllPicture::m_addSubBlt = NULL;
CStretchAddSubBlt* CAllPicture::m_stretchAddSubBlt = NULL;




CAllPicture::CAllPicture()
{
	m_greyBlt = new CGreyBlt();
	m_redBlt = new CRedBlt();
	m_colorBlt = new CColorBlt();
	m_transLucentBlt = new CTransLucentBlt();
	m_transLucentBlt0 = new CTransLucentBlt0();
	m_transLucentBlt2 = new CTransLucentBlt2();
	m_transLucentBlt3 = new CTransLucentBlt3();
	m_maskBlt = new CMaskBlt();
	m_negaBlt = new CNegaBlt();
	m_blt = new CBlt();
	m_bltBeta = new CBltBeta();
	m_blt256 = new CBlt256();
	m_blt256Beta = new CBlt256Beta();
	m_shapeBlt = new CShapeBlt();
	m_gradationShapeBlt = new CGradationShapeBlt();
	m_addBlt = new CAddBlt();
	m_lightBlt = new CLightBlt();
	m_stretchBlt = new CStretchBlt();
	m_colorAddBlt = new CColorAddBlt();
	m_changeTransLucentBlt = new CChangeTransLucentBlt();
	m_overrapBlt = new COverrapBlt();
	m_yuvChangeBlt = new CYUVChangeBlt();
	m_greyBlt2 = new CGreyBlt2();
	m_sepiaBlt = new CSepiaBlt();
	m_addSubBlt = new CAddSubBlt();
	m_stretchAddSubBlt = new CStretchAddSubBlt();
}


CAllPicture::~CAllPicture()
{
	End();
}

void CAllPicture::End(void)
{
	ENDDELETECLASS(m_stretchAddSubBlt);
	ENDDELETECLASS(m_addSubBlt);
	ENDDELETECLASS(m_sepiaBlt);
	ENDDELETECLASS(m_greyBlt2);
	ENDDELETECLASS(m_yuvChangeBlt);
	ENDDELETECLASS(m_overrapBlt);
	ENDDELETECLASS(m_changeTransLucentBlt);
	ENDDELETECLASS(m_colorAddBlt);
	ENDDELETECLASS(m_stretchBlt);
	ENDDELETECLASS(m_lightBlt);
	ENDDELETECLASS(m_addBlt);
	ENDDELETECLASS(m_gradationShapeBlt);
	ENDDELETECLASS(m_shapeBlt);
	ENDDELETECLASS(m_blt256Beta);
	ENDDELETECLASS(m_blt256);
	ENDDELETECLASS(m_bltBeta);
	ENDDELETECLASS(m_blt);
	ENDDELETECLASS(m_negaBlt);
	ENDDELETECLASS(m_maskBlt);
	ENDDELETECLASS(m_transLucentBlt3);
	ENDDELETECLASS(m_transLucentBlt2);
	ENDDELETECLASS(m_transLucentBlt0);
	ENDDELETECLASS(m_transLucentBlt);
	ENDDELETECLASS(m_colorBlt);
	ENDDELETECLASS(m_redBlt);
	ENDDELETECLASS(m_greyBlt);
}




void CAllPicture::GreyBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize,char* maskPic, BOOL transFlag, LPVOID lpPalette)
{
	if (m_greyBlt == NULL) return;
	m_greyBlt->Print(putPoint,srcPoint,putSize,srcPic,picSize,maskPic,transFlag,lpPalette);
}


void CAllPicture::RedBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize,char* maskPic, BOOL transFlag, LPVOID lpPalette)
{
	if (m_redBlt == NULL) return;
	m_redBlt->Print(putPoint,srcPoint,putSize,srcPic,picSize,maskPic,transFlag,lpPalette);
}


void CAllPicture::ColorBlt(POINT putPoint,POINT srcPoint,SIZE putSize,char* maskPic,SIZE srcSize,int r,int g,int b)
{
	if (m_colorBlt == NULL) return;
	m_colorBlt->Print(putPoint,srcPoint,putSize,maskPic,srcSize,r,g,b);
}

void CAllPicture::TransLucentBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize,int transPercent)
{
	if (m_transLucentBlt == NULL) return;
	m_transLucentBlt->Print(putPoint,srcPoint,putSize,picData,srcSize,transPercent);
}

void CAllPicture::TransLucentBlt0(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize,int transPercent)
{
	if (m_transLucentBlt0 == NULL) return;
	m_transLucentBlt0->Print(putPoint,srcPoint,putSize,picData,srcSize,transPercent);
}

void CAllPicture::TransLucentBlt2(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize,int transPercent)
{
	if (m_transLucentBlt2 == NULL) return;
	m_transLucentBlt2->Print(putPoint,srcPoint,putSize,picData,srcSize,transPercent);
}

void CAllPicture::TransLucentBlt3(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,LPVOID maskPic,SIZE srcSize,int transPercent)
{
	if (m_transLucentBlt3 == NULL) return;
	m_transLucentBlt3->Print(putPoint,srcPoint,putSize,picData,maskPic,srcSize,transPercent);
}

void CAllPicture::MaskBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,LPVOID maskPic,SIZE srcSize)
{
	if (m_maskBlt == NULL) return;
	m_maskBlt->Print(putPoint,srcPoint,putSize,picData,maskPic,srcSize);
}

void CAllPicture::NegaBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize,int negaPercent)
{
	if (m_negaBlt == NULL) return;
	m_negaBlt->Print(putPoint,srcPoint,putSize,picData,srcSize,negaPercent);
}

void CAllPicture::Blt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize)
{
	if (m_blt == NULL) return;
	m_blt->Print(putPoint,srcPoint,putSize,picData,srcSize);
}

void CAllPicture::BltBeta(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize)
{
	if (m_bltBeta == NULL) return;
	m_bltBeta->Print(putPoint,srcPoint,putSize,picData,srcSize);
}

void CAllPicture::Blt256(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,LPVOID lpPalette,SIZE srcSize)
{
	if (m_blt256 == NULL) return;
	m_blt256->Print(putPoint,srcPoint,putSize,picData,lpPalette,srcSize);
}

void CAllPicture::Blt256Beta(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,LPVOID lpPalette,SIZE srcSize)
{
	if (m_blt256Beta == NULL) return;
	m_blt256Beta->Print(putPoint,srcPoint,putSize,picData,lpPalette,srcSize);
}

void CAllPicture::ShapeBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID maskData,SIZE srcSize,int r,int g,int b)
{
	if (m_shapeBlt == NULL) return;
	m_shapeBlt->Print(putPoint,srcPoint,putSize,maskData,srcSize,r,g,b);
}

void CAllPicture::GradationShapeBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID maskData,SIZE srcSize,int r1,int g1,int b1,int r2,int g2,int b2)
{
	if (m_gradationShapeBlt == NULL) return;
	m_gradationShapeBlt->Print(putPoint,srcPoint,putSize,maskData,srcSize,r1,g1,b1,r2,g2,b2);
}

void CAllPicture::AddBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize)
{
	if (m_addBlt == NULL) return;
	m_addBlt->Print(putPoint,srcPoint,putSize,picData,srcSize);
}

void CAllPicture::LightBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize,int lightPercent)
{
	if (m_lightBlt == NULL) return;
	m_lightBlt->Print(putPoint,srcPoint,putSize,picData,srcSize,lightPercent);
}


void CAllPicture::StrtchBlt1(POINT dstPoint,POINT srcPoint,SIZE dstSize,SIZE srcSize,LPVOID picData,LPVOID maskData,SIZE picSize,BOOL transFlag,int transPercent)
{
	if (m_stretchBlt == NULL) return;
	m_stretchBlt->Print(dstPoint,srcPoint,dstSize,srcSize,picData,maskData,picSize,transFlag,transPercent);
}

void CAllPicture::ColorAddBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,LPVOID maskData,SIZE srcSize,BOOL transFlag,int r,int g,int b,int ps)
{
	if (m_colorAddBlt == NULL) return;
	m_colorAddBlt->Print(putPoint,srcPoint,putSize,picData,maskData,srcSize,transFlag,r,g,b,ps);
}

void CAllPicture::ChangeTransLucentBlt(POINT dstPoint,SIZE putSize,LPVOID picData1,LPVOID picData2,LPVOID maskData1,LPVOID maskData2,SIZE picSize,SIZE picSize2,int ps1,int ps2)
//void CAllPicture::ChangeTransLucentBlt(POINT dstPoint,POINT srcPoint,SIZE putSize,LPVOID picData1,LPVOID picData2,LPVOID maskData1,LPVOID maskData2,SIZE picSize,int ps1,int ps2)
{
	if (m_changeTransLucentBlt == NULL) return;
	if ((maskData1 != NULL) && (maskData2 != NULL))
	{
		m_changeTransLucentBlt->Print(dstPoint,putSize,picData1,picData2,maskData1,maskData2,picSize,picSize2,ps1,ps2);
	}
	else
	{
		m_changeTransLucentBlt->PrintBeta(dstPoint,putSize,picData1,picData2,picSize,picSize2,ps1,ps2);
	}
}

void CAllPicture::ChangeBlt256Beta(POINT dstPoint,SIZE putSize,LPVOID picData1,LPVOID picData2,LPVOID paletteData1,LPVOID paletteData2,SIZE picSize,SIZE picSize2,int ps1,int ps2)
{
	if (m_changeTransLucentBlt == NULL) return;
	m_changeTransLucentBlt->PrintBeta256(dstPoint,putSize,picData1,picData2,paletteData1,paletteData2,picSize,picSize2,ps1,ps2);
}


void CAllPicture::OverrapBltWithScreen(POINT nextPoint,LPVOID nextPic,SIZE nextPicSize,int startPercent,int endPercent)
{
	if (m_overrapBlt == NULL) return;
	m_overrapBlt->PrintWithScreen(nextPoint,nextPic,nextPicSize,startPercent,endPercent);
}

void CAllPicture::OverrapBlt(POINT startPoint,LPVOID startPic,SIZE startPicSize,POINT endPoint,LPVOID endPic,SIZE endPicSize,int startPercent,int endPercent)
{
	if (m_overrapBlt == NULL) return;
	m_overrapBlt->Print(startPoint,startPic,startPicSize,endPoint,endPic,endPicSize,startPercent,endPercent);
}


void CAllPicture::YUVChangeBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,LPVOID maskData,SIZE srcSize,BOOL yuvReverseFlag,int betaTransPercent255)
{
	if (m_yuvChangeBlt == NULL) return;
	m_yuvChangeBlt->Print(putPoint,srcPoint,putSize,picData,maskData,srcSize,yuvReverseFlag,betaTransPercent255);
}


void CAllPicture::GreyBlt2(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize,char* maskPic, int ps256,BOOL transFlag, LPVOID lpPalette)
{
	if (m_greyBlt2 == NULL) return;
	m_greyBlt2->Print(putPoint,srcPoint,putSize,srcPic,picSize,maskPic,ps256,transFlag,lpPalette);
}

void CAllPicture::SepiaBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize,char* maskPic, int ps256,int r,int g,int b,BOOL transFlag, LPVOID lpPalette)
{
	if (m_sepiaBlt == NULL) return;
	m_sepiaBlt->Print(putPoint,srcPoint,putSize,srcPic,picSize,maskPic,ps256,r,g,b,transFlag,lpPalette);
}

void CAllPicture::AddSubBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,char* maskData,SIZE srcSize,int percent)
{
	if (m_addSubBlt == NULL) return;
	m_addSubBlt->Print(putPoint,srcPoint,putSize,picData,maskData,srcSize,percent);
}

void CAllPicture::StrtchAddSubBlt(POINT dstPoint,POINT srcPoint,SIZE dstSize,SIZE srcSize,LPVOID picData,LPVOID maskData,SIZE picSize,BOOL transFlag,int transPercent,int deltaR,int deltaG,int deltaB)
{
	if (m_stretchAddSubBlt == NULL) return;
	m_stretchAddSubBlt->Print(dstPoint,srcPoint,dstSize,srcSize,picData,maskData,picSize,transFlag,transPercent,deltaR,deltaG,deltaB);
}

/*_*/


