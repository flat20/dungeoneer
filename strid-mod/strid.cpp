
#include <functional>
#include <map>
#include <ctime>
#include <chrono>
#include <codecvt>
#include <string>
#include <set>
#include <algorithm>
#include <vector>


#include "strid.h"


ModuleInfo modInfo = {
    DUNGEONEER_VERSION,
    "Strid DPS",
};

void makeFString(FString *str, std::wstring wide);
std::wstring makeWide(std::string text);

std::map<DamageTypeID, DamageType> damageTypes { 
    {"MeleeDamageGameplayEffect", DamageType{"Melee", true, true, true, false, false, -0.2}},
    {"BaseProjectileDamageGameplayEffect", DamageType{"Ranged", true, true, true, false, false, -0.2}},
    {"SwirlingDamageGameplayEffect", DamageType{"Swirling", true, true, true, false, false, -0.2}},
    {"ShockwaveDamageGameplayEffect", DamageType{"Shockwave", true, true, true, false, false, -0.2}},
    {"HarvesterDamageGameplayEffect", DamageType{"Harvester", true, true, true, false, false, -0.2}},
    {"TargetingStrikeDamageItemGameplayEffect", DamageType{"Lightning Rod", true, true, true, false, false, -0.2}},
    {"TNTBoxDamageGameplayEffect", DamageType{"TNT Box", true, true, true, false, false, -0.2}},
    {"LifestealGameplayEffect", DamageType{"Lifesteal", true, true, true, false, false, 0.2}},

    
    //LifestealGameplayEffect // Should be amount?
    // For LifeSteal:
    //HealingModCalculation.Default__HealingModCalculation->
    //MeleeDamageItemPowerGameplayEffect
    //MeleeDamageItemPowerGameplayEffect
    //BP_SpeedDownGameplayEffect_C
    //GenerateSoulsGameplayEffect
};


// For any damagetypes we haven't defined. Mostly souls and things like that.
// Should hide them by default eventually.
DamageType damageTypeDefaults = DamageType{
    "", true, false, false, false, true, 1.0
};

Meter meter;

void formatDamageAmount(long long amount, char *str) {
    const char *sizes[4] = { "", "K", "M", "B" };
 
    int i;
    double value = amount;
    for (i = 0; i < 4 && amount >= 1000; i++, amount /= 1000)
        value = amount / 1000.0;
 
    if (i == 0) {
        sprintf(str, "%.0f", value);
    } else {
        sprintf(str, "%.2f %s", value, sizes[i]);
    }
 
 //   return strcat(strcat(str, " "), sizes[i]);
}



struct comp
{
	//template<typename T>
	bool operator()(const std::pair<DamageTypeID, Damage*> &a, const std::pair<DamageTypeID, Damage*> &b) const
	{
		return a.second->amount < b.second->amount;
	}
};


// UProperty *GetPropertyByName(UStruct *s, const char *name) {
    
//     UProperty *found = nullptr;
//     iterateStruct(s, [&](UProperty *p){
//         if (strcmp(getName(p), name) == 0) {
//             found = p;
//             return true;
//         }
//         return false;
//     });
//     return found;
// }

