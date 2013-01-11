//
// scriptCallBack.h
//

#if !defined __NNNLIB_SCRIPTCALLBACK__
#define __NNNLIB_SCRIPTCALLBACK__


class CScriptCallBack
{
public:
	CScriptCallBack();
	virtual ~CScriptCallBack();
	void End(void);

	virtual void ReceiveScriptCommand(int cmd, int para1 = 0, LPVOID para2 = NULL,int para3 = 0) = 0;
	virtual void PreReceiveScriptData(int cmd, int para1 = 0, LPVOID para2 = NULL) = 0;
	virtual void ReceiveUserCommand0(int cmd, int paraKosuu, int* paraPtr) = 0;
//	virtual void ReceiveUserCommand(int cmd, int paraKosuu, int* paraPtr) = 0;
//	virtual void ReceiveUserFunction(int cmd, int paraKosuu, int* paraPtr) = 0;
	virtual void ReceiveUserFunction0(int cmd, int paraKosuu, int* paraPtr) = 0;

	virtual int GetVarData(int varNum) = 0;
	virtual int GetCalcuVarData(int varNum) = 0;
	virtual void SetVarData(int varNum, int dat) = 0;
protected:
private:
};

#endif

/*_*/

