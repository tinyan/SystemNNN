//
// mymessage.cpp
//

#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"

#include "..\nnnUtilLib\autoSaveSubData.h"
#include "..\nnnUtilLib\okikaeData.h"

#include "myfont.h"
#include "rubiFont.h"

//#include "game.h"

#include "mymessage.h"

#define MYMESSAGE_MAX 256
//#define RUBI_KOSUU_MAX 100

//#define RUBI_START 'Åk'
//#define RUBI_END 'Ål'


#define RUBI_START ( (('Åm' >> 8) & 0xff) | (('Åm' << 8) & 0x0ff00) )
#define RUBI_END ( (('Ån' >> 8) & 0xff) | (('Ån' << 8) & 0x0ff00) )
#define NUMBER_ZERO ( (('ÇO' >> 8) & 0xff) | (('ÇO' << 8) & 0x0ff00) )
#define KYOCHO_END RUBI_END

#define RUBI_START_1BYTE '['
#define RUBI_END_1BYTE ']'
#define NUMBER_ZERO_1BYTE '0'
#define KYOCHO_END_1BYTE RUBI_END_1BYTE


#define OKIKAE_SEI 0
#define OKIKAE_MEI 1
#define OKIKAE_KAI 2
#define OKIKAE_HANA 3
#define OKIKAE_RUBI_START 4
#define OKIKAE_RUBI_END 5
#define OKIKAE_KYOCHO 6
#define OKIKAE_KYOCHO_END OKIKAE_RUBI_END


#define OKIKAE_SYSTEM_MESSAGE 1000
#define OKIKAE_MESSAGE 2000

//äOéöÇÕ50Ç±Ç‹Ç≈
#define OKIKAE_GAIJI 50
//êFÇÕ100Ç±Ç‹Ç≈
#define OKIKAE_COLOR 100



//
// #ê©	éÂêlåˆÇÃê©
// #ñº	éÂêlåˆÇÃñº
// #â¸	â¸çs
// #êF	ÇªÇÃêFÇ… çïê¬ê‘éáóŒêÖâ©îí
//


char CMyMessage::m_sei[16] = "ÅsÅüê©Åt";
char CMyMessage::m_mei[16] = "ÅsÅüñºÅt";
char CMyMessage::m_hana[20] = "â‘ÇÃñºëO";

//short CMyMessage::m_rubiWork[RUBI_KOSUU_MAX][32];

//char CMyMessage::m_mei[] = "Ç®";

char CMyMessage::m_to2byteTable[]= "\
Å@ÅIÅhÅîÅêÅìÅïÅfÅiÅjÅñÅ{ÅCÅ|ÅDÅ^\
ÇOÇPÇQÇRÇSÇTÇUÇVÇWÇXÅFÅGÅÉÅÅÅÑÅH\
ÅóÇ`ÇaÇbÇcÇdÇeÇfÇgÇhÇiÇjÇkÇlÇmÇn\
ÇoÇpÇqÇrÇsÇtÇuÇvÇwÇxÇyÅmÅèÅnÅOÅQ\
ÅeÇÅÇÇÇÉÇÑÇÖÇÜÇáÇàÇâÇäÇãÇåÇçÇéÇè\
ÇêÇëÇíÇìÇîÇïÇñÇóÇòÇôÇöÅoÅbÅpÅ`Å°\
Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°\
Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°Å°\
ÉAÅBÅuÅvÅAÅEÉíÉ@ÉBÉDÉFÉHÉÉÉÖÉáÉb\
Å[ÉAÉCÉEÉGÉIÉJÉLÉNÉPÉRÉTÉVÉXÉZÉ\\
É^É`ÉcÉeÉgÉiÉjÉkÉlÉmÉnÉqÉtÉwÉzÉ}\
É~ÉÄÉÅÉÇÉÑÉÜÉàÉâÉäÉãÉåÉçÉèÉìÅJÅK";

char CMyMessage::m_messageWork[(MYMESSAGE_MAX+10)*2+1];
COLORREF CMyMessage::m_colorPtr[MYMESSAGE_MAX+10];


CMyMessage::COLORNAMETABLE CMyMessage::m_specialNameTable[] = 
{
	{'êS',50},
	{'äæ',51},
	{'ì{',52},
	{'ë´',53},
	{'îL',54},
	{'ëß',55},
	{'ÂK',56},
	{'èI',255},
};

CMyMessage::COLORNAMETABLE CMyMessage::m_specialNameTable1Byte[] = 
{
	{'h',50},//heart
	{'s',51},//sweat
	{'a',52},//anger
	{'f',53},//foot
	{'c',54},//cat
	{'b',55},//breath
	{'r',56},//rose
	{'e',255},
};

char CMyMessage::m_userGaiji[]= "èI";
char CMyMessage::m_userGaiji1Byte[]= "e";


CMyMessage::COLORNAMETABLE CMyMessage::m_colorNameTable1Byte[100]=
{
	{'B',0x000000},
	{'U',0xff0000},
	{'R',0x0000ff},
	{'P',0xff00ff},
	{'G',0x00ff00},
	{'C',0xffff00},
	{'Y',0x00ffff},
	{'W',0xffffff},

	{'O',0x0080ff},

	{'e',0x000000},
};

CMyMessage::COLORNAMETABLE CMyMessage::m_colorNameTable[100]=
{
	{'çï',0x000000},
	{'ê¬',0xff0000},
	{'ê‘',0x0000ff},
	{'éá',0xff00ff},
	{'óŒ',0x00ff00},
	{'êÖ',0xffff00},
	{'â©',0x00ffff},
	{'îí',0xffffff},

	{'ûÚ',0x0080ff},

	{'ç˜',0xc4d2fc},//252 210 196
	{'ìç',0x938af6},//246 138 147
	{'ä`',0x4760da},//218 96 71
	{'éÈ',0x648aff},//255 138 100
	{'åœ',0x3968a7},//167 104 57
	{'äD',0x6f7d90},//144 125 111
	{'ÈÚ',0x556876},//118 104 85
	{'ë€',0x4c8e9a},//154 142 76
	{'ïc',0x67bd9c},//156 189 103
	{'í|',0x74a27d},//125 162 116
	{'ï…',0x727b4b},//75 123 114
	{'ìS',0x44483b},//59 72 68
	{'óï',0x5a5535},//53 85 90
	{'ãÛ',0xb99e5f},//95 158 185
	{'çÆ',0x483025},//37 48 72
	{'ì°',0xac8399},//153 131 172
	{'î~',0x68539f},//159 83 104
	{'çg',0x533abc},//188 58 83
	{'‰ï',0x4f00c5},//197 0 79
	{'à«',0x6797e2},//226 151 103
	{'àπ',0x3d719e},//158 113 61
	{'åÕ',0x96c3ea},//234 195 150
	{'åI',0x0b1544},//68 21 11
	{'ã‡',0x0081a8},//168 129 0
	{'ót',0xa4cfbc},//188 207 164
	{'âî',0xf9fbf9},//249 251 249
	{'îß',0xacc6f2},//242 198 172
	{'èI',0x000000},
};

