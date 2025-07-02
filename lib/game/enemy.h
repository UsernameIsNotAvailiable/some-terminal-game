#ifndef _ENEMY_F
#define _ENEMY_F
#pragma message("===> Building file "__FILE__)


#include <windows.h>
#include "../handle/debug/c_handle.h"
#include "../handle/debug/etc/error.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "resources.h"

#define _check_bp bp_check(__FUNCTION__)
#define _stack_ addStack(__FUNCTION__)

extern session_informaton sessiond;
extern external_settings settings;
extern enemy_data Enemyd;
extern TZ_Security_System tzss;
extern device ethernet;

bool queryAttack(void){
    _stack_;
    _check_bp;
    signal_init();
    if(sessiond.LoggedIn && Enemyd.isAttackAllowed && !Enemyd.isOnBreak){
        return true;
    } else {
        return false;
    }
    return true;
}

bool createRemoteConnection(){
    signal_init();
    if(!queryAttack()){
        return false;
    }
    if(!ethernet.Mounted){
        return false;
    }
    if(!sessiond.Level >= 2){
        return false;
    }
    sessiond.remoteConnection = true;
    return true;
}


int remoteCommandExec(char *command, ...){
    signal_init();
    _stack_;
    _check_bp;
    ETC_file(_FILE_DEBUG_LOG,"threads/Enemy attempting remoteCommandExec","a","OUT");
    if(!createRemoteConnection() && settings.isDebug){
        threadPrint("Enemy","ether: %s\n",btos(ethernet.Mounted));
        threadPrint("Enemy","level: %d\n",sessiond.Level);
        threadPrint("Enemy","logged in: %s\n",btos(sessiond.LoggedIn));
        threadPrint("Enemy","attack allowed: %s\n",btos(Enemyd.isAttackAllowed));
        threadPrint("Enemy","on break: %s\n",btos(Enemyd.isOnBreak));
        return 1;
    }
    Enemyd.AttackStatus = true;
    Enemyd.Attackd.AttackStatus = true;

    _command cmd_input;
    va_list args;
    va_start(args,command);
    vsprintf(cmd_input.raw_data,command,args);

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
        count = i;
        strcpy(parse.command[i], tokens[i]);
    }
    if(settings.isDebug){
        printf("\n");
        threadPrint("Enemy","Remote command execution debug\n");
        threadPrint("Enemy","\tRaw command: \"%s\"\n",cmd_input.raw_data);
        threadPrint("Enemy","\tToken count: %d\n",count);
    }
    free(tokens);
    if(settings.isDebug){
        threadPrint("Enemy","Executing remote command: \"%s\"\n",parse.raw_data);
    }
    execute(&parse);
    if(settings.isDebug){
        threadPrint("Enemy","Successfully executed remote command!");
    }
    va_end(args);
    return 0;
}

#endif