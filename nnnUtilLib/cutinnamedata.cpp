#include <windows.h>

#include "..\nyanlib\include\commonMacro.h"
#include "..\nnnUtilLib\nameList.h"

#include "cutinNameData.h"


//ƒLƒƒƒ‰–¼,fileTag,X,Y,nextX(0),nextY,windowType,windowDX,windowDY,windowcolorR,G,B,A,fontDeltaSize(0),param1,param2

//windowtype
//0:‚È‚µ
//1:Ž©“®•
//2-ŒÅ’è•
//-1:filename (default:ta_cutinwindow[-n]) ta_cutinwindow1,ta_cutinwindow2,ta_cutinwindow3, ...


char CCutinNameData::m_errorCharaName[] = "ƒGƒ‰[";
char CCutinNameData::m_errorFileNameTag[] = "ta_errortagname";

CCutinNameData::CCutinNameData(LPSTR name)
{
	char filename[1024];

	if (name == NULL)
	{
		wsprintf(filename,"spt\\cutinChara.xtx");
	}
	else
	{
		wsprintf(filename,name);
	}

	m_list = new CNameList();
	m_kosuu = 0;


	m_zahyo = NULL;
	m_nextZahyo = NULL;
	m_windowType = NULL;
	m_windowDXDY = NULL;
	m_windowColorRGBA = NULL;
	m_fontSizeDelta = NULL;

	if (m_list->LoadFile(filename))
	{
		m_kosuu = m_list->GetNameKosuu() / 16;

		m_zahyo = new POINT[m_kosuu];
		m_nextZahyo = new POINT[m_kosuu];
		m_windowType = new int[m_kosuu];
		m_windowDXDY = new SIZE[m_kosuu];
		m_windowColorRGBA = new int[m_kosuu*4];
		m_fontSizeDelta = new int[m_kosuu];

		for (int i=0;i<m_kosuu;i++)
		{
			m_zahyo[i].x = 0;
			m_zahyo[i].y = 0;
			m_nextZahyo[i].x = 0;
			m_nextZahyo[i].y = 30;
			m_windowType[i] = 1;
			m_windowDXDY[i].cx = 0;
			m_windowDXDY[i].cy = 0;
			m_windowColorRGBA[i*4+0] = 128;
			m_windowColorRGBA[i*4+1] = 255;
			m_windowColorRGBA[i*4+2] = 192;
			m_windowColorRGBA[i*4+3] = 50;
			m_fontSizeDelta[i] = 0;
		}

		for (int i=1;i<m_kosuu;i++)
		{
			m_zahyo[i].x = atoi(m_list->GetName(i*16+2));
			m_zahyo[i].y = atoi(m_list->GetName(i*16+3));
			m_nextZahyo[i].x = atoi(m_list->GetName(i*16+4));
			m_nextZahyo[i].y = atoi(m_list->GetName(i*16+5));
			
			m_windowType[i] = atoi(m_list->GetName(i*16+6));
			m_windowDXDY[i].cx = atoi(m_list->GetName(i*16+7));
			m_windowDXDY[i].cy = atoi(m_list->GetName(i*16+8));

			m_windowColorRGBA[i*4+0] = atoi(m_list->GetName(i*16+9));
			m_windowColorRGBA[i*4+1] = atoi(m_list->GetName(i*16+10));
			m_windowColorRGBA[i*4+2] = atoi(m_list->GetName(i*16+11));
			m_windowColorRGBA[i*4+3] = atoi(m_list->GetName(i*16+12));

			m_fontSizeDelta[i] = atoi(m_list->GetName(i*16+13));
		}

	}
}

CCutinNameData::~CCutinNameData()
{
	End();
}

void CCutinNameData::End(void)
{
	DELETEARRAY(m_fontSizeDelta);
	DELETEARRAY(m_windowColorRGBA);
	DELETEARRAY(m_windowDXDY);
	DELETEARRAY(m_windowType);
	DELETEARRAY(m_nextZahyo);
	DELETEARRAY(m_zahyo);

	ENDDELETECLASS(m_list);
}


