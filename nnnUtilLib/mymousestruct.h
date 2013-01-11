//
// mymousestruct.h
//

#if !defined __TINYAN_NNNUTILLIB_MYMOUSESTRUCT__
#define __TINYAN_NNNUTILLIB_MYMOUSESTRUCT__

typedef struct _tagMYMOUSESTRUCT
{
	int mouseX,mouseY;
	BOOL trig1,trig2,trig3;
	BOOL trig1Mae,trig2Mae,trig3Mae;
	BOOL click1,click2,click3;
	int wheel;
	BOOL shiftKey;
	BOOL ctrlKey;
} MYMOUSESTRUCT, *LPMYMOUSESTRUCT;



#endif
/*_*/

