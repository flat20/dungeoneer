
#include <Windows.h>

#include <cstdio>
#include <tlhelp32.h>
#include <sstream>
#include <vector>
#include <map>
#include "offsets.h"
#include "unrealspy.h"

namespace offsets {


    // Some defaults for us.
    std::map<UE4Reference, std::string> defaultAddressLookups = {
        {RefFName_GetNames,         "48 83 EC 28 ?? ?? ?? ?? ?? ?? ?? 48 85 C0 ?? ?? B9 08 08 00 00 48 89 5C 24 20"},
        {RefFRawObjectIterator_Ctor,"84 D2 48 C7 41 10 00 00 00 00 B8 FF FF FF FF ?? ?? ?? ?? ?? ?? ?? 89 41 08 4C 8B D1 4C 89 01"},
        {"AHUD_DrawRect",           "48 8B C4 48 89 58 08 57 48 81 EC E0 00 00 00 0F 29 70 E8 48 8B FA 0F 29 78 D8 0F 28 F3 0F 28 FA 48 8B D9"},
        {"AHUD_DrawText",           "40 55 56 57 48 81 EC 30 02 00 00 44 0F 29 84 24 00 02 00 00"},
        {"AHUD_GetTextSize",        "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 40 49 8B F9 49 8B F0 48 8B EA 48 8B D9 ?? ?? ?? ?? ?? 84 C0"},
        {RefStaticLoadObject,       "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 18 FE FF FF 48 81 EC E8 02 00 00 ?? ?? ?? ?? ?? ?? ?? 48 33 C4 48 89 85 D0 01 00 00 48 8B 85 68 02 00 00"},
        {RefStaticLoadClass,        "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 08 FF FF FF 48 81 EC F8 01 00 00 ?? ?? ?? ?? ?? ?? ?? 48 33 C4 48 89 85 E0 00 00 00 8B BD 60 01 00 00"},
        {RefLoadPackage,            "48 8B C4 53 56 48 83 EC 68 48 89 68 08 48 8B EA 4C 89 60 18 33 D2 4C 89 68 E8 4C 8B E1 4C 89 70 E0 48 8D 48 C8 4C 89 78 D8 45 33 ED"},
        {RefUObject_ProcessEvent,   "40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC F0 00 00 00 48 8D 6C 24 30 48 89 9D 18 01 00 00"},
        {RefAHUD_PostRender,        "40 55 56 48 8D 6C 24 B1 48 81 EC C8 00 00 00 48 8B 01 48 8B F1"},
    };

    // Lookup offsets using search strings and convert to runtime addresses.
    // lookups is a map like:
    // ["AHUD_DrawRect"] = "48 8B C4 48 89 ?? ?? 57 48 81 EC E0"
    // Returns a map keyed by the same string name and a uintptr_t which is the found address.
    // TODO void* ?
    std::map<UE4Reference,uintptr_t> FindAddresses(HANDLE process, std::map<UE4Reference,std::string> lookups) {

        std::map<UE4Reference,uintptr_t> results;

        DWORD pid = GetProcessId(process);
        MODULEENTRY32 modEntry = GetModule(pid);
        if (modEntry.th32ModuleID == 0) {
            printf("Unable to find module. %d\n", GetLastError());
            return results;
        }

        uintptr_t baseAddr = (uintptr_t)modEntry.modBaseAddr;
        uintptr_t offset;
        for (auto &it = std::begin(lookups); it != std::end(lookups); ++it) {
            std::string name = it->first;
            std::string opcodes = it->second;
            offset = FindOffset(process, modEntry, opcodes);
            uintptr_t addr = baseAddr + offset;
            printf("%s: %llx = %llx\n", name.c_str(), (uint64)offset, (uint64)addr);
            results[name] = addr;
        }
        return results;
    }


    uintptr_t FindOffset(HANDLE process, MODULEENTRY32 modEntry, std::string opcodes) {
        
        uintptr_t baseAddr = (uintptr_t)modEntry.modBaseAddr;
        BYTE pattern[64]; // Could allocate correct size
        std::stringstream mask;
        int len = parseHex(opcodes, &pattern[0], &mask);
        void *addr = PatternScanModule(process, modEntry, (char*)&pattern[0], mask.str().c_str());
        return (uintptr_t)addr - baseAddr;
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
    // Now just gets the first module which is _probably_ the main one anyway.
    MODULEENTRY32 GetModule(const DWORD &pid) {
        MODULEENTRY32 modEntry = {0};

        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);

        if (snapshot != INVALID_HANDLE_VALUE) {
            MODULEENTRY32 curr = {0};
            curr.dwSize = sizeof(MODULEENTRY32);

            if (Module32First(snapshot, &curr)) {
                modEntry = curr;
                // do {
                //     if (strcmp((const char*)curr.szModule, modName) == 0) {
                //         modEntry = curr;
                //         break;
                //     }
                // } while (Module32Next(snapshot, &curr));
            }
            CloseHandle(snapshot);
        }
        return modEntry;
    }
}