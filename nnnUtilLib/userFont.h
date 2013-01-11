//
//
//

#if !defined __NNNUTILLIB_USERFONT__
#define __NNNUTILLIB_USERFONT__



class CUserFont
{
public:
	CUserFont(LPSTR fontfilename);
	~CUserFont();
	void End(void);

	int GetUserFontSize(void){return m_userFontSize;}
	int GetUserFontDataSize(void){return m_fontDataSize;}
	char* GetFont1Moji(char* mes);



	int GetUserFontType(void){return m_userFontType;}//not used?

private:
	char* m_userFontData0;
	char* m_userFontData;

	char* m_makedFontWork0;
	char* m_makedFontWork;

	char* m_makedFont0;
	char* m_makedFont;

	int m_userFontSize;
	int m_userFontType;

	int m_fontDataSize;

	void MakeFont2(int cd);
	void MakeFont4(int cd);
	void MakeFont8(int cd);

	char* MakedToData(void);

};






#endif
/*_*/

