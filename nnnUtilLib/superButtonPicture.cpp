//
// systempicture.cpp
//

#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"


#include "superButtonPicture.h"

CSuperButtonPicture* CSuperButtonPicture::m_this = NULL;
CPicture** CSuperButtonPicture::m_ppPic = NULL;


CSuperButtonPicture::CSuperButtonPicture()
{
	m_ppPic = new CPicture* [SUPERBUTTON_PICKOSUU_MAX];

	for (int i=0;i<SUPERBUTTON_PICKOSUU_MAX;i++)
	{
		m_ppPic[i] = NULL;
	}
}


CSuperButtonPicture::~CSuperButtonPicture()
{
	End();
}

void CSuperButtonPicture::End(void)
{
	if (m_ppPic != NULL)
	{
		for (int i=0;i<SUPERBUTTON_PICKOSUU_MAX;i++)
		{
			ENDDELETECLASS(m_ppPic[i]);
		}
		DELETEARRAY(m_ppPic);
	}
}



//static
CPicture* CSuperButtonPicture::GetPicture(int n)
{
	if ((n<0) || (n>=SUPERBUTTON_PICKOSUU_MAX)) n = 0;

	CPicture* lpPic = m_ppPic[n];
	if (lpPic == NULL)
	{
		lpPic = new CPicture();
		m_ppPic[n] = lpPic;
	}

	return lpPic;
}



/*_*/

