


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


#include "scriptSoundControl.h"

CScriptSoundControl::CScriptSoundControl(CMyDirectSound* myDirectSound,int* expFlag)
{
	m_myDirectSound = myDirectSound;
	m_soundKosuu = 8;

	m_expFlag = new int[m_soundKosuu];
	for (int i=0;i<m_soundKosuu;i++)
	{
		m_expFlag[i] = expFlag[i];
	}

	m_loopSoundWork = new int[16*m_soundKosuu];
	for (int i=0;i<m_soundKosuu;i++)
	{
		SetLoopFlag(i,FALSE);
	}

#if defined __USE_XAUDIO2__
	if (CMyDirectSound::m_xAudioFlag)
	{
		m_scriptSound = (CMyDirectSoundBuffer**)(new CMyXAudio2Buffer*[m_soundKosuu]);
	}
	else
	{
		m_scriptSound = new CMyDirectSoundBuffer*[m_soundKosuu];
	}
#else
	m_scriptSound = new CMyDirectSoundBuffer*[m_soundKosuu];
#endif


	for (int i=0;i<m_soundKosuu;i++)
	{
		BOOL flg = FALSE;
		if (i >= 4) flg = TRUE;

#if defined __USE_XAUDIO2__
		if (CMyDirectSound::m_xAudioFlag)
		{
			m_scriptSound[i] = new CMyXAudio2Buffer(m_myDirectSound->GetDirectSound(), flg);
		}
		else
		{
			m_scriptSound[i] = new CMyDirectSoundBuffer(m_myDirectSound->GetDirectSound(), flg);
		}
#else
		m_scriptSound[i] = new CMyDirectSoundBuffer(m_myDirectSound->GetDirectSound(), flg);
#endif

	}


	m_fadeTime = new int[m_soundKosuu];
	m_fadeCount = new int[m_soundKosuu];
	m_fadeFromVolume = new int[m_soundKosuu];
	m_fadeTargetVolume = new int[m_soundKosuu];

	for (int i=0;i<m_soundKosuu;i++)
	{
		m_fadeTime[i] = 0;
		m_fadeCount[i] = 0;
		m_fadeFromVolume[i] = 0;
		m_fadeTargetVolume[i] = 0;
	}
}

CScriptSoundControl::~CScriptSoundControl()
{
	End();
}

void CScriptSoundControl::End(void)
{
	DELETEARRAY(m_fadeTargetVolume);
	DELETEARRAY(m_fadeFromVolume);
	DELETEARRAY(m_fadeCount);
	DELETEARRAY(m_fadeTime);

	if (m_scriptSound != NULL)
	{
		for (int i=0;i<m_soundKosuu;i++)
		{
			ENDDELETECLASS(m_scriptSound[i]);
		}
		DELETEARRAY(m_scriptSound);
	}

	DELETEARRAY(m_loopSoundWork);
	DELETEARRAY(m_expFlag);
}


void CScriptSoundControl::SetLoopFlag(int n,BOOL flg)
{
	m_loopSoundWork[n*16+0] = flg;
}

BOOL CScriptSoundControl::GetLoopFlag(int n)
{
	return m_loopSoundWork[n*16+0];
}


void CScriptSoundControl::Play(int ch,BOOL loopFlag,int fadeTime)
{
	m_fadeTime[ch] = fadeTime * 100;

	if (fadeTime > 0)
	{
		m_scriptSound[ch]->SetVolume(0);
		m_fadeFromVolume[ch] = 0;
		m_fadeCount[ch] = 0;
	}

	m_scriptSound[ch]->Play(loopFlag);
	InvalidateVolumeCommand(ch,FALSE);
}

