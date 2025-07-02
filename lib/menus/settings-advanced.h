
/////////////////////////////////////
//       Some_Terminal_Game        //
//    lib/menus/settingsmenu.c     //
//                                 //
/////////////////////////////////////

//preprocessor

#pragma once
#ifndef SETTINGS_ADV
#define SETTINGS_ADV
#pragma message("===> Building file "__FILE__)

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "mainmenu.h"
#include "../handle/Registry.h"
//menu


DWORD alwaysDebug;
DWORD alwaysLogfile;
DWORD useRegistryCache;
bool advGotValues = false;
bool changed = false;

bool advGetValues(){
    _stack_;
    if(advGotValues){
        return false;
    } else {
        alwaysDebug = RegistryReadDword("alwaysDebug");
        alwaysLogfile = RegistryReadDword("alwaysLogfile");
        useRegistryCache = RegistryReadDword("useRegistryCache");
    }
    advGotValues = true;
    return true;
}

int advsettingsmaxopt = 4;
int advsettingsmenu() {
    _stack_;
    void advsettingsselect(int);
    advGetValues();
    system("cls");

    int i = 1;
    char ch;
    advsettingsselect(1);
    while(1) {
        ch = getch();

        switch(ch) {

            case 72: //up
                if(i != 1) {
                    i--;
                    advsettingsselect(i);
                } else {
                    i = advsettingsmaxopt;
                    advsettingsselect(i);
                }
                break;

            case 80: //down
                if(i != advsettingsmaxopt) {
                    i++;
                    advsettingsselect(i);
                } else {
                    i = 1;
                    advsettingsselect(i);
                }
                break;

                default:
                    break;

            case 13:
                if(i == 4) { //exit
                    settingsmenu();
                }
                break;

            case 32:
                if(i == 1){
                    if(alwaysDebug == 1){
                        changed = true;
                        RegistrySetDword("alwaysDebug",0);
                    } else {
                        changed = true;
                        RegistrySetDword("alwaysDebug",1);
                    }
                    advGotValues = false;
                    advGetValues();
                    advsettingsselect(i);
                }
                if(i == 2){
                    if(alwaysLogfile == 1){
                        changed = true;
                        RegistrySetDword("alwaysLogfile",0);
                    } else {
                        changed = true;
                        RegistrySetDword("alwaysLogfile",1);
                    }
                    advGotValues = false;
                    advGetValues();
                    advsettingsselect(i);
                }
                if(i == 3){
                    if(useRegistryCache == 1){
                        changed = true;
                        RegistrySetDword("useRegistryCache",0);
                    } else {
                        changed = true;
                        RegistrySetDword("useRegistryCache",1);
                    }
                    advGotValues = false;
                    advGetValues();
                    advsettingsselect(i);
                }
        }
    }
}


void advsettingsselect(int arrPos){
    _stack_;
    system("cls");
    char options[][25] = {"alwaysDebug","alwaysLogfile","useRegistryCache","Back"};

    printf("Some Terminal Game / Settings / Advanced\n");
    menubar();
    for(int i = 0; i < advsettingsmaxopt; i++) {
        if(arrPos == i+1) {
            if(i == 0){
                printf(menuArrow"%s <%s>\n", options[i],btos(alwaysDebug));
            } else if(i == 1){
                printf(menuArrow"%s <%s>\n", options[i],btos(alwaysLogfile));
            } else if(i == 2){
                printf(menuArrow"%s <%s>\n",options[i],btos(useRegistryCache));
            }else{
                printf(menuArrow"%s\n", options[i],i);
            }
        } else {
            if(i == 0){
                printf("     %s <%s>\n", options[i],btos(alwaysDebug));
            } else if(i == 1){
                printf("     %s <%s>\n", options[i],btos(alwaysLogfile));
            } else if(i == 2){
                printf("     %s <%s>\n",options[i],btos(useRegistryCache));
            }else {
                printf("     %s\n", options[i]);
            }
        }
    }
    showBottomInfo();
    if(changed){    
        sessiond.top->EditText(sessiond.top,0,"Relaunch SomeTerminalGame for changes to take affect. [i]");
        sessiond.top->currentIndex++;
    }
}

//etc




#endif //SETTINGS_ADV