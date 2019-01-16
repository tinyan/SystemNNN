//
// SelectPlace.h
//

#if !defined __NNNLIB_COMMONPRINTPARTY____
#define __NNNLIB_COMMONPRINTPARTY____

class CCommonGeneral;
class CGameCallBack;
class CNameList;
class CMyMessage;

//class CPrintGameDate;
class CCommonAnimeParts;
class CHaveItemData;

class CCommonCheckButton;
class CCommonPartyStatusData;
class CPrintPlayerStatus;

class CCommonPrintParty : public CCommonGeneral
{
public:
	CCommonPrintParty(CGameCallBack* lpGame, int extMode = 0);
	virtual ~CCommonPrintParty();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	virtual void CreateStartScreen(void);


protected:
	CCommonPartyStatusData* m_partyStatusData;
	int m_partyNumber;
	int m_printNumberMax;
	int m_statusNumber;
	int m_etcNumber;

	int m_oldVersion;



	int m_setNumber;
	CPrintPlayerStatus* m_printPlayerStatus;

	void PrintStatusSub(int ps = 100, BOOL mustPrint = FALSE);

	void GetPlaceList(void);
	void SetDataToPlayerStatus(void);
	void SetPlaceSetPointList(void);
	void SetParamOnOffWork(void);


	CCommonCheckButton** m_onOffButton;
	int* m_onOffVar;
	POINT* m_printZahyo;
	CCommonUpDownButtonGroup** m_placeUpDown;
	int* m_place;
	CCommonRadioButtonGroup* m_radio;
	int m_useRadioFlag;

	CCommonCheckButton** m_etcOnOffButton;
	int* m_etcOnOffVar;
	POINT* m_etcPrintZahyo;
	int* m_etcOnOffWork;
	POINT* m_etcPlaceWork;



	int m_setPlaceSetNumber;
	POINT* m_setPlaceSetData;
	int m_setPlaceSetSelectVar;



	int m_paramNumber;
	int* m_paramOnOffVar;
	int* m_paramOnOffWork;
	int* m_param;

	CCommonCheckButton** m_paramOnOffButton;

	POINT* m_setPlaceSetWork;


//	void PrintStatusSub(int ps, BOOL mustPrint = FALSE);


	int InitOldVersion(void);
	int InitNewVersion(void);
	int CalcuOldVersion(void);
	int CalcuNewVersion(void);
	int PrintOldVersion(void);
	int PrintNewVersion(void);

	virtual void FinalExitRoutine(void);
	virtual int EndMode(void);

	virtual int PrintDokuristu(int nowMode);

	CMyMessage* m_message;

	int m_effectTime;
	int m_effectCount;


	int m_checkPrintDeltaX;
	int m_checkPrintDeltaY;
	int m_upPrintDeltaX;
	int m_upPrintDeltaY;
	int m_downPrintDeltaX;
	int m_downPrintDeltaY;

	int m_etcPrintDeltaX;
	int m_etcPrintDeltaY;


	void LoadCheckButtonPic(void);
	void LoadUpdownButtonPic(void);
	void LoadRadioButtonPic(void);
	void LoadParamButtonPic(void);
	void LoadEtcCheckButtonPic(void);

	void InitCheckButton(void);
	void InitUpdownButton(void);
	void InitRadioButton(void);
	void InitParamButton(void);
	void InitEtcCheckButton(void);


	int GetSetSelectSetNumber(void);
	void SetSetSelectSetNumber(int n);

	void ChangePlace(int set, int delta);
	void SetPlaceToVar(void);
	void GetVarToParam(void);
	void SetParamToVar(void);
	void ChangeOnOff(int set);
	void ChangeParamOnOff(int set);
	void ChangeEtcOnOff(int etc);

	POINT GetBaseZahyo(int place);

	POINT GetEtcBaseZahyo(int n);

		
private:

};

#endif
/*_*/

