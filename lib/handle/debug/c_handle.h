
/////////////////////////////////////
//       Some_Terminal_Game        //
//   lib/handle/debug/c_handle.h   //
//                                 //
/////////////////////////////////////

//preprocessor

#ifndef ERR_HANDLE
#define ERR_HANDLE
#pragma message("===> Building file "__FILE__)
#define _stack_ addStack(__FUNCTION__)

#define __TERM_SIGNAL 0x1
#define __TERM_USER_INITIATED 0x2
#define __TERM_INTURRUPT 0x3
#define __TERM_ONCRASH 0x4

#define COLOR_RED 4
#define COLOR_BLUE 3
#define COLOR_PINK 01
#define COLOR_GREEN 2
#define COLOR_YELLOW 6
#define COLOR_PURPLE 5
#define COLOR_WHITE 00

#define _START_ARGS_ERROR 0x01F8
#define _START_ARGS_ALL 0x01F7
#define _START_ARGS_DEBUG 0x1F6
#define _START_ARGS_FAST 0x01F5
#define _START_ARGS_NONE 0x01F4

#define _DIR_PROGRAM_DATA ".\\data\\app\\"
#define _DIR_RESOURCES ".\\data\\app\\resources\\"
#define _DIR_AUDIO ".\\data\\app\\resources\\sfx\\"
#define _DIR_LOG ".\\data\\logs\\"
#define _DIR_DATA ".\\data\\"
#define _DIR_CRASH ".\\data\\crash"

#define _FILE_HELPER ".\\helper.exe"
#define _FILE_PREFERENCES ".\\data\\preferences"
#define _FILE_DEBUG_LOG ".\\data\\logs\\Debug.log"
#define _FILE_FATAL_LOG ".\\data\\crash\\FATAL.log"
#define _FILE_MEMORY_DUMP ".\\data\\crash\\memory.dmp"
#define _FILE_DUMPSTACK ".\\data\\crash\\DumpStack"
#define _FILE_TEMP ".\\data\\app\\RUNTIME.temp"

#define _SFX_MAINMENU "mainmenu.wav"

#define _FILE_EXIST 00
#define _FILE_WRITE 02
#define _FILE_READ 03

//includes
#include <Windows.h>
#include <Psapi.h>
#include <DbgHelp.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <errno.h>
#include "../../game/resources.h"
#include "../../game/struct.h"
#include "etc/error.h"
#include "../../external/compile_time.h"
#include "../../game/hook.h"

struct fatal_data{
    int repeatCount;
    int maxRepeatCount;
    char original_readable[120];
    int original_errcode;
    int refid;
    bool AlreadyCreatedRefID;
    bool FatalCalledMoreThanOnce;
    bool AlreadySetOriginalData;
    bool AlreadyLogged;
    bool FileSystemFailure;
};

struct fatal_data data = {
    0,
    15,
    "data.original_readable not set",
    0,
    0,
    false,
    false,
    false,
    false,
    false
};

typedef struct{
    int *returnAddr;
    int *returnAddrOfReturn;
    int *nextInstructionAddr;
}fatal_info;

fatal_info info={
    0,
    0,
    0
};

extern HANDLE htMain;
refferal_id _refid;
char err_etc[120];
int errcode_etc;
bool ForceDumpWrite = false;
bool showDumpStatus = false;
extern stack_data stackd;
extern char stack[1024][256];
extern session_informaton sessiond;
extern external_settings settings;
extern _fatal_paramaters _fparam;
extern HookRoot hCrash;
extern DWORD mainThreadId;
extern char protectedFunctions[50][50];
char *WinGetLastErrorAsString();

/*
Alternative to HANLDE_fatal (__impl_HANDLE_fatal).

*** THREAD SAFE ***
*/
#define _panic2(msg) __impl_panic(__FUNCTION__,GetCurrentThreadId(),strip_to_last_slash(__FILE__),__LINE__,msg)
#define _panic() __impl_panic(__FUNCTION__,GetCurrentThreadId(),strip_to_last_slash(__FILE__),__LINE__,"")

