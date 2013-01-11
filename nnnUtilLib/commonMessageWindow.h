//
//
//

#if !defined __TINYAN_NNNUTILLIB_COMMONMESSAGEWINDOW__
#define __TINYAN_NNNUTILLIB_COMMONMESSAGEWINDOW__

class CPicture;
class CBasicSetup;

class CCommonMessageWindow : public CBasicSetup
{
public:
	CCommonMessageWindow();
	virtual ~CCommonMessageWindow();
	virtual void End(void);

	virtual void Print(BOOL flg,BOOL namePrintFlag = FALSE,POINT* lpDeltaPoint = NULL);
	virtual void PrintDirect(BOOL flg,BOOL namePrintFlag = FALSE,POINT* lpPoint = NULL);

	static char m_defaultWindowFileName[];
	static char m_defaultWindowFileName2[];

	void SetWindowNumberByConfig(int n){m_windowNumberConfig = n;}
	void SetWindowNumberByScript(int n){m_windowNumberScript = n;};
	void SetWindowNumberByFontSizeType(int n);
	
	int GetWindowShuruiConfig(void){return m_windowShuruiConfig;}
	int GetWindowShuruiScript(void){return m_windowShuruiScript;}


	BOOL CheckOn(POINT pt, BOOL nameCheckFlag = TRUE);
	BOOL CheckOnSize(POINT pt, BOOL nameCheckFlag = TRUE);

	void SetWindowPercent(int ps){m_windowPercent = ps;}
protected:
	int m_windowPrintX;
	int m_windowPrintY;
	int m_windowSizeX;
	int m_windowSizeY;

	int m_nameWindowPrintX;
	int m_nameWindowPrintY;
	int m_nameWindowSizeX;
	int m_nameWindowSizeY;

	CPicture* m_windowPic;
	CPicture* m_nameWindowPic;

	int m_nameWindowFlag;

	int m_windowNumberConfig;
	int m_windowNumberScript;
	int m_windowNumberFontSizeType;

	int m_loadedWindowNumberConfig;
	int m_loadedWindowNumberScript;
	int m_loadedWindowNumberFontSizeType;

	int m_loadedNameWindowNumberConfig;
	int m_loadedNameWindowNumberScript;
	int m_loadedNameWindowNumberFontSizeType;

	BOOL CheckWindowLoaded(void);
	BOOL CheckNameWindowLoaded(void);

	void LoadWindow(void);
	void LoadNameWindow(void);

	int m_windowShuruiConfig;
	int m_windowShuruiScript;
	int m_windowShuruiFontSizeType;

	LPSTR* m_ppWindowFileName;
	LPSTR* m_ppNameWindowFileName;

	int m_windowPercent;
private:

};







#endif
/*_*/
