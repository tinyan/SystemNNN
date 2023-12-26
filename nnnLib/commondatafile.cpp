//
// CommonDataFile.cpp
//

#include <windows.h>
#include <stdio.h>



#include <ddraw.h>
//#include <d3dx9.h>

#if defined _TINYAN3DLIB_
#include "..\..\systemNNN3D\nyanDirectX3DLib\myTexture.h"
#else
#endif


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGeo.h"
#include "..\nyanLib\include\myFile.h"
#include "..\nnnUtilLib\suuji.h"
#include "..\nnnUtilLib\myfont.h"

#include "..\nnnUtilLib\calcuWeek.h"

#include "..\nnnUtilLib\mySaveFolder.h"

#include "..\nyanEffectLib\effectstruct.h"

#include "..\nnnUtilLib\commonGameVersion.h"

#include "commonMode.h"

#include "commonGeneral.h"
//#include "gamedatepic.h"
#include "CommonDataFile.h"
#include "..\nnnUtilLib\myMessage.h"
//#include "mode.h"

#include "..\nnnUtilLib\inputStatus.h"
#include "..\nnnUtilLib\nameList.h"
#include "..\nnnUtilLib\commonAnimeParts.h"

#include "..\nnnUtilLib\printGameDate.h"

#include "..\nnnLib\gameCallBack.h"


#include "..\nnnUtilLib\dataFileSetup.h"

//CPicture* CCommonDataFile::m_dayPic = NULL;
//CPicture* CCommonDataFile::m_dayFontPic = NULL;
//CPicture* CCommonDataFile::m_fontPic = NULL;



