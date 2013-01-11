//
// gameUtil.h
//

#if !defined __TINYAN_GAMEUTIL__
#define __TINYAN_GAMEUTIL__

class CGameUtil
{
public:
	CGameUtil();
	~CGameUtil();
	void End(void);

	BOOL MakeMiniCG106x80(int* screenBuffer, int* makedBuffer);
	BOOL MakeMiniCG132x100(int* screenBuffer, int* makedBuffer);


private:
};


#endif
/*_*/

