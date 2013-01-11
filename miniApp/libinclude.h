#if !defined __MINIAPP_LIBINCLUDE__
#define __MINIAPP_LIBINCLUDE__



#pragma comment(lib,"winmm.lib")

#if _MSC_VER >= 1500

#if defined _DEBUG
#pragma comment(lib,"..\\..\\systemNNN\\nyanlib\\lib\\miniApp2008D.lib")
#else
#pragma comment(lib,"..\\..\\systemNNN\\nyanlib\\lib\\miniApp2008.lib")
#endif

#else

#if defined _DEBUG
#pragma comment(lib,"..\\..\\systemNNN\\nyanlib\\lib\\miniApp2005D.lib")
#else
#pragma comment(lib,"..\\..\\systemNNN\\nyanlib\\lib\\miniApp2005.lib")
#endif

#endif


#endif
/*_*/

