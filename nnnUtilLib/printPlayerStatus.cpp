#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"


#include "..\nnnUtilLib\nameList.h"

#include "commonAnimeParts.h"
#include "suuji.h"
#include "autoSaveSubData.h"
#include "okikaeData.h"
#include "mymessage.h"

#include "printPlayerStatus.h"


#define MYVARTYPE_GENERAL 0
#define MYVARTYPE_PLACETYPE 1
#define MYVARTYPE_FACE 2
#define MYVARTYPE_TEXT 3
#define MYVARTYPE_NUM 4
#define MYVARTYPE_BAR 5
#define MYVARTYPE_ETCNUM 6


CPrintPlayerStatus::CPrintPlayerStatus(CMyMessage* message)
{

	m_message = message;

	m_setup = new CNameList();
	m_setup->LoadInit("faceStatusList");


	m_plateSizeX = 100;
	m_plateSizeY = 60;
	GetInitGameParam(&m_plateSizeX, "plateSizeX");
	GetInitGameParam(&m_plateSizeY, "plateSizeY");

	m_facePrintX = 0;
	m_facePrintY = 0;
	GetInitGameParam(&m_facePrintX, "facePrintX");
	GetInitGameParam(&m_facePrintY, "facePrintY");


	m_etcNumber = 0;
	GetInitGameParam(&m_etcNumber, "etcNumber");

	m_plateTypeNumber = 1;
	GetInitGameParam(&m_plateTypeNumber, "plateTypeNumber");
	m_statusPlateParam = new STATUSPLATEPARAM[m_plateTypeNumber];
	for (int i = 0; i < m_plateTypeNumber; i++)
	{
		char name[256];

		int plateNumX = 5;
		int plateNumY = 2;
		sprintf_s(name, 256, "plate%dNumX", i + 1);
		GetInitGameParam(&plateNumX, name);
		sprintf_s(name, 256, "plate%dNumY", i + 1);
		GetInitGameParam(&plateNumY, name);
		m_statusPlateParam[i].numX = plateNumX;
		m_statusPlateParam[i].numY = plateNumY;

		int plateNextX = 100;
		int plateNextY = 60;
		sprintf_s(name, 256, "plate%dNextX", i + 1);
		GetInitGameParam(&plateNextX, name);
		sprintf_s(name, 256, "plate%dNextY", i + 1);
		GetInitGameParam(&plateNextY, name);
		m_statusPlateParam[i].nextX = plateNextX;
		m_statusPlateParam[i].nextY = plateNextY;

		int platePrintX = 100;
		int platePrintY = 50;
		sprintf_s(name, 256, "plate%dPrintX", i + 1);
		GetInitGameParam(&platePrintX, name);
		sprintf_s(name, 256, "plate%dPrintY", i + 1);
		GetInitGameParam(&platePrintY, name);
		m_statusPlateParam[i].printX = platePrintX;
		m_statusPlateParam[i].printY = platePrintY;

	}




	m_charaNumber = 1;
	GetInitGameParam(&m_charaNumber, "charaNumber");
	m_textNumber = 0;
	GetInitGameParam(&m_textNumber, "textNumber");
	m_suujiNumber = 0;
	GetInitGameParam(&m_suujiNumber, "suujiNumber");
	m_barNumber = 0;
	GetInitGameParam(&m_barNumber, "barNumber");

	m_statusTextParam = NULL;
	if (m_textNumber > 0)
	{
		m_statusTextParam = new STATUSTEXTPARAM[m_textNumber];
		for (int i = 0; i < m_textNumber; i++)
		{
			int printX = 0;
			int printY = 0;
			int fontSize = 16;
			int colorR = 255;
			int colorG = 255;
			int colorB = 255;
			int textType = 0;
			char name[256];
			sprintf_s(name, 256, "text%dPrintX", i + 1);
			GetInitGameParam(&printX, name);
			sprintf_s(name, 256, "text%dPrintY", i + 1);
			GetInitGameParam(&printY, name);
			sprintf_s(name, 256, "text%dFontSize", i + 1);
			GetInitGameParam(&fontSize, name);
			sprintf_s(name, 256, "text%dColorR", i + 1);
			GetInitGameParam(&colorR, name);
			sprintf_s(name, 256, "text%dColorG", i + 1);
			GetInitGameParam(&colorG, name);
			sprintf_s(name, 256, "text%dColorB", i + 1);
			GetInitGameParam(&colorB, name);
			sprintf_s(name, 256, "text%dType", i + 1);
			GetInitGameParam(&textType, name);

			m_statusTextParam[i].printX = printX;
			m_statusTextParam[i].printY = printY;
			m_statusTextParam[i].fontSize = fontSize;
			m_statusTextParam[i].fontColorR = colorR;
			m_statusTextParam[i].fontColorG = colorG;
			m_statusTextParam[i].fontColorB = colorB;
			m_statusTextParam[i].textType = textType;

			int messageNumber = 1;
			sprintf_s(name, 256, "text%dMessageNumber", i + 1);
			GetInitGameParam(&messageNumber, name);
			m_statusTextParam[i].messageNumber = messageNumber;

			m_statusTextParam[i].message = new LPSTR[m_charaNumber*messageNumber];
			for (int c = 0; c < m_charaNumber; c++)
			{
				for (int k = 0; k < messageNumber; k++)
				{
					sprintf_s(name, 256, "text%dMessage%d_%d", i + 1, c + 1, k + 1);
					LPSTR mes = NULL;
					GetInitGameString(&mes, name);
					m_statusTextParam[i].message[c*messageNumber + k] = mes;
				}
			}

		}
	}

	m_statusSuujiParam = NULL;
	if (m_suujiNumber > 0)
	{
		m_statusSuujiParam = new STATUSSUUJIPARAM[m_suujiNumber];
		for (int i = 0; i < m_suujiNumber; i++)
		{
			char name[256];
			int printX = 0;
			int printY = 0;
			sprintf_s(name, 256, "suuji%dPrintX", i + 1);
			GetInitGameParam(&printX, name);
			sprintf_s(name, 256, "suuji%dPrintY", i + 1);
			GetInitGameParam(&printY, name);

			m_statusSuujiParam[i].printX = printX;
			m_statusSuujiParam[i].printY = printY;

			char tagName[256];
			sprintf_s(tagName, 256, "suuji%d", i + 1);
			m_statusSuujiParam[i].suuji = new CSuuji(m_setup, tagName, true);
		}
	}

	m_statusBarParam = NULL;
	if (m_barNumber > 0)
	{
		m_statusBarParam = new STATUSBARPARAM[m_barNumber];

		for (int i = 0; i < m_barNumber; i++)
		{
			int basePrintX = 0;
			int basePrintY = 0;
			int printX = 2;
			int printY = 2;
			int sizeX = 50;
			int sizeY = 10;

			char name[256];
			sprintf_s(name, 256, "bar%dBasePrintX", i + 1);
			GetInitGameParam(&basePrintX, name);
			sprintf_s(name, 256, "bar%dBasePrintY", i + 1);
			GetInitGameParam(&basePrintY, name);
			sprintf_s(name, 256, "bar%dPrintX", i + 1);
			GetInitGameParam(&printX, name);
			sprintf_s(name, 256, "bar%dPrintY", i + 1);
			GetInitGameParam(&printY, name);
			sprintf_s(name, 256, "bar%dSizeX", i + 1);
			GetInitGameParam(&sizeX, name);
			sprintf_s(name, 256, "bar%dSizeY", i + 1);
			GetInitGameParam(&sizeY, name);


			CPicture* basePic = NULL;
			CPicture* barPic = NULL;

			LPSTR baseFilename = NULL;
			sprintf_s(name, 256, "bar%dBaseFilename", i + 1);
			GetInitGameString(&baseFilename, name);
			if (baseFilename)
			{
				char filename[1024];
				sprintf_s(filename, 1024, "sys\\%s", baseFilename);
				basePic = new CPicture();
				basePic->LoadDWQ(filename);
			}

			LPSTR barFilename = NULL;
			sprintf_s(name, 256, "bar%dFilename", i + 1);
			GetInitGameString(&barFilename, name);
			if (barFilename)
			{
				char filename[1024];
				sprintf_s(filename, 1024, "sys\\%s", barFilename);
				barPic = new CPicture();
				barPic->LoadDWQ(filename);
			}


			m_statusBarParam[i].basePrintX = basePrintX;
			m_statusBarParam[i].basePrintY = basePrintY;
			m_statusBarParam[i].printX = printX;
			m_statusBarParam[i].printY = printY;
			m_statusBarParam[i].sizeX = sizeX;
			m_statusBarParam[i].sizeY = sizeY;

			m_statusBarParam[i].basePic = basePic;
			m_statusBarParam[i].barPic = barPic;


		}

	}


	m_faceAnimePic = new CCommonAnimeParts*[m_charaNumber];
	for (int i = 0; i < m_charaNumber; i++)
	{
		char name[256];
		for (int k = 0; k < 1; k++)
		{
			sprintf_s(name, 256, "face%d_%d", i + 1, k + 1);
			m_faceAnimePic[i] = new CCommonAnimeParts(name, m_setup, TRUE);
		}
	}


	m_generalVarData = new int[1 + m_charaNumber];
	m_generalVarNumber = new int[1 + m_charaNumber];
	for (int i = 0; i < m_charaNumber + 1; i++)
	{
		m_generalVarData[i] = 0;
		m_generalVarNumber[i] = -1;
	}
	m_faceVarNumber = new int[1 + m_charaNumber];
	m_faceVarData = new int[1 + m_charaNumber];
	for (int i = 0; i < m_charaNumber; i++)
	{
		m_faceVarData[i] = 0;
		m_faceVarNumber[i] = -1;
	}

	m_textVarNumber = new int*[1 + m_textNumber];
	m_textVarData = new int*[1 + m_textNumber];
	for (int i = 0; i < m_textNumber; i++)
	{
		m_textVarNumber[i] = new int[1 + m_charaNumber];
		m_textVarData[i] = new int[1 + m_charaNumber];
		for (int k = 0; k < m_charaNumber; k++)
		{
			m_textVarNumber[i][k] = -1;
			m_textVarData[i][k] = 0;
		}


	}

	m_suujiVarNumber = new int*[1 + m_suujiNumber];
	m_suujiVarData = new int*[1 + m_suujiNumber];
	for (int i = 0; i < m_suujiNumber; i++)
	{
		m_suujiVarNumber[i] = new int[1 + m_charaNumber];
		m_suujiVarData[i] = new int[1 + m_charaNumber];
		for (int k = 0; k < m_charaNumber; k++)
		{
			m_suujiVarNumber[i][k] = -1;
			m_suujiVarData[i][k] = 0;
		}
	}

	m_barVarNumber = new int*[1 + m_barNumber];
	m_barVarData = new int*[1 + m_barNumber];
	for (int i = 0; i < m_barNumber; i++)
	{
		m_barVarNumber[i] = new int[1 + m_charaNumber * 2];
		m_barVarData[i] = new int[1 + m_charaNumber * 2];
		for (int k = 0; k < m_charaNumber; k++)
		{
			m_barVarNumber[i][k * 2] = -1;
			m_barVarNumber[i][k * 2 + 1] = -1;
			m_barVarData[i][k * 2] = 0;
			m_barVarData[i][k * 2 + 1] = 100;
		}
	}

	m_etcVarNumber = new int[1 + m_etcNumber];
	m_etcVarData = new int[1 + m_etcNumber];
	for (int i = 0; i < m_etcNumber; i++)
	{
		m_etcVarNumber[i] = -1;
		m_etcVarData[i] = 0;
	}


	m_etcPlatePic = new CPicture*[1 + m_etcNumber];
	for (int i = 0; i < m_etcNumber + 1; i++)
	{
		m_etcPlatePic[i] = NULL;
	}

	m_etcPointDelta = new POINT[1 + m_etcNumber];

	m_etcSuuji = new CSuuji*[1 + m_etcNumber];
	for (int i = 0; i < m_etcNumber + 1; i++)
	{
		m_etcSuuji[i] = NULL;
	}

	if (true)
	{
		int deltaX = 0;
		int deltaY = 0;

		for (int i = 0; i < m_etcNumber; i++)
		{
			char name[256];
			sprintf_s(name, 256,"etc%dPlateFilename", i + 1);

			LPSTR fname = NULL;
			GetInitGameString(&fname, name);
			if (fname != NULL)
			{
				m_etcPlatePic[i] = new CPicture();
				char filename[256];
				sprintf_s(filename, 256, "sys\\%s", fname);
				m_etcPlatePic[i]->LoadDWQ(filename);
			}


			sprintf_s(name, 256, "etc%dPrintX", i + 1);
			GetInitGameParam(&deltaX, name);
			sprintf_s(name, 256, "etc%dPrintY", i + 1);
			GetInitGameParam(&deltaY, name);

			m_etcPointDelta[i].x = deltaX;
			m_etcPointDelta[i].y = deltaY;


			char tagName[256];
			sprintf_s(tagName, 256, "etc%dsuuji", i + 1);

			m_etcSuuji[i] = new CSuuji(m_setup, tagName, true);
		}
	}




	m_platePic = NULL;

	if (true)
	{
		LPSTR fname = NULL;
		GetInitGameString(&fname, "plateFilename");
		if (fname != NULL)
		{
			m_platePic = new CPicture();
			char filename[256];
			sprintf_s(filename, 256, "sys\\%s", fname);
			m_platePic->LoadDWQ(filename);
		}
	}

	for (int i = 0; i < 256; i++)
	{
		m_useMode[i] = 0;
	}
}




