#include <Windows.h>
#include <stdio.h>


#ifndef FUNAS
#define FUNAS
#pragma message("===> Building file "__FILE__)

char *WinGetLastErrorAsString()
{
    //Get the error message ID, if any.
    DWORD errorMessageID = GetLastError();
    if(errorMessageID == 0) {
        return "?"; //No error message has been recorded
    }
    
    LPSTR messageBuffer = NULL;
    char *return_val = {0};

    //Ask Win32 to give us the string version of that message ID.
    //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
    
    //Copy the error message into a std::string.
    strcpy(return_val,messageBuffer);
    
    //Free the Win32's string's buffer.
    LocalFree(messageBuffer);
            
    return return_val;
}


int WinDisplayBox(char *message,char *title,UINT style)
{
    int ret = ShellMessageBoxA(NULL,NULL,message,title,style);
    return ret;
}

int WinDisplayBoxLegacy(char *message,char *title,UINT style){
    int ret = MessageBoxA(NULL,message,title,style);
    return ret;
}

#endif

int main(int argc, char* argv[]) {
    if(argv[1] != NULL){
        if(strcmpi(argv[1],"--help") == 0){
            printf("SomeTerminalGame / Command Line Arguments\n");
            printf("------------------------------------------------\n");
            printf("    --fast          Skip the booting process\n");
            printf("    --debug         Enable debug mode\n");
            printf("    --pausestart    Pause startup when it ends\n");
            printf("    --ignorerrors   Ignore any error and exception handling\n");
            printf("    --console       After startup, jumps to debug console.\n");
            return 0;
        }
    }
    signal_init();
    _check_bp;
    _stack_;
    sessiond.memLimit = 10000000000LLU;

    //startup
    //register the main thread for the sake of it
    //name it main for simplicity
    _thread_init("main",GetCurrentThread());
    thread_main_active = true;

    system("cls");
    printf("Starting bin/SomeTerminalGame. . .\n");
    HANDLE_notice("Setting window title. . .");
    system("title bin/SomeTerminalGame");
    printf("[ OK ] The window title has been set as: \"bin/SomeTerminalGame\"\n");
    HANDLE_notice("Fetching Process ID. . .");
    sessiond.PID = GetCurrentProcessId();
    printf("[ OK ] Fetched process ID: %d\n", sessiond.PID);
    HANDLE_notice("Verifying installation. . .");
    if(verify_installation() != 0){
        HANDLE_fatal("BAD_INSTALLATION",__BAD_INSTALLATION);
    } else {
        printf("[ OK ] The installation has been verified.\n");
    }
    HANDLE_notice("Parsing starting arguments. . .");
    if(argc > 10){
        HANDLE_fatal("BAD_ARGUMENT_COUNT", __BAD_ARGUMENT_COUNT);
        sessiond.deprecated.StartArgsFetchFailure = true;
    }
    for(int i = 1; i < argc ; i++){
        if(strcmpi(argv[i],"--fast") == 0){
            sessiond.skip = true;
            printf("[ OK ] Starting argument applied: '%s'\n", argv[i]);
        } else if(strcmpi(argv[i], "--debug") == 0){
            settings.isDebug = true;
            printf("[ OK ] Starting argument applied: '%s'\n", argv[i]);
        } else if (strcmpi(argv[i],"--PauseStart") == 0){
            pause_start=true;
            printf("[ OK ] Starting argument applied: '%s'\n", argv[i]);
        }else if(strcmpi(argv[i],"--IgnoreErrors") == 0){
            settings.IgnoreErrors=true;
            printf("[ OK ] Starting argument applied: '%s'\n", argv[i]);
        } else if(strcmpi(argv[i],"--console") == 0){
            sessiond.usingDebugCmd = true;
            settings.isDebug = true;
            printf("[ OK ] Starting argument applied: '%s'\n", argv[i]);
        }else {
            printf("[ ERROR ] Ignoring unknown argument: '%s'\n", argv[i]);
        }
    }

    HANDLE_notice("Creating threads. . .");
    createThreads();
    printf("[ OK ] Threads Created\n");
    
    //start threads
    startThreads();
    HANDLE_notice("Waiting on thread(s) to start. . .");
    while(!thread_KbdListen_active && !thread_MemMgr_active && !thread_BkgProcessing_active){
    
    }
    HANDLE_notice("Fetching  version information. . .");
    _fetchVersion();
    printf("[ OK ] Fetched version: %s\n", sessiond._version_);
    HANDLE_notice("Fetching executable location. . .");
    _fetchExecLocation();
    printf("[ OK ] Fetched executable location: %s\n", sessiond._exec_path_);
    HANDLE_notice("Fetching installation location. . .");
    _fetchInstallationLocation();
    printf("[ OK ] Fetched installation location: %s\n", sessiond._installation_path_);
    HANDLE_notice("Loading preferences. . .");
    int pref_read_color = ETC_readpreferences("DefaultColor");
    HANDLE_notice("Applying DefaultColor from File:preferences/DefaultColor. . .");
    if(pref_read_color == COLOR_RED){
        settings.ColorSelection = COLOR_RED;
        system("color 04");
    }
    if(pref_read_color == COLOR_GREEN){
        settings.ColorSelection = COLOR_GREEN;
        system("color 02");
    }
    if(pref_read_color == COLOR_PINK){
        settings.ColorSelection = COLOR_PINK;
        system("color 0d");
    }
    if(pref_read_color == COLOR_PURPLE){
        settings.ColorSelection = COLOR_PURPLE;
        system("color 05");
    }
    if(pref_read_color == COLOR_BLUE){
        settings.ColorSelection = COLOR_BLUE;
        system("color 03");
    }
    if(pref_read_color == COLOR_YELLOW){
        settings.ColorSelection = COLOR_YELLOW;
        system("color 06");
    }
    if(pref_read_color == COLOR_WHITE){
        settings.ColorSelection = COLOR_WHITE;
        system("color 0f");
    }
    HANDLE_notice("Applied DefaultColor");
    HANDLE_notice("Applying SuppressSplashMessage from File:preferences/SuppressSplashMessage. . .");
    char *pref_read_ssm = querySetting("SettingsRoot","SuppressSplashMessage");
    printf("%s\n",pref_read_ssm);
    verifyhelper:
    HANDLE_notice("Initializing helper. . .");
    init_helper();
    //temporary file
    HANDLE_notice("Loading runtime temp file. . .");
    createTemporaryContentContainer();
    printf("[ OK ] Runtime temp was created.\n");
    
    //sessiond
    HANDLE_notice("Initializing values of session data.");
    sessiond.FirstRun = true;
    sessiond.LoggedIn = false;
    sessiond.SetupCompleted = false;
    strcpy(sessiond.bp_func, "value_not_set!");
    printf("[ OK ] The required values have been set.\n");
    HANDLE_notice("Creating session ID. . .");
    sessionID();
    printf("[ OK  ] Session ID created: %d\n", sessiond.sessionID);
    printf("Initialzing values. . .\n");
    universal_data_init();
    printf("[ OK ] Initialized\n");
    if(settings.isDebug){
        int c  = confirm("[ STARTUP/INTURRUPT ] Debug mode is enabled, would you like to also enable the log file?");
        if(c==0){
            ETC_file(_FILE_DEBUG_LOG,"Stack begin","w","OUT");      
            settings.LogFileExist=true;
        }
    }
    printf("[ OK ] Startup has completed!\n");
    if(sessiond.usingDebugCmd){
        printf("Starting debugConsole(). . .\n");
    } else {
        printf("Starting mainmenu(). . .\n");
    }
    if(pause_start){
        printf("\nStartup paused. Press [SPACE] to continue.");
        while(1){
            if(kbhit){
                char ch = getch();
                if(ch==32){
                    break;
                }
            }
        }
    }
    if(!sessiond.usingDebugCmd && !settings.SuppressSplashMessage){
        system("cls");
        char *text = get_splash_text();
        printf("%s",btos(settings.SuppressSplashMessage));
        printf("%s\n",text);
        printf("\nPress [SPACE] to close.\n");
        while(1){
            if(kbhit){
                char ch = getch();
                if(ch == 32){
                    break;
                }
            }
        }
    }
    if(sessiond.usingDebugCmd){
        debugConsole();
    }
    int y = mainmenu();
    if(y == 2) {
        settingsmenu();
    }
}