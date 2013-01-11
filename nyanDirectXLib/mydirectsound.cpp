//
// mydirectsound.cpp
//

#include <windows.h>
#include "..\nyanlib\include\commonmacro.h"


////#define DIRECTSOUND_VERSION 0x0700 ->9.00
//#include "c:\Program Files\Microsoft DirectX 9.0 SDK (Summer 2004)\include\dsound.h"
#include <dsound.h>

#include "mydirectsound.h"


CMyDirectSound::CMyDirectSound(HWND hwnd)
{
	m_hWnd = hwnd;

	m_lpDirectSound = NULL;
	m_lpPrimaryBuffer = NULL;

	m_primaryChannel = 1;
	m_primarySampleRate = 22050;
	m_primaryBit = 16;

	for (int i=0;i<DSOUND_BUFFER_KOSUU;i++)
	{
		m_lpDirectSoundBuffer[i] = NULL;
	}
//	m_lpDirectSoundBufferForStream = NULL;

	m_vol = 0;

	m_3dSoundFlag = TRUE;	//default

	m_lpListener = NULL;
//	for (i=0;i<SYSTEMSOUND_BUFFER_KOSUU;i++)
//	{
//		m_lpDirectSoundBufferForSystem[i] = NULL;
//		m_systemSoundExistFlag[i] = FALSE;
//	}

}


CMyDirectSound::~CMyDirectSound()
{
	End();
}


void CMyDirectSound::End(void)
{
	// stop sound
	for (int i=0;i<DSOUND_BUFFER_KOSUU;i++)
	{
		LPDIRECTSOUNDBUFFER lp = (LPDIRECTSOUNDBUFFER)(m_lpDirectSoundBuffer[i]);
		if (lp != NULL)
		{
			lp->Stop();
		}
	}

//	if (m_lpDirectSoundBufferForStream != NULL)
//	{
//		m_lpDirectSoundBufferForStream->Stop();
//	}

//	for (i=0;i<SYSTEMSOUND_BUFFER_KOSUU;i++)
//	{
//		LPDIRECTSOUNDBUFFER lp = m_lpDirectSoundBufferForSystem[i];
//		if (lp != NULL)
//		{
//			lp->Stop();
//		}
//		m_systemSoundExistFlag[i] = FALSE;
//	}


	//release object
	for (int i=0;i<DSOUND_BUFFER_KOSUU;i++)
	{
		LPDIRECTSOUNDBUFFER lp = (LPDIRECTSOUNDBUFFER)(m_lpDirectSoundBuffer[i]);
		if (lp != NULL)
		{
			lp->Release();
			m_lpDirectSoundBuffer[i] = NULL;
		}
	}

//	if (m_lpDirectSoundBufferForStream != NULL)
//	{
//		ENDRELEASE(m_lpDirectSoundBufferForStream);
//	}

//	for (i=0;i<SYSTEMSOUND_BUFFER_KOSUU;i++)
//	{
//		ENDRELEASE(m_lpDirectSoundBufferForSystem[i]);
//	}

	if (m_lpListener != NULL)
	{
		((LPDIRECTSOUND3DLISTENER8)m_lpListener)->Release();
		m_lpListener = NULL;
	}

	if (m_lpPrimaryBuffer != NULL)
	{
		((LPDIRECTSOUNDBUFFER)m_lpPrimaryBuffer)->Release();
		m_lpPrimaryBuffer = NULL;
	}

	if (m_lpDirectSound != NULL)
	{
		((LPDIRECTSOUND8)m_lpDirectSound)->Release();
		m_lpDirectSound = NULL;
	}
//	ENDRELEASE(((LPDIRECTSOUNDBUFFER)m_lpPrimaryBuffer));
//	ENDRELEASE(((LPDIRECTSOUND)m_lpDirectSound));
}




