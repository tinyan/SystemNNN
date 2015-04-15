#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"


#include "..\nnnUtilLib\nameList.h"

#include "autoSaveSubData.h"
#include "animeControl.h"
#include "faceControl.h"

char CFaceControl::m_defaultTag[] = "ta_sys_face";

CFaceControl::CFaceControl(CNameList* nameList,int faceMax) : CAutoSaveSubData(1024)
{
	m_nameList = nameList;

	m_setup = new CNameList();
	m_setup->LoadInit("face");

	m_animeControl = new CAnimeControl();

	m_faceMax = m_nameList->GetNameKosuu() / 2;
	m_faceType = new int[m_faceMax + 1];
	Clear();

	m_face[0] = -1;
	m_face[1] = -1;
	m_facePicNumber = -1;
	m_facePicSubNumber = -1;
	m_lastSetFace = -1;
	m_facePrintNumber = 1;

	m_pic = new CPicture();
	m_player2Pic = new CPicture();

	m_sizeX = 160;
	m_sizeY = 160;
	int printX = 10;
	int printY = 400;

	GetInitGameParam(&m_facePrintNumber,"facePrintNumber");

	GetInitGameParam(&printX,"printX");
	GetInitGameParam(&printY,"printY");
	m_printX[0] = printX;
	m_printY[0] = printY;
	GetInitGameParam(&printX,"printX2");
	GetInitGameParam(&printY,"printY2");
	m_printX[1] = printX;
	m_printY[1] = printY;


	GetInitGameParam(&m_sizeX,"sizeX");
	GetInitGameParam(&m_sizeY,"sizeY");

	m_tagName = m_defaultTag;
	GetInitGameString(&m_tagName,"filenameTag");

	m_customTagName = new LPSTR[m_faceMax + 1];
	m_customTagFlag = 0;
	GetInitGameParam(&m_customTagFlag,"customFaceNameFlag");

	m_customTagName[0] = NULL;
	for (int i=1;i<=m_faceMax;i++)
	{
		m_customTagName[i] = NULL;

		if (m_customTagFlag)
		{
			LPSTR tagName = m_tagName;
			char name[256];
			sprintf_s(name,sizeof(name),"filenameFace%d",i);
			if (GetInitGameString(&tagName,name))
			{
				m_customTagName[i] = tagName;
			}
		}
	}



	m_faceTypeKosuu = new int[m_faceMax + 1];
	m_faceTypeKosuu[0] = 1;
	int kosuu = 1;
	for (int i=1;i<=m_faceMax;i++)
	{
		char name[256];
		sprintf_s(name,sizeof(name),"faceType%d",i);//for old version
		GetInitGameParam(&kosuu,name);
		sprintf_s(name,sizeof(name),"face%dTypeNumber",i);
		GetInitGameParam(&kosuu,name);
		if (kosuu < 1) kosuu = 1;
		m_faceTypeKosuu[i] = kosuu;
	}


	m_faceParam = new int*[m_faceMax+1];

	for (int j=0;j<=m_faceMax;j++)
	{
		int animeType = 1;
		int animePattern = 1;
		int animeSpeed = 1;
		int waitMin = 0;
		int waitMax = 0;

		int n = m_faceTypeKosuu[j];
		m_faceParam[j] = new int[8 * (n+1)];

		for (int i=0;i<=n;i++)
		{
			char name[256];
			sprintf_s(name,sizeof(name),"face%dType%danimePattern",j,i);
			GetInitGameParam(&animePattern,name);
			if (animePattern > 1)
			{
				sprintf_s(name,sizeof(name),"face%dType%danimeType",j,i);
				GetInitGameParam(&animeType,name);
				sprintf_s(name,sizeof(name),"face%dType%danimeSpeed",j,i);
				GetInitGameParam(&animeSpeed,name);
				sprintf_s(name,sizeof(name),"face%dType%dWaitMin",j,i);
				GetInitGameParam(&waitMin,name);
				sprintf_s(name,sizeof(name),"face%dType%dWaitMax",j,i);
				GetInitGameParam(&waitMax,name);
			}

			m_faceParam[j][i*8 + 0] = animePattern;
			m_faceParam[j][i*8 + 1] = animeType;
			m_faceParam[j][i*8 + 2] = animeSpeed;
			m_faceParam[j][i*8 + 3] = waitMin;
			m_faceParam[j][i*8 + 4] = waitMax;

			m_faceParam[j][i*8 + 5] = 0;
			m_faceParam[j][i*8 + 6] = 0;
			m_faceParam[j][i*8 + 7] = 0;
		}
	}




	m_animeParamInitFlag = FALSE;


	//dummy
	m_maxSaveData = 256;
	GetInitGameParam(&m_maxSaveData,"maxSave");
	if (m_maxSaveData < (m_faceMax+1))
	{
		m_maxSaveData = m_faceMax + 1;
	}

	int size = m_maxSaveData * sizeof(int);
	SetDataSize(size);
}

