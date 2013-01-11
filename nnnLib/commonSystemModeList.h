#if !defined __NNNLIB_COMMONSYSTEMMODELIST__
#define __NNNLIB_COMMONSYSTEMMODELIST__



class CCommonSystemModeList
{
public:
	CCommonSystemModeList();
	~CCommonSystemModeList();
	void End(void);


	int GetModeNumberByName(LPSTR name);
	LPSTR GetModeName(int n);


private:
	static char m_systemClassNameList[][32];

};

#endif
/*_*/
