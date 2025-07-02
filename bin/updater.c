#include <windows.h> 
#include <winhttp.h>
#include <iphlpapi.h>
#include <IcmpAPI.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//cl updater.c ../lib/external/cJson/cJson.c

#pragma comment(lib, "winhttp.lib")
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

#define BUFFER_SIZE 32
#define TIMEOUT 1000

#define uMSG    "[ SomeTerminalGame/updater ] "
#define upMSG   "[ SomeTerminalGame/updater::ping ] "
#include "../lib/external/cJson/cJSON.h" // Include the cJSON library

char sha256_checksum[256];
long get_file_size(const char* file_path) {
    WIN32_FILE_ATTRIBUTE_DATA file_data;
    if (GetFileAttributesEx(file_path, GetFileExInfoStandard, &file_data)) {
        LARGE_INTEGER file_size;
        file_size.LowPart = file_data.nFileSizeLow;
        file_size.HighPart = file_data.nFileSizeHigh;
        return file_size.QuadPart;
    }
    return -1; // Return -1 on error
}


void display_progress_bar() {
    //printf("\r.");
    //printf("\r..");
    //printf("\r...");

    fflush(stdout); // Important: Flush the output buffer
}

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
        printf(upMSG" ERROR:  WSAStartup failed: %09X\n",WSAGetLastError());
        return (WSAGetLastError());
    }

    ipaddr = inet_addr(dest);
    printf(upMSG" Resolving hostname...\n");
    if(ipaddr == INADDR_NONE){
        struct hostent *host = gethostbyname(dest);
        if(host == NULL){
            printf(upMSG" ERROR:  Failed to resolve hostname: \"%s\"",dest);
            WSACleanup();
            return (WSAGetLastError());
        }
        memcpy(&destIP,host->h_addr_list[0],host->h_length);
    } else {
        destIP = ipaddr;
    }
    struct hostent *host = gethostbyname(dest);
    if(host == NULL){
        printf(upMSG" ERROR:  Failed to resolve hostname: \"%s\"",dest);
        WSACleanup();
        return (WSAGetLastError());
    }
    printf(upMSG" Resolved hostname is %s\n",host->h_name);

    icmpFile = IcmpCreateFile();
    if(icmpFile == INVALID_HANDLE_VALUE){
        printf(upMSG" ERROR:  IcmpCreateFile failed!\n");
        IcmpCloseHandle(icmpFile);
        WSACleanup();
        return (WSAGetLastError());
    }

    echoReply = (PICMP_ECHO_REPLY)malloc(sizeof(ICMP_ECHO_REPLY) + BUFFER_SIZE);
    if(echoReply == NULL){
        printf(upMSG" ERROR:  Memory allocation failed!\n");
        IcmpCloseHandle(icmpFile);
        WSACleanup();
        return (WSAGetLastError());
    }

    BOOL isOnline;
    ULONG Times[4];
    int timeOutCnt;
    printf(upMSG" Start ping...\n");
    for(int i = 0; i < 4; i++){
        ret = IcmpSendEcho(icmpFile,destIP,sendData,BUFFER_SIZE,NULL,echoReply,sizeof(ICMP_ECHO_REPLY) + BUFFER_SIZE, TIMEOUT);
        printf(upMSG"REPLY - ");
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
            if(echoReply->Status == IP_DEST_HOST_UNREACHABLE){
                isOnline = FALSE;
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
    printf(uMSG"Average roundtrip time (mean): %lu ms\n",meanTimes);


    free(echoReply);
    IcmpCloseHandle(icmpFile);
    WSACleanup();
    return (int)(isOnline);
}


// Function to fetch the JSON data from the URL
char* fetch_json_data(const char* url) {
    HINTERNET hInternet = NULL;
    HINTERNET hConnect = NULL;
    HINTERNET hRequest = NULL;

    char* json_data = NULL;
    DWORD bytes_read = 0;
    DWORD total_bytes = 0;
    char buffer[4096]; // Buffer for reading data

    // Initialize WinHTTP
    hInternet = WinHttpOpen(L"MyUpdateClient", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (hInternet == NULL) {
        fprintf(stderr, "WinHttpOpen failed: %lu\n", GetLastError());
        goto cleanup;
    }

    // Open a connection to the server
    wchar_t w_url[2048]; // Wide char version of the URL
    mbstowcs(w_url, url, strlen(url) + 1); // Convert to wide char
    URL_COMPONENTS url_components;
    memset(&url_components, 0, sizeof(url_components));
    url_components.dwStructSize = sizeof(url_components);
    url_components.lpszHostName = w_url;
    url_components.dwHostNameLength = wcslen(w_url);
    url_components.dwSchemeLength = -1;
    url_components.dwUrlPathLength = -1;
    WinHttpCrackUrl(w_url, 0, 0, &url_components);
    hConnect = WinHttpConnect(hInternet, url_components.lpszHostName, url_components.nPort, 0);


    if (hConnect == NULL) {
        fprintf(stderr, "WinHttpConnect failed: %lu\n", GetLastError());
        goto cleanup;
    }

    // Create an HTTP request
    hRequest = WinHttpOpenRequest(hConnect, L"GET", url_components.lpszUrlPath, NULL, 0, NULL, 0);
    if (hRequest == NULL) {
        fprintf(stderr, "WinHttpOpenRequest failed: %lu\n", GetLastError());
        goto cleanup;
    }

    // Send the request
    if (!WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, 0, 0, 0, 0)) {
        fprintf(stderr, "WinHttpSendRequest failed: %lu\n", GetLastError());
        goto cleanup;
    }

    // Receive the response
    if (!WinHttpReceiveResponse(hRequest, NULL)) {
        fprintf(stderr, "WinHttpReceiveResponse failed: %lu\n", GetLastError());
        goto cleanup;
    }

    // Allocate memory for the JSON data (start with a reasonable size)
    json_data = (char*)malloc(4096);
    if (json_data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        goto cleanup;
    }
    json_data[0] = '\0'; // Initialize as an empty string

    // Read the data in chunks
    do {
        if (!WinHttpReadData(hRequest, buffer, sizeof(buffer), &bytes_read)) {
            fprintf(stderr, "WinHttpReadData failed: %lu\n", GetLastError());
            goto cleanup;
        }

        if (bytes_read > 0) {
            // Reallocate memory to accommodate the new data
            char* temp = (char*)realloc(json_data, total_bytes + bytes_read + 1);
            if (temp == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                goto cleanup;
            }
            json_data = temp;
            memcpy(json_data + total_bytes, buffer, bytes_read);
            total_bytes += bytes_read;
            json_data[total_bytes] = '\0'; // Null-terminate
        }
    } while (bytes_read > 0);

cleanup:
    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hInternet) WinHttpCloseHandle(hInternet);

    if (json_data == NULL && total_bytes > 0) {
      json_data = malloc(total_bytes+1);
      memcpy(json_data, buffer, total_bytes);
      json_data[total_bytes] = '\0';
    }

    return json_data;
}

