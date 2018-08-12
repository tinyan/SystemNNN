//
//
//

#include <windows.h>
#include <stdio.h>
#include <mmSystem.h>

#include <dsound.h>
#include <xaudio2.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\myFile.h"

#include "..\nyanDirectXLib\myDirectSound.h"

#include "..\nyanDirectXLib\myXAudio2.h"


#include "oggStreamDecoder.h"
//#include "oggDecoder.h"

#include "mmlControl.h"


#include "waveMusic.h"
#include "waveMusicXAudio2.h"





#define STARTBGM_COMMAND 3
#define STOPBGM_COMMAND 4
#define THREADEND_COMMAND 5
#define GETMUSICTIME_COMMAND 7
#define PAUSEBGM_COMMAND 8
#define RESUMEBGM_COMMAND 9
#define CHECKPLAYING_COMMAND 10
#define SETVOLUME_COMMAND 11
#define FADEOUT_COMMAND 12
//#define RETURNEVENT_STATUS 13
#define GETFFT_COMMAND 13
#define FADEVOLUME_COMMAND 14

short convBufferXAudio2[4096];
short convBuffer2XAudio2[4096];

//
// multiThreadOnly
//


class VoiceCallback : public IXAudio2VoiceCallback
{
public:
	HANDLE* m_handle;
	int m_n;

	VoiceCallback() {  m_n = 0; }
	~VoiceCallback() {  }
	void SetHandle(HANDLE* lpHandle) { m_handle = lpHandle; }
	void STDMETHODCALLTYPE OnBufferEnd(void * pBufferContext) 
	{
		char mes[256];
		sprintf_s(mes, 256, "[event %d]\n", m_n);
		OutputDebugString(mes);
		SetEvent(m_handle[m_n]); m_n++; m_n %= 2; 
	}


	void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32 BytesRequired) { }
	void STDMETHODCALLTYPE OnVoiceProcessingPassEnd(void) { }
	void STDMETHODCALLTYPE OnStreamEnd(void) { /*SetEvent(g_hEvent);*/ }
	void STDMETHODCALLTYPE OnBufferStart(void *pBufferContext) { /*SetEvent(g_hEvent);*/ }
//	void STDMETHODCALLTYPE OnBufferEnd(void *pBufferContext) { }
	void STDMETHODCALLTYPE OnLoopEnd(void *pBufferContext) { }
	void STDMETHODCALLTYPE OnVoiceError(void *pBufferContext, HRESULT Error) { }

};


