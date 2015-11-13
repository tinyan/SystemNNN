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
#include "..\nnnUtilLib\Myfont.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\inputStatus.h"

#include "..\nnnUtilLib\nameList.h"
#include "..\nnnUtilLib\cviewControl.h"
#include "..\nnnUtilLib\myIme.h"


#include "softKey.h"



char CSoftKey::m_to2byteTable[]= "\
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


#define SOFTKET_TEXTTYPE_KAKUTEI 0
#define SOFTKET_TEXTTYPE_HENKAN 1
#define SOFTKET_TEXTTYPE_INPUT 2


#define SOFTCOMMANDKEY_NEXT 1

#define SOFTCOMMANDKEY_HENKAN 100
#define SOFTCOMMANDKEY_KAKUTEI 101
#define SOFTCOMMANDKEY_DELETE 102
#define SOFTCOMMANDKEY_OK 103
#define SOFTCOMMANDKEY_DAKUTEN 104
#define SOFTCOMMANDKEY_HANDAKUTEN 105
#define SOFTCOMMANDKEY_SHIFT 106


#define SOFTKEYTEXT_HENKAN "•ÏŠ·"
#define SOFTKEYTEXT_HIRAGANA "‚©‚È"
#define SOFTKEYTEXT_KATAKANA "ƒJƒi"
#define SOFTKEYTEXT_ALPHA "‰p”"
#define SOFTKEYTEXT_KIGOU "‰p¬"
#define SOFTKEYTEXT_KAKUTEI "Šm’è"
#define SOFTKEYTEXT_DELETE "íœ"
#define SOFTKEYTEXT_OK "Œˆ’è"
#define SOFTKEYTEXT_DAKUTEN "J"
#define SOFTKEYTEXT_HANDAKUTEN "K"
#define SOFTKEYTEXT_SHIFT "ª"


#define SOFTKEYTEXT_DELETE_1BYTE "DEL"
#define SOFTKEYTEXT_OK_1BYTE "OK"
#define SOFTKEYTEXT_SHIFT_1BYTE "SHIFT"


