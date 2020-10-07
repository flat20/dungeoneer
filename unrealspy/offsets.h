#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <map>
#include <unrealspy.h>

namespace offsets {

    // ["name"] = opcodes string
    extern std::map<UE4Reference,std::string> defaultAddressLookups;

    std::map<UE4Reference,uintptr_t> FindAddresses(HANDLE process, std::map<std::string,std::string> lookups);
    uintptr_t FindOffset(HANDLE process, MODULEENTRY32 modEntry, std::string opcodes);
    MODULEENTRY32 GetModule(const DWORD &pid);
    int parseHex(std::string hex, BYTE *bytes, std::stringstream *mask);


    // Taken from https://github.com/0xZ0F/CPPMemory/blob/master/x64/Scanning.cpp

    // Actual pattern scanning:
    void* PatternScan(char* bytes, size_t size, const char* pattern, const char* mask);

    // Wrapper:
    void* PatternScanProcess(HANDLE hProc, uintptr_t begin, uintptr_t end, const char* pattern, const char* mask);

    // Wrapper for scanning modules:
    void* PatternScanModule(HANDLE hProc, MODULEENTRY32 modEntry, const char* pattern, const char* mask);
}

