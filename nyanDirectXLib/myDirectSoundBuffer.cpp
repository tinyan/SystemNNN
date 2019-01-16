//
//
//

#include <windows.h>
#include <dsound.h>

//#include "c:\Program Files\Microsoft DirectX 9.0 SDK (Summer 2004)\include\dsound.h"

#include "myDirectSoundBuffer.h"

CMyDirectSoundBuffer::CMyDirectSoundBuffer(LPVOID lpDirectSound,BOOL sound3DFlag)
{
//MessageBox(NULL,"constractoer","soundbuf",MB_OK);

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

	SetStartTeii(0.0f,0.0f,0.0f);
	SetEndTeii(0.0f,0.0f,0.0f);
	SetMoveTime(0);
	SetDoppler(0);
//	m_playFlag = FALSE;
}


CMyDirectSoundBuffer::~CMyDirectSoundBuffer()
{
	End();
}


void CMyDirectSoundBuffer::End(void)
{
	Stop();

	if (m_directSound3DBuffer != NULL)
	{
		((LPDIRECTSOUND3DBUFFER8)m_directSound3DBuffer)->Release();
		m_directSound3DBuffer = NULL;
	}

	if (m_directSoundBuffer8 != NULL)
	{
		((LPDIRECTSOUNDBUFFER8)m_directSoundBuffer8)->Release();
		m_directSoundBuffer8 = NULL;
	}

	if (m_directSoundBuffer != NULL)
	{
		((LPDIRECTSOUNDBUFFER)m_directSoundBuffer)->Release();
		m_directSoundBuffer = NULL;
	}
}



void CMyDirectSoundBuffer::Play(BOOL loopFlag)
{
//MessageBox(NULL,"play-1","soundbuf",MB_OK);

	if (m_dataExistFlag == FALSE) return;
//MessageBox(NULL,"play-2","soundbuf",MB_OK);
	if (m_directSoundBuffer8 == NULL) return;
//MessageBox(NULL,"play-3","soundbuf",MB_OK);

	Set3DPosition(m_startXYZ[0],m_startXYZ[1],m_startXYZ[2]);
//MessageBox(NULL,"play-4","soundbuf",MB_OK);

//	m_playFlag = TRUE;

	if (loopFlag)
	{
		((LPDIRECTSOUNDBUFFER8)m_directSoundBuffer8)->Play(0,0,DSBPLAY_LOOPING);
	}
	else
	{
		((LPDIRECTSOUNDBUFFER8)m_directSoundBuffer8)->Play(0,0,0);
	}
//MessageBox(NULL,"play-99","soundbuf",MB_OK);

}

void CMyDirectSoundBuffer::Stop(BOOL waitFlag)
{
//MessageBox(NULL,"stop-1","soundbuf",MB_OK);

	if (m_dataExistFlag == FALSE) return;
//MessageBox(NULL,"stop-2","soundbuf",MB_OK);
	if (m_directSoundBuffer8 == NULL) return;
//	if (m_playFlag == FALSE) return;
//MessageBox(NULL,"stop-3","soundbuf",MB_OK);

	((LPDIRECTSOUNDBUFFER8)m_directSoundBuffer8)->Stop();
//	m_playFlag = FALSE;

	if (waitFlag == FALSE) return;

	for (int i=0;i<100;i++)
	{
	//	OutputDebugString(".");
		DWORD st;
		HRESULT hr = ((LPDIRECTSOUNDBUFFER8)m_directSoundBuffer8)->GetStatus(&st);
		if (FAILED(hr))
		{
		//	OutputDebugString("x");
			return;
		}

		if ((st & DSBSTATUS_PLAYING) == 0) return;
	//	OutputDebugString("-");
		Sleep(1);
	}
//MessageBox(NULL,"stop-99","soundbuf",MB_OK);

}


void CMyDirectSoundBuffer::SetVolume(int volume)
{
//MessageBox(NULL,"setvolume-1","soundbuf",MB_OK);

	if (m_directSoundBuffer8 == NULL) return;

	int vol = volume * 100;
	vol -= 10000;
//	if (volume == 0) vol = -10000;

	((LPDIRECTSOUNDBUFFER8)m_directSoundBuffer8)->SetVolume(vol);
//MessageBox(NULL,"setvolume-99","soundbuf",MB_OK);
}


void CMyDirectSoundBuffer::SetVelocity(float speedX,float speedY,float speedZ)
{
	if (m_3DSoundFlag == FALSE) return;

	if (m_directSound3DBuffer == NULL) return;

	((LPDIRECTSOUND3DBUFFER8)m_directSound3DBuffer)->SetVelocity(speedX,speedY,speedZ,DS3D_IMMEDIATE);
}

void CMyDirectSoundBuffer::Set3DPosition(float x,float y,float z)
{
	if (m_3DSoundFlag == FALSE)
	{
		//SET PAN use xy
		if (m_directSoundBuffer8 == NULL) return;

		int pan = (int)(x*100+0.5);

		((LPDIRECTSOUNDBUFFER8)m_directSoundBuffer8)->SetPan(pan);

		return;
	}

	if (m_directSound3DBuffer == NULL) return;

	((LPDIRECTSOUND3DBUFFER8)m_directSound3DBuffer)->SetPosition(x,y,z,DS3D_IMMEDIATE);
}