CSoftKey::MYSOFTKEY CSoftKey::m_defaultKeySet[]=
{
	{0,0,0,"‚ "},
	{0,1,0,"‚¢"},
	{0,2,0,"‚¤"},
	{0,3,0,"‚¦"},
	{0,4,0,"‚¨"},

	{0,5,0,"‚©"},
	{0,6,0,"‚«"},
	{0,7,0,"‚­"},
	{0,8,0,"‚¯"},
	{0,9,0,"‚±"},

	{0,10,0,"‚³"},
	{0,11,0,"‚µ"},
	{0,12,0,"‚·"},
	{0,13,0,"‚¹"},
	{0,14,0,"‚»"},

	{0,0,1,"‚½"},
	{0,1,1,"‚¿"},
	{0,2,1,"‚Â"},
	{0,3,1,"‚Ä"},
	{0,4,1,"‚Æ"},

	{0,5,1,"‚È"},
	{0,6,1,"‚É"},
	{0,7,1,"‚Ê"},
	{0,8,1,"‚Ë"},
	{0,9,1,"‚Ì"},

	{0,10,1,"‚Í"},
	{0,11,1,"‚Ð"},
	{0,12,1,"‚Ó"},
	{0,13,1,"‚Ö"},
	{0,14,1,"‚Ù"},

	{0,0,2,"‚Ü"},
	{0,1,2,"‚Ý"},
	{0,2,2,"‚Þ"},
	{0,3,2,"‚ß"},
	{0,4,2,"‚à"},

	{0,5,2,"‚â"},

	{0,7,2,"‚ä"},

	{0,9,2,"‚æ"},

	{0,10,2,"‚ç"},
	{0,11,2,"‚è"},
	{0,12,2,"‚é"},
	{0,13,2,"‚ê"},
	{0,14,2,"‚ë"},

	{0,0,3,"‚í"},
	{0,1,3,"‚ð"},
	{0,2,3,"‚ñ"},

	{0,4,3,"‚Á"},
	
	{0,5,3,"‚á"},

	{0,7,3,"‚ã"},

	{0,9,3,"‚å"},

	{0,10,3,"J"},
	{0,11,3,"K"},

	{0,0,4,SOFTKEYTEXT_HENKAN},
	{0,1,4,SOFTKEYTEXT_KAKUTEI},
	{0,2,4,SOFTKEYTEXT_KATAKANA},
	{0,3,4,SOFTKEYTEXT_ALPHA},
	{0,4,4,SOFTKEYTEXT_DELETE},

	{0,5,4,SOFTKEYTEXT_OK},

//
	{1,0,0,"ƒA"},
	{1,1,0,"ƒC"},
	{1,2,0,"ƒE"},
	{1,3,0,"ƒG"},
	{1,4,0,"ƒI"},

	{1,5,0,"ƒJ"},
	{1,6,0,"ƒL"},
	{1,7,0,"ƒN"},
	{1,8,0,"ƒP"},
	{1,9,0,"ƒR"},

	{1,10,0,"ƒT"},
	{1,11,0,"ƒV"},
	{1,12,0,"ƒX"},
	{1,13,0,"ƒZ"},
	{1,14,0,"ƒ\"},

	{1,0,1,"ƒ^"},
	{1,1,1,"ƒ`"},
	{1,2,1,"ƒc"},
	{1,3,1,"ƒe"},
	{1,4,1,"ƒg"},

	{1,5,1,"ƒi"},
	{1,6,1,"ƒj"},
	{1,7,1,"ƒk"},
	{1,8,1,"ƒl"},
	{1,9,1,"ƒm"},

	{1,10,1,"ƒn"},
	{1,11,1,"ƒq"},
	{1,12,1,"ƒt"},
	{1,13,1,"ƒw"},
	{1,14,1,"ƒz"},

	{1,0,2,"ƒ}"},
	{1,1,2,"ƒ~"},
	{1,2,2,"ƒ€"},
	{1,3,2,"ƒ"},
	{1,4,2,"ƒ‚"},

	{1,5,2,"ƒ„"},

	{1,7,2,"ƒ†"},

	{1,9,2,"ƒˆ"},

	{1,10,2,"ƒ‰"},
	{1,11,2,"ƒŠ"},
	{1,12,2,"ƒ‹"},
	{1,13,2,"ƒŒ"},
	{1,14,2,"ƒ"},

	{1,0,3,"ƒ"},
	{1,1,3,"ƒ’"},
	{1,2,3,"ƒ“"},

	{1,4,3,"ƒb"},
	
	{1,5,3,"ƒƒ"},

	{1,7,3,"ƒ…"},

	{1,9,3,"ƒ‡"},

	{1,10,3,"J"},
	{1,11,3,"K"},

	{1,0,4,SOFTKEYTEXT_HENKAN},
	{1,1,4,SOFTKEYTEXT_KAKUTEI},
	{1,2,4,SOFTKEYTEXT_HIRAGANA},
	{1,3,4,SOFTKEYTEXT_ALPHA},
	{1,4,4,SOFTKEYTEXT_DELETE},

	{1,5,4,SOFTKEYTEXT_OK},


//
	//
	{2,0,0,"‚P"},
	{2,1,0,"‚Q"},
	{2,2,0,"‚R"},
	{2,3,0,"‚S"},
	{2,4,0,"‚T"},

	{2,5,0,"‚U"},
	{2,6,0,"‚V"},
	{2,7,0,"‚W"},
	{2,8,0,"‚X"},
	{2,9,0,"‚O"},

	{2,0,1,"‚`"},
	{2,1,1,"‚a"},
	{2,2,1,"‚b"},
	{2,3,1,"‚c"},
	{2,4,1,"‚d"},

	{2,5,1,"‚e"},
	{2,6,1,"‚f"},
	{2,7,1,"‚g"},
	{2,8,1,"‚h"},
	{2,9,1,"‚i"},

	{2,10,1,"‚j"},
	{2,11,1,"‚k"},
	{2,12,1,"‚l"},
	{2,13,1,"‚m"},
	{2,14,1,"‚n"},

	{2,0,2,"‚o"},
	{2,1,2,"‚p"},
	{2,2,2,"‚q"},
	{2,3,2,"‚r"},
	{2,4,2,"‚s"},

	{2,5,2,"‚t"},
	{2,6,2,"‚u"},
	{2,7,2,"‚v"},
	{2,8,2,"‚w"},
	{2,9,2,"‚x"},

	{2,10,2,"‚y"},

	{2,0,4,SOFTKEYTEXT_HENKAN},
	{2,1,4,SOFTKEYTEXT_KAKUTEI},
	{2,2,4,SOFTKEYTEXT_SHIFT},
	{2,3,4,SOFTKEYTEXT_HIRAGANA},
	{2,4,4,SOFTKEYTEXT_DELETE},

	{2,5,4,SOFTKEYTEXT_OK},


	//
	//
	{3,0,0,"‚P"},
	{3,1,0,"‚Q"},
	{3,2,0,"‚R"},
	{3,3,0,"‚S"},
	{3,4,0,"‚T"},

	{3,5,0,"‚U"},
	{3,6,0,"‚V"},
	{3,7,0,"‚W"},
	{3,8,0,"‚X"},
	{3,9,0,"‚O"},


	{3,0,1,"‚"},
	{3,1,1,"‚‚"},
	{3,2,1,"‚ƒ"},
	{3,3,1,"‚„"},
	{3,4,1,"‚…"},

	{3,5,1,"‚†"},
	{3,6,1,"‚‡"},
	{3,7,1,"‚ˆ"},
	{3,8,1,"‚‰"},
	{3,9,1,"‚Š"},

	{3,10,1,"‚‹"},
	{3,11,1,"‚Œ"},
	{3,12,1,"‚"},
	{3,13,1,"‚Ž"},
	{3,14,1,"‚"},

	{3,0,2,"‚"},
	{3,1,2,"‚‘"},
	{3,2,2,"‚’"},
	{3,3,2,"‚“"},
	{3,4,2,"‚”"},

	{3,5,2,"‚•"},
	{3,6,2,"‚–"},
	{3,7,2,"‚—"},
	{3,8,2,"‚˜"},
	{3,9,2,"‚™"},

	{3,10,2,"‚š"},

	{3,0,4,SOFTKEYTEXT_HENKAN},
	{3,1,4,SOFTKEYTEXT_KAKUTEI},
	{3,2,4,SOFTKEYTEXT_SHIFT},
	{3,3,4,SOFTKEYTEXT_HIRAGANA},
	{3,4,4,SOFTKEYTEXT_DELETE},

	{3,5,4,SOFTKEYTEXT_OK},

};


CSoftKey::MYSOFTKEY CSoftKey::m_defaultKeySet1Byte[]=
{
	{0,0,0,"a"},
	{0,1,0,"b"},
	{0,2,0,"c"},
	{0,3,0,"d"},
	{0,4,0,"e"},

	{0,5,0,"f"},
	{0,6,0,"g"},
	{0,7,0,"h"},
	{0,8,0,"i"},
	{0,9,0,"j"},

	{0,10,0,"k"},
	{0,11,0,"l"},
	{0,12,0,"m"},
	{0,13,0,"n"},
	{0,14,0,"o"},

	{0,0,1,"p"},
	{0,1,1,"q"},
	{0,2,1,"r"},
	{0,3,1,"s"},
	{0,4,1,"t"},

	{0,5,1,"u"},
	{0,6,1,"v"},
	{0,7,1,"w"},
	{0,8,1,"x"},
	{0,9,1,"y"},

	{0,10,1,"z"},

	{0,0,4,SOFTKEYTEXT_SHIFT_1BYTE},
	{0,3,4,SOFTKEYTEXT_DELETE_1BYTE},

	{0,6,4,SOFTKEYTEXT_OK_1BYTE},

//
	{1,0,0,"A"},
	{1,1,0,"B"},
	{1,2,0,"C"},
	{1,3,0,"D"},
	{1,4,0,"E"},

	{1,5,0,"F"},
	{1,6,0,"G"},
	{1,7,0,"H"},
	{1,8,0,"I"},
	{1,9,0,"J"},

	{1,10,0,"K"},
	{1,11,0,"L"},
	{1,12,0,"M"},
	{1,13,0,"N"},
	{1,14,0,"O"},

	{1,0,1,"P"},
	{1,1,1,"Q"},
	{1,2,1,"R"},
	{1,3,1,"S"},
	{1,4,1,"T"},

	{1,5,1,"U"},
	{1,6,1,"V"},
	{1,7,1,"W"},
	{1,8,1,"X"},
	{1,9,1,"Y"},

	{1,10,1,"Z"},

//	{1,0,4,SOFTKEYTEXT_HENKAN},
//	{1,1,4,SOFTKEYTEXT_KAKUTEI},
//	{1,2,4,SOFTKEYTEXT_HIRAGANA},
	{1,0,4,SOFTKEYTEXT_SHIFT_1BYTE},
	{1,3,4,SOFTKEYTEXT_DELETE_1BYTE},

	{1,6,4,SOFTKEYTEXT_OK_1BYTE},
};

char CSoftKey::m_dakutenList[][4]=
{
	"‚©","‚ª","‚«","‚¬","‚­","‚®",	"‚¯","‚°","‚±","‚²",
	"‚³","‚´","‚µ","‚¶","‚·","‚¸","‚¹","‚º","‚»","‚¼",
	"‚½","‚¾","‚¿","‚À","‚Â","‚Ã","‚Ä","‚Å","‚Æ","‚Ç",
	"‚Í","‚Î","‚Ð","‚Ñ","‚Ó","‚Ô","‚Ö","‚×","‚Ù","‚Ú",
	"‚Ï","‚Î","‚Ò","‚Ñ","‚Õ","‚Ô","‚Ø","‚×","‚Û","‚Ú",
	"ƒJ","ƒK","ƒL","ƒM","ƒN","ƒO",	"ƒP","ƒQ","ƒR","ƒS",
	"ƒT","ƒU","ƒV","ƒW","ƒX","ƒY","ƒZ","ƒ[","ƒ\","ƒ]",
	"ƒ^","ƒ_","ƒ`","ƒa","ƒc","ƒY","ƒe","ƒf","ƒg","ƒh",
	"ƒn","ƒo","ƒq","ƒr","ƒt","ƒu","ƒw","ƒx","ƒz","ƒ{",
	"ƒp","ƒo","ƒs","ƒr","ƒv","ƒu","ƒy","ƒx","ƒ|","ƒ{",
	"ƒE","ƒ”",

	""
};

