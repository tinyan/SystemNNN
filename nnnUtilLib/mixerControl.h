//
// mixerControl.h
//

#if !defined __TINYAN_NNNUTILIB_MIXERCONTROL__
#define __TINYAN_NNNUTILLIB_MIXERCONTROL__

#include <mmsystem.h>

class CMixerControl
{
public:
	CMixerControl(BOOL masterVolume);
	~CMixerControl();
	void End(void);

	void SetMIDIVolume(int n,BOOL directFlag = FALSE);
	void SetWAVEVolume(int n,BOOL directFlag = FALSE);

	void SetCDVolume(int n,BOOL directFlag = FALSE);
	void SetTotalVolume(int n,BOOL directFlag = FALSE);
	void ResetWaveVolume(void);

	int SetMasterVolume(int vol,BOOL directFlag = FALSE);

private:
	int GetMIDIVolume(BOOL directFlag = FALSE);
	int GetWAVEVolume(BOOL directFlag = FALSE);
	int GetCDVolume(BOOL directFlag = FALSE);
	int GetTotalVolume(BOOL directFlag = FALSE);


	void SetVolume(MIXERCONTROL* lpMixerControl,MIXERLINE* lpMixerLine, int vol);
	int GetVolume(MIXERCONTROL* lpMixerControl,MIXERLINE* lpMixerLine,BOOL directFlag = FALSE);


	BOOL m_mixcerDeviceExist;
	BOOL m_xp;

	int m_defaultMIDIVolume;
	int m_defaultWAVEVolume;
	int m_defaultCDVolume;
	int m_defaultTotalVolume;


	BOOL m_midiVolumeExistFlag;
	BOOL m_waveVolumeExistFlag;
	BOOL m_cdVolumeExistFlag;
	BOOL m_totalVolumeExistFlag;

	HMIXER m_hMixer;

	MIXERCONTROL m_mixerControlMIDI;
	MIXERCONTROL m_mixerControlWAVE;
	MIXERCONTROL m_mixerControlCD;
	MIXERCONTROL m_mixerControlTotal;

	MIXERLINE m_mixerLineMIDI;
	MIXERLINE m_mixerLineWAVE;
	MIXERLINE m_mixerLineCD;
	MIXERLINE m_mixerLineTotal;

	BOOL m_masterVolumeFlag;
};


#endif
/*_*/

