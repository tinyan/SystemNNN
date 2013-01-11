//
// backExecClass
//

#if !defined __NNNLIB_BACKEXECCLASS__
#define __NNNLIB_BACKEXECCLASS__


class CExecScript;
class CNameList;
class CGameCallBack;

class CBackExecClass
{
public:
	CBackExecClass(CGameCallBack* lpGame);
	~CBackExecClass();
	void End(void);

	void ReStart(void);

	void SetDrawMode(int count);
	void SetOverrapMode(void);

	BOOL ExecScript(BOOL mustFlag = FALSE,BOOL loopFlag = TRUE);
	BOOL LoadScript(int scriptNumber);

	void Print(void);
	void PrintLayers(int startLayer,int endLayer);

	void Calcu(void);

//	int GetShakin(void){return m_shakin;}
//	void ResetShakin(void){m_shakin = 0;}

private:
	CGameCallBack* m_game;
	int m_backExecMode;
	CExecScript* m_execScript;
	int m_scriptNumber;
	CNameList* m_sptList;

//	int m_shakin;
	int m_drawCount;

	CPicture* m_pic1;
	CPicture* m_pic2;

	int m_count;
	int m_type;
	int m_length;

//	int m_deltaPaste;
	int m_kaeshita;
};









#endif
/*_*/