void CMyDirectSound::Start(BOOL formatSetFlag)
{
	LPDIRECTSOUND8 lpDirectSound = NULL;
//MessageBox(NULL,"start-1","directsound",MB_OK);
	if (m_lpDirectSound != NULL) return;
//MessageBox(NULL,"start-2","directsound",MB_OK);

	HRESULT hr = DirectSoundCreate8(NULL,&lpDirectSound,NULL);
	if (hr != DS_OK)
	{
//MessageBox(NULL,"start-exit3","directsound",MB_OK);
		return;
	}
//MessageBox(NULL,"start-3","directsound",MB_OK);

	m_lpDirectSound = lpDirectSound;

	hr = lpDirectSound->SetCooperativeLevel(m_hWnd,DSSCL_PRIORITY);
	if (hr != DS_OK) return;
//MessageBox(NULL,"start-4","directsound",MB_OK);

	//make primary

	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc,sizeof(dsbdesc));
	dsbdesc.dwSize = sizeof(dsbdesc);
	dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_PRIMARYBUFFER;

	if (m_3dSoundFlag)
	{
		dsbdesc.dwFlags |= DSBCAPS_CTRL3D;
	}
	else
	{
		dsbdesc.dwFlags |= DSBCAPS_CTRLPAN;
	}

	dsbdesc.dwBufferBytes = 0;
	dsbdesc.lpwfxFormat = NULL;

	LPDIRECTSOUNDBUFFER lpPrimaryBuffer = NULL;

	hr = lpDirectSound->CreateSoundBuffer(&dsbdesc,&lpPrimaryBuffer,NULL);
	if (FAILED(hr))
	{
		if (m_3dSoundFlag)
		{
			m_3dSoundFlag = FALSE;
			dsbdesc.dwFlags &= (~DSBCAPS_CTRL3D);
			dsbdesc.dwFlags |= DSBCAPS_CTRLPAN;

			hr = lpDirectSound->CreateSoundBuffer(&dsbdesc,&lpPrimaryBuffer,NULL);
			if (FAILED(hr)) return;
		}
		else
		{
			return;
		}
	}
//MessageBox(NULL,"start-5","directsound",MB_OK);

	m_lpPrimaryBuffer = lpPrimaryBuffer;

	WAVEFORMATEX pcmwf;
	ZeroMemory(&pcmwf,sizeof(pcmwf));
	pcmwf.cbSize = 0;
	pcmwf.wBitsPerSample = m_primaryBit;
	pcmwf.wFormatTag = WAVE_FORMAT_PCM;
	pcmwf.nChannels = m_primaryChannel;
	pcmwf.nSamplesPerSec = m_primarySampleRate;
	pcmwf.nBlockAlign = (m_primaryBit / 8) * m_primaryChannel;
	pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;

	if (formatSetFlag) lpPrimaryBuffer->SetFormat(&pcmwf);

	//if error,low down



	if (m_3dSoundFlag)
	{
		hr = lpPrimaryBuffer->QueryInterface(IID_IDirectSound3DListener8,(void**)&m_lpListener);
		if (FAILED(hr))
		{
			MessageBox(m_hWnd,"DirectSound3Dリスナーの作成に失敗しました","ERROR",MB_OK | MB_ICONSTOP);
		}

		LPDIRECTSOUND3DLISTENER8 lpListener = (LPDIRECTSOUND3DLISTENER8)m_lpListener;

		lpListener->SetPosition(0.0f, 0.0f, 0.0f, DS3D_IMMEDIATE);
		lpListener->SetVelocity(0.0f, 0.0f, 0.0f, DS3D_IMMEDIATE);

		lpListener->SetOrientation(0.0f, 0.0f, 1.0f, 0.0f,1.0f,0.0f, DS3D_IMMEDIATE);
//		lpListener->SetOrientation(1.0f, 0.0f, 0.0f, 0.0f,1.0f,0.0f, DS3D_IMMEDIATE);

		//ドップラーノーマル
		//距離ノーマル
	}



	m_nowSoundNumber = 0;


/*


	//stream
//	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc,sizeof(dsbdesc));
	dsbdesc.dwSize = sizeof(dsbdesc);
	dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER;
	dsbdesc.dwBufferBytes = 1024*128*2;	//128*2


//	WAVEFORMATEX pcmwf;
	ZeroMemory(&pcmwf,sizeof(pcmwf));
	pcmwf.cbSize = 0;
	pcmwf.wBitsPerSample = 16;
	pcmwf.wFormatTag = WAVE_FORMAT_PCM;
	pcmwf.nChannels = 1;
	pcmwf.nSamplesPerSec = 22050;//44100;
	pcmwf.nBlockAlign = 2;
	pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;

	dsbdesc.lpwfxFormat = &pcmwf;

	hr = m_lpDirectSound->CreateSoundBuffer(&dsbdesc,&m_lpDirectSoundBufferForStream,NULL);
	if (hr != DS_OK) return;	//error

  */

//MessageBox(NULL,"start-99","directsound",MB_OK);

}


//LPDIRECTSOUND CMyDirectSound::GetDirectSound(void)
LPVOID CMyDirectSound::GetDirectSound(void)
{
	return m_lpDirectSound;
}


//削除よてい

