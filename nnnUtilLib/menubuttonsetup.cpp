//
// menubuttonsetup
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"

#include "namelist.h"
#include "setupList.h"
#include "superButtonSetup.h"




//#include "myCommonButton.h"


#include "menuButtonSetup.h"


//char CMenuButtonSetup::m_defaultExtModeCheckVarName[] = "";
//char CMenuButtonSetup::m_defaultExtModeReturnVarName[] = "";


CMenuButtonSetup::CMenuButtonSetup(CNameList* lpNameList,int basicButtonKosuu)
{
	m_setupList = new CSetupList();
	m_setupList->SetSetup(lpNameList);

	m_basicButtonKosuu = basicButtonKosuu;
	m_extButtonKosuu = 0;
	m_extModeKosuu = 0;
	m_superMode = 1;

	m_extModeCheckVarName = NULL;
	m_extModeReturnVarName = NULL;


	//現在superButtonのみ対応@@@@@@@@@@@@@@@@@@@@
//@@	m_setupList->GetInitGameParam(&m_superMode,"superMode");



	//標準ボタン個数
	m_setupList->GetInitGameParam(&m_basicButtonKosuu,"basicButtonNumber");
	//追加モード個数
	m_setupList->GetInitGameParam(&m_extModeKosuu,"extModeNumber");

	m_buttonKosuu = m_basicButtonKosuu;


	m_pBasicSpecialMode = new int[m_buttonKosuu + 1];	//kosuu0 patch
	for (int i=0;i<m_basicButtonKosuu;i++)
	{
		char name[256];
		wsprintf(name,"basicButtonSpecialMode%d",i+1);
		int specialMode = -1;
		m_setupList->GetInitGameParam(&specialMode,name);
		m_pBasicSpecialMode[i] = specialMode;
	}

	//追加ボタン個数
	m_pExtSpecialMode = NULL;
	if (GetExtModeKosuu() > 0)
	{
		m_extButtonKosuu = 1;
		m_setupList->GetInitGameParam(&m_extButtonKosuu,"extButtonNumber");

		m_buttonKosuu = m_basicButtonKosuu + m_extButtonKosuu;

		//追加モードチェック変数名
		m_setupList->GetInitGameString(&m_extModeCheckVarName,"extModeCheckVarName");
		//追加モード用戻り値変数名
		m_setupList->GetInitGameString(&m_extModeReturnVarName,"extModeReturnVarName");

		m_pExtSpecialMode = new int[m_extButtonKosuu];
		for (int i=0;i<m_extButtonKosuu;i++)
		{
			int specialMode = -1;
			char name[256];
			wsprintf(name,"extButtonSpecialMode%d",i+1);
			m_setupList->GetInitGameParam(&specialMode,name);
			m_pExtSpecialMode[i] = specialMode;
		}
	}


	m_menuAnimeAdjustFlag = 0;
	m_setupList->GetInitGameParam(&m_menuAnimeAdjustFlag,"menuAnimeAdjustFlag");

//	//背景スクリプト有り無し
//	m_backScriptFlag = 0;
//	m_setupList->GetInitGameParam(&m_backScriptFlag,"backScriptFlag");

//	m_ppZahyo = new POINT*[m_extModeKosuu + 1];
//	for (int i=0;i<1+m_extModeKosuu;i++)
//	{
//		m_ppZahyo[i] = new POINT[m_basicButtonKosuu + m_extButtonKosuu];
//	}
		
	m_ppExistFlag = NULL;
	m_ppEnableFlag = NULL;
//	if (m_extModeKosuu > 0)
//	{
	m_ppExistFlag = new int[m_buttonKosuu*(m_extModeKosuu+1)];
	m_ppEnableFlag = new int[m_buttonKosuu*(m_extModeKosuu+1)];
//	}

	//1-1よみこみ
	int sizeX = 16;
	int sizeY = 16;
	m_setupList->GetInitGameParam(&sizeX,"menu1Button1SizeX");
	m_setupList->GetInitGameParam(&sizeY,"menu1Button1SizeY");
	m_size.cx = sizeX;
	m_size.cy = sizeY;

	m_nextX = 0;
	m_nextY = m_size.cy;
	m_setupList->GetInitGameParam(&m_nextX,"menuNextX");
	m_setupList->GetInitGameParam(&m_nextY,"menuNextY");

//	m_menuPrintX = 0;
//	m_menuPrintY = 0;
//	m_setupList->GetInitGameParam(&m_menuPrintX,"menuPrintX");
//	m_setupList->GetInitGameParam(&m_menuPrintY,"menuPrintY");


	//新設定よみこみ

	//button[n]PrintX[k]	モード[n]の[k]番めのボタン座標の個別指定
	//button[n]PrintY[k]

	char name[256];
	for (int j=0;j<1+m_extModeKosuu;j++)
	{
		if (j == 0)
		{
			for (int i=0;i<m_buttonKosuu;i++)
			{
				int flg = 1;
				if (i>=m_basicButtonKosuu) flg = 0;

				wsprintf(name,"menu%dButton%dExistFlag",j+1,i+1);
				m_setupList->GetInitGameParam(&flg,name);
				m_ppExistFlag[i+j*m_buttonKosuu] = flg;

				wsprintf(name,"menu%dButton%dEnableFlag",j+1,i+1);
				m_setupList->GetInitGameParam(&flg,name);
				m_ppEnableFlag[i+j*m_buttonKosuu] = flg;
			}
		}

		if (j > 0)
		{
			for (int i=0;i<m_buttonKosuu;i++)
			{
				int flg = m_ppExistFlag[i+(j-1)*m_buttonKosuu];
				if (j == 1)
				{
					if (i>=m_basicButtonKosuu) flg = 1;
				}

				wsprintf(name,"menu%dButton%dExistFlag",j+1,i+1);
				m_setupList->GetInitGameParam(&flg,name);
				m_ppExistFlag[i+j*m_buttonKosuu] = flg;

				if (flg)
				{
					if (i<m_basicButtonKosuu)
					{
						flg = m_ppEnableFlag[i+(j-1)*m_buttonKosuu];
					}
				}

				wsprintf(name,"menu%dButton%dEnableFlag",j+1,i+1);
				m_setupList->GetInitGameParam(&flg,name);
				m_ppEnableFlag[i+j*m_buttonKosuu] = flg;
			}
		}
/*
		for (int i=0;i<m_basicButtonKosuu+m_extButtonKosuu;i++)
		{
			if (i>0)
			{
				m_ppZahyo[j][i].x = m_ppZahyo[j][i-1].x + m_nextX;
				m_ppZahyo[j][i].y = m_ppZahyo[j][i-1].y + m_nextY;
			}

			int x = m_ppZahyo[j][i].x;
			int y = m_ppZahyo[j][i].y;

			sprintf(name,"menu%dButton%dPrintX",j+1,i+1);
			m_setupList->GetInitGameParam(&x,name);
			sprintf(name,"menu%dButton%dPrintY",j+1,i+1);
			m_setupList->GetInitGameParam(&y,name);

			m_ppZahyo[j][i].x = x;
			m_ppZahyo[j][i].y = y;
		}
		*/
	}

	//superButton設定？
	m_ppSuperSetup = NULL;
//	m_pSuperFileName = NULL;
	m_normalFileName = NULL;

	if (m_superMode)
	{
		int k = GetBasicButtonKosuu() + GetExtButtonKosuu();
		int l= GetExtModeKosuu() + 1;

		m_ppSuperSetup = new CSuperButtonSetup* [k*l];
//		m_pSuperFileName = new char* [k];


		for (int j=0;j<l;j++)
		{
			for (int i=0;i<k;i++)
			{
				wsprintf(name,"menu%dbutton%d",j+1,i+1);
				CSuperButtonSetup* lpCopyFrom = NULL;

				POINT delta;
				delta.x = 0;
				delta.y = 0;

				if (j == 0)
				{
					if (i>0)
					{
						lpCopyFrom = m_ppSuperSetup[i-1];
					}
					delta.x = m_nextX;
					delta.y = m_nextY;
				}
				else
				{
					lpCopyFrom = m_ppSuperSetup[i+(j-1)*k];
				}
				m_ppSuperSetup[i+j*k] = new CSuperButtonSetup(lpNameList,name,lpCopyFrom,&delta);
			}
		}
	}
	else
	{
//@@@		m_setupList->GetInitGameString(&m_normalFileName,"filenameButton");
	}
}




