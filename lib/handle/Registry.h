#ifndef _REGISTRY
#define _REGISTRY
#pragma message("===> Building file "__FILE__)

#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>

#include "../game/hook.h"
#include "../game/struct.h"
#include "debug/c_handle.h"
#include "debug/etc/error.h"
#define REG_PATH "Software\\SomeTerminalGame"
extern external_settings settings;
extern session_informaton sessiond;
bool RegistryInit();
char *RegistryReadSz(char *ValueName);

//registry cache stuff (prevents repeated read from values)

enum RegistryCache_t{
    Dword,
    Sz
};

typedef struct{
    enum RegistryCache_t type;
    char *path;
    char *RegSZ;
    DWORD RegDword;
}RegistryCache,*pRegistryCache;


pRegistryCache cache_data = NULL;
size_t cache_size = 0;
size_t cache_capacity = 0;

bool InitRegistryCache(void){
    _stack_;
    _check_bp;
    if(!settings.useRegistryCache) return false;
    printf("Init registry cache...");
    cache_data = (pRegistryCache)malloc(sizeof(pRegistryCache) * 25);
    printf("done\n");
    return true;
}

bool FlushRegistryCache(void){
    if(!settings.useRegistryCache) return false;
    ETC_file2(_FILE_DEBUG_LOG,"a","OUT","registry: flushed cache");
    _stack_;
    _check_bp;
    free(cache_data);
    cache_size = 0;
    cache_capacity = 0;
    return true;
}

bool WriteCacheString(char *path,char *data){
    if(!settings.useRegistryCache) return false;
    _stack_;
    _check_bp;
    if(cache_size >= cache_capacity){
        size_t new_capacity = (cache_capacity == 0) ? 1 : cache_capacity * 2;
        pRegistryCache temp = realloc(cache_data,new_capacity * sizeof(pRegistryCache));

        if(temp == NULL){
            HANDLE_fatal("MEMORY_ALLOCATION_FAILURE",__MEMORY_ALLOCATION_FAILURE);
        }

        cache_data = temp;
        cache_capacity = new_capacity;
    }
    cache_data[cache_size].path = path;
    cache_data[cache_size].RegSZ = data;
    cache_data[cache_size].type = Sz;
    debugLog("OUT","registry: write cached string data: %s=\"%s\"",path,data);
    cache_size++;
    return true;
}

bool WriteCacheDword(char *path,DWORD ddata){
    if(!settings.useRegistryCache) return false;
    _stack_;
    _check_bp;
    if(cache_size >= cache_capacity){
        size_t new_capacity = (cache_capacity == 0) ? 1 : cache_capacity * 2;
        pRegistryCache temp = realloc(cache_data,new_capacity * sizeof(pRegistryCache));

        if(temp == NULL){
            HANDLE_fatal("MEMORY_ALLOCATION_FAILURE",__MEMORY_ALLOCATION_FAILURE);
        }

        cache_data = temp;
        cache_capacity = new_capacity;
    }
    cache_data[cache_size].path = path;
    cache_data[cache_size].RegDword = ddata;
    cache_data[cache_size].type = Dword;
    debugLog("OUT","registry: write cached dword data: %s=%d",path,ddata);
    cache_size++;
    return true;
}

bool GetCachedValue(char *path, pRegistryCache out){
    if(!settings.useRegistryCache) return false;
    _stack_;
    _check_bp;
    for(int i = 0; i < cache_size; i++){
        if(strcmp(path,cache_data[i].path)==0){
            *out = cache_data[i];
            if(out->type == Sz){
                debugLog("OUT","registry: read cached string data: %s=\"%s\"",path,out->RegSZ);
            } else if(out->type = Dword){
                debugLog("OUT","registry: read cached dword data: %s=%d\n",path,out->RegDword);
            }
            return true;
        }
    }
    return false;
}

bool SetCachedValueDword(char *path,DWORD new){
    if(!settings.useRegistryCache) return false;
    _stack_;
    _check_bp;
    debugLog("OUT","registry: update cached dword %s=%d",path,new);
    for(int i = 0; i < cache_size; i++){
        if(strcmp(path,cache_data[i].path)==0){
            cache_data[i].RegDword = new;
        }
    }
    return false;
}


