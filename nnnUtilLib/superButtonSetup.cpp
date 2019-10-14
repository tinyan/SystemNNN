//
// 
//

#include <windows.h>
#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"

#include "namelist.h"
#include "setupList.h"

#include "CommonButton.h"
#include "superButtonSetup.h"


BOOL CSuperButtonSetup::m_notCopyFlag = FALSE;


CSuperButtonSetup::CSuperButtonSetup(CNameList* nameList,LPSTR buttonName,CSuperButtonSetup* lpCopyFrom,POINT* lpDelta,BOOL notSrcPicCopy)
{
	m_setupList = new CSetupList();
	m_setupList->SetSetup(nameList);


	int ln = (int)strlen(buttonName);
	if (ln>254) ln = 254;
	memcpy(m_buttonName,buttonName,ln);
	m_buttonName[ln] = 0;
	m_buttonName[ln+1] = 0;

	m_clickTime = 8;
	m_size.cx = 16;
	m_size.cy = 16;
	m_zahyo.x = 0;
	m_zahyo.y = 0;
	m_filename = NULL;

	int i = 0;
	for (i=0;i<4;i++)
	{
		m_animePattern[i] = 1;
		m_animeSpeed[i] = 1;
		m_animeType[i] = 1;
	}

	m_clickSound = 0;
	m_cannotClickSound = 0;
	m_enterSound = 0;
	m_exitSound = 0;
	m_enterWaitTime = 0;
	m_exitWaitTime = 0;
	m_volumeType = 0;

	m_buttonPrintMode = 2;
	m_cancelButtonFlag = 0;
	m_upButtonFlag = 0;
	m_downButtonFlag = 0;
	m_updownReverseFlag = 0;

	m_picTateYoko = 0;

	for (i=0;i<3;i++)
	{
		m_accelKey[i] = 0;
	}

	if (lpCopyFrom != NULL)
	{
		POINT pt;
		if (lpDelta != NULL)
		{
			pt = *lpDelta;
		}
		else
		{
			SIZE sz = lpCopyFrom->GetSize();
			pt.x = sz.cx;
			pt.y = sz.cy;
		}

		CopyParam(lpCopyFrom,pt.x,pt.y);
	}





	int sizeX = m_size.cx;
	int sizeY = m_size.cy;
	int x = m_zahyo.x;
	int y = m_zahyo.y;

	char name[256];

	wsprintf(name,"%sClickTime",buttonName);
	m_setupList->GetInitGameParam(&m_clickTime,name);
	wsprintf(name,"%sSizeX",buttonName);
	m_setupList->GetInitGameParam(&sizeX,name);
	wsprintf(name,"%sSizeY",buttonName);
	m_setupList->GetInitGameParam(&sizeY,name);
	wsprintf(name,"%sPrintX",buttonName);
	m_setupList->GetInitGameParam(&x,name);
	wsprintf(name,"%sPrintY",buttonName);
	m_setupList->GetInitGameParam(&y,name);

	m_size.cx = sizeX;
	m_size.cy = sizeY;

	m_zahyo.x = x;
	m_zahyo.y = y;

	x = m_checkDelta.x;
	y = m_checkDelta.y;

	if (lpCopyFrom == NULL)
	{
		x = 0;
		y = 0;
	}
	wsprintf(name,"%scheckDeltaX",buttonName);
	m_setupList->GetInitGameParam(&x,name);
	wsprintf(name,"%scheckDeltaY",buttonName);
	m_setupList->GetInitGameParam(&y,name);
	m_checkDelta.x = x;
	m_checkDelta.y = y;


	x = m_checkPicZahyo.x;
	y = m_checkPicZahyo.y;
	if (lpCopyFrom == NULL)
	{
		x = 0;
		y = 0;
	}
	wsprintf(name,"%scheckPicX",buttonName);
	m_setupList->GetInitGameParam(&x,name);
	wsprintf(name,"%scheckPicY",buttonName);
	m_setupList->GetInitGameParam(&y,name);
	m_checkPicZahyo.x = x;
	m_checkPicZahyo.y = y;

	sizeX = m_size.cx;
	sizeY = m_size.cy;
	wsprintf(name,"%scheckSizeX",buttonName);
	m_setupList->GetInitGameParam(&sizeX,name);
	wsprintf(name,"%scheckSizeY",buttonName);
	m_setupList->GetInitGameParam(&sizeY,name);
	m_checkSize.cx = sizeX;
	m_checkSize.cy = sizeY;


	int mode = m_buttonPrintMode;
	wsprintf(name,"%sPrintMode",buttonName);
	m_setupList->GetInitGameParam(&mode,name);
	m_buttonPrintMode = mode;

	int cancelFlag = m_cancelButtonFlag;
	wsprintf(name,"%sIsCancelButton",buttonName);
	m_setupList->GetInitGameParam(&cancelFlag,name);
	m_cancelButtonFlag = cancelFlag;

	int upFlag = m_upButtonFlag;
	wsprintf(name,"%sIsUpButton",buttonName);
	m_setupList->GetInitGameParam(&upFlag,name);
	m_upButtonFlag = upFlag;

	int downFlag = m_downButtonFlag;
	wsprintf(name,"%sIsDownButton",buttonName);
	m_setupList->GetInitGameParam(&downFlag,name);
	m_downButtonFlag = downFlag;

	int rev = 0;
	wsprintf(name,"%sUpDownReverse",buttonName);
	m_setupList->GetInitGameParam(&rev,name);
	m_updownReverseFlag = rev;


	for (i=0;i<3;i++)
	{
		wsprintf(name,"%sAccelKey%d",buttonName,i+1);
		LPSTR keyName = NULL;

		if (m_setupList->GetInitGameString(&keyName,name))
		{
			int accelKey = atoi(keyName);
			if (accelKey == 0)
			{
				if ((*keyName) != '0')
				{
					accelKey = (int)(*keyName);
					accelKey &= 0xff;
				}
			}

			m_accelKey[i] = accelKey;
		}
	}



	for (i=0;i<4;i++)
	{
		int pattern = m_animePattern[i];
		if (lpCopyFrom == NULL)
		{
			if (i > 0) pattern = m_animePattern[i-1];
		}

		wsprintf(name,"%sAnimePattern%d",buttonName,i+1);
		m_setupList->GetInitGameParam(&pattern,name);
		m_animePattern[i] = pattern;

		int speed = m_animeSpeed[i];
		if (lpCopyFrom == NULL)
		{
			if (i > 0) speed = m_animeSpeed[i-1];
		}
		wsprintf(name,"%sAnimeSpeed%d",buttonName,i+1);
		m_setupList->GetInitGameParam(&speed,name);
		m_animeSpeed[i] = speed;

		int type = m_animeType[i];
		if (lpCopyFrom == NULL)
		{
			if (i > 0) type = m_animeType[i-1];
		}
		wsprintf(name,"%sAnimeType%d",buttonName,i+1);
		m_setupList->GetInitGameParam(&type,name);
		m_animeType[i] = type;


		x = m_picSrcZahyo[i].x;
		y = m_picSrcZahyo[i].y;

		if ((lpCopyFrom == NULL) || (notSrcPicCopy && m_notCopyFlag))
		{
			x = m_size.cx * i;
			y = 0;
		}


		wsprintf(name,"%sPicSrcX%d",buttonName,i+1);
		m_setupList->GetInitGameParam(&x,name);
		wsprintf(name,"%sPicSrcY%d",buttonName,i+1);
		m_setupList->GetInitGameParam(&y,name);
		m_picSrcZahyo[i].x = x;
		m_picSrcZahyo[i].y = y;
	}

	int tateyoko = m_picTateYoko;
	wsprintf(name,"%sTateYoko",buttonName);
	m_setupList->GetInitGameParam(&tateyoko,name);
	m_picTateYoko = tateyoko;


//	int picOnMemory = 0;
///	int picUseLayerStart = 0;
//	int picUseLayerKosuu = 0;
//	sprintf(name,"%sPicOnMemory",buttonName);
//	m_setupList->GetInitGameParam(&picOnMemory,name);
//	m_picOnMemory = picOnMemory;
//	sprintf(name,"%sPicUseLayerStart",buttonName);
//	m_setupList->GetInitGameParam(&picUseLayerStart,name);
//	m_picUseLayerStart = picUseLayerStart;
//	sprintf(name,"%sPicUseLayerMemory",buttonName);
//	m_setupList->GetInitGameParam(&picUseLayerKosuu,name);
//	m_picUseLayerKosuu = picUseLayerKosuu;




	wsprintf(name,"%sClickSound",buttonName);
	m_setupList->GetInitGameParam(&m_clickSound,name);

	wsprintf(name,"%sBadSound",buttonName);
	m_setupList->GetInitGameParam(&m_cannotClickSound,name);
	
	wsprintf(name,"%sEnterSound",buttonName);
	m_setupList->GetInitGameParam(&m_enterSound,name);

	wsprintf(name,"%sExitSound",buttonName);
	m_setupList->GetInitGameParam(&m_exitSound,name);

	wsprintf(name,"%sVolumeType",buttonName);
	m_setupList->GetInitGameParam(&m_volumeType,name);

	wsprintf(name,"%sEnterWait",buttonName);
	m_setupList->GetInitGameParam(&m_enterWaitTime,name);

	wsprintf(name,"%sExitWait",buttonName);
	m_setupList->GetInitGameParam(&m_exitWaitTime,name);

	wsprintf(name,"%sFilename",buttonName);
	m_setupList->GetInitGameString(&m_filename,name);
}



