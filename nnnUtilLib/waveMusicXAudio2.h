#pragma once
//
//
//

#if !defined __NNNUTILLIB_WAVEMUSICXAUDIO2__
#define __NNNUTILLIB_WAVEMUSICXAUDIO2__

class COggStreamDecoder;
class CMMLControl;
class CWaveMusic;

class VoiceCallback;

class CWaveMusicXAudio2 : public CWaveMusic 
{
public:
	CWaveMusicXAudio2(LPVOID myDirectSound, int number = 0);
	virtual ~CWaveMusicXAudio2();
	void End(void);






//	BOOL PlayBGM(LPSTR filename, int loop = 0, BOOL fadeinFlag = TRUE, int fadeinTime = 0);
//	BOOL StopBGM(BOOL fadeOutFlag = FALSE, int fadeOutTime = 0);
//	void SetStartVolume(int vol);
//	void ChangeVolume(int vol);
//	void FadeVolume(int vol, int fadeTime);

	void SetFadeInTime(int fadeInTime) { m_fadeInTime0 = fadeInTime; }
	void SetFadeOutTime(int fadeOutTime) { m_fadeOutTime0 = fadeOutTime; }


//	void Pause(void);
//	void Resume(void);
//	BOOL CheckPlaying(void);
//	int GetMusicTime(void);

	static DWORD WINAPI staticMyThreadXAudio2(LPVOID Param);
	DWORD WINAPI MyThread(LPVOID Param);

	int GetBlock(int n);

	void SetFadeInVolume(void);
	void SetFadeOutVolume(void);
	void SetNormalVolume(void);
	void SetFadeVolume(void);

//	BOOL OpenNewFile(LPSTR filename);

	void SetVolumeRoutine(int vol);

	void OnWaveTime(void);


//	void StartSpectrum(void);
//	void StopSpectrum(void);

//	BOOL GetWavePlainData(int* wave, int block = 16);
//	BOOL GetFFT(int* fft, int p = 256, int block = 16);


//	BOOL GetWaveCut(float* wave, int n = 256, int rightChannel = 0);
//	void FadeVolumeMain(void);

	LPVOID m_xAudio2;
	LPVOID m_sourceVoice;

	VoiceCallback* m_callback;
	char* m_blockBuffer2;
	int m_xaudio2BufferNumber;


protected:

private:

};




#endif
/*_*/

