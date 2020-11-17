#include "launcher.h"

int main(int argc, char *argv[]) {

    // quick way to override which dll to inject.
    std::string dll = "dungeoneer.dll";
    if (argc == 2) {
        dll = argv[1];
    }

    const std::vector<std::string> exeFiles = {"Dungeons-Win64-Shipping.exe", "Dungeons.exe"};
    return Launch(dll, exeFiles);
}
