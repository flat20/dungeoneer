
#include <functional>
#include <vector>
#include <unreal.h>

namespace debug {
    typedef std::function<void (bool result)> CommandExecutor;

    void AddExecutor(CommandExecutor);
    // Probably will need this since UI shouldn't have it.
    std::vector<UObject*> Search(const char *obj, const char *cls);
}