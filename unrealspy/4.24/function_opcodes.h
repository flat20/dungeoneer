#pragma once

#include <vector>
#include <string>

// Base class used by offset pattern finding code.
class AddressLookup {
private:
    // "48 23 ?? 42 41"
    const char *Opcodes;

public:
    const char *GetOpcodes() {
        return Opcodes;
    }

    virtual void SetAddress(uintptr_t Address);

};

// Templated subclass with Call which makes it look
// and feel almost like a real function when using.
template<typename T>
class FuncRef : public AddressLookup {
public:

    FuncRef(const char *InOpcodes) : Opcodes(InOpcodes)
    {        
    }

    // Needed 
    void SetAddress(uintptr_t Address) {
        Call = (T)Address;
    }

    // Ref to function, named Call for neater calling code later.
    T Call;

};


namespace Functions
{
    static FuncRef<void (_stdcall *) (int value)> FName_GetNames;
    static FuncRef<void (_stdcall *) (int value)> XApa("123");
};

// // Can be defined in CPP, different per SDK
const FuncRef<void (_stdcall *) (int value)> Functions::FName_GetNames("48 83 EC 28 ?? ?? ?? ?? ?? ?? ?? 48 85 C0 ?? ?? B9 08 08 00 00 48 89 5C 24 20");

void MyTestCode() {

    Functions::FName_GetNames.SetAddress(0x123123);
    Functions::XApa.SetAddress(0x123123);
//    static const Bla apa("123");

    static FuncRef<void (_stdcall *) (int value)> Apa("123");
    static FuncRef<int (_stdcall *) (const char *str)> Another("123");
    Apa.Call(23);
    Another.Call("hej");
    Apa.SetAddress(0x2323);

    // Some defaults for us.
    std::vector<AddressLookup> defaultFunctions = {Apa, Functions::FName_GetNames, Functions::XApa, Another};
    defaultFunctions[0].GetOpcodes();
    defaultFunctions[0].SetAddress(23);

    //using ::f;
    //f(2,3);
    //using Vector = ::f<int,int>;
    //GetFunc<Functions::FName_GetNames>()
}