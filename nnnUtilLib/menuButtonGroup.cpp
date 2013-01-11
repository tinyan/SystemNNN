//
// menubuttongroup.cpp
//

#include <windows.h>
#include <Math.h>

#include "..\nyanLib\include\commonmacro.h"



#include "nnnButtonStatus.h"
//#include "myMouseStatus.h"
#include "commonbutton.h"



#include "menubuttongroup.h"
#include "menuButtonSetup.h"


#include "superButtonSetup.h"
//#include "..\nnnlib\gameCallBack.h"



CMenuButtonGroup::CMenuButtonGroup(CMenuButtonSetup* lpMenuButtonSetup,CPicture* lpBG)
{
	m_extMode = 0;

	m_menuButtonSetup = lpMenuButtonSetup;

	m_extModeKosuu = m_menuButtonSetup->GetExtModeKosuu();
	m_basicButtonKosuu = m_menuButtonSetup->GetBasicButtonKosuu();
	m_extButtonKosuu = m_menuButtonSetup->GetExtButtonKosuu();

	m_buttonKosuu = m_basicButtonKosuu + m_extButtonKosuu;

	int superMode = m_menuButtonSetup->GetSuperMode();
	m_superMode = superMode;

	m_ppButton = new CCommonButton* [m_buttonKosuu*(m_extModeKosuu+1)];

	for (int j=0;j<m_extModeKosuu+1;j++)
	{
		for (int i=0;i<m_buttonKosuu;i++)
		{
			int k = i + j * m_buttonKosuu;

			m_ppButton[k] = new CCommonButton();

			CSuperButtonSetup* superSetup = m_menuButtonSetup->GetSuperSetup(i,j);
			superSetup->SetupButtonStatus(m_ppButton[k]);

			if (lpBG != NULL)
			{
				m_ppButton[k]->SetBG(lpBG);
			}
		}
	}

	m_pExistFlag = new BOOL[m_buttonKosuu*(m_extModeKosuu+1)];
	m_pEnableFlag = new BOOL[m_buttonKosuu*(m_extModeKosuu+1)];

	for (int i=0;i<m_buttonKosuu*(m_extModeKosuu+1);i++)
	{
		m_pExistFlag[i] = TRUE;
		m_pEnableFlag[i] = TRUE;
	}

	m_status = 0;
	m_buttonNumber = -1;
}


CMenuButtonGroup::~CMenuButtonGroup()
{
	End();
}


void CMenuButtonGroup::End(void)
{
	DELETEARRAY(m_pEnableFlag);
	DELETEARRAY(m_pExistFlag);
	if (m_ppButton != NULL)
	{
		for (int i=0;i<m_buttonKosuu*(m_extModeKosuu +1);i++)
		{
			ENDDELETECLASS(m_ppButton[i]);
		}
		DELETEARRAY(m_ppButton);
	}
}


void CMenuButtonGroup::SetCancelButton(int n,BOOL flg)
{
	if ((n<0) || (n>=m_buttonKosuu)) return;

	for (int i=0;i<m_extModeKosuu+1;i++)
	{
		int k = n + i*m_buttonKosuu;
		CCommonButton* backButton = m_ppButton[k];
		if (backButton != NULL)
		{
			backButton->SetCancelButtonFlag();
		}
	}
}



void CMenuButtonGroup::SetExist(int n, BOOL flg,int extMode)
{
	if ((n<0) || (n>=m_buttonKosuu)) return;
	int st = 0;
	int ed = m_extModeKosuu;
	if (extMode != -1)
	{
		st = extMode;
		ed = extMode;
	}

	for (int i=st;i<=ed;i++)
	{
//		CCommonButton* button = m_ppButton[n+m_buttonKosuu*i];
//		if (button != NULL)
//		{
//			button->SetExist(flg);
//		}
		m_pExistFlag[n+m_buttonKosuu*i] = flg;
	}
}

void CMenuButtonGroup::SetEnable(int n, BOOL flg,int extMode)
{
	if ((n<0) || (n>=m_buttonKosuu)) return;

	int st = 0;
	int ed = m_extModeKosuu;
	if (extMode != -1)
	{
		st = extMode;
		ed = extMode;
	}

	for (int i=st;i<=ed;i++)
	{
//		CCommonButton* button = m_ppButton[n+m_buttonKosuu*i];
//		if (button != NULL)
//		{
//			button->SetEnable(flg);
//		}
		m_pEnableFlag[n+m_buttonKosuu*i] = flg;
	}
}