CCommonDataFile::CCommonDataFile(CGameCallBack* lpGame, int printX, int printY,CPicture* lpBG)
{
	m_game = lpGame;

	m_loadSave = FALSE;//not use?

	int codeByte = CMyFont::m_codeByte;



	m_dataFileSetup = m_game->GetDataFileSetup();
	m_bg = lpBG;
	m_printGameDate = m_dataFileSetup->GetPrintGameDate();

	m_quickLoadEnable = m_game->GetQuickLoadEnable();
	m_quickSaveEnable = m_game->GetQuickSaveEnable();

	m_quickSlotNumber = m_dataFileSetup->GetQuickSlotNumber();

	//m_quickLoadSelectOk = m_dataFileSetup->GetQuickLoadSelectOk();
	//m_quickSaveSelectOk = m_dataFileSetup->GetQuickSaveSelectOk();


	m_commonBuffer2 = m_game->GetCommonBuffer();
	m_systemGameVersion = m_game->GetGameVersion();

	m_extDataBlockKosuu = m_game->GetExtDataBlockKosuu();

	m_pExtBlockSize = NULL;
//	m_ppExtBlockData = NULL;
	if (m_extDataBlockKosuu > 0)
	{
		m_pExtBlockSize = new int[m_extDataBlockKosuu];
//		m_ppExtBlockData = new char* [m_extDataBlockKosuu + sizeof(GAMEGENERALDATA)];
		for (int i=0;i<m_extDataBlockKosuu;i++)
		{
			m_pExtBlockSize[i] = m_game->GetExtDataBlockSize(i);
//			m_ppExtBlockData[i] = new char[ m_pExtBlockSize[i] + sizeof(GAMEGENERALDATA)];
		}
	}

	m_omakeClassExistFlag = m_game->GetOmakeClassExistFlag();
	m_cutinUseFlag = m_game->GetUseCutin();
	m_logFlag = m_game->GetSaveLog();


	m_printX = printX;
	m_printY = printY;

//	SIZE sz = m_game->GetSaveAreaSize();
	SIZE sz = m_dataFileSetup->GetSaveAreaSize();
	m_sizeX = sz.cx;
	m_sizeY = sz.cy;

//	sz = m_game->GetSavePicSize();
	sz = m_dataFileSetup->GetSavePicSize();
	m_picSizeX = sz.cx;
	m_picSizeY = sz.cy;

	m_picPrintType = 0;
	m_dataFileSetup->GetInitGameParam(&m_picPrintType,"picPrintType");

	m_basePrintFlag = m_dataFileSetup->GetBasePrintFlag();
	if (m_basePrintFlag)
	{
		m_loadBasePic = m_dataFileSetup->GetLoadBase();
		m_saveBasePic = m_dataFileSetup->GetSaveBase();
		if (m_quickLoadEnable)
		{
			m_quickLoadBasePic = m_dataFileSetup->GetQuickLoadBase();
		}
		if (m_quickSaveEnable)
		{
			m_quickSaveBasePic = m_dataFileSetup->GetQuickSaveBase();
		}
	}


//	POINT pt = m_game->GetSavePicZahyo();
	POINT pt = m_dataFileSetup->GetSavePicZahyo();


	m_picPrintX = pt.x;
	m_picPrintY = pt.y;

	pt = m_dataFileSetup->GetSelectZahyo();
	m_selectPrintX = pt.x;
	m_selectPrintY = pt.y;

	sz = m_dataFileSetup->GetSelectSize();
	m_selectSizeX = sz.cx;
	m_selectSizeY = sz.cy;



//	pt = m_game->GetSaveTimeZahyo();
	pt = m_dataFileSetup->GetSaveTimeZahyo();
	m_saveTimePrintX = pt.x;
	m_saveTimePrintY = pt.y;

//	sz = m_game->GetSaveTimeFontSize();
	sz = m_dataFileSetup->GetSaveTimeSize();
	m_saveTimeSizeX = sz.cx;
	m_saveTimeSizeY = sz.cy;

//	m_saveTimeFontNextX = m_game->GetSaveTimeFontNextX();
	m_saveTimeNextX = m_dataFileSetup->GetSaveTimeNextX();

//	m_saveTimePrintFlag = m_game->GetSaveTimePrintFlag();
	m_saveTimePrintFlag = m_dataFileSetup->GetSaveTimePrintFlag();

	m_saveTimeSuuji4 = NULL;
	m_saveTimeSuuji2 = NULL;

	if (m_saveTimePrintFlag)
	{
		m_saveDatePic = m_dataFileSetup->GetSaveTimePic();
		m_saveTimeSuuji4 = m_dataFileSetup->GetSaveTimeSuuji4();
		m_saveTimeSuuji2 = m_dataFileSetup->GetSaveTimeSuuji2();
	}


//	pt = m_game->GetSaveGameTimeZahyo();
	pt = m_dataFileSetup->GetGameTimeZahyo();
	m_gameTimePrintX = pt.x;
	m_gameTimePrintY = pt.y;

	pt = m_dataFileSetup->GetGameDayZahyo();
	m_gameDayPrintX = pt.x;
	m_gameDayPrintY = pt.y;

	pt = m_dataFileSetup->GetGameWeekZahyo();
	m_gameWeekPrintX = pt.x;
	m_gameWeekPrintY = pt.y;

//	sz = m_game->GetSaveGameTimeFontSize();
	sz = m_dataFileSetup->GetGameTimeSize();
	m_gameTimeSizeX = sz.cx;
	m_gameTimeSizeY = sz.cy;

	sz = m_dataFileSetup->GetGameWeekSize();
	m_gameWeekSizeX = sz.cx;
	m_gameWeekSizeY = sz.cy;

//	m_gameTimeFontNextX = m_game->GetSaveGameTimeFontNextX();
	m_gameTimeNextX = m_dataFileSetup->GetGameTimeNextX();

	m_gameYearPrintFlag = m_dataFileSetup->GetGameYearPrintFlag();
	m_gameDatePrintFlag = m_dataFileSetup->GetGameDatePrintFlag();
	m_gameWeekPrintFlag = m_dataFileSetup->GetGameWeekPrintFlag();
	m_gameWeekYouPrintFlag = m_dataFileSetup->GetGameWeekYouPrintFlag();
	m_gameWeekBiPrintFlag = m_dataFileSetup->GetGameWeekBiPrintFlag();

	m_gameTimePrintFlag = m_gameYearPrintFlag | m_gameDatePrintFlag;

	m_gameTimeSuuji4 = NULL;
	m_gameTimeSuuji2 = NULL;
	m_gameTimeSuuji3 = NULL;
	m_gameWeekSuuji = NULL;

	m_lpGameVar = NULL;

	m_gameYearVarNumber = m_game->GetVarNumber("year");
	m_gameDateVarNumber = m_game->GetVarNumber("date");

	if (m_gameTimePrintFlag)
	{

		m_lpGameVar = new GAMEVAR;

		
//		LPSTR name = m_game->GetSaveGameTimeFileName();
//		m_gameDatePic = m_game->GetSystemPicture(name);

		m_gameDatePic = m_dataFileSetup->GetGameYearDatePic();

		if (m_gameYearPrintFlag)
		{
			m_gameTimeSuuji4 = m_dataFileSetup->GetGameYearSuuji();
//			m_gameTimeSuuji4 = new CSuuji(m_gameDatePic,m_gameTimeFontSizeX,m_gameTimeFontSizeY,4,m_gameTimeFontNextX,TRUE);
		}

		if (m_gameDatePrintFlag)
		{
			m_gameTimeSuuji2 = m_dataFileSetup->GetGameMonthSuuji();
			m_gameTimeSuuji3 = m_dataFileSetup->GetGameDaySuuji();
			m_gameDateSlashPrintFlag = m_dataFileSetup->GetGameDateSlashPrintFlag();
//			m_gameTimeSuuji2 = new CSuuji(m_gameDatePic,m_gameTimeFontSizeX,m_gameTimeFontSizeY,2,m_gameTimeFontNextX,TRUE);
		}

		if (m_gameWeekPrintFlag)
		{
			m_gameWeekSuuji = m_dataFileSetup->GetGameWeekSuuji();
		}
	}


	m_numPrintFlag = m_dataFileSetup->GetNumPrintFlag();
	if (m_numPrintFlag)
	{
		POINT pn = m_dataFileSetup->GetNumZahyo();

		m_numPrintX = pn.x;
		m_numPrintY = pn.y;
		m_numSuuji = m_dataFileSetup->GetNumSuuji();
	}

	m_specialNumberSuuji = NULL;


//	m_specialNumberPrintFlag = m_game->GetSpecialNumberPrintFlag();
	m_specialNumberPrintFlag = m_dataFileSetup->GetSpecialNumberPrintFlag();
	if (m_specialNumberPrintFlag)
	{
		m_specialNumberPrintZahyo = m_dataFileSetup->GetSpecialNumberZahyo();
		m_specialNumberSuuji = m_dataFileSetup->GetSpecialNumberSuuji();
	}
	m_specialNumberPrintLimit = m_dataFileSetup->GetSpecialNumberPrintLimit();


	m_kazariPrintFlag = m_dataFileSetup->GetKazariPrintFlag();
	if (m_kazariPrintFlag)
	{
		m_kazariZahyo = m_dataFileSetup->GetKazariZahyo();
		m_kazariSize = m_dataFileSetup->GetKazariSize();
		m_kazariPic = m_dataFileSetup->GetKazariPic();
	}

	m_addPicPrintFlag = m_dataFileSetup->GetAddPicFlag();
	m_addPicWithSpecialFlag = 0;
	if (m_addPicPrintFlag)
	{
		m_addPic = m_dataFileSetup->GetAddPic();
		m_addPicWithSpecialFlag = m_dataFileSetup->GetAddPicWithSpecialFlag();
		m_addPicPrintZahyo = m_dataFileSetup->GetAddPicZahyo();
		m_addPicSize = m_dataFileSetup->GetAddPicSize();

		m_addPicMultiFlag = m_dataFileSetup->GetAddPicMultiFlag();
		m_addPicMultiKosuuX = m_dataFileSetup->GetAddPicMultiKosuuX();
	}


	m_serialNumberPrintFlag = m_dataFileSetup->GetSerialNumberPrintFlag();
	if (m_serialNumberPrintFlag)
	{
		m_serialSuuji = m_dataFileSetup->GetSerialNumberSuuji();
		m_serialNumberPrintZahyo = m_dataFileSetup->GetSerialNumberZahyo();
	}


	m_commentPrintFlag = m_dataFileSetup->GetCommentPrintFlag();
	if (m_commentPrintFlag)
	{
		m_commentPrintZahyo = m_dataFileSetup->GetCommentZahyo();
		m_commentFontSize = m_dataFileSetup->GetCommentFontSize();
		m_commentSukima = m_dataFileSetup->GetCommentSukima();
		m_commentColorR = m_dataFileSetup->GetCommentColor(0);
		m_commentColorG = m_dataFileSetup->GetCommentColor(1);
		m_commentColorB = m_dataFileSetup->GetCommentColor(2);
		m_commentColorShade = m_dataFileSetup->GetCommentColor(3);
	}

	m_textPrintFlag = m_dataFileSetup->GetTextPrintFlag();
	if (m_textPrintFlag)
	{
		m_textPrintZahyo = m_dataFileSetup->GetTextZahyo();
		m_textFontSize = m_dataFileSetup->GetTextFontSize();
		m_textSukima = m_dataFileSetup->GetTextSukima();
		m_textColorR = m_dataFileSetup->GetTextColor(0);
		m_textColorG = m_dataFileSetup->GetTextColor(1);
		m_textColorB = m_dataFileSetup->GetTextColor(2);
		m_textColorShade = m_dataFileSetup->GetTextColor(3);
		m_textNextY = m_dataFileSetup->GetTextNextY();
		m_textPrintGyo = m_dataFileSetup->GetTextPrintGyo();
	}


	m_cursorPic[0] = NULL;
	m_cursorPic[1] = NULL;
	m_cursorPic[2] = NULL;

	m_selectPrintMode = m_dataFileSetup->GetSaveSelectPrintMode();
	if (m_selectPrintMode == 0)
	{
		m_selectColorR = m_dataFileSetup->GetSelectColorParam(0);
		m_selectColorG = m_dataFileSetup->GetSelectColorParam(1);
		m_selectColorB = m_dataFileSetup->GetSelectColorParam(2);
		m_selectColorPercent = m_dataFileSetup->GetSelectColorParam(3);
	}
	else if (m_selectPrintMode >= 1)
	{
//		LPSTR name = m_game->GetSaveSelectFileName();
//		m_selectPic = m_game->GetSystemPicture(name);
		m_selectPic = m_dataFileSetup->GetSaveSelectPic();

		m_animePattern[0] = m_dataFileSetup->GetSaveAnimePattern();
		m_animePattern[1] = m_dataFileSetup->GetLoadAnimePattern();
		m_animePattern[2] = m_dataFileSetup->GetOverwriteAnimePattern();
		m_animePattern[3] = m_dataFileSetup->GetSaveAnimePattern(1);
		m_animePattern[4] = m_dataFileSetup->GetLoadAnimePattern(1);
		m_animePattern[5] = m_dataFileSetup->GetOverwriteAnimePattern(1);

		m_animeType[0] = m_dataFileSetup->GetSaveAnimeType();
		m_animeType[1] = m_dataFileSetup->GetLoadAnimeType();
		m_animeType[2] = m_dataFileSetup->GetOverwriteAnimeType();
		m_animeType[3] = m_dataFileSetup->GetSaveAnimeType(1);
		m_animeType[4] = m_dataFileSetup->GetLoadAnimeType(1);
		m_animeType[5] = m_dataFileSetup->GetOverwriteAnimeType(1);

		m_animeSpeed[0] = m_dataFileSetup->GetSaveAnimeSpeed();
		m_animeSpeed[1] = m_dataFileSetup->GetLoadAnimeSpeed();
		m_animeSpeed[2] = m_dataFileSetup->GetOverwriteAnimeSpeed();
		m_animeSpeed[3] = m_dataFileSetup->GetSaveAnimeSpeed(1);
		m_animeSpeed[4] = m_dataFileSetup->GetLoadAnimeSpeed(1);
		m_animeSpeed[5] = m_dataFileSetup->GetOverwriteAnimeSpeed(1);

		m_animeCount[0] = 0;
		m_animeCount[1] = 0;
		m_animeCount[2] = 0;
		m_animeCount[3] = 0;
		m_animeCount[4] = 0;
		m_animeCount[5] = 0;

		m_cursorPic[0] = m_dataFileSetup->GetSaveCursorPic();
		m_cursorPic[1] = m_dataFileSetup->GetLoadCursorPic();
		m_cursorPic[2] = m_dataFileSetup->GetOverwriteCursorPic();
	}

	m_commonBG = m_game->GetCommonBG();
	m_font = m_game->GetMyFont();
	m_message = m_game->GetMyMessage();

	m_dataExistFlag = FALSE;

	m_pic = new CPicture(m_picSizeX,m_picSizeY);

	pt = m_dataFileSetup->GetSaveErrorZahyo();
	m_errorPrintX = pt.x;
	m_errorPrintY = pt.y;

	pt = m_dataFileSetup->GetSaveOldZahyo();
	m_oldPrintX = pt.x;
	m_oldPrintY = pt.y;

	pt = m_dataFileSetup->GetSaveBadZahyo();
	m_badPrintX = pt.x;
	m_badPrintY = pt.y;

	m_errorVersionPic = m_dataFileSetup->GetSaveErrorPic();
	m_oldVersionPic = m_dataFileSetup->GetSaveOldPic();
	m_badVersionPic = m_dataFileSetup->GetSaveBadPic();

	m_printLastSelect = m_dataFileSetup->GetPrintLastSelect();

//	m_largeCommentFlag = 0;
//	m_lergeComment1[0] = 0;
//	m_lergeComment2[0] = 0;
//	m_lergeComment3[0] = 0;
//	m_lergeComment4[0] = 0;

	if (codeByte == 2)
	{
		memcpy(m_sei,"ê©Ç≈Å[ÇΩ",strlen("ê©Ç≈Å[ÇΩ")+1);
		memcpy(m_mei,"ñºÇ≈Å[ÇΩ",strlen("ñºÇ≈Å[ÇΩ")+1);
	}
	else
	{
		memcpy(m_sei,"LastName",strlen("LastName")+1);
		memcpy(m_mei,"FirstName",strlen("FirstName")+1);
	}
}



CCommonDataFile::~CCommonDataFile()
{
	End();
}

