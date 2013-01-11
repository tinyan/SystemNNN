//
// cardSystem.h
//


#if !defined __NNNLIB_CARDSYSTEM__
#define __NNNLIB_CARDSYSTEM__

class CCommonGeneral;
class CGameCallBack;
class CNameList;
class CPrintCard;
class CPrintCardPower;
class CPrintCardGaze;
class CCommonButton;


class CCommonCardSystem : public CCommonGeneral
{
public:
	CCommonCardSystem(CGameCallBack* lpGame);
	virtual ~CCommonCardSystem();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	virtual void Function(int type,int paraKosuu,int* lpParam);
	virtual void StartUserCommand(int paraKosuu,int* paraPtr);


protected:
	int m_cardKosuu;
	int m_cardLevelMax;
	int* m_cardPlaceVar;

	int m_appearControlFlag;
	int m_enableControlFlag;
	int m_noserareruControlFlag;

	static char m_defaultAppearFunctionName[];
	static char m_defaultEnableFunctionName[];
	static char m_defaultNoserareruFunctionName[];


	static char m_defaultAppearVarName[];
	static char m_defaultEnableVarName[];
	static char m_defaultNoserareruVarName[];

	static char m_defaultCardNameTag[];

	int m_appearVarNumber;
	int m_enableVarNumber;
	int m_noserareruVarNumber;

	int* m_appearFlag;
	int* m_enableFlag;
	int* m_noserareruFlag;

	int CheckAppearByVar(int card);
	int CheckEnableByVar(int card);
	int CheckNoserareruByVar(int card);

	void SetAppearCard(int card,int flg);
	void SetEnableCard(int card,int flg);
	void SetNoserareruCard(int card,int flg);

	int m_bitPattern[32];

	int m_updownAdjust;

//	int* m_cardStatusVarNumber;
	
	int m_powerMax;
	int m_powerMaxVarNumber;
	void CheckPowerMaxByVar(void);

	int m_cardSizeX;
	int m_cardSizeY;
	int m_onCardPrintX;
	int m_onCardPrintY;
	POINT* m_cardZahyo;

	CPrintCard** m_printCard;
	CPrintCardPower* m_printCardPower;
	CPrintCardGaze* m_printCardGaze;

	void PutCard(int card,POINT pt,int st=0);

	int m_catchNumber;
	CCommonButton* m_okButton;

};



#endif
/*_*/

