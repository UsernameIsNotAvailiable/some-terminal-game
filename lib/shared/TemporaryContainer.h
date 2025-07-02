
/////////////////////////////////////
//       Some_Terminal_Game        //
// lib/shared/TemporaryConainer.h  //
//                                 //
/////////////////////////////////////

/*  NOTICE
This header compiles differently depending upon
if __APP_MAIN__ or __APP_HELPER__ is used during compilation.

This is used to avoid the helper conflicting over functions for __APP_MAIN__
*/

//preprocessor

#ifndef TMP_CONT
#define F_OK 0
#pragma message("===> Building file "__FILE__)
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef __APP_MAIN__

#define TEMP_CREATE 1
#define TEMP_QUERY 2
#define TEMP_WRITE 3
#define TEMP_DESTROY 4

#define ID_TEMP_CREATE "CREATE"
#define ID_TEMP_QUERY "QUERY"
#define ID_TEMP_WRITE "WRITE"
#define ID_TEMP_DESTROY "DESTROY"

#include "../handle/debug/c_handle.h"
#include "../handle/debug/etc/error.h"
#include "../game/resources.h"
#include "../game/struct.h"
#define _check_bp bp_check(__FUNCTION__)
#define _stack_ addStack(__FUNCTION__)

extern session_informaton sessiond;
_temporary_content_container_data TempContentData;

void LogAction(int actionClass){
    _stack_;
    _check_bp;
    if(!sessiond.LogTemporaryContainerActions){ //verify if the user want's to log temp cont actions
        return; //return because no
    }

    switch(actionClass){
        default:
            HANDLE_errormessage("Bad type in FunctionCall:void:LogAction() within switch operation on Variable:int:actionClass.", __BAD_TYPE);

        case TEMP_CREATE:
            HANDLE_debugmsg("TemporaryContainer: A temporary content container was created. Located at .\\data\\app\\RUNTIME.temp.");
            strcpy(TempContentData.last, ID_TEMP_CREATE);

        case TEMP_QUERY:
            HANDLE_debugmsg("TemporaryContainer: A query operation was preformed on a temporary container located at .\\data\\app\\RUNTIME.temp.");
            strcpy(TempContentData.last, ID_TEMP_QUERY);

        case TEMP_WRITE:
            HANDLE_debugmsg("TemporaryContainer: A write operation was preformed on a temporary container located at .\\data\\app\\RUNTIME.temp.");
            strcpy(TempContentData.last, ID_TEMP_WRITE);
        
        case TEMP_DESTROY:
            HANDLE_debugmsg("TemporaryContainer: A destory operation was preformed on a temporary container located at .\\data\\app\\RUNTIME.temp.");
            strcpy(TempContentData.last, ID_TEMP_DESTROY);
    }
}

int destoryTemporaryContentContainer(){
    DeleteFile(_FILE_TEMP);
    LogAction(TEMP_DESTROY);
    return 0;
}

int createTemporaryContentContainer(){
    _stack_;
    _check_bp;
    FILE *tmp;
    if(access(_FILE_TEMP, F_OK) == 0){
        destoryTemporaryContentContainer();
    }
    //create
    tmp = fopen(_FILE_TEMP, "w");
    strcpy(TempContentData.file, _FILE_TEMP);
    TempContentData.exist = true;
    LogAction(TEMP_CREATE);
    //close handle
    fclose(tmp);
    return 0;
}

int writeTemporaryContent(char msg[256]){
    _stack_;
    _check_bp;

    if(!TempContentData.exist){
        createTemporaryContentContainer();
    }
    FILE *t;
    t = fopen(_FILE_TEMP, "w");
    fprintf(t, msg);
    LogAction(TEMP_WRITE);
    fclose(t);
    return 0;
}

char *queryTemporaryContent(){
    _stack_;
    _check_bp;

    char *buffer = "placeholder";
    if(!TempContentData.exist){
        createTemporaryContentContainer();
    }
    FILE *t;
    t = fopen(_FILE_TEMP, "r");
    fgets(buffer, 256, t);
    LogAction(TEMP_QUERY);
    fclose(t);
    return buffer;
}
#endif // __APP_MAIN__

#ifdef __APP_HELPER__
//the helper is prohibited from deleting or creating RUNTIME.temp
//because of this, the helper can only query and write
//helper related function are to be prefixed with h_

int h_writeTemporaryContent(char msg[256]){
    FILE *t;
    t = fopen(_FILE_TEMP, "w");
    fprintf(t, msg);
    fclose(t);
    return 0;
}

char *h_queryTemporaryContent(){
    char *buffer = "placeholder";
    FILE *t;
    t = fopen(_FILE_TEMP, "r");
    fgets(buffer, 256, t);
    fclose(t);
    return buffer;
}

int external_WriteLog(char file_name[50], char msg[500], char mode[2], char type[20], ...){
    if(strlen(file_name) == 0){
        return 1;
    }
    if(strlen(msg) == 0){
        return 1;
    }
    if(strlen(mode) == 0){
        return 1;
    }
    if(strlen(type) == 0){
        return 1;
    }

    FILE *ftr; //declare file
    ftr = fopen(file_name, mode); //create the file with char mode[2]
    if(ftr == NULL){
        return 1;
    }

    //time stuff
    time_t t  = time(NULL);
    struct tm tm = *localtime(&t);
    
    //write to file
    fprintf(ftr, "%d/%d/%d %d:%d:%d[log:%s]     : %s\n", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec, type, msg); //month : day : year : hour : minute : seconds : type : msg

    //close
    fclose(ftr);
    return 0;
}

#endif // __APP_HELPER__

#endif