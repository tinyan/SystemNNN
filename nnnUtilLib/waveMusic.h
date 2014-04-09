//
//
//

#if !defined __NNNUTILLIB_WAVEMUSIC__
#define __NNNUTILLIB_WAVEMUSIC__

class COggStreamDecoder;
class CMMLControl;

class CWaveMusic
{
public:
	CWaveMusic(LPVOID myDirectSound,int number = 0);
	~CWaveMusic();
	void End(void);

	BOOL PlayBGM(LPSTR filename,int loop = 0,BOOL fadeinFlag = TRUE,int fadeinTime = 0);
	BOOL StopBGM(BOOL fadeOutFlag = FALSE,int fadeOutTime = 0);
	void SetStartVolume(int vol);
	void ChangeVolume(int vol);
	void FadeVolume(int vol,int fadeTime);

	void SetFadeInTime(int fadeInTime){m_fadeInTime0 = fadeInTime;}
	void SetFadeOutTime(int fadeOutTime){m_fadeOutTime0 = fadeOutTime;}


	void Pause(void);
	void Resume(void);
	BOOL CheckPlaying(void);
	int GetMusicTime(void);

	static DWORD WINAPI staticMyThread(LPVOID Param);
	DWORD WINAPI MyThread(LPVOID Param);
	HANDLE m_hEvent[16];
	HANDLE m_hReturnEvent[16];


	int m_musicLoopCount;
	int m_musicLoopCount0;
	LPVOID m_myDirectSound;
	LPVOID m_directSoundBuffer;
	LPVOID m_directSoundBuffer8;
	LPVOID m_directSoundNotify;

	COggStreamDecoder* m_oggStreamDecoder;
	DWORD m_threadID;
	HANDLE m_threadHandle;
	FILE* m_filePointer;

//	HANDLE m_fileHandle;
//	static CWaveMusic* m_this;
	BOOL m_dataEndFlag;
	LPSTR m_filename;

	int GetBlock(int n);

	int m_nokoriDataSize;

//	char m_blockBuffer[44100*2*2 *2];
//	char m_fftBuffer[4096];
//	char m_fftBuffer0[44100*2*2 ];
//	char m_fftBuffer00[44100*2*2 ];

	char* m_blockBuffer;
	char* m_fftBuffer;
	char* m_fftBuffer0;
	char* m_fftBuffer00;

	int m_waveTime;
	int m_waveTime0;

	int m_playFlag0;
	int m_playFlag;

	int m_bufferTime;

	int m_bufferNumber;

	int m_bufferBlockNumber;

	CMMLControl* m_mmlControl;

	short* m_convBuffer;


	int m_volume;
	int m_volume0;
	BOOL m_fadeInFlag;
	BOOL m_fadeOutFlag;
	BOOL m_fadeInFlag0;
	BOOL m_fadeOutFlag0;
	int m_fadeInTime;
	int m_fadeInTime0;
	int m_fadeOutTime;
	int m_fadeOutTime0;

	int m_fadeInCount;
	int m_fadeOutCount;

	BOOL m_fadeFlag;
	int m_fadeVolumeStart;
	int m_fadeVolumeEnd;
	int m_fadeVolumeEnd0;
	int m_fadeTime;
	int m_fadeTime0;
	int m_fadeCount;

	int m_nowVolume;


	void SetFadeInVolume(void);
	void SetFadeOutVolume(void);
	void SetNormalVolume(void);
	void SetFadeVolume(void);

	BOOL OpenNewFile(LPSTR filename);

	int m_startVolume;
	BOOL m_startVolumeFlag;
	void SetVolumeRoutine(int vol);

	void OnWaveTime(void);

	int m_oldTime;
	int m_amari;
	int m_bufferTimeAmari;


	void StartSpectrum(void);
	void StopSpectrum(void);
	
	BOOL GetWavePlainData(int* wave,int block = 16);
	BOOL GetFFT(int* fft,int p = 256,int block = 16);

	int m_playTime;
	int m_spectrumCalcuMode;

	BOOL GetWaveCut(float* wave,int n = 256,int rightChannel = 0);
	void FadeVolumeMain(void);

private:

};




#endif
/*_*/

