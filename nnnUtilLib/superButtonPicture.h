//
// systempicture.h
//

#if !defined __NNNUTILLIB_SUPERBUTTONPICTURE__
#define __NNNUTILLIB_SUPERBUTTONPICTURE__

class CPicture;

#define SUPERBUTTON_PICKOSUU_MAX 200

class CSuperButtonPicture
{
public:
	CSuperButtonPicture();
	~CSuperButtonPicture();
	void End(void);

	static CSuperButtonPicture* m_this;
	static CPicture* GetPicture(int n);
private:
	static CPicture** m_ppPic;
};



#endif
/*_*/

