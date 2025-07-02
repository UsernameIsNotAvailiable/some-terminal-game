
/////////////////////////////////////
//       Some_Terminal_Game        //
//     bin/SomeTerminalGame.c      //
//                                 //
/////////////////////////////////////

//preprocessor

//auto link
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "./lua54.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "rpcrt4.lib")
#pragma comment(lib, "dbghelp.lib")
#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "Advapi32.lib")

//build messages
#pragma message("===> Displaying verbose build messages")
#pragma message("===> Building SomeTerminalGame on "__DATE__" at "__TIME__)
#pragma message("===> Automatically linked the following libraries:")
#pragma message("====> user32.lib")
#pragma message("====> ./lua54.lib")
#pragma message("====> shlwapi.lib")
#pragma message("====> rpcrt4.lib")
#pragma message("====> dbghelp.lib")
#pragma message("====> psapi.lib")
#pragma message("====> Advapi32.lib")
#pragma message("===> Building file "__FILE__)

#define _WIN32_WINNT 0x0505
#define KEY_DOWN 0x8000
#define _DBG_DISABLE_SIGNAL FALSE
#pragma once

#define _FILE_EXIST 00
#define _FILE_WRITE 02
#define _FILE_READ 03

#define sleep _sleep
#define __IS_TEST_BUILD FALSE
#define __IS_PRIVATE_BUILD FALSE


#define FUNCTION_REMAP(original,new)

#define _stack_ addStack(__FUNCTION__)
#define _fn_ __FUNCTION__
#define __APP_MAIN__
#define _pLine (printf("_pLine: %d\n",__LINE__))

#define HANDLE_errormessage(msg,err) __impl_HANDLE_errormessage(msg,err,__LINE__,__FUNCTION__,strip_to_last_slash(__FILE__))


//directory things
#define _DIR_PROGRAM_DATA ".\\data\\app\\"
#define _DIR_RESOURCES ".\\data\\app\\resources\\"
#define _DIR_LOG ".\\data\\logs\\"
#define _DIR_DATA ".\\data\\"
#define _DIR_CRASH ".\\data\\crash"

#define _FILE_HELPER ".\\helper.exe"
#define _FILE_DEBUG_LOG ".\\data\\logs\\Debug.log"
#define _FILE_FATAL_LOG ".\\data\\crash\\FATAL.log"
#define _FILE_MEMORY_DUMP ".\\data\\crash\\memory.dmp"
#define _FILE_DUMPSTACK ".\\data\\crash\\DumpStack"
#define _FILE_TEMP ".\\data\\app\\RUNTIME.temp"
#define _FILE_VERSION ".\\data\\VERSION"
#define _FILE_FIRSTRUN ".\\data\\app\\first_run"

#define _SFX_MAINMENU "mainmenu.wav"
//etc

#ifdef __PRIVATE_BUILD
#undef __IS_PRIVATE_BUILD
#define __IS_PRIVATE_BUILD TRUE
#endif

#ifdef __TEST_BUILD
#undef __IS_TEST_BUILD
#define __IS_TEST_BUILD TRUE
#endif

#define __PUBLIC_BUILD  FALSE
#define __TEST_BUILD    TRUE

#define _check_bp bp_check(__FUNCTION__)
#pragma intrinsic(_ReturnAddress)

#define __TERM_SIGNAL 0x1
#define __TERM_USER_INITIATED 0x2
#define __TERM_INTURRUPT 0x3
#define __TERM_ONCRASH 0x4
#define __TERM_GAME_END 0x5

#define __OVERRIDE_STARTUP_NOTICE false
#define __BUG_TRACKER_GB_COUNT 0

#define __USERID_ROOT 0
#define __USERID_SYSTEM 1
#define __USERID_STANDARD 2
#define __USERID_TEMPLATE 3
#define __USERID_LAMHU 4
#define __USERID_NULL_USER NULL

#define _EXECUTION_STD 0
#define _EXECUTION_VERBOSE 1
#define _EXECUTION_FORCE 2
#define _EXECUTION_BOTH 3

#define _EXIT_THREAD_STOP 0
#define _EXIT_THREAD_FATAL 1

//versions

/*version class standard 
    release - no class
    private - all can be child of private

    test_build
        experimental
            pre_release

    pre_release
        experimental

*/

//app
#define _APPID_MAIL 401

//devices
#define __DEV_SDA0 410
#define __DEV_SDA1 411
#define __DEV_ETHER0 412

//defines
#define attrib(x) __declspec(x)
#define no_return attrib(noreturn)

//includes
#include <Windows.h>
#include <Shlwapi.h>
#include <psapi.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <errno.h>
#include <intrin.h>
#include <sys/types.h>
#include <io.h>
#include <inttypes.h>


#include "../lib/game/secret.h"
#include "../lib/game/resources.h"
#include "../lib/menus/mainmenu.h"
#include "../lib/handle/debug/etc/error.h"
#include "../lib/handle/debug/c_handle.h"
#include "../lib/game/screen.h"
#include "../lib/game/struct.h"
#include "../lib/game/pkg/pkg.h"
#include "../lib/game/pkg/mail.h"
#include "../lib/game/pkg/rl.h"
#include "../lib/game/usrmgr.h"
#include "../lib/game/random.h"
#include "../lib/game/enemy.h"
#include "../lib/shared/TemporaryContainer.h"
#include "../lib/external/compile_time.h"
#include "../lib/handle/Registry.h"
#include "../lib/extensions/main.h"
#include "../lib/game/hook.h"
#include "../lib/game/topright.h"

#pragma message("===> Building rest of file "__FILE__)

static char protectedFunctions[50][50] = {
    "_wow"
};

