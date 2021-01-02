//
//
//

#include <windows.h>
#include <math.h>

#include "..\nyanlib\include\commonMacro.h"
#include "..\nyanlib\include\picture.h"
#include "..\nyanlib\include\areaControl.h"

#include "superButtonSetup.h"

#include "taihi.h"

#include "nnnButtonStatus.h"

#include "myMouseStatus.h"
#include "myKeyStatus.h"
#include "inputStatus.h"

#include "commonButton.h"


//
// STATUSMASK
// REQUESTSOUNDFLAGMASK
// SOUNDMASK 
// 
//



CCommonButton::CCommonButton(CNameList* lpSetup,LPSTR buttonName, CPicture* lpBG)
{
	m_setup = lpSetup;

	SetExist();
	SetEnable();
	SetReturnCannotClick(FALSE);

	SetPicTateYoko();
	SetPicture(NULL);
	SetDisableMode();
	POINT pt;
	pt.x = 0;
	pt.y = 0;
	SetZahyo(pt);
	SetCheckDelta(pt);
	SIZE sz;
	sz.cx = 1;
	sz.cy = 1;
	SetSize(sz);
	
	SetCancelButtonFlag(FALSE);
	SetUpButtonFlag(FALSE);
	SetDownButtonFlag(FALSE);

	SetButtonCode(0);
	SetVolumeType(0);

	int i = 0;
	for (i=0;i<4;i++)
	{
		SetAnimePattern(i,1);
		SetAnimeSpeed(i,1);
		SetAnimeType(i,1);
		SetClickSound(0);
		SetCannotClickSound(0);
		SetEnterSound(0);
		SetExitSound(0);
		SetEnterSoundWait(0);
		SetExitSoundWait(0);
		SetClickVoice(0);
		SetCannotClickVoice(0);
		SetEnterVoice(0);
		SetExitVoice(0);
	}

	for (i=0;i<3;i++)
	{
		SetAccelKey(-1,i);
	}

	SetButtonPrintMode(2);
	SetClickTime(1);

	SetPicture(NULL);
	SetBG(NULL);


	m_superButtonSetup = NULL;
	if (m_setup != NULL)
	{
		m_superButtonSetup = new CSuperButtonSetup(m_setup,buttonName);
		m_superButtonSetup->SetupButtonStatus(this);
		SetBG(lpBG);
	}

	Init();
}



CCommonButton::~CCommonButton()
{
	End();
}


void CCommonButton::End(void)
{
	ENDDELETECLASS(m_superButtonSetup);
}



void CCommonButton::Init(void)
{
	m_ignoreCount = 0;
	m_mode = 0;
	m_count = 0;
	m_enterCount = 0;
	m_exitCount = 0;
	m_enterFlag = FALSE;
	m_exitFlag = FALSE;
	m_entered = false;

	for (int i=0;i<4;i++)
	{
		m_animeCount[i] = 0;
	}
	if (GetEnable() == FALSE) m_mode = 3;
}


