int ping(const char *dest){
    WSADATA wsaData;
    HANDLE icmpFile;
    ULONG ipaddr = INADDR_NONE;
    char sendData[BUFFER_SIZE] = "Ping test";
    char recvData[BUFFER_SIZE];
    IPAddr destIP;
    PICMP_ECHO_REPLY echoReply;
    DWORD ret;
    struct sockaddr_in destAddr;
    int i;

    if(WSAStartup(MAKEWORD(2,2),&wsaData) != 0){
        printf("[-] WSAStartup failed: %09X\n",WSAGetLastError());
        return (WSAGetLastError());
    }

    ipaddr = inet_addr(dest);
    printf("[+] Resolving hostname...\n");
    if(ipaddr == INADDR_NONE){
        struct hostent *host = gethostbyname(dest);
        if(host == NULL){
            printf("[-] Failed to resolve hostname: \"%s\"",dest);
            WSACleanup();
            return (WSAGetLastError());
        }
        memcpy(&destIP,host->h_addr_list[0],host->h_length);
    } else {
        destIP = ipaddr;
    }
    struct hostent *host = gethostbyname(dest);
    if(host == NULL){
        printf("[-] Failed to resolve hostname: \"%s\"",dest);
        WSACleanup();
        printf("[+] Exiting `%s`...\n",argv[0]);
        return (WSAGetLastError());
    }
    printf("[+] Resolved hostname is %s\n",host->h_name);

    icmpFile = IcmpCreateFile();
    if(icmpFile == INVALID_HANDLE_VALUE){
        printf("[-] IcmpCreateFile failed!\n");
        IcmpCloseHandle(icmpFile);
        WSACleanup();
        printf("[+] Exiting `%s`...\n",argv[0]);
        return (WSAGetLastError());
    }

    echoReply = (PICMP_ECHO_REPLY)malloc(sizeof(ICMP_ECHO_REPLY) + BUFFER_SIZE);
    if(echoReply == NULL){
        printf("[-] Memory allocation failed!\n");
        IcmpCloseHandle(icmpFile);
        WSACleanup();
        printf("[+] Exiting `%s`...\n",argv[0]);
        return (WSAGetLastError());
    }

    ULONG Times[4];
    printf("[+] Start ping...\n");
    for(int i = 0; i < 4; i++){
        ret = IcmpSendEcho(icmpFile,destIP,sendData,BUFFER_SIZE,NULL,echoReply,sizeof(ICMP_ECHO_REPLY) + BUFFER_SIZE, TIMEOUT);
        printf("REPLY: ");
        if(ret != 0){
            Times[i] = echoReply->RoundTripTime;
            printf("%s, ",inet_ntoa(*(struct in_addr *)&echoReply->Address));
            printf("%lu ms, ",echoReply->RoundTripTime);
            switch(echoReply->Status){
                case IP_SUCCESS:
                    printf("IP_SUCCESS\n");
                    break;
                default:
                    printf("<status: %lu>\n",echoReply->Status);
            }
        } else {
            printf("TIMED OUT\n");
        }
        Sleep(1000);
    }

    printf("\n");
    //get mean of Times[]
    ULONG meanTimes;
    meanTimes = (Times[0] + Times[1] + Times[2] + Times[3]) / 4;
    printf("Average roundtrip time (mean): %lu ms\n",meanTimes);


    free(echoReply);
    IcmpCloseHandle(icmpFile);
    WSACleanup();