void CCommonDataFile::End(void)
{
	if (m_lpGameVar != NULL)
	{
		delete m_lpGameVar;
		m_lpGameVar = NULL;
	}

//	ENDDELETECLASS(m_specialNumberSuuji);
//	ENDDELETECLASS(m_saveTimeSuuji4);
//	ENDDELETECLASS(m_saveTimeSuuji2);
//	ENDDELETECLASS(m_gameTimeSuuji4);
//	ENDDELETECLASS(m_gameTimeSuuji2);


	ENDDELETECLASS(m_pic);

	DELETEARRAY(m_pExtBlockSize);
//	if (m_ppExtBlockData != NULL)
//	{
//		for (int i=0;i<m_extDataBlockKosuu;i++)
//		{
//			DELETEARRAY(m_ppExtBlockData[i]);
//		}
//		DELETEARRAY(m_ppExtBlockData);
//	}
}


BOOL CCommonDataFile::LoadHeaderAndPic(int n)
{
	m_number = n;

	LPSTR saveFolder = CMySaveFolder::GetFullFolder();

	char filename[1024];
//	if (m_game->CheckTaikenVersion() == FALSE)
	if (CCommonGameVersion::CheckTaikenVersion() == FALSE)
	{
		wsprintf(filename,"%s\\data%d.sav",saveFolder,n);
	}
	else
	{
		wsprintf(filename,"%s\\tdata%d.sav",saveFolder,n);
	}

//	sprintf(filename,"sav\\data%d.sav",n);

	m_file = CMyFile::OpenFullPath(filename,"rb");
	if (m_file == NULL)
	{
		m_dataExistFlag = FALSE;
		return FALSE;
	}

	Load1Block();	//header

//	Load1Block();	//info
	fread(&m_gameInfo,sizeof(GAMEINFO),1,m_file);

	fread(&m_gameStatus,sizeof(GAMESTATUS),1,m_file);

	Load1Block();	//

	int* ptr = (int*)(m_pic->GetBuffer());
	int* src = ((GAMEMINICG*)m_commonBuffer2)->cg;






	int sz = m_picSizeX * m_picSizeY;

	int* ptr2 = ptr;
#if defined _TINYAN3DLIB_
	ptr2 += 128/sizeof(int);
#endif
	for (int i=0;i<sz;i++)
	{
		*ptr2 = *src;
		src++;
		ptr2++;
	}

#if defined _TINYAN3DLIB_

	//make header


	//mask DDS HEADER
	char* ptr0 = (char*)ptr;
	*ptr0 = 'D';
	ptr0++;
	*ptr0 = 'D';
	ptr0++;
	*ptr0 = 'S';
	ptr0++;
	*ptr0 = ' ';
	ptr0++;

	DDSURFACEDESC2* lpDDS = (DDSURFACEDESC2*)ptr0;
	ZeroMemory(lpDDS,124);
	lpDDS->dwSize = 124;
	lpDDS->dwFlags = DDSD_CAPS |  DDSD_PIXELFORMAT | DDSD_WIDTH | DDSD_HEIGHT;
	lpDDS->dwWidth = m_picSizeX;
	lpDDS->dwHeight = m_picSizeY;	
	lpDDS->ddpfPixelFormat.dwSize = 32;
	lpDDS->ddpfPixelFormat.dwFlags = DDPF_RGB | DDPF_ALPHAPIXELS;
	lpDDS->ddpfPixelFormat.dwRGBBitCount = 32;
//		lpDDS->dwLinearSize = m_pictureSizeX * 4;

	lpDDS->ddpfPixelFormat.dwRGBAlphaBitMask = 0xff000000;
	lpDDS->ddpfPixelFormat.dwRBitMask = 0x00ff0000;
	lpDDS->ddpfPixelFormat.dwGBitMask = 0x0000ff00;
	lpDDS->ddpfPixelFormat.dwBBitMask = 0x000000ff;

	lpDDS->ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_ALPHA;



	CMyTexture* lpTexture = (CMyTexture*)(m_pic->GetTexture());
	lpTexture->CreateTexture(ptr);

#endif




	//var
	if (m_gameTimePrintFlag)
	{
		int varType = m_game->GetVarType();
		if (varType == 0)
		{
			fread(m_lpGameVar, sizeof(GAMEVAR1), 1, m_file);
		}
		else
		{
			fread(m_lpGameVar, sizeof(GAMEVAR), 1, m_file);
		}
	}



	fclose(m_file);

	m_dataExistFlag = TRUE;

	return m_dataExistFlag;
}


BOOL CCommonDataFile::CheckDataExist(void)
{
	return m_dataExistFlag;
}



