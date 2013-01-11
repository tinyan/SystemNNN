
#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nnnUtilLib\inputStatus.h"
#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"

#include "allMiniGame.h"
#include "miniGameBase.h"



CMiniGameBase::CMiniGameBase(CAllMiniGame* lpAllMiniGame)
{
	m_allMiniGame = lpAllMiniGame;

	m_input = m_allMiniGame->GetInputStatus();
	m_mouseStatus = m_input->GetMouseStatus();
	m_keyStatus = m_input->GetKeyStatus();
}

CMiniGameBase::~CMiniGameBase()
{
	End();
}

void CMiniGameBase::End(void)
{
}

int CMiniGameBase::GeneralInit(void)
{
	m_input = m_allMiniGame->GetInputStatus();
	m_mouseStatus = m_input->GetMouseStatus();
	m_keyStatus = m_input->GetKeyStatus();
	m_pic1 = m_allMiniGame->GetPicture(0);
	m_pic2 = m_allMiniGame->GetPicture(1);
	m_pic3 = m_allMiniGame->GetPicture(2);
	m_commonBG = m_allMiniGame->GetCommonBG();
	m_commonParts = m_allMiniGame->GetCommonParts();

	m_clearFlag = FALSE;
	m_gameoverFlag = FALSE;

	return Init();
}

int CMiniGameBase::GeneralCalcu(void)
{
	return Calcu();
}

int CMiniGameBase::GeneralPrint(void)
{
	return Print();
}

int CMiniGameBase::Init(void)
{
	return -1;
}

int CMiniGameBase::Calcu(void)
{
	return -1;
}

int CMiniGameBase::Print(void)
{
	return -1;
}