CPrintPlayerStatus::~CPrintPlayerStatus()
{
	End();

}

void CPrintPlayerStatus::End(void)
{

	if (m_etcSuuji)
	{
		for (int i = 0; i < m_etcNumber; i++)
		{
			ENDDELETECLASS(m_etcSuuji[i]);
		}
		DELETEARRAY(m_etcSuuji);
	}
	DELETEARRAY(m_etcPointDelta);

	if (m_etcPlatePic)
	{
		for (int i = 0; i < m_etcNumber; i++)
		{
			ENDDELETECLASS(m_etcPlatePic[i]);
		}
		DELETEARRAY(m_etcPlatePic);
	}
	ENDDELETECLASS(m_platePic);

	DELETEARRAY(m_etcVarData);
	DELETEARRAY(m_etcVarNumber);



	if (m_barVarData)
	{
		for (int i = 0; i < m_barNumber; i++)
		{
			DELETEARRAY(m_barVarData[i]);
		}
		DELETEARRAY(m_barVarData);
	}

	if (m_barVarNumber)
	{
		for (int i = 0; i < m_barNumber; i++)
		{
			DELETEARRAY(m_barVarNumber[i]);
		}
		DELETEARRAY(m_barVarNumber);
	}


	if (m_suujiVarData)
	{
		for (int i = 0; i < m_suujiNumber; i++)
		{
			DELETEARRAY(m_suujiVarData[i]);
		}
		DELETEARRAY(m_suujiVarData);
	}

	if (m_suujiVarNumber)
	{
		for (int i = 0; i < m_suujiNumber; i++)
		{
			DELETEARRAY(m_suujiVarNumber[i]);
		}
		DELETEARRAY(m_suujiVarNumber);
	}


	if (m_textVarData)
	{
		for (int i = 0; i < m_textNumber; i++)
		{
			DELETEARRAY(m_textVarData[i]);
		}
		DELETEARRAY(m_textVarData);
	}

	if (m_textVarNumber)
	{
		for (int i = 0; i < m_textNumber; i++)
		{
			DELETEARRAY(m_textVarNumber[i]);
		}
		DELETEARRAY(m_textVarNumber);
	}


	DELETEARRAY(m_faceVarData);
	DELETEARRAY(m_faceVarNumber);

	DELETEARRAY(m_generalVarData);
	DELETEARRAY(m_generalVarNumber);

	if (m_faceAnimePic)
	{
		for (int i = 0; i < m_charaNumber; i++)
		{
			ENDDELETECLASS(m_faceAnimePic[i]);
		}

		DELETEARRAY(m_faceAnimePic);
	}


	if (m_statusBarParam)
	{
		for (int i = 0; i < m_barNumber; i++)
		{
			ENDDELETECLASS(m_statusBarParam[i].barPic);
			ENDDELETECLASS(m_statusBarParam[i].basePic);
		}
		DELETEARRAY(m_statusBarParam);
	}
	if (m_statusSuujiParam)
	{
		for (int i = 0; i < m_suujiNumber; i++)
		{
			ENDDELETECLASS(m_statusSuujiParam[i].suuji);
		}
		DELETEARRAY(m_statusSuujiParam);
	}

	if (m_statusTextParam)
	{
		for (int i = 0; i < m_textNumber; i++)
		{
			DELETEARRAY(m_statusTextParam[i].message);
		}

		DELETEARRAY(m_statusTextParam);
	}

	DELETEARRAY(m_statusPlateParam);

	ENDDELETECLASS(m_setup);
}