//0:normal 1-(on) 1:save 2:load 3:overwrite
void CCommonDataFile::Print(int md,int clicking,int nm,int loadSave,int lastCount)
{
	//erase
	if (m_bg != NULL)
	{
		m_bg->Blt(m_printX,m_printY,m_printX,m_printY,m_sizeX,m_sizeY,FALSE);
	}

	//base
	if (m_basePrintFlag)
	{
		if (loadSave == 0)
		{
			if (m_quickLoadEnable && (m_number == m_quickSlotNumber))
			{
				if (m_quickLoadBasePic != NULL)
				{
					m_quickLoadBasePic->Put(m_printX,m_printY,TRUE);
				}
			}
			else
			{
				if (m_loadBasePic != NULL)
				{
					m_loadBasePic->Put(m_printX,m_printY,TRUE);
				}
			}
		}
		else
		{
			if (m_quickSaveEnable && (m_number == m_quickSlotNumber))
			{
				if (m_quickSaveBasePic != NULL)
				{
					m_quickSaveBasePic->Put(m_printX,m_printY,TRUE);
				}
			}
			else
			{
				if (m_saveBasePic != NULL)
				{
					m_saveBasePic->Put(m_printX,m_printY,TRUE);
				}
			}
		}
	}

	//pic
	if (m_dataExistFlag)
	{
//		if (m_pic != NULL) m_pic->Blt(m_printX + m_picPrintX,m_printY + m_picPrintY,0,0,m_picSizeX,m_picSizeY,FALSE);

#if defined _TINYAN3DLIB_NOTUSED
		CAllGeo::BoxFill(m_printX + m_picPrintX,m_printY + m_picPrintY,m_picSizeX,m_picSizeY,14,78,93);
		m_message->PrintMessage(m_printX + m_picPrintX,m_printY + m_picPrintY,"ÇmÇnÇv",10);
		m_message->PrintMessage(m_printX + m_picPrintX,m_printY + m_picPrintY + 12,"ÇoÇqÇhÇmÇsÇhÇmÇf",10);
#else
		if (m_pic != NULL)
		{
			if (m_picPrintType == 0)	//normal
			{
				m_pic->Blt(m_printX + m_picPrintX,m_printY + m_picPrintY,0,0,m_picSizeX,m_picSizeY,FALSE);
			}
			else if (m_picPrintType == 1)	//color
			{
				m_pic->YUVChangeBlt(m_printX + m_picPrintX,m_printY + m_picPrintY,0,0,m_picSizeX,m_picSizeY,FALSE,255);
			}
			else if (m_picPrintType == 2)	//multi
			{
//				m_pic->BltMulti(m_printX + m_picPrintX,m_printY + m_picPrintY,0,0,m_picSizeX,m_picSizeY,FALSE,255);
			}
			else if (m_picPrintType == 3)	//add
			{
//				m_pic->YUVChangeBlt(m_printX + m_picPrintX,m_printY + m_picPrintY,0,0,m_picSizeX,m_picSizeY,FALSE,255);
			}
		}
#endif

		//
		if (m_numPrintFlag)
		{
			if (nm >= 0)
			{
				m_numSuuji->Print(m_printX+m_numPrintX,m_printY+m_numPrintY,nm);
			}
		}


		if (m_serialNumberPrintFlag)
		{
			m_serialSuuji->Print(m_printX+m_serialNumberPrintZahyo.x,m_printY+m_serialNumberPrintZahyo.y,m_number+1);
		}

		if (m_kazariPrintFlag)
		{
			int putX = m_printX + m_kazariZahyo.x;
			int putY = m_printY + m_kazariZahyo.y;
			int sizeX = m_kazariSize.cx;
			int sizeY = m_kazariSize.cy;

			int srcX = 0;
			int srcY = 0;

			m_kazariPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
		}


		//Ç®Ç‹ÇØ
		if (m_addPicPrintFlag)
		{
			if (m_addPic != NULL)
			{
				int putX = m_printX + m_addPicPrintZahyo.x;
				int putY = m_printY + m_addPicPrintZahyo.y;
				int sizeX = m_addPicSize.cx;
				int sizeY = m_addPicSize.cy;

				int srcX = 0;
				int srcY = 0;


				int dat = m_gameStatus.nokori;

				if (m_addPicMultiFlag)
				{
					int dv = m_addPicMultiKosuuX;
					if (dv<1) dv = 1;
					srcX = dat % dv;
					srcY = dat / dv;
					srcX *= sizeX;
					srcY *= sizeY;
				}

				BOOL okflg = TRUE;
				if (m_addPicWithSpecialFlag)
				{
					if (dat < m_specialNumberPrintLimit)
					{
						okflg = FALSE;
					}
				}

				if (okflg)
				{
					m_addPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
				}
			}
		}

		//special
		if (m_specialNumberPrintFlag)
		{
			int putX = m_printX + m_specialNumberPrintZahyo.x;
			int putY = m_printY + m_specialNumberPrintZahyo.y;

			int dat = m_gameStatus.nokori;
			if (dat >= m_specialNumberPrintLimit)
			{
				m_specialNumberSuuji->Print(putX,putY,dat);
			}
		}

		//save date
		if (m_saveTimePrintFlag)
		{
			int year = m_gameStatus.year;
			int month = m_gameStatus.month;
			int day = m_gameStatus.day;
			int hour = m_gameStatus.hour;
			int minute = m_gameStatus.minute;

			int putX = m_printX + m_saveTimePrintX;
			int putY = m_printY + m_saveTimePrintY;
			int sizeX = m_saveTimeSizeX;
			int sizeY = m_saveTimeSizeY;
			int nextX = m_saveTimeNextX;

			//year
			m_saveTimeSuuji4->Print(putX,putY,year);
			putX += nextX * 4;
			// /
			m_saveDatePic->Blt(putX,putY,sizeX*11,0,sizeX,sizeY,TRUE);
			putX += nextX;
			//month
			m_saveTimeSuuji2->Print(putX,putY,month);
			putX += nextX * 2;
			// /
			m_saveDatePic->Blt(putX,putY,sizeX*11,0,sizeX,sizeY,TRUE);
			putX += nextX;
			//day
			m_saveTimeSuuji2->Print(putX,putY,day);
			putX += nextX * 2;
			// space
			putX += nextX;
			//hour
			m_saveTimeSuuji2->Print(putX,putY,hour);
			putX += nextX * 2;
			//:
			m_saveDatePic->Blt(putX,putY,sizeX*10,0,sizeX,sizeY,TRUE);
			putX += nextX;
			//minute
			m_saveTimeSuuji2->Print(putX,putY,minute);
		}

		if (m_gameTimePrintFlag)
		{
			POINT pt;
			pt.x = m_printX;
			pt.y = m_printY;
			int year = m_lpGameVar->var[m_gameYearVarNumber];
			int date = m_lpGameVar->var[m_gameDateVarNumber];
			int month = date /100;
			int day = date % 100;

			m_printGameDate->Print(pt,year,month,day);
		}

/*
		if (m_gameTimePrintFlag)
		{
			int putX = m_printX + m_gameTimePrintX;
			int putY = m_printY + m_gameTimePrintY;
			int sizeX = m_gameTimeSizeX;
			int sizeY = m_gameTimeSizeY;
			int nextX = m_gameTimeNextX;

			if (m_gameYearPrintFlag)
			{
				int year = m_lpGameVar->var[m_gameYearVarNumber];
				m_gameTimeSuuji4->Print(putX,putY,year);
				putX += sizeX * 4;

				if (m_gameDatePrintFlag)
				{
					// /
					if (m_gameDateSlashPrintFlag)
					{
						m_gameDatePic->Blt(putX,putY,sizeX*11,0,sizeX,sizeY,TRUE);
					}
					putX += sizeX;
				}
			}

			if (m_gameDatePrintFlag)
			{
				putX = m_printX + m_gameMonthPrintX;
				putY = m_printY + m_gameMonthPrintY;

				int date = m_lpGameVar->var[m_gameDateVarNumber];
				int month = date /100;
				int day = date % 100;

				//month
				m_gameTimeSuuji2->Print(putX,putY,month);
				putX += nextX * 2;
				// /
				if (m_gameDateSlashPrintFlag)
				{
					m_gameDatePic->Blt(putX,putY,sizeX*11,0,sizeX,sizeY,TRUE);
				}
				putX = m_printX + m_gameDayPrintX;
				putY = m_printY + m_gameDayPrintY;
//				putX += nextX;
				//day
				m_gameTimeSuuji3->Print(putX,putY,day);
				putX += nextX * 2;
			}

			if (m_gameWeekPrintFlag)
			{
				putX = m_printX + m_gameWeekPrintX;
				putY = m_printY + m_gameWeekPrintY;
				int year = m_lpGameVar->var[m_gameYearVarNumber];
				int date = m_lpGameVar->var[m_gameDateVarNumber];
				int month = date /100;
				int day = date % 100;

				int week = CCalcuWeek::CalcuWeek(year,month,day);
				m_gameWeekSuuji->Print(putX,putY,week);

				if (m_gameWeekYouPrintFlag)
				{
					m_gameWeekSuuji->Put(putX+m_gameWeekSizeX,putY,10);
				}

				if (m_gameWeekBiPrintFlag)
				{
					m_gameWeekSuuji->Put(putX+m_gameWeekSizeX*2,putY,11);
				}
			}

		}
*/

		//comment
		if (m_commentPrintFlag)
		{
			int putX = m_printX + m_commentPrintZahyo.x;
			int putY = m_printY + m_commentPrintZahyo.y;
			LPSTR message = m_gameStatus.minicomment;
			if (m_message != NULL)
			{
				m_message->PrintMessage(putX,putY,message,m_commentFontSize,m_commentColorR,m_commentColorR,m_commentColorR,m_commentSukima,-1,m_commentColorShade);
			}
		}

		//text
		if (m_textPrintFlag)
		{
			for (int i=0;i<m_textPrintGyo;i++)
			{
				int putX = m_printX + m_textPrintZahyo.x;
				int putY = m_printY + m_textPrintZahyo.y + i * m_textNextY;
				
				LPSTR mes = m_gameStatus.largeComment1;
				if (i == 1) mes = m_gameStatus.largeComment2;
				if (i == 2) mes = m_gameStatus.largeComment3;
				if (i == 3) mes = m_gameStatus.largeComment4;

				if ((*mes) != 0)
				{
					m_message->PrintMessage(putX,putY,mes,m_textFontSize,m_textColorR,m_textColorR,m_textColorR,m_textSukima,-1,m_textColorShade);
				}
			}
		}

		if (lastCount > 0)
		{
			if (m_printLastSelect != NULL)
			{
				POINT lastPoint;
				lastPoint.x = m_printX;
				lastPoint.y = m_printY;

				m_printLastSelect->DeltaPrint(lastPoint);
			}
		}

		//bad message
		int deltaVersion = GetVersionDeltaMode();

		if (deltaVersion < 0)
		{
			if (m_errorVersionPic != NULL)
			{
				m_errorVersionPic->Put(m_printX+m_errorPrintX,m_printY+m_errorPrintY,TRUE);
			}
			else
			{
				if (m_badVersionPic != NULL) m_badVersionPic->Put(m_printX + m_badPrintX,m_printY+m_badPrintY,TRUE);
			}
		}
		else if (deltaVersion >= 2)
		{
			//version 1.0 BAD
			if (m_badVersionPic != NULL) m_badVersionPic->Put(m_printX+m_badPrintX,m_printY+m_badPrintY,TRUE);
		}
		else if (deltaVersion == 1)
		{
			//version 1.0 OK
			if (m_oldVersionPic != NULL) m_oldVersionPic->Put(m_printX+m_oldPrintX,m_printY+m_oldPrintY,TRUE);
		}
		else
		{
			//ok
		}
	}




	if (md >= 1)
	{
		//ëIëï\é¶ÇÇ¬ÇØÇÈÇ…Ç·
		if (m_selectPrintMode == 0)
		{
			if ((clicking & 1) == 0)
			{
				CAllGeo::TransBoxFill(m_printX+m_selectPrintX,m_printY+m_selectPrintY,m_selectSizeX,m_selectSizeY,m_selectColorR,m_selectColorG,m_selectColorB,m_selectColorPercent);
			}
		}
		else if (m_selectPrintMode == 1)
		{
			if ((clicking & 1) == 0)
			{
				m_selectPic->Put(m_printX+m_selectPrintX,m_printY+m_selectPrintY,TRUE);
			}
		}
		else if (m_selectPrintMode == 2)
		{
			int md2 = md-1;
			if (clicking >= 1) md2 += 3;

			GetNowCursorPic(md2);

			int sizeX = m_selectSizeX;
			int sizeY = m_selectSizeY;
			CPicture* lpPic = m_cursorPic[md-1];

			int srcX = 0;
			if (clicking >= 1) srcX = sizeX;

			int srcY1 = sizeY * m_cursor1;
			int srcY2 = sizeY * m_cursor2;

			int putX = m_printX + m_selectPrintX;
			int putY = m_printY + m_selectPrintY;


			if (m_cursorPercent == 100)
			{
				lpPic->Blt(putX,putY,srcX,srcY1,sizeX,sizeY,TRUE);
			}
			else if (m_cursorPercent == 0)
			{
				lpPic->Blt(putX,putY,srcX,srcY2,sizeX,sizeY,TRUE);
			}
			else
			{

				int ps2 = 100 - m_cursorPercent;
				int* lpBuffer2 = (int*)(lpPic->GetBuffer());
				char* lpMask2 = (char*)(lpPic->GetMaskPic());
		
				int deltaX = 0;
				int deltaY = srcY2 - srcY1;

				SIZE sz = lpPic->GetPicSize();

				lpBuffer2 += deltaX;
				lpBuffer2 += deltaY * sz.cx;

				lpMask2 += deltaX;
				lpMask2 += deltaY * sz.cx;


//				lpPic->ChangeTranslateBlt(putX,putY,srcX,srcY1,sizeX,sizeY,m_cursorPercent,ps2,lpBuffer2,lpMask2,lpPic);
				lpPic->ChangeTranslateBlt(putX,putY,srcX,srcY1,sizeX,sizeY,m_cursorPercent,ps2,lpPic,srcX,srcY2);

			}


			//del
//			if (m_selectPic != NULL)
//			{
//				m_selectPic->Put(m_printX+m_selectPrintX,m_printY+m_selectPrintY,TRUE);
//			}


			CalcuCursorAnime(md2);
		}
	}

	CAreaControl::AddArea(m_printX,m_printY,m_sizeX,m_sizeY);
}

