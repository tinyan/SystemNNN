//
//
//

#if !defined __NNNUTILLIB_COMMONBACKBUTTON__
#define __NNNUTILLIB_COMMONBACKBUTTON__

class CCommonButton;

class CPicture;
class CNameList;

class CCommonBackButton : public CCommonButton
{
public:
	CCommonBackButton(CNameList* lpSetup = NULL,LPSTR buttonName = NULL, CPicture* lpBG = NULL);
	virtual ~CCommonBackButton();
	void End(void);

protected:

};

#endif
/*_*/

