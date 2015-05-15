//
// SelectPlace.h
//

#if !defined __NNNLIB_COMMONSHOP____
#define __NNNLIB_COMMONSHOP__

class CCommonGeneral;
class CGameCallBack;
class CNameList;
class CMyMessage;

//class CPrintGameDate;
class CCommonAnimeParts;
class CShopItemData;

class CSuuji;

class CCommonShop : public CCommonGeneral
{
public:
	CCommonShop(CGameCallBack* lpGame,int extMode = 0);
	virtual ~CCommonShop();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	virtual void CreateStartScreen(void);

	typedef struct _tagITEMDATA
	{
		int n;
		int type;
		int param;
		LPSTR title;
	}ITEMDATA;

protected:
	CShopItemData* m_shopItem;

	virtual void FinalExitRoutine(void);
	virtual int EndMode(void);

	int m_canSelectLimit;
	int m_canSelectNoPoint;



	CCommonButton* m_okButton;
	CCommonButton* m_cancelButton;


	static char m_defaultPlateFilename[];
	LPSTR m_plateFilename;

	int m_platePrintX;
	int m_platePrintY;
	int m_plateItemPrintX;
	int m_plateItemPrintY;
	int m_descPrintX;
	int m_descPrintY;
	int m_descPrintNextX;
	int m_descPrintNextY;
	int m_descFontSize;
	int m_descColorR;
	int m_descColorG;
	int m_descColorB;
	int m_plateItemPrintFlag;



	CMyMessage* m_message;
	int m_itemTypeKosuu;
	CCommonRadioButtonGroup* m_radio;

	int m_page;
	int m_pageMax;
	int m_itemBlockX;
	int m_itemBlockY;
	int m_itemPerPage;
	int m_itemPrintX;
	int m_itemPrintY;
	int m_itemPrintNextX;
	int m_itemPrintNextY;
	int m_itemSizeX;
	int m_itemSizeY;

//	LPSTR m_suffix;
//	static char m_defaultSuffix[];
	static char m_defaultNoItemFilename[];
	static char m_defaultCursorPicFilename[];
	static char m_defaultNotAppearName[];
	static char m_defaultPointVarName[];

	LPSTR m_notAppearName;

	LPSTR m_noItemFilename;

	POINT GetItemZahyo(int nx,int ny);
	POINT GetItemZahyo(int n);

	int m_allItemNumber;
	int* m_itemTable;


	void CreateTable(void);
	void SetupButton(void);
	int m_itemListNumber;

	int m_selectedItemNumber;

	void LoadItemPic(void);
	CPicture** m_itemPic;

	int m_typeNumber;
	int* m_typeTableNumber;
	int** m_typeTable;



	void ReloadButtonPic(void);
	int m_onNumber;
	int GetOnNumber(POINT pt);

	int m_lowCursor;
	void PutCursor(int n);
	CPicture* m_cursorPic;
	int m_useCursorPic;

	int 	m_cursorColorR;
	int 	m_cursorColorG;
	int 	m_cursorColorB;
	int 	m_cursorColorA;

	int m_itemNamePrintFlag;
	int m_itemNameFontSize;
	int m_itemNamePrintX;
	int m_itemNamePrintY;
	int m_itemNameFontColorR;
	int m_itemNameFontColorG;
	int m_itemNameFontColorB;


	void BuyItem(void);
	int m_pointVarNumber;
	int m_gamePoint;

	void GetGamePoint(void);
	void UseGamePoint(int p);

	void SetAppearFlag(int n);
	BOOL CheckAppearFlag(int n);
	int* m_appearControlVarNumber;
	int* m_appearFlag;
	int* m_soldOutFlag;
	int m_bitPattern[32];

	void SetOkCancelStatus(void);

	CPicture* m_newMarkPic;
	CPicture* m_soldOutPic;
	CSuuji* m_gamePointSuuji;
	CSuuji* m_pricePointSuuji;
	int m_printNewMarkFlag;
	int m_printSoldOutFlag;
	int m_newMarkPrintX;
	int m_newMarkPrintY;
	int m_soldoutPrintX;
	int m_soldoutPrintY;


	int m_gamePointPrintX;
	int m_gamePointPrintY;
	int m_pricePointPrintX;
	int m_pricePointPrintY;

private:

};

#endif
/*_*/

