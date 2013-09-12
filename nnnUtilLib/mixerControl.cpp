//
// mixerControl.cpp
//

#include <windows.h>
#include <Mmdeviceapi.h>
#include <endpointvolume.h>

#include "..\nyanLib\include\commonmacro.h"

#include "mixercontrol.h"


// MIXERLINE_COMPONENTTYPE_DST_SPEAKERS

CMixerControl::CMixerControl(BOOL masterVolumeFlag)
{
	m_masterVolumeFlag = masterVolumeFlag;

	m_mixcerDeviceExist = FALSE;

	m_xp = TRUE;

	OSVERSIONINFO osVersion;
	osVersion.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osVersion);
	if (osVersion.dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		if (osVersion.dwMajorVersion >= 6)
		{
			m_xp = FALSE;
		}
	}


	m_defaultMIDIVolume = 0;
	m_defaultWAVEVolume = 0;
	m_defaultCDVolume = 0;
	m_defaultTotalVolume = 0;


	m_midiVolumeExistFlag = FALSE;
	m_waveVolumeExistFlag = FALSE;
	m_cdVolumeExistFlag = FALSE;
	m_totalVolumeExistFlag = FALSE;


       
	MIXERCAPS mixerCaps;
	
	m_hMixer = NULL;
	
	int mixerMax;


    MIXERCONTROLDETAILS mixerControlDetail;
    MIXERCONTROL mixerControl;
    MIXERLINECONTROLS lineControl;
    MIXERLINE mixerLine;
        
	mixerMax = (int)(mixerGetNumDevs());

	mixerCaps.cDestinations = 0;

	for (int k=0;k<mixerMax;k++)
	{
		ZeroMemory(&mixerCaps,sizeof(mixerCaps));
		mixerGetDevCaps(k,&mixerCaps,sizeof(mixerCaps));
		mixerOpen(&m_hMixer,k,0,0,MIXER_OBJECTF_MIXER);

		int dstNum = mixerCaps.cDestinations;

		for (int j=0;j<dstNum;j++)
		{
			ZeroMemory(&mixerLine,sizeof(mixerLine));
			mixerLine.cbStruct = sizeof(mixerLine);
			mixerLine.dwDestination = j;
			mixerLine.dwSource = 0;

            if(mixerGetLineInfo((HMIXEROBJ)m_hMixer,&mixerLine,MIXER_GETLINEINFOF_DESTINATION | MIXER_OBJECTF_HMIXER) != 0) break;

			int sourceLineMax = mixerLine.cConnections;

			for (int i=0;i<sourceLineMax;i++)
			{
				ZeroMemory(&mixerControlDetail,sizeof(mixerControlDetail));
				ZeroMemory(&mixerControl,sizeof(mixerControl));
				ZeroMemory(&lineControl,sizeof(lineControl));
				ZeroMemory(&mixerLine,sizeof(mixerLine));

				mixerLine.cbStruct = sizeof(mixerLine);
				mixerLine.dwDestination = j;
				mixerLine.dwSource = i;

				if(mixerGetLineInfo((HMIXEROBJ)m_hMixer,&mixerLine,MIXER_GETLINEINFOF_SOURCE | MIXER_OBJECTF_HMIXER) != 0) break;
                                
                lineControl.cbStruct = sizeof(lineControl);
                lineControl.cbmxctrl = sizeof(mixerControl);
                lineControl.dwLineID = mixerLine.dwLineID;
                lineControl.dwControlType = MIXERCONTROL_CT_CLASS_FADER | MIXERCONTROL_CONTROLTYPE_VOLUME;
                lineControl.pamxctrl = &mixerControl;
                lineControl.cControls = 1;
                mixerControl.cbStruct = sizeof(mixerControl);

                mixerGetLineControls((HMIXEROBJ)m_hMixer,&lineControl,MIXER_GETLINECONTROLSF_ONEBYTYPE | MIXER_OBJECTF_HMIXER);
                                

				//2000-06-14
				if(mixerLine.dwComponentType == MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER)
				{
					if (m_midiVolumeExistFlag == FALSE)
					{
						CopyMemory(&m_mixerControlMIDI,&mixerControl,sizeof(mixerControl));
						CopyMemory(&m_mixerLineMIDI,&mixerLine,sizeof(mixerLine));
						m_midiVolumeExistFlag = TRUE;
					}
                }

				//2000-06-14
				if(mixerLine.dwComponentType == MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT)
				{
					if (m_waveVolumeExistFlag == FALSE)
					{
						CopyMemory(&m_mixerControlWAVE,&mixerControl,sizeof(mixerControl));
						CopyMemory(&m_mixerLineWAVE,&mixerLine,sizeof(mixerLine));
						m_waveVolumeExistFlag = TRUE;
					}
                }

				//2002-11-03
				if(mixerLine.dwComponentType == MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC)
				{
					if (m_cdVolumeExistFlag == FALSE)
					{
						CopyMemory(&m_mixerControlCD,&mixerControl,sizeof(mixerControl));
						CopyMemory(&m_mixerLineCD,&mixerLine,sizeof(mixerLine));
						m_cdVolumeExistFlag = TRUE;
					}
                }
				/*
				//2013-08-07
				if(mixerLine.dwComponentType == MIXERLINE_COMPONENTTYPE_DST_SPEAKERS)
				{
					if (m_totalVolumeExistFlag == FALSE)
					{
						CopyMemory(&m_mixerControlTotal,&mixerControl,sizeof(mixerControl));
						CopyMemory(&m_mixerLineTotal,&mixerLine,sizeof(mixerLine));
						m_totalVolumeExistFlag = TRUE;
					}
                }
				*/
			}

			if (m_totalVolumeExistFlag == FALSE)
			{

				ZeroMemory(&mixerLine,sizeof(mixerLine));
				mixerLine.cbStruct = sizeof(mixerLine);
				mixerLine.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
				if (mixerGetLineInfo((HMIXEROBJ)m_hMixer,&mixerLine,MIXER_GETLINEINFOF_COMPONENTTYPE | MIXER_OBJECTF_HMIXER ) == MMSYSERR_NOERROR )
				{
					ZeroMemory(&lineControl,sizeof(lineControl));
	                lineControl.cbStruct = sizeof(lineControl);
					lineControl.dwLineID = mixerLine.dwLineID;
					//lineControl.dwControlType = MIXERCONTROL_CT_CLASS_FADER | MIXERCONTROL_CONTROLTYPE_VOLUME;
					lineControl.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
					lineControl.cControls = 1;
				    lineControl.pamxctrl = &mixerControl;
		            lineControl.cbmxctrl = sizeof(mixerControl);
					if (mixerGetLineControls((HMIXEROBJ)m_hMixer, &lineControl,
						MIXER_GETLINECONTROLSF_ONEBYTYPE | MIXER_OBJECTF_HMIXER) == MMSYSERR_NOERROR)
					{

						CopyMemory(&m_mixerControlTotal,&mixerControl,sizeof(mixerControl));
						CopyMemory(&m_mixerLineTotal,&mixerLine,sizeof(mixerLine));
						m_totalVolumeExistFlag = TRUE;
					}
				}
			}
		}

		mixerClose(m_hMixer);
	}


	if (m_midiVolumeExistFlag)
	{
		m_defaultMIDIVolume = GetMIDIVolume(TRUE);
	}

	if (m_waveVolumeExistFlag)
	{
		m_defaultWAVEVolume = GetWAVEVolume(TRUE);
	}

	if (m_cdVolumeExistFlag)
	{
		m_defaultCDVolume = GetCDVolume(TRUE);
	}

	if (m_totalVolumeExistFlag)
	{
		m_defaultTotalVolume = GetTotalVolume(TRUE);
	}
}


