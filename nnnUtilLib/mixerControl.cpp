//
// mixerControl.cpp
//

#include <windows.h>
#include "..\nyanLib\include\commonmacro.h"

#include "mixercontrol.h"

CMixerControl::CMixerControl()
{
	m_mixcerDeviceExist = FALSE;

	m_defaultMIDIVolume = 0;
	m_defaultWAVEVolume = 0;
	m_defaultCDVolume = 0;


	m_midiVolumeExistFlag = FALSE;
	m_waveVolumeExistFlag = FALSE;
	m_cdVolumeExistFlag = FALSE;


       
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

