
#include <Windows.h>

#include <cstdio>
#include <tlhelp32.h>
#include <sstream>
#include <vector>
#include <map>
#include "offsets.h"

namespace offsets {

    // Lookup offsets using search strings and convert to runtime addresses.
    std::map<std::string,uintptr_t> FindAddresses(HANDLE process, const char *moduleName) {
        
        std::map<std::string,uintptr_t> results;

        DWORD pid = GetProcessId(process);
        MODULEENTRY32 modEntry = GetModule(pid, moduleName);
        if (modEntry.th32ModuleID == 0) {
            printf("Unable to find %s module. %d\n", moduleName, GetLastError());
            return results;
        }

        std::vector<OffsetLookup> lookups;

        
        // This lookup only shows a function which has a parent function with a ref to the variable.  See guobjectarray.md
        // lookups.push_back({
        //     "GUObjectArray",
        //     "41 54 48 81 EC C0 00 00 00 44 0F B6 E1 44 0F 29 44 24 60 ?? ?? ?? ?? ?? ?? ?? 44 0F 28 C1",
        // });

        // // This lookup only shows a function which references the GNames variable. See gnames.md
        // lookups.push_back({
        //     "GNames",
        //     "48 83 EC 28 ?? ?? ?? ?? ?? ?? ?? 48 85 C0 ?? ?? B9 08 08 00 00 48 89 5C 24 20",
        // });
        
        // // Same as above, use IDA Pro for now to find it. See gengine.md
        // lookups.push_back({
        //     "gengine",
        //     "48 89 7C 24 30 48 8B C8 40 88 7C 24 28 45 33 C9 4C 8B C7 48 89 7C 24 20 48 8B D3 ?? ?? ?? ?? ?? 48 8B 4C 24 40",
        // });
        
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
        lookups.push_back({
            "FName_GetNames",
            "48 83 EC 28 ?? ?? ?? ?? ?? ?? ?? 48 85 C0 ?? ?? B9 08 08 00 00 48 89 5C 24 20",
        });
        lookups.push_back({
            "FRawObjectIterator_Ctor",
            "84 D2 48 C7 41 10 00 00 00 00 B8 FF FF FF FF ?? ?? ?? ?? ?? ?? ?? 89 41 08 4C 8B D1 4C 89 01",
        });


        uintptr_t baseAddr = (uintptr_t)modEntry.modBaseAddr;
        uintptr_t offset;
        for (auto it = std::begin(lookups); it != std::end(lookups); ++it) {
            OffsetLookup lookup = *it;
            offset = FindOffset(process, modEntry, lookup);
            uintptr_t addr = baseAddr + offset;
            printf("%s: %llx = %llx\n", lookup.name, offset, addr);
            results[lookup.name] = addr;
        }
        return results;
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



    // Actual pattern scanning:
    void* PatternScan(char* bytes, size_t size, const char* pattern, const char* mask) {
        size_t patternLength = strlen(mask);
        for (unsigned int i = 0; i < size - patternLength; i++) {
            bool found = true;
            for (unsigned int j = 0; j < patternLength; j++) {
                if (mask[j] != '?' && pattern[j] != *(bytes + i + j)) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return (void *)(bytes + i);
            }
        }
        return nullptr;
    }

    // Wrapper:
    void* PatternScanProcess(HANDLE hProc, uintptr_t begin, uintptr_t end, const char* pattern, const char* mask) {
        uintptr_t currentChunk = begin;
        SIZE_T bytesRead;

        while (currentChunk < end) {
            char buffer[4096];

            DWORD oldProtect;
            VirtualProtectEx(hProc, (void*)currentChunk, sizeof(buffer), PAGE_EXECUTE_READWRITE, &oldProtect);
            ReadProcessMemory(hProc, (void *)currentChunk, &buffer, sizeof(buffer), &bytesRead);
            VirtualProtectEx(hProc, (void *)currentChunk, sizeof(buffer), oldProtect, &oldProtect);

            if (bytesRead == 0) { return nullptr; }

            // Scan the current chunk of memory for the pattern we are looking for using PatternScan():
            void *internalAddress = PatternScan((char *)&buffer, bytesRead, pattern, mask);

            if (internalAddress != nullptr) {
                uintptr_t offsetFromBuffer = (uintptr_t)internalAddress - (uintptr_t)&buffer;
                return (void *)(currentChunk + offsetFromBuffer);
            } else {
                currentChunk = currentChunk + bytesRead;
            }
        }
        return nullptr;
    }

    // Wrapper for scanning modules:
    void* PatternScanModule(HANDLE hProc, MODULEENTRY32 modEntry, const char* pattern, const char* mask) {

        if (!modEntry.th32ModuleID) {
            return nullptr;
        }

        uintptr_t begin = (uintptr_t)modEntry.modBaseAddr;
        uintptr_t end = begin + modEntry.modBaseSize;
        return PatternScanProcess(hProc, begin, end, pattern, mask);
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
                    if (strcmp((const char*)curr.szModule, modName) == 0) {
                        modEntry = curr;
                        break;
                    }
                } while (Module32Next(snapshot, &curr));
            }
            CloseHandle(snapshot);
        }
        return modEntry;
    }
}