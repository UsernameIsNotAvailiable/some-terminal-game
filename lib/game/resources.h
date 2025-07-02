
/////////////////////////////////////
//       Some_Terminal_Game        //
//      lib/game/resources.h       //
//                                 //
/////////////////////////////////////

#pragma once
#ifndef GAME_RESOURCES
#define GAME_RESOURCES
#pragma message("===> Building file "__FILE__)

#define _check_bp bp_check(__FUNCTION__)
#define _stack_ addStack(__FUNCTION__)

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include "../handle/debug/etc/error.h"
#include "struct.h"
#include <stdarg.h>
char *RegistryReadSz(char *ValueName);

#define COLOR_RED 4
#define COLOR_BLUE 3
#define COLOR_PINK 01
#define COLOR_GREEN 2
#define COLOR_YELLOW 6
#define COLOR_PURPLE 5
#define COLOR_WHITE 00

//externs
extern external_settings settings;
extern session_informaton sessiond;
extern TZ_Security_System tzss;

enum AttackTypes {
    AttackType_Network,
    AttackType_SystemFile,
    AttackType_RemoteControl,
    AttackType_AccessLevelChange,
    AttackType_Test,
};

const char *AttackTypeStrings[] = {
    "AttackVector/Network",
    "AttackVector/SystemFile",
    "AttackVector/RemoteControl",
    "AttackVector/AccessLevelChange",
    "AttackVector/DebugTest",
};
#define menuArrow "  \xE2\x96\xB6   "

char *btos(bool b);

char* strip_to_last_slash(const char* str) {
    if (str == NULL) {
        return NULL; // Handle null input
    }

    const char* last_slash = strrchr(str, '/');

    if (last_slash == NULL) {
        char* result = strdup(str);
        return result;
    } else {
        char* result = strdup(last_slash + 1);
        return result;
    }
}

int howLongBtmLeft = 0;
int howLongBtmRight = 0;

void flushBottomLeft(void){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int rows, cols;
    
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    
    COORD coord = {0, rows - 1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("%*s",howLongBtmLeft," ");
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),csbi.dwCursorPosition);
}

void flushBottomRight(void){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    int x = columns - howLongBtmRight;
    int y = rows - 1;

    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    printf("%*s", howLongBtmRight, " ");
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),csbi.dwCursorPosition);
}

void flushBottom(void){
    flushBottomLeft();
    flushBottomRight();
}

void printBottomLeft(const char* text) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int rows, cols;
    
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    
    COORD coord = {0, rows - 1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("%s", text);
    howLongBtmLeft = strlen(text);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),csbi.dwCursorPosition);
}



void printBottomRight(const char* text) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    int x = columns - strlen(text);
    int y = rows - 1;

    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    howLongBtmRight = strlen(text);
    printf("%s", text);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),csbi.dwCursorPosition);
}

void printBottomRightv(const char *fmt, ... ){
    _stack_;
    va_list args;
    va_start(args,fmt);
    char buffer[1024];
    int r = vsprintf(buffer,fmt,args);
    printBottomRight(buffer);
    va_end(args);
}

void printBottomLeftv(const char *fmt, ... ){
    _stack_;
    va_list args;
    va_start(args,fmt);
    char buffer[1024];
    int r = vsprintf(buffer,fmt,args);
    printBottomLeft(buffer);
    va_end(args);
}

int showBottomInfo(void){
    printBottomLeftv("Version %s build %d", sessiond._version_,sessiond.build);
    if(settings.isDebug){
        printBottomRightv("isDebug <%s>; PID %d; sessionID %d; timeToStart %.2fs",
                            btos(settings.isDebug),sessiond.PID,
                            sessiond.sessionID,sessiond.timeToStart);
    }
    topinfo();
    return 0;
}

#define RED "\033[0;31m"
int topinfo(void){
    if(sessiond.SharedConstants.testBuild){
        sessiond.top->EditText(sessiond.top,0,"[!!] THIS IS A TEST BUILD - EXPECT CRASHES [!!]");
        resetColor();
    }
    return 0;
}

