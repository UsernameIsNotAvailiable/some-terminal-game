
/////////////////////////////////////
//       Some_Terminal_Game        //
//      lib/menus/mainmenu.h       //
//                                 //
/////////////////////////////////////

//preprocessor

#pragma once
#ifndef MENUS
#define MENUS
#pragma message("===> Building file "__FILE__)
#define _stack_ addStack(__FUNCTION__)

//includes
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include "../handle/debug/c_handle.h"
#include "settingsmenu.h"
#include "../game/resources.h"
#include "../game/topright.h"

char ch;
int maxopt = 6;
int mainmenu() {
    _stack_;
    system("cls");
    void mainselect2(int);
    int i = 1;
    mainselect2(1);
    while(1) {
        ch = getch();

        switch(ch) {

            case 72: //up
                if(i != 1) {
                    i--;
                    mainselect2(i);
                } else {
                    i = maxopt;
                    mainselect2(i);
                }
                break;

            case 80: //down
                if(i != maxopt) {
                    i++;
                    mainselect2(i);
                } else {
                    i = 1;
                    mainselect2(i);
                }
                break;

            case 13:
                if(i == 6) { //exit
                    quit(__TERM_USER_INITIATED);
                    showcursor();
                }
                if(i == 5){ //updates
                    updatesmenu();
                }
                if(i == 4){
                    creditsmenu();
                }
                if(i == 3) {
                    aboutmenu();
                }
                if(i == 2) { //settings
                    settingsmenu();
                }
                if(i == 1) { //start
                    showcursor();
                    screen_bootLoader();
                }
        }
    }
}

void mainselect2(int arrPos){
    _stack_;
    system("cls");
    _sfx_play(_SFX_MAINMENU);
    char options[][20] = {"Start","Settings","About","Credits","Updates","Quit"};
    printf("Some Terminal Game\n");
    menubar();
    for(int i = 0; i < maxopt; i++) {
        if(arrPos == i+1) {
            printf(menuArrow "%s\n", options[i]);
        } else {
            printf("     %s\n", options[i]);
        }
    }
    showBottomInfo();
}

int updatesmenu(){
    _stack_;
    system("cls");
    printf("Some Terminal Game / Updates\n");
    menubar();
    printf("Updates for version: %s\n", sessiond._version_);
    printf("    Registry data read cache.\n");
    printf("    \"--noregistrycache\" command line argument.\n");
    printf("    useRegistryCache advanced setting.\n");
    printf("    And other small changes.\n\n");

    printf(menuArrow" Back");
    showBottomInfo();
    while(1){
        if(kbhit) {
            ch = getch();
            if((int)ch == 13) {
                mainmenu();
            }
        }
    }
}

//etc
int aboutmenu() {
    _stack_;
    system("cls");
    printf("Some Terminal Game / About\n");
    menubar();
    printf("    Your goal is to infiltrate the systems of the enemy\n");
    printf(" to prevent them from launching an attack on us! You\n");
    printf(" have been given the necessary tools to get this job\n");
    printf(" done. We're all counting on you to prevent this attack!\n\n");

    printf(menuArrow" Back");
    showBottomInfo();
    while(1){
        if(kbhit) {
            ch = getch();
            if((int)ch == 13) {
                mainmenu();
            }
        }
    }
}


int creditsmenu() {
    _stack_;
    system("cls");
    printf("Some Terminal Game / Credits\n");
    menubar();
    printf("I made this game by myself!\n\n");

    printf(menuArrow" Back");
    showBottomInfo();
    while(1){
        if(kbhit){
            ch = getch();
            if((int)ch == 13){
                mainmenu();
            }
        }
    }
}

#endif