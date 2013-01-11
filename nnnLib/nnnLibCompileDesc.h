//
//
//

#if !defined __NNNLIB_COMPILEDESC__
#define __NNNLIB_COMPILEDESC__

class CNNNLibCompileDesc
{
public:
	CNNNLibCompileDesc();
	~CNNNLibCompileDesc();
	void End(void);

	static LPSTR GetCompileDate(void);
	static LPSTR GetCompileTime(void);

	static char m_date[];
	static char m_time[];

private:

};


#endif
/*_*/

