
/////////////////////////////////////
//       Some_Terminal_Game        //
//       lib/game/usrmgr.h         //
//                                 //
/////////////////////////////////////

//preprocessor
#ifndef USRMGR_
#define USRMGR_
#pragma message("===> Building file "__FILE__)

//includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "resources.h"
#include "struct.h"
#include "screen.h"
#include "../handle/debug/c_handle.h"
#include "../handle/debug/etc/error.h"

//etc
extern user SYSTEM;
extern user root;
extern user standard;
extern user dummy;
extern session_informaton sessiond;
extern external_settings settings;

int usrmgr_fetch(user *_cur, user *_tar){
    addStack("usrmgr_fetch");
    printf("Starting user manager. . .\n");
    sleep(200);
    printf("Verifying permissions. . .\n");
    sleep(350);
    if(!_cur->permissions.CanUseUsrmgr || !_cur->permissions.SuperUser || !_cur->permissions.KernelPermissions){
        printf("-usrmgr: access denied\n");
        return 1;
    }
    printf("-usrmgr: fetching information of user:%s, UID:%d. . .\n", _tar->Username, _tar->UserID);
    sleep(50);
    printf("Fetching user information. . .\n");
    sleep(450);
    printf("Fetching user permissions. . .\n");
    sleep(1200);
    printf("Fetched!\n\n");
    sleep(50);
    printf("User information (info)---------------------------\n");
    printf("  Username: . . . . . . . . . . . %s\n", _tar->Username);
    printf("  Password: . . . . . . . . . . . <hidden>\n");
    printf("  UserID: . . . . . . . . . . . . %d\n", _tar->UserID);
    printf("  HomeDir:. . . . . . . . . . . . %s\n", _tar->HomeDir);
    printf("  Active: . . . . . . . . . . . . <%s>\n",btos(_tar->Active));
    printf("  CurrentUser:. . . . . . . . . . <%s>\n\n", btos(_tar->CurrentUser));

    printf("User permissions (permissions) --------------------\n");
    printf("  KernelPermissions: . . . . . . <%s>\n", btos(_tar->permissions.KernelPermissions));
    printf("  SuperUser: . . . . . . . . . . <%s>\n", btos(_tar->permissions.SuperUser));
    printf("  DriveOperations: . . . . . . . <%s>\n", btos(_tar->permissions.DriveOperations));
    printf("  FileRead:. . . . . . . . . . . <%s>\n", btos(_tar->permissions.FileRead));
    printf("  FileWrite: . . . . . . . . . . <%s>\n", btos(_tar->permissions.FileWrite));
    printf("  CanChangePassword: . . . . . . <%s>\n", btos(_tar->permissions.CanChangePassword));
    printf("  CanUseUsrmgr:. . . . . . . . . <%s>\n", btos(_tar->permissions.CanUseUsrmgr));
    printf("  CanChangeUser: . . . . . . . . <%s>\n", btos(_tar->permissions.CanChangeUser));
    printf("  IsLoginAllowed:. . . . . . . . <%s>\n\n", btos(_tar->permissions.IsLoginAllowed));
    return 0;
}

usrmgr_cmd _usrmgr_backend_parse(usrmgr_cmd *cmd){
    usrmgr_cmd _return;
    strcpy(_return.RawData, cmd->RawData);
    sscanf(_return.RawData, "%[^.]", _return.Class);
    sscanf(_return.RawData, "%*[^.].%[^=]", _return.subClass);
    sscanf(_return.RawData, "%*[^=]=%s", _return.Value);
    return _return;
}