CWaveMusicXAudio2::CWaveMusicXAudio2(LPVOID myXAudio2, int number) : CWaveMusic(NULL,number)
{
	//change to xaudio2
	m_xAudio2 = myXAudio2;

//	m_myDirectSound = myDirectSound;
	m_bufferNumber = number;

	m_xaudio2BufferNumber = 0;

	m_blockBuffer2 = new char[44100 * 2 * 2 * 2];



//	m_filePointer = NULL;
	//	m_fileHandle = INVALID_HANDLE_VALUE;

//	m_spectrumCalcuMode = 0;

	//create second buffer 2sec

	WAVEFORMATEX pcmwf;
	ZeroMemory(&pcmwf, sizeof(pcmwf));
	pcmwf.cbSize = sizeof(pcmwf);
	pcmwf.wBitsPerSample = 16;
	pcmwf.wFormatTag = WAVE_FORMAT_PCM;
	pcmwf.nChannels = 2;
	pcmwf.nSamplesPerSec = 44100;
	pcmwf.nBlockAlign = 4;
	pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;

	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc, sizeof(dsbdesc));
	dsbdesc.dwSize = sizeof(dsbdesc);
	dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLPOSITIONNOTIFY;
	//	dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER | DSBCAPS_CTRLPOSITIONNOTIFY;
	dsbdesc.dwBufferBytes = pcmwf.nAvgBytesPerSec * 2;
	dsbdesc.lpwfxFormat = &pcmwf;


	//VoiceCallback callback;
	m_callback = new VoiceCallback();

	m_callback->SetHandle(m_hEvent);
	IXAudio2SourceVoice* sourceVoice;

	HRESULT hr = ((IXAudio2*)m_xAudio2)->CreateSourceVoice(&sourceVoice, &pcmwf, 0, XAUDIO2_DEFAULT_FREQ_RATIO, m_callback, NULL, NULL);

	if (FAILED(hr))
	{
		OutputDebugString("Error XAudio2 CreateSourceVoice\n");
		return;
	}
	m_sourceVoice = sourceVoice;


	//source voiceÇ…ÉnÉìÉhÉãÇìnÇ∑




	//@@@change xaudio2
	/*
	LPDIRECTSOUND8 directSound8 = (LPDIRECTSOUND8)m_myDirectSound;

	LPDIRECTSOUNDBUFFER lp = NULL;
	HRESULT hr = directSound8->CreateSoundBuffer(&dsbdesc, &lp, NULL);

	m_directSoundBuffer = lp;
	lp->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&m_directSoundBuffer8);
	//refget
	*/



	//	if (hr != DS_OK) return FALSE;
	//	if (lp == NULL) return FALSE;





	//m_startVolumeFlag = FALSE;



	//	char m_blockBuffer[44100*2*2 *2];
	//	char m_fftBuffer[4096];
	//	char m_fftBuffer0[44100*2*2 ];
	//	char m_fftBuffer00[44100*2*2 ];

	/*
	m_blockBuffer = NULL;
	m_fftBuffer = NULL;
	m_fftBuffer0 = NULL;
	m_fftBuffer00 = NULL;

	m_blockBuffer = new char[44100 * 2 * 2 * 2];
	if (number < 2)
	{
		m_fftBuffer = new char[4096];
		m_fftBuffer0 = new char[44100 * 2 * 2];
		m_fftBuffer00 = new char[44100 * 2 * 2];
	}
	*/



	m_convBuffer = NULL;

	if (number == 0)
	{
		m_oggStreamDecoder = new COggStreamDecoder(convBufferXAudio2);
	}
	else if (number == 1)
	{
		m_oggStreamDecoder = new COggStreamDecoder(convBuffer2XAudio2);
	}
	else
	{
		m_convBuffer = new short[4096];
		m_oggStreamDecoder = new COggStreamDecoder(m_convBuffer);
	}



	/*

	m_mmlControl = new CMMLControl();

	for (int i = 0; i<16; i++)
	{
		m_hEvent[i] = NULL;
		m_hReturnEvent[i] = NULL;
	}

	//event
	m_hEvent[0] = CreateEvent(NULL, FALSE, FALSE, NULL);	//first point
	m_hEvent[1] = CreateEvent(NULL, FALSE, FALSE, NULL);	//centerpoint
	m_hEvent[2] = CreateEvent(NULL, FALSE, FALSE, NULL);	//end
	m_hEvent[3] = CreateEvent(NULL, FALSE, FALSE, NULL);	//start bgm command
	m_hEvent[4] = CreateEvent(NULL, FALSE, FALSE, NULL);	//stop bgm command
	m_hEvent[5] = CreateEvent(NULL, FALSE, FALSE, NULL);	//thread end command
	m_hEvent[6] = CreateEvent(NULL, FALSE, FALSE, NULL);	//bgm stopped
	m_hEvent[7] = CreateEvent(NULL, FALSE, FALSE, NULL);	//gettime event
	m_hEvent[8] = CreateEvent(NULL, FALSE, FALSE, NULL);	//pause event
	m_hEvent[9] = CreateEvent(NULL, FALSE, FALSE, NULL);	//resume event
	m_hEvent[10] = CreateEvent(NULL, FALSE, FALSE, NULL);	//checkplaying
	m_hEvent[11] = CreateEvent(NULL, FALSE, FALSE, NULL);	//setvolume
	m_hEvent[12] = CreateEvent(NULL, FALSE, FALSE, NULL);	//fadeout
															//m_hEvent[13] = CreateEvent(NULL,FALSE,FALSE,NULL);	//return event

	m_hEvent[13] = CreateEvent(NULL, FALSE, FALSE, NULL);	//getfftbuffer
	m_hEvent[14] = CreateEvent(NULL, FALSE, FALSE, NULL);	//fadeVolume

	m_hReturnEvent[3] = CreateEvent(NULL, FALSE, FALSE, NULL);	//start bgm command
	m_hReturnEvent[4] = CreateEvent(NULL, FALSE, FALSE, NULL);	//stop bgm command
	m_hReturnEvent[5] = CreateEvent(NULL, FALSE, FALSE, NULL);	//thread end command
	m_hReturnEvent[6] = CreateEvent(NULL, FALSE, FALSE, NULL);	//bgm stopped
	m_hReturnEvent[7] = CreateEvent(NULL, FALSE, FALSE, NULL);	//gettime event
	m_hReturnEvent[8] = CreateEvent(NULL, FALSE, FALSE, NULL);	//pause event
	m_hReturnEvent[9] = CreateEvent(NULL, FALSE, FALSE, NULL);	//resume event
	m_hReturnEvent[10] = CreateEvent(NULL, FALSE, FALSE, NULL);	//checkplaying
	m_hReturnEvent[11] = CreateEvent(NULL, FALSE, FALSE, NULL);	//setvolume
	m_hReturnEvent[12] = CreateEvent(NULL, FALSE, FALSE, NULL);	//fadeout

	m_hReturnEvent[13] = CreateEvent(NULL, FALSE, FALSE, NULL);	//getfftbuffer
	m_hReturnEvent[14] = CreateEvent(NULL, FALSE, FALSE, NULL);	//fadeVolume

	DSBPOSITIONNOTIFY pn[3];
	pn[0].dwOffset = 0;
	pn[0].hEventNotify = m_hEvent[0];
	pn[1].dwOffset = 1 * (44100 * 2 * 2);
	pn[1].hEventNotify = m_hEvent[1];
	pn[2].dwOffset = DSBPN_OFFSETSTOP;
	pn[2].hEventNotify = m_hEvent[2];



	LPDIRECTSOUNDNOTIFY pNotify;
	HRESULT hr2 = lp->QueryInterface(IID_IDirectSoundNotify, (LPVOID*)&pNotify);
	m_directSoundNotify = lp;

	HRESULT hr3 = pNotify->SetNotificationPositions(3, pn);

	*/

/*
	m_fadeInFlag = FALSE;
	m_fadeOutFlag = FALSE;
	m_volume = 100;

	m_fadeInCount = 0;
	m_fadeOutCount = 0;

	m_fadeInTime0 = 20;
	m_fadeInTime = 20;

	m_fadeOutTime0 = 30;
	m_fadeOutTime = 30;

	ZeroMemory(m_fftBuffer, 4096);
	ZeroMemory(m_fftBuffer0, 40960);
	ZeroMemory(m_fftBuffer00, 40960);

	m_fadeTime = 0;
	m_fadeTime0 = 0;
	m_fadeCount = 0;
	m_fadeVolumeStart = 0;
	m_fadeVolumeEnd = 0;
	m_fadeVolumeEnd0 = 0;

	*/

	//	m_this = this;

	//thread
	m_threadHandle = CreateThread(NULL, 0, staticMyThreadXAudio2, (LPVOID)this, 0, &m_threadID);
	if (m_threadHandle == NULL)
	{
		//error
	}
}


CWaveMusicXAudio2::~CWaveMusicXAudio2()
{
	End();
}


