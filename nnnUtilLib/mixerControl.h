//
// mixerControl.h
//

#if !defined __TINYAN_NNNUTILIB_MIXERCONTROL__
#define __TINYAN_NNNUTILLIB_MIXERCONTROL__

#include <mmsystem.h>

class CMixerControl
{
public:
	CMixerControl();
	~CMixerControl();
	void End(void);

	void SetMIDIVolume(int n,BOOL directFlag = FALSE);
	void SetWAVEVolume(int n,BOOL directFlag = FALSE);

	void SetCDVolume(int n,BOOL directFlag = FALSE);

	void ResetWaveVolume(void);


private:
	int GetMIDIVolume(BOOL directFlag = FALSE);
	int GetWAVEVolume(BOOL directFlag = FALSE);
	int GetCDVolume(BOOL directFlag = FALSE);


	void SetVolume(MIXERCONTROL* lpMixerControl,MIXERLINE* lpMixerLine, int vol);
	int GetVolume(MIXERCONTROL* lpMixerControl,MIXERLINE* lpMixerLine,BOOL directFlag = FALSE);


	BOOL m_mixcerDeviceExist;

	int m_defaultMIDIVolume;
	int m_defaultWAVEVolume;
	int m_defaultCDVolume;

	BOOL m_midiVolumeExistFlag;
	BOOL m_waveVolumeExistFlag;
	BOOL m_cdVolumeExistFlag;

	HMIXER m_hMixer;

	MIXERCONTROL m_mixerControlMIDI;
	MIXERCONTROL m_mixerControlWAVE;
	MIXERCONTROL m_mixerControlCD;

	MIXERLINE m_mixerLineMIDI;
	MIXERLINE m_mixerLineWAVE;
	MIXERLINE m_mixerLineCD;
};


#endif
/*_*/