void CPrintPlayerStatus::Init(void)
{

}

void CPrintPlayerStatus::Calcu(int cnt)
{
	if (!CheckPrint())
	{
		return;
	}

	//face anime
	for (int i = 0; i < m_charaNumber; i++)
	{
		if (m_faceAnimePic[i])
		{
			m_faceAnimePic[i]->Calcu(cnt);
		}
	}


}
void CPrintPlayerStatus::Print(int setMax,BOOL placeMustPrint,int* onOffParam,int* onOffSet,POINT* placeList, int* etcOnOff, POINT* etcPlaceList)
{
	if (!CheckPrint())
	{
		return;
	}

	int placeNumber = 0;
	for (int i = 0; i < m_charaNumber; i++)
	{
		if (placeNumber >= setMax)
		{
			//�\���v���[�g�������Ȃ�
			break;
		}


		//�I�t�̕\���G���A�̓X�L�b�v�����
		//�X�L�b�v���Ȃ��d�l�ɕύX
		if (onOffSet[placeNumber] <= 0)
		{
			if (!placeMustPrint)
			{
				placeNumber++;
				continue;
			}
		}

		POINT basePoint = placeList[placeNumber];
		if (m_platePic)
		{
			m_platePic->Put(basePoint.x, basePoint.y, TRUE);
		}


		/*
		while (onOffSet[placeNumber] <= 0)
		{
			if (placeMustPrint)
			{
				POINT basePoint = placeList[placeNumber];

				//plate
				if (m_platePic)
				{
					m_platePic->Put(basePoint.x, basePoint.y, TRUE);
				}
			}

			placeNumber++;
			if (placeNumber >= setMax)
			{
				//�\���v���[�g�������Ȃ�
				break;
			}
		}
		*/



		int charaNumber = m_generalVarData[i + 1];
		if ((charaNumber > 0) && (charaNumber <= m_charaNumber))
		{
			charaNumber -= 1;
			int paramType = 0;

			//			POINT basePoint = GetBasePoint(placeNumber);
			//			POINT basePoint = placeList[placeNumber];


						//plate
			if (m_platePic)
			{
				m_platePic->Put(basePoint.x, basePoint.y, TRUE);
			}


			//face
			POINT faceDelta = GetFacePointDelta();
			int faceType = m_faceVarData[charaNumber];//not use now
			if (m_faceAnimePic[charaNumber])
			{
				if (onOffParam[paramType] || placeMustPrint)
				{
					POINT pt = basePoint;
					pt.x += faceDelta.x;
					pt.y += faceDelta.y;
					m_faceAnimePic[charaNumber]->Print(pt);
				}
			}
			paramType++;

			//text
			for (int k = 0; k < m_textNumber; k++)
			{
				if (onOffParam[paramType] || placeMustPrint)
				{

					int messageType = m_statusTextParam[k].textType;
					LPSTR mes = NULL;
					int m = m_textVarData[k][charaNumber];

					if (messageType == 2)
					{
						mes = CMyMessage::m_okikaeData->GetOkikaeMessage(m);
					}
					else if (messageType == 3)
					{
						mes = CMyMessage::m_okikaeData->GetSystemOkikaeMessage(m);
					}

					if (mes == NULL)
					{
						int messageNumber = m_statusTextParam[k].messageNumber;
						int m = m_textVarData[k][charaNumber];
						if ((m >= 0) && (m <= messageNumber))
						{
							if (m > 0)
							{
								m--;
							}

							mes = m_statusTextParam[k].message[charaNumber * messageNumber + m];
						}
					}



					//				int messageNumber = m_statusTextParam[k].messageNumber;
					//				int m = m_textVarData[k][charaNumber];
					//				if ((m >= 0) && (m <= messageNumber))
					{
						//					if (m > 0)
						//					{
						//						m--;
						//					}

						//					LPSTR mes = m_statusTextParam[k].message[charaNumber * messageNumber + m];
						if (mes != NULL)
						{
							POINT pt = basePoint;
							POINT textDelta = GetTextPointDelta(k);
							pt.x += textDelta.x;
							pt.y += textDelta.y;
							int colorR = m_statusTextParam[k].fontColorR;
							int colorG = m_statusTextParam[k].fontColorG;
							int colorB = m_statusTextParam[k].fontColorB;
							int fontSize = m_statusTextParam[k].fontSize;
							m_message->PrintMessage(pt.x, pt.y, mes, fontSize, colorR, colorG, colorB);
						}
					}
				}

				paramType++;

			}

			//suuji
			for (int k = 0; k < m_suujiNumber; k++)
			{
				CSuuji* suuji = m_statusSuujiParam[k].suuji;
				if (suuji)
				{
					if (onOffParam[paramType] || placeMustPrint)
					{
						POINT suujiDelta = GetSuujiPointDelta(k);
						int data = m_suujiVarData[k][charaNumber];
						POINT pt = basePoint;
						pt.x += suujiDelta.x;
						pt.y += suujiDelta.y;
						suuji->Print(pt.x, pt.y, data);
					}
				}
				paramType++;
			}

			//bar
			for (int k = 0; k < m_barNumber; k++)
			{
				if (onOffParam[paramType] || placeMustPrint)
				{
					CPicture* barBasePic = m_statusBarParam[k].basePic;
					if (barBasePic)
					{
						POINT pt = basePoint;
						POINT baseDelta = GetBarBasePointDelta(k);
						pt.x += baseDelta.x;
						pt.y += baseDelta.y;
						barBasePic->Put(pt.x, pt.y, TRUE);
					}

					CPicture* pic = m_statusBarParam[k].barPic;
					if (pic)
					{
						POINT pt = basePoint;
						POINT baseDelta = GetBarBasePointDelta(k);
						pt.x += baseDelta.x;
						pt.y += baseDelta.y;
						POINT barDelta = GetBarPointDelta(k);
						pt.x += barDelta.x;
						pt.y += barDelta.y;

						int sizeX = m_statusBarParam[k].sizeX;
						int sizeY = m_statusBarParam[k].sizeY;

						int data = m_barVarData[k][charaNumber * 2];
						int dataMax = m_barVarData[k][charaNumber * 2 + 1];
						if (dataMax > 0)
						{
							int putSizeX = (data * sizeX) / dataMax;
							int putSizeY = sizeY;
							int srcX = 0;
							int srcY = 0;
							pic->Blt(pt.x, pt.y, srcX, srcY, putSizeX, putSizeY, TRUE);
						}
					}
				}
				paramType++;
			}
		}

		placeNumber++;
		if (placeNumber >= setMax)
		{
			//�\���v���[�g�������Ȃ�
			break;
		}
		
	}

	for (int i = 0; i < m_etcNumber; i++)
	{
		if (placeMustPrint || etcOnOff[i])
		{
			POINT p = etcPlaceList[i];
			if (m_etcPlatePic[i])
			{
				m_etcPlatePic[i]->Put(p.x, p.y, TRUE);
			}

			p.x += m_etcPointDelta[i].x;
			p.y += m_etcPointDelta[i].y;

			int data = m_etcVarData[i];
			CSuuji* suuji = m_etcSuuji[i];
			if (suuji)
			{
				suuji->Print(p.x, p.y, data);
			}

		}

	}
}