int CCommonButton::Calcu(CInputStatus* lpInput,int clickFlag)
{
	if (GetExist() == FALSE) return NNNBUTTON_NOTHING;
	if (m_ignoreCount > 0)
	{
		m_ignoreCount--;
		lpInput = NULL;
	}

	if (lpInput == NULL)
	{
		if (GetEnable() == FALSE)
		{
			m_mode = 3;
		}
		else
		{
			m_mode = 0;
		}

		ResetOtherAnimeCount();
		return NNNBUTTON_NOTHING;
	}

	int voice = 0;

	if (GetEnable() == FALSE)
	{
		m_mode = 3;
		//check cannot click sound
		ResetOtherAnimeCount();

		if (CheckClick(lpInput))
		{
			if (m_returnCannotClick)
			{
				return MakeButtonStatus(NNNBUTTON_CLICKING);
			}

			int sound = GetCannotClickSound();
			int voice = GetCannotClickVoice();

			if (sound != 0 || voice > 0)
			{
				return MakeButtonStatus(NNNBUTTON_REQUESTSOUND,sound,voice,-1,m_volumeType);
			}

		}


		return NNNBUTTON_NOTHING;
	}


	//clicking
	if (m_mode == 2)
	{
		m_count++;
		ResetOtherAnimeCount();
		if (m_count >= m_clickTime)
		{
			return MakeButtonStatus(NNNBUTTON_NUMBER,-1,-1,m_buttonCode);
		}

		return MakeButtonStatus(NNNBUTTON_CLICKING);
	}


	if (CheckClick(lpInput,clickFlag))
	{
		StartClick();
		ResetOtherAnimeCount();
		int sound = GetClickSound();
		voice = GetClickVoice();

		if (m_count >= m_clickTime)
		{
			return MakeButtonStatus(NNNBUTTON_NUMBER,sound,voice,m_buttonCode,m_volumeType);
		}

		return MakeButtonStatus(NNNBUTTON_STARTCLICK,sound,voice,-1,m_volumeType);
	}

	BOOL onButtonFlag = CheckOnButton(lpInput);
	m_count++;

	if (m_mode == 0)
	{
		if (onButtonFlag)
		{
			StartEnter();
			ResetOtherAnimeCount();
			int sound = GetEnterSound();
			voice = GetEnterVoice();
			if (m_entered)
			{
				voice = 0;
				sound = 0;
			}
			if (GetEnterSoundWait() != 0)
			{
				sound = 0;
				voice = 0;
			}
			return MakeButtonStatus(NNNBUTTON_ENTER,sound,voice,-1,m_volumeType);
		}

		m_entered = false;

		if (m_exitFlag)
		{
			if (m_count == GetExitSoundWait())
			{
				int sound = GetExitSound();
				voice = GetExitVoice();
				if (sound > 0 || voice > 0)
				{
					return MakeButtonStatus(NNNBUTTON_REQUESTSOUND,sound,voice,-1,m_volumeType);
				}
			}
		}

		return NNNBUTTON_NOTHING;
	}

	if (m_mode == 1)
	{
		if (onButtonFlag == FALSE)
		{
			m_entered = false;
			StartExit();
			ResetOtherAnimeCount();
			int sound = GetExitSound();
			voice = GetExitVoice();
			if (GetExitSoundWait() != 0)
			{
				sound = 0;
				voice = 0;
			}
			return MakeButtonStatus(NNNBUTTON_EXIT,sound,voice,-1,m_volumeType);
		}

		if (m_enterFlag)
		{
			if (m_count == GetEnterSoundWait())
			{
				int sound = GetEnterSound();
				voice = GetEnterVoice();
				if (m_entered)
				{
					voice = 0;
					sound = 0;
				}

				if (sound > 0 || voice > 0)
				{
					return MakeButtonStatus(NNNBUTTON_REQUESTSOUND,sound,voice,-1,m_volumeType);
				}
			}
		}

		return NNNBUTTON_NOTHING;
	}

	return NNNBUTTON_NOTHING;
}

void CCommonButton::StartClick(void)
{
	m_count = 0;
	m_mode = 2;
}

void CCommonButton::StartEnter(void)
{
//	OutputDebugString("StartEnter\n");

	m_enterFlag = TRUE;
	m_mode = 1;
	m_count = 0;
}

void CCommonButton::StartExit(void)
{
	m_exitFlag = TRUE;
	m_mode = 0;
	m_count = 0;
}

void CCommonButton::StretchPut(int multiX,int multiY,POINT delta,int percent)
{
	CPicture* lpPic = GetPicture();
	if (lpPic == NULL) return;	//no pic

	m_animeCount[m_mode] = 0;
	CalcuPicParam();
	POINT pt1 = GetPicZahyo(m_mode,m_picPattern1);

	int putX0 = m_zahyo.x;
	int putY0 = m_zahyo.y;

	int srcSizeX = m_size.cx;
	int srcSizeY = m_size.cy;

	int srcX = pt1.x;
	int srcY = pt1.y;

	int centerX = putX0 + srcSizeX / 2;
	int centerY = putY0 + srcSizeY / 2;

	int deltaX = ((srcSizeX / 2) * multiX) / 100;
	int deltaY = ((srcSizeY / 2) * multiY) / 100;

	int dstSizeX = deltaX * 2;
	int dstSizeY = deltaY * 2;

	int dstX = centerX - deltaX;
	int dstY = centerY - deltaY;


	dstX += delta.x;
	dstY += delta.y;


	CAreaControl::AddArea(dstX,dstY,dstSizeX,dstSizeY);

	lpPic->StretchBlt1(dstX, dstY, dstSizeX, dstSizeY, srcX, srcY, srcSizeX, srcSizeY, percent, TRUE);
}


