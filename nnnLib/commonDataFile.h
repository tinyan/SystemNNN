//
// datafile.h
//

#if !defined __TINYAN_NNNUTILLIB_COMMONDATAFILE__
#define __TINYAN_NNNUTILLIB_COMMONDATAFILE__

#define GAMEDATATYPE_HEADER (0)
#define GAMEDATATYPE_INFO (1)
#define GAMEDATATYPE_STATUS (2)
#define GAMEDATATYPE_MINICG (3)
#define GAMEDATATYPE_VAR (4)
#define GAMEDATATYPE_EFFECT (5)
#define GAMEDATATYPE_EFFECTFILENAME (6)
#define GAMEDATATYPE_MESSAGE (7)

#define GAMEDATATYPE_OMAKECLASS (8)

#define GAMEDATATYPE_CUTIN (9)
#define GAMEDATATYPE_LOG (10)


#define GAMEDATATYPE_EXT (100)


#include "..\..\systemNNN\nyanEffectLib\allEffect.h"
#include "commonBackLog.h"

//#include "datatype.h"
//#include "..\nyanEffectLib\effectstruct.h"
//#include <stdio.h>

class CPicture;
class CMyFont;
class CMyMessage;
//class CGameDatePic;
class CSuuji;
class CGameCallBack;

class CPrintGameDate;

class CDataFileSetup;

class CCommonAnimeParts;

class CCommonGeneral;


class CCommonDataFile
{
public:
	CCommonDataFile(CGameCallBack* lpGame, int printX, int printY,CPicture* lpBG);

	virtual ~CCommonDataFile();
	virtual void End(void);

	BOOL LoadHeaderAndPic(int n);

	BOOL CheckDataExist(void);
	int GetVersionDeltaMode(void);
	BOOL CheckLoadOkVersion(void);
	BOOL CheckOn(int mouseX, int mouseY);

	void InitAnime(void);

	int Load(int n);
	int Save(int n);


	void Print(int md = 0,int clicking = 0,int nm = -1,int loadsave = 0,int lastCount = 0);
	void AppearPrint(int appearCount,int appearCountMax,int appearType, int md = 0, int clicking = 0, int nm = -1, int loadsave = 0, int lastCount = 0);


	void SetLoadSave(BOOL loadsave){m_loadSave = loadsave;}

	void ChangeExtDataSize(int extNumber,int dataSize);

	int GetSaveMode(void);

	LPSTR GetMiniMessage(int n);
	LPSTR GetLargeMessage(int n);

//	typedef struct _tagGAMEDATATYPETABLE
//	{
//		int dataType;
//		int dataSize;
//		char mes[16];
//	} GAMEDATATYPETABLE;



	typedef struct _tagGAMEGENERALDATA
	{
		int size;
		int code;
		int dummy1;
		int dummy2;
		char message[16];
	} GAMEGENERALDATA;



	typedef struct _tagGAMEHEADER
	{
		GAMEGENERALDATA general;
	} GAMEHEADER;

	typedef struct tagGAMEINFO
	{
		GAMEGENERALDATA general;
		int dataKosuu;
		int version;
		int extDataKosuu;
		int omakeClass;
		int cutin;
		int log;
		int pad[16-14];
	} GAMEINFO;


	typedef struct tagGAMESTATUS
	{
		GAMEGENERALDATA general;
		
		int year,month,day,week;
		int hour,minute,second,milli;

		int gameMonth,gameDay,gameHour,gameWeek;
		int gameMode;
		int saveCount;
		int scriptAdjustVersion;
		int pad0;


		int scriptRunMode;
		int controlScriptNumber;	//dummy
		int scriptNumber;
		int scriptSubNumber;


		int lastMessageID;	//追加
		int messageKosuu;
		int messageSubMode;
		int scriptSubSubNumber;	//追加2008-05-01

		int lastSelectID;
		int selectMessageKosuu;
		int selectMessageAddKosuu;
		int selectSerialID;//追加2020-05-23


		int bgmNumber;
		int bgmKaisuu;
		int bgmVolume;
		int voiceExistCount;
		int bgmParam[4];

		int messageWindowPrintFlag;
		int frame;
		int nokori;
		int lastselectheroinnumber;
		int layerOff;
		int messageFontSizeType;
		int renameLayer;
		int messageSerial;

		int loopSound[8*16];

		int scriptWindowNumber;
		int scriptCursorNumber;
		int scriptMouseNumber;
		int pad6;

		int loopVoice[8*16];

		char loopVoiceFileName[8*64];

		char minicomment[32];

		char playerSei[16];
		char playerMei[16];

		char sptFilename[32-16];	//未使用
		char guid[16];
//		char bgmFilename[32];	//未使用
		short varcontrollayer[16];//16layer:short 32layer:(highByte = layer+16,lowByte=layer)

		int m_PC;
		int m_PC2;
		int m_PC3;
		int m_PC4;

		int configMask;
		int skipFilm;
		int pad8,pad9;

		int selectTimeLimit;
		int autoSelect;
		int selectTimeCount;
		int specialFlag;

		int autoMessage;
		int cannotClick;
		int cannotSkip;
		int pad11;

		int stackPointer;
		int callStack[255];

		int stackPointer2;
		int callStack2[255];

		int stackPointer3;
		int callStack3[255];

		int stackPointer4;
		int callStack4[255];

		int largeCommentFlag;
		int pad20,pad21,pad22;
		char largeComment1[256];
		char largeComment2[256];
		char largeComment3[256];
		char largeComment4[256];
	} GAMESTATUS;