char CSoftKey::m_handakutenList[][4]=
{
	"‚Í","‚Ï","‚Ð","‚Ò","‚Ó","‚Õ","‚Ö","‚Ø","‚Ù","‚Û",
	"‚Î","‚Ï","‚Ñ","‚Ò","‚Ô","‚Õ","‚×","‚Ø","‚Ú","‚Û",
	"ƒn","ƒp","ƒq","ƒs","ƒt","ƒv","ƒw","ƒy","ƒz","ƒ|",
	"ƒo","ƒp","ƒr","ƒs","ƒu","ƒv","ƒx","ƒy","ƒ{","ƒ|",
	""
};

CSoftKey::MYSOFTCOMMANDKEY CSoftKey::m_userCommandCheckList[]=
{
	{SOFTCOMMANDKEY_HENKAN,"•ÏŠ·"},
	{SOFTCOMMANDKEY_KAKUTEI,"Šm’è"},
	{SOFTCOMMANDKEY_DELETE,"íœ"},
	{SOFTCOMMANDKEY_OK,"Œˆ’è"},
	{SOFTCOMMANDKEY_DAKUTEN,"‘÷“_"},
	{SOFTCOMMANDKEY_HANDAKUTEN,"”¼‘÷“_"},
	{SOFTCOMMANDKEY_SHIFT,"ƒVƒtƒg"},

	{-1,""},
};

CSoftKey::MYSOFTCOMMANDKEY CSoftKey::m_userCommandCheckList1Byte[]=
{
	{-2,"•ÏŠ·"},
	{-2,"Šm’è"},
	{SOFTCOMMANDKEY_DELETE,"DEL"},
	{SOFTCOMMANDKEY_OK,"OK"},
	{-2,"‘÷“_"},
	{-2,"”¼‘÷“_"},
	{SOFTCOMMANDKEY_SHIFT,"SHIFT"},

	{-1,""},
};

CSoftKey::MYSOFTCOMMANDKEY CSoftKey::m_commandKeyList[]=
{
	{SOFTCOMMANDKEY_HENKAN,SOFTKEYTEXT_HENKAN},
	{SOFTCOMMANDKEY_KAKUTEI,SOFTKEYTEXT_KAKUTEI},

	{SOFTCOMMANDKEY_DELETE,SOFTKEYTEXT_DELETE},
	{SOFTCOMMANDKEY_OK,SOFTKEYTEXT_OK},
	{SOFTCOMMANDKEY_DAKUTEN,SOFTKEYTEXT_DAKUTEN},
	{SOFTCOMMANDKEY_HANDAKUTEN,SOFTKEYTEXT_HANDAKUTEN},

	{SOFTCOMMANDKEY_SHIFT,SOFTKEYTEXT_SHIFT},

	{SOFTCOMMANDKEY_NEXT+0,SOFTKEYTEXT_HIRAGANA},
	{SOFTCOMMANDKEY_NEXT+1,SOFTKEYTEXT_KATAKANA},
	{SOFTCOMMANDKEY_NEXT+2,SOFTKEYTEXT_ALPHA},
	{SOFTCOMMANDKEY_NEXT+3,SOFTKEYTEXT_KIGOU},

	{-1,""},
};

