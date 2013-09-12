//
// gameUtil.h
//

#if !defined __TINYAN_GAMEUTIL__
#define __TINYAN_GAMEUTIL__

class CPicture;

class CGameUtil
{
public:
	CGameUtil();
	~CGameUtil();
	void End(void);

	void SetScreenSize(int sizeX,int sizeY);
	void SetMiniCGSize(int sizeX,int sizeY);
	void SetMiniCGReduce(int reduce);

	void MakeMiniCG(int* screenBuffer, int* makedBuffer);

	void MakeFitMiniCG(int* screenBuffer, int* makedBuffer);
	void MakeNoFitMiniCG(int* screenBuffer, int* makedBuffer);

	BOOL MakeMiniCG106x80(int* screenBuffer, int* makedBuffer);
	BOOL MakeMiniCG132x100(int* screenBuffer, int* makedBuffer);

	void AddMaskToMiniPic(int* buffer,CPicture* lpPic);

private:
	int m_screenSizeX;
	int m_screenSizeY;
	int m_miniCGSizeX;
	int m_miniCGSizeY;
	int m_miniCGReduce;
	
	BOOL m_reduceFitFlag;

	BOOL CheckSpecialSize(void);

};


#endif
/*_*/