BOOL CPrintPlayerStatus::CheckPrint(void)
{
	if (m_generalVarData[0] != 0)
	{
		return TRUE;
	}
	return FALSE;
}




void CPrintPlayerStatus::StartRequestVarNumberName(void)
{
	m_varType = MYVARTYPE_GENERAL;
	m_varParam1 = 0;
	m_varParam2 = 0;
}

bool CPrintPlayerStatus::RequestVarNumberName(LPSTR* varname)
{
	bool b = true;
	LPSTR returnVarName = NULL;

	char name[256];


	m_varTypeSet = m_varType;
	m_varParam1Set = m_varParam1;
	m_varParam2Set = m_varParam2;

	switch (m_varType)
	{
	case MYVARTYPE_GENERAL:
		if (m_varParam1 == 0)
		{
			sprintf_s(name, 256, "statusPrintVarName");
		}
		else
		{
			sprintf_s(name, 256, "status%dPlayerVarName",m_varParam1);
		}
		GetInitGameString(&returnVarName, name);

		m_varParam1++;
		if (m_varParam1 >= 1 + m_charaNumber)
		{
			m_varType = MYVARTYPE_PLACETYPE;
			m_varParam1 = 0;
			m_varParam2 = 0;
		}
		break;
	case MYVARTYPE_PLACETYPE:

		GetInitGameString(&returnVarName, "placeTypeVarName");

		m_varType = MYVARTYPE_FACE;
		m_varParam1 = 0;
		m_varParam2 = 0;
		break;
	case MYVARTYPE_FACE:

		sprintf_s(name, 256, "chara%dVarName", 1+m_varParam1);
		GetInitGameString(&returnVarName, name);

		m_varParam1++;
		if (m_varParam1 >= m_charaNumber)
		{
			m_varType = MYVARTYPE_TEXT;
			m_varParam1 = 0;
			m_varParam2 = 0;
		}
		break;
	case MYVARTYPE_TEXT:

		sprintf_s(name, 256, "text%d_%dVarName", 1 + m_varParam1,1+m_varParam2);
		GetInitGameString(&returnVarName, name);

		m_varParam2++;
		if (m_varParam2 >= m_charaNumber)
		{
			m_varParam2 = 0;
			m_varParam1++;
			if (m_varParam1 >= m_textNumber)
			{
				m_varType = MYVARTYPE_NUM;
				m_varParam1 = 0;
				m_varParam2 = 0;
			}
		}
		break;
	case MYVARTYPE_NUM:
		sprintf_s(name, 256, "data%d_%dVarName", 1 + m_varParam1, 1 + m_varParam2);
		GetInitGameString(&returnVarName, name);

		m_varParam2++;
		if (m_varParam2 >= m_charaNumber)
		{
			m_varParam2 = 0;
			m_varParam1++;
			if (m_varParam1 >= m_suujiNumber)
			{
				m_varType = MYVARTYPE_BAR;
				m_varParam1 = 0;
				m_varParam2 = 0;
			}
		}
		break;
	case MYVARTYPE_BAR:

		if ((m_varParam2 & 1) == 0)
		{
			sprintf_s(name, 256, "bar%d_%dVarName", 1 + m_varParam1, 1 + m_varParam2 / 2);
		}
		else
		{
			sprintf_s(name, 256, "bar%d_%dMaxVarName", 1 + m_varParam1, 1 + m_varParam2 / 2);
		}
		GetInitGameString(&returnVarName, name);



		m_varParam2++;
		if (m_varParam2 >= m_charaNumber*2)
		{
			m_varParam2 = 0;
			m_varParam1++;
			if (m_varParam1 >= m_barNumber)
			{
				if (m_etcNumber <= 0)
				{
					b = false;
				}
				else
				{
					m_varType = MYVARTYPE_ETCNUM;
					m_varParam1 = 0;
					m_varParam2 = 0;

				}
			}
		}
		break;

	case MYVARTYPE_ETCNUM:
		sprintf_s(name, 256, "etc%dVarName", 1 + m_varParam1);
		GetInitGameString(&returnVarName, name);

		m_varParam1++;
		if (m_varParam1 >= m_etcNumber)
		{
			m_varParam1 = 0;
			b = false;
		}
		break;

	}

	*varname = returnVarName;
	return b;
}


