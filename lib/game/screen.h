
/////////////////////////////////////
//       Some_Terminal_Game        //
//       lib/game/screen.h         //
//                                 //
/////////////////////////////////////

#ifndef UNLOCKED
#define UNLOCKED
#pragma message("===> Building file "__FILE__)
#define sleep _sleep

#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "resources.h"
#include "boot.h"
#include "net.h"


extern user standard;
extern user SYSTEM;
extern user dummy;
extern user root;
extern session_informaton sessiond;

char ch;
int lvlunlock(int new){
    addStack("lvlunlock");
    system("cls");
    sleep(1200);
    int i;
    char level[15] = "LEVEL UNLOCKED";
    for(i = 0; i <= strlen(level); i++){
        printf("%c", level[i]);
        sleep(150);
    }
    sleep(1000);
    printf("\n\n%d\n\n", new);
    sessiond.Level = new;
    sleep(500);
    printf("Press [SPACE] to close\n");
    while(1) {
        if(kbhit) {
            ch = getch();
            if((int)ch == 32){
                system("cls");
                return 0;
            }
        }
    }
}

int GameOver(char reason[120], bool win){
    addStack("GameOver");
    system("cls");
    sleep(1200);
    char over[13] = "GAME OVER:\n";
    for(int i = 0; i <= strlen(over); i++){
        printf("%c",over[i]);
        sleep(150);
    }
    for(int i = 0; i <= strlen(reason); i++){
        printf("%c", reason[i]);
        sleep(150);
    }
    printf("\n\nPress [SPACE] to exit");
    while(1){
        if(kbhit){
            ch = getch();
            if((int)ch == 32){
                forceexit(__TERM_GAME_END);
            }
        }
    }
}

int setup(){
    addStack("setup");
    char *buffer1;
    char *buffer2;
    char *buffer3;
    char username[50];
    system("cls");
    printf("TerminalZ / Setup / Root Password | Current IP: 127.0.0.1\n");
    printf("-----------------------------------------\n");
    printf("Welcome to the TerminalZ setup process!\n");
    sleep(20);
    printf("-setup: Loading required files. . .\n");
    sleep(50);
    printf("-TZ_KRNL: /usr/terminalz/firstrun/setup is loading files from /usr/terminalz/utils/setup/*. . .\n");
    sleep(600);

    system("cls");
    printf("TerminalZ / Setup / Root | Current IP: 127.0.0.1\n");
    printf("-----------------------------------------\n");
    printf("Please enter the password for the root account.\n");
    printf("Make sure this password is secure as the root account\n");
    printf("can admister the entire system.\n\n");
    get_password1:
    buffer1 = get_password("Password: ");
    buffer2 = get_password("Please type your password again: ");
    if(strcmp(buffer1, buffer2) != 0){
        printf("-pswd: passwords do not match!\n\n");
        goto get_password1;
    } else {
        ChangeUserPassword(&SYSTEM, &root, buffer2, true);
        free(buffer1);
        free(buffer2);
    }
    sleep(500);

    system("cls");
    printf("TerminalZ / Setup / Create an account | Current IP: 127.0.0.1\n");
    printf("-----------------------------------------\n");
    printf("Create your account.\n\n");
    get_username:
    printf("Username: ");
    gets(&username);
    strcpy(standard.Username, username);
    char *temp = malloc(120);
    strcpy(temp, "/home/");
    strcat(temp, standard.Username);
    strcpy(standard.HomeDir, temp);
    free(temp);
    get_password2:
    buffer2 = get_password("Password: ");
    buffer3 = get_password("Please type your password again: ");
    if(strcmp(buffer2, buffer3) != 0){
        printf("-pswd: passwords do not match!\n\n");
        goto get_password1;
    }else {
        ChangeUserPassword(&SYSTEM, &standard, buffer3, true);
        free(buffer2);
        free(buffer3);
    }
    sleep(500);
    system("cls");
    printf("-TZ_KRNL: The system must reboot to complete changes. . .\n");
    printf("Rebooting in 3 seconds.\n");
    sleep(3000);
    sessiond.SetupCompleted = true;
    screen_reboot();
    return 0;
}

extern user root;
extern user SYSTEM;
extern user standard;
extern user dummy;
extern user null_user;
extern user LocalAccountManagerHostUser;