void CCommonDataFile::AppearPrint(int appearCount, int appearCountMax, int appearType, int md, int clicking, int nm, int loadSave, int lastCount)
{
	//erase
	if (m_bg != NULL)
	{
		m_bg->Blt(m_printX, m_printY, m_printX, m_printY, m_sizeX, m_sizeY, FALSE);
	}

	if ((appearCount == 0) && (appearCountMax > 0))
	{
		return;
	}

	int dv = appearCountMax;
	if (dv < 1) dv = 1;

	int percent = 100;
	if (appearType & 1)
	{
		percent = (100 * appearCount) / dv;
		if (percent < 0) percent = 0;
		if (percent > 100) percent = 100;
	}
	int percent256 = (255 * percent) / 100;


	//base
	if (m_basePrintFlag)
	{
		if (loadSave == 0)
		{
			if (m_quickLoadEnable && (m_number == m_quickSlotNumber))
			{
				if (m_quickLoadBasePic != NULL)
				{
//					m_quickLoadBasePic->Put(m_printX, m_printY, TRUE);
					m_quickLoadBasePic->TransLucentBlt3(m_printX, m_printY, 0, 0, m_sizeX, m_sizeY, percent);
				}
			}
			else
			{
				if (m_loadBasePic != NULL)
				{
//					m_loadBasePic->Put(m_printX, m_printY, TRUE);
					m_loadBasePic->TransLucentBlt3(m_printX, m_printY, 0, 0, m_sizeX, m_sizeY, percent);
				}
			}
		}
		else
		{
			if (m_quickSaveEnable && (m_number == m_quickSlotNumber))
			{
				if (m_quickSaveBasePic != NULL)
				{
//					m_quickSaveBasePic->Put(m_printX, m_printY, TRUE);
					m_quickSaveBasePic->TransLucentBlt3(m_printX, m_printY, 0, 0, m_sizeX, m_sizeY, percent);
				}
			}
			else
			{
				if (m_saveBasePic != NULL)
				{
//					m_saveBasePic->Put(m_printX, m_printY, TRUE);
					m_saveBasePic->TransLucentBlt3(m_printX, m_printY, 0, 0, m_sizeX, m_sizeY, percent);
				}
			}
		}
	}

	//pic
	if (m_dataExistFlag)
	{
		//		if (m_pic != NULL) m_pic->Blt(m_printX + m_picPrintX,m_printY + m_picPrintY,0,0,m_picSizeX,m_picSizeY,FALSE);

#if defined _TINYAN3DLIB_NOTUSED
		CAllGeo::BoxFill(m_printX + m_picPrintX, m_printY + m_picPrintY, m_picSizeX, m_picSizeY, 14, 78, 93);
		m_message->PrintMessage(m_printX + m_picPrintX, m_printY + m_picPrintY, "ÇmÇnÇv", 10);
		m_message->PrintMessage(m_printX + m_picPrintX, m_printY + m_picPrintY + 12, "ÇoÇqÇhÇmÇsÇhÇmÇf", 10);
#else
		if (m_pic != NULL)
		{
			if (m_picPrintType == 0)	//normal
			{
//				m_pic->Blt(m_printX + m_picPrintX, m_printY + m_picPrintY, 0, 0, m_picSizeX, m_picSizeY, FALSE);
				m_pic->TransLucentBlt0(m_printX + m_picPrintX, m_printY + m_picPrintY, 0, 0, m_picSizeX, m_picSizeY, percent);
			}
			else if (m_picPrintType == 1)	//color
			{
//				m_pic->YUVChangeBlt(m_printX + m_picPrintX, m_printY + m_picPrintY, 0, 0, m_picSizeX, m_picSizeY, FALSE, 255);
				m_pic->YUVChangeBlt(m_printX + m_picPrintX, m_printY + m_picPrintY, 0, 0, m_picSizeX, m_picSizeY, FALSE, percent256);
			}
			else if (m_picPrintType == 2)	//multi
			{
				//				m_pic->BltMulti(m_printX + m_picPrintX,m_printY + m_picPrintY,0,0,m_picSizeX,m_picSizeY,FALSE,255);
			}
			else if (m_picPrintType == 3)	//add
			{
				//				m_pic->YUVChangeBlt(m_printX + m_picPrintX,m_printY + m_picPrintY,0,0,m_picSizeX,m_picSizeY,FALSE,255);
			}
		}
#endif

		//
		if (m_numPrintFlag)
		{
			if (nm >= 0)
			{
//				m_numSuuji->Print(m_printX + m_numPrintX, m_printY + m_numPrintY, nm);
				m_numSuuji->AppearPrint(appearCount,appearCountMax,appearType, m_printX + m_numPrintX, m_printY + m_numPrintY, nm);
			}
		}


		if (m_serialNumberPrintFlag)
		{
//			m_serialSuuji->Print(m_printX + m_serialNumberPrintZahyo.x, m_printY + m_serialNumberPrintZahyo.y, m_number + 1);
			m_serialSuuji->AppearPrint(appearCount, appearCountMax, appearType, m_printX + m_serialNumberPrintZahyo.x, m_printY + m_serialNumberPrintZahyo.y, m_number + 1);
		}

		if (m_kazariPrintFlag)
		{
			int putX = m_printX + m_kazariZahyo.x;
			int putY = m_printY + m_kazariZahyo.y;
			int sizeX = m_kazariSize.cx;
			int sizeY = m_kazariSize.cy;

			int srcX = 0;
			int srcY = 0;

//			m_kazariPic->Blt(putX, putY, srcX, srcY, sizeX, sizeY, TRUE);
			m_kazariPic->TransLucentBlt3(putX, putY, srcX, srcY, sizeX, sizeY, percent);
		}


		//Ç®Ç‹ÇØ
		if (m_addPicPrintFlag)
		{
			if (m_addPic != NULL)
			{
				int putX = m_printX + m_addPicPrintZahyo.x;
				int putY = m_printY + m_addPicPrintZahyo.y;
				int sizeX = m_addPicSize.cx;
				int sizeY = m_addPicSize.cy;

				int srcX = 0;
				int srcY = 0;


				int dat = m_gameStatus.nokori;

				if (m_addPicMultiFlag)
				{
					int dv = m_addPicMultiKosuuX;
					if (dv < 1) dv = 1;
					srcX = dat % dv;
					srcY = dat / dv;
					srcX *= sizeX;
					srcY *= sizeY;
				}

				BOOL okflg = TRUE;
				if (m_addPicWithSpecialFlag)
				{
					if (dat < m_specialNumberPrintLimit)
					{
						okflg = FALSE;
					}
				}

				if (okflg)
				{
//					m_addPic->Blt(putX, putY, srcX, srcY, sizeX, sizeY, TRUE);
					m_addPic->TransLucentBlt3(putX, putY, srcX, srcY, sizeX, sizeY, percent);
				}
			}
		}

		//special
		if (m_specialNumberPrintFlag)
		{
			int putX = m_printX + m_specialNumberPrintZahyo.x;
			int putY = m_printY + m_specialNumberPrintZahyo.y;

			int dat = m_gameStatus.nokori;
			if (dat >= m_specialNumberPrintLimit)
			{
//				m_specialNumberSuuji->Print(putX, putY, dat);
				m_specialNumberSuuji->AppearPrint(appearCount, appearCountMax, appearType, putX, putY, dat);
			}
		}

		//save date
		if (m_saveTimePrintFlag)
		{
			int year = m_gameStatus.year;
			int month = m_gameStatus.month;
			int day = m_gameStatus.day;
			int hour = m_gameStatus.hour;
			int minute = m_gameStatus.minute;

			int putX = m_printX + m_saveTimePrintX;
			int putY = m_printY + m_saveTimePrintY;
			int sizeX = m_saveTimeSizeX;
			int sizeY = m_saveTimeSizeY;
			int nextX = m_saveTimeNextX;

			//year
//			m_saveTimeSuuji4->Print(putX, putY, year);
			m_saveTimeSuuji4->AppearPrint(appearCount, appearCountMax, appearType, putX, putY, year);
			putX += nextX * 4;
			// /
//			m_saveDatePic->Blt(putX, putY, sizeX * 11, 0, sizeX, sizeY, TRUE);
			m_saveDatePic->TransLucentBlt3(putX, putY, sizeX * 11, 0, sizeX, sizeY, percent);
			putX += nextX;
			//month
//			m_saveTimeSuuji2->Print(putX, putY, month);
			m_saveTimeSuuji2->AppearPrint(appearCount, appearCountMax, appearType, putX, putY, month);
			putX += nextX * 2;
			// /
//			m_saveDatePic->Blt(putX, putY, sizeX * 11, 0, sizeX, sizeY, TRUE);
			m_saveDatePic->TransLucentBlt3(putX, putY, sizeX * 11, 0, sizeX, sizeY, percent);
			putX += nextX;
			//day
//			m_saveTimeSuuji2->Print(putX, putY, day);
			m_saveTimeSuuji2->AppearPrint(appearCount, appearCountMax, appearType,putX, putY, day);
			putX += nextX * 2;
			// space
			putX += nextX;
			//hour
//			m_saveTimeSuuji2->Print(putX, putY, hour);
			m_saveTimeSuuji2->AppearPrint(appearCount, appearCountMax, appearType, putX, putY, hour);
			putX += nextX * 2;
			//:
//			m_saveDatePic->Blt(putX, putY, sizeX * 10, 0, sizeX, sizeY, TRUE);
			m_saveDatePic->TransLucentBlt3(putX, putY, sizeX * 10, 0, sizeX, sizeY, percent);
			putX += nextX;
			//minute
//			m_saveTimeSuuji2->Print(putX, putY, minute);
			m_saveTimeSuuji2->AppearPrint(appearCount, appearCountMax, appearType, putX, putY, minute);
		}

		if (m_gameTimePrintFlag)
		{
			POINT pt;
			pt.x = m_printX;
			pt.y = m_printY;
			int year = m_lpGameVar->var[m_gameYearVarNumber];
			int date = m_lpGameVar->var[m_gameDateVarNumber];
			int month = date / 100;
			int day = date % 100;

		//	m_printGameDate->Print(pt, year, month, day);
			m_printGameDate->AppearPrint(appearCount, appearCountMax, appearType, pt, year, month, day);
		}


		//comment
		if (m_commentPrintFlag)
		{
			int putX = m_printX + m_commentPrintZahyo.x;
			int putY = m_printY + m_commentPrintZahyo.y;
			LPSTR message = m_gameStatus.minicomment;
			if (m_message != NULL)
			{
				if (appearCount >= appearCountMax)
				{
					m_message->PrintMessage(putX, putY, message, m_commentFontSize, m_commentColorR, m_commentColorR, m_commentColorR, m_commentSukima, -1, m_commentColorShade);
				}
			}
		}

		//text
		if (m_textPrintFlag)
		{
			for (int i = 0; i < m_textPrintGyo; i++)
			{
				int putX = m_printX + m_textPrintZahyo.x;
				int putY = m_printY + m_textPrintZahyo.y + i * m_textNextY;

				LPSTR mes = m_gameStatus.largeComment1;
				if (i == 1) mes = m_gameStatus.largeComment2;
				if (i == 2) mes = m_gameStatus.largeComment3;
				if (i == 3) mes = m_gameStatus.largeComment4;

				if ((*mes) != 0)
				{
					if (appearCount >= appearCountMax)
					{
						m_message->PrintMessage(putX, putY, mes, m_textFontSize, m_textColorR, m_textColorR, m_textColorR, m_textSukima, -1, m_textColorShade);
					}
				}
			}
		}

		if (lastCount > 0)
		{
			if (m_printLastSelect != NULL)
			{
				POINT lastPoint;
				lastPoint.x = m_printX;
				lastPoint.y = m_printY;

				if (appearCount >= appearCountMax)
				{
					m_printLastSelect->DeltaPrint(lastPoint);
				}
				else
				{
					m_printLastSelect->AppearPrint(lastPoint,appearCount, appearCountMax, appearType,true);
				}
			}
		}

		//bad message
		int deltaVersion = GetVersionDeltaMode();

		if (deltaVersion < 0)
		{
			if (m_errorVersionPic != NULL)
			{
//				m_errorVersionPic->Put(m_printX + m_errorPrintX, m_printY + m_errorPrintY, TRUE);
				SIZE sz = m_errorVersionPic->GetPicSize();
				m_errorVersionPic->TransLucentBlt3(m_printX + m_errorPrintX, m_printY + m_errorPrintY, 0,0,sz.cx,sz.cy,percent);
			}
			else
			{
				if (m_badVersionPic != NULL)
				{
//					m_badVersionPic->Put(m_printX + m_badPrintX, m_printY + m_badPrintY, TRUE);
					SIZE sz = m_badVersionPic->GetPicSize();
					m_badVersionPic->TransLucentBlt3(m_printX + m_badPrintX, m_printY + m_badPrintY, 0,0,sz.cx,sz.cy,percent);
				}
			}
		}
		else if (deltaVersion >= 2)
		{
			//version 1.0 BAD
			if (m_badVersionPic != NULL)
			{
//				m_badVersionPic->Put(m_printX + m_badPrintX, m_printY + m_badPrintY, TRUE);
				SIZE sz = m_badVersionPic->GetPicSize();
				m_badVersionPic->TransLucentBlt3(m_printX + m_badPrintX, m_printY + m_badPrintY, 0,0,sz.cx,sz.cy,percent);
			}
		}
		else if (deltaVersion == 1)
		{
			//version 1.0 OK
			if (m_oldVersionPic != NULL)
			{
//				m_oldVersionPic->Put(m_printX + m_oldPrintX, m_printY + m_oldPrintY, TRUE);
				SIZE sz = m_oldVersionPic->GetPicSize();
				m_oldVersionPic->TransLucentBlt3(m_printX + m_oldPrintX, m_printY + m_oldPrintY, 0,0,sz.cx,sz.cy,percent);
			}
		}
		else
		{
			//ok
		}
	}




	if (md >= 1)
	{
		//ëIëï\é¶ÇÇ¬ÇØÇÈÇ…Ç·
		if (m_selectPrintMode == 0)
		{
			if ((clicking & 1) == 0)
			{
				CAllGeo::TransBoxFill(m_printX + m_selectPrintX, m_printY + m_selectPrintY, m_selectSizeX, m_selectSizeY, m_selectColorR, m_selectColorG, m_selectColorB, (m_selectColorPercent * percent) / 100);
			}
		}
		else if (m_selectPrintMode == 1)
		{
			if ((clicking & 1) == 0)
			{
//				m_selectPic->Put(m_printX + m_selectPrintX, m_printY + m_selectPrintY, TRUE);
				SIZE sz = m_selectPic->GetPicSize();
				m_selectPic->TransLucentBlt3(m_printX + m_selectPrintX, m_printY + m_selectPrintY, 0,0,sz.cx,sz.cy,percent);
			}
		}
		else if (m_selectPrintMode == 2)
		{
			int md2 = md - 1;
			if (clicking >= 1) md2 += 3;

			GetNowCursorPic(md2);

			int sizeX = m_selectSizeX;
			int sizeY = m_selectSizeY;
			CPicture* lpPic = m_cursorPic[md - 1];

			int srcX = 0;
			if (clicking >= 1) srcX = sizeX;

			int srcY1 = sizeY * m_cursor1;
			int srcY2 = sizeY * m_cursor2;

			int putX = m_printX + m_selectPrintX;
			int putY = m_printY + m_selectPrintY;


			if (m_cursorPercent == 100)
			{
//				lpPic->Blt(putX, putY, srcX, srcY1, sizeX, sizeY, TRUE);
				lpPic->TransLucentBlt3(putX, putY, srcX, srcY1, sizeX, sizeY, percent);
			}
			else if (m_cursorPercent == 0)
			{
//				lpPic->Blt(putX, putY, srcX, srcY2, sizeX, sizeY, TRUE);
				lpPic->TransLucentBlt3(putX, putY, srcX, srcY2, sizeX, sizeY, percent);
			}
			else
			{

				int ps2 = 100 - m_cursorPercent;
				int* lpBuffer2 = (int*)(lpPic->GetBuffer());
				char* lpMask2 = (char*)(lpPic->GetMaskPic());

				int deltaX = 0;
				int deltaY = srcY2 - srcY1;

				SIZE sz = lpPic->GetPicSize();

				lpBuffer2 += deltaX;
				lpBuffer2 += deltaY * sz.cx;

				lpMask2 += deltaX;
				lpMask2 += deltaY * sz.cx;


				//				lpPic->ChangeTranslateBlt(putX,putY,srcX,srcY1,sizeX,sizeY,m_cursorPercent,ps2,lpBuffer2,lpMask2,lpPic);
//				lpPic->ChangeTranslateBlt(putX, putY, srcX, srcY1, sizeX, sizeY, m_cursorPercent, ps2, lpPic, srcX, srcY2);
				lpPic->ChangeTranslateBlt(putX, putY, srcX, srcY1, sizeX, sizeY, (m_cursorPercent*percent)/100, ps2, lpPic, srcX, srcY2);

			}


			//del
//			if (m_selectPic != NULL)
//			{
//				m_selectPic->Put(m_printX+m_selectPrintX,m_printY+m_selectPrintY,TRUE);
//			}


			CalcuCursorAnime(md2);
		}
	}

	CAreaControl::AddArea(m_printX, m_printY, m_sizeX, m_sizeY);
}


