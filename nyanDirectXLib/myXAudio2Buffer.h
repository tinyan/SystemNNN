#pragma once
//
//
//

#if !defined __NYANDIRECTX_XAUDIO2SOUNDBUFFER__
#define __NYA__NYANDIRECTX_XAUDIO2SOUNDBUFFER__

class CMyDirectSoundBuffer;

class CMyXAudio2Buffer : public CMyDirectSoundBuffer
{
public:
	CMyXAudio2Buffer(LPVOID lpDirectSound, BOOL sound3DFlag = FALSE);
	virtual ~CMyXAudio2Buffer();
	virtual void End(void);


	BOOL SetData(char* data, int dataSize, int channel, int samplingRate, int samplingBit,BOOL loopFlag = FALSE);

	void Play(BOOL loopFlag = FALSE);
	void Stop(BOOL waitFlag = FALSE);

	void SetVolume(int volume);

//	void SetStartTeii(float fx, float fy, float fz);
//	void SetEndTeii(float fx, float fy, float fz);
//	void SetMoveTime(int tm);
//	void SetDoppler(int dop);


	void SetVelocity(float speedX, float speedY, float speedZ);
	void Set3DPosition(float x, float y, float z);
private:
	LPVOID m_xAudio2;
	/*
	LPVOID m_directSound;
	LPVOID m_directSoundBuffer;
	LPVOID m_directSoundBuffer8;
	LPVOID m_directSound3DBuffer;

	int m_bufferSize;
	int m_channel;
	int m_samplingRate;
	int m_samplingBit;

	BOOL m_3DSoundFlag;
	BOOL m_dataExistFlag;

	float m_startXYZ[3];
	float m_endXYZ[3];
	int m_moveTime;
	int m_doppler;
	*/

	//	BOOL m_playFlag;
	char* m_inBuffer;
	int m_inBufferSize;

};






#endif
/*_*/



