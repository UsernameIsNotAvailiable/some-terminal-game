
/////////////////////////////////////
//       Some_Terminal_Game        //
//       lib/mail/mail_s.h         //
//                                 //
/////////////////////////////////////

//preprocessor
#ifndef MAIL_SEND
#define MAIL_SEND
#pragma message("===> Building file "__FILE__)

//includes
#include "mail_m.h"
#include "../../game/struct.h"
#include "../../game/pkg/mail.h"
#include "../../game/pkg/pkg.h"

int _SEND_MAXOPT = 2;
int pkg_mail_new(){
    char status[50];
    if(MailServer.ServerStatus == 0){
        strcpy(status, "online");
    } else if(MailServer.ServerStatus == 0){
        strcpy(status, "offline");
    } else {
        strcpy(status, "net.status.fetch.Exception(\"Unable to get server status.\")");
    }
    system("cls");
    printf("Mail Service | Server: %s | Status: %d\n", MailServer.IP, MailServer.ServerStatus);
    printf("-----------------------------------------\n\n");
    printf("Mail -> Send Message\n\n");
    printf("Send to -> ");
    return 0;
}

#endif