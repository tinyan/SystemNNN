


#include <windows.h>
#include <process.h>
//#include <stddef.h>
#include <stdlib.h>
//#include <conio.h>


#if defined _TINYAN3DLIB_
#include <d3dx9.h>
#endif





//#include <windows.h>
#include <stdio.h>

#include <WINNLS32.H>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\myFile.h"

#include "..\nyanPictureLib\jpegDecoder.h"

#if !defined _TINYAN3DLIB_
#include "..\nyanDirectXLib\myDirectSoundBuffer.h"
#include "..\nyanDirectXLib\myDirectShow.h"
#include "..\nyanDirectXLib\myXAudio2Buffer.h"
#else
#include "..\nyanDirectXLib\myDirectSoundBuffer.h"
#include "..\nyanDirectXLib\myDirectShow.h"
//#include "..\..\systemNNN3D\nyanDirectX3DLib\myDirectSoundBuffer.h"
//#include "..\..\systemNNN3D\nyanDirectX3DLib\myDirectShow.h"
#endif


#include "..\nnnUtilLib\waveData.h"

#include "..\nyanDirectXLib\mydirectsound.h"

#include "..\nnnUtilLib\waveData.h"


#include "scriptVoiceControl.h"

CScriptVoiceControl::CScriptVoiceControl(CMyDirectSound* myDirectSound,int* expFlag)
{
	m_myDirectSound = myDirectSound;
	m_voiceKosuu = 4;
	m_workKosuu = 8;
	m_expFlag = new int[m_voiceKosuu];
	for (int i=0;i<m_voiceKosuu;i++)
	{
		m_expFlag[i] = expFlag[i];
	}

	m_loopVoiceWork = new int[16*m_workKosuu];
	for (int i=0;i<m_voiceKosuu;i++)
	{
		SetLoopFlag(i,FALSE);
	}


#if defined __USE_XAUDIO2__
	if (CMyDirectSound::m_xAudioFlag)
	{
		m_scriptVoice = (CMyDirectSoundBuffer**)(new CMyXAudio2Buffer*[m_voiceKosuu]);
	}
	else
	{
		m_scriptVoice = new CMyDirectSoundBuffer*[m_voiceKosuu];
	}
#else
	m_scriptVoice = new CMyDirectSoundBuffer*[m_voiceKosuu];
#endif

	for (int i=0;i<m_voiceKosuu;i++)
	{
		BOOL flg = FALSE;
		if (i & 1) flg = TRUE;

#if defined __USE_XAUDIO2__
		if (CMyDirectSound::m_xAudioFlag)
		{
			m_scriptVoice[i] = new CMyXAudio2Buffer(m_myDirectSound->GetDirectSound(), flg);
		}
		else
		{
			m_scriptVoice[i] = new CMyDirectSoundBuffer(m_myDirectSound->GetDirectSound(), flg);
		}
#else
		m_scriptVoice[i] = new CMyDirectSoundBuffer(m_myDirectSound->GetDirectSound(), flg);
#endif

	}


	m_fadeTime = new int[m_workKosuu];
	m_fadeCount = new int[m_workKosuu];
	m_fadeFromVolume = new int[m_workKosuu];
	m_fadeTargetVolume = new int[m_workKosuu];

	for (int i=0;i<m_workKosuu;i++)
	{
		m_fadeTime[i] = 0;
		m_fadeCount[i] = 0;
		m_fadeFromVolume[i] = 0;
		m_fadeTargetVolume[i] = 0;
	}
}

CScriptVoiceControl::~CScriptVoiceControl()
{
	End();
}

void CScriptVoiceControl::End(void)
{
	DELETEARRAY(m_fadeTargetVolume);
	DELETEARRAY(m_fadeFromVolume);
	DELETEARRAY(m_fadeCount);
	DELETEARRAY(m_fadeTime);

	if (m_scriptVoice != NULL)
	{
		for (int i=0;i<m_voiceKosuu;i++)
		{
			ENDDELETECLASS(m_scriptVoice[i]);
		}
		DELETEARRAY(m_scriptVoice);
	}

	DELETEARRAY(m_loopVoiceWork);
	DELETEARRAY(m_expFlag);
}


void CScriptVoiceControl::SetLoopFlag(int n,BOOL flg)
{
	m_loopVoiceWork[n*16+0] = flg;
}

BOOL CScriptVoiceControl::GetLoopFlag(int n)
{
	return m_loopVoiceWork[n*16+0];
}