CSoftKey::MYSOFTCOMMANDKEY CSoftKey::m_commandKeyList1Byte[]=
{
//	{SOFTCOMMANDKEY_HENKAN,SOFTKEYTEXT_HENKAN},
//	{SOFTCOMMANDKEY_KAKUTEI,SOFTKEYTEXT_KAKUTEI},

	{SOFTCOMMANDKEY_DELETE,SOFTKEYTEXT_DELETE_1BYTE},
	{SOFTCOMMANDKEY_OK,SOFTKEYTEXT_OK_1BYTE},
//	{SOFTCOMMANDKEY_DAKUTEN,SOFTKEYTEXT_DAKUTEN},
//	{SOFTCOMMANDKEY_HANDAKUTEN,SOFTKEYTEXT_HANDAKUTEN},

	{SOFTCOMMANDKEY_SHIFT,SOFTKEYTEXT_SHIFT_1BYTE},

//	{SOFTCOMMANDKEY_NEXT+0,SOFTKEYTEXT_HIRAGANA},
//	{SOFTCOMMANDKEY_NEXT+1,SOFTKEYTEXT_KATAKANA},
//	{SOFTCOMMANDKEY_NEXT+2,SOFTKEYTEXT_ALPHA},
//	{SOFTCOMMANDKEY_NEXT+3,SOFTKEYTEXT_KIGOU},

	{-1,""},
};

char CSoftKey::m_defaultDialogFilename[32]= "ta_softkey1";


