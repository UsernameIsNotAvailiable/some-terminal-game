
/////////////////////////////////////
//       Some_Terminal_Game        //
//       lib/menus/color.h         //
//                                 //
/////////////////////////////////////

//preprocessor

#pragma once
#ifndef COLOR
#define COLOR
#pragma message("===> Building file "__FILE__)
#define _stack_ addStack(__FUNCTION__)

//includes
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "settingsmenu.h"
#include "mainmenu.h"
#include "../handle/Registry.h"

int colormaxopt = 8;
int textcolor() {
    _stack_;
    void selectcolor(int);
    system("cls");

    int v = 1;
    char colorch;
    selectcolor(1);
    while(1) {
        colorch = getch();

        switch(colorch) {

            case 72: //up
                if(v != 1) {
                    v--;
                    selectcolor(v);
                } else {
                    v = colormaxopt;
                    selectcolor(v);
                }
                break;

            case 80:
                if(v != colormaxopt) {
                    v++;
                    selectcolor(v);
                } else {
                    v = 1;
                    selectcolor(v);
                }
                break;

            case 32:
                if(v == 1) {
                    system("color 02");
                    RegistrySetSz("Color","02");
                }
                if(v == 2) {
                    system("color 04");
                    RegistrySetSz("Color","04");
                }
                if(v == 3) {
                    system("color 03");
                    RegistrySetSz("Color","03");
                }
                if(v == 4) {
                    system("color 0F");
                    RegistrySetSz("Color","0F");
                }
                if(v == 5) {
                    system("color 05");
                    RegistrySetSz("Color","05");
                }
                if(v == 6) {
                    system("color 06");
                    RegistrySetSz("Color","06");
                }
                if(v == 7) {
                    system("color 0d");
                    RegistrySetSz("Color","0d");
                }
                break;
            
            case 13:
                if(v == 8) {
                    settingsmenu();
                }
                break;
        }
    }

}


void selectcolor(int arrPos) {
    _stack_;
    system("cls");
    char coloroptions[][50] = {"Green","Red","Blue","White","Purple","Yellow","Pink","Back"};
    printf("Some Terminal Game / Settings / Color\n");
    menubar();
    for(int v = 0; v < colormaxopt; v++) {
        if(arrPos == v+1) {
            printf(menuArrow"%s\n", coloroptions[v]);
        } else {
            printf("     %s\n", coloroptions[v]);
        }
    }
    showBottomInfo();
}

#endif