//int CMyMessage::m_okikaeMessageMax = 0;

char CMyMessage::m_numMessage[10][OKIKAE_MESSAGE_LENGTH+2]=
{
	"íuÇ´ä∑Ç¶ÇO",
	"íuÇ´ä∑Ç¶ÇP",
	"íuÇ´ä∑Ç¶ÇQ",
	"íuÇ´ä∑Ç¶ÇR",
	"íuÇ´ä∑Ç¶ÇS",
	"íuÇ´ä∑Ç¶ÇT",
	"íuÇ´ä∑Ç¶ÇU",
	"íuÇ´ä∑Ç¶ÇV",
	"íuÇ´ä∑Ç¶ÇW",
	"íuÇ´ä∑Ç¶ÇX",
};


COkikaeData* CMyMessage::m_okikaeData = NULL;

//char* CMyMessage::m_okikaeMessage = NULL;

char CMyMessage::m_defaultKyochoMessage[] = "ÅE";


int CMyMessage::m_santenCheckFlag = 1; 
int CMyMessage::m_dashCheckFlag = 1;

#define RUBI_KOSUU_MAX 256


//CMyMessage::CMyMessage(CGame* lpGame)
CMyMessage::CMyMessage(CMyFont* lpMyFont, CRubiFont* lpRubiFont)
{
//	m_game = lpGame;
//	m_myFont = m_game->GetMyFont();
	m_myFont = lpMyFont;
	m_rubiFont = lpRubiFont;

	m_pic = m_myFont->GetPic();

	m_gradFlag = FALSE;
	m_gradStartX = 0;
	m_gradEndX = 0;

	m_effectType = 0;
	m_effectCount1000 = 0;

	m_rubiParam = new int[RUBI_KOSUU_MAX*4];
	m_rubiMessage = new char*[RUBI_KOSUU_MAX];
}

CMyMessage::~CMyMessage()
{
	End();
}

void CMyMessage::End(void)
{
	DELETEARRAY(m_rubiMessage);
	DELETEARRAY(m_rubiParam);
}

//startÇ‡Ç∂ÇﬂÇ©ÇÁlengthÇ‡Ç∂ï\é¶ÅBñﬂÇËílÇÕÇøÇÂÇ§Ç«Ç©Ç¢ÇΩÇÁ0ÅAÇ©ÇØÇ»Ç©Ç¡ÇΩÇÁÉ}ÉCÉiÉXÅAÇ†Ç‹Ç¡ÇΩÇÁÉvÉâÉX
int CMyMessage::PrintMessageParts(int start, int length, int x, int y, LPSTR message, int fontSize, int colR, int colG , int colB,int sukima, int nextY,int kageColor, BOOL bAntiAliasFlag, bool rubiColorIsMessageColor,bool bRubiNotPrintFlag,bool bColorNorChangeFlag)
{
	m_myFont->BeginPrint(fontSize,bAntiAliasFlag);
	int rt = MakeMessage(start,start+length,x, y, message, fontSize, colR, colG, colB, sukima, nextY, kageColor, bAntiAliasFlag, -1,1,rubiColorIsMessageColor, bRubiNotPrintFlag, bColorNorChangeFlag);

	m_myFont->EndPrint();

	return rt;
}

//ÉGÉtÉFÉNÉgïtÇ≈çÏê¨
int CMyMessage::PrintEffectMessageParts(int start, int length, int x, int y, LPSTR message, int fontSize, int colR, int colG , int colB,int sukima, int nextY,int kageColor, BOOL bAntiAliasFlag,int effectType,int effectCount1000, bool rubiColorIsMessageColor)
{
	m_effectType = effectType;
	m_effectCount1000 = effectCount1000;
	m_myFont->BeginPrint(fontSize,bAntiAliasFlag);
	int rt = MakeMessage(start,start+length,x, y, message, fontSize, colR, colG, colB, sukima, nextY, kageColor, bAntiAliasFlag,-1,1, rubiColorIsMessageColor);

	m_myFont->EndPrint();
	m_effectType = 0;
	return rt;
}

void CMyMessage::PrintSelectMessage(int startY, int lengthY, int x, int y, LPSTR message, int fontSize, int colR, int colG , int colB,int sukima, int nextY,int kageColor, BOOL bAntiAliasFlag, bool rubiColorIsMessageColor)
{
	m_myFont->BeginPrint(fontSize,bAntiAliasFlag);

	int rt = MakeMessage(0,1000,x, y, message, fontSize, colR, colG, colB, sukima, nextY, kageColor, bAntiAliasFlag,startY,lengthY, rubiColorIsMessageColor);
	m_myFont->EndPrint();
}