no_return void __impl_panic(char *func,DWORD faultingThread,char *file,int line,char *errmsg){
    _stack_;
    printf("\n");
    if(strlen(errmsg) > 1){
        printf("panic: macro _panic2() ==> __impl_panic()\n");
    } else {
        printf("panic: macro _panic() ==> __impl_panic()\n");
    }

    printf("\n");
    printf("panic: __impl_panic() was called.\n");
    printf("panic: Exception information = [\n");
    if(strlen(errmsg) > 1){
        printf("panic:         error message:      %s\n",errmsg);
    }
    printf(
        "panic:         faulting thread:    %d\n"
        "panic:         faulting function:  %s\n"
        "panic:         source file:        %s\n"
        "panic:         source line:        %d\n"
        "panic:         last error:         0x%09X\n"
        "panic:         errno:              %d\n"
        "panic: ]",faultingThread,func,file,line,GetLastError(),errno
    );
    showcursor();
    exit(GetLastError());
}

/*
Thread safe HANDLE_fatal

*/

/*
Used to notify the user of a major problem.

*/

#define HANDLE_fatal(read,err) __impl_HANDLE_fatal(read,err,__FUNCTION__,strip_to_last_slash(__FILE__),__LINE__)
no_return void __impl_HANDLE_fatal(char readable[120], int errcode,char *faultingFunction,char *file,int line) {
#ifdef USE_PANIC_NOT_FATAL
    __impl_panic(faultingFunction,GetCurrentThreadId(),file,line,readable);
    return;
#endif
    _stack_;
    bp_check(__FUNCTION__);
    SetThreadPriority(htMain,THREAD_PRIORITY_TIME_CRITICAL);
    SwitchToThread();
    //is this being called from the main thread?
    if(GetCurrentThreadId() != sessiond.mainThreadId){
        printf("unable to handle threads (except main) calling "__FUNCTION__"()\n");
        printf("redirecting function "__FUNCTION__"() ==> __impl_panic()\n");
       __impl_panic(faultingFunction,GetCurrentThreadId(),file,line,readable);
    }

    if(settings.IgnoreErrors && data.repeatCount==0){
        printf("\nSomeTerminalGame ran into a fatal error.\n");
        printf("However, you have chosen to ignore errors.\n");
        bool c = confirm("Would you like to ignore this error? (Possible crash)");
        if(c){
            return;
        }
    }
    if(!data.AlreadySetOriginalData){
        strcpy(data.original_readable, readable);
        data.original_errcode = errcode;
        data.AlreadySetOriginalData = true;
    }
    info.returnAddr = _ReturnAddress();
    info.nextInstructionAddr = _AddressOfNextInstruction();
    info.returnAddrOfReturn = _AddressOfReturnAddress();
    if(data.FatalCalledMoreThanOnce){
        if(settings.LogFileExist){
            ETC_file(_FILE_DEBUG_LOG,"FunctionCall:void:HANDLE_fatal() failed for an unknown reason. Using FunctionCall:void:HANDLE_fallback_fatal()","a","ERROR");
        }
       no_return void HANDLE_fallback_fatal();
       HANDLE_fallback_fatal(readable, errcode);
    }

    data.repeatCount += 1;
    if(data.repeatCount >= data.maxRepeatCount){
        if(data.AlreadySetOriginalData){
            strcpy(err_etc, readable);
            errcode_etc = errcode;
        }
        data.FatalCalledMoreThanOnce = true;
    }

    //hCrash.Fire(&hCrash);
    system("cls");
    system("color 0c");
    char ch;

    if(!data.AlreadyCreatedRefID){
        refid(&_refid);
    }
    //logging
    if(!data.AlreadyLogged){
        haltStack(false);
        FILE *ffl;
        ffl = fopen(_FILE_FATAL_LOG, "a");
        fprintf(ffl, "Fatal error initiated with reason of: %s (0x%09X).\n      Technical information: %u : 0x%p : 0x%p : 0x%p\n", readable, errcode, GetCurrentProcessId(),info.nextInstructionAddr, info.returnAddrOfReturn, info.returnAddr);
        fprintf(ffl, "      Refferal ID: %d-%d-%d\n", _refid.start_args, _refid.pid, _refid.random_num);
        fclose(ffl);
        CreateMemoryDump(MiniDumpNormal);
    }


    if(settings.LogFileExist && !data.AlreadyLogged){
        ETC_file(_FILE_DEBUG_LOG,"Fatal error initated. See FATAL.log for more information.","a","FATAL");
    }
    data.AlreadyLogged = true;

    dumpStackToFile(ForceDumpWrite);
    int build;
    srand(UNIX_TIMESTAMP);
    build = rand() * 2;
    //beeper
    //printf("SomeTerminalGame build 0x0%X - Compiled %s (%d unix time)\n",build,__TIMESTAMP__,UNIX_TIMESTAMP);

    bool protected = false;
    for(int i = 0; i < sizeof(protectedFunctions)/sizeof(protectedFunctions[0]); i++){
        if(strcmp(faultingFunction,protectedFunctions[i])==0){
            protected = true;
        }
    }

    if(protected){
        printf("Whoops! It appears a fatal backend error has occurred at <protected>%s/%s().%d\n",file,faultingFunction,line);
    } else {
        printf("Whoops! It appears a fatal backend error has occurred at %s/%s().%d\n",file,faultingFunction,line);
    }
    printf("\n  STOP: %s (0x%09X)", readable, errcode);
    if(_fparam.show){
        printf("\n  PARAMATER(S): ");
        for(int i = 0; i < _fparam.ParamCnt; i++){
            printf("%s     ", _fparam.Paramaters[i]);
        }
    }
    printf("\n\nWe're sorry about this! Please report this issue to me. If you\n");
    printf("have seen this screen multiple times, download a newer version.\n");
    printf("If you decide to report this error, please use the generated\n");
    printf("refferal ID: %d-%d-%d\n\n", _refid.start_args, _refid.pid, _refid.random_num);

    OnCrashErrInfo(info);
    if(showDumpStatus){
        printf("\n");
        dumpStack();
    }
    printf("\nPRESS [SPACE] TO EXIT OR PRESS [V] TO SHOW / HIDE THE STACK DUMP\n");
    while(1) {
        if(kbhit) {
            ch = getch();
            if((int)ch == 32){
                //FILE *ffl;
                //ffl = fopen(_FILE_FATAL_LOG, "a");
                //fprintf(ffl, "Fatal exit for %s",sessiond._verinfo);
                //fclose(ffl);
                char *temp3 = malloc(256);
                sprintf(temp3,"Fatal exit for %s located at %s\n",sessiond._verinfo,sessiond._installation_path_);
                if(settings.LogFileExist){
                    ETC_file(_FILE_DEBUG_LOG,temp3,"a","EXIT");
                }
                printf("Fatal exit for %s located at %s\n",sessiond._verinfo,sessiond._installation_path_);
                WriteThreadRegisters();
                printf("base address: 0x%p\n",sessiond.baseAddress);
                exit(errcode);
            }
            if(ch == 'v'){
                if(showDumpStatus){
                    showDumpStatus = false;
                } else {
                    showDumpStatus = true;
                }
                HANDLE_fatal(readable, errcode);
            }
        }
    }
}