void CCommonButton::Put(POINT delta,int percent)
{
	CPicture* lpPic = GetPicture();
	if (lpPic == NULL) return;	//no pic

	//taihi
	if ((m_taihi != NULL) && (m_taihiNumber != -1))
	{
	}

	m_animeCount[m_mode] = 0;
	CalcuPicParam();
	POINT pt1 = GetPicZahyo(m_mode,m_picPattern1);

	int putX = m_zahyo.x;
	int putY = m_zahyo.y;

	int sizeX = m_size.cx;
	int sizeY = m_size.cy;

	int srcX = pt1.x;
	int srcY = pt1.y;

	putX += delta.x;
	putY += delta.y;

	CAreaControl::AddArea(putX,putY,sizeX,sizeY);

//	CPicture* lpBG = GetBG();
//	if (lpBG != NULL)
//	{
//		lpBG->Blt(putX,putY,putX,putY,sizeX,sizeY,FALSE);
//	}

	if (percent == 100)
	{
		lpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
	}
	else
	{
		lpPic->TransLucentBlt3(putX,putY,srcX,srcY,sizeX,sizeY,percent);
	}


}


void CCommonButton::PutInFromRight(int ps)
{
	CPicture* lpPic = GetPicture();
	if (lpPic == NULL) return;	//no pic

	m_animeCount[m_mode] = 0;
	CalcuPicParam();
	POINT pt1 = GetPicZahyo(m_mode,m_picPattern1);

	int putX = m_zahyo.x;
	int putY = m_zahyo.y;

	int sizeX = m_size.cx;
	int sizeY = m_size.cy;

	int srcX = pt1.x;
	int srcY = pt1.y;

	CAreaControl::AddArea(putX,putY,sizeX,sizeY);

	int deltaRight = (sizeX * (100-ps)) / 100;

	sizeX -= deltaRight;
	if (sizeX <= 0) return;

	putX += deltaRight;

	lpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
}

void CCommonButton::PutInFromLeft(int ps)
{
	CPicture* lpPic = GetPicture();
	if (lpPic == NULL) return;	//no pic

	m_animeCount[m_mode] = 0;
	CalcuPicParam();
	POINT pt1 = GetPicZahyo(m_mode,m_picPattern1);

	int putX = m_zahyo.x;
	int putY = m_zahyo.y;

	int sizeX = m_size.cx;
	int sizeY = m_size.cy;

	int srcX = pt1.x;
	int srcY = pt1.y;

	CAreaControl::AddArea(putX,putY,sizeX,sizeY);

	int deltaLeft = (sizeX * (100-ps)) / 100;

	sizeX -= deltaLeft;
	if (sizeX <= 0) return;

	srcX += deltaLeft;

	lpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
}

void CCommonButton::PutInFromUp(int ps)
{
	CPicture* lpPic = GetPicture();
	if (lpPic == NULL) return;	//no pic

	m_animeCount[m_mode] = 0;
	CalcuPicParam();
	POINT pt1 = GetPicZahyo(m_mode,m_picPattern1);

	int putX = m_zahyo.x;
	int putY = m_zahyo.y;

	int sizeX = m_size.cx;
	int sizeY = m_size.cy;

	int srcX = pt1.x;
	int srcY = pt1.y;

	CAreaControl::AddArea(putX,putY,sizeX,sizeY);

	int deltaUp = (sizeY * (100-ps)) / 100;

	sizeY -= deltaUp;
	if (sizeY <= 0) return;

	srcY += deltaUp;

	lpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
}

void CCommonButton::PutInFromDown(int ps)
{
	CPicture* lpPic = GetPicture();
	if (lpPic == NULL) return;	//no pic

	m_animeCount[m_mode] = 0;
	CalcuPicParam();
	POINT pt1 = GetPicZahyo(m_mode,m_picPattern1);

	int putX = m_zahyo.x;
	int putY = m_zahyo.y;

	int sizeX = m_size.cx;
	int sizeY = m_size.cy;

	int srcX = pt1.x;
	int srcY = pt1.y;

	CAreaControl::AddArea(putX,putY,sizeX,sizeY);

	int deltaDown = (sizeY * (100-ps)) / 100;

	sizeY -= deltaDown;
	if (sizeY <= 0) return;

	putY += deltaDown;

	lpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
}


void CCommonButton::PutInFromCenterUpDown(int ps)
{
	CPicture* lpPic = GetPicture();
	if (lpPic == NULL) return;	//no pic

	m_animeCount[m_mode] = 0;
	CalcuPicParam();
	POINT pt1 = GetPicZahyo(m_mode,m_picPattern1);

	int putX = m_zahyo.x;
	int putY = m_zahyo.y;

	int sizeX = m_size.cx;
	int sizeY = m_size.cy;

	int srcX = pt1.x;
	int srcY = pt1.y;

	CAreaControl::AddArea(putX,putY,sizeX,sizeY);

	int deltaUpDown = (sizeY * (100-ps)) / (100*2);

	sizeY -= deltaUpDown*2;
	if (sizeY <= 0) return;

	srcY += deltaUpDown;
	putY += deltaUpDown;
	lpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
}