void CPrintPlayerStatus::SetVarNumber(int n, LPSTR varName)
{
	switch (m_varTypeSet)
	{
	case MYVARTYPE_GENERAL:
		m_generalVarNumber[m_varParam1Set] = n;
		break;
	case MYVARTYPE_PLACETYPE:
		m_placeVarNumber = n;
		break;
	case MYVARTYPE_FACE:
		m_faceVarNumber[m_varParam1Set] = n;
		break;
	case MYVARTYPE_TEXT:
		m_textVarNumber[m_varParam1Set][m_varParam2Set] = n;
		break;
	case MYVARTYPE_NUM:
		m_suujiVarNumber[m_varParam1Set][m_varParam2Set] = n;
		break;
	case MYVARTYPE_BAR:
		m_barVarNumber[m_varParam1Set][m_varParam2Set] = n;
		break;
	case MYVARTYPE_ETCNUM:
		m_etcVarNumber[m_varParam1Set] = n;
		break;
	}


}


void CPrintPlayerStatus::StartRequestVarData(void)
{
	m_varType = MYVARTYPE_GENERAL;
	m_varParam1 = 0;
	m_varParam2 = 0;
}

bool CPrintPlayerStatus::RequestVarData(int* varNumber)
{
	bool b = true;
	int returnVarNumber = -1;

	m_varTypeSet = m_varType;
	m_varParam1Set = m_varParam1;
	m_varParam2Set = m_varParam2;

	switch (m_varType)
	{
	case MYVARTYPE_GENERAL:
		returnVarNumber = m_generalVarNumber[m_varParam1];
		m_varParam1++;
		if (m_varParam1 >= 1 + m_charaNumber)
		{
			m_varType = MYVARTYPE_PLACETYPE;
			m_varParam1 = 0;
			m_varParam2 = 0;
		}
		break;
	case MYVARTYPE_PLACETYPE:
		returnVarNumber = m_placeVarNumber;
		m_varType = MYVARTYPE_FACE;
		m_varParam1 = 0;
		m_varParam2 = 0;
		break;
	case MYVARTYPE_FACE:
		returnVarNumber = m_faceVarNumber[m_varParam1];
		m_varParam1++;
		if (m_varParam1 >= m_charaNumber)
		{
			m_varType = MYVARTYPE_TEXT;
			m_varParam1 = 0;
			m_varParam2 = 0;
		}
		break;
	case MYVARTYPE_TEXT:
		returnVarNumber = m_textVarNumber[m_varParam1][m_varParam2];
		m_varParam2++;
		if (m_varParam2 >= m_charaNumber)
		{
			m_varParam2 = 0;
			m_varParam1++;
			if (m_varParam1 >= m_textNumber)
			{
				m_varType = MYVARTYPE_NUM;
				m_varParam1 = 0;
				m_varParam2 = 0;
			}
		}
		break;
	case MYVARTYPE_NUM:
		returnVarNumber = m_suujiVarNumber[m_varParam1][m_varParam2];
		m_varParam2++;
		if (m_varParam2 >= m_charaNumber)
		{
			m_varParam2 = 0;
			m_varParam1++;
			if (m_varParam1 >= m_suujiNumber)
			{
				m_varType = MYVARTYPE_BAR;
				m_varParam1 = 0;
				m_varParam2 = 0;
			}
		}
		break;
	case MYVARTYPE_BAR:
		returnVarNumber = m_barVarNumber[m_varParam1][m_varParam2];
		m_varParam2++;
		if (m_varParam2 >= m_charaNumber*2)
		{
			m_varParam2 = 0;
			m_varParam1++;
			if (m_varParam1 >= m_barNumber)
			{
				if (m_etcNumber <= 0)
				{
					b = false;
				}
				else
				{
					m_varType = MYVARTYPE_ETCNUM;
					m_varParam1 = 0;
					m_varParam2 = 0;
				}
			}
		}
		break;
	case MYVARTYPE_ETCNUM:
		returnVarNumber = m_etcVarNumber[m_varParam1];
		m_varParam1++;
		if (m_varParam1 >= m_etcNumber)
		{
			m_varParam1 = 0;
			b = false;
		}
		break;

	}

	*varNumber = returnVarNumber;
	return b;
}

