//
// CommonSystemFile.cpp
//


#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myFile.h"

#include "mySaveFolder.h"

#include "commonGameVersion.h"
#include "CommonSystemFile.h"

#if _MSC_VER >= 1500
#include <rpcdce.h>
#endif




char CCommonSystemFile::m_saveFileNameNormal[] = "sysfile";
char CCommonSystemFile::m_saveFileNameTaiken[] = "tsysfile";
char CCommonSystemFile::m_saveFileNameNormal2[] = "sysfile2";
char CCommonSystemFile::m_saveFileNameTaiken2[] = "tsysfile2";
char CCommonSystemFile::m_saveFileNameNormal3[] = "sysfile3";
char CCommonSystemFile::m_saveFileNameTaiken3[] = "tsysfile3";

int CCommonSystemFile::m_maxScriptNumberForInit = 64;
int CCommonSystemFile::m_maxCGCharaNumberForInit = 20;
int CCommonSystemFile::m_maxMovieCharaNumberForInit = 20;

int CCommonSystemFile::m_CGCharaNumber = 0;

char CCommonSystemFile::m_defaultSei[16] = "";
char CCommonSystemFile::m_defaultMei[16] = "";


CCommonSystemFile::CCommonSystemFile()
{
	int bt = 1;
	for (int i = 0; i < 32; i++)
	{
		m_bitTable[i] = bt;
		bt <<= 1;
	}
	m_bitTable[31] = 0x80000000;

	m_taikenFlag = FALSE;
	if (CCommonGameVersion::CheckTaikenOrNetVersion()) m_taikenFlag = TRUE;

	m_netVersion = FALSE;
	if (CCommonGameVersion::CheckNetVersion()) m_netVersion = TRUE;


	int varType = GetVarType();

	if (varType == 0)
	{
		m_saveFileNameOnly = m_saveFileNameNormal;
		if (m_taikenFlag) m_saveFileNameOnly = m_saveFileNameTaiken;
	}
	else
	{
#if !defined __SYSTEMNNN_VER2__
		m_saveFileNameOnly = m_saveFileNameNormal2;
		if (m_taikenFlag) m_saveFileNameOnly = m_saveFileNameTaiken2;
#else
		m_saveFileNameOnly = m_saveFileNameNormal3;
		if (m_taikenFlag) m_saveFileNameOnly = m_saveFileNameTaiken3;
#endif
	}

	CalcuInitParameter();
}


CCommonSystemFile::~CCommonSystemFile()
{
}

void CCommonSystemFile::End(void)
{
}


