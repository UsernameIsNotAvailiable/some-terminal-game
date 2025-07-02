
/////////////////////////////////////
//       Some_Terminal_Game        //
//  lib/handle/debug/etc/error.h   //
//                                 //
/////////////////////////////////////

//preproccesor
#ifndef ERROR_CODES_HEADER
#define ERROR_CODES_HEADER
#pragma message("===> Building file "__FILE__)

/*      ERROR NAME                          CODE       */
#define __HELPER_SEEK_FAILURE               0x000000001 //helper is deprecated why is this here??
#define __UNKNOWN_FLAG                      0x000000002
#define __DEBUG_FORCE_FATAL                 0x000000003
#define __RUNTIME_TEMP_ERROR                0x000000004
#define __INVALID_STRING_LENGTH             0x000000005
#define __VALUE_CHANGE_FAILURE              0x000000006
#define __INVALID_BOOLEAN                   0x000000007
#define __FILE_VERIF_FAILURE                0x000000008
#define __OUT_OF_MEMORY                     0x000000009
#define __UNKNOWN_ERROR                     0x00000000A
#define __HELPER_RESPONSE_FAILURE           0x00000000B
#define __UNEXPECTED_TERMINATION            0x00000000C
#define __BAD_ARGUMENT                      0x00000000D
#define __BAD_ARGUMENT_COUNT                0x00000000E
#define __BAD_TYPE                          0x00000000F
#define __BUFFER_LIMIT_EXCEED               0x000000010

#define __SEGMENT_VIOLATION                 0x000000012 // THE MOST COMMON ERROR 😭😭😭

#define __ABORT_PROCESS                     0x000000013
#define __ILLEGAL_OPERATION                 0x000000014
#define __STACK_FLOOD_FAILURE               0x000000015
#define __FLOATING_POINT_EXCEPTION          0x000000016
#define __PREFERENCES_SEEK_FAILURE          0x000000017
#define __ACCESS_DENIED                     0x000000018
#define __STACK_DATA_NOT_SYNCING            0x000000019
#define __PROCESS_HANDLE_FAILURE            0x00000001A
#define __PARSE_FAILURE                     0x00000001B
#define __RUNAS_INVALID_USER                0x00000001C
#define __EXCEPTION_HANDLER_REPEAT          0x00000001D
#define __NULL_RETURN_VALUE                 0x00000001E
#define __SEGMENT_VIOLATION_CAUGHT          0x00000001F
#define __MEMORY                            0x000000020
#define __MEMORY_ALLOCATION_FAILURE         0x000000021
#define __BAD_INSTALLATION                  0x000000022
#define __NOT_FOUND                         0x000000023
#define __HELPER_CREATION_FAILURE           0x000000024
#define __INVALID_PARAMATER                 0x000000025
#define __TIMEOUT                           0x000000027
#define __WAIT_FAILURE                      0x000000028
#define __ATTEMPTED_USE_OF_DEPERCATED_ITEM  0x000000029
#define __UNCAUGHT_EXCEPTION                0x00000002A
#define __DLL_LOAD_FAILURE                  0x00000002B
#define __DLL_UNLOAD_FAILURE                0x00000002C
#define __REGISTRY_KEY_READ_FAILURE         0x00000002D
#define __REGISTRY_KEY_WRITE_FAILURE        0x00000002E
#define __REGISTRY_VALUE_READ_FAILURE       0x00000002F
#define __REGISTRY_VALUE_WRITE_FAILURE      0x000000030
#define __SIZE_QUERY_FAILURE                0x000000031
#define __EVENT_NOT_FOUND                   0x000000032
#define __DANGLING_POINTER                  0x000000033
#define __ARRAY_BOUNDS_EXCEEDED             0x000000033
#define __LUA                               0x000000034
#define __STACK_OVERFLOW                    0x000000035
#define __REGISTRY_BAD_CONFIGURATION        0x000000036
#define __PROTECTED_FUNCTION_BAD_RETURN     0x000000037
#define __MUTEX_ABANDONED                   0x000000038
#define __MUTEX_WAIT_FAILED                 0x000000039

/* errors of all time 🔥🔥😭😭💀💀                */ 
#define __FUCK_YOU                          0x000694201
#define __KILL_YOURSELF                     0x000694202
#define __ERROR_NO_BITCHES                  0x000694203
#define __I_AM_ON_METHAMPHETMINE            0x000694204
#define __YOU_WATCHED_SKIBIDI_TOILET        0x000694205
#define __FORTNITE_FUNNY_MOMENTS            0x000694206
#define __BRUH_MOMENT                       0x000694207
#define __VIBE_CHECK                        0x000694208
#define __BRM5_HITREG_MOMENT                0x000694209
#define __NOT_ALLOWED                       0x000694210

#endif