CMixerControl::~CMixerControl()
{
	End();
}

void CMixerControl::End(void)
{
	if (m_midiVolumeExistFlag)
	{
		SetMIDIVolume(m_defaultMIDIVolume,TRUE);
	}

	if (m_waveVolumeExistFlag)
	{
		SetWAVEVolume(m_defaultWAVEVolume,TRUE);
	}

	if (m_cdVolumeExistFlag)
	{
		SetCDVolume(m_defaultCDVolume,TRUE);
	
	}

	if (m_totalVolumeExistFlag)
	{
		SetTotalVolume(m_defaultTotalVolume,TRUE);
	}
}


void CMixerControl::ResetWaveVolume(void)
{
	if (m_waveVolumeExistFlag)
	{
		SetWAVEVolume(m_defaultWAVEVolume,TRUE);
	}
}




int CMixerControl::GetMIDIVolume(BOOL directFlag)
{
	return GetVolume(&m_mixerControlMIDI,&m_mixerLineMIDI,directFlag);
}

int CMixerControl::GetWAVEVolume(BOOL directFlag)
{
	return GetVolume(&m_mixerControlWAVE,&m_mixerLineWAVE,directFlag);
}

int CMixerControl::GetCDVolume(BOOL directFlag)
{
	return GetVolume(&m_mixerControlCD,&m_mixerLineCD,directFlag);
}