extern user_data _universal_user_data_table;
int login(){
    _check_bp;
    SignOutAllUsers();
    _universal_user_data_table.CurrentUser = &LocalAccountManagerHostUser;
    LocalAccountManagerHostUser.Active = true;

    system("cls");
    printf("TerminalZ / Login | Current IP: 127.0.0.1\n");
    printf("-----------------------------------------\n");
    prompt:
    user *login_target;
    char target[120];
    printf("login: ");
    gets_s(target, 120);
    if(!doesUsernameExist(target)){
        status(false, "login_host","user does not exists");
        goto prompt;
    }
    for(int i = 0; i < _universal_user_data_table.UserCount; i++){
        if(strcmp(_universal_user_data_table.AllUsers[i]->Username, target) == 0){
            login_target = _universal_user_data_table.AllUsers[i];
            if(!login_target->permissions.IsLoginAllowed){
                status(false, "login_host","login is not allowed for this user");
                goto prompt;
            }
        }
    }
    int password_attempts = 0;
    get_pswd:
    char *pswd = get_password("password: ");
    if(strcmp(pswd, login_target->Password) != 0){
        if(password_attempts >= 3){
            status(false, "login_host","too many attempts");
            password_attempts = 0;
            screen_reboot();
        }
        password_attempts += 1;
        printf("invalid password\n");
        goto get_pswd;
    }
    _backend_SwapCurrentUser(*login_target);
    ObscenceNameChecker(login_target);
    game();
    return 0;
}

char chv;
int underattack(){
    int i;
    system("cls");
    sleep(1200);
    char alert[120] = "ALERT!\n\nSYSTEMS UNDER ATTACK\n\n";
    for(i = 0; i <= strlen(alert); i++){
        printf("%c", alert[i]);
        sleep(150);
    }
    sleep(150);
    printf("Press [SPACE] to close\n");
    while(1) {
        if(kbhit) {
            chv = getch();
            if((int)chv == 32){
                system("cls");
                return 0;
            }
        }
    }
}

char cha;
int somestevenscreen(){
    _check_bp;
    sleep(1200);
    char string[120] = ":D https://www.youtube.com/@SomeSteven\n";
    int i;
    for(i = 0; i <= strlen(string); i++){
        printf("%c", string[i]);
        sleep(150);
    }
    sleep(2500);
    return 0;
}

int screen_reboot(){
    addStack("screen_reboot");
    _check_bp;
    sessiond.LoggedIn = false;
    printf("-system: rebooting. . . \n");
    sleep(500);
    screen_bootLoader();
    return 0;
}

int screen_powerloss(){
    system("cls");
    _stack_;
    _check_bp;
    printf("-powerd: critical - System power loss...");
    sessiond.LoggedIn = false;
    sleep(2000);
    system("cls");
    sleep(3500);
    printf("Autostart from power loss...\n");
    sleep(2500);
    screen_bootLoader();
    return 0;
}


//boot
int screen_bootLoader(){
    system("cls");
    char ch;
    printf("Loading TerminalZ boot manager. . .\n");
    sleep(800);
    system("cls");
    printf("TerminalZ Boot Manager\n");
    printf("-------------------------------------------\n");
    printf("Searching for bootable media. . .\n");
    sleep(1025);
    system("cls");
    printf("TerminalZ Boot Manager\n");
    printf("-------------------------------------------\n");
    printf("Press enter for default device.\n");
    if(USB.Default){
        printf("F1 \t%s [ DEFAULT ]\n", USB.FriendlyName);
    } else if(TerminalZ.Default){
        printf("F1 \t%s [ DEFAULT ]\n", TerminalZ.FriendlyName);
    }
    if(!TerminalZ.Default){
        printf("F2 \t%s\n", TerminalZ.FriendlyName);
    }
    if(!USB.Default){
        if(USB.Mounted){
            printf("F2 \t%s\n", USB.FriendlyName);
        }
    }
    printf("F6 \tEscape to loader prompt\n");
    printf("ESC\tShutdown");
    while(1){
        if(kbhit){
            ch = getch();
            if((int)ch == 13) {//enter (default option)
                if(TerminalZ.Default){
                    screen_boot(false);
                    boot(TerminalZ);
                }
                if(USB.Default){
                    screen_boot(false);
                    boot(USB);
                }
            }
            if((int)ch == 59){ //F1
                if(TerminalZ.Default){
                    screen_boot(false);
                    boot(TerminalZ);
                }
                if(USB.Default){
                    screen_boot(false);
                    boot(USB);
                }
            }
            if((int)ch == 64) { //F6
                printf("\nExiting menu. . .\n");
                load_prompt();
            }
            if(!USB.Default){
                if(USB.Mounted){
                    if((int)ch == 60) {//F2
                        screen_boot(false);
                        boot(USB);
                    }
                }
            }
            if((int)ch == 27){ //F12
                forceexit(__TERM_USER_INITIATED);
            }
        }
    }
}


