#pragma once
#include <map>
#include <vector>
#include <chrono>

#include <dungeoneer_mod.h>

using namespace util;
using namespace std::chrono;

typedef std::string DamageTypeID;


struct Damage {
    DamageTypeID type;
    uint64 count = 0;
    float amount = 0.0; // make double. Also this is totalAmount
    float amountPerSecond = 0.0;
    float amountPercentage = 0.0;
};

struct DamageView { // Final output to render
    Damage *damage;
    FString name;   // Melee
    std::wstring nameW;
    FString amount; // 10.5k / s
    std::wstring amountW;
};



struct MeterView {
    // Damages ordered by their damage amounts
    std::vector<DamageView> damages;
};
struct Meter {
    bool isRunning = false;
    high_resolution_clock::time_point started;    // Timestamp
    high_resolution_clock::time_point lastUpdate;    // Timestamp
    std::map<DamageTypeID, Damage*> damageSources;
    MeterView view;
};


// DamageType display options. Rename?
struct DamageType {
    std::string displayName;   
    bool display;           // Should this type be visible
    bool showPerSecond;     // Hide DPS for stuff like souls, for now.
    bool showPercentage;    // Damage out of total
    bool showAverage;       // Average amount per hit
    bool showCountAsAmount; // For souls.. for now.
    float multiplier;       // Don't know why MCD has damage numbers * 5, but we put 0.2 in here and -0.2 if inverse is needed
};


struct Execution { // size 0x58
    UObject *object;
    char unknown[0x50];
    // 0214aae73b80  0000    00 4a ed ab 14 02 00 00   00 00 00 00 00 00 00 00   =214abed4a00  =0 - uobject
    // 0214aae73b90  0010    00 00 00 00 00 00 00 00   00 00 00 00 00 00 00 00   =0  =0
    // 0214aae73ba0  0020    00 00 00 00 00 00 00 00   00 00 00 00 00 00 00 00   =0  =0
    // 0214aae73bb0  0030    00 00 00 00 00 00 00 00   00 00 00 00 00 00 00 00   =0  =0
    // 0214aae73bc0  0040    00 00 00 00 00 00 00 00   00 00 00 00 00 00 00 00   =0  =0
    // 0214aae73bd0  0050    00 00 00 00 00 00 00 00   00 06 f1 ab 14 02 00 00   =0  =214abf10600
};

// The header, down to obj1 is used in Modifiers too.
struct AttributeToCapture { // size 0x28
    FString name;
    UObject *obj1;
    UObject *obj2;  // Comes back multiple times after captured, but obj1 is different for each "result"
    uint16 int1;
    uint16 int2;
    uint16 int3;
    uint16 int4;
};

// We get more captured attributes back
struct CapturedAttribute { // size 0x38
    AttributeToCapture toCapture;
    void *ptr1;
    void *ptr2;
};