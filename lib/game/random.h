
/////////////////////////////////////
//       Some_Terminal_Game        //
//   lib/game/notice_messages.h    //
//                                 //
/////////////////////////////////////

//preprocessor
#ifndef _RANDOM
#define _RAMDOM
#pragma message("===> Building file "__FILE__)
#define ARR_SIZE(arr) ( sizeof((arr)) / sizeof((arr[0])) )

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "resources.h"
#include "struct.h"
#include "../handle/debug/c_handle.h"
#include "../handle/debug/etc/error.h"

char *messages[120] = {
    "haha funny backspace\b",
    "this uses get_splash_text()",
    "hehe cool text",
    "int main(void)",
    "microsoft edge is bad",
    "if( notOkay ){\n    exit(1);\n}","hi","one developer!",
    "this game is buggy",
    "do not trust software",
    "stay safe on the internet",
    "do not give out your personal information",
    "i will add more splash text(s)",
    "this is a very useless feature",
    "(null) hours wasted",
    "yeah",
    "toeball or football",
};
int messages_count = 17;
//assign
char *get_splash_text(){
    addStack("get_splash_text");
    _check_bp;
    //check if it should be forefully set
    srand(time(0));
    int index;
    index = rand() % (messages_count + 1 - 0) + 0;
    return strdup(messages[index]);
}

#endif