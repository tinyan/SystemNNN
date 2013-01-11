//
// selectZukan.h
//

#if !defined __NNNLIB_SELECTZUKAN__
#define __NNNLIB_SELECTZUKAN__

class CCommonGeneral;
class CGameCallBack;
class CNameList;

class CCommonAnimeParts;

class CCommonSelectZukan : public CCommonGeneral
{
public:
	CCommonSelectZukan(CGameCallBack* lpGame);
	virtual ~CCommonSelectZukan();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	virtual void BeforeInit(void);
	int m_bitPattern[32];

	void Function(int type,int paraKosuu,int* lpParam);

protected:

	int m_blocks;
	LPSTR m_filenameSeat;
	int* m_appearVarNumber;
	int m_returnVarNumber;
	int m_zukanKosuu;
	int m_zukanNumber;

	int m_onNumber;
	int GetOnNumber(POINT pt);
	BOOL CheckSelectOk(int n);

	int* m_flag;

	POINT GetPrintZahyo(int n);
	POINT GetPicSrc(int n);


	int m_printX;
	int m_printY;
	int m_nextX;
	int m_nextY;
	int m_sizeX;
	int m_sizeY;
	int m_kosuuX;
	int m_kosuuY;
	int m_picKosuuX;
	int m_picKosuuY;

	void SetReturnVar(void);

	static char m_defaultAppearVarName[];
	static char m_defaultReturnVarName[];
	static char m_defaultFunctionName[];

	CCommonAnimeParts* m_animeCursor;
	int m_old;
};

#endif
/*_*/