char RegisterdClasses[2][120] = {"info","permissions"};
char RegisterdSubClass_info[6][120] = {"Username","HomeDir","Active","CurrentUser","UserID","Password"};
char RegisterdSubClass_permissions[9][120] = {"KernelPermissions","SuperUser","DriveOperations","FileRead","FileWrite","CanChangePassword","CanUseUsrmgr","CanChangeUser","IsLoginAllowed"};
int usrmgr_modify_prompt(user *_tar, user *_pool){
    usrmgr_cmd cmd;
    printf("usrmgr->");
    gets_s(cmd.RawData, 120);
    if(strcmp(cmd.RawData, "exit") == 0){
        status(true, "usrmgr","v","v");
        while(1){
            promptline();
        }
    }
    if(strcmp(cmd.RawData, "help") == 0){
        printf("-usrmgr: command syntax: <class>.<subclass>=<value>\n");
        printf("-usrmgr: example: info.Username=yes\n");
        printf("-usrmgr: exit - quit usrmgr\n");
        printf("-usrmgr: fetch - fetch user data\n");
        status(true, "usrmgr","v","v");
        usrmgr_modify_prompt(_tar, _pool);
    }
    if(strcmp(cmd.RawData, "fetch") == 0){
        printf("Fetching. . .\n\n");
        sleep(1200);
        printf("User information (info)---------------------------\n");
        printf("  Username: . . . . . . . . . . . %s\n", _tar->Username);
        printf("  Password: . . . . . . . . . . . <hidden>\n");
        printf("  UserID: . . . . . . . . . . . . %d\n", _tar->UserID);
        printf("  HomeDir:. . . . . . . . . . . . %s\n", _tar->HomeDir);
        printf("  Active: . . . . . . . . . . . . <%s>\n",btos(_tar->Active));
        printf("  CurrentUser:. . . . . . . . . . <%s>\n\n", btos(_tar->CurrentUser));

        printf("User permissions (permissions) --------------------\n");
        printf("  KernelPermissions: . . . . . . <%s>\n", btos(_tar->permissions.KernelPermissions));
        printf("  SuperUser: . . . . . . . . . . <%s>\n", btos(_tar->permissions.SuperUser));
        printf("  DriveOperations: . . . . . . . <%s>\n", btos(_tar->permissions.DriveOperations));
        printf("  FileRead:. . . . . . . . . . . <%s>\n", btos(_tar->permissions.FileRead));
        printf("  FileWrite: . . . . . . . . . . <%s>\n", btos(_tar->permissions.FileWrite));
        printf("  CanChangePassword: . . . . . . <%s>\n", btos(_tar->permissions.CanChangePassword));
        printf("  CanUseUsrmgr:. . . . . . . . . <%s>\n", btos(_tar->permissions.CanUseUsrmgr));
        printf("  CanChangeUser: . . . . . . . . <%s>\n", btos(_tar->permissions.CanChangeUser));
        printf("  IsLoginAllowed:. . . . . . . . <%s>\n", btos(_tar->permissions.IsLoginAllowed));
        printf("  CanChangeOthersPasswords . . . <%s>\n", btos(_tar->permissions.CanChangeOthersPasswords));
        status(true, "usrmgr","v");
        usrmgr_modify_prompt(_tar,_pool);
    }
    usrmgr_cmd _parsed = _usrmgr_backend_parse(&cmd);
    usrmgr_modify_execute(_tar, &_parsed, &_pool);
    return 0;
}

