//
// suuji.cpp
//

#include <windows.h>
#include <stdio.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"


#include "..\nnnUtilLib\nameList.h"
#include "..\nnnUtilLib\systemPicture.h"


#include "suuji.h"

CSuuji::CSuuji(CPicture* lpPic, int sizeX, int sizeY, int keta, int nextX, BOOL upZeroFlag, BOOL transFlag, BOOL leftFlag)
{
	m_sizeX = sizeX;
	m_sizeY = sizeY;
	m_keta = keta;
	m_upZeroFlag = upZeroFlag;
	m_transFlag = transFlag;
	m_leftFlag = leftFlag;
	m_pic = lpPic;
	
	if (nextX == -9999) nextX = m_sizeX;

	m_nextX = nextX;
	m_nextY = 0;

	m_picCreateFlag = FALSE;
}

CSuuji::CSuuji(CNameList* lpSetup,LPSTR tagName,BOOL picCreateFlag)
{
	m_setup = lpSetup;
	m_picCreateFlag = picCreateFlag;


	char name[1024];

	int sizeX = 16;
	int sizeY = 16;
	int keta = 2;
	int upZeroFlag = 0;
	int transFlag = 1;
	int leftFlag = 0;

	sprintf_s(name,sizeof(name),"%sFontSizeX",tagName);
	GetInitGameParam(&sizeX,name);
	sprintf_s(name,sizeof(name),"%sFontSizeY",tagName);
	GetInitGameParam(&sizeY,name);
	sprintf_s(name,sizeof(name),"%sKeta",tagName);
	GetInitGameParam(&keta,name);
	sprintf_s(name,sizeof(name),"%sUpZeroFlag",tagName);
	GetInitGameParam(&upZeroFlag,name);
	sprintf_s(name,sizeof(name),"%sLeftFlag",tagName);
	GetInitGameParam(&leftFlag,name);
	sprintf_s(name,sizeof(name),"%sTransFlag",tagName);
	GetInitGameParam(&transFlag,name);

	int nextX = sizeX;
	int nextY = 0;
	sprintf_s(name,sizeof(name),"%sNextX",tagName);
	GetInitGameParam(&nextX,name);
//	sprintf_s(name,"%sNextY",tagName);
//	GetInitGameParam(&nextY,name);


	LPSTR picName = NULL;
	sprintf_s(name,sizeof(name),"filename%s",tagName);
	GetInitGameString(&picName,name);


	m_sizeX = sizeX;
	m_sizeY = sizeY;
	m_keta = keta;
	m_upZeroFlag = upZeroFlag;
	m_transFlag = transFlag;
	m_leftFlag = leftFlag;
	m_nextX = nextX;
	m_nextY = nextY;



	if (picCreateFlag)
	{
		char filename[1024];
		sprintf_s(filename,sizeof(filename),"sys\\%s",picName);
		m_pic = new CPicture(filename);
	}
	else
	{
		m_pic = CSystemPicture::GetSystemPicture(picName);
	}
}



CSuuji::~CSuuji()
{
	End();
}


void CSuuji::End(void)
{
	if (m_picCreateFlag)
	{
		m_picCreateFlag = FALSE;
		ENDDELETECLASS(m_pic);
	}
}


void CSuuji::Print(int printX, int printY, int dat, int keta,int col)
{
	if (m_pic == NULL) return;
	if (keta == -1) keta = m_keta;

	if (m_leftFlag)
	{
		if (dat < 0) return;	//not support

		int putX = printX;
		int putY = printY;

		int dv = 1;
		int i = 1;
		for (i=1;i<keta;i++)
		{
			dv *= 10;
		}

		BOOL b = FALSE;

		for (i=0;i<keta;i++)
		{
			int d = dat / dv;

			if ((d != 0) || (i == (keta-1)) || (b) || m_upZeroFlag)
			{
				b = TRUE;
				Put(putX,putY,d,col);
				putX += m_nextX;
				putY += m_nextY;
			}

			dat -= d * dv;
			dv /= 10;

//			if ((dat == 0) && (m_upZeroFlag == FALSE))return;
		}
	}
	else
	{
		if (dat < 0) return;	//not support

		int putX = printX + (keta - 1) * m_nextX;
		int putY = printY + (keta - 1) * m_nextY;

		for (int i=0;i<keta;i++)
		{
			int d = dat % 10;
			if ((d != 0) || (i == 0) || (dat > 0) || m_upZeroFlag)
			{
				Put(putX,putY,d,col);
			}

			putX -= m_nextX;
			putY -= m_nextY;

			dat /= 10;

			if ((dat == 0) && (m_upZeroFlag == FALSE))return;
		}
	}
}


