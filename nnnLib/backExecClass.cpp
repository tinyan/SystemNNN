//
//
//

#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"

#include "..\nnnUtilLib\namelist.h"
#include "execScript.h"

#include "..\nnnUtilLib\inputStatus.h"

#include "gameCallBack.h"

#include "backExecClass.h"

#include "..\nnnUtilLib\scriptDefine.h"



CBackExecClass::CBackExecClass(CGameCallBack* lpGame)
{
	m_game = lpGame;
	m_sptList = m_game->GetSptList();
	m_execScript = new CExecScript(m_game,1024*512);
	m_scriptNumber = -1;

	m_pic1 = m_game->GetOverrapPic(0);
	m_pic2= m_game->GetOverrapPic(1);

//	m_shakin = 0;

	m_backExecMode = 0;
	m_drawCount = 1;
	m_count = 0;
	m_length = 1;
}


CBackExecClass::~CBackExecClass(void)
{
	End();
}

void CBackExecClass::End(void)
{
	ENDDELETECLASS(m_execScript);
}


void CBackExecClass::SetDrawMode(int count)
{
	m_drawCount = count;
	m_backExecMode = 0;
}

void CBackExecClass::SetOverrapMode(void)
{
	m_backExecMode = 1;

	m_count = 0;
	m_type = m_game->GetOverrapType();
	m_length = m_game->GetOverrapLength();
}

void CBackExecClass::ReStart(void)
{
	m_execScript->SetPC(0);
	m_execScript->m_stackPointer = 0;

	m_drawCount = 0;
	m_count = m_length;
}


BOOL CBackExecClass::LoadScript(int scriptNumber)
{
	if (scriptNumber != m_scriptNumber)
	{
		m_scriptNumber = scriptNumber;
		LPSTR name = m_sptList->GetName(m_scriptNumber);
		char filename[256];
		wsprintf(filename,"spt\\%s.spt",name);
		m_execScript->LoadScript(filename);
	}

	m_execScript->SetPC(0);
	m_execScript->m_stackPointer = 0;

	m_drawCount = 0;
	m_count = m_length;

	return TRUE;
}


void CBackExecClass::Print(void)
{
	CAreaControl::SetNextAllPrint();

	BOOL b = CAreaControl::CheckAllPrintMode();


	if (m_backExecMode == 0)
	{


		m_game->PrintEffect();
		m_game->PrintEffect(TRUE);



		m_game->CountUpOnly(m_kaeshita);
	}
	else if (m_backExecMode == 1)
	{
		m_game->PrintOverrap(m_count);
	}

}

void CBackExecClass::PrintLayers(int startLayer,int endLayer)
{
	CAreaControl::SetNextAllPrint();

	BOOL b = CAreaControl::CheckAllPrintMode();

	if (m_backExecMode == 0)
	{
		m_game->PrintEffectLayer(startLayer,endLayer);

		if (endLayer == LAYER_KOSUU_MAX - 1)
		{
			m_game->CountUpOnly(m_kaeshita);
		}
	}
}


BOOL CBackExecClass::ExecScript(BOOL mustFlag,BOOL loopFlag)
{
	int rt = -1;


	if (m_backExecMode == 0)	//DRAW
	{
		if (m_drawCount <= 0)
		{
			mustFlag = TRUE;
		}
	}
	else if (m_backExecMode)
	{
		if (m_count >= m_length)
		{
			mustFlag = TRUE;
		}
	}

	if (mustFlag)
	{
		rt = m_execScript->Exec();
		if (rt == CODE_CONTROL_NEXT)
		{
			if (loopFlag)
			{
				ReStart();
				m_execScript->Exec();
			}
			else
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}


void CBackExecClass::Calcu(void)
{
	m_game->CalcuEffectOnly();


	if (m_backExecMode == 0)	//DRAW
	{
		int kaeseru = m_drawCount;
		if (kaeseru < 1) kaeseru = 1;
		m_kaeshita = m_game->ShakinHensai(kaeseru);
		m_drawCount -= m_kaeshita;

		if (m_drawCount <= 0)
		{
			m_drawCount = 0;
//			m_game->SetYoyaku();
			return;
		}

		return;
	}
	else if (m_backExecMode == 1)	//OVERRAP
	{
		int kaeseru = m_length - m_count;
		if (kaeseru < 1) kaeseru = 1;
		m_kaeshita = m_game->ShakinHensai(kaeseru);

		m_count += m_kaeshita;

		if (m_count > m_length)
		{
			m_count = m_length;
		}
	}
}