	typedef struct tagGAMEMINICG
	{
		GAMEGENERALDATA general;
		int sizeX;
		int sizeY;
		int pad[2];
		int cg[1];		//@@@@@@@@@@@@@@@@あとでカスタム可能にする
	} GAMEMINICG;


	typedef struct _tagGAMEVAR
	{
		GAMEGENERALDATA general;
//		int var[1024];
		int var[2224];
	} GAMEVAR;

	typedef struct _tagGAMEVAR1
	{
		GAMEGENERALDATA general;
		int var[1024];
	} GAMEVAR1;


	typedef struct _tagGAMEEFFECT
	{
		GAMEGENERALDATA general;
		EFFECT effect[LAYER_KOSUU_MAX];
	} GAMEEFFECT;


	typedef struct _tagGAMEEFFECTFILENAME
	{
		GAMEGENERALDATA general;
		char filename[PICTURE_KOSUU_MAX][256];
	} GAMEEFFECTFILENAME;


	typedef struct _tagGAMEMESSAGE
	{
		GAMEGENERALDATA general;
		char messageData[64][256];
	} GAMEMESSAGE;


	typedef struct _tagGAMEEXTDATA
	{
		GAMEGENERALDATA general;
		char dat[1];
	} GAMEEXTDATA;


	typedef struct _tagGAMECUTIN
	{
		GAMEGENERALDATA general;
		int cutinData[64*4];	//64*2でいいけど用心のため少しおおめに
	} GAMECUTIN;


	typedef struct _tagGAMEOMAKECLASSDATA
	{
		GAMEGENERALDATA general;
		int omake[3200];
	} GAMEOMAKECLASSDATA;


	typedef struct _tagGAMELOG
	{
		GAMEGENERALDATA general;
		int nowPointer;
		int messageKosuu;
		int pad[6];
		
		int logColor[BACKLOG_KOSUU];
		char logMessage[BACKLOG_KOSUU * BACKLOG_LENGTH];
		char voiceFile[BACKLOG_KOSUU * VOICEFILE_LENGTH];

	} GAMELOG;


protected:

	CGameCallBack* m_game;

	CPicture* m_pic;
	CPicture* m_commonBG;
	CMyFont* m_commonFont;

	CPicture* m_saveDatePic;
	CPicture* m_gameDatePic;

	CMyFont* m_font;
	CMyMessage* m_message;

	CPicture* m_errorVersionPic;
	CPicture* m_badVersionPic;
	CPicture* m_oldVersionPic;
	CPicture* m_selectPic;

	CSuuji* m_saveTimeSuuji2;
	CSuuji* m_saveTimeSuuji4;
	CSuuji* m_gameTimeSuuji2;
	CSuuji* m_gameTimeSuuji3;
	CSuuji* m_gameTimeSuuji4;
	CSuuji* m_gameWeekSuuji;

	CSuuji* m_specialNumberSuuji;

	int m_specialNumberPrintLimit;
	
	int m_gameYearVarNumber;
	int m_gameDateVarNumber;

	int m_addPicWithSpecialFlag;

	int m_addPicMultiFlag;
	int m_addPicMultiKosuuX;

	GAMESTATUS m_gameStatus;
	GAMEINFO m_gameInfo;
	GAMEVAR* m_lpGameVar;


	BOOL SaveHeader(void);
	BOOL SaveInfo(void);
	BOOL SaveStatus(void);
	BOOL SaveVar(void);
	BOOL SaveKumiawaseVar(void);
	BOOL SaveMiniCG(void);
	BOOL SaveMessage(void);
	BOOL SaveEffect(void);
	BOOL SaveEffectFileName(void);
	BOOL SaveExtData(int n);
	BOOL SaveOmakeClassData(void);
	BOOL SaveCutin(void);
	BOOL SaveLog(void);

	BOOL LoadHeader(void);
	BOOL LoadInfo(void);
	BOOL LoadStatus(void);
	BOOL LoadVar(void);
	BOOL LoadMiniCG(void);
	BOOL LoadMessage(void);
	BOOL LoadEffect(void);
	BOOL LoadEffectFileName(void);
	BOOL LoadExtData(int n);
	BOOL LoadOmakeClassData(void);
	BOOL LoadCutin(void);
	BOOL LoadLog(void);