BOOL CCommonSystemFile::Load(BOOL errorPrintFlag)
{
	LPSTR saveFolder = CMySaveFolder::GetFullFolder();

	char filename[1024];
	wsprintf(filename,"%s\\%s.sav",saveFolder,m_saveFileNameOnly);

	FILE* file = CMyFile::OpenFullPath(filename,"rb");

	if (file == NULL)
	{
		wsprintf(filename,"sav\\%s.org",m_saveFileNameOnly);
		file = CMyFile::Open(filename,"rb");
	}

	CreateInitData();

	if (file == NULL)
	{
		if (errorPrintFlag)
		{
			char ermes[1024];
			if (CCommonGameVersion::CheckTaikenOrNetVersion() == FALSE)
			{
//				wsprintf(ermes,"ƒVƒXƒeƒ€ƒtƒ@ƒCƒ‹:%s\\sysfile.sav‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ",saveFolder);
				wsprintf(ermes, "ƒVƒXƒeƒ€ƒtƒ@ƒCƒ‹:%s\\%s.sav‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ", saveFolder, m_saveFileNameOnly);
			}
			else
			{
//				wsprintf(ermes,"ƒVƒXƒeƒ€ƒtƒ@ƒCƒ‹:%s\\tsysfile.sav‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ",saveFolder);
				wsprintf(ermes, "ƒVƒXƒeƒ€ƒtƒ@ƒCƒ‹:%s\\%s.sav‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ", saveFolder, m_saveFileNameOnly);
			}

			MessageBox(NULL,ermes,"Error",MB_OK);
		}

		Save();

		return FALSE;
	}


	fread(&m_dataHeader.size,sizeof(m_dataHeader.size),1,file);
	fread(&m_dataHeader.code,sizeof(char),m_dataHeader.size-4,file);

	int dataKosuu = m_dataHeader.dataKosuu;

	if (dataKosuu>1)
	{
		fread(&m_systemdata.size,sizeof(m_systemdata.size),1,file);
		fread(&m_systemdata.code,sizeof(char),m_systemdata.size-4,file);
	}

	if (dataKosuu>2)
	{
		fread(&m_messageFlag.size,sizeof(m_messageFlag.size),1,file);
		fread(&m_messageFlag.code,sizeof(char),m_messageFlag.size-4,file);
	}

	if (dataKosuu>3)
	{
		fread(&m_systemVar.size, sizeof(m_systemVar.size), 1, file);
		fread(&m_systemVar.code, sizeof(char), m_systemVar.size - 4, file);
	}

	if (dataKosuu>4)
	{
		fread(&m_cgFlag.size,sizeof(m_cgFlag.size),1,file);
		fread(&m_cgFlag.code,sizeof(char),m_cgFlag.size-4,file);
	}

	if (dataKosuu>5)
	{
		fread(&m_sceneFlag.size,sizeof(m_sceneFlag.size),1,file);
		fread(&m_sceneFlag.code,sizeof(char),m_sceneFlag.size-4,file);

	}

	if (dataKosuu>6)
	{
		fread(&m_filmFlag.size,sizeof(m_filmFlag.size),1,file);
		fread(&m_filmFlag.code,sizeof(char),m_filmFlag.size-4,file);
	}

	if (dataKosuu>7)
	{
		fread(&m_voiceFlag.size,sizeof(m_voiceFlag.size),1,file);
		fread(&m_voiceFlag.code,sizeof(char),m_voiceFlag.size-4,file);
	}

	if (dataKosuu>8)
	{
		fread(&m_movieFlag.size,sizeof(m_movieFlag.size),1,file);
		fread(&m_movieFlag.code,sizeof(char),m_movieFlag.size-4,file);
	}

	if (dataKosuu>9)
	{
		fread(&m_musicFlag.size,sizeof(m_musicFlag.size),1,file);
		fread(&m_musicFlag.code,sizeof(char),m_musicFlag.size-4,file);
	}

	if (dataKosuu>10)
	{
		fread(&m_okikae.size,sizeof(m_okikae.size),1,file);
		fread(&m_okikae.code,sizeof(char),m_okikae.size-4,file);
	}

	if (dataKosuu>11)
	{
		fread(&m_achievement.size,sizeof(m_achievement.size),1,file);
		fread(&m_achievement.code,sizeof(char),m_achievement.size-4,file);
	}

	if (dataKosuu>12)
	{
		fread(&m_term.size,sizeof(m_term.size),1,file);
		fread(&m_term.code,sizeof(char),m_term.size-4,file);
	}

	if (dataKosuu>13)
	{
		fread(&m_charaVoiceFlag.size,sizeof(m_charaVoiceFlag.size),1,file);
		fread(&m_charaVoiceFlag.code,sizeof(char),m_charaVoiceFlag.size-4,file);
	}

	if (dataKosuu > 14)
	{
		fread(&m_systemFlag2.size, sizeof(m_systemFlag2.size), 1, file);
		fread(&m_systemFlag2.code, sizeof(char), m_systemFlag2.size - 4, file);
	}

	if (dataKosuu > 15)
	{
		fread(&m_selectMessageFlag.size, sizeof(m_selectMessageFlag.size), 1, file);
		fread(&m_selectMessageFlag.code, sizeof(char), m_selectMessageFlag.size - 4, file);
	}

	fclose(file);

	return TRUE;

}


