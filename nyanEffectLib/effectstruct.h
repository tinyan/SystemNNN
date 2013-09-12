//
// effectstruct.h
//

#if !defined __NYANEFFECTLIB_EFFECTSTRUCT__
#define __NYANEFFECTLIB_EFFECTSTRUCT__

	typedef struct _tagOLDEFFECT
	{
		BOOL flag;
		int pic;
		int command;
		RECT src;
		RECT dst;
		RECT srcFrom;
		RECT dstFrom;
		RECT srcTo;
		RECT dstTo;
		int count;
		int countMax;
		int para[16];
		BOOL notTransFlag;
		int pad[2];
	} OLDEFFECT;


	typedef struct _tagEFFECT
	{
		BOOL flag;
		int pic;
		int command;
		RECT src;
		RECT dst;
		RECT srcFrom;
		RECT dstFrom;
		RECT srcTo;
		RECT dstTo;
		int count;
		int countMax;
		int para[256-32];
		BOOL notTransFlag;
		int previousEffect;
		int pad[1];
	} EFFECT;


#endif
/*_*/


