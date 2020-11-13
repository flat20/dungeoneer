#include <launcher.h>
#include <vector>

int main(int argc, char *argv[]) {
    std::vector<std::string> exeFiles = {"Fuser-Win64-Shipping.exe"};
    return Launch("fuser.dll", exeFiles);
}
