#include <windows.h>

#include "..\nyanlib\include\commonMacro.h"

#include "nameList.h"

#include "cutinControl.h"


//キャラ名,fileTag,X,Y,nextX(0),nextY,windowtype,windowdx,windowdy,windowcolorr,g,b,a,fontDeltaSize(0),param1-2

CCutinControl::CCutinControl(BOOL editorFlag)
{
	m_nameList = new CNameList();
	if (editorFlag == FALSE)
	{
		m_nameList->LoadFile("spt\\charaName.xtx");
	}
	else
	{
		m_nameList->LoadFile("nnndir\\charaName.txt");
	}

	int charaNameKosuu = m_nameList->GetNameKosuu() / 2;

	m_cutinChara = new CNameList();
	if (editorFlag == FALSE)
	{
		m_cutinChara->LoadFile("spt\\cutinChara.xtx");
	}
	else
	{
		m_cutinChara->LoadFile("nnndir\\cutinChara.txt");
	}

	m_cutinParamKosuu = 16;
	int kosuu = m_cutinChara->GetNameKosuu() / m_cutinParamKosuu;
	m_cutinKosuu = kosuu;

	if (kosuu == 0) kosuu = 1;
	m_tagLength = new int[kosuu];
	m_cutinCharaNumber = new int[kosuu];
	m_zahyo = new POINT[kosuu];
	m_nextZahyo = new POINT[kosuu];
	m_windowType = new int[kosuu];
	m_windowDeltaSize = new SIZE[kosuu];
	m_windowColorRGBAPack = new unsigned int[kosuu];
	m_windowColorRGBA = new int[kosuu*4];
	m_fontDeltaSize = new int[kosuu];


	for (int i=0;i<kosuu;i++)
	{
		m_cutinCharaNumber[i] = 0;
		m_tagLength[i] = 0;
		m_zahyo[i].x = 0;
		m_zahyo[i].y = 0;
		m_nextZahyo[i].x = 0;
		m_nextZahyo[i].y = 24;
		m_windowType[i] = 0;
		m_windowDeltaSize[i].cx = 0;
		m_windowDeltaSize[i].cy = 0;
		m_windowColorRGBAPack[i] = 0x80204060;

		m_windowColorRGBA[i*4+0] = 0x80;
		m_windowColorRGBA[i*4+1] = 0x20;
		m_windowColorRGBA[i*4+2] = 0x40;
		m_windowColorRGBA[i*4+3] = 0x60;

		m_fontDeltaSize[i] = 0;
	}

	for (int i=1;i<m_cutinKosuu;i++)
	{
		LPSTR name = m_cutinChara->GetName(i*m_cutinParamKosuu+0);
		int found = SearchCharaName(name);
		if (found == -1)
		{
			//error!
			MessageBox(NULL,"カットイン:キャラ名が存在しません",name,MB_ICONEXCLAMATION | MB_OK);
			found = 0;
		}
		m_cutinCharaNumber[i] = found;

		LPSTR tag = m_cutinChara->GetName(i*m_cutinParamKosuu+1);
		m_tagLength[i] = strlen(tag);
		m_zahyo[i].x = atoi(m_cutinChara->GetName(i*m_cutinParamKosuu+2));
		m_zahyo[i].y = atoi(m_cutinChara->GetName(i*m_cutinParamKosuu+3));
		m_nextZahyo[i].x = atoi(m_cutinChara->GetName(i*m_cutinParamKosuu+4));
		m_nextZahyo[i].y = atoi(m_cutinChara->GetName(i*m_cutinParamKosuu+5));

		m_windowType[i] = atoi(m_cutinChara->GetName(i*m_cutinParamKosuu+6));
		m_windowDeltaSize[i].cx = atoi(m_cutinChara->GetName(i*m_cutinParamKosuu+7));
		m_windowDeltaSize[i].cy = atoi(m_cutinChara->GetName(i*m_cutinParamKosuu+8));

		unsigned int r = (unsigned int)(atoi(m_cutinChara->GetName(i*m_cutinParamKosuu+9)));
		unsigned int g = (unsigned int)(atoi(m_cutinChara->GetName(i*m_cutinParamKosuu+10)));
		unsigned int b = (unsigned int)(atoi(m_cutinChara->GetName(i*m_cutinParamKosuu+11)));
		unsigned int a = (unsigned int)(atoi(m_cutinChara->GetName(i*m_cutinParamKosuu+12)));


		m_windowColorRGBAPack[i] = (a<<24) | (r<<16) | (g<<8) | b;
		m_windowColorRGBA[i*4+0] = (int)a;
		m_windowColorRGBA[i*4+1] = (int)r;
		m_windowColorRGBA[i*4+2] = (int)g;
		m_windowColorRGBA[i*4+3] = (int)b;

		m_fontDeltaSize[i] = atoi(m_cutinChara->GetName(i*m_cutinParamKosuu+13));
	}


	//default data
	for (int i=0;i<16;i++)
	{
		m_layerData[i] = 0;
	}
}