void CMenuButtonGroup::Init(void)
{
	m_status = 0;
	m_buttonNumber = -1;

	int i = 0;

	int extMode = GetNowExtMode();


	//標準ボタン存在設定
	for (i=0;i<m_buttonKosuu;i++)
	{
		int n = i + extMode * m_buttonKosuu;

		BOOL existFlag = m_pExistFlag[n];
		BOOL enableFlag = m_pEnableFlag[n];

		CCommonButton* button = m_ppButton[n];
		if (button != NULL)
		{
			if (m_menuButtonSetup->CheckButtonExist(i,extMode) == FALSE) existFlag = FALSE;
			if (m_menuButtonSetup->CheckButtonEnable(i,extMode) == FALSE) enableFlag = FALSE;
			button->SetExist(existFlag);
			button->SetEnable(enableFlag);
		}
	}


	for (i=0;i<m_buttonKosuu;i++)
	{
		int n = i + extMode * m_buttonKosuu;
		CCommonButton* button = m_ppButton[n];
		if (button != NULL)
		{
			button->Init();
		}
	}
}








/*

void CMenuButtonGroup::SetAllButtonZahyo(int extMode)
{
	for (int i=0;i<m_buttonKosuu;i++)
	{
		POINT pt = m_menuButtonSetup->GetZahyo(i,extMode);
		
		CCommonButton* button = m_ppButton[i];
		if (button != NULL)
		{
			button->SetZahyo(pt);
		}
	}
}
*/

int CMenuButtonGroup::Calcu(CInputStatus* lpInput,int clickFlag )
{
	if (m_superMode)
	{
		return CalcuSuper(lpInput,clickFlag);
	}

	return NNNBUTTON_NOTHING;
}



int CMenuButtonGroup::CalcuSuper(CInputStatus* lpInput,int clickFlag)
{
	int n = m_buttonKosuu * m_extMode;

	if (m_status != 0)
	{
		for (int i=0;i<m_buttonKosuu;i++)
		{
			if (i != m_buttonNumber)
			{
				CCommonButton* button = m_ppButton[n+i];
				if (button != NULL)
				{
					button->Calcu(NULL);
				}
			}
		}

		CCommonButton* button = m_ppButton[n+m_buttonNumber];
		if (button != NULL)
		{
			int rt = button->Calcu(lpInput);	//NULLでもいいか?

			int st = rt & NNNBUTTON_STATUSMASK;
			if (st == NNNBUTTON_NUMBER)
			{
				return CCommonButton::ChangeButtonData(rt,m_buttonNumber);
			}

			return rt;
		}

		//error
		return NNNBUTTON_NOTHING;
	}


	int returnCode = NNNBUTTON_NOTHING;

	for (int i=0;i<m_buttonKosuu;i++)
	{
		CCommonButton* button = m_ppButton[n+i];
		if (button != NULL)
		{
			if (m_status == 0)
			{
				int rt = button->Calcu(lpInput,clickFlag);

				if (rt != NNNBUTTON_NOTHING)
				{
					int st = rt & NNNBUTTON_STATUSMASK;

					if (st == NNNBUTTON_STARTCLICK)
					{
						m_status = 1;
						m_buttonNumber = i;
						returnCode = rt;
					}
					else if (st == NNNBUTTON_NUMBER)
					{
						m_status = 1;
						m_buttonNumber = i;
						returnCode = CCommonButton::ChangeButtonData(rt,m_buttonNumber);
					}
					else
					{
						returnCode = rt;//sound etc
					}

					if ((st == NNNBUTTON_ENTER) || (st == NNNBUTTON_EXIT))
					{
						if (m_menuButtonSetup->GetMenuAnimeAdjustFlag())
						{
							for (int i=0;i<m_buttonKosuu;i++)
							{
								CCommonButton* button2 = m_ppButton[n+i];
								if (button2 != NULL)
								{
									button2->ResetAnimeCount();
								}
							}
						}
					}
				}
			}
			else
			{
				button->Calcu(NULL);
			}
		}
	}

	return returnCode;
}



void CMenuButtonGroup::Print(BOOL mustPrintFlag)
{
	int n = m_buttonKosuu * m_extMode;

	for (int i=0;i<m_buttonKosuu;i++)
	{
		CCommonButton* button = m_ppButton[n+i];
		if (button != NULL)
		{
			if (button->GetExist())
			{
				button->Print(mustPrintFlag);
			}
		}
	}
}


