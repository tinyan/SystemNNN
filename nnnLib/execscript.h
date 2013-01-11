//
// execscript.h
//

#if !defined __NNNLIB_EXECSCRIPT__
#define __NNNLIB_EXECSCRIPT__

class CScriptCallBack;

class CExecScript
{
public:
	CExecScript(CScriptCallBack* lpCallBack,int sz = -1);
	~CExecScript();
	void End(void);

	BOOL LoadScript(LPSTR filename);

	int GetErrorKosuu(void);
	LPSTR GetErrorMessage(int);

	int Exec(int n = -1);
	int ExecCase(int nm);

	int GetCase(int pc, int n);

	LPSTR GetMessagePtr(int mesNum);
	LPSTR GetStringPtr(int strNum);

//	int GetMessageNumber(int script);

	int GetPC(void);
	void SetPC(int pc);

	int SearchLabel(LPSTR labelName);

	int m_stackPointer;
	int m_stack[256];
	int m_ID[256];

//	int GetNextMessageNumber(void);


	BOOL SearchMessageID(int id);
	BOOL SearchSelectID(int id);

	BOOL SetPCByFilmNumber(int filmNumber);

	int GetInt32(int n);

	static void SetAngouCode(int xorCode = 0xffffffff,int addXorCode = 0, int addIncCode = 0){m_xorCode = xorCode;m_addXorCode = addXorCode;m_addIncCode = addIncCode;}


	BOOL ChangeIDToAddr(void);
	BOOL AdjustScriptCall(void);
	BOOL AdjustCommandCall(void);

	int GetData(int pc){return m_data[pc];}

private:
//	CGame* m_game;
	CScriptCallBack* m_callBack;

	char m_filename[256];

	int* m_data;
	int m_dataSize;

	int m_pc;

	int m_messagePointer1;
	int m_messagePointer2;
	int m_messageKosuu1;
	int m_messageKosuu2;

	int m_int32Pointer;

	BOOL m_dataExistFlag;


	int m_stateCount;

	//ErrorŠÖŒW
	void AddError(LPSTR mes);

	BOOL m_errorFlag;
	char m_errorMessage[16][256];
	int m_errorCount;
	int m_errorNum;

	int m_bufferSize;
	int Enzan(int pc, int* pSkip = NULL);

	int ScriptToVarNumber(int script);
	int ScriptToData(int script);

//	void GetSelectMessage(int pc);

//	void GetParameter(int pc);
	int m_polandStack[256];
	int m_int32stack[256];
	int m_paraKosuu;
	int m_paraWork[256];

	char m_errorMessageTmp[256];

	int m_selectMessageKosuu;
	LPSTR m_selectMessage[3];
	int m_selectMessageNumber[3];

	int m_storyKosuu;
	int m_subCallPointer;
	int m_selectPointer;
	int m_commandCallPointer;
	int m_scriptCallPointer;

	static int m_xorCode;
	static int m_addXorCode;
	static int m_addIncCode;
};

#endif
/*_*/

