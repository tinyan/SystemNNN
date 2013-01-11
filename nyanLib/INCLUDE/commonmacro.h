//
// commonmacro.h
//

#if !defined __NYANLIB_COMMONMACRO__
#define __NYANLIB_COMMONMACRO__

#define DELETEARRAY(x) if ((x) != NULL) {delete [] (x); (x) = NULL;}
#define DELETECLASS(x) if ((x) != NULL) {delete (x); (x) = NULL;}
#define ENDDELETECLASS(x) if ((x) != NULL) {(x)->End(); delete (x); (x) = NULL;}
#define ENDRELEASE(x) if ((x) != NULL) {(x)->Release();(x) = NULL;}
#define DELETEGDIOBJECT(x) if ((x) != NULL) {DeleteObject(x); (x) = NULL;}


#endif
/*_*/

