//
//
//

#if !defined __NYANPICTURELIB_ALLPICTURE__
#define __NYANPICTURELIB_ALLPICTURE__


class CRedBlt;
class CGreyBlt;
class CColorBlt;
class CTransLucentBlt;
class CTransLucentBlt0;
class CTransLucentBlt2;
class CTransLucentBlt3;
class CMaskBlt;
class CNegaBlt;
class CBlt;
class CBltBeta;
class CBlt256;
class CBlt256Beta;
class CShapeBlt;
class CGradationShapeBlt;
class CAddBlt;
class CLightBlt;
class CStretchBlt;
class CColorAddBlt;
class CChangeTransLucentBlt;
class COverrapBlt;
class CYUVChangeBlt;
class CGreyBlt2;
class CSepiaBlt;
class CAddSubBlt;
class CStretchAddSubBlt;

class CAllPicture
{
public:
	CAllPicture();
	virtual ~CAllPicture();
	void End(void);


	static void GreyBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize,char* maskPic, BOOL transFlag = TRUE, LPVOID lpPalette = NULL);
	static void RedBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize,char* maskPic, BOOL transFlag = TRUE, LPVOID lpPalette = NULL);
	static void ColorBlt(POINT putPoint,POINT srcPoint,SIZE putSize,char* maskPic,SIZE srcSize,int r,int g,int b);
	static void TransLucentBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize,int transPercent);
	static void TransLucentBlt0(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize,int transPercent);
	static void TransLucentBlt2(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize,int transPercent);
	static void TransLucentBlt3(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,LPVOID maskData,SIZE srcSize,int transPercent);
	static void MaskBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,LPVOID maskData,SIZE srcSize);
	static void NegaBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize,int negaPercent);
	static void Blt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize);
	static void BltBeta(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize);
	static void Blt256(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,LPVOID lpPalette,SIZE srcSize);
	static void Blt256Beta(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,LPVOID lpPalette,SIZE srcSize);
	static void ShapeBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID maskData,SIZE srcSize,int r,int g,int b);
	static void GradationShapeBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID maskData,SIZE srcSize,int r1,int g1,int b1,int r2,int g2,int b2);
	static void AddBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize);
	static void LightBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize,int lightPercent);
	static void StrtchBlt1(POINT dstPoint,POINT srcPoint,SIZE dstSize,SIZE srcSize,LPVOID picData,LPVOID maskData,SIZE picSize,BOOL transFlag,int transPercent);
	static void ColorAddBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,LPVOID maskData,SIZE srcSize,BOOL transFlag,int r,int g,int b,int ps = 100);
//	static void ChangeTransLucentBlt(POINT dstPoint,POINT srcPoint,SIZE putSize,LPVOID picData1,LPVOID picData2,LPVOID maskData1,LPVOID maskData2,SIZE picSize,int ps1,int ps2);
	static void ChangeTransLucentBlt(POINT dstPoint,SIZE putSize,LPVOID picData1,LPVOID picData2,LPVOID maskData1,LPVOID maskData2,SIZE picSize,SIZE picSize2,int ps1,int ps2);
	static void OverrapBltWithScreen(POINT nextPoint,LPVOID nextPic,SIZE nextPicSize,int startPercent,int endPercent);
	static void OverrapBlt(POINT startPoint,LPVOID startPic,SIZE startPicSize,POINT endPoint,LPVOID endPic,SIZE endPicSize,int startPercent,int endPercent);
	static void YUVChangeBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,LPVOID maskData,SIZE srcSize,BOOL yuvReverse = FALSE,int betaTransPercent255 = 255);
	static void GreyBlt2(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize,char* maskPic, int ps256,BOOL transFlag = TRUE, LPVOID lpPalette = NULL);
	static void SepiaBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize,char* maskPic, int ps256,int r,int g,int b,BOOL transFlag = TRUE, LPVOID lpPalette = NULL);
	static void AddSubBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,char* maskData,SIZE srcSize,int percent);
	static void StrtchAddSubBlt(POINT dstPoint,POINT srcPoint,SIZE dstSize,SIZE srcSize,LPVOID picData,LPVOID maskData,SIZE picSize,BOOL transFlag,int transPercent,int deltaR = 0,int deltaG = 0,int deltaB = 0);
	void ReCreateAllShader(void);
	static void ChangeBlt256Beta(POINT dstPoint,SIZE putSize,LPVOID picData1,LPVOID picData2,LPVOID paletteData1,LPVOID paletteData2,SIZE picSize,SIZE picSize2,int ps1,int ps2);

protected:
	static CRedBlt* m_redBlt;
	static CGreyBlt* m_greyBlt;
	static CColorBlt* m_colorBlt;
	static CTransLucentBlt* m_transLucentBlt;
	static CTransLucentBlt0* m_transLucentBlt0;
	static CTransLucentBlt2* m_transLucentBlt2;
	static CTransLucentBlt3* m_transLucentBlt3;
	static CMaskBlt* m_maskBlt;
	static CNegaBlt* m_negaBlt;
	static CBlt* m_blt;
	static CBltBeta* m_bltBeta;
	static CBlt256* m_blt256;
	static CBlt256Beta* m_blt256Beta;
	static CShapeBlt* m_shapeBlt;
	static CGradationShapeBlt* m_gradationShapeBlt;
	static CAddBlt* m_addBlt;
	static CLightBlt* m_lightBlt;
	static CStretchBlt* m_stretchBlt;
	static CColorAddBlt* m_colorAddBlt;
	static CChangeTransLucentBlt* m_changeTransLucentBlt;
	static COverrapBlt* m_overrapBlt;
	static CYUVChangeBlt* m_yuvChangeBlt;
	static CGreyBlt2* m_greyBlt2;
	static CSepiaBlt* m_sepiaBlt;
	static CAddSubBlt* m_addSubBlt;
	static CStretchAddSubBlt* m_stretchAddSubBlt;
private:
};



#endif
/*_*/

