//
// setuplist.h
//

#if !defined __NNNUTILLIB_SETUPLIST__
#define __NNNUTILLIB_SETUPLIST__

class CNameList;
class CSetupList
{
public:
	CSetupList();
	virtual ~CSetupList();
	virtual void End(void);

	void SetSetup(CNameList* setup);
	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name);
	CNameList* m_setup;
	CNameList* m_createSetup;
	BOOL LoadSetupFile(LPSTR filenameonly, int varKosuu = 64);
	CNameList* GetNameList(void){return m_setup;}
private:
};










#endif
/*_*/