CSoftKey::CSoftKey(CMyMessage* message)
{
//	m_hWnd = hwnd;
	m_message = message;
//	m_viewControl = viewControl;

	m_setupList = new CNameList();
	m_setupList->LoadFile("nya\\softkey.xtx");

	int codeByte = CMyFont::m_codeByte;

	m_textTypeMax = 3;
	for (int i=0;i<m_textTypeMax;i++)
	{
		m_textLengthMax[i] = 6;
	}
	m_textLengthMax[0] = 6;
	m_textLengthMax[1] = 6;
	m_textLengthMax[2] = 6;


	int textMax = m_textLengthMax[0];
	GetInitGameParam(&textMax,"kakuteiTextMax");
	m_textLengthMax[0] = textMax;

	textMax = m_textLengthMax[1];
	GetInitGameParam(&textMax,"henkanTextMax");
	m_textLengthMax[1] = textMax;

	textMax = m_textLengthMax[2];
	GetInitGameParam(&textMax,"inputTextMax");
	m_textLengthMax[2] = textMax;

	for (int i=0;i<m_textTypeMax;i++)
	{
		m_textLengthMaxDefault[i] = m_textLengthMax[i];
	}


	m_dialogPrintX = 100;
	m_dialogPrintY = 100;
	GetInitGameParam(&m_dialogPrintX,"dialogPrintX");
	GetInitGameParam(&m_dialogPrintY,"dialogPrintY");
	m_softKeyPrintX = 50;
	m_softKeyPrintY = 30;
	GetInitGameParam(&m_softKeyPrintX,"softKeyPrintX");
	GetInitGameParam(&m_softKeyPrintY,"softKeyPrintY");

	for (int i=0;i<16;i++)
	{
		m_dialogFilename[i] = m_defaultDialogFilename;
	}

	if (1)
	{
		LPSTR filename = NULL;
		for (int i=0;i<16;i++)
		{
			char name[256];
			sprintf_s(name,256,"dialog%dFilename",i+1);
			if (GetInitGameString(&filename,name))
			{
				m_dialogFilename[i] = filename;
			}
			else
			{
				break;
			}
		}
	}
	m_dialogPic = new CPicture();

	int sizeX = 24;
	int sizeY = 24;

	GetInitGameParam(&sizeX,"softKeySizeX");
	GetInitGameParam(&sizeX,"softKeySizeY");
	m_softKeySize.cx = sizeX;
	m_softKeySize.cy = sizeY;
	m_fontSize = sizeX;
	GetInitGameParam(&m_fontSize,"softKeyFontSize");

	m_useFont = 1;
	GetInitGameParam(&m_useFont,"useFont");

	m_fontColorR = 255;
	m_fontColorG = 255;
	m_fontColorB = 255;
	GetInitGameParam(&m_fontColorR,"fontColorR");
	GetInitGameParam(&m_fontColorG,"fontColorG");
	GetInitGameParam(&m_fontColorB,"fontColorB");

	m_selectColorR = 255;
	m_selectColorG = 255;
	m_selectColorB = 255;
	m_selectColorA = 50;
	GetInitGameParam(&m_selectColorR,"selectColorR");
	GetInitGameParam(&m_selectColorG,"selectColorG");
	GetInitGameParam(&m_selectColorB,"selectColorB");
	GetInitGameParam(&m_selectColorA,"selectColorA");



	m_keyPointNextX = sizeX + 8;
	m_keyPointNextY = sizeY + 8;
	m_keyPointBlockX = 5;
	m_keyPointBlockY = 1;
	m_keyPointSkipX = 16;
	m_keyPointSkipY = 0;
	m_keyPrintDeltaX = 0;
	m_keyPrintDeltaY = 0;
	if (codeByte == 1)
	{
		m_keyPrintDeltaX = sizeX / 4;
	}

	GetInitGameParam(&m_keyPointNextX,"softKeyNextX");
	GetInitGameParam(&m_keyPointNextY,"softKeyNextY");
	GetInitGameParam(&m_keyPointBlockX,"softKeyBlockX");
	GetInitGameParam(&m_keyPointBlockY,"softKeyBlockY");
	GetInitGameParam(&m_keyPointSkipX,"softKeySkipX");
	GetInitGameParam(&m_keyPointSkipY,"softKeySkipY");
	GetInitGameParam(&m_keyPrintDeltaX,"keyPrintDeltaX");
	GetInitGameParam(&m_keyPrintDeltaY,"keyPrintDeltaY");

	for (int j=0;j<SOFTKEY_Y_MAX;j++)
	{
		for (int i=0;i<SOFTKEY_X_MAX;i++)
		{
			int x = i * m_keyPointNextX + (i / m_keyPointBlockX) * m_keyPointSkipX;
			int y = j * m_keyPointNextY + (j / m_keyPointBlockY) * m_keyPointSkipY;

			m_keyPoint[j][i].x = x;
			m_keyPoint[j][i].y = y;
			m_keySize[j][i].cx = m_softKeySize.cx;
			m_keySize[j][i].cy = m_softKeySize.cy;
		}

	}
	if (codeByte == 2)
	{
		for (int i=0;i<SOFTKEY_X_MAX;i++)
		{
			int j = 4;
			int x = i * m_keyPointNextX*2 ;
			int y = j * m_keyPointNextY + (j / m_keyPointBlockY) * m_keyPointSkipY;

			m_keyPoint[j][i].x = x;
			m_keyPoint[j][i].y = y;

			m_keySize[j][i].cx = m_softKeySize.cx * 2;
			m_keySize[j][i].cy = m_softKeySize.cy;
		}
	}
	else
	{
			int j = 4;
			for (int i=0;i<3;i++)
			{
				int x = i * m_keyPointNextX*3 ;
				int y = j * m_keyPointNextY + (j / m_keyPointBlockY) * m_keyPointSkipY;

				m_keyPoint[j][i*3].x = x;
				m_keyPoint[j][i*3].y = y;

				m_keySize[j][i*3].cy = m_softKeySize.cy;
			}

			m_keySize[j][0].cx = (m_softKeySize.cx * (5+1))/2;
			m_keySize[j][3].cx = (m_softKeySize.cx * (3+1))/2;
			m_keySize[j][6].cx = (m_softKeySize.cx * (2+1))/2;
	}





	int customSize = 0;
	GetInitGameParam(&customSize,"customSize");
	if (customSize)
	{
		CNameList* customList = new CNameList();
		customList->LoadFile("nya\\softkeysize.xtx");
		int k = customList->GetNameKosuu() / 4;
		for (int i=0;i<k;i++)
		{
			int nx = atoi(customList->GetName(i*4));
			int ny = atoi(customList->GetName(i*4+1));
			nx--;
			ny--;
			int cx = atoi(customList->GetName(i*4+2));
			int cy = atoi(customList->GetName(i*4+3));
			if ((nx>=0) && (nx<SOFTKEY_X_MAX) && (ny>=0) && (ny<SOFTKEY_Y_MAX))
			{
				m_keySize[ny][nx].cx = cx;
				m_keySize[ny][nx].cy = cy;
			}
		}
		ENDDELETECLASS(customList);
	}

	int customPoint = 0;
	GetInitGameParam(&customPoint,"customPoint");
	if (customPoint)
	{
		CNameList* customList = new CNameList();
		customList->LoadFile("nya\\softkeypoint.xtx");
		int k = customList->GetNameKosuu() / 4;
		for (int i=0;i<k;i++)
		{
			int nx = atoi(customList->GetName(i*4));
			int ny = atoi(customList->GetName(i*4+1));
			nx--;
			ny--;
			int x = atoi(customList->GetName(i*4+2));
			int y = atoi(customList->GetName(i*4+3));
			if ((nx>=0) && (nx<SOFTKEY_X_MAX) && (ny>=0) && (ny<SOFTKEY_Y_MAX))
			{
				m_keyPoint[ny][nx].x = x;
				m_keyPoint[ny][nx].y = y;
			}
		}
		ENDDELETECLASS(customList);

	}


	m_keyPage = 0;
	m_keyPageMax = 4;
	GetInitGameParam(&m_keyPageMax,"softKeyPageMax");


	int tableMax;
	if (codeByte == 2)
	{
		tableMax = sizeof(m_defaultKeySet) / sizeof(MYSOFTKEY);
	}
	else
	{
		tableMax = sizeof(m_defaultKeySet1Byte) / sizeof(MYSOFTKEY);
	}


	int customKey = 0;
	GetInitGameParam(&customKey,"customKey");
	//check nya/hoge.xtx
	if (customKey == 0)
	{
		m_softKeyTableNumber = tableMax;

		m_softKeyTable = new MYSOFTKEY[m_softKeyTableNumber];
		for (int i=0;i<m_softKeyTableNumber;i++)
		{
			if (codeByte == 2)
			{
				m_softKeyTable[i] = m_defaultKeySet[i];
			}
			else
			{
				m_softKeyTable[i] = m_defaultKeySet1Byte[i];
			}
		}
	}
	else
	{
		CNameList* customList = new CNameList();
		customList->LoadFile("nya\\softkeycustom.xtx");
		int k = customList->GetNameKosuu() / 4;
		m_softKeyTableNumber = k;
		m_softKeyTable = new MYSOFTKEY[m_softKeyTableNumber];
		for (int i=0;i<m_softKeyTableNumber;i++)
		{
			int page = atoi(customList->GetName(i*4));
			if (page > m_keyPageMax)
			{
				m_keyPageMax = page;
			}

			int nx = atoi(customList->GetName(i*4+1));
			int ny = atoi(customList->GetName(i*4+2));
			nx--;
			ny--;
			LPSTR mes = customList->GetName(i*4+3);
			m_softKeyTable[i].page = page-1;
			m_softKeyTable[i].x = nx;
			m_softKeyTable[i].y = ny;
			int ln = strlen(mes);
			if (ln>14) ln = 14;
			memcpy(m_softKeyTable[i].key,mes,ln);
			m_softKeyTable[i].key[ln] = 0;
			m_softKeyTable[i].key[ln+1] = 0;
		}
		ENDDELETECLASS(customList);
	}

	m_userCommandKeyList = NULL;
	m_userSoftCommandNumber = 0;
//	int customCommand = 0;
	GetInitGameParam(&m_userSoftCommandNumber,"customCommand");
	//check nya/hoge.xtx
	if (m_userSoftCommandNumber != 0)
	{
		CNameList* customList = new CNameList();
		customList->LoadFile("nya\\softkeycommand.xtx");

		int k = customList->GetNameKosuu() / 2;

		m_userSoftCommandNumber = k;
		m_userCommandKeyList = new MYSOFTCOMMANDKEY[m_userSoftCommandNumber];
		for (int i=0;i<m_userSoftCommandNumber;i++)
		{
			LPSTR cmdtext = customList->GetName(i*2);
			int cmd = GetUserCommand(cmdtext);
//			int cmd = atoi(customList->GetName(i*2));
			LPSTR key = customList->GetName(i*2+1);
			m_userCommandKeyList[i].cmd = cmd;
			int ln = strlen(key);
			if (ln>14) ln = 14;
			memcpy(m_userCommandKeyList[i].key,key,ln);
			m_userCommandKeyList[i].key[ln+0] = 0;
			m_userCommandKeyList[i].key[ln+1] = 0;
		}
		ENDDELETECLASS(customList);
	}


	for (int i=0;i<16;i++)
	{
		m_shiftKeyList[i] = -1;
	}
	if (codeByte == 2)
	{
		m_shiftKeyList[2] = 3;
		m_shiftKeyList[3] = 2;
	}
	else
	{
		m_shiftKeyList[0] = 1;
		m_shiftKeyList[1] = 0;
	}

	for (int i=0;i<16;i++)
	{
		char name[256];
		sprintf_s(name,256,"shift%d",i+1);
		int shift = -1;
		if (GetInitGameParam(&shift,name))
		{
			m_shiftKeyList[i] = shift-1;
		}
	}




	m_ime = new CMyIME();
}


