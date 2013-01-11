//
// dataFileSetup
//

#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"

#include "suuji.h"
#include "nameList.h"
#include "setupList.h"

#include "printGameDate.h"
#include "commonAnimeParts.h"

#include "dataFileSetup.h"

#include "..\nyanLib\INCLUDE\allGeo.h"

char CDataFileSetup::m_defaultFontFileName[] = "ta_sl_font";


CDataFileSetup::CDataFileSetup()
{

//MessageBox(NULL,"datafilesetup:const-0","game",MB_OK);
//CAllGeo::BoxFill(10,10,300,300,55,66,77);




	m_setup = new CSetupList();
	m_setup->LoadSetupFile("dataFile");

	//mini cg

	if (1)
	{
		int sizeX = 132;
		int sizeY = 100;
		m_setup->GetInitGameParam(&sizeX,"areaSizeX");
		m_setup->GetInitGameParam(&sizeY,"areaSizeY");
		m_saveAreaSize.cx = sizeX;
		m_saveAreaSize.cy = sizeY;

//		sizeX = m_miniCGSizeX;
//		sizeY = m_miniCGSizeY;
		m_setup->GetInitGameParam(&sizeX,"picSizeX");
		m_setup->GetInitGameParam(&sizeY,"picSizeY");
		m_savePicSize.cx = sizeX;
		m_savePicSize.cy = sizeY;

		int px = 0;
		int py = 0;
		m_setup->GetInitGameParam(&px,"picPrintX");
		m_setup->GetInitGameParam(&py,"picPrintY");
		m_savePicZahyo.x = px;
		m_savePicZahyo.y = py;
	}




	//real time

	m_saveTimePrintFlag = 1;
	m_setup->GetInitGameParam(&m_saveTimePrintFlag,"saveTimePrintFlag");

	m_saveTimePic = NULL;
	m_saveTimeSuuji2 = NULL;
	m_saveTimeSuuji4 = NULL;

	if (m_saveTimePrintFlag)
	{
		int x = 0;
		int y = 0;
		m_setup->GetInitGameParam(&x,"saveTimePrintX");
		m_setup->GetInitGameParam(&y,"saveTimePrintY");
		m_saveTimeZahyo.x = x;
		m_saveTimeZahyo.y = y;

		int sizeX = 10;
		int sizeY = 10;	//dummy
		m_setup->GetInitGameParam(&sizeX,"saveTimeFontSizeX");
		m_setup->GetInitGameParam(&sizeY,"saveTimeFontSizeY");
		m_saveTimeSize.cx = sizeX;
		m_saveTimeSize.cy = sizeY;

		m_saveTimeNextX = sizeX;
		m_setup->GetInitGameParam(&m_saveTimeNextX,"saveTimeFontNextX");

		LPSTR saveTimeFileName = m_defaultFontFileName;
		m_setup->GetInitGameString(&saveTimeFileName,"fileNameSaveTimeFont");

		m_saveTimePic = new CPicture();
		char filename[256];
		wsprintf(filename,"sys\\%s",saveTimeFileName);
		m_saveTimePic->LoadDWQ(filename);

		m_saveTimeSuuji4 = new CSuuji(m_saveTimePic,m_saveTimeSize.cx,m_saveTimeSize.cy,4,m_saveTimeNextX,TRUE);
		m_saveTimeSuuji2 = new CSuuji(m_saveTimePic,m_saveTimeSize.cx,m_saveTimeSize.cy,2,m_saveTimeNextX,TRUE);
	}


	//gameyear
	m_gameYearPrintFlag = 0;
	m_setup->GetInitGameParam(&m_gameYearPrintFlag,"gameYearPrintFlag");

	m_gameDatePrintFlag = 0;
	m_setup->GetInitGameParam(&m_gameDatePrintFlag,"gameDatePrintFlag");

	m_gameWeekPrintFlag = 0;
	m_setup->GetInitGameParam(&m_gameWeekPrintFlag,"gameWeekPrintFlag");

	m_gameWeekYouPrintFlag = 1;
	m_setup->GetInitGameParam(&m_gameWeekYouPrintFlag,"gameWeekYouPrintFlag");
	m_gameWeekBiPrintFlag = 1;
	m_setup->GetInitGameParam(&m_gameWeekBiPrintFlag,"gameWeekBiPrintFlag");


	m_gameYearDatePic = NULL;
	m_gameWeekPic = NULL;
	m_gameYearSuuji = NULL;
	m_gameMonthSuuji = NULL;
	m_gameDaySuuji = NULL;
	m_gameWeekSuuji = NULL;

	//m_gameDateSuuji = NULL;

	int weekPrintX = 0;
	int weekPrintY = 0;

	m_gameWeekSize.cx = 16;
	m_gameWeekSize.cy = 16;

	if (m_gameYearPrintFlag || m_gameDatePrintFlag)
	{
		LPSTR gameYearDataFileName = m_defaultFontFileName;
		m_setup->GetInitGameString(&gameYearDataFileName,"fileNameGameTimeFont");


		m_gameYearDatePic = new CPicture();
		char filename[256];
		wsprintf(filename,"sys\\%s",gameYearDataFileName);
		m_gameYearDatePic->LoadDWQ(filename);

		int x = 0;
		int y = 0;

		m_setup->GetInitGameParam(&x,"gameTimePrintX");
		m_setup->GetInitGameParam(&y,"gameTimePrintY");
		m_gameTimeZahyo.x = x;
		m_gameTimeZahyo.y = y;


		int sizeX = 10;
		int sizeY = 10;
		m_setup->GetInitGameParam(&sizeX,"gameTimeFontSizeX");
		m_setup->GetInitGameParam(&sizeY,"gameTimeFontSizeY");
		m_gameTimeSize.cx = sizeX;
		m_gameTimeSize.cy = sizeY;

		m_gameTimeNextX = sizeX;
		m_setup->GetInitGameParam(&m_gameTimeNextX,"gameTimeFontNextX");


		if (m_gameYearPrintFlag)
		{
			m_gameYearSuuji = new CSuuji(m_gameYearDatePic,m_gameTimeSize.cx,m_gameTimeSize.cy,4,m_gameTimeNextX,TRUE);
			weekPrintX = x + sizeX * 5;
			weekPrintX = y;
		}

		if (m_gameDatePrintFlag)
		{
			m_gameMonthUpzeroPrintFlag = 1;
			m_gameDayUpzeroPrintFlag = 1;
			GetInitGameParam(&m_gameDateSlashPrintFlag,"gameDateSlashPrintFlag");
			GetInitGameParam(&m_gameMonthUpzeroPrintFlag,"gameMonthUpZeroPrintFlag");
			GetInitGameParam(&m_gameMonthUpzeroPrintFlag,"gameDayUpZeroPrintFlag");
			m_gameMonthSuuji = new CSuuji(m_gameYearDatePic,m_gameTimeSize.cx,m_gameTimeSize.cy,2,m_gameTimeNextX,m_gameMonthUpzeroPrintFlag);
			m_gameDaySuuji = new CSuuji(m_gameYearDatePic,m_gameTimeSize.cx,m_gameTimeSize.cy,2,m_gameTimeNextX,m_gameDayUpzeroPrintFlag);

			x = m_gameTimeZahyo.x + sizeX * 5;
			y = m_gameTimeZahyo.y;

			GetInitGameParam(&x,"gameMonthPrintX");
			GetInitGameParam(&y,"gameMonthPrintY");
			m_gameMonthZahyo.x = x;
			m_gameMonthZahyo.y = y;

			x += sizeX * 3;
			GetInitGameParam(&x,"gameDayPrintX");
			GetInitGameParam(&y,"gameDayPrintY");
			m_gameDayZahyo.x = x;
			m_gameDayZahyo.y = y;

			weekPrintX = x + sizeX*3;
			weekPrintY = y;
		}
	}


	if (m_gameWeekPrintFlag)
	{
		LPSTR gameWeekFileName = m_defaultFontFileName;
		m_setup->GetInitGameString(&gameWeekFileName,"fileNameGameWeekFont");


		m_gameWeekPic = new CPicture();
		char filename[256];
		wsprintf(filename,"sys\\%s",gameWeekFileName);
		m_gameWeekPic->LoadDWQ(filename);

		int x = weekPrintX;
		int y = weekPrintY;

		m_setup->GetInitGameParam(&x,"gameWeekPrintX");
		m_setup->GetInitGameParam(&y,"gameWeekPrintY");
		m_gameWeekZahyo.x = x;
		m_gameWeekZahyo.y = y;


		int sizeX = 10;
		int sizeY = 10;
		m_setup->GetInitGameParam(&sizeX,"gameWeekFontSizeX");
		m_setup->GetInitGameParam(&sizeY,"gameWeekFontSizeY");
		m_gameWeekSize.cx = sizeX;
		m_gameWeekSize.cy = sizeY;


		m_gameWeekSuuji = new CSuuji(m_gameWeekPic,m_gameWeekSize.cx,m_gameWeekSize.cy,1,sizeX,FALSE);
	}

	//kazari
	m_kazariPrintFlag = 0;
	m_kazariPic = NULL;
	m_setup->GetInitGameParam(&m_kazariPrintFlag,"kazariPrintFlag");
	if (m_kazariPrintFlag)
	{
		int x = 0;
		int y = 0;
		m_setup->GetInitGameParam(&x,"kazariPrintX");
		m_setup->GetInitGameParam(&y,"kazariPrinty");
		m_kazariZahyo.x = x;
		m_kazariZahyo.y = y;

		LPSTR filename = m_defaultFontFileName;
		m_setup->GetInitGameString(&filename,"filenameKazari");

		char picName[256];
		wsprintf(picName,"sys\\%s",filename);

		m_kazariPic = new CPicture(picName);
		SIZE sz = m_kazariPic->GetPicSize();

		int sizeX = sz.cx;
		int sizeY = sz.cy;
		m_setup->GetInitGameParam(&sizeX,"kazariSizeX");
		m_setup->GetInitGameParam(&sizeY,"kazariSizeY");
		m_kazariSize.cx = sizeX;
		m_kazariSize.cy = sizeY;
	
	}

	//addpic
	m_addPicFlag = 0;
	m_addPicZahyo.x = 0;
	m_addPicZahyo.y = 0;
	m_addPicSize.cx = 16;
	m_addPicSize.cy = 16;
	m_setup->GetInitGameParam(&m_addPicFlag,"addPicPrintFlag");
	m_addPic = NULL;
	m_addPicWithSpecialFlag = 0;
	if (m_addPicFlag)
	{
		int x = 0;
		int y = 0;
		m_setup->GetInitGameParam(&x,"addPicPrintX");
		m_setup->GetInitGameParam(&y,"addPicPrintY");
		m_addPicZahyo.x = x;
		m_addPicZahyo.y = y;
		int sizeX = 16;
		int sizeY = 16;
		m_setup->GetInitGameParam(&sizeX,"addPicSizeX");
		m_setup->GetInitGameParam(&sizeY,"addPicSizeY");
		m_addPicSize.cx = sizeX;
		m_addPicSize.cy = sizeY;

		LPSTR filename = m_defaultFontFileName;
		m_setup->GetInitGameString(&filename,"fileNameAddPic");

		char addPicName[256];
		wsprintf(addPicName,"sys\\%s",filename);

		m_addPic = new CPicture(addPicName);

		m_setup->GetInitGameParam(&m_addPicWithSpecialFlag,"addPicWithSpecialFlag");

		m_addPicMultiFlag = 0;
		m_addPicMultiKosuuX = 1;

		m_setup->GetInitGameParam(&m_addPicMultiFlag,"addPicMultiFlag");
		m_setup->GetInitGameParam(&m_addPicMultiKosuuX,"addPicMultiNumberX");
	}


	//special number
	m_specialNumberPrintFlag = 0;
	m_specialNumberPrintLimit = -1;
	m_specialNumberZahyo.x = 0;
	m_specialNumberZahyo.y = 0;
	m_specialNumberSize.cx = 16;
	m_specialNumberSize.cy = 16;
	m_specialNumberNextX = 16;

	m_setup->GetInitGameParam(&m_specialNumberPrintFlag,"specialNumberPrintFlag");
	m_specialNumberPic = NULL;
	m_specialNumberSuuji = NULL;

	if (m_specialNumberPrintFlag)
	{
		m_setup->GetInitGameParam(&m_specialNumberPrintLimit,"specialNumberPrintLimit");

		int x = 0;
		int y = 0;
		m_setup->GetInitGameParam(&x,"specialNumberPrintX");
		m_setup->GetInitGameParam(&y,"specialNumberPrintY");
		int sizeX = 16;
		int sizeY = 16;
		m_setup->GetInitGameParam(&sizeX,"specialNumberFontSizeX");
		m_setup->GetInitGameParam(&sizeY,"specialNumberFontSizeY");

		m_specialNumberNextX = sizeX;
		m_setup->GetInitGameParam(&m_specialNumberNextX,"specialNumberFontNextX");

		int keta = 2;
		m_setup->GetInitGameParam(&keta,"specialNumberKeta");


		LPSTR filename = m_defaultFontFileName;
		m_setup->GetInitGameString(&filename,"fileNameSpecialNumberFont");

		m_specialNumberZahyo.x = x;
		m_specialNumberZahyo.y = y;
		m_specialNumberSize.cx = sizeX;
		m_specialNumberSize.cy = sizeY;
		m_specialNumberNextX = m_specialNumberNextX;

		char fontName[256];
		wsprintf(fontName,"sys\\%s",filename);

		m_specialNumberPic = new CPicture(fontName);
		m_specialNumberSuuji = new CSuuji(m_specialNumberPic,sizeX,sizeY,keta,m_specialNumberNextX);
	}

	m_serialNumberPrintFlag = 0;
	m_serialNumberSuuji = NULL;
	m_serialNumberPic = NULL;

	m_setup->GetInitGameParam(&m_serialNumberPrintFlag,"serialPrintFlag");
	if (m_serialNumberPrintFlag)
	{
		int x = 0;
		int y = 0;
		m_setup->GetInitGameParam(&x,"serialPrintX");
		m_setup->GetInitGameParam(&y,"serialPrintY");
		m_serialZahyo.x = x;
		m_serialZahyo.y = y;
		int sizeX = 12;
		int sizeY = 12;
		m_setup->GetInitGameParam(&sizeX,"serialFontSizeX");
		m_setup->GetInitGameParam(&sizeY,"serialFontSizeY");
		m_serialFontSize.cx = sizeX;
		m_serialFontSize.cy = sizeY;
		int nextX = sizeX;
		m_setup->GetInitGameParam(&nextX,"serialFontNextX");
		m_serialNextX = nextX;

		LPSTR filename = m_defaultFontFileName;
		m_setup->GetInitGameString(&filename,"fileNameSerialNumberFont");

		char fontName[256];
		wsprintf(fontName,"sys\\%s",filename);

		int keta = 2;
		m_setup->GetInitGameParam(&keta,"serialNumberKeta");


		m_serialNumberPic = new CPicture(fontName);
		m_serialNumberSuuji = new CSuuji(m_serialNumberPic,sizeX,sizeY,keta,m_serialNextX);

	}

//MessageBox(NULL,"datafilesetup:const-3","game",MB_OK);
//CAllGeo::BoxFill(10,10,300,300,55,66,77);

	m_commentPrintFlag = 0;
	m_setup->GetInitGameParam(&m_commentPrintFlag,"commentPrintFlag");
	m_commentZahyo.x = 0;
	m_commentZahyo.y = 0;
	m_commentFontSize = 12;
	m_commentSukima = 1;
	m_commentColor[0] = 255;
	m_commentColor[1] = 255;
	m_commentColor[2] = 255;
	m_commentColor[3] = 0;

	if (m_commentPrintFlag)
	{
		int x,y;
		x = 0;
		y = 0;
		m_setup->GetInitGameParam(&x,"commentPrintX");
		m_setup->GetInitGameParam(&y,"commentPrintY");
		m_commentZahyo.x = x;
		m_commentZahyo.y = y;
		m_setup->GetInitGameParam(&m_commentFontSize,"commentFontSize");
		m_setup->GetInitGameParam(&m_commentSukima,"commentSpaceX");
		
		m_setup->GetInitGameParam(&m_commentColor[0],"commentColorR");
		m_setup->GetInitGameParam(&m_commentColor[1],"commentColorG");
		m_setup->GetInitGameParam(&m_commentColor[2],"commentColorB");
		m_setup->GetInitGameParam(&m_commentColor[3],"commentColorShade");
	}


	m_textPrintFlag = 0;
	m_setup->GetInitGameParam(&m_textPrintFlag,"textPrintFlag");
	m_textZahyo.x = 0;
	m_textZahyo.y = 0;
	m_textFontSize = 12;
	m_textSukima = 1;
	m_textColor[0] = 255;
	m_textColor[1] = 255;
	m_textColor[2] = 255;
	m_textColor[3] = 0;
	m_textNextY = 30;
	m_textPrintGyo = 1;

	if (m_textPrintFlag)
	{
		int x,y;
		x = 0;
		y = 0;
		m_setup->GetInitGameParam(&x,"textPrintX");
		m_setup->GetInitGameParam(&y,"textPrintY");
		m_textZahyo.x = x;
		m_textZahyo.y = y;
		m_setup->GetInitGameParam(&m_textFontSize,"textFontSize");
		m_setup->GetInitGameParam(&m_textSukima,"textSpaceX");
		
		m_setup->GetInitGameParam(&m_textColor[0],"textColorR");
		m_setup->GetInitGameParam(&m_textColor[1],"textColorG");
		m_setup->GetInitGameParam(&m_textColor[2],"textColorB");
		m_setup->GetInitGameParam(&m_textColor[3],"textColorShade");

		m_setup->GetInitGameParam(&m_textNextY,"textNextY");
		m_setup->GetInitGameParam(&m_textPrintGyo,"textPrintNumber");
	}



//error
	
	m_errorVersionPic = NULL;
	m_oldVersionPic = NULL;
	m_badVersionPic = NULL;

	if (1)
	{
		int px = 0;
		int py = 0;
		m_setup->GetInitGameParam(&px,"errorPrintX");
		m_setup->GetInitGameParam(&py,"errorPrintY");
		m_saveErrorZahyo.x = px;
		m_saveErrorZahyo.y = py;

		m_setup->GetInitGameParam(&px,"oldPrintX");
		m_setup->GetInitGameParam(&py,"oldPrintY");
		m_saveOldZahyo.x = px;
		m_saveOldZahyo.y = py;

		m_setup->GetInitGameParam(&px,"badPrintX");
		m_setup->GetInitGameParam(&py,"badPrintY");
		m_saveBadZahyo.x = px;
		m_saveBadZahyo.y = py;



		LPSTR errorName = NULL;
		LPSTR badName = NULL;
		LPSTR oldName = NULL;

		m_setup->GetInitGameString(&errorName,"fileNameError");
		m_setup->GetInitGameString(&badName,"fileNameBad");
		m_setup->GetInitGameString(&oldName,"fileNameOld");


		if (errorName != NULL)
		{
			m_errorVersionPic = new CPicture();
			char filename[256];

			wsprintf(filename,"sys\\%s",errorName);

//MessageBox(NULL,"datafilesetup:const-3-3-1-b","game",MB_OK);
//CAllGeo::BoxFill(10,10,300,300,55,66,77);

			m_errorVersionPic->LoadDWQ(filename);

//MessageBox(NULL,"datafilesetup:const-3-3-1-c","game",MB_OK);
//CAllGeo::BoxFill(10,10,300,300,55,66,77);

		}

//MessageBox(NULL,"datafilesetup:const-3-3-2","game",MB_OK);
//CAllGeo::BoxFill(10,10,300,300,55,66,77);

		if (oldName != NULL)
		{
			m_oldVersionPic = new CPicture();
			char filename[256];
			wsprintf(filename,"sys\\%s",oldName);
			m_oldVersionPic->LoadDWQ(filename);
		}
//MessageBox(NULL,"datafilesetup:const-3-3-3","game",MB_OK);
//CAllGeo::BoxFill(10,10,300,300,55,66,77);

		if (badName != NULL)
		{
			m_badVersionPic = new CPicture();
			char filename[256];
			wsprintf(filename,"sys\\%s",badName);
			m_badVersionPic->LoadDWQ(filename);
		}
	}

//MessageBox(NULL,"datafilesetup:const-4","game",MB_OK);
//CAllGeo::BoxFill(10,10,300,300,55,66,77);

	m_savePic = NULL;
	m_loadPic = NULL;
	m_overwritePic = NULL;

	m_saveAnimePattern[0] = 0;
	m_loadAnimePattern[0] = 0;
	m_overwriteAnimePattern[0] = 0;
	m_saveAnimePattern[1] = 0;
	m_loadAnimePattern[1] = 0;
	m_overwriteAnimePattern[1] = 0;

	m_saveAnimeType[0] = 1;
	m_loadAnimeType[0] = 1;
	m_overwriteAnimeType[0] = 1;
	m_saveAnimeType[1] = 1;
	m_loadAnimeType[1] = 1;
	m_overwriteAnimeType[1] = 1;

	m_saveAnimeSpeed[0] = 1;
	m_loadAnimeSpeed[0] = 1;
	m_overwriteAnimeSpeed[0] = 1;
	m_saveAnimeSpeed[1] = 1;
	m_loadAnimeSpeed[1] = 1;
	m_overwriteAnimeSpeed[1] = 1;

	if (1)
	{
		m_saveSelectPic = NULL;

		m_saveSelectColor[0] = 230;
		m_saveSelectColor[1] = 0;
		m_saveSelectColor[2] = 255;
		m_saveSelectColor[3] = 50;
		
		m_setup->GetInitGameParam(&m_saveSelectColor[0],"selectColorR");
		m_setup->GetInitGameParam(&m_saveSelectColor[1],"selectColorG");
		m_setup->GetInitGameParam(&m_saveSelectColor[2],"selectColorB");
		m_setup->GetInitGameParam(&m_saveSelectColor[3],"selectPercent");

		m_saveSelectPrintMode = 0;
		m_setup->GetInitGameParam(&m_saveSelectPrintMode,"selectPrintMode");

//		m_saveSelectFileName = NULL;
		if (m_saveSelectPrintMode >= 1)
		{
			LPSTR selectName = m_defaultFontFileName;
			m_setup->GetInitGameString(&selectName,"fileNameSelectPic");
			char filename[256];

			if (m_saveSelectPrintMode == 1)
			{
				m_saveSelectPic = new CPicture();
				wsprintf(filename,"sys\\%s",selectName);
				m_saveSelectPic->LoadDWQ(filename);
			}

			if (m_saveSelectPrintMode == 2)
			{
				m_setup->GetInitGameParam(&m_saveAnimePattern[0],"saveAnimePattern");
				m_setup->GetInitGameParam(&m_saveAnimeType[0],"saveAnimeType");
				m_setup->GetInitGameParam(&m_saveAnimeSpeed[0],"saveAnimeSpeed");

				m_saveAnimePattern[1] = m_saveAnimePattern[0];
				m_saveAnimeType[1] = m_saveAnimeType[0];
				m_saveAnimeSpeed[1] = m_saveAnimeSpeed[0];

				m_setup->GetInitGameParam(&m_saveAnimePattern[1],"saveAnimePattern2");
				m_setup->GetInitGameParam(&m_saveAnimeType[1],"saveAnimeType2");
				m_setup->GetInitGameParam(&m_saveAnimeSpeed[1],"saveAnimeSpeed2");

				m_savePic = new CPicture();
				m_setup->GetInitGameString(&selectName,"fileNameSaveCursor");
				wsprintf(filename,"sys\\%s",selectName);
				m_savePic->LoadDWQ(filename);


				m_setup->GetInitGameParam(&m_loadAnimePattern[0],"loadAnimePattern");
				m_setup->GetInitGameParam(&m_loadAnimeType[0],"loadAnimeType");
				m_setup->GetInitGameParam(&m_loadAnimeSpeed[0],"loadAnimeSpeed");

				m_loadAnimePattern[1] = m_loadAnimePattern[0];
				m_loadAnimeType[1] = m_loadAnimeType[0];
				m_loadAnimeSpeed[1] = m_loadAnimeSpeed[0];

				m_setup->GetInitGameParam(&m_loadAnimePattern[1],"loadAnimePattern2");
				m_setup->GetInitGameParam(&m_loadAnimeType[1],"loadAnimeType2");
				m_setup->GetInitGameParam(&m_loadAnimeSpeed[1],"loadAnimeSpeed2");

				m_loadPic = new CPicture();
				m_setup->GetInitGameString(&selectName,"fileNameLoadCursor");
				wsprintf(filename,"sys\\%s",selectName);
				m_loadPic->LoadDWQ(filename);


				m_setup->GetInitGameParam(&m_overwriteAnimePattern[0],"overwriteAnimePattern");
				m_setup->GetInitGameParam(&m_overwriteAnimeType[0],"overwriteAnimeType");
				m_setup->GetInitGameParam(&m_overwriteAnimeSpeed[0],"overwriteAnimeSpeed");

				m_overwriteAnimePattern[1] = m_overwriteAnimePattern[0];
				m_overwriteAnimeType[1] = m_overwriteAnimeType[0];
				m_overwriteAnimeSpeed[1] = m_overwriteAnimeSpeed[0];

				m_setup->GetInitGameParam(&m_overwriteAnimePattern[1],"overwriteAnimePattern2");
				m_setup->GetInitGameParam(&m_overwriteAnimeType[1],"overwriteAnimeType2");
				m_setup->GetInitGameParam(&m_overwriteAnimeSpeed[1],"overwriteAnimeSpeed2");

				m_overwritePic = new CPicture();
				m_setup->GetInitGameString(&selectName,"fileNameOverwriteCursor");
				wsprintf(filename,"sys\\%s",selectName);
				m_overwritePic->LoadDWQ(filename);
			}
			
		}
	}


	m_numPrintFlag = 0;
	m_setup->GetInitGameParam(&m_numPrintFlag,"numberPrintFlag");
	m_numSuuji = NULL;
	m_numPic = NULL;

	if (m_numPrintFlag)
	{
		char filename[1024];
		LPSTR numName = NULL;
		m_setup->GetInitGameString(&numName,"numberFileName");
		m_numPic = new CPicture();
		wsprintf(filename,"sys\\%s",numName);
		m_numPic->LoadDWQ(filename);


		int sizeX = 16;
		int sizeY = 16;
		m_setup->GetInitGameParam(&sizeX,"numberSizeX");
		m_setup->GetInitGameParam(&sizeY,"numberSizeY");
		int keta = 2;
		m_setup->GetInitGameParam(&keta,"numberKeta");
		int nextX = sizeX;
		m_setup->GetInitGameParam(&nextX,"numberNextX");
		int upZeroFlag = 0;
		m_setup->GetInitGameParam(&upZeroFlag,"numberUpZaro");
		int leftFlag = 0;
		m_setup->GetInitGameParam(&leftFlag,"numberLeft");
		m_numSuuji = new CSuuji(m_numPic,sizeX,sizeY,keta,nextX,upZeroFlag,TRUE,leftFlag);

		int x = 0;
		int y = 0;
		m_setup->GetInitGameParam(&x,"numberPrintX");
		m_setup->GetInitGameParam(&y,"numberPrintY");
		m_numZahyo.x = x;
		m_numZahyo.y = y;
	}


	//quick select
//	m_quickLoadSelectOk = 0;
//	m_quickSaveSelectOk = 0;
//	m_setup->GetInitGameParam(&m_quickLoadSelectOk,"quickLoadSelectOk");
//	m_setup->GetInitGameParam(&m_quickSaveSelectOk,"quickSaveSelectOk");

	//base
	m_basePrintFlag = 0;
	m_setup->GetInitGameParam(&m_basePrintFlag,"basePrintFlag");
	m_loadBasePic = NULL;
	m_saveBasePic = NULL;
	m_quickLoadBasePic = NULL;
	m_quickSaveBasePic = NULL;

	m_quickLoadPicMake = FALSE;
	m_quickSavePicMake = FALSE;

	m_baseChangeLoadSave = 1;
	if (m_basePrintFlag)
	{
		m_setup->GetInitGameParam(&m_baseChangeLoadSave,"baseChangeLoadSave");
		if (m_baseChangeLoadSave == 0)
		{
			LPSTR name = NULL;
			if (m_setup->GetInitGameString(&name,"filenameLoadBase"))
			{
				m_loadBasePic = new CPicture();
				char filename[256];
				wsprintf(filename,"sys\\%s",name);
				m_loadBasePic->LoadDWQ(filename);
				m_saveBasePic = m_loadBasePic;
			}

			if (m_setup->GetInitGameString(&name,"filenameQuickLoadBase"))
			{
				m_quickLoadPicMake = TRUE;
				m_quickLoadBasePic = new CPicture();
				char filename[256];
				wsprintf(filename,"sys\\%s",name);
				m_quickLoadBasePic->LoadDWQ(filename);
				m_quickSaveBasePic = m_quickLoadBasePic;
			}
			else
			{
				m_quickLoadBasePic = m_loadBasePic;
				m_quickSaveBasePic = m_saveBasePic;
			}
		}
		else
		{
			LPSTR name = NULL;
			if (m_setup->GetInitGameString(&name,"filenameLoadBase"))
			{
				m_loadBasePic = new CPicture();
				char filename[256];
				wsprintf(filename,"sys\\%s",name);
				m_loadBasePic->LoadDWQ(filename);
			}

			name = NULL;
			if (m_setup->GetInitGameString(&name,"filenameSaveBase"))
			{
				m_saveBasePic = new CPicture();
				char filename[256];
				wsprintf(filename,"sys\\%s",name);
				m_saveBasePic->LoadDWQ(filename);
			}


			name = NULL;
			if (m_setup->GetInitGameString(&name,"filenameQuickLoadBase"))
			{
				m_quickLoadPicMake = TRUE;
				m_quickLoadBasePic = new CPicture();
				char filename[256];
				wsprintf(filename,"sys\\%s",name);
				m_quickLoadBasePic->LoadDWQ(filename);
			}
			else
			{
				m_quickLoadBasePic = m_loadBasePic;
			}

			name = NULL;
			if (m_setup->GetInitGameString(&name,"filenameQuickSaveBase"))
			{
				m_quickSavePicMake = TRUE;
				m_quickSaveBasePic = new CPicture();
				char filename[256];
				wsprintf(filename,"sys\\%s",name);
				m_quickSaveBasePic->LoadDWQ(filename);
			}
			else
			{
				m_quickSaveBasePic = m_saveBasePic;
			}
		}
	}

	m_quickSlotNumber = 1;
	GetInitGameParam(&m_quickSlotNumber,"quickSlotNumber");
	m_quickSlotNumber -= 1;


	//select
	if (1)
	{
		int printX = m_savePicZahyo.x;
		int printY = m_savePicZahyo.y;
		m_setup->GetInitGameParam(&printX,"selectPrintX");
		m_setup->GetInitGameParam(&printY,"selectPrintY");
		m_selectZahyo.x = printX;
		m_selectZahyo.y = printY;

		int sizeX = m_savePicSize.cx;
		int sizeY = m_savePicSize.cy;
		m_setup->GetInitGameParam(&sizeX,"selectSizeX");
		m_setup->GetInitGameParam(&sizeY,"selectSizeY");
		m_selectSize.cx = sizeX;
		m_selectSize.cy = sizeY;
	}

	m_printGameDate = NULL;
	if (m_gameYearPrintFlag || m_gameDatePrintFlag)
	{
		m_printGameDate = new CPrintGameDate(m_setup->GetNameList(),"game");
	}

	m_printLastSelect = NULL;

	if (1)
	{
		LPSTR lastSelectAnimeName = NULL;
		if (m_setup->GetInitGameString(&lastSelectAnimeName,"filenameLastSave"))
		{
			if (lastSelectAnimeName != NULL)
			{
				if ((*lastSelectAnimeName) != 0)
				{
					m_printLastSelect = new CCommonAnimeParts("lastSave",m_setup->GetNameList(),TRUE);
				}
			}
		}
	}
}



