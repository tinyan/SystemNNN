//
// mymessage.cpp
//

#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"

#include "myfont.h"
#include "rubiFont.h"

//#include "game.h"

#include "mymessage.h"

#define MYMESSAGE_MAX 256
//#define RUBI_KOSUU_MAX 100

//#define RUBI_START '〔'
//#define RUBI_END '〕'


#define RUBI_START ( (('［' >> 8) & 0xff) | (('［' << 8) & 0x0ff00) )
#define RUBI_END ( (('］' >> 8) & 0xff) | (('］' << 8) & 0x0ff00) )
#define NUMBER_ZERO ( (('０' >> 8) & 0xff) | (('０' << 8) & 0x0ff00) )
#define KYOCHO_END RUBI_END


#define OKIKAE_SEI 0
#define OKIKAE_MEI 1
#define OKIKAE_KAI 2
#define OKIKAE_HANA 3
#define OKIKAE_RUBI_START 4
#define OKIKAE_RUBI_END 5
#define OKIKAE_KYOCHO 6
#define OKIKAE_KYOCHO_END OKIKAE_RUBI_END


//めっせーじは１０こ
#define OKIKAE_MESSAGE 10

//外字は50こまで
#define OKIKAE_GAIJI 50
//色は100こまで
#define OKIKAE_COLOR 100



//
// #姓	主人公の姓
// #名	主人公の名
// #改	改行
// #色	その色に 黒青赤紫緑水黄白
//


char CMyMessage::m_sei[16] = "《◆姓》";
char CMyMessage::m_mei[16] = "《◆名》";
char CMyMessage::m_hana[20] = "花の名前";

//short CMyMessage::m_rubiWork[RUBI_KOSUU_MAX][32];

//char CMyMessage::m_mei[] = "お";

char CMyMessage::m_to2byteTable[]= "\
　！”＃＄％＆’（）＊＋，−．／\
０１２３４５６７８９：；＜＝＞？\
＠ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯ\
ＰＱＲＳＴＵＶＷＸＹＺ［￥］＾＿\
‘ａｂｃｄｅｆｇｈｉｊｋｌｍｎｏ\
ｐｑｒｓｔｕｖｗｘｙｚ｛｜｝〜■\
■■■■■■■■■■■■■■■■\
■■■■■■■■■■■■■■■■\
ア。「」、・ヲァィゥェォャュョッ\
ーアイウエオカキクケコサシスセソ\
タチツテトナニヌネノハヒフヘホマ\
ミムメモヤユヨラリルレロワン゛゜";

char CMyMessage::m_messageWork[(MYMESSAGE_MAX+10)*2+1];
COLORREF CMyMessage::m_colorPtr[MYMESSAGE_MAX+10];


CMyMessage::COLORNAMETABLE CMyMessage::m_specialNameTable[] = 
{
	{'心',50},
	{'汗',51},
	{'怒',52},
	{'足',53},
	{'猫',54},
	{'息',55},
	{'薔',56},
	{'終',255},
};


char CMyMessage::m_userGaiji[]= "終";


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
	{'黒',0x000000},
	{'青',0xff0000},
	{'赤',0x0000ff},
	{'紫',0xff00ff},
	{'緑',0x00ff00},
	{'水',0xffff00},
	{'黄',0x00ffff},
	{'白',0xffffff},

	{'橙',0x0080ff},

	{'桜',0xc4d2fc},//252 210 196
	{'桃',0x938af6},//246 138 147
	{'柿',0x4760da},//218 96 71
	{'朱',0x648aff},//255 138 100
	{'狐',0x3968a7},//167 104 57
	{'灰',0x6f7d90},//144 125 111
	{'鶯',0x556876},//118 104 85
	{'苔',0x4c8e9a},//154 142 76
	{'苗',0x67bd9c},//156 189 103
	{'竹',0x74a27d},//125 162 116
	{'碧',0x727b4b},//75 123 114
	{'鉄',0x44483b},//59 72 68
	{'藍',0x5a5535},//53 85 90
	{'空',0xb99e5f},//95 158 185
	{'紺',0x483025},//37 48 72
	{'藤',0xac8399},//153 131 172
	{'梅',0x68539f},//159 83 104
	{'紅',0x533abc},//188 58 83
	{'苺',0x4f00c5},//197 0 79
	{'杏',0x6797e2},//226 151 103
	{'飴',0x3d719e},//158 113 61
	{'枯',0x96c3ea},//234 195 150
	{'栗',0x0b1544},//68 21 11
	{'金',0x0081a8},//168 129 0
	{'葉',0xa4cfbc},//188 207 164
	{'鉛',0xf9fbf9},//249 251 249
	{'肌',0xacc6f2},//242 198 172
	{'終',0x000000},
};


