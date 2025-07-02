/*
SomeTerminalGame Extensions API

===========================================

This file includes public function
definitions for stg.extension.api.dll.
*/
#include <stdbool.h>
#include <guiddef.h>
#include "stg.core.api.h"
#define EXTAPI __declspec(dllexport)

typedef _no_return_ (*ExtensionFunctionRoutinePtr)( sint reason );
typedef _no_return_ (*ExtensionFunctionInitRoutinePtr)( void );

typedef struct{
    char *name;
    char *description;
    bool isDisabled;
    GUID Uuid;
}EXTENSION, *PEXTENSION;

EXTAPI
_return_int_
Print(
    PEXTENSION sender,
    ccharp format,
    ...
);

EXTAPI
_no_return_
RegisterExtension(
    PEXTENSION Extension,
    char *name,
    char *description
);

EXTAPI
_no_return_
Unload(
    PEXTENSION extension,
    ExtensionFunctionRoutinePtr Unloader,
    sint reason
);

EXTAPI
_return_bool_
SetDebug(
    bool new
);

EXTAPI
_no_return_
RunTestExtension(
    void
);