void CCommonButton::PutInFromCenterLeftRight(int ps)
{
	CPicture* lpPic = GetPicture();
	if (lpPic == NULL) return;	//no pic

	m_animeCount[m_mode] = 0;
	CalcuPicParam();
	POINT pt1 = GetPicZahyo(m_mode,m_picPattern1);

	int putX = m_zahyo.x;
	int putY = m_zahyo.y;

	int sizeX = m_size.cx;
	int sizeY = m_size.cy;

	int srcX = pt1.x;
	int srcY = pt1.y;

	CAreaControl::AddArea(putX,putY,sizeX,sizeY);

	int deltaLeftRight = (sizeX * (100-ps)) / (100*2);

	sizeX -= deltaLeftRight*2;
	if (sizeX <= 0) return;

	srcX += deltaLeftRight;
	putX += deltaLeftRight;
	lpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
}



void CCommonButton::Print(int md)
{
	CPicture* lpPic = GetPicture();
	if (lpPic == NULL) return;	//no pic


	//taihi
	if ((m_taihi != NULL) && (m_taihiNumber != -1))
	{
	}


	CalcuPicParam();

	POINT pt1 = GetPicZahyo(m_mode,m_picPattern1);
	POINT pt2 = GetPicZahyo(m_mode,m_picPattern2);

	int putX = m_zahyo.x;
	int putY = m_zahyo.y;

	int sizeX = m_size.cx;
	int sizeY = m_size.cy;


	CAreaControl::AddArea(putX,putY,sizeX,sizeY);

	//BG?
	CPicture* lpBG = GetBG();
	if (lpBG != NULL)
	{
		lpBG->Blt(putX,putY,putX,putY,sizeX,sizeY,FALSE);
	}


	int printMode = GetButtonPrintMode();

	if (m_picPercent == 100)
	{
		if (printMode == 0)
		{
			lpPic->Blt(putX,putY,pt1.x,pt1.y,sizeX,sizeY,FALSE);
		}
		else
		{
			lpPic->Blt(putX,putY,pt1.x,pt1.y,sizeX,sizeY,TRUE);
		}
	}
	else if (m_picPercent == 0)
	{
		if (printMode == 0)
		{
			lpPic->Blt(putX,putY,pt2.x,pt2.y,sizeX,sizeY,FALSE);
		}
		else
		{
			lpPic->Blt(putX,putY,pt2.x,pt2.y,sizeX,sizeY,TRUE);
		}
	}
	else
	{
		if (printMode == 0)
		{
			lpPic->Blt(putX,putY,pt1.x,pt1.y,sizeX,sizeY,FALSE);
		}
		else if (printMode == 1)
		{
			lpPic->Blt(putX,putY,pt1.x,pt1.y,sizeX,sizeY,TRUE);
		}
		else
		{
			int ps2 = 100 - m_picPercent;
			int* lpBuffer2 = (int*)(m_pic->GetBuffer());
			char* lpMask2 = (char*)(m_pic->GetMaskPic());
		
			int deltaX = pt2.x - pt1.x;
			int deltaY = pt2.y - pt1.y;

			SIZE sz = m_pic->GetPicSize();

			lpBuffer2 += deltaX;
			lpBuffer2 += deltaY * sz.cx;

			lpMask2 += deltaX;
			lpMask2 += deltaY * sz.cx;

			int srcX = pt1.x;
			int srcY = pt1.y;

			//m_pic->ChangeTranslateBlt(putX,putY,srcX,srcY,sizeX,sizeY,m_picPercent,ps2,lpBuffer2,lpMask2,m_pic);
			m_pic->ChangeTranslateBlt(putX,putY,srcX,srcY,sizeX,sizeY,m_picPercent,ps2,m_pic,pt2.x,pt2.y);
		}

	}


	Anime();
}



void CCommonButton::SetSize(SIZE sz)
{
	m_size = sz;
	int tateyoko = GetPicTateYoko();

	for (int i=0;i<4;i++)
	{
		POINT pt2;
		pt2.x = sz.cx * i;
		pt2.y = sz.cy * i;

		if (tateyoko == 0)
		{
			pt2.y = 0;
		}
		else
		{
			pt2.x = 0;
		}

		SetSrcPicZahyo(pt2,i);
	}
	SetCheckSize(sz);
}




