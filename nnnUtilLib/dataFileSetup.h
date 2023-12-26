//
// dataFileSetup
//

#if !defined __TINYANGAMELIB_DATAFILESETUP__
#define __TINYANGAMELIB_DATAFILESETUP__

class CSetupList;
class CSuuji;
class CPicture;
class CPrintGameDate;
class CCommonAnimeParts;

class CDataFileSetup
{
public:
	CDataFileSetup();
	~CDataFileSetup();
	void End(void);

	int GetSaveSelectPrintMode(void) {return m_saveSelectPrintMode;}
	int GetSelectColorParam(int n) {return m_saveSelectColor[n];}
	CPicture* GetSaveSelectPic(void) {return m_saveSelectPic;}

	SIZE GetSaveAreaSize(void) {return m_saveAreaSize;}
	SIZE GetSavePicSize(void) {return m_savePicSize;}
	POINT GetSavePicZahyo(void) {return m_savePicZahyo;}

	POINT GetSaveErrorZahyo(void) {return m_saveErrorZahyo;}
	POINT GetSaveOldZahyo(void) {return m_saveOldZahyo;}
	POINT GetSaveBadZahyo(void) {return m_saveBadZahyo;}

	CPicture* GetSaveErrorPic(void) {return m_errorVersionPic;}
	CPicture* GetSaveOldPic(void) {return m_oldVersionPic;}
	CPicture* GetSaveBadPic(void) {return m_badVersionPic;}

	int GetSaveTimePrintFlag(void){return m_saveTimePrintFlag;}
	POINT GetSaveTimeZahyo(void) {return m_saveTimeZahyo;}
	CSuuji* GetSaveTimeSuuji4(void) {return m_saveTimeSuuji4;}
	CSuuji* GetSaveTimeSuuji2(void) {return m_saveTimeSuuji2;}
	CPicture* GetSaveTimePic(void) {return m_saveTimePic;}
	SIZE GetSaveTimeSize(void) {return m_saveTimeSize;}
	int GetSaveTimeNextX(void) {return m_saveTimeNextX;}


//	int GetGameTimePrintFlag(void) {return m_gameTimePrintFlag;}
	int GetGameYearPrintFlag(void) {return m_gameYearPrintFlag;}
	int GetGameDatePrintFlag(void) {return m_gameDatePrintFlag;}
	int GetGameWeekPrintFlag(void) {return m_gameWeekPrintFlag;}
	int GetGameWeekYouPrintFlag(void) {return m_gameWeekYouPrintFlag;}
	int GetGameWeekBiPrintFlag(void) {return m_gameWeekBiPrintFlag;}
	POINT GetGameTimeZahyo(void) {return m_gameTimeZahyo;}
	POINT GetGameDayZahyo(void) {return m_gameDayZahyo;}
	POINT GetGameWeekZahyo(void) {return m_gameWeekZahyo;}
	CSuuji* GetGameYearSuuji(void) {return m_gameYearSuuji;}
	CSuuji* GetGameMonthSuuji(void) {return m_gameMonthSuuji;}
	CSuuji* GetGameDaySuuji(void) {return m_gameDaySuuji;}
	CSuuji* GetGameWeekSuuji(void) {return m_gameWeekSuuji;}
	CPicture* GetGameYearDatePic(void) {return m_gameYearDatePic;}
	int GetGameTimeNextX(void) {return m_gameTimeNextX;}
	SIZE GetGameTimeSize(void) {return m_gameTimeSize;}
	SIZE GetGameWeekSize(void) {return m_gameWeekSize;}
	int GetGameDateSlashPrintFlag(void){return m_gameDateSlashPrintFlag;}
	CPrintGameDate* GetPrintGameDate(void){return m_printGameDate;}

	int GetKazariPrintFlag(void){return m_kazariPrintFlag;}
	POINT GetKazariZahyo(void){return m_kazariZahyo;}
	SIZE GetKazariSize(void){return m_kazariSize;}
	CPicture* GetKazariPic(void){return m_kazariPic;}

	int GetAddPicFlag(void) {return m_addPicFlag;}
	POINT GetAddPicZahyo(void) {return m_addPicZahyo;}
	SIZE GetAddPicSize(void) {return m_addPicSize;}
	CPicture* GetAddPic(void) {return m_addPic;}
	int GetAddPicWithSpecialFlag(void) {return m_addPicWithSpecialFlag;}