int CMyMessage::GetMessageRealLength(LPSTR message)
{
	int realLen = 0;
	int ln = (int)strlen(message);
	int k = 0;

	int codeByte = CMyFont::m_codeByte;

	int rubiFlag = 0;
	int kyochoFlag = 0;

	int okikaeMessageMax = 0;
	int okikaeSystemMessageMax = 0;
	if (m_okikaeData != NULL)
	{
		okikaeMessageMax = m_okikaeData->GetOkikaeMax();
		okikaeSystemMessageMax = m_okikaeData->GetSystemOkikaeMax();
	}

	while (k<=ln)
	{
		char ch = *(message+k);
		if (ch == '#')
		{
			k++;
			int cmd;

			if (codeByte == 2)
			{
				short* ptr = (short*)(message+k);
				k+=2;

				short dt = *ptr;
				cmd = GetCommand(dt);
			}
			else
			{
				short dt = (short)(*(message+k));
				k+=1;
				dt &= 0xff;
				dt <<= 8;
				cmd = GetCommand(dt);
			}

			if (cmd == OKIKAE_SEI)
			{
				if (codeByte != 1)
				{
					realLen += (int)strlen(m_sei) / 2;
				}
				else
				{
					realLen += (int)strlen(m_sei);
				}
				continue;
			}

			if (cmd == OKIKAE_MEI)
			{
				if (codeByte != 1)
				{
					realLen += (int)strlen(m_mei) / 2;
				}
				else
				{
					realLen += (int)strlen(m_mei);
				}
				continue;
			}

			if (cmd == OKIKAE_RUBI_START)
			{
				rubiFlag = 1;
				continue;
			}

//			if ((cmd == OKIKAE_RUBI_END) || (cmd == OKIKAE_KYOCHO_END))
			if (cmd == OKIKAE_RUBI_END)//OKIKAE_RUBI_END == OKIKAE_KYOCHO_END
			{
				rubiFlag = 0;
				kyochoFlag = 0;
				continue;
			}

			if (cmd == OKIKAE_KYOCHO)
			{
				kyochoFlag = 1;
				continue;
			}

			if ((cmd >= OKIKAE_GAIJI) && (cmd < (OKIKAE_GAIJI+50)))
			{
				realLen++;
				continue;
			}

			if ((cmd >= OKIKAE_COLOR) && (cmd < (OKIKAE_COLOR + 100)))	//color
			{
				continue;
			}

			if ((cmd >= OKIKAE_MESSAGE) && (cmd < OKIKAE_MESSAGE + okikaeMessageMax))
			{
				k -= codeByte;
				int newSkip = GetNewSkip(message+k);
				int okikae = GetOkikae(message+k);
				if (okikae < okikaeMessageMax)
				{
//						realLen += strlen(m_okikaeMessage + (OKIKAE_MESSAGE_LENGTH + 2) * okikae) / 2;
					realLen += (int)strlen(m_okikaeData->GetOkikaeMessage(okikae)) / codeByte;
				}
				else
				{
					//error
				}
				k += newSkip;

				continue;
			}

			if ((cmd >= OKIKAE_SYSTEM_MESSAGE) && (cmd < OKIKAE_SYSTEM_MESSAGE + okikaeSystemMessageMax))
			{
//					k -= 2;
				int newSkip = GetNewSkip(message+k);
				int okikae = GetOkikae(message+k);//ã§í Ç≈Ç¢ÇØÇÈ
				if (okikae < okikaeSystemMessageMax)
				{
//						realLen += strlen(m_okikaeMessage + (OKIKAE_MESSAGE_LENGTH + 2) * okikae) / 2;
					realLen += (int)strlen(m_okikaeData->GetSystemOkikaeMessage(okikae)) / codeByte;
				}
				else
				{
					//error
				}
				k += newSkip;

				continue;
			}

			if (cmd != 2)
			{
				continue;	//unknown
			}
		}


		if (ch == 0x0a)
		{
			break;
		}

		if (ch == 0)
		{
			break;
		}

		int cc = ch & 0xff;

		if (((cc >=0x20) && (cc<=0x7f)) || ((cc>=0xa0) && (cc<=0xdf)))
		{
			if ((rubiFlag == 0) && (kyochoFlag == 0))
			{
				realLen++;
			}
			k++;
			continue;
		}

		if (cc<0x20)
		{
			k++;
			continue;
		}

		if ((rubiFlag == 0) && (kyochoFlag == 0))
		{
			realLen++;
		}


		if (codeByte != 1)
		{
			k+=2;
		}
		else
		{
			k+=1;
		}
	}


	return realLen;

}

int CMyMessage::GetNewSkip(char* mes)
{
	short* ptr = (short*)mes;
	char* ptr1Byte = (char*)mes;


	int skip = 0;
	int codeByte = CMyFont::m_codeByte;

	while(skip < 2*codeByte)
	{
		if (codeByte == 2)
		{
			short d = *ptr;
			int d0 = ((d>>8)& 0xff) | ((d<<8) & 0xff00);
			d0 -= 'ÇO';
			if ((d0 >= 0) && (d0 <= 9))
			{
				ptr += 1;
				skip++;
			}
			else
			{
				break;
			}
		}
		else
		{
			char d1 = *ptr1Byte;
			d1 -= '0';
			if ((d1 >= 0) && (d1 <= 9))
			{
				ptr1Byte += 1;
				skip++;
			}
			else
			{
				break;
			}
		}

	}

	return skip * codeByte;
}

int CMyMessage::GetOkikae(char* mes)
{
	short* ptr = (short*)mes;
	char* ptr1Byte = (char*)mes;
	int codeByte = CMyFont::m_codeByte;

	int rt = 0;
	int skip = 0;

	while(skip < 2*codeByte)
	{
		if (codeByte == 2)
		{
			short d = *ptr;
			int d0 = ((d>>8)& 0xff) | ((d<<8) & 0xff00);
			d0 -= 'ÇO';
			if ((d0 >= 0) && (d0 <= 9))
			{
				ptr += 1;
				skip++;
				rt *= 10;
				rt += d0;
			}
			else
			{
				break;
			}
		}
		else
		{
			char d1 = *ptr1Byte;
			d1 -= '0';
			if ((d1 >= 0) && (d1 <= 9))
			{
				ptr1Byte += 1;
				skip++;
				rt *= 10;
				rt += d1;
			}
			else
			{
				break;
			}
		}
	}

	return rt;
}