void CPrintPlayerStatus::SetVarData(int data, int varNumber)
{

	switch (m_varTypeSet)
	{
	case MYVARTYPE_GENERAL:
		m_generalVarData[m_varParam1Set] = data;
		break;
	case MYVARTYPE_PLACETYPE:
		m_placeVarData = data;
		break;
	case MYVARTYPE_FACE:
		m_faceVarData[m_varParam1Set] = data;
		break;
	case MYVARTYPE_TEXT:
		m_textVarData[m_varParam1Set][m_varParam2Set] = data;
		break;
	case MYVARTYPE_NUM:
		m_suujiVarData[m_varParam1Set][m_varParam2Set] = data;
		break;
	case MYVARTYPE_BAR:
		m_barVarData[m_varParam1Set][m_varParam2Set] = data;
		break;
	case MYVARTYPE_ETCNUM:
		m_etcVarData[m_varParam1Set] = data;
		break;
	}
}



int CPrintPlayerStatus::GetPlaceType(void)
{
	int type = m_placeVarData;
	if (type > 0)
	{
		type -= 1;
	}

	if (type >= m_plateTypeNumber)
	{
		type = m_plateTypeNumber - 1;
	}
	if (type < 0)
	{
		type = 0;
	}

	return type;
}

POINT CPrintPlayerStatus::GetBasePoint(int n)
{
	POINT pt;
	int type = GetPlaceType();
	int startX = m_statusPlateParam[type].printX;
	int startY = m_statusPlateParam[type].printY;
	int nextX = m_statusPlateParam[type].nextX;
	int nextY = m_statusPlateParam[type].nextY;
	int picNumX = m_statusPlateParam[type].numX;
	int picNumY = m_statusPlateParam[type].numY;

	if (picNumX < 1)
	{
		picNumX = 1;
	}
	if (picNumY < 1)
	{
		picNumY = 1;
	}

	int nx = 0;
	int ny = 0;


	int yoko = 1;
	if (yoko)
	{
		nx = n % picNumX;
		ny = (n / picNumX) % picNumY;
	}
	else
	{
		ny += n % picNumY;
		nx += (n / picNumY) % picNumX;
	}

	int x = startX + nx * nextX;
	int y = startY + ny * nextY;

	pt.x = x;
	pt.y = y;

	return pt;

}


