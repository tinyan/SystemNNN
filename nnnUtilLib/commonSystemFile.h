//
// systemfile.h
//

#if !defined __NNNUTILLIB_SYSTEMFILE__
#define __NNNUTILLIB_SYSTEMFILE__


#define OKIKAE_SYSTEM_MAX 100

class CCommonSystemFile
{
public:

	CCommonSystemFile();
	virtual ~CCommonSystemFile();
	virtual void End(void);

	virtual BOOL Load(BOOL errorPrintFlag = FALSE);
	virtual BOOL Save(BOOL errorPrintFlag = FALSE);

	virtual BOOL GetWindowZahyo(POINT* lpPoint);

	virtual void SetCG(int playerNumber, int cgNumber);
	virtual BOOL CheckCG(int playerNumber,int cgNumber);
	virtual void SetFilm(int sptNum, int filmNum);
	virtual BOOL CheckFilm(int sptNum, int filmNum);
	virtual void SetMessageRead(int sptNum, int mesNum);
	virtual BOOL CheckMessageRead(int sptNum, int mesNum);
	virtual void SetMovie(int playerNumber,int movieNumber);
	virtual BOOL CheckMovie(int playerNumber,int movieNumber);
	virtual void SetVoice(int voicePlayerNumber);
	virtual BOOL CheckVoice(int voicePlayerNumber);

	virtual void SetMusic(int musicNumber);
	virtual BOOL CheckMusic(int musicNumber);

	virtual void SetCharaVoiceVolumeSlider(int chara,int deltaVolumeSlider);
	virtual int GetCharaVoiceVolumeSlider(int chara);

	virtual BOOL CreateGUID(BOOL existCheck = TRUE);

	virtual char* GetOkikae(int n);
	virtual void SetOkikae(int n,char* mes);

	virtual void SetAchievement(int n,int ps = 100);
	virtual int GetAchievement(int n);
	virtual void SetTerm(int n,BOOL flag = TRUE);
	virtual BOOL GetTerm(int n);
	virtual void SetTermLook(int n,BOOL flag = TRUE);
	virtual BOOL GetTermLook(int n);
	virtual void SetCharaVoiceFlag(int flagNumber,BOOL flag = TRUE);
	virtual BOOL CheckCharaVoiceFlag(int flagNumber);

//	void SetScene(int paraKosuu, int* paraPtr);
//	void SetScene(int sceneNumber);



	typedef struct tagSYSTEMDATAINFO
	{
		int size;
		int code;
		int dummy1;
		int dummy2;
		char message[16];
		int dataKosuu;
		int pad[16-9];
	} SYSTEMDATAINFO;

	typedef struct tagSYSTEMDATA
	{
		int size;
		int code;
		int dummy;
		int dummy2;
		char message[16];
		
		int year,month,day,week,hour,minute,second,milli;
		int windowX,windowY,windowSizeX,windowSizeY,colorBits,fullScreenFlag,midiMode,saveCount;
		int normalMusicVolume,normalSoundVolume,normalVoiceVolume,normalCDVolume;
		int directMusicVolume,directSoundVolume,directVoiceVolume,directCDVolume;

		int voiceMode,warningMode,messageSpeed,skipMode;
		
		int highcolormesh;
		int fontType;
		int noSkipFrame;
		int userFontFlag;

		int bgmMode;
		int autoMode;
		int notUse3DSound;
		int useVMR9;

		int musicVolume;
		int voiceVolume;
		int soundVolume;
		int movieVolume;

		int musicSwitch;
		int voiceSwitch;
		int soundSwitch;
		int movieSwitch;

		int launchCount;
		int soundVoiceVolume;
		int soundVoiceSwitch;
		int autoSpeedSlider;


		char sei[16];
		char mei[16];

		char fontName[1024];

		char seiYomi[64];
		char meiYomi[48];
		char guid[16];

		int seiAccent[16-12];
		int charaVoiceVolumeSlider[12];
		int meiAccent[16];

		int voiceOff[32];

		int userParam[32];

		int expMode[16];
		int expCheck[16];
		
		int windowNumber;
		int cursorNumber;
		int mouseNumber;
		int windowPercent;

		int d2d3d;
		int shader;
		int needShader;
		int lowTexture;

		int monitor;
		int lastSaveSlot;
		int notUseDirectDraw;
		int coninueAuto;

		int totalVolume;
		int totalVolumeSwitch;
		int screenSizeType;
		int genericFlag;//bit0:screenStretchflag
		int user[16];
	} SYSTEMDATA;



	typedef struct _tagMESSAGEREADFLAG
	{
		int size;
		int code;
		int dummy;
		int dummy2;
		char message[16];

		int flag[4096*64/32];
	} MESSAGEREADFLAG;