CMenuButtonSetup::~CMenuButtonSetup()
{
	End();
}


void CMenuButtonSetup::End(void)
{
//	DELETEARRAY(m_pSuperFileName);

	if (m_ppSuperSetup != NULL)
	{
		int k = GetBasicButtonKosuu() + GetExtButtonKosuu();
		int l = GetExtModeKosuu() + 1;

		for (int i=0;i<k*l;i++)
		{
			ENDDELETECLASS(m_ppSuperSetup[i]);
		}
		DELETEARRAY(m_ppSuperSetup);
	}


	DELETEARRAY(m_pExtSpecialMode);

	DELETEARRAY(m_ppExistFlag);
	DELETEARRAY(m_ppEnableFlag);

	DELETEARRAY(m_pBasicSpecialMode);

//	if (m_ppZahyo != NULL)
//	{
//		for (int i=0;i<m_extModeKosuu+1;i++)
//		{
//			DELETEARRAY(m_ppZahyo[i]);
//		}
//		DELETEARRAY(m_ppZahyo);
//	}

	ENDDELETECLASS(m_setupList);
}


/*
POINT CMenuButtonSetup::GetZahyo(int buttonNumber, int extMode)
{
	POINT pt;
	pt.x = 0;
	pt.y = 0;
	if ((extMode >=0) && (extMode < (1+m_extModeKosuu)))
	{
		if ((buttonNumber>=0) && (buttonNumber < m_basicButtonKosuu + m_extButtonKosuu))
		{
//@@			pt = m_ppZahyo[extMode][buttonNumber];
		}
	}

	return pt;
}
*/