int CMixerControl::GetTotalVolume(BOOL directFlag)
{
	return GetVolume(&m_mixerControlTotal,&m_mixerLineTotal,directFlag);
}

void CMixerControl::SetMIDIVolume(int n,BOOL directFlag)
{
	if (m_midiVolumeExistFlag)
	{
		int vol = n;
		if (directFlag == FALSE)
		{
			vol = n * 65535 / 100;
		}

		SetVolume(&m_mixerControlMIDI,&m_mixerLineMIDI,vol);
	}
}

void CMixerControl::SetWAVEVolume(int n,BOOL directFlag)
{
	if (m_waveVolumeExistFlag)
	{
		int vol = n;
		if (directFlag == FALSE)
		{
			vol = n * 65535 / 100;
		}

		SetVolume(&m_mixerControlWAVE,&m_mixerLineWAVE,vol);
	}
}

void CMixerControl::SetCDVolume(int n,BOOL directFlag)
{
	if (m_cdVolumeExistFlag)
	{
		int vol = n;
		if (directFlag == FALSE)
		{
			vol = n * 65535 / 100;
		}

		SetVolume(&m_mixerControlCD,&m_mixerLineCD,vol);
	}
}

void CMixerControl::SetTotalVolume(int n,BOOL directFlag)
{
	if (m_totalVolumeExistFlag)
	{
		int vol = n;
		if (directFlag == FALSE)
		{
			vol = n * 65535 / 100;
		}

		int vol2 = vol;
		if (m_masterVolumeFlag)
		{
			vol2 = SetMasterVolume(vol,TRUE);
		}

		SetVolume(&m_mixerControlTotal,&m_mixerLineTotal,vol2);
//		SetWAVEVolume(n,directFlag);
	}
}

void CMixerControl::SetVolume(MIXERCONTROL* lpMixerControl,MIXERLINE* lpMixerLine, int vol)
{
	MIXERCONTROLDETAILS mixerControlDetail;
	MIXERCONTROLDETAILS_SIGNED* lpMixerControlDetailSigned;

	mixerOpen(&m_hMixer,0,0,0,MIXER_OBJECTF_MIXER);

	mixerControlDetail.cbStruct = sizeof(mixerControlDetail);
	mixerControlDetail.dwControlID = lpMixerControl->dwControlID;
	mixerControlDetail.cMultipleItems = lpMixerControl->cMultipleItems;
	mixerControlDetail.cChannels = lpMixerLine->cChannels;
	mixerControlDetail.cbDetails = sizeof(MIXERCONTROLDETAILS_SIGNED);

	lpMixerControlDetailSigned = (MIXERCONTROLDETAILS_SIGNED*)malloc(sizeof(MIXERCONTROLDETAILS_SIGNED) * mixerControlDetail.cChannels);

	mixerControlDetail.paDetails = lpMixerControlDetailSigned;

	if (lpMixerControlDetailSigned != NULL)
	{
		mixerGetControlDetails((HMIXEROBJ)m_hMixer,&mixerControlDetail,MIXER_OBJECTF_HMIXER | MIXER_GETCONTROLDETAILSF_VALUE);


		for (int i=0;i<(int)(mixerControlDetail.cChannels);i++)
		{
			lpMixerControlDetailSigned[i].lValue = vol;
		}

		mixerSetControlDetails((HMIXEROBJ)m_hMixer,&mixerControlDetail,MIXER_OBJECTF_HMIXER | MIXER_SETCONTROLDETAILSF_VALUE);

		free(lpMixerControlDetailSigned);
	}

	mixerClose(m_hMixer);
}


