//
// CommonSelectObject.cpp
//


#include <windows.h>
#include <stdio.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGeo.h"
#include "..\nyanLib\include\allGraphics.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"
#include "..\nnnUtilLib\nnnButtonStatus.h"
#include "..\nnnUtilLib\selectObjectSetup.h"

#include "..\nnnUtilLib\commonButton.h"
#include "..\nnnUtilLib\commonButtonGroup.h"
#include "..\nnnUtilLib\commonBackButton.h"

#include "..\nnnUtilLib\superButtonPicture.h"

#include "..\nnnUtilLib\printGameDate.h"
#include "..\nnnUtilLib\mymessage.h"

#include "..\nnnUtilLib\commonAnimeParts.h"
#include "..\nnnUtilLib\suuji.h"

#include "commonMode.h"
#include "commonSystemParamName.h"


#include "commonSystemSoundName.h"

#include "gameCallBack.h"

#include "commonGeneral.h"


#include "commonPrintAchievement.h"

#include "commonKeyList.h"


char CCommonPrintAchievement::m_typeName[][32]=
{
	"ending","endingrange"
};

CCommonPrintAchievement::CCommonPrintAchievement(CGameCallBack* lpGame,int extMode) : CCommonGeneral(lpGame)
{
	SetClassNumber(PRINTACHIEVEMENT_MODE);
	LoadSetupFile("PrintAchievement",256);

	m_message = m_game->GetMyMessage();

	GetBackExecSetup();
	GetAllPrintSetup();
	m_mustAllPrintFlag = TRUE;

	m_achievementNumber = 0;
	GetInitGameParam(&m_achievementNumber,"achievementNumber");

	m_achievementTable = new ACHIEVEMENT[m_achievementNumber+1];
	for (int i=0;i<m_achievementNumber;i++)
	{
		//������ł��`�F�b�N�ł���悤��"ending","endingrange"...


		int type = 0;
		char name[256];
		sprintf_s(name,256,"achievementType%d",i+1);
		LPSTR typeString = NULL;

		if (GetInitGameString(&typeString,name))
		{
			if (typeString != NULL)
			{
				char c = *typeString;
				if ((c >= '0') && (c <= '9'))
				{
					type = atoi(typeString);
				}
				else
				{
					for (int k=0;k<2;k++)
					{
						if (_stricmp(typeString,m_typeName[k]) == 0)
						{
							type = k + 1;
							break;
						}
					}
				}
			}
		}


		m_achievementTable[i].type = type;

		int paraNumber = 0;
		sprintf_s(name,256,"achievementParamNumber%d",i+1);
		GetInitGameParam(&paraNumber,name);
		if (paraNumber> 16) paraNumber = 16;
		m_achievementTable[i].paramNumber = paraNumber;

		for (int k=0;k<16;k++)
		{
			m_achievementTable[i].param[k] = 0;
		}

		for (int k=0;k<paraNumber;k++)
		{
			int para = 0;
			sprintf_s(name,256,"achievement%dParam%d",i+1,k+1);
			GetInitGameParam(&para,name);
			m_achievementTable[i].param[k] = para;
		}
	}

	m_achievementResult = new int[m_achievementNumber+1];
	for (int i=0;i<m_achievementNumber;i++)
	{
		m_achievementResult[i] = 0;
	}
	CheckAllResult(FALSE);

	m_anime = new CCommonAnimeParts*[m_achievementNumber*2];
	for (int i=0;i<m_achievementNumber;i++)
	{
		char tagName[256];
		sprintf_s(tagName,256,"achievement%dok",i+1);
		m_anime[i*2+0] = new CCommonAnimeParts(tagName,m_setup,TRUE);
		sprintf_s(tagName,256,"achievement%dnot",i+1);
		m_anime[i*2+1] = new CCommonAnimeParts(tagName,m_setup,TRUE);
	}

	m_suuji = NULL;
	m_percentPrintFlag = 0;
	m_percentPrintX = 0;
	m_percentPrintY = 0;
	GetInitGameParam(&m_percentPrintFlag,"percentPrintFlag");
	if (m_percentPrintFlag)
	{
		m_suuji = new CSuuji(m_setup,"suuji",TRUE);
		GetInitGameParam(&m_percentPrintX,"percentPrintX");
		GetInitGameParam(&m_percentPrintY,"percentPrintY");
	}


	CreateBackButton();

	GetDisableQuickButtonSetup();
	GetBGMSetup();
	GetFadeInOutSetup();
	GetEnterExitVoiceFileName();
	GetAddLayerSetup();
	GetAnimeLayerSetup();
}



CCommonPrintAchievement::~CCommonPrintAchievement()
{
	End();
}

void CCommonPrintAchievement::End(void)
{
	ENDDELETECLASS(m_suuji);
	if (m_anime != NULL)
	{
		for (int i=0;i<m_achievementNumber*2;i++)
		{
			ENDDELETECLASS(m_anime[i]);
		}
		DELETEARRAY(m_anime);
	}
	DELETEARRAY(m_achievementResult);
	DELETEARRAY(m_achievementTable);
}


int CCommonPrintAchievement::Init(void)
{

	CheckAllResult();

	for (int i=0;i<m_achievementNumber*2;i++)
	{
		m_anime[i]->Init();
	}

	m_back->Init();
	LoadBackButtonPic();

	return -1;
}