no_return void HANDLE_fallback_fatal(char msg[120], int code){
    bp_check(__FUNCTION__);
    haltStack(true);
    _stack_;

    if(!data.AlreadyCreatedRefID){
        refid(&_refid);
    }

    FILE *flf;
    flf = fopen(_FILE_FATAL_LOG,"a");
    data.FileSystemFailure = true;
    fclose(flf);
    fprintf(flf, "FATAL FALLBACK: Max repeat count exceeded: Repeat count: %d. Max: %d: Fatal error initiated with reason of: %s (%09X)\n", data.repeatCount, data.maxRepeatCount, msg, code);
    fclose(flf);

    system("cls");
    printf("FATAL ERROR SCREEN FALLBACK\n");
    printf("--------------------------------------\n\n");
    if(data.original_errcode == code){
        printf("    STOP: %s (0x%09X)\n\n", msg, code);
    } else {
        printf("    STOP: %s (0x%09X)\n", data.original_readable, data.original_errcode);
        printf("    STOP: %s (0x%09X)\n\n", msg, code);
    }
    printf("If you have reached this screen that means something\n");
    printf("has gone seriously wrong. This screen usually appears\n");
    printf("when FunctionCall:void:HANDLE_fatal repeats more than once.\n\n");
    if(data.FileSystemFailure){
        HANDLE_errormessage("Failed to write FATAL.log.", __ACCESS_DENIED);
    }
    OnCrashErrInfo(info);
    haltStack(false);
    dumpStack();
    dumpStackToFile(true);
    printf("\nAUTO CLOSE IN 5 SECONDS\n");
    sleep(5000);
    exit(code);
}