void CScriptSoundControl::Stop(int ch,BOOL waitFlag,int fadeTime)
{
#if defined _DEBUG
	OutputDebugString("\n - StopScriptSound");
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
		m_scriptSound[ch]->Stop(waitFlag);
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

void CScriptSoundControl::StopIfLoops(int ch)
{
	if (GetLoopFlag(ch))
	{
		Stop(ch);
		SetLoopFlag(ch,FALSE);
	}
}

void CScriptSoundControl::AllStop(void)
{
	for (int i=0;i<m_soundKosuu;i++)
	{
		m_scriptSound[i]->Stop();
		m_fadeTime[i] = 0;
		InvalidateVolumeCommand(i);


	}
}

BOOL CScriptSoundControl::SetData(int ch,char* data,int dataSize, int channel,int samplingRate,int samplingBit,BOOL loopFlag)
{
	return m_scriptSound[ch]->SetData(data,dataSize,channel,samplingRate,samplingBit,loopFlag);
}

void CScriptSoundControl::SetVolume(int ch,int volume,int fadeTime)
{
#if defined _DEBUG
	OutputDebugString("\n[SetScriptSoundVolume]");
#endif

	m_fadeCount[ch] = 0;
	m_fadeTime[ch] = fadeTime * 100;//ms

	if (fadeTime == 0)
	{
		m_scriptSound[ch]->SetVolume(volume);
	}
	else
	{
		m_fadeFromVolume[ch] = m_fadeTargetVolume[ch];
	}
	m_fadeTargetVolume[ch] = volume;
}


void CScriptSoundControl::SetStartTeii(int ch,float fx,float fy,float fz)
{
	m_scriptSound[ch]->SetStartTeii(fx,fy,fz);
}

void CScriptSoundControl::SetEndTeii(int ch,float fx,float fy,float fz)
{
	m_scriptSound[ch]->SetEndTeii(fx,fy,fz);
}

void CScriptSoundControl::SetMoveTime(int ch,int tm)
{
	m_scriptSound[ch]->SetMoveTime(tm);
}

void CScriptSoundControl::SetDoppler(int ch,int dop)
{
	m_scriptSound[ch]->SetDoppler(dop);
}


void CScriptSoundControl::SetVelocity(int ch,float speedX,float speedY,float speedZ)
{

	m_scriptSound[ch]->SetVelocity(speedX,speedY,speedZ);
}

void CScriptSoundControl::Set3DPosition(int ch,float x,float y,float z)
{
	m_scriptSound[ch]->Set3DPosition(x,y,z);
}



int CScriptSoundControl::GetLoopWork(int n,int k)
{
	return m_loopSoundWork[n*16+k];
}

void CScriptSoundControl::SetLoopWork(int n,int k,int d)
{
	m_loopSoundWork[n*16+k] = d;
}


void CScriptSoundControl::SetLoopWorkParam(int ch,int senum,int paraKosuu,int* pData)
{
	int deltaVolume = 0;
	if (paraKosuu >=3) deltaVolume = *(pData+2);

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


	m_loopSoundWork[ch*16] = loopFlag;

	m_loopSoundWork[ch*16+1] = senum;
	m_loopSoundWork[ch*16+2] = deltaVolume;

	m_loopSoundWork[ch*16+3] = xyz[0];
	m_loopSoundWork[ch*16+4] = xyz[1];
	m_loopSoundWork[ch*16+5] = xyz[2];

	m_loopSoundWork[ch*16+6] = moveTime;

	m_loopSoundWork[ch*16+7] = xyz2[0];
	m_loopSoundWork[ch*16+8] = xyz2[1];
	m_loopSoundWork[ch*16+9] = xyz2[2];

	m_loopSoundWork[ch*16+10] = dop;
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


void CScriptSoundControl::CalcuTeii(int ch)
{
	int loopFlag = m_loopSoundWork[ch*16+0];
	int senum = m_loopSoundWork[ch*16+1];
	int deltaVolume = m_loopSoundWork[ch*16+2];

	int xyz[3];
	xyz[0] = m_loopSoundWork[ch*16+3];
	xyz[1] = m_loopSoundWork[ch*16+4];
	xyz[2] = m_loopSoundWork[ch*16+5];

	int moveTime = m_loopSoundWork[ch*16+6];

	int xyz2[3];
	xyz2[0] = m_loopSoundWork[ch*16+7];
	xyz2[1] = m_loopSoundWork[ch*16+8];
	xyz2[2] = m_loopSoundWork[ch*16+9];

	int dop = m_loopSoundWork[ch*16+10];

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


void CScriptSoundControl::OnMainLoop(int cnt)
{
	for (int i=0;i<m_soundKosuu;i++)
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
			sprintf_s(mes,1024,"\n  [fade ch=%d vol=%d]",i,vol);
			OutputDebugString(mes);
#endif
			m_scriptSound[i]->SetVolume(vol);

			//stop?
			if (vol == 0)
			{
				if (m_fadeTargetVolume[i] <= 0)
				{
					//stop
					m_scriptSound[i]->Stop();
					m_fadeTime[i] = 0;
					SetLoopFlag(i,FALSE);
					InvalidateVolumeCommand(i);
				}
			}
		}
	}
}



void CScriptSoundControl::InvalidateVolumeCommand(int ch,BOOL flg)
{
	if (flg)
	{
		m_loopSoundWork[ch*16+15] = 0;
	}
	else
	{
		m_loopSoundWork[ch*16+15] = 1;
	}
}

BOOL CScriptSoundControl::CheckVolumeCommandOk(int ch)
{
	return m_loopSoundWork[ch*16+15];
}


/*_*/