//1çsÇÃÇ›ëŒâûÇ…èCê≥
int CMyMessage::MakeMessage(int start, int end, int x, int y, LPSTR message,int fontSize,int colR, int colG, int colB,int sukima, int nextY,int kageColor,BOOL bAntiAliasFlag,int startY,int lengthY,bool rubiColorIsMessageColor, bool bRubiNotPrintFlag, bool bColorNorChangeFlag)
{
	int codeByte = CMyFont::m_codeByte;

	if (m_rubiFont != NULL)
	{
		m_rubiFont->Reset();
	}

	int rubiFlag = CMyFont::m_rubiUseFlag;

	int rubiFontSize = GetRubiFontSize();

//	m_rubiKosuu = 0;

	if (colR == -1) colR = 255;
	if (colG == -1) colG = colR;
	if (colB == -1) colB = colG;

	int colR0 = colR;
	int colG0 = colG;
	int colB0 = colB;

	int santen = 'Åc';
	int dash = 'Å\';

	santen = ((santen >> 8) & 0xff) | ((santen<<8) & 0xff00);
	dash = ((dash >> 8) & 0xff) | ((dash<<8) & 0xff00);

	int dataSize = 0;
	int printEnd = 0;

	if (startY == -1)
	{
		startY = 0;
		lengthY = fontSize;
	}


	if (nextY == -1)
	{
		nextY = fontSize + 4;
	}


	COLORREF col = COLORREF(colR | (colG << 8) | (colB<<16));

	if (message == nullptr)
	{
		return 0;
	}
	int ln = (int)strlen(message);
	int k = 0;
	
	int nowLen = 0;
	BOOL bNewCol = FALSE;

	int top = 0;

	char orgMessage[MYMESSAGE_MAX];


	int okikaeMessageMax = 0;
	int okikaeSystemMessageMax = 0;
	if (m_okikaeData != NULL)
	{
		okikaeMessageMax = m_okikaeData->GetOkikaeMax();
		okikaeSystemMessageMax = m_okikaeData->GetSystemOkikaeMax();
	}

	int rubiKosuu = 0;

	while (k<=ln)
	{
		//create data

		char ch = *(message+k);
		int cmd = -1;

		if (ch == '#')
		{
			k++;
			if (codeByte == 2)
			{
				short* ptr = (short*)(message+k);
				k+=2;

				short dt = *ptr;
				cmd = GetCommand(dt);


				if ((cmd >= OKIKAE_MESSAGE) && (cmd < OKIKAE_MESSAGE + okikaeMessageMax))
				{
					k -= 2;
					int newSkip = GetNewSkip(message+k);
					cmd = GetOkikae(message+k) + OKIKAE_MESSAGE;

					k += newSkip;
				}
				else if ((cmd >= OKIKAE_SYSTEM_MESSAGE) && (cmd < OKIKAE_SYSTEM_MESSAGE + okikaeSystemMessageMax))
				{
					int newSkip = GetNewSkip(message+k);
					cmd = GetOkikae(message+k) + OKIKAE_SYSTEM_MESSAGE;
					k += newSkip;
				}




			}
			else
			{
				char* ptr1byte = (char*)(message+k);
				k+=1;

				short dt1 = (short)(*ptr1byte) << 8;
				cmd = GetCommand(dt1);


				if ((cmd >= OKIKAE_MESSAGE) && (cmd < OKIKAE_MESSAGE + okikaeMessageMax))
				{
					k -= 1;
					int newSkip = GetNewSkip(message+k);
					cmd = GetOkikae(message+k) + OKIKAE_MESSAGE;

					k += newSkip;
				}
				else if ((cmd >= OKIKAE_SYSTEM_MESSAGE) && (cmd < OKIKAE_SYSTEM_MESSAGE + okikaeSystemMessageMax))
				{
					int newSkip = GetNewSkip(message+k);
					cmd = GetOkikae(message+k) + OKIKAE_SYSTEM_MESSAGE;
					k += newSkip;
				}


				/*
				short dt = (short)(*(message+k));
				k+=1;
				dt &= 0xff;
				dt <<= 8;

				cmd = GetCommand(dt);
				//íuÇ´ä∑Ç¶ï∂éöóÒÇÃèÍçáÇ≥ÇÁÇ…ÉXÉLÉbÉvñ¢é¿ëï
				*/
			}

			if (cmd == OKIKAE_SEI)
			{
				if (codeByte != 1)
				{
					int ln1 = (int)strlen(m_sei) / 2;
					if ((nowLen + ln1) <= MYMESSAGE_MAX)
					{
						memcpy(m_messageWork + 2 * (SSIZE_T)nowLen,m_sei,(SSIZE_T)ln1*2);
						if (bNewCol)
						{
							for (int i=0;i<ln1;i++)
							{
								m_colorPtr[nowLen+i] = col;
							}
						}
						nowLen += ln1;
					}
					continue;
				}
				else
				{
					int ln1 = (int)strlen(m_sei);
					if ((nowLen + ln1) <= MYMESSAGE_MAX)
					{
						for (int b1 = 0;b1<ln1;b1++)
						{
							*(m_messageWork + 2 * ((SSIZE_T)nowLen + b1))     = *(m_sei+b1);
							*(m_messageWork + 2 * ((SSIZE_T)nowLen + b1) + 1) = *(m_sei+b1);
						}
						//memcpy(m_messageWork + 1 * nowLen,m_sei,ln1);//@@@@

						if (bNewCol)
						{
							for (int i=0;i<ln1;i++)
							{
								m_colorPtr[nowLen+i] = col;
							}
						}
						nowLen += ln1;
					}
					continue;

				}
			}

			if (cmd == OKIKAE_MEI)
			{
				if (codeByte != 1)
				{
					int ln2 = (int)strlen(m_mei) / 2;
					if ((nowLen + ln2) <= MYMESSAGE_MAX)
					{
						memcpy(m_messageWork + 2 * (SSIZE_T)nowLen,m_mei,(SSIZE_T)ln2*2);
						if (bNewCol)
						{
							for (int i=0;i<ln2;i++)
							{
								m_colorPtr[nowLen+i] = col;
							}
						}
						nowLen += ln2;
					}
					continue;
				}
				else
				{
					int ln2 = (int)strlen(m_mei);
					if ((nowLen + ln2) <= MYMESSAGE_MAX)
					{
						for (int b1 = 0;b1<ln2;b1++)
						{
							*(m_messageWork + 2 * ((SSIZE_T)nowLen + b1))     = *(m_mei+b1);
							*(m_messageWork + 2 * ((SSIZE_T)nowLen + b1) + 1) = *(m_mei+b1);
						}
//						memcpy(m_messageWork + 1 * nowLen,m_mei,ln2);//@@@@
						if (bNewCol)
						{
							for (int i=0;i<ln2;i++)
							{
								m_colorPtr[nowLen+i] = col;
							}
						}
						nowLen += ln2;
					}
					continue;

				}
			}

			if (cmd == OKIKAE_HANA)
			{
				int ln3 = (int)strlen(m_hana) / 2;
				if ((nowLen + ln3) <= MYMESSAGE_MAX)
				{
					memcpy(m_messageWork + 2 * (SSIZE_T)nowLen,m_hana,(SSIZE_T)ln3*2);
					if (bNewCol)
					{
						for (int i=0;i<ln3;i++)
						{
							m_colorPtr[nowLen+i] = col;
						}
					}
					nowLen += ln3;
				}
				continue;
			}

			//rubi start
			if (cmd == OKIKAE_RUBI_START)
			{


//				int skp = m_font->AddRubi(x,y,message+k,COLORREF(colR | (colG << 8) | (colB<<16)));


				short* rubiPtr = (short*)(message+k);
				char* rubiPtr1Byte = (char*)(message+k);

				char kklc = *(message+k);

				short kanjilen = 0;

				if ((kklc >= '1') && (kklc <= '9'))
				{
					rubiPtr = (short*)(message+k+1);
					rubiPtr1Byte = (char*)(message+k+1);
					k++;
					kanjilen = ((short)(kklc)) - '0';


				}
				else
				{
					short kkl = *rubiPtr;
					k += 2;
					rubiPtr++;

					kanjilen = (int)(( ((kkl >> 8) & 0xff) | ((kkl << 8) & 0x0ff00) ));
					kanjilen -= (short)'ÇO';//NUMBER_ZERO;
				}





//				short kkl = *rubiPtr;
//				rubiPtr++;
				LPSTR rubiMes = (LPSTR)rubiPtr;
//				k+=2;


				if ((kanjilen<1) || (kanjilen>9))
				{
					continue;	//error
				}


				//get data
				int ss = 0;

				while (ss<100)	//max100
				{
					short rubichr = *(rubiPtr);
					char rubichr1Byte = *(rubiPtr1Byte);

					BOOL re = FALSE;

					if (codeByte == 2)
					{
						k += 2;
						rubiPtr++;
						if (rubichr == 0x0a0d)
						{
							break; //error
						}
						if (rubichr == RUBI_END)
						{
							re = TRUE;
						}
					}
					else
					{
						k += 1;
						rubiPtr1Byte++;
						if (rubichr1Byte == 0x0d)
						{
							break; //error
						}
						if (rubichr1Byte == RUBI_END_1BYTE)
						{
							re = TRUE;
						}
					}


//					if (rubichr == RUBI_END)
					if (re)
					{
						if (ss == 0)
						{
							break;	//error
						}

						if (rubiFlag)
						{
							if (rubiKosuu < RUBI_KOSUU_MAX)
							{
								m_rubiParam[rubiKosuu*4+0] = (int)kanjilen; //kanji length
								m_rubiParam[rubiKosuu*4+1] = ss;	//rubi length
								m_rubiParam[rubiKosuu*4+2] = nowLen-(int)kanjilen;//kanji start
								m_rubiMessage[rubiKosuu] = rubiMes;

								rubiKosuu++;
							}
						}

//						if (m_rubiFont != NULL)
//						{
//							int rubiX = x + nowLen * 24 + 8 - (kanjilen*24/2);
//							
//							int rubiY = y - 16 + 32;
//
//							rubiX = 32;
//							rubiY = 32;
//
//							m_rubiFont->AddRubi(rubiX,rubiY,rubiMes,COLORREF(colR | (colG << 8) | (colB<<16)),ss*2);
//
//						}
						break;
					}

					ss++;
				}

				continue;
			}

			//rubiEnd
			if (cmd == OKIKAE_RUBI_END)
			{
				continue;	//error
			}


			//kyocho start
			if (cmd == OKIKAE_KYOCHO)
			{
				short* kyochoPtr = (short*)(message+k);
				char* kyochoPtr1Byte = message+k;

				LPSTR kyochoMes = message+k;

				//get data
				int ss = 0;

				while (ss<100)	//max100
				{
					short kyochochr = *(kyochoPtr);
					char kyochochr1Byte = *(kyochoPtr1Byte);

					BOOL kf = FALSE;
					if (codeByte == 2)
					{
						kyochochr = *(kyochoPtr);
						k += 2;
						kyochoPtr++;

						if (kyochochr == 0x0a0d)
						{
							break; //error
						}
						if (kyochochr == KYOCHO_END)
						{
							kf = TRUE;
						}
					}
					else
					{
						kyochochr1Byte = *(kyochoPtr1Byte);
						k += 1;
						kyochoPtr1Byte++;

						if (kyochochr1Byte == 0x0d)
						{
							break; //error
						}
						if (kyochochr1Byte == KYOCHO_END_1BYTE)
						{
							kf = TRUE;
						}
					}

//					if (kyochochr == KYOCHO_END)
					if (kf)
					{
						if (ss == 0)
						{
							break;	//error
						}

						if (rubiKosuu < RUBI_KOSUU_MAX)
						{
							m_rubiParam[rubiKosuu*4+0] = ss; //kanji length
							m_rubiParam[rubiKosuu*4+1] = -1;	//rubi length
							m_rubiParam[rubiKosuu*4+2] = nowLen-(int)ss;//kanji start
							m_rubiMessage[rubiKosuu] = kyochoMes;
							rubiKosuu++;
						}

						break;
					}

					ss++;
				}

				continue;
			}




			if ((cmd >= OKIKAE_MESSAGE) && (cmd<(OKIKAE_MESSAGE+okikaeMessageMax)))
			{
//				int ln3 = strlen(&m_numMessage[cmd-OKIKAE_MESSAGE][0]) / 2;
				if (m_okikaeData != NULL)
				{
					char* okikaeMessage = m_okikaeData->GetOkikaeMessage(cmd-OKIKAE_MESSAGE);
					int ln3 = (int)strlen(okikaeMessage) / codeByte;
					if ((nowLen + ln3) <= MYMESSAGE_MAX)
					{
						if (codeByte == 2)
						{
							memcpy(m_messageWork + 2 * (SSIZE_T)nowLen,okikaeMessage,(SSIZE_T)ln3*2);
						}
						else
						{
							for (int o3=0;o3<ln3;o3++)
							{
								*(m_messageWork + 2 * (SSIZE_T)nowLen + (SSIZE_T)o3*2 + 0) = *(okikaeMessage + o3);
								*(m_messageWork + 2 * (SSIZE_T)nowLen + (SSIZE_T)o3*2 + 1) = *(okikaeMessage + o3);
							}
						}

						if (bNewCol)
						{
							for (int i=0;i<ln3;i++)
							{
								m_colorPtr[nowLen+i] = col;
							}
						}
						nowLen += ln3;
					}

				}
				continue;
			}

			if ((cmd >= OKIKAE_SYSTEM_MESSAGE) && (cmd<(OKIKAE_SYSTEM_MESSAGE+okikaeSystemMessageMax)))
			{
//				int ln3 = strlen(&m_numMessage[cmd-OKIKAE_MESSAGE][0]) / 2;
				if (m_okikaeData != NULL)
				{
					char* okikaeMessage = m_okikaeData->GetSystemOkikaeMessage(cmd-OKIKAE_SYSTEM_MESSAGE);
					int ln3 = (int)strlen(okikaeMessage) / codeByte;
					if ((nowLen + ln3) <= MYMESSAGE_MAX)
					{
						if (codeByte == 2)
						{
							memcpy(m_messageWork + 2 * (SSIZE_T)nowLen,okikaeMessage,(SSIZE_T)ln3*2);
						}
						else
						{
							for (int o3=0;o3<ln3;o3++)
							{
								*(m_messageWork + 2 * (SSIZE_T)nowLen + (SSIZE_T)o3*2 + 0) = *(okikaeMessage + o3);
								*(m_messageWork + 2 * (SSIZE_T)nowLen + (SSIZE_T)o3*2 + 1) = *(okikaeMessage + o3);
							}
						}
						if (bNewCol)
						{
							for (int i=0;i<ln3;i++)
							{
								m_colorPtr[nowLen+i] = col;
							}
						}
						nowLen += ln3;
					}
				}
				continue;
			}

			if ((cmd >= OKIKAE_GAIJI) && (cmd < (OKIKAE_GAIJI+50)))
			{
				m_colorPtr[nowLen] = col;
				m_messageWork[nowLen*2]=(char)0x80;
				m_messageWork[nowLen*2+1] = cmd - OKIKAE_GAIJI + 5;
				nowLen++;
				continue;
			}

			if ((!bColorNorChangeFlag) && (cmd >= OKIKAE_COLOR) && (cmd < (OKIKAE_COLOR + 100)))	//color
			{
				if (bNewCol == FALSE)
				{
					bNewCol = TRUE;
					for (int i=0;i<nowLen;i++)
					{
						m_colorPtr[i] = col;
					}
				}

				if (codeByte == 2)
				{
					col = COLORREF(m_colorNameTable[cmd - OKIKAE_COLOR].col);
				}
				else
				{
					col = COLORREF(m_colorNameTable1Byte[cmd - OKIKAE_COLOR].col);
				}
				colR = col & 0xff;
				colG = (col>>8) & 0xff;
				colB = (col>>16) & 0xff;

//				m_colorPtr[nowLen] = col;
				m_colorPtr[nowLen] = (colR<<16) | (colG<<8) | colB;
				continue;
			}

			if (cmd != 2)
			{
				continue;	//unknown
			}
		}

		if (ch == 0x0a)
		{
			cmd = 2;
			k++;
		}

		if (ch == 0)
		{
			cmd = 2;
			k++;
		}









		if (bRubiNotPrintFlag)
		{
			rubiKosuu = 0;
		}

		if (cmd == 2)
		{
			int orgSize = k-top;
			if (orgSize >= MYMESSAGE_MAX-2)
			{
				orgSize = MYMESSAGE_MAX-2;
			}
			memcpy(orgMessage,message+top,orgSize);
			orgMessage[orgSize]=0;
			orgMessage[orgSize+1]=0;



			if (codeByte == 2)
			{
				m_messageWork[nowLen*2] = 0;
			}
			else
			{
				m_messageWork[nowLen*2] = 0;
			}
			int rt = -1;

//			LPSTR* rubiMessage = NULL;
//			if (!bRubiNotPrintFlag)
//			{
//				rubiMessage = m_rubiMessage;
//			}

			if (bNewCol)
			{
//				rt = m_myFont->MakePic(message+top,m_messageWork,colR,colG,colB,sukima,kageColor,m_colorPtr);
				rt = m_myFont->MakePic(orgMessage,m_messageWork,colR0,colG0,colB0,sukima,kageColor,m_colorPtr,rubiKosuu,nowLen,m_rubiParam,m_rubiMessage, rubiColorIsMessageColor);
			}
			else
			{
//				rt = m_myFont->MakePic(message+top,m_messageWork,colR,colG,colB,sukima,kageColor);
				rt = m_myFont->MakePic(orgMessage,m_messageWork,colR0,colG0,colB0,sukima,kageColor,NULL,rubiKosuu,nowLen,m_rubiParam,m_rubiMessage, rubiColorIsMessageColor);
			}

			if (rt>0)
			{
				int sizeX = rt & 0xffff;
				int sizeY = (rt>>16) & 0xffff;

				int len;
				if (codeByte == 2)
				{
					len = sizeX / (fontSize + sukima);
				}
				else
				{
					len = sizeX / (fontSize/2 + sukima);
				}

				dataSize = len;

				int sx = start;
				int ex = end;

				if (ex>=len) ex = len;
				
				if (sx <= len)
				{
//					printEed = ex;


					int deltaX;
					if (codeByte == 2)
					{
						deltaX = sx * (fontSize + sukima);
					}
					else
					{
						deltaX = sx * (fontSize/2 + sukima);
					}

					int deltaY = startY;
					int putSizeX;
					if (codeByte == 2)
					{
						putSizeX = (fontSize + sukima) * (ex-sx);
					}
					else
					{
						putSizeX = (fontSize/2 + sukima) * (ex-sx);
					}

					int putSizeY = lengthY;


					if (m_gradFlag == FALSE)
					{
						if ((m_effectType > 0) && (ex < len))
						{
							if (ex < len)
							{
								m_myFont->EffectPrint(x,y,deltaX,deltaY,putSizeX,putSizeY,fontSize,m_effectType,m_effectCount1000);
							}
							else
							{
								m_myFont->Print(x,y,deltaX,deltaY,putSizeX,putSizeY);
							}
						}
						else
						{
							if (sx < len)
							{
								m_myFont->Print(x,y,deltaX,deltaY,putSizeX,putSizeY);
							}
						}
					}
					else
					{
						m_myFont->GradPrint(m_gradStartX,m_gradEndX,x,y,deltaX,deltaY,putSizeX,putSizeY);
					}


					if ((rubiFlag) && (sx < len))
					{
						if (rubiKosuu > 0)
						{
							if (lengthY >= fontSize)//all print!
							{
								int rubiPutSizeY = m_myFont->GetRubiFontSize();

								int rubiPutY = y;	//dummy

								if (m_gradFlag == FALSE)
								{
									m_myFont->PrintRubi(x,rubiPutY,deltaX,deltaY,putSizeX,rubiPutSizeY);
								}
								else
								{
									m_myFont->GradPrintRubi(m_gradStartX,m_gradEndX,x,rubiPutY,deltaX,deltaY,putSizeX,rubiPutSizeY);
								}

							//rubi print delta y,fontsize-rubi

							//m_myFont->PrintRubi(x,y,deltaX,deltaY,putSizeX,putSizeY);
							}
						}
					}

					//rubi
					/*
					int srcX = sx * (fontSize + sukima);
					int srcY = startY;
					int putX = x + srcX;
					int putY = y + startY;
					int picSizeX = (fontSize + sukima) * (ex-sx);
					int picSizeY = lengthY;

					m_pic->Blt(putX,putY,srcX,srcY,picSizeX,picSizeY,TRUE);
					CAreaControl::AddArea(putX,putY,picSizeX,picSizeY);
					*/

				}
			}

			y += nextY;

			bNewCol = FALSE;
			nowLen = 0;
			top = k;

			rubiKosuu = 0;//clear!

			continue;
		}

		int cc = ch & 0xff;

		if (((cc >=0x20) && (cc<=0x7f)) || ((cc>=0xa0) && (cc<=0xdf)))
		{
			if (nowLen<MYMESSAGE_MAX)
			{
				if (codeByte == 2)
				{
					memcpy(&m_messageWork[nowLen*2],&m_to2byteTable[(cc-0x20)*2],2);
					m_colorPtr[nowLen] = col;
					nowLen++;
				}
				else
				{
					m_messageWork[nowLen*2] = cc;
					m_messageWork[nowLen*2+1] = cc;
					m_colorPtr[nowLen] = col;
					nowLen++;
				}
			}
			k++;
			continue;
		}

		if (cc<0x20)
		{
			k++;
			continue;
		}

		//check Åc Å\

		if (nowLen<MYMESSAGE_MAX)
		{
			m_colorPtr[nowLen] = col;
			int mj = ((int)(*((short*)(message+k)))) & 0xffff;

			if ((mj == santen) && (m_santenCheckFlag))
			{
				m_messageWork[nowLen*2] = (char)0x80;
				m_messageWork[nowLen*2+1] = 1;
			}
			else if ((mj == dash) && (m_dashCheckFlag))
			{
				int mj0 = 0;
				int mj2 = 0;

				if (k>=2)
				{
					mj0 = ((int)(*((short*)(message+k-2)))) & 0xffff;
				}

				if ((k+2)<MYMESSAGE_MAX)
				{
					mj2 = ((int)(*((short*)(message+k+2)))) & 0xffff;
				}

				m_messageWork[nowLen*2] = (char)0x80;

				if ((mj0 == dash) && (mj2 == dash))
				{
					m_messageWork[nowLen*2+1] = 3;
				}
				else
				{
					if (mj0 != dash)
					{
						m_messageWork[nowLen*2+1] = 2;
					}
					else
					{
						m_messageWork[nowLen*2+1] = 4;
					}
				}
			}
			else
			{
				if (codeByte == 2)
				{
					memcpy(&m_messageWork[nowLen*2],message+k,2);
				}
				else
				{
					memcpy(&m_messageWork[nowLen*2],message+k,1);
					memcpy(&m_messageWork[nowLen*2+1],message+k,1);
				}
			}
			nowLen++;
		}


		if (codeByte == 2)
		{
			k+=2;
		}
		else
		{
			k+=1;
		}

	}


	if (m_rubiFont != NULL)
	{
		if (!bRubiNotPrintFlag)
		{
			HDC hdc = m_myFont->GetHDC();
			//		m_rubiFont->BeginPrint();
			m_rubiFont->PrintRubi(hdc);
			//		m_rubiFont->EndPrint();
					//print rubi
		}
	}




	if (end<dataSize) return dataSize - end;	//Ç†Ç‹Ç¡ÇΩ
	if (end==dataSize) return 0;				//ÇøÇÂÇ§Ç«
	if (end>dataSize) return dataSize - end;	//ÇΩÇËÇ…Ç·Ç¢


	return 0;
}



