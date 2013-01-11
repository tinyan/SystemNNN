#if !defined __NNNUTILLIB_PRINTCARDGAZE__
#define __NNNUTILLIB_PRINTCARDGAZE__


class CNameList;
class CPicture;

class CPrintCardGaze
{
public:
	CPrintCardGaze(CNameList* setup);
	~CPrintCardGaze();
	void End(void);

	void Put(POINT cardPoint,int gaze,int st = 0);

private:

	static char m_defaultCardGazeFileName[];

	CNameList* m_setup;
	CPicture* m_pic;

	int m_typeKosuu;
	int m_tate;
	SIZE* m_size;
	POINT* m_zahyo;



	BOOL GetInitGameParam(int* lpVar, LPSTR name,int initData);
	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name,LPSTR initString);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name);

};

#endif

/*_*/