//RangedDamageModCalculation.CalculateBaseMagnitude() params 2
void HandleDamageModCalculation(UObject* object, UFunction* func, void *params) {

    printf("%s.%s->%s(%llx)\n", getName(object->ClassPrivate),getName(object),getName(func), (uint64)params);

    // iteratePropertiesRecursive(func, params, 0, [&](UProperty *p, void *container, int depth) {
        
    //     printf("%*s", depth, "");
    //     dumpProperty(p, container);
    //     printf("\n");

    //     return false;
    // });

    if (params != nullptr) {
        
        UObject *Def = util::GetPropertyValueByPath<UObject>(func, params, "Spec/Def");
        char *meterType = getName(Def->ClassPrivate);
    
        float *meterAmount = util::GetPropertyValueByPath<float>(func, params, "ReturnValue");

        // bool result = findPropertyByPath(func, params, "Spec/CapturedRelevantAttributes/SourceAttributes", [&](UProperty *p, void *container) {
        //     // ArrayProperty
        //     FScriptArray *sa = GetPropertyValue<FScriptArray>(p, container);
        //     UArrayProperty *ap = (UArrayProperty*)p;
        //     UProperty *inner = ap->Inner;
        //     printf(",innerClass:%s,%llx,firstNext: %llx, innerEleSize:%x,innerFlags:%llx,innerCastFlags:%x", getName(inner->ClassPrivate), (uint64)inner->ClassPrivate, (uint64)inner->NextRef, inner->ElementSize, inner->PropertyFlags, inner->ObjectFlags);
        //     printf("=%d,%d,%llx\n", sa->ArrayNum, sa->ArrayMax, (uint64)sa->Data);
        //     // According to IDA Pro rcx+70h is an FString
        //     char *ptr = (char *)sa->Data;
        //     for (int i=0; i<sa->ArrayNum; i++) {
        //         printf("Inner: %d\n", i);
        //         hexDump(ptr, inner->ElementSize);

        //         CapturedAttribute* attr = (CapturedAttribute*)ptr;
        //         printf("str: %.*ws\n", attr->toCapture.name.Data.ArrayNum, (wchar_t*)attr->toCapture.name.Data.Data);
        //         printf("obj1 %s (%s) obj2 %s (%s)\n", getName(attr->toCapture.obj1), getName(attr->toCapture.obj1->ClassPrivate), getName(attr->toCapture.obj2), getName(attr->toCapture.obj2->ClassPrivate));
        //         float *am = GetPropertyValue<float>((UProperty *)attr->toCapture.obj1, (void*)attr->toCapture.obj1);
        //         printf("value: %f\n", *am);
        //         ptr += inner->ElementSize;
        //     }
        // });

        // result = findPropertyByPath(func, params, "Spec/Def/Executions", [&](UProperty *p, void *container) {
        //     // ArrayProperty
        //     FScriptArray *sa = GetPropertyValue<FScriptArray>(p, container);
        //     UArrayProperty *ap = (UArrayProperty*)p;
        //     UProperty *inner = ap->Inner;
        //     printf(",innerClass:%s,%llx,firstNext: %llx, innerEleSize:%x,innerFlags:%llx,innerCastFlags:%x", getName(inner->ClassPrivate), (uint64)inner->ClassPrivate, (uint64)inner->NextRef, inner->ElementSize, inner->PropertyFlags, inner->ObjectFlags);
        //     printf("=%d,%d,%llx\n", sa->ArrayNum, sa->ArrayMax, (uint64)sa->Data);
        //     char *ptr = (char *)sa->Data;
        //     for (int i=0; i<sa->ArrayNum; i++) {
        //         printf("Inner: %d\n", i);
        //         hexDump(ptr, inner->ElementSize);
        //         Execution* v = (Execution*)ptr;
        //         printf("execution object %s (%s)\n", getName(v->object), getName(v->object->ClassPrivate));
        //         ptr += inner->ElementSize;
        //     }
        // });

        // Get current timestamp

        auto now = high_resolution_clock::now();

        if (meterAmount != nullptr && meterType != nullptr) {

            // Resets meter after 5 seconds, also from first hit
            if (duration_cast<seconds>(now - meter.lastUpdate).count() > 5) {
                meter.damageSources.clear(); // Delete old Damage*s??
                meter.started = now;   
                meter.isRunning = true; 
            }
            


            // // Disable all unknowns for now
            // if (damageTypes.find(meterType) == damageTypes.end()) {
            //     return 0;
            // }

            // Are c++ maps really this stupid? Just return me null if at() can't find it
            // like every other language does.
            if (meter.damageSources.find(meterType) == meter.damageSources.end()) {
                meter.damageSources.insert(std::make_pair(meterType, new Damage));
                // TODO We never destruct this "new Damage"
            }

            Damage *damage = meter.damageSources.at(meterType);
            damage->type = meterType;
            damage->amount += *meterAmount;
            damage->count++;

            meter.lastUpdate = now;
        }

        // Somewhere between model and view.
        auto elapsed = now - meter.started;
        auto ms = duration_cast<milliseconds>(elapsed).count();

        float seconds = (float)ms/1000.0f;

        meter.view.damages.clear();

        float totalPerSecond = 0.0;
        for (auto it=meter.damageSources.begin(); it!=meter.damageSources.end(); ++it) {
            //DamageTypeID type = it->first;
            Damage *damage = it->second;

            damage->amountPercentage = 0.0;
            damage->amountPerSecond = damage->amount / seconds;
            totalPerSecond += damage->amountPerSecond;

            DamageView dv = DamageView{damage};
            meter.view.damages.push_back(dv);
        }

        // Calculate percentages
        for (auto &dv: meter.view.damages) {
            dv.damage->amountPercentage = dv.damage->amountPerSecond / totalPerSecond;
        }


        // This is the view stuff. Sort the array and then create strings

        std::sort(std::begin(meter.view.damages), std::end(meter.view.damages), [](const DamageView &a, const DamageView &b) {
            return a.damage->amountPerSecond < b.damage->amountPerSecond;
        });

        // final render
        for (auto &dv: meter.view.damages) {
            
            DamageType *dt = &damageTypeDefaults;
            dt->displayName = (std::string)dv.damage->type;
            if (damageTypes.find(dv.damage->type) != damageTypes.end()) {
                dt = &damageTypes.at(dv.damage->type);
            }

            float amount = dv.damage->amount * dt->multiplier;
            float amountPerSecond = dv.damage->amountPerSecond * dt->multiplier;

            // TODO model shouldn't do view stuff.
            // On the other hand. the text doesn't need to be recreated every frame if data
            // doesn't change.
            std::string strName = "";
//            damage->view.name.clear();

            strName += dt->displayName;
            if (!dt->showCountAsAmount) {
                 strName += " (" + std::to_string((int)dv.damage->count) + ")";
            }

            // I can't get GetTextSize to measure width correctly for short strings.
            // so I'm adding some spaces to it..
            std::string strAmount = "      ";
            if (dt->showAverage) {
                strAmount += std::to_string((int)(amount / (float)dv.damage->count));
            }
            if (dt->showPerSecond && seconds > 0) {
                char formatted[64]; 
                formatDamageAmount((long)(amountPerSecond), &formatted[0]);
                strAmount += " " + std::string(formatted);
            }
            if (dt->showPercentage) {
                char percentage[10];
                sprintf(percentage, "%3.2f", dv.damage->amountPercentage * 100);
                strAmount += ", " + std::string(percentage) + "%";
            }
            if (dt->showCountAsAmount) { // For souls, etc
                strAmount += " " + std::to_string((int)dv.damage->count);
            }

            dv.nameW = makeWide(strName);
            dv.amountW = makeWide(strAmount);
        }
    }
    return;
}

