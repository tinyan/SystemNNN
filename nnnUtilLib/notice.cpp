//
// gameMouse.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"

#include "..\nyanLib\include\allGeo.h"

#include "taihi.h"

#include "animeControl.h"

#include "FloatingLayer.H"
#include "notice.h"


char CNotice::m_defaultNoticePicFileName[] = "ta_notice";

char CNotice::m_soundTypeName[][32] = 
{
	"start","wait","End"
};


CNotice::CNotice(CTaihi* lpTaihi, int taihiLayer) : CFloatingLayer(lpTaihi, taihiLayer)
{
	LoadSetupFile("notice");	

	m_noticeKosuu = 1;
	GetInitGameParam(&m_noticeKosuu,"noticeNumber");

	int mk = m_noticeKosuu;
	if (mk<1) mk = 1;


	m_startZahyo = new POINT[mk];
	m_waitZahyo = new POINT[mk];
	m_endZahyo = new POINT[mk];
	m_startTime = new int[mk];
	m_waitTime = new int[mk];
	m_endTime = new int[mk];
	m_startPercent = new int[mk];
	m_waitPercent = new int[mk];
	m_endPercent = new int[mk];

	m_sound = new int[mk*3];
//	m_pic = new CPicture* [mk];

//	for (int i=0;i<m_noticeKosuu;i++)
//	{
//		m_pic[i] = new CPicture();
//	}

	m_startZahyo[0].x = 0;
	m_startZahyo[0].y = 0;
	m_startTime[0] = 30;
	m_startPercent[0] = 100;

	m_sound[0] = 0;
	m_sound[1] = 0;
	m_sound[2] = 0;

	m_sameDontSetFlag = 1;
	GetInitGameParam(&m_sameDontSetFlag,"sameDontSetFlag");


	for (int i=0;i<m_noticeKosuu;i++)
	{
		int from = i - 1;
		if (from<0) from = 0;

		int x = m_startZahyo[from].x;
		int y = m_startZahyo[from].y;

		char name[256];
		wsprintf(name,"startX%d",i+1);
		GetInitGameParam(&x,name);
		wsprintf(name,"startY%d",i+1);
		GetInitGameParam(&y,name);

		m_startZahyo[i].x = x;
		m_startZahyo[i].y = y;

		if (i == 0)
		{
			x = m_startZahyo[0].x;
			y = m_startZahyo[0].y;
		}
		else
		{
			x = m_waitZahyo[from].x;
			y = m_waitZahyo[from].y;
		}
		wsprintf(name,"waitX%d",i+1);
		GetInitGameParam(&x,name);
		wsprintf(name,"waitY%d",i+1);
		GetInitGameParam(&y,name);

		m_waitZahyo[i].x = x;
		m_waitZahyo[i].y = y;


		if (i == 0)
		{
			x = m_waitZahyo[0].x;
			y = m_waitZahyo[0].y;
		}
		else
		{
			x = m_endZahyo[from].x;
			y = m_endZahyo[from].y;
		}
		wsprintf(name,"endX%d",i+1);
		GetInitGameParam(&x,name);
		wsprintf(name,"endY%d",i+1);
		GetInitGameParam(&y,name);

		m_endZahyo[i].x = x;
		m_endZahyo[i].y = y;

		int tm = m_startTime[from];
		wsprintf(name,"startTime%d",i+1);
		GetInitGameParam(&tm,name);
		m_startTime[i] = tm;

		if (i==0)
		{
			tm = m_startTime[0];
		}
		else
		{
			tm = m_waitTime[from];
		}
		wsprintf(name,"waitTime%d",i+1);
		GetInitGameParam(&tm,name);
		m_waitTime[i] = tm;

		if (i==0)
		{
			tm = m_waitTime[0];
		}
		else
		{
			tm = m_endTime[from];
		}
		wsprintf(name,"endTime%d",i+1);
		GetInitGameParam(&tm,name);
		m_endTime[i] = tm;

		int ps = m_startPercent[from];
		wsprintf(name,"startPercent%d",i+1);
		GetInitGameParam(&ps,name);
		m_startPercent[i] = ps;

		if (i==0)
		{
			ps = m_startPercent[0];
		}
		else
		{
			ps = m_waitPercent[from];
		}
		wsprintf(name,"waitPercent%d",i+1);
		GetInitGameParam(&ps,name);
		m_waitPercent[i] = ps;

		if (i==0)
		{
			ps = m_waitPercent[0];
		}
		else
		{
			ps = m_endPercent[from];
		}
		wsprintf(name,"endPercent%d",i+1);
		GetInitGameParam(&ps,name);
		m_endPercent[i] = ps;


		for (int k=0;k<3;k++)
		{
			int sound = 0;
			if (i > 0)
			{
				sound = m_sound[(i-1)*3+k];
			}

			wsprintf(name,"%sSound%d",m_soundTypeName[k],i+1);
			GetInitGameParam(&sound,name);

			m_sound[i*3+k] = sound;
		}
	}

	m_pic = new CPicture();

	m_filenameTag = m_defaultNoticePicFileName;
	GetInitGameString(&m_filenameTag,"filenameNoticeTag");

	m_seatNumber = -1;

	m_sizeX = 160;
	m_sizeY = 80;

	GetInitGameParam(&m_sizeX,"sizeX");
	GetInitGameParam(&m_sizeY,"sizeY");

	m_blockX = 1;
	m_blockY = 1;
	GetInitGameParam(&m_blockX,"blockX");
	GetInitGameParam(&m_blockY,"blockY");


	m_bufferMax = 1;
	GetInitGameParam(&m_bufferMax,"bufferMax");
	if (m_bufferMax < 1) m_bufferMax = 1;
	m_buffer = new int[m_bufferMax];
	m_bufferKosuu = 0;


	CreateLayer(m_sizeX,m_sizeY);

	Clear();
}