CSoftKey::~CSoftKey()
{
	End();
}

void CSoftKey::End(void)
{
	ENDDELETECLASS(m_ime);
	DELETEARRAY(m_userCommandKeyList);
	DELETEARRAY(m_softKeyTable);
	ENDDELETECLASS(m_dialogPic);
	ENDDELETECLASS(m_setupList);
}



void CSoftKey::Init(LPSTR kakuteiText)
{
	m_onNumber = -1;
	m_keyPage = 0;
	ClearKakutei();
	ClearInput();
	ClearHenkan();
	AddKakutei(kakuteiText);

	PageChanged();
}


int CSoftKey::Calcu(CInputStatus* lpInput)
{
	m_onNumber = -1;
	m_onNumber = GetOnNumber(lpInput->GetMouseStatus()->GetZahyo());

	int codeByte = CMyFont::m_codeByte;

	if (m_onNumber != -1)
	{
		if (lpInput->GetMouseStatus()->CheckClick(0))
		{
			LPSTR text = m_softKeyTable[m_onNumber].key;

			int cmd = CheckCommandKey(text);

			if (cmd == SOFTCOMMANDKEY_OK)
			{
				if ((GetHenkanLength() == 0) && (GetInputLength() == 0))
				{
					int kakuteiSize = GetKakuteiLength();
					if (kakuteiSize > 0)
					{
						return kakuteiSize;
					}
				}
			}
			else if (cmd == SOFTCOMMANDKEY_HENKAN)
			{
				if (GetInputLength() > 0)
				{
					ClearHenkan();//—pS
					LPSTR henkan = m_ime->Start(GetInputText());
					ClearInput();
					AddHenkan(henkan);
				}
				else if (GetHenkanLength() > 0)
				{
					LPSTR henkan = m_ime->GetNext();
					ClearHenkan();
					AddHenkan(henkan);
				}
			}
			else if (cmd == SOFTCOMMANDKEY_KAKUTEI)
			{
				if (GetInputLength() > 0)
				{
					CopySoftBuffer(2,0);
					ClearInput();
					ClearHenkan();//—pS
				}
				else
				{
					if (GetHenkanLength() > 0)
					{
						CopySoftBuffer(1,0);
						ClearHenkan();
					}
				}
			}
			else if ((cmd >= SOFTCOMMANDKEY_NEXT) && (cmd < SOFTCOMMANDKEY_NEXT + 99))
			{
				m_keyPage = cmd - SOFTCOMMANDKEY_NEXT;
				PageChanged();

				return -1;
			}
			else if (cmd == SOFTCOMMANDKEY_DELETE)
			{
				int lastTextType = GetLastTextType();
				if (lastTextType == SOFTKET_TEXTTYPE_HENKAN)
				{
					CopySoftBuffer(1,2);
					ClearHenkan();
					lastTextType = GetLastTextType();
				}
				DeleteLastText(lastTextType);
			}
			else if (cmd == SOFTCOMMANDKEY_DAKUTEN)
			{
				int lastTextType = GetLastTextType();
				if ((lastTextType == SOFTKET_TEXTTYPE_KAKUTEI) || (lastTextType == SOFTKET_TEXTTYPE_INPUT))
				{
					int check = CheckDakutenList(m_lastText);
					if (check != -1)
					{
						int k = check ^ 1;
						LPSTR repText = m_dakutenList[k];
						ReplaceLastText(lastTextType,repText);
					}
				}
			}
			else if (cmd == SOFTCOMMANDKEY_HANDAKUTEN)
			{
				int lastTextType = GetLastTextType();
				if ((lastTextType == SOFTKET_TEXTTYPE_KAKUTEI) || (lastTextType == SOFTKET_TEXTTYPE_INPUT))
				{
					int check = CheckHandakutenList(m_lastText);
					if (check != -1)
					{
						int k = check ^ 1;
						LPSTR repText = m_handakutenList[k];
						ReplaceLastText(lastTextType,repText);
					}

				}
			}
			else if (cmd == SOFTCOMMANDKEY_SHIFT)
			{
				int page = m_shiftKeyList[m_keyPage];
				if (page >= 0)
				{
					m_keyPage = m_shiftKeyList[m_keyPage];
				}
				else
				{
					m_keyPage++;
					m_keyPage %= m_keyPageMax;
				}
				PageChanged();
			}
			else if (cmd == -1)
			{
				int lastTextType = GetLastTextType();
				if (lastTextType == SOFTKET_TEXTTYPE_HENKAN)
				{
					CopySoftBuffer(1,0);
					ClearHenkan();
				}
				AddText(SOFTKET_TEXTTYPE_INPUT,text);

				if (codeByte == 1)
				{
					if (GetInputLength() > 0)
					{
						CopySoftBuffer(2,0);
						ClearInput();
						ClearHenkan();//—pS
					}
					else
					{
						if (GetHenkanLength() > 0)
						{
							CopySoftBuffer(1,0);
							ClearHenkan();
						}
					}
				}
			}
		}
	}


	return -1;
}



