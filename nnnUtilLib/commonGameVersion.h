//
//
//

#if !defined __TINYAN_NNNUTILLIB_COMMONGAMEVERSION__
#define __TINYAN_NNNUTILLIB_COMMONGAMEVERSION__

//#define __TAIKEN_VERSION__

class CCommonGameVersion
{
public:
	CCommonGameVersion();
	~CCommonGameVersion();
	void End(void);

	static BOOL CheckTaikenOrNetVersion(void);

	static BOOL CheckTaikenVersion(void) {return m_taikenVersion;}
	static BOOL CheckDemoVersion(void) {return m_demoVersion;}
	static BOOL CheckNetVersion(void) {return m_netVersion;}

	static BOOL CheckLoadCommandOk(void){return m_loadOk;}
	static BOOL CheckSaveCommandOk(void){return m_saveOk;}
	static BOOL CheckOmakeOk(void){return m_omakeOk;}
	static BOOL CheckListenBGMOk(void){return m_listenBGMOk;}
	static BOOL CheckCGOk(void){return m_cgOk;}
	static BOOL CheckSceneOk(void){return m_sceneOk;}
	static BOOL CheckMovieOk(void){return m_movieOk;}

	static void SetTaikenVersion(BOOL flg = TRUE) {m_taikenVersion = flg;}
	static void SetDemoVersion(BOOL flg = TRUE) {m_demoVersion = flg;}
	static void SetNetVersion(BOOL flg = TRUE) {m_netVersion = flg;}

	static void SetLoadOk(BOOL flg = TRUE){m_loadOk = flg;}
	static void SetSaveOk(BOOL flg = TRUE){m_saveOk = flg;}
	static void SetOmakeOk(BOOL flg = TRUE){m_omakeOk = flg;}
	static void SetListenBGMOk(BOOL flg = TRUE){m_listenBGMOk = flg;}
	static void SetCGOk(BOOL flg = TRUE){m_cgOk = flg;}
	static void SetSceneOk(BOOL flg = TRUE){m_sceneOk = flg;}
	static void SetMovieOk(BOOL flg = TRUE){m_movieOk = flg;}

	static BOOL m_taikenVersion;
	static BOOL m_demoVersion;
	static BOOL m_netVersion;

	static BOOL m_loadOk;
	static BOOL m_saveOk;
	static BOOL m_omakeOk;
	static BOOL m_listenBGMOk;
	static BOOL m_cgOk;
	static BOOL m_sceneOk;
	static BOOL m_movieOk;
	
private:
};




#endif
/*_*/