CNotice::~CNotice()
{
	End();
}


void CNotice::End(void)
{
	DELETEARRAY(m_buffer);
//	if (m_pic != NULL)
//	{
//		for (int i=0;i<m_noticeKosuu;i++)
//		{
//			ENDDELETECLASS(m_pic[i]);
//		}
//		DELETEARRAY(m_pic);
//	}

	ENDDELETECLASS(m_pic);

	DELETEARRAY(m_sound);

	DELETEARRAY(m_endPercent);
	DELETEARRAY(m_waitPercent);
	DELETEARRAY(m_startPercent);

	DELETEARRAY(m_endTime);
	DELETEARRAY(m_waitTime);
	DELETEARRAY(m_startTime);

	DELETEARRAY(m_endZahyo);
	DELETEARRAY(m_waitZahyo);
	DELETEARRAY(m_startZahyo);
}

void CNotice::Start(int n)
{
	if ((n<0)  || (n>=m_noticeKosuu)) return;

	if (m_sameDontSetFlag)
	{
		for (int i=0;i<m_bufferKosuu;i++)
		{
			if (n == m_buffer[i]) return;
		}
	}



	BOOL newPicFlag = FALSE;
	if (m_bufferKosuu == 0)
	{
		newPicFlag = TRUE;
	}
	else
	{
		if (m_bufferKosuu >= m_bufferMax)
		{
			newPicFlag = TRUE;
			//‚Â‚ß‚é
			DecBuffer();
		}
	}


	m_buffer[m_bufferKosuu] = n;
	m_bufferKosuu++;

	if (newPicFlag)
	{
		NewPic();
	}
}

void CNotice::Clear(void)
{
//	m_number = -1;
	m_bufferKosuu = 0;
}


int CNotice::Print(BOOL taihiFlag)
{
	if (m_bufferKosuu <= 0) return -1;
	int n = m_buffer[0];

	if (n < 0) return -1;
	int sound = -1;

	m_count++;
	if ((m_count <= 1) && (m_printMode == 0))
	{
		return m_sound[n*3+0];
	}

	int fromX = 0;
	int fromY = 0;
	int toX = 0;
	int toY = 0;

	int fromPercent = 100;
	int toPercent = 100;

	int dv = 1;

	if (m_printMode == 0)
	{
		dv = m_startTime[n];

		fromX = m_startZahyo[n].x;
		fromY = m_startZahyo[n].y;
		toX = m_waitZahyo[n].x;
		toY = m_waitZahyo[n].y;

		fromPercent = m_startPercent[n];
		toPercent = m_waitPercent[n];
	}
	else if (m_printMode == 1)
	{
		dv = m_waitTime[n];

		fromX = m_waitZahyo[n].x;
		fromY = m_waitZahyo[n].y;
		toX = m_waitZahyo[n].x;
		toY = m_waitZahyo[n].y;

		fromPercent = m_waitPercent[n];
		toPercent = m_waitPercent[n];
	}
	else
	{
		dv = m_endTime[n];

		fromX = m_waitZahyo[n].x;
		fromY = m_waitZahyo[n].y;
		toX = m_endZahyo[n].x;
		toY = m_endZahyo[n].y;

		fromPercent = m_waitPercent[n];
		toPercent = m_endPercent[n];
	}

	if (dv<1) dv = 0;

	int putX = fromX + ((toX - fromX) * m_count) / dv;
	int putY = fromY + ((toY - fromY) * m_count) / dv;
	int ps = fromPercent + ((toPercent - fromPercent) * m_count) / dv;

	if (m_count >= dv)
	{
		m_count = 0;
		m_printMode++;
		if (m_printMode > 2)
		{
			DecBuffer();
			if (m_bufferKosuu > 0)
			{
				NewPic();
			}
			else
			{
				Clear();
			}
			return -1;
		}
		sound = m_sound[n*3+m_printMode];
	}


	//zahyo

	if (taihiFlag)
	{
		Taihi(putX,putY);
	}
	
	int sizeX = m_sizeX;
	int sizeY = m_sizeY;

	int nx = n % m_blockX;
	int ny = (n / m_blockX) % m_blockY;

	int srcX = sizeX * nx;
	int srcY = sizeY * ny;
	CAreaControl::AddArea(putX,putY,sizeX,sizeY);

	if (ps >= 100)
	{
		m_pic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
	}
	else if (ps > 0)
	{
		m_pic->TransLucentBlt3(putX,putY,srcX,srcY,sizeX,sizeY,ps);
	}

	return sound;
}

void CNotice::NewPic(void)
{
	int n = m_buffer[0];

	int seatNumber = (n / (m_blockX * m_blockY));
	if (m_seatNumber != seatNumber)
	{
		//load
		char filename[256];
		if (seatNumber == 0)
		{
			wsprintf(filename,"sys\\%s",m_filenameTag);
		}
		else
		{
			wsprintf(filename,"sys\\%s%d",m_filenameTag,seatNumber+1);
		}
		m_pic->LoadDWQ(filename);
		m_seatNumber = seatNumber;
	}

	m_printMode = 0;
	m_count = 0;
}

void CNotice::DecBuffer(void)
{
	if (m_bufferKosuu <= 0) return;

	for (int i=0;i<m_bufferKosuu-1;i++)
	{
		m_buffer[i] = m_buffer[i+1];
	}
	m_buffer[m_bufferKosuu-1] = -1;

	m_bufferKosuu--;
}

/*_*/

