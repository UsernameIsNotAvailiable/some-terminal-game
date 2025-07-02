
/////////////////////////////////////
//       Some_Terminal_Game        //
//         lib/game/net.h          //
//                                 //
/////////////////////////////////////

//preprocessor
#ifndef NETWORK_CMD
#define NETWORK_CMD
#pragma message("===> Building file "__FILE__)

#define __NET_START 0
#define __CONNECTION_TOOL 1
#define sleep _sleep
#define _check_bp bp_check(__FUNCTION__)
#define _stack_ addStack(__FUNCTION__)
//includes
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../handle/debug/c_handle.h"
#include "resources.h"
#include "struct.h"

extern device ethernet;

int init_boot_ethernet(){
    _stack_;
    _check_bp;
    printf("NETW: init/device/ethernet. . .\n");
    sleep(15);
    printf("NETW: Loading device information. . .\n");
    sleep(50);
    printf("NETW:       Ethernet device name:           %s\n", ethernet.FriendlyName);
    printf("NETW:       Ethernet hardware address:      %s\n", ethernet.HardwareAddress);
    printf("NETW:       Ethernet mount point:           %s\n", ethernet.MountPoint);
    printf("NETW:       Ethernet mount location:        %s\n", ethernet.MountLocation);
    printf("NETW:       Ethernet enabled:               %s\n\n", btos(ethernet.Mounted));

    printf("NETW: Enabling %s at %s. . .\n", ethernet.HardwareAddress, ethernet.MountLocation);
    ethernet.Mounted = true;
    sleep(200);
    printf("NETW: %s has been enabled with 0 error(s).\n", ethernet.FriendlyName);
    return 0;
}


#endif