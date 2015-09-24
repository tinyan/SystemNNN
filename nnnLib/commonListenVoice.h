//
// SelectPlace.h
//

#if !defined __NNNLIB_COMMONLISTENVOICE____
#define __NNNLIB_COMMONLISTENVOICE__

class CCommonGeneral;
class CGameCallBack;
class CNameList;

//class CPrintGameDate;

class CCommonRadioButtonGroup;

class CCommonListenVoice : public CCommonGeneral
{
public:
	CCommonListenVoice(CGameCallBack* lpGame,int extMode = 0);
	virtual ~CCommonListenVoice();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	virtual void CreateStartScreen(void);
protected:
	virtual void FinalExitRoutine(void);
	virtual int EndMode(void);

	static char m_defaultUnknownVoice[];
	static char m_defaultUnknownVoice1[];
	LPSTR m_unknownVoice;

	CMyMessage* m_message;

	int m_voiceCharaNumber;
	CNameList** m_voiceList;

	int* m_voiceNumber;
	int** m_voiceTypeOrVar;
	int** m_voiceFlag;
	int** m_charaVoiceRange;

	int m_voicePerPage;

	char* m_charaVoiceFilename;
	int m_charaVoiceFileNumber;
	void LoadCharaVoiceFilename(void);
	int SearchFilename(LPSTR filename);

	CCommonRadioButtonGroup* m_radio;
	int m_charaNumber;
	void ReloadButtonPic(void);
	int m_page;
	int m_pageMax;

	int m_listPrintX;
	int m_listPrintY;
	int m_listNextX;
	int m_listNextY;
	int m_listSizeX;
	int m_listSizeY;

	POINT GetListPoint(int n);
	int GetOnNumber(POINT pt);
	int m_onNumber;

private:


};

#endif
/*_*/

