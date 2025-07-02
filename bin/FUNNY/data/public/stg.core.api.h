
/////////////////////////////////////
//       Some_Terminal_Game        //
//       bin/stg.core.api.h        //
//                                 //
/////////////////////////////////////
//Public header for stg.core.api.dll functions


#ifndef _SOMETERMINALGAME_CORE_API
#define _SOMETERMINALGAME_CORE_API
#define STGAPI __declspec(dllexport)
#define MAX_PATH  260
#include <stdbool.h>
#include <guiddef.h>

typedef char* pchar;
typedef unsigned int uint;
typedef signed int sint;
typedef const char* ccharp;

typedef struct{
    char NtPath[MAX_PATH];
    char GuidPath[MAX_PATH];
    char DosPath[MAX_PATH];
    char Std[MAX_PATH];
    char NonePath[MAX_PATH];
}FilePaths,*pFilePaths;

#define _return_bool_ bool
#define _return_sint_ signed int
#define _return_uint_ uint
#define _return_int_ int
#define _return_char_ char
#define _return_pchar_ char*
#define _return_slong_ signed long
#define _return_ulong_ unsigned long
#define _no_return_ void



/*
Returns the provided file
in the following path formats:
NT Object, Volume GUID, DOS,
Standard, & None. Returns false
if failed.
*/
STGAPI
_return_bool_
GetAllFilePaths(
    const char *fileName,
    pFilePaths paths
);


/*
Prints the error recived from
GetLastError(). If GetLastError() returns ERROR_SUCCESS
an error message will not be shown unless ShowDllMessage
is set to true.
*/
STGAPI
_return_bool_ 
PrintLastError( 
    bool ShowDllMessage
);

/*
Displays a message box containing
the last error.
*/
STGAPI
_no_return_ 
DisplayLastErrorInBox( 
    void 
);

/*
Same thing as DisplayLastErorInBox
but uses MessageBoxA() instead of
ShellMessageBoxA()
*/
STGAPI
_no_return_
DisplayLastErrorInBoxLegacy( 
    void 
);

/*
Returns a GUID / UUID
*/
STGAPI
_no_return_
GetUuid(
    UUID* uuid
);

/*
Compares two UUID's to check if they
are the same. If they are the same
the function retruns true, if not;
false is returned.
*/
STGAPI
_return_bool_
CompareUuid(
    UUID *uuid1,
    UUID *uuid2
);

#endif //_SOMETERMINALGAME_API