void DisableFlowInturrupts(){
    _stack_;
    _check_bp;
    settings.AllowPowerout = false;
    settings.AllowRegistry = false;
    return;
}


void SetFatalParamater(char content[256]){
    _stack_;
    bp_check(__FUNCTION__);
    if(!_fparam.show){
        _fparam.show=true;
    }
    strcpy(_fparam.Paramaters[_fparam.ParamCnt],content);
    _fparam.ParamCnt += 1;
    return;
}

int NotifyUnhandledException(LPEXCEPTION_POINTERS except){
    char addressBuffer[256];
    char codeBuffer[256];
    sprintf(addressBuffer,"0x%p",except->ExceptionRecord->ExceptionAddress);
    sprintf(codeBuffer,"0x%09X",except->ExceptionRecord->ExceptionCode);
    SetFatalParamater(addressBuffer);
    SetFatalParamater(codeBuffer);
    HANDLE_fatal("UNCAUGHT_EXCEPTION",__UNCAUGHT_EXCEPTION);
    return 0;
}

int HANDLE_private_errormessage(char msg[120], int err_code, ...){
    bp_check(__FUNCTION__);
    if(!settings.isDebug){
        //the user is not in debug mode so we don't want to show them
        //private internal errors
        return 1;
    }
    _stack_;
    printf("[ PRIVATE INTERNAL ERROR (0x%09X) ] %s\n", err_code, msg);
    if(settings.LogFileExist){
        ETC_file("Debug.log",msg,"a", "PRIVATE_ERROR");
    }
    _sleep(50);
    return 0;
}

int notify_exception_handler_entry(const char exception_handler[120]){
    printf("Exception handler entry: %s", exception_handler);
    return 0;
}

int __impl_HANDLE_errormessage(const char *msg , int err_code,int line,const char *func,const char *file) {
    bp_check(__FUNCTION__);
    _stack_;
    if(settings.LogFileExist){
        ETC_file("Debug.log",msg, "a","ERROR");
    }
    printf("[ ERROR (0x%09X) ] %s\n", err_code,msg);
    printf("\tat %s/%s().%d (thread %d)\n\n",file,func,line,GetCurrentThreadId());
    return 0;
}

bool queryFile(_file *fil){
    _stack_;

    //exists?
    if(access(fil->path, _FILE_EXIST) == 0){
        fil->exists = true;
    } else {
        fil->exists = false;
        return false;
    }

    return true;
}

int verify_installation(){
    _stack_;
    _file file[20];
    
    //directories
    file[0].directory=true;
    strcpy(file[0].path,_DIR_DATA);
    
    file[1].directory=true;
    strcpy(file[1].path, _DIR_PROGRAM_DATA);

    file[2].directory=true;
    strcpy(file[2].path,_DIR_RESOURCES);

    file[3].directory=true;
    strcpy(file[3].path,_DIR_AUDIO);

    file[4].directory=true;
    strcpy(file[4].path,_DIR_CRASH);

    file[5].directory=true;
    strcpy(file[5].path,_DIR_LOG);

    //verify
    bool bad = false;
    int index = 0;
    for(int i = 0; i < 5; i++){
        if(!queryFile(&file[i])){
            bad = true;
            break;
        }
    }
    if(bad){
        SetFatalParamater(file[index].path);
        HANDLE_fatal("BAD_INSTALLATION",__BAD_INSTALLATION);
    }
    return 0;
}

inline int HANDLE_notice(char msg[256], ...) {
    bp_check(__FUNCTION__);
    _stack_;
    printf("[ INTERNAL NOTICE ] %s\n", msg);
    return 0;
}

inline int HANDLE_warn(char msg[256], ...) {
    bp_check(__FUNCTION__);
    _stack_;
    printf("[ WARNING ] %s\n", msg);
    return 0;
}

inline int HANDLE_earlymsg(const char *msg, ...){
    bp_check(__FUNCTION__);
    _stack_;
    va_list args;
    va_start(args,msg);
    printf("::[early] ");
    int r = vprintf(msg,args);
    va_end(args);
    sleep(10);
    return 0;
}

inline int HANDLE_debugmsg(char msg[256], ...) {
    bp_check(__FUNCTION__);
    _stack_;
    va_list args;
    va_start(args,msg);
    printf("debug: ");
    int r = vprintf(msg,args);
    printf("\n");
    va_end(args);
    sleep(10);
    return 0;
}

