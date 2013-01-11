//
// basicSetup.h
//

#if !defined __TINYAN_NNNUTILLIB_BASICSETUP__
#define __TINYAN_NNNUTILLIB_BASICSETUP__

#include "myMouseStruct.h"

//class CGameCallBack;
//class CPicture;
//class CMyMouseStatus;
class CNameList;

class CBasicSetup
{
public:
	CBasicSetup();
	virtual ~CBasicSetup();
	void End(void);

protected:
	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name);
	CNameList* m_setup;
	BOOL LoadSetupFile(LPSTR filenameonly, int varKosuu = 64);
};


#endif
/*_*/

