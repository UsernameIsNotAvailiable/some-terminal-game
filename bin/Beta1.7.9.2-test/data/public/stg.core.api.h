
/////////////////////////////////////
//       Some_Terminal_Game        //
//       bin/stg.core.api.h        //
//                                 //
/////////////////////////////////////
//Public header for stg.core.api.dll functions


#ifndef _SOMETERMINALGAME_API
#define _SOMETERMINALGAME_API


typedef int BOOL;
#define STGAPI __declspec(dllexport)
#define _return_bool_ BOOL
#define _return_sint_ signed int
#define _return_uint unsigned int
#define _return_int int
#define _return_char_ char
#define _return_pchar_ char*
#define _return_slong_ signed long
#define _return_ulong_ unsigned long
#define _no_return_ void



/*
Prints the error recived from
GetLastError(). If GetLastError() returns ERROR_SUCCESS
an error message will not be shown unless ShowDllMessage
is set to true.
*/
STGAPI
_return_bool_ 
PrintLastError( 
    BOOL ShowDllMessage
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

#endif //_SOMETERMINALGAME_API