/*
void CCommonDataFile::PrintSuuji0(int x, int y,int d, int keta)
{
//	if (m_fontPic == NULL) return;

	x += m_gameFontNextX * (keta-1);
	for (int i=0;i<keta;i++)
	{
		int dt = d % 10;

		m_gameDatePic->Blt(x,y,dt*m_gameFontSizeX,0,m_gameFontSizeX,m_gameFontSizeY,TRUE);

		x -= m_gameFontNextX;
		d /= 10;
	}
}

void CCommonDataFile::PrintSuuji(int x, int y,int d, int keta)
{
//	if (m_fontPic == NULL) return;

	x += m_saveFontNextX * (keta-1);
	for (int i=0;i<keta;i++)
	{
		int dt = d % 10;

		m_saveDatePic->Blt(x,y,dt*m_saveFontSizeX,0,m_saveFontSizeX,m_saveFontSizeY,TRUE);

		x -= m_saveFontNextX;
		d /= 10;
	}
}
*/


BOOL CCommonDataFile::CheckOn(int mouseX, int mouseY)
{
	int x = mouseX - m_printX;
	int y = mouseY - m_printY;

	if ((x>=0) && (x<m_sizeX) && (y>=0) && (y<m_sizeY)) return TRUE;

	return FALSE;
}