	BOOL Load1Block(void);

	void MakeCG(int n);


	int GetMessage(void);


	void MakeHeader(int* work, int sz, int cd ,LPSTR mes);


	int* m_commonBuffer;
	int* m_commonBuffer2;



	int m_printX;
	int m_printY;
	int m_sizeX;
	int m_sizeY;

	int m_picPrintX;
	int m_picPrintY;

	int m_picSizeX;
	int m_picSizeY;


	int m_saveTimePrintFlag;

	int m_saveTimePrintX;
	int m_saveTimePrintY;

	int m_saveTimeSizeX;
	int m_saveTimeSizeY;
	int m_saveTimeNextX;



	int m_gameTimePrintFlag;
	int m_gameYearPrintFlag;
	int m_gameDatePrintFlag;
	int m_gameTimePrintX;
	int m_gameTimePrintY;
	int m_gameTimeSizeX;
	int m_gameTimeSizeY;
	int m_gameTimeNextX;

	int m_gameMonthPrintX;
	int m_gameMonthPrintY;
	int m_gameDayPrintX;
	int m_gameDayPrintY;
	int m_gameWeekPrintX;
	int m_gameWeekPrintY;
	int m_gameWeekPrintFlag;
	int m_gameWeekYouPrintFlag;
	int m_gameWeekBiPrintFlag;
	int m_gameMonthUpzeroPrintFlag;
	int m_gameDayUpzeroPrintFlag;
	int m_gameDateSlashPrintFlag;
	int m_gameWeekSizeX;
	int m_gameWeekSizeY;




	int m_selectColorR;
	int m_selectColorG;
	int m_selectColorB;
	int m_selectColorPercent;

	int m_selectPrintMode;

	int m_errorPrintX;
	int m_errorPrintY;
	int m_badPrintX;
	int m_badPrintY;
	int m_oldPrintX;
	int m_oldPrintY;

	int m_numPrintFlag;
	int m_numPrintX;
	int m_numPrintY;
	CSuuji* m_numSuuji;

	int m_specialNumberPrintFlag;
	POINT m_specialNumberPrintZahyo;

	int m_commentPrintFlag;
	POINT m_commentPrintZahyo;
	int m_commentFontSize;
	int m_commentSukima;
	int m_commentColorR;
	int m_commentColorG;
	int m_commentColorB;
	int m_commentColorShade;



	int m_textPrintFlag;
	POINT m_textPrintZahyo;
	int m_textFontSize;
	int m_textSukima;
	int m_textColorR;
	int m_textColorG;
	int m_textColorB;
	int m_textColorShade;
	int m_textNextY;
	int m_textPrintGyo;


	int m_kazariPrintFlag;
	SIZE m_kazariSize;
	POINT m_kazariZahyo;
	CPicture* m_kazariPic;

	POINT m_addPicPrintZahyo;
	SIZE m_addPicSize;
	int m_addPicPrintFlag;
	CPicture* m_addPic;
	BOOL m_dataExistFlag;

	int m_serialNumberPrintFlag;
	CSuuji* m_serialSuuji;
	POINT m_serialNumberPrintZahyo;

//	void PrintSuuji(int x, int y, int d, int keta = 2);
//	void PrintSuuji0(int x, int y, int d, int keta = 2);

	char m_sei[16];
	char m_mei[16];

	FILE* m_file;

	int m_extDataBlockKosuu;

	int* m_pExtBlockSize;
//	char** m_ppExtBlockData;

	int m_systemGameVersion;

	CDataFileSetup* m_dataFileSetup;

	int m_omakeClassExistFlag;
	int m_cutinUseFlag;
	int m_logFlag;

	int m_basePrintFlag;
	CPicture* m_loadBasePic;
	CPicture* m_saveBasePic;

	CPicture* m_quickLoadBasePic;
	CPicture* m_quickSaveBasePic;

	int m_quickLoadEnable;
	int m_quickSaveEnable;


	BOOL m_loadSave;

	int m_selectPrintX;
	int m_selectPrintY;
	int m_selectSizeX;
	int m_selectSizeY;

	int m_picPrintType;
	CPicture* m_bg;

	int m_animePattern[6];
	int m_animeSpeed[6];
	int m_animeType[6];
	int m_animeCount[6];

	CPicture* m_cursorPic[6];	//3??

	int m_cursorPercent;
	int m_cursor1;
	int m_cursor2;

	void GetNowCursorPic(int n);
	void CalcuCursorAnime(int n);

//	int m_largeCommentFlag;

	int m_number;
	int m_quickSlotNumber;

	CPrintGameDate* m_printGameDate;

	CCommonAnimeParts* m_printLastSelect;



};


#endif
/*_*/

