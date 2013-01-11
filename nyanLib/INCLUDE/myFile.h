//
//
//

#if !defined __NYANLIB_MYFILE__
#define __NYANLIB_MYFILE__

class CMyFile
{
public:
	CMyFile();
	~CMyFile();
	void End(void);

	static FILE* Open(LPSTR filename,LPSTR mode);
	static HANDLE OpenRead(LPSTR filename);
	static HANDLE OpenWrite(LPSTR filename);

private:
};

#endif
/*_*/