int CCommonDataFile::Load(int n)
{
	LPSTR saveFolder = CMySaveFolder::GetFullFolder();

	char filename[1024];
//	if (m_game->CheckTaikenVersion() == FALSE)
	if (CCommonGameVersion::CheckTaikenVersion() == FALSE)
	{
		wsprintf(filename,"%s\\data%d.sav",saveFolder,n);
	}
	else
	{
		wsprintf(filename,"%s\\tdata%d.sav",saveFolder,n);
	}

	m_file = CMyFile::OpenFullPath(filename,"rb");
	if (m_file == NULL) return -1;


	LoadHeader();
	LoadInfo();
	LoadStatus();
	LoadMiniCG();
	LoadVar();
	LoadEffect();
	LoadEffectFileName();
	LoadMessage();

	if (m_gameInfo.omakeClass)
	{
		LoadOmakeClassData();
	}

	if (m_gameInfo.cutin)
	{
		LoadCutin();
	}

	if (m_gameInfo.log)
	{
		LoadLog();
	}

	for (int i=0;i<m_extDataBlockKosuu;i++)
	{
		LoadExtData(i);
	}

	fclose(m_file);

	return m_gameStatus.gameMode;
}

int CCommonDataFile::Save(int n)
{
	LPSTR saveFolder = CMySaveFolder::GetFullFolder();

	char filename[1024];
//	if (m_game->CheckTaikenVersion() == FALSE)
	if (CCommonGameVersion::CheckTaikenVersion() == FALSE)
	{
		wsprintf(filename,"%s\\data%d.sav",saveFolder,n);
	}
	else
	{
		wsprintf(filename,"%s\\tdata%d.sav",saveFolder,n);
	}

//	sprintf(filename,"sav\\data%d.sav",n);

	m_file = CMyFile::OpenFullPath(filename,"wb");

	if (m_file == NULL) return -1;

	SaveHeader();
	SaveInfo();
	SaveStatus();
	SaveMiniCG();
	SaveVar();
	SaveEffect();
	SaveEffectFileName();
	SaveMessage();

	if (m_omakeClassExistFlag)
	{
		SaveOmakeClassData();
	}

	if (m_cutinUseFlag)
	{
		SaveCutin();
	}

	if (m_logFlag)
	{
		SaveLog();
	}

	for (int i=0;i<m_extDataBlockKosuu;i++)
	{
		SaveExtData(i);
	}


	fclose(m_file);

	return 0;	//???
}



BOOL CCommonDataFile::LoadHeader(void)
{
	Load1Block();	//skip
	return TRUE;
}

BOOL CCommonDataFile::LoadInfo(void)
{
	Load1Block();	//skip
	m_game->SetGameInfoByLoad(&m_gameInfo);
	return TRUE;
}


BOOL CCommonDataFile::LoadStatus(void)
{
	fread(&m_gameStatus,sizeof(GAMESTATUS),1,m_file);
	m_game->SetGameStatusByLoad(&m_gameStatus);
	return TRUE;
}


BOOL CCommonDataFile::LoadVar(void)
{
	Load1Block();
	m_game->SetVarByLoad(m_commonBuffer2);
	return TRUE;
}


BOOL CCommonDataFile::LoadMiniCG(void)
{
	fread(m_commonBuffer2,sizeof(GAMEHEADER),1,m_file);	//skip header
	fread(m_commonBuffer2,sizeof(int),4,m_file);	//skip size 

	int* ptr = (int*)(m_pic->GetBuffer());
	fread(ptr,sizeof(int),m_picSizeX*m_picSizeY,m_file);
	return TRUE;
}


BOOL CCommonDataFile::LoadMessage(void)
{
	Load1Block();
	m_game->SetMessageByLoad(m_commonBuffer2);
	return TRUE;
}




BOOL CCommonDataFile::LoadEffect(void)
{
	Load1Block();
	m_game->SetEffectByLoad(m_commonBuffer2);
	return TRUE;
}


BOOL CCommonDataFile::LoadEffectFileName(void)
{
	Load1Block();
	m_game->SetEffectFileNameByLoad(m_commonBuffer2);
	return TRUE;
}


BOOL CCommonDataFile::LoadExtData(int n)
{
	Load1Block();

	char* ptr = (char*)m_commonBuffer2;
	ptr += sizeof(GAMEGENERALDATA);

	m_game->SetExtDataByLoadGeneral(ptr,n);

	return TRUE;
}

BOOL CCommonDataFile::LoadCutin(void)
{
	Load1Block();
	m_game->SetCutinByLoad(m_commonBuffer2);
	return TRUE;
}

BOOL CCommonDataFile::LoadLog(void)
{
	Load1Block();
	m_game->SetLogByLoad(m_commonBuffer2);
	return TRUE;
}


BOOL CCommonDataFile::LoadOmakeClassData(void)
{
	Load1Block();
	char* ptr = (char*)m_commonBuffer2;
	ptr += sizeof(GAMEGENERALDATA);
	m_game->SetOmakeClassDataByLoad(ptr);

	return TRUE;
}


BOOL CCommonDataFile::Load1Block(void)
{
	fread(m_commonBuffer2,sizeof(int),1,m_file);
	int ln = *m_commonBuffer2;
	if (ln>4)
	{
		fread(m_commonBuffer2+1 ,sizeof(char),ln-4,m_file);
	}
	return TRUE;
}


/////////////////

BOOL CCommonDataFile::SaveHeader(void)
{
	int sz = sizeof(GAMEHEADER);
	GAMEHEADER* header = (GAMEHEADER*)m_commonBuffer2;
	ZeroMemory(header,sz);

	LPSTR headerName = m_game->GetSaveHeaderName();

//	MakeHeader(m_commonBuffer2,sz,GAMEDATATYPE_HEADER,"à≈ÇÃê∫SAVEDATA");
	MakeHeader(m_commonBuffer2,sz,GAMEDATATYPE_HEADER,headerName);

	fwrite(m_commonBuffer2,sizeof(GAMEHEADER),1,m_file);
	return TRUE;
}


BOOL CCommonDataFile::SaveInfo(void)
{
	int sz = sizeof(GAMEINFO);
	GAMEINFO* header = (GAMEINFO*)m_commonBuffer2;
	ZeroMemory(header,sz);
	MakeHeader(m_commonBuffer2,sz,GAMEDATATYPE_INFO,"INFO");

	header->extDataKosuu = m_extDataBlockKosuu;

	header->omakeClass = 0;
	if (m_omakeClassExistFlag)
	{
		header->omakeClass = 1;
	}

	header->cutin = 0;
	if (m_cutinUseFlag)
	{
		header->cutin = 1;
	}

	header->log = 0;
	if (m_logFlag)
	{
		header->log = 1;
	}

	header->dataKosuu = 8 + m_extDataBlockKosuu + header->cutin + header->omakeClass;

//	header->version = m_gameVersion;
	header->version = m_game->GetGameVersion();


	fwrite(m_commonBuffer2,sizeof(GAMEINFO),1,m_file);
	return TRUE;
}



BOOL CCommonDataFile::SaveStatus(void)
{
	int sz = sizeof(GAMESTATUS);
	ZeroMemory(&m_gameStatus,sz);

	//get data

	m_game->GetGameStatusForSave(&m_gameStatus);


	SYSTEMTIME st;
	GetLocalTime(&st);

	m_gameStatus.year = st.wYear;
	m_gameStatus.month = st.wMonth;
	m_gameStatus.day = st.wDay;
	m_gameStatus.week = st.wDayOfWeek;
	m_gameStatus.hour = st.wHour;
	m_gameStatus.minute = st.wMinute;
	m_gameStatus.second = st.wSecond;
	m_gameStatus.milli = st.wMilliseconds;

	m_gameStatus.saveCount++;


	MakeHeader((int*)&m_gameStatus,sz,GAMEDATATYPE_STATUS,"GAMESTATUS");

	fwrite(&m_gameStatus,sizeof(GAMESTATUS),1,m_file);
	return TRUE;
}


BOOL CCommonDataFile::SaveMiniCG(void)
{
//	int sz = sizeof(GAMEMINICG);
	int sz = sizeof(GAMEGENERALDATA) + sizeof(int)*4 + m_picSizeX * m_picSizeY * sizeof(int);

	ZeroMemory(m_commonBuffer2,sz);
	GAMEMINICG* lp = (GAMEMINICG*)m_commonBuffer2;
	MakeHeader(m_commonBuffer2,sz,GAMEDATATYPE_MINICG,"MINICG");
	
	lp->sizeX = m_picSizeX;
	lp->sizeY = m_picSizeY;

	m_game->GetMiniCGForSave(m_commonBuffer2);

	fwrite(m_commonBuffer2,sz,1,m_file);

	return TRUE;
}


BOOL CCommonDataFile::SaveVar(void)
{
	int varType = m_game->GetVarType();

	int sz = sizeof(GAMEVAR1);
	if (varType != 0)
	{
		sz = sizeof(GAMEVAR);
	}


	ZeroMemory(m_commonBuffer2,sz);
	MakeHeader(m_commonBuffer2,sz,GAMEDATATYPE_VAR,"GAMEVAR");

	m_game->GetVarForSave(m_commonBuffer2);
	fwrite(m_commonBuffer2,sz,1,m_file);

	return TRUE;
}


