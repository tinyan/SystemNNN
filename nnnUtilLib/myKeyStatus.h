//
//
//

#if !defined __NNNUTILLIB_MYKEYSTATUS__
#define __NNNUTILLIB_MYKEYSTATUS__

class CMyKeyStatus
{
public:
	CMyKeyStatus();
	virtual ~CMyKeyStatus();
	virtual void End(void);

	BOOL CheckKey(int key,BOOL clickFlag = FALSE);

	void ClearAllKey(void);
	void SetKey(int key,BOOL flg = TRUE);


protected:
	int m_keyStatus[256];
};

#endif

/*_*/

