#include <windows.h>
#include "..\nyanLib\include\commonMacro.h"
#include "commonMode.h"


#include "commonUserCommandList.h"

//‚±‚Ì2‚Â‚Í‚»‚ë‚¦‚é‚±‚Æ

CCommonUserCommandList::NNNUSERCOMMANDLIST CCommonUserCommandList::m_list[]=
{
	{SELECTPLACE_MODE,"selectplace"},
	{SELECTHEROIN_MODE,"selectheroin"},
	{PRINTMOVIE_MODE,"printmovie"},
	{PRINTCALENDAR_MODE,"printcalendar"},
	{MYPRINTRESULT_MODE,"printresult"},
	{SELECTCHART_MODE,"selectchart"},
	{NAMEINPUT_MODE,"nameinput"},
	{SELECTPLACE2_MODE,"selectplace2"},
	{SELECTZUKAN_MODE,"selectzukan"},
	{CARDSYSTEM_MODE,"cardsystem"},
	{SELECTOBJECT_MODE,"selectobject"},
	{PRINTACHIEVEMENT_MODE,"printachievement"},
	{PRINTTERM_MODE,"printterm"},
	{KANJIINPUT_MODE,"kanjiinput"},
	{PRINTITEM_MODE,"printitem"},
	{SHOP_MODE,"shop"},
	{PRINTSTATUS_MODE,"printstatus"},
	{PRINTHINT_MODE,"printhint"},
	{SELECTHINT_MODE,"selecthint" },
	{LISTENVOICE_MODE,"listenvoice"},
	{PRINTPARTY_MODE,"printparty"},

	{-1,""},
};



CCommonUserCommandList::CCommonUserCommandList()
{
	int n = 0;
	while (n<50)
	{
		if (m_list[n].number == -1)
		{
			break;
		}
		n++;
	}

	m_kosuu = n;

}

CCommonUserCommandList::~CCommonUserCommandList()
{
	End();
}

void CCommonUserCommandList::End(void)
{

}

int CCommonUserCommandList::GetKosuu(void)
{
	return m_kosuu;
}

int CCommonUserCommandList::GetModeNumber(int n)
{
	if ((n>=0) && (n<m_kosuu))
	{
		return m_list[n].number;
	}
	
	return 0;//error
}

LPSTR CCommonUserCommandList::GetModeName(int n)
{
	if ((n>=0) && (n<m_kosuu))
	{
		return m_list[n].name;
	}

	return NULL;//error
}


