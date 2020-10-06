#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <string>

// Taken from https://github.com/0xZ0F/CPPMemory/blob/master/x64/Scanning.cpp

// Actual pattern scanning:
void* PatternScan(char* bytes, size_t size, const char* pattern, const char* mask);

// Wrapper:
void* PatternScanProcess(HANDLE hProc, uintptr_t begin, uintptr_t end, const char* pattern, const char* mask);

// Wrapper for scanning modules:
void* PatternScanModule(HANDLE hProc, MODULEENTRY32 modEntry, const char* pattern, const char* mask);

