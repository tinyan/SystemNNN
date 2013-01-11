//
//
//

#if !defined __NNNUTILLIB_COMMONCHECKBUTTON__
#define __NNNUTILLIB_COMMONCHECKBUTTON__


class CCommonButton;
class CCommonMultiStateButton;
class CNameList;
class CPicture;

class CSuperButtonSetup;
class CCommonCheckButton : public CCommonMultiStateButton
{
public:
	CCommonCheckButton(CNameList* lpSetup,CPicture* lpBG,LPSTR buttonName = NULL,POINT* lpPoint = NULL,CSuperButtonSetup* lpSuperSetup = NULL);
	virtual ~CCommonCheckButton();
	virtual void End(void);

protected:
//	CCommonButton* m_button[2];


};

#endif
/*_*/

