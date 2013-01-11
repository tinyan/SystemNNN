#if !defined __NNNUTILLIB_NNNLOG__
#define __NNNUTILLIB_NNNLOG__

class CNNNLog
{
public:
	CNNNLog();
	~CNNNLog();
	void End(void);

	static void StartLog(void);
	static void AddLog(LPSTR mes);
private:
	static BOOL m_errorLogFlag;
	static char m_logFileName[];

};
#endif
/*_*/
