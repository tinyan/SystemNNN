#if !defined __NNNLIB_COMMONUSERCOMMANDLIST__
#define __NNNLIB_COMMONUSERCOMMANDLIST__

class CCommonUserCommandList
{
public:
	CCommonUserCommandList();
	~CCommonUserCommandList();
	void End(void);

	int GetKosuu(void);
	int GetModeNumber(int n);
	LPSTR GetModeName(int n);

private:
	int m_kosuu;
	typedef struct _tagNNUSERCOMMANDLIST
	{
		int number;
		char name[64];
	} NNNUSERCOMMANDLIST;

	static NNNUSERCOMMANDLIST m_list[];

};

#endif
/*_*/