bool CScriptVoiceControl::IsPlaying(int ch)
{
	return m_scriptVoice[ch]->IsPlaying();
}


void CScriptVoiceControl::Play(int ch,BOOL loopFlag,int fadeTime)
{
	char mes[256];
	sprintf_s(mes, 256, "\nCScriptVoiceControl::Play %d ", ch);
	OutputDebugString(mes);

	m_fadeTime[ch] = fadeTime * 100;

	if (fadeTime > 0)
	{
		m_scriptVoice[ch]->SetVolume(0);
		m_fadeFromVolume[ch] = 0;
		m_fadeCount[ch] = 0;
	}

	m_scriptVoice[ch]->Play(loopFlag);
	InvalidateVolumeCommand(ch,FALSE);
}

void CScriptVoiceControl::Stop(int ch,BOOL waitFlag,int fadeTime)
{
#if defined _DEBUG
	OutputDebugString("\n - StopScriptVoice");
#endif

	int oldFromVolume = m_fadeFromVolume[ch];
	int oldTargetVolume = m_fadeTargetVolume[ch];
	int oldFadeTime = m_fadeTime[ch];
	int oldFadeCount = m_fadeCount[ch];

	m_fadeFromVolume[ch] = m_fadeTargetVolume[ch];
	m_fadeTargetVolume[ch] = 0;
	m_fadeCount[ch] = 0;
	m_fadeTime[ch] = fadeTime * 100;

	if (fadeTime == 0)
	{
		m_scriptVoice[ch]->Stop(waitFlag);
	}
	else
	{
		if (oldFadeTime > 0)
		{
			if ((oldFadeCount >= 0) && (oldFadeCount < oldFadeTime))
			{
				int fromVolume = oldFromVolume + ((oldTargetVolume - oldFromVolume) * oldFadeCount) / oldFadeTime;
				if (fromVolume < 0) fromVolume = 0;
				if (fromVolume > 100) fromVolume = 100;


				m_fadeFromVolume[ch] = fromVolume;
			}
		}
	}
	InvalidateVolumeCommand(ch);
}

void CScriptVoiceControl::StopIfLoops(int ch)
{
	if (GetLoopFlag(ch))
	{
		Stop(ch);
		SetLoopFlag(ch,FALSE);
	}
}

void CScriptVoiceControl::AllStop(void)
{
	for (int i=0;i<m_voiceKosuu;i++)
	{
//		m_scriptVoice[i]->Stop(FALSE,true);
		char mes[256];
		sprintf_s(mes, 256, "\nCScriptVoiceControl::AllStop %d ", i);
		OutputDebugString(mes);
		m_scriptVoice[i]->Stop();

		m_fadeTime[i] = 0;
		InvalidateVolumeCommand(i);

		Sleep(1);
//		SetLoopFlag(i,FALSE);
	}
}

BOOL CScriptVoiceControl::SetData(int ch,char* data,int dataSize, int channel,int samplingRate,int samplingBit,BOOL loopFlag)
{

	char mes[256];
	sprintf_s(mes, 256, "\nsetdata ch=%d size=%d loop=%d", ch, dataSize, loopFlag);
	OutputDebugString(mes);

	return m_scriptVoice[ch]->SetData(data,dataSize,channel,samplingRate,samplingBit,loopFlag);
}

void CScriptVoiceControl::SetVolume(int ch,int volume,int fadeTime)
{
#if defined _DEBUG
	OutputDebugString("\n[SetScriptVoiceVolume]");
#endif

	m_fadeCount[ch] = 0;
	m_fadeTime[ch] = fadeTime * 100;//ms

	if (fadeTime == 0)
	{
		m_scriptVoice[ch]->SetVolume(volume);
	}
	else
	{
		m_fadeFromVolume[ch] = m_fadeTargetVolume[ch];
	}
	m_fadeTargetVolume[ch] = volume;
}


void CScriptVoiceControl::SetStartTeii(int ch,float fx,float fy,float fz)
{
	m_scriptVoice[ch]->SetStartTeii(fx,fy,fz);
}

void CScriptVoiceControl::SetEndTeii(int ch,float fx,float fy,float fz)
{
	m_scriptVoice[ch]->SetEndTeii(fx,fy,fz);
}

void CScriptVoiceControl::SetMoveTime(int ch,int tm)
{
	m_scriptVoice[ch]->SetMoveTime(tm);
}