BOOL CMyDirectSound::Play(char* waveData, int waveSize)
{
	if (m_lpDirectSound == NULL) return FALSE;

	LPDIRECTSOUNDBUFFER lp = (LPDIRECTSOUNDBUFFER)(m_lpDirectSoundBuffer[m_nowSoundNumber]);
	if (lp != NULL)
	{
		lp->Stop();
		lp->Release();
		m_lpDirectSoundBuffer[m_nowSoundNumber] = NULL;
	}

	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc,sizeof(dsbdesc));
	dsbdesc.dwSize = sizeof(dsbdesc);
	dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER;
	dsbdesc.dwBufferBytes = waveSize;


	WAVEFORMATEX pcmwf;
	ZeroMemory(&pcmwf,sizeof(pcmwf));
	pcmwf.cbSize = 0;
	pcmwf.wBitsPerSample = 16;
	pcmwf.wFormatTag = WAVE_FORMAT_PCM;
	pcmwf.nChannels = 1;
	pcmwf.nSamplesPerSec = 22050 * 1;
	pcmwf.nBlockAlign = 2;
	pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;

	dsbdesc.lpwfxFormat = &pcmwf;

	HRESULT hr = ((LPDIRECTSOUND8)m_lpDirectSound)->CreateSoundBuffer(&dsbdesc,&lp,NULL);
	if (hr != DS_OK) return FALSE;
	if (lp == NULL) return FALSE;

	m_lpDirectSoundBuffer[m_nowSoundNumber] = lp;

//	if (waveSize> 4 * 22050) waveSize = 22050;
//	LPDIRECTSOUNDBUFFER lp = m_lpDirectSoundBuffer[m_nowSoundNumber];

	char* ptr1;
	char* ptr2;
	DWORD sz1,sz2;

	hr = lp->Lock(0,waveSize,(void**)&ptr1,&sz1,(void**)&ptr2,&sz2,DSBLOCK_FROMWRITECURSOR);
	if (hr == DSERR_BUFFERLOST)
	{
		lp->Restore();
		hr = lp->Lock(0,waveSize,(void**)&ptr1,&sz1,(void**)&ptr2,&sz2,DSBLOCK_FROMWRITECURSOR);
	}

	if (hr != DS_OK) return FALSE;

	if (sz1>0) memcpy(ptr1,waveData,sz1);
	if (sz2>0) memcpy(ptr2,waveData+sz1,sz2);

	lp->Unlock(ptr1,sz1,ptr2,sz2);
	lp->SetVolume(m_vol);
//	lp->SetCurrentPosition(0);
	lp->Play(0,0,0);

	m_nowSoundNumber++;
	m_nowSoundNumber %= DSOUND_BUFFER_KOSUU;
	return TRUE;
}

/*
BOOL CMyDirectSound::SetSystemSound(int n, char* waveData, int waveSize)
{
	return FALSE;

//	if ((n<0) || (n>=SYSTEMSOUND_BUFFER_KOSUU)) return FALSE;
//	if (m_lpDirectSound == NULL) return FALSE;
//	LPDIRECTSOUNDBUFFER lp = m_lpDirectSoundBufferForSystem[n];
//	if (lp == NULL) return FALSE;

//	m_systemSoundExistFlag[n] = TRUE;
//	return TRUE;
}
*/

/*
BOOL CMyDirectSound::PlaySystemSound(int n)
{
	return FALSE;

//	if ((n<0) || (n>=SYSTEMSOUND_BUFFER_KOSUU)) return FALSE;
//	if (m_lpDirectSound == NULL) return FALSE;
//	LPDIRECTSOUNDBUFFER lp = m_lpDirectSoundBufferForSystem[n];
//	if (lp == NULL) return FALSE;
//	if (m_systemSoundExistFlag[n] == FALSE) return FALSE;

//	lp->SetCurrentPosition(0);
//	lp->Play(0,0,0);
//	return TRUE;
}
*/

void CMyDirectSound::SetVolume(int vol)
{
	if (m_lpDirectSound == NULL) return;

	int volume = (vol - 100 ) * 100;
	if (vol == 0)
	{
		volume = -10000;
	}

//	if (m_lpPrimaryBuffer != NULL) m_lpPrimaryBuffer->SetVolume(volume);
	m_vol = volume;
}

void CMyDirectSound::Stop(void)
{
	if (m_lpDirectSound == NULL) return;

	for (int i=0;i<DSOUND_BUFFER_KOSUU;i++)
	{
		if (m_lpDirectSoundBuffer[i] != NULL)
		{
			((LPDIRECTSOUNDBUFFER)m_lpDirectSoundBuffer[i])->Stop();
		}
	}


}

