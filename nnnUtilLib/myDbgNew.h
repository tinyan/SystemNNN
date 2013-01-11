/* MyDbgNew.h
/* Defines global operator new to allocate from
/* client blocks
*/ 


#include <stdlib.h>
#include <crtdbg.h>

#if defined _DEBUG

#define MYDEBUG_NEW   new( _NORMAL_BLOCK, __FILE__, __LINE__)
       // Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
       //allocations to be of _CLIENT_BLOCK type
#else
#define MYDEBUG_NEW
#endif // _DEBUG