CFaceControl::~CFaceControl()
{
	End();
}

void CFaceControl::End(void)
{
	if (m_faceParam != NULL)
	{
		for (int i=0;i<=m_faceMax;i++)
		{
			DELETEARRAY(m_faceParam[i]);
		}
		DELETEARRAY(m_faceParam);
	}

	DELETEARRAY(m_faceTypeKosuu);
	DELETEARRAY(m_customTagName);

	ENDDELETECLASS(m_player2Pic);
	ENDDELETECLASS(m_pic);
	DELETEARRAY(m_faceType);
	ENDDELETECLASS(m_animeControl);
	ENDDELETECLASS(m_setup);

}

void CFaceControl::Clear(void)
{
	m_lastSetFace = -1;
	m_mustFace = 0;
	m_koteiFace = 0;
	m_koteiType = 0;
	m_koteiYoyaku = FALSE;

	for (int i=0;i<=m_faceMax;i++)
	{
		m_faceType[i] = 1;
	}

	m_face[0] = -1;
	m_face[1] = -1;


	m_startCount = 0;
	m_startCountMax = 0;
	m_animeControl->Init();
	m_animeParamInitFlag = FALSE;
}


void CFaceControl::ChangeFace(int face,int type)
{
	m_lastSetFace = face;

	int waitMin = 0;
	int waitMax = 0;

	int animePattern = 1;
	int animeSpeed = 1;
	int animeType = 1;

//	m_count = 0;
	m_startCount = 0;
	m_startCountMax = 0;

	if ((face > 0) && (face <= m_faceMax))
	{
		m_faceType[face] = type;
		if ((type > 0) && (type <= m_faceTypeKosuu[face]))
		{
			animePattern = m_faceParam[face][type*8+0];
			animeType = m_faceParam[face][type*8+1];
			animeSpeed = m_faceParam[face][type*8+2];
			waitMin = m_faceParam[face][type*8+3];
			waitMax = m_faceParam[face][type*8+4];

			int dv = waitMax - waitMin;
			if (dv<0) dv = 0;
			dv++;
			m_startCountMax = rand() % dv;
			m_startCountMax += waitMin;
		}
	}

	m_animeControl->SetParam(animeType,animePattern,animeSpeed);
	m_animeControl->Init();

	m_animeParamInitFlag = TRUE;
}

void CFaceControl::MustFace(int mustFace)
{
	int must = mustFace & 0xffff;
	int kotei = mustFace >> 16;

	m_mustFace = must;
	if (mustFace != 0)
	{
		m_koteiType = kotei;
		if (m_koteiType != 0)
		{
			m_koteiYoyaku = TRUE;
		}
	}
}