/*
BOOL CMyDirectSound::StartStream(char* waveData, int startBlockSize)
{
	if (m_lpDirectSound == NULL) return FALSE;

	LPDIRECTSOUNDBUFFER lp = m_lpDirectSoundBufferForStream;
	if (lp == NULL) return FALSE;

	lp->Stop();

	char* ptr1;
	char* ptr2;
	DWORD sz1,sz2;

	HRESULT hr = lp->Lock(0,startBlockSize,(void**)&ptr1,&sz1,(void**)&ptr2,&sz2,DSBLOCK_FROMWRITECURSOR);
	if (hr == DSERR_BUFFERLOST)
	{
		lp->Restore();
		hr = lp->Lock(0,startBlockSize,(void**)&ptr1,&sz1,(void**)&ptr2,&sz2,DSBLOCK_FROMWRITECURSOR);
	}

	if (hr != DS_OK) return FALSE;

	if (sz1>0) memcpy(ptr1,waveData,sz1);
	if (sz2>0) memcpy(ptr2,waveData+sz1,sz2);

	lp->Unlock(ptr1,sz1,ptr2,sz2);
	lp->SetVolume(m_vol);
	lp->Play(0,0,DSBPLAY_LOOPING);

	m_streamBlockNumber = 0;

	return TRUE;
}


BOOL CMyDirectSound::NextStream(char* waveData, int blockSize)
{
	if (m_lpDirectSound == NULL) return FALSE;

	LPDIRECTSOUNDBUFFER lp = m_lpDirectSoundBufferForStream;
	if (lp == NULL) return FALSE;

	m_streamBlockNumber++;

	int st = m_streamBlockNumber % 2;

	char* ptr1;
	char* ptr2;
	DWORD sz1,sz2;

	HRESULT hr = lp->Lock(st*1024*128,blockSize,(void**)&ptr1,&sz1,(void**)&ptr2,&sz2,DSBLOCK_FROMWRITECURSOR);
	if (hr == DSERR_BUFFERLOST)
	{
		lp->Restore();
		hr = lp->Lock(st*1024*128,blockSize,(void**)&ptr1,&sz1,(void**)&ptr2,&sz2,DSBLOCK_FROMWRITECURSOR);
	}

	if (hr != DS_OK) return FALSE;

	if (sz1>0) memcpy(ptr1,waveData,sz1);
	if (sz2>0) memcpy(ptr2,waveData+sz1,sz2);

	lp->Unlock(ptr1,sz1,ptr2,sz2);

	return TRUE;
}

BOOL CMyDirectSound::StopStream(void)
{
	if (m_lpDirectSound == NULL) return FALSE;

	LPDIRECTSOUNDBUFFER lp = m_lpDirectSoundBufferForStream;
	if (lp == NULL) return FALSE;

	lp->Stop();

	return TRUE;
}
*/

/*
int CMyDirectSound::GetCurrentPosition(void)
{
	if (m_lpDirectSound == NULL) return -1;
	if (m_lpDirectSoundBufferForStream == NULL) return -1;

	
	DWORD pos1;
	DWORD pos2;

	m_lpDirectSoundBufferForStream->GetCurrentPosition(&pos1,&pos2);

	return pos1;
}
*/


void CMyDirectSound::SetPrimaryFormat(int channel,int sampleRate,int bit)
{
	m_primaryChannel = channel;
	m_primarySampleRate = sampleRate;
	m_primaryBit = bit;
}

void CMyDirectSound::SetPrimaryVolume(int volume)
{
	if (m_lpPrimaryBuffer != NULL)
	{
		int vol = volume * 100;
		vol -= 10000;

		if (volume == 0)
		{
			vol = -10000;
		}

		((LPDIRECTSOUNDBUFFER)m_lpPrimaryBuffer)->SetVolume(vol);
	}
}

void CMyDirectSound::Set3DSoundFlag(BOOL flg)
{
	m_3dSoundFlag = flg;
}

BOOL CMyDirectSound::Check3DSoundOk(void)
{
	if (m_3dSoundFlag) return TRUE;
	return FALSE;
}


//
// not use this callback routine
//
BOOL CALLBACK CMyDirectSound::DSEnumCallback(LPGUID lpGuid,LPCSTR lpcstrDescription,LPCSTR lpcstrModule,LPVOID lpContext)
{

	return FALSE;
}



