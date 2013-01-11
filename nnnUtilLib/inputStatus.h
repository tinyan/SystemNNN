//
//
//

#if !defined __NNNUTILLIB_INPUTSTATUS__
#define __NNNUTILLIB_INPUTSTATUS__


class CMyKeyStatus;
class CMyMouseStatus;

class CInputStatus
{
public:
	CInputStatus();
	virtual ~CInputStatus();
	void End(void);


	void SetMouseStatus(CMyMouseStatus* lpMouse){m_mouseStatus = lpMouse;}
	CMyMouseStatus* GetMouseStatus(void){return m_mouseStatus;}

	void SetKeyStatus(CMyKeyStatus* lpKey){m_keyStatus = lpKey;}
	CMyKeyStatus* GetKeyStatus(void){return m_keyStatus;}
protected:
	CMyMouseStatus* m_mouseStatus;
	CMyKeyStatus* m_keyStatus;
};



#endif
/*_*/

