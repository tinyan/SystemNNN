//
//
//

#if !defined __NNNUTILLIB_COMMONBUTTON__
#define __NNNUTILLIB_COMMONBUTTON__


class CInputStatus;
class CPicture;
class CTaihi;
class CNameList;
class CSuperButtonSetup;

class CCommonButton
{
public:
	CCommonButton(CNameList* lpSetup = NULL,LPSTR buttonName = NULL, CPicture* lpBG = NULL);
	virtual ~CCommonButton();
	virtual void End(void);

	void Init(void);
	int Calcu(CInputStatus* lpInput,int clickFlag = 0);
	void Print(int md = -1);

	void Put(POINT delta,int percent = 100);
	void StretchPut(int multiX,int multiY,POINT delta,int percent = 100);

	void SetPicture(CPicture* lpPic){m_pic = lpPic;}
	CPicture* GetPicture(void){return m_pic;}
	void SetBG(CPicture* lpPic){m_bg = lpPic;}
	CPicture* GetBG(void){return m_bg;}

	void SetTaihi(CTaihi* lpTaihi,int n){m_taihi = lpTaihi;m_taihiNumber = n;}

	void SetExist(BOOL flg = TRUE){m_existFlag = flg;}
	BOOL GetExist(void){return m_existFlag;}

	void SetEnable(BOOL flg = TRUE);
	BOOL GetEnable(void){return m_enableFlag;}
	void SetReturnCannotClick(BOOL flg = TRUE){m_returnCannotClick = flg;}

	void SetDisableMode(int md = 0){m_disableMode = md;}
	int GetDisableMode(void){return m_disableMode;}

	void SetZahyo(POINT pt){m_zahyo = pt;}
	POINT GetZahyo(void){return m_zahyo;}

	void SetPicTateYoko(int tateYoko = 0){m_tateYoko = tateYoko;}
	int GetPicTateYoko(void){return m_tateYoko;}

	void SetSize(SIZE sz);
	SIZE GetSize(void){return m_size;}


	void SetEntered(bool bEnter = true);

	void SetCancelButtonFlag(BOOL flg = TRUE){m_cancelButtonFlag = flg;}
	BOOL GetCancelButtonFlag(void){return m_cancelButtonFlag;}
	void SetUpButtonFlag(BOOL flg = TRUE,BOOL revFlag = FALSE){m_upButtonFlag = flg;m_updownRevFlag = revFlag;}
	BOOL GetUpButtonFlag(void){return m_upButtonFlag;}
	void SetDownButtonFlag(BOOL flg = TRUE,BOOL revFlag = FALSE){m_downButtonFlag = flg;m_updownRevFlag = revFlag;}
	BOOL GetDownButtonFlag(void){return m_downButtonFlag;}
	BOOL GetUpdownRev(void){return m_updownRevFlag;}

	void SetSrcPicZahyo(POINT pt,int md = 0){m_picSrcZahyo[md] = pt;}
	POINT GetSrcPicZahyo(int md = 0){return m_picSrcZahyo[md];}

	POINT GetPicZahyo(int md,int pattern);

	void SetAnimePattern(int n,int pattern){m_animePattern[n] = pattern;}
	void SetAnimeSpeed(int n,int speed){m_animeSpeed[n] = speed;}
	void SetAnimeType(int n,int type){m_animeType[n] = type;}
	
	int GetAnimePattern(int n){return m_animePattern[n];}
	int GetAnimeSpeed(int n){return m_animeSpeed[n];}
	int GetAnimeType(int n){return m_animeType[n];}


	void SetClickSound(int d){m_clickSound = d;}
	void SetCannotClickSound(int d){m_cannotClickSound = d;}
	void SetEnterSound(int d){m_enterSound = d;}
	void SetExitSound(int d){m_exitSound = d;}
	void SetEnterSoundWait(int wait){m_enterSoundWait = wait;}
	void SetExitSoundWait(int wait){m_exitSoundWait = wait;}
	void SetClickVoice(int d) { m_clickVoice = d; }
	void SetCannotClickVoice(int d) { m_cannotClickVoice = d; }
	void SetEnterVoice(int d) { m_enterVoice = d; }
	void SetExitVoice(int d) { m_exitVoice = d; }

	int GetClickSound(void){return m_clickSound;}
	int GetCannotClickSound(void){return m_cannotClickSound;}
	int GetEnterSound(void){return m_enterSound;}
	int GetExitSound(void){return m_exitSound;}
	int GetEnterSoundWait(void){return m_enterSoundWait;}
	int GetExitSoundWait(void){return m_exitSoundWait;}
	int GetClickVoice(void) { return m_clickVoice; }
	int GetCannotClickVoice(void) { return m_cannotClickVoice; }
	int GetEnterVoice(void) { return m_enterVoice; }
	int GetExitVoice(void) { return m_exitVoice; }

