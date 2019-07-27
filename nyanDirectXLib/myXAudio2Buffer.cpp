//
//
//

#include <windows.h>
#include <stdio.h>
#include <dsound.h>
#include <xaudio2.h>

//#include "c:\Program Files\Microsoft DirectX 9.0 SDK (Summer 2004)\include\dsound.h"

#include "myDirectSoundBuffer.h"
#include "myXAudio2Buffer.h"

CMyXAudio2Buffer::CMyXAudio2Buffer(LPVOID lpXAudio2, BOOL sound3DFlag) : CMyDirectSoundBuffer(NULL,sound3DFlag)

{
	//MessageBox(NULL,"constractoer","soundbuf",MB_OK);


	m_xAudio2 = lpXAudio2;

	m_inBufferSize = 1024 * 1024 * 2;
	m_inBuffer = new char[m_inBufferSize];

	/*
	m_directSound = lpDirectSound;
	m_directSoundBuffer = NULL;
	m_directSoundBuffer8 = NULL;
	m_directSound3DBuffer = NULL;

	m_bufferSize = 0;
	m_channel = 0;
	m_samplingRate = 0;
	m_samplingBit = 0;

	m_3DSoundFlag = sound3DFlag;
	m_dataExistFlag = FALSE;

	SetStartTeii(0.0f, 0.0f, 0.0f);
	SetEndTeii(0.0f, 0.0f, 0.0f);
	SetMoveTime(0);
	SetDoppler(0);
	*/

	//	m_playFlag = FALSE;
}


CMyXAudio2Buffer::~CMyXAudio2Buffer()
{
	End();
}


void CMyXAudio2Buffer::End(void)
{
	Stop();

//	if (m_directSound3DBuffer != NULL)
//	{
//		((LPDIRECTSOUND3DBUFFER8)m_directSound3DBuffer)->Release();
//		m_directSound3DBuffer = NULL;
//	}

	//if (m_directSoundBuffer8 != NULL)
	//{
//		((LPDIRECTSOUNDBUFFER8)m_directSoundBuffer8)->Release();
//		m_directSoundBuffer8 = NULL;
//	}

	if (m_directSoundBuffer8 != NULL)
	{
		//@@@@@@@@@@((IXAudio2SourceVoice*)m_directSoundBuffer8)->DestroyVoice();


	//	((LPDIRECTSOUNDBUFFER)m_directSoundBuffer)->Release();
		m_directSoundBuffer8 = NULL;
	}

	if (m_inBuffer)
	{
		delete[] m_inBuffer;
		m_inBuffer = nullptr;
		m_bufferSize = 0;
	}
}



void CMyXAudio2Buffer::Play(BOOL loopFlag)
{
	if (m_dataExistFlag == FALSE) return;
	if (m_directSoundBuffer8 == NULL) return;
	Set3DPosition(m_startXYZ[0], m_startXYZ[1], m_startXYZ[2]);


	if (loopFlag)
	{
		
		((IXAudio2SourceVoice*)m_directSoundBuffer8)->Start(0, 0);
	}
	else
	{
		((IXAudio2SourceVoice*)m_directSoundBuffer8)->Start(0, 0);
	}
}

void CMyXAudio2Buffer::Stop(BOOL waitFlag)
{
	if (m_dataExistFlag == FALSE) return;
	if (m_directSoundBuffer8 == NULL) return;

	((IXAudio2SourceVoice*)m_directSoundBuffer8)->Stop();

	if (waitFlag == FALSE) return;

	for (int i = 0; i<100; i++)
	{
		XAUDIO2_VOICE_STATE st;
		((IXAudio2SourceVoice*)m_directSoundBuffer8)->GetState(&st, 0);


//		if (st & hoge)
		{
			return;
		}
		return;

//		if ((st & DSBSTATUS_PLAYING) == 0) return;
//		//	OutputDebugString("-");
//		Sleep(1);
	}
	//MessageBox(NULL,"stop-99","soundbuf",MB_OK);

}


void CMyXAudio2Buffer::SetVolume(int volume)
{

	if (m_directSoundBuffer8 == NULL) return;

	float vol = (float)volume;
	vol *= 0.01f;

	((IXAudio2SourceVoice*)m_directSoundBuffer8)->SetVolume(vol);

}