CSuperButtonSetup::~CSuperButtonSetup()
{
	End();
}

void CSuperButtonSetup::End(void)
{
	ENDDELETECLASS(m_setupList);
}


void CSuperButtonSetup::SetupButtonStatus(CCommonButton* lpButton)
{
	/*

	int sizeX = m_size.cx;
	int sizeY = m_size.cy;
	int x = m_zahyo.x;
	int y = m_zahyo.y;

	char name[256];
	sprintf(name,"%sClickTime",m_buttonName);
	m_setupList->GetInitGameParam(&m_clickTime,name);
	sprintf(name,"%sSizeX",m_buttonName);
	m_setupList->GetInitGameParam(&sizeX,name);
	sprintf(name,"%sSizeY",m_buttonName);
	m_setupList->GetInitGameParam(&sizeY,name);
	sprintf(name,"%sPrintX",m_buttonName);
	m_setupList->GetInitGameParam(&x,name);
	sprintf(name,"%sPrintY",m_buttonName);
	m_setupList->GetInitGameParam(&y,name);

	m_size.cx = sizeX;
	m_size.cy = sizeY;

	m_zahyo.x = x;
	m_zahyo.y = y;

	for (int i=0;i<4;i++)
	{
		int pattern = m_animePattern[i];
		sprintf(name,"%sAnimePattern%d",m_buttonName,i+1);
		m_setupList->GetInitGameParam(&pattern,name);
		m_animePattern[i] = pattern;

		int speed = m_animeSpeed[i];
		sprintf(name,"%sAnimeSpeed%d",m_buttonName,i+1);
		m_setupList->GetInitGameParam(&speed,name);
		m_animeSpeed[i] = speed;

		int type = m_animeType[i];
		sprintf(name,"%sAnimeType%d",m_buttonName,i+1);
		m_setupList->GetInitGameParam(&type,name);
		m_animeType[i] = type;
	}

	sprintf(name,"%sClickSound",m_buttonName);
	m_setupList->GetInitGameParam(&m_clickSound,name);




	sprintf(name,"%sBadSound",m_buttonName);
	m_setupList->GetInitGameParam(&m_cannotClickSound,name);
	
	sprintf(name,"%sEnterSound",m_buttonName);
	m_setupList->GetInitGameParam(&m_enterSound,name);

	sprintf(name,"%sExitSound",m_buttonName);
	m_setupList->GetInitGameParam(&m_exitSound,name);

	sprintf(name,"%sEnterWait",m_buttonName);
	m_setupList->GetInitGameParam(&m_enterWaitTime,name);

	sprintf(name,"%sExitWait",m_buttonName);
	m_setupList->GetInitGameParam(&m_exitWaitTime,name);

	sprintf(name,"%sFilename",m_buttonName);
	m_setupList->GetInitGameString(&m_filename,name);




*/

	lpButton->SetZahyo(GetZahyo());
	lpButton->SetSize(GetSize());


	lpButton->SetClickTime(GetClickTime());
	lpButton->SetButtonPrintMode(GetButtonPrintMode());
	lpButton->SetSize(GetSize());
	lpButton->SetZahyo(GetZahyo());


	lpButton->SetCancelButtonFlag(GetCancelButtonFlag());
	int rev = GetUpDownReverseFlag();

	lpButton->SetUpButtonFlag(GetUpButtonFlag(),rev);
	lpButton->SetDownButtonFlag(GetDownButtonFlag(),rev);

	//key
	int i = 0;
	for (i=0;i<3;i++)
	{
		lpButton->SetAccelKey(GetAccelKey(i),i);
	}

	//pic
	for (i=0;i<4;i++)
	{
		lpButton->SetAnimePattern(i,GetAnimePattern(i));
		lpButton->SetAnimeSpeed(i,GetAnimeSpeed(i));
		lpButton->SetAnimeType(i,GetAnimeType(i));
		lpButton->SetSrcPicZahyo(GetPicSrcZahyo(i),i);
	}

	lpButton->SetFileName(GetFileName());
	lpButton->SetCheckSize(GetCheckSize());
	lpButton->SetCheckPicZahyo(GetCheckPicZahyo());
	lpButton->SetCheckDelta(GetCheckDelta());
	lpButton->SetPicTateYoko(GetPicTateYoko());

	//sound
	lpButton->SetClickSound(GetClickSound());
	lpButton->SetCannotClickSound(GetCannotClickSound());
	lpButton->SetEnterSound(GetEnterSound());
	lpButton->SetExitSound(GetExitSound());
	lpButton->SetEnterSoundWait(GetEnterWaitTime());
	lpButton->SetExitSoundWait(GetExitWaitTime());
	lpButton->SetVolumeType(GetVolumeType());
}