POINT CCommonButton::GetPicZahyo(int md,int pattern)
{
	POINT pt = GetSrcPicZahyo(md);
	CPicture* lpPic = GetPicture();

	SIZE sz;
	sz.cx = 1;
	sz.cy = 1;
	if (lpPic != NULL) sz = lpPic->GetPicSize();

	int allPicSizeX = sz.cx;
	int allPicSizeY = sz.cy;

	SIZE srcSize = GetSize();
	int srcSizeX = srcSize.cx;
	int srcSizeY = srcSize.cy;

	if (srcSizeX<1) srcSizeX = 1;
	if (srcSizeY<1) srcSizeY = 1;

	int tateYoko = GetPicTateYoko();

	int kosuuX = allPicSizeX / srcSizeX;
	int kosuuY = allPicSizeY / srcSizeY;

	if (kosuuX<1) kosuuX = 1;
	if (kosuuY<1) kosuuY = 1;

	int srcX = pt.x;
	int srcY = pt.y;


	if (tateYoko == 0)
	{
		srcY += pattern * srcSizeY;
		int yEnd = srcY + srcSizeY;
		
		if (yEnd > allPicSizeY)
		{
//			int amariKosuu = pattern + 1 - (allPicSizeY - srcY) / srcSizeY;
			int amariKosuu = (yEnd - allPicSizeY) / srcSizeY;
			amariKosuu--;

			srcY = 0;
			srcX += srcSizeX;

			int amariX2 = amariKosuu / kosuuY;
			int amariY2 = amariKosuu % kosuuY;

			srcX += srcSizeX * amariX2;
			srcY = srcSizeY * amariY2;
		}
	}
	else
	{
		srcX += pattern * srcSizeX;
		int xEnd = srcX + srcSizeX;

		if (xEnd > allPicSizeX)
		{
//			int amariKosuu = pattern + 1 - (allPicSizeX - srcX) / srcSizeX;
			int amariKosuu = (xEnd - allPicSizeX) / srcSizeX;
			amariKosuu--;

			srcX = 0;
			srcY += srcSizeY;

			int amariY2 = amariKosuu / kosuuX;
			int amariX2 = amariKosuu % kosuuX;

			srcY += srcSizeY * amariY2;
			srcX = srcSizeX * amariX2;
		}
	}

	POINT ansPoint;

	ansPoint.x = srcX;
	ansPoint.y = srcY;

	return ansPoint;
}

int CCommonButton::MakeButtonStatus(int status,int sound,int voice,int data,int volumeType)
{
	status &= NNNBUTTON_STATUSMASK;

	if (sound > 0)
	{
		sound <<= 8;
		sound &= NNNBUTTON_SOUNDMASK;
		sound |= NNNBUTTON_REQUESTSOUNDMASK;
		if (volumeType == -1)
		{
			volumeType = 0;
		}
		else
		{
			volumeType <<= 22;
			volumeType &= NNNBUTTON_VOLUMETYPEMASK;
		}
	}
	else
	{
		sound = 0;
		volumeType = 0;
	}

	if (voice > 0)
	{
		//ã§í 
		sound |= NNNBUTTON_REQUESTSOUNDMASK;
		voice <<= 16;
		voice &= NNNBUTTON_VOICEMASK;
	}
	else
	{
		voice = 0;
	}


	/*
	if (mode == -1) mode = 0;//m_mode;
	mode <<= 16;
	mode &= NNNBUTTON_MODEMASK;
	*/


	if (data >= 0)
	{
		data &= NNNBUTTON_DATAMASK;
		data |= NNNBUTTON_DATAEXISTMASK;
	}
	else
	{
		data = 0;
	}

	int d = status | sound | voice | data | volumeType;

	return d;

//	return (status & NNNBUTTON_STATUSMASK) | (NNNBUTTON_MODEMASK & (mode << 16)) | (NNNBUTTON_DATAMASK & data);
}



int CCommonButton::ChangeButtonData(int statusData,int data)
{
	statusData &= ~(NNNBUTTON_DATAEXISTMASK | NNNBUTTON_DATAMASK);
	data &= NNNBUTTON_DATAMASK;
	statusData |= data;
	statusData |= NNNBUTTON_DATAEXISTMASK;

	return statusData;
}

int CCommonButton::GetButtonStatus(int statusData)
{
	if (statusData == NNNBUTTON_NOTHING) return statusData;

	return statusData & NNNBUTTON_STATUSMASK;
}

/*
int CCommonButton::GetButtonMode(int statusData)
{
	if (statusData == NNNBUTTON_NOTHING)
	{
		return 0;
	}

	int mode = statusData & NNNBUTTON_MODEMASK;
	mode >>= 16;
	return mode;
}
*/

