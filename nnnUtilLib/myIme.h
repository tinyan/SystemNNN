//
//
//

#if !defined __NNNUTILLIB_MYIME__
#define __NNNUTILLIB_MYIME__

class CNameList;

class CMyIME
{
public:
	CMyIME();
	~CMyIME();
	void End(void);


	LPSTR Start(LPSTR text);
	LPSTR GetNext(void);


private:
	int m_dummy;
	int m_max;
};

#endif
/*_*/