void CWaveMusicXAudio2::End(void)
{
	//threadÇ™ë∂ç›Ç∑ÇÍÇŒí‚é~èIóπÇ≥ÇπÇÈ

	/*
	if (m_threadHandle != NULL)
	{
		SetEvent(m_hEvent[THREADEND_COMMAND]);

		WaitForSingleObject(m_threadHandle, 5 * 1000);

		//		if (m_hEvent[RETURNEVENT_STATUS] != NULL)
		//		{
		//			WaitForSingleObject(m_hEvent[RETURNEVENT_STATUS],2*1000);
		//		}

		Sleep(100);
		CloseHandle(m_threadHandle);

		m_threadHandle = NULL;
	}
	*/


/*
	int i = 0;
	for (i = 0; i<16; i++)
	{
		if (m_hEvent[i] != NULL)
		{
			CloseHandle(m_hEvent[i]);
			m_hEvent[i] = NULL;
		}
	}

	for (i = 0; i<16; i++)
	{
		if (m_hReturnEvent[i] != NULL)
		{
			CloseHandle(m_hReturnEvent[i]);
			m_hReturnEvent[i] = NULL;
		}
	}
	*/

	//@@@change to xaudio2
	/*
	if (m_directSoundNotify != NULL)
	{
		LPDIRECTSOUNDNOTIFY lp = (LPDIRECTSOUNDNOTIFY)m_directSoundNotify;
		lp->Release();
		m_directSoundNotify = NULL;
	}


	//release second buffer

	if (m_directSoundBuffer8 != NULL)
	{
		LPDIRECTSOUNDBUFFER8 lp8 = (LPDIRECTSOUNDBUFFER8)m_directSoundBuffer8;
		lp8->Release();

		m_directSoundBuffer8 = NULL;
	}

	if (m_directSoundBuffer != NULL)
	{
		LPDIRECTSOUNDBUFFER lp = (LPDIRECTSOUNDBUFFER)m_directSoundBuffer;
		lp->Release();

		m_directSoundBuffer = NULL;
	}
	*/

	/*
	//ópêS
	if (m_filePointer != NULL)
	{
		fclose(m_filePointer);
		m_filePointer = NULL;
	}
	*/

	//	if (m_fileHandle != INVALID_HANDLE_VALUE)
	//	{
	//		CloseHandle(m_fileHandle);
	//		m_fileHandle = INVALID_HANDLE_VALUE;
	//	}

	//

	/*
	DELETEARRAY(m_convBuffer);

	DELETEARRAY(m_fftBuffer00);
	DELETEARRAY(m_fftBuffer0);
	DELETEARRAY(m_fftBuffer);
	DELETEARRAY(m_blockBuffer);


	ENDDELETECLASS(m_mmlControl);
	ENDDELETECLASS(m_oggStreamDecoder);
	*/

	if (m_callback)
	{
		delete m_callback;
		m_callback = NULL;
	}

	DELETEARRAY(m_blockBuffer2);

}

/*
BOOL CWaveMusicXAudio2::PlayBGM(LPSTR filename, int loop, BOOL fadeinFlag, int fadeinTime)
{
	if (m_threadHandle == NULL) return FALSE;

	//stop in  playing
	StopBGM();

	if (m_mmlControl->LoadMML(filename) == FALSE) return FALSE;

	//
	m_musicLoopCount0 = loop;
	m_filename = filename;

	if (fadeinFlag)
	{
		m_fadeInTime0 = fadeinTime;
		//		char mes[256];
		//		sprintf(mes,"[PlayWithFadeIn %d]",fadeinTime);
		//		OutputDebugString(mes);
	}
	else
	{
		m_fadeInTime0 = 0;
	}

	m_fadeInFlag0 = fadeinFlag;

	SetEvent(m_hEvent[STARTBGM_COMMAND]);
	WaitForSingleObject(m_hReturnEvent[STARTBGM_COMMAND], 10 * 1000);
	ResetEvent(m_hReturnEvent[STARTBGM_COMMAND]);

	return TRUE;
}
*/


//PlayVoice	pack voice
//PlaySound plain wave

/*
BOOL CWaveMusicXAudio2::StopBGM(BOOL fadeOutFlag, int fadeOutTime)
{
	if (m_threadHandle == NULL) return FALSE;

	if (fadeOutFlag == FALSE)
	{
		SetEvent(m_hEvent[STOPBGM_COMMAND]);
		WaitForSingleObject(m_hReturnEvent[STOPBGM_COMMAND], 10 * 1000);
		ResetEvent(m_hReturnEvent[STOPBGM_COMMAND]);
		//if (m_bufferNumber == 1)
		//{
		//OutputDebugString("[xxx]");
		//}
		m_fadeInFlag = FALSE;
		m_fadeFlag = FALSE;
	}
	else
	{
		if (fadeOutTime > 0)
		{
			m_fadeOutTime0 = fadeOutTime;
		}

		m_fadeOutFlag0 = fadeOutFlag;
		SetEvent(m_hEvent[FADEOUT_COMMAND]);
		WaitForSingleObject(m_hReturnEvent[FADEOUT_COMMAND], 10 * 1000);
		ResetEvent(m_hReturnEvent[FADEOUT_COMMAND]);

		//		OutputDebugString("bgm(FADEOUT)");
	}

	return TRUE;
}
*/

/*
void CWaveMusicXAudio2::SetStartVolume(int vol)
{
	m_startVolume = vol;
	m_startVolumeFlag = TRUE;
}
*/




void CWaveMusicXAudio2::SetVolumeRoutine(int vol)
{
	//@@@change to xaudio2
	if (m_sourceVoice)
	{
		float v = (float)vol;
		v *= 0.01f;
		((IXAudio2SourceVoice*)m_sourceVoice)->SetVolume(v);

	}
	/*
	if (m_directSoundBuffer != NULL)
	{
		long vol2 = (vol - 100) * 20;
		if (vol == 0) vol2 = -10000;
		if (vol2>0) vol2 = 0;
		if (vol2<-10000) vol2 = -10000;

		LPDIRECTSOUNDBUFFER8 lp = (LPDIRECTSOUNDBUFFER8)m_directSoundBuffer8;
		lp->SetVolume(vol2);
	}
	*/
}


DWORD WINAPI CWaveMusicXAudio2::staticMyThreadXAudio2(LPVOID param)
{
	CWaveMusic* thisObject = (CWaveMusic*)param;
	int rt = thisObject->MyThread(param);

	ExitThread(0);

	return rt;
}