void CCommonSystemFile::CreateInitData(void)
{
	ZeroMemory(&m_dataHeader,sizeof(m_dataHeader));
	ZeroMemory(&m_systemdata,sizeof(m_systemdata));
	ZeroMemory(&m_messageFlag,sizeof(m_messageFlag));
	ZeroMemory(&m_systemVar,sizeof(m_systemVar));
	ZeroMemory(&m_cgFlag,sizeof(m_cgFlag));
	ZeroMemory(&m_sceneFlag,sizeof(m_sceneFlag));
	ZeroMemory(&m_filmFlag,sizeof(m_filmFlag));
	ZeroMemory(&m_voiceFlag,sizeof(m_voiceFlag));
	ZeroMemory(&m_movieFlag,sizeof(m_movieFlag));
	ZeroMemory(&m_musicFlag,sizeof(m_musicFlag));
	ZeroMemory(&m_okikae,sizeof(m_okikae));
	ZeroMemory(&m_achievement,sizeof(m_achievement));
	ZeroMemory(&m_term,sizeof(m_term));
	ZeroMemory(&m_charaVoiceFlag,sizeof(m_charaVoiceFlag));
	ZeroMemory(&m_systemFlag2, sizeof(m_systemFlag2));
	ZeroMemory(&m_selectMessageFlag, sizeof(m_selectMessageFlag));

	//Make Info
	m_dataHeader.size = sizeof(m_dataHeader);
	m_dataHeader.code = 0;	
	m_dataHeader.dataKosuu = 15;
	CopyMemory(&m_dataHeader.message[0],"FILE INFO      ",16);


	//Make Header
	m_systemdata.size = sizeof(m_systemdata);
	m_systemdata.code = 1;	
	CopyMemory(&m_systemdata.message[0],"SYSTEM DATA    ",16);


	SYSTEMTIME st;
	GetLocalTime(&st);

	m_systemdata.year = st.wYear;
	m_systemdata.month = st.wMonth;
	m_systemdata.day = st.wDay;
	m_systemdata.week = st.wDayOfWeek;
	m_systemdata.hour = st.wHour;
	m_systemdata.minute = st.wMinute;
	m_systemdata.second = st.wSecond;
	m_systemdata.milli = st.wMilliseconds;

	m_systemdata.windowX = 0;
	m_systemdata.windowY = 0;
	
	m_systemdata.windowSizeX = 800;
	m_systemdata.windowSizeY = 600;
	m_systemdata.colorBits = 16;

	m_systemdata.fullScreenFlag = 0;
	m_systemdata.midiMode = 0;
	m_systemdata.saveCount = 0;

	m_systemdata.normalMusicVolume = 30;
	m_systemdata.normalSoundVolume = 70;
	m_systemdata.normalVoiceVolume = 60;
	m_systemdata.normalCDVolume = 80;

	m_systemdata.directMusicVolume = 60;
	m_systemdata.directSoundVolume = 80;
	m_systemdata.directVoiceVolume = 70;
	m_systemdata.directCDVolume = 80;

	m_systemdata.voiceMode = 1;
	m_systemdata.warningMode = 1;

	m_systemdata.messageSpeed = 2;
	m_systemdata.skipMode = 0;


	m_systemdata.musicSwitch = 1;
	m_systemdata.soundSwitch = 1;
	m_systemdata.voiceSwitch = 1;
	m_systemdata.movieSwitch = 1;
	m_systemdata.soundVoiceSwitch = 1;
	m_systemdata.totalVolumeSwitch = 1;

	m_systemdata.musicVolume = 90;
	m_systemdata.soundVolume = 90;
	m_systemdata.voiceVolume = 90;
	m_systemdata.movieVolume = 90;
	m_systemdata.soundVoiceVolume = 90;
	m_systemdata.totalVolume = 90;
#if !defined _TINYAN3DLIB_
	m_systemdata.d2d3d = 2;	//2D
#else
	m_systemdata.d2d3d = 3;	//2D
#endif

	m_systemdata.shader = 0;	//vshader 0:auto 1:soft 2:hard
	m_systemdata.needShader = 2; //

	m_systemdata.autoSpeedSlider = 50;

	m_systemdata.screenSizeType = 0;
	m_systemdata.genericFlag = 0;


//	if (m_netVersion == FALSE)
//	{
//		m_systemdata.bgmMode = 1;
//	}
//	else
//	{
//		m_systemdata.bgmMode = 0;
//	}


	memcpy(m_systemdata.fontName,"‚l‚r ƒSƒVƒbƒN",strlen("‚l‚r ƒSƒVƒbƒN")+1);

	memcpy(m_systemdata.sei,m_defaultSei,strlen(m_defaultSei)+1);
	memcpy(m_systemdata.mei,m_defaultMei,strlen(m_defaultMei)+1);


//			m_cgdata[i].size = sizeof(m_cgdata[i]);
//			m_cgdata[i].code = 2;
//			char mes[256];
//			sprintf(mes,"CG FLAG%d          ",i+1);
//			CopyMemory(&m_cgdata[i].message[0],mes,16);
//			m_cgdata[i].message[15] = 0;

	m_messageFlag.size = sizeof(m_messageFlag);
	m_messageFlag.code = 5;
	CopyMemory(m_messageFlag.message,"MES FLAG       ",16);


	int varType = GetVarType();
	if (varType == 0)
	{
		m_systemVar.size = sizeof(SYSTEMVAR1);//old size
	}
	else
	{
		m_systemVar.size = sizeof(SYSTEMVAR);
	}
	m_systemVar.code = 6;
	CopyMemory(m_systemVar.message,"SYSTEMVAR      ",16);

	m_cgFlag.size = sizeof(m_cgFlag);
	m_cgFlag.code = 7;
	CopyMemory(m_cgFlag.message,"CGFLAG         ",16);

	m_sceneFlag.size = sizeof(m_sceneFlag);
	m_sceneFlag.code = 8;
	CopyMemory(m_sceneFlag.message,"SCENEFLAG      ",16);

	m_filmFlag.size = sizeof(m_filmFlag);
	m_filmFlag.code = 9;
	CopyMemory(m_filmFlag.message,"FILMFLAG       ",16);

	m_voiceFlag.size = sizeof(m_voiceFlag);
	m_voiceFlag.code = 10;
	CopyMemory(m_voiceFlag.message,"VOICEFLAG      ",16);

	m_movieFlag.size = sizeof(m_movieFlag);
	m_movieFlag.code = 11;
	CopyMemory(m_movieFlag.message,"MOVIEFLAG      ",16);

	m_musicFlag.size = sizeof(m_musicFlag);
	m_musicFlag.code = 12;
	CopyMemory(m_musicFlag.message,"MUSICFLAG      ",16);

	m_okikae.size = sizeof(m_okikae);
	m_okikae.code = 13;
	CopyMemory(m_okikae.message,"OKIKAE         ",16);

	m_achievement.size = sizeof(m_achievement);
	m_achievement.code = 14;
	CopyMemory(m_achievement.message,"ACHIEVEMENT    ",16);

	m_term.size = sizeof(m_term);
	m_term.code = 15;
	CopyMemory(m_term.message,"TERM           ",16);

	m_charaVoiceFlag.size = sizeof(m_charaVoiceFlag);
	m_charaVoiceFlag.code = 16;
	CopyMemory(m_charaVoiceFlag.message,"CHARAVOICEFLAG ",16);

	m_systemFlag2.size = sizeof(m_systemFlag2);
	m_systemFlag2.code = 17;
	CopyMemory(m_systemFlag2.message, "SYSTEMFLAG2    ", 16);

	m_selectMessageFlag.size = sizeof(m_selectMessageFlag);
	m_selectMessageFlag.code = 18;
	CopyMemory(m_selectMessageFlag.message, "SELECTMESSAGE  ", 16);

}

