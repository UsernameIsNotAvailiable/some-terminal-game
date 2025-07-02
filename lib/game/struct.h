
/////////////////////////////////////
//       Some_Terminal_Game        //
//       lib/game/struct.h         //
//                                 //
/////////////////////////////////////

//prepoccesor
#ifndef STRUCT_MAN
#define STRUCT_MAN
#pragma message("===> Building file "__FILE__)
#include <Windows.h>
#include <stdbool.h>
#include "topright.h"

typedef struct{
    char SSID[50];
    char PSWD[50];
    char SECURITY_TYPE[10];

    int SecurityLevel;
    bool HiddenNetwork;
    bool Rememberd;
    bool Connected;
}network;

typedef struct{
    char FriendlyName[50];
    char HardwareAddress[50];
    char MountPoint[50];
    char MountLocation[10];
    char type[10];
    int Corruption;

    bool Bootable;
    bool Trusted;
    bool Default;
    bool Mounted;
    bool CurrentDevice;
    bool Hidden;
}device;

typedef struct{
    char Name[50];
    char Source[50];
    char Host[50];

    bool Active;
    bool Trusted;
    bool Installed;
}package;

typedef struct{
    char FriendlyName[50];
    char IPv4[50];
    char IP[50];
    char AssociatedApplication[50];

    int ServerStatus;
}server;

typedef struct{
    int maxSize;
    int warnSize;
    int symbolCnt;
    int addrCnt;

    bool stackHalted;
}stack_data;

typedef struct{
    char username[50];
    bool LoggedIn;
    bool Elevated;
}pkg_user_data;

typedef struct{
    bool isDebug;
    bool SomeStevenEasterEgg;
    bool LogFileExist;
    bool IgnoreErrors;
    bool SuppressSplashMessage;
    bool AllowRegistry;
    bool AllowPowerout;
    bool DumpstackOnCrash;
    bool useRegistryCache;
    int ColorSelection;
}external_settings;

typedef struct{
    bool FileRead;
    bool FileWrite;
    bool DriveOperations;
    bool SuperUser;
    bool CanChangePassword;
    bool KernelPermissions;
    bool CanChangeUser;
    bool IsLoginAllowed;
    bool CanUseUsrmgr;
    bool CanChangeOthersPasswords;
}user_permissions;

typedef struct{
    user_permissions permissions;
    char Username[50];
    char Password[120];
    char HomeDir[256];
    int UserID;
    bool CurrentUser;
    bool Active;
}user;

typedef struct{
    bool StartArgsFetchFailure;
    int whoami_id;
    int helperPID;
}_sessiond_deprecated;

typedef struct{
    const bool testBuild;
    const bool publicRelease;
}_sharedConstants;

typedef struct{
    bool FirstRun;
    bool SuperUserPasswordSet;
    bool SetupCompleted;
    bool LoggedIn;
    bool skip;
    bool LogTemporaryContainerActions;
    bool HelperIsActive;
    bool ObscenceName;
    bool UseLegacyMemoryManager;
    bool usingDebugCmd;
    bool remoteConnection;

    UUID secretKey;
    HANDLE hProcess;
    int sessionID;
    int PID;
    int Level;
    struct{
        int Chance;
        int When; //unix time
        bool isPowerout;
    }Poweroff;
    unsigned long long UnixEpochTime;
    unsigned long long memLimit;
    
    double timeToStart;
    
    char bp_func[120];
    char _version_[120];
    char _exec_path_[256];
    char _installation_path_[256];
    char _verinfo[256];
    int build;
    DWORD mainThreadId;

    void *baseAddress;
    void *entryAddress; // main()

    _sessiond_deprecated deprecated;
    _sharedConstants SharedConstants;

    p_topright_text top;
}session_informaton;

typedef struct{
    bool InduceFatal;
    bool Disregard;
}_exception_actions;

typedef struct{
    char RawData[120];
    char Class[120];
    char subClass[120];
    char Value[120];
    char temp[120];
}usrmgr_cmd;

typedef struct{
    device *TrustedDevices[20];
    device *MountedDevices[20];
    device *UnmountDevices[20];
    device *AllDevices[20];
    device *CurrentDevice;
    int TrustedDevCount;
    int MountedDevCount;
    int UnmountedDevCount;
    int AllDevicesCount;
}dev_data;

typedef struct{
    user *CurrentUser;
    user *StandardUsers[20];
    user *SuperUsers[20];
    user *_Special[20];
    user *AllUsers[20];
    int UserCount;
    int SuperUserCount;
    int StandardUserCount;
    int SpecialUserCount;
}user_data;

typedef struct{
    bool SystemMemoryIntegrity;
    bool PreventSystemFileChanges;
    bool UnmountInvalidDisks;
    bool ControlNetworkFlow;
}security_policy;

typedef struct{
    bool enabled;
    bool AlreadyDisplayedEnablePrompt;
    security_policy policy;
    int ProtectionLevel;
}TZ_Security_System;

typedef struct{
    unsigned int start_args;
    unsigned int pid;
    unsigned int random_num;
}refferal_id;

typedef struct{
    char file[120];
    char identifer[120];
}_sound_item;

typedef struct{
    char last[10];
    char file[256];
    bool exist;
}_temporary_content_container_data;

typedef struct{
    int Wins;
    int Losses;
}_win_loss;

typedef struct{
    bool read;
    bool write;
    bool execute;
}_file_permissions;

typedef struct{
    char path[256];
    bool exists;
    bool directory;
}_file;

typedef struct{
    char Paramaters[4][256];
    int ParamCnt;
    bool show;
}_fatal_paramaters;

typedef struct{
    bool AttackStatus;
    enum AttackTypes Type;
    int Severity;
}_attack;

typedef struct{
    int TimeAttacked;
    int Level;
    long long unsigned TimeUntilNextAttack;
    bool isOnBreak;
    bool isAttackAllowed;
    bool AttackStatus;
    _attack Attackd;
    _win_loss WL;
}enemy_data;

typedef struct{
    UUID uuid;
    char *StringUUID;
}_identify;

typedef struct{
    char raw_data[1024];
    char command[50][1024];
    char argument_count;
    int execution_flags;
}_command, *_pCommand;

typedef struct{
    int high;
    int medium;
    int low;
    char asString[50];
}_MSC_verStruct;

typedef struct{
    char *EventName;
    int FunctionCnt;
    void (*Functions[50])(void);
}_event_class;

typedef struct{
    int RegistrerdEvents;
    bool EventsEnabled;

    _event_class *Events[50];
}_event_root;

typedef struct{
    char DosPath[MAX_PATH];
    char GuidPath[MAX_PATH];
    char NonePath[MAX_PATH];
    char NtPath[MAX_PATH];
    char Std[MAX_PATH];
}FilePaths;

#endif