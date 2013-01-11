//
// musicControl.h
//

#if !defined __NNNUTILLIB_MUSICCONTROL__
#define __NNNUTILLIB_MUSICCONTROL__


//class CCDControl;
//class CMIDIPlayer;
//class CNameList;

class CWaveMusic;
class CWaveData;
class CMyDirectSound;

class CMusicControl
{
public:
	CMusicControl(CMyDirectSound* lpMyDirectSound);
	~CMusicControl();
	void End(void);

	void SetDefaultFadeInOutTime(int fadein,int fadeout){m_defaultFadeInTime = fadein;m_defaultFadeOutTime = fadeout;}


	void PlayMusic(LPSTR filename,int loopCount,int volume,int fadeInTime = -1,int fadeOutTime = -1);


	void ChangeVolume(int vol);
//	void PlayMusic(int n, int md = 1);


	void StopMusic(int fadeOutTime = -1);
	void PauseMusic(void);
	void ResumeMusic(void);
	BOOL CheckPlaying(void);

	void StartSpectrum(void);
	void StopSpectrum(void);
	BOOL GetWavePlainData(int* wave,int block);
	BOOL GetSpectrum(int* spectrum,int block = 16,int point = 256);
	BOOL GetWaveCut(float* ar,int n,int rightChannel=0);

	void FadeVolume(int vol, int fadeTime = 0);

private:
	CWaveMusic* m_waveMusic[2];
	int m_useWaveMusicNumber;

	int m_defaultFadeInTime;
	int m_defaultFadeOutTime;

//	CCDControl* m_cdControl;
//	CMIDIPlayer* m_midi;

//	int m_musicMode;
//	CNameList* m_bgmList;

//	int m_bgmNumber;
//	int m_bgmKaisuu;
//	int m_playingNumber;
};


#endif
/*_*/

