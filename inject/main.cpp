#include <Windows.h>

#include <cstdio>
#include <tlhelp32.h>
#include <sstream>
#include <vector>


int Error(HANDLE process, const char *fmt);
DWORD GetProcessID(const char *exeFile);

int main(int argc, char *argv[]) {

    // quick way to override which dll to inject.
    std::string dll = "dungeoneer.dll";
    if (argc == 2) {
        dll = argv[1];
    }

    TCHAR dir[MAX_PATH];
    char  dllPath[MAX_PATH];
    DWORD len = GetCurrentDirectory(MAX_PATH, &dir[0]);
    sprintf(dllPath, "%s\\%s", dir, dll.c_str()); // console.dll

    printf("Dll: %s\n", dllPath);

    // Find the running .exe
    DWORD pid = 0;
    const std::vector<std::string> exeFiles = {"Dungeons.exe", "Dungeons-Win64-Shipping.exe"};
    for(const auto& exeFile: exeFiles) {
        pid = GetProcessID(exeFile.c_str());
        if (pid != 0) {
            printf("Found %s\n", exeFile.c_str());
            break;
        }

        printf("Unable to find %s process\n", exeFile.c_str());
    }

    if (pid == 0) {
        printf("Unable to find any Minecraft Dungeons processes running\n");
        return -1;
    }

    printf("Process: (%d)\n", pid);

    //Open the target process with read , write and execute priviledges
    HANDLE process = OpenProcess(PROCESS_CREATE_THREAD|PROCESS_QUERY_INFORMATION|PROCESS_VM_READ|PROCESS_VM_WRITE|PROCESS_VM_OPERATION, FALSE, pid); 
    if (process == NULL) {
        return Error(process, "Unable to open process. %d\n");
    }


    //Get the address of LoadLibraryA
    LPVOID LoadLibrary = GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
    if (LoadLibrary == NULL) {
        return Error(process, "Unable to find LoadLibrary function. %d\n");
    }

    // Allocate space in the process for our DLL 
    LPVOID memory = VirtualAllocEx(process, NULL, strlen(dllPath)+1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE); 
    if (memory == NULL) {
        return Error(process, "Unable to find allocate memory in process. %d\n");
    }

    // Write the string name of our DLL in the memory allocated 
    BOOL writeResult = WriteProcessMemory(process, (LPVOID)memory, dllPath, strlen(dllPath)+1, NULL); 
    if (writeResult == FALSE) {
        return Error(process, "Unable to write memory in process. %d\n");
    }

    // Load our DLL 
    HANDLE thread = CreateRemoteThread(process, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibrary, (LPVOID)memory, NULL, NULL); 
    if (thread == NULL) {
        return Error(process, "Unable to create remote thread in process. %d\n");
    }

    // Let the program regain control of itself
    BOOL closeResult = CloseHandle(process);
    if (closeResult == FALSE) {
         return Error(NULL, "Unable to close process. %d\n");
    }

    printf("Injected %s in to (%d)\n", dllPath, pid);
    return 0;
}

int Error(HANDLE process, const char *fmt) {
    printf(fmt, GetLastError());
    if (process != NULL) {
        CloseHandle(process);
    }
    return -1;
}

DWORD GetProcessID(const char *exeFile) {
    PROCESSENTRY32 entry;
    ZeroMemory(&entry, sizeof(entry));
    entry.dwSize = sizeof(PROCESSENTRY32);
    DWORD pid = 0;

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);    
    if (Process32First(snapshot, &entry) == TRUE) {
        do {
            if (stricmp((char *)entry.szExeFile, exeFile) == 0) {
                pid = entry.th32ProcessID;
                break;
            }
        } while(Process32Next(snapshot, &entry) == TRUE);
    }

    CloseHandle(snapshot);
    return pid;
}