CCutinControl::~CCutinControl()
{
	End();
}

void CCutinControl::End(void)
{
	DELETEARRAY(m_fontDeltaSize);
	DELETEARRAY(m_windowColorRGBA);
	DELETEARRAY(m_windowColorRGBAPack);
	DELETEARRAY(m_windowDeltaSize);
	DELETEARRAY(m_windowType);

	DELETEARRAY(m_nextZahyo);
	DELETEARRAY(m_zahyo);

	DELETEARRAY(m_cutinCharaNumber);
	DELETEARRAY(m_tagLength);
	ENDDELETECLASS(m_cutinChara);
	ENDDELETECLASS(m_nameList);
}

int CCutinControl::SearchCharaName(LPSTR name)
{
	int charaNameKosuu = m_nameList->GetNameKosuu() / 2;
	for (int k=1;k<charaNameKosuu;k++)
	{
		if (strcmp(name,m_nameList->GetName(k*2+1)) == 0)
		{
			return k;
		}
	}
	return -1;
}


int CCutinControl::SearchCharaLayer(LPSTR name)
{
	int n = SearchCharaName(name);
	if (n == -1) return 0;//error!

	for (int i=0;i<16;i++)
	{
		int k = m_layerData[i];
		if (k>0)
		{
			if (n == m_cutinCharaNumber[k])
			{
				return i;
			}
		}
	}
	
	return 0;//not found!
}


POINT CCutinControl::GetZahyo(int layer)
{
	int n = m_layerData[layer];
	return m_zahyo[n];
}

POINT CCutinControl::GetNextZahyo(int layer)
{
	int n = m_layerData[layer];
	return m_nextZahyo[n];
}


unsigned int CCutinControl::GetColorRGBAPack(int layer)
{
	int n = m_layerData[layer];
	return m_windowColorRGBAPack[n];
}

int CCutinControl::GetColorR(int layer)
{
	int n = m_layerData[layer];
	return m_windowColorRGBA[n*4+1];
}

int CCutinControl::GetColorG(int layer)
{
	int n = m_layerData[layer];
	return m_windowColorRGBA[n*4+2];
}

int CCutinControl::GetColorB(int layer)
{
	int n = m_layerData[layer];
	return m_windowColorRGBA[n*4+3];
}

int CCutinControl::GetColorA(int layer)
{
	int n = m_layerData[layer];
	return m_windowColorRGBA[n*4+0];
}

int CCutinControl::GetFukidashiType(int layer)//0:col 1-window
{
	int n = m_layerData[layer];
	return m_windowType[n];
}


SIZE CCutinControl::GetFukidashiDeltaSize(int layer)
{
	int n = m_layerData[layer];
	return m_windowDeltaSize[n];
}

int CCutinControl::GetFontDeltaSize(int layer)
{
	int n = m_layerData[layer];
	return m_fontDeltaSize[n];
}




int CCutinControl::OnNewFile(int layer,LPSTR filename)
{
	int ln = strlen(filename);
	char mes[1024];


	int found = -1;

	for (int i=1;i<m_cutinKosuu;i++)
	{
		int checkLen = m_tagLength[i];
		if (ln>=checkLen)
		{
			memcpy(mes,filename,ln);
			mes[ln] = 0;

			LPSTR tag = m_cutinChara->GetName(i*m_cutinParamKosuu+1);
			if (_stricmp(tag,mes) == 0)
			{
				found = i;
				break;
			}
		}
	}

	if (found == -1) return 0;//false
	m_layerData[layer] = found;

	return found;
}



void CCutinControl::OnClearAllEffect(void)
{
	for (int i=0;i<16;i++)
	{
		m_layerData[i] = 0;
	}
}

void CCutinControl::OnClearEffect(int layer)
{
	m_layerData[layer] = 0;
}



/*_*/

