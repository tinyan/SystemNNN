//
//
//

#if !defined __NYANGRAPHICSLIB_ALLGRAPHICS__
#define __NYANGRAPHICSLIB_ALLGRAPHICS__


class CFade;
class CFillScreen;
class CMulti;
class CAddSub;
class CGrey;
class CNega;
class CLayerSepia;
class CLayerGrey;

class CAllGraphics
{
public:
	CAllGraphics();
	virtual ~CAllGraphics();
	void End(void);


	static void Fade(int ps1,int r=0,int g=-1,int b=-1,int ps2 = -1);
	static void FillScreen(int r = 0,int g = -1, int b = -1);
	static void Multi(int percentR,int percentG = -1,int percentB = -1);
	static void AddSub(int deltaR,int deltaG = -9999,int deltaB = -9999);
	static void Nega(void);
	static void Grey(void);

	static void MultiClip(int startX,int startY,int sizeX,int sizeY,int percentR,int percentG = -1,int percentB = -1);
	static void AddSubClip(int startX,int startY,int sizeX,int sizeY,int deltaR,int deltaG = -9999,int deltaB = -9999);
	static void NegaClip(int startX,int startY,int sizeX,int sizeY);
	static void GreyClip(int startX,int startY,int sizeX,int sizeY);

	static void LayerSepia(int ps256,int r,int g,int b);
	static void LayerGrey(int ps256);

	static BOOL Clip(int& startX,int& startY,int& sizeX,int& sizeY);

	void ReCreateAllShader(void);

protected:
	static CFade* m_fade;
	static CFillScreen* m_fillScreen;
	static CMulti* m_multi;
	static CAddSub* m_addSub;
	static CGrey* m_grey;
	static CNega* m_nega;
	static CLayerSepia* m_layerSepia;
	static CLayerGrey* m_layerGrey;

private:
};

#endif
/*_*/