DWORD WINAPI CWaveMusicXAudio2::MyThread(LPVOID param)
{
	BOOL bgmPlayingFlag = FALSE;
	int loopCount = 0;

	//	LPDIRECTSOUND directSound = (LPDIRECTSOUND)m_myDirectSound;
	LPDIRECTSOUNDBUFFER8 directSoundBuffer = (LPDIRECTSOUNDBUFFER8)(m_directSoundBuffer8);



	//	static int debugCount = 0;

	m_oldTime = timeGetTime();
	m_amari = 0;
	m_bufferTimeAmari = 0;


	while (TRUE)
	{
		DWORD en = WaitForMultipleObjects(15, m_hEvent, FALSE, 100);
		switch (en)
		{
		case WAIT_OBJECT_0:	//first
							//OutputDebugString("[F]");
		case WAIT_OBJECT_0 + 1:	//center
								//OutputDebugString("[C]");
								//OutputDebugString("[1sec]");
			m_waveTime0++;
			int n;
			n = 0;
			if (en == WAIT_OBJECT_0) n = 1;

			if (m_dataEndFlag)
			{
				((IXAudio2SourceVoice*)m_sourceVoice)->Stop();
				m_playFlag0 = FALSE;
			}
			else
			{
				if (GetBlock(n) == 0)
				{
					m_dataEndFlag = TRUE;
				}
			}

			OnWaveTime();

			break;
		case WAIT_OBJECT_0 + 2:	//end dummy
			break;
		case WAIT_OBJECT_0 + 3:	//play command
			m_waveTime0 = 0;

			LPSTR filename;
			filename = m_mmlControl->Kaiseki();
			if (filename == NULL)
			{
				m_mmlControl->RestartMML();
				filename = m_mmlControl->Kaiseki();
			}

#if defined _DEBUG
			char mes[256];
			wsprintf(mes, "PLAY ch=%d ã»Åy%sÅz\n", m_bufferNumber, filename);
			OutputDebugString(mes);
#endif

			OpenNewFile(filename);
			m_dataEndFlag = FALSE;
			m_nokoriDataSize = 0;

			if (m_filePointer != NULL)
				//			if (m_fileHandle != INVALID_HANDLE_VALUE)
			{
				m_xaudio2BufferNumber = 0;
				if (GetBlock(0) == 0) m_dataEndFlag = TRUE;//???
			}

			//@@@ change to xaudio2
			/*
			directSoundBuffer->SetCurrentPosition(0);
			*/
			m_fadeInFlag = m_fadeInFlag0;
			m_fadeInCount = 0;
			m_fadeInTime = m_fadeInTime0;
			m_fadeOutFlag = FALSE;
			m_fadeOutCount = 0;
			m_musicLoopCount = m_musicLoopCount0;

			if (m_startVolumeFlag)
			{
				m_volume = m_startVolume;
				m_startVolumeFlag = FALSE;
			}
			//set start volume
			if (m_fadeInFlag)
			{
				//if (m_bufferNumber == 1)
				//{
				//OutputDebugString("[o]");
				//}
				SetFadeInVolume();
			}
			else
			{
				SetNormalVolume();
			}

			//			ResetEvent(m_hEvent[0]);
			//			ResetEvent(m_hEvent[1]);

			int hr;
			//@@@change to xautio2
			//hr = directSoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@loopÇÕÇ«Ç±Ç≈ÅH
			((IXAudio2SourceVoice*)m_sourceVoice)->Start(0,0);

			hr = S_OK;
			//			if FAILED(hr)
			//			{
			//				OutputDebugString("DirectSoundBuffer::Play Error");
			//			}

			m_playTime = 0;
			m_bufferTime = 0;
			m_playFlag0 = TRUE;
			m_amari = 0;
			m_bufferTimeAmari = 0;

			m_oldTime = timeGetTime();

			SetEvent(m_hReturnEvent[STARTBGM_COMMAND]);
			break;
		case WAIT_OBJECT_0 + 4:	//stop command
			//@@@change to xaudio2
			//directSoundBuffer->Stop();
			((IXAudio2SourceVoice*)m_sourceVoice)->Stop();

			if (m_filePointer != NULL)
			{
				fclose(m_filePointer);
				m_filePointer = NULL;
			}
			//			if (m_fileHandle != INVALID_HANDLE_VALUE)
			//			{
			//				CloseHandle(m_fileHandle);
			//				m_fileHandle = INVALID_HANDLE_VALUE;
			//			}
			m_playFlag0 = FALSE;
			SetEvent(m_hReturnEvent[STOPBGM_COMMAND]);
			break;
		case WAIT_OBJECT_0 + 5:	//exit command
			//change to xaudio2
			if (m_sourceVoice)
			{
				((IXAudio2SourceVoice*)m_sourceVoice)->Stop(0, 0);
			}

			/*
			if (directSoundBuffer != NULL)
			{
				directSoundBuffer->Stop();
			}
			*/

			//			SetEvent(m_hEvent[RETURNEVENT_STATUS]);
			ExitThread(0);
			return 0;
			break;
		case WAIT_OBJECT_0 + 7:	//getmusictime
			m_waveTime = m_waveTime0;
			SetEvent(m_hReturnEvent[GETMUSICTIME_COMMAND]);
			break;
		case WAIT_OBJECT_0 + 8:	//pause
			//@@@change to xaudio2
			((IXAudio2SourceVoice*)m_sourceVoice)->Stop();

			/*
			directSoundBuffer->Stop();
			*/

			m_playFlag0 = FALSE;
			SetEvent(m_hReturnEvent[PAUSEBGM_COMMAND]);
			break;
		case WAIT_OBJECT_0 + 9:	//resume
			//@@@change to xaudio2
			/*
			directSoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
			*/
			((IXAudio2SourceVoice*)m_sourceVoice)->Start(0, 0);

			m_playFlag0 = TRUE;
			SetEvent(m_hReturnEvent[RESUMEBGM_COMMAND]);
			break;
		case WAIT_OBJECT_0 + 10:	//checkplaying
			m_playFlag = m_playFlag0;
			SetEvent(m_hReturnEvent[CHECKPLAYING_COMMAND]);
			break;
		case WAIT_OBJECT_0 + 11:	//setvolume
			m_volume = m_volume0;
			if (m_fadeOutFlag)
			{
				SetFadeOutVolume();
			}
			else if (m_fadeInFlag)
			{
				SetFadeInVolume();
			}
			else if (m_fadeFlag)
			{
				SetFadeVolume();
			}
			else
			{
				SetNormalVolume();
			}
			SetEvent(m_hReturnEvent[SETVOLUME_COMMAND]);
			break;
		case WAIT_OBJECT_0 + 12:	//fadeout

			if (m_fadeInFlag)
			{
				//ÇØÇ¢Ç≥ÇÒ
				m_fadeOutCount = m_fadeInTime - m_fadeInCount;
				if (m_fadeOutCount < 0) m_fadeOutCount = 0;
				if (m_fadeOutCount > m_fadeInTime) m_fadeOutCount = m_fadeInTime;
				if (m_fadeInTime > 0)
				{
					m_fadeOutCount *= m_fadeOutTime;
					m_fadeOutCount /= m_fadeInTime;
				}
				//				OutputDebugString("ì¡éÍ");
			}
			else if (m_fadeOutFlag == FALSE)
			{
				m_fadeOutCount = 0;
			}
			else
			{
				//ÇªÇÃÇ‹Ç‹ÅH
			}

			m_fadeOutFlag = TRUE;

			m_fadeOutTime = m_fadeOutTime0;
			//if (m_bufferNumber == 1)
			//{
			//OutputDebugString("[x]");
			//}
			m_fadeInFlag = FALSE;
			SetEvent(m_hReturnEvent[FADEOUT_COMMAND]);
			break;

		case WAIT_OBJECT_0 + 13:	//getfftbuffer
			OnWaveTime();

			if (m_fftBuffer != NULL)
			{

				//@@@change to xaudio2
				/*
				DWORD playPtr;
				if (directSoundBuffer->GetCurrentPosition(&playPtr, NULL) == DS_OK)
				{
					playPtr %= (44100 * 2 * 2 * 2);

					int n2 = playPtr / (44100 * 2 * 2);
					int n3 = playPtr % (44100 * 2 * 2);
					n3 &= ~3;
					if (n3>4408 * 39) n3 = 4408 * 39;

					if (n2 == 0)
					{
						memcpy(m_fftBuffer, m_fftBuffer00 + n3, 4096);
					}
					else
					{
						memcpy(m_fftBuffer, m_fftBuffer0 + n3, 4096);
					}
				}
				else
				{

					if (m_bufferBlockNumber == 1)
					{
						memcpy(m_fftBuffer, m_fftBuffer00 + 4408 * (m_bufferTime % 40), 4096);//4410ÇÕ4ÇÃî{êîÇ∂Ç·Ç»Ç¢ÇÃÇ≈Ç≤Ç‹Ç©Ç∑
					}
					else
					{
						memcpy(m_fftBuffer, m_fftBuffer0 + 4408 * (m_bufferTime % 40), 4096);
					}
				}
				*/
			}

			//			memcpy(m_fftBuffer,m_fftBuffer0+4096*(rand() % 10),4096);
			SetEvent(m_hReturnEvent[GETFFT_COMMAND]);
			break;

		case WAIT_OBJECT_0 + 14://fadevolume
			FadeVolumeMain();
			SetEvent(m_hReturnEvent[FADEVOLUME_COMMAND]);
			break;

		case WAIT_TIMEOUT:
			OnWaveTime();
			break;
		}
	}


	return 0;
}