int CCommonButton::GetButtonVoice(int statusData)
{
	if (statusData == NNNBUTTON_NOTHING)
	{
		return 0;
	}

	int voice = statusData & NNNBUTTON_VOICEMASK;
	voice >>= 16;
	return voice;
}

int CCommonButton::GetButtonSound(int statusData)
{
	if (statusData == NNNBUTTON_NOTHING) return 0;
	if ((statusData & NNNBUTTON_REQUESTSOUNDMASK) == 0) return 0;
	int sound = statusData & NNNBUTTON_SOUNDMASK;
	sound >>= 8;
	return sound;
}

int CCommonButton::GetButtonData(int statusData)
{
	if (statusData == NNNBUTTON_NOTHING) return -1;
	if ((statusData & NNNBUTTON_DATAEXISTMASK) == 0) return -1;

	int d = statusData & NNNBUTTON_DATAMASK;
	return d;
}

int CCommonButton::GetVolumeTypeData(int statusData)
{
	if (statusData == NNNBUTTON_NOTHING) return 0;//error!
	int d = statusData & NNNBUTTON_VOLUMETYPEMASK;
	d >>= 22;
	return d;
}


BOOL CCommonButton::CheckRequestSound(int statusData)
{
	if (statusData == NNNBUTTON_NOTHING) return FALSE;
	if (statusData & NNNBUTTON_REQUESTSOUNDMASK) return TRUE;
	return FALSE;
}

BOOL CCommonButton::CheckExistData(int statusData)
{
	if (statusData == NNNBUTTON_NOTHING) return FALSE;
	if (statusData & NNNBUTTON_DATAEXISTMASK) return TRUE;
	return FALSE;
}



BOOL CCommonButton::CheckOnButton(CInputStatus* lpInput)
{
	CMyMouseStatus* lpMouse = lpInput->GetMouseStatus();
	POINT mousePoint = lpMouse->GetZahyo();
	int mouseX = mousePoint.x;
	int mouseY = mousePoint.y;

	POINT zahyo = GetZahyo();
	int checkX = zahyo.x;
	int checkY = zahyo.y;

	POINT delta = GetCheckDelta();
	checkX += delta.x;
	checkY += delta.y;

	int dx = mouseX - checkX;
	int dy = mouseY - checkY;

	SIZE size = GetCheckSize();
	int sizeX = size.cx;
	int sizeY = size.cy;

	BOOL onFlag = FALSE;

	int buttonPrintMode = GetButtonPrintMode();

	if ((dx>=0) && (dx<sizeX) && (dy>=0) && (dy<sizeY))
	{
		if (buttonPrintMode == 0)
		{
			onFlag = TRUE;
		}
		else
		{
			POINT checkPicZahyo = GetCheckPicZahyo();
			int checkPicX = checkPicZahyo.x;
			int checkPicY = checkPicZahyo.y;

			CPicture* lpPic = GetPicture();
			if (lpPic != NULL)
			{
				if (lpPic->CheckOnPic(checkPicX + dx,checkPicY + dy))
				{
					onFlag = TRUE;
				}
			}
		}
	}

	return onFlag;
}


BOOL CCommonButton::CheckOnButtonPic(POINT pt)
{
//	CMyMouseStatus* lpMouse = lpInput->GetMouseStatus();
	POINT mousePoint = pt;
	int mouseX = mousePoint.x;
	int mouseY = mousePoint.y;

	POINT zahyo = GetZahyo();
	int checkX = zahyo.x;
	int checkY = zahyo.y;

	POINT delta = GetCheckDelta();
	checkX += delta.x;
	checkY += delta.y;

	int dx = mouseX - checkX;
	int dy = mouseY - checkY;

	SIZE size = GetCheckSize();
	int sizeX = size.cx;
	int sizeY = size.cy;

	BOOL onFlag = FALSE;

	int buttonPrintMode = GetButtonPrintMode();

	if ((dx>=0) && (dx<sizeX) && (dy>=0) && (dy<sizeY))
	{
		if (buttonPrintMode == 0)
		{
			onFlag = TRUE;
		}
		else
		{
			POINT checkPicZahyo = GetCheckPicZahyo();
			int checkPicX = checkPicZahyo.x;
			int checkPicY = checkPicZahyo.y;

			CPicture* lpPic = GetPicture();
			if (lpPic != NULL)
			{
				if (lpPic->CheckOnPic(checkPicX + dx,checkPicY + dy))
				{
					onFlag = TRUE;
				}
			}
		}
	}

	return onFlag;
}

