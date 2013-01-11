//
//
//

#if !defined __NNNUTILLIB_COMPILEDESC__
#define __NNNUTILLIB_COMPILEDESC__

class CNNNUtilLibCompileDesc
{
public:
	CNNNUtilLibCompileDesc();
	~CNNNUtilLibCompileDesc();
	void End(void);

	static LPSTR GetCompileDate(void);
	static LPSTR GetCompileTime(void);

	static char m_date[];
	static char m_time[];

private:

};


#endif
/*_*/