void hidecursor(){
    _stack_;
    _check_bp;
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   GetConsoleCursorInfo(consoleHandle,&info);
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void showcursor(){
    _stack_;
    _check_bp;
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(consoleHandle,&info);
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

#define BOX_HLINE "\xE2\x94\x80"
#define BOX_VLINE "\xE2\x94\x82"

void menubar(void){
    for(int i = 0; i < 44; i++){
        printf(BOX_HLINE);
    }
    printf("\n");
}

#define pthread(...) (threadPrint(__FUNCTION__,__VA_ARGS__))

inline int threadPrint(const char *thread, const char *in, ... ){
    _stack_;
    va_list args;
    va_start(args,in);
    printf("[ threads/%s (id: %d) ] ",thread,GetCurrentThreadId());
    int r = vprintf(in,args);
    va_end(args);
    return r;
}

int alert(char msg[120]) {
    _stack_;
    _check_bp;
    addStack("alert");
    printf("[ ALERT ] %s\n", msg);

    return 0;
}

int tzssCreateInturrupt(enum AttackTypes AttackVec,int Severity) {
    _stack_;
    _check_bp;
    if(tzss.policy.ControlNetworkFlow && tzss.enabled){
        printf("\n[ CRITICAL SYSTEM INTURRUPT ]\n");
        printf("Terminal Z Security System has detected a security incident.\n");
        printf("    Type:       %s\n",AttackTypeStrings[AttackVec]);
        printf("    Severity:   %d\n\n",Severity);
        switch(AttackVec){
            case AttackType_Network:
                printf("Try running 'net hide' to combat this attack.\n");
                break;

            case AttackType_SystemFile:
                printf("Try running 'system-clean' to combat this attack.\n");
                break;

            default:
                printf("Unknown?\n");
                break;
        }
    }
    promptline();
    return 0;
}

int error(const char *msg, ... ) {
    _stack_;
    _check_bp;
    va_list args;
    va_start(args,msg);
    printf("[ ERROR ] ");
    int r = vprintf(msg,args);
    va_end(args);
    return r;
}

bool ObscenceNameChecker(user *usr){
    _stack_;
    int count = 10;
    char list[20][120] = {"fuck","shit","dumbass","sex","fucker","motherfucker","shitter","penis","vagina","pussy"};
    for(int i = 0; i < 10; i++){
        if(strcmpi(usr->Username, list[i]) == 0){
            sessiond.ObscenceName = true;
            return true;
        }
    }
    sessiond.ObscenceName = false;
    return false;
}

char *get_password(char msg[50]){
    _stack_;
    _check_bp;
    addStack("get_password");
    int i = 0;
    char ch;
    char *password = (char*)malloc(51);
    printf("%s", msg);
    while (i < 50) {
        ch = getch();
        if ((int)ch == 27) {
            continue;
        } else if (ch == '\b') {
            if (i > 0) {
                printf("\b \b");
                --i;
            } else {
                continue;
            }
        } else if ((int)ch == '\r' || (int)ch == '\t') {
            break;
        } else if ((int)ch == 0 || (int)ch == 224) {
            ch = getch();
            continue;
        } else {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
    return password;
}

int panic(char *reason, ...){
    va_list args;
    va_start(args,reason);


    printf("\nsystem panic: ");
    vprintf(reason,args);
    va_end(args);
    printf("\n\npress [ENTER] key to reboot");
    char ch;
    while(1){
        if(kbhit){
            ch = getch();
            if(ch == 13){
                screen_reboot();
            }
        }
    }
}

char *DEPERCATED_get_password(char reason[120]){
    _stack_;
    _check_bp;
    char chv;
    char* pswd = (char*)malloc(121);
    char curlen = 0;

    printf("%s", reason);
    while(1){
        if(kbhit){
            chv = getch();
            if((int)chv == 13){
                if(settings.isDebug){
                    printf("\nvalue: %s\n", pswd);
                }
                return pswd;
            }
            if((int)chv == 8){
                if(curlen == 0){
                    continue;
                }
                memset(pswd, 0, curlen - 1);
                curlen -= 1;
                continue;
            }
            pswd[curlen] = chv;
            curlen += 1;
        }
    }
    printf("\n");
    return 0;
}

int remove_new_line(char* string){
    size_t length = strlen(string);
    if((length > 0) && (string[length-1] == '\n'))
    {
        string[length-1] ='\0';
    }
    return 0;
}

char *floodString(char str[120], char replace_char,bool showRedacted){
    _check_bp;
    addStack("floodString");
    if(strlen(str) <= 1){
        HANDLE_errormessage("Variable:char:str has invalid length in FunctionCall:char:floodString", __INVALID_STRING_LENGTH);
        return "\b";
    }


    for(int i = 0; i < strlen(str); i++){
        if(str[i] == ' '){
            continue;
        }
        str[i] = replace_char;
    }
    if(showRedacted){
        return "[ REDACTED ]";
    }
    return str;
}

char *btos(_Bool b){
    _check_bp;
    addStack("btos");
    return b ? "true" : "false";
}

void temp_dump_stack_thing(){
    _check_bp;
    dumpStack();
}

void GetUuid(UUID *uuid)
{
    UuidCreate(uuid);
    return;
};

bool
GetAllFilePaths(const char *fileName,FilePaths *paths){
    HANDLE file = CreateFileA(fileName,GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
    if(file == NULL){
        return false;
    }
    GetFullPathNameA(fileName,MAX_PATH,paths->Std,NULL);
    GetFinalPathNameByHandleA(file,paths->DosPath,sizeof(paths->DosPath),VOLUME_NAME_DOS);
    GetFinalPathNameByHandleA(file,paths->GuidPath,sizeof(paths->GuidPath),VOLUME_NAME_GUID);
    GetFinalPathNameByHandleA(file,paths->NonePath,sizeof(paths->NonePath),VOLUME_NAME_NONE);
    GetFinalPathNameByHandleA(file,paths->NtPath,sizeof(paths->NtPath),VOLUME_NAME_NT);
    CloseHandle(file);
    return true;
};

bool confirm(char msg[256]) {
    _check_bp;
    addStack("confirm");
    char ch;
    printf("%s [Y/N]", msg);
    while(1){
        ch = getch();
        if(ch == 'y'){
            printf("y\n");
            return true;
        }
        if(ch == 'n'){
            printf("n\n");
            return false;
        }
    }
}

int instant_reboot(){
    system("cls");
    sleep(250);
    screen_boot(false);
    return 0;
}

extern user_data _universal_user_data_table;
BOOL doesUsernameExist(const char username[120]){
    for(int i = 0; i < _universal_user_data_table.UserCount; i++){
        if(strcmp(username, _universal_user_data_table.AllUsers[i]->Username) == 0){
            return true;
        }
    }
    return false;
}

void rm_spaces(char* target){
    _check_bp;
    char* d = target;
    do {
        while(*d == ' '){
            ++d;
        }
    }while(*target++ = *d++);
}

int split(const char *txt, char delim, char ***tokens){
    signal_init();
    _check_bp;
    addStack("split");
    int *tklen, *t, count = 1;
    char **arr, *p = (char *) txt;

    while (*p != '\0') if (*p++ == delim) count += 1;
    t = tklen = calloc (count, sizeof (int));
    for (p = (char *) txt; *p != '\0'; p++) *p == delim ? *t++ : (*t)++;
    *tokens = arr = malloc (count * sizeof (char *));
    t = tklen;
    p = *arr++ = calloc (*(t++) + 1, sizeof (char *));
    while (*txt != '\0')
    {
        if (*txt == delim)
        {
            p = *arr++ = calloc (*(t++) + 1, sizeof (char *));
            txt++;
        }
        else *p++ = *txt++;
    }
    free (tklen);
    return count;
}

inline float _to_mb(unsigned long long const in){
    float bytes = 512LLU*1024LLU*in;
    return bytes/1048576;
}

inline void status(_Bool success, const char _cur[120], const char _reason[120], ...){
    _check_bp;
    addStack("status");
    if(success){
        printf("-%s: the operation completed successfully\n", _cur);
    } else {
        printf("-%s: the operation failed: %s\n", _cur, _reason);
    }
}

inline void dbg_status(_Bool success, const char _reason[120], ...){
    _check_bp;
    addStack("status");
    if(success){
        printf("debug: the operation completed successfully\n");
    } else {
        printf("debug: the operation failed: %s\n",_reason);
    }
}



#endif