int CMixerControl::GetVolume(MIXERCONTROL* lpMixerControl,MIXERLINE* lpMixerLine,BOOL directFlag)
{
	MIXERCONTROLDETAILS mixerControlDetail;
	MIXERCONTROLDETAILS_SIGNED* lpMixerControlDetailSigned;

	mixerOpen(&m_hMixer,0,0,0,MIXER_OBJECTF_MIXER);

	mixerControlDetail.cbStruct = sizeof(mixerControlDetail);
	mixerControlDetail.dwControlID = lpMixerControl->dwControlID;
	mixerControlDetail.cMultipleItems = lpMixerControl->cMultipleItems;
	mixerControlDetail.cChannels = lpMixerLine->cChannels;
	mixerControlDetail.cbDetails = sizeof(MIXERCONTROLDETAILS_SIGNED);

	lpMixerControlDetailSigned = (MIXERCONTROLDETAILS_SIGNED*)malloc(sizeof(MIXERCONTROLDETAILS_SIGNED) * mixerControlDetail.cChannels);

	mixerControlDetail.paDetails = lpMixerControlDetailSigned;

	int vol = 0;

	if (lpMixerControlDetailSigned != NULL)
	{
		mixerGetControlDetails((HMIXEROBJ)m_hMixer,&mixerControlDetail,MIXER_OBJECTF_HMIXER | MIXER_GETCONTROLDETAILSF_VALUE);


		for (int i=0;i<(int)(mixerControlDetail.cChannels);i++)
		{
			vol += lpMixerControlDetailSigned[i].lValue;
		}

		vol /= (int)(mixerControlDetail.cChannels);
//		mixerSetControlDetails((HMIXEROBJ)m_hMixer,&mixerControlDetail,MIXER_OBJECTF_HMIXER | MIXER_SETCONTROLDETAILSF_VALUE);

		free(lpMixerControlDetailSigned);
	}

	mixerClose(m_hMixer);

	if (directFlag) return vol;

	return vol * 100 / 65535;
}


int CMixerControl::SetMasterVolume(int vol,BOOL directFlag)
{
	if (m_xp) return vol;//XP!

	if (directFlag == FALSE)
	{
		vol = vol * 65535 / 100;
	}


	HRESULT hr;

	IMMDeviceEnumerator *deviceEnumerator = NULL;
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
	if (hr != S_OK) return vol;


	IMMDevice *defaultDevice = NULL;
	
	hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
	deviceEnumerator->Release();
	deviceEnumerator = NULL;
	if (hr != S_OK) return vol;


	IAudioEndpointVolume *endpointVolume = NULL;
	hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
	defaultDevice->Release();
	defaultDevice = NULL;

	if (hr != S_OK) return vol;


	float masterVolume = 0.0f;
	endpointVolume->GetMasterVolumeLevelScalar(&masterVolume);

	float rangeMin = 0.0f;
	float rangeMax = 1.0f;
	float rangeInc = 1.0f;

	endpointVolume->GetVolumeRange(&rangeMin,&rangeMax,&rangeInc);

	float v = (float)vol;
//	v *= (rangeMax - rangeMin);
	v /= 65535.0f;
//	v += rangeMin;

	if (v > masterVolume)
	{

//		endpointVolume->SetMasterVolumeLevel(v,NULL);
		endpointVolume->SetMasterVolumeLevelScalar(v,NULL);
//		vol = (int)(100.0f * (v - rangeMin) / (rangeMax - rangeMin)*0.5f);
//		vol = (int)(65535.0f*100.0f * (v - rangeMin) / (rangeMax - rangeMin)*0.5f);
//		if (vol<0) vol = 0;
//		if (vol>100) vol = 100;


		vol = 65535;
	}
	else
	{
		if (masterVolume > 0.0f)
		{
			vol = (int)(v * 65535.0f / masterVolume);
			if (vol<0) vol = 0;
			if (vol>65535) vol = 65535;
		}
		else
		{
			vol = 0;
		}
	}


	endpointVolume->Release();

	return vol;
}



/*
HRESULT hr;
 HRESULT mute;
 BOOL muted = false;

CoInitialize(NULL);
 IMMDeviceEnumerator *deviceEnumerator = NULL;
 hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
 IMMDevice *defaultDevice = NULL;

hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
 deviceEnumerator->Release();
 deviceEnumerator = NULL;

IAudioEndpointVolume *endpointVolume = NULL;
 hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
 defaultDevice->Release();
 defaultDevice = NULL;

mute = endpointVolume->GetMute( &muted );

//endpointVolume->SetMute(TRUE, NULL);

endpointVolume->Release();

CoUninitialize();
*/