void CMyMessage::PrintMessage(int x, int y, LPSTR message,int fontSize,int colR, int colG, int colB,int sukima, int nextY,int kageColor,BOOL bAntiAliasFlag, bool rubiColorIsMessageColor)
{
	m_myFont->BeginPrint(fontSize,bAntiAliasFlag);

	MakeMessage(0,1000,x, y, message, fontSize, colR, colG, colB, sukima, nextY, kageColor, bAntiAliasFlag,-1,1, rubiColorIsMessageColor);

	m_myFont->EndPrint();
}

void CMyMessage::GradPrintMessage(int startX,int endX,int x, int y, LPSTR message,int fontSize,int colR, int colG, int colB,int sukima, int nextY,int kageColor,BOOL bAntiAliasFlag, bool rubiColorIsMessageColor)
{
	m_myFont->BeginPrint(fontSize,bAntiAliasFlag);
	m_gradFlag = TRUE;
	m_gradStartX = startX;
	m_gradEndX = endX;
	MakeMessage(0,1000,x, y, message, fontSize, colR, colG, colB, sukima, nextY, kageColor, bAntiAliasFlag,-1,1, rubiColorIsMessageColor);
	m_gradFlag = FALSE;

	m_myFont->EndPrint();
}

int CMyMessage::GetCommand(short d)
{
	int codeByte = CMyFont::m_codeByte;

	int d0 = ((d>>8)& 0xff) | ((d<<8) & 0xff00);
	if (codeByte == 1)
	{
		d0 = (d>>8)& 0xff;
	}

	int sei = 'ê©';
	int mei = 'ñº';
	int kai = 'â¸';
	int hana = 'â‘';
	int rubiStart = 'Åm';
	int rubiEnd = 'Ån';
	int kyoucho = 'ã≠';

	int owari = 'èI';
	int owari1byte = 'e';

	int nums[10] = {'ÇO','ÇP','ÇQ','ÇR','ÇS','ÇT','ÇU','ÇV','ÇW','ÇX'};

	int systemOkikae = 'ÉV';

	sei &= 0xffff;
	mei &= 0xffff;
	kai &= 0xffff;
	hana &= 0xffff;
	owari &= 0xffff;
	owari1byte &= 0xffff;

	int i = 0;
	for (i=0;i<10;i++)
	{
		nums[i] &= 0xffff;
	}


//	if (CMyFont::m_codeByte == 1)
	if (codeByte == 1)
	{
		sei = 'L';
		mei = 'F';
		rubiStart = '[';
		rubiEnd = ']';
		kai = 'N';
		kyoucho = '.';
		systemOkikae = 'S';
	}




	if (d0 == sei) return OKIKAE_SEI;
	if (d0 == mei) return OKIKAE_MEI;
	if (d0 == kai) return OKIKAE_KAI;
	if (d0 == hana) return OKIKAE_HANA;

	if (d0 == rubiStart) return OKIKAE_RUBI_START;
	if (d0 == rubiEnd) return OKIKAE_RUBI_END;

	if (d0 == kyoucho) return OKIKAE_KYOCHO;

	if (codeByte == 2)
	{
		for (i=0;i<10;i++)
		{
			if (d0 == nums[i]) return i+OKIKAE_MESSAGE;
		}
	}
	else
	{
		if ((d0 >= '0') && (d0 <= '9'))
		{
			return d0 - '0' + OKIKAE_MESSAGE;
		}
	}

	if (codeByte == 2)
	{
		if (d0 == systemOkikae) return OKIKAE_SYSTEM_MESSAGE;
	}
	else
	{
		if (d0 == systemOkikae) return OKIKAE_SYSTEM_MESSAGE;
	}

//	int dd = (int)d;
//	dd &= 0xffff;



//	if (CMyFont::m_codeByte == 2)
	if (codeByte == 2)
	{
		for (i=0;i<100;i++)
		{
			int dt = m_colorNameTable[i].name;
			if (dt == owari) break;

			if (d0 == dt) return OKIKAE_COLOR+i;
		}
	}
	else
	{
		for (i=0;i<100;i++)
		{
			int dt = m_colorNameTable1Byte[i].name;
			if (dt == owari1byte) break;

			if (d0 == dt) return OKIKAE_COLOR+i;
		}
	}

	if (codeByte == 2)
	{
		for (i=0;i<20;i++)
		{
			int dt = m_specialNameTable[i].name;
			if (dt == owari) break;

			if (d0 == dt)
			{
				return OKIKAE_GAIJI+i;
			}
		}
	}
	else
	{
		for (i=0;i<20;i++)
		{
			int dt = m_specialNameTable1Byte[i].name;
			if (dt == owari) break;

			if (d0 == dt)
			{
				return OKIKAE_GAIJI+i;
			}
		}
	}


	if (codeByte == 2)
	{
		short owari2 = ((owari>>8)& 0xff) | ((owari<<8) & 0xff00);

		short* sh = (short*)m_userGaiji;
		for (i=0;i<30;i++)
		{
			short dt = *(sh+i);
			if (dt == owari2) break;

			if (d == dt)
			{
				return OKIKAE_GAIJI+20+i;
			}
		}
	}
	else
	{
		char owari2 = 'e';

		char* sh = (char*)m_userGaiji1Byte;
		for (i=0;i<30;i++)
		{
			char dt = *(sh+i);
			if (dt == owari2) break;

			if (d == dt)
			{
				return OKIKAE_GAIJI+20+i;
			}
		}
	}


	return -1;
}


