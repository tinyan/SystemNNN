#if !defined __NNNUTILLIB_OMAKECLASSSUPPORT__
#define __NNNUTILLIB_OMAKECLASSSUPPORT__

#define MODE_MAX_OMAKE 100
#define OMAKEMODE_KOSUU_OMAKE 32

class COmakeClassSupport
{
public:
	COmakeClassSupport(int omakeClassExistFlag);
	~COmakeClassSupport();
	void End(void);


	int GetOmakeClassExistFlag(void){return m_omakeClassExistFlag;}
	void SetOmakeClassDataByLoad(LPVOID ptr);
	void GetOmakeClassDataForSave(LPVOID ptr);

	int GetOmakeClass(int md,int n){return m_omakeClass[md][n];}

	BOOL AddOmakeClass(int parentModeNumber, int omakeModeNumber,int mode,int place);
	BOOL DeleteOmakeClass(int parentModeNumber, int omakeModeNumber);
	int GetOmakeMode(int parentModeNumber, int omakeModeNumber, int type);
	void SetOmakeMode(int parentModeNumber, int mode, int omakeModeNumber, int type);
	int SearchOmakeMode(int parentModeNumber, int omakeModeNumber);

private:
	void AllClearOmakeClass(void);
	void ClearOmakeClass(int parentModeNumber);

	int m_omakeClass[MODE_MAX_OMAKE][OMAKEMODE_KOSUU_OMAKE];

	int m_omakeClassExistFlag;
};

#endif
/*_*/

