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
        
    class MemoryIterator {

    private:

        HANDLE hProc;
        char buffer[4096];
        SIZE_T bytesRead = 0;

        uintptr_t currentChunk;
        uintptr_t end;

    public:
        MemoryIterator(const HANDLE hProc, uintptr_t begin, uintptr_t end) : hProc(hProc), currentChunk(begin), end(end)
        {
            ReadData();
        }

        /** conversion to "bool" returning true if the iterator is valid. */
        inline explicit operator bool() const
        { 
            return hProc != NULL; 
        }
        /** inverse of the "bool" operator */
        inline bool operator !() const 
        {
            return !(bool)*this;
        }

        inline friend bool operator==(const MemoryIterator& Lhs, const MemoryIterator& Rhs) { return Lhs.hProc == Rhs.hProc; }
        inline friend bool operator!=(const MemoryIterator& Lhs, const MemoryIterator& Rhs) { return Lhs.hProc != Rhs.hProc; }

        inline void operator++() {
            ReadData();
        }

        inline char* operator*(){
            return (char*)&buffer;
        }

        inline char* operator->() {
            return (char*)&buffer;
        }

        inline SIZE_T GetBytesRead() {
            return bytesRead;
        }

        inline SIZE_T GetCurrentAddr() {
            return currentChunk;
        }

    protected:
        inline void ReadData() {
            currentChunk = currentChunk + bytesRead; // 0 first time anyway
            if (currentChunk < end) {
                DWORD oldProtect;
                VirtualProtectEx(hProc, (void*)currentChunk, sizeof(buffer), PAGE_EXECUTE_READWRITE, &oldProtect);
                ReadProcessMemory(hProc, (void *)currentChunk, &buffer, sizeof(buffer), &bytesRead);
                VirtualProtectEx(hProc, (void *)currentChunk, sizeof(buffer), oldProtect, &oldProtect);

                if (bytesRead == 0) {
                    hProc = NULL;
                }
            }
        }
    };

}
