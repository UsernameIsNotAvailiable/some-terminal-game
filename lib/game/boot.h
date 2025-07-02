
/////////////////////////////////////
//       Some_Terminal_Game        //
//         lib/game/boot.h         //
//                                 //
/////////////////////////////////////

//preproceesor

#ifndef BOOT_CONTROLLER
#define BOOT_CONTROLLER
#pragma message("===> Building file "__FILE__)
#define sleep _sleep
#define __HWID_DISK0 "//DEVICE/HARDDISK0"
#define __HWID_USB0 "//DEVICE/USB/removeableMedia0"
#define __HWID_ETHER0 "//DEVICE/NET/ethernetPort0"
#define __HWID_DJT "//DEVICE/DONALD/TRUMP/2024"
#define __HWID_SECRET_CREDITS "//DEVICE/META/SECRET_CREDITS"
#define __HWFS_ROOT "rootfs"
#define _stack_ addStack(__FUNCTION__)

//includes
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>
#include "resources.h"
#include "struct.h"

char value[50];
int load_prompt(){
    addStack("load_prompt()");
    printf("\nTerminalZ/x64\n");
    printf("boot-> ");
    gets_s(value, 500);
    loader(value);
    return 0;
}

extern device TerminalZ;
extern device USB;
extern device ethernet;
extern device djt;
extern device secret_credits;

int loader(char action[50]){
    _stack_;
    if(strcmpi(action, "sda0") == 0){
        screen_boot(false);
        boot(TerminalZ);
        return 0;
    }
    if(strcmpi(action, "sda1") == 0){
        screen_boot(false);
        boot(USB);
        return 0;
    }
    if(strcmpi(action, "2024") == 0){
        screen_boot(false);
        boot(djt);
    }
    if(strcmpi(action, "secret") == 0){
        screen_boot(false);
        boot(secret_credits);
    }
    printf("loader: %s: invalid boot device\n", action);
    load_prompt();
    return 0;
}

int boot(device Desired){
    addStack("boot");
    sleep(600);
    if(!Desired.Trusted){
        panic("Unable to mount %s on untrusted-block(0,0)",__HWFS_ROOT);
    }
    if(!Desired.Mounted){
        panic("Unable to mount %s on unknown-block(0,0)",__HWFS_ROOT);
    }
    printf("Boot from: ");
    sleep(200);
    printf("%s\n", Desired.type);
    sleep(500);
    printf("%s\n", Desired.MountPoint);
    printf("Initializing device. . .\n");
    sleep(200);
    printf("Loading device information. . .\n");
    printf("Friendly Name    : %s\n", Desired.FriendlyName);
    sleep(100);
    printf("Device type      : %s\n", Desired.type);
    sleep(70);
    printf("Hardware Address : %s\n", Desired.HardwareAddress);
    sleep(200);
    printf("Mount Point      : %s\n\n", Desired.MountLocation);
    sleep(1000);
    printf("Booting %s at %s", Desired.HardwareAddress, Desired.MountLocation);
    sleep(2200);
    if(strcmp(Desired.HardwareAddress, __HWID_DISK0) == 0){
        if(USB.CurrentDevice){
            USB.CurrentDevice = false;
        }
        TerminalZ.CurrentDevice = true;
        game();
    }
    if(strcmp(Desired.HardwareAddress, __HWID_USB0) == 0){
        if(TerminalZ.CurrentDevice){
            TerminalZ.CurrentDevice = false;
        }
        USB.CurrentDevice = true;
        game();
    }
    if(strcmp(Desired.HardwareAddress, __HWID_DJT) == 0){
        system("cls");
        printf("DONALD TRUMP 2024");
        sleep(1500);
        screen_boot(false);
    }
    if(strcmp(Desired.HardwareAddress, __HWID_SECRET_CREDITS) == 0){
        system("cls");
        printf("SECRET CREDITS------------------------------\n\n");
        printf("\"snail snort snow\" - greg     :   My friend\n");
        sleep(7000);
        screen_boot(false);
    }
    return 0;
}

#endif