BOOL CMenuButtonSetup::CheckButtonExist(int buttonNumber, int extMode)
{
	if ((extMode <0) || (extMode > m_extModeKosuu)) return FALSE;
	if ((buttonNumber<0) || (buttonNumber >= m_buttonKosuu)) return FALSE;

	if (m_ppExistFlag[extMode*m_buttonKosuu+buttonNumber]) return TRUE;

	return FALSE;
}

BOOL CMenuButtonSetup::CheckButtonEnable(int buttonNumber, int extMode)
{
	if ((extMode <0) || (extMode > m_extModeKosuu)) return FALSE;
	if ((buttonNumber<0) || (buttonNumber >= m_buttonKosuu)) return FALSE;

	if (m_ppEnableFlag[extMode*m_buttonKosuu+buttonNumber]) return TRUE;

	return FALSE;
}

int CMenuButtonSetup::GetExtSpecialMode(int extButtonNumber)
{
	if (m_extModeKosuu <= 0) return 0;
	return m_pExtSpecialMode[extButtonNumber];
}


CSuperButtonSetup* CMenuButtonSetup::GetSuperSetup(int n,int extMode)
{
//	int l = GetExtButtonKosuu();
	int l = GetBasicButtonKosuu() + GetExtButtonKosuu();
	return m_ppSuperSetup[n+extMode * l];
}

int CMenuButtonSetup::GetBasicSpecialMode(int basicButtonNumber)
{
	if ((basicButtonNumber < 0) || (basicButtonNumber >= m_basicButtonKosuu)) return 0;

	return m_pBasicSpecialMode[basicButtonNumber];
}


