
/////////////////////////////////////
//       Some_Terminal_Game        //
//     lib/menus/game/shop.h       //
//                                 //
/////////////////////////////////////

//preproccesor

#pragma once
#ifndef GAME_SHOP
#define GAME_SHOP
#pragma message("===> Building file "__FILE__)

//includes
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "hardware.h"



char ch;
int maxopt_shop = 3;
int shop_main_window(int current_points) {
    void selection_win(int, int current_points);
    int i = 1;
    selection_win(1, current_points);

    while(1){
        ch = getch();

        switch(ch) {
            
            case 72: //up
                if(i != 1){
                    i--;
                    selection_win(i, current_points);
                } else {
                    i = maxopt_shop;
                    selection_win(i, current_points);
                }
                break;

                default:
                    break;

                case 80: //down
                    if(i != maxopt_shop){
                        i++;
                        selection_win(i, current_points);
                    } else {
                        i = 1;
                        selection_win(i, current_points);
                    }
                    break;

                case 13: //enter
                    if(i == 3){
                        //return_shop(current_points, 2, 2, 2);
                        return 0;
                    }
                    if(i == 2){
                        return 0;
                    }
                    if(i == 1){
                        shop_child_hardware(current_points);
                        return 0;
                    }
        }
    }





    return 0;
}



void selection_win(int arrPos, int current_points){
    system("cls");
    char options[][20] = {"Hardware", "Software", "Return"};
    printf("Shop                          Points: %d\n", current_points);
    printf("-----------------------------------------\n\n");
    for(int i = 0; i < maxopt_shop; i++){
        if(arrPos == i+1){
            printf("> %s <\n", options[i]);
        } else {
            printf("  %s  \n", options[i]);
        }
    }
} 

#endif