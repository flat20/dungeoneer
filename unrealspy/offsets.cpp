
#include <cstdio>
#include <sstream>
#include "offsets.h"
#include <Windows.h>
#include <tlhelp32.h>

namespace offsets {


    void FindAddresses(HANDLE process, std::vector<OpcodeAddress*>& lookups) {

        DWORD pid = GetProcessId(process);
        MODULEENTRY32 modEntry = GetModule(pid);
        if (modEntry.th32ModuleID == 0) {
            printf("Unable to find module. %ld\n", GetLastError());
            return;
        }

        struct Pattern {
            OpcodeAddress* opcode;
            BYTE values[128];
            char mask[128]; // Not null-terminated
            size_t length;
            bool found = false;
        };

        std::vector<Pattern> patterns;
        for (OpcodeAddress* opcode: lookups) {
            std::string opcodes = opcode->GetOpcodes();
            Pattern pattern = {opcode};
            pattern.length = parseHex(opcodes, &pattern.values[0], &pattern.mask[0]);

            patterns.push_back(pattern);
        }

        uintptr_t baseAddr = (uintptr_t)modEntry.modBaseAddr;
        uintptr_t endAddr = baseAddr + modEntry.modBaseSize;
        int numPatterns = patterns.size();

        for (MemoryIterator it(process, baseAddr, endAddr); it; ++it) {

            for(auto pit = std::begin(patterns); pit != std::end(patterns); ++pit) {

                Pattern pattern = *pit;
                if (pattern.found) {
                    continue;
                }

                int index = PatternScan(*it, it.GetBytesRead(), &pattern.values[0], &pattern.mask[0], pattern.length);

                if (index != -1) {
                    uintptr_t addr = it.GetCurrentAddr() + index;
                    pattern.opcode->SetAddress(addr);
                    pattern.found = true; // erase pattern instead?
                    numPatterns--;
                }
            }
            if (numPatterns == 0) {
                printf("all found\n");
                break;
            }
        }

    }

    // // Lookup offsets using search strings and convert to runtime addresses.
    // // lookups is a map like:
    // // ["AHUD_DrawRect"] = "48 8B C4 48 89 ?? ?? 57 48 81 EC E0"
    // // Returns a map keyed by the same string name and a uintptr_t which is the found address.
    // std::map<UE4Reference,uintptr_t> FindAddresses(HANDLE process, std::map<UE4Reference,std::string> opcodes) {

    //     std::map<UE4Reference,uintptr_t> results;

    //     DWORD pid = GetProcessId(process);
    //     MODULEENTRY32 modEntry = GetModule(pid);
    //     if (modEntry.th32ModuleID == 0) {
    //         printf("Unable to find module. %ld\n", GetLastError());
    //         return results;
    //     }

    //     return FindAddresses(process, modEntry, opcodes);
    // }

    // std::map<UE4Reference,uintptr_t> FindAddresses(HANDLE process, MODULEENTRY32 modEntry, std::map<UE4Reference, std::string> opcodes) {

    //     struct Pattern {
    //         UE4Reference refName;
    //         BYTE values[128];
    //         char mask[128]; // Not null-terminated
    //         size_t length;
    //         bool found = false;
    //     };

    //     std::vector<Pattern> patterns;
    //     for (auto it = std::begin(opcodes); it != std::end(opcodes); ++it) {
    //         UE4Reference name = it->first;
    //         std::string opcode = it->second;

    //         Pattern pattern = {name};
    //         pattern.length = parseHex(opcode, &pattern.values[0], &pattern.mask[0]);

    //         patterns.push_back(pattern);
    //     }

    //     std::map<UE4Reference,uintptr_t> offsets;
    //     for (auto &it : patterns) {
    //         offsets[it.refName] = 0;
    //     }

    //     uintptr_t baseAddr = (uintptr_t)modEntry.modBaseAddr;
    //     uintptr_t endAddr = baseAddr + modEntry.modBaseSize;
    //     int numPatterns = patterns.size();

    //     for (MemoryIterator it(process, baseAddr, endAddr); it; ++it) {

    //         for(auto pit = std::begin(patterns); pit != std::end(patterns); ++pit) {

    //             Pattern pattern = *pit;
    //             if (pattern.found) {
    //                 continue;
    //             }

    //             int index = PatternScan(*it, it.GetBytesRead(), &pattern.values[0], &pattern.mask[0], pattern.length);

    //             if (index != -1) {
    //                 uintptr_t addr = it.GetCurrentAddr() + index;
    //                 offsets[pattern.refName] = addr;
    //                 pattern.found = true; // erase pattern instead?
    //                 numPatterns--;
    //             }
    //         }
    //         if (numPatterns == 0) {
    //             printf("all found\n");
    //             break;
    //         }
    //     }

    //     return offsets;
    // }

    uintptr_t PatternScan(char* bytes, size_t size, const BYTE* pattern, const char* mask, size_t patternLength) {

        //printf("size %zd patlen %zd\n", size, patternLength);
        for (unsigned int i = 0; i <= size - patternLength; i++) {
            bool found = true;
            for (unsigned int j = 0; j < patternLength; j++) {
                if (mask[j] != '?' && pattern[j] != (BYTE)*(bytes + i + j)) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return (uintptr_t)i;
            }
        }
        return -1;
    }

    // Convert IDA Pro binary search strings into an array of bytes and a mask
    // "48 8B ?? C4 53" = 0x48 0x8b 0x0 0xC4 mask = xx?x
    size_t parseHex(std::string hex, BYTE *bytes, char *mask) {

        std::istringstream ss(hex);
        std::string text;
        int i = 0;
        while (std::getline(ss, text, ' ')) {
            BYTE value = 0;
            if (text.c_str()[0] == '?') {
                mask[i] = '?'; 
            } else {
                mask[i] = 'x';
                value = strtol(text.c_str(), NULL, 16);
            }
            bytes[i] = value;

            i++;
        }
        return i;

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
//                printf("%ws\n", curr.szModule);
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