#if !defined __NNNUTILLIB_CURRENTDIRCONTROL__
#define __NNNUTILLIB_CURRENTDIRCONTROL__


class CCurrentDirControl
{
public:
	CCurrentDirControl();
	~CCurrentDirControl();
	void End(void);

	static void ChangeCurrentToExe(void);
	static void RestoreCurrent(void);
private:
	static char m_dir[];

};

#endif
/*_*/