//this is now deprecated and is a wrapper for ETC_file2
int ETC_file(char file_name[50], char msg[500], char mode[2], char type[20]){

    ETC_file2(file_name,mode,type,msg);
    return 0;
}

//the file suit to simplify this stuff
#define debugLog(type,msg,...) ETC_file2(_FILE_DEBUG_LOG,"a",type,msg,__VA_ARGS__)

//soo better
int ETC_file2(char file_name[50],char mode[2],char type[20],char msg[500],...){
    bp_check(__FUNCTION__);
    _stack_;
    if(!settings.LogFileExist){
        return 1;
    }
    if(strlen(file_name) == 0){
        HANDLE_errormessage("Variable:Char:file_name invalid file length in FunctionCall:int:ETC_file()", __INVALID_STRING_LENGTH);
        return 1;
    }
    if(strlen(msg) == 0){
        HANDLE_errormessage("Variable:Char:msg invalid message length in FunctionCall:int:ETC_file()", __INVALID_STRING_LENGTH);
        return 1;
    }
    if(strlen(mode) == 0){
        HANDLE_errormessage("Variable:Char:mode invalid message length in FunctionCall:int:ETC_file()", __INVALID_STRING_LENGTH);
        return 1;
    }
    if(strlen(type) == 0){
        HANDLE_errormessage("Variable:Char:type invalid message length in FunctionCall:int:ETC_file()", __INVALID_STRING_LENGTH);
        return 1;
    }
    FILE *ftr; //declare file
    ftr = fopen(file_name, mode); //create the file with char mode[2]
    if(ftr == NULL){
        SetFatalParamater(file_name);
        SetFatalParamater(mode);
        HANDLE_fatal("ACCESS_DENIED",__ACCESS_DENIED);
    }
    //message stuff
    va_list args;
    va_start(args,msg);
    char *messageText = (char*)malloc(256);
    vsprintf(messageText,msg,args);

    //stupid time & type stuff
    time_t t  = time(NULL);
    struct tm tm = *localtime(&t);
    char *timeAndTypeInfo = (char*)malloc(256);
    sprintf(timeAndTypeInfo, "%d/%d/%d %02d:%02d:%02d[logT:%s]", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec, type); //month : day : year : hour : minute : seconds : type : msg

    //write to file
    fprintf(ftr,"%s:\t%s\n",timeAndTypeInfo,messageText);

    //free stuff or something yeah
    free(messageText);
    free(timeAndTypeInfo);
    fclose(ftr);
    return 0;
}

int WinErrorMessageBox(){
    if(GetLastError() == 0){
        return 0;
    }
    char messageBuffer[256];
    FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL,GetLastError(),MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPSTR)&messageBuffer,256,NULL);
    ShellMessageBoxA(NULL,NULL,messageBuffer,"STG/Error",MB_OK | MB_ICONWARNING);
    return 0;
}


char *WinGetLastErrorAsString()
{
    //Get the error message ID, if any.
    char messageBuffer[256];
    char *return_val = {0};

    //Ask Win32 to give us the string version of that message ID.
    //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
    FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL,GetLastError(),MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPSTR)&messageBuffer,256,NULL);
    
    strcpy(return_val,messageBuffer);
            
    return return_val;
}