void CSuperButtonSetup::CopyParam(CSuperButtonSetup* lpSetup,int deltaX,int deltaY)
{
	m_clickTime = lpSetup->GetClickTime();
	m_size = lpSetup->GetSize();
	m_zahyo = lpSetup->GetZahyo();
	m_zahyo.x += deltaX;
	m_zahyo.y += deltaY;
	m_filename = lpSetup->GetFileName();

	m_checkPicZahyo = lpSetup->GetCheckPicZahyo();
	m_checkSize = lpSetup->GetCheckSize();

	int i = 0;
	for (i=0;i<4;i++)
	{
		m_animePattern[i] = lpSetup->GetAnimePattern(i);
		m_animeSpeed[i] = lpSetup->GetAnimeSpeed(i);
		m_animeType[i] = lpSetup->GetAnimeType(i);
		m_picSrcZahyo[i] = lpSetup->GetPicSrcZahyo(i);
	}

	m_checkDelta = lpSetup->GetCheckDelta();

	for (i=0;i<3;i++)
	{
///		m_accelKey[i] = lpSetup->GetAccelKey(i);
	}

	m_clickSound = lpSetup->GetClickSound();
	m_cannotClickSound = lpSetup->GetCannotClickSound();
	m_enterSound = lpSetup->GetEnterSound();
	m_exitSound = lpSetup->GetExitSound();

	m_enterWaitTime = lpSetup->GetEnterWaitTime();
	m_exitWaitTime = lpSetup->GetEnterWaitTime();

	m_buttonPrintMode = lpSetup->GetButtonPrintMode();
	m_volumeType = lpSetup->GetVolumeType();
	//not copy cancel,up,down buttonflag
	//not copy updown rev

	m_picTateYoko = lpSetup->GetPicTateYoko();

}

void CSuperButtonSetup::SetZahyoIfCan(POINT pt)
{
	int x = pt.x;
	int y = pt.y;

	char name[256];

	wsprintf(name,"%sPrintX",m_buttonName);
	m_setupList->GetInitGameParam(&x,name);
	wsprintf(name,"%sPrintY",m_buttonName);
	m_setupList->GetInitGameParam(&y,name);

	m_zahyo.x = x;
	m_zahyo.y = y;
}



/*_*/