void CScriptVoiceControl::SetDoppler(int ch,int dop)
{
	m_scriptVoice[ch]->SetDoppler(dop);
}


void CScriptVoiceControl::SetVelocity(int ch,float speedX,float speedY,float speedZ)
{

	m_scriptVoice[ch]->SetVelocity(speedX,speedY,speedZ);
}

void CScriptVoiceControl::Set3DPosition(int ch,float x,float y,float z)
{
	m_scriptVoice[ch]->Set3DPosition(x,y,z);
}



int CScriptVoiceControl::GetLoopWork(int n,int k)
{
	return m_loopVoiceWork[n*16+k];
}

void CScriptVoiceControl::SetLoopWork(int n,int k,int d)
{
	m_loopVoiceWork[n*16+k] = d;
}


void CScriptVoiceControl::SetLoopWorkParam(int ch,int voicenum,int charcVoiceDelta,int paraKosuu,int* pData)
{
	int deltaVolume = 0;
	if (paraKosuu >=3) deltaVolume = *(pData+2);
	deltaVolume += charcVoiceDelta;
	if (deltaVolume < -100) deltaVolume = -100;
	if (deltaVolume > 100) deltaVolume = 100;

	int loopFlag = 0;
	if (paraKosuu>=4) loopFlag = *(pData+3);

	int xyz[3];
	int xyz2[3];
	xyz[0] = 0;
	xyz[1] = 0;
	xyz[2] = 0;
	xyz2[0] = 0;
	xyz2[1] = 0;
	xyz2[2] = 0;
	int moveTime = 0;
	int dop = 0;

	if (paraKosuu >= 5) xyz[0] = *(pData+4);
	if (paraKosuu >= 6) xyz[1] = *(pData+5);
	if (paraKosuu >= 7) xyz[2] = *(pData+6);

	int sq = 0;
	for (sq=0;sq<3;sq++)
	{
		if (xyz[sq] >= 128) xyz[sq] -= 256;
	}

	if (paraKosuu >= 8) moveTime = *(pData+7);
		
	if (paraKosuu >= 9) xyz2[0] = *(pData+8);
	if (paraKosuu >= 10) xyz2[1] = *(pData+9);
	if (paraKosuu >= 11) xyz2[2] = *(pData+10);

	for (sq=0;sq<3;sq++)
	{
		if (xyz2[sq] >= 128) xyz2[sq] -= 256;
	}

	if (paraKosuu >= 12) dop = *(pData+11);


	m_loopVoiceWork[ch*16] = loopFlag;

	m_loopVoiceWork[ch*16+1] = voicenum;
	m_loopVoiceWork[ch*16+2] = deltaVolume;

	m_loopVoiceWork[ch*16+3] = xyz[0];
	m_loopVoiceWork[ch*16+4] = xyz[1];
	m_loopVoiceWork[ch*16+5] = xyz[2];

	m_loopVoiceWork[ch*16+6] = moveTime;

	m_loopVoiceWork[ch*16+7] = xyz2[0];
	m_loopVoiceWork[ch*16+8] = xyz2[1];
	m_loopVoiceWork[ch*16+9] = xyz2[2];

	m_loopVoiceWork[ch*16+10] = dop;
/*
			m_scriptSoundControl->SetLoopWork(ch,0,loopFlag);
			m_scriptSoundControl->SetLoopWork(ch,1,senum);
			m_scriptSoundControl->SetLoopWork(ch,2,deltaVolume);
			m_scriptSoundControl->SetLoopWork(ch,3,xyz[0]);
			m_scriptSoundControl->SetLoopWork(ch,4,xyz[1]);
			m_scriptSoundControl->SetLoopWork(ch,5,xyz[2]);
			m_scriptSoundControl->SetLoopWork(ch,6,moveTime);
			m_scriptSoundControl->SetLoopWork(ch,7,xyz2[0]);
			m_scriptSoundControl->SetLoopWork(ch,8,xyz2[1]);
			m_scriptSoundControl->SetLoopWork(ch,9,xyz2[2]);
			m_scriptSoundControl->SetLoopWork(ch,10,dop);
*/

}