CDataFileSetup::~CDataFileSetup()
{
	End();
}


void CDataFileSetup::End(void)
{
	ENDDELETECLASS(m_printLastSelect);
	
	ENDDELETECLASS(m_printGameDate);

	ENDDELETECLASS(m_numPic);
	ENDDELETECLASS(m_numSuuji);

	if (m_quickSavePicMake)
	{
		m_quickSavePicMake = FALSE;
		ENDDELETECLASS(m_quickSaveBasePic);
	}
	if (m_quickLoadPicMake)
	{
		m_quickLoadPicMake = FALSE;
		ENDDELETECLASS(m_quickLoadBasePic);
	}

	if (m_basePrintFlag)
	{
		if (m_baseChangeLoadSave == 0)
		{
			ENDDELETECLASS(m_loadBasePic);
			m_saveBasePic = NULL;
		}
		else
		{
			ENDDELETECLASS(m_loadBasePic);
			ENDDELETECLASS(m_saveBasePic);
		}
	}

	ENDDELETECLASS(m_serialNumberPic);
	ENDDELETECLASS(m_serialNumberSuuji);

	ENDDELETECLASS(m_specialNumberPic);
	ENDDELETECLASS(m_specialNumberSuuji);

	ENDDELETECLASS(m_addPic);
	ENDDELETECLASS(m_kazariPic);

	ENDDELETECLASS(m_savePic);
	ENDDELETECLASS(m_loadPic);
	ENDDELETECLASS(m_overwritePic);


	ENDDELETECLASS(m_saveSelectPic);

	ENDDELETECLASS(m_badVersionPic);
	ENDDELETECLASS(m_oldVersionPic);
	ENDDELETECLASS(m_errorVersionPic);

	ENDDELETECLASS(m_gameWeekSuuji);
	ENDDELETECLASS(m_gameWeekPic);
	ENDDELETECLASS(m_gameDaySuuji);
	ENDDELETECLASS(m_gameMonthSuuji);
	ENDDELETECLASS(m_gameYearSuuji);
	ENDDELETECLASS(m_gameYearDatePic);

	ENDDELETECLASS(m_saveTimeSuuji2);
	ENDDELETECLASS(m_saveTimeSuuji4);
	ENDDELETECLASS(m_saveTimePic);

	ENDDELETECLASS(m_setup);
}



BOOL CDataFileSetup::GetInitGameParam(int* lpVar, LPSTR name)
{
	return m_setup->GetInitGameParam(lpVar,name);
}


BOOL CDataFileSetup::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	return m_setup->GetInitGameString(lpStr,name);
}


CPicture* CDataFileSetup::GetSaveCursorPic(void)
{
	if (m_savePic == NULL)
	{
		return m_saveSelectPic;
	}

	return m_savePic;
}


CPicture* CDataFileSetup::GetLoadCursorPic(void)
{
	if (m_loadPic == NULL) return GetSaveCursorPic();
	return m_loadPic;
}

CPicture* CDataFileSetup::GetOverwriteCursorPic(void)
{
	if (m_overwritePic == NULL) return GetSaveCursorPic();
	return m_overwritePic;
}





/*_*/


