
/////////////////////////////////////
//       Some_Terminal_Game        //
//       lib/mail/mail_m.h         //
//                                 //
/////////////////////////////////////

//preprocessor
#ifndef MAIL_MENU_MAIN
#define MAIL_MENU_MAIN
#pragma message("===> Building file "__FILE__)

//includes
#include <stdio.h>
#include <stdlib.h>
#include "../../game/pkg/mail.h"
#include "../../game/struct.h"
#include <conio.h>

int __MAIL_MAXOPT = 3;
int __MAIL_MENU(){
    void __MAIL_SELECTION(int);
    system("cls");
    char mailch;
    int v = 1;
    __MAIL_SELECTION(1);
    while(1){
        mailch = getch();
        switch(mailch){

            case 72: //up
                if(v != 1) {
                    v--;
                    __MAIL_SELECTION(v);
                } else {
                    v = __MAIL_MAXOPT;
                    __MAIL_SELECTION(v);
                }
                break;

            case 80:
                if(v != __MAIL_MAXOPT) {
                    v++;
                    __MAIL_SELECTION(v);
                } else {
                    v = 1;
                    __MAIL_SELECTION(v);
                }
                break;

            case 13: //enter
            if(v == 3){ //exit
                system("cls");
                promptline();
                return 0;
            }
            if(v == 1){ //send
                
            }
            break;
        }
    }
}

extern int __COLOR_SELECTION;
extern server MailServer;
void __MAIL_SELECTION(int arrPos){
    char status[50];
    if(MailServer.ServerStatus == 0){
        strcpy(status, "online");
    } else if(MailServer.ServerStatus == 0){
        strcpy(status, "offline");
    } else {
        strcpy(status, "net.status.fetch.Exception(\"Unable to get server status.\")");
    }
    system("cls");
    char opt[][50] = {"Send Mail","View Mail","Return"};
    printf("Mail Service | Server: %s | Status: %d\n", MailServer.IP, MailServer.ServerStatus);
    printf("-----------------------------------------\n\n");
    for(int v = 0; v < __MAIL_MAXOPT; v++){
        if(arrPos == v+1){
            printf("\033[1m> %s <\033[0m\n", opt[v]);
        } else {
            printf("  %s  \n", opt[v]);
        }
    }
}

#endif