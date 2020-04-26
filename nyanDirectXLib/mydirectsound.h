//
// mydirectsound.h
//

#if !defined __NYANDIECTX_SOUND__
#define __NYANDIRECTX_SOUND__

//#define INITGUID
//‚Í‚¸‚·




//#include <dsound.h>
//dummy
//#include "c:\Program Files\Microsoft DirectX 9.0 SDK (Summer 2004)\include\dsound.h"

//#define SYSTEMSOUND_BUFFER_KOSUU 17
#define DSOUND_BUFFER_KOSUU 5

//class CGame;

class CMyDirectSound
{
public:
	CMyDirectSound(HWND hwnd);
	virtual ~CMyDirectSound();
	virtual void End(void);

	virtual void Set3DSoundFlag(BOOL flg);
	virtual void SetPrimaryFormat(int channel,int sampleRate,int bit);

	virtual void Start(BOOL formatSetFlag = FALSE);

	static BOOL CALLBACK DSEnumCallback(LPGUID lpGuid,LPCSTR lpcstrDescription,LPCSTR lpcstrModule,LPVOID lpContext);

	virtual BOOL Play(char* waveData,int waveSize);
//	BOOL SetSystemSound(int n, char* waveData, int waveSize);
//	BOOL PlaySystemSound(int n);

//	BOOL StartStream(char* waveData, int startBlockSize = 1024*128);
//	BOOL NextStream(char* waveData, int blockSize = 1024*128);
//	BOOL StopStream(void);

//	int GetCurrentPosition(void);

	//LPDIRECTSOUND GetDirectSound(void);
	virtual LPVOID GetDirectSound(void);

	virtual void SetPrimaryVolume(int volume);

	virtual void Stop(void);
	virtual void SetVolume(int vol);


	virtual BOOL Check3DSoundOk(void);
	static int m_xAudioFlag;
protected:
//	CGame* m_game;
	HWND m_hWnd;

	//LPDIRECTSOUND m_lpDirectSound;
	//LPDIRECTSOUNDBUFFER m_lpPrimaryBuffer;
	//LPDIRECTSOUNDBUFFER m_lpDirectSoundBuffer[DSOUND_BUFFER_KOSUU];

	LPVOID m_lpDirectSound;
	LPVOID m_lpPrimaryBuffer;
	//LPVOID m_lpDirectSoundBuffer[DSOUND_BUFFER_KOSUU];
	LPVOID* m_lpDirectSoundBuffer;


//	LPDIRECTSOUNDBUFFER m_lpDirectSoundBufferForStream;

//	LPDIRECTSOUND3DLISTENER m_lpListener;
	LPVOID m_lpListener;


//	LPDIRECTSOUNDBUFFER m_lpDirectSoundBufferForSystem[SYSTEMSOUND_BUFFER_KOSUU];

	int m_nowSoundNumber;

	int m_vol;
//	BOOL m_systemSoundExistFlag[SYSTEMSOUND_BUFFER_KOSUU];

//	int m_streamBlockNumber;

	int m_primaryChannel;
	int m_primarySampleRate;
	int m_primaryBit;

	int m_3dSoundFlag;



};

#endif
/*_*/