	void SetAccelKey(int key,int n = 0){m_accelKey[n] = key;}
	int GetAccelKey(int n = 0){return m_accelKey[n];}


	void SetButtonPrintMode(int md){m_buttonPrintMode = md;}
	int GetButtonPrintMode(void){return m_buttonPrintMode;}

	void SetClickTime(int tm){m_clickTime = tm;}
	int GetClickTime(void){return m_clickTime;}

	static int MakeButtonStatus(int status,int sound = -1,int voice=-1,int data=-1,int volumeType = -1);
	static int ChangeButtonData(int statusData,int data);

	static int GetButtonStatus(int statusData);
//	static int GetButtonMode(int statusData);
	static int GetButtonVoice(int statusData);
	static int GetButtonSound(int statusData);
	static int GetButtonData(int statusData);
	static int GetVolumeTypeData(int statusData);
	static BOOL CheckRequestSound(int statusData);
	static BOOL CheckExistData(int statusData);



	void SetCheckPicZahyo(POINT pt){m_checkPicZahyo = pt;}
	POINT GetCheckPicZahyo(void){return m_checkPicZahyo;}

	void SetCheckDelta(POINT pt){m_checkDelta = pt;}
	POINT GetCheckDelta(void){return m_checkDelta;}

	void SetCheckSize(SIZE sz){m_checkSize = sz;}
	SIZE GetCheckSize(void){return m_checkSize;}


	void Anime(int cnt = 1);
	//
	BOOL CheckClick(CInputStatus* lpInput,int clickFlag = 0);

	void StartClick(void);

	void SetButtonCode(int code = 0){m_buttonCode = code;}
	int GetButtonCode(void){return m_buttonCode;}

	void StartEnter(void);
	void StartExit(void);

	LPSTR GetFileName(void){return m_filename;}
	void SetFileName(LPSTR filename){m_filename = filename;}
	void ResetAnimeCount(void);

	void PutInFromRight(int ps);
	void PutInFromLeft(int ps);
	void PutInFromUp(int ps);
	void PutInFromDown(int ps);

	void PutInFromCenterUpDown(int ps);
	void PutInFromCenterLeftRight(int ps);

	void SetVolumeType(int volumeType){m_volumeType = volumeType;}
	int GetVolumeType(void){return m_volumeType;}

	BOOL CheckOnButtonPic(POINT pt);

	int GetButtonNowMode(void){return m_mode;}

	void SetNextIgnore(int cnt = 1);

	BOOL LoadFile(LPSTR dirName = "sys");

	void ClearAccelKey(void);

	void AppearPrint(int count, int countMax, int type = 1, POINT deltaPoint = POINT{ 0,0 },int buttonNumber = 0,int buttonmax = 1);
	void SpecialPrint(int count, int countMax, int type,int buttonNumber = 0,int buttonmax = 1);

protected:
	BOOL m_existFlag;
	BOOL m_enableFlag;
	int m_disableMode;
	POINT m_zahyo;
	SIZE m_size;
	BOOL m_cancelButtonFlag;
	BOOL m_upButtonFlag;
	BOOL m_downButtonFlag;

	POINT m_checkPicZahyo;
	POINT m_checkDelta;
	SIZE m_checkSize;


	BOOL m_returnCannotClick;

	int m_volumeType;

	int m_clickTime;

	int m_animePattern[4];
	int m_animeSpeed[4];
	int m_animeType[4];

	int m_clickSound;
	int m_cannotClickSound;
	int m_enterSound;
	int m_exitSound;
	int m_enterSoundWait;
	int m_exitSoundWait;

	int m_clickVoice;
	int m_cannotClickVoice;
	int m_enterVoice;
	int m_exitVoice;

	int m_buttonPrintMode;

	int m_accelKey[3];
	CPicture* m_pic;
	CPicture* m_bg;
	POINT m_picSrcZahyo[4];
	int m_tateYoko;

	int m_mode;
	int m_count;
	int m_enterCount;
	int m_exitCount;
	BOOL m_enterFlag;
	BOOL m_exitFlag;

	CTaihi* m_taihi;
	int m_taihiNumber;

	int m_animeCount[4];

	void CalcuPicParam(void);

	void ResetOtherAnimeCount(void);

	int m_picPattern1;
	int m_picPattern2;
	int m_picPercent;

	BOOL m_updownRevFlag;
	BOOL CheckOnButton(CInputStatus* lpInput);

	int m_buttonCode;

	LPSTR m_filename;

	CNameList* m_setup;	
	CSuperButtonSetup* m_superButtonSetup;

	int m_ignoreCount;
	bool m_entered;
};




#endif
/*_*/