BOOL CCommonDataFile::SaveEffect(void)
{
	int sz = sizeof(GAMEEFFECT);
	ZeroMemory(m_commonBuffer2,sz);
	MakeHeader(m_commonBuffer2,sz,GAMEDATATYPE_EFFECT,"EFFECT");
	m_game->GetEffectForSave(m_commonBuffer2);
	fwrite(m_commonBuffer2,sz,1,m_file);
	return TRUE;
}

BOOL CCommonDataFile::SaveEffectFileName(void)
{
	int sz = sizeof(GAMEEFFECTFILENAME);
	ZeroMemory(m_commonBuffer2,sz);
	MakeHeader(m_commonBuffer2,sz,GAMEDATATYPE_EFFECTFILENAME,"EFFECTFILENAME");
	m_game->GetEffectFileNameForSave(m_commonBuffer2);
	fwrite(m_commonBuffer2,sz,1,m_file);
	return TRUE;
}


BOOL CCommonDataFile::SaveMessage(void)
{
	int sz = sizeof(GAMEMESSAGE);

	ZeroMemory(m_commonBuffer2,sz);
	MakeHeader(m_commonBuffer2,sz,GAMEDATATYPE_MESSAGE,"MESSAGE");
	m_game->GetMessageForSave(m_commonBuffer2);
	fwrite(m_commonBuffer2,sz,1,m_file);

	return TRUE;
}


BOOL CCommonDataFile::SaveExtData(int n)
{
	int sz = m_pExtBlockSize[n];
	sz += sizeof(GAMEGENERALDATA);
	ZeroMemory(m_commonBuffer2,sz);

	char ename[32];
	wsprintf(ename,"EXT%d",n+1);


	MakeHeader(m_commonBuffer2,sz,GAMEDATATYPE_EXT+n,ename);

	char* ptr = (char*)m_commonBuffer2;
	ptr += sizeof(GAMEGENERALDATA);
	m_game->GetExtDataForSaveGeneral(ptr,n);

	fwrite(m_commonBuffer2,sz,1,m_file);

	return TRUE;
}

BOOL CCommonDataFile::SaveCutin(void)
{
	int sz = sizeof(GAMECUTIN);

	ZeroMemory(m_commonBuffer2,sz);
	MakeHeader(m_commonBuffer2,sz,GAMEDATATYPE_CUTIN,"CUTIN");
	m_game->GetCutinForSave(m_commonBuffer2);
	fwrite(m_commonBuffer2,sz,1,m_file);

	return TRUE;
}

BOOL CCommonDataFile::SaveLog(void)
{
	int sz = sizeof(GAMELOG);

	ZeroMemory(m_commonBuffer2, sz);
	MakeHeader(m_commonBuffer2, sz, GAMEDATATYPE_LOG, "LOG");
	m_game->GetLogForSave(m_commonBuffer2);
	fwrite(m_commonBuffer2, sz, 1, m_file);

	return TRUE;
}



BOOL CCommonDataFile::SaveOmakeClassData(void)
{
	int sz = sizeof(GAMEOMAKECLASSDATA);


	ZeroMemory(m_commonBuffer2,sz);
	MakeHeader(m_commonBuffer2,sz,GAMEDATATYPE_OMAKECLASS,"OMAKECLASS");

	char* ptr = (char*)m_commonBuffer2;
	ptr += sizeof(GAMEGENERALDATA);

	m_game->GetOmakeClassDataForSave(ptr);
	fwrite(m_commonBuffer2,sz,1,m_file);

	return TRUE;
}


void CCommonDataFile::MakeHeader(int* work, int sz, int cd, LPSTR mes)
{
	GAMEHEADER* header = (GAMEHEADER*)work;

	header->general.size = sz;
	header->general.code = cd;
	header->general.dummy1 = 0;
	header->general.dummy2 = 0;

	ZeroMemory(header->general.message,16);

	int ln = (int)strlen(mes);
	if (ln>15) ln = 15;
	memcpy(header->general.message,mes,ln);
}




BOOL CCommonDataFile::CheckLoadOkVersion(void)
{
	int delta = GetVersionDeltaMode();
	if (delta < 0) return FALSE;

	if ((delta == 0) || (delta == 1)) return TRUE;

	return FALSE;
}

// highVersion changed! all data cannot use
// middleVersion changed cannot use message etc
// lowVersion changed use data ok



int CCommonDataFile::GetVersionDeltaMode(void)
{
	if (m_gameInfo.version > m_systemGameVersion) return -1;	//å√Ç¢ÇµÇ∑ÇƒÇﬁÇ≈êVÇµÇ¢dataÇÇÊÇ‡Ç§Ç∆ÇµÇƒÇÈ

	int highVersion =   (m_gameInfo.version >> 16) & 0xff;
	int middleVersion = (m_gameInfo.version >>  8) & 0xff;
	int lowVersion =    (m_gameInfo.version      ) & 0xff;

	int systemHighVersion = (m_systemGameVersion >> 16) & 0xff;
	int systemMiddleVersion = (m_systemGameVersion >>  8) & 0xff;
	int systemLowVersion = (m_systemGameVersion      ) & 0xff;


	if (highVersion < systemHighVersion) return 2;

	if (middleVersion < systemMiddleVersion)
	{
		int mode = m_gameStatus.gameMode;
		if (mode == PRINTMESSAGE_MODE) return 2;

		if (mode == SELECTMESSAGE_MODE)
		{
			if (m_gameStatus.scriptRunMode > 0) return 2;
		}

		return 1;
	}

	return 0;
}


void CCommonDataFile::GetNowCursorPic(int n)
{
	if (m_animePattern[n] <= 1)
	{
		m_cursor1 = 0;
		m_cursor2 = 0;
		m_cursorPercent = 100;
		return;
	}

	int pattern = m_animePattern[n];
	int speed = m_animeSpeed[n];
	int count = m_animeCount[n];
	int type = m_animeType[n];


	int revFlag = 0;
	int dv = pattern;

	if (speed<1) speed = 1;

	if ((type == 3) || (type == 4) || (type == 7) || (type == 8))
	{
		dv = (pattern-1) * 2;
		if (dv<1) dv = 1;
		revFlag = 1;
	}

	int limitFlag = 0;
	if ((type == 2) || (type == 4) || (type == 6) || (type == 8))
	{
		limitFlag = 1;
	}

	int pic1 = count / speed;
	int pic2 = pic1+1;
	
	if (limitFlag)
	{
		int limData = dv-1;
		if (revFlag) limData = dv;

		if (pic1>=dv) pic1 = limData;
		if (pic2>=dv) pic2 = limData;
	}

	pic2 %= dv;

	int percent = 100;

	if (revFlag)
	{
		if (pic1 >= pattern) pic1 = (pattern-1)*2 - pic1;
		if (pic2 >= pattern) pic2 = (pattern-1)*2 - pic2;
	}

	if (type >= 5)
	{
		percent = 100 * (speed - (count - ((count / speed) * speed)));
		percent /= speed;
	}

	m_cursor1 = pic1;
	m_cursor2 = pic2;
	m_cursorPercent = percent;
}


void CCommonDataFile::CalcuCursorAnime(int n)
{
	if (m_animePattern[n] <= 1) return;
	
	int pattern = m_animePattern[n];
	int speed = m_animeSpeed[n];
	int count = m_animeCount[n];
	int type = m_animeType[n];

	if (speed<1) speed = 1;

	int revFlag = 0;
	int dv = pattern;

	if ((type == 3) || (type == 4) || (type == 7) || (type == 8))
	{
		dv = (pattern-1) * 2;
		if (dv<1) dv = 1;
		revFlag = 1;
	}

	dv *= speed;

	int limitFlag = 0;
	if ((type == 2) || (type == 4) || (type == 6) || (type == 8))
	{
		limitFlag = 1;
	}

	count += 1;
	if (limitFlag)
	{
		if (count >= dv) count = dv;
	}
	else
	{
		count %= dv;
	}

	m_animeCount[n] = count;
}


void CCommonDataFile::InitAnime(void)
{
	for (int i=0;i<6;i++)
	{
		m_animeCount[i] = 0;
	}
}


int CCommonDataFile::GetSaveMode(void)
{
	return m_gameStatus.gameMode;
}

LPSTR CCommonDataFile::GetLargeMessage(int n)
{
	if (n == 0) return m_gameStatus.largeComment1;
	if (n == 1) return m_gameStatus.largeComment2;
	if (n == 2) return m_gameStatus.largeComment3;
	if (n == 3) return m_gameStatus.largeComment4;

	return m_gameStatus.largeComment1;//youjin
}

LPSTR CCommonDataFile::GetMiniMessage(int n)
{
	return m_gameStatus.minicomment;
}

void CCommonDataFile::ChangeExtDataSize(int extNumber,int dataSize)
{
	if (m_extDataBlockKosuu > 0)
	{
		if ((extNumber >= 0) && (extNumber < m_extDataBlockKosuu))
		{
			if (m_pExtBlockSize != NULL)
			{
				m_pExtBlockSize[extNumber] = dataSize;
			}
		}
	}
}


/*_*/

