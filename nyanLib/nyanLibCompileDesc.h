//
//
//

#if !defined __NYANLIB_COMPILEDESC__
#define __NYANLIB_COMPILEDESC__


class CNyanLibCompileDesc
{
public:
	CNyanLibCompileDesc();
	~CNyanLibCompileDesc();
	void End(void);

	static LPSTR GetCompileDate(void);
	static LPSTR GetCompileTime(void);

	static char m_date[];
	static char m_time[];
private:
};










#endif
/*_*/