#define PROTECTED(rfname) \
    int _real_protected_##rfname(const char *fname); \
    int _##rfname(void) { \
        addStack(#rfname"::protected"); \
        int ret = _real_protected_##rfname(#rfname); \
        if(ret != 0) { \
            char buffer[50]; \
            itoa(ret,buffer,10); \
            SetFatalParamater(buffer); \
            __impl_HANDLE_fatal("PROTECTED_FUNCTION_BAD_RETURN",__PROTECTED_FUNCTION_BAD_RETURN,#rfname"::protected",__FILE__,__LINE__); \
        } \
        return ret; \
    } \
    int _real_protected_##rfname(const char *fname) \

PROTECTED(protected_function_test){
    printf("protected_function_test: it work!\n");
    return 0;
}

#define STRINGIFY(x) #x
#define CONCAT(x,y) x##y
#define EVALSTRINGIFY(x) STRINGIFY(x)

void *baseAddress;
extern void *baseAddress;

int ThreadCnt = 0;
int *ThreadList[50];
char ThreadNames[50][256];
DWORD mainThreadId;

char stack[1024][256];
int *stack_addr[1024];
int symbolcnt;
bool LogFileExist = false;
bool EtherConnected = false;
bool isSuperUser = false;
bool AttemptPowerout(void);

enum FunnyThings {
    DEREFRENCE_NULL_PTR,
    INVALID_ARRAY_LOCATION,
};

//useless things


int DoSomethingFunny(enum FunnyThings funItem){
    _stack_;
    _check_bp;
    if(funItem == DEREFRENCE_NULL_PTR){
        int *funPointer = NULL;
        printf("%d",*funPointer); //derefrence null pointer to seg fault
    } else if(funItem == INVALID_ARRAY_LOCATION){
        //make an array and access an invalid value
        int *funArray = (int*)malloc(3);
        printf("%d",funArray[5]); //5 does not exist lol
    }
    return 0;
}

bool isFirstRun(){
    _stack_;
    _check_bp;
    if(access(_FILE_FIRSTRUN,F_OK) == 0){
        //exists
        return false;
    } else {
        //doesn't exist
        return true;
    }
}

dev_data _universal_dev_data_table = {
    .AllDevicesCount = 0,
    .MountedDevCount = 0,
    .TrustedDevCount = 0,
    .UnmountedDevCount = 0,
};
user_data _universal_user_data_table = {
    .SpecialUserCount = 0,
    .StandardUserCount = 0,
    .SuperUserCount = 0,
    .UserCount = 0,
};
extern user_data _universal_user_data_table;
extern dev_data _universal_dev_data_table;

//preperation n stuff
external_settings settings = {
    .isDebug=false, //isDebug
    .SomeStevenEasterEgg=false, //easter egg
    .LogFileExist=false, //log file
    .ColorSelection=COLOR_WHITE,
    .IgnoreErrors=false,
};
extern external_settings settings;

TZ_Security_System tzss = {
    .AlreadyDisplayedEnablePrompt = false,
    .enabled = false,
    .policy.ControlNetworkFlow = true,
    .policy.PreventSystemFileChanges = true,
    .policy.SystemMemoryIntegrity = true,
    .policy.UnmountInvalidDisks = true,
    .ProtectionLevel = 0
};
extern TZ_Security_System tzss;

_fatal_paramaters _fparam = {
    .ParamCnt = 0,
    .show=false,
};
extern _fatal_paramaters _fparam;

enemy_data Enemyd = {
    .isOnBreak = false,
    .isAttackAllowed = false,
    .Level = 1,
    .WL.Losses = 0,
    .WL.Wins = 0,
    .TimeAttacked = 0,
};
extern enemy_data Enemyd;


int _tzss_prompt(){
    if(tzss.AlreadyDisplayedEnablePrompt){
        return 0;
    }
    tzss.AlreadyDisplayedEnablePrompt = true;
    printf("TerminalZ Security System is disabled!\n");
    printf("We suggest you enable TZSS to keep this computer safe.\n\n");
    bool v = confirm("Would you like to enable TZSS?");
    if(!v){
        return 0;
    }
    tzss.enabled = true;
    tzss.policy.ControlNetworkFlow = true;
    tzss.policy.PreventSystemFileChanges = true;
    tzss.policy.SystemMemoryIntegrity = true;
    tzss.policy.UnmountInvalidDisks = true;
    printf("TerminalZ Security System has been enabled. You can modify it by running tzss through the command line.\n");
    return 0;
}

session_informaton sessiond = {
    false,
    false,
    0,
    __USERID_SYSTEM,
    false,
    .deprecated.StartArgsFetchFailure = false,
    .LogTemporaryContainerActions = false,
    .Level = 0,
    .remoteConnection = false,


    .SharedConstants.publicRelease = __PUBLIC_BUILD,
    .SharedConstants.testBuild = __TEST_BUILD
};
extern session_informaton sessiond;

int _fetchExecLocation(){
    _stack_;
    _check_bp;
    char path[256];
    GetModuleFileNameA(NULL, (LPSTR)path, 256);
    strcpy(sessiond._exec_path_, path);
    return 0;
}

int _fetchInstallationLocation(){
    _stack_;
    _check_bp;

    char buf[256];
    GetCurrentDirectoryA(256,(LPSTR)buf);
    strcpy(sessiond._installation_path_,buf);
    return 0;
}

void update_settings(){
    _stack_;
    settings.LogFileExist = LogFileExist;
}


void _displaySessionData(){
    _stack_;
    //strings
    printf("------------------------- STRINGS --------------------------\n");
    printf("  sessiond._version_:                         \"%s\"\n", sessiond._version_);
    printf("  sessiond._exec_path_:                       \"%s\"\n", sessiond._exec_path_);
    printf("  sessiond._installation_path_:               \"%s\"\n", sessiond._installation_path_);
    printf("  sessiond.bp_func                            \"%s\"\n\n", sessiond.bp_func);

    //int
    printf("------------------------- INTEGERS --------------------------\n");
    printf("  sessiond.SessionID:                         %d\n", sessiond.sessionID);
    printf("  sessiond.PID                                %d\n",sessiond.PID);
    printf("  sessiond.memLimit                           %llu\n", sessiond.memLimit);
    printf("  sessiond.UnixEpochTime:                     %llu\n\n",sessiond.UnixEpochTime);

    //bool
    printf("------------------------- BOOLEANS --------------------------\n");
    printf("  sessiond.SuperUserPasswordSet:              <%s>\n", btos(sessiond.SuperUserPasswordSet));
    printf("  sessiond.skip:                              <%s>\n", btos(sessiond.skip));
    printf("  sessiond.SetupCompleted:                    <%s>\n", btos(sessiond.SetupCompleted));
    printf("  sessiond.Logeed:                            <%s>\n", btos(sessiond.LoggedIn));
    printf("  sessiond.FirstRun:                          <%s>\n", btos(sessiond.FirstRun));
    printf("  sessiond.usingDebugCmd:                     <%s>\n", btos(sessiond.usingDebugCmd));
    printf("  sessiond.LogTemporaryContainerActions       <%s>\n", btos(sessiond.LogTemporaryContainerActions));
    printf("  sessiond.UseLegacyMemoryManager             <%s>\n\n", btos(sessiond.UseLegacyMemoryManager));

    printf("------------------------- POWEROFF --------------------------\n");
    printf(" sessiond.Poweroff.Chance:                    %d\n",sessiond.Poweroff.Chance);
    printf(" sessiond.Poweroff.When:                      %d\n",sessiond.Poweroff.When);
    printf(" sessiond.Poweroff.isPowerout                 <%s>\n\n",btos(sessiond.Poweroff.isPowerout));
    
    
    printf("------------------------- DEPRECATED --------------------------\n");
    printf("  sessiond.depercated.helperPID               %d\n",sessiond.deprecated.helperPID);
    printf("  sessiond.depercated.whoami_id:              %d\n", sessiond.deprecated.whoami_id);
    printf("  sessiond.depercated.StartArgsFetchFailure   <%s>\n", btos(sessiond.deprecated.StartArgsFetchFailure));
}

//init signal & handlers

void signal_sigsegv(int sig){
    if(_DBG_DISABLE_SIGNAL){
        return;
    }
    _stack_;
    if(settings.isDebug){
        HANDLE_debugmsg("Recived signal inturrupt: SIGSEGV");
    }
    if(settings.LogFileExist){
        ETC_file(_FILE_DEBUG_LOG,"Recived signal inturrupt: SIGSEGV","a","INTURRUPT");
    }
    HANDLE_fatal("SEGMENT_VIOLATION", __SEGMENT_VIOLATION); 
}

void signal_sigabrt(int sig){
    if(_DBG_DISABLE_SIGNAL){
        return;
    }
    _stack_;
    if(settings.isDebug){
        HANDLE_debugmsg("Recived signal inturrupt: SIGABRT");
    }
    if(settings.LogFileExist){
        ETC_file(_FILE_DEBUG_LOG,"Recived signal inturrupt: SIGABRT","a","INTURRUPT");
    }
    //abortion bruh
    HANDLE_fatal("ABORT_PROCESS", __ABORT_PROCESS);
}

void signal_sigill(int sig){
    if(_DBG_DISABLE_SIGNAL){
        return;
    }
    _stack_;
    if(settings.isDebug){
        HANDLE_debugmsg("Recived signal inturrupt: SIGILL");
    }
    if(settings.LogFileExist){
        ETC_file(_FILE_DEBUG_LOG,"Recived signal inturrupt: SIGILL","a","INTURRUPT");
    }
    HANDLE_fatal("ILLEGAL_INSTRUCTION", __ILLEGAL_OPERATION);
}

void signal_sigint(int sig){
    if(_DBG_DISABLE_SIGNAL){
        return;
    }
    _stack_;
    if(settings.isDebug){
        HANDLE_debugmsg("Recived signal inturrupt: SIGINT");
    }
    if(settings.LogFileExist){
        ETC_file(_FILE_DEBUG_LOG,"Recived signal inturrupt: SIGINT","a","INTURRUPT");
    }
    forceexit(__TERM_INTURRUPT);
}

void test(){
    printf("test function!\n");
    return;
}

void signal_sigterm(int sig){
    if(_DBG_DISABLE_SIGNAL){
        return;
    }
    _stack_;
    if(settings.isDebug){
        HANDLE_debugmsg("Recived signal inturrupt: SIGTERM");
    }
    if(settings.LogFileExist){
        ETC_file(_FILE_DEBUG_LOG,"Recived signal inturrupt: SIGTERM","a","INTURRUPT");
    }
    forceexit(__TERM_SIGNAL);
}

void signal_sigfpe(int sig){
    if(_DBG_DISABLE_SIGNAL){
        return;
    }
    _stack_;
    if(settings.isDebug){
        HANDLE_debugmsg("Recived signal inturrupt: SIGFPE");
    }
    if(settings.LogFileExist){
        ETC_file(_FILE_DEBUG_LOG,"Recived signal inturrupt: SIGFPE","a","INTURRUPT");
    }
    HANDLE_fatal("FLOATING_POINT_EXCEPTION", __FLOATING_POINT_EXCEPTION);
}

int signal_init(){
    if(_DBG_DISABLE_SIGNAL){
        return 0;
    }
    signal(SIGSEGV, signal_sigsegv);
    signal(SIGABRT, signal_sigabrt);
    signal(SIGABRT_COMPAT,signal_sigabrt);
    signal(SIGILL, signal_sigill);
    signal(SIGINT, signal_sigint);
    signal(SIGFPE, signal_sigfpe);
    signal(SIGBREAK, signal_sigterm);
    signal(SIGTERM, signal_sigterm);
    return 0;
}

//init etc

LPSTARTUPINFOW hsi;
LPPROCESS_INFORMATION hpi;

void init_helper(){
    HANDLE_errormessage("not launching helper.exe lol",0);
    return;
    
    _stack_;
    if(_access("helper.exe", _FILE_WRITE) != 0){
        SetFatalParamater(_FILE_HELPER);
        HANDLE_fatal("HELPER_SEEK_FAILURE", __HELPER_SEEK_FAILURE);
    }
    system("start helper.exe");
}

int _sfx_stop(){
    _stack_;
    system(".\\data\\app\\resources\\sfx\\playsound.exe s_killself");
    return 0;
}

int _sfx_play(char id[120]){
    _stack_;
    _check_bp;
    char *command = malloc(sizeof(".\\data\\app\\resources\\sfx\\playsound.exe ") + sizeof(id) + 1);
    strcpy(command, ".\\data\\app\\resources\\sfx\\playsound.exe ");
    strcat(command, id);
    system(command);
    command = NULL;
    free(command);
    return 0;
}

//init stack

stack_data stackd = {
    .maxSize = 1024,
    .warnSize = 1000,
    .stackHalted = false,
    .symbolCnt = 0,
    .addrCnt = 0,
};


bool OverrideStackHalted = false;
int addStack(char call[1024]){
    if(stackd.stackHalted && !OverrideStackHalted){
        return 1;
    }
    //is the call a DEPERCATED item?
    char *parsed = (char*)malloc(256);
    sscanf(call,"%[^_]_",parsed);
    if(strcmpi(parsed,"DEPERCATED") == 0){
        HANDLE_fatal("ATTEMPTED_USE_OF_DEPERCATED_ITEM",__ATTEMPTED_USE_OF_DEPERCATED_ITEM);
    }
    free(parsed);
    parsed = NULL;
    signal_init();
    if(stackd.symbolCnt >= stackd.warnSize){
        if(settings.isDebug){
            printf("debug: stackd.warnSize has been reached.");
        }
        flushStack();
    }
    stack_addr[stackd.addrCnt] = _ReturnAddress();
    strcpy(stack[stackd.symbolCnt], call);
    stackd.symbolCnt += 1;
    stackd.addrCnt += 1;
    if(OverrideStackHalted){
        OverrideStackHalted = false;
    }
    return 0;
}

int haltStack(bool unhalt){
    if(stackd.stackHalted){
        if(unhalt){
            stackd.stackHalted = false;
        }
        return 0;
    }
    stackd.stackHalted = true;
    return 0;
}

int flushStack(){
    signal_init();
    if(stackd.stackHalted){
        return 1;
    }
    stackd.addrCnt = 0;
    stackd.symbolCnt = 0;
    memset(stack,0,sizeof(stack));
    return 0;
}

int dumpStackToFile(bool ignorePreferences){
    _check_bp;
    _stack_;

    //verify stuff n' setting
    if(!settings.DumpstackOnCrash){
        return 0;
    }
    if(!strcmp(stack[0], "main()") == 0){
        strcpy(stack[0],"main");
    }
    if(access(_FILE_DUMPSTACK, F_OK) == 0){
        remove(_FILE_DUMPSTACK);
    }

    FILE *dsf;
    dsf = fopen(_FILE_DUMPSTACK,"a");
    fprintf(dsf,"[STACK LOCATION] -> [MEMORY LOCATION] -> [OPERATION]\n");
    for(int i = 0; i < sizeof(stack)/sizeof(stack[0]); i++){
        if(strlen(stack[i]) < 1){
            continue;
        }
        fprintf(dsf, " %03i                 0x%p   %s\n", i, stack_addr[i], stack[i]);
    }
    fclose(dsf);
    return 0;
}

int dumpStack(){
    _stack_;
    //err check
    if(!strcmp(stack[0], "main()") == 0){
        strcpy(stack[0], "main");
    }
    printf("Stack trace (most recent calls):\n");
    printf(" [STACK LOCATION] -> [MEMORY LOCATION] -> [OPERATION]\n");
    for(int i = 0; i < sizeof(stack)/sizeof(stack[0]); i++){
        if(strlen(stack[i]) < 1 ){
            continue;
        }
        printf("  %03i                 0x%p   %s\n", i,stack_addr[i],stack[i]);
    }
    return 0;
}

user root = {
    .permissions.SuperUser = true,
    .permissions.FileRead = true,
    .permissions.FileWrite = true,
    .permissions.DriveOperations = true,
    .permissions.CanChangePassword = true,
    .permissions.KernelPermissions = false,
    .permissions.CanChangeUser = true,
    .permissions.IsLoginAllowed = true,
    .permissions.CanUseUsrmgr = true,
    .permissions.CanChangeOthersPasswords = true,

    .Username = "root",
    .Password = "password_not_set",
    .HomeDir = "/root",
    .UserID = 0,
    .CurrentUser = false,
    .Active = true,
};

user SYSTEM = {
    .permissions.SuperUser = true,
    .permissions.FileRead = true,
    .permissions.DriveOperations = true,
    .permissions.FileWrite = true,
    .permissions.CanChangePassword = true,
    .permissions.KernelPermissions = true,
    .permissions.CanChangeUser = true,
    .permissions.IsLoginAllowed = false,
    .permissions.CanUseUsrmgr = true,
    .permissions.CanChangeOthersPasswords = true,

    .Username = "SYSTEM",
    .Password = "SYSTEM",
    .HomeDir = "/system/Kernel/etc/SYSTEM.profile",
    .UserID = 1,
    .CurrentUser = false,
    .Active = false,
};


user standard = {
    .permissions.FileRead = true,
    .permissions.FileWrite = true,
    .permissions.SuperUser = false,
    .permissions.DriveOperations = false,
    .permissions.KernelPermissions = false,
    .permissions.CanChangePassword = true,
    .permissions.CanChangeUser = true,
    .permissions.IsLoginAllowed = true,
    .permissions.CanUseUsrmgr = false,
    .permissions.CanChangeOthersPasswords = false,

    .Username = "username_not_set",
    .Password = "password_not_set",
    .HomeDir = "value_not_set",
    .UserID = 2,
    .CurrentUser = false,
    .Active = false,
};

user dummy = {
    .permissions.CanChangePassword = false,
    .permissions.DriveOperations = false,
    .permissions.FileRead = false,
    .permissions.FileWrite = false,
    .permissions.SuperUser = false,
    .permissions.KernelPermissions = false,
    .permissions.CanChangePassword = false,
    .permissions.IsLoginAllowed = false,
    .permissions.CanUseUsrmgr = false,
    .permissions.CanChangeOthersPasswords = false,

    .Username = "template",
    .Password = "password_not_set",
    .HomeDir = "/home/template.profile",
    .UserID = 3,
    .CurrentUser = false,
    .Active = false,
};

user LocalAccountManagerHostUser = {
    .permissions.IsLoginAllowed = true,
    .permissions.SuperUser = true,
    .permissions.CanChangeUser = true,
    .permissions.KernelPermissions = true,
    .permissions.CanUseUsrmgr = true,

    .Username = "LocalAccountManagerHostUser",
    .Password = "lamg",
    .HomeDir = "/system/kernel/system.applications/LocalAcountManagerHost/elevated_utils/user/LocalAccountManagerHostUser.profile",
    .UserID = 4,
    .CurrentUser = false,
    .Active = false,
};

user null_user = {
    .permissions.IsLoginAllowed = false,
    .UserID = NULL,
    .Username = "null_user",
    .Password = "(null)",
    .HomeDir = "/system/application_profiles/user/null.profile",
    .UserID = 5,
    .Active = false,
};

user debugee = {
    .permissions.FileRead =true,
    .permissions.FileWrite =true,
    .permissions.SuperUser = true,
    .permissions.DriveOperations = true,
    .permissions.KernelPermissions = true,
    .permissions.CanChangePassword =true,
    .permissions.CanChangeUser =true,
    .permissions.IsLoginAllowed =true,
    .permissions.CanUseUsrmgr = true,
    .permissions.CanChangeOthersPasswords = true,

    .Username = "debugee",
    .Password = "debugee",
    .HomeDir = "/system/debugee/.profile",
    .UserID = 6,
    .Active = false,
};

extern user root;
extern user SYSTEM;
extern user standard;
extern user dummy;
extern user null_user;
extern user LocalAccountManagerHostUser;
extern user debugee;

int SignOutAllUsers(){
    
    _stack_;
    SYSTEM.CurrentUser = false;
    standard.CurrentUser = false;
    root.CurrentUser = false;
    _universal_user_data_table.CurrentUser = &null_user;

    if(SYSTEM.CurrentUser || standard.CurrentUser || root.CurrentUser){
        HANDLE_errormessage("The game failed to properly change the value User:*:CurrentUser to false in FunctionCall:BOOL:SignOutAllUsers()", __VALUE_CHANGE_FAILURE);
        return false;
    } else {
        return true;
    }
}

int ChangeUserPassword(user *_user, user *_target, char password[120], bool Force){
    _stack_;
    char *auth;
    char *new;
    if(_user->permissions.CanChangePassword || _user->permissions.SuperUser){
        if(Force){
            strcpy(_target->Password, password);
            printf("-psswd: successfully changed password\n");
            return 0;
        }
        if(_user->UserID != _target->UserID){
            if(!_user->permissions.SuperUser){
                printf("-psswd: cannot change password of other user: access denied\n");
                return 1;
            } else if(_user->permissions.SuperUser) {
                auth = get_password("Current password: ");
                if(strcmp(_user->Password, auth) == 0){
                    new = get_password("New password: ");
                    strcpy(_target->Password, new);
                    printf("-psswd: successfully changed password\n");
                    return 0;
                }
            }
        } else if(_user->UserID == _target->UserID){
            auth = get_password("Current password: ");
            if(strcmp(auth, _user->Password) == 0){
                new = get_password("New password: ");
                strcpy(_target->Password, new);
                printf("-psswd: successfully changed password\n");
                return 0;
            }
        }
    } else {
        printf("-psswd: access denied\n");
        return 1;
    }
    return 0;
}

int GetCurrentUserByUserID(bool printResult){
    _stack_;
    if(root.CurrentUser){
        if(printResult){
            printf("-/usr/sys/bin/getCurrentUserByID: %d\n", root.UserID);
        }
        return root.UserID;
    } else if(SYSTEM.CurrentUser){
        if(printResult){
            printf("-/usr/sys/bin/getCurrentUserByID: %d\n", SYSTEM.UserID);
        }
        return SYSTEM.UserID;
    } else if(standard.CurrentUser){
        if(printResult){
            printf("-/usr/sys/bin/getCurrentUserByID: %d\n", standard.UserID);
        }
        return standard.UserID;
    } else {
        if(printResult){
            printf("-/usr/sys/bin/getCurrentUserByID: no current user\n");
        }
        return 1;
    }
}


network netMain = {
    "netMain", 
    "default", 
    "WPA2", 
    3, 
    true, 
    true,
    true,
};
device TerminalZ = {
    "TerminalZ",
    __HWID_DISK0,
    "sda0",
    "/dev/sda0",
    "SSD",
    0,
    true,
    true,
    true,
    true,
    true,
    false,
};

device djt = {
    "DONALD TRUMP",
    __HWID_DJT,
    "2024",
    "/dev/sda3",
    "DJT",
    0,
    true,
    true,
    false,
    true,
    false,
    true,
};

device secret_credits = {
    "SECRET CREDITS",
    __HWID_SECRET_CREDITS,
    "secret"
    "/system/devices/secret/credits",
    "SYS",
    0,
    true,
    true,
    false,
    true,
    false,
    true,
};

device USB = {
    "USBSTORAGEDEVICE0",
    __HWID_USB0,
    "sda1",
    "/dev/sda1",
    "USB",
    0,
    true,
    false,
    false,
    false,
    false,
    false,
};
device ethernet = {
    "Ethernet Connection",
    __HWID_ETHER0,
    "ether0",
    "/dev/ethr0",
    "ETHERNET",
    0,
    false,
    true,
    true,
    false,
    false,
    false,
};
extern device USB;
extern device TerminalZ;
extern device ethernet;
extern device djt;
extern device secret_credits;

//*universal data tables

int _backend_SwapCurrentUser(user _target){
    _check_bp;
    _stack_;
    for(int i = 0; i < _universal_user_data_table.UserCount; i++){
        if(_target.UserID == _universal_user_data_table.AllUsers[i]->UserID){
            _universal_user_data_table.CurrentUser = _universal_user_data_table.AllUsers[i];
            break;
        }
    }
    if(settings.isDebug || sessiond.usingDebugCmd){
        printf("debug: Swapping current user to SomeTerminalGame:users/%s\n",_target.Username);
    }
    sessiond.LoggedIn = true;
    return 0;
}

int SetCurrentUser(user _new, bool BypassPermissions){
    _check_bp;
    int attempts = 0;
    _stack_;
    if(_universal_user_data_table.CurrentUser->permissions.CanChangeUser || BypassPermissions){
        if(!BypassPermissions){
            get_pswd:
            char *passwd;
            passwd = get_password("Password: ");
            if(strcmp(passwd, _new.Password) != 0){
                attempts += 1;
                if(attempts >= 3){
                    return 1;
                }
                goto get_pswd;
            }
        }
        _backend_SwapCurrentUser(_new);
        return 0;
    } else {
        status(false, "/usr/bin/user_manager", "access denied");
        return 1;
    }
    return 0;
}

int Invalid_User_Exception___RepeatCount;
int exception_handle_invalid_user(){
    _stack_;
    bp_check(__FUNCTION__);
    notify_exception_handler_entry(__FUNCTION__);
    Invalid_User_Exception___RepeatCount += 1;
    if(Invalid_User_Exception___RepeatCount >= 3){
        HANDLE_fatal("EXCEPTION_HANDLER_REPEAT", __EXCEPTION_HANDLER_REPEAT);
    }
    //reset all users
    HANDLE_notice("Unregistering all users.");
    UnregisterAllUsers();
    RegisterAllUsers();
    printf("Exception handler exit: %s", __FUNCTION__);
    return 0;
}

void RegisterUser(user *usr, bool SuperUser, bool Special, bool Standard){
    _check_bp;
    _stack_;

    _universal_user_data_table.AllUsers[_universal_user_data_table.UserCount] = usr;
    _universal_user_data_table.UserCount += 1;
    if(SuperUser){
        _universal_user_data_table.SuperUsers[_universal_user_data_table.SuperUserCount] = usr;
        _universal_user_data_table.SuperUserCount += 1;
    }
    if(Standard){
        _universal_user_data_table.StandardUsers[_universal_user_data_table.StandardUserCount] = usr;
        _universal_user_data_table.StandardUserCount += 1;
    }
    if(Special){
        _universal_user_data_table._Special[_universal_user_data_table.SpecialUserCount] = usr;
        _universal_user_data_table.SpecialUserCount += 1;
    }
}

int UnregisterAllUsers(){
    _check_bp;
    _stack_;
    for(int i = 0; i < _universal_user_data_table.UserCount; i++){
        memset(_universal_user_data_table.AllUsers, i, 1);
    }
    for(int i = 0; i < _universal_user_data_table.SpecialUserCount; i++){
        memset(_universal_user_data_table._Special, i, 1);
    }
    for(int i = 0; i < _universal_user_data_table.SuperUserCount; i++){
        memset(_universal_user_data_table.SuperUsers, i, 1);
    }
    for(int i = 0; i < _universal_user_data_table.StandardUserCount; i++){
        memset(_universal_user_data_table.StandardUsers, i, 1);
    }
    _universal_user_data_table.StandardUserCount = 0;
    _universal_user_data_table.SpecialUserCount = 0;
    _universal_user_data_table.SuperUserCount = 0;
    _universal_user_data_table.SuperUserCount = 0;
    _universal_user_data_table.UserCount = 0;
    return 0;
}

void RegisterDevice(device *dev, bool Trusted, bool Mounted, bool ShouldBeCurrent, bool hidden){
    _check_bp;
    _stack_;
    //add device to _universal_dev_data_table

    _universal_dev_data_table.AllDevices[_universal_dev_data_table.AllDevicesCount] = dev;
    _universal_dev_data_table.AllDevicesCount += 1;
    if(Mounted){
        _universal_dev_data_table.MountedDevices[_universal_dev_data_table.MountedDevCount] = dev;
        _universal_dev_data_table.MountedDevCount += 1;
    } else {
        _universal_dev_data_table.UnmountDevices[_universal_dev_data_table.UnmountedDevCount] = dev;
        _universal_dev_data_table.UnmountedDevCount += 1;
    }
    if(Trusted){
        _universal_dev_data_table.TrustedDevices[_universal_dev_data_table.TrustedDevCount] = dev;
        _universal_dev_data_table.TrustedDevCount += 1;
    }
    if(ShouldBeCurrent){
        _universal_dev_data_table.CurrentDevice = dev;
        dev->CurrentDevice = true;
    }
}

void universal_data_init(){
    _check_bp;
    _stack_;
    //* register all devices
    RegisterAllDevices();

    //* register all users
    RegisterAllUsers();
}

int RegisterAllDevices(){
    _check_bp;
    _stack_;
    RegisterDevice(&TerminalZ, true, true, true, false);
    RegisterDevice(&USB, false, false, false, false);
    RegisterDevice(&djt, true, false, false, true);
    RegisterDevice(&secret_credits, true, false, false, true);
    return 0;
}

int RegisterAllUsers(){
    _check_bp;
    _stack_;
    RegisterUser(&SYSTEM, true, true, false);
    RegisterUser(&root, true, false, false);
    RegisterUser(&dummy, false, true, false);
    RegisterUser(&standard, false, false, true);
    RegisterUser(&LocalAccountManagerHostUser, true, true, false);
    RegisterUser(&null_user, false, true, false);
    RegisterUser(&debugee, true, true, false);
    return 0;
}

int sessionID(){
    _check_bp;
    srand(time(0));
    _stack_;
    //create the secret key also
    GetUuid(&sessiond.secretKey);
    //create a valid session ID
    sessiond.sessionID = rand() * strtol(sessiond._version_, NULL, 16);
    return 0;
}


//threads
bool thread_KbdListen_active;
bool thread_MemMgr_active;
bool thread_Enemy_active;
bool thread_BkgProcessing_active;
bool thread_main_active;

HANDLE htMain = NULL;
HANDLE htKbdListen = NULL;
HANDLE htMemMgr = NULL;
HANDLE htEnemy = NULL;
HANDLE htBkgProcessing = NULL;


#define thread_init(hThread) (__FUNCTION__,hThread)
void __imp_thread_init(char thread[256], HANDLE hThread){
    _stack_;
    _check_bp;
    DWORD threadId = GetThreadId(hThread);
    printf("[ threads/%s ] The %s thread (thread id: %d) has been started.\n", thread, thread, threadId);
    strcpy(ThreadNames[ThreadCnt],thread);
    ThreadList[ThreadCnt] = hThread;
    ThreadCnt += 1;
    return;
}

int _thread_remove(char thread[256],HANDLE hThread){
    int index = -1;
    int nameLen = sizeof(ThreadNames) / sizeof(ThreadNames[0]);
    int handleLen = sizeof(ThreadList) / sizeof(ThreadList[0]);
    for(int i = 0; i < ThreadCnt; i++){
        if(strcmpi(ThreadNames[i],thread) == 0){
            index = i;
            break;
        }
    }
    if(index == -1){
        HANDLE_errormessage("Attempted to terminate a non-existant thread.",__NOT_FOUND);
        return 1;
    }
    //kill
    TerminateThread(ThreadList[index],0);
    if(settings.isDebug){
        printf("Terminated SomeTerminalGame:threads/%s\n",ThreadNames[index]);
    }
    //move everything back and remove the value
    for(int i = index; i < nameLen; i++){
        strcpy(ThreadNames[i],ThreadNames[i+1]);
    }
    for(int i = index; i < handleLen; i++){
        ThreadList[i] = ThreadList[i + 1];
    }
    ThreadCnt -= 1;
    hThread = NULL;
    return 0;
}

//thread func
int UpdateUnixEpochTime(){
    time_t unix;
    time(&unix);
    sessiond.UnixEpochTime = unix;
    return 0;
}

long long unsigned GetUnixEpochTime(){
    time_t unix;
    time(&unix);
    return unix;
}

DWORD WINAPI Enemy(LPVOID lpParam){
    _stack_;
    thread_init(htEnemy);
    Enemyd.TimeUntilNextAttack = GetUnixEpochTime() + 90;
    while(1){
        if(GetUnixEpochTime() == Enemyd.TimeUntilNextAttack && Enemyd.isAttackAllowed){
            remoteCommandExec("unixtime");
            Enemyd.TimeUntilNextAttack = sessiond.UnixEpochTime + 90;
            SwitchToThread();
        }
        sleep(500);
        SwitchToThread();
    }
}

DWORD WINAPI BkgProcessing(LPVOID lpPARAM){
    _stack_;
    thread_init(htBkgProcessing);
    thread_BkgProcessing_active = true;
    time_t now;

    int i = 0;
    while(1){ //do stuff in a loop
        sleep(150); //prevent excess usage

        //tzss
        if(Enemyd.Attackd.AttackStatus){ //attack in action
            tzssCreateInturrupt(Enemyd.Attackd.Type,Enemyd.Attackd.Severity);
        }

        if(sessiond.Poweroff.When == GetUnixEpochTime() && !sessiond.Poweroff.isPowerout){
            if(AttemptPowerout()){
                screen_powerloss();
            }
        }


        UpdateUnixEpochTime();
        if (i == 20){
            i = 0;
            SwitchToThread();
        }
        i += 1;
    }
}
static SIZE_T lastwss;
DWORD WINAPI MemMgr(LPVOID lpParam){
    _stack_;
    thread_init(htMemMgr);
    thread_MemMgr_active = true;
    HANDLE hMemoryManagement;
    PROCESS_MEMORY_COUNTERS pmc;
    InitializeProcessForWsWatch(htMain);
    hMemoryManagement = OpenProcess(PROCESS_VM_READ | PROCESS_SET_QUOTA | PROCESS_QUERY_INFORMATION, FALSE, sessiond.PID);
    
    if(hMemoryManagement == NULL){
        //revert to legacy and exit
        threadPrint(_fn_, "error: Unable to create process handle. Reverting to legacy memory manager.\n");
        sessiond.UseLegacyMemoryManager = true;
        TerminateThread(htMemMgr, 0);
    }
    GetProcessMemoryInfo(hMemoryManagement, &pmc, sizeof(pmc));
    int i = 0;
    while(1){
        //memory counters
        GetProcessMemoryInfo(hMemoryManagement, &pmc, sizeof(pmc));
        //did it increase too much?
        if(lastwss*2 < pmc.WorkingSetSize){
            printf("Memory increase!\n");
        }
        
        lastwss = pmc.WorkingSetSize;
        if(pmc.WorkingSetSize >= sessiond.memLimit){
            if(settings.isDebug){
                threadPrint(_fn_, "Flushing working set. . .");
            }
            EmptyWorkingSet(hMemoryManagement);
            if(settings.isDebug){
                threadPrint(_fn_, "Flushed!");
            }
            SwitchToThread();
        }

        if(i == 20){
            SwitchToThread();
            i = 0;
        }
        i += 1;
    }
}

typedef enum {
    STATE_NORMAL,         // No modifier key pressed, waiting for any key
    STATE_MODIFIER_PRESSED, // F5 was pressed, waiting for the next key
    STATE_MODIFIER_WAIT_FOR_NEXT_KEY
} KeyState;

#define MOD_KEY VK_F5
DWORD WINAPI KbdListen(LPVOID lpParam){
    _stack_;
    thread_init(htKbdListen);

    KeyState state = STATE_NORMAL;
    thread_KbdListen_active = true;
    int i = 0;

    while(1){
        if(GetAsyncKeyState(MOD_KEY) & 0x8000){
            if(state == STATE_NORMAL){
                state = STATE_MODIFIER_PRESSED;
            }
        } else {
            if(state = STATE_MODIFIER_PRESSED){
                state = STATE_MODIFIER_WAIT_FOR_NEXT_KEY;
            }
        }

        static bool modWasDown = false;
        static bool modSequenceActive = false;

        bool modIsDown = (GetAsyncKeyState(MOD_KEY) & 0x8000) != 0;

        if(modIsDown && !modWasDown){
            modSequenceActive = true;
        }
        modWasDown = modIsDown;

        if(modSequenceActive){
            static bool modWasDownPrevIter = false;
            bool modIsDownRightNow = (GetAsyncKeyState(MOD_KEY) & 0x8000) != 0;

            if(!modIsDownRightNow && modWasDownPrevIter){
                modSequenceActive = true;
            }
            modWasDownPrevIter = modIsDownRightNow;

            if(modSequenceActive){
                if(GetAsyncKeyState('H') & 0x8000){
                    pthread("HELP: F5+H - This help, F5+Q - Quit game, F5+M - Memory info, F5+P - call _panic\n");
                    modSequenceActive = false;
                }
                if(GetAsyncKeyState('Q') & 0x8000){
                    pthread("Quitting game...\n");
                    quit(__TERM_USER_INITIATED);
                    modSequenceActive = false;
                }
                if(GetAsyncKeyState('M') & 0x8000){
                    pthread("Show memory information\n");
                    HANDLE hProcess;
                    PROCESS_MEMORY_COUNTERS pmc;
                    MEMORYSTATUSEX status;
                    APP_MEMORY_INFORMATION mem;
                    hProcess = OpenProcess(  PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());

                    if(hProcess == NULL){
                        SetFatalParamater("PROCESS_QUERY_INFORMATION");
                        SetFatalParamater("PROCESS_VM_READ");
                        SetFatalParamater(__FUNCTION__);
                        HANDLE_fatal("PROCESS_HANDLE_FAILURE",__PROCESS_HANDLE_FAILURE);
                    }
                    if( GetProcessMemoryInfo( hProcess, &pmc, sizeof(pmc) ) ){
                        pthread("Page Fault Count: %d\n", pmc.PageFaultCount);
                        pthread("Peak Working Set Size: %.2f MB\n", _to_mb(pmc.PeakWorkingSetSize) );
                        pthread("Working Set Size: %.2f MB\n", _to_mb(pmc.WorkingSetSize));
                        pthread("Quota Peak Paged Pool Usage: %.2f MB\n", _to_mb(pmc.QuotaPeakPagedPoolUsage) );
                        pthread("Quota Paged Pool Usage: %.2f MB\n", _to_mb(pmc.QuotaPagedPoolUsage) );
                        pthread("Quota Peak Non Paged Pool Usage: %.2f MB\n", _to_mb(pmc.QuotaPeakNonPagedPoolUsage) );
                        pthread("Quota Non Paged Pool Usage: %.2f MB\n", _to_mb(pmc.QuotaNonPagedPoolUsage) );
                        pthread("Page file Usage: %.2f MB\n", _to_mb(pmc.PagefileUsage) ); 
                        pthread("Peak Page file Usage: %.2f MB\n\n", _to_mb(pmc.PeakPagefileUsage) );
                    }
                    if( GetProcessInformation( hProcess, ProcessAppMemoryInfo, &mem,sizeof(APP_MEMORY_INFORMATION) ) ){
                        pthread("Available Commit: %llu\n",mem.AvailableCommit);
                        pthread("Total commit usage: %llu\n", mem.TotalCommitUsage);
                        pthread("Private commit usage: %llu\n",mem.PrivateCommitUsage);
                        pthread("Peak private commit usage: %llu\n\n", mem.PeakPrivateCommitUsage);
                    }
                
                    CloseHandle(hProcess);
                    modSequenceActive = false;
                }
                if(GetAsyncKeyState('P') & 0x8000){
                    pthread("call panic\n");
                    _panic();
                    modSequenceActive = false;
                }
            }

        }

        if(i == 20){
            SwitchToThread();
            i = 0;
        }
        Sleep(100);
        i += 1;
    }
    return 0;
}

int createThreads(){
    _stack_;
    //create
    htKbdListen = CreateThread(NULL, 0, KbdListen, NULL, CREATE_SUSPENDED, NULL);
    htMemMgr = CreateThread(NULL, 0, MemMgr, NULL, CREATE_SUSPENDED, NULL);
    htBkgProcessing = CreateThread(NULL,0,BkgProcessing,NULL,CREATE_SUSPENDED,NULL);
    htEnemy = CreateThread(NULL,0,Enemy,NULL,CREATE_SUSPENDED,NULL);
    SetThreadPriority(htKbdListen, THREAD_PRIORITY_NORMAL);
    SetThreadPriority(htEnemy,THREAD_PRIORITY_NORMAL);
    SetThreadPriority(htMemMgr, THREAD_PRIORITY_NORMAL);
    SetThreadPriority(htBkgProcessing,THREAD_PRIORITY_LOWEST);
    return 0;
}

int startThreads(){
    _stack_;
    ResumeThread(htMemMgr);
    ResumeThread(htKbdListen);
    ResumeThread(htBkgProcessing);
    ResumeThread(htEnemy);
    return 0;
}

#define pshutdown(...) (printf("STG/exit: "__VA_ARGS__))

int killThreads(){
    _stack_;
    _check_bp;
    //suspend threads first
    printf("Suspending threads:\n");
    for(int i = 0; i < ThreadCnt; i++){
        SuspendThread(ThreadList[i]);
        printf("    Suspended SomeTerminalGame:threads/%s\n",ThreadNames[i]);
    }
    printf("Terminating threads:\n");
    for(int i = 0; i < ThreadCnt; i++){
        TerminateThread(ThreadList[i],0);
        printf("    Terminated SomeTerminalGame:threads/%s\n",ThreadNames[i]);
    }
    return 0;
}

void hRegistry_ev(void){
    printf("Registry event!\n");
}

HookRoot hCrash;
HookRoot hEnemy;
HookRoot hPowerout;
HookRoot hRegistry;
int doCreateHooks(){
    _stack_;
    _check_bp;
    printf("Creating hook:hCrash,Active=true,ManualReset=true\n");
    CreateHookRoot(&hCrash,true,true);
    printf("[ OK ] Created hook!\n");

    printf("Creating hook:hEnemy,Active=true,ManualReset=false\n");
    CreateHookRoot(&hEnemy,true,false);
    printf("[ OK ] Created hook!\n");

    printf("Creating hook:hPowerout,Active=true,ManualReset=false\n");
    CreateHookRoot(&hPowerout,true,false);
    printf("[ OK ] Created hook!\n");

    printf("Creating hook:hRegistry,Active=true,ManualReset=false\n");
    CreateHookRoot(&hRegistry,true,false);
    printf("[ OK ] Created hook!\n");

    return 0;
}

int quit(int TERMINATION_TYPE){
    _stack_;
    printf("\n\n");
    system("cls");
    printf("Invoke SomeTerminalGame/exit\n");
    showcursor();
    flushBottom();
    sessiond.top->Flush(sessiond.top);
    killThreads();
    if(settings.LogFileExist){
        ETC_file(_FILE_DEBUG_LOG,"Stack end\n","a","OUT");
    }
    FlushRegistryCache();
    printf("Ending game. . .\n");
    printf("\n");
    printf("Goodbye!\n");
    exit(TERMINATION_TYPE);
    TerminateProcess(sessiond.hProcess,TERMINATION_TYPE);
    return TERMINATION_TYPE;
}

int StoreCurrentRuntimeDependencies(){
    HMODULE mods[1024];
    DWORD cbNeed;
    DWORD misc;
    if ( EnumProcessModules(GetCurrentProcess(),mods,sizeof(mods),&cbNeed) ){
        for(int i = 0; i < (cbNeed / sizeof(HMODULE)); i++){
            MODULEINFO modinfo;
            char path[MAX_PATH];
            if( GetModuleFileNameExA(GetCurrentProcess(),mods[i],(LPSTR)path, sizeof(path) / sizeof(char))) {
                if( GetModuleInformation(GetCurrentProcess(),mods[i],&modinfo,sizeof(MODULEINFO))){
                    FilePaths paths;
                    GetAllFilePaths(path,&paths);
                    //printf("[ OK ] Found %s: modinfo={\n",path);
                    //printf("    .EntryPoint=0x%p\n",modinfo.EntryPoint);
                    //printf("    .lpBaseOfDll=0x%p\n",modinfo.lpBaseOfDll);
                    //printf("    .SizeOfImage=%d bytes\n",modinfo.SizeOfImage);
                    //printf("}\n");
                    printf("\t%s\n",paths.NtPath);
                    //printf("       Image entry: 0x%p\n",modinfo.EntryPoint);
                    //printf("       Image base: 0x%p\n",modinfo.lpBaseOfDll);
                    //printf("       Image size (in bytes): %d\n",modinfo.SizeOfImage);
                }
            }
        }
    }
    return 0;
}

bool AttemptPowerout(){
    if(!settings.AllowPowerout){
        HANDLE_warn("Attempted to trigger poweroutage event but settings.AllowPowerout is set to false.");
        return false;
    }
    if(settings.isDebug){
        HANDLE_debugmsg("Attempting to trigger poweroutage event...");
    }
    srand(time(NULL));
    int random = (rand() / sessiond.PID) % 101;

    if(random < sessiond.Poweroff.Chance){
        hPowerout.Fire(&hPowerout);
        HANDLE_debugmsg("Poweroutage success");
        sessiond.Poweroff.isPowerout = true;
    } else {
        HANDLE_debugmsg("Poweroutage failed");
        sessiond.Poweroff.isPowerout = false;
    }

    printf("\n");
    if(settings.isDebug){
        HANDLE_debugmsg("random=%d,  sessiond.Poweroff.Chance=%d,  sessiond.Powerout.When=%lld, sessiond.Poweroff.isPowerout=%s",
                        random,sessiond.Poweroff.Chance,sessiond.Poweroff.When,btos(sessiond.Poweroff.isPowerout));
        sleep(500);
    }
    sessiond.Poweroff.When = GetUnixEpochTime() + 30;
    return sessiond.Poweroff.isPowerout;
}

void Nothing(void){
    return;
}

int resetColor(void){
    char *colorsel = RegistryReadSz("Color");
    char colorstr[25];
    sprintf(colorstr,"color %s",colorsel);
    return system(colorstr);
}

no_return void GetAGirlfriend(void) {
    _stack_;
    printf("finding baddies...");
    sleep(1500);
    HANDLE_errormessage("no baddies!!!",__ERROR_NO_BITCHES);
    HANDLE_fatal("ERROR_NO_BITCHES",__ERROR_NO_BITCHES);
}

int v_argv;
int build;
extern int build;
bool pause_start = false;
#define SHOW_ULOW
#define VERSION_HIGH 1
#define VERSION_MEDIUM 7
#define VERSION_LOW 9
#define VERSION_ULLOW 4
#define VERSION_CODENAME "Return"
char MSC_VERSION_STR[50];
#define VERSION_MAIN EVALSTRINGIFY(VERSION_HIGH)"."EVALSTRINGIFY(VERSION_MEDIUM)"."EVALSTRINGIFY(VERSION_LOW)"."EVALSTRINGIFY(VERSION_ULLOW)
#ifdef __TEST_BUILD
    #define VERSION_FULL_STR VERSION_MAIN ".test_build"
#elif
    #define VERSION_FULL_STR VERSION_MAIN
#endif
bool UseEarlyConsole = false;

int main(int argc, char* argv[]) {
    void run_tests(void);
    SetConsoleOutputCP(CP_UTF8);
    if(argv[1] != NULL){
        if(strcmpi(argv[1],"--help") == 0){
            printf("SomeTerminalGame / Command Line Arguments\n");
            printf("------------------------------------------------\n");
            printf("    --fast              Skip the booting process\n");
            printf("    --debug             Enable debug mode\n");
            printf("    --pausestart        Pause startup when it ends\n");
            printf("    --ignorerrors       Ignore any error and exception handling\n");
            printf("    --console           After startup, jumps to debug console.\n");
            printf("    --noregistrycache   Do not cache registry read's.\n");
            printf("    --reset             Reset registry config, can only be used alone.\n");
            return 0;
        }
        if(strcmpi(argv[1],"--reset") == 0){
            printf("Reset registry configuration...");
            RegistryReset();
            printf("done!\n");
            return 0;
        }
    }
    system("cls");
    printf("\n");
    HANDLE_earlymsg("Do pre-startup init\n");
    //get build from time
    srand(UNIX_TIMESTAMP);
    build = rand() * 2;
    char *temp = (char*)malloc(50);
    sprintf(temp,"%d",_MSC_FULL_VER);
    char *temp2 = (char*)malloc(50);
    sprintf(temp2,"%c%c.%c%c.%c%c%c%c",temp[0],temp[1],temp[2],temp[3],temp[5],temp[6],temp[7],temp[8]);
    strcpy(MSC_VERSION_STR,temp2);
    free(temp);free(temp2);
    time_t now;
    time(&now);
    char *temp3 = (char*)malloc(256);
    sessiond.build = build;
    sprintf(temp3,"SomeTerminalGame Version %s codename \"%s\" build %d - Compiled %s local time (%d unix time) with MSVC Version %s",
        VERSION_FULL_STR,VERSION_CODENAME
        ,build,__TIMESTAMP__,UNIX_TIMESTAMP,
        MSC_VERSION_STR);
    strcpy(sessiond._verinfo,temp3);
    free(temp3);
    SetUnhandledExceptionFilter(ExceptionFilter);
    signal_init();
    _check_bp;
    _stack_;
    sessiond.entryAddress = (void*)main;
    sessiond.memLimit = 10000000000LLU;
    sessiond.hProcess = GetCurrentProcess();

    //set the base address for offset information
    HMODULE tmp = GetModuleHandleA(0);
    baseAddress = (void*)tmp;
    sessiond.baseAddress = baseAddress;
    //startup
    //register the main thread for the sake of it
    //name it main for simplicit
    htMain = GetCurrentThread();
    thread_init(htMain);
    sessiond.mainThreadId = GetCurrentThreadId();
    thread_main_active = true;

    clock_t start_time, end_time;
    start_time = clock();
    printf("Starting %s at %s",sessiond._verinfo,ctime(&now));
    printf("Command line: \"");
    for(int i =0; i < argc;i++){
        printf("%s ",argv[i]);
    }

    printf("Hello, World!\n");
    printf("Setting window title. . .\n");
    system("title bin/SomeTerminalGame");
    printf("[ OK ] The window title has been set as: \"bin/SomeTerminalGame\"\n");

    printf("Reached target: loadModulesAndDependencies\n");
    //list dependencies
    printf("Currently loaded DLL's:\n");
    StoreCurrentRuntimeDependencies();

    printf("Fetching Process ID. . .\n");
    sessiond.PID = GetCurrentProcessId();
    printf("[ OK ] Fetched process ID: %d\n", sessiond.PID);
    printf("Verifying installation. . .\n");
    if(verify_installation() != 0){
        HANDLE_fatal("BAD_INSTALLATION",__BAD_INSTALLATION);
    } else {
        printf("[ OK ] The installation has been verified.\n");
    }
    printf("Parsing starting arguments. . .\n");
    if(argc > 10){
        HANDLE_fatal("BAD_ARGUMENT_COUNT", __BAD_ARGUMENT_COUNT);
        sessiond.deprecated.StartArgsFetchFailure = true;
    }
    bool regCachesetFromCmd = false;
    for(int i = 1; i < argc ; i++){
        if(strcmpi(argv[i],"--fast") == 0){
            sessiond.skip = true;
            printf("[ OK ] Starting argument applied: '%s'\n", argv[i]);
        } else if(strcmpi(argv[i], "--debug") == 0){
            settings.isDebug = true;
            printf("[ OK ] Starting argument applied: '%s'\n", argv[i]);
        } else if (strcmpi(argv[i],"--PauseStart") == 0){
            pause_start=true;
            printf("[ OK ] Starting argument applied: '%s'\n", argv[i]);
        }else if(strcmpi(argv[i],"--IgnoreErrors") == 0){
            settings.IgnoreErrors=true;
            printf("[ OK ] Starting argument applied: '%s'\n", argv[i]);
        } else if(strcmpi(argv[i],"--console") == 0){
            sessiond.usingDebugCmd = true;
            settings.isDebug = true;
            printf("[ OK ] Starting argument applied: '%s'\n", argv[i]);
        } else if(strcmpi(argv[1],"--noregistrycache") == 0){
            settings.useRegistryCache = false;
            regCachesetFromCmd = true;
        }else {
            printf("[ ERROR ] Ignoring unknown argument: '%s'\n", argv[i]);
        }
    }
    printf("Reached target: threads \n");
    printf("Creating threads. . .\n");
    createThreads();
    printf("[ OK ] Threads Created\n");
    
    //hook
    printf("Reached target: hooking\n");
    printf("Creating hooks. . .\n");
    doCreateHooks();
    //hRegistry.AddFunction(&hRegistry,Nothing);

    //start threads
    startThreads();
    printf("Waiting on thread(s) to start. . .\n");
    while(!thread_KbdListen_active && !thread_MemMgr_active && !thread_BkgProcessing_active && !thread_Enemy_active){
        sleep(1);
    }
    printf("Reached target: CoreInfo \n");
    strcpy(sessiond._version_,VERSION_FULL_STR);
    printf("[ OK ] Fetched version: %s\n", sessiond._version_);
    printf("Fetching executable location. . .\n");
    _fetchExecLocation();
    printf("[ OK ] Fetched executable location: %s\n", sessiond._exec_path_);
    printf("Fetching installation location. . .\n");
    _fetchInstallationLocation();
    printf("[ OK ] Fetched installation location: %s\n", sessiond._installation_path_);

    printf("Reached target: registry \n");
    printf("Checking if registry config exists...\n");

    if(!DoesRegistryConfigExist()){
        printf("[ OK ] Registry config does not exist!\n");
        printf("Creating default registry data...\n");
        RegistryInit();
        printf("[ OK ] Created registry key: REGISTRY\\HKEY_CURRENT_USER\\%s\n",REG_PATH);
    } else {
        printf("[ OK ] Found registry config: REGISTRY\\HKEY_CURRENT_USER\\%s\n",REG_PATH);
    }

    settings.useRegistryCache = RegistryReadDword("useRegistryCache");
    if(regCachesetFromCmd){
        settings.useRegistryCache = false;
    }
    bool registryCacheWarningShow = false;
    if(!InitRegistryCache()){
        registryCacheWarningShow = true;
        HANDLE_warn("Registry data cache is disabled! Expect a lot of registry reads");
        if(regCachesetFromCmd){
            printf("               Source: command line: \"--noregistrycache\"\n\n");
        } else {
            printf("               Source: REG_DWORD REGISTRY\\HKEY_CURRENT_USER\\%s\\useRegistryCache\n\n",REG_PATH);
        }
        sleep(50);
    } else {
        printf("[ OK ] Registry data cache is enabled!\n");
    }

    DWORD useLog = RegistryReadDword("alwaysLogfile");
    if(useLog == 1){
        settings.LogFileExist = true;
    } else {
        settings.LogFileExist = false;
    }
    if(settings.LogFileExist){
        //create newline
        ETC_file(_FILE_DEBUG_LOG,"Stack begin","a","OUT");
        ETC_file(_FILE_DEBUG_LOG,sessiond._verinfo,"a","OUT");
    }
    printf("[ OK ] Applied REG_DWORD REGISTRY\\HKEY_CURRENT_USER\\%s\\alwaysLogfile\n",REG_PATH);

    char *colorsel = RegistryReadSz("Color");
    char colorstr[25];
    sprintf(colorstr,"color %s",colorsel);
    system(colorstr);
    printf("[ OK ] Applied REG_DWORD REGISTRY\\HKEY_CURRENT_USER\\%s\\Color\n",REG_PATH);

    DWORD suppres = RegistryReadDword("SuppressSplashMessage");
    if(suppres == 1){
        settings.SuppressSplashMessage = true;
    } else {
        settings.SuppressSplashMessage = false;
    }
    printf("[ OK ] Applied REG_DWORD REGISTRY\\HKEY_CURRENT_USER\\%s\\SuppressSplashMessage\n",REG_PATH);

    DWORD dumps = RegistryReadDword("DumpstackOnCrash");
    if(dumps == 1){
        settings.DumpstackOnCrash = true;
    } else {
        settings.DumpstackOnCrash = false;
    }
    printf("[ OK ] Applied REG_DWORD REGISTRY\\HKEY_CURRENT_USER\\%s\\DumpstackOnCrash\n",REG_PATH);

    DWORD alwaysDbg = RegistryReadDword("alwaysDebug");
    if(alwaysDbg < 0){
        SetFatalParamater("REGISTRY\\HKEY_CURRENT_USER\\%s\\alwaysDebug < 0");
        HANDLE_fatal("REGISTRY_BAD_CONFIGURATION",__REGISTRY_BAD_CONFIGURATION);
    }
    if(alwaysDbg){
        settings.isDebug = true;
    } else {
        settings.isDebug = false;
    }
    printf("[ OK ] Applied REG_DWORD REGISTRY\\HKEY_CURRENT_USER\\%s\\alwaysDebug\n",REG_PATH);

    //temporary file
    printf("Reached target: temporary container \n");
    printf("Creating runtime temp file. . .\n");
    createTemporaryContentContainer();
    printf("[ OK ] Runtime temp was created.\n");

    //extension
    printf("Reached target: extensions\n");
    //debugLog("OUT","what %s",sessiond._verinfo);
    doInitLua();


    //sessiond
    printf("Reached target: sessiond\n");
    printf("Initializing values of session data.\n");
    sessiond.FirstRun = true;
    sessiond.LoggedIn = false;
    sessiond.SetupCompleted = false;
    sessiond.Poweroff.Chance = 10;
    sessiond.Poweroff.isPowerout = false;
    sessiond.Poweroff.When = GetUnixEpochTime() + 600;
    settings.AllowPowerout = true;
    sessiond.top = (_topright_text*)malloc(sizeof(_topright_text));
    CreateTopRight(sessiond.top);
    strcpy(sessiond.bp_func, "value_not_set!");
    printf("[ OK ] The required values have been set.\n");
    printf("Creating session ID. . .\n");
    sessionID();
    printf("[ OK  ] Session ID created: %d\n", sessiond.sessionID);
    printf("[ NOTICE] Initialzing values. . .\n");
    universal_data_init();
    printf("[ OK ] Initialized\n");
    if(settings.isDebug && !settings.LogFileExist){
        bool c = confirm("[ STARTUP/INTERRUPT ] Debug mode is enabled, would you like to also enable the log file?");
        if(c){
            ETC_file(_FILE_DEBUG_LOG,"Stack begin","w","OUT");      
            settings.LogFileExist=true;
        }
    }

    printf("Reached target: gameStart \n");
    printf("[ OK ] Startup has completed!\n");
    end_time = clock();
    sessiond.timeToStart = (double)(end_time - start_time)  / CLOCKS_PER_SEC;
    ETC_file(_FILE_DEBUG_LOG,"Startup finished!","a","OUT");
    if(pause_start && settings.isDebug){
        dumpStack();
    }

    run_tests();

    if(sessiond.usingDebugCmd){
        printf("Starting debugConsole(). . .\n");
    } else {
        printf("Starting mainmenu(). . .\n");
    }
    if(pause_start){
        printf("\nStartup paused. Press [SPACE] to continue.");
        while(1){
            if(kbhit){
                char ch = getch();
                if(ch==32){
                    break;
                }
            }
        }
    }
    if(!sessiond.usingDebugCmd && !settings.SuppressSplashMessage){
        system("cls");
        char *text = get_splash_text();
        printf("%s\n",text);
        #define SPACE_BAR_SYMBOL    "\xE2\x94\x94\xE2\x94\x80\xE2\x94\x98"
        #define SPACE_BAR_SYMBOL2   "\xE2\x96\x95\xE2\x96\x81\xE2\x96\x81\xE2\x96\x8F"
        #define SPACE_BAR_SYMBOL_ORIG "\xE2\x90\xA3"
        printf("\nPress {SPACE} to close.\n");
        showBottomInfo();
        while(1){
            if(kbhit){
                char ch = getch();
                if(ch == 32){
                    break;
                }
            }
        }
    }
    if(sessiond.usingDebugCmd){
        debugConsole();
    }
    hidecursor();
    int y = mainmenu();
    if(y == 2) {
        settingsmenu();
    }
}

void run_tests(void){
    _stack_;
    _check_bp;
    printf("run_tests...\n");
    HANDLE_errormessage("fart",0x00000);
    printf("%d\n",sessiond.mainThreadId);
}

//data
char command;
char ch;
int accesslevel = 0; //max is 3
bool IsDatabaseLoaded = false;
bool FirstRun = true;
char currentIP[120] = "127.0.0.1";
int $points;
int xp;
int cpu = 0;
int ram = 0;
int storage = 0;

int TZSS_CheckDiskIntegrity(){
    _stack_;
    _check_bp;
    int al_index = 0;
    char action_list[15][120];
    if(!tzss.enabled || !tzss.policy.UnmountInvalidDisks){
        return 1;
    }
    for(int i = 0; i < _universal_dev_data_table.AllDevicesCount; i++){
        if(!_universal_dev_data_table.AllDevices[i]->Trusted && _universal_dev_data_table.AllDevices[i]->Mounted){
            strcpy(action_list[al_index],"Invalid disk detected and unmounted");
            _universal_dev_data_table.AllDevices[i]->Mounted = false;
        }
    }
    printf("Terminal Z Security System has detected %d problem(s) and has fixed them\n", al_index);
    for(int i = 0; i < al_index; i++){
        printf("Action %d: %s\n", i, action_list[i]);
    }
    return 0;
}


int shop_return(int pnt, int level_cpu, int level_ram, int level_storage){
    _check_bp;
    _stack_;
    signal_init();
    $points = pnt;
    level_cpu = cpu;
    level_ram = ram;
    level_storage = storage;
    promptline();
    
    return 0;
}

//class:debug

int changeaccesslevel(int newlvl) {
    signal_init();
    _check_bp;
    _stack_;
    if(settings.isDebug){
        printf("debug: Changing Variable:int:accesslevel to %i\n", newlvl);
    }
    if(LogFileExist){
        ETC_file(_FILE_DEBUG_LOG, "Value changed on: Variable:int:accesslevel", "a", "OUT");
    }
    if(accesslevel == newlvl) {
        HANDLE_errormessage("Variable:int:accesslevel can not be set to current value!", __VALUE_CHANGE_FAILURE);
    }
    accesslevel = newlvl;
    return 0;
}



bool curhost = false;
bool isDatabaseRead = false;

//i know it's a mess but it works
int execute(_command *cmd) {
    _check_bp;
    signal_init();
    _stack_;

    if(strcmpi(cmd->command[0],"help") == 0){
        printf("Help\n");
        printf("---------------------------\n");
        printf("    help                Display this help message\n");
        printf("    clear               Clear the screen\n");
        printf("    reboot              Reboot the system\n");
        printf("    lsblk               List blocks / devices\n");
        printf("    su <user>           Swap User\n");
        printf("    usrmgr <user>       launched user manager\n");
        printf("    logout              Logout\n"); 
        printf("    exit                Return to main menu\n");
        printf("    mount <device>      Mount a device to the system\n");
        printf("    unmount <device>    Unmount a device from the system\n");
        printf("    trust <device>      Trust a deivce\n");
        printf("    untrust <device>    Revoke trust from a device\n");
        printf("    whoami              Displays the current user\n");
        printf("    unixtime            Prints the time from the Unix Epoch (seconds since January 1st, 1970).\n");
        printf("    stg-version         Displays version info for SomeTerminalGame.\n");
        promptline();
    }
    if(strcmpi(cmd->command[0],"getAGirlfriend")==0){
        GetAGirlfriend();
    }
    if(strcmpi(cmd->command[0],"stg-version") == 0){
        printf("%s\n",sessiond._verinfo);
        promptline();
    }
    if(strcmpi(cmd->command[0],"tzss") == 0){
        if(strcmpi(cmd->command[1],"enable") == 0){
            tzss.enabled = true;
        } else {
            tzss.enabled = false;
        }
        status(true,"tzss","b");
        promptline();
    }
    if(strcmpi(cmd->command[0],"net") == 0){
        if(strcmpi(cmd->command[1],"disconnect") == 0){
            ethernet.Mounted = false;
            EtherConnected = false;
            printf("%s has been disconnected.\n",ethernet.FriendlyName);
        }
        if(strcmpi(cmd->command[1],"connect") == 0){
            init_boot_ethernet();
        }
    }
    if(strcmpi(cmd->command[0],"logout") == 0){
        printf("logout\n");
        sleep(250);
        login();
    }
    if(strcmpi(cmd->command[0], "lsblk") == 0){
        printf("-devmgr: gathering list of block data...\n");
        for(int i = 0; i < _universal_dev_data_table.AllDevicesCount; i++){
            if(_universal_dev_data_table.AllDevices[i]->Hidden){
                continue;
            }
            printf("Mounted point %s\n\n", _universal_dev_data_table.AllDevices[i]->MountPoint);
            printf("  Name. . . . . . . . . . : %s\n", _universal_dev_data_table.AllDevices[i]->FriendlyName);
            printf("  Hardware Address. . . . : %s\n", _universal_dev_data_table.AllDevices[i]->HardwareAddress);
            printf("  Mount . . . . . . . . . : %s\n", _universal_dev_data_table.AllDevices[i]->MountLocation);
            printf("  Device Type . . . . . . : %s\n", _universal_dev_data_table.AllDevices[i]->type);
            printf("  CurrentDevice . . . . . : %s\n", btos(_universal_dev_data_table.AllDevices[i]->CurrentDevice));
            printf("  Bootable. . . . . . . . : %s\n", btos(_universal_dev_data_table.AllDevices[i]->Bootable));   
            printf("  Trusted . . . . . . . . : %s\n", btos(_universal_dev_data_table.AllDevices[i]->Trusted));
            printf("  Default . . . . . . . . : %s\n", btos(_universal_dev_data_table.AllDevices[i]->Default));   
            printf("  Mounted . . . . . . . . : %s\n\n", btos(_universal_dev_data_table.AllDevices[i]->Mounted));
        }
        TZSS_CheckDiskIntegrity();
        status(true, "devmgr","v");
        promptline();
    }
    if(strcmpi(cmd->command[0],"su") == 0){
        if(!_universal_user_data_table.CurrentUser->permissions.CanChangeUser){
            status(false,"su","permission denied.");
            promptline();
        }
        user target;
        if(!doesUsernameExist(cmd->command[2])){
            status(false, "su", "user does not exist");
            promptline();
        }
        for(int i = 0; i < _universal_user_data_table.UserCount; i++){
            if(strcmp(_universal_user_data_table.AllUsers[i]->Username, cmd->command[2]) == 0){
                target = *_universal_user_data_table.AllUsers[i];
            }
        }
        SetCurrentUser(target, false);
        sleep(1000);
        status(true, "usrmgr","b");
        promptline();
    }
    if(strcmpi(cmd->command[0],"usrmgr") == 0){
        if(!_universal_user_data_table.CurrentUser->permissions.CanUseUsrmgr){
            status(false,"usrmgr","permission denied.");
            promptline();
        }
        if(strcmpi(cmd->command[1],"modify") == 0){
            user target;
            if(!doesUsernameExist(cmd->command[2])){
                status(false, "usrmgr", "user does not exist");
                promptline();
            }
            for(int i = 0; i < _universal_user_data_table.UserCount; i++){
                if(strcmp(_universal_user_data_table.AllUsers[i]->Username, cmd->command[2]) == 0){
                    target = *_universal_user_data_table.AllUsers[i];
                }
            }
            usrmgr_modify(_universal_user_data_table.CurrentUser, &target);
        }
    }
    if(strcmpi(cmd->command[0],"clear") == 0){
        system("cls");
        promptline();
    }
    if(strcmpi(cmd->command[0], "exit") == 0){
        if(sessiond.usingDebugCmd){
            forceexit(0);
        }
        mainmenu();
    }
    if(strcmpi(cmd->command[0], "reboot") == 0){
        screen_reboot();
    }
    if(strcmpi(cmd->command[0], "mount") == 0){
        if(!_universal_user_data_table.CurrentUser->permissions.DriveOperations){
            status(false, "devmgr","permission denied.");
            promptline();
        }
        device *target;
        bool force = false;
        for(int i = 0; i < _universal_dev_data_table.AllDevicesCount; i++){
            if(strcmpi(_universal_dev_data_table.AllDevices[i]->MountLocation, cmd->command[1]) == 0){
                target = _universal_dev_data_table.AllDevices[i];
                break;
            }
        }
        if(strcmpi(cmd->command[2], "--force") == 0){
            force = true;
        }
        if(!target->Mounted){
            if(!target->Trusted && !force){
                status(false, "devmgr","The specified device is not trusted and will not be mounted. Use '--force' to override.");
                promptline();
            }
            if(force){
                printf("-devmgr: '--force' applied. Bypassing security checks...\n");
                sleep(500);
            }
            printf("-devmgr: mounting %s at %s...\n", target->HardwareAddress, target->MountLocation);
            sleep(1200);
            target->Mounted = true;
            status(true,"devmgr","v");
            promptline();
        } else {
            status(false, "devmgr","The specified device is already mounted.");
            promptline();
        }
    }
    if(strcmpi(cmd->command[0],"unmount") == 0){
        if(!_universal_user_data_table.CurrentUser->permissions.DriveOperations){
            status(false, "devmgr","permission denied.");
            promptline();
        }
        device *target;
        bool force = false;
        for(int i = 0; i < _universal_dev_data_table.AllDevicesCount; i++){
            if(strcmpi(_universal_dev_data_table.AllDevices[i]->MountLocation, cmd->command[1]) == 0){
                target = _universal_dev_data_table.AllDevices[i];
                break;
            }
        }
        if(strcmpi(cmd->command[2],"--force") == 0){
            force = true;
        }
        if(target->Mounted){
            if(target->CurrentDevice && !force){
                status(false, "devmgr","currently booted to specified device. Use '--force' to override.");
                promptline();
            }
             if(force){
                printf("-devmgr: '--force' applied. Bypassing security checks...\n");
                sleep(500);
            }
            printf("-devmgr: canceling drive operations on %s...\n",target->MountLocation);
            sleep(780);
            printf("-devmgr: unmounting %s...\n",target->MountLocation);
            if(target->CurrentDevice){
                printf("-TZ_KRNL: panic: / unmounted during use\n");
                printf("-TZ_KRNL: Dumping error information...\n");
                sleep(150);
                instant_reboot();
            }
            sleep(450);
            printf("-devmgr: verifying...\n");
            sleep(240);
            promptline();
        } else {
            status(false, "devmgr","the specified devie is not mounted");
        }
    }
    if(strcmpi(cmd->command[0], "trust") == 0){
       if(!_universal_user_data_table.CurrentUser->permissions.DriveOperations){
            status(false, "devmgr","permission denied.");
            promptline();
        }
        device *target;
        bool force = false;
        for(int i = 0; i < _universal_dev_data_table.AllDevicesCount; i++){
            if(strcmpi(_universal_dev_data_table.AllDevices[i]->MountLocation, cmd->command[1]) == 0){
                target = _universal_dev_data_table.AllDevices[i];
                break;
            }
        }
        if(strcmpi(cmd->command[2],"--force") == 0){
            force = true;
        }
        if(!target->Trusted){
            if(target->Mounted && !force){
                status(false, "devmgr","The specified device is already mounted, unmount this device first or use '--force' to override.");
                promptline();
            }
            if(force){
                printf("-devmgr: '--force' applied. Bypassing security checks...\n");
                sleep(500);
            }
            bool con = confirm("Would you like to trust the target device?");
            if(!con){
                promptline();
            }
            printf("Trusting the specified device: %s...\n", target->MountLocation);
            sleep(450);
            status(true,"devmgr","v");
            promptline();
        } else if(target->Trusted){
            status(false, "devmgr","the specified device is already trusted");
        }
    }
    if(strcmpi(cmd->command[0],"untrust") == 0){
        if(!_universal_user_data_table.CurrentUser->permissions.DriveOperations){
            status(false, "devmgr","permission denied.");
            promptline();
        }
        device *target;
        bool force = false;
        for(int i = 0; i < _universal_dev_data_table.AllDevicesCount; i++){
            if(strcmpi(_universal_dev_data_table.AllDevices[i]->MountLocation, cmd->command[1]) == 0){
                target = _universal_dev_data_table.AllDevices[i];
                break;
            }
        }
        if(target->Trusted){
            if(target->Mounted && !force){
                status(false,"devmgr","The specified device is currently mounted, use '--force' to override.");
                promptline();
            }
            if(force){
                printf("-devmgr: '--force' applied. Bypassing security checks...\n");
                sleep(500);
            }
            printf("Untrusting device: %s...\n", target->MountLocation);
            sleep(560);
            status(true, "devmgr","v");
            promptline();
        }
    }
    if(strcmpi(cmd->command[0], "whoami") == 0){
        if(sessiond.ObscenceName){
            printf("Who are you? You my friend, are the player. Non just a");
            printf("normal player. Your the player who set their name as profanity.\n");
        }
        if(settings.isDebug){
            printf("debug: SomeTerminalGame:users/%s\n", _universal_user_data_table.CurrentUser->Username);
            promptline();
        }
        printf("%s\n", _universal_user_data_table.CurrentUser->Username);
        promptline();   
    }
    if(strcmpi(cmd->command[0],"nuke") == 0){
        //choose what to do
        srand(time(0));
        if (rand() % 2 == 0){
            //even
            DoSomethingFunny(DEREFRENCE_NULL_PTR);
        } else {
            //odd
            DoSomethingFunny(INVALID_ARRAY_LOCATION);
        }
    }
    if(strcmpi(cmd->command[0],"unixTime") == 0){
        printf("Unix Epoch time is %llu\n",sessiond.UnixEpochTime);
        promptline();
    }
    if(sessiond.usingDebugCmd && strcmpi(cmd->command[0],"start") == 0){
        printf("Starting mainmenu(). . .\n");
        hidecursor();
        mainmenu();
    }


    //debugee
    if(sessiond.usingDebugCmd || settings.isDebug && strcmpi(cmd->command[0], "debug") == 0){

        if(strcmpi(cmd->command[1],"help") == 0){
            printf("debug / help\n");
            printf("all commands are to be prefixed with \"debug\"\n");
            printf("-------------------------------------------------------\n");
            printf("    setaccesslevel <int>        Set's your access level to the specified integer\n");
            printf("    thread                      Any command regarding threads\n");
            printf("    set <value> <boolean>       Set a specified value to a boolean\n");
            printf("    builtin                     Display builtin macros\n");
            printf("    forcefatal                  Force a fatal error\n");
            printf("    session                     Display contents of sessiond\n");
            printf("    memory                      Commands related to memory usage\n");
            printf("    bp                          Breakpoints\n");
            printf("    raise <signal>              Raise a specified signal\n");
            printf("    stack                       Modify & view the stack.\n");
            printf("    setAttackTime               Set's the value for Enemyd.TimeUntilNextAttack.\n");
            printf("    getAttackTime               Get's the value at Enemyd.TimeUntilNextAttack.\n");
            printf("    objregistry                 Some Terminal Game's object registry.\n");
            printf("    exitnow                     Exit SomeTerminalGame ASAP without calling quit()\n");
            printf("    runapi Function <args...>   Run a function from stg.core.api.dll\n");
            printf("    powerout                    Command related to poweroutage event.\n");
            printf("    experiments                 Enable or disable experiments.\n");
            printf("    win-reg                     Registry experiment\n"); 
            printf("    hook                        Hook API stuff.\n");
            printf("    put \"help\" after any command for extra information\n");
        }

        if(strcmpi(cmd->command[1],"hook") == 0){
            if(strcmpi(cmd->command[2],"help")==0){
                printf("SomeTerminalGame/help/hook\n");
                printf("===================================\n");
                printf("  enable        Enabled the hook event on registry operations. (testing)\n");
            }
            if(strcmpi(cmd->command[2],"enable")==0){
                hRegistry.AddFunction(&hRegistry,hRegistry_ev);
            }
            promptline();
        }

        if(strcmpi(cmd->command[1],"win-reg") == 0){
            if(strcmpi(cmd->command[2],"help") == 0){
                printf("SomeTerminalGame/help/win-reg\n");
                printf("===================================\n");
                printf("  init                  Create default registry values.\n");
                printf("  read <type> <name>    Read from a registry value of the specifed type.\n");
                printf("  set <type> <name>     Change a value.\n");
                printf("  types                 List of supported types.\n");
                printf("  reset                 Same thing as starting option '--reset'\n");
                printf("  list                  List contents inside \\REGISTRY\\HKEY_CURRENT_USER\\%s\n",REG_PATH);
                promptline();
            }
            if(strcmpi(cmd->command[2],"list")==0){
                RegistryPrintList();
                promptline();
            }
            if(strcmpi(cmd->command[2],"types") == 0){
                printf("REG_SZ\n");
                printf("REG_DWORD\n");
                promptline();
            }
            if(strcmpi(cmd->command[2],"set") == 0){
                if(strcmp(cmd->command[3],"REG_SZ") == 0){
                    //set string
                    char *ret = RegistryReadSz(cmd->command[4]);
                    printf("REGISTRY\\HKEY_CURRENT_USER\\%s\\%s = \"%s\" --> \"%s\"\n",REG_PATH,cmd->command[4],ret,cmd->command[5]);
                    RegistrySetSz(cmd->command[4],cmd->command[5]);
                    promptline();
                } else if(strcmp(cmd->command[3],"REG_DWORD") == 0){
                    //set dword
                    DWORD data = RegistryReadDword(cmd->command[4]);
                    printf("REGISTRY\\HKEY_CURRENT_USER\\%s\\%s = %d --> %d\n",REG_PATH,cmd->command[4],data,atoi(cmd->command[5]));
                    RegistrySetDword(cmd->command[4],atoi(cmd->command[5]));
                    promptline();
                } else {
                    printf("Invalid type\n");
                    promptline();
                }
            }
            if(strcmpi(cmd->command[2],"read") == 0){
                if(strcmp(cmd->command[3],"REG_SZ") == 0){
                    //read string
                    char *ret = RegistryReadSz(cmd->command[4]);
                    printf("REGISTRY\\HKEY_CURRENT_USER\\%s\\%s = \"%s\"\n",REG_PATH,cmd->command[4],ret);
                    promptline();
                } else if(strcmp(cmd->command[3],"REG_DWORD") == 0){
                    //read dword
                    DWORD ret = RegistryReadDword(cmd->command[4]);
                    printf("REGISTRY\\HKEY_CURRENT_USER\\%s\\%s = %lu\n",REG_PATH,cmd->command[4],ret);
                    promptline();
                } else {
                    printf("Invalid type\n");
                    promptline();
                }
            }
            if(strcmpi(cmd->command[2],"reset")==0){
                printf("reset: REGISTRY\\HKEY_CURRENT_USER\\%s\n",REG_PATH);
                RegistryReset();
                promptline();
            }
        }

        if(strcmpi(cmd->command[1],"powerout") == 0){
            if(strcmpi(cmd->command[2],"help") == 0){
                printf("SomeTerminalGame/help/powerout\n");
                printf("=======================================\n");
                printf("  allow <boolean>       Determines if powerouts should occur.\n");
                printf("  try                   Attepts a poweroutage via calling AttemptPowerout()\n");
                printf("  when                  Set's the value of sessiond.Poweroff.When\n");
            }
            if(strcmpi(cmd->command[2],"allow") == 0){
                if(strcmpi(cmd->command[3],"true") == 0){
                    bool new = true;
                    HANDLE_debugmsg("settings.AllowPowerout = %s -> %s",btos(settings.AllowPowerout),btos(new));
                    settings.AllowPowerout = new;
                } else if(strcmpi(cmd->command[3],"false") == 0){
                    bool new = false;
                    HANDLE_debugmsg("settings.AllowPowerout = %s -> %s",btos(settings.AllowPowerout),btos(new));
                    settings.AllowPowerout = new;
                } else {
                    printf("ERROR: Required argument of type BOOLEAN not given or found.\n");
                    promptline();
                }
                dbg_status(true,"r");
                promptline();
            }

            if(strcmpi(cmd->command[2],"try") == 0){
                if(AttemptPowerout()){
                    screen_powerloss();
                }
                promptline();
            }

            if(strcmpi(cmd->command[2],"when") == 0){
                long long unsigned new = (long long unsigned)atoi(cmd->command[3]);
                HANDLE_debugmsg("sessiond.Poweroff.When = %llu -> %llu",sessiond.Poweroff.When,new);
                sessiond.Poweroff.When = new;
                dbg_status(true,"v");
            }
        }

        if(strcmpi(cmd->command[1],"launchAttack") == 0){
            if(strcmpi(cmd->command[2],AttackTypeStrings[AttackType_Network]) == 0){
                tzssCreateInturrupt(AttackType_Network,atoi(cmd->command[3]));
                promptline();
            }
            if(strcmpi(cmd->command[2],AttackTypeStrings[AttackType_SystemFile]) == 0){
                tzssCreateInturrupt(AttackType_SystemFile,atoi(cmd->command[3]) == 0);
                promptline();
            }
        }

        if(strcmpi(cmd->command[1],"stack") == 0){
            if(strcmpi(cmd->command[2],"dump") == 0){
                dumpStack();
                dbg_status(true,"b");
                promptline();
            }
            if(strcmpi(cmd->command[2],"flush") == 0){
                int v = flushStack();
                if(v != 0){
                    dbg_status(false,"The stack is halted.");
                    promptline();
                }
                dbg_status(true,"b");
                promptline();
            }
            if(strcmpi(cmd->command[2],"setwarn") == 0){
                int new = atoi(cmd->command[3]);
                if(new < 65 && strcmpi(cmd->command[4],"--force") != 0){
                    HANDLE_debugmsg("illegal value for stackd.warnSize: less than 65.");
                    HANDLE_debugmsg("use '--force' to override this safeguard.");
                }
                printf("debug: stackd.warnSize: %d -> %d\n",stackd.warnSize,new);
                stackd.warnSize = new;
                promptline();
            }
            if(strcmpi(cmd->command[2],"data") == 0){
                printf("Some Terminal Game Stack Data\n");
                printf("-------------------------------------\n\n");
                printf("  stackd.addrCnt        %d\n",stackd.addrCnt);
                printf("  stackd.symbolCnt      %d\n",stackd.symbolCnt);
                printf("  stackd.maxSize        %d\n",stackd.maxSize);
                printf("  stackd.warnSize       %d\n",stackd.warnSize);
                printf("  stackd.stackHalted    <%s>\n",btos(stackd.stackHalted));
                promptline();
            }
            if(strcmpi(cmd->command[2],"help") == 0){
                printf("SomeTerminalGame/help/stack\n");
                printf("---------------------------------\n");
                printf("flush       flush the stack with 0's\n");
                printf("dump        dumps the stack to the console.\n");
                printf("data        Contents of stackd.\n");
                printf("setwarn     Set the value of stackd.warnSize\n");
                promptline();
            }
        }

        if(strcmpi(cmd->command[1],"setlevel") == 0){
            int al = atoi(cmd->command[2]);
            lvlunlock(atoi(cmd->command[2]));
            dbg_status(true, "v");
            promptline();
        }

        if(strcmpi(cmd->command[1], "setaccesslevel") == 0){
            int al = atoi(cmd->command[2]);
            changeaccesslevel(al);
            dbg_status(true, "v");
            promptline();
        }


        if(strcmpi(cmd->command[1],"thread") == 0){
            if(strcmpi(cmd->command[2],"help")==0){
                printf("SomeTerminalGame/help/threads\n");
                printf("----------------------------------\n");
                printf("list            list active threads\n");
                printf("stop <thread>   stop a thread\n");
                promptline();
            }
            if(strcmpi(cmd->command[2],"list") == 0){
                printf("SomeTerminalGame/Threads\n");
                printf("---------------------------------\n");
                for(int i = 0; i < ThreadCnt; i++){
                    printf("threads/%s\n", ThreadNames[i]);
                    printf("    Thread ID:  %d\n",GetThreadId(ThreadList[i]));
                    printf("    Priority:   %s\n",ThreadPriorityAsString(ThreadList[i]));
                }
                promptline();
            }
            if(strcmpi(cmd->command[2],"stop") == 0){
                if(strcmpi(cmd->command[3],"main") == 0 && strcmpi(cmd->command[4],"--force") != 0){
                    printf("debug: illegal stop: termination of threads/main is prohibited.\n");
                    printf("debug: use '--force' to override this safeguard.\n");
                    promptline();
                }
                for(int i = 0; i < ThreadCnt; i++){
                    if(strcmpi(cmd->command[3],ThreadNames[i]) == 0){
                        _thread_remove(ThreadNames[i],ThreadList[i]);
                        break;
                    }
                }
                promptline();
            }
        }

        if(strcmpi(cmd->command[1],"exitnow") == 0){
            exit(0);
        }

        if(strcmpi(cmd->command[1],"set") == 0){
            if(strcmpi(cmd->command[2],"help")==0){
                printf("SomeTerminalGame/help/set\n");
                printf("----------------------------------\n");
                printf("    LogTempActions      sessiond.LogTemporaryContainerActions\n");
                promptline();
            }
            if(strcmpi(cmd->command[2], "LogTempActions") == 0){

                if(strcmpi(cmd->command[3],"true") == 0){
                    sessiond.LogTemporaryContainerActions = true;
                    dbg_status(true, "v");
                    promptline();
                }

                if(strcmpi(cmd->command[3],"false") == 0){
                    sessiond.LogTemporaryContainerActions = false;
                    dbg_status(true, "v");
                    promptline();
                }
                dbg_status(false, "Invalid value");
                promptline();
            }
            promptline();
        }

        if(strcmpi(cmd->command[1],"builtin") == 0){
            ShowBuiltinInformation();
            promptline();
        }

        if(strcmpi(cmd->command[1], "forcefatal") == 0){
            HANDLE_fatal("DEBUG_FORCE_FATAL",__DEBUG_FORCE_FATAL);
            promptline();
        }

        if(strcmpi(cmd->command[1], "session") == 0){
            _displaySessionData();
            promptline();
        }

        if(strcmpi(cmd->command[1],"memory") == 0){
            if(strcmpi(cmd->command[2],"help") == 0){
                printf("help / debug / memory");
                printf("------------------------------------\n");
                printf("    debug memory info                   : Display memory information\n");
                printf("    debug memory flushworkingset        : Flush the working set\n");
                promptline();
            }

            if(strcmpi(cmd->command[2],"info") == 0){
                printf("Some_Terminal_Game Memory Usage Information\n");
                printf("------------------------------------------------\n\n");
                winapi_print_memory_information(GetCurrentProcessId());
                dbg_status(true,"b");
                promptline();
            }

            if(strcmpi(cmd->command[2],"FlushWorkingSet") == 0){
                MEMORY_FlushWorkingSet(GetCurrentProcessId());
                dbg_status(true,"b");
                promptline();
            }

        }
        if(strcmpi(cmd->command[1], "bp") == 0){ //breakpoints

            if(strcmpi(cmd->command[2], "create") == 0){
                strcpy(sessiond.bp_func, cmd->command[3]);
                printf("debug: created breakpoint on FunctionCall:unknown:%s()\n", cmd->command[3]);
                dbg_status(true, "b");
                promptline();
            }

            if(strcmpi(cmd->command[2], "clear") == 0){
                strcpy(sessiond.bp_func, "__NO_BREAKPOINT_FUNCTION_DEFINED__");
                dbg_status(true, "v");
                promptline();
            }

            if(strcmpi(cmd->command[2], "help") == 0){
                printf("help / debug / bp\n");
                printf("------------------------------------\n");
                printf("    debug bp create <FUNCTION NAME> : Create a breakpoint on the specified function name.\n");
                printf("    debug bp clear                  : Clear the breakpoint.\n\n");
                promptline();
            }
        }
        if(strcmpi(cmd->command[1],"getAttackTime") == 0){
            printf("debug: Enemyd.TimeUntilNextAttack: %llu\n",Enemyd.TimeUntilNextAttack);
            promptline();
        }
        if(strcmpi(cmd->command[1],"setAttackTime") == 0){
            long long unsigned new = (long long unsigned)atoi(cmd->command[2]);
            printf("debug: Enemyd.TimeUntilNextAttack: %llu -> %llu\n",Enemyd.TimeUntilNextAttack,new);
            Enemyd.TimeUntilNextAttack = new;
            promptline();
        }
        if(strcmpi(cmd->command[1], "raise") == 0){

            if(strcmpi(cmd->command[2],"sigsegv") == 0){
                raise(SIGSEGV);
            }

            if(strcmpi(cmd->command[2], "sigabrt") == 0){
                raise(SIGABRT);
            }

            if(strcmpi(cmd->command[2], "sigfpe") == 0){
                raise(SIGFPE);
            }

            if(strcmpi(cmd->command[2], "sigill") == 0){
                raise(SIGILL);
            }

            dbg_status(false, "Unknown signal");
            promptline();
        }
    }
    promptline();
    return 0;
}

int setdebug(bool e){
    _stack_;
    _check_bp;
    settings.isDebug = e;
    return 0;
}

int forceexit(int TERM_type){
    _check_bp;
    _stack_;
    //destoryTemporaryContentContainer();
    //CloseHandle(htKbdListen);
    quit(TERM_type);
    return 0;
}

bool alreadyunlockedlvl1 = false;
char cha;
int promptline(){
    _check_bp;
    signal_init();
    _stack_;
    if(xp >= 10){
        _sleep(500);
        if(alreadyunlockedlvl1 == false){
            alreadyunlockedlvl1 = true;
            lvlunlock(1);
            $points += 25;
            changeaccesslevel(1);
        }
    }
    _command cmd_input;
    char *temp = malloc(1024);
    int len = 0;
    while(strlen(cmd_input.raw_data) == 0){
        printf("->",(len));
        gets_s(temp, 1024);
        strcpy(cmd_input.raw_data, temp);
    }
    free(temp);

    /* 
    *
    *   command parser
    *   took me a while to make
    *   do NOT fuck with this please
    * 
    */
    _command parse;
    int count, i;
    char **tokens;
    strcpy(parse.raw_data, cmd_input.raw_data);
    parse.argument_count = split(cmd_input.raw_data, ' ', &tokens);

    for(int i = 0; i < parse.argument_count; i++){
        if(strcmpi(tokens[i], "--force") == 0){
            parse.execution_flags = _EXECUTION_FORCE;
        } else if(strcmpi(tokens[i], "--verbose") == 0){
            parse.execution_flags = _EXECUTION_VERBOSE;
        } else if(strcmpi(tokens[i], "--force") == 0 && strcmpi(tokens[i], "--verbose") == 0){
            parse.execution_flags = _EXECUTION_BOTH;
        } else {
            parse.execution_flags = _EXECUTION_STD;
        }
        strcpy(parse.command[i], tokens[i]);
    }
    free(tokens);
    execute(&parse);

    return 0;
}

int debugConsole(void){
    _check_bp;
    signal_init();
    addStack(__FUNCTION__);
    ETC_file(_FILE_DEBUG_LOG,"using debug console","a","OUT");
    _backend_SwapCurrentUser(debugee);
    printf("\nSomeTerminalGame/DebugConsole\n");
    printf(" Startup information:\n");
    printf("    isDebug=%s\n",btos(settings.isDebug));
    printf("    PID=%d\n",sessiond.PID);
    printf("    sessionID=%d\n",sessiond.sessionID);
    printf("    timeToStart=%.2fs\n",sessiond.timeToStart);
    printf("  \n");
    printf("type \"start\" to start the mainmenu and exit the debug console.\n");
    while(1){
        promptline();
    }
}

bool already_asked_for_log_file = false;
int game(void) {
    _check_bp;
    signal_init();
    _stack_;
    ETC_file(_FILE_DEBUG_LOG,"starting game loop","a","OUT");
    extern session_informaton sessiond;
    //start the game
    system("cls");
    HANDLE_notice("The game is currently loading. . .");
    _sleep(1000);
    system("cls");
    //main
    if(sessiond.FirstRun){
        sessiond.FirstRun = false;
        printf("Welcome to TerminalZ!\n");
        printf("It looks like this is the first time you ran TerminalZ.\n\n");
        sleep(670);
        printf("Loading setup. . .\n");
        sleep(200);
        printf("-TZ_KRNL: Starting /usr/terminalz/firstrun/helper\n");
        sleep(500);
        printf("-/usr/terminalz/firstrun/helper: Acquiring session information. . .\n");
        sleep(1200);
        printf("-/usr/terminalz/firstrun/helper: Starting /usr/terminalz/firstrun/setup");
        sleep(600);
        setup();
    } else if(sessiond.SetupCompleted && !sessiond.LoggedIn) {
        login();
    }
    system("cls");
    _tzss_prompt();
    Enemyd.isAttackAllowed = true;
    system("cls");
    printf("TerminalZ | Current IP: 127.0.0.1\n");
    printf("-----------------------------------------\n");
    if(sessiond.ObscenceName){
        printf("You should be ashamed of yourself. Look at what name you're using.\n");
        printf("This action will have dire consequences. Good luck, %s", _universal_user_data_table.CurrentUser->Username);
    }
    ETC_file(_FILE_DEBUG_LOG,"start game loop","a","OUT");
    while(1) {
        promptline();
    }
}

#pragma message("===> Reached end of file...")
#pragma message("===> Successfully built SomeTerminalGame.c --> SomeTerminalGame.exe ")