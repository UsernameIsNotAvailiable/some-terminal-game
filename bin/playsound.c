#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//MOVE ME INTO bin/data/app/resources/sfx

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE a, PSTR b, int nCmdShow){
    if(strcmpi(__argv[1],"s_killself") == 0){
        system("taskkill /f /im playsound.exe");
        return 0;
    }
    bool loop = FALSE;
    if(strcmpi(__argv[2],"loop") == 0){
        loop = TRUE;
    }
    if ( GetFileAttributes(__argv[1]) == INVALID_FILE_ATTRIBUTES){
        return -1;
    }
    if(loop){
        for(;;){
            PlaySoundA(__argv[1],NULL,SND_FILENAME);
        }
    } else {
    while(TRUE){
            PlaySoundA(__argv[1],NULL,SND_FILENAME);
        }
    }
    return 0;
}