
/////////////////////////////////////
//       Some_Terminal_Game        //
//       lib/game/pkg/pkg.h        //
//                                 //
/////////////////////////////////////

//preprocessor

#ifndef __PKG_INSTALLER
#define __PKG_INSTALLER
#pragma message("===> Building file "__FILE__)
#define sleep _sleep

//includes
#include "../struct.h"
#include "../../handle/debug/c_handle.h"
#include "../../handle/debug/etc/error.h"
#include "../resources.h"

#define _APPID_MAIL 401
#define __APPID_REMOTE_LOGIN 402

bool isPackageManagerInstalled = false;

int pkgman_run(int appid){
    addStack("pkgman_run()");
    printf("Loading package manager. . .\n");
    if(!isPackageManagerInstalled){
        install_pkgman();
    }
    if(appid == _APPID_MAIL){
        pkg_mail_main();
    }
    if(appid == __APPID_REMOTE_LOGIN){
        pkg_rl_main();
    }
    return 0;
}

int install_pkgman(){
    if(!isPackageManagerInstalled){
        bool con = confirm("The package manager is not installed! Would you like to fetch and install it now?");
        if(!con){
            return 1;
        }
        printf("Fetching pkg.manager from tz.nu. . .\n");
        sleep(500);
        printf("Installing. . .\n");
        isPackageManagerInstalled = true;
        printf("Installed package manger!\n\n");
    }
    return 0;
}

int install_pkg(package pkg, bool isSuperUser){
    if(!isPackageManagerInstalled){
        install_pkgman();
    }
    if(pkg.Installed){
        printf("%s is already installed on your machine!\n", pkg.Name);
        return 1;
    }
    printf("Loading package manager. . .\n");
    sleep(500);
    if(!pkg.Trusted && !isSuperUser){
        printf("The specified package is not trusted and will not be installed. Please run as Super User to bypass this.\n");
        return 1;
    }
    sleep(750);
    printf("Install: %s from source: %s. . .\n", pkg.Name, pkg.Host);
    bool c = confirm("Proceed with installation? ");
    if(!c){
        return 1;
    }
    printf("Verifying source is online. . .\n");
    sleep(200);
    printf("Pinging %s. . .\n", pkg.Host);
    sleep(50);
    printf("Waiting 5 seconds for response");
    for(int i = 0; i < 2; i++){
        printf(" %d", i);
    }
    printf("\n[ OK ] Installer is online.\n");
    sleep(70);
    printf("Verifying installer hash. . .\n");
    sleep(250);
    printf("[ OK ] Verified hash.\n");
    sleep(20);
    printf("Fetching %s from %s. . .\n", pkg.Source, pkg.Host);
    sleep(890);
    printf("Installing %s. . .\n", pkg.Source);
    sleep(1200);
    pkg.Installed = true;
    pkg.Active = true;
    printf("Verifying installation. . .\n");
    sleep(720);
    printf("Installed with 0 error(s).\n\n");
    sleep(50);
    printf("Installation summary ---------------\n");
    printf("  Package Name      : %s\n", pkg.Name);
    printf("  Package Source    : %s\n", pkg.Source);
    printf("  Package Host      : %s\n", pkg.Host);
    printf("  Package Active    : %s\n\n", btos(pkg.Active));
    return 0;
}

#endif