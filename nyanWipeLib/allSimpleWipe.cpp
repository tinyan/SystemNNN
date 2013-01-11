//
//
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanlib\include\myGraphics.h"

#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeShape.h"
#include "allSimpleWipe.h"






//#include "simplewipesub\effectsimplewipeshape.h"



#include "effectsimplewipeoverrap.h"
#include "effectsimplewipecurtain.h"
#include "effectsimplewipecurtain2.h"
#include "effectsimplewipezebra.h"
#include "effectsimplewipeslide1.h"
#include "effectsimplewipeslide2.h"

#include "effectsimplewipecircle.h"


//#include "simplewipesub\effectsimplewipecircle1.h"
//#include "simplewipesub\effectsimplewipecircle2.h"
#include "effectsimplewipewarp1.h"
#include "effectsimplewipeclock.h"

//8種類
#include "effectSimpleWipeMove.h"

//4種類
#include "effectSimpleWipeDoor.h"

#include "effectSimpleWipeNurikae.h"
#include "effectSimpleWipeGrav.h"

//2種類
#include "effectSimpleWipeGaza.h"

#include "effectSimpleWipeRaster.h"

#include "effectsimplewipeStar.h"

#include "effectsimplewipeHeart.h"
#include "effectsimplewipeTurnStar.h"

#include "effectsimplewipeHahen.h"

#include "effectsimplewipeBeach.h"

#include "effectsimplewipeMozaic.h"

#include "effectsimplewipeRandomStrip.h"

#include "effectsimplewipeAdd.h"

#include "effectsimplewipeMekuri.h"

#include "effectsimplewipeSudare.h"

#include "effectSimpleWipeMulti.h"

#include "effectSimpleWipeTokoroten.h"

#include "effectSimpleWipeNaname.h"
#include "effectSimpleWipeSlot.h"

#include "effectSimpleWipeZoom.h"
#include "effectSimpleWipeCenter.h"

#include "effectSimpleWipeTogari.h"
#include "effectSimpleWipeWTogari.h"


//dummy
/*
#include "simplewipesub\effectsimplewipePage.h"
#include "simplewipesub\effectsimplewipeRadical.h"
#include "simplewipesub\effectsimplewipeChecker.h"
*/



CAllSimpleWipe::CAllSimpleWipe()
{
	int i,j;

	m_getBuffer = NULL;

	m_wipeKosuuMax = 256;
	m_wipes = new CEffectSimpleWipeCommon* [m_wipeKosuuMax];
	for (i=0;i<m_wipeKosuuMax;i++)
	{
		m_wipes[i] = NULL;
	}

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int szMax = screenSizeY;
	if (szMax < screenSizeX) szMax = screenSizeX;
	m_shapeWork = new int[szMax * 8];


	m_randomTableX2 = NULL;
	m_randomTableY2 = NULL;


	m_wipes[0] = new CEffectSimpleWipeOverrap(this);
	m_wipes[1] = new CEffectSimpleWipeCurtain(this);
	m_wipes[2] = new CEffectSimpleWipeCurtain2(this);
	m_wipes[3] = new CEffectSimpleWipeZebra(this);
	m_wipes[4] = new CEffectSimpleWipeSlide1(this);
	m_wipes[5] = new CEffectSimpleWipeSlide2(this);

	for (i=0;i<2;i++)
	{
		m_wipes[6+i] = new CEffectSimpleWipeCircle(this,i);
	}
//	m_wipes[7] = new CEffectSimpleWipeCircle(this,1);

	m_wipes[8] = new CEffectSimpleWipeWarp1(this);
	m_wipes[9] = new CEffectSimpleWipeClock(this);

	for (j=0;j<2;j++)
	{
		for (i=0;i<4;i++)
		{
			m_wipes[10+i+j*4] = new CEffectSimpleWipeMove(this,j,i);
		}
	}


	for (j=0;j<2;j++)
	{
		for (i=0;i<2;i++)
		{
			m_wipes[18+i+j*2] = new CEffectSimpleWipeDoor(this,j,i);
		}
	}

	m_wipes[22] = new CEffectSimpleWipeNurikae(this);
	m_wipes[23] = new CEffectSimpleWipeGrav(this);

	for (i=0;i<2;i++)
	{
		m_wipes[24+i] = new CEffectSimpleWipeGaza(this,i);
	}



	for (i=0;i<2;i++)
	{
		m_wipes[26+i] = new CEffectSimpleWipeRaster(this,i);
	}

	for (i=0;i<2;i++)
	{
		m_wipes[28+i] = new CEffectSimpleWipeStar(this,i);
	}

	for (i=0;i<2;i++)
	{
		m_wipes[30+i] = new CEffectSimpleWipeHeart(this,i);
	}

	for (i=0;i<2;i++)
	{
		m_wipes[32+i] = new CEffectSimpleWipeTurnStar(this,i);
	}

	for (i=0;i<2;i++)
	{
		m_wipes[34+i] = new CEffectSimpleWipeHahen(this,i);
	}

	for (i=0;i<2;i++)
	{
		m_wipes[36+i] = new CEffectSimpleWipeBeach(this,i);
	}

	m_wipes[38] = new CEffectSimpleWipeMozaic(this);
	m_wipes[39] = new CEffectSimpleWipeRandomStrip(this);
	m_wipes[40] = new CEffectSimpleWipeAdd(this);
	m_wipes[41] = new CEffectSimpleWipeMekuri(this);

	for (j=0;j<3;j++)	//type
	{
		for (i=0;i<2;i++)
		{
			m_wipes[42+i+j*2] = new CEffectSimpleWipeSudare(this,i,j);//方向、タイプの順
		}
	}

	for (j=0;j<2;j++)
	{
		for (i=0;i<3;i++)
		{
			int gradSize = 32<<(i+1);
			int k = i+j*3;
			m_wipes[48+k] = new CEffectSimpleWipeGaza(this,j,TRUE,gradSize);
		}
	}

	for (j=0;j<2;j++)
	{
		for (i=0;i<3;i++)
		{
			int gradSize = 32<<(i+1);
			int k = i+j*3;
			m_wipes[54+k] = new CEffectSimpleWipeBeach(this,j,TRUE,gradSize);
		}
	}

	m_wipes[60] = new CEffectSimpleWipeMulti(this);

	for (i=0;i<4;i++)
	{
		m_wipes[61+i] = new CEffectSimpleWipeTokoroten(this,i);
	}

	for (i=0;i<4;i++)
	{
		int gradSize = 32<<1;
		m_wipes[65+i] = new CEffectSimpleWipeNaname(this,i,TRUE,gradSize);
	}

	for (i=0;i<4;i++)
	{
		m_wipes[69+i] = new CEffectSimpleWipeSlot(this,i+2);
	}

	m_wipes[73] = new CEffectSimpleWipeGrav(this,1);

	for (i=0;i<4;i++)
	{
		m_wipes[74+i] = new CEffectSimpleWipeSlot(this,i+2,1);
	}

	for (i=0;i<2;i++)
	{
		m_wipes[78+i] = new CEffectSimpleWipeTurnStar(this,i,1);
	}

	for (i=0;i<4;i++)
	{
		m_wipes[80+i] = new CEffectSimpleWipeZoom(this,i,0);
	}

	for (j=0;j<2;j++)
	{
		for (i=0;i<2;i++)
		{
			m_wipes[84+j*2+i] = new CEffectSimpleWipeCenter(this,i,j);
		}
	}

	for (i=0;i<2;i++)
	{
		m_wipes[88+i] = new CEffectSimpleWipeTogari(this,i);
	}

	for (j=0;j<2;j++)
	{
		for (i=0;i<2;i++)
		{
			int gradSize = 32<<(i*2+1);
			int k = i+j*2;
			m_wipes[90+k] = new CEffectSimpleWipeTogari(this,j,TRUE,gradSize);
		}
	}

	for (i=0;i<2;i++)
	{
		m_wipes[94+i] = new CEffectSimpleWipeWTogari(this,i);
	}
}


