#if !defined __NNNUTILLIB_PRINTCARDPOWER__
#define __NNNUTILLIB_PRINTCARDPOWER__

class CNameList;
class CPicture;

class CPrintCardPower
{
public:
	CPrintCardPower(CNameList* setup);
	~CPrintCardPower();
	void End(void);

	void Put(POINT cardPoint,int power,int st = 0,int level = 0,int card = 0);
private:
	CNameList* m_setup;

	int m_cardPowerPicByCard;
	int m_cardPowerPicByLevel;
	int m_cardShurui;
	int m_levelMax;

	CPicture* m_pic;

	SIZE m_size;
	POINT m_zahyo;
	POINT m_next;

	int m_seatTable[10];
	int m_printTypeTable[10];

	int m_addColor[3];
	int m_percent;

	static char m_defaultPowerPicFileName[];

	BOOL GetInitGameParam(int* lpVar, LPSTR name,int initData);
	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name,LPSTR initString);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name);


};

#endif
/*_*/