void CScriptVoiceControl::CalcuTeii(int ch)
{
	int loopFlag = m_loopVoiceWork[ch*16+0];
	int senum = m_loopVoiceWork[ch*16+1];
	int deltaVolume = m_loopVoiceWork[ch*16+2];

	int xyz[3];
	xyz[0] = m_loopVoiceWork[ch*16+3];
	xyz[1] = m_loopVoiceWork[ch*16+4];
	xyz[2] = m_loopVoiceWork[ch*16+5];

	int moveTime = m_loopVoiceWork[ch*16+6];

	int xyz2[3];
	xyz2[0] = m_loopVoiceWork[ch*16+7];
	xyz2[1] = m_loopVoiceWork[ch*16+8];
	xyz2[2] = m_loopVoiceWork[ch*16+9];

	int dop = m_loopVoiceWork[ch*16+10];

//	int vol = GetSystemParam(NNNPARAM_SOUNDVOLUME);
//	vol += deltaVolume;
//		if (vol<0) vol = 0;
//		if (vol>100) vol = 100;

//		LPSTR sefilename = m_seList->GetName(senum*2);

//		char filename[256];
//		wsprintf(filename,"se\\%s",sefilename);

//		if (m_waveData->LoadSystemWave("se",sefilename) == FALSE) return FALSE;

//		m_scriptSound[ch]->Stop();
//		m_scriptSoundControl->Stop(ch);

//		int stereo = m_waveData->GetChannel();
//		int sampleRate = m_waveData->GetSampleRate();
//		int bitRate = m_waveData->GetBitRate();

//		char* realPtr = (char*)(m_waveData->GetRealDataPtr());
//		int realSize = m_waveData->GetRealDataSize();

//		m_scriptSound[ch]->SetData(realPtr,realSize,stereo,sampleRate,bitRate);
//		m_scriptSoundControl->SetData(ch,realPtr,realSize,stereo,sampleRate,bitRate);

	float fx = (float)xyz[0];
	float fy = (float)xyz[1];
	float fz = (float)xyz[2];
	fx *= 0.1f;
	fy *= 0.1f;
	fz *= 0.1f;

//		m_scriptSound[ch]->SetStartTeii(fx,fy,fz);
//		m_scriptSound[ch]->SetMoveTime(moveTime);
	SetStartTeii(ch,fx,fy,fz);
	SetMoveTime(ch,moveTime);
	if (moveTime > 0)
	{
		float fx2 = (float)xyz2[0];
		float fy2 = (float)xyz2[1];
		float fz2 = (float)xyz2[2];
		fx2 *= 0.1f;
		fy2 *= 0.1f;
		fz2 *= 0.1f;
		SetEndTeii(ch,fx2,fy2,fz2);
		SetDoppler(ch,dop);
	}

//		m_scriptSoundControl->SetVolume(ch,vol,m_nextFadeSe);
//		m_scriptSoundControl->Play(ch,loopFlag,m_nextFadeSe);

}


void CScriptVoiceControl::OnMainLoop(int cnt)
{
	for (int i=0;i<m_voiceKosuu;i++)
	{
		int fadeTime = m_fadeTime[i];
		if (fadeTime > 0)
		{
			int count = m_fadeCount[i] + cnt;
			m_fadeCount[i] = count;

			if (count >= fadeTime)//fade end
			{
				m_fadeTime[i] = 0;
				count = fadeTime;
			}

			int vol = m_fadeFromVolume[i] + ((m_fadeTargetVolume[i] - m_fadeFromVolume[i]) * count) / fadeTime;
			if (vol < 0) vol = 0;
			if (vol >= 100) vol = 100;

#if defined _DEBUG
			char mes[1024];
			sprintf_s(mes,1024,"\n voice  [fade ch=%d vol=%d]",i,vol);
			OutputDebugString(mes);
#endif
			m_scriptVoice[i]->SetVolume(vol);

			//stop?
			if (vol == 0)
			{
				if (m_fadeTargetVolume[i] <= 0)
				{
					//stop
					m_scriptVoice[i]->Stop();
					m_fadeTime[i] = 0;
					SetLoopFlag(i,FALSE);
					InvalidateVolumeCommand(i);
				}
			}
		}
	}
}



void CScriptVoiceControl::InvalidateVolumeCommand(int ch,BOOL flg)
{
	if (flg)
	{
		m_loopVoiceWork[ch*16+15] = 0;
	}
	else
	{
		m_loopVoiceWork[ch*16+15] = 1;
	}
}

BOOL CScriptVoiceControl::CheckVolumeCommandOk(int ch)
{
	return m_loopVoiceWork[ch*16+15];
}



/*_*/


