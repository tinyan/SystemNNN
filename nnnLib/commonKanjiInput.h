//
// nothing.h
//

#if !defined __NNNLIB_KANJIINPUT__
#define __NNNLIB_KANJIINPUT__

class CCommonGeneral;
class CGameCallBack;
class CNameList;
class CMyMessage;
class CSoftKey;

class CCommonKanjiInput : public CCommonGeneral
{
public:
	CCommonKanjiInput(CGameCallBack* lpGame);
	virtual ~CCommonKanjiInput();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);
	virtual void StartUserCommand(int paraKosuu,int* paraPtr);

	virtual void FinalExitRoutine(void);

protected:
	CMyMessage* m_message;
	CSoftKey* m_softKey;

	int m_targetNumber;
	int m_targetType;

	int m_fontSize;
	int m_printX;
	int m_printY;
	int m_kakuteiFontColorR;
	int m_kakuteiFontColorG;
	int m_kakuteiFontColorB;
	int m_henkanFontColorR;
	int m_henkanFontColorG;
	int m_henkanFontColorB;
	int m_inputFontColorR;
	int m_inputFontColorG;
	int m_inputFontColorB;
	int m_henkanSelectColorR;
	int m_henkanSelectColorG;
	int m_henkanSelectColorB;
	int m_henkanSelectColorA;
	int m_inputSelectColorR;
	int m_inputSelectColorG;
	int m_inputSelectColorB;
	int m_inputSelectColorA;

	int m_debugPrintFlag;
	int m_debugFontSize;
	int m_debugPrintX;
	int m_debugPrintY;
	int m_debugNextY;

	int m_textMax[4][3];

};

#endif
/*_*/