int fetch_update_file(const char* url, const char* file_path) {
    HINTERNET hInternet = NULL;
    HINTERNET hConnect = NULL;
    HINTERNET hRequest = NULL;
    FILE* fp = NULL;

    DWORD bytes_read = 0;
    char buffer[4096];

    // Initialize WinHTTP
    hInternet = WinHttpOpen(L"MyUpdateClient", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (hInternet == NULL) {
        fprintf(stderr, "WinHttpOpen failed: %lu\n", GetLastError());
        return 1;
    }

    // Open a connection to the server
    wchar_t w_url[2048];
    mbstowcs(w_url, url, strlen(url) + 1);
    URL_COMPONENTS url_components;
    memset(&url_components, 0, sizeof(url_components));
    url_components.dwStructSize = sizeof(url_components);
    url_components.lpszHostName = w_url;
    url_components.dwHostNameLength = wcslen(w_url);
    url_components.dwSchemeLength = -1;
    url_components.dwUrlPathLength = -1;
    WinHttpCrackUrl(w_url, 0, 0, &url_components);

    hConnect = WinHttpConnect(hInternet, url_components.lpszHostName, url_components.nPort, 0);
    if (hConnect == NULL) {
        fprintf(stderr, "WinHttpConnect failed: %lu\n", GetLastError());
        goto cleanup;
    }

    // Create an HTTP request
    hRequest = WinHttpOpenRequest(hConnect, L"GET", url_components.lpszUrlPath, NULL, 0, NULL, 0);
    if (hRequest == NULL) {
        fprintf(stderr, "WinHttpOpenRequest failed: %lu\n", GetLastError());
        goto cleanup;
    }

    // Send the request
    if (!WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, 0, 0, 0, 0)) {
        fprintf(stderr, "WinHttpSendRequest failed: %lu\n", GetLastError());
        goto cleanup;
    }
    // Receive the response
    if (!WinHttpReceiveResponse(hRequest, NULL)) {
        fprintf(stderr, "WinHttpReceiveResponse failed: %lu\n", GetLastError());
        goto cleanup;
    }
    //start
    // 7. Get Content-Length (after receiving response)
    DWORD content_length_length = 0; // Length of the content length string
    if (!WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_CONTENT_LENGTH, NULL, NULL, &content_length_length, NULL)) {
        // Get the required buffer size
        DWORD last_error = GetLastError();
        if (last_error != ERROR_INSUFFICIENT_BUFFER) {
            fprintf(stderr, "WinHttpQueryHeaders (size) failed: %lu\n", last_error);
            goto cleanup;
        }
    }
    // Open the file for writing (binary mode)
    fp = fopen(file_path, "wb"); // Important: Use binary mode ("wb")
    if (fp == NULL) {
        fprintf(stderr, "Error opening file for writing.\n");
        goto cleanup;
    }
    long current_size = 0;
    clock_t start = clock();
    // Read the data in chunks and write to the file
    do {
        if (!WinHttpReadData(hRequest, buffer, sizeof(buffer), &bytes_read)) {
            fprintf(stderr, "WinHttpReadData failed: %lu\n", GetLastError());
            goto cleanup;
        }

        if (bytes_read > 0) {
            fwrite(buffer, 1, bytes_read, fp); // Write the data to the file
            current_size += bytes_read;
            if(current_size > 0){
                printf("\r%sDownloaded %.2f KiB",uMSG,(double)current_size / 1024);
                fflush(stdout);
            }
        }
    } while (bytes_read > 0);
    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\r%sDownloaded in %.2f seconds\n",uMSG, elapsed);

