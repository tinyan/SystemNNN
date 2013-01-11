//
// mymessage.h
//
#if !defined __NYANUTILLIB_MYMESSAGE__
#define __NYANUTILLIB_MYMESSAGE__

//class CGame;
class CPicture;
class CMyFont;
class CRubiFont;

class CMyMessage
{
public:
	CMyMessage(CMyFont* lpMyFont, CRubiFont* lpRubiFont = NULL);
	~CMyMessage();
	void End(void);

	void PrintMessage(int x, int y, LPSTR message, int fontSize=16, int colR = -1, int colG = -1, int colB = -1,int sukima = 1, int nextY = -1,int kageColor = -1,BOOL bAntiAliasFlag = TRUE);
	int PrintMessageParts(int start, int length, int x, int y, LPSTR message, int fontSize = 16, int col=-1, int colG = -1, int colB = -1,int sukima = 1, int nextY = -1,int kageColor= -1, BOOL bAntiAliasFlag = TRUE);
	void PrintSelectMessage(int start, int length, int x, int y, LPSTR message, int fontSize = 16, int col=-1, int colG = -1, int colB = -1,int sukima = 1, int nextY = -1,int kageColor= -1, BOOL bAntiAliasFlag = TRUE);
	void GradPrintMessage(int startX,int endX,int x, int y, LPSTR message, int fontSize=16, int colR = -1, int colG = -1, int colB = -1,int sukima = 1, int nextY = -1,int kageColor = -1,BOOL bAntiAliasFlag = TRUE);

	int GetMessageRealLength(LPSTR message);



	static char m_sei[16];
	static char m_mei[16];
	static char m_hana[20];
	static char m_to2byteTable[];
	
	static COLORREF m_colorPtr[];
	static char m_messageWork[];

	static char m_numMessage[10][34];
//	static short m_rubiWork[][32];
//	static int m_rubiColor[][32];
//	static int m_rubiZahyo[][32];

	static char m_userGaiji[31*2];
	typedef struct _tagCOLORNAMETABLE
	{
		int name;
		int col;
	} COLORNAMETABLE;

	static COLORNAMETABLE m_colorNameTable[100];
	static COLORNAMETABLE m_colorNameTable1Byte[100];
	static COLORNAMETABLE m_specialNameTable[100];

	static void SetHanaName(LPSTR hanaName);
	static void SetNumMessage(int n, LPSTR mes);


	static int m_santenCheckFlag;
	static int m_dashCheckFlag;

	void SetUserGaiji(LPSTR gaijiList);
protected:
	int GetRubiFontSize(void);

private:
	int MakeMessage(int start, int length, int x, int y, LPSTR message, int fontSize=16, int colR = -1, int colG = -1, int colB = -1,int sukima = 1, int nextY = -1,int kageColor = -1,BOOL bAntiAliasFlag = TRUE,int startY = -1,int lengthY = 1);
//	CGame* m_game;
	CMyFont* m_myFont;
	CRubiFont* m_rubiFont;

	CPicture* m_pic;
	int GetCommand(short d);
//	int m_rubiKosuu;

	char** m_rubiMessage;
	int* m_rubiParam;
//	int* m_rubiSize;

	int m_gradStartX;
	int m_gradEndX;
	BOOL m_gradFlag;

	static char m_defaultKyochoMessage[];



};
#endif
/*_*/
