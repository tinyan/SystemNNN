#if !defined __NNNUTILLIB_GETCOMMANDLINEPARAM__
#define __NNNUTILLIB_GETCOMMANDLINEPARAM__

class CGetCommandLineParam
{
public:
	CGetCommandLineParam();
	~CGetCommandLineParam();
	void End(void);

	static int GetParam(int buffKosuu,int buffSize,char** lplpBuff,LPSTR lpCmd);
	static void SetParamSub(int start,int end,char* buf,int buffSize,LPSTR lpCmd);

private:
};

#endif
/*_*/