bool SetCachedValueSz(char *path,char *new){
    if(!settings.useRegistryCache) return false;
    _stack_;
    _check_bp;
    debugLog("OUT","registry: update cached string %s=\"%s\"",path,new);
    for(int i = 0; i < cache_size; i++){
        if(strcmp(path,cache_data[i].path)==0){
            cache_data[i].RegSZ = new;
        }
    }
    return false;
}

bool DoesRegistryConfigExist(){
    _stack_;
    _check_bp;
    long status;
    HKEY hKey;
    status = RegOpenKeyExA(HKEY_CURRENT_USER,REG_PATH,0,KEY_READ,&hKey);
    if(status == ERROR_SUCCESS){
        RegCloseKey(hKey);
        return true;
    } else {
        return false;
    }
}

bool RegistryReset(){
    _stack_;
    _check_bp;
    if(settings.LogFileExist){
        ETC_file(_FILE_DEBUG_LOG,"registry: value reset","a","OUT");
    }

    long status;
    status = RegDeleteKeyExA(HKEY_CURRENT_USER,"Software\\SomeTerminalGame",KEY_ALL_ACCESS,0);
    if(status == ERROR_SUCCESS){
        RegistryInit();
        return true;
    } else {
        HANDLE_fatal("REGISTRY_VALUE_WRITE_FAILURE",__REGISTRY_KEY_READ_FAILURE);
    }
    return false;
}

bool RegistryInit(){
    _stack_;
    _check_bp;

    if(settings.LogFileExist){
        ETC_file(_FILE_DEBUG_LOG,"registry: init","a","OUT");
    }

    HKEY hKey;
    long status;
    status = RegCreateKeyExA(HKEY_CURRENT_USER,REG_PATH,0,NULL,REG_OPTION_NON_VOLATILE,
                            KEY_WRITE,NULL,&hKey,NULL);
    if(status == ERROR_SUCCESS){
        DWORD data = 1;
        DWORD data2 = 0;

        status = RegSetValueExA(hKey,"DumpstackOnCrash",0,REG_DWORD,(const BYTE*)&data,sizeof(data));
        if(status != ERROR_SUCCESS){
            RegCloseKey(hKey);
            HANDLE_fatal("REGISTRY_VALUE_WRITE_FAILURE",__REGISTRY_KEY_READ_FAILURE);
        }
        printf("(REG_DWORD) DumpstackOnCrash=1\n");

        status = RegSetValueExA(hKey,"SuppressSplashMessage",0,REG_DWORD,(const BYTE*)&data2,sizeof(data2));
        if(status != ERROR_SUCCESS){
            RegCloseKey(hKey);
            HANDLE_fatal("REGISTRY_VALUE_WRITE_FAILURE",__REGISTRY_KEY_READ_FAILURE);
        }
        printf("(REG_DWORD) SuppressSplashMessage=0\n");

        status = RegSetValueExA(hKey,"alwaysDebug",0,REG_DWORD,(const BYTE*)&data2,sizeof(data2));
        if(status != ERROR_SUCCESS){
            RegCloseKey(hKey);
            HANDLE_fatal("REGISTRY_VALUE_WRITE_FAILURE",__REGISTRY_KEY_READ_FAILURE);
        }
        printf("(REG_DWORD) alwaysDebug=0\n");

        status = RegSetValueExA(hKey,"useRegistryCache",0,REG_DWORD,(const BYTE*)&data,sizeof(data));
        if(status != ERROR_SUCCESS){
            RegCloseKey(hKey);
            HANDLE_fatal("REGISTRY_VALUE_WRITE_FAILURE",__REGISTRY_KEY_READ_FAILURE);
        }
        printf("(REG_DWORD) useRegistryCache=1\n");

        status = RegSetValueExA(hKey,"alwaysLogfile",0,REG_DWORD,(const BYTE*)&data2,sizeof(data2));
        if(status != ERROR_SUCCESS){
            RegCloseKey(hKey);
            HANDLE_fatal("REGISTRY_VALUE_WRITE_FAILURE",__REGISTRY_KEY_READ_FAILURE);
        }
        printf("(REG_DWORD) alwaysLogfile=0\n");
        

        char data3[3] = "02";
        status = RegSetValueExA(hKey,"Color",0,REG_SZ,(const BYTE*)&data3,sizeof(data3));
        if(status != ERROR_SUCCESS){
            RegCloseKey(hKey);
            HANDLE_fatal("REGISTRY_VALUE_WRITE_FAILURE",__REGISTRY_KEY_READ_FAILURE);
        }
        printf("(REG_SZ) Color=\"02\"\n");
    } else {
        HANDLE_fatal("REGISTRY_KEY_READ_FAILURE",__REGISTRY_KEY_READ_FAILURE);
    }
    RegCloseKey(hKey);
    return true;
}