BOOL CCutinNameData::CheckNameIsNotAll(int cutin)
{
	if ((m_kosuu>1) && (cutin > 0) && (cutin<m_kosuu))
	{
		LPSTR charaName = GetCharaName(cutin);
		if (charaName != NULL)
		{
			if ((*charaName) == '*')
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

POINT CCutinNameData::GetWindowZahyo(int cutin)
{
	POINT pt = GetZahyo(cutin);
	SIZE pt2 = GetWindowDXDY(cutin);

	POINT pt3 = GetNextZahyo(cutin);

	pt.x -= pt2.cx;
	pt.y -= pt2.cy;

	return pt;
}


SIZE CCutinNameData::GetWindowSize(int cutin,int fontSize,int gyo,int ln)
{
	POINT pt = GetNextZahyo(cutin);
	SIZE pt2 = GetWindowDXDY(cutin);
	int fontDelta = GetFontSizeDelta(cutin);
	fontSize += fontDelta;

	int windowType = GetWindowType(cutin);

	int sizeX = (fontSize+1) * ln;
	sizeX += pt2.cx * 2;
	sizeX += pt.x * (gyo-1);

	if (windowType > 1)
	{
		sizeX = windowType;
	}

	int sizeY = pt.y * (gyo-1) + fontSize + 1;
	sizeY += pt2.cy * 2;

	SIZE sz;
	sz.cx = sizeX;
	sz.cy = sizeY;

	return sz;
}



LPSTR CCutinNameData::GetCharaName(int cutin)
{
	if ((m_kosuu>1) && (cutin > 0) && (cutin<m_kosuu))
	{
		return m_list->GetName(cutin*16+0);
	}

	return m_errorCharaName;
}

LPSTR CCutinNameData::GetFileNameTag(int cutin)
{
	if ((m_kosuu>1) && (cutin > 0) && (cutin<m_kosuu))
	{
		return m_list->GetName(cutin*16+1);
	}

	return m_errorFileNameTag;
}

POINT CCutinNameData::GetZahyo(int cutin)
{
	POINT pt;
	pt.x = 0;
	pt.y = 0;
	if ((m_kosuu>1) && (cutin > 0) && (cutin<m_kosuu))
	{
		pt = m_zahyo[cutin];
	}

	return pt;
}

POINT CCutinNameData::GetNextZahyo(int cutin)
{
	POINT pt;
	pt.x = 0;
	pt.y = 30;
	if ((m_kosuu>1) && (cutin > 0) && (cutin<m_kosuu))
	{
		pt = m_nextZahyo[cutin];
	}
	return pt;
}

int CCutinNameData::GetWindowType(int cutin)
{
	int windowType = 1;

	if ((m_kosuu>1) && (cutin > 0) && (cutin<m_kosuu))
	{
		windowType = m_windowType[cutin];
	}

	return windowType;
}


SIZE CCutinNameData::GetWindowDXDY(int cutin)
{
	SIZE sz;
	sz.cx = 0;
	sz.cy = 0;

	if ((m_kosuu>1) && (cutin > 0) && (cutin<m_kosuu))
	{
		sz = m_windowDXDY[cutin];
	}

	return sz;
}

int CCutinNameData::GetWindowColorR(int cutin)
{
	int r = 128;

	if ((m_kosuu>1) && (cutin > 0) && (cutin<m_kosuu))
	{
		r = m_windowColorRGBA[cutin*4+0];
	}

	return r;
}

int CCutinNameData::GetWindowColorG(int cutin)
{
	int g = 255;

	if ((m_kosuu>1) && (cutin > 0) && (cutin<m_kosuu))
	{
		g = m_windowColorRGBA[cutin*4+1];
	}

	return g;
}

int CCutinNameData::GetWindowColorB(int cutin)
{
	int b = 192;

	if ((m_kosuu>1) && (cutin > 0) && (cutin<m_kosuu))
	{
		b = m_windowColorRGBA[cutin*4+2];
	}

	return b;

}

int CCutinNameData::GetWindowColorA(int cutin)
{
	int a = 50;

	if ((m_kosuu>1) && (cutin > 0) && (cutin<m_kosuu))
	{
		a = m_windowColorRGBA[cutin*4+3];
	}

	return a;

}

int CCutinNameData::GetFontSizeDelta(int cutin)
{
	int fontDelta = 0;

	if ((m_kosuu>1) && (cutin > 0) && (cutin<m_kosuu))
	{
		fontDelta = m_fontSizeDelta[cutin];
	}

	return fontDelta;
}

int CCutinNameData::SearchFirst(LPSTR charaName)
{
	m_foundNumber = -1;
	int ln = (int)strlen(charaName);
	memcpy(m_searchCharaName,charaName,ln+1);

	for (int i=1;i<m_kosuu;i++)
	{
		LPSTR name = GetCharaName(i);
		if ((*name) == '*')
		{
			m_foundNumber = i;
			break;
		}

		if (strcmp(name,charaName) == 0)
		{
			m_foundNumber = i;
			break;
		}
	}
	return m_foundNumber;
}

int CCutinNameData::GetNext(void)
{
	if (m_foundNumber == -1) return -1;

	int found2 = -1;

	for (int i=m_foundNumber+1;i<m_kosuu;i++)
	{
		LPSTR name = GetCharaName(i);
		if ((*name) == '*')
		{
			found2 = i;
			break;
		}

		if (strcmp(name,m_searchCharaName) == 0)
		{
			found2 = i;
			break;
		}
	}

	m_foundNumber = found2;

	return m_foundNumber;
}


/*_*/



