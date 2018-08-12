//
// SelectPlace.h
//

#if !defined __NNNLIB_COMMONPRINTSTATUS____
#define __NNNLIB_COMMONPRINTSTATUS____

class CCommonGeneral;
class CGameCallBack;
class CNameList;
class CMyMessage;

//class CPrintGameDate;
class CCommonAnimeParts;
class CHaveItemData;


class CCommonCheckButton;

class CCommonPlayStatusData;

class CCommonPrintStatus : public CCommonGeneral
{
public:
	CCommonPrintStatus(CGameCallBack* lpGame,int extMode = 0);
	virtual ~CCommonPrintStatus();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	virtual void CreateStartScreen(void);


protected:
	int m_setNumber;
	CCommonPlayStatusData** m_playStatusData;
	CCommonCheckButton** m_onOffButton;
	int* m_onOffVar;
	POINT* m_printZahyo;
	CCommonUpDownButtonGroup** m_placeUpDown;
	int* m_place;
	CCommonRadioButtonGroup* m_radio;
	int m_useRadioFlag;
	int m_setPlaceSetNumber;
	POINT* m_setPlaceSetData;

	int m_setPlaceSetSelectVar;

	virtual void FinalExitRoutine(void);
	virtual int EndMode(void);
	virtual int PrintDokuristu(int nowMode);

	CMyMessage* m_message;

	int m_effectTime;
	int m_effectCount;

	int GetSetSelectSetNumber(void);
	void SetSetSelectSetNumber(int n);

	void PrintStatusSub(int ps = 100,BOOL mustPrint = FALSE);

	void LoadCheckButtonPic(void);
	void LoadUpdownButtonPic(void);
	void LoadRadioButtonPic(void);

	void InitCheckButton(void);
	void InitUpdownButton(void);
	void InitRadioButton(void);

	void GetPlaceList(void);
	void ChangePlace(int set, int delta);
	void SetPlaceToVar(void);
	void ChangeOnOff(int set);
//	void SetOnOffButton(void);
//	void SetUpdownButton(void);


	int m_checkPrintDeltaX;
	int m_checkPrintDeltaY;
	int m_upPrintDeltaX;
	int m_upPrintDeltaY;
	int m_downPrintDeltaX;
	int m_downPrintDeltaY;

	POINT GetBaseZahyo(int place);

private:

};

#endif
/*_*/

