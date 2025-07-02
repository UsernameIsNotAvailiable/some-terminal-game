#ifndef TOPRIGHT_TEXT
#define TOPRIGHT_TEXT
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

typedef struct{
    char *text;
    size_t len;
}_topRText,*p_topRText;

typedef struct _topright_text{
    void (*AddText)(struct _topright_text* self,const char *format,...);
    void (*EditText)(struct _topright_text* self,int index,const char *format,...);
    void (*Flush)(struct _topright_text* self);
    _topRText Text[15];
    int currentIndex;
}_topright_text,*p_topright_text;

void __topright_internal_Flush(p_topright_text self){
    _stack_;
    for(int i = 0; i < 15; i++){
        self->EditText(self,i,"%*s",50," ");
    }
}

void __topright_internal_EditText(p_topright_text self,int index,const char *format,...){
    _stack_;
    va_list args;
    va_start(args,format);
    char buffer[256];
    int r = vsprintf(buffer,format,args);
    va_end(args);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    int x = columns - strlen(buffer);
    int y = index;

    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    //self->Text[index].len = strlen(buffer);
    //strcpy(self->Text[index].text,buffer);
    printf("%s", buffer);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),csbi.dwCursorPosition);
}

void __topright_internal_AddText(p_topright_text self,const char *format,...){
    _stack_;
    va_list args;
    va_start(args,format);
    char buffer[256];
    int r = vsprintf(buffer,format,args);
    va_end(args);

    
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;
    
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    
    int x = columns - strlen(buffer);
    int y = self->currentIndex;
    
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    printf("%s", buffer);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),csbi.dwCursorPosition);
    self->currentIndex++;
}

void CreateTopRight(p_topright_text top){
    top->AddText = __topright_internal_AddText;
    top->EditText = __topright_internal_EditText;
    top->Flush = __topright_internal_Flush;
    top->currentIndex = 0;
}

#endif