BOOL CCommonSystemFile::Save(BOOL errorPrintFlag)
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	m_dataHeader.dataKosuu = 14;
#if defined __SYSTEMNNN_VER2__
	m_dataHeader.dataKosuu = 16;
#endif

	m_systemdata.year = st.wYear;
	m_systemdata.month = st.wMonth;
	m_systemdata.day = st.wDay;
	m_systemdata.week = st.wDayOfWeek;
	m_systemdata.hour = st.wHour;
	m_systemdata.minute = st.wMinute;
	m_systemdata.second = st.wSecond;
	m_systemdata.milli = st.wMilliseconds;

	m_systemdata.saveCount++;

	LPSTR saveFolder = CMySaveFolder::GetFullFolder();

	char filename[256];
	wsprintf(filename, "%s\\%s.sav", saveFolder, m_saveFileNameOnly);
	FILE* file = CMyFile::OpenFullPath(filename, "wb");

	if (file == NULL)
	{
		if (errorPrintFlag)
		{
			char ermes[1024];
			if (CCommonGameVersion::CheckTaikenOrNetVersion() == FALSE)
			{
				wsprintf(ermes, "ƒVƒXƒeƒ€ƒtƒ@ƒCƒ‹:%s\\sysfile.sav‚ªsave‚Å‚«‚Ü‚¹‚ñ‚Å‚µ‚½", saveFolder);
			}
			else
			{
				wsprintf(ermes, "ƒVƒXƒeƒ€ƒtƒ@ƒCƒ‹:%s\\tsysfile.sav‚ªsave‚Å‚«‚Ü‚¹‚ñ‚Å‚µ‚½", saveFolder);
			}

			MessageBox(NULL, ermes, "Error", MB_OK);
		}

		return FALSE;
	}

	fwrite(&m_dataHeader, sizeof(m_dataHeader), 1, file);
	fwrite(&m_systemdata, sizeof(m_systemdata), 1, file);

	fwrite(&m_messageFlag, sizeof(m_messageFlag), 1, file);

	int varType = GetVarType();
	if (varType == 0)
	{
		fwrite(&m_systemVar, sizeof(SYSTEMVAR1), 1, file);
	}
	else
	{
		fwrite(&m_systemVar, sizeof(SYSTEMVAR), 1, file);
	}
	fwrite(&m_cgFlag,sizeof(m_cgFlag),1,file);
	fwrite(&m_sceneFlag,sizeof(m_sceneFlag),1,file);
	fwrite(&m_filmFlag,sizeof(m_filmFlag),1,file);
	fwrite(&m_voiceFlag,sizeof(m_voiceFlag),1,file);
	fwrite(&m_movieFlag,sizeof(m_movieFlag),1,file);
	fwrite(&m_musicFlag,sizeof(m_musicFlag),1,file);
	fwrite(&m_okikae,sizeof(m_okikae),1,file);
	fwrite(&m_achievement,sizeof(m_achievement),1,file);
	fwrite(&m_term,sizeof(m_term),1,file);
	fwrite(&m_charaVoiceFlag,sizeof(m_charaVoiceFlag),1,file);
#if defined __SYSTEMNNN_VER2__
	fwrite(&m_systemFlag2, sizeof(m_systemFlag2), 1, file);
	fwrite(&m_selectMessageFlag, sizeof(m_selectMessageFlag), 1, file);
