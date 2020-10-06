#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <map>

namespace offsets {
    struct OffsetLookup {
        const char *name;
        const char *opcodes;
        uintptr_t offset; // in case base address of the opcodes isn't where we can find our value.
    };

    std::map<std::string,uintptr_t> FindAddresses(HANDLE process, const char *moduleName);
    uintptr_t FindOffset(HANDLE process, MODULEENTRY32 modEntry, OffsetLookup lookup);
    MODULEENTRY32 GetModule(const DWORD &pid, const char *modName);
    int parseHex(std::string hex, BYTE *bytes, std::stringstream *mask);
    // Taken from https://github.com/0xZ0F/CPPMemory/blob/master/x64/Scanning.cpp

    // Actual pattern scanning:
    void* PatternScan(char* bytes, size_t size, const char* pattern, const char* mask);

    // Wrapper:
    void* PatternScanProcess(HANDLE hProc, uintptr_t begin, uintptr_t end, const char* pattern, const char* mask);

    // Wrapper for scanning modules:
    void* PatternScanModule(HANDLE hProc, MODULEENTRY32 modEntry, const char* pattern, const char* mask);
}

