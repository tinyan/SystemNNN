#if !defined __TINYAN_NNNUTILLIB_PRINTSPECTRUM__
#define __TINYAN_NNNUTILLIB_PRINTSPECTRUM__


class CNameList;

class CPrintSpectrum
{
public:
	CPrintSpectrum(int printKosuu,CNameList* setup);
	~CPrintSpectrum();
	void End(void);

	void Init(void);
	void Print(int* data);
	void AppearPrint(int* data,int count,int countMax,int type);

private:
	CNameList* m_setup;

	int m_printKosuu;
	int m_printType;
	int m_maxGrav;
	int* m_maxData;
	int* m_maxG;
	int* m_data;
	int* m_maxWait;

	int m_maxWaitTime;

	int m_printX;
	int m_printY;
	int m_nextX;
	int m_sizeX;
	int m_sizeY;
	int m_maxSizeY;

	int m_colorR;
	int m_colorG;
	int m_colorB;
	int m_percent;
	int m_maxColorR;
	int m_maxColorG;
	int m_maxColorB;
	int m_maxPercent;


	BOOL GetInitGameParam(int* lpVar, LPSTR name,int initData);
	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name,LPSTR initString);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name);

};

#endif
/*_*/