CAllSimpleWipe::~CAllSimpleWipe()
{
	End();
}

void CAllSimpleWipe::End(void)
{
	DELETEARRAY(m_randomTableY2);
	DELETEARRAY(m_randomTableX2);
	DELETEARRAY(m_shapeWork);

	if (m_wipes != NULL)
	{
		for (int i=m_wipeKosuuMax-1;i>=0;i--)
		{
			ENDDELETECLASS(m_wipes[i]);
		}
		DELETEARRAY(m_wipes);
	}
}


int* CAllSimpleWipe::GetRandomTableX(void)
{
	if (m_randomTableX2 == NULL) CreateRandomTableX();
	return m_randomTableX2;
}

int* CAllSimpleWipe::GetRandomTableY(void)
{
	if (m_randomTableY2 == NULL) CreateRandomTableY();
	return m_randomTableY2;
}


void CAllSimpleWipe::CreateRandomTableX(void)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();

	if (m_randomTableX2 == NULL)
	{
		m_randomTableX2 = new int[screenSizeX * 2];
	}

	if (m_randomTableX2 == NULL) return;

	for (int i=0;i<screenSizeX*2;i++)
	{
		m_randomTableX2[i] = rand() & 0x7fff;
	}
}

void CAllSimpleWipe::CreateRandomTableY(void)
{
	int screenSizeY = CMyGraphics::GetScreenSizeY();
	if (m_randomTableY2 == NULL)
	{
		m_randomTableY2 = new int[screenSizeY * 2];
	}

	if (m_randomTableY2 == NULL) return;

	for (int i=0;i<screenSizeY*2;i++)
	{
		m_randomTableY2[i] = rand() & 0x7fff;
	}
}




void CAllSimpleWipe::PrintWipe(int n,CPicture* lpPicStart,CPicture* lpPicEnd,int count,int countMax,POINT* lpStartPoint,POINT* lpEndPoint)
{
	if ((n<0) || (n>m_wipeKosuuMax)) return;

	CEffectSimpleWipeCommon* lpWipe = GetWipeObject(n);
	if (lpWipe == NULL) return;

	lpWipe->Print(lpPicStart,lpPicEnd,count,countMax,lpStartPoint,lpEndPoint);
}


CEffectSimpleWipeCommon* CAllSimpleWipe::GetWipeObject(int n)
{
	return m_wipes[n];
}


int* CAllSimpleWipe::GetShapeWork(void)
{
	return m_shapeWork;
}

/*_*/