	typedef struct tagSYSTEMVAR
	{
		int size;
		int code;
		int dummy;
		int dummy2;
		char message[16];

		int var[128];
	} SYSTEMVAR;

	typedef struct tagCGFLAG
	{
		int size;
		int code;
		int dummy;
		int dummy2;
		char message[16];

		int data[128/32*20*4];
	} CGFLAG;

	typedef struct tagSCENEFLAG
	{
		int size;
		int code;
		int dummy;
		int dummy2;
		char message[16];

		int data[512];
	} SCENEFLAG;

	typedef struct tagFILMFLAG
	{
		int size;
		int code;
		int dummy;
		int dummy2;
		char message[16];

		int flag[128*32];
	} FILMFLAG;

	typedef struct tagVOICEFLAG
	{
		int size;
		int code;
		int dummy;
		int dummy2;
		char message[16];

		int flag[256];
	} VOICEFLAG;

	typedef struct tagMOVIEFLAG
	{
		int size;
		int code;
		int dummy;
		int dummy2;
		char message[16];

		int flag[256];
	} MOVIEFLAG;

	typedef struct tagMUSICFLAG
	{
		int size;
		int code;
		int dummy;
		int dummy2;

		char message[16];

		int flag[256];
	} MUSICFLAG;

	typedef struct tagOKIKAE
	{
		int size;
		int code;
		int dummy;
		int dummy2;

		char message[16];

		char okikae[64*OKIKAE_SYSTEM_MAX];
	} OKIKAE;

	typedef struct tagACHIEVEMENT
	{
		int size;
		int code;
		int dummy;
		int dummy2;

		char message[16];

		int achievement[1024];
	} ACHIEVEMENT;

	typedef struct tagNNNTERM
	{
		int size;
		int code;
		int dummy;
		int dummy2;

		char message[16];

		int term[1024];
	} NNNTERM;

	typedef struct tagCHARAVOICEFLAG
	{
		int size;
		int code;
		int dummy;
		int dummy2;

		char message[16];

		int flag[65536*8/32];
	} CHARAVOICEFLAG;

	SYSTEMDATAINFO m_dataHeader;	
	SYSTEMDATA m_systemdata;
//	CGDATA m_cgdata[8];
	MESSAGEREADFLAG m_messageFlag;
	SYSTEMVAR m_systemVar;
	CGFLAG m_cgFlag;
	SCENEFLAG m_sceneFlag;
	FILMFLAG m_filmFlag;
	VOICEFLAG m_voiceFlag;
	MOVIEFLAG m_movieFlag;
	MUSICFLAG m_musicFlag;
	OKIKAE m_okikae;
	ACHIEVEMENT m_achievement;
	NNNTERM m_term;
	CHARAVOICEFLAG m_charaVoiceFlag;


//	int GetSceneSubKosuuMax(int sceneNumber);
//	int GetSceneSubKosuu(int sceneNumber);
//	int GetSceneSubNumber(int sceneNumber, int* buf);
//
//	int GetScenePlayer(int sceneNumber, int* numberBuffer);
//	int GetScene(int scene,int* buff);

	BOOL m_taikenFlag;
	BOOL m_netVersion;
	int m_bitTable[32];

	LPSTR m_saveFileNameOnly;
	static char m_saveFileNameNormal[];
	static char m_saveFileNameTaiken[];

	static void SetMaxScriptNumber(int n = 64);
	static void SetMaxCGCharaNumber(int n = 20);
	static void SetMaxMovieCharaNumber(int n = 20);

	static void SetDefaultSei(LPSTR sei);
	static void SetDefaultMei(LPSTR mei);

	static int m_maxScriptNumberForInit;
	static int m_maxCGCharaNumberForInit;
	static int m_maxMovieCharaNumberForInit;
	static int m_CGCharaNumber;

	static char m_defaultSei[16];
	static char m_defaultMei[16];
	virtual void CalcuInitParameter(void);
	virtual void CreateInitData(void);

	static void SetCGCharaNinzu(int n);
	static int GetCGCharaNinzu(void);

	void ClearAllCGFlag(void);
	void ClearAllSceneFlag(void);
	void ClearAllFilmFlag(void);
	void ClearAllMessageFlag(void);
	void ClearAllVoiceFlag(void);
	void ClearAllMovieFlag(void);
	void ClearAllMusicFlag(void);
	void ClearAllOkikae(void);
	void ClearAllAchievement(void);
	void ClearAllTerm(void);
	void ClearAllCharaVoiceFlag(void);



protected:
	int m_maxScriptNumber;
	int m_maxFilmNumber;
	int m_maxMessageNumber;

	int m_maxCGCharaNumber;
	int m_maxCGNumber;

	int m_maxMovieCharaNumber;
	int m_maxMovieNumber;


private:
};

#endif
/*_*/