void CMyMessage::SetHanaName(LPSTR hanaName)
{
	int ln = (int)strlen(hanaName);
	if (ln>18) ln = 18;
	memcpy(m_hana,hanaName,ln);
	m_hana[ln] = 0;
	m_hana[ln+1] = 0;
}



void CMyMessage::SetNumMessage(int n, LPSTR mes)
{
	if ((n<0) || (n>=10)) return;
	if (mes == NULL) return;

	int ln = (int)strlen(mes);
	if (ln>32) ln = 32;

	memcpy(&m_numMessage[n][0],mes,ln);
	m_numMessage[n][ln] = 0;
	m_numMessage[n][ln+1] = 0;
}


void CMyMessage::SetUserGaiji(LPSTR gaijiList)
{
	if (gaijiList == NULL) return;
	int ln = lstrlen(gaijiList);
	if (CMyFont::m_codeByte == 2)
	{
		if (ln>60) ln = 60;
		memcpy(m_userGaiji,gaijiList,ln);
		memcpy(m_userGaiji+ln,"èI",2);
	}
	else
	{
		if (ln>30) ln = 30;
		memcpy(m_userGaiji,gaijiList,ln);
		memcpy(m_userGaiji+ln,"e",1);
	}
}


int CMyMessage::GetRubiFontSize(void)
{
	if (CMyFont::m_rubiUseFlag == 0)
	{
		return -1;
	}

	return 12;//dummy@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
}
/*
void CMyMessage::InitStaticData(int param)
{
	int messageMax = 100;
	if (param != -1)
	{
		messageMax = param;
	}

	m_okikaeMessageMax = messageMax;
	m_okikaeMessage = new char[(OKIKAE_MESSAGE_LENGTH+2) * messageMax];

	for (int i=0;i<messageMax;i++)
	{
		int k = i;
		if (k>10) k= 0;
		char* src = m_numMessage[k];
		char* dst = m_okikaeMessage + (OKIKAE_MESSAGE_LENGTH+2) * i;
		memcpy(dst,src,OKIKAE_MESSAGE_LENGTH+2);
	}
}


void CMyMessage::ReleaseStaticData(void)
{
	DELETEARRAY(m_okikaeMessage);
}
*/

char* CMyMessage::GetOkikaeMessage(int n)
{
	if (m_okikaeData != NULL)
	{
		return m_okikaeData->GetOkikaeMessage(n);
	}

	return NULL;//error
}

void CMyMessage::SetOkikaeMessage(int n,char* mes)
{
	if (m_okikaeData != NULL)
	{
		m_okikaeData->SetOkikaeMessage(n,mes);
	}
}



/*_*/