int CreateMemoryDump(MINIDUMP_TYPE type){
    bp_check(__FUNCTION__);
    _stack_;
    HANDLE dmpFile = CreateFileA(_FILE_MEMORY_DUMP,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
    return MiniDumpWriteDump(GetCurrentProcess(),GetCurrentProcessId(),dmpFile,type,NULL,NULL,NULL);
}

int bp_check(char func[120]){
    if(strcmp(func, sessiond.bp_func) == 0){
        if(settings.isDebug){
            printf("debug: breakpoint hit: %s()\n", func);
            promptline();
        }
    }
    return 0;
}

int ShowBuiltinInformation(){
    printf("Compilation Information\n");
    printf("    __DATE__:. . . . . . . . . . . . . . . %s\n", __DATE__);
    printf("    __TIME__:. . . . . . . . . . . . . . . %s\n\n", __TIME__);
                                     
    printf("C Information:\n");      
    printf("    _MSC_VER:. . . . . . . . . . . . . . . %d\n",_MSC_VER);
    printf("    _MSC_FULL_VER: . . . . . . . . . . . . %d\n", _MSC_FULL_VER);
    printf("    _MSC_EXTENSIONS: . . . . . . . . . . . %d\n",_MSC_EXTENSIONS);
    printf("    _MSC_BUILD:. . . . . . . . . . . . . . %d\n", _MSC_BUILD);
    printf("    _MSVC_TRADITIONAL: . . . . . . . . . . %d\n", _MSVC_TRADITIONAL);
    printf("    _MSVC_EXECUTION_CHARATER_SET:. . . . . %d\n",_MSVC_EXECUTION_CHARACTER_SET);
    printf("    _WIN64:. . . . . . . . . . . . . . . . %d\n",_WIN64);
    printf("    _WIN32:. . . . . . . . . . . . . . . . %d\n",_WIN32);
    printf("    _M_AMD64:. . . . . . . . . . . . . . . %d\n",_M_AMD64);
    printf("    _M_X64:. . . . . . . . . . . . . . . . %d\n",_M_X64);
    printf("    _INTEGRAL_MAX_BITS:. . . . . . . . . . %d\n",_INTEGRAL_MAX_BITS);
    printf("    __STDC_HOSTED__: . . . . . . . . . . . %d\n",__STDC_HOSTED__);
    return 0;
}

//err handle

int Segment_Violation_Caught___RepeatCount;
BOOL exception_caught_sigsegv(){
    _stack_;
    bp_check(__FUNCTION__);
    notify_exception_handler_entry(__FUNCTION__);
    if(settings.IgnoreErrors){
        printf("\nSomeTerminalGame attempted to handle an exception.\n");
        printf("However, you have chosen to ingore errors.\n");
        bool c = confirm("Would you like to proceed? (possible crash)");
        if(c){
            return true;
        }
    }
    Segment_Violation_Caught___RepeatCount += 1;
    if(Segment_Violation_Caught___RepeatCount >= 3){
        SetFatalParamater(__FUNCTION__);
        HANDLE_fatal("EXCEPTION_HANDLER_REPEAT",__EXCEPTION_HANDLER_REPEAT);
        return false;
    }
    printf("\nException handler exit: %s: exiting caller function\n", __FUNCTION__);
    return true;
}

int Null_Return_Exception___RepeatCount;
BOOL exception_handle_null_return(char *_null_value, size_t _null_size){
    _stack_;
    bp_check(__FUNCTION__);
    notify_exception_handler_entry(__FUNCTION__);
    if(settings.IgnoreErrors){
        printf("\nSomeTerminalGame attempted to handle an exception.\n");
        printf("However, you have chosen to ingore errors.\n");
        bool c = confirm("Would you like to proceed? (possible crash)");
        if(c){
            return true;
        }
    }
    Null_Return_Exception___RepeatCount += 1;
    if(Null_Return_Exception___RepeatCount >= 3){
        SetFatalParamater(__FUNCTION__);
        HANDLE_fatal("EXCEPTION_HANDLER_REPEAT",__EXCEPTION_HANDLER_REPEAT);
        return false;
    }
    if(_null_value != NULL){
        printf("\nException handler exit: %s: value is not null\n",__FUNCTION__);
        return true;
    }
    if(_null_size <= 17){
        printf("\n");
        bool ecs = exception_caught_sigsegv();
        if(ecs){
            return 0;
        }
    }
    strcpy(_null_value, "NULL_VALUE_RESET");
    return true;
}

char *ThreadPriorityAsString(HANDLE hThread){
    int pri = GetThreadPriority(hThread);
    /*
    THREAD_PRIORITY_TIME_CRITICAL 15
    THREAD_PRIORITY_HIGHEST 2
    THREAD_PRIORITY_ABOVE_NORMAL 1
    THREAD_PRIORITY_NORMAL 0
    THREAD_PRIORITY_LOWEST -2
    THREAD_PRIORITY_IDLE -15
    THREAD_PRIORITY_ERROR_RETURN (long number or smth)
    */
   switch(pri){
    case THREAD_PRIORITY_TIME_CRITICAL:
        return "THREAD_PRIORITY_TIME_CRITICAL";
        break;

    case THREAD_PRIORITY_HIGHEST:
        return "THREAD_PRIORITY_HIGHEST";
        break;

    case THREAD_PRIORITY_ABOVE_NORMAL:
        return "THREAD_PRIORITY_ABOVE_NORMAL";
        break;

    case THREAD_PRIORITY_NORMAL:
        return "THREAD_PRIORITY_NORMAL";
        break;

    case THREAD_PRIORITY_LOWEST:
        return "THREAD_PRIORITY_LOWEST";
        break;
    
    case THREAD_PRIORITY_IDLE:
        return "THREAD_PRIORITY_IDLE";
        break;

    case THREAD_PRIORITY_ERROR_RETURN:
        return "THREAD_PRIORITY_ERROR_RETURN";
        break;

    default:
        return "UNKNOWN";
        break;
   }
    return 0;
}

int winapi_print_memory_information(DWORD pid){
    _stack_;
    bp_check(__FUNCTION__);
    HANDLE hProcess;
    PROCESS_MEMORY_COUNTERS pmc;
    MEMORYSTATUSEX status;
    APP_MEMORY_INFORMATION mem;
    hProcess = OpenProcess(  PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid );

    if(hProcess == NULL){
        SetFatalParamater("PROCESS_QUERY_INFORMATION");
        SetFatalParamater("PROCESS_VM_READ");
        SetFatalParamater(__FUNCTION__);
        HANDLE_fatal("PROCESS_HANDLE_FAILURE",__PROCESS_HANDLE_FAILURE);
    }
    if( GetProcessMemoryInfo( hProcess, &pmc, sizeof(pmc) ) ){
        printf("Page Fault Count: %d\n", pmc.PageFaultCount);
        printf("Peak Working Set Size: %.2f MB\n", _to_mb(pmc.PeakWorkingSetSize) );
        printf("Working Set Size: %.2f MB\n", _to_mb(pmc.WorkingSetSize));
        printf("Quota Peak Paged Pool Usage: %.2f MB\n", _to_mb(pmc.QuotaPeakPagedPoolUsage) );
        printf("Quota Paged Pool Usage: %.2f MB\n", _to_mb(pmc.QuotaPagedPoolUsage) );
        printf("Quota Peak Non Paged Pool Usage: %.2f MB\n", _to_mb(pmc.QuotaPeakNonPagedPoolUsage) );
        printf("Quota Non Paged Pool Usage: %.2f MB\n", _to_mb(pmc.QuotaNonPagedPoolUsage) );
        printf("Page file Usage: %.2f MB\n", _to_mb(pmc.PagefileUsage) ); 
        printf("Peak Page file Usage: %.2f MB\n\n", _to_mb(pmc.PeakPagefileUsage) );
    }
    if( GetProcessInformation( hProcess, ProcessAppMemoryInfo, &mem,sizeof(APP_MEMORY_INFORMATION) ) ){
        printf("Available Commit: %llu\n",mem.AvailableCommit);
        printf("Total commit usage: %llu\n", mem.TotalCommitUsage);
        printf("Private commit usage: %llu\n",mem.PrivateCommitUsage);
        printf("Peak private commit usage: %llu\n\n", mem.PeakPrivateCommitUsage);
    }

    CloseHandle(hProcess);
    return 0;
}


int MEMORY_FlushWorkingSet(DWORD pid){
    addStack("MEMORY_FlushWorkigSet");
    bp_check(__FUNCTION__);
    HANDLE hProcess;
    hProcess = OpenProcess( PROCESS_SET_QUOTA | PROCESS_QUERY_INFORMATION , FALSE, pid);
    if(hProcess == NULL){
        SetFatalParamater("PROCESS_QUERY_INFORMATION");
        SetFatalParamater("PROCESS_SET_QUOTA");
        HANDLE_fatal("PROCESS_HANDLE_FAILURE",__PROCESS_HANDLE_FAILURE);
    }

    EmptyWorkingSet(hProcess);

    CloseHandle(hProcess);
    return 0;
}

void WriteContext(LPCONTEXT c){
    printf("CONTEXT FLAGS: %016X EFLAGS: %016X\n",c->ContextFlags,c->EFlags);
    printf("RAX: %016llX  RBX: %016llX  RCX: %016llX\n",c->Rax,c->Rbx,c->Rcx);
    printf("RDI: %016llX  RSI: %016llX  RBP: %016llX\n",c->Rdi,c->Rsi,c->Rbp);
    printf("RSP: %016llX  RDX: %016llX  R10: %016llX\n",c->Rsp,c->Rdx,c->R10);
    printf("R11: %016llX  R12: %016llX  R13: %016llX\n",c->R11,c->R12,c->R13);
    printf("R14: %016llX  R15: %016llX  R8:  %016llX\n",c->R14,c->R15,c->R8);
    printf("R9:  %016llX  RIP: %016llX\n\n",c->R9,c->Rip);
}

LONG WINAPI disp(LPEXCEPTION_POINTERS excep){
    WriteContext(excep->ContextRecord);
    return EXCEPTION_CONTINUE_SEARCH;
}

bool ignorefault = false;
int WriteThreadRegisters(){
    ignorefault = true;
    AddVectoredExceptionHandler(1,disp);
    int x = 0;
    int y = 5 / x;
    RemoveVectoredExceptionHandler(disp);
    ignorefault = false;
    return 0;
}

extern void *baseAddress;
LONG WINAPI ExceptionFilter(LPEXCEPTION_POINTERS excep)
{
    if(ignorefault){return EXCEPTION_CONTINUE_SEARCH;}
    //printf("Windows Exception: ");
    char exceptype[256];
    switch(excep->ExceptionRecord->ExceptionCode){
        case EXCEPTION_ACCESS_VIOLATION:
            sprintf(exceptype,"WINDOWS::EXCEPTION_ACCESS_VIOLATION");
            break;
        case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
            sprintf(exceptype,"WINDOWS::EXCEPTION_ARRAY_BOUNDS_EXCEEDED");
            break;
        case EXCEPTION_STACK_OVERFLOW:
            sprintf(exceptype,"WINDOWS::EXCEPTION_STACK_OVERFLOW");
            break;
        case EXCEPTION_BREAKPOINT:
            sprintf(exceptype,"WINDOWS::EXCEPTION_BREAKPOINT");
            break;
        case EXCEPTION_DATATYPE_MISALIGNMENT:
            sprintf(exceptype,"WINDOWS::EXCEPTION_DATATYPE_MISALIGNMENT");
            break;
        case EXCEPTION_ILLEGAL_INSTRUCTION:
            sprintf(exceptype,"WINDOWS::EXCEPTION_ILLEGAL_INSTRUCTION");
            break;

        default:
            sprintf(exceptype,"WINDOWS::UNKNOWN_ERROR");
            break;
    }
    char arg[50];
    //sprintf(arg,"0x%p",excep->ExceptionRecord->ExceptionAddress);
    SetFatalParamater(arg);
    HANDLE_fatal(exceptype,excep->ExceptionRecord->ExceptionCode);
    printf("\n\nerror: %s (0x%09X) at %p\n",exceptype,excep->ExceptionRecord->ExceptionCode,excep->ExceptionRecord->ExceptionAddress);
    WriteContext(excep->ContextRecord);
    //dumpStack();
    return EXCEPTION_EXECUTE_FAULT;
}

inline int refid(refferal_id *_target_refid){
    _stack_;
    time_t t  = time(NULL);
    struct tm tm = *localtime(&t);
    srand(time(0));

    if(sessiond.deprecated.StartArgsFetchFailure){
        _target_refid->start_args = _START_ARGS_ERROR;
        goto generate;
    }
    if(!settings.isDebug || !sessiond.skip){
        _target_refid->start_args = _START_ARGS_NONE;
        goto generate;
    }
    if(settings.isDebug && sessiond.skip){
        _target_refid->start_args = _START_ARGS_ALL;
        goto generate;
    }
    if(settings.isDebug){
        _target_refid->start_args = _START_ARGS_DEBUG;
        goto generate;
    }
    if(sessiond.skip){
        _target_refid->start_args = _START_ARGS_FAST;
        goto generate;
    }
    
    //format: <start args>-<pid>-<random numbers>
    generate:
    _target_refid->pid = GetCurrentProcessId();
    _target_refid->random_num = rand();
    return 0;
}

int OnCrashErrInfo(fatal_info fi){
    _stack_;
    bp_check(__FUNCTION__);
    printf(" %u : 0x%p : 0x%p : 0x%p\n", GetCurrentProcessId(),fi.nextInstructionAddr, fi.returnAddrOfReturn, fi.returnAddr);
    return 0;
}

long long unsigned GetMemoryOffset(void *obj, void *base){
    return (long long unsigned)obj - (long long unsigned)base;
}

int TEST_EXTERNAL__printStack(void)
{
    return 0;
}

#endif 