void CWaveMusicXAudio2::OnWaveTime(void)
{
	int newTime;
	newTime = timeGetTime();
	int deltaTime = newTime - m_oldTime + m_amari;
	int dms;
	dms = deltaTime / 100;
	m_amari = deltaTime - dms * 100;

	int deltaBufferTime = newTime - m_oldTime + m_bufferTimeAmari;
	int dms2;
	dms2 = deltaBufferTime / 25;
	m_bufferTimeAmari = deltaBufferTime - dms2 * 25;

	m_oldTime = newTime;

	if (dms <= 0) return;

	m_playTime += dms;
	m_bufferTime += dms2;

	//if (m_bufferNumber == 1)
	//{
	//OutputDebugString(".");
	//}

	if (m_fadeInFlag)
	{
		//OutputDebugString("+");
		if (m_fadeInCount <= m_fadeInTime)
		{
			m_fadeInCount += dms;
			if (dms>0)
			{
				//						OutputDebugString("+");
			}
			else
			{
				//						OutputDebugString(",");
			}
			if (m_fadeInCount >= m_fadeInTime)
			{
				m_fadeInCount = m_fadeInTime;
				m_fadeInFlag = FALSE;
				//				OutputDebugString("[fadeinèIóπÇ…Ç·]");
			}
			//set volume
			if (m_playFlag0)
			{
				SetFadeInVolume();
			}
		}
	}
	else if (m_fadeOutFlag)
	{
		m_fadeOutCount += dms;
		if (dms>0)
		{
			//					OutputDebugString("-");
		}
		else
		{
			//					OutputDebugString(".");
		}

		if (m_fadeOutCount >= m_fadeOutTime)
		{
			//stop bgm

			if (m_playFlag0)
			{
				//@@@ change to xaudio2
				/*
				LPDIRECTSOUNDBUFFER8 directSoundBuffer = (LPDIRECTSOUNDBUFFER8)(m_directSoundBuffer8);

				directSoundBuffer->Stop();
				*/
				((IXAudio2SourceVoice*)m_sourceVoice)->Stop();

				//				if (m_fileHandle != INVALID_HANDLE_VALUE)
				//				{
				//					CloseHandle(m_fileHandle);
				//					m_fileHandle = INVALID_HANDLE_VALUE;
				//				}

				if (m_filePointer != NULL)
				{
					fclose(m_filePointer);
					m_filePointer = NULL;
				}
			}
			m_playFlag0 = FALSE;
			m_fadeOutFlag = FALSE;
			//if (m_bufferNumber == 1)
			//{
			//OutputDebugString("[xx]");
			//}
			m_fadeInFlag = FALSE;
		}
		else
		{
			//set volume
			SetFadeOutVolume();
		}
	}
	else if (m_fadeFlag)
	{
		if (m_fadeCount <= m_fadeTime)
		{
			m_fadeCount += dms;
			if (dms>0)
			{
				//						OutputDebugString("+");
			}
			else
			{
				//						OutputDebugString(",");
			}
			if (m_fadeCount >= m_fadeTime)
			{
				m_fadeCount = m_fadeTime;
				m_fadeFlag = FALSE;
				//				OutputDebugString("[fadeinèIóπÇ…Ç·]");
			}
			//set volume
			if (m_playFlag0)
			{
				SetFadeVolume();
			}
		}

	}
}




