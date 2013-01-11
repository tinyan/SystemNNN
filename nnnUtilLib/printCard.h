#if !defined __NNNUTILLIB_PRINTCARD__
#define __NNNUTILLIB_PRINTCARD__


class CPicture;
class CPrintCard
{
public:
	CPrintCard(LPSTR filenameTag,SIZE size,BOOL useType = TRUE);
	~CPrintCard();
	void End(void);

	void Put(POINT pt,int st,int type = -1);
	static void ChangePrintType(int n,int printType);
	static void ChangeSaetTable(int n,int seatNumber);
	static void ChangeAddColor(int r,int g, int b);
	static void ChangePercent(int ps);

	static int GetPrintType(int n){return m_printType[n];}
	static int GetSeatTable(int n){return m_seatTable[n];}
	static int GetAddColor(int k){return m_addColor[k];}
	static int GetPercent(void){return m_percent;}

private:
	SIZE m_cardSize;
	char* m_filenameTag;
	int m_typeKosuu;
	int m_picType;
	BOOL m_useType;

	static int m_printType[];
	static int m_seatTable[];
	static int m_addColor[];
	static int m_percent;

	CPicture* m_pic;

	BOOL LoadPic(int type);

};

#endif
/*_*/
