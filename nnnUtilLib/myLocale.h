#if !defined __NNNUTILLIB_MYLOCALE__
#define __NNNUTILLIB_MYLOCALE__

class CMyLocale
{
public:
	CMyLocale();
	~CMyLocale();
	void End(void);

	static void SetLocale(LPSTR name);
	static void SetLocale(int locale);

	static char m_localeString[256];
	static int m_locale;

private:
};

#endif
/*_*/