int del_press = 0;
extern user debugee;
int screen_boot(bool changesPending){
    _check_bp;
    _sfx_stop();
    addStack("screen_boot");
    char ch;
    char boot_msg_hid_loader[][120] = {"Loading kernel. . .","Reached target: drivers","Initializing drivers. . .","[ OK ] Drivers loader","Reached target: Human Interface Devices","HID_LOADER: Loading Human Interface Devices. . .","[ OK ] HID_LOADER: Found device < KEYBOARD_PIU20PB9 >","HID_LOADER: < KEYBOARD_PIU20B9 > AT //DEVICE/USBS/BUS1","HID_LOADER: Initializing device: < KEYBOARD_PIU20B9>. . .","[ OK ] HID_LOADER: Device < KEYBOARD_PIU20BP > intialized at //DEVICE/USB/BUS1","HID_LOADER: Marked < KEYBOARD_PIU20BP > to be mounted at /dev/loop2","[ OK ] HID_LOADER: Found device < USBSTORAGEDEVICE0 >","HID_LOADER: < USBSTORAGEDEVIEC0 > at //DEVICE/USB/REMOVEABLEUSB0","HID_LOADER: Initializing device: < USBSTORAGEDEVICE0 >. . .","HID_LOADER: Marked < USBSTORAGEDEVICE0 > to be mounted at /dev/sda1."};
    char boot_msg_vol_mount[][120] = {"VOL_MOUNT: Loading devices. . .","VOL_MOUNT: Found device: < KEYBOARD_PIU20B9 > at //DEVICE/USB/BUS1","VOL_MOUNT: Mounting device < KEYBOARD_PIU20B9 > at /dev/loop2","VOL_MOUNT: Mounted //DEVICE/USB/BUS1 at /dev/loop2","VOL_MOUNT: Found device: < TerminalZ > at //DEVICE/HARDDISK0","VOL_MOUNT: Mounting < TerminalZ > at /dev/sda0. . .","VOL_MOUNT: Mounted //DEVICE/HARDDISK0 at dev/sda0","VOL_MOUNT: Found device: < USBSTORAGEDEVICE0 > at //DEVICE/USB/REMOVEABLEUSB0"};
    char boot_msg_usb_mount[][120] = {"VOL_MOUNT: Mounting device < USBSTORAGEDEVICE0 > at /dev/sda1. . .","VOL_MOUNT: Mounted //DEVICE/USB/REMOVEABLEUSB0 at /dev/sda1"};
    system("cls");
    if(sessiond.skip){
        game();
    }
    sleep(2000);
    for(int i = 0; i < 15; i++){
        printf("%s\n", boot_msg_hid_loader[i]);
        if(i == 6){
            sleep(80);
        } else if(i == 1){
            sleep(60);
        }else if( i == 10){
            sleep(20);
        } else if(i == 15){
            sleep(145);
        } else {
            sleep(20);
        }
    }
    sleep(50);
    printf("Reached target: VOL_MOUNT\n");
    sleep(120);
    for(int i = 0; i < 5; i++){
        printf("%s\n", boot_msg_vol_mount[i]);
        if(i == 3){
            sleep(150);
        } else {
            sleep(220);
        }
    }
    printf("Reached target: NETW\n");
    sleep(120);
    printf("NETW: Locating. . .\n");
    sleep(50);
    if(!ethernet.Mounted){
        printf("NETW: Connection device found.\n");
        printf("NETW: Media check. . .\n");
        sleep(950);
        printf("NETW: Media check success.\n");
        init_boot_ethernet();
    }
    //random junk
    printf("Reached target: service starter.\n");
    sleep(410);
    for(int i = 0; i < 18; i++){
        printf("servstr: Starting system_service_%d...\n",i);
    }
    printf("[ OK ] Task starter end.\n");
    printf("Reached target: mount fs\n");
    return 0;
}

#endif