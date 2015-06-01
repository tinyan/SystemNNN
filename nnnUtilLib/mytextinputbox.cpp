//
// nameinput.cpp
//

#include <windows.h>

#include <winnls32.h>
#include <stdio.h>
#include "..\nyanlib\include\commonMacro.h"
#include "..\nyanlib\include\myGraphics.h"
#include "..\nyanlib\include\allGeo.h"
#include "..\nyanlib\include\areaControl.h"
#include "..\nyanlib\include\picture.h"

//#include "mode.h"

#include "..\nnnUtilLib\myMessage.h"

#include "..\nnnUtilLib\nameList.h"
#include "..\nnnUtilLib\cviewControl.h"


#include "myTextInputBox.h"



char CMyTextInputBox::m_to2byteTable[]= "\
@Ih”“•fij–{C|D^\
‚O‚P‚Q‚R‚S‚T‚U‚V‚W‚XFGƒ„H\
—‚`‚a‚b‚c‚d‚e‚f‚g‚h‚i‚j‚k‚l‚m‚n\
‚o‚p‚q‚r‚s‚t‚u‚v‚w‚x‚ymnOQ\
e‚‚‚‚ƒ‚„‚…‚†‚‡‚ˆ‚‰‚Š‚‹‚Œ‚‚Ž‚\
‚‚‘‚’‚“‚”‚•‚–‚—‚˜‚™‚šobp`¡\
¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡\
¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡\
ƒABuvAEƒ’ƒ@ƒBƒDƒFƒHƒƒƒ…ƒ‡ƒb\
[ƒAƒCƒEƒGƒIƒJƒLƒNƒPƒRƒTƒVƒXƒZƒ\\
ƒ^ƒ`ƒcƒeƒgƒiƒjƒkƒlƒmƒnƒqƒtƒwƒzƒ}\
ƒ~ƒ€ƒƒ‚ƒ„ƒ†ƒˆƒ‰ƒŠƒ‹ƒŒƒƒƒ“JK";



CMyTextInputBox::CMyTextInputBox(HWND hwnd,CMyMessage* message,CViewControl* viewControl)
{
	m_hWnd = hwnd;
	m_message = message;
	m_viewControl = viewControl;

	m_setupList = NULL;

	m_parameterShuruiKosuu = 3;


	m_zahyo = new POINT[m_parameterShuruiKosuu];
	m_fontSize = new int[m_parameterShuruiKosuu];
	m_sukimaSize = new int[m_parameterShuruiKosuu];
	m_maxLength = new int[m_parameterShuruiKosuu];
	m_areaSize = new SIZE[m_parameterShuruiKosuu];
	m_cursorMode = new int[m_parameterShuruiKosuu];
	m_cursorColor = new int[m_parameterShuruiKosuu * 4];
	m_textColor = new int[m_parameterShuruiKosuu * 4];
	m_cursorTime = new int[m_parameterShuruiKosuu * 3];
	m_cursorDelta = new POINT[m_parameterShuruiKosuu];
	m_cursorSize = new SIZE[m_parameterShuruiKosuu];
	m_alignFlag = new int[m_parameterShuruiKosuu];

	m_autoOpenFlag = FALSE;
	m_autoCloseFlag = FALSE;

	m_enableFlag = FALSE;
	m_immMovedFlag = FALSE;
	m_immWindowParamGetFlag = FALSE;
	m_changedFlag = FALSE;
	m_pushReturnKeyFlag = FALSE;
	m_kanjiFlag = FALSE;
	m_kanjiHigh = 0;
	m_kanjiLow = 0;
	m_textBufferSize = 256;
	m_cursorCount = 0;
	m_text = new char[m_textBufferSize+1];

	m_nowParameterNumber = 0;

	SetZahyo(0,0,-1);
	SetFontSize(24,1,-1);
	SetMaxLength(256,-1);
	SetMaxLength(8,-1);
	SetAlignFlag(0,-1);
	SetCursorMode(1,-1);
	SetCursorTime(15,15,-1);
	SetTextColor(255,255,255,-1);
	
	POINT pt;
	pt.x = 0;
	pt.y = 0;
	SetCursorDelta(pt,-1);

	SIZE sz;
	sz.cx = 3;
	sz.cy = 24;
	SetCursorSize(sz,-1);
	SetCursorColor(255,255,255,255,-1);
	

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	SetRect(&m_immRect,0,0,screenSizeX,16);
	m_immZahyo.x = 0;
	m_immZahyo.y = 0;
}


CMyTextInputBox::~CMyTextInputBox()
{
	End();
}

void CMyTextInputBox::End(void)
{
	DELETEARRAY(m_text);

	DELETEARRAY(m_alignFlag);
	DELETEARRAY(m_zahyo);
	DELETEARRAY(m_fontSize);
	DELETEARRAY(m_sukimaSize);
	DELETEARRAY(m_maxLength);
	DELETEARRAY(m_areaSize);
	DELETEARRAY(m_cursorMode);
	DELETEARRAY(m_cursorColor);
	DELETEARRAY(m_textColor);
	DELETEARRAY(m_cursorTime);
	DELETEARRAY(m_cursorDelta);
	DELETEARRAY(m_cursorSize);

	if (m_immMovedFlag)
	{
		RemoveIMEWindow();
	}
}

void CMyTextInputBox::Init(void)
{
	m_changedFlag = FALSE;
	m_pushReturnKeyFlag = FALSE;
	m_kanjiFlag = FALSE;

	char* ptr = GetText();
	if (ptr != NULL)
	{
		*ptr = 0;
	}

	MoveIMEWindow();
}


void CMyTextInputBox::SetText(LPSTR name,BOOL moveFlag)
{
	if (name == NULL)
	{
		m_text[0] = 0;
		if (moveFlag)
		{
			MoveIMEWindow();
		}
		return;
	}

	int ln = strlen(name);
	if (ln>m_maxLength[m_nowParameterNumber])
	{
		ln = m_maxLength[m_nowParameterNumber];
	}
	memcpy(m_text,name,ln+1);
	if (moveFlag)
	{
		MoveIMEWindow();
	}
}



void CMyTextInputBox::Print(void)
{
	char* mes = GetText();
	if (mes != NULL)
	{
		if ((*mes) != 0)
		{
			POINT pt = GetTextZahyo();
			int fontSize = m_fontSize[m_nowParameterNumber];
			int r = m_textColor[m_nowParameterNumber*4+0];
			int g = m_textColor[m_nowParameterNumber*4+1];
			int b = m_textColor[m_nowParameterNumber*4+2];
			int sukimaSize = m_sukimaSize[m_nowParameterNumber];

			m_message->PrintMessage(pt.x,pt.y,mes,fontSize,r,g,b,sukimaSize);
		}
	}

	CursorAnime();
	PrintCursor();
}



void CMyTextInputBox::SetZahyo(int x,int y,int n)
{
	int st = n;
	int ed = n;
	if (n == -1)
	{
		st = 0;
		ed = m_parameterShuruiKosuu-1;
	}

	for (int i=st;i<=ed;i++)
	{
		m_zahyo[i].x = x;
		m_zahyo[i].y = y;
	}
}

void CMyTextInputBox::SetFontSize(int fontSize,int sukima,int n)
{
	int st = n;
	int ed = n;
	if (n == -1)
	{
		st = 0;
		ed = m_parameterShuruiKosuu-1;
	}

	for (int i=st;i<=ed;i++)
	{
		m_fontSize[i] = fontSize;
		m_sukimaSize[i] = sukima;
		CalcuAreaSize(i);
	}
}

void CMyTextInputBox::SetAlignFlag(int flg,int n)
{
	int st = n;
	int ed = n;
	if (n == -1)
	{
		st = 0;
		ed = m_parameterShuruiKosuu-1;
	}

	for (int i=st;i<=ed;i++)
	{
		m_alignFlag[i] = flg;
	}
}

void CMyTextInputBox::SetMaxLength(int mx,int n)
{
	if (mx > m_textBufferSize)
	{
		DELETEARRAY(m_text);
		m_text = new char[n+1];
		m_textBufferSize = mx;
	}

	int st = n;
	int ed = n;
	if (n == -1)
	{
		st = 0;
		ed = m_parameterShuruiKosuu-1;
	}

	for (int i=st;i<=ed;i++)
	{
		m_maxLength[i] = mx;
		CalcuAreaSize(i);
	}
}

void CMyTextInputBox::CalcuAreaSize(int n)
{
	int st = n;
	int ed = n;
	if (n == -1)
	{
		st = 0;
		ed = m_parameterShuruiKosuu-1;
	}

	for (int i=st;i<=ed;i++)
	{
		m_areaSize[i].cx = ((m_fontSize[i]+m_sukimaSize[i]) * m_maxLength[i])/2;
	}
}

void CMyTextInputBox::AddChara(int ch)
{
	if (m_enableFlag == FALSE) return;

	m_changedFlag = TRUE;

	if (ch == 13)
	{
		m_pushReturnKeyFlag = TRUE;
	}

	if ((ch == 8) || (ch == 127))	//DEL BS
	{
		DelKanji();
		return;
	}

	if (ch < 0x20) return;

	if (m_kanjiFlag)
	{
		AddKanji(m_kanjiHigh,ch);
		m_kanjiFlag = FALSE;
		return;
	}

	if (((ch >= 0x20) && (ch <= 0x7e)) || ((ch >=0xa0) && (ch <= 0xdf)))	//1byte code
	{
		AddKanji(m_to2byteTable[(ch-0x20)*2],m_to2byteTable[(ch-0x20)*2+1]);
		return;
	}

	if (((ch >= 0x80) && (ch <= 0x9f)) || (((ch >= 0xe0) && (ch <= 0xff))))	//kanji code
	{
		m_kanjiFlag = TRUE;
		m_kanjiHigh = ch;
		return;
	}


}



BOOL CMyTextInputBox::AddKanji(int high,int low)
{
	m_changedFlag = TRUE;

	char* ptr = GetText();
	int ln = strlen(ptr);

	if (ln<0) return FALSE;
	if (ln>m_textBufferSize-2) return FALSE;
	if (ln>m_maxLength[m_nowParameterNumber]-2) return FALSE;

	*(ptr+ln) = high;
	*(ptr+ln+1) = low;
	*(ptr+ln+2) = 0;

	MoveIMEWindow();

	return TRUE;
}

BOOL CMyTextInputBox::DelKanji(void)
{
	char* ptr = GetText();
	int ln = strlen(ptr);

	if (ln < 0) return FALSE;
	if (ln < 1) return FALSE;

	*(ptr+ln-2) = 0;
	MoveIMEWindow();
	return TRUE;
}


void CMyTextInputBox::Start(void)
{
	m_enableFlag = TRUE;
	if (m_immWindowParamGetFlag == FALSE)
	{
		HIMC himc = ImmGetContext(m_hWnd);
		if (himc != NULL)
		{
			COMPOSITIONFORM cf;
			cf.dwStyle = CFS_POINT;
			ImmGetCompositionWindow(himc,&cf);
			m_immZahyo = cf.ptCurrentPos;
			m_immRect = cf.rcArea;

			ImmReleaseContext(m_hWnd,himc);
			m_immWindowParamGetFlag = TRUE;
		}
	}

	if (m_autoOpenFlag)
	{
		HIMC himc = ImmGetContext(m_hWnd);
		if (himc != NULL)
		{
			if (ImmGetOpenStatus(himc) == FALSE)
			{
				ImmSetOpenStatus(himc,TRUE);
			}

			ImmReleaseContext(m_hWnd,himc);
		}
	}
}

void CMyTextInputBox::Stop(void)
{
	m_enableFlag = FALSE;
	AutoClose();
}


void CMyTextInputBox::AutoClose(void)
{
	if (m_autoCloseFlag)
	{
		HIMC himc = ImmGetContext(m_hWnd);
		if (himc != NULL)
		{
			if (ImmGetOpenStatus(himc))
			{
				ImmSetOpenStatus(himc,FALSE);
			}

			ImmReleaseContext(m_hWnd,himc);
		}
	}
}


void CMyTextInputBox::MoveIMEWindow(void)
{
	HIMC himc = ImmGetContext(m_hWnd);
	if (himc != NULL)
	{
		COMPOSITIONFORM cf;

	//	cf.dwStyle = CFS_RECT;
		cf.dwStyle = CFS_POINT;

		POINT pt = GetCursorZahyo();
		pt = m_viewControl->GameToView(pt);

		cf.ptCurrentPos = pt;
		ImmSetCompositionWindow(himc,&cf);

		ImmReleaseContext(m_hWnd,himc);
	}


}


void CMyTextInputBox::RemoveIMEWindow(void)
{
	if (m_immMovedFlag == FALSE) return;


	HIMC himc = ImmGetContext(m_hWnd);
	if (himc != NULL)
	{
		COMPOSITIONFORM cf;
		cf.ptCurrentPos = m_immZahyo;
	//	cf.rcArea = m_immRect;

//	cf.dwStyle = CFS_RECT;
		cf.dwStyle = CFS_POINT;

		ImmSetCompositionWindow(himc,&cf);

		ImmReleaseContext(m_hWnd,himc);
	}

	m_immMovedFlag = FALSE;
}


void CMyTextInputBox::SetCursorMode(int md,int n)
{
	int st = n;
	int ed = n;
	if (n == -1)
	{
		st = 0;
		ed = m_parameterShuruiKosuu-1;
	}

	for (int i=st;i<=ed;i++)
	{
		m_cursorMode[i] = md;
	}
}

void CMyTextInputBox::SetCursorSize(SIZE sz,int n)
{
	int st = n;
	int ed = n;
	if (n == -1)
	{
		st = 0;
		ed = m_parameterShuruiKosuu-1;
	}

	for (int i=st;i<=ed;i++)
	{
		m_cursorSize[i] = sz;
	}
}

void CMyTextInputBox::SetCursorDelta(POINT pt,int n)
{
	int st = n;
	int ed = n;
	if (n == -1)
	{
		st = 0;
		ed = m_parameterShuruiKosuu-1;
	}

	for (int i=st;i<=ed;i++)
	{
		m_cursorDelta[i] = pt;
	}
}


void CMyTextInputBox::SetCursorTime(int onTime,int offTime,int n)
{
	if (offTime == -1) offTime = onTime;

	int st = n;
	int ed = n;
	if (n == -1)
	{
		st = 0;
		ed = m_parameterShuruiKosuu-1;
	}

	for (int i=st;i<=ed;i++)
	{
		m_cursorTime[i*3] = onTime;
		m_cursorTime[i*3+1] = offTime;
		m_cursorTime[i*3+2] = onTime + offTime;
	}
}

void CMyTextInputBox::CursorAnime(int cnt)
{
	m_cursorCount += cnt;
	int dv = m_cursorTime[m_nowParameterNumber*3+2];
	if (dv<1) dv = 1;
	m_cursorCount %= dv;
}

void CMyTextInputBox::SetCursorColor(int r,int g,int b,int a,int n)
{
	if (g == -1) g = r;
	if (b == -1) b = g;

	int st = n;
	int ed = n;
	if (n == -1)
	{
		st = 0;
		ed = m_parameterShuruiKosuu-1;
	}

	for (int i=st;i<=ed;i++)
	{
		m_cursorColor[i*4+0] = r;
		m_cursorColor[i*4+1] = g;
		m_cursorColor[i*4+2] = b;
		m_cursorColor[i*4+3] = a;
	}

}


void CMyTextInputBox::PrintCursor(void)
{
	if (m_cursorMode[m_nowParameterNumber] == 0) return;

	//box
	if (m_cursorMode[m_nowParameterNumber] == 1)
	{
		if (m_cursorCount >= m_cursorTime[m_nowParameterNumber*3+0]) return;
		POINT pt = GetCursorZahyo();
		int putX = pt.x;
		int putY = pt.y;
		int sizeX = m_cursorSize[m_nowParameterNumber].cx;
		int sizeY = m_cursorSize[m_nowParameterNumber].cy;

		int r = m_cursorColor[m_nowParameterNumber*4+0];
		int g = m_cursorColor[m_nowParameterNumber*4+1];
		int b = m_cursorColor[m_nowParameterNumber*4+2];
		int a = m_cursorColor[m_nowParameterNumber*4+3];//dummy

		CAllGeo::BoxFill(putX,putY,sizeX,sizeY,r,g,b);

		return;
	}
}


POINT CMyTextInputBox::GetCursorZahyo(void)
{
	POINT pt = GetTextZahyo();
	char* mes = GetText();
	int ln = strlen(mes);
	pt.x += ((ln/2)*((m_fontSize[m_nowParameterNumber]+m_sukimaSize[m_nowParameterNumber])));

	pt.x += m_cursorDelta[m_nowParameterNumber].x;
	pt.y += m_cursorDelta[m_nowParameterNumber].y;

	return pt;
}

POINT CMyTextInputBox::GetTextZahyo(POINT pt,LPSTR name,int maxLen,int alignMode)
{

	int x = 0;
	int y = 0;

	int mojiSize = m_fontSize[m_nowParameterNumber]+m_sukimaSize[m_nowParameterNumber];
	int areaSize = mojiSize * (maxLen/2);

	if (alignMode == 1)
	{
		x += areaSize / 2;
		int ln = strlen(name);
		x -= ((ln/2)*(mojiSize))/2;
	}
	else if (alignMode == 2)
	{
		x += areaSize;
		int ln = strlen(name);
		x -= (ln/2)*mojiSize;
	}

	pt.x += x;
	pt.y += y;

	return pt;
}


POINT CMyTextInputBox::GetTextZahyo(void)
{
	return GetTextZahyo(m_zahyo[m_nowParameterNumber],GetText(),m_maxLength[m_nowParameterNumber],m_alignFlag[m_nowParameterNumber]);
}

void CMyTextInputBox::SetTextColor(int r,int g,int b,int n)
{
	if (g < 0) g = r;
	if (b < 0) b = g;

	int st = n;
	int ed = n;
	if (n == -1)
	{
		st = 0;
		ed = m_parameterShuruiKosuu-1;
	}

	for (int i=st;i<=ed;i++)
	{
		m_textColor[i*4+0] = r;
		m_textColor[i*4+1] = g;
		m_textColor[i*4+2] = b;
		m_textColor[i*4+3] = 255;
	}
}


void CMyTextInputBox::SetSetup(CNameList* nameList)
{
	m_setupList = nameList;

	for (int i=0;i<m_parameterShuruiKosuu;i++)
	{
//		SetParameter("",i);
	}
}

void CMyTextInputBox::ChangeParameterNumber(int n)
{
	if (n>=m_parameterShuruiKosuu) n = m_parameterShuruiKosuu-1;
	if (n<0) n = 0;

	m_nowParameterNumber = n;

}

void CMyTextInputBox::SetParameter(LPSTR tagName,int n)
{
	char name[1024];
/*
	wsprintf(name,"%sPrintX",tagName);
	int x = 0;
	if (GetInitGameParam(&x,name))
	{
		m_zahyo[n].x = x;
	}

	wsprintf(name,"%sPrintY",tagName);
	int y = 0;
	if (GetInitGameParam(&y,name))
	{
		m_zahyo[n].y = y;
	}
*/


	wsprintf(name,"%sMax",tagName);
	int mx = 4;
	if (GetInitGameParam(&mx,name))
	{
		mx *= 2;
		SetMaxLength(mx,n);
	}

	int r = 255;
	wsprintf(name,"%sColorR",tagName);
	if (GetInitGameParam(&r,name))
	{
		m_textColor[n*4+0] = r;
	}

	int g = 255;
	wsprintf(name,"%sColorG",tagName);
	if (GetInitGameParam(&g,name))
	{
		m_textColor[n*4+1] = g;
	}

	int b = 255;
	wsprintf(name,"%sColorB",tagName);
	if (GetInitGameParam(&b,name))
	{
		m_textColor[n*4+2] = b;
	}

	int alignMode = 0;
	wsprintf(name,"%sAlignMode",tagName);
	if (GetInitGameParam(&alignMode,name))
	{
		m_alignFlag[n] = alignMode;
	}

	int cursorMode = 1;
	wsprintf(name,"%sCursorMode",tagName);
	if (GetInitGameParam(&cursorMode,name))
	{
		m_cursorMode[n] = cursorMode;
	}

	int cr = 255;
	wsprintf(name,"%sCursorColorR",tagName);
	if (GetInitGameParam(&cr,name))
	{
		m_cursorColor[n*4+0] = cr;
	}

	int cg = 255;
	wsprintf(name,"%sCursorColorG",tagName);
	if (GetInitGameParam(&cg,name))
	{
		m_cursorColor[n*4+1] = cg;
	}

	int cb = 255;
	wsprintf(name,"%sCursorColorB",tagName);
	if (GetInitGameParam(&cb,name))
	{
		m_cursorColor[n*4+2] = cb;
	}

	int ca = 255;
	wsprintf(name,"%sCursorColorA",tagName);
	if (GetInitGameParam(&ca,name))
	{
		m_cursorColor[n*4+3] = ca;
	}

	int cSizeX = 3;
	wsprintf(name,"%sCursorSizeX",tagName);
	if (GetInitGameParam(&cSizeX,name))
	{
		m_cursorSize[n].cx = cSizeX;
	}

	int cSizeY = 24;
	wsprintf(name,"%sCursorSizeY",tagName);
	if (GetInitGameParam(&cSizeY,name))
	{
		m_cursorSize[n].cy = cSizeY;
	}

	int cPrintX = 0;
	wsprintf(name,"%sCursorPrintX",tagName);
	if (GetInitGameParam(&cPrintX,name))
	{
		m_cursorDelta[n].x = cPrintX;
	}

	int cPrintY = 0;
	wsprintf(name,"%sCursorPrintY",tagName);
	if (GetInitGameParam(&cPrintY,name))
	{
		m_cursorDelta[n].y = cPrintY;
	}

	int onTime = 15;
	wsprintf(name,"%sCursorOnTime",tagName);
	if (GetInitGameParam(&onTime,name))
	{
		m_cursorTime[n*3+0] = onTime;
	}

	int offTime = 15;
	wsprintf(name,"%sCursorOffTime",tagName);
	if (GetInitGameParam(&offTime,name))
	{
		m_cursorTime[n*3+1] = offTime;
	}

	m_cursorTime[n*3+2] = m_cursorTime[n*3+0] + m_cursorTime[n*3+1];

	int fontSize = 24;
	wsprintf(name,"%sFontSize",tagName);
	if (GetInitGameParam(&fontSize,name))
	{
		m_fontSize[n] = fontSize;
	}

	int sukimaSize = 1;
	wsprintf(name,"%sSukimaSize",tagName);
	if (GetInitGameParam(&sukimaSize,name))
	{
		m_sukimaSize[n] = sukimaSize;
	}






	ChangeParameterNumber(n);
}




BOOL CMyTextInputBox::GetInitGameParam(int* lpVar, LPSTR name)
{
	if (m_setupList == NULL) return FALSE;

	int rNum = m_setupList->SearchName2(name);
	if (rNum == -1) return FALSE;
	*lpVar = atoi(m_setupList->GetName(rNum + 1));

	return TRUE;
}


BOOL CMyTextInputBox::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	if (m_setupList == NULL) return FALSE;

	int rNum = m_setupList->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_setupList->GetName(rNum + 1);

	return TRUE;
}

/*_*/