int usrmgr_modify_execute(user *_tar, usrmgr_cmd *cmd, user *_pool){
    if(strcmp(cmd->Class, RegisterdClasses[0]) != 0 && strcmp(cmd->Class, RegisterdClasses[1]) != 0){
        status(false, "usrmgr","unknown class");
        usrmgr_modify_prompt(_tar,_pool);
    }

    //class things
    if(strcmp(cmd->Class, "info") == 0){ //CLASS: INFO
        if(strcmp(cmd->subClass, "Active") == 0){
            if(strcmp(cmd->Value, "true") == 0){
                _tar->Active = true;
                _pool->Active = true;
                status(true, "usrmgr","v","v");
            } else if(strcmp(cmd->Value, "false") == 0){
                _tar->Active = false;
                _pool->Active = false;
                status(true, "usrmgr","v","v");
            } else {
                status(false, "usrmgr","incompatible value");
            }
        }
        if(strcmp(cmd->subClass, "CurrentUser") == 0){
            if(strcmp(cmd->Value, "true") == 0){
                _tar->CurrentUser = true;
                _pool->CurrentUser = true;
                status(true, "usrmgr","v");
            } else if(strcmp(cmd->Value, "false") == 0){
                _tar->CurrentUser = false;
                _pool->CurrentUser = false;
                status(true, "usrmgr","v","v");
            } else {
                status(false, "usrmgr","incompatible value");
            }
        }
        if(strcmp(cmd->subClass, "Username") == 0){
            if(strlen(cmd->Value) >= 50){
                status(false, "usrmgr","length limit exceeded");
            } else {
                for(int i = 0; i < _universal_user_data_table.UserCount; i++){
                    if(strcmp(_tar->Username, _universal_user_data_table.AllUsers[i]->Username) == 0){
                        strcpy(_universal_user_data_table.AllUsers[i]->Username, cmd->Value);
                        strcpy(_tar->Username, cmd->Value);
                    }
            }
                status(true, "usrmgr","v");
            }
        }
        if(strcmp(cmd->subClass, "HomeDir") == 0){
            if(strlen(cmd->Value) >= 50){
                status(false, "usrmgr","length limit exceeded");
            } else {
                strcpy(_tar->HomeDir, cmd->Value);
                strcpy(_pool->HomeDir, cmd->Value);
                status(true, "usrmgr","v");
            }
        }
    }   

    if(strcmp(cmd->Class, "permissions") == 0){ //CLASS: PERMISSIONS
        if(strcmp(cmd->subClass, "IsLoginAllowed") == 0){
            if(strcmp(cmd->Value, "true") == 0){
                _tar->permissions.IsLoginAllowed = true;
                _pool->permissions.IsLoginAllowed = true;
                status(true, "usrmgr","v");
            } else if(strcmp(cmd->Value, "false") == 0){
                _tar->permissions.IsLoginAllowed = false;
                _pool->permissions.IsLoginAllowed = false;
                status(true, "usrmgr","v","v");
            } else {
                status(false, "usrmgr","incompatible value");
            }
        }
        if(strcmp(cmd->subClass, "SuperUser") == 0){
            if(strcmp(cmd->Value, "true") == 0){
                _tar->permissions.SuperUser = true;
                _pool->permissions.SuperUser = true;
                status(true, "usrmgr","v");
            } else if(strcmp(cmd->Value, "false") == 0){
                _tar->permissions.SuperUser = false;
                _pool->permissions.SuperUser = false;
                status(true, "usrmgr","v");
            } else {
                status(false, "usrmgr","incompatible value");
            }
        }
        if(strcmp(cmd->subClass, "KernelPermissions") == 0){
            if(strcmp(cmd->Value, "true") == 0){
                _tar->permissions.KernelPermissions = true;
                _pool->permissions.KernelPermissions = true;
                status(true, "usrmgr","v");
            } else if(strcmp(cmd->Value, "false") == 0){
                _tar->permissions.KernelPermissions = false;
                _pool->permissions.KernelPermissions = false;
                status(true, "usrmgr","v");
            } else {
                status(false, "usrmgr","incompatible value");
            }
        }
        if(strcmp(cmd->subClass, "DriveOperations") == 0){
            if(strcmp(cmd->Value, "true") == 0){
                _tar->permissions.DriveOperations = true;
                status(true, "usrmgr","v");
            } else if(strcmp(cmd->Value, "false") == 0){
                _tar->permissions.DriveOperations = false;
                status(true, "usrmgr","v");
            } else {
                status(false, "usrmgr","incompatible value");
            }
        }
        if(strcmp(cmd->subClass, "FileWrite") == 0){
            if(strcmp(cmd->Value, "true") == 0){
                _tar->permissions.FileWrite = true;
                _pool->permissions.FileWrite = true;
                status(true, "usrmgr","v");
            } else if(strcmp(cmd->Value, "false") == 0){
                _tar->permissions.FileWrite = false;
                _pool->permissions.FileWrite = false;
                status(true, "usrmgr","v");
            } else {
                status(false, "usrmgr","incompatible value");
            }
        }
        if(strcmp(cmd->subClass, "FileRead") == 0){
            if(strcmp(cmd->Value, "true") == 0){
                _tar->permissions.FileRead = true;
                _pool->permissions.FileRead = true;
                status(true, "usrmgr","v");
            } else if(strcmp(cmd->Value, "false") == 0){
                _tar->permissions.FileRead = false;
                _pool->permissions.FileRead = false;
                status(true, "usrmgr","v");
            } else {
                status(false, "usrmgr","incompatible value");
            }
        }
        if(strcmp(cmd->subClass, "CanUseUsrmgr") == 0){
            if(strcmp(cmd->Value, "true") == 0){
                _tar->permissions.CanUseUsrmgr = true;
                _pool->permissions.CanUseUsrmgr = true;
                status(true, "usrmgr","v");
            } else if(strcmp(cmd->Value, "false") == 0){
                _tar->permissions.CanUseUsrmgr = false;
                _pool->permissions.CanUseUsrmgr = false;
                status(true, "usrmgr","v");
            } else {
                status(false, "usrmgr","incompatible value");
            }
        }
    }


    usrmgr_modify_prompt(_tar,_pool);
    return 0;
}




int usrmgr_modify(user *_cur, user *_tar){
    addStack("usrmgr_modify");
    user *_tar_pool;
    printf("Starting user manager. . .\n");
    sleep(200);
    printf("Verifying permissions. . .\n");
    sleep(350);
    if(!_cur->permissions.CanUseUsrmgr || !_cur->permissions.SuperUser){
        printf("-usrmgr: access denied\n");
        promptline();
    }
    //get the target in the user pool
    for(int i = 0; i < _universal_user_data_table.UserCount; i++){
        if(_tar->UserID == _universal_user_data_table.AllUsers[i]->UserID){
            _tar_pool = _universal_user_data_table.AllUsers[i];
        }
    }
    printf("\nModifying permissions of User:%s, UID:%d\n", _tar->Username, _tar->UserID);
    printf("---------------------------------------------\n");
    usrmgr_modify_prompt(_tar,_tar_pool);
    return 0;
}




#endif