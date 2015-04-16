#if !defined __SYSTEMNNN_NNNUTILLIB_SELECTOBJECTSETUP__
#define __SYSTEMNNN_NNNUTILLIB_SELECTOBJECTSETUP__


class CNameList;
class CSelectObjectSetup
{
public:
	CSelectObjectSetup(int n);
	~CSelectObjectSetup();
	void End(void);

	int m_objectNumber;
	int m_addObjectNumber;
	LPSTR m_filenameBG;
	int* m_placeExistVarNumber;
	int* m_placeSelectOkVarNumber;
	int* m_addVarNumber;
	int m_addOnlyFlag;


	BOOL GetInitGameParam(int* lpVar, LPSTR name,int initData);
	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name,LPSTR initString);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name);

	CNameList* m_nameList;

	POINT GetAddPrint(int n);
protected:
	int m_addPrintX;
	int m_addPrintY;
	POINT* m_addPrint;

};


#endif
/*_*/
