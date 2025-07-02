
/////////////////////////////////////
//       Some_Terminal_Game        //
// lib/menus/game/shop/hardware.h  //
//                                 //
/////////////////////////////////////

//preproccesor
#ifndef SHOP_HW
#define SHOP_HW
#pragma message("===> Building file "__FILE__)

//includes
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "shop.h"

char ch;
int hw_options_max = 4;
int shop_child_hardware(int current_points) {
    system("cls");
    void hw_selection(int, int current_points);
    int i = 1;
    hw_selection(1, current_points);

    while(1){
        ch = getch();

        switch(ch){

            case 72: //up
                if(i != 1){
                    i--;
                    hw_selection(i, current_points);
                } else {
                    i = hw_options_max;
                    hw_selection(i, current_points);
                }
                break;

                default:
                    break;

                case 80: //down
                    if(i != hw_options_max){
                        i++;
                        hw_selection(i, current_points);
                    } else {
                        i = 1;
                        hw_selection(i, current_points);
                    }
                    break;

                case 13: //enter
                    if(i == 4){
                        shop_main_window(current_points);
                    }
                    if(i == 3){
                        if(current_points < 20){
                            printf("\n\nNot enough points!\n");
                            _sleep(500);
                            break;
                        }
                        current_points -= 20;
                        system("cls");
                    }
                    if(i == 2){
                        if(current_points < 100){
                            printf("\n\nNot enough points!\n");
                            _sleep(500);
                            break;
                        }
                        
                        current_points -= 50;
                        system("cls");
                    }
                    if(i == 1){
                        if(current_points < 15){
                            printf("\n\nNot enough points!\n");
                            _sleep(500);
                            break;
                        }
                        current_points -= 15;
                        system("cls");
                    }
                    break;
        }
    }
}


void hw_selection(int arrPos, int current_points){
    system("cls");
    char hw_options[][50] = {"15 Points: Upgrade RAM", "100 Points: Upgrade CPU", "20 Points: Upgrade Storage", "Return"};
    printf("Shop / Hardware                 Points: %d\n", current_points);
    printf("-----------------------------------------\n\n");
    for(int i = 0; i < hw_options_max; i++){
        if(arrPos == i+1){
            printf("> %s <\n", hw_options[i]);
        } else {
            printf("  %s  \n", hw_options[i]);
        }
    }
}   









#endif