//loopf flag is dummy for XAudioi2
BOOL CMyDirectSoundBuffer::SetData(char* waveData,int dataSize, int channel,int samplingRate,int samplingBit,BOOL loopFlag)
{
	if (m_directSound == NULL)
	{
		m_dataExistFlag = FALSE;
		return FALSE;
	}

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

	HRESULT hr;

	//再利用不可！！前の音がきえるタイミングで新しい音がけされる！

	//if ((dataSize != m_bufferSize) || (channel != m_channel) || (samplingRate != m_samplingRate) || (samplingBit != m_samplingBit))
	if (1)
	{
		if (m_directSound3DBuffer != NULL)
		{
			((LPDIRECTSOUND3DBUFFER8)m_directSound3DBuffer)->Release();
			m_directSound3DBuffer = NULL;
		}

		if (m_directSoundBuffer8 != NULL)
		{
			((LPDIRECTSOUNDBUFFER8)m_directSoundBuffer8)->Release();
			m_directSoundBuffer8 = NULL;
		}

		if (m_directSoundBuffer != NULL)
		{
			((LPDIRECTSOUNDBUFFER)m_directSoundBuffer)->Release();
			m_directSoundBuffer = NULL;
		}
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
		ZeroMemory(&pcmwf,sizeof(pcmwf));
		pcmwf.cbSize = 0;
		pcmwf.wBitsPerSample = samplingBit;
		pcmwf.wFormatTag = WAVE_FORMAT_PCM;
		pcmwf.nChannels = channel;
		pcmwf.nSamplesPerSec = samplingRate;
		pcmwf.nBlockAlign = (samplingBit / 8) * channel;
		pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;


		DSBUFFERDESC dsbdesc;
		ZeroMemory(&dsbdesc,sizeof(dsbdesc));
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

		LPDIRECTSOUNDBUFFER lp = NULL;

		hr = ((LPDIRECTSOUND8)m_directSound)->CreateSoundBuffer(&dsbdesc,&lp,NULL);
		if (FAILED(hr)) return FALSE;

		LPDIRECTSOUNDBUFFER8 lp8 = NULL;

		lp->QueryInterface(IID_IDirectSoundBuffer8,(void**)&lp8);

		m_directSoundBuffer8 = lp8;

		m_samplingBit = samplingBit;
		m_samplingRate = samplingRate;
		m_channel = channel;
		m_bufferSize = dataSize;


		m_directSoundBuffer = lp;

		if (m_3DSoundFlag)
		{
			//3dbuffer

			hr = lp8->QueryInterface(IID_IDirectSound3DBuffer8,(void**)&m_directSound3DBuffer);
			
			if FAILED(hr)
			{
				//???
			}
		
		}
	}
//MessageBox(NULL,"setdata-4","soundbuf",MB_OK);

	char* ptr1;
	char* ptr2;
	DWORD sz1,sz2;

	LPDIRECTSOUNDBUFFER8 lp2 = (LPDIRECTSOUNDBUFFER8)m_directSoundBuffer8;


	hr = lp2->Lock(0,dataSize,(void**)&ptr1,&sz1,(void**)&ptr2,&sz2,DSBLOCK_FROMWRITECURSOR);
	if (hr == DSERR_BUFFERLOST)
	{
		lp2->Restore();
		hr = lp2->Lock(0,dataSize,(void**)&ptr1,&sz1,(void**)&ptr2,&sz2,DSBLOCK_FROMWRITECURSOR);
	}

	if (hr != DS_OK)
	{
OutputDebugString("cant lock!!!");
		return FALSE;
	}
//MessageBox(NULL,"setdata-5","soundbuf",MB_OK);

	if (sz1>0) memcpy(ptr1,waveData,sz1);
	if (sz2>0) memcpy(ptr2,waveData+sz1,sz2);

	lp2->Unlock(ptr1,sz1,ptr2,sz2);
	m_dataExistFlag = TRUE;


	SetStartTeii(0.0f,0.0f,0.0f);
	SetEndTeii(0.0f,0.0f,0.0f);
	SetMoveTime(0);
	SetDoppler(0);

	if (m_3DSoundFlag)
	{
		Set3DPosition(0.0f,0.0f,0.0f);
		SetVelocity(0.0f,0.0f,0.0f);
	}
	else
	{
		lp2->SetPan(0);
	}
//MessageBox(NULL,"setdata-6","soundbuf",MB_OK);


	return TRUE;
}


void CMyDirectSoundBuffer::SetStartTeii(float fx,float fy,float fz)
{
	m_startXYZ[0] = fx;
	m_startXYZ[1] = fy;
	m_startXYZ[2] = fz;
}


void CMyDirectSoundBuffer::SetEndTeii(float fx,float fy,float fz)
{
	m_endXYZ[0] = fx;
	m_endXYZ[1] = fy;
	m_endXYZ[2] = fz;
}

void CMyDirectSoundBuffer::SetMoveTime(int tm)
{
	m_moveTime = tm;
}

void CMyDirectSoundBuffer::SetDoppler(int dop)
{
	m_doppler = dop;
}


/*_*/


