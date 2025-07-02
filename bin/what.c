#include <windows.h>
#include <stdio.h>

int main() {
    HKEY hKey;
    DWORD dwType = REG_SZ;
    DWORD dwSize = 256;
    char gpuName[256] = {0}; 
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, 
                      "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\WinSAT\\", 
                      0, 
                      KEY_READ, 
                      &hKey) == ERROR_SUCCESS) {

        if (RegQueryValueExA(hKey, 
                            "PrimaryAdapterString", 
                            NULL, 
                            &dwType, 
                            (LPBYTE)gpuName, 
                            &dwSize) == ERROR_SUCCESS) {

            printf("GPU Name: %s\n", gpuName);

        } else {
            printf("Failed to read GPU name from registry.\n");
        }

        RegCloseKey(hKey);

    } else {
        printf("Failed to open registry key.\n");
    }

    return 0;
}