//Ç‡Ç«ÇËÅFóLå¯ÉfÅ[É^ÉTÉCÉY
int CWaveMusicXAudio2::GetBlock(int n)
{
	char* blockBuffer = m_blockBuffer;
	if (m_xaudio2BufferNumber != 0)
	{
		blockBuffer = m_blockBuffer2;
	}

	if (m_filePointer == NULL)
		//	if (m_fileHandle == INVALID_HANDLE_VALUE)
	{
//		ZeroMemory(m_blockBuffer, 44100 * 2 * 2);
		ZeroMemory(blockBuffer, 44100 * 2 * 2);
		return 0;
	}



	BOOL f = TRUE;
	while (f)
	{
		//OutputDebugString("[decode]");
		int sz = m_oggStreamDecoder->Decode();
		if (sz>0)
		{
			if (m_bufferNumber == 0)
			{
//				memcpy(m_blockBuffer + m_nokoriDataSize, convBufferXAudio2, sz);
				memcpy(blockBuffer + m_nokoriDataSize, convBufferXAudio2, sz);
			}
			else
			{
//				memcpy(m_blockBuffer + m_nokoriDataSize, convBuffer2XAudio2, sz);
				memcpy(blockBuffer + m_nokoriDataSize, convBuffer2XAudio2, sz);
			}

			m_nokoriDataSize += sz;
			if (m_nokoriDataSize >= 44100 * 2 * 2) f = FALSE;

			//char mes[256];
			//sprintf(mes,"[decode=%d nokori=%d]",sz,m_nokoriDataSize);
			//OutputDebugString(mes);

		}
		else
		{
			//char mes[256];
			//sprintf(mes,"[nokori=%d]",m_nokoriDataSize);
			//OutputDebugString(mes);

			m_oggStreamDecoder->EndDecode();
			BOOL flg = TRUE;

			if (m_filePointer != NULL)
			{
				fclose(m_filePointer);
				m_filePointer = NULL;
			}

			//			if (m_fileHandle != INVALID_HANDLE_VALUE)
			//			{
			//				CloseHandle(m_fileHandle);
			//				m_fileHandle = INVALID_HANDLE_VALUE;
			//			}

			//nextdecode?

			LPSTR filename;
			filename = m_mmlControl->Kaiseki();
			if (filename == NULL)
			{
				if (m_musicLoopCount == 0)
				{
					m_mmlControl->RestartMML();
					filename = m_mmlControl->Kaiseki();
				}
				else
				{
					m_musicLoopCount--;
					if (m_musicLoopCount > 0)
					{
						m_mmlControl->RestartMML();
						filename = m_mmlControl->Kaiseki();
					}
				}
			}


			if (filename == NULL)
			{
				f = FALSE;
			}
			else
			{
#if defined _DEBUG
				OutputDebugString("- ã»Åy");
				OutputDebugString(filename);
				OutputDebugString("Åz");
#endif

				OpenNewFile(filename);
			}
		}
	}


	int dataSize = m_nokoriDataSize;
	if (dataSize > 44100 * 2 * 2) dataSize = 44100 * 2 * 2;

#if defined _DEBUG
	//char mes2[256];
	//sprintf(mes2,"[dataSize=%d]",dataSize);
	//OutputDebugString(mes2);
#endif

	//Ç†Ç´ÇÇ§ÇﬂÇÈ
	if (m_nokoriDataSize < 44100 * 2 * 2)
	{
//		ZeroMemory(m_blockBuffer + m_nokoriDataSize, 44100 * 2 * 2 - m_nokoriDataSize);
		ZeroMemory(blockBuffer + m_nokoriDataSize, 44100 * 2 * 2 - m_nokoriDataSize);
	}

	//ì]ëó


//	((IXAudio2SourceVoice*)m_sourceVoice)->Start(0, 0);


	XAUDIO2_BUFFER buffer = { 0 };


	buffer.AudioBytes = dataSize;

	buffer.pAudioData = (const BYTE*)blockBuffer;
//	buffer.pAudioData = (const BYTE*)m_blockBuffer;
	buffer.Flags = XAUDIO2_END_OF_STREAM;

	((IXAudio2SourceVoice*)m_sourceVoice)->SubmitSourceBuffer(&buffer);





	//@@@ change to xaudio2
	/*
	LPBYTE lpBlockAdd1;
	LPBYTE lpBlockAdd2;
	DWORD blockSize1;
	DWORD blockSize2;
	LPDIRECTSOUNDBUFFER8 lpDSBuffer = (LPDIRECTSOUNDBUFFER8)(m_directSoundBuffer8);

	int dsize = (44100 * 2 * 2 * 2) / 2;
	HRESULT hr = lpDSBuffer->Lock(dsize*n, dsize, (LPVOID*)&lpBlockAdd1, &blockSize1, (LPVOID*)&lpBlockAdd2, &blockSize2, 0);
	//error check


	if (blockSize1>0)
	{
		memcpy(lpBlockAdd1, m_blockBuffer, blockSize1);
	}

	if (blockSize2>0)
	{
		memcpy(lpBlockAdd2, m_blockBuffer + blockSize1, blockSize2);
	}


	lpDSBuffer->Unlock(lpBlockAdd1, blockSize1, lpBlockAdd2, blockSize2);
	*/


	if (m_spectrumCalcuMode == 1)
	{
		//4096byte to fft buffer
		if (n == 0)
		{
			memcpy(m_fftBuffer00, blockBuffer, 4408 * 40);
		}
		else
		{
			memcpy(m_fftBuffer0, blockBuffer, 4408 * 40);
		}
	}




	//ÇÃÇ±ÇËÇÇ∏ÇÁÇ∑
	m_nokoriDataSize -= 44100 * 2 * 2;
	if (m_nokoriDataSize < 0) m_nokoriDataSize = 0;

	if (m_nokoriDataSize > 0)
	{
		if (m_xaudio2BufferNumber == 0)
		{
			memmove(m_blockBuffer2, blockBuffer + 44100 * 2 * 2, m_nokoriDataSize);
		}
		else
		{
			memmove(m_blockBuffer, blockBuffer + 44100 * 2 * 2, m_nokoriDataSize);
		}

		//memmove(m_blockBuffer, m_blockBuffer + 44100 * 2 * 2, m_nokoriDataSize);
	}

	m_xaudio2BufferNumber++;
	m_xaudio2BufferNumber %= 2;

	m_bufferBlockNumber = n;

	return dataSize;
}



/*
void CWaveMusicXAudio2::Pause(void)
{
	SetEvent(m_hEvent[PAUSEBGM_COMMAND]);
	WaitForSingleObject(m_hReturnEvent[PAUSEBGM_COMMAND], 10 * 1000);
	ResetEvent(m_hReturnEvent[PAUSEBGM_COMMAND]);
}

void CWaveMusicXAudio2::Resume(void)
{
	//OutputDebugString("resumeCommand");

	SetEvent(m_hEvent[RESUMEBGM_COMMAND]);
	WaitForSingleObject(m_hReturnEvent[RESUMEBGM_COMMAND], 10 * 1000);
	ResetEvent(m_hReturnEvent[RESUMEBGM_COMMAND]);
}

BOOL CWaveMusicXAudio2::CheckPlaying(void)
{
	SetEvent(m_hEvent[CHECKPLAYING_COMMAND]);
	WaitForSingleObject(m_hReturnEvent[CHECKPLAYING_COMMAND], 10 * 1000);
	ResetEvent(m_hReturnEvent[CHECKPLAYING_COMMAND]);
	return m_playFlag;
}

int CWaveMusicXAudio2::GetMusicTime(void)
{
	SetEvent(m_hEvent[GETMUSICTIME_COMMAND]);
	WaitForSingleObject(m_hReturnEvent[GETMUSICTIME_COMMAND], 10 * 1000);
	ResetEvent(m_hReturnEvent[GETMUSICTIME_COMMAND]);
	return m_waveTime;
}
*/