char CMyMessage::m_numMessage[10][34]=
{
	"置き換え０",
	"置き換え１",
	"置き換え２",
	"置き換え３",
	"置き換え４",
	"置き換え５",
	"置き換え６",
	"置き換え７",
	"置き換え８",
	"置き換え９",
};

char CMyMessage::m_defaultKyochoMessage[] = "・";


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

//startもじめからlengthもじ表示。戻り値はちょうどかいたら0、かけなかったらマイナス、あまったらプラス
int CMyMessage::PrintMessageParts(int start, int length, int x, int y, LPSTR message, int fontSize, int colR, int colG , int colB,int sukima, int nextY,int kageColor, BOOL bAntiAliasFlag)
{
	m_myFont->BeginPrint(fontSize,bAntiAliasFlag);
	int rt = MakeMessage(start,start+length,x, y, message, fontSize, colR, colG, colB, sukima, nextY, kageColor, bAntiAliasFlag);

	m_myFont->EndPrint();

	return rt;
}


void CMyMessage::PrintSelectMessage(int startY, int lengthY, int x, int y, LPSTR message, int fontSize, int colR, int colG , int colB,int sukima, int nextY,int kageColor, BOOL bAntiAliasFlag)
{
	m_myFont->BeginPrint(fontSize,bAntiAliasFlag);

	int rt = MakeMessage(0,1000,x, y, message, fontSize, colR, colG, colB, sukima, nextY, kageColor, bAntiAliasFlag,startY,lengthY);
	m_myFont->EndPrint();
}

int CMyMessage::GetMessageRealLength(LPSTR message)
{
	int realLen = 0;
	int ln = strlen(message);
	int k = 0;

	int codeByte = CMyFont::m_codeByte;

	int rubiFlag = 0;
	int kyochoFlag = 0;

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
					realLen += strlen(m_sei) / 2;
				}
				else
				{
					realLen += strlen(m_sei);
				}
				continue;
			}

			if (cmd == OKIKAE_MEI)
			{
				if (codeByte != 1)
				{
					realLen += strlen(m_mei) / 2;
				}
				else
				{
					realLen += strlen(m_mei);
				}
				continue;
			}

			if (cmd == OKIKAE_RUBI_START)
			{
				rubiFlag = 1;
				continue;
			}

			if ((cmd == OKIKAE_RUBI_END) || (cmd == OKIKAE_KYOCHO_END))
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