	int GetSpecialNumberPrintFlag(void) {return m_specialNumberPrintFlag;}
	int GetSpecialNumberPrintLimit(void) {return m_specialNumberPrintLimit;}
	POINT GetSpecialNumberZahyo(void){return m_specialNumberZahyo;}
	CSuuji* GetSpecialNumberSuuji(void){return m_specialNumberSuuji;}

	static char m_defaultFontFileName[];

	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name);


	int GetCommentPrintFlag(void) {return m_commentPrintFlag;}
	POINT GetCommentZahyo(void) {return m_commentZahyo;}
	int GetCommentFontSize(void) {return m_commentFontSize;}
	int GetCommentSukima(void) {return m_commentSukima;}
	int GetCommentColor(int n) {return m_commentColor[n];}

	int GetTextPrintFlag(void) {return m_textPrintFlag;}
	POINT GetTextZahyo(void) {return m_textZahyo;}
	int GetTextFontSize(void) {return m_textFontSize;}
	int GetTextSukima(void) {return m_textSukima;}
	int GetTextColor(int n) {return m_textColor[n];}
	int GetTextNextY(void){return m_textNextY;}
	int GetTextPrintGyo(void){return m_textPrintGyo;}

	int GetBasePrintFlag(void){return m_basePrintFlag;}
	CPicture* GetLoadBase(void){return m_loadBasePic;}
	CPicture* GetSaveBase(void){return m_saveBasePic;}

	POINT GetSelectZahyo(void){return m_selectZahyo;}
	SIZE GetSelectSize(void){return m_selectSize;}

	int GetAddPicMultiFlag(void){return m_addPicMultiFlag;}
	int GetAddPicMultiKosuuX(void){return m_addPicMultiKosuuX;}

	int GetSaveAnimePattern(int n = 0){return m_saveAnimePattern[n];}
	int GetSaveAnimeSpeed(int n = 0){return m_saveAnimeSpeed[n];}
	int GetSaveAnimeType(int n = 0){return m_saveAnimeType[n];}
	int GetLoadAnimePattern(int n = 0){return m_loadAnimePattern[n];}
	int GetLoadAnimeSpeed(int n = 0){return m_loadAnimeSpeed[n];}
	int GetLoadAnimeType(int n = 0){return m_loadAnimeType[n];}
	int GetOverwriteAnimePattern(int n = 0){return m_overwriteAnimePattern[n];}
	int GetOverwriteAnimeSpeed(int n = 0){return m_overwriteAnimeSpeed[n];}
	int GetOverwriteAnimeType(int n = 0){return m_overwriteAnimeType[n];}

	CPicture* GetSaveCursorPic(void);
	CPicture* GetLoadCursorPic(void);
	CPicture* GetOverwriteCursorPic(void);

	int GetNumPrintFlag(void){return m_numPrintFlag;}
	POINT GetNumZahyo(void){return m_numZahyo;}
	CSuuji* GetNumSuuji(void){return m_numSuuji;}

//	int GetQuickLoadSelectOk(void){return m_quickLoadSelectOk;}
//	int GetQuickSaveSelectOk(void){return m_quickSaveSelectOk;}

	CPicture* GetQuickLoadBase(void){return m_quickLoadBasePic;}
	CPicture* GetQuickSaveBase(void){return m_quickSaveBasePic;}

	int GetQuickSlotNumber(void){return m_quickSlotNumber;}

	int GetSerialNumberPrintFlag(void){return m_serialNumberPrintFlag;}
	CSuuji* GetSerialNumberSuuji(void){return m_serialNumberSuuji;}
	POINT GetSerialNumberZahyo(void){return m_serialZahyo;}

	CCommonAnimeParts* GetPrintLastSelect(void){return m_printLastSelect;}
private:
	CSetupList* m_setup;

	SIZE m_saveAreaSize;
	SIZE m_savePicSize;
	POINT m_savePicZahyo;



	int m_saveTimePrintFlag;
	POINT m_saveTimeZahyo;
	SIZE m_saveTimeSize;
	CPicture* m_saveTimePic;
	CSuuji* m_saveTimeSuuji4;
	CSuuji* m_saveTimeSuuji2;
	int m_saveTimeNextX;