void CWaveMusicXAudio2::SetNormalVolume(void)
{
	int vol = m_volume * 100;

	m_nowVolume = m_volume;

	if (m_sourceVoice)
	{
		float v = (float)vol;
		v *= 0.0001f;

		((IXAudio2SourceVoice*)m_sourceVoice)->SetVolume(v);
	}

	//@@@ change to xaudio
	/*
	LPDIRECTSOUNDBUFFER8 directSoundBuffer = (LPDIRECTSOUNDBUFFER8)(m_directSoundBuffer8);

	int vol = m_volume * 100;

	m_nowVolume = m_volume;

	vol -= 10000;
	directSoundBuffer->SetVolume(vol);
	*/

	//char mes[256];
	//sprintf(mes,"[ch=%d VOL=%d]",m_bufferNumber,m_volume);
	//OutputDebugString(mes);
}


void CWaveMusicXAudio2::SetFadeVolume(void)
{
	//@@@ change to xaudio2

	int dv = m_fadeTime;
	if (dv<1) dv = 1;

	int count = m_fadeCount;
	if (m_fadeTime == 0) count = 1;
	if (count>dv) count = dv;


	int vol = ((m_fadeVolumeEnd - m_fadeVolumeStart) * 100 * count) / dv;
	vol += m_fadeVolumeStart * 100;

	if (vol < 0) vol = 0;
	if (vol > 10000) vol = 10000;

	float v = (float)vol;
	v *= 0.01f;

	((IXAudio2SourceVoice*)m_sourceVoice)->SetVolume(v);


	/*
	LPDIRECTSOUNDBUFFER8 directSoundBuffer = (LPDIRECTSOUNDBUFFER8)(m_directSoundBuffer8);


	int dv = m_fadeTime;
	if (dv<1) dv = 1;

	int count = m_fadeCount;
	if (m_fadeTime == 0) count = 1;
	if (count>dv) count = dv;


	int vol = ((m_fadeVolumeEnd - m_fadeVolumeStart) * 100 * count) / dv;
	vol += m_fadeVolumeStart * 100;

	if (vol < 0) vol = 0;
	if (vol > 10000) vol = 10000;

	vol -= 10000;
	directSoundBuffer->SetVolume(vol);
	*/
}


void CWaveMusicXAudio2::SetFadeInVolume(void)
{
	//@@@ change to xaudio2

	int dv = m_fadeInTime;
	if (dv<1) dv = 1;

	int count = m_fadeInCount;
	if (m_fadeInTime == 0) count = 1;
	if (count>dv) count = dv;

	if (m_fadeInFlag == FALSE)
	{
		count = dv;
	}

	m_nowVolume = (m_volume * count) / dv;

	int vol = (m_volume * 100 * count) / dv;

	float v = (float)vol;
	v *= 0.01f;

	((IXAudio2SourceVoice*)m_sourceVoice)->SetVolume(v);


	/*
	LPDIRECTSOUNDBUFFER8 directSoundBuffer = (LPDIRECTSOUNDBUFFER8)(m_directSoundBuffer8);



	int dv = m_fadeInTime;
	if (dv<1) dv = 1;

	int count = m_fadeInCount;
	if (m_fadeInTime == 0) count = 1;
	if (count>dv) count = dv;

	if (m_fadeInFlag == FALSE)
	{
		count = dv;
	}

	m_nowVolume = (m_volume * count) / dv;

	int vol = (m_volume * 100 * count) / dv;

	//char mes[256];
	//sprintf(mes,"[ch=%d FadeInVol=%d]",m_bufferNumber,vol/100);
	//OutputDebugString(mes);

	vol -= 10000;
	directSoundBuffer->SetVolume(vol);
	*/
}


void CWaveMusicXAudio2::SetFadeOutVolume(void)
{
	//@@@change to xaudio2

	int dv = m_fadeOutTime;
	if (dv<1) dv = 1;

	int count = m_fadeOutCount;
	if (m_fadeOutTime == 0) count = 1;
	if (count>dv) count = dv;

	m_nowVolume = (m_volume * count) / dv;

	int vol = (m_volume * 100 * (dv - count)) / dv;


	float v = (float)vol;
	v *= 0.01f;

	((IXAudio2SourceVoice*)m_sourceVoice)->SetVolume(v);

	/*
	LPDIRECTSOUNDBUFFER8 directSoundBuffer = (LPDIRECTSOUNDBUFFER8)(m_directSoundBuffer8);


	int dv = m_fadeOutTime;
	if (dv<1) dv = 1;

	int count = m_fadeOutCount;
	if (m_fadeOutTime == 0) count = 1;
	if (count>dv) count = dv;

	m_nowVolume = (m_volume * count) / dv;

	int vol = (m_volume * 100 * (dv - count)) / dv;

	//char mes[256];
	//sprintf(mes,"[ch=%d FadeOutVol=%d]",m_bufferNumber,vol/100);
	//OutputDebugString(mes);

	vol -= 10000;
	directSoundBuffer->SetVolume(vol);
	*/

}