cleanup:
    if (fp) fclose(fp);
    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hInternet) WinHttpCloseHandle(hInternet);

    return 0;
}

int main(void) {
    printf(uMSG"Checking host availablity...");
    int ret = ping("192.168.0.78");
    if(ret == 0){
        printf("not online\n");
        exit(0);
    }
    const char* url = "http://192.168.0.78/updinfo.json"; // Replace with your URL
    printf("%sFetching update information...",uMSG);
    clock_t start;
    clock_t end;
    double elapsed;
    start = clock();
    char* json_string = fetch_json_data(url);
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\r%sFetched update information in %.2f seconds\n",uMSG,elapsed);

    if (json_string == NULL) {
        fprintf(stderr, "Failed to fetch JSON data.\n");
        return 1;
    }
    
    printf("%sParsing JSON...",uMSG);
    // Parse the JSON data
    start = clock(); 
    cJSON* root = cJSON_Parse(json_string);
    if (root == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        goto cleanup_json;
    }
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\r%sParsed JSON in %.2f seconds\n",uMSG,elapsed);
    // Extract the "Build" and "FileLocation" values
    cJSON* build = cJSON_GetObjectItemCaseSensitive(root, "Build");
    cJSON* file_location = cJSON_GetObjectItemCaseSensitive(root, "FileLocation");
    cJSON* SHA256 = cJSON_GetObjectItemCaseSensitive(root,"SHA256");
    if (cJSON_IsString(build) && cJSON_IsString(file_location)) {
        char updateurl[2050];
        sprintf(updateurl,"http://192.168.0.78/%s",file_location->valuestring);
        printf("%s\"Build\": \"%s\"\n", uMSG, build->valuestring);
        printf("%s\"FileLocation\": \"%s\"\n",uMSG, file_location->valuestring);
        strcpy(sha256_checksum,SHA256->string);
        if(fetch_update_file(updateurl,"./update.exe") != 0){
            fprintf(stderr,"%sERROR: Failed to download update file.\n",uMSG);
        }
    } else {
        fprintf(stderr, "%sERROR: Invalid JSON format.\n",uMSG);
    }

cleanup_json:
    cJSON_Delete(root);
    free(json_string); // Free the allocated memory
    return 0;
}
