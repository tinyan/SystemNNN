//
//
//

#if !defined __NNNUTILLIB_MMLCONTROL__
#define __NNNUTILLIB_MMLCONTROL__



class CMMLControl
{
public:
	CMMLControl();
	~CMMLControl();
	void End(void);

	BOOL LoadMML(LPSTR filename);
	void RestartMML(void);
	LPSTR Kaiseki(void);	//if return NULL end of MML

private:
	char* m_mml;
	int m_mmlLoop[16];
	int m_mmlKakkoPointer[16];
	int m_mmlBufferSize;
	int m_mmlSize;
	int m_level;
	int m_mmlPointer;

	char m_filename[256];
};







#endif
/*_*/