//	int m_saveGameTimePrintFlag;
	int m_gameYearPrintFlag;
	int m_gameDatePrintFlag;
	int m_gameWeekPrintFlag;
	int m_gameWeekYouPrintFlag;
	int m_gameWeekBiPrintFlag;

	POINT m_gameTimeZahyo;
	POINT m_gameMonthZahyo;
	POINT m_gameDayZahyo;
	POINT m_gameWeekZahyo;
	int m_gameDateSlashPrintFlag;

	SIZE m_gameTimeSize;
	SIZE m_gameWeekSize;

	int m_gameMonthUpzeroPrintFlag;
	int m_gameDayUpzeroPrintFlag;
	CPicture* m_gameYearPic;
	CPicture* m_gameYearDatePic;
	CPicture* m_gameWeekPic;
	CSuuji* m_gameYearSuuji;
	CSuuji* m_gameMonthSuuji;
	CSuuji* m_gameDaySuuji;
	CSuuji* m_gameWeekSuuji;
	int m_gameTimeNextX;

	int m_kazariPrintFlag;
	POINT m_kazariZahyo;
	SIZE m_kazariSize;
	CPicture* m_kazariPic;




	int m_addPicFlag;
	POINT m_addPicZahyo;
	SIZE m_addPicSize;
	CPicture* m_addPic;
	int m_addPicWithSpecialFlag;

	int m_specialNumberPrintFlag;
	POINT m_specialNumberZahyo;
	SIZE m_specialNumberSize;
	int m_specialNumberNextX;
	CPicture* m_specialNumberPic;
	CSuuji* m_specialNumberSuuji;


	POINT m_saveErrorZahyo;
	POINT m_saveOldZahyo;
	POINT m_saveBadZahyo;

	CPicture* m_errorVersionPic;
	CPicture* m_oldVersionPic;
	CPicture* m_badVersionPic;

	int m_saveSelectPrintMode;
	int m_saveSelectColor[4];
	CPicture* m_saveSelectPic;

	int m_specialNumberPrintLimit;

	int m_commentPrintFlag;
	POINT m_commentZahyo;
	int m_commentFontSize;
	int m_commentSukima;
	int m_commentColor[4];

	int m_textPrintFlag;
	POINT m_textZahyo;
	int m_textFontSize;
	int m_textSukima;
	int m_textColor[4];
	int m_textNextY;
	int m_textPrintGyo;

	int m_basePrintFlag;
	int m_baseChangeLoadSave;
	CPicture* m_loadBasePic;
	CPicture* m_saveBasePic;

	POINT m_selectZahyo;
	SIZE m_selectSize;

	int m_addPicMultiFlag;
	int m_addPicMultiKosuuX;

	int m_saveAnimePattern[2];
	int m_saveAnimeSpeed[2];
	int m_saveAnimeType[2];
	int m_loadAnimePattern[2];
	int m_loadAnimeSpeed[2];
	int m_loadAnimeType[2];
	int m_overwriteAnimePattern[2];
	int m_overwriteAnimeSpeed[2];
	int m_overwriteAnimeType[2];

	int m_savePicKosuu;
	int m_loadPicKosuu;
	int m_overwritePicKosuu;
	CPicture* m_savePic;
	CPicture* m_loadPic;
	CPicture* m_overwritePic;

	int m_numPrintFlag;
	POINT m_numZahyo;
	CPicture* m_numPic;
	CSuuji* m_numSuuji;


	CPicture* m_quickLoadBasePic;
	CPicture* m_quickSaveBasePic;

//	int m_quickLoadSelectOk;
//	int m_quickSaveSelectOk;

	BOOL m_quickLoadPicMake;
	BOOL m_quickSavePicMake;

	int m_quickSlotNumber;

	int m_serialNumberPrintFlag;
	CPicture* m_serialNumberPic;
	CSuuji* m_serialNumberSuuji;
	POINT m_serialZahyo;
	SIZE m_serialFontSize;
	int m_serialNextX;

	CPrintGameDate* m_printGameDate;

	CCommonAnimeParts* m_printLastSelect;

	int m_appearAdjust;

};









#endif
/*_*/

