//
//
//

#if !defined __NNNUTILLIB_COMMONRADIOBUTTON__
#define __NNNUTILLIB_COMMONRADIOBUTTON__


class CCommonButton;
class CCommonMultiStateButton;

class CCommonRadioButton : public CCommonMultiStateButton
//class CCommonRadioButton
{
public:
	CCommonRadioButton(CNameList* lpSetup,CPicture* lpBG = NULL,LPSTR buttonName = NULL,POINT* lpPoint = NULL,CSuperButtonSetup* lpSuperSetup = NULL);
//	CCommonRadioButton();
	virtual ~CCommonRadioButton();
	virtual void End(void);
protected:

};

#endif
/*_*/