//1行のみ対応に修正
int CMyMessage::MakeMessage(int start, int end, int x, int y, LPSTR message,int fontSize,int colR, int colG, int colB,int sukima, int nextY,int kageColor,BOOL bAntiAliasFlag,int startY,int lengthY)
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

	int santen = '…';
	int dash = '―';

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

	int ln = strlen(message);
	int k = 0;
	
	int nowLen = 0;
	BOOL bNewCol = FALSE;

	int top = 0;

	char orgMessage[MYMESSAGE_MAX];


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
					int ln1 = strlen(m_sei) / 2;
					if ((nowLen + ln1) <= MYMESSAGE_MAX)
					{
						memcpy(m_messageWork + 2 * nowLen,m_sei,ln1*2);
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
					int ln1 = strlen(m_sei);
					if ((nowLen + ln1) <= MYMESSAGE_MAX)
					{
						memcpy(m_messageWork + 1 * nowLen,m_sei,ln1);
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
					int ln2 = strlen(m_mei) / 2;
					if ((nowLen + ln2) <= MYMESSAGE_MAX)
					{
						memcpy(m_messageWork + 2 * nowLen,m_mei,ln2*2);
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
					int ln2 = strlen(m_mei);
					if ((nowLen + ln2) <= MYMESSAGE_MAX)
					{
						memcpy(m_messageWork + 1 * nowLen,m_mei,ln2);
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
				int ln3 = strlen(m_hana) / 2;
				if ((nowLen + ln3) <= MYMESSAGE_MAX)
				{
					memcpy(m_messageWork + 2 * nowLen,m_hana,ln3*2);
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
				char kklc = *(message+k);

				short kanjilen = 0;

				if ((kklc >= '1') && (kklc <= '9'))
				{
					rubiPtr = (short*)(message+k+1);
					k++;
					kanjilen = ((short)(kklc)) - '0';


				}
				else
				{
					short kkl = *rubiPtr;
					k += 2;
					rubiPtr++;

					kanjilen = (int)(( ((kkl >> 8) & 0xff) | ((kkl << 8) & 0x0ff00) ));
					kanjilen -= (short)'０';//NUMBER_ZERO;
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
					k += 2;
					rubiPtr++;

					if (rubichr == 0x0a0d)
					{
						break; //error
					}

					if (rubichr == RUBI_END)
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

				LPSTR kyochoMes = message+k;

				//get data
				int ss = 0;

				while (ss<100)	//max100
				{
					short kyochochr = *(kyochoPtr);
					k += 2;
					kyochoPtr++;

					if (kyochochr == 0x0a0d)
					{
						break; //error
					}

					if (kyochochr == KYOCHO_END)
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




			if ((cmd >= OKIKAE_MESSAGE) && (cmd<(OKIKAE_MESSAGE+10)))
			{
				int ln3 = strlen(&m_numMessage[cmd-10][0]) / 2;
				if ((nowLen + ln3) <= MYMESSAGE_MAX)
				{
					memcpy(m_messageWork + 2 * nowLen,&m_numMessage[cmd-10][0],ln3*2);
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

			if ((cmd >= OKIKAE_GAIJI) && (cmd < (OKIKAE_GAIJI+50)))
			{
				m_colorPtr[nowLen] = col;
				m_messageWork[nowLen*2]=(char)0x80;
				m_messageWork[nowLen*2+1] = cmd - OKIKAE_GAIJI + 5;
				nowLen++;
				continue;
			}

			if ((cmd >= OKIKAE_COLOR) && (cmd < (OKIKAE_COLOR + 100)))	//color
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
				m_messageWork[nowLen] = 0;
			}
			int rt = -1;

			if (bNewCol)
			{
//				rt = m_myFont->MakePic(message+top,m_messageWork,colR,colG,colB,sukima,kageColor,m_colorPtr);
				rt = m_myFont->MakePic(orgMessage,m_messageWork,colR0,colG0,colB0,sukima,kageColor,m_colorPtr,rubiKosuu,nowLen,m_rubiParam,m_rubiMessage);
			}
			else
			{
//				rt = m_myFont->MakePic(message+top,m_messageWork,colR,colG,colB,sukima,kageColor);
				rt = m_myFont->MakePic(orgMessage,m_messageWork,colR0,colG0,colB0,sukima,kageColor,NULL,rubiKosuu,nowLen,m_rubiParam,m_rubiMessage);
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
				
				if (sx < len)
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
						m_myFont->Print(x,y,deltaX,deltaY,putSizeX,putSizeY);
					}
					else
					{
						m_myFont->GradPrint(m_gradStartX,m_gradEndX,x,y,deltaX,deltaY,putSizeX,putSizeY);
					}


					if (rubiFlag)
					{
						if (rubiKosuu > 0)
						{
							if (lengthY >= fontSize)//all print!
							{
								int rubiPutSizeY = putSizeY;//dummy
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
					m_messageWork[nowLen] = cc;
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

		//check … ―

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
					memcpy(&m_messageWork[nowLen],message+k,1);
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
		HDC hdc = m_myFont->GetHDC();
//		m_rubiFont->BeginPrint();
		m_rubiFont->PrintRubi(hdc);
//		m_rubiFont->EndPrint();
		//print rubi
	}




	if (end<dataSize) return dataSize - end;	//あまった
	if (end==dataSize) return 0;				//ちょうど
	if (end>dataSize) return dataSize - end;	//たりにゃい


	return 0;
}



void CMyMessage::PrintMessage(int x, int y, LPSTR message,int fontSize,int colR, int colG, int colB,int sukima, int nextY,int kageColor,BOOL bAntiAliasFlag)
{
	m_myFont->BeginPrint(fontSize,bAntiAliasFlag);

	MakeMessage(0,1000,x, y, message, fontSize, colR, colG, colB, sukima, nextY, kageColor, bAntiAliasFlag);

	m_myFont->EndPrint();
}

void CMyMessage::GradPrintMessage(int startX,int endX,int x, int y, LPSTR message,int fontSize,int colR, int colG, int colB,int sukima, int nextY,int kageColor,BOOL bAntiAliasFlag)
{
	m_myFont->BeginPrint(fontSize,bAntiAliasFlag);
	m_gradFlag = TRUE;
	m_gradStartX = startX;
	m_gradEndX = endX;
	MakeMessage(0,1000,x, y, message, fontSize, colR, colG, colB, sukima, nextY, kageColor, bAntiAliasFlag);
	m_gradFlag = FALSE;

	m_myFont->EndPrint();
}

int CMyMessage::GetCommand(short d)
{
	int d0 = ((d>>8)& 0xff) | ((d<<8) & 0xff00);

	int sei = '姓';
	int mei = '名';
	int kai = '改';
	int hana = '花';
	int rubiStart = '［';
	int rubiEnd = '］';
	int kyoucho = '強';

	int owari = '終';
	int owari1byte = 'e';

	int nums[10] = {'０','１','２','３','４','５','６','７','８','９'};

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

	if (CMyFont::m_codeByte == 1)
	{
		sei = 'L';
		mei = 'F';
	}

	if (d0 == sei) return OKIKAE_SEI;
	if (d0 == mei) return OKIKAE_MEI;
	if (d0 == kai) return OKIKAE_KAI;
	if (d0 == hana) return OKIKAE_HANA;

	if (d0 == rubiStart) return OKIKAE_RUBI_START;
	if (d0 == rubiEnd) return OKIKAE_RUBI_END;

	if (d0 == kyoucho) return OKIKAE_KYOCHO;

	for (i=0;i<10;i++)
	{
		if (d0 == nums[i]) return i+OKIKAE_MESSAGE;
	}

//	int dd = (int)d;
//	dd &= 0xffff;



	if (CMyFont::m_codeByte == 2)
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

	for (i=0;i<20;i++)
	{
		int dt = m_specialNameTable[i].name;
		if (dt == owari) break;

		if (d0 == dt)
		{
			return OKIKAE_GAIJI+i;
		}
	}

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


	return -1;
}


void CMyMessage::SetHanaName(LPSTR hanaName)
{
	int ln = strlen(hanaName);
	if (ln>18) ln = 18;
	memcpy(m_hana,hanaName,ln);
	m_hana[ln] = 0;
	m_hana[ln+1] = 0;
}



void CMyMessage::SetNumMessage(int n, LPSTR mes)
{
	if ((n<0) || (n>=10)) return;
	if (mes == NULL) return;

	int ln = strlen(mes);
	if (ln>32) ln = 32;

	memcpy(&m_numMessage[n][0],mes,ln);
	m_numMessage[n][ln] = 0;
	m_numMessage[n][ln+1] = 0;
}


void CMyMessage::SetUserGaiji(LPSTR gaijiList)
{
	if (gaijiList == NULL) return;
	int ln = lstrlen(gaijiList);
	if (ln>60) ln = 60;
	memcpy(m_userGaiji,gaijiList,ln);
	memcpy(m_userGaiji+ln,"終",2);
}

int CMyMessage::GetRubiFontSize(void)
{
	if (CMyFont::m_rubiUseFlag == 0)
	{
		return -1;
	}

	return 12;//dummy@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
}


/*_*/

