//
// myMouseStatus.h
//

#if !defined __TINYAN_NNNUTILLIB_MYMOUSESTATUS__
#define __TINYAN_NNNUTILLIB_MYMOUSESTATUS__

#include "mymousestruct.h"

class CMyMouseStatus
{
public:
	CMyMouseStatus();
	~CMyMouseStatus();
	void End(void);

	void Init(BOOL generalInitFlag = FALSE);

	void SetStatus(LPMYMOUSESTRUCT lpMouse);

//	BOOL CheckClick(BOOL trigFlag = FALSE);
	BOOL CheckClick(int trigNumber = 0);
	BOOL CheckSkipClick(void);

	POINT GetZahyo(void);
	BOOL GetTrig(int trigNumber);
	BOOL GetTrigMae(int trigNumber);
	int GetWheel(void);

	void TrigToMae(void);

	void SetTrig(int n, BOOL flg = TRUE);
	void SetTrigOnly(int n, BOOL flg = TRUE);
	void SetZahyo(int x, int y);
	void AdjustOffset(int dx,int dy);

	void SetWheel(int wheel);

	void CheckButtonSwap(void);
private:
	MYMOUSESTRUCT m_mouseStatus;

	int m_swapFlag;
};


#endif

/*_*/

