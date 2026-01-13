#if !defined __NNNUTILLIB_SCRIPTVOICECONTROL__
#define __NNNUTILLIB_SCRIPTVOICECONTROL__


class CMyDirectSound;
class CMyDirectSoundBuffer;


class CScriptVoiceControl
{
public:
	CScriptVoiceControl(CMyDirectSound* myDirectSound,int* expFlag);
	~CScriptVoiceControl();
	void End(void);

	void SetLoopFlag(int n,BOOL flg = TRUE);
	BOOL GetLoopFlag(int n);

	void Play(int ch,BOOL loopFlag = FALSE,int fadeTime = 0);
	void Stop(int ch,BOOL waitFlag = FALSE,int fadeTime = 0);

//	void Stop(int ch);
	void AllStop(void);
	void StopIfLoops(int ch);
	bool IsPlaying(int ch);

	BOOL SetData(int ch,char* data,int dataSize, int channel,int samplingRate,int samplingBit,BOOL loopFlag = FALSE);

	void SetVolume(int ch,int volume,int fadeTime);

	void SetStartTeii(int ch,float fx,float fy,float fz);
	void SetEndTeii(int ch,float fx,float fy,float fz);
	void SetMoveTime(int ch,int tm);
	void SetDoppler(int ch,int dop);


	void SetVelocity(int ch,float speedX,float speedY,float speedZ);
	void Set3DPosition(int ch,float x,float y,float z);

	int GetLoopWork(int n,int k);
	void SetLoopWork(int n,int k,int d);

	void OnMainLoop(int cnt);

	void SetLoopWorkParam(int ch,int senum,int charaVoiceDelta,int paraKosuu,int* pData);
	void CalcuTeii(int ch);

	void InvalidateVolumeCommand(int ch,BOOL flg = TRUE);
	BOOL CheckVolumeCommandOk(int ch);
	void JumpToLast(void);

private:
	CMyDirectSound* m_myDirectSound;
	CMyDirectSoundBuffer** m_scriptVoice;
	int m_voiceKosuu;
	int m_workKosuu;
	int* m_expFlag;
	int* m_loopVoiceWork;


	int* m_fadeTime;
	int* m_fadeCount;
	int* m_fadeFromVolume;
	int* m_fadeTargetVolume;

};



#endif
/*_*/