#endif
	fclose(file);

	return TRUE;
}


BOOL CCommonSystemFile::GetWindowZahyo(POINT* lpPoint)
{
	lpPoint->x = m_systemdata.windowX;
	lpPoint->y = m_systemdata.windowY;

	return TRUE;
}






void CCommonSystemFile::SetCG(int playerNumber, int cgNumber)
{
	if ((playerNumber<0) || (playerNumber>=m_maxCGCharaNumber)) return;
	if ((cgNumber<0) || (cgNumber>=m_maxCGNumber)) return;

	int k = playerNumber * m_maxCGNumber + cgNumber;
	int bt = m_bitTable[k & 0x1f];

	m_cgFlag.data[k>>5] |= bt;
}


BOOL CCommonSystemFile::CheckCG(int playerNumber,int cgNumber)
{
	if ((playerNumber<0) || (playerNumber>=m_maxCGCharaNumber)) return FALSE;
	if ((cgNumber<0) || (cgNumber>=m_maxCGNumber)) return FALSE;

	int k = playerNumber * m_maxCGNumber + cgNumber;
	int bt = m_bitTable[k & 0x1f];

	if (m_cgFlag.data[k>>5] & bt) return TRUE;

	return FALSE;
}



void CCommonSystemFile::SetMessageRead(int sptNum, int mesNum)
{
	if ((sptNum<0) || (sptNum>=m_maxScriptNumber)) return;
	if ((mesNum<0) || (mesNum>=m_maxMessageNumber)) return;

	int k = sptNum * m_maxMessageNumber + mesNum;
	int bt = m_bitTable[k & 0x1f];

	m_messageFlag.flag[k>>5] |=  bt;
}

BOOL CCommonSystemFile::CheckMessageRead(int sptNum, int mesNum)
{
	if ((sptNum<0) || (sptNum>=m_maxScriptNumber)) return FALSE;
	if ((mesNum<0) || (mesNum>=m_maxMessageNumber)) return FALSE;

	int k = sptNum * m_maxMessageNumber + mesNum;
	int bt = m_bitTable[k & 0x1f];

	if (m_messageFlag.flag[k>>5] & bt) return TRUE;

	return FALSE;
}



void CCommonSystemFile::SetFilm(int sptNum, int filmNum)
{
	if ((sptNum<0) || (sptNum>=m_maxScriptNumber)) return;
	if ((filmNum<0) || (filmNum>=m_maxFilmNumber)) return;

	int k = sptNum * m_maxFilmNumber + filmNum;
	int bt = m_bitTable[k & 0x1f];

	m_filmFlag.flag[k>>5] |=  bt;
}


BOOL CCommonSystemFile::CheckFilm(int sptNum, int filmNum)
{
	if ((sptNum<0) || (sptNum>=m_maxScriptNumber)) return FALSE;
	if ((filmNum<0) || (filmNum>=m_maxFilmNumber)) return FALSE;

	int k = sptNum * m_maxFilmNumber + filmNum;
	int bt = m_bitTable[k & 0x1f];

	if (m_filmFlag.flag[k>>5] & bt) return TRUE;

	return FALSE;
}




void CCommonSystemFile::CalcuInitParameter(void)
{
	m_maxScriptNumber = m_maxScriptNumberForInit;

	//spt		:spt	film	mes
	//2:		:2		65536	65536*2
	//3`4		:4		32768	65536
	//5`8		:8		16384	32768
	//9`16		:16		8192	16384
	//17`32	:32		4096	8192
	//33`64	:64		2048	4096
	//65`128	:128	1024	2048
	//129`256	:256	512		1024

	int sptMax = m_maxScriptNumber;
	
	if (sptMax >= 129) sptMax = 256;
	else if (sptMax >= 65) sptMax = 128;
	else if (sptMax >= 33) sptMax = 64;
	else if (sptMax >= 17) sptMax = 32;
	else if (sptMax >= 9) sptMax = 16;
	else if (sptMax >= 5) sptMax = 8;
	else if (sptMax >= 3) sptMax = 4;

	m_maxFilmNumber = 65536*2 / sptMax;
	m_maxMessageNumber = 65536*4 / sptMax;

	m_maxCGCharaNumber = m_maxCGCharaNumberForInit;
	int charaMax = m_maxCGCharaNumber;

	//player	:pl		cg
	//1			:1		4*2048cg
	//2			:2		4*1024cg
	//3`5		:5		4*512cg
	//6`10		:10		4*256cg
	//11`20	:20		4*128cg
	//21`40	:40		4*64cg
	//41`80	:80		4*32cg
	//81`160	:160	4*16cg
	//161`255	:320	4*8cg

	if (charaMax >= 161) charaMax = 320;
	else if (charaMax >= 81) charaMax = 160;
	else if (charaMax >= 41) charaMax = 80;
	else if (charaMax >= 21) charaMax = 40;
	else if (charaMax >= 11) charaMax = 20;
	else if (charaMax >= 6) charaMax = 10;
	else if (charaMax >= 3) charaMax = 5;

	if (charaMax >= 5)
	{
		m_maxCGNumber = 2560*4 / charaMax;
	}
	else
	{
		if (charaMax == 2) m_maxCGNumber = 1024*4;
		if (charaMax == 1) m_maxCGNumber = 2048*4;
	}




	m_maxMovieCharaNumber = m_maxMovieCharaNumberForInit;
	m_maxMovieNumber = 256/m_maxMovieCharaNumber;
	m_maxMovieNumber *= 32;
}


