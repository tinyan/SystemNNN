//
// superButtonSetup
//

#if !defined __NNNUTILLIB_SUPERBUTTONSETUP__
#define __NNNUTILLIB_SUPERBUTTONSETUP__

class CSetupList;

class CCommonButton;
class CNameList;

class CSuperButtonSetup
{
public:
	CSuperButtonSetup(CNameList* lpNameList,LPSTR buttonName,CSuperButtonSetup* lpCopyFrom = NULL,POINT* lpDelta = NULL,BOOL notSrcPicCopy = FALSE);
	~CSuperButtonSetup();
	void End(void);

	void SetupButtonStatus(CCommonButton* lpButton);

	int GetClickTime(void) {return m_clickTime;}
	SIZE GetSize(void) {return m_size;}
	POINT GetZahyo(void){return m_zahyo;}
	LPSTR GetFileName(void){return m_filename;}
	POINT GetCheckDelta(void){return m_checkDelta;}
	SIZE GetCheckSize(void){return m_checkSize;}
	POINT GetCheckPicZahyo(void){return m_checkPicZahyo;}

	void CopyParam(CSuperButtonSetup* lpSetup,int deltaX = 0,int deltaY = 0);



	int GetAnimePattern(int n){return m_animePattern[n];}
	int GetAnimeSpeed(int n){return m_animeSpeed[n];}
	int GetAnimeType(int n){return m_animeType[n];}
	POINT GetPicSrcZahyo(int n){return m_picSrcZahyo[n];}
	int GetPicTateYoko(void){return m_picTateYoko;}

	int GetClickSound(void) {return m_clickSound;}
	int GetCannotClickSound(void) {return m_cannotClickSound;}
	int GetEnterSound(void){return m_enterSound;}
	int GetExitSound(void) {return m_exitSound;}
	
	int GetEnterWaitTime(void){return m_enterWaitTime;}
	int GetExitWaitTime(void){return m_exitWaitTime;}

	int GetAccelKey(int n){return m_accelKey[n];}

	int GetButtonPrintMode(void){return m_buttonPrintMode;}
	int GetCancelButtonFlag(void){return m_cancelButtonFlag;}
	int GetUpButtonFlag(void){return m_upButtonFlag;}
	int GetDownButtonFlag(void){return m_downButtonFlag;}
	int GetUpDownReverseFlag(void){return m_updownReverseFlag;}

	int GetVolumeType(void){return m_volumeType;}

//	int GetPicOnMemory(void){return m_picOnMemory;}
//	int GetPicUseLayerStart(void){return m_picUseLayerStart;}
//	int GetPicUseLayerKosuu(void){return m_picUseLayerKosuu;}

	static BOOL m_notCopyFlag;

	void SetZahyoIfCan(POINT pt);
	static void SetNotCopyFlagEnable(BOOL flg = TRUE){m_notCopyFlag = flg;}
private:
	CSetupList* m_setupList;
	
	int m_clickTime;
	SIZE m_size;
	POINT m_zahyo;
	LPSTR m_filename;

	POINT m_checkPicZahyo;
	POINT m_checkDelta;
	SIZE m_checkSize;

	int m_animePattern[4];
	int m_animeSpeed[4];
	int m_animeType[4];

	POINT m_picSrcZahyo[4];

	int m_accelKey[3];

	int m_clickSound;
	int m_cannotClickSound;
	int m_enterSound;
	int m_exitSound;
	int m_enterWaitTime;
	int m_exitWaitTime;

	int m_buttonPrintMode;
	int m_cancelButtonFlag;
	int m_upButtonFlag;
	int m_downButtonFlag;
	int m_updownReverseFlag;

	int m_picTateYoko;
	int m_volumeType;

//	int m_picOnMemory;
//	int m_picUseLayerStart;
//	int m_picUseLayerKosuu;

	char m_buttonName[256];
};

#endif
/*_*/