BOOL CCommonButton::CheckClick(CInputStatus* lpInput,int clickFlag)
{
	//mouse,cancel,upmdown,accelKey

	CMyMouseStatus* lpMouse = lpInput->GetMouseStatus();

	//cancel button
	if (GetCancelButtonFlag())
	{
		if (lpMouse->CheckClick(1)) return TRUE;
		if (clickFlag & 2) return TRUE;
	}

	//upbutton,downButton
	int wheel = lpMouse->GetWheel();
	if (GetUpdownRev()) wheel *= -1;

	if (GetUpButtonFlag())
	{
		if (wheel > 0) return TRUE;
	}

	if (GetDownButtonFlag())
	{
		if (wheel < 0) return TRUE;
	}

	if (CheckOnButton(lpInput))
	{
		if (lpMouse->CheckClick(0)) return TRUE;
		if (clickFlag & 1) return TRUE;
	}


	CMyKeyStatus* lpKey = lpInput->GetKeyStatus();

	//accelkey
	if (lpKey != NULL)
	{
		for (int i=0;i<3;i++)
		{
			int key = m_accelKey[i];
			if (key != -1)
			{
				if (lpKey->CheckKey(key)) return TRUE;
			}
		}
	}

	return FALSE;
}

void CCommonButton::CalcuPicParam(void)
{
	int type = m_animeType[m_mode];
	int speed = m_animeSpeed[m_mode];
	int count = m_animeCount[m_mode];
	int pattern = m_animePattern[m_mode];

	int revFlag = 0;
	int dv = pattern;

	if (speed<1) speed = 1;

	if ((type == 3) || (type == 4) || (type == 7) || (type == 8))
	{
		dv = (pattern-1) * 2;
		if (dv<1) dv = 1;
		revFlag = 1;
	}

	int limitFlag = 0;
	if ((type == 2) || (type == 4) || (type == 6) || (type == 8))
	{
		limitFlag = 1;
	}

	int pic1 = count / speed;
	int pic2 = pic1+1;
	
	if (limitFlag)
	{
		int limData = dv-1;
		if (revFlag) limData = dv;

		if (pic1>=dv) pic1 = limData;
		if (pic2>=dv) pic2 = limData;
	}

	pic2 %= dv;

	int percent = 100;

	if (revFlag)
	{
		if (pic1 >= pattern) pic1 = (pattern-1)*2 - pic1;
		if (pic2 >= pattern) pic2 = (pattern-1)*2 - pic2;
	}

	if (type >= 5)
	{
		percent = 100 * (speed - (count - ((count / speed) * speed)));
		percent /= speed;
	}

	m_picPattern1 = pic1;
	m_picPattern2 = pic2;
	m_picPercent = percent;
}



void CCommonButton::Anime(int cnt)
{
	int type = m_animeType[m_mode];
	int speed = m_animeSpeed[m_mode];
	int count = m_animeCount[m_mode];
	int pattern = m_animePattern[m_mode];

	if (speed<1) speed = 1;

	int revFlag = 0;
	int dv = pattern;

	if ((type == 3) || (type == 4) || (type == 7) || (type == 8))
	{
		dv = (pattern-1) * 2;
		if (dv<1) dv = 1;
		revFlag = 1;
	}

	dv *= speed;

	int limitFlag = 0;
	if ((type == 2) || (type == 4) || (type == 6) || (type == 8))
	{
		limitFlag = 1;
	}

	count += cnt;
	if (limitFlag)
	{
		if (count >= dv) count = dv;
	}
	else
	{
		count %= dv;
	}

	m_animeCount[m_mode] = count;
}


void CCommonButton::ResetAnimeCount(void)
{
	for (int i=0;i<4;i++)
	{
		m_animeCount[i] = 0;
	}
}

void CCommonButton::ResetOtherAnimeCount(void)
{
	for (int i=0;i<4;i++)
	{
		if (i != m_mode)
		{
			m_animeCount[i] = 0;
		}
	}
}

void CCommonButton::SetEnable(BOOL flg)
{
	m_enableFlag = flg;
	if (flg == FALSE) m_mode = 3;
}

void CCommonButton::SetNextIgnore(int cnt)
{
	m_ignoreCount = cnt;
}

BOOL CCommonButton::LoadFile(LPSTR dirName)
{
	char filename[256];
	if (dirName == NULL)
	{
		sprintf_s(filename,256,"%s",GetFileName());
	}
	else
	{
		sprintf_s(filename,256,"%s\\%s",dirName,GetFileName());
	}
	CPicture* lpPic = GetPicture();
	if (lpPic == NULL) return FALSE;	//no pic

	return lpPic->LoadDWQ(filename);
}


