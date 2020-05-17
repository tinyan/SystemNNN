//
// nothing.h
//

#if !defined __NNNLIB_PRINTMOVIE__
#define __NNNLIB_PRINTMOVIE__

class CCommonGeneral;
class CGameCallBack;
class CNameList;

class CMyDirectShow;

class CCommonPrintMovie : public CCommonGeneral
{
public:
	CCommonPrintMovie(CGameCallBack* lpGame);
	virtual ~CCommonPrintMovie();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	int CheckCodec(void);

	static char m_defaultFileNameBG[];
	void SetCodecError(int flg = TRUE){m_codecError = flg;}

	static char m_defaultMovieFileName[];

	void SetMovieNumber(int n);
	void SetMovie(LPSTR filename);

	void ChangeDirectShow(CMyDirectShow* lpShow){m_directShow = lpShow;}
	virtual void StartUserCommand(int paraKosuu,int* paraPtr);

	static char m_defaultSelectMovieVarName[];

	BOOL CheckFirstFrame(void){return m_firstFrame;}

	void StartByDirect(int moveieNumber);

protected:
	LPSTR m_filenameBG;
	int m_codecError;

	CMyDirectShow* m_directShow;

	LPSTR m_movieFileName;
	LPSTR m_codecCheckFileName;

	BOOL m_selectMovieFlag;
	LPSTR m_selectMovieFileName;

	int m_noSkipFlag;

	BOOL m_scriptMovieFlag;

	int m_selectMovieByVarFlag;
	int m_selectMovieVarNumber;

	BOOL m_exitFlag;
	int m_lastCount;
	int m_lastWait;
	BOOL m_dontSaiseiFlag;

	BOOL m_firstFrame;
	int m_autoDebugWait;

	bool m_directMovieFlag;
	int m_directMovieNumber;
};

#endif
/*_*/

