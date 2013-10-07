#if !defined __NYANLIB_LIBINCLUDE__
#define __NYANLIB_LIBINCLUDE__

#if !defined __TINYANLIBDIR__
#define __TINYANLIBDIR__ "d:\\tinyan\\systemNNNLib\\lib\\"
#endif


#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"imm32.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"ddraw.lib")
#pragma comment(lib,"dsound.lib")
//#pragma comment(lib,"dsetup.lib")

#if defined _DEBUG
//#if _MSC_VER >= 1700
	#pragma comment(lib,__TINYANLIBDIR__ "nyanLib2012D.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanGraphicsLib2012D.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanPictureLib2012D.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanGeoLib2012D.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanEffectLib2012D.lib")

	#pragma comment(lib,__TINYANLIBDIR__ "nyanEffectNaturalLib2012D.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanEffectCharaLib2012D.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanEffectSpecialLib2012D.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanEffectScreenLib2012D.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanEffectWipeLib2012D.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanEffectGeoLib2012D.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanEffectTransformLib2012D.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanEffectMoveLib2012D.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanEffectAnimeLib2012D.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanEffectEtcLib2012D.lib")

	#pragma comment(lib,__TINYANLIBDIR__ "nyanWipeLib2012D.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanDirectXLib2012D.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nnnUtilLib2012D.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nnnMiniGameLib2012D.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nnnLib2012D.lib")
#else
	#pragma comment(lib,__TINYANLIBDIR__ "nyanLib2012.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanGraphicsLib2012.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanPictureLib2012.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanGeoLib2012.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanEffectLib2012.lib")

	#pragma comment(lib,__TINYANLIBDIR__ "nyanEffectNaturalLib2012.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanEffectCharaLib2012.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanEffectSpecialLib2012.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanEffectScreenLib2012.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanEffectWipeLib2012.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanEffectGeoLib2012.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanEffectTransformLib2012.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanEffectMoveLib2012.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanEffectAnimeLib2012.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanEffectEtcLib2012.lib")

	#pragma comment(lib,__TINYANLIBDIR__ "nyanWipeLib2012.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nyanDirectXLib2012.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nnnUtilLib2012.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nnnMiniGameLib2012.lib")
	#pragma comment(lib,__TINYANLIBDIR__ "nnnLib2012.lib")

#endif




#pragma comment(lib,"rpcrt4.lib")





#if defined _DEBUG
#pragma comment(lib,"libogg_static_d.lib")
#pragma comment(lib,"libvorbis_static_d.lib")
#else
#pragma comment(lib,"libogg_static.lib")
#pragma comment(lib,"libvorbis_static.lib")

#endif

#if !defined __LIBPNGDIR__
#define __LIBPNGDIR__ "d:\\libpng\\lib\\"
#endif


#if !defined _DEBUG
#pragma comment(lib,__LIBPNGDIR__ "zlib.lib")
#pragma comment(lib,__LIBPNGDIR__ "libpng.lib")

#else
#pragma comment(lib,__LIBPNGDIR__ "zlibd.lib")
#pragma comment(lib,__LIBPNGDIR__ "libpngd.lib")

#endif





#pragma comment(lib,"Strmiids.lib")
//#pragma comment(lib,"xp32_strmbasd_d.lib")

#endif
/*_*/