DWORD RegistryReadDword(char *ValueName){
    _stack_;
    _check_bp;
    DWORD type = REG_DWORD;
    HKEY hKey;
    DWORD data;
    DWORD size = sizeof(data);
    long status;
    bool cached = false;
    RegistryCache out;
    cached = GetCachedValue(ValueName,&out);
    if(cached){
        return out.RegDword;
    }

    status = RegOpenKeyExA(HKEY_CURRENT_USER,REG_PATH,0,KEY_READ,&hKey);
    if(status == ERROR_SUCCESS){
        status = RegQueryValueExA(hKey,ValueName,NULL,NULL,(LPBYTE)&data,&size);
        char *temp3 = malloc(256);
        sprintf(temp3,"registry: read REG_DWORD: REGISTRY\\HKEY_CURRENT_USER\\%s\\%s=%d",REG_PATH,ValueName,data);
        ETC_file(_FILE_DEBUG_LOG,temp3,"a","OUT");
        free(temp3);
        if(status == ERROR_SUCCESS){
            RegCloseKey(hKey);
            return data;
        } else {
            RegCloseKey(hKey);
            HANDLE_fatal("REGISTRY_VALUE_READ_FAILURE",__REGISTRY_KEY_READ_FAILURE);
        }
    } else {
        HANDLE_fatal("REGISTRY_KEY_READ_FAILURE",__REGISTRY_KEY_READ_FAILURE);
    }
    return 0;
}

char *RegistryReadSz(char *ValueName){
    _stack_;
    _check_bp;
    DWORD type = REG_SZ;
    DWORD size;
    HKEY hKey;
    char *data = NULL;
    long status;
    bool cached = false;
    RegistryCache out;
    cached = GetCachedValue(ValueName,&out);
    if(cached){
        return out.RegSZ;
    }

    status = RegOpenKeyExA(HKEY_CURRENT_USER,REG_PATH,0,KEY_READ,&hKey);
    if(status == ERROR_SUCCESS){
        //get size
        status = RegQueryValueExA(hKey,ValueName,NULL,&type,NULL,&size);
        if(status == ERROR_SUCCESS){
            data = (char*)malloc(size);
            if(data == NULL){
                RegCloseKey(hKey);
                HANDLE_fatal("MEMORY_ALLOCATION_FAILURE",__MEMORY_ALLOCATION_FAILURE);
            }
            status = RegQueryValueExA(hKey,ValueName,NULL,&type,(LPBYTE)data,&size);
            if(status != ERROR_SUCCESS){
                RegCloseKey(hKey);
                free(data);
                HANDLE_fatal("REGISTRY_VALUE_READ_FAILURE",__REGISTRY_KEY_READ_FAILURE);
            }
            char *temp3 = malloc(256);
            sprintf(temp3,"registry: read REG_SZ: REGISTRY\\HKEY_CURRENT_USER\\%s\\%s=\"%s\"",REG_PATH,ValueName,data);
            if(!cached){
                WriteCacheString(ValueName,data);
            }
            ETC_file(_FILE_DEBUG_LOG,temp3,"a","OUT");
            free(temp3);
            return data;
        } else {
            RegCloseKey(hKey);
            HANDLE_fatal("SIZE_QUERY_FAILURE",__SIZE_QUERY_FAILURE);
        }
    } else {
        HANDLE_fatal("REGISTRY_KEY_READ_FAILURE",__REGISTRY_KEY_READ_FAILURE);
    }
    return NULL;
}

