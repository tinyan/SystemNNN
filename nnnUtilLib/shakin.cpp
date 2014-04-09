//
//
//

#include <windows.h>

#include "shakin.h"


CShakin::CShakin()
{
	SetFrame();
	SetMax();
	SetKikan();
	Clear();
}


CShakin::~CShakin()
{
	End();
}


void CShakin::End(void)
{
}



void CShakin::SetFrame(int frameTime)
{
	m_frameTime = frameTime;
}

void CShakin::SetMax(int mx)
{
	m_max = mx;
}

void CShakin::SetKikan(int kikan)
{
	m_kikan = kikan;
}

void CShakin::Clear(void)
{
	m_shakin = 0;
	m_hensaiYotei = 0;
	m_hensaiFlag = TRUE;
}

void CShakin::HensaiFrame(int frame)
{
	m_shakin -= frame * m_frameTime;
	//������1�t���[���Ԃ�܂�
	if (m_shakin<-m_frameTime) m_shakin = -m_frameTime;
	m_hensaiFlag = TRUE;
}

void CShakin::HensaiTime(int tm)
{
	m_shakin -= tm;
	//������1�t���[���Ԃ�܂�
	if (m_shakin<-m_frameTime) m_shakin = -m_frameTime;
	m_hensaiFlag = TRUE;
}


void CShakin::BeginFrame(int tm)
{
	m_hensaiFlag = FALSE;

	m_shakin += tm;

	if (m_shakin < m_frameTime)
	{
		m_hensaiYotei = 0;
		return;
	}

	//���̕ԍϑ��x�ŗ\����Ԉȓ��ɕԋp�ł��Ȃ��Ȃ�ӂ₷
	if ((m_hensaiYotei*m_kikan*m_frameTime) < m_shakin)
	{
		m_hensaiYotei++;
	}
	
	//���̕ԍϑ��x��肨�Ƃ��Ă��\����ԓ��ɕԋp�ł���Ȃ�ւ炷
	if (m_hensaiYotei>1)
	{
		if (((m_hensaiYotei-1)*m_kikan*m_frameTime) > m_shakin)
		{
			m_hensaiYotei--;
		}
	}


	if (m_hensaiYotei > m_max) m_hensaiYotei = m_max;
}


void CShakin::EndFrame(void)
{
	if (m_hensaiFlag == FALSE)
	{
		Clear();
	}
}


int CShakin::GetHensaiFrame(int kaeseru)
{
	if (kaeseru < 0) return m_hensaiYotei;

	int kaese = m_hensaiYotei;
	if (kaese > kaeseru) kaese = kaeseru;

	return kaese;
}

int CShakin::GetShakinTime(int kaeseru)
{
	return m_shakin;
}



/*_*/