Dungeoneer *dungeoneer;
SpyData *spyData;

UFont *font = nullptr;

std::wstring makeWide(std::string text) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(text);
}

void makeFString(FString *str, std::wstring wide) {
    const wchar_t *wideChars = wide.c_str();                // get the wchar_t

    str->Data.Data = (void*)wideChars;
    str->Data.ArrayNum = wcslen(wideChars)+2; // Not sure why +1
    str->Data.ArrayMax = str->Data.ArrayNum;
}

// I wonder if PostRender is called in same thread as ProcessEvent? Hopefully..
void AHUD_PostRender(void *hud) {

    FLinearColor textColor {1.0, 1.0, 1.0, 1.0};
    FLinearColor bg {0.1, 0.1, 0.1, 0.6};
    spyData->AHUD_DrawRect(hud, bg, 20.0, 20.0, 400.0, 160.0);

    float y = 30;
    for (auto &dv: meter.view.damages) {

        // Name - left aligned
        if (dv.nameW.length() > 0) {
            makeFString(&dv.name, dv.nameW);
            spyData->AHUD_DrawText(hud, &dv.name, textColor, 30, y, font, 1.f, false);
        }

        // Amount - right aligned.
        if (dv.amountW.length() > 0) {
            makeFString(&dv.amount, dv.amountW);
            float width = 0.0;
            float height = 0.0;
            spyData->AHUD_GetTextSize(hud, &dv.amount, &width, &height, font, 1.f);
            spyData->AHUD_DrawText(hud, &dv.amount, textColor, 420 - 10 - width, y, font, 1.f, false); // right - margin - textWidth
        }

        y += 20; // Only if we actually printed something.

        
    }

}

void UObject_ProcessEvent(UObject* object, UFunction* func, void *params) {
    char *funcName = getName(func);
    if (strcmp(funcName, "CalculateBaseMagnitude") == 0) {
        HandleDamageModCalculation(object, func, params);
    }
}

// This should be called from Dungeoneer after loading this DLL.
void ModMain(Dungeoneer *dng, Module *mod) {

    dungeoneer = dng;
    spyData = dng->spyData;

    //findObjectsByClassName(spyData->GUObjectArray, "Font");

    font = (UFont*)findObjectByName(spyData->GUObjectArray, "NotoSans", "Font");
    //font = (UFont*)findObjectByName(GUObjectArray, "Minecraft", "Font");
    if (font != nullptr) {
        printf("font: %s %s\n", getName(font), getName(font->ClassPrivate));
    } else {
        printf("font not found!\n");
    }
    
    dng->AddFunctionHandler(mod, RefUObject_ProcessEvent, &UObject_ProcessEvent);
    dng->AddFunctionHandler(mod, RefAHUD_PostRender, &AHUD_PostRender);

}
