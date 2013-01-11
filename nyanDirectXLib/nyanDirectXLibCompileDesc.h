//
//
//

#if !defined __NYANDIRECTXLIB_COMPILEDESC__
#define __NYANDIRECTX_COMPILEDESC__

class CNyanDirectXLibCompileDesc
{
public:
	CNyanDirectXLibCompileDesc();
	~CNyanDirectXLibCompileDesc();
	void End(void);

	static LPSTR GetCompileDate(void);
	static LPSTR GetCompileTime(void);

	static char m_date[];
	static char m_time[];

private:

};


#endif
/*_*/