POINT CPrintPlayerStatus::GetFacePointDelta(void)
{
	POINT pt;
	pt.x = m_facePrintX;
	pt.y = m_facePrintY;
	return pt;
}
POINT CPrintPlayerStatus::GetTextPointDelta(int n)
{
	POINT pt;
	pt.x = m_statusTextParam[n].printX;
	pt.y = m_statusTextParam[n].printY;
	return pt;
}

POINT CPrintPlayerStatus::GetSuujiPointDelta(int n)
{
	POINT pt;
	pt.x = m_statusSuujiParam[n].printX;
	pt.y = m_statusSuujiParam[n].printY;
	return pt;

}
POINT CPrintPlayerStatus::GetBarBasePointDelta(int n)
{
	POINT pt;
	pt.x = m_statusBarParam[n].basePrintX;
	pt.y = m_statusBarParam[n].basePrintY;

	return pt;
}
POINT CPrintPlayerStatus::GetBarPointDelta(int n)
{
	POINT pt;
	pt.x = m_statusBarParam[n].printX;
	pt.y = m_statusBarParam[n].printY;
	return pt;

}


void CPrintPlayerStatus::CheckUseMode(int mode, LPSTR modeName)
{
	if ((mode >= 0) && (mode <= 255))
	{
		char name[256];
		sprintf_s(name, 256, "Use%s", modeName);
		int flag = 0;
		GetInitGameParam(&flag, name);
		if (flag)
		{
			m_useMode[mode] = 1;
		}
	}
}

BOOL CPrintPlayerStatus::IsEnable(int mode)
{
	if ((mode < 0) || (mode > 255))
	{
		return FALSE;
	}

	return m_useMode[mode] != 0;
}


BOOL CPrintPlayerStatus::GetInitGameParam(int* lpVar, LPSTR name, int initData)
{
	*lpVar = initData;
	return GetInitGameParam(lpVar, name);
}

BOOL CPrintPlayerStatus::GetInitGameParam(int* lpVar, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpVar = atoi(m_setup->GetName(rNum + 1));

	return TRUE;
}

BOOL CPrintPlayerStatus::GetInitGameString(LPSTR* lpStr, LPSTR name, LPSTR initString)
{
	*lpStr = initString;
	return GetInitGameString(lpStr, name);
}

BOOL CPrintPlayerStatus::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_setup->GetName(rNum + 1);

	return TRUE;
}



int CPrintPlayerStatus::GetSetNumber(void)
{
	return m_charaNumber;
}
int CPrintPlayerStatus::GetStatusTypeNumber(void)
{
	return m_textNumber + m_suujiNumber + m_barNumber + 1;
}

int CPrintPlayerStatus::GetEtcNumber(void)
{
	return m_etcNumber;
}

/*_*/
