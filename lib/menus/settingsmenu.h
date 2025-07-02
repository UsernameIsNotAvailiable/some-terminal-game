
/////////////////////////////////////
//       Some_Terminal_Game        //
//    lib/menus/settingsmenu.c     //
//                                 //
/////////////////////////////////////

//preprocessor

#pragma once
#ifndef SETTINGS
#define SETTINGS
#pragma message("===> Building file "__FILE__)

//includes
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "mainmenu.h"
#include "color.h"
#include "../handle/Registry.h"
#include "settings-advanced.h"
//menu

DWORD suppress;
DWORD dumpstack;
bool GotValues = false;

bool GetValues(){
    _stack_;
    if(GotValues){
        return false;
    } else {
        suppress = RegistryReadDword("SuppressSplashMessage");
        dumpstack = RegistryReadDword("DumpstackOnCrash");
    }
    GotValues = true;
    return true;
}

int settingsmaxopt = 6;
int settingsmenu() {
    _stack_;
    void settingsselect(int);
    GetValues();
    system("cls");

    int i = 1;
    char ch;
    settingsselect(1);
    while(1) {
        ch = getch();

        switch(ch) {

            case 72: //up
                if(i != 1) {
                    i--;
                    settingsselect(i);
                } else {
                    i = settingsmaxopt;
                    settingsselect(i);
                }
                break;

            case 80: //down
                if(i != settingsmaxopt) {
                    i++;
                    settingsselect(i);
                } else {
                    i = 1;
                    settingsselect(i);
                }
                break;

                default:
                    break;
            
            case 32:
                if(i == 3){
                    if(suppress == 1){
                        RegistrySetDword("SuppressSplashMessage",0);
                    } else {
                        RegistrySetDword("SuppressSplashMessage",1);
                    }
                    GotValues = false;
                    GetValues();
                    settingsselect(i);
                }
                if(i == 2){
                    if(dumpstack == 1){
                        RegistrySetDword("DumpstackOnCrash",0);
                    } else {
                        RegistrySetDword("DumpstackOnCrash",1);
                    }
                    GotValues = false;
                    GetValues();
                    settingsselect(i);
                }
                break;
            case 13:
                if(i == 6) { //exit
                    mainmenu();
                }
                if(i == 5){
                    system("cls");
                    printf("Some Terminal Game / Settings / Reset\n");
                    menubar();
                    showcursor();
                    bool conf = confirm("Reset all settings?");
                    if(conf){
                        RegistryReset();
                        printf("relaunch someterminalgame for settings to take affect\n");
                        quit(__TERM_USER_INITIATED);
                    } else {
                        printf("operation aborted\n");
                        sleep(500);
                        hidecursor();
                        settingsselect(i);
                    }
                }
                if(i == 4){
                    advsettingsmenu();
                }
                if(i == 1) { //settings: text color
                    textcolor();
                }
        }
    }
}


void settingsselect(int arrPos){
    _stack_;
    system("cls");
    char options[][25] = {"Text color","DumpstackOnCrash","SuppressSplashMessage","Advanced","Reset all settings","Back"};
    printf("Some Terminal Game / Settings\n");
    menubar();
    for(int i = 0; i < settingsmaxopt; i++) {
        if(arrPos == i+1) {
            if(i == 2){
                printf(menuArrow"%s <%s>\n", options[i],btos(suppress));
            } else if(i == 1){
                printf(menuArrow"%s <%s>\n", options[i],btos(dumpstack));
            }else {
                printf(menuArrow"%s\n", options[i],i);
            }
        } else {
            if(i == 2){
                printf("     %s <%s>\n", options[i],btos(suppress));
            } else if(i == 1){
                printf("     %s <%s>\n", options[i],btos(dumpstack));
            } else {
                printf("     %s\n", options[i]);
            }
        }
    }
    showBottomInfo();
}

//etc





#endif