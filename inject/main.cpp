#include <Windows.h>

#include <cstdio>
#include <tlhelp32.h>
#include "patternscan.h"
#include <sstream>
#include <vector>


struct OffsetLookup {
    const char *name;
    const char *opcodes;
    uintptr_t offset; // in case base address of the opcodes isn't where we can find our value.
};

int Error(HANDLE process, const char *fmt);
DWORD GetProcessID(const char *exeFile);
int FindOffsets(DWORD pid);
uintptr_t FindOffset(HANDLE process, MODULEENTRY32 modEntry, OffsetLookup lookup);
int parseHex(std::string hex, BYTE *bytes, std::stringstream *mask);

int main() {
    TCHAR dir[MAX_PATH];
    char  dllPath[MAX_PATH];
    DWORD len = GetCurrentDirectory(MAX_PATH, &dir[0]);
    sprintf(dllPath, "%s\\%s", dir, "console.dll");

    printf("Dll: %s\n", dllPath);

    const char *exeFile = "Dungeons-Win64-Shipping.exe";
    DWORD pid = GetProcessID(exeFile);
    if (pid == 0) {
        printf("Unable to find %s process\n", exeFile);
        return -1;
    }
    printf("Process: (%d) %s\n", pid, exeFile);

    // TODO Make the dungeoneer.dll find these offsets
    FindOffsets(pid);

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

    printf("Injected %s in to (%d) %s\n", dllPath, pid, exeFile);
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


// Get ModuleEntry from module name, using toolhelp32snapshot:
MODULEENTRY32 GetModule(const DWORD &pid, const char *modName) {
	MODULEENTRY32 modEntry = {0};

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);

	if (snapshot != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 curr = {0};
		curr.dwSize = sizeof(MODULEENTRY32);

		if (Module32First(snapshot, &curr)) {
			do {
				if (strcmp(curr.szModule, modName) == 0) {
					modEntry = curr;
					break;
				}
			} while (Module32Next(snapshot, &curr));
		}
		CloseHandle(snapshot);
	}
	return modEntry;
}


int FindOffsets(DWORD pid) {
    
    //Open the target process with read , write and execute priviledges
    HANDLE process = OpenProcess(PROCESS_CREATE_THREAD|PROCESS_QUERY_INFORMATION|PROCESS_VM_READ|PROCESS_VM_WRITE|PROCESS_VM_OPERATION, FALSE, pid); 
    if (process == NULL) {
        return Error(process, "Unable to open process. %d\n");
    }

    MODULEENTRY32 modEntry = GetModule(pid, "Dungeons-Win64-Shipping.exe");
	if (modEntry.th32ModuleID == 0) {
		return Error(process, "Unable to find Dungeons-Win64-Shipping.exe module. %d\n");
	}

    std::vector<OffsetLookup> lookups;

    
    // This lookup only shows a function which has a parent function with a ref to the variable.  See guobjectarray.md
    lookups.push_back({
        "GUObjectArray",
        "41 54 48 81 EC C0 00 00 00 44 0F B6 E1 44 0F 29 44 24 60 ?? ?? ?? ?? ?? ?? ?? 44 0F 28 C1",
    });

    // This lookup only shows a function which references the GNames variable. See gnames.md
    lookups.push_back({
        "GNames",
        "48 83 EC 28 ?? ?? ?? ?? ?? ?? ?? 48 85 C0 ?? ?? B9 08 08 00 00 48 89 5C 24 20",
    });
    
    // Same as above, use IDA Pro for now to find it. See gengine.md
    lookups.push_back({
        "gengine",
        "48 89 7C 24 30 48 8B C8 40 88 7C 24 28 45 33 C9 4C 8B C7 48 89 7C 24 20 48 8B D3 ?? ?? ?? ?? ?? 48 8B 4C 24 40",
    });
    
    // These offsets can just be copy pasted in to the code

    lookups.push_back({
        "AHUD_DrawRect",
        "48 8B C4 48 89 58 08 57 48 81 EC E0 00 00 00 0F 29 70 E8 48 8B FA 0F 29 78 D8 0F 28 F3 0F 28 FA 48 8B D9",
    });
    lookups.push_back({
        "AHUD_DrawText",
        "40 55 56 57 48 81 EC 30 02 00 00 44 0F 29 84 24 00 02 00 00",
    });
    lookups.push_back({
        "AHUD_GetTextSize",
        "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 40 49 8B F9 49 8B F0 48 8B EA 48 8B D9 ?? ?? ?? ?? ?? 84 C0",
    });
    lookups.push_back({
        "StaticLoadObject",
        "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 18 FE FF FF 48 81 EC E8 02 00 00 ?? ?? ?? ?? ?? ?? ?? 48 33 C4 48 89 85 D0 01 00 00 48 8B 85 68 02 00 00",
    });
    lookups.push_back({
        "StaticLoadClass",
        "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 08 FF FF FF 48 81 EC F8 01 00 00 ?? ?? ?? ?? ?? ?? ?? 48 33 C4 48 89 85 E0 00 00 00 8B BD 60 01 00 00",
    });
    lookups.push_back({
        "LoadPackage",
        "48 8B C4 53 56 48 83 EC 68 48 89 68 08 48 8B EA 4C 89 60 18 33 D2 4C 89 68 E8 4C 8B E1 4C 89 70 E0 48 8D 48 C8 4C 89 78 D8 45 33 ED",
    });

    // Hooked functions
    lookups.push_back({
        "UObject_ProcessEvent",
        "40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC F0 00 00 00 48 8D 6C 24 30 48 89 9D 18 01 00 00",
    });
    lookups.push_back({
        "AHUD_PostRender",
        "40 55 56 48 8D 6C 24 B1 48 81 EC C8 00 00 00 48 8B 01 48 8B F1",
    });

    uintptr_t offset;
    for (auto it = std::begin(lookups); it != std::end(lookups); ++it) {
        OffsetLookup lookup = *it;
        offset = FindOffset(process, modEntry, lookup);
        printf("%s: %llx\n", lookup.name, offset);
    }
    CloseHandle(process);
    return 0;
}

uintptr_t FindOffset(HANDLE process, MODULEENTRY32 modEntry, OffsetLookup lookup) {
    
    uintptr_t baseAddr = (uintptr_t)modEntry.modBaseAddr;
    BYTE pattern[64]; // Could allocate correct size
    std::stringstream mask;
    int len = parseHex(lookup.opcodes, &pattern[0], &mask);
    void *addr = PatternScanModule(process, modEntry, (char*)&pattern[0], mask.str().c_str());
    return (uintptr_t)addr+lookup.offset - baseAddr;
}

// Convert IDA Pro binary search strings into an array of bytes and a mask
// "48 8B ?? C4 53" = 0x48 0x8b 0x0 0xC4 mask = xx?x
int parseHex(std::string hex, BYTE *bytes, std::stringstream *mask) {

    std::istringstream ss(hex);
    std::string text;
    int i = 0;
    while (std::getline(ss, text, ' ')) {
        BYTE value = 0;
        if (text.c_str()[0] == '?') {
            *mask << "?"; 
        } else {
            *mask << "x";
            value = strtol(text.c_str(), NULL, 16);
        }
        bytes[i] = value;
        i++;
    }
    return i;

}