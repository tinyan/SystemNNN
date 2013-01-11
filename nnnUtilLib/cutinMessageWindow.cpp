#include <windows.h>

#include "..\nyanlib\include\commonMacro.h"
#include "..\nyanlib\include\picture.h"

#include "cutinMessageWindow.h"

char CCutinMessageWindow::m_defaultTagName[] = "ta_cutinwindow";


CCutinMessageWindow::CCutinMessageWindow(LPSTR tagName,int buffer)
{
	if (tagName == NULL)
	{
		memcpy(m_tagName,m_defaultTagName,strlen(m_defaultTagName)+1);
	}
	else
	{
		memcpy(m_tagName,tagName,strlen(tagName)+1);
	}

	m_bufferKosuu = buffer;
	m_pic = new CPicture*[m_bufferKosuu];
	for (int i=0;i<m_bufferKosuu;i++)
	{
		m_pic[i] = NULL;
	}
	m_pic[0] = new CPicture();

	m_bufferNumber = new int[m_bufferKosuu];
	for (int i=0;i<m_bufferKosuu;i++)
	{
		m_bufferNumber[i] = -1;
	}

	m_windowPercent = 100;

	m_nowBufferNumber = -1;
}

CCutinMessageWindow::~CCutinMessageWindow()
{
	End();
}

void CCutinMessageWindow::End(void)
{
	DELETEARRAY(m_bufferNumber);
	if (m_pic != NULL)
	{
		for (int i=0;i<m_bufferKosuu;i++)
		{
			ENDDELETECLASS(m_pic[i]);
		}
		DELETEARRAY(m_pic);
	}
}

	
BOOL CCutinMessageWindow::LoadPic(int n)
{
	int found = -1;
	for (int i=0;i<m_bufferKosuu;i++)
	{
		if (m_bufferNumber[i] == n)
		{
			found = i;
			break;
		}
	}

	if (found != -1)
	{
		m_nowBufferNumber = found;
		return TRUE;
	}

	int found2 = -1;
	for (int i=0;i<m_bufferKosuu;i++)
	{
		if (m_bufferNumber[i] == -1)
		{
			found2 = i;
			break;
		}
	}

	if (found2 != -1)
	{
		if (LoadPicRoutine(found2,n))
		{
			m_bufferNumber[found2] = n;
			m_nowBufferNumber = found2;
			return TRUE;
		}
		else
		{
			m_nowBufferNumber = -1;
			return FALSE;
		}
	}

	int k = (m_nowBufferNumber + 1) % m_bufferKosuu;
	if (LoadPicRoutine(k,n))
	{
		m_bufferNumber[k] = n;
		m_nowBufferNumber = k;
		return TRUE;
	}

	m_nowBufferNumber = -1;

	return FALSE;
}


BOOL CCutinMessageWindow::LoadPicRoutine(int buffer,int n)
{
	char filename[1024];
	wsprintf(filename,"sys\\%s%d",m_tagName,n);
	
	if (m_pic[buffer] == NULL)
	{
		m_pic[buffer] = new CPicture();
	}

	return m_pic[buffer]->LoadDWQ(filename);
}


void CCutinMessageWindow::Print(POINT pt)
{
	if (m_nowBufferNumber == -1) return;
	if (m_pic[m_nowBufferNumber] == NULL) return;

	int putX = pt.x;
	int putY = pt.y;
	int srcX = 0;
	int srcY = 0;
	SIZE sz = m_pic[m_nowBufferNumber]->GetPicSize();
	int sizeX = sz.cx;
	int sizeY = sz.cy;
	if (m_windowPercent == 100)
	{
		m_pic[m_nowBufferNumber]->Put(pt.x,pt.y,TRUE);
	}
	else
	{
		m_pic[m_nowBufferNumber]->TransLucentBlt3(putX,putY,srcX,srcY,sizeX,sizeY,m_windowPercent);
	}
}


/*_*/