/*
BOOL CWaveMusicXAudio2::OpenNewFile(LPSTR filename)
{
	char allfilename[256];
	wsprintf(allfilename, "wgq\\%s.wgq", filename);
	//	memcpy(allfilename,"wgq\\",4);
	//	int ln = strlen(filename);
	//	memcpy(allfilename+4,filename,ln);
	//	memcpy(allfilename+4+ln,".wgq",5);


	m_filePointer = CMyFile::Open(allfilename, "rb");
	//	m_fileHandle = CreateFile(allfilename,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

	if (m_filePointer != NULL)
		//	if (m_fileHandle != INVALID_HANDLE_VALUE)
	{

		//packtypeÇ≈ÇÌÇØÇÈ
		char header[64];
		DWORD readed = 0;
		//ReadFile(m_fileHandle,header,64,&readed,NULL);
		fread(header, sizeof(char), 64, m_filePointer);
		if (header[57] == '2')
		{
			char waveheader[20];
			//	ReadFile(m_fileHandle,waveheader,20,&readed,NULL);
			fread(waveheader, sizeof(char), 20, m_filePointer);

			int* ptr = (int*)waveheader;
			ptr += 4;

			int skp = *ptr;

			//	SetFilePointer(m_fileHandle,skp,NULL,FILE_CURRENT);
			fpos_t nowPos;
			fgetpos(m_filePointer, &nowPos);
			nowPos += skp;
			fsetpos(m_filePointer, &nowPos);

		}


		//		SetFilePointer(m_fileHandle,64,NULL,FILE_BEGIN);

		m_dataEndFlag = FALSE;
		m_oggStreamDecoder->StartDecode2(m_filePointer);
		//		m_oggStreamDecoder->StartDecode2(m_fileHandle);
		return TRUE;
	}

	return FALSE;
}
*/

/*
void CWaveMusicXAudio2::FadeVolume(int vol, int fadeTime)
{
	m_fadeVolumeEnd0 = vol;
	m_fadeTime0 = fadeTime;

	SetEvent(m_hEvent[FADEVOLUME_COMMAND]);
	WaitForSingleObject(m_hReturnEvent[FADEVOLUME_COMMAND], 10 * 1000);
	ResetEvent(m_hReturnEvent[FADEVOLUME_COMMAND]);
}
*/


/*
void CWaveMusicXAudio2::ChangeVolume(int vol)
{
	m_volume0 = vol;

	//	char mes[256];
	//	sprintf(mes,"[COMMAND SETVOLUME %d]",m_volume);
	//	OutputDebugString(mes);

	SetEvent(m_hEvent[SETVOLUME_COMMAND]);
	WaitForSingleObject(m_hReturnEvent[SETVOLUME_COMMAND], 10 * 1000);
	ResetEvent(m_hReturnEvent[SETVOLUME_COMMAND]);

	//	sprintf(mes,"[RETURN SETVOLUME %d]",m_volume);
	//	OutputDebugString(mes);
}
*/

/*
BOOL CWaveMusicXAudio2::GetWaveCut(float* wave, int n, int rightChannel)
{
	if ((m_threadHandle == NULL) || (m_playFlag0 == FALSE) || (m_spectrumCalcuMode == 0))
	{
		for (int i = 0; i<n; i++)
		{
			*(wave) = 0.0f;
		}
		return FALSE;
	}

	SetEvent(m_hEvent[GETFFT_COMMAND]);
	WaitForSingleObject(m_hReturnEvent[GETFFT_COMMAND], 10 * 1000);
	ResetEvent(m_hReturnEvent[GETFFT_COMMAND]);

	short* ptr = (short*)m_fftBuffer;
	ptr += rightChannel;

	float dv = 1.0f / 32768.0f;

	for (int i = 0; i<n; i++)
	{
		*(wave + i) = ((float)(ptr[2 * i])) * dv;
	}

	return TRUE;

}
*/

/*
BOOL CWaveMusicXAudio2::GetWavePlainData(int* wave, int block)
{
	if ((m_threadHandle == NULL) || (m_playFlag0 == FALSE) || (m_spectrumCalcuMode == 0))
	{
		for (int i = 0; i<block; i++)
		{
			*(wave) = 0;
		}
		return FALSE;
	}

	SetEvent(m_hEvent[GETFFT_COMMAND]);
	WaitForSingleObject(m_hReturnEvent[GETFFT_COMMAND], 10 * 1000);
	ResetEvent(m_hReturnEvent[GETFFT_COMMAND]);

	short* ptr = (short*)m_fftBuffer;
	for (int i = 0; i<block; i++)
	{
		*(wave + i) = (int)(ptr[2 * i * (1024 / block)]);
	}

	return TRUE;

}
*/

/*
BOOL CWaveMusicXAudio2::GetFFT(int* fft, int point, int block)
{
	if ((m_threadHandle == NULL) || (m_playFlag0 == FALSE) || (m_spectrumCalcuMode == 0))
	{
		for (int i = 0; i<block; i++)
		{
			*(fft + i) = 0;
		}
		return FALSE;
	}

	SetEvent(m_hEvent[GETFFT_COMMAND]);
	WaitForSingleObject(m_hReturnEvent[GETFFT_COMMAND], 10 * 1000);
	ResetEvent(m_hReturnEvent[GETFFT_COMMAND]);

	//	int tm = GetMusicTime();
	//	tm %= 10;

	//fftåvéZÇÕç≈ëÂ1024pointÇ‹Ç≈


	//volumeÇ‡çló∂Ç∑Ç◊Ç´Ç©Å®FFTÇ…êÍîO

	//dummy routine stereo 44 16bit
	short* ptr = (short*)m_fftBuffer;
	//	ptr += 44100*2*2/2/10*tm;

	for (int i = 0; i<block; i++)
	{
		*(fft + i) = (int)(ptr[2 * i * (1024 / block)]);
	}


	//	memcpy(buffer,m_fftBuffer,4096);
	return TRUE;
}
*/

/*
//handleÇ≈ìØä˙Ç∆ÇÁÇ»Ç≠ÇƒÇ‡ÇæÇ¢Ç∂ÇÂÇ§Ç‘Ç©Ç»
void CWaveMusicXAudio2::StartSpectrum(void)
{
	m_spectrumCalcuMode = 1;
}

void CWaveMusicXAudio2::StopSpectrum(void)
{
	m_spectrumCalcuMode = 0;
}
*/

/*
void CWaveMusicXAudio2::FadeVolumeMain(void)
{
	int vol = m_volume;
	if (m_fadeInFlag)
	{
		vol = m_nowVolume;
	}
	else if (m_fadeOutFlag)
	{
		vol = m_nowVolume;
	}
	else
	{
		//
	}


	m_fadeVolumeStart = vol;
	m_fadeVolumeEnd = m_fadeVolumeEnd0;
	m_fadeInFlag = FALSE;
	m_fadeOutFlag = FALSE;
	m_fadeFlag = TRUE;
	m_fadeTime = m_fadeTime0;
	m_fadeCount = 0;

	m_volume = m_fadeVolumeEnd;
}
*/