//static


void CCommonSystemFile::SetMaxScriptNumber(int n)
{
	if (n<2) n = 2;
	if (n>256) n = 256;

	m_maxScriptNumberForInit = n;
}

void CCommonSystemFile::SetMaxCGCharaNumber(int n)
{
	if (n<1) n = 1;
	if (n>256) n = 256;

	m_maxCGCharaNumberForInit = n;
	SetMaxMovieCharaNumber(n);
}

void CCommonSystemFile::SetMaxMovieCharaNumber(int n)
{
	if (n<1) n = 1;
	if (n>256) n = 256;

	m_maxMovieCharaNumberForInit = n;
}


void CCommonSystemFile::SetDefaultSei(LPSTR sei)
{
	if (sei == NULL) return;
	int ln = (int)strlen(sei);
	if (ln >= 16) return;
	memcpy(m_defaultSei,sei,ln+1);
}

void CCommonSystemFile::SetDefaultMei(LPSTR mei)
{
	if (mei == NULL) return;
	int ln = (int)strlen(mei);
	if (ln >= 16) return;
	memcpy(m_defaultMei,mei,ln+1);
}

void CCommonSystemFile::SetMovie(int movieCharaNumber,int movieNumber)
{
	if ((movieCharaNumber<0) || (movieCharaNumber>=m_maxMovieCharaNumber)) return;
	if ((movieNumber<0) || (movieNumber>=m_maxMovieNumber)) return;

	int k = movieCharaNumber * m_maxMovieNumber + movieNumber;
	int bt = m_bitTable[k & 0x1f];

	m_movieFlag.flag[k>>5] |= bt;
}

BOOL CCommonSystemFile::CheckMovie(int movieCharaNumber,int movieNumber)
{
	if ((movieCharaNumber<0) || (movieCharaNumber>=m_maxMovieCharaNumber)) return FALSE;
	if ((movieNumber<0) || (movieNumber>=m_maxMovieNumber)) return FALSE;

	int k = movieCharaNumber * m_maxMovieNumber + movieNumber;
	int bt = m_bitTable[k & 0x1f];

	if (m_movieFlag.flag[k>>5] & bt) return TRUE;
	return FALSE;
}

void CCommonSystemFile::SetVoice(int voicePlayerNumber)
{
	if ((voicePlayerNumber<0) || (voicePlayerNumber>=256)) return;

	m_voiceFlag.flag[voicePlayerNumber] |= 1;
}

BOOL CCommonSystemFile::CheckVoice(int voicePlayerNumber)
{
	if ((voicePlayerNumber<0) || (voicePlayerNumber>=256)) return FALSE;

	if (m_voiceFlag.flag[voicePlayerNumber]) return TRUE;

	return FALSE;
}

void CCommonSystemFile::SetMusic(int musicNumber)
{
	if ((musicNumber < 0) || (musicNumber > 255)) return;
	if (m_musicFlag.flag[musicNumber] < 9999) m_musicFlag.flag[musicNumber]++;
}


BOOL CCommonSystemFile::CheckMusic(int musicNumber)
{
	if ((musicNumber < 0) || (musicNumber > 255)) return FALSE;
	if (m_musicFlag.flag[musicNumber] > 0) return TRUE;

	return FALSE;
}

void CCommonSystemFile::SetCharaVoiceVolumeSlider(int chara,int deltaVolumeSlider)
{
	if ((chara < 0) || (chara >= 12*6)) return;
	int n = chara / 6;
	int shift = chara % 6;

	int mask = 0x1f << (shift*5);
	int d = m_systemdata.charaVoiceVolumeSlider[n];

	d &= ~mask;
	d |= ((deltaVolumeSlider << (shift*5)) & mask);

	m_systemdata.charaVoiceVolumeSlider[n] = d;
}

int CCommonSystemFile::GetCharaVoiceVolumeSlider(int chara)
{
	if ((chara < 0) || (chara >= 12*6)) return 0;

	int n = chara / 6;
	int shift = chara % 6;

	int d = m_systemdata.charaVoiceVolumeSlider[n];
	d >>= (shift*5);
	d &= 0x1f;
	if (d & 0x10)
	{
		d |= (~(0x1f));
	}

	return d;
}