void CFaceControl::Print(LPSTR name)
{
	int leftRight = 0;

	int face = -1;

	if (m_mustFace > 0)
	{
		face = m_mustFace;
	}
	else
	{
		face = m_nameList->SearchBlock(name,2,TRUE,1);
	}

	if (face < 1) return;
	if (m_faceType[face] < 1) return;
	if (face > m_faceMax) return;

	if (m_koteiYoyaku)
	{
		m_koteiYoyaku = FALSE;
		m_koteiFace = face;
	}


	if (m_facePrintNumber >= 2)
	{
		if (m_koteiType != 0)
		{
			if (face == m_koteiFace)
			{
				if (m_koteiType == 1)
				{
					leftRight = 0;
				}
				else if (m_koteiType == 2)
				{
					leftRight = 1;
				}
				else if (m_koteiType == 3)
				{
					//search ?
					if (m_face[0] == face)
					{
						leftRight = 0;
					}
					else if (m_face[1] == face)
					{
						leftRight = 1;
					}
				}

			}
			else
			{
				if (m_koteiType == 1)
				{
					if ((m_face[0] == m_koteiFace) && (m_koteiFace != -1))
					{
						leftRight = 1;
					}
					else
					{
						leftRight = 0;
					}
				}
				else if ((m_koteiType == 2) && (m_koteiFace != -1))
				{
					if (m_face[1] == m_koteiFace)
					{
						leftRight = 0;
					}
					else
					{
						leftRight = 0;
					}
				}
				else if (m_koteiType == 3)
				{
					if ((m_face[0] == m_koteiFace) && (m_koteiFace != -1))
					{
						leftRight = 1;
					}
					else
					{
						leftRight = 0;
					}
				}
			}
		}
	}

	//‚¨‚µ‚¾‚µ
	int oshidashi = m_face[leftRight];
	if (oshidashi != -1)
	{
		if (oshidashi != face)
		{
			if ((m_face[1-leftRight] != m_koteiFace) || (m_face[1-leftRight] == -1))
			{
				m_face[1-leftRight] = oshidashi;
			}
		}
	}

	m_face[leftRight] = face;






	LoadPic(m_face[leftRight],m_faceType[m_face[leftRight]]);

	if ((m_animeParamInitFlag == FALSE) || (m_face[leftRight] != m_lastSetFace))
	{
		ChangeFace(m_face[leftRight],m_faceType[m_face[leftRight]]);
	}



	int printX = m_printX[leftRight];
	int printY = m_printY[leftRight];

	//print
	int pic1 = 0;
	int pic2 = 0;
	int ps = 100;

	int count = 0;
	if (m_startCount < m_startCountMax)
	{
		m_startCount++;
	}
	else
	{
		pic1 = m_animeControl->GetAnimePic1();
		pic2 = m_animeControl->GetAnimePic2();
		ps = m_animeControl->GetAnimePercent();

		if (m_animeControl->Calcu())
		{
			int type = m_faceType[m_face[leftRight]];
			if (m_faceParam[m_face[leftRight]][type*8+4] > 0)
			{

				int waitMin = m_faceParam[m_face[leftRight]][type*8+3];
				int waitMax = m_faceParam[m_face[leftRight]][type*8+4];

				int dv = waitMax - waitMin;
				if (dv<0) dv = 0;
				dv++;
				m_startCountMax = rand() % dv;
				m_startCountMax += waitMin;

				m_startCount = 0;
				m_animeControl->Init();
			}
		}
	}


	SIZE sz = m_pic->GetPicSize();
	int yokoKosuu = sz.cx / m_sizeX;
	if (yokoKosuu < 1) yokoKosuu = 1;

	int pic1nx = pic1 % yokoKosuu;
	int pic1ny = pic1 / yokoKosuu;
	int pic2nx = pic2 % yokoKosuu;
	int pic2ny = pic2 / yokoKosuu;

	int srcX1 = pic1nx * m_sizeX;
	int srcY1 = pic1ny * m_sizeY;
	int srcX2 = pic2nx * m_sizeX;
	int srcY2 = pic2ny * m_sizeY;

	if (ps == 100)
	{
		m_pic->Blt(printX,printY,srcX1,srcY1,m_sizeX,m_sizeY,TRUE);
	}
	else if (ps > 0)
	{
		m_pic->ChangeTranslateBlt(printX,printY,srcX1,srcY1,m_sizeX,m_sizeY,ps,100-ps,m_pic,srcX2,srcY2);
	}
	else
	{
		m_pic->Blt(printX,printY,srcX2,srcY2,m_sizeX,m_sizeY,TRUE);
	}

	//player 2?
	if (m_facePrintNumber >= 2)
	{
		int player2 = m_face[1-leftRight];
		if (player2 != -1)
		{
			//loadpic
			int type2 = m_faceType[player2];
			if (LoadPlayer2Pic(player2,type2))
			{
				//print first anime parts
				int printX2 = m_printX[1-leftRight];
				int printY2 = m_printY[1-leftRight];

				m_player2Pic->Blt(printX2,printY2,0,0,m_sizeX,m_sizeY,TRUE);
			}
		}
	}
}


