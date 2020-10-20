
#include <functional>
#include <vector>
#include <list>
#include <map>
#include <unreal.h>

struct UObjectData {
    UObject *object;
    void *value;    // Maybe?
    std::string name;
    std::string clsName;
};
// View?
struct TreeNode {
    UObjectData data;

    std::map<UObject *,TreeNode> children;
};

namespace debug {
    typedef std::function<void (bool result)> CommandExecutor;

    void AddExecutor(CommandExecutor);
    // Probably will need this since UI shouldn't have it.
    std::vector<UObject*> Search(const char *obj, const char *cls);
    std::vector<UObjectData> ListProperties(UObject *obj);
}