char* CCommonSystemFile::GetOkikae(int n)
{
	if ((n>=0) && (n<OKIKAE_SYSTEM_MAX))
	{
		return &(m_okikae.okikae[64*n]);
	}

	return NULL;
}

void CCommonSystemFile::SetOkikae(int n,char* mes)
{
	if (mes == NULL) return;

	if ((n>=0) && (n<OKIKAE_SYSTEM_MAX))
	{
		char* ptr = &(m_okikae.okikae[64*n]);
		int ln = (int)strlen(mes);
		if (ln>32) ln = 32;
		memcpy(ptr,mes,ln);
		*(ptr+ln) = 0;
		*(ptr+ln+1) = 0;
	}
}


void CCommonSystemFile::SetAchievement(int n,int ps)
{
	if ((n>=0) && (n<1024))
	{
		m_achievement.achievement[n] = ps;
	}
}

int CCommonSystemFile::GetAchievement(int n)
{
	if ((n >= 0) && (n < 1024))
	{
		return m_achievement.achievement[n];
	}
	return 0;
}

void CCommonSystemFile::SetTerm(int n, BOOL flag)
{
	if ((n >= 0) && (n < 1024))
	{
		int d = m_term.term[n];
		if (flag)
		{
			d |= 1;
		}
		else
		{
			d &= ~1;
		}
		m_term.term[n] = d;
	}
}

BOOL CCommonSystemFile::GetTerm(int n)
{
	if ((n >= 0) && (n < 1024))
	{
		if (m_term.term[n] & 1) return TRUE;
	}
	return FALSE;
}

void CCommonSystemFile::SetTermLook(int n, BOOL flag)
{
	if ((n >= 0) && (n < 1024))
	{
		int d = m_term.term[n];
		if (flag)
		{
			d |= 2;
		}
		else
		{
			d &= ~2;
		}
		m_term.term[n] = d;
	}
}

BOOL CCommonSystemFile::GetTermLook(int n)
{
	if ((n >= 0) && (n < 1024))
	{
		if (m_term.term[n] & 2) return TRUE;
	}
	return FALSE;
}

void CCommonSystemFile::SetCharaVoiceFlag(int flagNumber, BOOL flag)
{
	if ((flagNumber >= 0) && (flagNumber < 65536 * 8))
	{
		int n = flagNumber / 32;
		int bit = m_bitTable[flagNumber & 31];
		if (flag)
		{
			m_charaVoiceFlag.flag[n] |= bit;
		}
		else
		{
			m_charaVoiceFlag.flag[n] &= ~bit;
		}
	}
}

BOOL CCommonSystemFile::CheckCharaVoiceFlag(int flagNumber)
{
	if ((flagNumber >= 0) && (flagNumber < 65536 * 8))
	{
		int n = flagNumber / 32;
		int bit = m_bitTable[flagNumber & 31];
		if (m_charaVoiceFlag.flag[n] & bit)
		{
			return TRUE;
		}
	}

	return FALSE;
}


void CCommonSystemFile::SetSelectMessageFlag(int select, int n, bool flag)
{
	if ((select >= 0) && (select < 1024))
	{
		int bit = m_bitTable[n & 31];
		if (flag)
		{
			m_selectMessageFlag.flag[select] |= bit;
		}
		else
		{
			m_selectMessageFlag.flag[select] &= ~bit;

		}

	}
}
bool CCommonSystemFile::CheckSelectMessageFlag(int select, int n)
{
	if ((select >= 0) && (select < 1024))
	{
		int bit = m_bitTable[n & 31];
		return (m_selectMessageFlag.flag[select] & bit) != 0;
	}

	return false;
}


void CCommonSystemFile::ClearAllCGFlag(void)
{
	LPVOID ptr = &(m_cgFlag.data);
	int sz = sizeof(m_cgFlag.data);
	ZeroMemory(ptr,sz);
}

void CCommonSystemFile::ClearAllSceneFlag(void)
{
	LPVOID ptr = &(m_sceneFlag.data);
	int sz = sizeof(m_sceneFlag.data);
	ZeroMemory(ptr,sz);
}

void CCommonSystemFile::ClearAllFilmFlag(void)
{
	LPVOID ptr = &(m_filmFlag.flag);
	int sz = sizeof(m_filmFlag.flag);
	ZeroMemory(ptr,sz);
}

void CCommonSystemFile::ClearAllMessageFlag(void)
{
	LPVOID ptr = &(m_messageFlag.flag);
	int sz = sizeof(m_messageFlag.flag);
	ZeroMemory(ptr,sz);
}

