//
//
//

//#include <windows.h>

#include "animeControl.h"



CAnimeControl::CAnimeControl()
{
	SetParam();
	Init();
	Calcu(0);
}

CAnimeControl::~CAnimeControl()
{
	End();
}

void CAnimeControl::End(void)
{
}


void CAnimeControl::SetParam(int type,int pattern,int speed)
{
	m_animeType = type;
	m_animePattern = pattern;
	m_animeSpeed = speed;
}


void CAnimeControl::Init(int count)
{
	m_animeCount = count;
	m_picPattern1 = 0;
	m_picPattern2 = 0;
	m_picPercent = 100;
}


int CAnimeControl::Calcu(int cnt)
{
	int loopEndFlag = 0;

	int type = m_animeType;
	int speed = m_animeSpeed;
	int count = m_animeCount;
	int pattern = m_animePattern;

	if (speed<1) speed = 1;

	int revFlag = 0;
	int dv = pattern;

	if ((type == 3) || (type == 4) || (type == 7) || (type == 8))
	{
		dv = (pattern-1) * 2;
		if (dv<1) dv = 1;
		revFlag = 1;
	}

	int dv2 = dv;
	dv *= speed;

	int limitFlag = 0;
	if ((type == 2) || (type == 4) || (type == 6) || (type == 8))
	{
		limitFlag = 1;
	}

	count += cnt;
	if (limitFlag)
	{
		if (count >= dv)
		{
			count = dv;
			loopEndFlag = 1;
		}
	}
	else
	{
		if (count >= dv)
		{
			loopEndFlag = 1;
		}
		count %= dv;
	}

	m_animeCount = count;




	int pic1 = count / speed;
	int pic2 = pic1+1;
	
	if (limitFlag)
	{
		int limData = dv2-1;
		if (revFlag) limData = dv2;

		if (pic1>=dv2) pic1 = limData;
		if (pic2>=dv2) pic2 = limData;
	}

	pic2 %= dv2;

	int percent = 100;

	if (revFlag)
	{
		if (pic1 >= pattern) pic1 = (pattern-1)*2 - pic1;
		if (pic2 >= pattern) pic2 = (pattern-1)*2 - pic2;
	}

	if (type >= 5)
	{
		percent = 100 * (speed - (count % speed));
		percent /= speed;
	}

	m_picPattern1 = pic1;
	m_picPattern2 = pic2;
	m_picPercent = percent;

	return loopEndFlag;
}


int CAnimeControl::GetAnimePic1(void)
{
	return m_picPattern1;
}

int CAnimeControl::GetAnimePic2(void)
{
	return m_picPattern2;
}

int CAnimeControl::GetAnimePercent(void)
{
	return m_picPercent;
}