void CCommonButton::ClearAccelKey(void)
{
	for (int i = 0; i<3; i++)
	{
		SetAccelKey(-1, i);
	}
}


void CCommonButton::SetEntered(bool bEnter)
{
	m_entered = bEnter;
}



void CCommonButton::AppearPrint(int count, int countMax, int type, POINT deltaPoint,int buttonNumber,int buttonMax)
{
	//type bit0:îºìßñæèàóù

	if (count >= countMax)
	{
		Print(true);
		return;
	}


//	int n = m_buttonKosuu * m_extMode;
	int n = 0;

	int dv = countMax;
	if (dv < 1) dv = 1;

	int percent = 100;
	if (type & 1)
	{
		percent = (100 * count) / dv;
		if (percent < 0) percent = 0;
		if (percent > 100) percent = 100;
	}

	POINT delta;
	int dx = (deltaPoint.x * (dv - count)) / dv;
	int dy = (deltaPoint.y * (dv - count)) / dv;
	delta.x = dx;
	delta.y = dy;

	int type2 = type / 2;

	if (type2 == 0)
	{
		if (GetExist())
		{
			if (percent > 0)
			{
				Put(delta, percent);
			}
		}
	}


	//2:Ç†Ç¬Ç‹Ç¡ÇƒÇ≠ÇÈ 4:Ç‹ÇÌÇËÇ»Ç™ÇÁÇ†Ç¬Ç‹Ç¡ÇƒÇ≠ÇÈ
	if ((type2 == 1) || (type2 == 2))
	{
		double dth = 0.0;
		if (type2 == 2)
		{
			dth = (double)count;
			dth /= (double)dv;
			dth *= 3.14159 * 2;
		}

		if (GetExist())
		{
			if (percent > 0)
			{
				double th = (double)buttonNumber;
				th /= (double)buttonMax;
				th *= 3.14159 * 2;
				th += dth;

				double cosTH = cos(th);
				double sinTH = sin(th);

				double dx2 = (double)dx;
				double dy2 = (double)dy;

				int dx3 = (int)(dx2 * cosTH - dy2 * sinTH + 0.5);
				int dy3 = (int)(dx2 * sinTH + dy2 * cosTH + 0.5);

				delta.x = dx3;
				delta.y = dy3;

				Put(delta, percent);
			}
		}
	}

	//6 8 10 ägëÂÇµÇ»Ç™ÇÁ ÇΩÇƒÇÊÇ±ÅAÇΩÇƒÅAÇÊÇ± 
	if ((type2 == 3) || (type2 == 4) || (type2 == 5))
	{
		delta.x = 0;
		delta.y = 0;

		int multi = (count * 100) / dv;
		if (multi <= 0) return;
		if (multi >= 100) multi = 100;

		int multiX = multi;
		int multiY = multi;

		if (type2 == 4) multiX = 100;
		if (type2 == 5) multiY = 100;

		if (GetExist())
		{
			if (percent > 0)
			{
				StretchPut(multiX, multiY, delta, percent);
			}
		}
	}

	if ((type2 >= 6) && (type2 <= 11))
	{
		SpecialPrint(count, countMax, type2 - 6,buttonNumber,buttonMax);
	}

}

void CCommonButton::SpecialPrint(int count, int countMax, int type,int buttonNumber,int buttonMax)
{
//	int n = m_buttonKosuu * m_extMode;
	int n = 0;

	int ps100 = (count * 10000) / countMax;
	if (ps100 < 0) ps100 = 0;
	if (ps100 > 10000) ps100 = 10000;

	if (GetExist())
	{

		int delay = 10000 / (buttonMax * 2 + 1);

		int  k = ps100 - buttonNumber * delay;
		if (k >= 0)
		{
			int dv = 10000 - buttonMax * delay;
			if (dv < 1) dv = 1;

			int ps = (k * 100) / dv;
			if (ps > 100) ps = 100;


			switch (type)
			{
			case 0:
				PutInFromUp(ps);
				break;
			case 1:
				PutInFromDown(ps);
				break;
			case 2:
				PutInFromLeft(ps);
				break;
			case 3:
				PutInFromRight(ps);
				break;
			case 4:
				PutInFromCenterUpDown(ps);
				break;
			case 5:
				PutInFromCenterLeftRight(ps);
				break;
			}
		}
	}
}

/*_*/


