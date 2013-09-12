//
// musicPlayer.cpp
//

#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"

#include "..\NyanDirectXLib\myDirectSound.h"

#include "waveData.h"
#include "waveMusic.h"

#include "musicControl.h"

//#include "namelist.h"

#define MYWAVEMUSIC_MODE 2

//CMusicControl::CMusicControl(CNameList* bgmList,CMIDIPlayer* midi, CCDControl* cdControl)
CMusicControl::CMusicControl(CMyDirectSound* lpMyDirectSound)
{
	m_waveMusic[0] = NULL;
	m_waveMusic[1] = NULL;
	m_useWaveMusicNumber = 0;
	m_defaultFadeInTime = 0;
	m_defaultFadeOutTime = 5;
	m_volumeData = 50;

	if (lpMyDirectSound->GetDirectSound() == NULL) return;

	m_waveMusic[0] = new CWaveMusic(lpMyDirectSound->GetDirectSound(),0);
	m_waveMusic[1] = new CWaveMusic(lpMyDirectSound->GetDirectSound(),1);
}

CMusicControl::~CMusicControl()
{
	End();
}


void CMusicControl::End(void)
{
	for (int i=0;i<2;i++)
	{
		ENDDELETECLASS(m_waveMusic[i]);
	}
}



void CMusicControl::PlayMusic(LPSTR filename,int loopCount,int volume,int fadeInTime,int fadeOutTime)
{
	//check music switch

	if (fadeInTime == -1) fadeInTime = m_defaultFadeInTime;
	if (fadeOutTime == -1) fadeOutTime = m_defaultFadeOutTime;

	if (m_waveMusic[m_useWaveMusicNumber] != NULL)
	{
		if (fadeOutTime == 0)
		{
			m_waveMusic[m_useWaveMusicNumber]->StopBGM();
		}
		else
		{
			m_waveMusic[m_useWaveMusicNumber]->StopBGM(TRUE,fadeOutTime);
		}
	}

	m_useWaveMusicNumber++;
	m_useWaveMusicNumber %= 2;

	//start volume set

	if (m_waveMusic[m_useWaveMusicNumber] != NULL)
	{
		m_waveMusic[m_useWaveMusicNumber]->SetStartVolume(volume);
		SetVolumeData(volume);

		if (fadeInTime == 0)
		{
			m_waveMusic[m_useWaveMusicNumber]->PlayBGM(filename,loopCount,FALSE);
		}
		else
		{
			m_waveMusic[m_useWaveMusicNumber]->PlayBGM(filename,loopCount,TRUE,fadeInTime);
		}
	}
}


void CMusicControl::StopMusic(int fadeOutTime)
{
	if (fadeOutTime == -1) fadeOutTime = m_defaultFadeOutTime;

	if (m_waveMusic[m_useWaveMusicNumber] != NULL)
	{
		if (fadeOutTime == 0)
		{
			m_waveMusic[m_useWaveMusicNumber]->StopBGM();
		}
		else
		{
			m_waveMusic[m_useWaveMusicNumber]->StopBGM(TRUE,fadeOutTime);
		}
	}
}


void CMusicControl::ResumeMusic(void)
{
	if (m_waveMusic[m_useWaveMusicNumber] == NULL) return;
	m_waveMusic[m_useWaveMusicNumber]->Resume();
}


void CMusicControl::PauseMusic(void)
{
	if (m_waveMusic[m_useWaveMusicNumber] == NULL) return;
	m_waveMusic[m_useWaveMusicNumber]->Pause();
}



BOOL CMusicControl::CheckPlaying(void)
{
	if (m_waveMusic[m_useWaveMusicNumber] == NULL) return FALSE;
	return m_waveMusic[m_useWaveMusicNumber]->CheckPlaying();
}


void CMusicControl::ChangeVolume(int vol)
{
	if (m_waveMusic[m_useWaveMusicNumber] == NULL) return;
	m_waveMusic[m_useWaveMusicNumber]->ChangeVolume(vol);
	SetVolumeData(vol);
}

void CMusicControl::StartSpectrum(void)
{
	for (int i=0;i<2;i++)
	{
		m_waveMusic[i]->StartSpectrum();
	}
}

void CMusicControl::StopSpectrum(void)
{
	for (int i=0;i<2;i++)
	{
		m_waveMusic[i]->StopSpectrum();
	}
}

BOOL CMusicControl::GetSpectrum(int* spectrum,int block,int point)
{
	return m_waveMusic[m_useWaveMusicNumber]->GetFFT(spectrum,point,block);
}

BOOL CMusicControl::GetWavePlainData(int* wave,int block)
{
	return m_waveMusic[m_useWaveMusicNumber]->GetWavePlainData(wave,block);
}

BOOL CMusicControl::GetWaveCut(float* ar,int n,int rightChannel)
{
	return m_waveMusic[m_useWaveMusicNumber]->GetWaveCut(ar,n,rightChannel);
}

void CMusicControl::FadeVolume(int vol, int fadeTime)
{
	if (m_waveMusic[m_useWaveMusicNumber] == NULL) return;
	m_waveMusic[m_useWaveMusicNumber]->FadeVolume(vol,fadeTime);
	SetVolumeData(vol);
}

void CMusicControl::SetVolumeData(int vol)
{
	m_volumeData = vol;
}

int CMusicControl::GetVolumeData(void)
{
	return m_volumeData;
}

/*_*/