void CSoftKey::Print(void)
{
	m_dialogPic->Put(m_dialogPrintX,m_dialogPrintY,TRUE);

	

	if (m_useFont)
	{
		for (int i=0;i<m_softKeyTableNumber;i++)
		{
			int page = m_softKeyTable[i].page;
			if (page == m_keyPage)
			{
				int nx = m_softKeyTable[i].x;
				int ny = m_softKeyTable[i].y;
				POINT pt = GetKeyZahyo(nx,ny,page);
				LPSTR mes =  m_softKeyTable[i].key;
				m_message->PrintMessage(pt.x + m_keyPrintDeltaX,pt.y + m_keyPrintDeltaY,mes,m_fontSize,m_fontColorR,m_fontColorG,m_fontColorB);
			}
		}
	}

	if (m_onNumber != -1)
	{
		int page = m_softKeyTable[m_onNumber].page;
		int nx = m_softKeyTable[m_onNumber].x;
		int ny = m_softKeyTable[m_onNumber].y;
		POINT pt = GetKeyZahyo(nx,ny,page);
		SIZE sz = GetKeySize(nx,ny,page);


		LPSTR text = m_softKeyTable[m_onNumber].key;
		int cmd = CheckCommandKey(text);
		BOOL enable = CheckEnableCommandKey(cmd);

		if (enable)
		{
			CAllGeo::TransBoxFill(pt.x,pt.y,sz.cx,sz.cy,m_selectColorR,m_selectColorG,m_selectColorB,m_selectColorA);
		}
	}



}


BOOL CSoftKey::CheckEnableCommandKey(int cmd)
{
	if (cmd == SOFTCOMMANDKEY_OK)
	{
		if ((GetHenkanLength() == 0) && (GetInputLength() == 0))
		{
			int kakuteiSize = GetKakuteiLength();
			if (kakuteiSize > 0)
			{
				return TRUE;
			}
		}
		return FALSE;
	}


	if (cmd == SOFTCOMMANDKEY_HENKAN)
	{
		if (GetInputLength() > 0)
		{
			return TRUE;
		}
		else if (GetHenkanLength() > 0)
		{
			return TRUE;
		}
		return FALSE;
	}

	if (cmd == SOFTCOMMANDKEY_KAKUTEI)
	{
		if (GetInputLength() > 0)
		{
			return TRUE;
		}
		else
		{
			if (GetHenkanLength() > 0)
			{
				return TRUE;
			}
		}
		return FALSE;
	}

	return TRUE;
}

void CSoftKey::PageChanged(void)
{
	if (m_dialogFilename[m_keyPage] != NULL)
	{
		char filename[256];
		sprintf_s(filename,256,"sys\\%s",m_dialogFilename[m_keyPage]);
		m_dialogPic->LoadDWQ(filename);
	}


	//enable etc set
}


int CSoftKey::GetUserCommand(LPSTR text)
{
	int codeByte = CMyFont::m_codeByte;

	for (int i=0;i<256;i++)
	{
		int cmd;
		LPSTR check;
		if (codeByte == 2)
		{
			cmd = m_userCommandCheckList[i].cmd;
			check = m_userCommandCheckList[i].key;
		}
		else
		{
			cmd = m_userCommandCheckList1Byte[i].cmd;
			check = m_userCommandCheckList1Byte[i].key;
		}


		if (cmd == -1) break;
		if (cmd == -2) continue;

		if (strcmp(check,text) == 0) return cmd;
	}

	if (text != NULL)
	{
		char c = *text;
		if ((c>='0') && (c<='9'))
		{
			return atoi(text);
		}
	}

	return -1;
}


void CSoftKey::CopySoftBuffer(int from,int to)
{
	LPSTR fromText = m_text[from];
	if (to == 0)
	{
		AddKakutei(fromText);
	}
	else if (to == 1)
	{
		AddHenkan(fromText);
	}
	else if (to == 2)
	{
		AddInput(fromText);
	}
}


int CSoftKey::GetLastTextType(void)
{
	m_lastText[0] = 0;

	for (int i=2;i>=0;i--)
	{
		if (m_textLength[i] > 0)
		{
			memcpy(m_lastText,&m_text[i][m_textLength[i]*2-2],2);
			m_lastText[2] = 0;
			m_lastText[3] = 0;
			return i;
		}
	}

	return -1;
}

//2byte only
void CSoftKey::ReplaceLastText(int textType,LPSTR repText)
{
	if (m_textLength[textType] <= 0) return;
	m_text[textType][m_textLength[textType]*2-2] = *(repText);
	m_text[textType][m_textLength[textType]*2-2+1] = *(repText+1);
}

void CSoftKey::DeleteLastText(int textType)
{
	if (m_textLength[textType] <= 0) return;
	m_textLength[textType]--;

	int codeByte = CMyFont::m_codeByte;
	if (codeByte == 2)
	{
		m_text[textType][m_textLength[textType]*2] = 0;
		m_text[textType][m_textLength[textType]*2+1] = 0;
	}
	else
	{
		m_text[textType][m_textLength[textType]] = 0;
	}
}


LPSTR CSoftKey::GetKakuteiText(void)
{
	return m_text[SOFTKET_TEXTTYPE_KAKUTEI];
}

LPSTR CSoftKey::GetHenkanText(void)
{
	return m_text[SOFTKET_TEXTTYPE_HENKAN];
}

LPSTR CSoftKey::GetInputText(void)
{
	return m_text[SOFTKET_TEXTTYPE_INPUT];
}

int  CSoftKey::GetKakuteiLength(void)
{
	return m_textLength[SOFTKET_TEXTTYPE_KAKUTEI];
}

int CSoftKey::GetHenkanLength(void)
{
	return m_textLength[SOFTKET_TEXTTYPE_HENKAN];
}

int CSoftKey::GetInputLength(void)
{
	return m_textLength[SOFTKET_TEXTTYPE_INPUT];
}


void CSoftKey::ClearKakutei(void)
{
	m_textLength[SOFTKET_TEXTTYPE_KAKUTEI] = 0;
	m_text[SOFTKET_TEXTTYPE_KAKUTEI][0] = 0;
}

void CSoftKey::ClearInput(void)
{
	m_textLength[SOFTKET_TEXTTYPE_INPUT] = 0;
	m_text[SOFTKET_TEXTTYPE_INPUT][0] = 0;
}

void CSoftKey::ClearHenkan(void)
{
	m_textLength[SOFTKET_TEXTTYPE_HENKAN] = 0;
	m_text[SOFTKET_TEXTTYPE_HENKAN][0] = 0;
}


void CSoftKey::AddKakutei(LPSTR mes)
{
	AddText(SOFTKET_TEXTTYPE_KAKUTEI,mes);
}

