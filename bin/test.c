printf("Starting %s at %s",sessiond._verinfo,ctime(&now));
    printf("Command line: \"");
    for(int i =0; i < argc;i++){
        printf("%s ",argv[i]);
    }
    printf("\"\n");
    SetUnhandledExceptionFilter(ExceptionFilter);
    signal_init();
    _check_bp;
    _stack_;
    sessiond.entryAddress = (void*)main;
    sessiond.memLimit = 10000000000LLU;
    sessiond.hProcess = GetCurrentProcess();

    //set the base address for offset information
    HMODULE tmp = GetModuleHandleA(0);
    baseAddress = (void*)tmp;
    sessiond.baseAddress = baseAddress;
    //startup
    //register the main thread for the sake of it
    //name it main for simplicit
    htMain = GetCurrentThread();
    _thread_init("main",GetCurrentThread());
    thread_main_active = true;

    printf("Hello, World!\n");
    printf("Setting window title. . .\n");
    system("title bin/SomeTerminalGame");
    printf("[ OK ] The window title has been set as: \"bin/SomeTerminalGame\"\n");

    printf("Reached target: loadModulesAndDependencies\n");
    printf("Starting external/stg.core.api.dll. . .\n");
    //list dependencies
    printf("Currently loaded DLL's:\n");
    StoreCurrentRuntimeDependencies();

    printf("Fetching Process ID. . .\n");
    sessiond.PID = GetCurrentProcessId();
    printf("[ OK ] Fetched process ID: %d\n", sessiond.PID);
    printf("Verifying installation. . .\n");
    if(verify_installation() != 0){
        HANDLE_fatal("BAD_INSTALLATION",__BAD_INSTALLATION);
    } else {
        printf("[ OK ] The installation has been verified.\n");
    }
    printf("Parsing starting arguments. . .\n");
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
    printf("Reached target: threads \n");
    printf("Creating threads. . .\n");
    createThreads();
    printf("[ OK ] Threads Created\n");
    
    //hook
    printf("Reached target: hooking\n");
    printf("Creating hooks. . .\n");
    doCreateHooks();
    //hRegistry.AddFunction(&hRegistry,Nothing);

    //start threads
    startThreads();
    printf("Waiting on thread(s) to start. . .\n");
    while(!thread_KbdListen_active && !thread_MemMgr_active && !thread_BkgProcessing_active && !thread_Enemy_active){
        sleep(1);
    }
    printf("Reached target: CoreInfo \n");
    strcpy(sessiond._version_,VERSION_FULL_STR);
    printf("[ OK ] Fetched version: %s\n", sessiond._version_);
    printf("Fetching executable location. . .\n");
    _fetchExecLocation();
    printf("[ OK ] Fetched executable location: %s\n", sessiond._exec_path_);
    printf("Fetching installation location. . .\n");
    _fetchInstallationLocation();
    printf("[ OK ] Fetched installation location: %s\n", sessiond._installation_path_);

    printf("Reached target: registry \n");
    printf("Checking if registry config exists...\n");
    if(!DoesRegistryConfigExist()){
        printf("[ OK ] Registry config does not exist!\n");
        printf("Creating default registry data...\n");
        RegistryInit();
        printf("[ OK ] Created registry key: REGISTRY\\HKEY_CURRENT_USER\\%s\n",REG_PATH);
    } else {
        printf("[ OK ] Found registry config: REGISTRY\\HKEY_CURRENT_USER\\%s\n",REG_PATH);
    }

    printf("Applying alwaysLogfile from REG_DWORD REGISTRY\\HKEY_CURRENT_USER\\%s\\alwaysLogfile. . .\n",REG_PATH);
    DWORD useLog = RegistryReadDword("alwaysLogfile");
    if(useLog < 0){
        SetFatalParamater("REGISTRY\\HKEY_CURRENT_USER\\%s\\alwaysLogfile < 0");
        HANDLE_fatal("REGISTRY_BAD_CONFIGURATION",__REGISTRY_BAD_CONFIGURATION);
    }
    if(useLog == 1){
        settings.LogFileExist = true;
    } else {
        settings.LogFileExist = false;
    }
    if(settings.LogFileExist){
        //create newline
        ETC_file(_FILE_DEBUG_LOG,"Stack begin","a","OUT");
        ETC_file(_FILE_DEBUG_LOG,sessiond._verinfo,"a","OUT");
    }
    printf("[ OK ] Applied alwaysLogfile\n");

    printf("Applying Color from REG_DWORD REGISTRY\\HKEY_CURRENT_USER\\%s\\Color. . .\n",REG_PATH);
    char *colorsel = RegistryReadSz("Color");
    char colorstr[25];
    sprintf(colorstr,"color %s",colorsel);
    system(colorstr);
    printf("[ OK ] Applied Color\n");

    printf("Applying SuppressSplashMessage from REG_DWORD REGISTRY\\HKEY_CURRENT_USER\\%s\\SuppressSplashMessage. . .\n",REG_PATH);
    DWORD suppres = RegistryReadDword("SuppressSplashMessage");

    if(suppres < 0){
        SetFatalParamater("REGISTRY\\HKEY_CURRENT_USER\\%s\\SuppressSplashMessage < 0");
        HANDLE_fatal("REGISTRY_BAD_CONFIGURATION",__REGISTRY_BAD_CONFIGURATION);
    }
    if(suppres == 1){
        settings.SuppressSplashMessage = true;
    } else {
        settings.SuppressSplashMessage = false;
    }
    printf("[ OK ] Applied SuppressSplashMessage\n");

    printf("Applying DumpstackOnCrash from REG_DWORD REGISTRY\\HKEY_CURRENT_USER\\%s\\DumpstackOnCrash. . .\n",REG_PATH);
    DWORD dumps = RegistryReadDword("DumpstackOnCrash");
    if(dumps < 0){
        SetFatalParamater("REGISTRY\\HKEY_CURRENT_USER\\%s\\DumpstackOnCrash < 0");
        HANDLE_fatal("REGISTRY_BAD_CONFIGURATION",__REGISTRY_BAD_CONFIGURATION);
    }
    if(dumps == 1){
        settings.DumpstackOnCrash = true;
    } else {
        settings.DumpstackOnCrash = false;
    }

    printf("Applying DumpstackOnCrash from REG_DWORD REGISTRY\\HKEY_CURRENT_USER\\%s\\alwaysDebug. . .\n",REG_PATH);
    DWORD alwaysDbg = RegistryReadDword("alwaysDebug");
    if(alwaysDbg < 0){
        SetFatalParamater("REGISTRY\\HKEY_CURRENT_USER\\%s\\alwaysDebug < 0");
        HANDLE_fatal("REGISTRY_BAD_CONFIGURATION",__REGISTRY_BAD_CONFIGURATION);
    }
    if(alwaysDbg){
        settings.isDebug = true;
    } else {
        settings.isDebug = false;
    }
    printf("[ OK ] Applied alwaysDebug\n");

    printf("Reached target: helper\n");
    verifyhelper:
    printf("Initializing helper. . .\n");
    init_helper();
    //temporary file
    printf("Reached target: temporary container \n");
    printf("Creating runtime temp file. . .\n");
    createTemporaryContentContainer();
    printf("[ OK ] Runtime temp was created.\n");

    //extension
    printf("Reached target: extensions\n");
    doInitLua();


    //sessiond
    printf("Reached target: sessiond\n");
    printf("Initializing values of session data.\n");
    sessiond.FirstRun = true;
    sessiond.LoggedIn = false;
    sessiond.SetupCompleted = false;
    sessiond.Poweroff.Chance = 10;
    sessiond.Poweroff.isPowerout = false;
    sessiond.Poweroff.When = GetUnixEpochTime() + 600;
    settings.AllowPowerout = true;
    strcpy(sessiond.bp_func, "value_not_set!");
    printf("[ OK ] The required values have been set.\n");
    printf("Creating session ID. . .\n");
    sessionID();
    printf("[ OK  ] Session ID created: %d\n", sessiond.sessionID);
    printf("[ NOTICE] Initialzing values. . .\n");
    universal_data_init();
    printf("[ OK ] Initialized\n");
    if(settings.isDebug && !settings.LogFileExist){
        bool c = confirm("[ STARTUP/INTERRUPT ] Debug mode is enabled, would you like to also enable the log file?");
        if(c){
            ETC_file(_FILE_DEBUG_LOG,"Stack begin","w","OUT");      
            settings.LogFileExist=true;
        }
    }

    printf("Reached target: gameStart \n");
    printf("[ OK ] Startup has completed!\n");