void CCommonSystemFile::ClearAllVoiceFlag(void)
{
	LPVOID ptr = &(m_voiceFlag.flag);
	int sz = sizeof(m_voiceFlag.flag);
	ZeroMemory(ptr,sz);
}

void CCommonSystemFile::ClearAllMovieFlag(void)
{
	LPVOID ptr = &(m_movieFlag.flag);
	int sz = sizeof(m_movieFlag.flag);
	ZeroMemory(ptr,sz);
}

void CCommonSystemFile::ClearAllMusicFlag(void)
{
	LPVOID ptr = &(m_musicFlag.flag);
	int sz = sizeof(m_musicFlag.flag);
	ZeroMemory(ptr,sz);
}

void CCommonSystemFile::ClearAllOkikae(void)
{
	LPVOID ptr = &(m_okikae.okikae);
	int sz = sizeof(m_okikae.okikae);
	ZeroMemory(ptr,sz);
}

void CCommonSystemFile::ClearAllAchievement(void)
{
	LPVOID ptr = &(m_achievement.achievement);
	int sz = sizeof(m_achievement.achievement);
	ZeroMemory(ptr,sz);
}

void CCommonSystemFile::ClearAllTerm(void)
{
	LPVOID ptr = &(m_term.term);
	int sz = sizeof(m_term.term);
	ZeroMemory(ptr,sz);
}

void CCommonSystemFile::ClearAllCharaVoiceFlag(void)
{
	LPVOID ptr = &(m_charaVoiceFlag.flag);
	int sz = sizeof(m_charaVoiceFlag.flag);
	ZeroMemory(ptr,sz);
}

void CCommonSystemFile::ClearAllSystemFlag2(void)
{
	LPVOID ptr = &(m_systemFlag2.lastSaveFileNumber);
	int sz = sizeof(m_systemFlag2.lastSaveFileNumber);
	ZeroMemory(ptr, sz);
	ptr = &(m_systemFlag2.pad[0]);
	sz = sizeof(m_systemFlag2.pad);
	ZeroMemory(ptr, sz);
}

void CCommonSystemFile::ClearAllSelectMessageFlag(void)
{
	LPVOID ptr = &(m_selectMessageFlag.flag);
	int sz = sizeof(m_selectMessageFlag.flag);
	ZeroMemory(ptr, sz);


}

void CCommonSystemFile::SetCGCharaNinzu(int n)
{
	m_CGCharaNumber = n;
}

int CCommonSystemFile::GetCGCharaNinzu(void)
{
	return m_CGCharaNumber;
}


void CCommonSystemFile::SetGoreFlag(int goreFlag)
{
	m_systemFlag2.goreFlag = goreFlag;
}
int CCommonSystemFile::GetGoreFlag(void)
{
	return m_systemFlag2.goreFlag;
}

BOOL CCommonSystemFile::CreateGUID(BOOL existCheck)
{
	if (existCheck)
	{
		for (int i=0;i<16;i++)
		{
			if (m_systemdata.guid[i] != 0)
			{
				return FALSE;
			}
		}
	}

#if _MSC_VER >= 1500

	UUID uuid;


	if (UuidCreateSequential(&uuid) == RPC_S_OK)
	{
		memcpy(&m_systemdata.guid[0],&uuid.Data1,4);
		memcpy(&m_systemdata.guid[4],&uuid.Data2,2);
		memcpy(&m_systemdata.guid[6],&uuid.Data3,2);
		memcpy(&m_systemdata.guid[8],uuid.Data4,8);
		return TRUE;
	}

	if (UuidCreate(&uuid) == RPC_S_OK)
	{
		memcpy(&m_systemdata.guid[0],&uuid.Data1,4);
		memcpy(&m_systemdata.guid[4],&uuid.Data2,2);
		memcpy(&m_systemdata.guid[6],&uuid.Data3,2);
		memcpy(&m_systemdata.guid[8],uuid.Data4,8);
		return TRUE;
	}

#endif


	//time only
	SYSTEMTIME systemtime;
	GetLocalTime(&systemtime);
	memcpy(&m_systemdata.guid[0],&systemtime.wYear,2);
	memcpy(&m_systemdata.guid[2],&systemtime.wMonth,2);
	memcpy(&m_systemdata.guid[4],&systemtime.wDay,2);
	memcpy(&m_systemdata.guid[6],&systemtime.wHour,2);
	memcpy(&m_systemdata.guid[8],&systemtime.wMinute,2);
	memcpy(&m_systemdata.guid[10],&systemtime.wSecond,2);
	memcpy(&m_systemdata.guid[12],&systemtime.wMilliseconds,2);
	memcpy(&m_systemdata.guid[14],&systemtime.wDayOfWeek,2);

	return TRUE;
}

int CCommonSystemFile::GetVarType(void)
{
	return 1;
}


/*_*/