bool RegistrySetSz(char *ValueName,char *NewData){
    _stack_;
    _check_bp;

    DWORD type = REG_SZ;
    DWORD size;
    HKEY hKey;
    long status;

    status = RegOpenKeyExA(HKEY_CURRENT_USER,REG_PATH,0,KEY_WRITE,&hKey);
    if(status == ERROR_SUCCESS){
        status = RegSetValueExA(hKey,ValueName,0,REG_SZ,(LPBYTE)NewData,sizeof(NewData));
        SetCachedValueSz(ValueName,NewData);
        char *temp3 = malloc(256);
        sprintf(temp3,"registry: set REG_SZ: REGISTRY\\HKEY_CURRENT_USER\\%s\\%s=\"%s\"",REG_PATH,ValueName,NewData);
        ETC_file(_FILE_DEBUG_LOG,temp3,"a","OUT");
        free(temp3);
        if(status == ERROR_SUCCESS){
            RegCloseKey(hKey);
            return true;
        } else {
            RegCloseKey(hKey);
            HANDLE_fatal("REGISTRY_VALUE_WRITE_FAILURE",__REGISTRY_VALUE_WRITE_FAILURE);
        }
    } else {
        HANDLE_fatal("REGISTRY_KEY_READ_FAILURE",__REGISTRY_KEY_READ_FAILURE);
    }
    return false;
}

bool RegistrySetDword(char *ValueName,DWORD NewData){
    _stack_;
    _check_bp;

    DWORD size;
    HKEY hKey;
    long status;
    status = RegOpenKeyExA(HKEY_CURRENT_USER,REG_PATH,0,KEY_WRITE,&hKey);
    if(status == ERROR_SUCCESS){
        status = RegSetValueExA(hKey,ValueName,0,REG_DWORD,(LPBYTE)&NewData,sizeof(NewData));
        char *temp3 = malloc(256);
        sprintf(temp3,"registry: read REG_DWORD: REGISTRY\\HKEY_CURRENT_USER\\%s\\%s=%d",REG_PATH,ValueName,NewData);
        SetCachedValueDword(ValueName,NewData);
        ETC_file(_FILE_DEBUG_LOG,temp3,"a","OUT");
        free(temp3);
        if(status == ERROR_SUCCESS){
            RegCloseKey(hKey);
            return true;
        } else {
            RegCloseKey(hKey);
            HANDLE_fatal("REGISTRY_VALUE_WRITE_FAILURE",__REGISTRY_VALUE_WRITE_FAILURE);
        }
    } else {
        HANDLE_fatal("REGISTRY_KEY_READ_FAILURE",__REGISTRY_KEY_READ_FAILURE);
    }
    return false;
}

int RegistryPrintList(){
    HKEY hKey;
    DWORD dwIndex = 0;
    TCHAR achValue[255];
    DWORD cbValue = 255;
    DWORD dwType;
    printf("Contents of \\REGISTRY\\HKEY_CURRENT_USER\\%s\\\n",REG_PATH);

    // Open the desired registry key
    if (RegOpenKeyExA(HKEY_CURRENT_USER, REG_PATH, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        // Enumerate values within the key
        while (RegEnumValueA(hKey, dwIndex, achValue, &cbValue, NULL, &dwType, NULL, NULL) == ERROR_SUCCESS) {
            // Process each value (e.g., print name and type)
            switch (dwType) {
                case REG_DWORD:
                    DWORD result = RegistryReadDword(achValue);
                    printf("(REG_DWORD)   %s = %d\n",achValue,result);
                    break;
                case REG_SZ:
                    char *res = RegistryReadSz(achValue);
                    printf("(REG_SZ)      %s = \"%s\"",achValue,res);
                    break;
                default:
                    printf("Value Type: Unknown\n");
            }
            // Reset buffer size for next value
            cbValue = 255; 
            dwIndex++; 
        }

        RegCloseKey(hKey);
    } else {
        printf("Failed to open registry key\n");
    }
    printf("\n");

    return 0;
}

#endif