void CSoftKey::AddInput(LPSTR mes)
{
	AddText(SOFTKET_TEXTTYPE_INPUT,mes);
}

void CSoftKey::AddHenkan(LPSTR mes)
{
	AddText(SOFTKET_TEXTTYPE_HENKAN,mes);
}

void CSoftKey::AddText(int textType,LPSTR mes)
{
	int codeByte = CMyFont::m_codeByte;

	if (mes == NULL) return;
	if (codeByte == 2)
	{
		if (!CheckKanjiOnly(mes)) return;
	}
	int ln = strlen(mes);


	int cp = ln / codeByte;
	if ((m_textLength[textType]+cp) > m_textLengthMax[textType])
	{
		cp = m_textLengthMax[textType] - m_textLength[textType];
	}
	if (cp<=0) return;

	memcpy(m_text[textType]+m_textLength[textType]*codeByte,mes,cp*codeByte);
	m_textLength[textType] += cp;
	m_text[textType][m_textLength[textType]*codeByte] = 0;
	m_text[textType][m_textLength[textType]*codeByte+1] = 0;
}

BOOL CSoftKey::CheckKanjiOnly(LPSTR mes)
{
	if (mes == NULL) return FALSE;
	int ln = strlen(mes);
	int n = 0;
	
	while (n<ln)
	{
		int c = ((int)*(mes+n)) & 0xff;
		if (c<0x81) return FALSE;
		if ((c>=0xa0) && (c<0xe0)) return FALSE;
		if (c>=0xf0) return FALSE;	
		if ((ln-n) < 2) return FALSE;

		n+=2;
	}

	return TRUE;
}


int CSoftKey::CheckCommandKey(LPSTR mes)
{
	int codeByte = CMyFont::m_codeByte;

	for (int i=0;i<m_userSoftCommandNumber;i++)
	{
		int cmd = m_userCommandKeyList[i].cmd;
		LPSTR key = m_userCommandKeyList[i].key;
		if (strcmp(mes,key) == 0) return cmd;
	}

	for (int i=0;i<256;i++)
	{
		int cmd;
		LPSTR check;

		if (codeByte == 2)
		{
			cmd = m_commandKeyList[i].cmd;
		}
		else
		{
			cmd = m_commandKeyList1Byte[i].cmd;
		}
		if (cmd == -1) return -1;

		if (codeByte == 2)
		{
			check = m_commandKeyList[i].key;
		}
		else
		{
			check = m_commandKeyList1Byte[i].key;
		}

		if (strcmp(mes,check) == 0) return cmd;
	}

	return -1;
}


int CSoftKey::CheckDakutenList(LPSTR mes)
{
	int codeByte = CMyFont::m_codeByte;
	if (codeByte != 2) return -1;

	for (int i=0;i<256;i++)
	{
		LPSTR check = m_dakutenList[i];
		if (*check == 0) return -1;
		if (strcmp(mes,check) == 0) return i;
	}

	return -1;
}

int CSoftKey::CheckHandakutenList(LPSTR mes)
{
	int codeByte = CMyFont::m_codeByte;
	if (codeByte != 2) return -1;

	for (int i=0;i<256;i++)
	{
		LPSTR check = m_handakutenList[i];
		if (*check == 0) return -1;
		if (strcmp(mes,check) == 0) return i;
	}

	return -1;
}

int CSoftKey::GetOnNumber(POINT pt)
{
	for (int i=0;i<m_softKeyTableNumber;i++)
	{
		int page = m_softKeyTable[i].page;
		if (page == m_keyPage)
		{
			//check enable
			if (TRUE)
			{
				int nx = m_softKeyTable[i].x;
				int ny = m_softKeyTable[i].y;

				POINT checkPoint = GetKeyZahyo(nx,ny,page);
				SIZE checkSize = GetKeySize(nx,ny,page);

				if (GetOnArea(pt,checkPoint,checkSize))
				{

					return i;
				}
			}
		}
	}

	return -1;
}

BOOL CSoftKey::GetOnArea(POINT pt,POINT checkPoint,SIZE checkSize)
{
	int dx = pt.x - checkPoint.x;
	int dy = pt.y - checkPoint.y;
	if ((dx<0) || (dy<0)) return FALSE;
	if (dx>=checkSize.cx) return FALSE;
	if (dy>=checkSize.cy) return FALSE;
	return TRUE;
}


POINT CSoftKey::GetKeyZahyo(int nx,int ny,int page)
{
	POINT pt;
	pt.x = 0;
	pt.y = 0;
	if ((nx>=0) && (nx<SOFTKEY_X_MAX) && (ny>=0) && (ny<SOFTKEY_Y_MAX))
	{
		pt = m_keyPoint[ny][nx];
	}

	pt.x += m_dialogPrintX;
	pt.x += m_softKeyPrintX;
	pt.y += m_dialogPrintY;
	pt.y += m_softKeyPrintY;

	return pt;
}

SIZE CSoftKey::GetKeySize(int nx,int ny,int page)
{
	SIZE sz = m_softKeySize;
	if ((nx>=0) && (nx<SOFTKEY_X_MAX) && (ny>=0) && (ny<SOFTKEY_Y_MAX))
	{
		sz = m_keySize[ny][nx];
	}

	return sz;
}



BOOL CSoftKey::GetInitGameParam(int* lpVar, LPSTR name)
{
	if (m_setupList == NULL) return FALSE;

	int rNum = m_setupList->SearchName2(name);
	if (rNum == -1) return FALSE;
	*lpVar = atoi(m_setupList->GetName(rNum + 1));

	return TRUE;
}


BOOL CSoftKey::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	if (m_setupList == NULL) return FALSE;

	int rNum = m_setupList->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_setupList->GetName(rNum + 1);

	return TRUE;
}

void CSoftKey::SetTextLengthMax(int* table)
{
	for (int i=0;i<m_textTypeMax;i++)
	{
		m_textLengthMax[i] = m_textLengthMaxDefault[i];
	}

	if (table != NULL)
	{
		for (int i=0;i<m_textTypeMax;i++)
		{
			int d = table[i];
			if (d>0)
			{
				m_textLengthMax[i] = table[i];
			}
		}
	}
}

/*_*/




