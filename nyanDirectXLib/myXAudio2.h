#pragma once
//
// mydirectsound.h
//

#if !defined __NYANDIECTX_XAUDIO2__
#define __NYANDIRECTX_XAUDIO2__

class CMyDirectSound;
class CMyXaudio2Buffer;

class CMyXAudio2 : public CMyDirectSound
{
public:
	CMyXAudio2(HWND hwnd);
	virtual ~CMyXAudio2();
	virtual void End(void);

//	virtual void Set3DSoundFlag(BOOL flg);
//	virtual void SetPrimaryFormat(int channel, int sampleRate, int bit);

	virtual void Start(BOOL formatSetFlag = FALSE);

//	static BOOL CALLBACK DSEnumCallback(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext);

	virtual BOOL Play(char* waveData, int waveSize);

	virtual LPVOID GetDirectSound(void);

	virtual void SetPrimaryVolume(int volume);

	virtual void Stop(void);
//	virtual void SetVolume(int vol);


//	virtual BOOL Check3DSoundOk(void);
protected:
	LPVOID m_xaudio2;
	LPVOID m_masterVoice;
	BOOL m_coInitFlag;

	//LPDIRECTSOUNDBUFFER m_lpDirectSoundBuffer[DSOUND_BUFFER_KOSUU];


	//	CGame* m_game;
	//HWND m_hWnd;

	//LPDIRECTSOUND m_lpDirectSound;
	//LPDIRECTSOUNDBUFFER m_lpPrimaryBuffer;
	//LPDIRECTSOUNDBUFFER m_lpDirectSoundBuffer[DSOUND_BUFFER_KOSUU];

	//LPVOID m_lpDirectSound;
	//LPVOID m_lpPrimaryBuffer;
	//LPVOID m_lpDirectSoundBuffer[DSOUND_BUFFER_KOSUU];


	//	LPDIRECTSOUNDBUFFER m_lpDirectSoundBufferForStream;

	//	LPDIRECTSOUND3DLISTENER m_lpListener;
	//LPVOID m_lpListener;


	//	LPDIRECTSOUNDBUFFER m_lpDirectSoundBufferForSystem[SYSTEMSOUND_BUFFER_KOSUU];

	//int m_nowSoundNumber;

	//int m_vol;
	//	BOOL m_systemSoundExistFlag[SYSTEMSOUND_BUFFER_KOSUU];

	//	int m_streamBlockNumber;

	//int m_primaryChannel;
	//int m_primarySampleRate;
	//int m_primaryBit;

	//int m_3dSoundFlag;


};

#endif
/*_*/