void CMenuButtonGroup::AppearPrint(int count,int countMax,int type,POINT deltaPoint)
{
	//type bit0:半透明処理

	int n = m_buttonKosuu * m_extMode;

	int dv = countMax;
	if (dv<1) dv = 1;

	int percent = 100;
	if (type & 1)
	{
		percent = (100 * count) / dv;
		if (percent < 0) percent = 0;
		if (percent > 100) percent = 100;
	}

	POINT delta;
	int dx = (deltaPoint.x * (dv-count)) / dv;
	int dy = (deltaPoint.y * (dv-count)) / dv;
	delta.x = dx;
	delta.y = dy;

	int type2 = type / 2;

	if (type2== 0)
	{
		for (int i=0;i<m_buttonKosuu;i++)
		{
			CCommonButton* button = m_ppButton[n+i];
			if (button != NULL)
			{
				if (button->GetExist())
				{
					if (percent > 0)
					{
						button->Put(delta,percent);
					}
				}
			}
		}
	}
	
	//2:あつまってくる 4:まわりながらあつまってくる
	if ((type2 == 1) || (type2 == 2))
	{
		double dth = 0.0;
		if (type2 == 2)
		{
			dth = (double)count;
			dth /= (double)dv;
			dth *= 3.14159*2;
		}

		for (int i=0;i<m_buttonKosuu;i++)
		{
			CCommonButton* button = m_ppButton[n+i];
			if (button != NULL)
			{
				if (button->GetExist())
				{
					if (percent > 0)
					{
						double th = (double)i;
						th /= (double)m_buttonKosuu;
						th *= 3.14159*2;
						th += dth;


						double cosTH = cos(th);
						double sinTH = sin(th);

						double dx2 = (double)dx;
						double dy2 = (double)dy;

						int dx3 = (int)(dx2 * cosTH - dy2 * sinTH + 0.5);
						int dy3 = (int)(dx2 * sinTH + dy2 * cosTH + 0.5);

						delta.x = dx3;
						delta.y = dy3;

						button->Put(delta,percent);
					}
				}
			}
		}

	}

	//6 8 10 拡大しながら たてよこ、たて、よこ 
	if ((type2== 3) || (type2 == 4) || (type2 == 5))
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

		for (int i=0;i<m_buttonKosuu;i++)
		{
			CCommonButton* button = m_ppButton[n+i];
			if (button != NULL)
			{
				if (button->GetExist())
				{
					if (percent > 0)
					{
						button->StretchPut(multiX,multiY,delta,percent);
					}
				}
			}
		}
	}

	if ((type2 >= 6) && (type2 <=11))
	{
		SpecialPrint(count,countMax,type2-6);
	}
}


void CMenuButtonGroup::SpecialPrint(int count,int countMax,int type)
{
	int n = m_buttonKosuu * m_extMode;

	int ps100 = (count * 10000) / countMax;
	if (ps100 < 0) ps100 = 0;
	if (ps100 > 10000) ps100 = 10000;

	for (int i=0;i<m_buttonKosuu;i++)
	{
		CCommonButton* button = m_ppButton[n+i];
		if (button != NULL)
		{
			if (button->GetExist())
			{

				int delay = 10000 / (m_buttonKosuu*2+1);

				int  k = ps100 - i * delay;
				if (k>=0)
				{

					int dv = 10000 - m_buttonKosuu * delay;
					if (dv<1) dv = 1;

					int ps = (k * 100) / dv;
					if (ps > 100) ps = 100;


					switch (type)
					{
					case 0:
						button->PutInFromUp(ps);
						break;
					case 1:
						button->PutInFromDown(ps);
						break;
					case 2:
						button->PutInFromLeft(ps);
						break;
					case 3:
						button->PutInFromRight(ps);
						break;
					case 4:
						button->PutInFromCenterUpDown(ps);
						break;
					case 5:
						button->PutInFromCenterLeftRight(ps);
						break;
					}
				}
			}
		}
	}

}


void CMenuButtonGroup::SetExtMode(int extMode)
{
	if (extMode < 0) extMode = 0;
	if (extMode > m_extModeKosuu) extMode = m_extModeKosuu;

	m_extMode = extMode;
}


void CMenuButtonGroup::SetPicture(int n,CPicture* lpPic,int extMode)
{
	int st = 0;
	int ed = m_extModeKosuu;
	if (extMode != -1)
	{
		st = extMode;
		ed = extMode;
	}

	for (int j=st;j<=ed;j++)
	{
		CCommonButton* button = m_ppButton[j*m_buttonKosuu+n];
		if (button != NULL)
		{
			button->SetPicture(lpPic);
		}
	}
}

CPicture* CMenuButtonGroup::GetPicture(int n,int extMode)
{
	CCommonButton* button = m_ppButton[extMode*m_buttonKosuu+n];
	if (button != NULL)
	{
		return button->GetPicture();
	}

	return NULL;
}

LPSTR CMenuButtonGroup::GetFileName(int n,int extMode)
{
	CCommonButton* button = m_ppButton[extMode*m_buttonKosuu+n];
	if (button != NULL)
	{
		return button->GetFileName();
	}

	return NULL;
}


LPSTR CMenuButtonGroup::GetExtModeCheckVarName(void)
{
	return m_menuButtonSetup->GetExtModeCheckVarName();
}

LPSTR CMenuButtonGroup::GetExtReturnVarName(void)
{
	return m_menuButtonSetup->GetExtModeReturnVarName();
}


/*_*/

