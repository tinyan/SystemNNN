//
// suujipair.cpp
//

#include <windows.h>
#include <stdio.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"


#include "..\nnnUtilLib\nameList.h"
#include "..\nnnUtilLib\systemPicture.h"


#include "suuji.h"
#include "suujiPair.h"


CSuujiPair::CSuujiPair(CSuuji* suuji,CSuuji* upSuuji)
{
	m_suuji = suuji;
	m_upSuuji = upSuuji;
	if (m_upSuuji == NULL) m_upSuuji = m_suuji;

	m_suujiSizeX = m_suuji->GetSizeX();
	m_suujiNextX = m_suuji->GetNextX();

	m_upSuujiSizeX = m_upSuuji->GetSizeX();
	m_upSuujiNextX = m_upSuuji->GetNextX();
}



CSuujiPair::~CSuujiPair()
{
	End();
}

void CSuujiPair::End(void)
{
}


void CSuujiPair::Print(POINT rightUpPoint,int up, int base, int upColor, int baseColor,int slashFlag,int slashColor)
{
	if (baseColor == -1) baseColor = upColor;
	if (slashColor == -1) slashColor = upColor;

	int upKeta = 1;
	int d = up;
	while (d >= 10)
	{
		d /= 10;
		upKeta++;
	}

	int baseKeta = 1;
	d = base;
	while (d >= 10)
	{
		d /= 10;
		baseKeta++;
	}

	int basePrintX = rightUpPoint.x;
	int basePrintY = rightUpPoint.y;

	basePrintX -= m_suujiSizeX;
	basePrintX -= m_suujiNextX * (baseKeta-1);

	int slashPrintX = basePrintX - m_suujiNextX;
	int slashPrintY = basePrintY;

	int upPrintX = slashPrintX - m_upSuujiSizeX - (upKeta-1) * m_upSuujiNextX;
	int upPrintY = slashPrintY;


	m_upSuuji->Print(upPrintX,upPrintY,up,upKeta,upColor);
	m_upSuuji->Put(slashPrintX,slashPrintY,11,slashColor);
	m_suuji->Print(basePrintX,basePrintY,base,baseKeta,baseColor);

}



