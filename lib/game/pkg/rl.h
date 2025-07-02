
/////////////////////////////////////
//       Some_Terminal_Game        //
//       lib/game/pkg/rl.h         //
//                                 //
/////////////////////////////////////

//preprocessor

#ifndef __APP_REMOTE_LOGIN
#define __APP_REMOTE_LOGIN
#pragma message("===> Building file "__FILE__)

//includes
#include "../struct.h"
#include "../../handle/debug/c_handle.h"
#include "../../handle/debug/etc/error.h"
#include "../resources.h"
#include "pkg.h"

package remote_login = {
    "Remote Login",
    "terminalz.pkg/packages.RL",
    "terminalz.pkg",

    false,
    true,
    false
};

pkg_user_data rl_user = {
    "username_not_set",
    false,
    false,
};
extern pkg_user_data rl_user;
extern package remote_login;

int pkg_rl_main(){
    addStack("pkg_rl_main()");
    sleep(150);
    printf("Starting: /pkg/remote_login/main. . .\n");
    sleep(400);
    printf("Starting: /pkg/remote_login/connecter. . .\n\n");
    sleep(700);
    printf("Welcome to Remote Login!\n");
    if(!rl_user.LoggedIn){
        pkg_rl_signup_main();
    }
    sleep(200);
    printf("Logged in as: %s\n\n", rl_user.username);
    promptline();
    return 0;
}

int pkg_rl_interfacer(){
    
    return 0;
}

int pkg_rl_signup_main(){
    char user_buffer[50];
    system("cls");
    printf("Remote Login -> Signup\n");
    printf("--------------------------------------\n");
    sleep(850);
    fetch_user:
    printf("Username: ");
    gets_s(user_buffer, 50);
    if(strlen(user_buffer) > 1){
        printf("Invalid username!\n");
        goto fetch_user;
    }
    bool c = confirm("Would you like to signup now?");
    if(!c){
        promptline();
    } else {
        strcpy(rl_user.username, user_buffer);
        rl_user.LoggedIn = true;
        pkg_rl_main();
    }
    return 0;    
}

#endif