int CCommonPrintAchievement::Calcu(void)
{
	//backbutton

	for (int i=0;i<m_achievementNumber*2;i++)
	{
		m_anime[i]->Calcu();
	}

	int back = m_back->Calcu(m_inputStatus);
	if (back != NNNBUTTON_NOTHING)
	{
		int nm = ProcessUpDownBack(back);
		if (nm >= 0)
		{
			if (nm == 0)
			{
//				m_game->FuqueAllEffectYoyaku();
				return ReturnFadeOut(OMAKE_MODE);
			}
		}
	}






	/*
	int rt = m_game->CalcuOptionButton();

	if (rt != NNNBUTTON_NOTHING)
	{
		int nm = ProcessCommonButton(rt);
		if (nm == 0)
		{
		//	return m_game->ChangeToSystemMode(SYSTEMMENU_MODE,m_classNumber);
			m_exitModeFlag = FALSE;
			return ReturnFadeOut(m_game->ChangeToSystemMode(SYSTEMMENU_MODE,m_classNumber));
	//		m_game->TaihiAllEffect();

//			m_game->PlayCommonSystemSound(COMMON_SYSTEMSOUND_OK);
	//		m_game->SetSaveMode(m_classNumber);
	//		m_game->MakeMiniCG();
	//		m_game->SetCommonBackMode(SYSTEMMENU_MODE,m_classNumber);
	//		return ReturnFadeOut(SYSTEMMENU_MODE);
		}

		if (nm == 1)
		{
			m_exitModeFlag = FALSE;
			m_game->SetCommonBackMode(CONFIG_MODE,m_classNumber);
			return ReturnFadeOut(m_game->ChangeToSystemMode(CONFIG_MODE,m_classNumber));
		}
		if (nm == 2)
		{
			m_exitModeFlag = FALSE;
			m_game->SetCommonBackMode(BACKLOG_MODE,m_classNumber);
			return ReturnFadeOut(m_game->ChangeToSystemMode(BACKLOG_MODE,m_classNumber));
		}



		int st = CCommonButton::GetButtonStatus(rt);
		if (st == NNNBUTTON_STARTCLICK) return -1;
		if (st == NNNBUTTON_CLICKING) return -1;
	}

	*/




	return -1;
}

int CCommonPrintAchievement::Print(void)
{
	CAreaControl::SetNextAllPrint();

	CAllGraphics::FillScreen();


	PrintBackScriptOrBG();

//	m_message->PrintMessage(40,40,"�g���t�B�[�m�F�p�_�~�[���");


	for (int i=0;i<m_achievementNumber;i++)
	{
//		char mes[256];
		int ps = m_achievementResult[i];

		int k = i*2;
		if (ps<100)
		{
			k = i*2+1;
		}

		m_anime[k]->Print();

		//�B�����\��
		if (m_percentPrintFlag)
		{
			POINT pt = m_anime[k]->GetZahyo();
			pt.x += m_percentPrintX;
			pt.y += m_percentPrintY;
			m_suuji->Print(pt.x+m_percentPrintX,pt.y+m_percentPrintY,ps,3);
		}


//		sprintf_s(mes,256,"%d�ԃg���t�B�[��%d�p�[�Z���g",i+1,ps);
//		m_message->PrintMessage(100,100+50*i,mes);
	}

	m_back->Print();


//	m_game->PrintOptionButtonYoyaku();

	return -1;
}







void CCommonPrintAchievement::FinalExitRoutine(void)
{

	if (m_exitModeFlag)
	{
//		m_game->SetYoyaku();
	}
}

int CCommonPrintAchievement::EndMode(void)
{
	return -1;

	/*
	if (m_exitModeFlag)
	{
		m_game->SetVarData(m_selectPlaceResultVarNumber,m_selectedNumber + 1);


		m_game->SetYoyaku();
	}
	*/

}

void CCommonPrintAchievement::CheckAllResult(BOOL noticePrint)
{
	for (int i=0;i<m_achievementNumber;i++)
	{
		int type = m_achievementTable[i].type;
		int paraKosuu = m_achievementTable[i].paramNumber;
		if (m_achievementResult[i] >= 100) continue;

		int ps = 0;

		if (type == 1)
		{
			if (paraKosuu > 0)
			{
				int p = 0;
				for (int k=0;k<paraKosuu;k++)
				{
					int param = m_achievementTable[i].param[k];
					p += m_game->GetAchievement(param);
				}

				ps = p / paraKosuu;
				if ((ps == 0) && (p>0))
				{
					ps = 1;
				}
			}
		}
		else if (type == 2)
		{
			if (paraKosuu >= 2)
			{
				int p = 0;
				int st = m_achievementTable[i].param[0];
				int ed = m_achievementTable[i].param[0+1];
				int dv = ed - st + 1;
				if (dv>0)
				{
					for (int k=st;k<=ed;k++)
					{
//						int param = m_achievementTable[i].param[k];
						p += m_game->GetAchievement(k);
					}
					ps = p / dv;
					if ((ps == 0) && (p>0))
					{
						ps = 1;
					}
				}
			}

		}

		m_achievementResult[i] = ps;

		if (noticePrint)
		{
			if (ps >= 100)
			{
				//notice
	
			}
		}
	}
}


void CCommonPrintAchievement::AchievementChanged(int n,int ps)
{
	//�K�v�Ȃ�notice�\���v����game��


}














