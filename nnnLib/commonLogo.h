//
// commonLogo.h
//

#if !defined __NNNLIB_LOGO__
#define __NNNLIB_LOGO__


class CGameCallBack;

class CCommonLogo : public CCommonGeneral
{
public:
	CCommonLogo(CGameCallBack* lpGame);
	virtual ~CCommonLogo();
	virtual void End(void);

	virtual int Calcu(void);
	virtual int Print(void);
	virtual int Init(void);

protected:
	int m_logoKosuu;
//	int m_nextMode;

	int m_defaultUseBGColor;
	int m_defaultFadeInTime;
	int m_defaultFadeOutTime;
	int m_defaultKeepTime;

	int m_defaultFadeInColorR;
	int m_defaultFadeInColorG;
	int m_defaultFadeInColorB;

	int m_defaultFadeOutColorR;
	int m_defaultFadeOutColorG;
	int m_defaultFadeOutColorB;

	LPSTR* m_filename;
	int* m_fadeInTime;
	int* m_fadeOutTime;
	int* m_keepTime;
	int* m_fadeInColor;
	int* m_fadeOutColor;
	int* m_skipOkFlag;
	int* m_fadeInBGColorFlag;
	int* m_fadeOutBGColorFlag;

	int m_useCustomBGColorFlag;
	int m_useCustomFileFlag;
	int m_useCustomSkipFlag;
	int m_useCustomTimeFlag;
	int m_useCustomColorFlag;

//	int m_cdCheckFlag;
	virtual void LoadPicture(void);
	virtual int NextMode(void);

	int m_mode;
	int m_subMode;
	int m_count;
	int m_soundCount;

	virtual void BeforeInit(void) {}
	virtual void AfterInit(void) {}
	virtual void BeforeCalcu(void){}
	virtual void AfterCalcu(void){}
	virtual void BeforePrint(void){}
	virtual void AfterPrint(void){}


	virtual void ReCreateExitScreen(void);


	int m_soundOrVoiceKosuu;
	int* m_soundOrVoiceTiming;//type mode frame
	LPSTR* m_soundOrVoiceName;
	int* m_soundOrVoicePlayed;

	void CheckSoundOrVoice(void);
	void PlaySoundOrVoice(int n);

private:
};



#endif
/*_*/

