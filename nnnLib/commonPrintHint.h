#pragma once

#if !defined __NNNLIB_COMMONPRINTHINT____
#define __NNNLIB_COMMONPRINTHINT__

class CCommonGeneral;
class CGameCallBack;
class CNameList;
class CMyMessage;


class CCommonPrintHint : public CCommonGeneral
{
public:
	CCommonPrintHint(CGameCallBack* lpGame, int extMode = 0);
	virtual ~CCommonPrintHint();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	virtual void CreateStartScreen(void);


	CMyMessage* m_message;
protected:
	int m_nowHintNumber;
	int m_allHintNumber;

	int m_picNumX;
	int m_picNumY;
	int m_picPrintX;
	int m_picPrintY;
	int m_picNextX;
	int m_picNextY;

	int* m_hintNumber;
	LPSTR** m_hintFilename;
	CPicture** m_picWork;

	LPSTR m_noPicFilename;

	void GetNowPic(void);

	int** m_flagVarNumber;



};

#endif


/*_*/