void CSuuji::Put(int printX, int printY, int ch,int col)
{
	if (m_pic == NULL) return;
	int srcX = ch * m_sizeX;
	int srcY = col * m_sizeY;
	m_pic->Blt(printX,printY,srcX,srcY,m_sizeX,m_sizeY,m_transFlag);
}

void CSuuji::AppearPrint(int count, int countMax, int type, int printX, int printY, int dat, int keta, int col)
{
	int dv = countMax;
	if (dv < 1) dv = 1;

	int percent = 100;
	if (type & 1)
	{
		percent = (100 * count) / dv;
		if (percent < 0) percent = 0;
		if (percent > 100) percent = 100;
	}

	if (m_pic == NULL) return;
	if (keta == -1) keta = m_keta;

	if (m_leftFlag)
	{
		if (dat < 0) return;	//not support

		int putX = printX;
		int putY = printY;

		int dv = 1;
		int i = 1;
		for (i = 1; i < keta; i++)
		{
			dv *= 10;
		}

		BOOL b = FALSE;

		for (i = 0; i < keta; i++)
		{
			int d = dat / dv;

			if ((d != 0) || (i == (keta - 1)) || (b) || m_upZeroFlag)
			{
				b = TRUE;
//				Put(putX, putY, d, col);
				AppearPut(count,countMax,type,putX, putY, d, col);
				putX += m_nextX;
				putY += m_nextY;
			}

			dat -= d * dv;
			dv /= 10;

			//			if ((dat == 0) && (m_upZeroFlag == FALSE))return;
		}
	}
	else
	{
		if (dat < 0) return;	//not support

		int putX = printX + (keta - 1) * m_nextX;
		int putY = printY + (keta - 1) * m_nextY;

		for (int i = 0; i < keta; i++)
		{
			int d = dat % 10;
			if ((d != 0) || (i == 0) || (dat > 0) || m_upZeroFlag)
			{
//				Put(putX, putY, d, col);
				AppearPut(count,countMax,type,putX, putY, d, col);
			}

			putX -= m_nextX;
			putY -= m_nextY;

			dat /= 10;

			if ((dat == 0) && (m_upZeroFlag == FALSE))return;
		}
	}

}


void CSuuji::AppearPut(int count, int countMax, int type, int printX, int printY, int ch, int col)
{
	if (m_pic == NULL) return;

	int dv = countMax;
	if (dv < 1) dv = 1;

	int percent = 100;
	if (type & 1)
	{
		percent = (100 * count) / dv;
		if (percent < 0) percent = 0;
		if (percent > 100) percent = 100;
	}


	int srcX = ch * m_sizeX;
	int srcY = col * m_sizeY;
//	m_pic->Blt(printX, printY, srcX, srcY, m_sizeX, m_sizeY, m_transFlag);
	m_pic->TransLucentBlt3(printX, printY, srcX, srcY, m_sizeX, m_sizeY, percent);
}



BOOL CSuuji::GetInitGameParam(int* lpVar, LPSTR name,int initData)
{
	*lpVar = initData;
	return GetInitGameParam(lpVar,name);
}

BOOL CSuuji::GetInitGameParam(int* lpVar, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpVar = atoi(m_setup->GetName(rNum + 1));

	return TRUE;
}

BOOL CSuuji::GetInitGameString(LPSTR* lpStr, LPSTR name,LPSTR initString)
{
	*lpStr = initString;
	return GetInitGameString(lpStr,name);
}

BOOL CSuuji::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_setup->GetName(rNum + 1);

	return TRUE;
}

/*_*/