BOOL CFaceControl::LoadPic(int face,int faceSubNumber)
{
	if ((face == m_facePicNumber) && (faceSubNumber == m_facePicSubNumber))
	{
		return TRUE;
	}

	m_facePicNumber = face;
	m_facePicSubNumber = faceSubNumber;


	char filename[1024];
	LPSTR tagName = NULL;

	if ((face >= 0) && (face <= m_faceMax))
	{
		tagName = m_customTagName[face];
	}

	if (m_facePicSubNumber < 2)
	{
		if (tagName == NULL)
		{
			sprintf_s(filename,sizeof(filename),"sys\\%s%d",m_tagName,m_facePicNumber);
		}
		else
		{
			sprintf_s(filename,sizeof(filename),"sys\\%s",tagName);
		}
	}
	else
	{
		if (tagName == NULL)
		{
			sprintf_s(filename,sizeof(filename),"sys\\%s%d__%d",m_tagName,m_facePicNumber,m_facePicSubNumber);
		}
		else
		{
			sprintf_s(filename,sizeof(filename),"sys\\%s__%d",tagName,m_facePicSubNumber);
		}
	}


	return m_pic->LoadDWQ(filename);

}


BOOL CFaceControl::LoadPlayer2Pic(int face,int faceSubNumber)
{
	char filename[1024];
	LPSTR tagName = NULL;

	if ((face >= 0) && (face <= m_faceMax))
	{
		tagName = m_customTagName[face];
	}

	if (faceSubNumber < 2)
	{
		if (tagName == NULL)
		{
			sprintf_s(filename,sizeof(filename),"sys\\%s%d",m_tagName,face);
		}
		else
		{
			sprintf_s(filename,sizeof(filename),"sys\\%s",tagName);
		}
	}
	else
	{
		if (tagName == NULL)
		{
			sprintf_s(filename,sizeof(filename),"sys\\%s%d__%d",m_tagName,face,faceSubNumber);
		}
		else
		{
			sprintf_s(filename,sizeof(filename),"sys\\%s__%d",tagName,faceSubNumber);
		}
	}

	return m_player2Pic->LoadDWQ(filename);

}

BOOL CFaceControl::GetInitGameParam(int* lpVar, LPSTR name,int initData)
{
	*lpVar = initData;
	return GetInitGameParam(lpVar,name);
}

BOOL CFaceControl::GetInitGameParam(int* lpVar, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpVar = atoi(m_setup->GetName(rNum + 1));

	return TRUE;
}

BOOL CFaceControl::GetInitGameString(LPSTR* lpStr, LPSTR name,LPSTR initString)
{
	*lpStr = initString;
	return GetInitGameString(lpStr,name);
}

BOOL CFaceControl::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_setup->GetName(rNum + 1);

	return TRUE;
}


void CFaceControl::GetExtDataForSave(LPVOID ptr,int extNumber)
{
	m_faceType[0] = m_mustFace;
	m_faceType[255] = m_koteiType;
	m_faceType[254] = m_koteiFace;
	m_faceType[253] = m_face[0];
	m_faceType[252] = m_face[1];

	memcpy(ptr,m_faceType,(m_faceMax+1) * sizeof(int));
}



void CFaceControl::SetExtDataByLoad(LPVOID ptr,int extNumber)
{
	memcpy(m_faceType,ptr,(m_faceMax+1) * sizeof(int));
	m_mustFace = m_faceType[0];
	m_koteiType = m_faceType[255];
	m_koteiFace = m_faceType[254];
	m_face[0] = m_faceType[253];
	m_face[1] = m_faceType[252];

	m_animeParamInitFlag = FALSE;
}



/*_*/

