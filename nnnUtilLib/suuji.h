//
// suuji.h
//

#if !defined __NNNUTILLIB_SUUJI__
#define __NNNUTILLIB_SUUJI__

class CNameList;
class CPicture;
class CSuuji
{
public:
	CSuuji(CPicture* lpPic, int sizeX, int sizeY, int keta, int nextX = -9999, BOOL upZeroFlag = FALSE, BOOL transFlag = TRUE, BOOL leftFlag = FALSE);
	CSuuji(CNameList* lpSetup,LPSTR tagName,BOOL picCreateFlag = FALSE);
	~CSuuji();
	void End(void);

	void Print(int printX, int printY, int dat,int keta = -1,int col = 0);
	void Put(int printX, int printY, int ch,int col = 0);

	int GetSizeX(void){return m_sizeX;}
	int GetNextX(void){return m_nextX;}

protected:
	CPicture* m_pic;
	int m_sizeX;
	int m_sizeY;
	int m_nextX;
	int m_nextY;
	int m_keta;
	BOOL m_transFlag;
	BOOL m_leftFlag;
	BOOL m_upZeroFlag;

	CNameList* m_setup;

	BOOL m_picCreateFlag;

	BOOL GetInitGameParam(int* lpVar, LPSTR name,int initData);
	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name,LPSTR initString);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name);

};



#endif
/*_*/