void CMyXAudio2Buffer::SetVelocity(float speedX, float speedY, float speedZ)
{
	if (m_3DSoundFlag == FALSE) return;

//	if (m_directSound3DBuffer == NULL) return;

//	((LPDIRECTSOUND3DBUFFER8)m_directSound3DBuffer)->SetVelocity(speedX, speedY, speedZ, DS3D_IMMEDIATE);
}

void CMyXAudio2Buffer::Set3DPosition(float x, float y, float z)
{
	if (m_3DSoundFlag == FALSE)
	{
		//SET PAN use xy
		if (m_directSoundBuffer8 == NULL) return;

		int pan = (int)(x * 100 + 0.5);

//		((LPDIRECTSOUNDBUFFER8)m_directSoundBuffer8)->SetPan(pan);

		return;
	}

	if (m_directSound3DBuffer == NULL) return;

//	((LPDIRECTSOUND3DBUFFER8)m_directSound3DBuffer)->SetPosition(x, y, z, DS3D_IMMEDIATE);
}


BOOL CMyXAudio2Buffer::SetData(char* waveData, int dataSize, int channel, int samplingRate, int samplingBit,BOOL loopFlag)
{
	if (m_xAudio2 == NULL)
	{
		m_dataExistFlag = FALSE;
		return FALSE;
	}


	if (m_bufferSize < dataSize)
	{
		if (m_inBuffer)
		{
			delete[] m_inBuffer;
		}
		m_bufferSize = dataSize;
		m_inBuffer = new char[m_bufferSize];
	}

	memcpy(m_inBuffer, waveData, dataSize);


//	char mes[256];
	//sprintf_s(mes, 256, "\n size=%d loop=%d", dataSize,loopFlag);
	//OutputDebugString(mes);

//	if (m_directSound == NULL)
//	{
//		m_dataExistFlag = FALSE;
//		return FALSE;
//	}

	//MessageBox(NULL,"setdata-1","soundbuf",MB_OK);
	//same rate,bit,channel,size then no re-create buffer

	//4n +1,+2,+3の場合のみ、さいずをけずる。アクセラレータなしだと、おかしくなるのを回避するため
	//	int amari = dataSize & 0x1fff;
	int amari = dataSize & 3;
	//	if ((amari >= 1) && (amari <= 3))
	if (amari != 0)
	{
		dataSize &= 0x7ffffffc;
	}

	//MessageBox(NULL,"setdata-2","soundbuf",MB_OK);

	Stop();
	//MessageBox(NULL,"setdata-3","soundbuf",MB_OK);

//	HRESULT hr;

	//再利用不可！！前の音がきえるタイミングで新しい音がけされる！

	//if ((dataSize != m_bufferSize) || (channel != m_channel) || (samplingRate != m_samplingRate) || (samplingBit != m_samplingBit))
	if (1)
	{
		//		if (m_directSound3DBuffer != NULL)
		//		{
		//			((LPDIRECTSOUND3DBUFFER8)m_directSound3DBuffer)->Release();
		//			m_directSound3DBuffer = NULL;
		//		}

		if (m_directSoundBuffer8 != NULL)
		{
			//@@@@@@@@@@@@@@@@@((IXAudio2SourceVoice*)m_directSoundBuffer8)->DestroyVoice();
			m_directSoundBuffer8 = NULL;
		}

		//		if (m_directSoundBuffer != NULL)
		//		{
		//			((LPDIRECTSOUNDBUFFER)m_directSoundBuffer)->Release();
		//			m_directSoundBuffer = NULL;
		//		}
		m_dataExistFlag = FALSE;

		//create


		/*
		WAVEFORMATEX pcmwf;
		ZeroMemory(&pcmwf,sizeof(pcmwf));
		pcmwf.cbSize = sizeof(pcmwf);
		pcmwf.wBitsPerSample = 16;
		pcmwf.wFormatTag = WAVE_FORMAT_PCM;
		pcmwf.nChannels = 2;
		pcmwf.nSamplesPerSec = 44100;
		pcmwf.nBlockAlign = 4;
		pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;

		DSBUFFERDESC dsbdesc;
		ZeroMemory(&dsbdesc,sizeof(dsbdesc));
		dsbdesc.dwSize = sizeof(dsbdesc);
		dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLPOSITIONNOTIFY;
		//	dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER | DSBCAPS_CTRLPOSITIONNOTIFY;
		dsbdesc.dwBufferBytes = pcmwf.nAvgBytesPerSec * 2;
		dsbdesc.lpwfxFormat = &pcmwf;

		*/

		WAVEFORMATEX pcmwf;
		ZeroMemory(&pcmwf, sizeof(pcmwf));
		pcmwf.cbSize = 0;
		pcmwf.wBitsPerSample = samplingBit;
		pcmwf.wFormatTag = WAVE_FORMAT_PCM;
		pcmwf.nChannels = channel;
		pcmwf.nSamplesPerSec = samplingRate;
		pcmwf.nBlockAlign = (samplingBit / 8) * channel;
		pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;

		/*
		DSBUFFERDESC dsbdesc;
		ZeroMemory(&dsbdesc, sizeof(dsbdesc));
		dsbdesc.dwSize = sizeof(dsbdesc);
		dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCSOFTWARE;
		//		dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER;
		if (m_3DSoundFlag)
		{
			dsbdesc.dwFlags |= DSBCAPS_CTRL3D;
		}
		else
		{
			dsbdesc.dwFlags |= DSBCAPS_CTRLPAN;
		}

		dsbdesc.dwBufferBytes = dataSize;


		dsbdesc.lpwfxFormat = &pcmwf;
		*/


		IXAudio2SourceVoice* sourceVoice;

		HRESULT hr = ((IXAudio2*)m_xAudio2)->CreateSourceVoice(&sourceVoice, &pcmwf, 0, XAUDIO2_DEFAULT_FREQ_RATIO, NULL, NULL, NULL);

		if (FAILED(hr))
		{
			OutputDebugString("Error XAudio2 CreateSourceVoice\n");
			return FALSE;


		}
		m_directSoundBuffer8 = sourceVoice;


		XAUDIO2_BUFFER buffer = { 0 };


		buffer.AudioBytes = dataSize;

//		buffer.pAudioData = (const BYTE*)waveData;
		buffer.pAudioData = (const BYTE*)m_inBuffer;

		if (loopFlag)
		{
			buffer.Flags = XAUDIO2_END_OF_STREAM;
			buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
		}
		else
		{
			buffer.Flags = XAUDIO2_END_OF_STREAM;
		}

		//sourceVoice->FlushSourceBuffers();
		hr = sourceVoice->SubmitSourceBuffer(&buffer);
		if (FAILED(hr))
		{
			OutputDebugString("Error XAudio2 SubmitSourceBuffer\n");
			return FALSE;
		}

		//@@@@@@@@@@@@@@@@@@@sourceVoice->SetVolume(m_vol);
//		sourceVoice->Start(0, XAUDIO2_COMMIT_NOW);





		m_dataExistFlag = TRUE;


		SetStartTeii(0.0f, 0.0f, 0.0f);
		SetEndTeii(0.0f, 0.0f, 0.0f);
		SetMoveTime(0);
		SetDoppler(0);

		if (m_3DSoundFlag)
		{
			//		Set3DPosition(0.0f, 0.0f, 0.0f);
			//		SetVelocity(0.0f, 0.0f, 0.0f);
		}
		else
		{
			//		lp2->SetPan(0);
		}
		//MessageBox(NULL,"setdata-6","soundbuf",MB_OK);

	}
	return TRUE;
}

/*
void CMyXAudio2Buffer::SetStartTeii(float fx, float fy, float fz)
{
	m_startXYZ[0] = fx;
	m_startXYZ[1] = fy;
	m_startXYZ[2] = fz;
}


void CMyXAudio2Buffer::SetEndTeii(float fx, float fy, float fz)
{
	m_endXYZ[0] = fx;
	m_endXYZ[1] = fy;
	m_endXYZ[2] = fz;
}

void CMyXAudio2Buffer::SetMoveTime(int tm)
{
	m_moveTime = tm;
}

void CMyXAudio2Buffer::SetDoppler(int dop)
{
	m_doppler = dop;
}
*/


/*_*/


