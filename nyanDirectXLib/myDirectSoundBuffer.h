//
//
//

#if !defined __NYANDIRECTX_DIRECTSOUNDBUFFER__
#define __NYANDIRECTX_DIRECTSOUNDBUFFER__


class CMyDirectSoundBuffer
{
public:
	CMyDirectSoundBuffer(LPVOID lpDirectSound,BOOL sound3DFlag = FALSE);
	virtual ~CMyDirectSoundBuffer();
	virtual void End(void);


	virtual BOOL SetData(char* data,int dataSize, int channel,int samplingRate,int samplingBit);

	virtual void Play(BOOL loopFlag = FALSE);
	virtual void Stop(BOOL waitFlag = FALSE);

	virtual void SetVolume(int volume);

	virtual void SetStartTeii(float fx,float fy,float fz);
	virtual void SetEndTeii(float fx,float fy,float fz);
	virtual void SetMoveTime(int tm);
	virtual void SetDoppler(int dop);


	virtual void SetVelocity(float speedX,float speedY,float speedZ);
	virtual void Set3DPosition(float x,float y,float z);
protected:

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

//	BOOL m_playFlag;
};






#endif
/*_*/


